CC      = clang++
LD      = clang++

CFLAGS  = -Wall -std=c++11 -x c++ -O2 -I. -c

LDFLAGS = -lm

INCS = hit.h image.h ray.h scene_parser.h vectors.h \
	object3d.h group.h camera.h orthographic_camera.h

OBJS =	$(patsubst %.cc, %.o, $(wildcard *.cc))

all: raycast

clean:
	rm -rf $(OBJS) raycast

%.o: %.cc Makefile
	$(CC) $(CFLAGS) $< -o $@

raycast: $(OBJS)
	$(LD) $(OBJS) -o raycast $(LDFLAGS)

test: all
	rm -rf *.ppm
	./raycast -input ../scenes/scene1.txt -size 200 200 -output scene1.ppm -depth 9 10 depth1.ppm
	./raycast -input ../scenes/scene2.txt -size 200 200 -output scene2.ppm -depth 8 12 depth2.ppm
	./raycast -input ../scenes/scene3.txt -size 200 200 -output scene3.ppm -depth 8 12 depth3.ppm
	./raycast -input ../scenes/scene4.txt -size 200 200 -output scene4.ppm -depth 13 16 depth4.ppm
	./raycast -input ../scenes/scene5.txt -size 300 300 -output scene5.ppm -depth 1 7 depth5.ppm

.PHONY: all clean