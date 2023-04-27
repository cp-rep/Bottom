BINDIR=./bin
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
BINNAME=program
_DEPS = log.hpp cursesWindow.hpp topWindow.hpp COMMANDWindow.hpp cpuWindow.hpp memWindow.hpp NIWindow.hpp percentCPUWindow.hpp percentMEMWindow.hpp PIDWindow.hpp PRWindow.hpp RESWindow.hpp SHRWindow.hpp SWindow.hpp TIMEWindow.hpp USERWindow.hpp VIRTWindow.hpp tasksWindow.hpp extractFileData.hpp memInfo.hpp byteConverter.hpp uptimeReader.hpp cpuInfo.hpp processInfo.hpp
_OBJ = main.o log.o cursesWindow.o topWindow.o COMMANDWindow.o cpuWindow.o memWindow.o NIWindow.o percentCPUWindow.o percentMEMWindow.o PIDWindow.o PRWindow.o RESWindow.o SHRWindow.o SWindow.o TIMEWindow.o USERWindow.o VIRTWindow.o tasksWindow.o extractFileData.o memInfo.o byteConverter.o uptimeReader.o cpuInfo.o processInfo.o

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
	rm -rf $(TESTINGDIR)/
	rm -f ./*~
