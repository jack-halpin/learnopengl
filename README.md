# LearnOpenGL

Following the tutorials from www.learnopengl.com and learning some handy tools like vim and CMake
along the way!

## build
From the source directory

```
mkdir build
cd build
cmake -G Xcode ..
```

Worth noting that `GLFW` installed using homebrew doesn't seem to work with cmake as I would expect. 
However compiling the libraries manually and installing them using `make` allows it to work just fine.

