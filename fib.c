#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "big.h"

extern int curr_radix;
#define num_hist 16

static int usage(void) {
    printf("usage: fib ...\n");
    return 1;
}

static void fib(u32 f1, u32 f2, u32 n, BigInt* result) {
    u32 i;
    u32 hm = num_hist - 1;
    BigInt pp[num_hist];
    #define pindex(i) (((i)+num_hist) & hm)
    #define p(i) &pp[pindex(i)]
    for (i = 0; i < num_hist; ++i)
        big_init(p(i), (i == 0) ? f1 : (i == 1) ? f2 : 0);
    for (i = 2; i < n; ++i) {
        BigInt s;
printf("add: "); big_print(p(i-1)); printf(" + "); big_print(p(i-2)); printf(" = ");
        big_add(&s, p(i-1), p(i-2));
big_print(&s); printf("\n");
        big_replace(p(i), &s);
printf("repl[%d:%d] ", i, pindex(i)); big_print(p(i)); printf("\n");
    }
    for (i = 0; i < num_hist; ++i) {
        if (i == pindex(n-1))
            big_set(result, p(i));
        else 
            big_deinit(p(i));
    }
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
    while ((ch = getopt(argc, argv, "dt:x")) >= 0) {
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
