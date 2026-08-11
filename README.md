# Lys

## Setup

- clang++-21+
- Ninja
- CMake 4.3.1+*
- Vcpkg

**Note**: The minimum CMake version will change once `import std;` is no longer experimental!

```bash
git submodule update --init --recursive
```

### Linux

```bash
sudo apt install libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev
```

### macOS

WIP

## Repository licenses

| Repository                                           | License                                        |
|------------------------------------------------------|------------------------------------------------|
| [MAG](https://github.com/marcusgigandet/mag)         | Apache-2.0 ([LICENSE](vendor/mag/LICENSE))     |
| [Toolbox](https://github.com/marcusgigandet/toolbox) | Apache-2.0 ([LICENSE](vendor/toolbox/LICENSE)) |
| [spdlog](https://github.com/gabime/spdlog)           | MIT                                            |
| [GLFW](https://github.com/glfw/glfw)                 | Zlib                                           |

## License

This project is licensed under Apache-2.0. See the [LICENSE](LICENSE) file for details.
