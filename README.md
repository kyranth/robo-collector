# Robo-Collector

## Directory Structure

```text
├── .github                 configuration GitHub Actions and other GitHub features
├── .vscode                 configuration for Visual Studio Code
├── bin                     the executable (created by make)
├── build                   intermediate build files e.g. *.o (created by make)
├── docs                    documentation
├── include                 header files
├── lib                     third-party libraries
├── src                     C source files
│   ├── main.cpp            (main) Entry point for the CLI
│   └── *.cpp
├── tests                   contains tests
├── .gitignore
├── LICENSE
├── Makefile
└── README.md               this file
```

## External Libraries

- [IRremote](https://github.com/Arduino-IRremote/Arduino-IRremote?tab=readme-ov-file#why-hpp-instead-of-cpp)
- [HCSR04](https://github.com/gamegine/HCSR04-ultrasonic-sensor-lib)
