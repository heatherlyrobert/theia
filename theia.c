/*===============================[[ beg code ]]===============================*/

/*
 *   black
 *
 *
 *
 *
 *
 *
 *
 */

#include   "theia.h"

#define     MAX_COLOR     10
/*------------------------------------- 12345678    12345678    12345678    12345678    12345678    12345678    12345678    12345678    12345678    12345678  */
char        cname  [MAX_COLOR][20] = { "black"   , "d.red"   , "d.green" , "d.yellow", "d.blue"  , "d.purple", "d.cyan"  , "brown"   , ""        , "default" };
char        cname2 [MAX_COLOR][20] = { "grey"    , "l.red"   , "l.green" , "l.yellow", "l.blue"  , "l.purple", "l.cyan"  , "white"   , ""        , "default" };
char        corder [MAX_COLOR]     = { 9, 0, 1, 2, 3, 4, 5, 6, 7, -1 };

char        abbr   [MAX_COLOR] = { 'k', 'r', 'g', 'y', 'b', 'm', 'c', 'w' };

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






/*====================------------------------------------====================*/
/*===----                            utilities                         ----===*/
/*====================------------------------------------====================*/
void  o___UTILITIES_______o () { return; }

char*      /*LD--: clean whitespace from both sides of a string -------------*/
ySTR_trim          (char *a_source, char a_mode)
{
   /*---(design notes)---------------------*/
   /*
    *   h = head
    *   t = tail
    *   b = head and tail
    *   e = head, tail, and every internal
    *   c = head, tail, and compress internal
    *
    */
   /*---(defenses)-------------------------*/
   if (a_source == NULL) return NULL;
   /*---(locals)---------------------------*/
   int       i, j;                     /* loop iterators -- characters        */
   int       len       = 0;            /* source string length                */
   int       count     = 0;            /* whitespace counter                  */
   int       limit     = (a_mode == 'c') ? 1 : 0;
   /*---(leading whitespace)---------------*/
   if (strchr("hbce", a_mode) != 0) {
      len = strlen(a_source);
      for (i = 0; i <= len; ++i) {
         if (a_source[0] != ' ') break;
         for (j = 0; j <= len; ++j)
            a_source[j] = a_source[j + 1];
         --len;
      }
   }
   /*---(trailing whitespace)--------------*/
   if (strchr("tbce", a_mode) != 0) {
      len = strlen(a_source);
      for (i = len - 1; i >= 0; --i) {
         if (a_source[i] != ' ') break;
         a_source[i] = '\0';
      }
   }
   /*---(internal whitespace)--------------*/
   if (strchr("ec" , a_mode) != 0) {
      len = strlen(a_source);
      for (i = 0; i <= len; ++i) {
         if (a_source[i] != ' ') { count = 0; continue; }
         if (count <  limit)     { ++count;   continue; }
         for (j = i; j <= len; ++j)
            a_source[j] = a_source[j + 1];
         --len;
         --i;
      }
   }
   /*---(complete)-------------------------*/
   return a_source;
}



/*====================------------------------------------====================*/
/*===----                           schemes                            ----===*/
/*====================------------------------------------====================*/
void  o___SCHEMES_________o () { return; }



/*====================------------------------------------====================*/
/*===----                         terminals                            ----===*/
/*====================------------------------------------====================*/
void  o___TERMS___________o () { return; }

