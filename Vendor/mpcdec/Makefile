VERSION=r475
MUSEPACK_FILENAME=musepack_src_$(VERSION).tar.gz

all: .patched

.patched: mpcdec-src/CMakeLists.txt
	patch -Np1 -d mpcdec-src < mpcdec-darwin.diff && \
	touch .patched

mpcdec-src/CMakeLists.txt: /tmp/$(MUSEPACK_FILENAME)
	tar xzf /tmp/$(MUSEPACK_FILENAME) -s /musepack_src_$(VERSION)/mpcdec-src/ musepack_src_$(VERSION)
	touch mpcdec-src/CMakeLists.txt

/tmp/$(MUSEPACK_FILENAME):
	curl -L http://files.musepack.net/source/$(MUSEPACK_FILENAME) -o /tmp/$(MUSEPACK_FILENAME)

clean:
	- rm -rf ./mpcdec-src/ ./.patched

install:
	
