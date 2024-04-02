#include   "theia.h"

/*
 *  getting background change results
 *
 *  escape sequence that sets title bar to a status line...
 *     # printf "\e]2;testing\a"       ## unblocks/clears the title
 *     # printf "\e[9n"                ## sets the status title
 *
 *     title  åeterm-0.9.7:  Transparent  -  100% shading  -  0x007733 tint maskæ
 *     -- i am not sure if spacing of data is constant
 *     -- destroys/overwrites any existing title data
 *
 *
 *
 *
 */

tBACK  g_backs     [MAX_BACK];
int    g_nback     =    0;
int    g_cback     =    0;



/*====================------------------------------------====================*/
/*===----                         program level                        ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char
BACK_purge              (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_CONF   yLOG_senter  (__FUNCTION__);
   /*---(clear table)--------------------*/
   for (i = 0; i < MAX_BACK; ++i)  {
      ystrlcpy (g_backs [i].b_abbr , "·", LEN_TERSE);
      ystrlcpy (g_backs [i].b_terse, "·", LEN_TERSE);
      ystrlcpy (g_backs [i].b_name , "·", LEN_LABEL);
      ystrlcpy (g_backs [i].b_hex  , "·", LEN_TERSE);
      g_backs [i].b_value     =   0;
   }
   g_nback = 0;
   /*---(header)-------------------------*/
   DEBUG_CONF   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         normal usage                         ----===*/
/*====================------------------------------------====================*/
static void      o___USAGE___________________o (void) {;}

