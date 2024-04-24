/*===============================[[ beg code ]]===============================*/
/*===[[ ONE_LINERS ]]=========================================================*/
/*                      ´·········1·········2·········3·········4·········5·········6·········7*/
/*--------- 12345678901 ´123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/
/*········· ··········· ´·····························´········································*/
#define     P_FOCUS     "WM (window_manager)"
#define     P_NICHE     "tc (terminal_configuration)"
#define     P_SUBJECT   "eterm configuration and tracking"
#define     P_PURPOSE   "aesthetic configuration and tracking for terminal windows"
/*········· ··········· ´·····························´········································*/
#define     P_NAMESAKE  "theia-euryphaessa (wide-shinning)"
#define     P_PRONOUCE  "thee·uh yur·ee·fray·shee·uh"
#define     P_HERITAGE  "goddess of sight and the light of the clear blue sky"
#define     P_BRIEFLY   "light of the clear blue sky"
#define     P_IMAGERY   "glittering woman, mother of helios (sun), selene (moon), and eos (dawn)"
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
/*········· ··········· ´·····························´········································*/
#define     P_DEPSTDC   "stdio,stdlib,string,math,fnctl"
#define     P_DEPGRAPH  "ncurses"
#define     P_DEPCORE   "yLOG,yURG,ySTR"
#define     P_DEPVIKEYS "···"
#define     P_DEPOTHER  "yEXEC,yX11"
/*········· ··········· ´·····························´········································*/
#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2014-01"
/*········· ··········· ´·····························´········································*/
#define     P_VERMAJOR  "1.--, running every day in production"
#define     P_VERMINOR  "1.0-, changed from hack to maintainable program."
#define     P_VERNUM    "1.0h"
#define     P_VERTXT    "updated for yURG testing and cleanup"
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
#include    <fcntl.h>        /* clibc  standard file control             */
#include    <math.h>         /*                                          */

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
   char        f_abbr      [LEN_TERSE];
   char        f_name      [LEN_LABEL];
   char        f_style;
   int         f_hex       [MAX_ENTRIES][LEN_TERSE];
   int         f_value     [MAX_ENTRIES];
};
extern tFORE  g_fores     [MAX_FORE];
extern int    g_nfore;
extern int    g_cfore;



#define     MAX_BACK         200
typedef     struct cBACK     tBACK;
struct cBACK {
   char        b_abbr      [LEN_TERSE];
   char        b_terse     [LEN_TERSE];
   char        b_name      [LEN_LABEL];
   char        b_hex       [LEN_TERSE];
   int         b_value;
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
   short       r_eterm;                     /* owning eterm                   */
   char        r_back      [LEN_TERSE];     /* background terse name          */
   char        r_fore      [LEN_TERSE];     /* foreground refno               */
   /*---(window)------------*/
   char        r_hex       [LEN_LABEL];
   long        r_winid;                     /* window reference number        */
   char        r_stack;                     /* window stacking order          */
   char        r_desk;                      /* which desktop                  */
   char        r_title     [LEN_HUND];      /* current window title           */
   char        r_type;                      /* window use based on title      */
   char        r_terse     [LEN_LABEL];
   char        r_hint      [LEN_SHORT];     /* two-letter hint code           */
   /*---(position)----------*/
   short       r_left;
   short       r_topp;
   short       r_wide;
   short       r_tall;
   char        r_size;
   char        r_scrn;
   char        r_locn;
   /*---(running)-----------*/
   short       r_use;
   char        r_pubname   [LEN_LABEL];
   char        r_cmdline   [LEN_RECD];
   char        r_order;
   /*---(done)--------------*/
};
extern tRUN   g_runs    [MAX_RUN];
extern int    g_nrun;
extern int    g_crun;

#define     FILE_FIFO      "/dev/theia.fifo"

