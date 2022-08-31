#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "big.h"

extern int curr_radix;

static int usage(void) {
    return 1;
}

static void fib(u32 f1, u32 f2, u32 n, BigInt* result) {
    BigInt p[4];
    big_init(&p[0], f1);
    big_init(&p[1], f2);
    big_init(&p[2], f1+f2);
    big_init(&p[3], f1+f2+f2);
//printf("[0]="); big_print(&p[0]); printf(" "); big_print(&p[1]); printf(" "); big_print(&p[2]); printf(" "); big_print(&p[3]); printf("\n");
    u32 i;
    for (i = 4; i < n; ++i) {
        big_add(&p[i&3], &p[(i+3)&3], &p[(i+2)&3]);
//printf("[%d]=",(int)i); big_print(&p[i&3]); printf("\n");
    }
    big_deinit(&p[n&3]);
    big_deinit(&p[(n+1)&3]);
    big_deinit(&p[(n+2)&3]);
    big_set(result, &p[(n+3)&3]);
}

static void test(int test_loops) {
}

static void print_fib(u32 n) {
    BigInt result;
    fib(1, 1, n, &result);
    big_print(&result);
    printf("\n");
}

int main(int argc, char* argv[]) {
    u32 n = 1;
    int ch;
    int test_loops = 0;
    while ((ch = getopt(argc, argv, "t:x")) >= 0) {
        switch (ch) {
        case 'd':
            curr_radix = 10;
            break;
        case 'x':
            curr_radix = 16;
            break;
        case 't':
            test_loops = atoi(optarg);
            break;
        default:
            usage();
            break;
        }
    }
    if (test_loops) {
        test(test_loops);
    } 
    for (; optind < argc; ++optind) {
        n = strtoull(argv[optind], NULL, 0);
        print_fib(n);
    }
}
