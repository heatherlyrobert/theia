#include   "theia.h"



tFORE  g_fores     [MAX_FORE];
int    g_nfore     = 0;;
int    g_cfore     = 0;;



/*====================------------------------------------====================*/
/*===----                         program level                        ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char
FORE_purge              (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         j           =    0;
   /*---(header)-------------------------*/
   DEBUG_CONF   yLOG_senter  (__FUNCTION__);
   /*---(clear table)--------------------*/
   for (i = 0; i < MAX_FORE; ++i)  {
      ystrlcpy (g_fores [i].f_abbr, "·", LEN_TERSE);
      ystrlcpy (g_fores [i].f_name , "·", LEN_LABEL);
      g_fores [i].f_style     = '·';
      for (j = 0; j < MAX_ENTRIES; ++j)  {
         ystrlcpy (g_fores [i].f_hex [j]  , "·", LEN_TERSE);
         g_fores [i].f_value [j]  =   0;
      }
   }
   g_nfore = 0;
   /*---(header)-------------------------*/
   DEBUG_CONF   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         normal usage                         ----===*/
/*====================------------------------------------====================*/
static void      o___USAGE___________________o (void) {;}

char
FORE_by_abbr       (cchar a_abbr [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(find fore)----------------------*/
   --rce;  if (a_abbr  == NULL)  return rce;
   g_cfore   = 0;
   for (i = 0; i < g_nfore; ++i) {
      if (strcmp (g_fores  [i].f_abbr, a_abbr) != 0)  continue;
      g_cfore  = i;
      return i;
   }
   /*---(complete)-----------------------*/
   return --rce;
}

char
FORE_create             (cchar a_recd [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_recd      [LEN_RECD]  = "";
   char        t           [LEN_LABEL] = "";
   char       *p           = NULL;
   char       *q           = "§";
   int         l           =    0;
   int         c           =    0;
   double      v           =  0.0;
   int         n           =    0;
   int         x_hex       =    0;
   /*---(header)-------------------------*/
   DEBUG_CONF   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_CONF   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_CONF   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   DEBUG_CONF   yLOG_info    ("a_recd"    , a_recd);
   --rce;  if (strncmp (a_recd, "foreground ", 11) != 0) {
      DEBUG_CONF   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(prepare)---------------------*/
   ystrlcpy (x_recd, a_recd, LEN_RECD);
   p = strtok (x_recd, q);
   DEBUG_CONF   yLOG_point   ("p"         , p);
   /*---(parse record)----------------*/
   --rce;  while (p != NULL) {
      ystrlcpy  (t, p, LEN_LABEL);
      ystrltrim (t, ySTR_BOTH, LEN_LABEL);
      l = strlen (t);
      DEBUG_CONF   yLOG_complex ("parse"     , "%d, %2då%sæ", c, l, t);
      switch (c) {
      case  1 :  /* font color abbrev    */
         if (l != 3)  { rc = -c; break; }
         rc = ystrl2hex (t, &v, LEN_TERSE);
         if (rc <  0)  { rc = -c; break; }
         n = FORE_by_abbr (t + 1);
         if (n >= 0) {
            DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         ystrlcpy  (g_fores [g_nfore].f_abbr, t + 1, LEN_TERSE);
         DEBUG_CONF   yLOG_info    ("f_abbr"    , g_fores [g_nfore].f_abbr);
         break;
      case  2 :  /* full name            */
         if (l < 3)  { rc = -c; break; }
         ystrlcpy  (g_fores [g_nfore].f_name , t, LEN_LABEL);
         DEBUG_CONF   yLOG_info    ("name"      , g_fores [g_nfore].f_name);
         break;
      case  3 :  /* style                */
         if (l != 1)  { rc = -c; break; }
         g_fores [g_nfore].f_style = t [0];
         DEBUG_CONF   yLOG_char    ("style"     , g_fores [g_nfore].f_style);
         break;
      default  : /* hex values           */
         if (l != 7)  { rc = -c; break; }
         ystrlcpy  (g_fores [g_nfore].f_hex [c - 4] , t, LEN_TERSE);
         DEBUG_CONF   yLOG_info    ("hex"       , g_fores [g_nfore].f_hex [c - 4]);
         rc = ystrl2hex (t, &v, LEN_TERSE);
         if (rc <  0)  { rc = -c; break; }
         g_fores [g_nfore].f_value [c - 4] = v;
         DEBUG_CONF   yLOG_value   ("value"     , g_fores [g_nfore].f_value [c - 4]);
         break;
      }
      if (rc < 0)  break;
      ++c;
      if (c >= 20) break;
      p = strtok (NULL, q);
      DEBUG_CONF   yLOG_point   ("p"         , p);
   }
   /*---(trouble)---------------------*/
   DEBUG_CONF   yLOG_value   ("c"         , c);
   DEBUG_CONF   yLOG_value   ("rc"        , rc);
   --rce;  if (c < 20 || rc < 0) {
      DEBUG_CONF   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(advance)---------------------*/
   ++g_nfore;
   /*---(complete)-----------------------*/
   DEBUG_CONF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
FORE_set           (cchar a_abbr [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        n           =    0;
   char        i           =    0;
   char        x           =    0;
   char        x_bold      =    0;
   char        x_slot      =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_info    ("a_abbr"     , a_abbr);
   --rce;  if (a_abbr == NULL) {
      DEBUG_CONF   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(find background)----------------*/
   n = FORE_by_abbr (a_abbr);
   DEBUG_PROG   yLOG_value   ("by_abbr"   , n);
   --rce;  if (n < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("name"      , g_fores [n].f_name);
   /*---(set actual)---------------------*/
   ystrlcpy (my.fore_act, a_abbr, LEN_TERSE);
   /*---(set background)-----------------*/
   for (i = 0; i < 16; ++i) {
      x = ((int) i / 2) - 0 + ((i % 2) *  8);
      printf ("\e]P%1x%06x", x, g_fores [n].f_value [i]);
      /*> printf ("%2d color %d to å%06xæ\n", i, x, g_fores [n].f_value [i]);           <*/
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      unit test accessor                      ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

/*> char                                                                                                                           <* 
 *> FORE__unit_force        (char a_abbr [LEN_TERSE], char a_terse [LEN_TERSE], char a_name [LEN_LABEL], char a_hex [LEN_TERSE])   <* 
 *> {                                                                                                                              <* 
 *>    double      v           =  0.0;                                                                                             <* 
 *>    ystrlcpy  (g_fores [g_nfore].b_abbr , a_abbr , LEN_TERSE);                                                                  <* 
 *>    ystrlcpy  (g_fores [g_nfore].b_terse, a_terse, LEN_TERSE);                                                                  <* 
 *>    ystrlcpy  (g_fores [g_nfore].b_name , a_name , LEN_LABEL);                                                                  <* 
 *>    ystrlcpy  (g_fores [g_nfore].b_hex  , a_hex  , LEN_TERSE);                                                                  <* 
 *>    ystrl2hex (a_hex, &v, LEN_TERSE);                                                                                           <* 
 *>    g_fores [g_nfore].b_value = v;                                                                                              <* 
 *>    ++g_nfore;                                                                                                                  <* 
 *>    return 0;                                                                                                                   <* 
 *> }                                                                                                                              <*/

char*            /*--> unit test accessor ------------------------------*/
FORE__unit              (char *a_question, int n)
{
   /*---(locals)-----------+-----------+-*/
   int         c           =    0;
   /*---(prepare)------------------------*/
   ystrlcpy  (unit_answer, "FORE             : question not understood", LEN_HUND);
   /*---(crontab name)-------------------*/
   if      (strcmp (a_question, "count"   )        == 0) {
      snprintf (unit_answer, LEN_HUND, "FORE count       : %d", g_nfore);
   }
   else if (strcmp (a_question, "entry"   )        == 0) {
      snprintf (unit_answer, LEN_HUND, "FORE entry  (%2d) : %-2.2s  %-15.15s  %-7.7s/%-9d  %-7.7s/%-9d  %-7.7s/%d", n, g_fores [n].f_abbr, g_fores [n].f_name, g_fores [n].f_hex [0], g_fores [n].f_value [0], g_fores [n].f_hex [7], g_fores [n].f_value [7], g_fores [n].f_hex [15], g_fores [n].f_value [15]);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}
