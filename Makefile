#Note, to run this fresh, first have to build the libraries if you haven't already done so
#make -C libdaisy && make -C DaisySP && make
# Project Name
TARGET = DaisyPatchDripSynth

# Sources
CPP_SOURCES = DripSynth.cpp

# Library Locations
LIBDAISY_DIR = libdaisy
DAISYSP_DIR = DaisySP

# Core location, and generic Makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile
