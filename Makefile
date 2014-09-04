# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.  This file is offered as-is,
# without any warranty.


# The package path prefix, if you want to install to another root, set DESTDIR to that root
PREFIX ?= /usr
# The library path excluding prefix
LIB ?= /lib
# The library header path excluding prefix.
INCLUDE ?= /include
# The resource path excluding prefix
DATA ?= /share
# The library path including prefix
LIBDIR ?= $(PREFIX)$(LIB)
# The library header path including prefix.
INCLUDEDIR ?= $(PREFIX)$(INCLUDE)
# The pkg-config file path including prefix.
PKGCONFIGDIR ?= $(LIBDIR)/pkgconfig
# The resource path including prefix
DATADIR ?= $(PREFIX)$(DATA)
# The generic documentation path including prefix
DOCDIR ?= $(DATADIR)/doc
# The info manual documentation path including prefix
INFODIR ?= $(DATADIR)/info
# The license base path including prefix
LICENSEDIR ?= $(DATADIR)/licenses

# The name of the package as it should be installed
PKGNAME = libgammamm



# The version of the library.
LIB_MAJOR = 1
LIB_MINOR = 0
LIB_VERSION = $(LIB_MAJOR).$(LIB_MINOR)

# The so in libgammamm.so as the library file is named on Linux
ifeq ($(PLATFORM),w32)
SO = dll
else
ifeq ($(PLATFORM),osx)
SO = dylib
else
SO = so
endif
endif

# Platform dependent flags
ifeq ($(PLATFORM),w32)
SHARED = -mdll
LDSO = -Wl,-soname,libgammamm.$(SO).$(LIB_MAJOR)
PIC =
else
ifeq ($(PLATFORM),osx)
SHARED = -dynamiclib
LDSO =
PIC = -fPIC
else
SHARED = -shared
LDSO = -Wl,-soname,libgammamm.$(SO).$(LIB_MAJOR)
PIC = -fPIC
endif
endif

# The C standard for C code compilation
STD = c++11
# Optimisation settings for C code compilation
OPTIMISE ?= -Og -g
# Definitions for CPP, remove __GCC__ if you are not using g++
DEFS = __GCC__

# Warning flags, set to empty if you are not using GCC
WARN = -Wall -Wextra -pedantic -Wdouble-promotion -Wformat=2 -Winit-self       \
       -Wmissing-include-dirs -Wtrampolines -Wfloat-equal -Wshadow             \
       -Wmissing-declarations -Wredundant-decls -Winline -Wno-variadic-macros  \
       -Weffc++ -Wc++11-compat -Wzero-as-null-pointer-constant -Wuseless-cast  \
       -Wsync-nand -Wunsafe-loop-optimizations -Wcast-align -Wstrict-overflow  \
       -Wundef -Wcast-qual -Wwrite-strings -Wlogical-op                        \
       -Wpacked -Wvector-operation-performance -Wsuggest-attribute=const       \
       -Wsuggest-attribute=noreturn -Wsuggest-attribute=pure                   \
       -Wsuggest-attribute=format -Wnormalized=nfkc -Wconversion               \
       -fstrict-aliasing -fstrict-overflow -fipa-pure-const -ftree-vrp         \
       -fstack-usage -funsafe-loop-optimizations
# ignored: -Waggregate-return



# Flags to use when compiling
CXX_FLAGS = $(foreach D,$(DEFS),-D$(D)) -std=$(STD) \
            $(OPTIMISE) $(CXXFLAGS) $(PIC) $(CPPFLAGS) $(WARN)

# Flags to use when linking
LD_FLAGS = -lgamma -std=$(STD) $(OPTIMISE) $(LDFLAGS) $(WARN)


# Header files
HEADERS = libgamma libgamma-error libgamma-facade libgamma-method libgamma-native



.PHONY: all lib test
all: lib test
lib: bin/libgammamm.$(SO).$(LIB_VERSION) bin/libgammamm.$(SO).$(LIB_MAJOR) bin/libgammamm.$(SO)
test: bin/test

