# ompiler & Linker settings
CC = g++
#CFLAGS = -g -Wall -march=native -flto -funroll-loops -finline-functions -ffast-math -std=c++11 -pthread -O3 -DNDEBUG -I./inc
#CFLAGS = -g -Wall -I ./inc -I ./third-party/CImg -I /home/course/2024OOP/2024OOPTA/libjpeg -std=c++11 
CFLAGS = -g -Wall -I ./inc -I ./third-party/CImg -I ./third-party/libjpeg -I ./Data-Loader -std=c++11 
LINKER = -L/usr/X11R6/lib -lm -lpthread -lX11 -L./third-party/libjpeg -ljpeg


# Valgrind for memory issue
CHECKCC = valgrind
CHECKFLAGS = --leak-check=full -s --show-leak-kinds=all --track-origins=yes 

# Source files and object files
SRCDIR = src
OBJDIR = obj
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Control the build verbosity
ifeq ("$(VERBOSE)","1")
    Q :=
    VECHO = @true
else
    Q := @
    VECHO = @printf
endif

# Name of the executable
TARGET = Image_Processing

all: $(TARGET)

$(OBJDIR):
	@mkdir $(OBJDIR)

$(TARGET): $(OBJS) $(OBJDIR)/data_loader.o
	$(VECHO) "	LD\t$@\n"
	$(Q)$(CC) $(CFLAGS) main.cpp $^ -o $@ $(LINKER)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(VECHO) "	CC\t$@\n"
	$(Q)$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/data_loader.o: ./Data-Loader/data_loader.cpp 
	$(VECHO) "	CC\t$@\n"
	$(Q)$(CC) $(CFLAGS) -c $< -o $@

install:
	chmod +x scripts/clone_env.sh  
	./scripts/clone_env.sh  

check:
	$(CHECKCC) $(CHECKFLAGS) ./$(TARGET)

clean:
	rm -rf $(OBJDIR) $(TARGET)