typedef    struct cACCESSOR  tACCESSOR;
struct cACCESSOR {
   /*---(overall)--------------*/
   char        term        [LEN_LABEL];     /* type of terminal               */
   /*---(arguments)------------*/
   char        identify;
   char        back_act    [LEN_TERSE];
   char        back_req    [LEN_TERSE];
   char        fore_act    [LEN_TERSE];
   char        fore_req    [LEN_TERSE];
   char        report;
   char        here;
   char        shortcut    [LEN_LABEL];
   float       scale;
   char        ygrid;
   char        xgrid;
   char        range;
   char        list;
   char        extra;
   /*---(files)----------------*/
   int         custom;
   int         theme;
   int         eterm;
   char        desk;
   long        win;
   /*---(files)----------------*/
};
extern tACCESSOR my;

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
char*       PROG__unit_title        (void);
char        PROG__unit_quiet        (void);
char        PROG__unit_loud         (void);
char        PROG__unit_end          (void);
/*---(done)-----------------*/


char        CONF_read               (void);

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        BACK_purge              (void);
char        BACK_by_abbr            (cchar a_abbr [LEN_TERSE]);
char        BACK_handler            (cchar a_recd [LEN_RECD]);
char        BACK_set                (cchar a_abbr [LEN_TERSE]);
char        BACK_report             (FILE *f);
char        BACK__unit_force        (char a_abbr [LEN_TERSE], char a_terse [LEN_TERSE], char a_name [LEN_LABEL], char a_hex [LEN_TERSE]);
char*       BACK__unit              (char *a_question, int n);


char        FORE_purge              (void);
char        FORE_by_abbr            (cchar a_abbr  [LEN_TERSE]);
char        FORE_create             (cchar a_recd [LEN_RECD]);
char        FORE_set                (cchar a_abbr  [LEN_TERSE]);
char*       FORE__unit              (char *a_question, int n);


/*===[[ theia_run.c ]]========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(program)--------------*/
char        RUN_clear               (char i);
char        RUN_purge               (void);
/*---(search)---------------*/
char        RUN_by_eterm            (short a_eterm);
char        RUN_by_winid            (long a_winid);
char        RUN_by_terse            (cchar a_terse [LEN_LABEL]);
char        RUN_by_hint             (cchar a_hint [LEN_TERSE]);
char        RUN_by_sticky           (char a_ref [LEN_LABEL]);
/*---(create)---------------*/
char        RUN_handler             (cchar a_match, cchar a_recd [LEN_RECD]);
/*---(exim)-----------------*/
char        RUN__add_eterm          (short a_rpid, cchar a_pubname [LEN_LABEL], cchar a_cmdline [LEN_RECD], cchar a_state, short a_ppid);
char        RUN__read               (char a_unit, cchar a_name [LEN_PATH]);
char        RUN_read                (cchar a_name [LEN_PATH]);
char        RUN__classify           (cchar a_title [LEN_HUND], cchar a_pubname [LEN_LABEL], cchar a_cmdline [LEN_RECD], cchar a_note [LEN_LABEL]);
char        RUN_gather              (void);
char        RUN_write               (cchar a_name [LEN_PATH]);
/*---(unittest)-------------*/
char        RUN__unit_force         (short a_eterm, char a_hint [LEN_SHORT], char a_back [LEN_TERSE], char a_fore [LEN_TERSE], char a_hex [LEN_TERSE], char a_terse [LEN_LABEL]);
char*       RUN__unit               (char *a_question, int n);
/*---(done)-----------------*/



/*===[[ theia_fifo.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(search)---------------*/
char        FIFO_by_stack           (char a_stack);
/*---(reorder)--------------*/
char        FIFO__current           (cchar a_hex [LEN_LABEL]);
/*---(listen)---------------*/
char        FIFO__listener          (cchar a_recd [LEN_RECD]);
char        FIFO_listen             (cchar a_name [LEN_PATH]);
char        FIFO_eater              (cchar a_name [LEN_PATH]);
/*---(done)-----------------*/



char        PAGE__init              (void);
char        PAGE__scaler            (float a_scale);
char        PAGE__single            (char a_type, short a_wide, char a_prefix [LEN_TERSE], char a_single [LEN_FULL], char a_break [LEN_TERSE]);
char        PAGE__line              (char x_grid, cchar a_prefix [LEN_TERSE], cchar a_single [LEN_FULL], cchar a_break [LEN_TERSE], char r_desk [LEN_FULL]);
char        PAGE__block             (short x_offset, char x_grid, short a_wide, short a_tall);
char        PAGE_single             (void);
char        PAGE_multi              (void);
char*       PAGE__unit              (char *a_question, int n);

#endif
/*===============================[[ end code ]]===============================*/
