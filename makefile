BINDIR=./bin
MKDIR_P = mkdir -p
SRCDIR=./src
BUILDDIR=./build
GTESTDIR=./gtest
LOGDIR=./log
LDIR=./lib
CSVDIR=./csv
ODIR=obj
CC=g++
CPPFLAGS=-I$(IDIR)
LIBS=-lm
BINNAME=bottom
_DEPS = log.hpp cursesWindow.hpp extractFileData.hpp memInfo.hpp byteConverter.hpp cpuInfo.hpp processInfo.hpp secondsToTime.hpp cursesFunctions.hpp _progStateConsts.hpp _fileConsts.hpp _cursesWinConsts.hpp sortProcessLists.hpp taskInfo.hpp changeProgramStates.hpp
_OBJ = main.o log.o cursesWindow.o extractFileData.o memInfo.o byteConverter.o cpuInfo.o processInfo.o secondsToTime.o cursesFunctions.o sortProcessLists.o taskInfo.o changeProgramStates.o

DEPS = $(patsubst %,$(LDIR)/%,$(_DEPS))

OBJ = $(patsubst %,$(SRCDIR)/$(ODIR)/%,$(_OBJ))

$(SRCDIR)/$(ODIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< -I$(LDIR)

$(BINDIR)/$(BINNAME): $(OBJ)
	$(CC) -std=c++98 -Wall -Wextra -o $@ $^ -l panel -l ncurses -I$(LDIR) $(LIBS)

.PHONY: clean dirs

clean:
	rm -f $(SRCDIR)/$(ODIR)/*.o
	rm -f $(SRCDIR)/$(ODIR)/*~
	rm -f $(SRCDIR)/*~
	rm -f $(LDIR)/*~
	rm -f $(OPDIR)/*~
	rm -rf $(BINDIR)/bottom
	rm -rf $(BUILDDIR)/
	rm -rf $(GTESTDIR)/*~
	rm -rf $(LOGDIR)/*.log
	rm -rf $(CSVDIR)/*.csv
	rm -f ./*~

dirs: ${BINDIR} ${LOGDIR} ${SRCDIR}/${ODIR}

${BINDIR}:
	${MKDIR_P} ${BINDIR}

${LOGDIR}:
	${MKDIR_P} ${LOGDIR}

${CSVDIR}:
	${MKDIR_P} ${CSVDIR}

${SRCDIR}/${ODIR}:
	${MKDIR_P} ${SRCDIR}/${ODIR}
