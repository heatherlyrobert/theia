#include   "theia.h"


static char        comp_ord [20] = {  0,  1,  3,  2,  4,  6,  5,  7 };
static char        comp_txt [20] [20] = {
   "black", "d.red", "d.grn", "d.yel", "d.blu", "d.mag", "d.cyn", "d.brn",
   "white", "l.red", "l.grn", "l.yel", "l.blu", "l.mag", "l.cyn", "l.brn",
};

static char        arti_ord [20] = {  0,  7,  1,  6,  3,  2,  4,  5 };
static char        artistic [20] [20] = {
   "black", "d.red", "d.grn", "d.yel", "d.blu", "d.pur", "d.gld", "d.brn",
   "white", "l.red", "l.grn", "l.yel", "l.blu", "l.pur", "l.gld", "l.brn",
};

static char        mega_ord [20] = {  0, 1,  6,  3,  2,  7,  4,  5 };
static char        mega_txt [20] [20] = {
   "d.brn", "d.red", "d.grn", "d.yel", "d.blu", "d.pur", "d.gld", "d.cyn",
   "l.brn", "l.red", "l.grn", "l.yel", "l.blu", "l.pur", "l.gld", "l.cyn",
};

static char        full_ord [20] = {  1,  6,  3,  2,  7,  4,  5,  0 };
static char        full_txt [20] [20] = {
   "d.cri", "d.red", "d.grn", "d.yel", "d.blu", "d.pur", "d.gld", "d.cyn",
   "l.cri", "l.red", "l.grn", "l.yel", "l.blu", "l.pur", "l.gld", "l.cyn",
};

static char        colo_ord [20] = {  0,  1,  6,  3,  2,  4,  5,  7 };
static char        colo_txt [20] [20] = {
   "d.brn", "d.red", "d.grn", "d.yel", "d.blu", "d.pur", "d.ora", "d.cri",
   "l.brn", "l.red", "l.grn", "l.yel", "l.blu", "l.pur", "l.ora", "l.cri",
};


char
RPTG__single            (char n, char a_fg, char a_bg, char a_style)
{
   char        s           [LEN_LABEL] = "";
   char        t           [LEN_LABEL] = "";
   /*---(set foreground)-----------------*/
   if (a_fg >= 0 || a_bg >= 0)  printf ("\e[0m");
   if      (a_fg >= 24) { printf ("\e[7;1;3%dm", a_fg - 24);  a_fg -= 16; }
   else if (a_fg >= 16) { printf ("\e[7;3%dm"  , a_fg - 16);  a_fg -= 16; }
   else if (a_fg >=  8) { printf ("\e[1;3%dm"  , a_fg - 8);               }
   else if (a_fg >=  0) { printf ("\e[3%dm"    , a_fg);                   }
   /*---(set background)-----------------*/
   if      (a_bg >=  8) { printf ("\e[5;4%dm"  , a_bg - 8);               }
   else if (a_bg >=  0) { printf ("\e[4%dm"    , a_bg);                   }
   /*---(prepare hex)--------------------*/
   sprintf (s, "%-6.6x", g_fores [n].hex [a_fg]);
   sprintf (t, "%-6.6x", g_fores [n].hex [a_bg]);
   switch (a_style) {
   case 1 :
      switch (g_fores [n].style) {
      case 'a'  :  printf (" %-5.5s ", artistic [a_fg]);  break;
      case 'm'  :  printf (" %-5.5s ", mega_txt [a_fg]);  break;
      case 'f'  :  printf (" %-5.5s ", full_txt [a_fg]);  break;
      case 'c'  :  printf (" %-5.5s ", colo_txt [a_fg]);  break;
      default   :  printf (" %-5.5s ", comp_txt [a_fg]);  break;
      }
      break;
   case 2 :
      printf (" %-2.2s %-2.2s ", s, t);
      break;
   case 3 :
      printf (" %-2.2s %-2.2s ", s + 2, t + 2);
      break;
   case 4 :
      printf (" %-2.2s %-2.2s ", s + 4, t + 4);
      break;
   default :
      printf ("       ");
      break;
   }
   if (a_fg >= 0 || a_bg >= 0)  printf ("\e[0m");
   return 0;
}


