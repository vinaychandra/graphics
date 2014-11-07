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
	rm -rf capture
	rm -f transformers.avi

video:
	cd capture; \
	mogrify -flip -format jpg frame_*.ppm; \
	mencoder mf://*.jpg -mf w=800:h=600:fps=25:type=jpg -ovc lavc -lavcopts vcodec=mpeg4:mbd=2:trell -oac copy -o ../transformers.avi
