#define CMD_MAX 4

#define LIST_CAT_SIZE 5
#define LIST_SLOW_SIZE 2
#define LIST_HEATER_SIZE 2
#define LIST_ARM_SIZE 2

struct cmd_format {
    int32_t cmd;
    int32_t opt;
};

struct cmd {
    uint8_t *name;
    int32_t no;
};

struct cmd cmd_list[] = {
    {"CAT_MOVE",      1},
    {"CAT_SLOW_MODE", 2},
    {"HEATER_MODE",   3},
    {"ARM_MODE",      4}
};

void perr(char *p) {
    perror(p);
    exit(EXIT_FAILURE);
}

void show_dbg(struct cmd c, int32_t opt) {
    printf("send cmd = %s, opt = %d\n", c.name, opt);
}

void send_cmd(int32_t sf, struct cmd c, int32_t opt) {
    struct cmd_format data;
    data.cmd = htonl(c.no);
    data.opt = htonl(opt);
    if (send(sf, &data, sizeof data, 0) < 0) {
        perr("send() failed");
    }
}

void dbg(int32_t sf, int32_t index, int32_t opt) {
    struct cmd c = cmd_list[index];
    show_dbg(c, opt);
    send_cmd(sf, c, opt);
}

int32_t opt_catepillar[LIST_CAT_SIZE] = {
    0b1010,
    0b0101,
    0b1001,
    0b0110,
    0b0000
};

int32_t opt_slowmode[LIST_SLOW_SIZE] = {
    0b0001,
    0b0000
};

int32_t opt_heater[LIST_HEATER_SIZE] = {
    0b0001,
    0b0000
};

int32_t opt_arm[LIST_ARM_SIZE] = {
    0b0001,
    0b0000
};
