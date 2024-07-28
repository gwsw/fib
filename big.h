
typedef unsigned long u32;
typedef unsigned long long u64;
#define u32_bits 32
///typedef unsigned char u32;
///typedef unsigned short u64;
///#define u32_bits 8

typedef struct BigInt {
    u32* val;
    int valen;
} BigInt;

void big_init(BigInt* b, u32 val);
void big_deinit(BigInt* b);
void big_set(BigInt* dst, BigInt* src);
void big_replace(BigInt* dst, BigInt* src);
void big_add32(BigInt* sum, BigInt* b1, u32 n2);
void big_add(BigInt* sum, BigInt* b1, BigInt* b2);
void big_print(BigInt* n);
void big_print_radix(BigInt* n, int radix);
