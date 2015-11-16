#pragma once
#include <stdint.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <fstream>
#include <vector>
#include <map>


struct Header 
{
    enum MSG_TYPE
    {
        ORDER_ENTRY = 1, 
        ORDER_ACK = 2,
        ORDER_FILL = 3
    };

    uint16_t marker;
    uint8_t msg_type;
    uint64_t sid;
    uint64_t timestamp;
    uint8_t direction;
    uint16_t msg_len;
} __attribute__((__packed__));

std::ostream& operator<<(std::ostream& os, const Header& h) {
    os << "marker: " << h.marker << "\n"
       << "msg_type: " << static_cast<unsigned>(h.msg_type) << "\n"
       << "sequence_id: " << h.sid << "\n"
       << "timestamp: " << h.timestamp << "\n"
       << "msg_direction: " << static_cast<unsigned>(h.direction) << "\n"
       << "msg_len: " << h.msg_len << "\n";
    return os;
}


class OrderEntryMessage 
{
    public: 
        enum 
        {
            IDC = 1,
            GFD = 2
        };
    public:
        explicit OrderEntryMessage(Header&, std::ifstream&);
        inline uint32_t get_qty() const { return qty; };
        inline std::string get_instrument() const { return instrument; };
        inline uint64_t get_client_id() const { return client_assigned_id; };
        inline int get_order_type() const { return time_in_force; };
        inline std::string get_trader_tag() const { return trader_tag; };
        inline uint8_t get_firm_id() const { return firm_id; } ;
        inline std::string get_firm() const { return firm; };
        Header header;

    private:
        uint64_t price;
        uint32_t qty;
        std::string instrument;
        uint8_t side; // buy = 1, sell = 2
        uint64_t client_assigned_id;
        uint8_t time_in_force; // IOC = 1, GFD = 2
        std::string trader_tag;
        uint8_t firm_id;
        std::string firm;
};

class OrderAckMessage
{
    public:
        enum STATUS
        {
            GOOD = 1,
            REJECT = 2
        };

    public:
        explicit OrderAckMessage(Header &, std::ifstream &);
        inline uint32_t get_order_id() const { return order_id; };
        inline uint64_t get_client_id() const { return client_id; };
        inline uint8_t status() const { return order_status;};
        Header header;

    private:
        uint32_t order_id;
        uint64_t client_id;
        uint8_t order_status;
        uint8_t reject_code;
};

class OrderFillMessage
{
    public: 
        struct Group 
        {
            uint8_t firm_id;
            std::string trader_tag;
            uint32_t qty;
        };

        const static uint16_t max_group = 256;

    public:
        explicit OrderFillMessage(Header &, std::ifstream &);
        uint32_t get_order_id() const { return order_id; };
        uint32_t get_fill_qty() const { return fill_qty; };
        uint8_t get_group_num() const { return no_of_contras; };
        Group* get_group(uint8_t i) { return &groups[i]; }
        Header header;

    private:
        uint32_t order_id;
        uint64_t fill_price;
        uint32_t fill_qty;
        uint8_t no_of_contras;
        Group groups[max_group];
};

class Trader
{
    public:
        explicit Trader(std::string tag) :tag(tag), gfd_qty(0), fill_qty(0){};
        std::string tag;
        uint32_t gfd_qty;
        uint32_t fill_qty;
};

class Firm 
{
    public:
        explicit Firm(std::string firm) : name(firm) {};
        std::string name;
        std::unordered_map<std::string, Trader*> traders;
};


class Parser 
{
    public:
        explicit Parser (std::string filename);
        int parse_header(Header &);
        ~Parser()
        {
            fs.close();
        };

        void operator()();

        uint32_t total_packets;

        std::unordered_map<uint64_t, OrderEntryMessage*> order_entries;
        std::unordered_map<uint32_t, OrderEntryMessage*> order_acks;
        std::unordered_map<uint32_t, OrderFillMessage*> order_fills;

        std::unordered_map<uint8_t, Firm*> firms;
        std::map<std::string, Trader*> traders;
        std::map<std::string, int> trades;

        std::ifstream fs;
};

