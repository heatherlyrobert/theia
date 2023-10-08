#include   "theia.h"



tRUN   g_runs      [MAX_RUN];
int    g_nrun      =    0;
int    g_crun      =    0;



/*====================------------------------------------====================*/
/*===----                      program level                           ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char
RUN_purge               (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_CONF   yLOG_senter  (__FUNCTION__);
   /*---(clear table)--------------------*/
   for (i = 0; i < MAX_RUN; ++i)  {
      /*---(eterm)----------*/
      g_runs [i].eterm     =  0;
      ystrlcpy (g_runs [i].back , "�", LEN_TERSE);
      ystrlcpy (g_runs [i].fore , "�", LEN_TERSE);
      /*---(window)---------*/
      ystrlcpy (g_runs [i].hex  , "�", LEN_LABEL);
      g_runs [i].ref       =  0;
      g_runs [i].stack     = -1;
      g_runs [i].desk      =  0;
      ystrlcpy (g_runs [i].title, "�", LEN_HUND);
      g_runs [i].type      = '�';
      ystrlcpy (g_runs [i].shortcut , "�", LEN_LABEL);
      /*---(position)-------*/
      g_runs [i].left      =  0;
      g_runs [i].topp      =  0;
      g_runs [i].wide      =  0;
      g_runs [i].tall      =  0;
      g_runs [i].size      = '�';
      g_runs [i].scrn      = '�';
      g_runs [i].locn      = '�';
      /*---(running)--------*/
      g_runs [i].use       =  0;
      ystrlcpy (g_runs [i].pubname, "�", LEN_LABEL);
      ystrlcpy (g_runs [i].cmdline, "�", LEN_RECD);
      g_runs [i].order     =  0;
      /*---(done)-----------*/
   }
   g_nrun  = 0;
   /*---(header)-------------------------*/
   DEBUG_CONF   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        data searching                        ----===*/
/*====================------------------------------------====================*/
static void      o___SEARCH__________________o (void) {;}

char
RUN_by_eterm            (short a_eterm)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(find back)----------------------*/
   --rce;  if (a_eterm == 0)  return rce;
   g_crun    = 0;
   for (i = 0; i < g_nrun; ++i) {
      if (g_runs  [i].eterm != a_eterm)  continue;
      g_crun   = i;
      return i;
   }
   /*---(complete)-----------------------*/
   return --rce;
}

char
RUN_by_ref              (long a_ref)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(find back)----------------------*/
   --rce;  if (a_ref   == 0)  return rce;
   g_crun    = 0;
   for (i = 0; i < g_nrun; ++i) {
      if (g_runs  [i].ref   != a_ref)  continue;
      g_crun   = i;
      return i;
   }
   /*---(complete)-----------------------*/
   return --rce;
}

