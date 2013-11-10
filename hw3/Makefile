CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =	object.o scene.o Transform.o RayTracer.o hw3.o

LIBS =	-lfreeimage

TARGET =	hw3

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
