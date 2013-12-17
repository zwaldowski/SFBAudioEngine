VERSION=1.2rc1
SPEEX_FILENAME=speex-$(VERSION).tar.gz

all: download

download: speex-src/README

speex-src/README: /tmp/$(SPEEX_FILENAME)
	tar xzf /tmp/$(SPEEX_FILENAME) -s /speex-$(VERSION)/speex-src/ speex-$(VERSION)

/tmp/$(SPEEX_FILENAME):
	curl -L http://downloads.xiph.org/releases/speex/$(SPEEX_FILENAME) -o /tmp/$(SPEEX_FILENAME)

clean:
	- rm -rf ./speex-src/

install:
	
