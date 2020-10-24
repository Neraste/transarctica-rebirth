# Transarctica Rebirth

This project is a fanmade rebuild of the Transarctica game, developed by Silmarils in 1993.

### Dependencies

The game uses the following dev dependencies:

- Boost (≥ 1.66);
- CMake (≥ 3.9);
- Doxygen (≥ 1.8).

### Build the project

The project uses CMake for building:

```sh
mkdir build
cd build
cmake ..
make
```

### Run tests

Tests are built by default.
The project uses CTest for running tests:

```sh
cd build
ctest -V # increase verbosity
```

### Generate documentation

The project uses Doxygen for generating the documentation:

```sh
cd build
make doc
xdg-open doc/index.html
```
