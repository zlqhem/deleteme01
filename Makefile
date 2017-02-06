CC := $(CROSS)gcc
CXX := $(CROSS)g++
OBJDUMP := $(CROSS)objdump

V1_CPP_SRCS := common.cpp 
V1_C_SRCS := v1.c mytimer.c

V2_CPP_SRCS := common.cpp 
V2_C_SRCS := v2.c mytimer.c

OPTIMIZE := -O2 
CFLAGS := -g -std=gnu99 $(OPTIMIZE)
CXXFLAGS := -std=gnu++11 -g $(OPTIMIZE)

LIBS := -lm 

V1_CPP_OBJS := $(V1_CPP_SRCS:.cpp=.o)
V1_C_OBJS :=   $(V1_C_SRCS:.c=.o)
V1_OBJS =      $(V1_CPP_OBJS) 
V1_OBJS +=     $(V1_C_OBJS)

V2_CPP_OBJS := $(V2_CPP_SRCS:.cpp=.o)
V2_C_OBJS :=   $(V2_C_SRCS:.c=.o)
V2_OBJS =      $(V2_CPP_OBJS) 
V2_OBJS +=     $(V2_C_OBJS)

all: v1.exe v2.exe 

v1.exe: $(V1_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	
v2.exe: $(V2_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	-rm -f v1.exe v2.exe $(V1_OBJS) $(V2_OBJS) *.s

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
	$(OBJDUMP) -s -D $@ > $@.s
