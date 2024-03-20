#include   "theia.h"

#define    MAX_X     2000
#define    MAX_Y     500

static char  s_desk   [MAX_Y][MAX_X];

static short s_xfull = 1366;
static short s_yfull = 1536;

static char  s_xmult =  6;       /* character size to scale                   */
static char  s_ymult = 10;       /*    x and y into ascii size blocks         */

static float s_xchar = 0.0;
static float s_ychar = 0.0;

static float s_xscal = 0.0;
static float s_yscal = 0.0;

static char  s_xnewc = 0.0;
static char  s_ynewc = 0.0;

static float s_scale = 0.0;      /* final product vs. full size               */

static char  s_xpage = 0;
static char  s_ypage = 0;

static float s_xfact = 0.0;
static float s_yfact = 0.0;

static short s_yredo = 0;
static short s_xredo = 0;

char
PAGE__scaler            (float a_scale)
{
   char        rce         =  -10;
   short       x, y;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_senter  (__FUNCTION__);
   /*---(default)------------------------*/
   s_xchar = s_ychar = 0;
   s_scale = 0.0;
   s_xpage = s_ypage = 0;
   s_xfact = s_yfact = 0.0;
   /*---(scaling)------------------------*/
   DEBUG_PROG   yLOG_sdouble (a_scale);
   --rce;  if (a_scale < 0.1 || a_scale > 0.5) {
      DEBUG_PROG   yLOG_snote   ("scale out of 0.1 - 0.5 range");
      DEBUG_PROG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   s_scale = a_scale;
   /*---(vertical)-----------------------*/
   s_ychar = (float) s_yfull / (float) s_ymult;
   s_yscal = s_yfull * s_scale;
   s_ynewc = trunc ((float) s_yscal / (float) s_ymult);
   if (s_ynewc % 2 == 0) {
      ++s_ynewc;
      /*
       *  s_ynewc = (s_yfull * s_scale) / s_ymult;
       *
       *  s_ynewc * s_ymult = s_yfull * s_scale;
       *  
       *  (s_ynewc * s_ymult) / s_yfull = s_scale;
       *
       */
      s_scale = (float) (s_ynewc * s_ymult) / (float) s_yfull;
   }
   s_yfact = (float) s_yfull / (float) (s_ynewc - 1);
   s_yredo = (s_ynewc - 1) * s_yfact;
   s_ypage = s_ynewc;
   DEBUG_PROG   yLOG_svalue  ("y", s_ypage);
   /*---(horizontal)---------------------*/
   s_xchar = (float) s_xfull / (float) s_xmult;
   s_xscal = s_xfull * s_scale;
   s_xnewc = trunc ((float) s_xscal / (float) s_xmult);
   s_xfact = (float) s_xfull / (float) (s_xnewc - 1);
   s_xredo = (s_xnewc - 1) * s_xfact;
   s_xpage = s_xnewc;
   DEBUG_PROG   yLOG_sint    (s_xchar);
   DEBUG_PROG   yLOG_svalue  ("x", s_xpage);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
PAGE__init              (void)
{
   int         x, y;
   for (x = 0; x < MAX_X; ++x) {
      for (y = 0; y < MAX_Y; ++y) {
         s_desk [y][x] = '\0';
      }
   }
   return 0;
}

char
PAGE__single            (char a_type, short a_wide, char a_prefix [LEN_TERSE], char a_single [LEN_FULL], char a_break [LEN_TERSE])
{
   int         i           =    0;
   int         h           =    0;
   /*---(blank it out)-------------------*/
   for (i = 0; i < LEN_FULL; ++i)  a_single [i] = '\0';
   /*---(prefix)-------------------------*/
   if (a_prefix != NULL) {
      switch (a_type) {
      case 'h' : ystrlcpy (a_prefix, "   Ï ", LEN_TERSE);   break;
      case 'e' : ystrlcpy (a_prefix, "·····", LEN_TERSE);   break;
      case 'm' : ystrlcpy (a_prefix, "   Ï ", LEN_TERSE);   break;
      case '-' : ystrlcpy (a_prefix, "     ", LEN_TERSE);   break;
      }
   }
   /*---(ends)---------------------------*/
   if (a_single != NULL) {
      switch (a_type) {
      case 'h' : a_single [0] = a_single [a_wide - 1] = 'Œ';   break;
      case 'e' : a_single [0] = a_single [a_wide - 1] = '´';   break;
      case 'm' : a_single [0] = a_single [a_wide - 1] = '·';   break;
      case '-' : a_single [0] = a_single [a_wide - 1] = '·';   break;
      }
   }
   /*---(fill)---------------------------*/
   if (a_single != NULL) {
      for (i = 1; i < a_wide - 1;  ++i) {
         switch (a_type) {
         case 'h' : a_single [i] = '­';   break;
         case 'e' : a_single [i] = ' ';   break;
         case 'm' : a_single [i] = ' ';   break;
         case '-' : a_single [i] = ' ';   break;
         }
      }
   }
   /*---(end lines centers)--------------*/
   if (a_single != NULL) {
      if (strchr ("he", a_type) != NULL) {
         h = trunc (a_wide / 2.0);
         if (a_wide % 2 == 0)  {
            if (a_type == 'e') {
               for (i = h - 3; i > 0; i -= 2) a_single [i] = '·';
               for (i = h + 2; i < a_wide - 2; i += 2) a_single [i] = '·';
            }
            if (a_type == 'e')  a_single [h - 1] = a_single [h] = '·';
            else                a_single [h - 1] = a_single [h] = 'Ï';
         }
         else {
            if (a_type == 'e') {
               for (i = 1; i < a_wide - 1; i += 2) a_single [i] = '·';
            }
            if (a_type == 'e')   a_single [h] = '·';
            else                 a_single [h] = 'Ï';
         }
      }
   }
   /*---(breaks)-------------------------*/
   if (a_break != NULL) {
      switch (a_type) {
      case 'h' : ystrlcpy (a_break, "   ", LEN_TERSE);   break;
      case 'e' : ystrlcpy (a_break, "···", LEN_TERSE);   break;
      case 'm' : ystrlcpy (a_break, " · ", LEN_TERSE);   break;
      case '-' : ystrlcpy (a_break, "   ", LEN_TERSE);   break;
      }
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
PAGE__line              (char x_grid, cchar a_prefix [LEN_TERSE], cchar a_single [LEN_FULL], cchar a_break [LEN_TERSE], char r_desk [LEN_FULL])
{
   int         i           =    0;
   char        x_suffix    [LEN_TERSE] = "";
   char        l           =    0;
   for (i = 0; i < LEN_FULL; ++i)  r_desk [i] = '\0';
   ystrlcpy (r_desk, a_prefix, LEN_FULL);
   for (i = 0; i < x_grid; ++i) {
      if (i > 0)  ystrlcat (r_desk, a_break, LEN_FULL);
      ystrlcat (r_desk, a_single, LEN_FULL);
   }
   l = strlen (a_prefix);
   for (i = 0; i < LEN_TERSE; ++i)  x_suffix [i] = '\0';
   for (i = 0; i < l        ; ++i)  x_suffix [i] = a_prefix [l - i - 1];
   ystrlcat (r_desk, x_suffix, LEN_FULL);
   return 0;
}

char
PAGE__block             (short x_offset, char x_grid, short a_wide, short a_tall)
{
   int         y           =    0;
   int         h1          =    0;
   char        h2          =    0;
   char        n           =    0;
   char        x_pre       [LEN_TERSE] = "";
   char        x_sin       [LEN_FULL]  = "";
   char        x_brk       [LEN_TERSE] = "";
   char        x_mpre      [LEN_TERSE] = "";
   char        x_msin      [LEN_FULL]  = "";
   char        x_mbrk      [LEN_TERSE] = "";
   PAGE__single ('e', a_wide, x_pre, x_sin, x_brk);
   PAGE__line   (x_grid, x_pre, x_sin, x_brk, s_desk [x_offset + 0]);
   PAGE__line   (x_grid, x_pre, x_sin, x_brk, s_desk [x_offset + a_tall - 1]);
   PAGE__single ('-', a_wide, x_pre , x_sin , x_brk );
   PAGE__single ('m', a_wide, x_mpre, x_msin, x_mbrk);
   h2 = trunc (a_tall / 2.0);
   if (a_tall % 2 == 0)  h1 = h2 - 1;
   else                  h1 = h2;
   for (y = 1; y < a_tall - 1; ++y) {
      if      (y == h1)   PAGE__line   (x_grid, x_mpre, x_msin, x_mbrk, s_desk [x_offset + y]);
      else if (y == h2)   PAGE__line   (x_grid, x_mpre, x_msin, x_mbrk, s_desk [x_offset + y]);
      else                PAGE__line   (x_grid, x_pre , x_sin , x_brk , s_desk [x_offset + y]);
   }
   return 0;
}

char
PAGE__outline           (char a_ygrid, char a_xgrid)
{
   int         x, y;
   char        i           =    0;
   char        l           =    0;
   short       o           =    0;
   short       h           =    0;
   char        t           [LEN_FULL]  = "";
   char        x_pre       [LEN_TERSE] = "";
   char        x_sin       [LEN_FULL]  = "";
   char        x_brk       [LEN_TERSE] = "";
   /*---(create single page header)------*/
   PAGE__single ('h', s_xnewc, x_pre, x_sin, x_brk);
   h = (s_ypage + 1) / 2.0;
   for (y = 0; y < a_ygrid; ++y) {
      o = y * (s_ynewc + 1);
      PAGE__line   (a_xgrid, x_pre, x_sin, x_brk, s_desk [o]);
      ++o;
      PAGE__block (o, a_xgrid, s_xpage, h);
      o += h - 1;
      PAGE__block (o, a_xgrid, s_xpage, h);
   }
   o = y * (s_ynewc + 1);
   PAGE__line   (a_xgrid, x_pre, x_sin, x_brk, s_desk [o]);

   return 0;

   /*---(top and bottom)-----------------*/
   sprintf (s_desk [ 0], "     Œ· · · · · · · · · · · · · · · · · · ´´ · · · · · · · · · · · · · · · · · ·Œ     ");
   sprintf (s_desk [ 1], "·····´· · · · · · · · · · · · · · · · · · ´´ · · · · · · · · · · · · · · · · · ·´·····");
   sprintf (s_desk [51], "·····´· · · · · · · · · · · · · · · · · · ´´ · · · · · · · · · · · · · · · · · ·´·····");
   sprintf (s_desk [52], "     Œ· · · · · · · · · · · · · · · · · · ´´ · · · · · · · · · · · · · · · · · ·Œ     ");
   /*---(fill in)------------------------*/
   for (y = 1; y <= 49; ++y) {
      if      (y == 13)  sprintf (s_desk [y + 1], "   ´ ·                                                                          · ´   ");
      else if (y == 14)  sprintf (s_desk [y + 1], "   ´ ·                                                                          · ´   ");
      else if (y == 25)  sprintf (s_desk [y + 1], "···´·´····································´´····································´·´···");
      else if (y == 38)  sprintf (s_desk [y + 1], "   ´ ·                                                                          · ´   ");
      else if (y == 39)  sprintf (s_desk [y + 1], "   ´ ·                                                                          · ´   ");
      else               sprintf (s_desk [y + 1], "   · ·                                                                          · ·   ");
   }
   /*---(labels)-------------------------*/
   ystrlcpy (t, "upper screen", LEN_LABEL);
   l = strlen (t);
   for (i = 0; i < l; ++i) {
      y = 14 - (l / 2) + i;
      s_desk [y][ 1] = s_desk [y][84] = t [i];
   }
   ystrlcpy (t, "lower screen", LEN_LABEL);
   l = strlen (t);
   for (i = 0; i < l; ++i) {
      y = 39 - (l / 2) + i;
      s_desk [y][ 1] = s_desk [y][84] = t [i];
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
PAGE__print             (char a_ygrid, char a_desk, char a_total, char a_here)
{
   int         x, y;
   short       i           =    0;
   char        n           =    0;
   char        x_first     =  '-';
   short       x_lines     =    0;
   char        x_scale     [LEN_LABEL] = "";
   char        x_range     [LEN_LABEL] = "";
   if      (my.scale <= 0.110)   strcpy (x_scale, "--micro");
   else if (my.scale <= 0.160)   strcpy (x_scale, "--mini");
   else if (my.scale <= 0.210)   strcpy (x_scale, "--tiny");
   else if (my.scale <= 0.260)   strcpy (x_scale, "--small");
   else if (my.scale <= 0.340)   strcpy (x_scale, "--medium");
   else                          strcpy (x_scale, "--large");
   if      (my.range == 1)       strcpy (x_range, "--one");
   else if (my.range == 2)       strcpy (x_range, "--two");
   else if (my.range == 3)       strcpy (x_range, "--three");
   else if (my.range == 8)       strcpy (x_range, "--all");
   if (my.extra == 'y') {
      printf ("#!/usr/local/bin/theia --pager %s %s\n", x_scale, x_range);
      printf ("##   %s\n", P_ONELINE);
      printf ("##   report : pager view dual 1366 x 768 screens, %d desktops and %d windows\n", my.range, a_here);
      /*> printf ("\n");                                                                                                                                      <* 
       *> printf ("##      full  mul  chars    scale    -new-  chr  factor  check\n");                                                                        <* 
       *> printf ("##   y  %4d  %3d  %5.1f    %5.3f    %5.1f  %3d  %6.3f  %4d\n", s_yfull, s_ymult, s_ychar, s_scale, s_yscal , s_ynewc, s_yfact, s_yredo);   <* 
       *> printf ("##   x  %4d  %3d  %5.1f    %5.3f    %5.1f  %3d  %6.3f  %4d\n", s_xfull, s_xmult, s_xchar, s_scale, s_xscal , s_xnewc, s_xfact, s_xredo);   <*/
      printf ("\n\n");
   }
   x_lines = s_ynewc * a_ygrid + a_ygrid;
   for (y = 0; y <= x_lines; ++y) {
      printf ("%s\n", s_desk [y]);
   }
   if (my.list == 'y') {
      x_first = '-';
      for (i = 0; i < g_nrun; ++i) {
         n = FIFO_by_stack (i);
         if (n < 0)  continue;
         if (g_runs [n].r_desk != a_desk)  continue;
         if (g_runs [n].r_scrn != 't')     continue;
         if (x_first == '-') {
            printf ("\n\n");
            printf ("## --) ---top------  st --x--  --y--  --w--  --t--  ---window-title--------------------\n");
            x_first = 'y';
         }
         printf ("## %2d) %-12.12s  %2d  %4d   %4d   %4d   %4d   %-35.35s\n",
               g_runs [n].r_order, g_runs [n].r_terse, g_runs [n].r_stack,
               g_runs [n].r_left, g_runs [n].r_topp, g_runs [n].r_wide, g_runs [n].r_tall,
               g_runs [n].r_title);
      }
      x_first = '-';
      for (i = 0; i < g_nrun; ++i) {
         n = FIFO_by_stack (i);
         if (n < 0)  continue;
         if (g_runs [n].r_desk != a_desk)  continue;
         if (g_runs [n].r_scrn != 'b')     continue;
         if (x_first == '-') {
            printf ("\n\n");
            printf ("## --) ---top------  st --x--  --y--  --w--  --t--  ---window-title--------------------\n");
            x_first = 'y';
         }
         printf ("## %2d) %-12.12s  %2d  %4d   %4d   %4d   %4d   %-35.35s\n",
               g_runs [n].r_order, g_runs [n].r_terse, g_runs [n].r_stack,
               g_runs [n].r_left, g_runs [n].r_topp, g_runs [n].r_wide, g_runs [n].r_tall,
               g_runs [n].r_title);
      }
   }
   if (my.extra == 'y') {
      printf ("\n\n");
      printf ("## end-of-file.  done, finito, completare, whimper [Ï´···\n");
   }
   return 0;
}

char
PAGE__topbar            (char a_max, char c, short y, short x, short r)
{
   short       i           =    0;
   char        x_prev      =  ' ';
   char        x_pprev     =  ' ';
   /*---(stack)--------------------------*/
   x_prev = s_desk [y + 1][x + 1];
   if (strchr (YSTR_MONGO, x_prev) != NULL) {
      x_pprev = s_desk [y + 2][x + 2];
      if (strchr (YSTR_MONGO, x_pprev) != NULL) {
         s_desk [y + 3][x + 3] = x_pprev;
      }
      s_desk [y + 2][x + 2] = x_prev;
   }
   s_desk [y + 1][x + 1] = YSTR_MONGO [c];
   /*---(top-left)-----------------------*/
   switch (s_desk [y][x]) {
   case  ''  : case  'Œ'  : s_desk [y][x] = '‡';  break;
   case  '€'  : case  '²'  : s_desk [y][x] = '‰';  break;
   case  'ƒ'  :              s_desk [y][x] = 'ƒ';  break;
   case  '…'  :              s_desk [y][x] = 'Š';  break;
   case  '‚'  :              s_desk [y][x] = '‰';  break;
   case  '„'  :              s_desk [y][x] = '‡';  break;
   case  '‡'  :              s_desk [y][x] = '‡';  break;
   case  '†'  :              s_desk [y][x] = 'Š';  break;
   case  'Š'  :              s_desk [y][x] = 'Š';  break;
   default    :              s_desk [y][x] = 'ƒ';  break;
   }
   /*---(horizontal)---------------------*/
   for (i = x + 1; i < r; ++i) {
      switch (s_desk [y][i]) {
      case  ''  : case  'Œ'  : s_desk [y][i] = 'Š'; break;
      case  'ƒ'  : s_desk [y][i] = '‰'; break;
      case  '…'  : s_desk [y][i] = 'ˆ'; break;
      case  '‚'  : s_desk [y][i] = '‰'; break;
      case  '„'  : s_desk [y][i] = 'ˆ'; break;
      case  '‰'  : s_desk [y][i] = '‰'; break;
      case  'ˆ'  : s_desk [y][i] = 'ˆ'; break;
      case  '†'  : s_desk [y][i] = 'Š'; break;
      case  '‡'  : s_desk [y][i] = 'Š'; break;
      case  'Š'  : s_desk [y][i] = 'Š'; break;
      default    :
                   if (a_max == 'y') s_desk [y][i] = '';
                   else              s_desk [y][i] = '€';
                   break;
      }
   }
   /*---(top-right)----------------------*/
   switch (s_desk [y][r]) {
   case  ''  : case  'Œ'  : s_desk [y][r] = '†';  break;
   case  '€'  : case  '²'  : s_desk [y][r] = '‰';  break;
   case  'ƒ'  :              s_desk [y][r] = '‰';  break;
   case  '…'  :              s_desk [y][r] = '†';  break;
   case  '‚'  :              s_desk [y][r] = '‚';  break;
   case  '„'  :              s_desk [y][r] = 'Š';  break;
   case  '‡'  :              s_desk [y][r] = 'Š';  break;
   case  '†'  :              s_desk [y][r] = '†';  break;
   case  'Š'  :              s_desk [y][r] = 'Š';  break;
   default    :              s_desk [y][r] = '‚';  break;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
PAGE__botbar            (char a_max, char c, short b, short x, short r)
{
   short       i           =    0;
   char        x_ch        =    0;
   x_ch = s_desk [b - 1][r - 1];
   if (strchr (YSTR_MONGO, x_ch) != NULL)  s_desk [b - 2][r - 2] = x_ch;
   s_desk [b - 1][r - 1] = YSTR_MONGO [c];
   /*---(bot-left)-----------------------*/
   switch (s_desk [b][x]) {
   case  ''  : case  'Œ'  : s_desk [b][x] = '‡';  break;
   case  '€'  : case  '²'  : s_desk [b][x] = 'ˆ';  break;
   case  'ƒ'  :              s_desk [b][x] = '‡';  break;
   case  '…'  :              s_desk [b][x] = 'Š';  break;
   case  '‚'  :              s_desk [b][x] = 'Š';  break;
   case  '„'  :              s_desk [b][x] = '„';  break;
   case  '‡'  :              s_desk [b][x] = '‡';  break;
   case  '†'  :              s_desk [b][x] = 'Š';  break;
   case  'Š'  :              s_desk [b][x] = 'Š';  break;
   default    :              s_desk [b][x] = '„';
   }
   /*---(horizontal)---------------------*/
   for (i = x + 1; i < r; ++i) {
      switch (s_desk [b][i]) {
      case  ''  : case  'Œ'  : s_desk [b][i] = 'Š'; break;
      case  'ƒ'  : s_desk [b][i] = '‰'; break;
      case  '…'  : s_desk [b][i] = 'ˆ'; break;
      case  '‚'  : s_desk [b][i] = '‰'; break;
      case  '„'  : s_desk [b][i] = 'ˆ'; break;
      case  '‰'  : s_desk [b][i] = '‰'; break;
      case  'ˆ'  : s_desk [b][i] = 'ˆ'; break;
      case  '†'  : s_desk [b][i] = 'Š'; break;
      case  '‡'  : s_desk [b][i] = 'Š'; break;
      case  'Š'  : s_desk [b][i] = 'Š'; break;
      default    :
                   if (a_max == 'y') s_desk [b][i] = 'œ';
                   else              s_desk [b][i] = '€';
                   break;
      }
   }
   /*---(bot-right)----------------------*/
   switch (s_desk [b][r]) {
   case  ''  : case  'Œ'  : s_desk [b][r] = '†';  break;
   case  '€'  : case  '²'  : s_desk [b][r] = 'ˆ';  break;
   case  '‚'  :              s_desk [b][r] = '†';  break;
   case  '„'  :              s_desk [b][r] = 'ˆ';  break;
   case  'ƒ'  :              s_desk [b][r] = 'Š';  break;
   case  '…'  :              s_desk [b][r] = '…';  break;
   case  '‡'  :              s_desk [b][r] = 'Š';  break;
   case  '†'  :              s_desk [b][r] = '†';  break;
   case  'Š'  :              s_desk [b][r] = 'Š';  break;
   default    :              s_desk [b][r] = '…';  break;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
PAGE__side              (char a_max, char a_side, short y, short b, short x)
{
   char        i           =    0;
   for (i = y + 1; i < b; ++i) {
      switch (s_desk [i][x]) {
      case  '€' : case  '²' : s_desk [i][x] = 'Š';  break;
      case  'ƒ' : case  '„' : s_desk [i][x] = '‡';  break;
      case  '‚' : case  '…' : s_desk [i][x] = '†';  break;
      case  '†' :             s_desk [i][x] = 'Š';  break;
      case  '‡' :             s_desk [i][x] = 'Š';  break;
      case  'Š' :             s_desk [i][x] = 'Š';  break;
      default   : 
                              if      (a_max  != 'y')  s_desk [i][x] = '';
                              else if (a_side == 'l')  s_desk [i][x] = 'ž';
                              else                     s_desk [i][x] = 'Ÿ';
                              break;
      }
   }
   return 0;
}

char
PAGE__place             (short yo, short xo, char a_all, char a_max, char c, short a_left, short a_topp, short a_wide, short a_tall)
{
   short      x, y;
   short      r, b;
   short      i, j;
   char       x_max        =  '-';
   /*---(special)------------------------*/
   if (c == a_all)  x_max = 'y';
   /*---(scaling)------------------------*/
   x = xo + round (a_left / s_xfact);
   y = yo + round (a_topp / s_yfact);
   r = xo + round ((a_left + a_wide) / s_xfact);
   b = yo + round ((a_topp + a_tall) / s_yfact);
   /*---(top)----------------------------*/
   PAGE__topbar (x_max, c, y, x, r);
   PAGE__botbar (x_max, c, b, x, r);
   PAGE__side   (x_max, 'l', y, b, x);
   PAGE__side   (x_max, 'r', y, b, r);
   /*---(fix fill)-----------------------*/
   for (i = y + 1; i < b; ++i) {
      for (j = x + 1; j < r; ++j) {
         switch (s_desk [i][j]) {
         case ''  :
            s_desk [i][j] = 'Œ';
            break;
         case '€'  :
            s_desk [i][j] = '²';
            break;
         case ' '  :
            if      (a_all == c)  s_desk [i][j] = '·';
            else if (a_max == c)  s_desk [i][j] = '·';
            break;
         }
      }
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
PAGE__deskplace         (char d, char *a_title, short y, short x)
{
   char        i           =    0;
   char        n           =    0;
   char        c           =    0;
   char        x_all       =    0;
   char        x_max       =    0;
   char        l           =    0;
   char        t           [LEN_LABEL] = "";
   if (d < 0)  d = 8 + d;
   d %= 8;
   switch (d) {
   case 0 :  strcpy (t, "0>1st");  break;
   case 1 :  strcpy (t, "1>2nd");  break;
   case 2 :  strcpy (t, "2>3rd");  break;
   case 3 :  strcpy (t, "3>4th");  break;
   case 4 :  strcpy (t, "4>5th");  break;
   case 5 :  strcpy (t, "5>6th");  break;
   case 6 :  strcpy (t, "6>7th");  break;
   case 7 :  strcpy (t, "7>8th");  break;
   }
   l = strlen (t);
   if (y == 1) {
      for (i = 0; i < l; ++i)       s_desk [y - 1][x + 3 + i] = t [i];
   } else {
      for (i = 0; i < l; ++i)       s_desk [y + s_ynewc][x + 3 + i] = t [i];
   }
   for (i = 0; i < g_nrun; ++i)  g_runs [i].r_order = -1;
   for (i = 0; i < g_nrun; ++i) {
      n = FIFO_by_stack (i);
      if (n < 0)  continue;
      if (c > x_all)  x_all = c;
      if (g_runs [n].r_desk != d)  continue;
      if (c > x_max)  x_max = c;
      g_runs [n].r_order = c;
      ++c;
   }
   for (i = 0; i < g_nrun; ++i) {
      n = FIFO_by_stack (i);
      if (n < 0)  continue;
      if (g_runs [n].r_desk != d)  continue;
      /*> if (g_runs [n].r_order == 2) continue;                                        <*/
      PAGE__place (y, x, x_all, x_max, g_runs [n].r_order, g_runs[n].r_left, g_runs[n].r_topp, g_runs[n].r_wide, g_runs[n].r_tall);
   }
   sprintf (t, "%dw", c);
   l = strlen (t);
   if (y == 1) {
      for (i = 0; i < l; ++i)       s_desk [y - 1][x + s_xnewc - 3 - l + i] = t [i];
   } else {
      for (i = 0; i < l; ++i)       s_desk [y + s_ynewc][x + s_xnewc - 3 - l + i] = t [i];
   }
   return c;
}

char
PAGE_single             (void)
{
   char        rce         =  -10;
   char        s           =    0;
   char        n           =    0;
   char        i           =    0;
   char        c           =    0;
   char        x_max       =    0;
   char        x_desk      =    0;
   x_desk = my.desk;
   PAGE__init ();
   PAGE__scaler  (my.scale);
   PAGE__outline   (my.ygrid, my.xgrid);
   switch (my.range) {
   case 8 :
      c += PAGE__deskplace (7, "8th", 1 + (s_ynewc + 1) * 1, 5 + (s_xnewc + 3) * 3);
      c += PAGE__deskplace (6, "7th", 1 + (s_ynewc + 1) * 1, 5 + (s_xnewc + 3) * 2);
      c += PAGE__deskplace (5, "6th", 1 + (s_ynewc + 1) * 1, 5 + (s_xnewc + 3) * 1);
      c += PAGE__deskplace (4, "5th", 1 + (s_ynewc + 1) * 1, 5 + (s_xnewc + 3) * 0);
      c += PAGE__deskplace (3, "4th", 1 + (s_ynewc + 1) * 0, 5 + (s_xnewc + 3) * 2);
      c += PAGE__deskplace (2, "3rd", 1 + (s_ynewc + 1) * 0, 5 + (s_xnewc + 3) * 2);
      c += PAGE__deskplace (1, "2nd", 1 + (s_ynewc + 1) * 0, 5 + (s_xnewc + 3) * 1);
      c += PAGE__deskplace (0, "1st", 1 + (s_ynewc + 1) * 0, 5 + (s_xnewc + 3) * 0);
      break;
   case 3 :
      c += PAGE__deskplace (my.desk - 1, "---", 1 + (s_ynewc + 0) * 0, 5 + (s_xnewc + 3) * 0);
      c += PAGE__deskplace (my.desk    , "---", 1 + (s_ynewc + 0) * 0, 5 + (s_xnewc + 3) * 1);
      c += PAGE__deskplace (my.desk + 1, "---", 1 + (s_ynewc + 0) * 0, 5 + (s_xnewc + 3) * 2);
      break;
   case 2 :
      c += PAGE__deskplace (my.desk    , "---", 1 + (s_ynewc + 0) * 0, 5 + (s_xnewc + 3) * 0);
      c += PAGE__deskplace (my.desk + 1, "---", 1 + (s_ynewc + 0) * 0, 5 + (s_xnewc + 3) * 1);
      break;
   case 1 :
      PAGE__deskplace (my.desk    , "---", 1 + (s_ynewc + 0) * 0, 5 + (s_xnewc + 3) * 0);
      break;
   }
   PAGE__print (2, x_desk, g_nrun, c);
   return 0;
}

char
PAGE_multi              (void)
{
}



/*====================------------------------------------====================*/
/*===----                      unit test accessor                      ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char*            /*--> unit test accessor ------------------------------*/
PAGE__unit              (char *a_question, int n)
{
   /*---(locals)-----------+-----------+-*/
   int         c           =    0;
   /*---(prepare)------------------------*/
   ystrlcpy  (unit_answer, "PAGE             : question not understood", LEN_RECD);
   /*---(crontab name)-------------------*/
   if      (strcmp (a_question, "full"    )        == 0) {
      snprintf (unit_answer, LEN_RECD, "PAGE full        :  %4d  %2d  %3d        ,  %4d  %2d  %3d", s_xfull, s_xmult, s_xchar, s_yfull, s_ymult, s_ychar);
   }
   else if (strcmp (a_question, "page"    )        == 0) {
      snprintf (unit_answer, LEN_RECD, "PAGE page        :  %5.3f     %3d  %6.2f,            %3d  %6.2f", s_scale, s_xpage, s_xfact, s_ypage, s_yfact);
   }
   else if (strcmp (a_question, "desk"    )        == 0) {
      snprintf (unit_answer, LEN_RECD, "PAGE desk  (%3d) : %3då%sæ", n, strlen (s_desk [n]), s_desk [n]);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}