char
BACK_by_abbr       (cchar a_abbr [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(find fore)----------------------*/
   --rce;  if (a_abbr  == NULL)  return rce;
   g_cback   = 0;
   for (i = 0; i < g_nback; ++i) {
      if (strcmp (g_backs  [i].b_abbr, a_abbr) != 0)  continue;
      g_cback  = i;
      return i;
   }
   /*---(complete)-----------------------*/
   return --rce;
}

char
BACK_handler            (cchar a_recd [LEN_RECD])
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
      case  1 :  /* color abbr           */
         if (l < 1)  { rc = -c; break; }
         n = BACK_by_abbr (t);
         if (n >= 0) {
            DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         ystrlcpy  (g_backs [g_nback].b_abbr, t, LEN_TERSE);
         DEBUG_CONF   yLOG_info    ("abbr"      , g_backs [g_nback].b_abbr);
         break;
      case  2 :  /* color terse          */
         if (l < 5)  { rc = -c; break; }
         ystrlcpy  (g_backs [g_nback].b_terse, t, LEN_TERSE);
         DEBUG_CONF   yLOG_info    ("terse"     , g_backs [g_nback].b_terse);
         break;
      case  3 :  /* full description     */
         if (l < 3)  { rc = -c; break; }
         ystrlcpy  (g_backs [g_nback].b_name , t, LEN_LABEL);
         DEBUG_CONF   yLOG_info    ("name"      , g_backs [g_nback].b_name);
         break;
      case  4 :  /* hex color value      */
         if (l != 7)  { rc = -c; break; }
         ystrlcpy  (g_backs [g_nback].b_hex  , t, LEN_TERSE);
         DEBUG_CONF   yLOG_info    ("hex"       , g_backs [g_nback].b_hex);
         rc = ystrl2hex (t, &v, LEN_TERSE);
         g_backs [g_nback].b_value = v;
         DEBUG_CONF   yLOG_value   ("value"     , g_backs [g_nback].b_value);
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
BACK_set           (cchar a_abbr [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        n           =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(find background)----------------*/
   n = BACK_by_abbr (a_abbr);
   DEBUG_PROG   yLOG_value   ("by_abbr"   , n);
   --rce;  if (n < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(set actual)---------------------*/
   ystrlcpy (my.back_act, a_abbr, LEN_TERSE);
   /*---(set background)-----------------*/
   /*> DEBUG_GRAF  yLOG_complex ("back"      , "%2d, %c, %s, %s, %s", g_cback, g_backs [g_cback].abbr, g_backs [g_cback].b_terse, g_backs [g_cback].b_name, g_backs [g_cback].b_hex);   <*/
   DEBUG_GRAF  yLOG_complex ("color"     , "%06x", g_backs [g_cback].b_value);
   printf ("\e]6;0;true");
   printf ("\e]6;2;tint;bg;0x%06x", g_backs [n].b_value);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      reporting/output                        ----===*/
/*====================------------------------------------====================*/
static void      o___OUTPUT__________________o (void) {;}

char
BACK_report        (FILE *f)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         c           =    0;
   char        x_curr      [LEN_TERSE] = "";
   char        x_save      [LEN_TERSE] = "";
   /*---(header)-------------------------*/
   fprintf (f, "## %s\n", P_ONELINE);
   fprintf (f, "##   inventory of possible eterm background shades\n");
   fprintf (f, "##\n");
   fprintf (f, "## usage : theia <b>\n");
   fprintf (f, "##    where <b> is the single/double letter listed in the first column\n");
   fprintf (f, "##\n");
   fprintf (f, "##    $ theia f¦      ## sets background as f =forest green\n");
   fprintf (f, "##    $ theia c-¦     ## sets background as f =darker crimson\n");
   fprintf (f, "##\n");
   fprintf (f, "## the normal base back colors are nearly always enough, but\n");
   fprintf (f, "## having used this for many years, i created the variants\n");
   fprintf (f, "## for contrast and to adjust for lighter and darker desktops\n");
   /*---(inventory)----------------------*/
   fprintf (f, "\n##===[[ BASE BACK COLORS]]==========================#\n");
   fprintf (f, "\n##  terse-   ---name-------------  --hex--  ---val---\n");
   c = 0;
   for (i = 0; i < g_nback; ++i) {
      if (g_backs [i].b_terse [5] != '·')   continue;
      if (c %  5 == 0)                    fprintf (f, "\n");
      fprintf (f, "%-2.2s  %-6.6s   %-20.20s  %-7.7s  %9d\n",
            g_backs [i].b_abbr , g_backs [i].b_terse,
            g_backs [i].b_name , g_backs [i].b_hex  , g_backs [i].b_value);
      ++c;
   }
   fprintf (f, "\n## %d bases\n\n", c);
   /*---(inventory)----------------------*/
   fprintf (f, "\n##===[[ BACK VARIATIONS ]]==========================#\n");
   c = 0;
   for (i = 0; i < g_nback; ++i) {
      sprintf (x_curr, "%5.5s", g_backs [i].b_terse);
      if (c % 25 == 0)                    fprintf (f, "\n##  terse-   ---name-------------  --hex--  ---val---\n");
      if (strcmp (x_curr, x_save) != 0)   fprintf (f, "\n");
      fprintf (f, "%-2.2s  %-6.6s   %-20.20s  %-7.7s  %9d\n",
            g_backs [i].b_abbr , g_backs [i].b_terse,
            g_backs [i].b_name , g_backs [i].b_hex  , g_backs [i].b_value);
      ++c;
      ystrlcpy (x_save, x_curr, LEN_TERSE);
   }
   fprintf (f, "\n## %d bases plus variants\n\n", c);
   /*---(footer)-------------------------*/
   fprintf (f, "## end-of-data.  done, finito, completare, whimper [Ï´···\n");
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      unit test accessor                      ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char        unit_answer [LEN_RECD];

char
BACK__unit_force        (char a_abbr [LEN_TERSE], char a_terse [LEN_TERSE], char a_name [LEN_LABEL], char a_hex [LEN_TERSE])
{
   double      v           =  0.0;
   ystrlcpy  (g_backs [g_nback].b_abbr , a_abbr , LEN_TERSE);
   ystrlcpy  (g_backs [g_nback].b_terse, a_terse, LEN_TERSE);
   ystrlcpy  (g_backs [g_nback].b_name , a_name , LEN_LABEL);
   ystrlcpy  (g_backs [g_nback].b_hex  , a_hex  , LEN_TERSE);
   ystrl2hex (a_hex, &v, LEN_TERSE);
   g_backs [g_nback].b_value = v;
   ++g_nback;
   return 0;
}

char*            /*--> unit test accessor ------------------------------*/
BACK__unit              (char *a_question, int n)
{
   /*---(locals)-----------+-----------+-*/
   int         c           =    0;
   /*---(prepare)------------------------*/
   ystrlcpy  (unit_answer, "BACK             : question not understood", LEN_HUND);
   /*---(crontab name)-------------------*/
   if      (strcmp (a_question, "count"   )        == 0) {
      snprintf (unit_answer, LEN_HUND, "BACK count       : %d", g_nback);
   }
   else if (strcmp (a_question, "entry"   )        == 0) {
      snprintf (unit_answer, LEN_HUND, "BACK entry  (%2d) : %-2.2s  %-6.6s  %-15.15s  %-7.7s  %d", n, g_backs [n].b_abbr, g_backs [n].b_terse, g_backs [n].b_name, g_backs [n].b_hex, g_backs [n].b_value);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}



