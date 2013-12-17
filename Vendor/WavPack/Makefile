VERSION=4.70.0
WAVPACK_FILENAME=wavpack-$(VERSION).tar.bz2

all: download

download: wavpack-src/README

wavpack-src/README: /tmp/$(WAVPACK_FILENAME)
	tar xjf /tmp/$(WAVPACK_FILENAME) -s /wavpack-$(VERSION)/wavpack-src/ wavpack-$(VERSION)

/tmp/$(WAVPACK_FILENAME):
	curl -L http://www.wavpack.com/$(WAVPACK_FILENAME) -o /tmp/$(WAVPACK_FILENAME)

clean:
	- rm -rf ./wavpack-src/

install:
	
