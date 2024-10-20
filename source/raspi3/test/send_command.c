#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "send_command.h"

// for debug param
int32_t is_once = 1;
int32_t loop = 1;

#define PORT 55555
// #define REMOTE_ADDR "127.0.0.1"
#define REMOTE_ADDR "192.168.5.10"

void start_debug(int32_t sf);
/* void perr(uint8_t *); */

int32_t *opt_list[CMD_MAX] = {
    opt_catepillar,
    opt_slowmode,
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
    int once = 1;
    while (once && loop) {
        int32_t i, j;

        for (i = 0; i < 4; i ++) {
            for (j = 0; j < opt_size[i]; j ++) {
                int _opt = opt_list[i][j];
                dbg(sf, i, _opt);
            }
        }
        if (is_once) {
            once = 0;
        }
    }
    sleep(10);
}
