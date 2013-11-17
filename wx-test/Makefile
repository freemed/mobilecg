LDFLAGS = `wx-config --libs --gl-libs` -framework GLUT
CXXFLAGS = -O2 `wx-config --cxxflags`

all: Info.plist ecgtest ecgtest.app #version.plist InfoPlist.strings ecgtestMacIcons.icns AnotherResource.txt  
	cp Info.plist ecgtest.app/Contents/
#	cp version.plist ecgtest.app/Contents/
#	cp InfoPlist.strings ecgtest.app/Contents/Resources/English.lproj/
	echo -n 'APPL????' > ecgtest.app/Contents/PkgInfo
	cp ecgtest ecgtest.app/Contents/MacOS/ecgtest
#	cp ecgtestMacIcons.icns AnotherResource.txt ecgtest.app/Contents/Resources/
	./ecgtest.app/Contents/MacOS/ecgtest

ecgtest.app:
	-mkdir ecgtest.app    
	-mkdir ecgtest.app/Contents
	-mkdir ecgtest.app/Contents/MacOS
	-mkdir ecgtest.app/Contents/Resources
	-mkdir ecgtest.app/Contents/Resources/English.lproj

ecgtest: dsp/dsp.a driver/driver.a

dsp/dsp.a:
	cd dsp; make

driver/driver.a:
	cd driver; make

clean:
	rm -rf ecgtest ecgtest.app
	cd dsp; make clean
	cd driver; make clean