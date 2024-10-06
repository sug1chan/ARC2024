#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT        55555
#define MAX_BUF_LEN 256
#define MAX_CMD_NUM 6

char *CMD_NAME[MAX_CMD_NUM] = {
    "CMD_NONE      ",
    "CAT_MOVE      ",
    "CAT_SLOW_MODE ",
    "HEATER_MODE   ",
    "ARM_MODE      ",
    "EMERGENCY_STOP",
};

char *get_cmd(int32_t cmd) {
    if (0 <= cmd && cmd < MAX_CMD_NUM)
        return CMD_NAME[cmd];
    else
        return CMD_NAME[0];
}

struct command {
    int32_t cmd;
    int32_t opt;
};

void main_app(int32_t);

void itob(int32_t b, uint8_t *res) {
    int32_t bit[33];
    int32_t count = 0, min_count = 8;

    while (min_count --) {
        bit[count++] = b % 2;
        b /= 2;
    }



    res[count] = '\0';
    int32_t bit_i, res_i;
    for (res_i = 0, bit_i = count - 1; bit_i >= 0; bit_i --, res_i ++) {
        res[res_i] = '0' + bit[bit_i];
    }
}

int32_t parse(uint8_t *data, size_t data_len, struct command *res) {
    struct command *cmd;
    if (data_len < 8)
        return -1;

    cmd = (struct command *) data;

    res->cmd = ntohl(cmd->cmd);
    res->opt = ntohl(cmd->opt);

    return 0;
}

int32_t main() {
    int32_t sock;
    struct sockaddr_in addr, client_addr;
    uint16_t listen_port = PORT;

    int32_t on = 0;

    if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        perror("socket() failed");
        exit(1);
    }

    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(listen_port);

    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on);

    if (bind(sock, (struct sockaddr *) &addr, sizeof addr) < 0) {
        perror("bind() failed");
        exit(1);
    }

    if (listen(sock, 5) < 0) {
        perror("listen() failed");
        exit(1);
    }

    while(1) {
        int32_t acc;
        struct sockaddr_in client_addr;
        int32_t client_addr_len;

        memset(&client_addr, 0, sizeof client_addr);
        client_addr_len = sizeof client_addr;

        if ((acc = accept(sock, (struct sockaddr *) &client_addr, &client_addr_len)) < 0) {
            perror("accept() failed");
            exit(1);
        }

        printf("Established!: addr = %s\n", inet_ntoa(client_addr.sin_addr));
        main_app(acc);
    }

    close(sock);
    return 0;
}

void main_app(int32_t sock) {
    uint8_t buf[MAX_BUF_LEN];
    uint8_t *sbuf, *ebuf, *cbuf, *nbuf;
    int32_t recv_len, total_buf_len;

    struct command res;

    sbuf = buf;
    ebuf = buf + MAX_BUF_LEN;
    cbuf = nbuf = sbuf;

    while(1) {
        // recv
        recv_len = 0;

        if (nbuf < ebuf) {
            if ((recv_len = recv(sock, nbuf, ebuf - nbuf, 0)) < 0) {
                perror("recv() failed");
                exit(1);
            } else if (recv_len == 0) {
                close(sock);
                return;
            }

            nbuf += recv_len;
        }

        /* printf("buf = %p, sbuf = %p, ebuf = %p\n", buf, sbuf, ebuf); */
        /* printf("cbuf = %p, nbuf = %p\n", cbuf, nbuf); */

        /* printf("recv: %d bytes\n", recv_len); */

        while ((total_buf_len = nbuf - cbuf) >= sizeof(struct command)) {
            if (parse(cbuf, total_buf_len, &res) != -1) {
                uint8_t p[33];
                itob(res.opt, p);

                printf("command = %s, opr = %s\n", get_cmd(res.cmd), p);

                cbuf += sizeof(struct command);

                if (cbuf >= ebuf)
                    cbuf = nbuf = cbuf;
            } else
                break;
        }
    }
    close(sock);
}
