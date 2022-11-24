#######################################
##                                    ##
##                RAINE               ##
##                                    ##
########################################

# version (when the version increases, raine shows the issue dialog on
# startup
VERSION = "0.94.7-soldam"

# Comment out if you don't want the debug features
#RAINE_DEBUG = 1

# Be verbose ?
#VERBOSE = 1

# Use musashi ?
# 1 = 68020
# 2 = 68000 + 68020
# set to 2 if NO_ASM is defined
#USE_MUSASHI = 1


# Disable all asm. This will also disable the asm_video_core of
# course
NO_ASM = 1

ifdef NO_ASM
USE_MUSASHI = 2
endif

# target build for cross compilation, the 2 defaults are for mingw32, 32
# and 64 bits. You can't build both at the same time, make a choice !
# Defining this allws to use ${target}-gcc for the compiler and includes
# from /usr/${target}/include, libs in /usr/${target}/lib
# choosing x86_64 here sets NO_ASM to 1 automatically.
# target=i686-w64-mingw32
# target=x86_64-w64-mingw32
# target=i686-pc-msdosdjgpp

# which lib to use :
# SDL = 1 or SDL = 2, or comment the line for allegro
SDL = 2

# end of user options, after this line the real thing starts...

ifdef target
	CROSSCOMPILE = 1
	# I don't think anyone would want another native here ?
	NATIVE=linux-gnu-sdl
ifeq ("${target}","x86_64-w64-mingw32")
	NO_ASM = 1
endif
endif

ifeq ("$(shell uname)","Linux")
OSTYPE=linux-gnu
endif

ifndef CC
	CC=cc
endif

ifdef target
CC=${target}-gcc
CXX=${target}-g++
INCDIR = -I/usr/${target}/include
else
CC=gcc
CXX=g++
endif

ifndef DARWIN
ifeq ("$(shell uname -m)","x86_64")
  # autodetect x86_64 arch, and in this case build for 32 bit arch
  # notice that you still need to make a symbolic link for libstdc++.so to
  # libstdc++.so.6, and make sure that the 32 bit version of all the libraries
  # are installed in 32 bit (which might be a little tricky at first).
 ifndef CROSSCOMPILE
ifndef NO_ASM
  CC += -m32
  CXX += -m32
  LD=$(CXX) -L /usr/lib32
else
  LD=$(CXX)
endif
 else
	ifeq ("$(LD)","ld")
	LD = $(CXX)
    endif
 endif
else
ifeq ("$(LD)","ld")
  LD=$(CXX)
endif
endif
endif

WINDRES_V := $(shell windres --version 2>/dev/null)
ifdef WINDRES_V
	WINDRES:=windres
else
	WINDRES:=$(target)-windres
endif

ifdef MINGDIR
# mingw
RAINE32 = 1
ifndef OSTYPE
OSTYPE = mingw32
endif
endif

RM =	@rm -f

# This test is for stupid win32 gcc ports with bad defaults
ifdef VERBOSE
CCV=$(CC)
CXXV=$(CXX)
LDV=$(LD)
else
CCV=@$(CC)
CXXV=@$(CXX)
LDV=@$(LD)
endif

GCC_MAJOR := $(shell echo $(CC) -dumpversion|sed 's/\..*//')
GCC_MINOR := $(shell $(CC) -dumpversion|sed 's/.\.\(.\)\..*/\1/')
GCC_PATCH := $(shell $(CC) -dumpversion|sed 's/.*\.//')

MD =	@mkdir

# profiling
# CC =	gcc -pg

INCDIR +=                 \
    -Isource            \
    -Isource/68000      \
    -Isource/sound      \
    -Isource/games      \
    -Isource/video      \
    -Isource/mini-unzip \
    -Isource/mame       \

INCDIR += -Isource/68020

ifeq ($(OSTYPE),cygwin)

   # Cygwin

RAINE_EXE = raine32.exe

# -O1 is necessary for stupid hq2x16.asm
#AFLAGS = -f coff -O1 -D__RAINE__ -DRAINE_WIN32

RAINE32 = 1

