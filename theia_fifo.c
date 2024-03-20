#include   "theia.h"


char
FIFO_by_stack           (char a_stack)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_senter  (__FUNCTION__);
   /*---(find back)----------------------*/
   DEBUG_PROG   yLOG_sint    (a_stack);
   --rce;  if (a_stack < 0 || a_stack >= g_nrun) {
      DEBUG_PROG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   for (i = 0; i < g_nrun; ++i) {
      DEBUG_PROG   yLOG_sint    (g_runs [i].r_stack);
      if (g_runs [i].r_stack != a_stack)  continue;
      DEBUG_PROG   yLOG_snote   ("FOUND");
      DEBUG_PROG   yLOG_sexit   (__FUNCTION__);
      return i;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_sexitr  (__FUNCTION__, --rce);
   return rce;
}

char
FIFO__current           (cchar a_hex [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   char        s           =    0;
   char        o           =    0;
   char        n           =    0;
   int         l           =    0;
   double      v           =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DEBUG_PROG   yLOG_point   ("a_hex"     , a_hex);
   --rce;  if (a_hex == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("a_hex"     , a_hex);
   l = strlen (a_hex);
   DEBUG_PROG   yLOG_value   ("l"         , l);
   --rce;  if (l < 8 || l > 9) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   ystrl2hex (a_hex, &v, LEN_LABEL);
   DEBUG_PROG   yLOG_value   ("v"         , v);
   /*---(get new current)----------------*/
   o =  RUN_by_winid (v);
   DEBUG_PROG   yLOG_value   ("o"         , o);
   --rce;  if (o < 0) {
      DEBUG_PROG   yLOG_note    ("can not find");
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare for run)----------------*/
   s =  g_runs [o].r_stack;
   if (g_runs [o].r_stack == g_nrun - 1)  {
      DEBUG_PROG   yLOG_note    ("already top");
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(restack)------------------------*/
   for (i = s + 1; i < g_nrun; ++i) {
      DEBUG_PROG   yLOG_value   ("i"         , i);
      n = FIFO_by_stack (i);
      DEBUG_PROG   yLOG_value   ("n"         , n);
      if (n >= 0)  g_runs [n].r_stack = i - 1;
   }
   /*---(place at top)-------------------*/
   g_runs [o].r_stack = g_nrun - 1;
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
FIFO__listener          (cchar a_recd [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_LABEL] = "";
   int         l           =    0;
   double      v           =  0.0;
   if (a_recd == NULL)  return 0;
   if (strncmp (a_recd, "_NET_ACTIVE_WINDOW(WINDOW): window id # ", 40) == 0) {
      ystrlcpy (t, a_recd + 40, LEN_LABEL);
      FIFO__current (t);
      return 0;
   }
   return 0;
}

char
FIFO_listen             (cchar a_name [LEN_PATH])
{
   /*> return yEXEC_fifo_listen ('y', a_name, FIFO__listener);                        <*/
}


char
FIFO_eater              (cchar a_name [LEN_PATH])
{
   /*---(locals)-----------+------+----+-*/
   char        rce         =  -10;
   char        rc          =  -10;
   FILE       *f           = NULL;
   int         x_fileno    =    0;
   int         x_flags     =    0;
   int         x_ch        =    0;
   int         l           =    0;
   char        x_recd      [LEN_RECD]  = "";
   char        t           [LEN_LABEL] = "";
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_PROG    yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG    yLOG_info    ("a_name"    , a_name);
   /*---(open)---------------------------*/
   DEBUG_PROG   yLOG_info    ("a_name"    , a_name);
   f = fopen (a_name, "rt");
   DEBUG_PROG   yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(non-blocking)-------------------*/
   /*> x_fileno    = fileno (f);                                                      <*/
   /*> x_flags     = fcntl  (x_fileno, F_GETFL, 0);                                   <*/
   /*> fcntl (x_fileno, F_SETFL, x_flags | O_NONBLOCK);                               <*/
   /*---(test for input)-----------------*/
   x_ch = fgetc (f);
   DEBUG_PROG   yLOG_value   ("x_ch"      , x_ch);
   for (i = 0; i < LEN_RECD; ++i) x_recd [i] = '\0'; 
   /*> DEBUG_PROG   yLOG_value   ("errno"     , errno);                               <*/
   /*> DEBUG_PROG   yLOG_info    ("strerror"  , strerror (errno));                    <*/
   /*---(loop)---------------------------*/
   while (1) {
      DEBUG_PROG   yLOG_complex ("read"      , "%2d, %3d, %c", l, x_ch, ychrvisible (x_ch));
      if (x_ch >= 0 && x_ch != '\n' && l < 100) {
         x_recd [l++] = x_ch;
      } else if (l > 0) {
         if (strncmp (x_recd, "_NET_ACTIVE_WINDOW(WINDOW): window id # ", 40) == 0) {
            ystrlcpy (t, x_recd + 40, LEN_LABEL);
            FIFO__current (t);
         }
         for (i = 0; i < LEN_RECD; ++i) x_recd [i] = '\0'; 
         l = 0;
      }
      if (x_ch < 0)  break;
      /*---(next)---------------------------*/
      x_ch = fgetc (f);
      /*---(done)---------------------------*/
   }
   /*---(back to normal)-----------------*/
   /*> fcntl  (x_fileno, F_SETFL, x_flags);                                           <*/
   /*---(close)--------------------------*/
   rc = fclose (f);
   DEBUG_PROG   yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(system)-------------------------*/
   system ("pkill xprop");
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}