char         /*--> find the terminal pid -----------------[ ------ [ ------ ]-*/
TERM_find          (int a_pid, int *a_term)
{
   /*---(locals)-----------+-----------+-*/
   FILE       *f           = NULL;          /* file handle for source file    */
   char        rce         = -10;           /* return code for errors         */
   char        rc          =   0;           /* generic return code            */
   char        recd        [LEN_RECD];
   int         x_len;
   char       *p;
   char       *q           = "\x1F";
   int         x_pid       = 0;             /* current pid                    */
   int         x_ppid      = 0;             /* parent pid                     */
   char        x_prog      [100];           /* program name                   */
   char        x_str       [100];           /* temp string                    */
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DEBUG_PROG   yLOG_value   ("a_pid"     , a_pid);
   DEBUG_PROG   yLOG_point   ("a_term"    , a_term);
   /*---(run up proc ladder)-------------*/
   x_ppid = x_pid = a_pid;
   while (x_pid != 1) {
      DEBUG_PROG   yLOG_value   ("processing", x_pid);
      /*---(open file)-------------------*/
      sprintf (x_str, "/proc/%d/status", x_pid);
      f = fopen (x_str, "r");
      DEBUG_PROG   yLOG_info    ("filename"  , x_str);
      DEBUG_PROG   yLOG_point   ("file"      , f);
      --rce;  if (f == NULL) {
         DEBUG_PROG   yLOG_note    ("proc state file did not open properly");
         DEBUG_PROG   yLOG_exit    (__FUNCTION__);
         return rce;
      }
      /*---(walk status lines)-----------*/
      x_ppid = x_pid;
      while (1) {
         /*---(get record)---------------*/
         fgets (recd, LEN_RECD, f);
         if (feof(f))                     break;
         x_len = strlen (recd);
         if (x_len <= 0)                  continue;
         recd [--x_len] = '\0';
         DEBUG_PROG   yLOG_info    ("entry"     , recd);
         /*---(save name)----------------*/
         if (strncmp (recd, "Name:", 5) == 0) {
            strcpy (x_prog, recd + 6);
            DEBUG_PROG   yLOG_info    ("name"      , x_prog);
         }
         /*---(save pid)-----------------*/
         if (strncmp (recd, "PPid:",  5) == 0) {
            x_ppid = atoi (recd + 6);
            DEBUG_PROG   yLOG_value   ("ppid"      , x_ppid);
            break;
         }
      }  /*---(done while)---------------*/
      /*---(close file)---------------------*/
      rc = fclose (f);
      --rce;  if (rc != 0) {
         DEBUG_PROG   yLOG_note    ("proc state file did not close properly");
         DEBUG_PROG   yLOG_exit    (__FUNCTION__);
         return rce;
      }
      --rce;  if (x_ppid == x_pid) {
         DEBUG_PROG   yLOG_note    ("did not find a ppid for process");
         DEBUG_PROG   yLOG_exit    (__FUNCTION__);
         return rce;
      }
      if (strcmp (x_prog, "Eterm"  ) == 0) {
         DEBUG_PROG   yLOG_note    ("FOUND an eterm");
         break;
      }
      if (strcmp (x_prog, "hearth" ) == 0) {
         DEBUG_PROG   yLOG_note    ("FOUND an hearth");
         break;
      }
      x_pid = x_ppid;
   }
   /*---(test for failure)---------------*/
   --rce;  if (x_pid == 1) {
      DEBUG_PROG   yLOG_note    ("ended at kharon (pid 1), way too high");
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(save terminal pid)--------------*/
   DEBUG_PROG   yLOG_value   ("final pid" , x_pid);
   if (a_term != NULL)  *a_term = x_pid;
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         backgrounds                          ----===*/
/*====================------------------------------------====================*/
void  o___BACKS___________o () { return; }

char         /*--> set a back by key ---------------------[ ------ [ ------ ]-*/
BACK_custom        (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;
   int         j           = 0;
   int         x           = 0;
   int         y           = 0;
   char        x_str       [20];
   int         x_ppid      = 0;
   long        x_now       = 0;
   char        rce         = -10;
   char        rc          = 0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense: index)-----------------*/
   --rce;  if (my.custom < 0)           return rce;
   /*---(set background)-----------------*/
   sprintf (x_str, "¥]6;2;tint;bg;0x%06x", my.custom);
   DEBUG_GRAF  yLOG_complex ("color"     , "%10d, %s", my.custom, x_str);
   printf ("\e]6;0;true");
   printf ("¥]6;2;tint;bg;0x%06x", my.custom);
   /*---(find eterm or hestia)-----------*/
   rc = TERM_find (getppid(), &x_ppid);
   --rce;  if (rc < 0)                 return rce;
   /*---(update in runtime list)---------*/
   x_now  = time(NULL);
   for (j = 0; j < g_nrun; ++j) {
      /*> if (x_ppid != g_runs [j].ppid)  continue;                                   <* 
       *> g_runs [j].when       = x_now;                                              <* 
       *> g_runs [j].back_key   = '>';                                                <* 
       *> strcpy (g_runs [j].back_name, "custom");                                    <* 
       *> g_runs [j].back_hex   = my.custom;                                          <*/
      break;
   }
   if (j == g_nrun) {
      /*> g_runs [j].ppid       = x_ppid;                                             <* 
       *> g_runs [j].when       = x_now;                                              <* 
       *> g_runs [j].back_key   = '>';                                                <* 
       *> strcpy (g_runs [j].back_name, "custom");                                    <* 
       *> g_runs [j].back_hex   = my.custom;                                          <* 
       *> strcpy (g_runs [j].theme_ref, my.fore);                                   <* 
       *> strcpy (g_runs [j].theme_name, "unknown");                                  <* 
       *> ++g_nrun;                                                                   <*/
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         font themes                          ----===*/
/*====================------------------------------------====================*/
void  o___THEMES__________o () { return; }

char         /*--> set a scheme by reference number ------[ ------ [ ------ ]-*/
THEME_find         (char *a_ref)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;
   /*---(find scheme)--------------------*/
   my.theme  = 0;
   for (i = 0; i < g_nfore; ++i) {
      if (strcmp (g_fores [i].f_abbr, a_ref) != 0)  continue;
      my.theme  = i;
      break;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char         /*--> set a scheme by reference number ------[ ------ [ ------ ]-*/
THEME_set          (void)
{
   /*---(design notes)-------------------*/
   /*
    *  P0 - P7   normal colors
    *  P8 - Pf   bright colors
    *
    *  P0 is also the default background color
    *  Pf is also the default foreground color
    *
    *
    */
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;
   int         j           = 0;
   int         x           = 0;
   int         y           = 0;
   char        x_str       [20];
   int         x_ppid      = 0;
   long        x_now       = 0;
   char        rce         = -10;
   char        rc          = 0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(find reference)-----------------*/
   for (j = 0; j < 18; ++j) {
      /*> if (j ==  0) {                                                                              <* 
       *>    yLOG_complex ("back"      , "%2d, 49, %8d, %6x", j, g_fores [my.theme].color [j], g_fores [my.theme].color [j]);   <* 
       *>    printf ("¥]49;%06x, g_fores [my.theme].color [j]);                                                 <* 
       *> }                                                                                           <* 
       *> if (j ==  1) {                                                                              <* 
       *>    yLOG_complex ("fore"      , "%2d, 39, %8d, %6x", j, g_fores [my.theme].color [j], g_fores [my.theme].color [j]);   <* 
       *>    printf ("¥]39;%06x, g_fores [my.theme].color [j]);                                                 <* 
       *> }                                                                                           <*/
      if (j >=  2) {
         x = ((int) j / 2) - 1 + ((j % 2) *  8);
         y = ((int) j / 2) - 1 + ((j % 2) * 10) + 30;
         sprintf (x_str, "¥]P%1x%06x", x, g_fores [my.theme].f_hex [j]);
         DEBUG_GRAF  yLOG_complex ("color"     , "%2d, %2d, %8d, %6x, %s", j, y, g_fores [my.theme].f_hex [j], g_fores [my.theme].f_hex [j], x_str);
         printf ("¥]P%1x%06x", x, g_fores [my.theme].f_hex [j]);
      }
   }
   /*---(find eterm or hestia)-----------*/
   rc = TERM_find (getppid(), &x_ppid);
   --rce;  if (rc < 0)                 return rce;
   /*---(update in runtime list)---------*/
   x_now  = time(NULL);
   for (j = 0; j < g_nrun; ++j) {
      /*> if (x_ppid != g_runs [j].ppid)  continue;                                   <* 
       *> g_runs [j].when      = x_now;                                               <* 
       *> strcpy (g_runs [j].theme_ref, my.fore);                                   <* 
       *> strcpy (g_runs [j].theme_name, g_fores [my.theme].f_name);                    <*/
      break;
   }
   if (j == g_nrun) {
      /*> g_runs [j].ppid      = x_ppid;                                              <* 
       *> g_runs [j].when      = x_now;                                               <* 
       *> g_runs [j].back_key  = '-';                                                 <* 
       *> strcpy (g_runs [j].back_name , "------");                                   <* 
       *> g_runs [j].back_hex  = 0;                                                   <* 
       *> strcpy (g_runs [j].theme_ref, my.fore);                                   <* 
       *> strcpy (g_runs [j].theme_name, g_fores [my.theme].f_name);                    <* 
       *> ++g_nrun;                                                                   <*/
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         runtime file                         ----===*/
/*====================------------------------------------====================*/
void  o___RUNTIME_________o () { return; }

char         /*--> save current theme to runtime ---------[ ------ [ ------ ]-*/
RUNTIME_write      (void)
{
   /*---(locals)-----------+-----------+-*/
   FILE       *f           = NULL;          /* file handle for source file    */
   char        rce         = -10;           /* return code for errors         */
   char        rc          =   0;           /* generic return code            */
   char        recd        [LEN_RECD];
   int         x_len;
   char       *p;
   char       *q           = "\x1F";
   int         i           = 0;
   int         j           = 0;
   long        x_num       = 0;
   char        x_back      [LEN_RECD] = "";
   char        x_theme     [LEN_RECD] = "";
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_enter   (__FUNCTION__);
   /*---(open file)----------------------*/
   f = fopen (FILE_RUNTIME, "w");
   DEBUG_FILE   yLOG_info    ("filename"  , FILE_RUNTIME);
   DEBUG_FILE   yLOG_point   ("file"      , f);
   --rce;  if (f == NULL) {
      DEBUG_FILE   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(header)-------------------------*/
   fprintf (f, "#!/usr/local/bin/theia\n");
   fprintf (f, "#   generated by theia euryphaessa (wide-shinning) the heatherly terminal management tool\n");
   /*---(column headings)----------------*/
   fprintf (f, "\n\n");
   fprintf (f, "#===[[ TERMINALS ]]==================================================================================================================\n");
   fprintf (f, "#-pid------- %c --time------ %c -background------------------- %c -font-theme------------------- %c -geometry--------------------- %c\n", 31, 31, 31, 31, 31);
   /*---(write g_runs)-----------------*/
   for (i = 0; i < g_nrun; ++i) {
      /*> if (g_runs [i].back_key == '-')  sprintf (x_back, "-  ------  ------");                                                                                                                           <* 
       *> else                               sprintf (x_back, "%c  %06x  %s", g_runs[i].back_key, g_runs[i].back_hex, g_runs[i].back_name);                                                                 <* 
       *> sprintf (x_theme, "%2s  %-25.25s", g_runs[i].theme_ref, g_runs[i].theme_name);                                                                                                                    <* 
       *> fprintf (f, "%-12d %c %-12d %c %-30.30s %c %-30.30s %c %2d   %c %4d %4d   %c %4d %4d %c¦", g_runs[i].ppid, 31, g_runs[i].when, 31, x_back, 31, x_theme, 31, 1, 'c', 50, 10, 'q', 400, 800, 31);   <*/
   }
   fprintf (f, "\n# end of file\n");
   /*---(close file)---------------------*/
   rc = fclose (f);
   --rce;  if (rc != 0) {
      DEBUG_FILE   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_FILE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> save current theme to runtime ---------[ ------ [ ------ ]-*/
RUNTIME_read       (void)
{
   /*---(locals)-----------+-----------+-*/
   /*> FILE       *f           = NULL;          /+ file handle for source file    +/                <* 
    *> char        rce         = -10;           /+ return code for errors         +/                <* 
    *> char        rc          =   0;           /+ generic return code            +/                <* 
    *> char        recd        [LEN_RECD];                                                          <* 
    *> int         x_len;                                                                           <* 
    *> char       *p;                                                                               <* 
    *> char       *q           = "\x1F";                                                            <* 
    *> long        x_num       = 0;                                                                 <* 
    *> int         x_lines     = 0;                                                                 <* 
    *> int         j           = 0;                                                                 <* 
    *> int         x_place     = 0;                                                                 <* 
    *> int         x_mult      = 0;                                                                 <* 
    *> char        x_result    [20];                                                                <* 
    *> /+---(header)-------------------------+/                                                     <* 
    *> DEBUG_FILE   yLOG_enter   (__FUNCTION__);                                                    <* 
    *> g_nrun = 0;                                                                                  <* 
    *> /+---(open file)----------------------+/                                                     <* 
    *> f = fopen (FILE_RUNTIME, "r");                                                               <* 
    *> DEBUG_FILE   yLOG_info    ("filename"  , FILE_RUNTIME);                                      <* 
    *> DEBUG_FILE   yLOG_point   ("file"      , f);                                                 <* 
    *> --rce;  if (f == NULL) {                                                                     <* 
    *>    DEBUG_FILE   yLOG_exit    (__FUNCTION__);                                                 <* 
    *>    return rce;                                                                               <* 
    *> }                                                                                            <* 
    *> /+---(read terminal)------------------+/                                                     <* 
    *> while (1) {                                                                                  <* 
    *>    /+---(get record)------------------+/                                                     <* 
    *>    fgets (recd, LEN_RECD, f);                                                                <* 
    *>    if (feof(f))                     break;                                                   <* 
    *>    ++x_lines;                                                                                <* 
    *>    DEBUG_FILE   yLOG_value   ("LINE"      , x_lines);                                        <* 
    *>    x_len = strlen (recd);                                                                    <* 
    *>    if (x_len <= 0)                  continue;                                                <* 
    *>    recd [--x_len] = '\0';                                                                    <* 
    *>    /+---(filter non-scheme lines)-----+/                                                     <* 
    *>    if (x_len <= 0)                  continue;                                                <* 
    *>    if (recd[0] == '#')              continue;                                                <* 
    *>    if (recd[0] == ' ')              continue;                                                <* 
    *>    if (recd[0] == '\0')             continue;                                                <* 
    *>    /+---(get ppid)--------------------+/                                                     <* 
    *>    p = strtok (recd, "\x1F");                                                                <* 
    *>    if (p == NULL)                   continue;                                                <* 
    *>    ySTR_trim (p, ySTR_BOTH);                                                                 <* 
    *>    x_num = atoi (p);                                                                         <* 
    *>    DEBUG_FILE   yLOG_value   ("ppid"      , x_num);                                          <* 
    *>    if (x_num <= 0)                  continue;                                                <* 
    *>    g_runs [g_nrun].ppid = x_num;                                                             <* 
    *>    /+---(get time)--------------------+/                                                     <* 
    *>    p = strtok (NULL, "\x1F");                                                                <* 
    *>    if (p == NULL)                   continue;                                                <* 
    *>    ySTR_trim (p, ySTR_BOTH);                                                                 <* 
    *>    x_num = atoi (p);                                                                         <* 
    *>    DEBUG_FILE   yLOG_value   ("time"      , x_num);                                          <* 
    *>    if (x_num <= 0)                  continue;                                                <* 
    *>    g_runs [g_nrun].when = x_num;                                                             <* 
    *>    /+---(get background)--------------+/                                                     <* 
    *>    p = strtok (NULL, "\x1F");                                                                <* 
    *>    if (p == NULL)                   continue;                                                <* 
    *>    ySTR_trim (p, ySTR_BOTH);                                                                 <* 
    *>    x_len = strlen (p);                                                                       <* 
    *>    if (x_len  <  9)                 continue;                                                <* 
    *>    DEBUG_FILE   yLOG_value   ("back_key"  , p[0]);                                           <* 
    *>    g_runs [g_nrun].back_key  = p[0];                                                         <* 
    *>    if      (p[0] == '-')  x_num = 0;                                                         <* 
    *>    else {                                                                                    <* 
    *>       /+---(read color)------------------+/                                                  <* 
    *>       p = p + 3;                                                                             <* 
    *>       x_num  = 0;                                                                            <* 
    *>       x_mult = 1;                                                                            <* 
    *>       for (j = 5; j >= 0; --j) {                                                             <* 
    *>          if (p[j] >= '0' && p[j] <= '9')  x_place = p[j] - '0';                              <* 
    *>          if (p[j] >= 'a' && p[j] <= 'f')  x_place = p[j] - 'a' + 10;                         <* 
    *>          if (p[j] >= 'A' && p[j] <= 'F')  x_place = p[j] - 'A' + 10;                         <* 
    *>          x_num  += x_place * x_mult;                                                         <* 
    *>          x_mult *= 16;                                                                       <* 
    *>       }                                                                                      <* 
    *>       DEBUG_FILE   yLOG_complex ("color"     , "%6s, %6d", p, x_num);                        <* 
    *>       if (x_num <  0       )        break;                                                   <* 
    *>       if (x_num >  16777215)        break;                                                   <* 
    *>       g_runs [g_nrun].back_hex = x_num;                                                      <* 
    *>       sprintf (x_result, "%06x", g_runs [g_nrun].back_hex);                                  <* 
    *>       DEBUG_FILE   yLOG_info    ("result"    , x_result);                                    <* 
    *>    }                                                                                         <* 
    *>    DEBUG_FILE   yLOG_value   ("back_hex"  , x_num);                                          <* 
    *>    strcpy (g_runs [g_nrun].back_name, p + 8);                                                <* 
    *>    if (x_num < -1)                  continue;                                                <* 
    *>    g_runs [g_nrun].back_hex  = x_num;                                                        <* 
    *>    /+---(get ref for scheme)----------+/                                                     <* 
    *>    p = strtok (NULL, "\x1F");                                                                <* 
    *>    if (p == NULL)                   continue;                                                <* 
    *>    ySTR_trim (p, ySTR_BOTH);                                                                 <* 
    *>    x_len = strlen (p);                                                                       <* 
    *>    if (x_len  < 2)                  continue;                                                <* 
    *>    if (strchr ("0123456789abcdef", p[0]) != 0 && strchr ("0123456789abcdef", p[1]) != 0) {   <* 
    *>       g_runs [g_nrun].theme_ref[0] = p[0];                                                   <* 
    *>       g_runs [g_nrun].theme_ref[1] = p[1];                                                   <* 
    *>       g_runs [g_nrun].theme_ref[2] = '£';                                                    <* 
    *>    }                                                                                         <* 
    *>    DEBUG_FILE   yLOG_info    ("theme_ref" , g_runs [g_nrun].theme_ref);                      <* 
    *>    if (p[4] != '-')  strcpy (g_runs [g_nrun].theme_name, p + 4);                             <* 
    *>    else              strcpy (g_runs [g_nrun].theme_name, "----------");                      <* 
    *>    /+---(prepare for next)------------+/                                                     <* 
    *>    ++g_nrun;                                                                                 <* 
    *> }                                                                                            <* 
    *> /+---(close file)---------------------+/                                                     <* 
    *> rc = fclose (f);                                                                             <* 
    *> --rce;  if (rc != 0) {                                                                       <* 
    *>    DEBUG_FILE   yLOG_exit    (__FUNCTION__);                                                 <* 
    *>    return rce;                                                                               <* 
    *> }                                                                                            <* 
    *> /+---(complete)-----------------------+/                                                     <* 
    *> DEBUG_FILE   yLOG_exit    (__FUNCTION__);                                                    <* 
    *> /+---(complete)-----------------------+/                                                     <* 
    *> return 0;                                                                                    <*/
}

char         /*--> save current theme to runtime ---------[ ------ [ ------ ]-*/
RUNTIME_report     (void)
{
   /*> /+---(locals)-----------+-----------+-+/                                                                                                <* 
    *> char        rce         = -10;           /+ return code for errors         +/                                                           <* 
    *> char        rc          =   0;           /+ generic return code            +/                                                           <* 
    *> char        recd        [LEN_RECD];                                                                                                     <* 
    *> int         x_len;                                                                                                                      <* 
    *> char       *p;                                                                                                                          <* 
    *> char       *q           = "\x1F";                                                                                                       <* 
    *> int         i           = 0;                                                                                                            <* 
    *> int         j           = 0;                                                                                                            <* 
    *> long        x_num       = 0;                                                                                                            <* 
    *> char        x_back      [LEN_RECD] = "";                                                                                                <* 
    *> char        x_theme     [LEN_RECD] = "";                                                                                                <* 
    *> /+---(header)-------------------------+/                                                                                                <* 
    *> printf ("\ntheia euryphaessa (wide-shinning) known terminal runtime inventory\n");                                                      <* 
    *> printf ("\n  --pid-------  -background-------------------  -font-theme-------------------\n");                                          <* 
    *> /+---(write g_runs)-----------------+/                                                                                                  <* 
    *> for (i = 0; i < g_nrun; ++i) {                                                                                                          <* 
    *>    if (g_runs [i].back_key == '-')   sprintf (x_back, "-  ------  ------");                                                             <* 
    *>    else                                sprintf (x_back, "%c  %06x  %s", g_runs[i].back_key, g_runs[i].back_hex, g_runs[i].back_name);   <* 
    *>    sprintf (x_theme, "%2s  %-25.25s", g_runs[i].theme_ref, g_runs[i].theme_name);                                                       <* 
    *>    printf ("  %-12d  %-30.30s  %-30.30s¦", g_runs[i].ppid, x_back, x_theme);                                                            <* 
    *> }                                                                                                                                       <* 
    *> /+---(complete)-----------------------+/                                                                                                <* 
    *> return 0;                                                                                                                               <*/
}



/*====================------------------------------------====================*/
/*===----                          reporting                           ----===*/
/*====================------------------------------------====================*/
void  o___REPORTS_________o () { return; }

char         /*--> show a wide display of the scheme -----[ ------ [ ------ ]-*/
REPORT_wide        (int  a_scheme)
{
   /*---(locals)-----------+-----------+-*/
   int         bcolor      = 0;             /* iterator -- color index        */
   int         fcolor      = 0;             /* iterator -- color index        */
   int         battr       = 0;             /* iterator -- color index        */
   int         fattr       = 0;             /* iterator -- color index        */
   int         bindex      = 0;
   int         findex      = 0;
   char        t           [80];
   char        bprefix     [20];
   char        fprefix     [20];
   /*---(overall title)------------------*/
   printf ("\n");
   printf ("heatherly terminal font color matrix (ansi 16 color, 12-bit)");
   snprintf (t, 60, "scheme [%s] %s", g_fores  [my.theme].f_abbr, g_fores  [my.theme].f_name);
   printf ("%160.160s\n", t);
   printf ("\n");
   /*---(column titles)------------------*/
   printf ("           ");
   for (bcolor = 0; bcolor < MAX_COLOR; ++bcolor) {
      bindex = corder [bcolor];
      if (bindex < 0)  continue;
      snprintf (t, 15, "%s-----------------------------", cname[bindex]);
      printf ("[-%2d)--%.9s]   ", bindex + 40, t);
   }
   printf ("  [--------color-hex--------]\n");
   /*---(column subtitles)---------------*/
   printf ("   fg ba   ");
   for (bcolor = 0; bcolor < 9; ++bcolor)  printf (" norm;0   bold;1    ");
   printf ("     norm;0         bold;1   \n");
   /*---(cycle colors)-------------------*/
   for (fcolor = 0; fcolor < MAX_COLOR; ++fcolor) {
      /*---(get index)-------------------*/
      findex = corder [fcolor];
      if (findex < 0)  continue;
      /*---(color group header)----------*/
      printf ("\n");
      snprintf (t, 15, "%s-----------------------------", cname[findex]);
      printf ("  %.7s\n", t);
      for (battr = 0; battr <= 5; battr += 5) {
         if (battr == 0)  sprintf (bprefix, "");
         else             sprintf (bprefix, "%d;", battr);
         printf ("   3%1d ;%1d   ", findex, battr);
         for (bcolor = 0; bcolor < MAX_COLOR; ++bcolor) {
            /*---(get index)-------------------*/
            bindex = corder [bcolor];
            if (bindex < 0)  continue;
            for (fattr = 0; fattr <= 1; ++fattr) {
               if (fattr == 0)  sprintf (fprefix, "");
               else             sprintf (fprefix, "%d;", fattr);
               printf ("\e[%s%s3%d;4%dm  test  \e[0m ", fprefix, bprefix, findex, bindex);
            }
            printf ("  ");
         }
         printf ("  ");
         if (battr == 0) {
            printf ("¥[5;3%d;4%dm   %06x   ¥[0m ", findex, findex, g_fores  [my.theme].f_hex [fcolor * 2 + 0    ]);
            printf ("  ");
            printf ("¥[1;3%d;4%dm   %06x   ¥[0m ", findex, findex, g_fores  [my.theme].f_hex [fcolor * 2 + 1    ]);
         } else {
            printf ("¥[1;3%d;4%dm   %06x   ¥[0m ", findex, findex, g_fores  [my.theme].f_hex [fcolor * 2 + 1    ]);
            printf ("  ");
            printf ("¥[5;3%d;4%dm   %06x   ¥[0m ", findex, findex, g_fores  [my.theme].f_hex [fcolor * 2 + 0    ]);
         }
         printf ("\n");
      }
   }
   printf ("\n");
   /*---(complete)-----------------------*/
   return 0;
}

char
REPORT_single_OLD   (char a_fg, char a_bg, char a_style)
{
   if (a_fg >= 0 || a_bg >= 0)  printf ("\e[0m");
   if      (a_fg >= 24) { printf ("\e[7;1;3%dm", a_fg - 24);  a_fg -= 16; }
   else if (a_fg >= 16) { printf ("\e[7;3%dm"  , a_fg - 16);  a_fg -= 16; }
   else if (a_fg >=  8) { printf ("\e[1;3%dm"  , a_fg - 8);               }
   else if (a_fg >=  0) { printf ("\e[3%dm"    , a_fg);                   }
   if      (a_bg >=  8) { printf ("\e[5;4%dm"  , a_bg - 8);               }
   else if (a_bg >=  0) { printf ("\e[4%dm"    , a_bg);                   }
   if (a_style == 1) {
      switch (g_fores [my.theme].f_style) {
      case 'a'  :  printf (" %-5.5s ", artistic [a_fg]);  break;
      case 'm'  :  printf (" %-5.5s ", mega_txt [a_fg]);  break;
      case 'f'  :  printf (" %-5.5s ", full_txt [a_fg]);  break;
      case 'c'  :  printf (" %-5.5s ", colo_txt [a_fg]);  break;
      default   :  printf (" %-5.5s ", comp_txt [a_fg]);  break;
      }
   } else               printf ("       ");
   if (a_fg >= 0 || a_bg >= 0)  printf ("\e[0m");
   return 0;
}

char
REPORT_single       (char a_fg, char a_bg, char a_style)
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
   sprintf (s, "%-6.6x", g_fores [my.theme].f_hex [a_fg]);
   sprintf (t, "%-6.6x", g_fores [my.theme].f_hex [a_bg]);
   switch (a_style) {
   case 1 :
      switch (g_fores [my.theme].f_style) {
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
REPORT_layout      (char a_fg, char a_style)
{
   char        b           =    7;
   char        s           = g_fores [my.theme].f_style;
   switch (s) {
   case 'a'  :  b = 7;  break;
   case 'm'  :  b = 7;  break;
   case 'f'  :  b = 7;  break;
   case 'c'  :  b = 6;  break;
   default   :  b = 7;  break;
   }
   /*> if (g_fores [my.theme].f_style != 'c') {                                           <*/
   printf (" ");
   REPORT_single (a_fg +  8, -1      , a_style);
   if (s == 'c') {
      REPORT_single (a_fg + 24, -1      , a_style);
      REPORT_single (a_fg + 16, -1      , a_style);
   }
   printf (" ");
   REPORT_single (a_fg    , a_fg + 8, a_style);
   REPORT_single (a_fg + 8, a_fg    , a_style);
   printf (" ");
   if (s != 'c') {
      REPORT_single (0       , a_fg + 8, a_style);
      REPORT_single (0       , a_fg    , a_style);
      printf (" ");
   }
   REPORT_single (a_fg    , 0    + 8, a_style);
   REPORT_single (a_fg + 8, 0       , a_style);
   printf (" ");
   REPORT_single (0       , a_fg + 8, a_style);
   REPORT_single (0    + 8, a_fg    , a_style);
   printf (" ");
   /*> REPORT_single (a_fg + 8,        2, a_style);                                   <*/
   /*> REPORT_single (a_fg + 8,        4, a_style);                                   <*/
   /*     0        1        2        3        4        5        6        7   */
   /*> "d.brn", "d.red", "d.grn", "d.yel", "d.blu", "d.pur", "d.ora", "d.cri",        <*/
   switch (a_fg) {
   case 0 :
      REPORT_single (a_fg    , 2 + 8   , a_style);
      REPORT_single (a_fg + 8, 2       , a_style);
      break;
   case 1 :
      REPORT_single (a_fg    , 4 + 8   , a_style);
      REPORT_single (a_fg + 8, 4       , a_style);
      break;
   case 6 : /* orange  */
      REPORT_single (a_fg    , 5 + 8   , a_style);
      REPORT_single (a_fg + 8, 5       , a_style);
      break;
   case 3 : /* yellow  */
      REPORT_single (a_fg    , 7 + 8   , a_style);
      REPORT_single (a_fg + 8, 7       , a_style);
      break;
   case 2 : /* green   */
      REPORT_single (a_fg    , 0 + 8   , a_style);
      REPORT_single (a_fg + 8, 0       , a_style);
      break;
   case 4 : /* blue    */
      REPORT_single (a_fg    , 1 + 8   , a_style);
      REPORT_single (a_fg + 8, 1       , a_style);
      break;
   case 5 : /* purple  */
      REPORT_single (a_fg    , 6 + 8   , a_style);
      REPORT_single (a_fg + 8, 6       , a_style);
      break;
   case 7 : /* crimson */
      REPORT_single (a_fg    , 3 + 8   , a_style);
      REPORT_single (a_fg + 8, 3       , a_style);
      break;
   default :
      REPORT_single (a_fg + 8,        5, a_style);
      REPORT_single (a_fg + 8,        7, a_style);
      break;
   }
   /*> } else {                                                                       <* 
    *>    REPORT_single (a_fg + 8, -1      , a_style);                                <* 
    *>    REPORT_single (a_fg    , a_fg + 8, a_style);                                <* 
    *>    REPORT_single (a_fg + 8, a_fg    , a_style);                                <* 
    *>    REPORT_single (0    + 8, a_fg    , a_style);                                <* 
    *>    REPORT_single (a_fg    , 0    + 8, a_style);                                <* 
    *>    REPORT_single (a_fg + 8, 0       , a_style);                                <* 
    *>    REPORT_single (a_fg    , 1    + 8, a_style);                                <* 
    *>    REPORT_single (a_fg + 8, 1       , a_style);                                <* 
    *>    REPORT_single (a_fg + 8, 6       , a_style);                                <* 
    *>    REPORT_single (a_fg + 8, 3       , a_style);                                <* 
    *>    REPORT_single (a_fg + 8, b       , a_style);                                <* 
    *>    REPORT_single (a_fg + 8, 4       , a_style);                                <* 
    *>    REPORT_single (a_fg + 8, 5       , a_style);                                <* 
    *>    REPORT_single (a_fg + 8, 7       , a_style);                                <* 
    *> }                                                                              <*/
   printf ("\n");
}


char         /*--> show a narrow display of the scheme ---[ ------ [ ------ ]-*/
REPORT_narrow      (int  a_scheme)
{
   /*---(locals)-----------+-----------+-*/
   int         bcolor      = 0;             /* iterator -- color index        */
   int         fcolor      = 0;             /* iterator -- color index        */
   int         battr       = 0;             /* iterator -- color index        */
   int         fattr       = 0;             /* iterator -- color index        */
   int         bindex      = 0;
   int         findex      = 0;
   char        t           [80];
   char        bprefix     [20];
   char        fprefix     [20];
   /*---(overall title)------------------*/
   printf ("\n");
   printf ("heatherly terminal font color matrix (ansi 16 color, 12-bit)");
   snprintf (t, 60, "scheme [%s] %s", g_fores  [my.theme].f_abbr, g_fores  [my.theme].f_name);
   printf ("%76.76s\n", t);
   printf ("\n");
   /*---(column titles)------------------*/
   printf ("           ");
   printf ("  [-------transparent-------]   ");
   printf ("  [-------same-color--------]   ");
   printf ("  [---------blacks----------]   ");
   printf ("  [---------whites----------]\n");
   /*---(column subtitles)---------------*/
   printf ("   fg ba   ");
   for (bcolor = 0; bcolor < 4; ++bcolor)  printf ("     norm;0         bold;1      ");
   printf ("\n");
   /*---(cycle colors)-------------------*/
   for (fcolor = 1; fcolor < MAX_COLOR; ++fcolor) {
      /*---(get index)-------------------*/
      findex = corder [fcolor];
      if (findex < 0)  continue;
      /*---(color group header)----------*/
      printf ("\n");
      snprintf (t, 15, "%s-----------------------------", cname[findex]);
      printf ("  %.7s\n", t);
      for (battr = 0; battr <= 5; battr += 5) {
         if (battr == 0)  sprintf (bprefix, "");
         else             sprintf (bprefix, "%d;", battr);
         printf ("   3%1d ;%1d   ", findex, battr);
         printf ("  ");
         if (battr == 0) {
            /*---(clear back)------------*/
            printf ("¥[5;3%d;4%dm   %06x   ¥[0m   ", findex, 9     , g_fores  [my.theme].f_hex [fcolor * 2 + 0    ]);
            printf ("¥[1;3%d;4%dm   %06x   ¥[0m   ", findex, 9     , g_fores  [my.theme].f_hex [fcolor * 2 + 1    ]);
            printf ("  ");
            /*---(same color swap)-------*/
            printf ("¥[5;3%d;4%dm   %06x   ¥[0m   ", findex, findex, g_fores  [my.theme].f_hex [fcolor * 2 + 0    ]);
            printf ("¥[1;3%d;4%dm   %06x   ¥[0m   ", findex, findex, g_fores  [my.theme].f_hex [fcolor * 2 + 1    ]);
            printf ("  ");
            /*---(black/white fore)------*/
            printf ("¥[5;3%d;4%dm   %06x   ¥[0m   ", 0     , findex, g_fores  [my.theme].f_hex [1      * 2 + 0    ]);
            printf ("¥[1;3%d;4%dm   %06x   ¥[0m   ", findex, 0     , g_fores  [my.theme].f_hex [fcolor * 2 + 1    ]);
            printf ("  ");
            /*---(black/white back)------*/
            printf ("¥[5;3%d;4%dm   %06x   ¥[0m   ", findex, 7     , g_fores  [my.theme].f_hex [fcolor * 2 + 0    ]);
            printf ("¥[1;3%d;4%dm   %06x   ¥[0m   ", 7     , findex, g_fores  [my.theme].f_hex [8      * 2 + 1    ]);
         } else {
            /*---(clear back)------------*/
            printf ("¥[1;3%d;4%dm   %06x   ¥[0m   ", findex, 9     , g_fores  [my.theme].f_hex [fcolor * 2 + 1    ]);
            printf ("¥[5;3%d;4%dm   %06x   ¥[0m   ", findex, 9     , g_fores  [my.theme].f_hex [fcolor * 2 + 0    ]);
            printf ("  ");
            /*---(same color swap)-------*/
            printf ("¥[1;3%d;4%dm   %06x   ¥[0m   ", findex, findex, g_fores  [my.theme].f_hex [fcolor * 2 + 1    ]);
            printf ("¥[5;3%d;4%dm   %06x   ¥[0m   ", findex, findex, g_fores  [my.theme].f_hex [fcolor * 2 + 0    ]);
            printf ("  ");
            /*---(black/white fore)------*/
            printf ("¥[1;3%d;4%dm   %06x   ¥[0m   ", findex, 0     , g_fores  [my.theme].f_hex [fcolor * 2 + 1    ]);
            printf ("¥[5;3%d;4%dm   %06x   ¥[0m   ", 0     , findex, g_fores  [my.theme].f_hex [1      * 2 + 0    ]);
            printf ("  ");
            /*---(black/white back)------*/
            printf ("¥[1;3%d;4%dm   %06x   ¥[0m   ", 7     , findex, g_fores  [my.theme].f_hex [8      * 2 + 1    ]);
            printf ("¥[5;3%d;4%dm   %06x   ¥[0m   ", findex, 7     , g_fores  [my.theme].f_hex [fcolor * 2 + 0    ]);
         }
         printf ("\n");
      }
   }
   printf ("\n");
   /*---(complete)-----------------------*/
   return 0;
}

char         /*--> show a tiny display of the scheme -----[ ------ [ ------ ]-*/
REPORT_tiny        (int  a_scheme)
{
   /*---(locals)-----------+-----------+-*/
   int         bcolor      = 0;             /* iterator -- color index        */
   int         fcolor      = 0;             /* iterator -- color index        */
   int         battr       = 0;             /* iterator -- color index        */
   int         fattr       = 0;             /* iterator -- color index        */
   int         bindex      = 0;
   int         findex      = 0;
   char        t           [80];
   char        bprefix     [20];
   char        fprefix     [20];
   /*---(overall title)------------------*/
   printf ("\n");
   printf ("theia, the heatherly terminal configuration system for ansi 16 x 12-bit color setups\n");
   snprintf (t, 60, "scheme [%s] %s", g_fores  [my.theme].f_abbr, g_fores  [my.theme].f_name);
   printf ("%s : %-47.47s%30.30s\n", P_VERNUM, P_VERTXT, t);
   /*---(cycle colors)-------------------*/
   for (fcolor = 1; fcolor < MAX_COLOR; ++fcolor) {
      /*---(get index)-------------------*/
      findex = corder [fcolor];
      if (findex < 0)  continue;
      /*---(color group header)----------*/
      printf ("\n");
      for (battr = 0; battr <= 5; battr += 5) {
         if (battr == 0) {
            /*---(clear back)------------*/
            printf ("¥[5;3%d;4%dm %06x ¥[0m"   , findex, 9     , g_fores  [my.theme].f_hex [fcolor * 2 + 0    ]);
            printf ("¥[1;3%d;4%dm %06x ¥[0m"   , findex, 9     , g_fores  [my.theme].f_hex [fcolor * 2 + 1    ]);
            printf (" ");
            /*---(same color swap)-------*/
            printf ("¥[5;3%d;4%dm  %06x  ¥[0m ", findex, findex, g_fores  [my.theme].f_hex [fcolor * 2 + 0    ]);
            printf ("¥[1;3%d;4%dm  %06x  ¥[0m ", findex, findex, g_fores  [my.theme].f_hex [fcolor * 2 + 1    ]);
            printf (" ");
            /*---(black/white fore)------*/
            printf ("¥[5;3%d;4%dm  %06x  ¥[0m ", 0     , findex, g_fores  [my.theme].f_hex [1      * 2 + 0    ]);
            printf ("¥[1;3%d;4%dm  %06x  ¥[0m ", findex, 0     , g_fores  [my.theme].f_hex [fcolor * 2 + 1    ]);
            printf (" ");
            /*---(black/white back)------*/
            printf ("¥[5;3%d;4%dm  %06x  ¥[0m ", findex, 7     , g_fores  [my.theme].f_hex [fcolor * 2 + 0    ]);
            printf ("¥[1;3%d;4%dm  %06x  ¥[0m ", 7     , findex, g_fores  [my.theme].f_hex [8      * 2 + 1    ]);
         } else {
            /*---(clear back)------------*/
            printf ("¥[1;3%d;4%dm %06x ¥[0m"   , findex, 9     , g_fores  [my.theme].f_hex [fcolor * 2 + 1    ]);
            printf ("¥[5;3%d;4%dm %06x ¥[0m"   , findex, 9     , g_fores  [my.theme].f_hex [fcolor * 2 + 0    ]);
            printf (" ");
            /*---(same color swap)-------*/
            printf ("¥[1;3%d;4%dm  %06x  ¥[0m ", findex, findex, g_fores  [my.theme].f_hex [fcolor * 2 + 1    ]);
            printf ("¥[5;3%d;4%dm  %06x  ¥[0m ", findex, findex, g_fores  [my.theme].f_hex [fcolor * 2 + 0    ]);
            printf (" ");
            /*---(black/white fore)------*/
            printf ("¥[1;3%d;4%dm  %06x  ¥[0m ", findex, 0     , g_fores  [my.theme].f_hex [fcolor * 2 + 1    ]);
            printf ("¥[5;3%d;4%dm  %06x  ¥[0m ", 0     , findex, g_fores  [my.theme].f_hex [1      * 2 + 0    ]);
            printf (" ");
            /*---(black/white back)------*/
            printf ("¥[1;3%d;4%dm  %06x  ¥[0m ", 7     , findex, g_fores  [my.theme].f_hex [8      * 2 + 1    ]);
            printf ("¥[5;3%d;4%dm  %06x  ¥[0m ", findex, 7     , g_fores  [my.theme].f_hex [fcolor * 2 + 0    ]);
         }
         printf ("\n");
      }
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
REPORT_line        (char a_line, char a_bg)
{
   int         s           = 0x2c2c2c;
   int         t           = 0xf8f8f8;
   int         u           = 0xf8f8f8;
   int         v           = 0xf8f8f8;
   int         i           =    0;
   u = g_fores [my.theme].f_hex [(a_bg + 1) * 2 + 0];
   v = g_fores [my.theme].f_hex [(a_bg + 1) * 2 + 1];
   if (a_line == 1) {
      printf ("\n");
      printf ("\e[3%dm%06x - %-8.8s (%c)\e[0m\n", a_bg, u, cname [a_bg], abbr [a_bg]);
   }
   printf ("  ");
   for (i = 0; i < 8; ++i) {
      s = g_fores  [my.theme].f_hex [(i + 1) * 2 + 0];
      t = g_fores  [my.theme].f_hex [(i + 1) * 2 + 1];
      switch (a_line) {
      case 1 : case 3 :
         printf ("\e[3%d;4%dm            \e[0m "  , i, a_bg);
         printf ("\e[1;3%d;4%dm            \e[0m ", i, a_bg);
         break;
      case 2 :
         printf ("\e[3%d;4%dm   %06x   \e[0m "  , i, a_bg, s);
         printf ("\e[1;3%d;4%dm   %06x   \e[0m ", i, a_bg, t);
         break;
      case 4 : case 6 :
         printf ("\e[5;3%d;4%dm            \e[0m "  , i, a_bg);
         printf ("\e[5;1;3%d;4%dm            \e[0m ", i, a_bg);
         break;
      case 5 :
         printf ("\e[5;3%d;4%dm   %06x   \e[0m "  , i, a_bg, s);
         printf ("\e[5;1;3%d;4%dm   %06x   \e[0m ", i, a_bg, t);
         break;
      }
      printf ("  ");
   }
   printf ("\n");
   if (a_line == 6) {
      printf ("\e[1;3%dm%06x - %-8.8s (%c)\e[0m\n", a_bg, v, cname2 [a_bg], toupper (abbr [a_bg]));
   }
   return 0;
}

char
REPORT_line2       (char a_line, char a_bg)
{
   int         s           = 0x2c2c2c;
   int         t           = 0xf8f8f8;
   int         u           = 0xf8f8f8;
   int         v           = 0xf8f8f8;
   int         i           =    0;
   int         f, b;
   u = g_fores [my.theme].f_hex [(a_bg + 1) * 2 + 0];
   v = g_fores [my.theme].f_hex [(a_bg + 1) * 2 + 1];
   if (a_line == 1) {
      printf ("\n");
      printf ("\e[3%dm%06x - %-8.8s (%c)\e[0m\n", a_bg, u, cname [a_bg], abbr [a_bg]);
   }
   printf ("  ");
   for (i = 0; i < 11; ++i) {
      if (i < 8) {
         s = g_fores  [my.theme].f_hex [(i + 1) * 2 + 0];
         t = g_fores  [my.theme].f_hex [(i + 1) * 2 + 1];
         f = i;
         b = a_bg;
      } else if (i == 8) {
         f = a_bg;
         b = a_bg;
      } else if (i == 9) {
         f = a_bg;
         b = 0;
      } else if (i == 10) {
         f = a_bg;
         b = 7;
      }
      switch (a_line) {
      case 1 : case 3 :
         printf ("\e[3%d;4%dm        \e[0m"  , f, b);
         printf ("\e[5;3%d;4%dm        \e[0m", f, b);
         break;
      case 2 :
         printf ("\e[3%d;4%dm %06x \e[0m"    , f, b, s);
         printf ("\e[5;1;3%d;4%dm %06x \e[0m", f, b, t);
         break;
      case 4 : case 6 :
         printf ("\e[5;3%d;4%dm        \e[0m", f, b);
         printf ("\e[1;3%d;4%dm        \e[0m", f, b);
         break;
      case 5 :
         printf ("\e[5;3%d;4%dm %06x \e[0m"  , f, b, s);
         printf ("\e[1;3%d;4%dm %06x \e[0m"  , f, b, t);
         break;
      }
      printf (" ");
      if (i == 7)  printf ("  ");
   }
   printf ("\n");
   if (a_line == 6) {
      printf ("\e[1;3%dm%06x - %-8.8s (%c)\e[0m\n", a_bg, v, cname2 [a_bg], toupper (abbr [a_bg]));
   }
   return 0;
}

char
REPORT_square      (char a_line, char a_fg, char a_bg)
{
   int         s           = 0x0000;
   int         t           = 0xffff;
   int         x_fg        = a_fg;
   int         x_bg        = a_bg;
   int         x_tm        = a_bg;
   if (a_line > 1) {
      x_tm = x_fg;
      x_fg = x_bg;
      x_bg = x_tm;
   }
   switch (a_line) {
   case 0 : case 3 :
      printf ("\e[3%d;4%dm  %04x  \e[0m "  , x_bg, x_bg, s);
      printf ("\e[1;3%d;4%dm  %04x  \e[0m ", x_bg, x_bg, t);
      printf ("\e[3%d;4%dm  %04x  \e[0m "  , x_fg, x_bg, s);
      printf ("\e[1;3%d;4%dm  %04x  \e[0m ", x_fg, x_bg, t);
      break;
   case 1 : case 2 :
      printf ("\e[5;1;3%d;4%dm  %04x  \e[0m "  , x_bg, x_bg, s);
      printf ("\e[5;3%d;4%dm  %04x  \e[0m ", x_bg, x_bg, t);
      printf ("\e[5;1;3%d;4%dm  %04x  \e[0m "  , x_fg, x_bg, s);
      printf ("\e[5;3%d;4%dm  %04x  \e[0m ", x_fg, x_bg, t);
      break;
   }
   printf ("  ");
   return 0;
}

char
REPORT_cell        (char a_top, char a_fg, char a_bg)
{
   char        a           [LEN_TERSE] = "";
   char        b           [LEN_TERSE] = "1;";
   int         s           = 0x0000;
   int         t           = 0xffff;
   /*> char        x_fg        = corder [a_fg];                                       <* 
    *> char        x_bg        = corder [a_bg];                                       <*/
   int         x_fg        = a_fg;
   int         x_bg        = a_bg;
   int         x_temp      = 0;
   if (a_top != 'y') {
      strcpy (a, "1;5;");
      strcpy (b, "5;");
      if (x_bg >= 0) {
         x_temp = x_fg;
         x_fg   = x_bg;
         x_bg   = x_temp;
      }
      x_temp = s;
      s      = t;
      t      = x_temp;
   }
   if (x_bg >= 0) {
      printf ("\e[%s3%d;4%dm  %04x  \e[0m ", a, x_bg, x_fg, s);
      printf ("\e[%s3%d;4%dm  %04x  \e[0m ", b, x_fg, x_bg, t);
   } else {
      printf ("\e[%s3%dm  %04x  \e[0m ", a, x_fg, s);
      printf ("\e[%s3%dm  %04x  \e[0m ", b, x_fg, t);
   }
   printf ("  ");
   return 0;
}

char         /*--> show a tiny display of the scheme -----[ ------ [ ------ ]-*/
REPORT_every       (int  a_scheme)
{
   /*---(locals)-----------+-----------+-*/
   int         bcolor      = 0;             /* iterator -- color index        */
   int         c           = 0;             /* iterator -- color index        */
   int         battr       = 0;             /* iterator -- color index        */
   int         fattr       = 0;             /* iterator -- color index        */
   int         bindex      = 0;
   int         findex      = 0;
   char        t           [80];
   char        bprefix     [20];
   char        fprefix     [20];
   /*---(overall title)------------------*/
   printf ("\n");
   snprintf (t, 60, "scheme [%s] %s", g_fores  [my.theme].f_abbr, g_fores  [my.theme].f_name);
   printf ("%s         %s\n", P_ONELINE, t);
   /*> printf ("--every   %s : %-47.47s%30.30s\n", P_VERNUM, P_VERTXT, t);            <*/
   /*---(cycle colors)-------------------*/
   /*> for (c = 0; c < 8; ++c) {                                                                <* 
    *>    printf ("\n");                                                                        <* 
    *>    /+> if (battr == 0)  sprintf (bprefix, "");                                     <*    <* 
    *>     *> else             sprintf (bprefix, "%d;", battr);                           <+/   <* 
    *>    snprintf (t, 15, "%s-----------------------------", cname[c]);                        <* 
    *>    printf ("%.9s ", t);                                                                  <* 
    *>    REPORT_cell ('y', c, -1);                                                             <* 
    *>    REPORT_cell ('y', c, c);                                                              <* 
    *>    REPORT_cell ('y', c, 0);                                                              <* 
    *>    REPORT_cell ('y', c, 1);                                                              <* 
    *>    REPORT_cell ('y', c, 2);                                                              <* 
    *>    REPORT_cell ('y', c, 3);                                                              <* 
    *>    REPORT_cell ('y', c, 4);                                                              <* 
    *>    REPORT_cell ('y', c, 5);                                                              <* 
    *>    REPORT_cell ('y', c, 6);                                                              <* 
    *>    REPORT_cell ('y', c, 7);                                                              <* 
    *>    printf ("\n");                                                                        <* 
    *>    printf ("   %c 4%1d   ", abbr [c], c);                                                <* 
    *>    REPORT_cell ('-', c, -1);                                                             <* 
    *>    REPORT_cell ('-', c, c);                                                              <* 
    *>    REPORT_cell ('-', c, 0);                                                              <* 
    *>    REPORT_cell ('-', c, 1);                                                              <* 
    *>    REPORT_cell ('-', c, 2);                                                              <* 
    *>    REPORT_cell ('-', c, 3);                                                              <* 
    *>    REPORT_cell ('-', c, 4);                                                              <* 
    *>    REPORT_cell ('-', c, 5);                                                              <* 
    *>    REPORT_cell ('-', c, 6);                                                              <* 
    *>    REPORT_cell ('-', c, 7);                                                              <* 
    *>    printf ("\n");                                                                        <* 
    *> }                                                                                        <*/
   for (c = 0; c < 8; ++c) {
      REPORT_line (1, c);
      REPORT_line (2, c);
      REPORT_line (3, c);
      REPORT_line (4, c);
      REPORT_line (5, c);
      REPORT_line (6, c);
   }
   /*> REPORT_square (0, 1, 2);                                                       <* 
    *> printf ("\n");                                                                 <* 
    *> REPORT_square (1, 1, 2);                                                       <* 
    *> printf ("\n");                                                                 <* 
    *> REPORT_square (2, 1, 2);                                                       <* 
    *> printf ("\n");                                                                 <* 
    *> REPORT_square (3, 1, 2);                                                       <*/
   /*---(complete)-----------------------*/
   return 0;
}

char         /*--> show a tiny display of the scheme -----[ ------ [ ------ ]-*/
REPORT_fullsome    (int  a_scheme)
{
   /*---(locals)-----------+-----------+-*/
   int         bcolor      = 0;             /* iterator -- color index        */
   int         c           = 0;             /* iterator -- color index        */
   int         battr       = 0;             /* iterator -- color index        */
   int         fattr       = 0;             /* iterator -- color index        */
   int         bindex      = 0;
   int         findex      = 0;
   char        t           [80];
   char        bprefix     [20];
   char        fprefix     [20];
   /*---(overall title)------------------*/
   printf ("\n");
   snprintf (t, 60, "scheme [%s] %s", g_fores  [my.theme].f_abbr, g_fores  [my.theme].f_name);
   printf ("%s         %s\n", P_ONELINE, t);
   /*> printf ("--every   %s : %-47.47s%30.30s\n", P_VERNUM, P_VERTXT, t);            <*/
   /*---(cycle colors)-------------------*/
   /*> for (c = 0; c < 8; ++c) {                                                                <* 
    *>    printf ("\n");                                                                        <* 
    *>    /+> if (battr == 0)  sprintf (bprefix, "");                                     <*    <* 
    *>     *> else             sprintf (bprefix, "%d;", battr);                           <+/   <* 
    *>    snprintf (t, 15, "%s-----------------------------", cname[c]);                        <* 
    *>    printf ("%.9s ", t);                                                                  <* 
    *>    REPORT_cell ('y', c, -1);                                                             <* 
    *>    REPORT_cell ('y', c, c);                                                              <* 
    *>    REPORT_cell ('y', c, 0);                                                              <* 
    *>    REPORT_cell ('y', c, 1);                                                              <* 
    *>    REPORT_cell ('y', c, 2);                                                              <* 
    *>    REPORT_cell ('y', c, 3);                                                              <* 
    *>    REPORT_cell ('y', c, 4);                                                              <* 
    *>    REPORT_cell ('y', c, 5);                                                              <* 
    *>    REPORT_cell ('y', c, 6);                                                              <* 
    *>    REPORT_cell ('y', c, 7);                                                              <* 
    *>    printf ("\n");                                                                        <* 
    *>    printf ("   %c 4%1d   ", abbr [c], c);                                                <* 
    *>    REPORT_cell ('-', c, -1);                                                             <* 
    *>    REPORT_cell ('-', c, c);                                                              <* 
    *>    REPORT_cell ('-', c, 0);                                                              <* 
    *>    REPORT_cell ('-', c, 1);                                                              <* 
    *>    REPORT_cell ('-', c, 2);                                                              <* 
    *>    REPORT_cell ('-', c, 3);                                                              <* 
    *>    REPORT_cell ('-', c, 4);                                                              <* 
    *>    REPORT_cell ('-', c, 5);                                                              <* 
    *>    REPORT_cell ('-', c, 6);                                                              <* 
    *>    REPORT_cell ('-', c, 7);                                                              <* 
    *>    printf ("\n");                                                                        <* 
    *> }                                                                                        <*/
   for (c = 0; c < 8; ++c) {
      REPORT_line2 (1, c);
      REPORT_line2 (2, c);
      REPORT_line2 (3, c);
      REPORT_line2 (4, c);
      REPORT_line2 (5, c);
      REPORT_line2 (6, c);
   }
   /*> REPORT_square (0, 1, 2);                                                       <* 
    *> printf ("\n");                                                                 <* 
    *> REPORT_square (1, 1, 2);                                                       <* 
    *> printf ("\n");                                                                 <* 
    *> REPORT_square (2, 1, 2);                                                       <* 
    *> printf ("\n");                                                                 <* 
    *> REPORT_square (3, 1, 2);                                                       <*/
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                            driver                            ----===*/
/*====================------------------------------------====================*/
void  o___DRIVER__________o () { return; }





/*===============================[[ end code ]]===============================*/
