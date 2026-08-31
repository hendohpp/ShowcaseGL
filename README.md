# ShowcaseGL

## building

TODO: clean this section up for finalized release

building the debug version:

```sh
cmake --preset debug
cmake --build --preset debug
```

running tests:

```sh
ctest --preset debug
```

running clang-tidy and clang-format

```sh
cmake --build build/debug --target tidy
cmake --build build/debug --target format
```

building the release verison

```
cmake --preset release
cmake --build --preset release