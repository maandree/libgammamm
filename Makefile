.POSIX:

CONFIGFILE = config.mk
include $(CONFIGFILE)

OS = linux
include mk/$(OS).mk


LIB_MAJOR = 1
LIB_MINOR = 0
LIB_VERSION = $(LIB_MAJOR).$(LIB_MINOR)
LIB_NAME = gammamm


HDR =\
	libgamma.hh\
	libgamma-error.hh\
	libgamma-facade.hh\
	libgamma-method.hh\
	libgamma-native.hh

OBJ =\
	libgamma-error.o\
	libgamma-facade.o\
	libgamma-method.o

LOBJ = $(OBJ:.o=.lo)


all: libgammamm.a libgammamm.$(LIBEXT)
$(OBJ): $(HDR)
$(LOBJ): $(HDR)
test.o: test.cc $(HDR)

libgammamm.a: $(OBJ)
	@rm -f -- $@
	$(AR) rc $@ $(OBJ)

libgammamm.$(LIBEXT): $(LOBJ)
	$(CXX) $(LIBFLAGS) -o $@ $(LOBJ) $(LDFLAGS)

test: test.o libgammamm.a
	$(CXX) -o $@ test.o libgammamm.a $(LDFLAGS)

.cc.o:
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(CPPFLAGS)

.cc.lo:
	$(CXX) -fPIC -c -o $@ $< $(CXXFLAGS) $(CPPFLAGS)

install: libgammamm.a libgammamm.$(LIBEXT)
	mkdir -p -- "$(DESTDIR)$(PREFIX)/lib"
	mkdir -p -- "$(DESTDIR)$(PREFIX)/include"
	mkdir -p -- "$(DESTDIR)$(PKGCONFIGDIR)"
	cp -- libgammamm.pc "$(DESTDIR)$(PKGCONFIGDIR)"
	cp -- libgammamm.a "$(DESTDIR)$(PREFIX)/lib/"
	cp -- libgammamm.$(LIBEXT) "$(DESTDIR)$(PREFIX)/lib/libgammamm.$(LIBMINOREXT)"
	$(FIX_INSTALL_NAME) "$(DESTDIR)$(PREFIX)/lib/libgammamm.$(LIBMINOREXT)"
	ln -sf -- libgammamm.$(LIBMINOREXT) "$(DESTDIR)$(PREFIX)/lib/libgammamm.$(LIBMAJOREXT)"
	ln -sf -- libgammamm.$(LIBMAJOREXT) "$(DESTDIR)$(PREFIX)/lib/libgammamm.$(LIBEXT)"
	cp -- $(HDR) "$(DESTDIR)$(PREFIX)/include/"

uninstall:
	mkdir -p -- "$(DESTDIR)$(PREFIX)/lib"
	mkdir -p -- "$(DESTDIR)$(PREFIX)/include"
	-rm -f -- "$(DESTDIR)$(PREFIX)/lib/libgammamm.a"
	-rm -f -- "$(DESTDIR)$(PREFIX)/lib/libgammamm.$(LIBMINOREXT)"
	-rm -f -- "$(DESTDIR)$(PREFIX)/lib/libgammamm.$(LIBMAJOREXT)"
	-rm -f -- "$(DESTDIR)$(PREFIX)/lib/libgammamm.$(LIBEXT)"
	-cd "$(DESTDIR)$(PREFIX)/include/" && rm -f -- $(HDR)
	-rm -- "$(DESTDIR)$(PKGCONFIGDIR)/libgammamm.pc"

run-test:
	./test

clean:
	-rm -f -- *.su *.so *.so.* *.dll *.dylib *.$(LIBEXT) *.o *.lo test

.SUFFIXES:
.SUFFIXES: .lo .o .cc

.PHONY: all install uninstall check run-test clean
