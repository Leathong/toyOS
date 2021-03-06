#ifndef __PRINTK_H__
#define __PRINTK_H__

#include <stdarg.h>

#define ZEROPAD     1
#define SIGN        2 /* unsigned/signed long */
#define PLUS        4
#define SPACE       8
#define LEFT        16
#define SPECIAL     32
#define SMALL       64
#define is_digit(c) ((c) >= '0' && (c) <= '9')

#define WHITE  0x00ffffff //白
#define BLACK  0x00000000 //黑
#define RED    0x00ff0000 //红
#define ORANGE 0x00ff8000 //橙
#define YELLOW 0x00ffff00 //黄
#define GREEN  0x0000ff00 //绿
#define BLUE   0x000000ff //蓝
#define INDIGO 0x0000ffff //靛
#define PURPLE 0x008000ff //紫

extern struct Position g_cursor;

struct Position {
  int XResolution;
  int YResolution;

  int XPosition;
  int YPosition;

  int XCharSize;
  int YCharSize;

  unsigned int* FB_addr;
  unsigned long FB_length;
};

extern "C" void
putchar(unsigned int* fb, int Xsize, int x, int y, unsigned int FRcolor, unsigned int BKcolor, unsigned char font);

int skip_atoi(const char** s);

#define do_div(n, base)                                                                                      \
  ({                                                                                                         \
    int __res;                                                                                               \
    __asm__("divq %%rcx" : "=a"(n), "=d"(__res) : "0"(n), "1"(0), "c"(base));                                \
    __res;                                                                                                   \
  })

static char* number(char* str, long num, int base, int size, int precision, int type);

int vsprintf(char* buf, const char* fmt, va_list args);

int color_printfk(unsigned int FRcolor, unsigned int BKcolor, const char* fmt, ...);
int printf(const char* fmt, ...);
extern "C" int color_printk(unsigned int FRcolor, unsigned int BKcolor, const char* str);

#endif
