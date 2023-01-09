TARGET = LTPTR1
OBJS = main.o ../common/callback.o gfx.o
INCDIR =
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -std=c++14 -fno-rtti
ASFLAGS = $(CFLAGS)
BUILD_PRX = 1
PSP_FW_VERSION = 500
PSP_LARGE_MEMORY = 1
LIBDIR =
LDFLAGS =
LIBS = -lpspaudio -lpspmp3
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = J aime le chocolat
PSP_EBOOT_ICON = icon.png
PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak