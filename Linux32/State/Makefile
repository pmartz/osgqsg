SRC_ROOT=../../Examples/State
LDFLAGS=-L/usr/local/lib -losg -losgDB -losgViewer

state:	$(SRC_ROOT)/StateMain.cpp $(SRC_ROOT)/StateSG.cpp
	$(CXX) $(CFLAGS) $(LDFLAGS) $? -o $@

clean:
	-rm -f state

