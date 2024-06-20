CC = g++
CPPFLAGS = -ggdb -Wall -pedantic
LD = g++
LDFLAGS = -ggdb
SRCS = main.cpp image.cpp
FINAL_TARGET = image.exe

default: $(FINAL_TARGET)

$(FINAL_TARGET): $(SRCS:%.cpp=%.o)
	$(LD) $+ -o $@ $(LDFLAGS) -L. -limagebmp_mingw64

%.o: %.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@

clean:
	del *.o $(FINAL_TARGET)

