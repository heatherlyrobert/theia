##*---(base name)----------------------*#
#BASE    = theia
##*---(standard variables)-------------*#
#COMP    = gcc -c -std=gnu89 -g -pg -Wall -Wextra
#INCS    = -I/usr/local/include 
#LINK    = gcc 
#LIBS    = -L/usr/local/libs -lncurses -lyLOG -lySTR
#COPY    = cp -f
#CLEAN   = rm -f
#ECHO    = @echo


##*---(executables)--------------------*#
#${BASE}            : ${BASE}.o
#	${LINK}  -o ${BASE}        ${BASE}.o ${LIBS}

##*---(normal objects)-----------------*#

#${BASE}.o          : ${BASE}.h ${BASE}.c
#	${COMP}  ${BASE}.c


##*---(housekeeping)-------------------*#
#bigclean           :
#	${CLEAN} .*.swp

#clean              :
#	${ECHO}  cleaning out object, backup, and temp files
#	${CLEAN} *.o
#	${CLEAN} *~
#	${CLEAN} temp*
#	${CLEAN} ${BASE}

#install            : ${FORMAL}
#	${COPY}  ${BASE}    /usr/local/bin/
#	chmod    0755  /usr/local/bin/${BASE}
#	sha1sum  ${BASE}
#	rm -f       /usr/share/man/man1/${BASE}.1.bz2
#	cp -f       ${BASE}.1    /usr/share/man/man1/${BASE}.1
#	bzip2       /usr/share/man/man1/${BASE}.1
#	chmod 0644  /usr/share/man/man1/${BASE}.1.bz2

#remove             :
#	rm -f /usr/local/bin/${BASE}

#all                   : _efont.sh _eterm.sh
#	_inst -v --bin _efont
#	_inst -v --bin _eterm
#================================[[ beg-code ]]================================#



#===(user defined)=========================================#
# basename of executable, header, and all code files
NAME_BASE  = theia
# additional standard and outside libraries
LIB_STD    = -lncurses -ltinfo
# all heatherly libraries used, debug versions whenever available
LIB_MINE   = -lySTR_debug
# directory for production code, no trailing slash
INST_DIR   = /usr/local/bin



#===(optional)=============================================#
# extra include directories required
INC_MINE   = 
# utilities generated, separate from main program
NAME_UTIL  = 
# libraries only for the utilities
LIB_UTIL   = 



#===(post-processing)======================================#
# create a rule for...
#install_prep       :
#remove_prep        :



#===(master template)======================================#
include /usr/local/sbin/make_program



#===(post-processing)======================================#
# create a rule for...
#install_post       :
#remove_post        :



#================================[[ end-code ]]================================#
