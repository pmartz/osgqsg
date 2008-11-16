SRC_ROOT=../../Examples/Simple
LDFLAGS=-L/usr/local/lib -losg -losgDB -losgViewer

simple:	$(SRC_ROOT)/SimpleMain.cpp $(SRC_ROOT)/SimpleSG.cpp
	$(CXX) $(CFLAGS) $(LDFLAGS) $? -o $@

clean:
	-rm -f simple

