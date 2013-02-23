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

.PHONY: all clean