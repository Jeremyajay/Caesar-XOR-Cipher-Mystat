# Jeremy Cuthbert
# CS333 - Jesse Chaney
# Lab 1 Makefile

CC = gcc
DEBUG = -g
DEFINES =
CFLAGS = $(DEBUG) -Wall -Wshadow -Wunreachable-code -Wredundant-decls \
	-Wmissing-declarations -Wold-style-definition -Wmissing-prototypes \
	-Wdeclaration-after-statement -Wextra $(DEFINES)
PROG1 = cae-xor
PROG2 = mystat
PROGS = $(PROG1) $(PROG2)

all: $(PROGS)

$(PROG1): $(PROG1).o
	$(CC) $(CFLAGS) -o $@ $^

$(PROG1).o: $(PROG1).c
	$(CC) $(CFLAGS) -c $<

$(PROG2): $(PROG2).o
	$(CC) $(CFLAGS) -o $@ $^

$(PROG2).o: $(PROG2).c
	$(CC) $(CFLAGS) -c $<

clean cls:
	rm -f $(PROGS) *.o *~ \#*

git:
	if [ ! -d .git ]; then git init; fi
	git add *.[ch] Makefile
	git commit -m "Auto commit on $$(date '+%Y-%m-%d %H:%M:%S')"

tar:
	tar cvfa ${LOGNAME}_bin_files.tar.gz *.[ch] Makefile