char
RUN_by_shortcut         (cchar a_shortcut [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(find back)----------------------*/
   --rce;  if (a_shortcut == NULL)  return rce;
   g_crun    = 0;
   for (i = 0; i < g_nrun; ++i) {
      if (strcmp (g_runs  [i].shortcut, a_shortcut) != 0)  continue;
      g_crun   = i;
      return i;
   }
   /*---(complete)-----------------------*/
   return --rce;
}



/*====================------------------------------------====================*/
/*===----                      data existance                          ----===*/
/*====================------------------------------------====================*/
static void      o___EXISTANCE_______________o (void) {;}

char
RUN__create             (cchar a_match, cchar a_recd [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_recd      [LEN_RECD]  = "";
   char        x_field     [LEN_LABEL] = "";
   char       *p           = NULL;
   char       *q           = "�";
   int         l           =    0;
   int         c           =    0;
   int         n           =    0;
   double      v           =  0.0;
   int         x_eterm     =    0;
   char        x_back      [LEN_TERSE] = "";
   char        x_fore      [LEN_TERSE] = "";
   char        x_hex       [LEN_LABEL] = "";
   long        x_ref       =    0;
   char        x_stack     =   -1;
   char        x_exist     =    0;
   /*---(header)-------------------------*/
   DEBUG_CONF   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_CONF   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_CONF   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   DEBUG_CONF   yLOG_info    ("a_recd"    , a_recd);
   /*---(prepare)---------------------*/
   ystrlcpy (x_recd, a_recd, LEN_RECD);
   p = strtok (x_recd, q);
   DEBUG_CONF   yLOG_point   ("p"         , p);
   n = g_nrun;
   /*---(parse record)----------------*/
   --rce;  while (p != NULL) {
      ystrlcpy  (x_field, p, LEN_LABEL);
      ystrltrim (x_field, ySTR_BOTH, LEN_LABEL);
      l = strlen (x_field);
      DEBUG_CONF   yLOG_complex ("parse"     , "%d, %2d�%s�", c, l, x_field);
      switch (c) {
      case  0 :  /* eterm rpid           */
         if (l < 3)  { rc = --rce; break; }
         x_eterm = atoi (p);
         DEBUG_CONF   yLOG_value   ("x_eterm"   , x_eterm);
         if (x_eterm == 0)  { rc = --rce;  break; }
         rc = RUN_by_eterm (x_eterm);
         DEBUG_CONF   yLOG_value   ("by_eterm"  , rc);
         if (rc < 0 && a_match == 'y') {
            DEBUG_CONF   yLOG_note    ("does not match existing eterm, discard");
            rc = --rce;
            break;
         }
         if (rc >= 0) n = rc;
         rc = 0;
         break;
      case  1 :  /* background           */
         if (l != 6)  {
            if (strcmp (x_field, "�") == 0) {
               DEBUG_CONF   yLOG_note    ("default value");
            } else { rc = --rce; break; }
         }
         ystrlcpy  (x_back, x_field, LEN_TERSE);
         DEBUG_CONF   yLOG_info    ("x_back"    , x_back);
         break;
      case  2 :  /* foreground           */
         if (l != 2)  {
            if (strcmp (x_field, "�") == 0) {
               DEBUG_CONF   yLOG_note    ("default value");
            } else { rc = --rce; break; }
         }
         ystrlcpy  (x_fore, x_field, LEN_TERSE);
         DEBUG_CONF   yLOG_info    ("x_fore"    , x_fore);
         break;
      case  3 :  /* window reference     */
         if (l == 0 || strcmp (x_field, "�") == 0) {
            DEBUG_CONF   yLOG_note    ("default value");
            break;
         } else if (x_field [0] == '�') {
            DEBUG_CONF   yLOG_note    ("hex value");
            ystrlcpy  (x_hex , x_field, LEN_LABEL);
            ystrldchg (x_hex , '0', '�', LEN_LABEL);
            if (x_hex [3] == '�')  x_hex [3] = '0';
            ystrldchg (x_field, '�', '0', LEN_LABEL);
            ystrl2hex (x_field, &v, LEN_LABEL);
            x_ref = v;
         } else {
            DEBUG_CONF   yLOG_note    ("long value");
            x_ref = atoi (x_field);
         }
         /*> if (RUN_by_ref (g_runs [n].ref) >= 0)  {                                 <* 
          *>    DEBUG_CONF   yLOG_note    ("reference already exists");               <* 
          *>    rc = --rce;                                                           <* 
          *>    break;                                                                <* 
          *> }                                                                        <*/
         DEBUG_CONF   yLOG_value   ("x_ref"     , x_ref);
         break;
      case  4 :  /* stacking order       */
         if (l == 0 || strcmp (x_field, "�") == 0) {
            DEBUG_CONF   yLOG_note    ("default value");
            break;
         }
         x_stack = atoi (x_field);
         DEBUG_CONF   yLOG_value   ("x_stack"   , x_stack);
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
   --rce;  if (c < 2 || rc < 0) {
      DEBUG_CONF   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(save out)--------------------*/
   x_exist = RUN_by_ref (x_ref);
   if (x_exist < 0) {
      g_runs [n].eterm = x_eterm;
      DEBUG_CONF   yLOG_value   (".eterm"    , g_runs [n].eterm);
      ystrlcpy  (g_runs [n].back, x_back, LEN_TERSE);
      DEBUG_CONF   yLOG_info    (".back"     , g_runs [n].back);
      ystrlcpy  (g_runs [n].fore, x_fore, LEN_TERSE);
      DEBUG_CONF   yLOG_info    (".fore"     , g_runs [n].fore);
      ystrlcpy  (g_runs [n].hex , x_hex , LEN_LABEL);
      DEBUG_CONF   yLOG_info    (".hex"      , g_runs [n].fore);
      g_runs [n].ref = x_ref;
      DEBUG_CONF   yLOG_value   (".ref"      , g_runs [n].ref);
      g_runs [n].stack = x_stack;
      DEBUG_CONF   yLOG_value   (".stack"    , g_runs [n].stack);
   }
   /*---(advance)---------------------*/
   if (n == g_nrun)  ++g_nrun;
   /*---(complete)-----------------------*/
   DEBUG_CONF   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      export/import                           ----===*/
/*====================------------------------------------====================*/
static void      o___EXIM____________________o (void) {;}

char
RUN__add_eterm          (short a_rpid, cchar a_pubname [LEN_LABEL], cchar a_cmdline [LEN_RECD], cchar a_state, short a_ppid)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        t           [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_CONF   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_CONF   yLOG_point   ("a_pubname" , a_pubname);
   --rce;  if (a_pubname == NULL) {
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF   yLOG_info    ("a_pubname" , a_pubname);
   /*---(filter)-------------------------*/
   if (strcmp (a_pubname, "Eterm") != 0) {
      DEBUG_CONF   yLOG_note    ("not an eterm");
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(add entry)----------------------*/
   sprintf (t, "%-6d � �      � �  �", a_rpid);
   rc = RUN__create ('-', t);
   DEBUG_CONF   yLOG_value   ("create"    , rc);
   --rce;  if (rc <  0) {
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_CONF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
RUN__read               (char a_unit, cchar a_name [LEN_PATH])
{
   /*---(locals)-----------+-----------+-*/
   FILE       *f           = NULL;          /* file handle for source file    */
   char        rce         = -10;           /* return code for errors         */
   char        rc          =   0;           /* generic return code            */
   char        x_recd      [LEN_RECD];
   int         x_len;
   int         x_lines     = 0;
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_enter   (__FUNCTION__);
   /*---(purge current)------------------*/
   rc = RUN_purge ();
   DEBUG_FILE   yLOG_value   ("purge"     , rc);
   /*---(add all eterms)-----------------*/
   if (a_unit != 'y') {
      rc = yEXEC_data_filter (0, "Eterm", 0, RUN__add_eterm);
      DEBUG_FILE   yLOG_value   ("filter"    , rc);
      --rce;  if (rc < 0)  {
         DEBUG_FILE   yLOG_exit    (__FUNCTION__);
         return rce;
      }
   }
   /*---(defense)------------------------*/
   DEBUG_FILE   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_FILE   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   DEBUG_FILE   yLOG_info    ("a_name"    , a_name);
   /*---(open file)----------------------*/
   f = fopen (a_name, "rt");
   DEBUG_FILE   yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_FILE   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(read terminal)------------------*/
   while (1) {
      /*---(get record)------------------*/
      fgets (x_recd, LEN_RECD, f);
      if (feof(f))                     break;
      ++x_lines;
      DEBUG_FILE   yLOG_value   ("LINE"      , x_lines);
      x_len = strlen (x_recd);
      if (x_len <= 0)                  continue;
      x_recd [--x_len] = '\0';
      /*---(filter non-scheme lines)-----*/
      if (x_len <= 0)                  continue;
      if (x_recd[0] == '#')            continue;
      if (x_recd[0] == ' ')            continue;
      if (x_recd[0] == '\0')           continue;
      /*---(handle the record)-----------*/
      if (a_unit != 'y')  rc = RUN__create ('y', x_recd);
      else                rc = RUN__create ('-', x_recd);
      /*---(done)------------------------*/
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

char RUN_read   (cchar a_name [LEN_PATH]) { return RUN__read ('-', a_name); }

char
RUN__classify         (cchar a_title [LEN_HUND], cchar a_pubname [LEN_LABEL], cchar a_cmdline [LEN_RECD], cchar a_note [LEN_LABEL])
{
   char        x_type      =  '�';
   char       *p           = NULL;
   char        t           [LEN_HUND]  = "";
   int         l           =    0;
   l = strlen (a_cmdline);
   if (strcmp (a_pubname, "vi") == 0) {
      if (strncmp (a_cmdline, "vi -c call HBUF_on() -c call HTAG_on() " , 39) == 0) {
         if (strncmp (a_cmdline + 39, "master.unit ", 12) != 0) {
            ystrlcpy (t, a_cmdline + 39, LEN_HUND);
            x_type = 'E';
         } else {
            ystrlcpy (t, a_cmdline + 51, LEN_HUND);
            x_type = 'U';
         }
         p = strchr (t, '.');
         if (p != NULL)  p [0] = '\0';
         p = strchr (t, '_');
         if (p != NULL)  p [0] = '\0';
      } else if (strcmp (a_cmdline + l - 5, ".ulog") == 0) {
         ystrlcpy (t, a_cmdline + 30, LEN_HUND);
         p = strchr (t, '.');
         if (p != NULL)  p [0] = '\0';
         p = strchr (t, '_');
         if (p != NULL)  p [0] = '\0';
         x_type = 'L';
      } else if (strncmp (a_cmdline, "vi ", 3) == 0) {
         ystrlcpy (t, a_cmdline + 3, LEN_HUND);
         p = strchr (t, ' ');
         if (p != NULL)  p [0] = '\0';
         x_type = 'V';
      } else {
         x_type = 'v';
      }
   }
   else if (strcmp (a_pubname, "less") == 0) {
      if (strcmp (a_cmdline + l - 5, ".urun") == 0) {
         p = strrchr (a_cmdline, ' ');
         ystrlcpy (t, p + 1, LEN_HUND);
         p = strchr (t, '.');
         if (p != NULL)  p [0] = '\0';
         p = strchr (t, '_');
         if (p != NULL)  p [0] = '\0';
         x_type = 'R';
      } else if (strcmp (a_cmdline, "/usr/bin/less") == 0) {
         ystrlcpy (t, "man"      , LEN_HUND);
         x_type = 'm';
      } else {
         ystrlcpy (t, "���������", LEN_HUND);
         x_type = 'l';
      }
   }
   else if (strcmp (a_pubname, "theia") == 0) {
      ystrlcpy (t, "���������", LEN_HUND);
      x_type = '�';
   }
   else {
      ystrlcpy (t, a_pubname, LEN_HUND);
      x_type = '-';
   }
   /*---(save-back)----------------*/
   if (x_type == 'U')  ystrlcat (t, "_unit", LEN_LABEL);
   if (x_type == 'R')  ystrlcat (t, "_urun", LEN_LABEL);
   if (x_type == 'L')  ystrlcat (t, "_ulog", LEN_LABEL);
   ystrlcpy (a_note, t, LEN_LABEL);
   /*---(return)-------------------*/
   return x_type;
}

char
RUN__stacking         (char a_unit)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                                                                  <* 
    *> char        rce         =  -10;                                                                                           <* 
    *> char        rc          =    0;                                                                                           <* 
    *> FILE       *f           = NULL;                                                                                           <* 
    *> char        x_recd      [LEN_RECD]  = "";                                                                                 <* 
    *> char        t           [LEN_LABEL] = "";                                                                                 <* 
    *> int         c           =    0;                                                                                           <* 
    *> int         l           =    0;                                                                                           <* 
    *> char       *p           = NULL;                                                                                           <* 
    *> char       *q           = ", ";                                                                                           <* 
    *> char       *r           = NULL;                                                                                           <* 
    *> double      v           =  0.0;                                                                                           <* 
    *> char        n           =    0;                                                                                           <* 
    *> /+---(header)-------------------------+/                                                                                  <* 
    *> DEBUG_FILE   yLOG_enter   (__FUNCTION__);                                                                                 <* 
    *> /+---(generate data)------------------+/                                                                                  <* 
    *> if (a_unit != 'y')  rc = system ("xprop -root | grep \"_NET_CLIENT_LIST_STACKING(WINDOW):\" > /tmp/yX11_stacking.txt");   <* 
    *> /+---(open)---------------------------+/                                                                                  <* 
    *> f = fopen ("/tmp/yX11_stacking.txt", "rt");                                                                               <* 
    *> DEBUG_FILE   yLOG_point   ("fopen"     , f);                                                                              <* 
    *> --rce;  if (f == NULL) {                                                                                                  <* 
    *>    DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);                                                                         <* 
    *>    return rce;                                                                                                            <* 
    *> }                                                                                                                         <* 
    *> /+---(prepare)------------------------+/                                                                                  <* 
    *> c = 0;                                                                                                                    <* 
    *> fgets (x_recd, LEN_RECD, f);                                                                                              <* 
    *> l = strlen (x_recd);                                                                                                      <* 
    *> if (x_recd [l - 1] == '\n')  x_recd [--l] = '\0';                                                                         <* 
    *> p = strtok_r (x_recd + 47, ", ", &r);                                                                                     <* 
    *> /+---(read and inventory)-------------+/                                                                                  <* 
    *> while (p != NULL) {                                                                                                       <* 
    *>    /+---(handle)----------------------+/                                                                                  <* 
    *>    l = strlen (p);                                                                                                        <* 
    *>    DEBUG_FILE   yLOG_complex ("p"         , "%2d %2d�%s�", c, l, p);                                                      <* 
    *>    ystrl2hex (p, &v, LEN_LABEL);                                                                                           <* 
    *>    DEBUG_FILE   yLOG_value   ("v"         , v);                                                                           <* 
    *>    n = RUN_by_ref (v);                                                                                                    <* 
    *>    if (n >= 0)  g_runs [n].stack = c;                                                                                     <* 
    *>    /+---(next)------------------------+/                                                                                  <* 
    *>    ++c;                                                                                                                   <* 
    *>    p = strtok_r (NULL, ", ", &r);                                                                                         <* 
    *>    /+---(done)------------------------+/                                                                                  <* 
    *> }                                                                                                                         <* 
    *> /+---(close)--------------------------+/                                                                                  <* 
    *> rc = fclose (f);                                                                                                          <* 
    *> DEBUG_FILE   yLOG_value   ("fclose"    , rc);                                                                             <* 
    *> --rce;  if (rc < 0) {                                                                                                     <* 
    *>    DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);                                                                         <* 
    *>    return rce;                                                                                                            <* 
    *> }                                                                                                                         <* 
    *> /+---(complete)-----------------------+/                                                                                  <* 
    *> DEBUG_FILE   yLOG_exit    (__FUNCTION__);                                                                                 <* 
    *> return 0;                                                                                                                 <*/
}

char
RUN_gather            (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_desk, x_type, x_curr, x_size, x_locn, x_scrn;
   long        x_id        =    0;
   char        x_title     [LEN_FULL]  = "";
   short       x_left, x_topp, x_wide, x_tall;
   int         x_eterm;
   char        x_pubname   [LEN_LABEL] = "";
   char        x_cmdline   [LEN_RECD]  = "";
   int         x_lvl       =    0;
   int         x_use       =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_enter   (__FUNCTION__);
   /*---(using process)------------------*/
   for (i = 0; i < g_nrun; ++i) {
      rc = yEXEC_find_eterm_use (g_runs [i].eterm, &x_lvl, &x_use, g_runs [i].pubname, g_runs [i].cmdline);
      g_runs [i].use = x_use;
      if (g_runs [i].ref == 0) {
         if (g_runs [i].eterm == my.eterm)  g_runs [i].ref = my.win;
      }
   }
   /*---(update data)--------------------*/
   rc = yX11_reset ();
   /*---(walk windows)-------------------*/
   rc = yX11_win_by_name (YDLST_HEAD, &x_id, &x_desk, x_title, &x_type, &x_curr, &x_left, &x_topp, &x_scrn, &x_locn, &x_wide, &x_tall, &x_size);
   while (rc >= 0) {
      /*> printf ("  %1d  %-100.100s  %c %c  %4d %4d %c %c %4d %4d %c\n", x_desk, x_title, x_type, x_curr, x_left, x_topp, x_scrn, x_locn, x_wide, x_tall, x_size);   <*/
      i = RUN_by_ref (x_id);
      if (i >= 0) {
         g_runs [i].desk = x_desk;
         ystrlcpy (g_runs [i].title, x_title, LEN_HUND);
         g_runs [i].left = x_left;
         g_runs [i].topp = x_topp;
         g_runs [i].scrn = x_scrn;
         g_runs [i].locn = x_locn;
         g_runs [i].wide = x_wide;
         g_runs [i].tall = x_tall;
         g_runs [i].size = x_size;
      }
      rc = yX11_win_by_name (YDLST_NEXT, &x_id, &x_desk, x_title, &x_type, &x_curr, &x_left, &x_topp, &x_scrn, &x_locn, &x_wide, &x_tall, &x_size);
   }
   /*---(stacking order)-----------------*/
   rc = RUN__stacking ('-');
   /*---(classify)-----------------------*/
   for (i = 0; i < g_nrun; ++i) {
      g_runs [i].type = RUN__classify (g_runs [i].title, g_runs [i].pubname, g_runs [i].cmdline, g_runs [i].shortcut);
   }
   /*---(complete)-----------------------*/
   DEBUG_FILE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
RUN_write             (cchar a_name [LEN_PATH])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   FILE       *f           = NULL;
   int         i           =    0;
   char        x_heart     [LEN_HUND]  = "";
   char        t           [LEN_LABEL] = "";
   char        s           [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_FILE   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_FILE   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   DEBUG_FILE   yLOG_info    ("a_name"    , a_name);
   /*---(heartbeat)----------------------*/
   yEXEC_heartbeat (getpid (), 0, NULL, NULL, x_heart);
   /*---(open file)----------------------*/
   f = fopen (a_name, "wt");
   DEBUG_FILE   yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_FILE   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(file header)--------------------*/
   fprintf (f, "#!/usr/local/bin/theia\n");
   fprintf (f, "##   %s %s\n", P_NAMESAKE, P_HERITAGE);
   fprintf (f, "##   last update on �%s�\n", x_heart);
   fprintf (f, "\n");
   /*---(read terminal)------------------*/
   for (i = 0; i < g_nrun; ++i) {
      if (i % 5 == 0)  fprintf (f, "#-epid  -back-  fg  ---ref---  st  d  ---title--------------------------------------------------------------------------------------------  t  ---shortcut---------  left  topp  s  l  wide  tall  z \n");
      if (g_runs [i].ref == 0)  strcpy (t, "�");
      else {
         ystrl4hex (g_runs [i].ref, t, 4, 'x', LEN_LABEL);
         ystrldchg (t, '0', '�', LEN_LABEL);
         if (t [3] == '�')  t [3] = '0';
      }
      if (g_runs [i].stack == -1)  strcpy (s, " �");
      else                         sprintf (s, "%2d", g_runs [i].stack);
      fprintf (f, "%-6d  %-6.6s  %-2.2s  %-9.9s  %-2.2s  %1d  %-100.100s  %c  %-20.20s  %4d  %4d  %c  %c  %4d  %4d  %c  %6d  %-10.10s  %s \n",
            g_runs [i].eterm, g_runs [i].back , g_runs [i].fore , t,
            s               , g_runs [i].desk , g_runs [i].title, g_runs [i].type , g_runs [i].shortcut ,
            g_runs [i].left , g_runs [i].topp , g_runs [i].scrn , g_runs [i].locn ,
            g_runs [i].wide , g_runs [i].tall , g_runs [i].size ,
            g_runs [i].use  , g_runs [i].pubname, g_runs [i].cmdline);
   }
   /*---(file footer)--------------------*/
   fprintf (f, "\n");
   fprintf (f, "## end-of-file.  %d lines.  done, finito, completare, whimper [ϴ���\n", i);
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



/*====================------------------------------------====================*/
/*===----                      unit test accessor                      ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char*            /*--> unit test accessor ------------------------------*/
RUN__unit               (char *a_question, int n)
{
   /*---(locals)-----------+-----------+-*/
   int         c           =    0;
   char        t           [LEN_LABEL] = "";
   /*---(prepare)------------------------*/
   ystrlcpy  (unit_answer, "RUN              : question not understood", LEN_HUND);
   /*---(crontab name)-------------------*/
   if      (strcmp (a_question, "count"   )        == 0) {
      snprintf (unit_answer, LEN_HUND, "RUN count        : %d", g_nrun);
   }
   else if (strcmp (a_question, "entry"   )        == 0) {
      if (g_runs [n].stack >= 0)  sprintf (t, "%2d", g_runs [n].stack);
      else                        strcpy  (t, " �");
      snprintf (unit_answer, LEN_HUND, "RUN entry   (%2d) : %-6d  %-6.6s  %-2.2s  %-9.9s  %-2.2s  %-12.12s  %ld", n, g_runs [n].eterm, g_runs [n].back, g_runs [n].fore, g_runs [n].hex, t, g_runs [n].shortcut, g_runs [n].ref);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


