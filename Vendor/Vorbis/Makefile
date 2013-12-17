VERSION=1.3.3
VORBIS_FILENAME=libvorbis-$(VERSION).tar.xz

all: download

download: libvorbis-src/README

libvorbis-src/README: /tmp/$(VORBIS_FILENAME)
	tar xJf /tmp/$(VORBIS_FILENAME) -s /libvorbis-$(VERSION)/libvorbis-src/ libvorbis-$(VERSION)

/tmp/$(VORBIS_FILENAME):
	curl -L http://downloads.xiph.org/releases/vorbis/$(VORBIS_FILENAME) -o /tmp/$(VORBIS_FILENAME)

clean:
	- rm -rf ./libvorbis-src/

install:
	
