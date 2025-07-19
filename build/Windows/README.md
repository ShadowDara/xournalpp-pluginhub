# Windows

**Container does not work yet !!!**

Continuing soon!


Docker Container to build for Windows

Run from the root of the Repository
```sh
docker build -f build/Windows/Dockerfile -t mein-windows-build .
```

Run the Container on Windows
```sh
docker run --rm -v "${PWD}\output:/app/build" mein-windows-build
```

DLLs
```sh
/usr/x86_64-w64-mingw32/sys-root/mingw/bin/*.dll
```
