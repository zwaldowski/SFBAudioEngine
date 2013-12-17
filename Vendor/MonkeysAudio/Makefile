MAC_FILENAME=MAC_SDK_412.zip

all: .patched

.patched: MonkeysAudio-src/Readme.txt
	patch -Np1 -d MonkeysAudio-src < MonkeysAudio-darwin.diff && \
	touch .patched

MonkeysAudio-src/Readme.txt: /tmp/$(MAC_FILENAME)
	unzip -aa -u /tmp/$(MAC_FILENAME) -d MonkeysAudio-src
	touch MonkeysAudio-src/Readme.txt

/tmp/$(MAC_FILENAME):
	curl -L http://monkeysaudio.com/files/$(MAC_FILENAME) -o /tmp/$(MAC_FILENAME)

clean:
	- rm -rf ./MonkeysAudio-src/ ./.patched

install:
	
