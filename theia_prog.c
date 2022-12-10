#include   "theia.h"



/*====================------------------------------------====================*/
/*===----                            program                           ----===*/
/*====================------------------------------------====================*/
void  o___PROGRAM_________o () { return; }

static char s_version    [LEN_HUND];

char*        /*--> return versioning information ---------[ ------ [ ------ ]-*/
PROG_version       (void)
{
   char        t [LEN_LABEL] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", LEN_LABEL);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", LEN_LABEL);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", LEN_LABEL);
#else
   strncpy (t, "[unknown    ]", LEN_LABEL);
#endif
   snprintf (s_version, LEN_HUND, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return s_version;
}



/*====================------------------------------------====================*/
/*===----                       pre-initialization                     ----===*/
/*====================------------------------------------====================*/
static void      o___PREINIT_________________o (void) {;}

char       /*----: very first setup ------------------s-----------------------*/
PROG__header            (void)
{
   /*---(header)----------------------*/
   DEBUG_PROG   yLOG_enter (__FUNCTION__);
   /*---(versioning)------------------*/
   DEBUG_PROG   yLOG_info     ("purpose" , P_PURPOSE);
   DEBUG_PROG   yLOG_info     ("namesake", P_NAMESAKE);
   DEBUG_PROG   yLOG_info     ("heritage", P_HERITAGE);
   DEBUG_PROG   yLOG_info     ("imagery" , P_IMAGERY);
   DEBUG_PROG   yLOG_info     ("theia"   , PROG_version ());
   DEBUG_PROG   yLOG_note     ("custom core");
   DEBUG_PROG   yLOG_info     ("yURG"    , yURG_version      ());
   DEBUG_PROG   yLOG_info     ("ySTR"    , ySTR_version      ());
   DEBUG_PROG   yLOG_info     ("yLOG"    , yLOGS_version     ());
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit  (__FUNCTION__);
   return 0;
}