DEFINE = -D__RAINE__ \
	   -DRAINE_WIN32 \

   PNG_LFLAGS = "$(shell libpng-config --ldflags)"
   PNG_STATIC_LFLAGS = "$(shell libpng-config --static --ldflags)"
   LIBS = -lz -lalleg $(PNG_LFAGS)
   LIBS_STATIC = -lz -lalleg_s -lkernel32 -luser32 -lgdi32 -lcomdlg32 \
   -lole32 -ldinput -lddraw -ldxguid -lwinmm -ldsound \
   -L/lib/mingw -lmoldname -lmsvcrt $(PNG_STATIC_LFLAGS)

LIBS_DEBUG = -lz -lalld $(PNG_LFLAGS)

  LFLAGS = -mno-cygwin -mwindows

else
ifdef RAINE32

   # MINGW32

	RAINE_EXE = raine.exe


ifdef CROSSCOMPILE
	MD = @mkdir
else
   MD = @mkdir.exe # to avoid the built-in command... strange it's necessary...
endif

   AFLAGS = -f coff -O1 -D__RAINE__ \
	   -DRAINE_WIN32

ifdef target
   PNG_CFLAGS = "$(shell /usr/${target}/bin/libpng-config --cflags)"
   PNG_LFLAGS = $(shell /usr/${target}/bin/libpng-config --ldflags)
   PNG_STATIC_LFLAGS = "$(shell /usr/${target}/bin/libpng-config --static --ldflags)"
else
   PNG_CFLAGS = "$(shell libpng-config --cflags)"
   PNG_LFLAGS = $(shell libpng-config --ldflags)
   PNG_STATIC_LFLAGS = "$(shell libpng-config --static --ldflags)"
endif
   DEFINE = -D__RAINE__ \
	   -DRAINE_WIN32 \

   LIBS = $(PNG_LFLAGS) -lopengl32 -lz
   LIBS_STATIC = -lz $(PNG_STATIC_LFLAGS)
   INCDIR += $(PNG_CFLAGS)

LIBS_DEBUG = -lz $(PNG_LFLAGS) -lopengl32

ifndef SDL
LIBS += -lalleg
LIBS_STATIC += -lalleg_s -lkernel32 -luSer32 -lgdi32 -lcomdlg32 \
   -lole32 -ldinput -lddraw -ldxguid -lwinmm -ldsound
LIBS_DEBUG += -lalld
endif

ifndef RAINE_DEBUG
# this one hides the console in windows
  LFLAGS = -mwindows
endif
else

ifeq ("${target}","i686-pc-msdosdjgpp")
   RAINE_EXE = Raine.exe
   RAINE_DOS = 1


   OSTYPE = dos
   HAS_CONSOLE =
   AFLAGS = -f coff -O1 -D__RAINE__ \
	   -DRAINE_DOS

   DEFINE = -D__RAINE__ \
	   -DRAINE_DOS

   LIBS = -lalleg -lpng -lz -lm
   LIBS_DEBUG = -lalleg -lpng -lz -lm
ifdef RAINE_DEBUG
   LFLAGS = -Xlinker -Ttext -Xlinker 0x68000
else
   LFLAGS = -Xlinker -Ttext -Xlinker 0x4000
endif
else
# linux
   prefix = $(DESTDIR)/usr
   bindir = $(prefix)/games
   sharedir = $(prefix)/share/games
   mandir = $(prefix)/man/man6
   rainedata = $(sharedir)/raine


ifndef SDL
   langdir = $(rainedata)/languages
else
   bitmaps_dir = $(rainedata)/bitmaps
   shaders_dir = $(rainedata)/shaders
   fonts_dir = $(rainedata)/fonts
   langdir = $(rainedata)/locale
   scripts_dir = $(rainedata)/scripts
endif
   romdir = $(rainedata)/roms
   artdir = $(rainedata)/artwork

RAINE_EXE = raine

#   RAINE_DAT = raine.dat
#   RAINE_LNG = brasil.cfg dansk.cfg espanol.cfg french2.cfg german2.cfg japanese.cfg spanish.cfg turkish.cfg catala.cfg dutch.cfg euskera.cfg french.cfg german.cfg polish.cfg svenska.cfg czech.cfg english.cfg finnish.cfg galego.cfg italian.cfg portugal.cfg template.cfg
   RAINE_UNIX = 1

ifdef VERBOSE
   INSTALL = /usr/bin/install
