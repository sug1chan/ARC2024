#include <stdio.h>
#include <stdbool.h>
#include "../hardware/operate.h"

typedef struct {
    short ln;
    short lr;
    short rn;
    short rr;
} signal;

bool get_cmd(opr op, signal* sig) {
    char ln, lr, rn, rr;

    ln = (op & OPR_L_NORMAL)  == OPR_L_NORMAL;
    lr = (op & OPR_L_REVERSE) == OPR_L_REVERSE;
    rn = (op & OPR_R_NORMAL)  == OPR_R_NORMAL;
    rr = (op & OPR_R_REVERSE) == OPR_R_REVERSE;

    sig->ln = (int)ln;
    sig->lr = (int)lr;
    sig->rn = (int)rn;
    sig->rr = (int)rr;
    return;
}

void print_signal(char op) {
    signal sig;
    get_cmd(op, &sig);

    printf(" = %d %d %d %d\n", sig.ln, sig.lr, sig.rn, sig.rr);
    return;
};


int main() {
    printf("PWM_DEFAULT     = %x\n", PWM_DEFAULT);
    printf("PWM_ARM_DEFAULT = %x\n", PWM_DEFAULT);

    printf("HAND_REST    = %x\n", HAND_REST);
    printf("HAND_NORMAL  = %x\n", HAND_OPEN);
    printf("HAND_REVERSE = %x\n", HAND_CLOSE);

    printf("CTPL_REST    = %x", CTPL_REST);
    print_signal(CTPL_REST);
    printf("CTPL_FWRD    = %x", CTPL_FWRD);
    print_signal(CTPL_FWRD);
    printf("CTPL_LFWD    = %x", CTPL_LFWD);
    print_signal(CTPL_LFWD);
    printf("CTPL_RFWD    = %x", CTPL_RFWD);
    print_signal(CTPL_RFWD);
    printf("CTPL_LBWD    = %x", CTPL_LBWD);
    print_signal(CTPL_LBWD);
    printf("CTPL_RBWD    = %x", CTPL_RBWD);
    print_signal(CTPL_RBWD);
    printf("CTPL_LTRN    = %x", CTPL_LTRN);
    print_signal(CTPL_LTRN);
    printf("CTPL_RTRN    = %x", CTPL_RTRN);
    print_signal(CTPL_RTRN);
    
    return 0;
}

