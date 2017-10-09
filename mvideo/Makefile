#
CC = gcc
LD = $(CC)

LDFLAGS = `pkg-config gtk+-2.0  --libs gthread-2.0` -ljpeg -lpthread 

PROG = mvideo
VERSION = 0.9

CFLAGS = `pkg-config gtk+-2.0 --cflags` -DVERSION=\"$(VERSION)\" -g -Wall
INCLUDES = 
OBJS = 

all: $(PROG)

clean:
	rm -f $(PROG) *.o *.core core *.bak *~
dist: mutils.c mprocess.c mvideo.c mvideo.h CHANGES COPYING INSTALL Makefile README
	mkdir ../$(PROG)-$(VERSION)
	cp mprocess.c ../$(PROG)-$(VERSION)/
	cp mutil.c ../$(PROG)-$(VERSION)/
	cp mvideo.c ../$(PROG)-$(VERSION)/
	cp mvideo.h ../$(PROG)-$(VERSION)/
	cp INSTALL ../$(PROG)-$(VERSION)/
	cp Makefile ../$(PROG)-$(VERSION)/
	cp README ../$(PROG)-$(VERSION)/
mvideo: mutils.o mprocess.o mvideo.o ccvt_c1.o 
	$(LD) $(LDFLAGS) mutils.o mprocess.o mvideo.o ccvt_c1.o -o mvideo 

mvideo.o: mvideo.c mvideo.h
	$(CC) $(CFLAGS) -c mvideo.c

mprocess.o: mprocess.c mvideo.h
	$(CC) $(CFLAGS) -c mprocess.c 

mutils.o: mutils.c mvideo.h
	$(CC) $(CFLAGS) -c mutils.c 

ccvt_c1.o: ccvt_c1.c ccvt.h
	$(CC) $(CFLAGS) -c ccvt_c1.c