else
    INSTALL = @install
endif
   INSTALL_BIN = $(INSTALL) -m 755
   INSTALL_DATA = $(INSTALL) -m 644
   RD = rmdir --ignore-fail-on-non-empty
   CD = cd

   AFLAGS = -f elf -O1 -D__RAINE__ \
	   -DRAINE_UNIX

   PNG_CFLAGS = "$(shell libpng-config --cflags)"
ifndef SDL
ALLEGRO_CFLAGS = "$(shell allegro-config --cflags)"
endif

   INCDIR += $(PNG_CFLAGS) $(ALLEGRO_CFLAGS)


   DEFINE = -D__RAINE__ \
	   -DRAINE_UNIX


ifndef SDL
   LIBS = -lz $(shell allegro-config --libs) $(shell libpng-config --ldflags) -lm
   LIBS_DEBUG = -lz $(shell allegro-config --libs ) $(shell libpng-config --ldflags) -lm
   LIBS_STATIC = -lz $(shell allegro-config --static) $(shell libpng-config --static --ldflags) -lm
else
ifdef DARWIN
   LIBS = -lz /usr/local/lib/libpng.a -lm
   LIBS_DEBUG = -lz /usr/local/lib/libpng.a -lm
   LIBS_STATIC = -lz /usr/local/lib/libpng.a -lm
else
   LIBS = -lz $(shell libpng-config --ldflags) -lm
   LIBS_DEBUG = -lz $(shell libpng-config --ldflags) -lm
   LIBS_STATIC = -lz $(shell libpng-config --static --ldflags) -lm
endif
ifndef DARWIN
	LIBS += -lGL
	LIBS_DEBUG += -lGL -lGLU
endif
endif

ifndef SDL
ifeq ("$(shell if [ -e /usr/include/vga.h ] || [ -e /usr/local/include/vga.h ]; then echo yes; fi)","yes")
GFX_SVGALIB=1
endif
endif

ifdef GFX_SVGALIB
   LIBS += -lvga
   LIBS_DEBUG += -lvga
   LIBS_STATIC += -lvga
endif # GFX_SVGALIB

endif # linux / mingw32
endif # djgpp
endif # if OSTYPE == cygwin

ifdef RAINE_DEBUG
 ifndef SDL
INCDIR +=	-Isource/alleg/debug
  endif
endif

ifeq (${SDL},1)
SDLCONFIG = "sdl-config"
else
SDLCONFIG = "sdl2-config"
endif


ifdef SDL
ifeq (${SDL},2)
	# gui is an implicit include directory with sdl1, it must become explicit here for the files which moved to the sdl2 directory
	INCDIR += -Isource/sdl2 -Isource/sdl2/gui -Isource/sdl/gui -Isource/sdl2/SDL_gfx -Isource/sdl/SDL_gfx -Isource/sdl2/sdl_sound
endif
INCDIR += -Isource/sdl
else
INCDIR += -Isource/alleg/gui
endif

# To allow cross-compilation, we need one dir / target
OBJDIR = $(OSTYPE)
ifdef SDL
OBJDIR = ${OSTYPE}-sdl
ifeq (${SDL},2)
	OBJDIR = ${OSTYPE}-sdl2
endif
endif


ifdef X86_64
OBJDIR := $(OBJDIR)64
endif

ifeq "$(RAINE32) $(STATIC) $(SDL)" "1 1 "
# Windows need a separate object dir for the static version (for allegro)
OBJDIR := $(OBJDIR)/static
else
OBJDIR := $(OBJDIR)/object
endif

ifdef RAINE_DEBUG
OBJDIR := $(OBJDIR)d
endif

VIDEO_CORE = $(OBJDIR)/video/c

OBJDIRS=$(OBJDIR)                \
    $(OBJDIR)/mame               \
    $(OBJDIR)/sound              \
    $(OBJDIR)/68000              \
    $(OBJDIR)/video              \
    $(OBJDIR)/video/c            \
    $(VIDEO_CORE)/blit_x2        \
    $(OBJDIR)/mini-unzip         \
    $(VIDEO_CORE)/str            \
    $(OBJDIR)/math               \
    $(OBJDIR)/games              \


ifdef USE_MUSASHI
	OBJDIRS += $(OBJDIR)/Musashi
