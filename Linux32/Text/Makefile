SRC_ROOT=../../Examples/Text
LDFLAGS=-L/usr/local/lib -losgText -losg -losgDB -losgViewer

text:	$(SRC_ROOT)/TextMain.cpp $(SRC_ROOT)/TextSG.cpp
	$(CXX) $(CFLAGS) $(LDFLAGS) $? -o $@

clean:
	-rm -f text

