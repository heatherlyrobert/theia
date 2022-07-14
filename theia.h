/*===============================[[ beg code ]]===============================*/
/*===[[ ONE_LINERS ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/

#define     P_FOCUS     "WM (window_manager)"
#define     P_NICHE     "tc (terminal_configuration)"
#define     P_SUBJECT   "terminal color configuration"
#define     P_PURPOSE   "interactive configuration for terminal windows"

#define     P_NAMESAKE  "theia-euryphaessa (wide-shinning)"
#define     P_HERITAGE  ""
#define     P_IMAGERY   ""
#define     P_REASON    ""

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  ""
#define     P_FULLPATH  ""
#define     P_SUFFIX    ""
#define     P_CONTENT   ""

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "large       (appoximately 10,000 slocl)"
#define     P_DEPENDS   "none"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2014-01"

#define     P_VERMAJOR  ""
#define     P_VERMINOR  ""
#define     P_VERNUM    "0.6d"
#define     P_VERTXT    "more color tweaking ;) and conf file"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"

/*===[[ HEADER ]]============================================================*/

/*   focus         : (WM) window_manager
 *   niche         : (tc) terminal_configuration
 *   heritage      : theia (titaness of sight and light of clear blue sky)
 *   purpose       : interactive configuration for terminal windows
 *
 *   base_system   : gnu/linux   (powerful, ubiquitous, technical, and hackable)
 *   lang_name     : ansi-c      (wicked, limitless, universal, and everlasting)
 *   dependencies  : ncurses, yLOG
 *   size          : small       (less than 2,000 slocL)
 * 
 *   author        : rob_heatherly
 *   created       : 2014-01
 *   priorities    : direct, simple, brief, vigorous, and lucid (h.w. fowler)
 *   end goal      : loosely coupled, strict interface, maintainable, portable
 *
 */
/*===[[ SUMMARY ]]===========================================================*/

/*   theia euryphaessa (wide-shinning) is one of the twelve greek titans and
 *   titaness of sight and the light of the clear blue sky.  she is the consort
 *   of hyperion and mother to helios (sun), selene (moon), and eos (dawn).
 *   she is the goddess who endowed gold, silver, and gems with their
 *   brilliance and intrinsic value.
 *
 *
 *
 */


/*===[[ PURPOSE ]]===========================================================*/

/*   theia is a configurator for eterm windows (my primary environment).  its
 *   goal is to provide an interactive method to beaufifully match eterm
 *   background and font colors with the desktop environment including other
 *   eterm windows.
 *
 *   while eterms are capable of being gorgeous and contain a huge variety of
 *   configuration options, they can be fussy and require time to get right.
 *   theia is a front-end tool for matching background colors and font colors.
 *
 *   theia will specifically handle the following...
 *      -- reading scheme file to get
 *      -- presets for transparent background colors
 *      -- interactive adjustment to background color
 *      -- presets for eterm font colors (16 color mode)
 *      -- showing changes to backgrounds and fonts together for testing
 *
 *   thea will not handle...
 *      -- writing updates to the theme preset file
 *      -- interactive font color adjustments beyond presets
 *
 *   AS ALWAYS, there are many stable, accepted, existing programs that have
 *   been built by better programmers and are likely superior in speed, size,
 *   capability, and reliability; BUT, i would not have learned nearly as much
 *   using them, so i follow the adage..
 *
 *   THE UNDERLYING IDEA is to use this build process to learn new programming
 *   capabilities and put additional pressure on me to improve my standards
 *   maintenance, and coding environment.  just using programs and ideas does
 *   not lead to understanding -- so get in there and get messy ;
 *
 */
/*===[[ NEXT STEPS ]]========================================================*/

/*   -- inventory of color schemes
 *   -- add eterm logic
 *   -- add interactive eterm color selection
 *   -- save font color scheme to the environment
 *   -- save eterm background color to the environment
 *
 */


/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef     YTHEIA
#define     YTHEIA loaded

/*===[[ STANDARD C LIBRARIES ]]===============================================*/
#include    <stdio.h>        /* C_ANSI : strcpy, strlen, strchr, strcmp, ...  */
#include    <string.h>       /* C_ANSI : printf, snprintf, fgets, fopen, ...  */
#include    <stdlib.h>       /* C_ANSI : exit                                 */

/*===[[ DE-FACTO STANDARD LIBRARIES ]]========================================*/
#include    <ncurses.h>      /* CURSES : mvprintw, refresh, getch, ...        */

/*---(custom core)-----------------------*/
#include    <yURG.h>              /* heatherly urgent processing              */
#include    <yLOG.h>              /* heatherly program logging                */
#include    <ySTR.h>              /* heatherly string processing              */








#define     MAX_SCHEME      200
#define     MAX_ENTRIES      18
#define     FILE_SCHEMES   "/etc/theia.conf"

