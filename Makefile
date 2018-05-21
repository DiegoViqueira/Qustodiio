# Compiler
CC = g++
OPTS = -c -Wall

# Project name
PROJECT = QustodioServer
PROJECT_CLI = QustodioCient

# Directories
OBJDIR = obj
SRCDIR = src
BLDDIR = build

# Libraries
LIBS = -lboost_filesystem-mgw73-mt-x64-1_67 -lboost_system-mgw73-mt-x64-1_67 -lboost_thread-mgw73-mt-x64-1_67 -lws2_32

#include

INCLUDE = -I ./common -I ./boost 
INCLUDE_LIBS = -L ./boost/stage/lib

# Files and folders for server
SRCS  =  $(SRCDIR)/QustodioServer.cpp $(SRCDIR)/TCP_Handlers.cpp $(SRCDIR)/Protocol.cpp
OBJS    = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Files and folders for client
SRCS_CLI    =  $(SRCDIR)/QustodioClient.cpp $(SRCDIR)/TCP_Handlers.cpp $(SRCDIR)/Protocol.cpp
OBJS_CLI    = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS_CLI))

# Targets
all:  $(BLDDIR)/$(PROJECT) $(BLDDIR)/$(PROJECT_CLI)

# Building Server
$(BLDDIR)/$(PROJECT): $(OBJS)
	@echo #################  Linking $@  #######################
	$(CC) $(OBJS) $(LIBS) $(LDFLAGS) $(INCLUDE_LIBS) -o $@

# Building Client
$(BLDDIR)/$(PROJECT_CLI): $(OBJS_CLI)
	@echo #################  Linking $@  #######################
	$(CC) $(OBJS_CLI) $(LIBS) $(LDFLAGS) $(INCLUDE_LIBS) -o $@

# Compiling Files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo #################   Building object $@ ###################
	$(CC) $(OPTS) $(LDFLAGS) $(INCLUDE) -c $< -o $@

# Clean 
clean:
	@echo #################   Cleaning   ###################
	rmdir /S /Q $(OBJDIR)
	rmdir /S /Q $(BLDDIR)
	
# Directory Creation
dirs:
	@echo #################   Directories creation ###################
	mkdir $(BLDDIR)
	mkdir $(OBJDIR)
	