endif


OBJDIRS += $(OBJDIR)/68020

ifdef SDL
OBJDIRS += \
	$(OBJDIR)/sdl \
	$(OBJDIR)/sdl/SDL_gfx \
	$(OBJDIR)/sdl/gui \
	$(OBJDIR)/sdl/dialogs \

ifeq (${SDL},2)
OBJDIRS += $(OBJDIR)/sdl2 \
	$(OBJDIR)/sdl2/SDL_gfx \
	$(OBJDIR)/sdl2/sdl_sound \
	$(OBJDIR)/sdl2/gui
endif

endif

ifdef SEAL
OBJDIRS += $(OBJDIR)/seal
endif

ifndef CROSSCOMPILE
INCDIR += -I/usr/local/include
endif

ifdef USE_MUSASHI
DEFINE += -DMUSASHI_CNF=\"m68kconf-raine.h\" -DUSE_MUSASHI=$(USE_MUSASHI)
endif

# define LSB_FIRST if we are a little-endian target
ifndef BIGENDIAN
DEFINE += -DLSB_FIRST
endif

# The -fno-stack-protector is because of a stack smash which happens on only 1 computer and which does not make any sense at all !
# see comment in TConsole::TConsole
ifdef RAINE_DEBUG
CFLAGS_MCU = $(INCDIR) $(DEFINE) $(_MARCH) -Wall -Wno-write-strings -g -DRAINE_DEBUG -Wno-format-truncation
CFLAGS += $(INCDIR) $(DEFINE) $(_MARCH) -Wall -Wno-write-strings -g -DRAINE_DEBUG -Wno-format-truncation -fno-stack-protector
else
# All the flags are optimisations except -fomit-frame-pointer necessary for
# the 68020 core in dos. -Wno-trigraphs suppress some anoying warnings with
# gcc-2.96
# These flags are for gcc-2.x

ifdef RAINE32
# when starting a game -> black screen if -O > 1 (bug in uint64 calculation)
CFLAGS += -O3
else
# Seems to work now, at least with the sdl version ? (to be tested with windows !)
CFLAGS = -O3
endif

CFLAGS += $(INCDIR) \
	$(DEFINE) \
	$(_MARCH) \
	-Wno-trigraphs \
	-fexpensive-optimizations \
	-ffast-math \
	-w \
	-fomit-frame-pointer -fno-stack-protector

# This is required for gcc-2.9x (bug in -fomit-frame-pointer)
ifeq ($(GCC_MAJOR),2)
CFLAGS_MCU = $(_MARCH) -O3 -fexpensive-optimizations # switches for the 68705 mcus
else
CFLAGS_MCU := $(CFLAGS)
endif

ifdef RAINE_UNIX
CFLAGS += -pipe
endif
# The accumulate-outgoing-args is for gcc3, but I am not sure it has any
# effect... And I could not notice any improvement with my duron if I change
# the cpu and arch to athlon... For now I comment the gcc3 option for the
# win32 version (no gcc3 for win32 for now).
#	 -maccumulate-outgoing-args
#	-pedantic
endif



ifdef X86_64
CFLAGS += -DX86_64
CFLAGS_MCU += -DX86_64
endif

ifdef NO_ASM
CFLAGS += -DNO_ASM
CFLAGS_MCU += -DNO_ASM
endif

ifdef SDL
CFLAGS += -DSDL=${SDL}
CFLAGS_MCU += -DSDL=${SDL}
endif


ifdef USE_MUSASHI
ASM020= $(OBJDIR)/68020/newcpu.o \
	$(OBJDIR)/Musashi/m68kcpu.o \
	$(OBJDIR)/Musashi/m68kops.o
endif


# STARSCREAM 68000 core

ifeq ($(USE_MUSASHI),2)
SC000= $(OBJDIR)/68000/starhelp.o
else
SC000=	$(OBJDIR)/68000/s68000.o \
	$(OBJDIR)/68000/starhelp.o
endif

# Video core

