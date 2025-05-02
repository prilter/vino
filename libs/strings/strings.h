#ifdef stddef_h
#else
  #include <stddef.h>
#endif



extern char **_erase(char **, size_t);
extern char  *_erase_s(char *, size_t);

extern char **_insert(char **, size_t, const char *);
extern char	 *_insert_s(char *, size_t, char);

extern char **_append(char **, const char *);
extern char  *_append_s(char *, const char *);

extern size_t size(char **);
extern char **_tabs_to_spaces(char **, size_t n);



#define substr(s, x)		      (s+x)                       /* GET SUBLINE */

#define erase(ss, y)          (ss = _erase(ss, y))        /* ERASE y CHAR * FROM CHAR ** */
#define erase_s(s, x)         (s = _erase_s(s, x))        /* ERASE SYMBOL FROM CHAR * */

#define insert_s(s, x, c)     (s = _insert_s(s, x, c))    /* INSERT IN CHAR * SYMBOL */
#define insert(ss, y, s)      (ss = _insert(ss, y, s))    /* INSERT IN CHAR ** CONST CHAR * */

#define append(ss, s)         (ss = _append(ss, s))       /* APPEND TO THE END OF CHAR ** SOME CONST CHAR * */
#define append_s(dst, src)    (dst = _append_s(dst, src)) /* LIKE STRCAT, BUT CONSIDER OUT OF MEMORY */

#define tabs_to_spaces(ss,n)  (ss = _tabs_to_spaces(ss, n))
