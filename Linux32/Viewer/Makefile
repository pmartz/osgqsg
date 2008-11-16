SRC_ROOT=../../Examples/Viewer
LDFLAGS=-L/usr/local/lib -losg -losgDB -losgViewer

viewer:	$(SRC_ROOT)/ViewerMain.cpp
	$(CXX) $(CFLAGS) $(LDFLAGS) $? -o $@

clean:
	-rm -f viewer

