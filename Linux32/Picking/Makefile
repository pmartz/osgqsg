SRC_ROOT=../../Examples/Picking
LDFLAGS=-L/usr/local/lib -losg -losgDB -losgViewer

picking:	$(SRC_ROOT)/PickingMain.cpp 
	$(CXX) $(CFLAGS) $(LDFLAGS) $? -o $@

clean:
	-rm -f picking

