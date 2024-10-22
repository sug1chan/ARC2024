int32_t ntohl(int32_t bn) {
    return (((bn & 0xFF000000) >> 24) |
            ((bn & 0x00FF0000) >> 8)  |
            ((bn & 0x0000FF00) << 8)  |
            ((bn & 0x000000FF) << 24));
}

int32_t parse(uint8_t *data, int32_t len, struct cmd_packet *res) {
    struct cmd_packet *pdata;
    if (len < 8)
        return -1;

    pdata = reinterpret_cast<cmd_packet*>(data);
    res->cmd = ntohl(pdata->cmd);
    res->opt = ntohl(pdata->opt);
    return 0;
}

