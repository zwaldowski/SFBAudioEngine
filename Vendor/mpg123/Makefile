VERSION=1.16.0
MPG123_FILENAME=mpg123-$(VERSION).tar.bz2

all: .patched

.patched: mpg123-src/README
	patch -Np1 -d mpg123-src < mpg123-darwin.diff && \
	touch .patched	

mpg123-src/README: /tmp/$(MPG123_FILENAME)
	tar xjf /tmp/$(MPG123_FILENAME) -s /mpg123-$(VERSION)/mpg123-src/ mpg123-$(VERSION)
	touch mpg123-src/README

/tmp/$(MPG123_FILENAME):
	curl -L http://sourceforge.net/projects/mpg123/files/mpg123/$(VERSION)/$(MPG123_FILENAME)/download -o /tmp/$(MPG123_FILENAME)

clean:
	- rm -rf ./mpg123-src/ ./.patched

install:
	
