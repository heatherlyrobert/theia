/*===============================[[ beg code ]]===============================*/
/*===[[ ONE_LINERS ]]=========================================================*/
/*                      ´·········1·········2·········3·········4·········5·········6·········7*/
/*--------- 12345678901 ´123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/
/*········· ··········· ´·····························´········································*/
#define     P_FOCUS     "WM (window_manager)"
#define     P_NICHE     "tc (terminal_configuration)"
#define     P_SUBJECT   "terminal color configuration"
#define     P_PURPOSE   "interactive configuration for terminal windows"
/*········· ··········· ´·····························´········································*/
#define     P_NAMESAKE  "theia-euryphaessa (wide-shinning)"
#define     P_PRONOUCE  "thee·uh yur·ee·fray·shee·uh"
#define     P_HERITAGE  "goddess of sight and the light of the clear blue sky"
#define     P_BRIEFLY   "light of the clear blue sky"
#define     P_IMAGERY   ""
#define     P_REASON    "the goddess of light and sky makes my environment beautiful"
/*········· ··········· ´·····························´········································*/
#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT
/*········· ··········· ´·····························´········································*/
#define     P_BASENAME  "theia"
#define     P_FULLPATH  "/usr/local/bin/theia"
#define     P_SUFFIX    "···"
#define     P_CONTENT   "···"
/*········· ··········· ´·····························´········································*/
#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_COMPILER  "gcc 5.3.0"
#define     P_CODESIZE  "large       (appoximately 10,000 slocl)"
#define     P_DEPENDS   "ySTR,yEXEC"
/*········· ··········· ´·····························´········································*/
#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2014-01"
/*········· ··········· ´·····························´········································*/
#define     P_VERMAJOR  "1.--, running every day in production"
#define     P_VERMINOR  "1.0-, changed from hack to maintainable program."
#define     P_VERNUM    "1.0b"
#define     P_VERTXT    "added a ton of stuff, should not have waied this long"
/*········· ··········· ´·····························´········································*/
#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"
/*········· ··········· ´·····························´········································*/
/*--------- 12345678901 ´123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/

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
#include    <yEXEC.h>        /* CUSTOM : heatherly process execution          */
#include    <yDLST_solo.h>
#include    <yX11.h>








#define     MAX_FORE        200
#define     MAX_ENTRIES      18
#define     FILE_SCHEMES   "/etc/theia.conf"

typedef     struct cFORE    tFORE;
struct cFORE {
   char        refno       [LEN_TERSE];
   char        name        [LEN_LABEL];
   char        style;
   int         hex         [MAX_ENTRIES][LEN_TERSE];
   int         value       [MAX_ENTRIES];
};
extern tFORE  g_fores     [MAX_FORE];
extern int    g_nfore;
extern int    g_cfore;



#define     MAX_BACK         200
typedef     struct cBACK     tBACK;
struct cBACK {
   char        abbr;
   char        terse       [LEN_TERSE];
   char        name        [LEN_LABEL];
   char        hex         [LEN_TERSE];
   int         value;
};
extern tBACK  g_backs     [MAX_BACK];
extern int    g_nback;
extern int    g_cback;
/*> char        g_backs   [52];                                                       <*/



typedef     struct cRUN  tRUN;
#define     MAX_RUN     400
#define     FILE_RUNTIME   "/var/run/theia.ttys"

struct cRUN {
   /*---(eterm specific)----*/
   short       eterm;                       /* owning eterm                   */
   char        back        [LEN_TERSE];     /* background terse name          */
   char        fore        [LEN_TERSE];     /* foreground refno               */
   /*---(window)------------*/
   long        ref;                         /* window reference number        */
   char        desk;                        /* which desktop                  */
   char        title       [LEN_HUND];      /* current window title           */
   char        type;                        /* window use based on title      */
   char        shortcut    [LEN_LABEL];
   /*---(position)----------*/
   short       left;
   short       topp;
   short       wide;
   short       tall;
   char        size;
   char        scrn;
   char        locn;
   /*---(running)-----------*/
   short       use;
   char        pubname     [LEN_LABEL];
   char        cmdline     [LEN_RECD];
   /*---(done)--------------*/
};
extern tRUN   g_runs    [MAX_RUN];
extern int    g_nrun;
extern int    g_crun;


