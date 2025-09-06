# Raylib

## dependencies

`sudo pacman -S raylib`

## build

### linux
```bash
gcc ./src/*.c -o demo -lraylib -lm -ldl -lpthread -lGL -lrt -lX11
```

### windows
```bash
gcc ./src/*.c -o demo -IC:/raylib/include -LC:/raylib/lib -lraylib -lgdi32 -lwinmm
```
