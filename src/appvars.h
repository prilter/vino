#ifdef stddef_h
#else
  #include <stddef.h>
#endif

/* STRUCTURES */
typedef struct {
	char *fn;     /* FILENAME */
  char *info;   /* INFO */
  int    sym;   /* SYMBOL */
	size_t x;     /* X COORD */
	size_t y;     /* Y COORD */
	size_t yst;   /* START LINE(by y) TO PRINT */
	size_t xst;   /* START LINE(by x) TO PRINT */
  int saved;    /* SAVING */
  int mode;     /* MODE */
	char **entry; /* FILE TEXT */
} geometry;
#define USE_ARROWS 1


/* GEOMETRY */
/* KEYS */
#define CTRL(c)       ((c) & 0x1f)
#define C_s           0x13
#define C_q           0x11
#define C_f           0x66

#define ESC           0x1B
#define ENTER         0xD
#define BACKSPACE     0x7F
#define DELETE        0x7E
#define TAB           0x9

#define UP            0x103
#define DOWN          0x102
#define RIGHT         0x105
#define LEFT          0x104

#define COLON_KEY     0x3A
#define I_KEY         0x49
#define i_KEY         0x69
#define j_KEY         0x6A
#define k_KEY         0x6B
#define l_KEY         0x6C
#define L_KEY         0x4C
#define h_KEY         0x68
#define H_KEY         0x48
#define g_KEY         0x67
#define G_KEY         0x47
#define w_KEY         0x77
#define b_KEY         0x62
#define A_KEY         0x41
#define a_KEY         0x61
#define o_KEY         0x6F
#define O_KEY         0x4F
#define d_KEY         0x64
#define D_KEY         0x44
#define s_KEY         0x73
#define S_KEY         0x53



/* LENS */
#define BUFLEN      1024
#define LINELEN     1024
#define FILENAMELEN 1000
#define TABLEN      2


/* MODES */
#define CONSOLE 0
#define INSERT  1