typedef     struct cTHEME   tTHEME;
struct cTHEME {
   char        refno       [ 5];
   char        name        [50];
   char        style;
   int         hex         [MAX_ENTRIES];
};
tTHEME      themes      [MAX_SCHEME];
int         ntheme;



#define     MAX_BACK         200
typedef     struct cBACK     tBACK;
struct cBACK {
   char        key;
   char        abbr        [LEN_TERSE];
   char        color       [LEN_LABEL];
   char        name        [50];
   char        rgb         [50];
   int         hex;
};
tBACK       backs       [MAX_BACK];
int         nback;



typedef     struct cRUNTIME  tRUNTIME;
#define     MAX_RUNTIME     400
#define     FILE_RUNTIME   "/var/run/theia.ttys"

struct cRUNTIME {
   int         ppid;
   long        when;
   char        back_key;
   char        back_name  [50];
   int         back_hex;
   char        theme_ref  [ 5];
   char        theme_name [50];
};
tRUNTIME    runtimes    [MAX_RUNTIME];
int         nruntime;



/*> #define     MAX_TERM         10000                                                <* 
 *> typedef     struct cTERM     tTERM;                                               <* 
 *> struct cTERM {                                                                    <* 
 *>    int         pid;                                                               <* 
 *>    int         term;                                                              <* 
 *> };                                                                                <* 
 *> tTERM       terms       [MAX_TERM];                                               <* 
 *> int         nterm;                                                                <*/







/*>                                                                                    <* 
 *> /+===[[ DEBUGGING ]]==========================================================+/   <* 
 *> typedef  struct cDEBUG  tDEBUG;                                                    <* 
 *> struct cDEBUG {   /+ abcdefgiopstx +/                                              <* 
 *>    /+---(standards)----------------------+/                                        <* 
 *>    char        tops;                   /+ t) broad structure and context      +/   <* 
 *>    char        args;                   /+ c) command line args and config     +/   <* 
 *>    char        prep;                   /+ x) program setup and teardown       +/   <* 
 *>    char        evnt;                   /+ e) event loop processing            +/   <* 
 *>    char        file;                   /+ f) text and data file input         +/   <* 
 *>    char        inpt;                   /+ i) interactive and keyboard input   +/   <* 
 *>    char        data;                   /+ d) data storage and stuctures       +/   <* 
 *>    char        proc;                   /+ p) data processing/manipulation     +/   <* 
 *>    char        graf;                   /+ g) grahpics, drawing, and display   +/   <* 
 *>    char        outp;                   /+ o) text and data file output        +/   <* 
 *>    char        apis;                   /+ a) interprocess communication       +/   <* 
 *>    char        scrp;                   /+ b) scripts and batch operations     +/   <* 
 *>    char        summ;                   /+ s) statistics and analytical output +/   <* 
 *>    /+---(special)------------------------+/                                        <* 
 *> };                                                                                 <* 
 *> tDEBUG      debug;         /+ primary debugging structure         +/               <*/

/*> #define     DEBUG_TOPS          if (debug.tops      == 'y')                       <* 
 *> #define     DEBUG_ARGS          if (debug.args      == 'y')                       <* 
 *> #define     DEBUG_PREP          if (debug.prep      == 'y')                       <* 
 *> #define     DEBUG_EVENT         if (debug.evnt      == 'y')                       <* 
 *> #define     DEBUG_FILE          if (debug.file      == 'y')                       <* 
 *> #define     DEBUG_INPUT         if (debug.inpt      == 'y')                       <* 
 *> #define     DEBUG_DATA          if (debug.data      == 'y')                       <* 
 *> #define     DEBUG_PROC          if (debug.proc      == 'y')                       <* 
 *> #define     DEBUG_GRAPH         if (debug.graf      == 'y')                       <* 
 *> #define     DEBUG_OUTPUT        if (debug.outp      == 'y')                       <* 
 *> #define     DEBUG_APIS          if (debug.apis      == 'y')                       <* 
 *> #define     DEBUG_SCRIPT        if (debug.scrp      == 'y')                       <* 
 *> #define     DEBUG_SUMM          if (debug.summ      == 'y')                       <*/






typedef    struct cACCESSOR  tACCESSOR;
struct cACCESSOR {
   /*---(files)----------------*/
   char      quiet;          /* bool : 0=normal, 1=quiet                      */
   int       logger;         /* log file so that we don't close it            */
};
tACCESSOR my;


char       *ySTR_trim          (char *a_source, char a_mode);
#define     ySTR_HEAD      'h'
#define     ySTR_TAIL      't'
#define     ySTR_BOTH      'b'
#define     ySTR_EVERY     'e'
#define     ySTR_COMPRESS  'c'



#endif

/*===============================[[ end code ]]===============================*/
