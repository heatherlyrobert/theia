/*===============================[[ beg code ]]===============================*/

#include   "theia.h"

#define     MAX_COLOR     10
char        cname  [MAX_COLOR][20] = {
   "blk"  , "red"    , "grn"  , "yel" ,
   "blu"  , "mag"    , "cya"  , "whi" ,
   ""       , "default"
};
char        corder [MAX_COLOR] = {
   9, 0, 1, 2, 3, 4, 5, 6, 7, -1
};

char        abbr   [MAX_COLOR] = { 'k', 'r', 'g', 'y', 'b', 'm', 'c', 'w' };


char        s_report;

char        s_backno  = '-';
int         s_back    = -1;
int         s_custom  = -1;

char        s_refnum     [  5];;
int         s_theme   = -1;

char        verstring    [500];



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

char         /*--> read all schemes from source file -----[ ------ [ ------ ]-*/
SCHEMES_read       (void)
{
   /*---(locals)-----------+-----------+-*/
   FILE       *f           = NULL;          /* file handle for source file    */
   char        rce         = -10;           /* return code for errors         */
   char        rc          =   0;           /* generic return code            */
   char        recd        [MAX_STR];
   int         x_len;
   char       *p;
   char       *q           = "\x1F";
   int         x_num       = 0;
   int         i           = 0;
   int         j           = 0;
   int         x_place     = 0;
   int         x_mult      = 0;
   int         x_lines     = 0;
   char        x_result    [20];
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_enter   (__FUNCTION__);
   /*---(open file)----------------------*/
   f = fopen(FILE_SCHEMES, "r");
   --rce;  if (rc != 0) {
      DEBUG_FILE   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(read schemes)-------------------*/
   while (1) {
      /*---(get record)------------------*/
      fgets (recd, MAX_STR, f);
      if (feof(f))                     break;
      ++x_lines;
      DEBUG_FILE   yLOG_value   ("LINE"      , x_lines);
      x_len = strlen (recd);
      if (x_len <= 0)                  continue;
      recd [--x_len] = '\0';
      /*---(get record type)-------------*/
      p = strtok (recd, "\x1F");
      if (p == NULL)                   continue;
      ySTR_trim (p, ySTR_BOTH);
      x_len = strlen (p);
      DEBUG_FILE   yLOG_value   ("length"    , x_len);
      if (x_len > 10)                  continue;
      DEBUG_FILE   yLOG_info    ("rectype"   , p);
      /*---(filter non-scheme lines)-----*/
      if (x_len <= 0)                  continue;
      if (p[0] == '#')                 continue;
      if (p[0] == ' ')                 continue;
      if (p[0] == '\0')                continue;
      /*---(address themes)--------------*/
      if (strcmp (p, "theme") == 0) {
         /*---(read ref number)-------------*/
         p = strtok (NULL, q);
         if (p == NULL)                   continue;
         ySTR_trim (p, ySTR_BOTH);
         x_len = strlen (p);
         DEBUG_FILE   yLOG_value   ("len"       , x_len);
         if (x_len != 2)                  break;
         DEBUG_FILE   yLOG_info    ("refnum"    , p);
         strcpy (themes  [ntheme].refno, p);
         /*---(read name)-------------------*/
         p = strtok (NULL, q);
         if (p == NULL)                   continue;
         ySTR_trim (p, ySTR_BOTH);
         x_len = strlen (p);
         if (x_len <= 0)                  continue;
         DEBUG_FILE   yLOG_info    ("name"      , p);
         strcpy (themes  [ntheme].name, p);
         /*---(read colors)-----------------*/
         for (i = 0; i < 16; ++i) {
            DEBUG_FILE   yLOG_value   ("color"     , i);
            p = strtok (NULL, q);
            if (p == NULL)                break;
            ySTR_trim (p, ySTR_BOTH);
            DEBUG_FILE   yLOG_info    ("hex"       , p);
            x_len = strlen (p);
            DEBUG_FILE   yLOG_value   ("len"       , x_len);
            if (x_len != 6)               break;
            x_num  = 0;
            x_mult = 1;
            for (j = 5; j >= 0; --j) {
               if (p[j] >= '0' && p[j] <= '9')  x_place = p[j] - '0';
               if (p[j] >= 'a' && p[j] <= 'f')  x_place = p[j] - 'a' + 10;
               if (p[j] >= 'A' && p[j] <= 'F')  x_place = p[j] - 'A' + 10;
               x_num  += x_place * x_mult;
               DEBUG_FILE   yLOG_complex ("place"     , "%1d, %c, %2d, %8d, %8d", j, p[j], x_place, x_mult, x_num);
               x_mult *= 16;
            }
            DEBUG_FILE   yLOG_complex ("color"     , "%2d, %1d, %6s, %6d", i, x_len, p, x_num);
            if (x_num <  0       )        break;
            if (x_num >  16777215)        break;
            themes  [ntheme].color [i + 2] = x_num;
            sprintf (x_result, "%06x", themes  [ntheme].color [i + 2]);
            DEBUG_FILE   yLOG_info    ("result"    , x_result);
            /*---(fill in defaults)---------*/
            if (i ==  0)  themes  [ntheme].color [0] = x_num;
            if (i == 15)  themes  [ntheme].color [1] = x_num;
         }
         if (i != 16)                     continue;
         /*---(ready for next)--------------*/
         ++ntheme;
         /*---(done)------------------------*/
      }
      /*---(address backgrounds)---------*/
      else if (strcmp (p, "background") == 0) {
         /*---(read key)--------------------*/
         p = strtok (NULL, q);
         if (p == NULL)                break;
         ySTR_trim (p, ySTR_BOTH);
         DEBUG_FILE   yLOG_info    ("key"       , p);
         x_len = strlen (p);
         if (x_len != 1)                  continue;
         backs [nback].key   = p[0];
         /*---(read abbreviation)-----------*/
         p = strtok (NULL, q);
         if (p == NULL)                break;
         ySTR_trim (p, ySTR_BOTH);
         DEBUG_FILE   yLOG_info    ("abbrev"    , p);
         x_len = strlen (p);
         if (x_len != 6)                  continue;
         strcpy (backs [nback].abbr  , p);
         /*---(read group)------------------*/
         p = strtok (NULL, q);
         if (p == NULL)                break;
         ySTR_trim (p, ySTR_BOTH);
         DEBUG_FILE   yLOG_info    ("group"     , p);
         x_len = strlen (p);
         if (x_len <= 0)                  continue;
         strcpy (backs [nback].cgroup, p);
         /*---(read name)-------------------*/
         p = strtok (NULL, q);
         if (p == NULL)                break;
         ySTR_trim (p, ySTR_BOTH);
         DEBUG_FILE   yLOG_info    ("name"      , p);
         x_len = strlen (p);
         if (x_len <= 0)                  continue;
         strcpy (backs [nback].name  , p);
         /*---(read rgb name)---------------*/
         p = strtok (NULL, q);
         if (p == NULL)                break;
         ySTR_trim (p, ySTR_BOTH);
         DEBUG_FILE   yLOG_info    ("rgb"       , p);
         x_len = strlen (p);
         if (x_len <= 0)                  continue;
         strcpy (backs [nback].rgb   , p);
         /*---(read color)------------------*/
         p = strtok (NULL, q);
         if (p == NULL)                break;
         ySTR_trim (p, ySTR_BOTH);
         DEBUG_FILE   yLOG_info    ("hex"       , p);
         x_len = strlen (p);
         DEBUG_FILE   yLOG_value   ("len"       , x_len);
         if (x_len != 6)               break;
         x_num  = 0;
         x_mult = 1;
         for (j = 5; j >= 0; --j) {
            if (p[j] >= '0' && p[j] <= '9')  x_place = p[j] - '0';
            if (p[j] >= 'a' && p[j] <= 'f')  x_place = p[j] - 'a' + 10;
            if (p[j] >= 'A' && p[j] <= 'F')  x_place = p[j] - 'A' + 10;
            x_num  += x_place * x_mult;
            DEBUG_FILE   yLOG_complex ("place"     , "%1d, %c, %2d, %8d, %8d", j, p[j], x_place, x_mult, x_num);
            x_mult *= 16;
         }
         DEBUG_FILE   yLOG_complex ("color"     , "%2d, %1d, %6s, %6d", i, x_len, p, x_num);
         if (x_num <  0       )        break;
         if (x_num >  16777215)        break;
         backs   [nback].color     = x_num;
         sprintf (x_result, "%06x", backs [nback].color);
         DEBUG_FILE   yLOG_info    ("result"    , x_result);
         /*---(ready for next)--------------*/
         ++nback;
      }
   }
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
   char        recd        [MAX_STR];
   int         x_len;
   char       *p;
   char       *q           = "\x1F";
   int         x_pid       = 0;             /* current pid                    */
   int         x_ppid      = 0;             /* parent pid                     */
   char        x_prog      [100];           /* program name                   */
   char        x_str       [100];           /* temp string                    */
   /*---(header)-------------------------*/
   DEBUG_PROC   yLOG_enter   (__FUNCTION__);
   DEBUG_PROC   yLOG_value   ("a_pid"     , a_pid);
   DEBUG_PROC   yLOG_point   ("a_term"    , a_term);
   /*---(run up proc ladder)-------------*/
   x_ppid = x_pid = a_pid;
   while (x_pid != 1) {
      DEBUG_PROC   yLOG_value   ("processing", x_pid);
      /*---(open file)-------------------*/
      sprintf (x_str, "/proc/%d/status", x_pid);
      f = fopen (x_str, "r");
      DEBUG_PROC   yLOG_info    ("filename"  , x_str);
      DEBUG_PROC   yLOG_point   ("file"      , f);
      --rce;  if (f == NULL) {
         DEBUG_PROC   yLOG_note    ("proc state file did not open properly");
         DEBUG_PROC   yLOG_exit    (__FUNCTION__);
         return rce;
      }
      /*---(walk status lines)-----------*/
      x_ppid = x_pid;
      while (1) {
         /*---(get record)---------------*/
         fgets (recd, MAX_STR, f);
         if (feof(f))                     break;
         x_len = strlen (recd);
         if (x_len <= 0)                  continue;
         recd [--x_len] = '\0';
         DEBUG_PROC   yLOG_info    ("entry"     , recd);
         /*---(save name)----------------*/
         if (strncmp (recd, "Name:", 5) == 0) {
            strcpy (x_prog, recd + 6);
            DEBUG_PROC   yLOG_info    ("name"      , x_prog);
         }
         /*---(save pid)-----------------*/
         if (strncmp (recd, "PPid:",  5) == 0) {
            x_ppid = atoi (recd + 6);
            DEBUG_PROC   yLOG_value   ("ppid"      , x_ppid);
            break;
         }
      }  /*---(done while)---------------*/
      /*---(close file)---------------------*/
      rc = fclose (f);
      --rce;  if (rc != 0) {
         DEBUG_PROC   yLOG_note    ("proc state file did not close properly");
         DEBUG_PROC   yLOG_exit    (__FUNCTION__);
         return rce;
      }
      --rce;  if (x_ppid == x_pid) {
         DEBUG_PROC   yLOG_note    ("did not find a ppid for process");
         DEBUG_PROC   yLOG_exit    (__FUNCTION__);
         return rce;
      }
      if (strcmp (x_prog, "Eterm"  ) == 0) {
         DEBUG_PROC   yLOG_note    ("FOUND an eterm");
         break;
      }
      if (strcmp (x_prog, "hearth" ) == 0) {
         DEBUG_PROC   yLOG_note    ("FOUND an hearth");
         break;
      }
      x_pid = x_ppid;
   }
   /*---(test for failure)---------------*/
   --rce;  if (x_pid == 1) {
      DEBUG_PROC   yLOG_note    ("ended at kharon (pid 1), way too high");
      DEBUG_PROC   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(save terminal pid)--------------*/
   DEBUG_PROC   yLOG_value   ("final pid" , x_pid);
   if (a_term != NULL)  *a_term = x_pid;
   /*---(complete)-----------------------*/
   DEBUG_PROC   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         backgrounds                          ----===*/
/*====================------------------------------------====================*/
void  o___BACKS___________o () { return; }

char         /*--> set a back by key ---------------------[ ------ [ ------ ]-*/
BACK_find          (char a_key)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;
   /*---(find back)----------------------*/
   s_back   = 0;
   for (i = 0; i < nback; ++i) {
      if (backs  [i].key != a_key)  continue;
      s_back   = i;
      break;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char         /*--> set a back by key ---------------------[ ------ [ ------ ]-*/
BACK_set           (void)
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
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(defense: index)-----------------*/
   --rce;  if (s_back < 0)             return rce;
   --rce;  if (s_back >= nback)        return rce;
   /*---(set background)-----------------*/
   sprintf (x_str, "\e]6;2;tint;bg;0x%06x", backs [s_back].color);
   DEBUG_GRAPH  yLOG_complex ("back"      , "%2d, %c, %s, %s, %s", s_back, backs [s_back].key, backs [s_back].abbr, backs [s_back].cgroup, backs [s_back].name);
   DEBUG_GRAPH  yLOG_complex ("color"     , "%10d, %s", backs [s_back].color, x_str);
   printf ("\e]6;0;true");
   printf ("\e]6;2;tint;bg;0x%06x", backs [s_back].color);
   /*---(find eterm or hestia)-----------*/
   rc = TERM_find (getppid(), &x_ppid);
   --rce;  if (rc < 0)                 return rce;
   /*---(update in runtime list)---------*/
   x_now  = time(NULL);
   for (j = 0; j < nruntime; ++j) {
      if (x_ppid != runtimes [j].ppid)  continue;
      runtimes [j].when       = x_now;
      runtimes [j].back_key   = backs [s_back].key;
      strcpy (runtimes [j].back_name, backs [s_back].name);
      runtimes [j].back_hex   = backs [s_back].color;
      break;
   }
   if (j == nruntime) {
      runtimes [j].ppid       = x_ppid;
      runtimes [j].when       = x_now;
      runtimes [j].back_key   = backs [s_back].key;
      strcpy (runtimes [j].back_name, backs [s_back].name);
      runtimes [j].back_hex   = backs [s_back].color;
      strcpy (runtimes [j].theme_ref, s_refnum);
      strcpy (runtimes [j].theme_name, "unknown");
      ++nruntime;
   }
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}

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
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(defense: index)-----------------*/
   --rce;  if (s_custom < 0)           return rce;
   /*---(set background)-----------------*/
   sprintf (x_str, "\e]6;2;tint;bg;0x%06x", s_custom);
   DEBUG_GRAPH  yLOG_complex ("color"     , "%10d, %s", s_custom, x_str);
   printf ("\e]6;0;true");
   printf ("\e]6;2;tint;bg;0x%06x", s_custom);
   /*---(find eterm or hestia)-----------*/
   rc = TERM_find (getppid(), &x_ppid);
   --rce;  if (rc < 0)                 return rce;
   /*---(update in runtime list)---------*/
   x_now  = time(NULL);
   for (j = 0; j < nruntime; ++j) {
      if (x_ppid != runtimes [j].ppid)  continue;
      runtimes [j].when       = x_now;
      runtimes [j].back_key   = '>';
      strcpy (runtimes [j].back_name, "custom");
      runtimes [j].back_hex   = s_custom;
      break;
   }
   if (j == nruntime) {
      runtimes [j].ppid       = x_ppid;
      runtimes [j].when       = x_now;
      runtimes [j].back_key   = '>';
      strcpy (runtimes [j].back_name, "custom");
      runtimes [j].back_hex   = s_custom;
      strcpy (runtimes [j].theme_ref, s_refnum);
      strcpy (runtimes [j].theme_name, "unknown");
      ++nruntime;
   }
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> list the background color options -----[ ------ [ ------ ]-*/
BACK_report        (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;
   char        x_save      [50];
   char        x_group     [50];
   /*---(header)-------------------------*/
   printf ("\ntheia euryphaessa (wide-shinning) transparent background tint inventory\n");
   printf ("\nusage : theia <c>\n");
   printf ("   where <c> is the single letter listed in the 'k' column\n");
   printf ("\n--k  -abbr-   ---name-------------  -hex--\n");
   /*---(inventory)----------------------*/
   for (i = 0; i < nback; ++i) {
      if (i == 0 || (i > 0 && strcmp (backs[i-1].cgroup, backs[i].cgroup) != 0)) {
         printf ("\n%s\n", backs[i].cgroup);
      }
      printf ("  %c  %-6.6s   %-20.20s  %06x\n",
            backs [i].key   , backs [i].abbr,
            backs [i].name  , backs [i].color);
   }
   /*---(footer)-------------------------*/
   printf ("\n");
   /*---(complete)-----------------------*/
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
   s_theme  = 0;
   for (i = 0; i < ntheme; ++i) {
      if (strcmp (themes [i].refno, a_ref) != 0)  continue;
      s_theme  = i;
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
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(find reference)-----------------*/
   for (j = 0; j < 18; ++j) {
      /*> if (j ==  0) {                                                                              <* 
       *>    yLOG_complex ("back"      , "%2d, 49, %8d, %6x", j, themes [s_theme].color [j], themes [s_theme].color [j]);   <* 
       *>    printf ("\e]49;%06x", themes [s_theme].color [j]);                                                 <* 
       *> }                                                                                           <* 
       *> if (j ==  1) {                                                                              <* 
       *>    yLOG_complex ("fore"      , "%2d, 39, %8d, %6x", j, themes [s_theme].color [j], themes [s_theme].color [j]);   <* 
       *>    printf ("\e]39;%06x", themes [s_theme].color [j]);                                                 <* 
       *> }                                                                                           <*/
      if (j >=  2) {
         x = ((int) j / 2) - 1 + ((j % 2) *  8);
         y = ((int) j / 2) - 1 + ((j % 2) * 10) + 30;
         sprintf (x_str, "\e]P%1x%06x", x, themes [s_theme].color [j]);
         DEBUG_GRAPH  yLOG_complex ("color"     , "%2d, %2d, %8d, %6x, %s", j, y, themes [s_theme].color [j], themes [s_theme].color [j], x_str);
         printf ("\e]P%1x%06x", x, themes [s_theme].color [j]);
      }
   }
   /*---(find eterm or hestia)-----------*/
   rc = TERM_find (getppid(), &x_ppid);
   --rce;  if (rc < 0)                 return rce;
   /*---(update in runtime list)---------*/
   x_now  = time(NULL);
   for (j = 0; j < nruntime; ++j) {
      if (x_ppid != runtimes [j].ppid)  continue;
      runtimes [j].when      = x_now;
      strcpy (runtimes [j].theme_ref, s_refnum);
      strcpy (runtimes [j].theme_name, themes [s_theme].name);
      break;
   }
   if (j == nruntime) {
      runtimes [j].ppid      = x_ppid;
      runtimes [j].when      = x_now;
      runtimes [j].back_key  = '-';
      strcpy (runtimes [j].back_name , "------");
      runtimes [j].back_hex  = 0;
      strcpy (runtimes [j].theme_ref, s_refnum);
      strcpy (runtimes [j].theme_name, themes [s_theme].name);
      ++nruntime;
   }
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
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
   char        recd        [MAX_STR];
   int         x_len;
   char       *p;
   char       *q           = "\x1F";
   int         i           = 0;
   int         j           = 0;
   long        x_num       = 0;
   char        x_back      [MAX_STR] = "";
   char        x_theme     [MAX_STR] = "";
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
   /*---(write runtimes)-----------------*/
   for (i = 0; i < nruntime; ++i) {
      if (runtimes [i].back_key == '-')  sprintf (x_back, "-  ------  ------");
      else                               sprintf (x_back, "%c  %06x  %s", runtimes[i].back_key, runtimes[i].back_hex, runtimes[i].back_name);
      sprintf (x_theme, "%2s  %-25.25s", runtimes[i].theme_ref, runtimes[i].theme_name);
      fprintf (f, "%-12d %c %-12d %c %-30.30s %c %-30.30s %c %2d   %c %4d %4d   %c %4d %4d %c\n", runtimes[i].ppid, 31, runtimes[i].when, 31, x_back, 31, x_theme, 31, 1, 'c', 50, 10, 'q', 400, 800, 31);
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
   FILE       *f           = NULL;          /* file handle for source file    */
   char        rce         = -10;           /* return code for errors         */
   char        rc          =   0;           /* generic return code            */
   char        recd        [MAX_STR];
   int         x_len;
   char       *p;
   char       *q           = "\x1F";
   long        x_num       = 0;
   int         x_lines     = 0;
   int         j           = 0;
   int         x_place     = 0;
   int         x_mult      = 0;
   char        x_result    [20];
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_enter   (__FUNCTION__);
   nruntime = 0;
   /*---(open file)----------------------*/
   f = fopen (FILE_RUNTIME, "r");
   DEBUG_FILE   yLOG_info    ("filename"  , FILE_RUNTIME);
   DEBUG_FILE   yLOG_point   ("file"      , f);
   --rce;  if (f == NULL) {
      DEBUG_FILE   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(read terminal)------------------*/
   while (1) {
      /*---(get record)------------------*/
      fgets (recd, MAX_STR, f);
      if (feof(f))                     break;
      ++x_lines;
      DEBUG_FILE   yLOG_value   ("LINE"      , x_lines);
      x_len = strlen (recd);
      if (x_len <= 0)                  continue;
      recd [--x_len] = '\0';
      /*---(filter non-scheme lines)-----*/
      if (x_len <= 0)                  continue;
      if (recd[0] == '#')              continue;
      if (recd[0] == ' ')              continue;
      if (recd[0] == '\0')             continue;
      /*---(get ppid)--------------------*/
      p = strtok (recd, "\x1F");
      if (p == NULL)                   continue;
      ySTR_trim (p, ySTR_BOTH);
      x_num = atoi (p);
      DEBUG_FILE   yLOG_value   ("ppid"      , x_num);
      if (x_num <= 0)                  continue;
      runtimes [nruntime].ppid = x_num;
      /*---(get time)--------------------*/
      p = strtok (NULL, "\x1F");
      if (p == NULL)                   continue;
      ySTR_trim (p, ySTR_BOTH);
      x_num = atoi (p);
      DEBUG_FILE   yLOG_value   ("time"      , x_num);
      if (x_num <= 0)                  continue;
      runtimes [nruntime].when = x_num;
      /*---(get background)--------------*/
      p = strtok (NULL, "\x1F");
      if (p == NULL)                   continue;
      ySTR_trim (p, ySTR_BOTH);
      x_len = strlen (p);
      if (x_len  <  9)                 continue;
      DEBUG_FILE   yLOG_value   ("back_key"  , p[0]);
      runtimes [nruntime].back_key  = p[0];
      if      (p[0] == '-')  x_num = 0;
      else {
         /*---(read color)------------------*/
         p = p + 3;
         x_num  = 0;
         x_mult = 1;
         for (j = 5; j >= 0; --j) {
            if (p[j] >= '0' && p[j] <= '9')  x_place = p[j] - '0';
            if (p[j] >= 'a' && p[j] <= 'f')  x_place = p[j] - 'a' + 10;
            if (p[j] >= 'A' && p[j] <= 'F')  x_place = p[j] - 'A' + 10;
            x_num  += x_place * x_mult;
            x_mult *= 16;
         }
         DEBUG_FILE   yLOG_complex ("color"     , "%6s, %6d", p, x_num);
         if (x_num <  0       )        break;
         if (x_num >  16777215)        break;
         runtimes [nruntime].back_hex = x_num;
         sprintf (x_result, "%06x", runtimes [nruntime].back_hex);
         DEBUG_FILE   yLOG_info    ("result"    , x_result);
      }
      DEBUG_FILE   yLOG_value   ("back_hex"  , x_num);
      strcpy (runtimes [nruntime].back_name, p + 8);
      if (x_num < -1)                  continue;
      runtimes [nruntime].back_hex  = x_num;
      /*---(get ref for scheme)----------*/
      p = strtok (NULL, "\x1F");
      if (p == NULL)                   continue;
      ySTR_trim (p, ySTR_BOTH);
      x_len = strlen (p);
      if (x_len  < 2)                  continue;
      if (strchr ("0123456789abcdef", p[0]) != 0 && strchr ("0123456789abcdef", p[1]) != 0) {
         runtimes [nruntime].theme_ref[0] = p[0];
         runtimes [nruntime].theme_ref[1] = p[1];
         runtimes [nruntime].theme_ref[2] = '\0';
      }
      DEBUG_FILE   yLOG_info    ("theme_ref" , runtimes [nruntime].theme_ref);
      if (p[4] != '-')  strcpy (runtimes [nruntime].theme_name, p + 4);
      else              strcpy (runtimes [nruntime].theme_name, "----------");
      /*---(prepare for next)------------*/
      ++nruntime;
   }
   /*---(close file)---------------------*/
   rc = fclose (f);
   --rce;  if (rc != 0) {
      DEBUG_FILE   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_FILE   yLOG_exit    (__FUNCTION__);
   /*---(complete)-----------------------*/
   return 0;
}

char         /*--> save current theme to runtime ---------[ ------ [ ------ ]-*/
RUNTIME_report     (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   char        rc          =   0;           /* generic return code            */
   char        recd        [MAX_STR];
   int         x_len;
   char       *p;
   char       *q           = "\x1F";
   int         i           = 0;
   int         j           = 0;
   long        x_num       = 0;
   char        x_back      [MAX_STR] = "";
   char        x_theme     [MAX_STR] = "";
   /*---(header)-------------------------*/
   printf ("\ntheia euryphaessa (wide-shinning) known terminal runtime inventory\n");
   printf ("\n  --pid-------  -background-------------------  -font-theme-------------------\n");
   /*---(write runtimes)-----------------*/
   for (i = 0; i < nruntime; ++i) {
      if (runtimes [i].back_key == '-')   sprintf (x_back, "-  ------  ------");
      else                                sprintf (x_back, "%c  %06x  %s", runtimes[i].back_key, runtimes[i].back_hex, runtimes[i].back_name);
      sprintf (x_theme, "%2s  %-25.25s", runtimes[i].theme_ref, runtimes[i].theme_name);
      printf ("  %-12d  %-30.30s  %-30.30s\n", runtimes[i].ppid, x_back, x_theme);
   }
   /*---(complete)-----------------------*/
   return 0;
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
   snprintf (t, 60, "scheme [%s] %s", themes  [s_theme].refno, themes  [s_theme].name);
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
            printf ("\e[5;3%d;4%dm   %06x   \e[0m ", findex, findex, themes  [s_theme].color [fcolor * 2 + 0    ]);
            printf ("  ");
            printf ("\e[1;3%d;4%dm   %06x   \e[0m ", findex, findex, themes  [s_theme].color [fcolor * 2 + 1    ]);
         } else {
            printf ("\e[1;3%d;4%dm   %06x   \e[0m ", findex, findex, themes  [s_theme].color [fcolor * 2 + 1    ]);
            printf ("  ");
            printf ("\e[5;3%d;4%dm   %06x   \e[0m ", findex, findex, themes  [s_theme].color [fcolor * 2 + 0    ]);
         }
         printf ("\n");
      }
   }
   printf ("\n");
   /*---(complete)-----------------------*/
   return 0;
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
   snprintf (t, 60, "scheme [%s] %s", themes  [s_theme].refno, themes  [s_theme].name);
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
            printf ("\e[5;3%d;4%dm   %06x   \e[0m   ", findex, 9     , themes  [s_theme].color [fcolor * 2 + 0    ]);
            printf ("\e[1;3%d;4%dm   %06x   \e[0m   ", findex, 9     , themes  [s_theme].color [fcolor * 2 + 1    ]);
            printf ("  ");
            /*---(same color swap)-------*/
            printf ("\e[5;3%d;4%dm   %06x   \e[0m   ", findex, findex, themes  [s_theme].color [fcolor * 2 + 0    ]);
            printf ("\e[1;3%d;4%dm   %06x   \e[0m   ", findex, findex, themes  [s_theme].color [fcolor * 2 + 1    ]);
            printf ("  ");
            /*---(black/white fore)------*/
            printf ("\e[5;3%d;4%dm   %06x   \e[0m   ", 0     , findex, themes  [s_theme].color [1      * 2 + 0    ]);
            printf ("\e[1;3%d;4%dm   %06x   \e[0m   ", findex, 0     , themes  [s_theme].color [fcolor * 2 + 1    ]);
            printf ("  ");
            /*---(black/white back)------*/
            printf ("\e[5;3%d;4%dm   %06x   \e[0m   ", findex, 7     , themes  [s_theme].color [fcolor * 2 + 0    ]);
            printf ("\e[1;3%d;4%dm   %06x   \e[0m   ", 7     , findex, themes  [s_theme].color [8      * 2 + 1    ]);
         } else {
            /*---(clear back)------------*/
            printf ("\e[1;3%d;4%dm   %06x   \e[0m   ", findex, 9     , themes  [s_theme].color [fcolor * 2 + 1    ]);
            printf ("\e[5;3%d;4%dm   %06x   \e[0m   ", findex, 9     , themes  [s_theme].color [fcolor * 2 + 0    ]);
            printf ("  ");
            /*---(same color swap)-------*/
            printf ("\e[1;3%d;4%dm   %06x   \e[0m   ", findex, findex, themes  [s_theme].color [fcolor * 2 + 1    ]);
            printf ("\e[5;3%d;4%dm   %06x   \e[0m   ", findex, findex, themes  [s_theme].color [fcolor * 2 + 0    ]);
            printf ("  ");
            /*---(black/white fore)------*/
            printf ("\e[1;3%d;4%dm   %06x   \e[0m   ", findex, 0     , themes  [s_theme].color [fcolor * 2 + 1    ]);
            printf ("\e[5;3%d;4%dm   %06x   \e[0m   ", 0     , findex, themes  [s_theme].color [1      * 2 + 0    ]);
            printf ("  ");
            /*---(black/white back)------*/
            printf ("\e[1;3%d;4%dm   %06x   \e[0m   ", 7     , findex, themes  [s_theme].color [8      * 2 + 1    ]);
            printf ("\e[5;3%d;4%dm   %06x   \e[0m   ", findex, 7     , themes  [s_theme].color [fcolor * 2 + 0    ]);
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
   snprintf (t, 60, "scheme [%s] %s", themes  [s_theme].refno, themes  [s_theme].name);
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
            printf ("\e[5;3%d;4%dm %06x \e[0m"   , findex, 9     , themes  [s_theme].color [fcolor * 2 + 0    ]);
            printf ("\e[1;3%d;4%dm %06x \e[0m"   , findex, 9     , themes  [s_theme].color [fcolor * 2 + 1    ]);
            printf (" ");
            /*---(same color swap)-------*/
            printf ("\e[5;3%d;4%dm  %06x  \e[0m ", findex, findex, themes  [s_theme].color [fcolor * 2 + 0    ]);
            printf ("\e[1;3%d;4%dm  %06x  \e[0m ", findex, findex, themes  [s_theme].color [fcolor * 2 + 1    ]);
            printf (" ");
            /*---(black/white fore)------*/
            printf ("\e[5;3%d;4%dm  %06x  \e[0m ", 0     , findex, themes  [s_theme].color [1      * 2 + 0    ]);
            printf ("\e[1;3%d;4%dm  %06x  \e[0m ", findex, 0     , themes  [s_theme].color [fcolor * 2 + 1    ]);
            printf (" ");
            /*---(black/white back)------*/
            printf ("\e[5;3%d;4%dm  %06x  \e[0m ", findex, 7     , themes  [s_theme].color [fcolor * 2 + 0    ]);
            printf ("\e[1;3%d;4%dm  %06x  \e[0m ", 7     , findex, themes  [s_theme].color [8      * 2 + 1    ]);
         } else {
            /*---(clear back)------------*/
            printf ("\e[1;3%d;4%dm %06x \e[0m"   , findex, 9     , themes  [s_theme].color [fcolor * 2 + 1    ]);
            printf ("\e[5;3%d;4%dm %06x \e[0m"   , findex, 9     , themes  [s_theme].color [fcolor * 2 + 0    ]);
            printf (" ");
            /*---(same color swap)-------*/
            printf ("\e[1;3%d;4%dm  %06x  \e[0m ", findex, findex, themes  [s_theme].color [fcolor * 2 + 1    ]);
            printf ("\e[5;3%d;4%dm  %06x  \e[0m ", findex, findex, themes  [s_theme].color [fcolor * 2 + 0    ]);
            printf (" ");
            /*---(black/white fore)------*/
            printf ("\e[1;3%d;4%dm  %06x  \e[0m ", findex, 0     , themes  [s_theme].color [fcolor * 2 + 1    ]);
            printf ("\e[5;3%d;4%dm  %06x  \e[0m ", 0     , findex, themes  [s_theme].color [1      * 2 + 0    ]);
            printf (" ");
            /*---(black/white back)------*/
            printf ("\e[1;3%d;4%dm  %06x  \e[0m ", 7     , findex, themes  [s_theme].color [8      * 2 + 1    ]);
            printf ("\e[5;3%d;4%dm  %06x  \e[0m ", findex, 7     , themes  [s_theme].color [fcolor * 2 + 0    ]);
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
   u = themes [s_theme].color [(a_bg + 1) * 2 + 0];
   v = themes [s_theme].color [(a_bg + 1) * 2 + 1];
   if (a_line == 1) {
      printf ("\n");
      printf ("\e[3%dm%06x - %s (%c)\e[0m\n", a_bg, u, cname [a_bg], abbr [a_bg]);
   }
   printf ("  ");
   for (i = 0; i < 8; ++i) {
      s = themes  [s_theme].color [(i + 1) * 2 + 0];
      t = themes  [s_theme].color [(i + 1) * 2 + 1];
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
      printf ("\e[1;3%dm%06x - %s (%c)\e[0m\n", a_bg, v, cname [a_bg], toupper (abbr [a_bg]));
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
   snprintf (t, 60, "scheme [%s] %s", themes  [s_theme].refno, themes  [s_theme].name);
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



/*====================------------------------------------====================*/
/*===----                            program                           ----===*/
/*====================------------------------------------====================*/
void  o___PROGRAM_________o () { return; }

char*        /*--> return versioning information ---------[ ------ [ ------ ]-*/
PROG_version       (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built]", 15);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc  ]", 15);
#elif  __CBANG__  > 0
   strncpy (t, "[cbang    ]", 15);
#else
   strncpy (t, "[unknown  ]", 15);
#endif
   snprintf (verstring, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return verstring;
}

char         /*--> initialize variables ------------------[ ------ [ ------ ]-*/
PROG_init          (void)
{
   /*---(locals)-------------------------*/
   int         i           = 0;             /* iterator -- structure entry    */
   int         j           = 0;             /* iterator -- color entry        */
   /*---(debugging)----------------------*/
   debug.tops     = '-';
   debug.args     = '-';
   debug.prep     = '-';
   debug.evnt     = '-';
   debug.file     = '-';
   debug.inpt     = '-';
   debug.data     = '-';
   debug.proc     = '-';
   debug.graf     = '-';
   debug.outp     = '-';
   debug.apis     = '-';
   debug.scrp     = '-';
   debug.summ     = '-';
   /*---(runtime)------------------------*/
   nruntime = 0;
   for (i = 0; i < MAX_RUNTIME; ++i) {
      runtimes [i].ppid       = -1;
      runtimes [i].when       = -1;
      runtimes [i].back_key   = '-';
      runtimes [i].back_hex   = 0;
      strcpy (runtimes [i].theme_ref , "00");
      strcpy (runtimes [i].theme_name, "unknown");
   }
   /*---(runtime)------------------------*/
   ntheme  = 0;
   for (i = 0; i < MAX_SCHEME ; ++i) {
      strcpy (themes   [i].refno, "00");
      strcpy (themes   [i].name , "--");
      for (j = 0; j < MAX_ENTRIES ; ++j) {
         themes   [i].color [j]   = -1;
      }
   }
   /*---(initialize)---------------------*/
   s_theme = 0;
   s_back  = 0;
   /*---(complete)-----------------------*/
   return 0;
}

char         /*--> process the command line urgents ------[ ------ [ ------ ]-*/
PROG_urgs          (int argc, char *argv[])
{
   /*---(locals)-------------------------*/
   char       *a           = NULL;          /* current argument               */
   int         i           = 0;             /* loop iterator -- arguments     */
   int         len         = 0;             /* argument length                */
   int         x_total     = 0;             /* total args looked at           */
   int         x_urgs      = 0;             /* num args identified as urgs    */
   /*---(logger in silent)---------------*/
   my.logger    = yLOGS_begin (argv[0], YLOG_SYS, YLOG_QUIET);
   /*---(process)------------------------*/
   for (i = 1; i < argc; ++i) {
      /*---(get next)--------------------*/
      a = argv[i];
      ++x_total;
      if      (a[0] != '@')                     continue;
      len = strlen (a);
      DEBUG_ARGS   yLOG_info  ("urgent", a);
      ++x_urgs;
      /*---(handle urgent)---------------*/
      if      (strcmp(a, "@t"        ) == 0)    debug.tops                = 'y';
      else if (strcmp(a, "@@tops"    ) == 0)    debug.tops                = 'y';
      else if (strcmp(a, "@c"        ) == 0)    debug.tops  = debug.args  = 'y';
      else if (strcmp(a, "@@args"    ) == 0)    debug.tops  = debug.args  = 'y';
      else if (strcmp(a, "@x"        ) == 0)    debug.tops  = debug.prep  = 'y';
      else if (strcmp(a, "@@prep"    ) == 0)    debug.tops  = debug.prep  = 'y';
      else if (strcmp(a, "@f"        ) == 0)    debug.tops  = debug.file  = 'y';
      else if (strcmp(a, "@@file"    ) == 0)    debug.tops  = debug.file  = 'y';
      else if (strcmp(a, "@g"        ) == 0)    debug.tops  = debug.graf  = 'y';
      else if (strcmp(a, "@@graf"    ) == 0)    debug.tops  = debug.graf  = 'y';
      else if (strcmp(a, "@o"        ) == 0)    debug.tops  = debug.outp  = 'y';
      else if (strcmp(a, "@@outp"    ) == 0)    debug.tops  = debug.outp  = 'y';
      else if (strcmp(a, "@p"        ) == 0)    debug.tops  = debug.proc  = 'y';
      else if (strcmp(a, "@@proc"    ) == 0)    debug.tops  = debug.proc  = 'y';
      /*---(logging)---------------------*/
      else if (strncmp (a, "@@log"    ,10) == 0) {
         debug.tops = 'y';
         yLOGS_end   ();
         my.logger = yLOGS_begin (argv[0], YLOG_SYS, YLOG_NOISE);
         if (my.logger < 1) {
            printf ("%s : can not start logger in noise mode, FATAL\n", argv[0]);
            exit(1);
         }
         yLOG_info  ("purpose",  "gorgeous, flexible terminal color configurator");
         yLOG_info  ("theia"  ,  PROG_version ());
         yLOG_info  ("yLOG"   ,  yLOGS_version ());
         DEBUG_TOPS   yLOG_enter (__FUNCTION__);
         DEBUG_ARGS   yLOG_info  ("urgent", a);
      }
      /*---(done)------------------------*/
   }
   /*---(summarize)----------------------*/
   DEBUG_ARGS   yLOG_value  ("entries"   , x_total);
   DEBUG_ARGS   yLOG_value  ("urgents"   , x_urgs);
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit  (__FUNCTION__);
   return 0;
}

char         /*--> process the command line arguments ----[ ------ [ ------ ]-*/
PROG_args          (int argc, char *argv[])
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
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   s_report = '-';
   strcpy (s_refnum, "00");
   /*---(process)------------------------*/
   for (i = 1; i < argc; ++i) {
      /*---(get next)--------------------*/
      a = argv[i];
      ++x_total;
      if      (a[0] == '@')                     continue;
      len = strlen(a);
      DEBUG_ARGS   yLOG_info  ("argument"  , a);
      ++x_args;
      /*---(reporting)-------------------*/
      if      (strcmp (a, "-w"        ) == 0)    s_report = 'w';
      else if (strcmp (a, "--wide"    ) == 0)    s_report = 'w';
      else if (strcmp (a, "-e"        ) == 0)    s_report = 'e';
      else if (strcmp (a, "--every"   ) == 0)    s_report = 'e';
      else if (strcmp (a, "-n"        ) == 0)    s_report = 'n';
      else if (strcmp (a, "--narrow"  ) == 0)    s_report = 'n';
      else if (strcmp (a, "-t"        ) == 0)    s_report = 't';
      else if (strcmp (a, "--tiny"    ) == 0)    s_report = 't';
      else if (strcmp (a, "-b"        ) == 0)    s_report = 'b';
      else if (strcmp (a, "--backs"   ) == 0)    s_report = 'b';
      else if (strcmp (a, "-r"        ) == 0)    s_report = 'r';
      else if (strcmp (a, "--runtime" ) == 0)    s_report = 'r';
      /*---(font number)-----------------*/
      else if (len == 1 && a[0] >= 'a' && a[0] <= 'z') s_backno = a[0];
      else if (len == 2 && strchr ("0123456789abcdef", a[0]) != 0 &&
            strchr ("0123456789abcdef", a[1]) != 0)
         strcpy (s_refnum, a);
      else if (len == 6 && a[0] != '-') {
         for (j = 0; j < 6; ++j) {
            if (strchr ("0123456789abcdef", a[j]) != 0)  continue;
            break;
         }
         if (j == 6) {
            x_num  = 0;
            x_mult = 1;
            for (j = 5; j >= 0; --j) {
               if (a[j] >= '0' && a[j] <= '9')  x_place = a[j] - '0';
               if (a[j] >= 'a' && a[j] <= 'f')  x_place = a[j] - 'a' + 10;
               if (a[j] >= 'A' && a[j] <= 'F')  x_place = a[j] - 'A' + 10;
               x_num  += x_place * x_mult;
               x_mult *= 16;
            }
            if (x_num >=  0  && x_num <=  16777215) {
               s_custom = x_num;
            }
         }
      }
      /*---(unknown)---------------------*/
      else    printf("requested action not understood or incomplete\n");
   }
   /*---(summarize)----------------------*/
   DEBUG_ARGS   yLOG_value  ("entries"   , x_total);
   DEBUG_ARGS   yLOG_value  ("arguments" , x_args);
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> final initialization steps ------------[ ------ [ ------ ]-*/
PROG_begin         (void)
{
   /*---(begin)--------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                            driver                            ----===*/
/*====================------------------------------------====================*/
void  o___DRIVER__________o () { return; }

int
main               (int argc, char *argv[])
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
   /*---(preprare)-----------------------*/
   if (rc == 0)  rc = PROG_init    ();
   if (rc == 0)  rc = PROG_urgs    (argc, argv);
   if (rc == 0)  rc = PROG_args    (argc, argv);
   if (rc == 0)  rc = PROG_begin   ();
   if (rc != 0)  exit (-1);
   /*---(begin)--------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(find eterm or hestia)-----------*/
   RUNTIME_read  ();
   rc = TERM_find (getppid(), &x_ppid);
   --rce;  if (rc < 0)                 return rce;
   for (i = 0; i < nruntime; ++i) {
      if (x_ppid != runtimes [i].ppid)  continue;
      x_back =  runtimes[i].back_key;
      strcpy (x_theme, runtimes [i].theme_ref);
      break;
   }
   /*---(get schemes)--------------------*/
   SCHEMES_read ();
   if (strcmp ("00", s_refnum) != 0)   THEME_find   (s_refnum);
   if (s_backno != '-')                BACK_find    (s_backno);
   /*---(set back)-----------------------*/
   if (s_back   > 0)  {
      BACK_set      ();
      RUNTIME_write ();
   }
   if (s_custom >= 0)  {
      BACK_custom   ();
      RUNTIME_write ();
   }
   /*---(set theme)----------------------*/
   if (s_theme  > 0)  {
      THEME_set     ();
      RUNTIME_write ();
   }
   /*---(display)------------------------*/
   if (strcmp ("00", s_refnum) == 0)   THEME_find   (x_theme);
   if (s_backno == '-')                BACK_find    (x_back);
   if      (s_report == 'w')  REPORT_wide    (s_theme );
   else if (s_report == 'e')  REPORT_every   (s_theme );
   else if (s_report == 'n')  REPORT_narrow  (s_theme );
   else if (s_report == 't')  REPORT_tiny    (s_theme );
   else if (s_report == 'b')  BACK_report    ();
   else if (s_report == 'r')  RUNTIME_report ();
   /*---(complete)-----------------------*/
   yLOG_exit    (__FUNCTION__);
   yLOGS_end     ();
   return 0;
}





/*===============================[[ end code ]]===============================*/
