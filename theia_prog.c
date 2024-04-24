#include   "theia.h"

tACCESSOR my;


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
static void      o___PREINIT___________o (void) {;}

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
static void      o___STARTUP____________o (void) {;}

char         /*--> initialize variables ------------------[ ------ [ ------ ]-*/
PROG__init              (int a_argc, char *a_argv [])
{
   /*---(locals)-------------------------*/
   char        rce         =  -10;
   int         i           =    0;
   int         j           =    0;
   int         x_running   =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter    (__FUNCTION__);
   /*---(check uid)----------------------*/
   if (getuid () != 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for normal version)-------*/
   x_running = yEXEC_find ("theia", NULL);
   DEBUG_PROG   yLOG_value   ("x_running" , x_running);
   --rce;  if (x_running > 1) {
      printf ("already running in normal mode\n");
      DEBUG_PROG   yLOG_note    ("already running in normal mode");
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for debug version)--------*/
   x_running = yEXEC_find ("theia_debug", NULL);
   DEBUG_PROG   yLOG_value   ("x_running" , x_running);
   --rce;  if (x_running > 1) {
      printf ("already running in debug mode\n");
      DEBUG_PROG   yLOG_note    ("already running in debug mode");
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check terminal)-----------------*/
   strcpy (my.term, "");
   ystrlcpy (my.term, getenv ("TERM"), LEN_LABEL);
   DEBUG_PROG   yLOG_info     ("TERM"      , my.term);
   --rce;  if (strcmp (my.term, "linux") == 0) {
      DEBUG_PROG   yLOG_note    ("using linux console");
   } else if  (strcmp (my.term, "Eterm") == 0) {
      DEBUG_PROG   yLOG_note    ("using eterm");
   } else {
      printf ("theia : unknown terminal type, no action\n");
      DEBUG_PROG   yLOG_note    ("unknown terminal type");
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(initialize)---------------------*/
   FORE_purge ();
   BACK_purge ();
   RUN_purge  ();
   my.identify = '·';
   my.theme    = 0;
   my.report   = '·';
   my.here     = '·';
   ystrlcpy (my.back_req, "·", LEN_TERSE);
   ystrlcpy (my.fore_req, "·", LEN_TERSE);
   my.custom   = -1;
   g_nback     = 0;
   g_cback     = 0;
   my.desk     = -1;
   my.scale    = 0.333;
   my.ygrid    = 1;
   my.xgrid    = 1;
   my.range    = 1;
   my.list     = '-';
   my.extra    = '-';
   my.eterm    = -1;
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
      if      (strcmp (a, "--identify") == 0)    my.identify = 'y';
      else if (strcmp (a, "--close"   ) == 0)    my.identify = 'x';
      /*> else if (strcmp (a, "-w"        ) == 0)    my.report   = 'w';               <*/
      /*> else if (strcmp (a, "--wide"    ) == 0)    my.report = 'w';                 <* 
       *> else if (strcmp (a, "-e"        ) == 0)    my.report = 'e';                 <* 
       *> else if (strcmp (a, "--every"   ) == 0)    my.report = 'e';                 <* 
       *> else if (strcmp (a, "-n"        ) == 0)    my.report = 'n';                 <* 
       *> else if (strcmp (a, "--narrow"  ) == 0)    my.report = 'n';                 <* 
       *> else if (strcmp (a, "-t"        ) == 0)    my.report = 't';                 <* 
       *> else if (strcmp (a, "--tiny"    ) == 0)    my.report = 't';                 <* 
       *> else if (strcmp (a, "-b"        ) == 0)    my.report = 'b';                 <* 
       *> else if (strcmp (a, "--backs"   ) == 0)    my.report = 'b';                 <* 
       *> else if (strcmp (a, "-r"        ) == 0)    my.report = 'r';                 <* 
       *> else if (strcmp (a, "--runtime" ) == 0)    my.report = 'r';                 <* 
       *> else if (strcmp (a, "-f"        ) == 0)    my.report = 'f';                 <* 
       *> else if (strcmp (a, "--fullsome") == 0)    my.report = 'f';                 <* 
       else if (strcmp (a, "-q"        ) == 0)    my.report = '!';                 <*/
      else if (strcmp (a, "--quarter" ) == 0)    my.report = '!';
      else if (strcmp (a, "--backs"   ) == 0)    my.report = 'b';
      /*> else if (strcmp (a, "--spin"    ) == 0)    my.back_req = '*';               <*/
      else if (strcmp (a, "--export"  ) == 0)    my.report = 'x';
      else if (strcmp (a, "--update"  ) == 0)    my.here   = 'u';
      else if (strcmp (a, "--pager"   ) == 0)    my.report = 'p';
      else if (strcmp (a, "--1st"     ) == 0)  { my.report = 'p'; my.desk   =  0; }
      else if (strcmp (a, "--2nd"     ) == 0)  { my.report = 'p'; my.desk   =  1; }
      else if (strcmp (a, "--3rd"     ) == 0)  { my.report = 'p'; my.desk   =  2; }
      else if (strcmp (a, "--4th"     ) == 0)  { my.report = 'p'; my.desk   =  3; }
      else if (strcmp (a, "--5th"     ) == 0)  { my.report = 'p'; my.desk   =  4; }
      else if (strcmp (a, "--6th"     ) == 0)  { my.report = 'p'; my.desk   =  5; }
      else if (strcmp (a, "--7th"     ) == 0)  { my.report = 'p'; my.desk   =  6; }
      else if (strcmp (a, "--8th"     ) == 0)  { my.report = 'p'; my.desk   =  7; }
      else if (strcmp (a, "--big"     ) == 0)    my.scale  = 0.500;
      else if (strcmp (a, "--large"   ) == 0)    my.scale  = 0.400;
      else if (strcmp (a, "--medium"  ) == 0)    my.scale  = 0.333;
      else if (strcmp (a, "--small"   ) == 0)    my.scale  = 0.250;
      else if (strcmp (a, "--tiny"    ) == 0)    my.scale  = 0.200;
      else if (strcmp (a, "--micro"   ) == 0)    my.scale  = 0.100;
      else if (strcmp (a, "--nano"    ) == 0)    my.scale  = 0.150;
      else if (strcmp (a, "--one"     ) == 0)  { my.range = 1; my.ygrid = 1; my.xgrid = 1; }
      else if (strcmp (a, "--two"     ) == 0)  { my.range = 2; my.ygrid = 1; my.xgrid = 2; }
      else if (strcmp (a, "--three"   ) == 0)  { my.range = 3; my.ygrid = 1; my.xgrid = 3; }
      else if (strcmp (a, "--all"     ) == 0)  { my.range = 8; my.ygrid = 2; my.xgrid = 4; }
      else if (strcmp (a, "--list"    ) == 0)    my.list  = 'y';
      else if (strcmp (a, "--extra"   ) == 0)    my.extra = 'y';
      /*---(background)------------------*/
      else if (len == 1 && a [0] >= 'a' && a [0] <= 'z') strcpy (my.back_req, a);
      else if (len == 2 && strchr ("abcdefghijklmnopqrstuvwxyz", a [0]) != 0 &&
            strchr ("[-+]", a [1]) != NULL)
         ystrlcpy (my.back_req, a, LEN_TERSE);
      /*---(foreground)------------------*/
      else if (len == 2 && strchr ("0123456789abcdef", a [0]) != 0 &&
            strchr ("0123456789abcdef", a [1]) != 0)
         ystrlcpy (my.fore_req, a, LEN_TERSE);
      /*---(unknown)---------------------*/
      else {
         ystrlcpy (my.shortcut, a, LEN_LABEL);
         DEBUG_ARGS   yLOG_info   ("shortcut"  , my.shortcut);
      }
   }
   /*---(summarize)----------------------*/
   DEBUG_ARGS   yLOG_value  ("entries"   , x_total);
   DEBUG_ARGS   yLOG_value  ("arguments" , x_args);
   DEBUG_ARGS   yLOG_char   ("identify"  , my.identify);
   DEBUG_ARGS   yLOG_char   ("report"    , my.report);
   DEBUG_ARGS   yLOG_char   ("here"      , my.here);
   DEBUG_ARGS   yLOG_value  ("desk"      , my.desk);
   DEBUG_ARGS   yLOG_double ("scale"     , my.scale);
   DEBUG_ARGS   yLOG_value  ("range"     , my.range);
   DEBUG_ARGS   yLOG_value  ("ygrid"     , my.ygrid);
   DEBUG_ARGS   yLOG_value  ("xgrid"     , my.xgrid);
   DEBUG_ARGS   yLOG_char   ("list"      , my.list);
   DEBUG_ARGS   yLOG_char   ("extra"     , my.extra);
   DEBUG_ARGS   yLOG_info   ("back_req"  , my.back_req);
   DEBUG_ARGS   yLOG_info   ("fore_req"  , my.fore_req);
   DEBUG_ARGS   yLOG_info   ("shortcut"  , my.shortcut);
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
   char       *x_file      = "/tmp/theia.txt";
   char        x_recd      [LEN_RECD]  = "";
   char        x_ref       [LEN_LABEL] = "";
   char        t           [LEN_LABEL] = "";
   short       c           =    0;
   char        x_back      =  '-';
   char       *p           = NULL;
   FILE       *f           = NULL;
   int         l           =    0;
   int         n           =   -1;
   /*---(begin)--------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(new terminal action)------------*/
   if (my.identify == 'y') {
      printf ("identifying\n");
      system ("wmctrl -l -G | grep \"Eterm 0.9.7\" | grep \"0    0    .... 20  \" > /tmp/theia.txt");
      c = yURG_lines (x_file);
      if (c > 0)  f = fopen (x_file, "rt");
      if (f != NULL) {
         printf ("theia --identify\n");
         printf ("   found %d lines\n", c);;
         fgets (x_recd, LEN_RECD, f);
         rc = fclose (f);
         l = strlen (x_recd);
         if (l > 1 && x_recd [l - 1] == '\n')  x_recd [--l] = '\0';
         printf ("   returned å%sæ\n", x_recd);
         if (l > 0) {
            sprintf (x_ref, "%-10.10s", x_recd);
            printf ("   window   å%sæ\n", x_ref);
            sprintf (t, "%-4.4s", x_recd + 24);
            printf ("   width    å%sæ\n", t);
            c  = atoi (t);
            if (c >= 592 && c <= 742) {
               sprintf (my.back_req, "%c", (c - 592) / 6 + 'a');
               printf ("   back      %s\n", my.back_req);
            }
            if (strcmp (my.back_req, "z") == 0) {
               rc = RUN_read  (FILE_RUNTIME);
               printf ("read %d\n", rc);
               DEBUG_PROG   yLOG_value   ("read"      , rc);
               n  = RUN_by_sticky (x_ref);
               printf ("sticky %d\n", n);
               DEBUG_PROG   yLOG_value   ("n"         , n);
               if (n >= 0) {
                  DEBUG_PROG   yLOG_note    ("already exists");
                  DEBUG_PROG   yLOG_exit    (__FUNCTION__);
                  return 1;
               }
               RUN_purge ();
               strcpy (my.back_req, "k");
               sprintf (x_recd, "wmctrl -i -r %s -e 0,350,720,709,30  2>&1 > /dev/null", x_ref);
               system (x_recd);
               sprintf (x_recd, "wmctrl -i -r %s -b add,sticky        2>&1 > /dev/null", x_ref);
               system (x_recd);
               sprintf (x_recd, "wmctrl -i -r %s -b add,above         2>&1 > /dev/null", x_ref);
               printf ("system window\n");
            } else {
               sprintf (x_recd, "wmctrl -i -r %s -e 0,150,100,529,383 2>&1 > /dev/null", x_ref);
            }
            system (x_recd);
         }
      }
      ystrlcpy (my.fore_req, "95", LEN_TERSE);
   }
   if (my.identify == 'x') {
      DEBUG_PROG   yLOG_note    ("updating after close of eterm window");
      rc = RUN_read  (FILE_RUNTIME);
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
      rc = RUN_clear  (n);
      rc = RUN_gather ();
      rc = RUN_write (FILE_RUNTIME);
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return 1;
   }
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
static void      o___EXECUTION__________o (void) {;}

char
PROG_dawn               (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        n           =    0;
   char        x_name      [LEN_HUND]  = "";
   char        x_desk      =    0;
   /*---(begin)--------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(configure)----------------------*/
   rc = CONF_read ();
   DEBUG_PROG   yLOG_value    ("conf"      , rc);
   if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check terminal type)------------*/
   DEBUG_PROG   yLOG_info     ("TERM"      , my.term);
   --rce;  if (strcmp (my.term, "linux") == 0) {
      printf ("linux terminal\n");
      my.eterm = -1;
      /*> ystrlcpy (my.fore_req, "99", LEN_TERSE);                                    <*/
      ystrlcpy (my.fore_act, "95", LEN_TERSE);
   } else if (strcmp (my.term, "Eterm") == 0) {
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
      ystrlcpy (my.back_act, g_runs [n].r_back, LEN_TERSE);
      ystrlcpy (my.fore_act, g_runs [n].r_fore, LEN_TERSE);
      if (my.desk < 0)  my.desk = yX11_desk_current (NULL);
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
   }
   /*> BACK_report (stdout);                                                          <*/
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
   if (my.eterm > 0) {
      if (strcmp (my.back_req, "·") != NULL || strcmp (my.fore_req, "·") != NULL) {
         n = RUN_by_eterm (my.eterm);
         if (strcmp (my.back_req, "·") != NULL) {
            m = BACK_by_abbr  (my.back_req);
            ystrlcpy (g_runs [n].r_back, g_backs [m].b_terse, LEN_TERSE);
         }
         if (strcmp (my.fore_req, "·") != NULL) {
            m = FORE_by_abbr (my.fore_req);
            ystrlcpy (g_runs [n].r_fore, g_fores [m].f_abbr, LEN_TERSE);
         }
         RUN_write (FILE_RUNTIME);
      }
      else if (my.here != '·') {
         RUN_write (FILE_RUNTIME);
      }
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

static char  s_print  [LEN_HUND] = "";

char*
PROG__unit_title        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        n           =    0;
   char        x_name      [LEN_HUND]  = "";
   char        x_desk      =    0;
   int         x_eterm     =   -1;
   /*---(begin)--------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(check terminal type)------------*/
   rc = RUN_read   (FILE_RUNTIME);
   sleep (1);
   printf ("\e]2;testing");
   sleep (1);
   printf ("\e[9n");
   sleep (1);
   rc = RUN_gather ();
   DEBUG_PROG   yLOG_value    ("run"       , rc);
   rc = yEXEC_find_my_eterm (getpid (), &(x_eterm));
   DEBUG_PROG   yLOG_value    ("my_eterm"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return "can't find eterm";
   }
   DEBUG_PROG   yLOG_value    ("eterm"     , x_eterm);
   rc = RUN_by_eterm (x_eterm);
   DEBUG_PROG   yLOG_value    ("by_eterm"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return "can't get eterm record";
   }
   n = rc;
   /*> if (r_eterm != NULL)  *r_eterm = x_eterm;                                      <*/
   /*> if (r_title != NULL)  ystrlcpy (r_title, g_runs [n].r_title, LEN_HUND);        <*/
   ystrlcpy (s_print, g_runs [n].r_title, LEN_HUND);
   rc = RUN_write  (FILE_RUNTIME);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return s_print;
}

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
   int         x_argc      =    5;
   char       *x_argv [5]  = { "theia_debug", "@@kitchen" , "@@ydesk"  , "@@yexec", "@@yx11"  };
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