char
RPTG__layout       (char n, char a_fg, char a_type)
{
   char        b           =    7;
   char        s           = g_fores [n].style;
   switch (s) {
   case 'a'  :  b = 7;  break;
   case 'm'  :  b = 7;  break;
   case 'f'  :  b = 7;  break;
   case 'c'  :  b = 6;  break;
   default   :  b = 7;  break;
   }
   /*> if (g_fores [n].style != 'c') {                                           <*/
   printf (" ");
   RPTG__single (n, a_fg +  8, -1      , a_type);
   if (s == 'c') {
      if (my.eterm > 0) {
         RPTG__single (n, a_fg + 24, -1       , a_type);
         RPTG__single (n, a_fg + 16, -1       , a_type);
      } else {
         RPTG__single (n, 0        , a_fg + 8 , a_type);
         RPTG__single (n, 0        , a_fg     , a_type);
      }
   }
   printf (" ");
   RPTG__single (n, a_fg    , a_fg + 8, a_type);
   RPTG__single (n, a_fg + 8, a_fg    , a_type);
   printf (" ");
   if (s != 'c') {
      RPTG__single (n, 0       , a_fg + 8, a_type);
      RPTG__single (n, 0       , a_fg    , a_type);
      printf (" ");
   }
   RPTG__single (n, a_fg    , 0    + 8, a_type);
   RPTG__single (n, a_fg + 8, 0       , a_type);
   printf (" ");
   RPTG__single (n, 0       , a_fg + 8, a_type);
   RPTG__single (n, 0    + 8, a_fg    , a_type);
   printf (" ");
   /*> RPTG__single (n, a_fg + 8,        2, a_type);                                   <*/
   /*> RPTG__single (n, a_fg + 8,        4, a_type);                                   <*/
   /*     0        1        2        3        4        5        6        7   */
   /*> "d.brn", "d.red", "d.grn", "d.yel", "d.blu", "d.pur", "d.ora", "d.cri",        <*/
   switch (a_fg) {
   case 0 :
      RPTG__single (n, a_fg    , 2 + 8   , a_type);
      RPTG__single (n, a_fg + 8, 2       , a_type);
      break;
   case 1 :
      RPTG__single (n, a_fg    , 4 + 8   , a_type);
      RPTG__single (n, a_fg + 8, 4       , a_type);
      break;
   case 6 : /* orange  */
      RPTG__single (n, a_fg    , 5 + 8   , a_type);
      RPTG__single (n, a_fg + 8, 5       , a_type);
      break;
   case 3 : /* yellow  */
      RPTG__single (n, a_fg    , 7 + 8   , a_type);
      RPTG__single (n, a_fg + 8, 7       , a_type);
      break;
   case 2 : /* green   */
      RPTG__single (n, a_fg    , 0 + 8   , a_type);
      RPTG__single (n, a_fg + 8, 0       , a_type);
      break;
   case 4 : /* blue    */
      RPTG__single (n, a_fg    , 1 + 8   , a_type);
      RPTG__single (n, a_fg + 8, 1       , a_type);
      break;
   case 5 : /* purple  */
      RPTG__single (n, a_fg    , 6 + 8   , a_type);
      RPTG__single (n, a_fg + 8, 6       , a_type);
      break;
   case 7 : /* crimson */
      RPTG__single (n, a_fg    , 3 + 8   , a_type);
      RPTG__single (n, a_fg + 8, 3       , a_type);
      break;
   default :
      RPTG__single (n, a_fg + 8,        5, a_type);
      RPTG__single (n, a_fg + 8,        7, a_type);
      break;
   }
   /*> } else {                                                                       <* 
    *>    RPTG__single (n, a_fg + 8, -1      , a_type);                                <* 
    *>    RPTG__single (n, a_fg    , a_fg + 8, a_type);                                <* 
    *>    RPTG__single (n, a_fg + 8, a_fg    , a_type);                                <* 
    *>    RPTG__single (n, 0    + 8, a_fg    , a_type);                                <* 
    *>    RPTG__single (n, a_fg    , 0    + 8, a_type);                                <* 
    *>    RPTG__single (n, a_fg + 8, 0       , a_type);                                <* 
    *>    RPTG__single (n, a_fg    , 1    + 8, a_type);                                <* 
    *>    RPTG__single (n, a_fg + 8, 1       , a_type);                                <* 
    *>    RPTG__single (n, a_fg + 8, 6       , a_type);                                <* 
    *>    RPTG__single (n, a_fg + 8, 3       , a_type);                                <* 
    *>    RPTG__single (n, a_fg + 8, b       , a_type);                                <* 
    *>    RPTG__single (n, a_fg + 8, 4       , a_type);                                <* 
    *>    RPTG__single (n, a_fg + 8, 5       , a_type);                                <* 
    *>    RPTG__single (n, a_fg + 8, 7       , a_type);                                <* 
    *> }                                                                              <*/
   printf ("\n");
}

char         /*--> show a narrow display of the scheme ---[ ------ [ ------ ]-*/
REPORT_quarter     (char *a_refno)
{
   char        n           =    0;
   char        i           =    0;
   char        x_fg        =    0;
   DEBUG_PROG  yLOG_enter   (__FUNCTION__);
   n = FORE_by_ref (a_refno);
   if (n < 0)  return 0;
   printf ("theia-euryphaessa (wide-shinning) terminal configuration for ansi 16-color terms\n");
   printf ("assortment of consistently nice contrasts           scheme [%s/%c] %s\n", g_fores  [n].refno, g_fores [n].style, g_fores [n].name);
   printf ("\n");
   for (i = 0;  i < 8; ++i) {
      switch (g_fores [n].style) {
      case 'a'  :  x_fg = arti_ord [i];  break;
      case 'm'  :  x_fg = mega_ord [i];  break;
      case 'f'  :  x_fg = full_ord [i];  break;
      case 'c'  :  x_fg = colo_ord [i];  break;
      default   :  x_fg = comp_ord [i];  break;
      }
      RPTG__layout (n, x_fg, 0);
      RPTG__layout (n, x_fg, 1);
      RPTG__layout (n, x_fg, 0);
      printf ("\n");
   }
   printf ("theia --quarter is my test for color schemes; perform here or i toss it\n");
   DEBUG_PROG  yLOG_exit    (__FUNCTION__);
   return 0;
}

