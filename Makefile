LDFLAGS=
OPENCVFLAGS=`pkg-config opencv --libs`
SRCFILES=`ls src/*.cpp`
EXENAME=build/eyes

all: compile
	@echo "USAGE: eyes"
clean:
	@echo "Clean old files"
	@rm -r -f $(EXENAME) build dist
compile: clean
	@echo "Compile from sources"
	mkdir -p build dist
	@g++ $(SRCFILES) $(LDFLAGS) $(OPENCVFLAGS) -o $(EXENAME)
	@strip $(EXENAME)
package: compile
	@echo "Package"
	cp $(EXENAME) dist/
compile-dev:
	@echo "Compile from sources development version"
	@g++ $(SRCFILES) $(LDFLAGS) -o $(EXENAME)
requirements:
	@echo "Install requirement libriries"
	@sudo apt-get -y install libopencv-dev libopencv-highgui-dev libopencv-objdetect-dev libopencv-imgproc-dev