char
PROG_urgents            (int a_argc, char *a_argv [])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(set mute)-----------------------*/
   yURG_all_mute ();
   /*---(start logger)-------------------*/
   rc = yURG_logger  (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("logger"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(process urgents)----------------*/
   rc = yURG_urgs    (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("urgents"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(show header)--------------------*/
   rc = PROG__header ();
   DEBUG_PROG   yLOG_value    ("header"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   return rc;
}



/*====================------------------------------------====================*/
/*===----                      startup functions                       ----===*/
/*====================------------------------------------====================*/
static void      o___STARTUP_________________o (void) {;}

char         /*--> initialize variables ------------------[ ------ [ ------ ]-*/
PROG__init              (int a_argc, char *a_argv [])
{
   /*---(locals)-------------------------*/
   int         i           = 0;             /* iterator -- structure entry    */
   int         j           = 0;             /* iterator -- color entry        */
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter    (__FUNCTION__);
   /*---(runtime)------------------------*/
   /*> g_nrun = 0;                                                                    <* 
    *> for (i = 0; i < MAX_RUN; ++i) {                                                <* 
    *>    g_runs [i].ppid       = -1;                                                 <* 
    *>    g_runs [i].when       = -1;                                                 <* 
    *>    g_runs [i].back_key   = '-';                                                <* 
    *>    g_runs [i].back_hex   = 0;                                                  <* 
    *>    strcpy (g_runs [i].theme_ref , "00");                                       <* 
    *>    strcpy (g_runs [i].theme_name, "unknown");                                  <* 
    *> }                                                                              <*/
   /*---(runtime)------------------------*/
   /*---(initialize)---------------------*/
   FORE_purge ();
   BACK_purge ();
   RUN_purge  ();
   my.theme  = 0;
   my.report = '·';
   my.here   = '·';
   my.back_req = '·';
   strlcpy (my.fore_req, "·", LEN_TERSE);
   my.custom = -1;
   g_nback   = 0;
   g_cback   = 0;
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit     (__FUNCTION__);
   return 0;
}

char         /*--> process the command line arguments ----[ ------ [ ------ ]-*/
PROG__args              (int a_argc, char *a_argv [])
{
   /*---(locals)-------------------------*/
   char     *a         = NULL;         /* current argument                    */
   int       i         = 0;            /* loop iterator -- arguments          */
   int       len       = 0;            /* argument length                     */
   int         x_total     = 0;             /* total args looked at           */
   int         x_args      = 0;             /* num args identified            */
   int         j           = 0;             /* iterator -- string position    */
   int         x_num       = 0;
   int         x_place     = 0;
   int         x_mult      = 0;
   /*---(begin)--------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(process)------------------------*/
   for (i = 1; i < a_argc; ++i) {
      /*---(get next)--------------------*/
      a = a_argv[i];
      ++x_total;
      if      (a[0] == '@')                     continue;
      len = strlen(a);
      DEBUG_ARGS   yLOG_info  ("argument"  , a);
      ++x_args;
      /*---(reporting)-------------------*/
      if      (strcmp (a, "-w"        ) == 0)    my.report = 'w';
      else if (strcmp (a, "--wide"    ) == 0)    my.report = 'w';
      else if (strcmp (a, "-e"        ) == 0)    my.report = 'e';
      else if (strcmp (a, "--every"   ) == 0)    my.report = 'e';
      else if (strcmp (a, "-n"        ) == 0)    my.report = 'n';
      else if (strcmp (a, "--narrow"  ) == 0)    my.report = 'n';
      else if (strcmp (a, "-t"        ) == 0)    my.report = 't';
      else if (strcmp (a, "--tiny"    ) == 0)    my.report = 't';
      else if (strcmp (a, "-b"        ) == 0)    my.report = 'b';
      else if (strcmp (a, "--backs"   ) == 0)    my.report = 'b';
      else if (strcmp (a, "-r"        ) == 0)    my.report = 'r';
      else if (strcmp (a, "--runtime" ) == 0)    my.report = 'r';
      else if (strcmp (a, "-f"        ) == 0)    my.report = 'f';
      else if (strcmp (a, "--fullsome") == 0)    my.report = 'f';
      else if (strcmp (a, "-q"        ) == 0)    my.report = '!';
      else if (strcmp (a, "--quarter" ) == 0)    my.report = '!';
      else if (strcmp (a, "--spin"    ) == 0)    my.back_req = '*';
      else if (strcmp (a, "--export"  ) == 0)    my.report = 'x';
      else if (strcmp (a, "--identify") == 0)    my.here   = 'y';
      else if (strcmp (a, "--update"  ) == 0)    my.here   = 'y';
      /*---(background)------------------*/
      else if (len == 1 && a [0] >= 'a' && a [0] <= 'z') my.back_req = a [0];
      else if (len == 1 && a [0] >= 'A' && a [0] <= 'Z') my.back_req = a [0];
      /*---(foreground)------------------*/
      else if (len == 2 && strchr ("0123456789abcdef", a [0]) != 0 &&
            strchr ("0123456789abcdef", a [1]) != 0)
         strlcpy (my.fore_req, a, LEN_TERSE);
      /*---(unknown)---------------------*/
      else {
         strlcpy (my.shortcut, a, LEN_LABEL);
         DEBUG_ARGS   yLOG_info   ("shortcut"  , my.shortcut);
      }
   }
   /*---(summarize)----------------------*/
   DEBUG_ARGS   yLOG_value  ("entries"   , x_total);
   DEBUG_ARGS   yLOG_value  ("arguments" , x_args);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> final initialization steps ------------[ ------ [ ------ ]-*/
PROG__begin             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(begin)--------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(configure)----------------------*/
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
PROG_startup            (int a_argc, char *a_argv [])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)----------------------*/
   yURG_stage_check (YURG_BEG);
   DEBUG_PROG  yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   rc = PROG__init   (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("init"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(arguments)----------------------*/
   rc = PROG__args   (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("args"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(begin)--------------------------*/
   rc = PROG__begin  ();
   DEBUG_PROG   yLOG_value    ("begin"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG  yLOG_exit  (__FUNCTION__);
   yURG_stage_check (YURG_MID);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                       execution support                      ----===*/
/*====================------------------------------------====================*/
static void      o___EXECUTION_______________o (void) {;}

char
PROG_dawn               (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        n           =    0;
   char        x_name      [LEN_HUND]  = "";
   char        x_desk      =    0;
   char        t           [LEN_RECD]  = "";
   /*---(begin)--------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(configure)----------------------*/
   rc = CONF_read ();
   DEBUG_PROG   yLOG_value    ("conf"      , rc);
   rc = RUN_read  (FILE_RUNTIME);
   DEBUG_PROG   yLOG_value    ("run"       , rc);
   rc = yEXEC_find_my_eterm (getpid (), &(my.eterm));
   DEBUG_PROG   yLOG_value    ("my_eterm"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_value    ("eterm"     , my.eterm);
   rc = RUN_by_eterm (my.eterm);
   DEBUG_PROG   yLOG_value    ("by_eterm"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   n = rc;
   my.back_act = g_runs [n].back [0];
   strlcpy (my.fore_act, g_runs [n].fore, LEN_TERSE);
   my.desk = yX11_desk_current (NULL);
   /*> printf ("my.desk  = %d\n", my.desk);                                           <*/
   my.win  = yX11_win_current (x_name, &x_desk);
   /*> printf ("my.win   = %ld (%1d) %s\n", my.win, x_desk, x_name);                  <*/
   /*> sprintf (t, "wmctrl -i -r %ld -T \"YOU ARE HERE\"", my.win);                   <* 
    *> system (t);                                                                    <*/
   RUN_gather ();
   /*> printf ("rpid     = %d\n", getpid ());                                         <*/
   /*> printf ("my eterm = %d\n", my.eterm);                                          <*/
   /*> printf ("back     = %c\n", my.back_act);                                       <*/
   /*> printf ("fore     = %s\n", my.fore_act);                                       <*/
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
PROG_dusk               (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        n           =    0;
   char        m           =    0;
   /*---(begin)--------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(configure)----------------------*/
   if (my.back_req != '·' || strcmp (my.fore_req, "·") != NULL) {
      n = RUN_by_eterm (my.eterm);
      if (my.back_req != '·') {
         m = BACK_by_abbr (my.back_req);
         strlcpy (g_runs [n].back, g_backs [m].terse, LEN_TERSE);
      }
      if (strcmp (my.fore_req, "·") != NULL) {
         m = FORE_by_ref (my.fore_req);
         strlcpy (g_runs [n].fore, g_fores [m].refno, LEN_TERSE);
      }
      RUN_write (FILE_RUNTIME);
   }
   else if (my.here == 'y') {
      RUN_write (FILE_RUNTIME);
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        program shutdown                      ----===*/
/*====================------------------------------------====================*/
static void      o___SHUTDOWN________________o (void) {;}

char       /*----: drive the program closure activities ----------------------*/
PROG__end               (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(shutdown)--------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char             /* [------] drive the program closure activities ------------*/
PROG_shutdown           (void)
{
   /*---(stage-check)--------------------*/
   yURG_stage_check (YURG_END);
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter    (__FUNCTION__);
   PROG__end ();
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit     (__FUNCTION__);
   DEBUG_PROG   yLOGS_end    ();
   return 0;
}




/*====================------------------------------------====================*/
/*===----                          unit testing                        ----===*/
/*====================------------------------------------====================*/
void  o___UNITTEST________o () { return; }

char
PROG__unit_quiet   (void)
{
   char        rc          =    0;
   int         x_argc      =    1;
   char       *x_argv [1]  = { "theia" };
   rc = PROG_urgents   (x_argc, x_argv);
   rc = PROG_startup   (x_argc, x_argv);
   return rc;
}

char
PROG__unit_loud    (void)
{
   char        rc          =    0;
   int         x_argc      =    2;
   char       *x_argv [2]  = { "theia_debug", "@@kitchen" };
   rc = PROG_urgents   (x_argc, x_argv);
   rc = PROG_startup   (x_argc, x_argv);
   return rc;
}

char       /*----: set up program urgents/debugging --------------------------*/
PROG__unit_end     (void)
{
   /*> PROG_shutdown  ();                                                             <+/   <*/
   return 0;
}