typedef    struct cACCESSOR  tACCESSOR;
struct cACCESSOR {
   /*---(arguments)------------*/
   char      back_act;
   char      back_req;
   char      fore_act   [LEN_TERSE];
   char      fore_req   [LEN_TERSE];
   char      report;
   char      here;
   char      shortcut      [LEN_LABEL];
   /*---(files)----------------*/
   int       custom;
   int       theme;
   int       eterm;
   char      desk;
   long      win;
   /*---(files)----------------*/
};
tACCESSOR my;

extern      char        unit_answer [LEN_RECD];

char       *ySTR_trim          (char *a_source, char a_mode);
#define     ySTR_HEAD      'h'
#define     ySTR_TAIL      't'
#define     ySTR_BOTH      'b'
#define     ySTR_EVERY     'e'
#define     ySTR_COMPRESS  'c'


/*---(support)--------------*/
char*       PROG_version            (void);
/*---(preinit)--------------*/
char        PROG__header            (void);
char        PROG_urgents            (int a_argc, char *a_argv []);
/*---(startup)--------------*/
char        PROG__init              (int a_argc, char *a_argv []);
char        PROG__args              (int a_argc, char *a_argv []);
char        PROG__begin             (void);
char        PROG_startup            (int a_argc, char *a_argv []);
/*---(execution)------------*/
char        PROG_dawn               (void);
char        PROG_dusk               (void);
/*---(shutdown)-------------*/
char        PROG__end               (void);
char        PROG_shutdown           (void);
/*---(testing)--------------*/
char        PROG__unit_quiet        (void);
char        PROG__unit_loud         (void);
char        PROG__unit_end          (void);
/*---(done)-----------------*/


char        CONF_read               (void);

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        BACK_purge              (void);
char        BACK_by_abbr            (cchar a_abbr);
char        BACK_create             (cchar a_recd [LEN_RECD]);
char        BACK_set                (cchar a_abbr);
char*       BACK__unit              (char *a_question, int n);


char        FORE_purge              (void);
char        FORE_by_ref             (cchar a_ref  [LEN_TERSE]);
char        FORE_create             (cchar a_recd [LEN_RECD]);
char        FORE_set                (cchar a_ref  [LEN_TERSE]);
char*       FORE__unit              (char *a_question, int n);


/*===[[ theia_run.c ]]========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(program)--------------*/
char        RUN_purge               (void);
/*---(search)---------------*/
char        RUN_by_eterm            (short a_eterm);
char        RUN_by_ref              (long a_ref);
char        RUN_by_shortcut         (cchar a_shortcut [LEN_LABEL]);
/*---(create)---------------*/
char        RUN__create             (cchar a_match, cchar a_recd [LEN_RECD]);
/*---(exim)-----------------*/
char        RUN__add_eterm          (short a_rpid, cchar a_pubname [LEN_LABEL], cchar a_cmdline [LEN_RECD], cchar a_state, short a_ppid);
char        RUN__read               (char a_unit, cchar a_name [LEN_PATH]);
char        RUN_read                (cchar a_name [LEN_PATH]);
char        RUN__classify           (cchar a_title [LEN_HUND], cchar a_pubname [LEN_LABEL], cchar a_cmdline [LEN_RECD], cchar a_note [LEN_LABEL]);
char        RUN_gather              (void);
char        RUN_write               (cchar a_name [LEN_PATH]);
/*---(unittest)-------------*/
char*       RUN__unit               (char *a_question, int n);
/*---(done)-----------------*/



#endif
/*===============================[[ end code ]]===============================*/
