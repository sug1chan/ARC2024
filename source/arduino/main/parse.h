struct cmd_packet {
    int32_t cmd;
    int32_t opt;
};

int parse(uint8_t, int32_t, struct cmd_packet*);
