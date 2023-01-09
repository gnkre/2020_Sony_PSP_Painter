TARGET = TST
OBJS = main.o ../../common/callback.o
INCDIR =
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -std=c++14 -fno-rtti
ASFLAGS = $(CFLAGS)
BUILD_PRX = 1
PSP_FW_VERSION = 500
PSP_LARGE_MEMORY = 1
LIBDIR =
LDFLAGS =
LIBS = -lpspaudio -lpspmp3 -lpng -lpng14 -lz -lzzip -lzzipwrap -lm
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = J aime
PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak