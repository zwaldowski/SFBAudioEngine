TAGLIB_GIT_URL=https://github.com/taglib/taglib.git
TAGLIB_GIT_BRANCH=taglib2

all: update

update: taglib-src/INSTALL
	cd taglib-src; git pull --rebase origin $(TAGLIB_GIT_BRANCH); cd -

taglib-src/INSTALL: 
	git clone -b taglib2 --depth=1 $(TAGLIB_GIT_URL) taglib-src

clean:
	- rm -rf ./taglib-src/

install:
	
