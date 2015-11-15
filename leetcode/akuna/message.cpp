#include <iostream>
#include <fstream>
#include <memory>
#include <iostream>
#include <string>
#include <cstring>
#include <exception>
#include <cstdint>
#include <algorithm>
#include "message.h"

template<typename type>
static int read(std::ifstream& input, type& val) 
{
    return input.read(reinterpret_cast<char*>(&val), sizeof(val)).gcount();
}

static int read(std::ifstream& input, char* val, size_t len)
{
    return input.read(val, len).gcount();
}

OrderEntryMessage::OrderEntryMessage(Header& h, std::ifstream &fs) : header(h)
{
    char tmp[256];
    int len = 0;
    len += read(fs, price);
    len += read(fs, qty);

    len += read(fs, tmp, 10);
    instrument = std::move(std::string(tmp, 10));

    len += read(fs, side);
    len += read(fs, client_assigned_id);
    len += read(fs, time_in_force);

    len += read(fs, tmp, 3);
    trader_tag = std::move(std::string(tmp, 3));

    len += read(fs, firm_id);

    int firm_len = read(fs, tmp, (h.msg_len - len - 8));
    firm = std::string(tmp, firm_len);

    read(fs, tmp, 8);
    if (strncmp(tmp, "DBDBDBDB", 8) != 0)
        throw std::runtime_error("Termination string is wrong");
}


OrderAckMessage::OrderAckMessage(Header& h, std::ifstream &fs) : header(h) 
{
    char tmp[8];
    int len = 0;

    read(fs, order_id);
    read(fs, client_id);
    read(fs, order_status);
    read(fs, reject_code);

    read(fs, tmp, 8);

    if (strncmp(tmp, "DBDBDBDB", 8) != 0)
        throw std::runtime_error("Termination string is wrong");
}


OrderFillMessage::OrderFillMessage(Header& h, std::ifstream &fs) : header(h)  
{
    char tmp[8];
    int len = 0;

    read(fs, order_id);
    read(fs, fill_price);
    read(fs, fill_qty);
    read(fs, no_of_contras);

    for (int i = 0; i < no_of_contras; i++) {
        read(fs, groups[i].firm_id);
        read(fs, tmp, 3);
        groups[i].trader_tag = std::move(std::string(tmp, 3));
        read(fs, groups[i].qty);
    }

    read(fs, tmp, 8);
    if (strncmp(tmp, "DBDBDBDB", 8) != 0)
    {
        tmp[8] = '\0';
        throw std::runtime_error("Termination string is wrong");
        std::cout << tmp <<std::endl;
    }
}

Parser::Parser(std::string filename) :
        total_packets(0)
{
    try
    {
        fs. open(filename, std::ios::in | std::ios::binary);
    }
    catch (...) 
    {
        throw std::runtime_error("Failed to open data file");
    }
}

int Parser::parse_header(Header &h) 
{
    if (!fs.eof())  
    {
        read(fs, h);
        
        if (h.marker != (((uint16_t)'T') << 8) + 'S')
            return -1;
    }

    return -1;
}

