SRC_ROOT=../../Examples/Lighting
LDFLAGS=-L/usr/local/lib -losg -losgDB -losgViewer

lighting:	$(SRC_ROOT)/LightingMain.cpp $(SRC_ROOT)/LightingSG.cpp
	$(CXX) $(CFLAGS) $(LDFLAGS) $? -o $@

clean:
	-rm -f lighting

