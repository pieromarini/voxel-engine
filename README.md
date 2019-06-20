# C++ Voxel Engine

## Build Dependencies ##
- [CMAKE](http://www.cmake.org/)
- [GLEW](http://glew.sourceforge.net/)
- [GLFW - Included in lib](https://www.glfw.org/)
- [OpenGL](https://www.opengl.org/)
- [SOIL](http://www.lonesock.net/soil.html)

## Build System ##
- Linux/MacOS -> cmake, make & g++ 
- Window -> Not yet tested/implemented.

### Basic Instructions ###
```shell
# Ubuntu
sudo apt install cmake libglew-dev

# Arch Linux
sudo pacman -S cmake glew

# MacOS
brew install cmake glew
```

### Running ###
```shell
# Compile
make

# Run
./run
```

### Current Features ###
- Chunk-Based Rendering System
- Atlas Texture System
- Face Culling
- Basic Raycasting (breaking/placing blocks)
