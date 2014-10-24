OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB) -lGLU
LDFLAGS=-L/usr/local/lib
CPPFLAGS=-I/usr/local/include

BIN=output
SRCS=transformer.cpp gl_framework.cpp scenery.cpp main.cpp
INCLUDES=gl_framework.hpp transformer.hpp scenery.hpp 



all: $(BIN)


$(BIN): $(SRCS) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(BIN)
	rm -f *.o
	rm -f *~
