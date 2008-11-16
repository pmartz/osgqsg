SRC_ROOT=../../Examples/Callback
LDFLAGS=-L/usr/local/lib -losg -losgDB -losgViewer

callback:	$(SRC_ROOT)/CallbackMain.cpp
	$(CXX) $(CFLAGS) $(LDFLAGS) $? -o $@

clean:
	-rm -f callback

