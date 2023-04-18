BINDIR=./bin
SRCDIR=./src
BUILDDIR=./build
GTESTDIR=./gtest
LOGDIR=./log
LDIR=./lib
ODIR=obj
VALDIR=./valtest
OPDIR=./open_project
CC=g++
CPPFLAGS=-I$(IDIR)
LIBS=-lm
BINNAME=program
_DEPS = foo.hpp log.hpp mainWindow.hpp
_OBJ = main.o foo.o log.o mainWindow.o

DEPS = $(patsubst %,$(LDIR)/%,$(_DEPS))

OBJ = $(patsubst %,$(SRCDIR)/$(ODIR)/%,$(_OBJ))

$(SRCDIR)/$(ODIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< -I$(LDIR)

$(BINDIR)/$(BINNAME): $(OBJ)
	$(CC) -o $@ $^ -l panel -l ncurses -I$(LDIR) $(LIBS)

.PHONY: clean

clean:
	rm -f $(SRCDIR)/$(ODIR)/*.o
	rm -f $(SRCDIR)/$(ODIR)/*~
	rm -f $(SRCDIR)/*~
	rm -f $(LDIR)/*~
	rm -f $(VALDIR)/*~
	rm -f $(OPDIR)/*~
	rm -rf $(BINDIR)/*
	rm -rf $(BUILDDIR)/
	rm -rf $(GTESTDIR)/*~
	rm -rf $(LOGDIR)/*
	rm -f ./*~
