VERSION=1.0.25
SNDFILE_FILENAME=libsndfile-$(VERSION).tar.gz

all: download

download: sndfile-src/README

sndfile-src/README: /tmp/$(SNDFILE_FILENAME)
	tar xzf /tmp/$(SNDFILE_FILENAME) -s /libsndfile-$(VERSION)/sndfile-src/ libsndfile-$(VERSION)

/tmp/$(SNDFILE_FILENAME):
	curl -L http://www.mega-nerd.com/libsndfile/files/$(SNDFILE_FILENAME) -o /tmp/$(SNDFILE_FILENAME)

clean:
	- rm -rf ./sndfile-src/

install:
	
