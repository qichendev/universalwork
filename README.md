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
- Keep dependency tools and caches under a project-local `.deps/` directory so they can be removed together.

## Status

Project initialization only. The application and API integrations are not implemented yet.

## Repository

This is an independent repository, also included as the `packages/universalwork` Git submodule of [qichen](https://github.com/qichendev/qichen).

From the parent repository, initialize this submodule with:

```sh
git submodule update --init packages/universalwork
```

Commit and push application changes in this repository first, then commit the updated submodule pointer in the parent repository.
