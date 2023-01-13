#include   "theia.h"



tFORE  g_fores     [MAX_FORE];
int    g_nfore     = 0;;
int    g_cfore     = 0;;



/*====================------------------------------------====================*/
/*===----                        basic support                         ----===*/
/*====================------------------------------------====================*/
static void      o___BASICS__________________o (void) {;}

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
      strlcpy (g_fores [i].refno, "·", LEN_TERSE);
      strlcpy (g_fores [i].name , "·", LEN_LABEL);
      g_fores [i].style     = '·';
      for (j = 0; j < MAX_ENTRIES; ++j)  {
         strlcpy (g_fores [i].hex [j]  , "·", LEN_TERSE);
         g_fores [i].value [j]  =   0;
      }
   }
   g_nfore = 0;
   /*---(header)-------------------------*/
   DEBUG_CONF   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
FORE_by_ref        (cchar a_ref [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(find fore)----------------------*/
   --rce;  if (a_ref  == NULL)  return rce;
   g_cfore   = 0;
   for (i = 0; i < g_nfore; ++i) {
      if (strcmp (g_fores  [i].refno, a_ref) != 0)  continue;
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
   strlcpy (x_recd, a_recd, LEN_RECD);
   p = strtok (x_recd, q);
   DEBUG_CONF   yLOG_point   ("p"         , p);
   /*---(parse record)----------------*/
   --rce;  while (p != NULL) {
      strlcpy  (t, p, LEN_LABEL);
      strltrim (t, ySTR_BOTH, LEN_LABEL);
      l = strlen (t);
      DEBUG_CONF   yLOG_complex ("parse"     , "%d, %2då%sæ", c, l, t);
      switch (c) {
      case  1 :  /* font color refno     */
         if (l != 3)  { rc = -c; break; }
         rc = strl2hex (t, &v, LEN_TERSE);
         if (rc <  0)  { rc = -c; break; }
         n = FORE_by_ref  (t + 1);
         if (n >= 0) {
            DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         strlcpy  (g_fores [g_nfore].refno, t + 1, LEN_TERSE);
         DEBUG_CONF   yLOG_info    ("refno"     , g_fores [g_nfore].refno);
         break;
      case  2 :  /* full name            */
         if (l < 3)  { rc = -c; break; }
         strlcpy  (g_fores [g_nfore].name , t, LEN_LABEL);
         DEBUG_CONF   yLOG_info    ("name"      , g_fores [g_nfore].name);
         break;
      case  3 :  /* style                */
         if (l != 1)  { rc = -c; break; }
         g_fores [g_nfore].style = t [0];
         DEBUG_CONF   yLOG_char    ("style"     , g_fores [g_nfore].style);
         break;
      default  : /* hex values           */
         if (l != 7)  { rc = -c; break; }
         strlcpy  (g_fores [g_nfore].hex [c - 4] , t, LEN_TERSE);
         DEBUG_CONF   yLOG_info    ("hex"       , g_fores [g_nfore].hex [c - 4]);
         rc = strl2hex (t, &v, LEN_TERSE);
         if (rc <  0)  { rc = -c; break; }
         g_fores [g_nfore].value [c - 4] = v;
         DEBUG_CONF   yLOG_value   ("value"     , g_fores [g_nfore].value [c - 4]);
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
FORE_set           (cchar a_ref [LEN_TERSE])
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
   DEBUG_PROG   yLOG_info    ("a_ref"     , a_ref);
   --rce;  if (a_ref == NULL) {
      DEBUG_CONF   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(find background)----------------*/
   n = FORE_by_ref (a_ref);
   DEBUG_PROG   yLOG_value   ("by_ref"    , n);
   --rce;  if (n < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("name"      , g_fores [n].name);
   /*---(set actual)---------------------*/
   strlcpy (my.fore_act, a_ref, LEN_TERSE);
   /*---(set background)-----------------*/
   for (i = 0; i < 16; ++i) {
      x = ((int) i / 2) - 0 + ((i % 2) *  8);
      printf ("\e]P%1x%06x", x, g_fores [n].value [i]);
      /*> printf ("%2d color %d to å%06xæ\n", i, x, g_fores [n].value [i]);           <*/
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      unit test accessor                      ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char*            /*--> unit test accessor ------------------------------*/
FORE__unit              (char *a_question, int n)
{
   /*---(locals)-----------+-----------+-*/
   int         c           =    0;
   /*---(prepare)------------------------*/
   strlcpy  (unit_answer, "FORE             : question not understood", LEN_HUND);
   /*---(crontab name)-------------------*/
   if      (strcmp (a_question, "count"   )        == 0) {
      snprintf (unit_answer, LEN_HUND, "FORE count       : %d", g_nfore);
   }
   else if (strcmp (a_question, "entry"   )        == 0) {
      snprintf (unit_answer, LEN_HUND, "FORE entry  (%2d) : %-2.2s  %-15.15s  %-7.7s/%-9d  %-7.7s/%-9d  %-7.7s/%d", n, g_fores [n].refno, g_fores [n].name, g_fores [n].hex [0], g_fores [n].value [0], g_fores [n].hex [7], g_fores [n].value [7], g_fores [n].hex [15], g_fores [n].value [15]);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}
