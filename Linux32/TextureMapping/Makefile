SRC_ROOT=../../Examples/TextureMapping
PROGRAM=TextureMappingMain
LDFLAGS=-L/usr/local/lib -losg -losgDB -losgViewer

texturemapping:	$(SRC_ROOT)/TextureMappingMain.cpp $(SRC_ROOT)/TextureMappingSG.cpp
	$(CXX) $(CFLAGS) $(LDFLAGS) $? -o $@

clean:
	-rm -f texturemapping