VIDEO=	$(OBJDIR)/video/tilemod.o \
	$(OBJDIR)/video/palette.o \
	$(OBJDIR)/video/priorities.o \
	$(OBJDIR)/video/newspr.o \
	$(OBJDIR)/video/spr64.o \
	$(OBJDIR)/video/cache.o \
	$(VIDEO_CORE)/str/6x8_8.o \
	$(VIDEO_CORE)/str/6x8_16.o \
	$(VIDEO_CORE)/str/6x8_32.o \
		\
	$(VIDEO_CORE)/16x8_8.o \
	$(VIDEO_CORE)/16x8_16.o \
	$(VIDEO_CORE)/16x8_32.o \
		\
	$(OBJDIR)/video/c/lscroll.o \
	$(OBJDIR)/video/alpha.o \
	$(OBJDIR)/video/c/str_opaque.o \
	$(OBJDIR)/video/c/common.o \
	$(OBJDIR)/video/c/pdraw.o

VIDEO += $(VIDEO_CORE)/sprites.o

# common to asm & c : 32bpp version of alpha blending
VIDEO += $(OBJDIR)/video/c/sprites32_a50.o \
	 $(OBJDIR)/video/c/mapped_alpha.o

# Sound core

SOUND= \
    $(OBJDIR)/sound/fmopl.o    \
    $(OBJDIR)/sound/emulator.o


2151 = 	$(OBJDIR)/sound/ym2151.o \
	$(OBJDIR)/sound/2151intf.o

ADPCM = $(OBJDIR)/sound/adpcm.o

M6585 = $(OBJDIR)/sound/m6585.o

MSM5205 = $(OBJDIR)/sound/msm5205.o

MSM5232 = $(OBJDIR)/sound/msm5232.o

# games

OBJS += \
	$(OBJDIR)/games/megasys1.o \
	$(OBJDIR)/games/taitosnd.o \

OBJS += \
	$(SC000) \
	$(ASM020) \
	$(2151) \
	$(OBJDIR)/decode.o \
	$(ADPCM) \
	$(M6585) \

# System drivers

SYSDRV= \
	$(OBJDIR)/games/games.o \
	$(OBJDIR)/games/default.o

# Interface

ifdef SDL
GUI=	$(OBJDIR)/sdl/gui.o \
	$(OBJDIR)/sdl/dialogs/video_info.o \
	$(OBJDIR)/sdl/dialogs/fsel.o \
	$(OBJDIR)/sdl/dialogs/video_options.o \
	$(OBJDIR)/sdl/dialogs/sound_options.o \
	$(OBJDIR)/sdl/dialogs/gui_options.o \
	$(OBJDIR)/sdl/dialogs/dirs.o \
	$(OBJDIR)/sdl/dialogs/messagebox.o \
	$(OBJDIR)/sdl/dialogs/controls.o \
	$(OBJDIR)/sdl/dialogs/game_options.o \
	$(OBJDIR)/sdl/dialogs/colors.o \
	$(OBJDIR)/sdl/gui/tfont.o \
	$(OBJDIR)/sdl/gui/widget.o \
	$(OBJDIR)/sdl/gui/tslider.o \
	$(OBJDIR)/sdl/gui/tlift.o \
	$(OBJDIR)/sdl/dialogs/game_selection.o \
	$(OBJDIR)/sdl/dialogs/romdirs.o \
	$(OBJDIR)/sdl/dialogs/dlg_dsw.o \

ifeq (${SDL},1)
	GUI += 	$(OBJDIR)/sdl/gui/tbitmap.o \
	$(OBJDIR)/sdl/gui/tedit.o
else
	GUI += $(OBJDIR)/sdl2/gui/menu.o \
	$(OBJDIR)/sdl2/gui/tedit.o
endif
endif

# Core

CORE=	$(OBJDIR)/raine.o \
	$(OBJDIR)/romdir.o \
	$(OBJDIR)/ingame.o \
	$(OBJDIR)/savegame.o \
	$(OBJDIR)/debug.o \
	$(OBJDIR)/config.o \
	$(OBJDIR)/confile.o \
	$(OBJDIR)/files.o \
	$(OBJDIR)/newmem.o \
	$(OBJDIR)/cpumain.o \
	$(OBJDIR)/emumain.o \
	$(OBJDIR)/timer.o \
	$(OBJDIR)/soundcfg.o \
 	$(OBJDIR)/loadroms.o


UNZIP = $(OBJDIR)/mini-unzip/unzip.o \
	$(OBJDIR)/mini-unzip/ioapi.o

