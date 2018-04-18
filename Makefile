# CS 3377.502
# Makefile for program 5
# Written By: Zachary Pillman
# zjp16003

CXX = g++
CXXFLAGS = -I /scratch/perkins/include
CPPFLAGS = -Wall -std=c++11

LDFLAGS= -L/scratch/perkins/lib
LDLIBS= -lcdk -lcurses

EXECFILE = program_6

OBJS = main.o

all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *~ \#*

$(EXECFILE):    $(OBJS)
	$(CXX) -static -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)


backup:
	@make clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename "`pwd`"))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME) 2> /dev/null
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!

