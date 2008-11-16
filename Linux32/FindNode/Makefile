SRC_ROOT=../../Examples/FindNode
LDFLAGS=-L/usr/local/lib -losg -losgDB -losgViewer

findnode:	$(SRC_ROOT)/FindNodeMain.cpp
	$(CXX) $(CFLAGS) $(LDFLAGS) $? -o $@

clean:
	-rm -f findnode

