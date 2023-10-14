BINDIR=./bin
MKDIR_P = mkdir -p
SRCDIR=./src
BUILDDIR=./build
GTESTDIR=./gtest
LOGDIR=./log
LDIR=./lib
ODIR=obj
TESTINGDIR=./Testing
VALDIR=./valtest
OPDIR=./open_project
CC=g++
CPPFLAGS=-I$(IDIR)
LIBS=-lm
BINNAME=bottom
_DEPS = log.hpp cursesWindow.hpp mainWindow.hpp topWindow.hpp COMMANDWindow.hpp cpuWindow.hpp memWindow.hpp NIWindow.hpp percentCPUWindow.hpp percentMEMWindow.hpp PIDWindow.hpp PRWindow.hpp RESWindow.hpp SHRWindow.hpp SWindow.hpp TIMEWindow.hpp USERWindow.hpp VIRTWindow.hpp tasksWindow.hpp extractFileData.hpp memInfo.hpp byteConverter.hpp cpuInfo.hpp processInfo.hpp secondsToTime.hpp cursesColors.hpp cursesFunctions.hpp _progStateConsts.hpp _fileConsts.hpp _cursesWinConsts.hpp sortProcessLists.hpp
_OBJ = main.o log.o cursesWindow.o mainWindow.o topWindow.o COMMANDWindow.o cpuWindow.o memWindow.o NIWindow.o percentCPUWindow.o percentMEMWindow.o PIDWindow.o PRWindow.o RESWindow.o SHRWindow.o SWindow.o TIMEWindow.o USERWindow.o VIRTWindow.o tasksWindow.o extractFileData.o memInfo.o byteConverter.o cpuInfo.o processInfo.o secondsToTime.o cursesFunctions.o sortProcessLists.o

DEPS = $(patsubst %,$(LDIR)/%,$(_DEPS))

OBJ = $(patsubst %,$(SRCDIR)/$(ODIR)/%,$(_OBJ))

$(SRCDIR)/$(ODIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< -I$(LDIR)

$(BINDIR)/$(BINNAME): $(OBJ)
	$(CC) -o $@ $^ -l panel -l ncurses -I$(LDIR) $(LIBS)

.PHONY: clean  dirs

clean:
	rm -f $(SRCDIR)/$(ODIR)/*.o
	rm -f $(SRCDIR)/$(ODIR)/*~
	rm -f $(SRCDIR)/*~
	rm -f $(LDIR)/*~
	rm -f $(VALDIR)/*~
	rm -f $(OPDIR)/*~
	rm -rf $(BINDIR)/bottom
	rm -rf $(BUILDDIR)/
	rm -rf $(GTESTDIR)/*~
	rm -rf $(LOGDIR)/*.log
	rm -rf $(TESTINGDIR)/
	rm -f ./*~

dirs: $(BINDIR) ${LOGDIR}

${BINDIR}:
	${MKDIR_P} ${BINDIR}

${LOGDIR}:
	${MKDIR_P} ${LOGDIR}
