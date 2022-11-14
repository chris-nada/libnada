# nadalib

## *User friendly C++ library for everyday basic needs*
+ string manipulation
+ random number generation
+ ini (config) file reading/writing
+ basic logging
+ file system

## How to include in your project
1. Git clone or copy folder `libnada` to the same directory your `CMakeLists.txt` is in.
2. Add these 3 lines to your `CMakeLists.txt`
```cmake
    ...
    add_subdirectory(libnada)
    ...
    include_directories(libnada/include)
    ...
    target_link_libraries(PROJECT_NAME PRIVATE nada)
    ...
```
## How to Use
TODO
