
struct msg_header
{
    uint16_t marker;
    uint8_t type;
    uint8_t msg_direction;
    uint16_t msg_len;
    uint64_t sequence_id;
    uint64_t timestamp;
};

struct order 
{
    struct msg_header;
    uint64_t price;
    uint32_t qty;
    uint64_t client_assigned_id;
    uint8_t firm_id;
    char instrument[10];
    char trader_tag[3];
    char *firm = 0;
    char termination[8];
};

struct ack
{
    struct header;
    uint32_t order_id;
    uint64_t client_id;
    uint8_t order_status;
    uint8_t reject_code;
    char termination[8];
}

struct order_fill 
{
    struct header;
    uint32_t order_id;
    uint64_t fill_price;
    uint32_t fill_qty;
    uint8_t num_of_contras;
    struct party_group {
        uint32_t qty;
        uint8_t firm_id;
        char trader_tag[3];
    };
    char termination[8];
}
    
