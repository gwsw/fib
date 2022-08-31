#include "big.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int curr_radix = 10;

void big_init(BigInt* b, u32 val) {
    b->val = malloc(sizeof(u32));
    b->valen = 1;
    b->val[0] = val;
}

void big_deinit(BigInt* b) {
    free(b->val);
    if (1) {
        b->val = NULL;
        b->valen = 0;
    }
}

static void big_setdigit(BigInt* b, int i, u32 digit) {
    if (i >= b->valen) {
        int valen = i + 1;
        u32* val = malloc(valen * sizeof(u32));
        memcpy(val, b->val, b->valen * sizeof(u32));
        memset(&val[b->valen], 0, (valen - b->valen) * sizeof(u32));
        free(b->val);
        b->val = val;
        b->valen = valen;
    }
    b->val[i] = digit;
}

void big_set(BigInt* dst, BigInt* src) {
    *dst = *src;
}

void big_add(BigInt* sum, BigInt* b1, BigInt* b2) {
    int valen = b1->valen;
    if (b2->valen > valen) valen = b2->valen;
    u32 carry = 0;
    for (int i = 0; i < valen; ++i) {
        u32 v1 = (i < b1->valen) ? b1->val[i] : 0;
        u32 v2 = (i < b2->valen) ? b2->val[i] : 0;
        u64 s = v1 + v2 + carry;
        carry = (u32)(s >> u32_bits);
        big_setdigit(sum, i, s);
    }
    if (carry)
        big_setdigit(sum, valen, carry);
}

void big_add32(BigInt* sum, BigInt* b1, u32 n2) {
    BigInt b2;
    big_init(&b2, n2);
    big_add(sum, b1, &b2);
    big_deinit(&b2);
}

void big_print_radix(BigInt* n, int radix) {
    if (radix <= 0) return;
    for (int i = n->valen-1; i >= 0; --i) {
        if (radix == 16)
            printf("%llx", (long long) n->val[i]);
        else 
            printf("%lld", (long long) n->val[i]);
        if (i > 0) printf(";");
    }
    unsigned long long r = 0;
    for (int i = n->valen-1; i >= 0; --i)
        r = (r << u32_bits) + n->val[i];
    printf((radix == 16) ? "(%llx)" : "(%llu)", r);
}

void big_print(BigInt* n) {
    big_print_radix(n, curr_radix);
}
