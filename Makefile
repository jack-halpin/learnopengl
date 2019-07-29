CC=clang++
CFLAGS=-I/Users/jack/Documents/third_party/glad/include

glfwmain: main.cpp glad.cpp
	$(CC) -o glfwmain main.cpp glad.cpp -lglfw $(CFLAGS)
