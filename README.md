# C++ coroutine Classes for universal use

## Description

This project contains classes that make the use of C++-coroutines very easy. The focused classes are ```CoTask``` and ```CoGenerator```.
A few [examples](/examples) demonstrate how they can be used.
All classes are template classes. This enables universal use.

## Class structure

![class structure](/classes.svg)

## Requirements

- cmake (> 3.14)
- C++ compiler with C++20-Standard and Coroutine-Support

## Compiling

```
cmake -B build -S
cd build
cmake --build .
```

## License

[BSD-3-Clause license](/LICENSE)
