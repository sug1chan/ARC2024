#include "parse.h"

int parse(uint8_t *data, int32_t len, struct cmd_packet *res) {
    struct cmd_packet *pdata;
    if (len < 8)
        return -1;

    pdata = (struct cmd_pakcet *) data;
    res->cmd = ntohl(pdata->cmd);
    res->opt = ntohl(pdata->opt);
    return 0;
}