bin/libgammamm.$(SO).$(LIB_VERSION): obj/libgamma-error.o obj/libgamma-facade.o obj/libgamma-method.o
	@mkdir -p bin
	$(CXX) $(LD_FLAGS) $(SHARED) $(LDSO) -o $@ $^

bin/libgammamm.$(SO).$(LIB_MAJOR):
	@mkdir -p bin
	ln -sf libgammamm.$(SO).$(LIB_VERSION) $@

bin/libgammamm.$(SO):
	@mkdir -p bin
	ln -sf libgammamm.$(SO).$(LIB_VERSION) $@

bin/test: obj/test.o obj/libgamma-error.o obj/libgamma-facade.o obj/libgamma-method.o
	$(CXX) $(LD_FLAGS) -o $@ $^

obj/%.o: src/%.cc src/*.hh
	@mkdir -p obj
	$(CXX) $(CXX_FLAGS) -c -o $@ $<



.PHONY: install
install: install-base

.PHONY: install
install-all: install-base

.PHONY: install-base
install-base: install-lib install-include install-pc install-copyright


.PHONY: install-lib
install-lib: bin/libgammamm.$(SO).$(LIB_VERSION)
	install -dm755 -- "$(DESTDIR)$(LIBDIR)"
	install -m755 $< -- "$(DESTDIR)$(LIBDIR)/libgammamm.$(SO).$(LIB_VERSION)"
	ln -sf libgammamm.$(SO).$(LIB_VERSION) -- "$(DESTDIR)$(LIBDIR)/libgammamm.$(SO).$(LIB_MAJOR)"
	ln -sf libgammamm.$(SO).$(LIB_VERSION) -- "$(DESTDIR)$(LIBDIR)/libgammamm.$(SO)"

.PHONY: install-include
install-include:
	install -dm755 -- "$(DESTDIR)$(INCLUDEDIR)"
	install -m644 $(foreach H,$(HEADERS),src/$(H).hh) -- "$(DESTDIR)$(INCLUDEDIR)"

.PHONY: install-pc
install-pc:
	install -dm755 -- "$(DESTDIR)$(PKGCONFIGDIR)"
	install -m644 libgammamm.pc -- "$(DESTDIR)$(PKGCONFIGDIR)"


.PHONY: install-copyright
install-copyright: install-copying install-license

.PHONY: install-copying
install-copying:
	install -dm755 -- "$(DESTDIR)$(LICENSEDIR)/$(PKGNAME)"
	install -m644 COPYING -- "$(DESTDIR)$(LICENSEDIR)/$(PKGNAME)/COPYING"

.PHONY: install-license
install-license:
	install -dm755 -- "$(DESTDIR)$(LICENSEDIR)/$(PKGNAME)"
	install -m644 LICENSE -- "$(DESTDIR)$(LICENSEDIR)/$(PKGNAME)/LICENSE"



.PHONY: uninstall
uninstall:
	-rm -- "$(DESTDIR)$(LIBDIR)/libgammamm.$(SO).$(LIB_VERSION)"
	-rm -- "$(DESTDIR)$(LIBDIR)/libgammamm.$(SO).$(LIB_MAJOR)"
	-rm -- "$(DESTDIR)$(LIBDIR)/libgammamm.$(SO)"
	-rm -- $(foreach H,$(HEADERS),"$(DESTDIR)$(INCLUDEDIR)/$(H).hh")
	-rm -- "$(DESTDIR)$(PKGCONFIGDIR)/libgammamm.pc"
	-rm -- "$(DESTDIR)$(LICENSEDIR)/$(PKGNAME)/COPYING"
	-rm -- "$(DESTDIR)$(LICENSEDIR)/$(PKGNAME)/LICENSE"
	-rmdir -- "$(DESTDIR)$(LICENSEDIR)/$(PKGNAME)"



.PHONY: clean
clean:
	-rm -r obj bin

