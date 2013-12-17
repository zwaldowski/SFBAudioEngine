VERSION=2.1
TTA_FILENAME=libtta++-$(VERSION).tar.gz

all: .patched

.patched: libtta++-src/README
	rm libtta++-src/config.h
	perl -pi -e 's/\r\n/\n/g' libtta++-src/*.h
	patch -Np1 -d libtta++-src < TTA++-darwin.diff && \
	touch .patched	

libtta++-src/README: /tmp/$(TTA_FILENAME)
	tar xzf /tmp/$(TTA_FILENAME) -s /libtta++-$(VERSION)/libtta++-src/ libtta++-$(VERSION)
	touch libtta++-src/README

/tmp/$(TTA_FILENAME):
	curl -L http://sourceforge.net/projects/tta/files/tta/libtta++/$(TTA_FILENAME)/download -o /tmp/$(TTA_FILENAME)

clean:
	- rm -rf ./libtta++-src/ ./.patched

install:
	
