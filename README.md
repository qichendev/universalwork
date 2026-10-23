# UniversalWork

A local-first desktop AI agent built with Qt.

UniversalWork aims to provide a personal AI workspace where users connect their own DeepSeek and Tavily API keys. Local-first describes the application's storage and workspace model; model inference and web search use external API services.

## Planned capabilities

- Native desktop interface built with Qt 6 and C++.
- DeepSeek API integration for AI conversations and agent tasks.
- Tavily API integration for web search.
- User-provided API keys, configured in the application.
- Local conversation history, settings, and workspace data.

API keys should be stored using the operating system's credential store, excluded from logs, and never committed to Git. Network requests should send only the context needed for the requested operation.

## Development direction

- CMake for application builds.
- Conan 2 for dependencies, preferring published binary packages.
- Dependency installation must use `--build=never`; missing binaries should fail without compiling dependencies from source.
- Keep dependency tools and caches under a project-local `.deps/` directory by default. An explicit shared `CONAN_HOME` can avoid duplicate downloads across local projects.

## Build and run on macOS ARM64

The initial GUI uses **Qt Widgets**, C++17, CMake 3.23+ and Conan 2.33.0. Qt 6.11.1 and resolved recipe revisions are pinned in `conanfile.txt` and `conan.lock`. No custom Python scripts are required; Python is only needed to run Conan.

For an isolated setup, run from this repository:

```sh
python3 -m venv .deps/tools/conan
.deps/tools/conan/bin/python -m pip install --no-cache-dir --only-binary=:all: conan==2.33.0
export CONAN_HOME="$PWD/.deps/conan"
.deps/tools/conan/bin/conan profile detect
.deps/tools/conan/bin/conan install . \
  -pr:h profiles/macos-arm64 \
  --build=never \
  --output-folder=build/conan

cmake -S . -B build/conan \
  -DCMAKE_TOOLCHAIN_FILE="$PWD/build/conan/conan_toolchain.cmake" \
  -DCMAKE_BUILD_TYPE=Release
cmake --build build/conan --config Release
```

To run the development app, start a subshell with Conan's Qt plugin paths. Remove the generated loader overrides on macOS: the executable already has development RPATHs, and the overrides can cause system tools to load incompatible libraries.

```sh
(
  source build/conan/conanrun.sh
  unset DYLD_LIBRARY_PATH LD_LIBRARY_PATH
  ./build/conan/UniversalWork.app/Contents/MacOS/UniversalWork
)
```

To verify GUI initialization without leaving a window open:

```sh
(
  source build/conan/conanrun.sh
  unset DYLD_LIBRARY_PATH LD_LIBRARY_PATH
  ctest --test-dir build/conan --output-on-failure
)
```

`profiles/macos-arm64` targets Apple Clang 17 and Release. It selects the published Clang 13 build **only for libffi**, a transitive C library; it does not install an old compiler or change the application compiler. This is an explicit binary selection for this tested environment, not a general guarantee of compatibility across compiler versions. Other platforms need their own validated profiles and available binaries. Never replace `--build=never` with a source-build fallback.

If Conan is already installed, use that executable instead of creating another environment. To reuse existing packages, set `CONAN_HOME` to the absolute existing cache path before installation. Do not move or delete a shared cache while development builds still reference it. The source repository itself has no dependency on a sibling checkout.

The generated `.app` is a development build referencing the Conan cache. A standalone distribution still needs runtime-library/plugin collection, path correction, signing and deployment validation. The Core-only benchmark ZIP is not a deployment package for this Widgets application.

## Status

Conan/CMake configuration and a minimal Qt Widgets window are implemented. Both offscreen GUI initialization and the native macOS Cocoa startup check passed using cached binary dependencies, without compiling dependencies from source. The native startup check briefly shows the window and exits via `--smoke-test`.

The initial verification reused the existing `qt-dependency-benchmark` Conan environment and cache to conserve local disk space; a fresh isolated dependency download was not repeated. DeepSeek, Tavily, API-key entry/storage, agent execution and local history are not implemented yet.

## Repository

This is an independent repository, also included as the `packages/universalwork` Git submodule of [qichen](https://github.com/qichendev/qichen).

From the parent repository, initialize this submodule with:

```sh
git submodule update --init packages/universalwork
```

Commit and push application changes in this repository first, then commit the updated submodule pointer in the parent repository.
