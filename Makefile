IDIR=include
CC=gcc
CFLAGS=-I$(IDIR) -DNCURSES_WIDECHAR=1 

ODIR=src
LDIR =/usr/local/lib

LIBS=-lm -lncursesw

_DEPS = *.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = board.o pieces.o gui.o main.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

chess: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
debug: CFLAGS += -DDEBUG -g
debug: chess

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
	rm chess
