OPUS_VERSION=1.1
OPUS_FILENAME=opus-$(OPUS_VERSION).tar.gz
OPUSFILE_VERSION=0.4
OPUSFILE_FILENAME=opusfile-$(OPUSFILE_VERSION).tar.gz

all: opus-src/README .patched-opusfile

.patched-opusfile: opusfile-src/README.txt
	patch -Np1 -d opusfile-src < opusfile-darwin.diff && \
	touch .patched-opusfile

opus-src/README: /tmp/$(OPUS_FILENAME)
	tar xzf /tmp/$(OPUS_FILENAME) -s /opus-$(OPUS_VERSION)/opus-src/ opus-$(OPUS_VERSION)
	touch opus-src/README

/tmp/$(OPUS_FILENAME):
	curl -L http://downloads.xiph.org/releases/opus/$(OPUS_FILENAME) -o /tmp/$(OPUS_FILENAME)

opusfile-src/README.txt: /tmp/$(OPUSFILE_FILENAME)
	tar xzf /tmp/$(OPUSFILE_FILENAME) -s /opusfile-$(OPUSFILE_VERSION)/opusfile-src/ opusfile-$(OPUSFILE_VERSION)
	touch opusfile-src/README.txt

/tmp/$(OPUSFILE_FILENAME):
	curl -L https://ftp.mozilla.org/pub/mozilla.org/opus/$(OPUSFILE_FILENAME) -o /tmp/$(OPUSFILE_FILENAME)

clean:
	- rm -rf ./opus-src/ ./opusfile-src/ ./.patched-opusfile

install:
	
