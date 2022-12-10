#include   "theia.h"


/*> char        s_backs   [52] = "";                                                  <*/



char         /*--> read all schemes from source file -----[ ------ [ ------ ]-*/
CONF_read          (void)
{
   /*---(locals)-----------+-----------+-*/
   FILE       *f           = NULL;          /* file handle for source file    */
   char        rce         = -10;           /* return code for errors         */
   char        rc          =   0;           /* generic return code            */
   char        x_recd      [LEN_RECD];
   int         x_len;
   int         x_lines     = 0;
   /*---(header)-------------------------*/
   DEBUG_CONF   yLOG_enter   (__FUNCTION__);
   /*---(open file)----------------------*/
   f = fopen(FILE_SCHEMES, "r");
   --rce;  if (rc != 0) {
      DEBUG_CONF   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(read schemes)-------------------*/
   while (1) {
      /*---(get record)------------------*/
      fgets (x_recd, LEN_RECD, f);
      if (feof(f))                     break;
      ++x_lines;
      DEBUG_CONF   yLOG_value   ("LINE"      , x_lines);
      x_len = strlen (x_recd);
      if (x_len <= 0)                  continue;
      x_recd [--x_len] = '\0';
      /*---(filter non-scheme lines)-----*/
      if (x_len <= 0)                  continue;
      if (x_recd [0] == '#')           continue;
      if (x_recd [0] == ' ')           continue;
      if (x_recd [0] == '\0')          continue;
      /*---(address themes)--------------*/
      if (strncmp (x_recd, "foreground ", 11) == 0) {
         rc = FORE_create (x_recd);
      }
      /*---(address backgrounds)---------*/
      else if (strncmp (x_recd, "background ", 11) == 0) {
         rc = BACK_create (x_recd);
      }
   }
   /*---(close file)---------------------*/
   rc = fclose (f);
   --rce;  if (rc != 0) {
      DEBUG_CONF   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_CONF   yLOG_exit    (__FUNCTION__);
   return 0;
}
