CC=clang++
CFLAGS=-I/Users/jack/Documents/third_party/glad/include

glfwmain: src/main.cpp src/glad.cpp
	$(CC) -o bin/glfwmain.out src/main.cpp src/glad.cpp -lglfw $(CFLAGS)
