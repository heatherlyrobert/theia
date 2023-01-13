#include   "theia.h"


tBACK  g_backs     [MAX_BACK];
int    g_nback     =    0;
int    g_cback     =    0;



char
BACK_purge              (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_CONF   yLOG_senter  (__FUNCTION__);
   /*---(clear table)--------------------*/
   for (i = 0; i < MAX_BACK; ++i)  {
      strlcpy (g_backs [i].refno, "·", LEN_TERSE);
      strlcpy (g_backs [i].terse, "·", LEN_TERSE);
      strlcpy (g_backs [i].name , "·", LEN_LABEL);
      strlcpy (g_backs [i].hex  , "·", LEN_TERSE);
      g_backs [i].value     =   0;
   }
   g_nback = 0;
   /*---(header)-------------------------*/
   DEBUG_CONF   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
BACK_by_ref        (cchar a_ref [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(find fore)----------------------*/
   --rce;  if (a_ref  == NULL)  return rce;
   g_cback   = 0;
   for (i = 0; i < g_nback; ++i) {
      if (strcmp (g_backs  [i].refno, a_ref) != 0)  continue;
      g_cback  = i;
      return i;
   }
   /*---(complete)-----------------------*/
   return --rce;
}

char
BACK_create             (cchar a_recd [LEN_RECD])
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
   /*---(header)-------------------------*/
   DEBUG_CONF   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_CONF   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_CONF   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   DEBUG_CONF   yLOG_info    ("a_recd"    , a_recd);
   --rce;  if (strncmp (a_recd, "background ", 11) != 0) {
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
      case  1 :  /* color abbr           */
         if (l < 1)  { rc = -c; break; }
         n = BACK_by_ref (t);
         if (n >= 0) {
            DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         strlcpy  (g_backs [g_nback].refno, t, LEN_TERSE);
         DEBUG_CONF   yLOG_info    ("refno"     , g_backs [g_nback].refno);
         break;
      case  2 :  /* color terse          */
         if (l < 5)  { rc = -c; break; }
         strlcpy  (g_backs [g_nback].terse, t, LEN_TERSE);
         DEBUG_CONF   yLOG_info    ("terse"     , g_backs [g_nback].terse);
         break;
      case  3 :  /* full description     */
         if (l < 3)  { rc = -c; break; }
         strlcpy  (g_backs [g_nback].name , t, LEN_LABEL);
         DEBUG_CONF   yLOG_info    ("name"      , g_backs [g_nback].name);
         break;
      case  4 :  /* old color */
         break;
      case  5 :  /* hex color value      */
         if (l != 7)  { rc = -c; break; }
         strlcpy  (g_backs [g_nback].hex  , t, LEN_TERSE);
         DEBUG_CONF   yLOG_info    ("hex"       , g_backs [g_nback].hex);
         rc = strl2hex (t, &v, LEN_TERSE);
         g_backs [g_nback].value = v;
         DEBUG_CONF   yLOG_value   ("value"     , g_backs [g_nback].value);
         break;
      }
      if (rc < 0)  break;
      ++c;
      p = strtok (NULL, q);
      DEBUG_CONF   yLOG_point   ("p"         , p);
   }
   /*---(trouble)---------------------*/
   DEBUG_CONF   yLOG_value   ("c"         , c);
   DEBUG_CONF   yLOG_value   ("rc"        , rc);
   --rce;  if (c < 5 || rc < 0) {
      DEBUG_CONF   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(advance)---------------------*/
   ++g_nback;
   /*---(complete)-----------------------*/
   DEBUG_CONF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
BACK_set           (cchar a_ref [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        n           =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(find background)----------------*/
   n = BACK_by_ref (a_ref);
   DEBUG_PROG   yLOG_value   ("by_ref"    , n);
   --rce;  if (n < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(set actual)---------------------*/
   strlcpy (my.back_act, a_ref, LEN_TERSE);
   /*---(set background)-----------------*/
   /*> DEBUG_GRAF  yLOG_complex ("back"      , "%2d, %c, %s, %s, %s", g_cback, g_backs [g_cback].abbr, g_backs [g_cback].terse, g_backs [g_cback].name, g_backs [g_cback].hex);   <*/
   /*> DEBUG_GRAF  yLOG_complex ("color"     , "%10d, %s", g_backs [g_cback].value, x_str);   <*/
   printf ("\e]6;0;true");
   printf ("\e]6;2;tint;bg;0x%06x", g_backs [n].value);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
BACK_report        (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;
   char        x_save      [50];
   char        x_group     [50];
   /*---(header)-------------------------*/
   printf ("\n## theia euryphaessa (wide-shinning) transparent background tint inventory\n");
   printf ("\n## usage : theia <c>\n");
   printf ("##    where <c> is the single letter listed in the 'k' column\n");
   printf ("\n## terse-   ---name-------------  --hex--  ---val---\n");
   /*---(inventory)----------------------*/
   for (i = 0; i < g_nback; ++i) {
      printf ("%-2.2s  %-6.6s   %-20.20s  %-7.7s  %9d\n",
            g_backs [i].refno , g_backs [i].terse,
            g_backs [i].name  , g_backs [i].hex, g_backs [i].value);
   }
   /*---(footer)-------------------------*/
   printf ("\n");
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      unit test accessor                      ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char        unit_answer [LEN_RECD];

char*            /*--> unit test accessor ------------------------------*/
BACK__unit              (char *a_question, int n)
{
   /*---(locals)-----------+-----------+-*/
   int         c           =    0;
   /*---(prepare)------------------------*/
   strlcpy  (unit_answer, "BACK             : question not understood", LEN_HUND);
   /*---(crontab name)-------------------*/
   if      (strcmp (a_question, "count"   )        == 0) {
      snprintf (unit_answer, LEN_HUND, "BACK count       : %d", g_nback);
   }
   else if (strcmp (a_question, "entry"   )        == 0) {
      snprintf (unit_answer, LEN_HUND, "BACK entry  (%2d) : %-2.2s  %-6.6s  %-15.15s  %-7.7s  %d", n, g_backs [n].refno, g_backs [n].terse, g_backs [n].name, g_backs [n].hex, g_backs [n].value);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}



