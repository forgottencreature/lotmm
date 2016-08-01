CC=gcc
CXX=g++
RM=rm -f
EXE=Silica.exe

#These next flags will vary system to system, have to adjust to fit your system.
CPPFLAGS=-g -std=c++11 -IC:\Development\sfml\SFML-2.3.2\include -IC:\Development\sfml\sfgui\include -I'C:\Development\thor\include' -I'C:\Development\Box2D\include\Box2D'
LDFLAGS=-g  -std=c++11 -LC:\Development\sfml\SFML-2.3.2\lib -L'C:\Development\thor\lib' -LC:\Development\sfml\sfgui\lib -L'C:\Development\Box2D\lib'
LDLIBS=-lBox2D -lsfgui -lsfml-graphics -lsfml-window -lsfml-system  -lthor

#SRCS= $(shell find src/ -name '*.cpp')
SRCS= $(wildcard *.cpp)
OBJS=$(subst .cpp,.o,$(SRCS))

all: silica

silica: $(OBJS)
	$(CXX) $(LDFLAGS) -o $(EXE) $(OBJS) $(LDLIBS)

run: all
	$(EXE)

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) $(EXE)

