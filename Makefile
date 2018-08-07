CCLIBS=-lcurl
#CCOPTS=-O2 -pipe -Wall
CCOPTS=-g -Wall

all: ciscodnd

ciscodnd: ciscodnd.cc
	g++ -o ciscodnd ciscodnd.cc $(CCOPTS) $(CCLIBS)

install: ciscodnd
	mv ciscodnd /usr/local/bin/

clean:
	rm -f ciscodnd *~
