VERSION=1.3.0
FLAC_FILENAME=flac-$(VERSION).tar.xz

all: download

download: flac-src/README

flac-src/README: /tmp/$(FLAC_FILENAME)
	tar xJf /tmp/$(FLAC_FILENAME) -s /flac-$(VERSION)/flac-src/ flac-$(VERSION)

/tmp/$(FLAC_FILENAME):
	curl -L http://downloads.xiph.org/releases/flac/$(FLAC_FILENAME) -o /tmp/$(FLAC_FILENAME)

clean:
	- rm -rf ./flac-src/

install:
	