CORE +=	$(OBJDIR)/sdl/dsw.o

ifndef RAINE_DOS
CORE += $(OBJDIR)/sdl/SDL_gfx/SDL_framerate.o
endif

ifdef SDL

ifneq (${SDL},2)
CORE += $(OBJDIR)/sdl/SDL_gfx/SDL_gfxPrimitives.o
else
CORE += $(OBJDIR)/sdl2/SDL_gfx/SDL_gfxPrimitives.o
endif

endif


OBJS +=	 \
	$(VIDEO) \
	$(SOUND) \
	$(CORE) \
	$(UNZIP) \
	$(MAME) \
	$(GUI) \
	$(GAMES) \
	$(SYSDRV) \

ifdef SDL
OBJS +=	 \
	$(OBJDIR)/sdl/control.o \
	$(OBJDIR)/sdl/opengl.o \
	$(OBJDIR)/math/matrix.o \
	$(OBJDIR)/sdl/glsl.o \
	$(OBJDIR)/sdl/profile.o


OBJS += $(OBJDIR)/sdl2/blit.o \
	$(OBJDIR)/sdl2/display.o \
	$(OBJDIR)/sdl2/controllermap.o \
	$(OBJDIR)/sdl2/compat.o
endif

ifdef STATIC
LIBS = $(LIBS_STATIC)
CFLAGS += -DALLEGRO_STATICLINK
endif
ifdef RAINE_DEBUG
LIBS = $(LIBS_DEBUG)
# Uncomment only if you want to debug the cpu cores
# AFLAGS += -g
endif

ifdef X86_64
AFLAGS += -m amd64
endif

ifdef SEAL
OBJS += $(OBJDIR)/seal/sasound.o
CFLAGS += -DSEAL
else
ifdef RAINE_DOS
OBJS += $(OBJDIR)/alleg/sasound.o
CFLAGS += -DALLEGRO_SOUND
else
# avoid allegro when we can, sdl is much more reliable for sound
OBJS += $(OBJDIR)/sdl/sasound.o

ifdef target
CFLAGS += $(shell /usr/${target}/bin/${SDLCONFIG} --cflags)
else
CFLAGS += $(shell ${SDLCONFIG} --cflags)
endif

ifdef target
LIBS += $(shell /usr/${target}/bin/${SDLCONFIG} --libs) -lSDL2_ttf
else
ifeq (${SDL},1)
LIBS += $(shell ${SDLCONFIG} --libs) -lSDL_ttf
else
LIBS += $(shell ${SDLCONFIG} --libs) -lSDL2_ttf
endif
endif
endif
endif


all:	source/version.h message maketree depend $(RAINE_EXE) \
	locale/raine.pot \

locale/raine.pot:
	xgettext --omit-header -C -k_ -kgettext -d raine -s -o locale/tmp `find source -name '*.c*'`
	cat locale/header locale/tmp > locale/raine.pot
	rm -f locale/tmp

CFLAGS_BS := -Wall -O2 $(shell ${SDLCONFIG} --cflags) $(INCDIR) -DSTANDALONE -DNO_GZIP -c

# Using gcc here instead of $(CC) because we don't want a 32 bit binary in
# an amd64 arch.
byteswap: $(OBJDIR)/byteswap.o $(OBJDIR)/files_b.o $(OBJDIR)/newmem_b.o
	gcc -o byteswap $^

$(OBJDIR)/byteswap.o: source/byteswap.c
	gcc $(CFLAGS_BS) -DSDL={SDL} -o $@ $<

$(OBJDIR)/files_b.o: source/files.c
	gcc $(CFLAGS_BS) -DSDL={SDL} -o $@ $<

$(OBJDIR)/newmem_b.o: source/newmem.c
	gcc $(CFLAGS_BS) -DSDL={SDL} -o $@ $<

depend:
	@echo dependencies : if you get an error here, install the required dev package
ifndef RAINE_DOS
	@echo -n libpng:
	@libpng-config --version
	@echo -n SDL:
	@${SDLCONFIG} --version
endif
ifdef RAINE_UNIX
endif

