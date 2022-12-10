#include   "theia.h"


char
main               (int a_argc, char *a_argv [])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   char        rc          =   0;           /* generic return code            */
   char        n           =   0;
   /*---(preprare)-----------------------*/
   rc = PROG_urgents (a_argc, a_argv );
   DEBUG_PROG   yLOG_value   ("urgents"   , rc);
   --rce;  if (rc <  0) {
      PROG_shutdown  ();
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = PROG_startup (a_argc, a_argv );
   DEBUG_PROG   yLOG_value   ("startup"   , rc);
   --rce;  if (rc <  0) {
      PROG_shutdown  ();
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(pre-run)------------------------*/
   rc = PROG_dawn    ();
   DEBUG_PROG   yLOG_value    ("dawn"      , rc);
   --rce;  if (rc <  0) {
      PROG_shutdown  ();
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(run)----------------------------*/
   if (my.back_req != '·') {
      BACK_set (my.back_req);
   }
   if (strcmp (my.fore_req, "·") != NULL) {
      FORE_set (my.fore_req);
   }
   if (my.report != '·') {
      if (my.report == '!')  REPORT_quarter (my.fore_act);
   }
   if (strcmp (my.shortcut, "") != 0) {
      DEBUG_PROG   yLOG_note     ("running a goto");
      DEBUG_PROG   yLOG_info     ("shortcut"  , my.shortcut);
      n = RUN_by_shortcut (my.shortcut);
      DEBUG_PROG   yLOG_value    ("n"         , n);
      if (n >= 0) {
         DEBUG_PROG   yLOG_value    ("ref"       , g_runs [n].ref);
         rc = yX11_win_goto (g_runs [n].ref);
         DEBUG_PROG   yLOG_value    ("goto"       , rc);
      }
   }
   /*---(post_run)-----------------------*/
   rc = PROG_dusk    ();
   DEBUG_PROG   yLOG_value    ("dusk"      , rc);
   /*---(wrapup)-------------------------*/
   rc = PROG_shutdown  ();
   DEBUG_PROG   yLOG_value    ("shutdown"  , rc);
   /*---(complete)-----------------------*/
   return rc;
}
        

char
main_OLD           (int a_argc, char *a_argv [])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   char        rc          =   0;           /* generic return code            */
   int         x_log       =   0;           /* logger id                      */
   int         x_ppid      =   0;
   char        x_back      =   '-';
   char        x_theme     [ 5]   = "00";
   int         i           =   0;
   int         j           =   0;
   char        t           [LEN_HUND]  = "";
   /*---(preprare)-----------------------*/
   rc = PROG_urgents (a_argc, a_argv );
   DEBUG_PROG   yLOG_value   ("urgents"   , rc);
   --rce;  if (rc <  0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = PROG_startup (a_argc, a_argv );
   DEBUG_PROG   yLOG_value   ("startup"   , rc);
   --rce;  if (rc <  0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(find eterm or hestia)-----------*/
   DEBUG_PROG   yLOG_note    ("before runtime_read");
   rc = RUNTIME_read  ();
   DEBUG_PROG   yLOG_value   ("read"      , rc);
   /*> --rce;  if (rc < 0) {                                                          <* 
    *>    DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                              <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <*/
   /*> printf ("before TERM_find\n");                                              <*/
   rc = TERM_find (getppid(), &x_ppid);
   DEBUG_PROG   yLOG_value   ("term_find" , rc);
   --rce;  if (rc < 0)                 return rce;
   /*> for (i = 0; i < g_nrun; ++i) {                                                 <* 
    *>    if (x_ppid != g_runs [i].ppid)  continue;                                   <* 
    *>    x_back =  g_runs[i].back_key;                                               <* 
    *>    strcpy (x_theme, g_runs [i].theme_ref);                                     <* 
    *>    break;                                                                      <* 
    *> }                                                                              <*/
   /*> printf ("before SCHEMES_read\n");                                           <*/
   /*---(get schemes)--------------------*/
   rc = CONF_read ();
   DEBUG_PROG   yLOG_value   ("schemes"   , rc);
   /*> if (strcmp ("00", my.fore) != 0)     THEME_find   (my.fore);                   <*/
   /*> if (strchr ("*-", my.back) == NULL)  BACK_find    (my.back);               <*/
   /*---(set environment)----------------*/
   if (my.report == 'x' && g_cback   >  0)  {
      printf ("export theia_tint=\"%c § %-6.6s § %-12.12s § %-7.7s § %9d §\";\n",
            g_backs [g_cback].abbr, g_backs [g_cback].terse, g_backs [g_cback].name,
            g_backs [g_cback].hex, g_backs [g_cback].value);
      /*> printf ("export theia_1_abbr=%c;\n" , g_backs [g_cback].key);                  <* 
       *> printf ("export theia_2_color=%s\n", g_backs [g_cback].color);                 <* 
       *> printf ("export theia_3_hex=%06x;\n", g_backs [g_cback].hex);                  <*/
   }
   if (my.report == 'x' && my.theme  > 0)  {
      printf ("export theia_text=\"%c § %-2.2s § %-16.16s §\";\n",
            g_fores [my.theme].style, g_fores [my.theme].refno , g_fores [my.theme].name);
      /*> printf ("export theia_5_ref=%s;¦"  , g_fores [my.theme].refno);              <* 
       *> printf ("export theia_6_name=%s;¦" , g_fores [my.theme].name);               <* 
       *> printf ("export theia_7_style=%c;¦", g_fores [my.theme].style);              <*/
   }
   if (my.report == 'x')  return 0;
   /*---(set back)-----------------------*/
   if (my.back_req == '*') {
      for (i = 1; i < g_nback; ++i) {
         /*> BACK_find    (g_backs [i]);                                              <*/
         /*> BACK_set      ();                                                        <*/
         printf ("%c  %s\n", g_backs [i].abbr, g_backs [i].name);
         usleep (750000);
      }
      return 0;
   }
   if (g_cback   >  0)  {
      /*> BACK_set      ();                                                           <*/
      RUNTIME_write ();
   }
   if (my.custom >= 0)  {
      BACK_custom   ();
      RUNTIME_write ();
   }
   /*---(set theme)----------------------*/
   if (my.theme  > 0)  {
      THEME_set     ();
      RUNTIME_write ();
   }
   /*---(display)------------------------*/
   /*> if (strcmp ("00", my.fore) == 0)   THEME_find   (x_theme);                     <*/
   /*> if (my.back == '-')                BACK_find    (x_back);                    <*/
   if      (my.report == 'w')  REPORT_wide    (my.theme );
   else if (my.report == 'e')  REPORT_every   (my.theme );
   else if (my.report == 'f')  REPORT_fullsome(my.theme );
   else if (my.report == 'n')  REPORT_narrow  (my.theme );
   else if (my.report == '!')  REPORT_quarter (my.theme );
   else if (my.report == 't')  REPORT_tiny    (my.theme );
   /*> else if (my.report == 'b')  BACK_report    ();                                 <+/   <*/
   else if (my.report == 'r')  RUNTIME_report ();
   /*---(complete)-----------------------*/
   DEBUG_PROG  yLOG_exit    (__FUNCTION__);
   yLOGS_end     ();
   return 0;
}
