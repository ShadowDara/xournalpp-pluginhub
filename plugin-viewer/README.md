# Xournalpp Pluigin Viewer

### TODO
- [ ] core/fetch.cpp, curl certifcat
- [ ] better UI
- [ ] refactor UI Code, it is very messy!
- [ ] add Software Icon

### Docker

to build the container
```sh
docker build -t gtk3-cpp .
```

to set the display
```sh
export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0.0
xhost +local:docker
```

start the container
````sh
docker run -it --rm \
  -e DISPLAY=$DISPLAY \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  -v $(pwd):/app \
  gtk3-cpp
```