source/version.h: makefile
# I have just removed the stuff about gcc --version.
# Too much trouble with it. And I didn't know the __GNUC__ macros...
ifeq ($(OSTYPE),dos)
ifdef CROSSCOMPILE
	@echo "#define VERSION \"$(VERSION)\"" > source/version.h
else
# The dos seems too stupid to redirect stderr to a file (lame command.com).
# Usually I use 4dos for that, but since most people don't I use redir here
# which is in the standard djgpp install...
# Even with bash installed it does not work (it calls the dos shell instead
# of sh).
	@djecho '#define VERSION $(VERSION)' > source/version.h
endif
else
# Carefull for the windows version you need sh.exe and echo.exe !
	@echo "#define VERSION \"$(VERSION)\"" > source/version.h
endif

message:
ifdef RAINE_DEBUG
	@echo -n Building Raine, debug version
else
	@echo -n Building Raine, Fully optimized version
endif
ifdef GFX_SVGALIB
	@echo -n " with svgalib support"
endif
	@echo " with $(CC) for $(OSTYPE) CPU=$(CPU)"

$(RAINE_EXE):	$(OBJS)

	@echo Linking Raine...
	$(LDV) $(LDFLAGS) $(LFLAGS) -g -Wall -Wno-write-strings -o $(RAINE_EXE) $^ $(LIBS)

tags:
	ctags --kinds-c=+fpdvx -R source

VIDEO: $(VIDEO)


compress: $(RAINE_EXE)
	   @strip $(RAINE_EXE)
	   @echo Appending datafile...
#	   exedat -a -c $(RAINE_EXE) raine.dat
	   upx -9 $(RAINE_EXE)

# compile object from standard c

$(OBJDIR)/%.o: source/%.c
	@echo Compiling $<...
	$(CCV) $(CFLAGS) -MD -c $< -o $@
	@cp $(OBJDIR)/$*.d $(OBJDIR)/$*.P; \
            sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
                -e '/^$$/ d' -e 's/$$/ :/' < $(OBJDIR)/$*.d >> $(OBJDIR)/$*.P; \
            rm -f $(OBJDIR)/$*.d

$(OBJDIR)/%.o: source/%.cpp
	@echo Compiling c++ $<...
	$(CXXV) $(CFLAGS) -MD -c $< -o $@
	@cp $(OBJDIR)/$*.d $(OBJDIR)/$*.P; \
            sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
                -e '/^$$/ d' -e 's/$$/ :/' < $(OBJDIR)/$*.d >> $(OBJDIR)/$*.P; \
            rm -f $(OBJDIR)/$*.d

-include $(OBJS:%.o=%.P)

# This one is for a bug in gcc-4.8.3, 4.8.4 and 4.9.2 at least
# just launch kazan or iganinju, the sound effects are bad while the demo
# is playing -O is ok, -O1 has already the bug !
ifndef RAINE_DEBUG
$(OBJDIR)/sound/adpcm.o: source/sound/adpcm.c
	@echo Compiling less optimized $<...
	$(CCV) -O $(INCDIR) $(INCDIR) $(DEFINE) $(_MARCH) -Wall -Wno-write-strings -g -MD -c $< -o $@
	@cp $*.d $*.P; \
            sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
                -e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
            rm -f $*.d
endif

# Notice : the following fix is specific to the frame pointer optimisation
# of gcc 2.81 and higher (< 3.00)


ifeq ($(GCC_MAJOR),3)
# This one happens for gcc < 3.2.1 (even 3.2.0)
$(OBJDIR)/sound/ymf278b.o: source/sound/ymf278b.c
	@echo Compiling WITH frame pointer $<...
	$(CCV) $(INCDIR) $(DEFINE) $(CFLAGS_MCU) -c $< -o $@

$(OBJDIR)/games/bubl_mcu.o: source/games/bubl_mcu.c
	@echo "Compiling $< (gcc-3.3 bug work around)..."
	$(CCV) $(INCDIR) $(DEFINE) $(_MARCH) -c $< -o $@
endif

# SDL redefines the main function for windows programs, so we need to
# explicitely compile the cpu emulators without SDL (or link them with it
# which would be useless).

$(OBJDIR)/68000/star.o: source/68000/star.c
	@echo Compiling StarScream...
	$(CCV) $(DEFINE) $(CFLAGS_MCU) -c $< -o $@

