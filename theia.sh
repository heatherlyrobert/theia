#!/bin/bash --
#

# theia is the greek titan of sight and the shinning light of the clear blue sky


#*============================================================================*#
#   
#   this program helps me do two main things...
#      -- design font color schemes
#      -- match font color schemes to eterm colors
#   but, it also helps me remember some of the clever
#   things that can be done with escape codes and the
#   creativity available in 16 color terminal setups.
#



##===[[ print header ]]=======================================================##
clear
printf "\n\n"
printf "  the heatherly aterm color pallette display...\n"
printf "\n"



##===[[ print color titles ]]=================================================##
printf "           "
printf "[-49)--clear----]   "
printf "[-40)--black----]   "
printf "[-41)--red------]   "
printf "[-42)--green----]   "
printf "[-43)--yellow---]   "
printf "[-44)--blue-----]   "
printf "[-45)--magenta--]   "
printf "[-46)--cyan-----]   "
printf "[-47)--grey-----]   "
printf "  [--------color-hex--------]"
printf "\n"



##===[[ print sub titles ]]===================================================##
printf "   fg ba   "
for bcolor in 9 0 1 2 3 4 5 6 7; do
   printf " norm;0   bold;1    "
done
printf "     norm;0         bold;1"
printf "\n\n"



##===[[ print color entries ]]================================================##
for fcolor in 9 0 1 2 3 4 5 6 7; do
   printf "  "
   case $fcolor in
   9) printf "default--\n";;
   0) printf "black----\n";;
   1) printf "red------\n";;
   2) printf "green----\n";;
   3) printf "yellow---\n";;
   4) printf "blue-----\n";;
   5) printf "magenta--\n";;
   6) printf "cyan-----\n";;
   7) printf "grey-----\n";;
   esac
   for battr  in 0 5; do
      printf "   3${fcolor} "
      case $battr  in
      0) printf ";0   ";;
      5) printf ";5   ";;
      esac
      for bcolor in 9 0 1 2 3 4 5 6 7; do
         for fattr  in 0 1; do
            if [[ $battr == 0 ]]; then
               if [[ $fattr == 0 ]]; then
                  printf "\e[3${fcolor};4${bcolor}m  test  \e[0m "
               else
                  printf "\e[${fattr};3${fcolor};4${bcolor}m  test  \e[0m "
               fi
            else 
               if [[ $fattr == 0 ]]; then
                  printf "\e[${battr};3${fcolor};4${bcolor}m  test  \e[0m "
               else
                  printf "\e[${fattr};${battr};3${fcolor};4${bcolor}m  test  \e[0m "
               fi
            fi
         done
         printf "  "
      done
       printf "  "
      case $battr  in
      0) printf "\e[5;3${fcolor};4${fcolor}m   3e5d78   \e[0m   "
         printf "\e[1;3${fcolor};4${fcolor}m   fa562a   \e[0m   "
         ;;
      5) printf "\e[1;3${fcolor};4${fcolor}m   3e5d78   \e[0m   "
         printf "\e[5;3${fcolor};4${fcolor}m   fa562a   \e[0m   "
         ;;
      esac
      printf "\n"
   done
   printf "\n"
done
#0) printf " 3e5d78   fa562a";;



##===[[ print number spacing bar ]]===========================================##
for i in $(seq 0 21); do
   printf "%02d        " "$i"
done
printf "\n"
for i in $(seq 0 21); do
   printf "0123456789"
done
printf "\n"

exit