void Parser::operator()()
{
   
    while(!fs.eof())
    {
        Header h;

        if (!parse_header(h) || !h.msg_len) break;

        switch (h.msg_type)
        {
            case ORDER_ENTRY: 
                {
                    OrderEntryMessage *oe = NULL;

                    try
                    {
                        oe = new OrderEntryMessage(h, fs);
                        total_packets ++;
                    }
                    catch (std::exception &e) 
                    {
                        //std::cout << e.what() <<std::endl;
                        break;
                    }

                    order_entries.insert(std::make_pair(oe->get_client_id(), oe));
                    Trader *trader = new Trader(oe->get_trader_tag());
                    if (traders.find(trader->tag) == traders.end())
                        traders.insert(std::make_pair(trader->tag, trader));

                    if (firms.find(oe->get_firm_id()) == firms.end()) 
                    {
                        Firm *firm = new Firm(oe->get_firm());
                        firm->traders.insert(std::make_pair(oe->get_trader_tag(), trader));
                        firms.insert(std::make_pair(oe->get_firm_id(), firm));
                    }
                    else 
                    {
                        firms[oe->get_firm_id()]->traders.insert(std::make_pair(oe->get_trader_tag(), trader));
                    }
                    
                    break;
                }
            case ORDER_ACK:
                {
                    OrderAckMessage *oa = NULL; 
                    
                    try 
                    {
                        oa = new OrderAckMessage(h, fs);
                        total_packets ++;
                    }
                    catch (std::exception &e)
                    {
                        //std::cout << e.what() <<std::endl;
                        break;
                    }


                    if (order_entries.find(oa->get_client_id()) == order_entries.end()) 
                    {
                        std::cout << "Warning: unmatched client_id"<< std::endl;
                        break;
                    }

                    order_acks.insert(std::make_pair(oa->get_order_id(), order_entries[oa->get_client_id()]));

                    if (oa->status() == OrderAckMessage::GOOD )
                    {
                       OrderEntryMessage *oe = order_entries[oa->get_client_id()];

                       if (oe->get_order_type() == OrderEntryMessage::GFD)
                       {
                           Trader *trader = firms[oe->get_firm_id()]->traders[oe->get_trader_tag()];
                           trader->gfd_qty += oe->get_qty();
                       }
                    }

                    break;
                }
            case ORDER_FILL: 
                {
                    OrderFillMessage *of = NULL;
                    try 
                    {
                        of = new OrderFillMessage(h, fs);
                        total_packets ++;
                    }
                    catch (std::exception &e) 
                    {
                        //std::cout << e.what() <<std::endl;
                        break;
                    }

                    order_fills.insert(std::make_pair(of->get_order_id(), of));
                    
                    if (order_acks.find(of->get_order_id()) == order_acks.end()) 
                    {
                        std::cout << "Warninng: unmatched order id" << std::endl;
                        break;
                    }

                    OrderEntryMessage *oe = order_acks[of->get_order_id()];
                    Trader *trader = firms[oe->get_firm_id()]->traders[oe->get_trader_tag()];
                    trader->fill_qty += of->get_fill_qty();

                    trades[oe->get_instrument()]  += of->get_fill_qty();

                    for (int i = 0; i < of->get_group_num(); i++) {
                        OrderFillMessage::Group *gp = of->get_group(i);
                        Trader *trader = firms[gp->firm_id]->traders[gp->trader_tag];
                        trader->fill_qty += gp->qty;
                    }

                    break;
                }
            default: 
                break;
        }
    }
}

int main(int argc, char* argv[]) 
{
    if (argc < 2) {
        std::cout << "Usage: " << std::endl;
        std::cout << argv[0] << " file_name" << std::endl;
        return -1;
    }

    Parser parser(argv[1]);
    parser();

    // Q1 -Q3
    std::cout << parser.total_packets << ", " << parser.order_entries.size() << ", ";
    std::cout << parser.order_acks.size() << ", " << parser.order_fills.size() << ", ";

    Trader *most_active_trader = (*parser.traders.begin()).second;
    Trader *most_liquidity_trader = (*parser.traders.begin()).second;

    uint32_t max_fill_qty = most_active_trader->fill_qty;
    uint32_t max_gfd_qty = most_liquidity_trader->gfd_qty;

    for (auto trader : parser.traders) 
    {
    //    std::cout << trader.first << ":" << trader.second->fill_qty << ":" << trader.second->gfd_qty << std::endl;
        if (trader.second->fill_qty > max_fill_qty)
        {
            max_fill_qty = trader.second->fill_qty;
            most_active_trader = trader.second; 
        }

       if (trader.second->gfd_qty > max_gfd_qty) 
       {
           max_gfd_qty = trader.second->gfd_qty;
           most_liquidity_trader = trader.second;
       }
    }

    std::cout << most_active_trader->fill_qty<< ", " << most_liquidity_trader->gfd_qty << ", ";
    std::cout << most_active_trader->tag << ", " << most_liquidity_trader->tag << ", ";

    for (auto trade : parser.trades) 
    {
        std::cout << trade.first << ":" << trade.second << ", ";
    }

    std::cout << std::endl;

    return 0;
}