# create directories

$(OBJDIRS):
ifndef OSTYPE
	@echo Your OSTYPE is not defined.
	@echo "If you are in Unix/Linux, make sure you are using bash/sh."
	@echo 'If this is the case, try to export OSTYPE : export OSTYPE=$OSTYPE'
	@echo "If not, you can type (for dos/windows) :"
	@echo "set OSTYPE=dos"
	@echo "before make."
	@exit 1
else
	$(MD) -p $@
endif

maketree: $(OBJDIRS)

# remove all object files

clean:
	@echo Deleting object tree ...
	$(RM) -r $(OBJDIR)
	@echo Deleting $(RAINE_EXE)...
	$(RM) $(RAINE_EXE) make.dep

# Installation part (Only for Unix)
ifndef SDL
install: install_dirs $(RAINE_LNG) $(RAINE_EXE)
else
install: install_dirs $(RAINE_EXE)
endif
	strip $(RAINE_EXE)
ifdef RAINE_UNIX
	@echo installing $(RAINE_EXE) in $(bindir)
	$(INSTALL_BIN) $(RAINE_EXE) $(bindir)
ifndef SDL
	$(INSTALL_DATA) $(RAINE_DAT) $(rainedata)
else

	@echo installing fonts in $(fonts_dir)
	$(INSTALL_DATA) fonts/Vera.ttf fonts/10x20.fnt fonts/VeraMono.ttf fonts/font6x8.bin $(fonts_dir)
	@echo installing bitmaps in $(bitmaps_dir)
	$(INSTALL_DATA) bitmaps/cursor.png bitmaps/raine_logo.png bitmaps/bub2.png bitmaps/axis.bmp bitmaps/button.bmp \
		bitmaps/controllermap.bmp bitmaps/controllermap_back.bmp $(bitmaps_dir)
	@echo installing shaders in $(shaders_dir)
	$(INSTALL_DATA) shaders/*.shader $(shaders_dir)
	@cp -rfva scripts/* $(scripts_dir)
	$(INSTALL_DATA) gamecontrollerdb.txt $(rainedata)
endif
	$(INSTALL_DATA) config/debug_dips.txt $(rainedata)

ifndef DARWIN
	$(INSTALL_DATA) raine.desktop $(prefix)/share/applications
endif
	$(INSTALL_DATA) raine.png $(prefix)/share/pixmaps
	@cp -rfv locale/pt locale/fr locale/es locale/it $(langdir)
ifdef DARWIN
	@echo creating package $(DESTDIR)
	@cp Info.plist $(prefix)
	@cp new_logo.icns $(sharedir)
endif

install_dirs:
	$(MD) -p $(bindir) $(rainedata) $(langdir) $(romdir) $(artdir) $(prefix)/share/pixmaps
	$(MD) -p $(prefix)/share/applications $(bitmaps_dir) $(fonts_dir) $(scripts_dir) $(shaders_dir)

ifndef SDL
$(RAINE_LNG):
	$(INSTALL_DATA) config/language/$@ $(langdir)
endif

else
	@echo There is no needs to install for a win32/dos system
endif

ifdef USE_MUSASHI
source/Musashi/m68kops.c source/Musashi/m68kops.h: $(OBJDIR)/Musashi/m68kmake
	cd source/Musashi && ../../$(OBJDIR)/Musashi/m68kmake

$(OBJDIR)/Musashi/m68kmake.o: source/Musashi/m68kmake.c
	$(CC) -c -o $@ $<

$(OBJDIR)/Musashi/m68kmake: $(OBJDIR)/Musashi/m68kmake.o
ifdef CROSSCOMPILE
	cp -fv $(NATIVE)/object/Musashi/m68kmake $(OBJDIR)/Musashi
else
	$(LD) -o $@ $<
endif

$(OBJDIR)/Musashi/m68kcpu.o: source/Musashi/m68kops.h source/Musashi/m68kops.c source/Musashi/m68kcpu.c

source/68021/68020.h: source/Musashi/m68k.h
source/Musashi/m68k.h:
	if ! [ -d source/Musashi ]; then git submodule add https://github.com/zelurker/Musashi.git source/Musashi; fi
	cd source/Musashi && git submodule init
	cd source/Musashi && git submodule update

endif