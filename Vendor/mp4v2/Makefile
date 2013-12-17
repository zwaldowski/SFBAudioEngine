MP4V2_SVN_URL=http://mp4v2.googlecode.com/svn/trunk/

all: update

update: mp4v2-src/README
	svn update mp4v2-src

mp4v2-src/README:
	svn checkout $(MP4V2_SVN_URL) mp4v2-src

clean:
	- rm -rf ./mp4v2-src/

install:
