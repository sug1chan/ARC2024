#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "send_command.h"

#define PORT 55555
#define REMOTE_ADDR "192.168.5.10"

void perr(char *p) {
    perror(p);
    exit(EXIT_FAILURE);
}

void (* dbg_func[CMD_MAX]) (int32_t) = {
    &dbg_catepillar,
    &dbg_showmode,
    &dbg_heater,
    &dbg_arm
};

int32_t *opt_list[CMD_MAX] = {
    opt_catepillar,
    opt_showmode,
    opt_heater,
    opt_arm,
};

int32_t opt_size[CMD_MAX] = {
    LIST_CAT_SIZE,
    LIST_SLOW_SIZE,
    LIST_HEATER_SIZE,
    LIST_ARM_SIZE
};


int32_t main() {
    int32_t sf;
    struct sockaddr_in addr;

    if ((sf = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        perr("socket() failed");

    memset(&addr, 0, sizeof addr);
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = inet_addr(REMOTE_ADDR);
    addr.sin_port        = htons(PORT);

    if (connect(sf, (struct sockaddr *) &addr, sizeof addr) < 0)
        perr("connect() failed ");

    start_debug(sf);

    close(sf);
    return 0;
}

void start_debug(int32_t sf) {
    while (1) {
        int32_t i;

        for (i = 0; i < 4; i ++) {

        }
    }
}
