VERSION=1.3.1
OGG_FILENAME=libogg-$(VERSION).tar.xz

all: download

download: libogg-src/README

libogg-src/README: /tmp/$(OGG_FILENAME)
	tar xJf /tmp/$(OGG_FILENAME) -s /libogg-$(VERSION)/libogg-src/ libogg-$(VERSION)

/tmp/$(OGG_FILENAME):
	curl -L http://downloads.xiph.org/releases/ogg/$(OGG_FILENAME) -o /tmp/$(OGG_FILENAME)

clean:
	- rm -rf ./libogg-src/

install:
	
