VERSION=0.9.3
DUMB_FILENAME=dumb-$(VERSION).tar.gz

all: .patched

.patched: DUMB-src/readme.txt
	patch -Np1 -d DUMB-src < DUMB-darwin.diff && \
	touch .patched	

DUMB-src/readme.txt: /tmp/$(DUMB_FILENAME)
	tar xzf /tmp/$(DUMB_FILENAME) -s /dumb-$(VERSION)/DUMB-src/ dumb-$(VERSION)
	touch DUMB-src/readme.txt

/tmp/$(DUMB_FILENAME):
	curl -L http://sourceforge.net/projects/dumb/files/dumb/$(VERSION)/$(DUMB_FILENAME)/download -o /tmp/$(DUMB_FILENAME)

clean:
	- rm -rf ./DUMB-src/ ./.patched

install:
	
