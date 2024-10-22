struct cmd_packet {
    int32_t cmd;
    int32_t opt;
};

int32_t parse(uint8_t, int32_t, struct cmd_packet*);
