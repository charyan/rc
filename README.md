# Ray Caster demo made with SDL2
![Ray Caster screenshot](https://github.com/charyan/rc/raw/master/rc.png)

## Build instructions
First you will need to [install SDL2](https://wiki.libsdl.org/Installation)
```bash
git clone https://github.com/charyan/rc.git
cd rc/
make all
./rc
```
If you encouter the following error : `libSDL2-2.0.so.0: cannot open shared object file`
You need to add the path to the SDL2 lib with `export LD_LIBRARY_PATH="/usr/local/lib"`

## Player movement
Use `W` `A` `S` `D` to move. `Shift` to move faster. 
Use `Left arrow` `Right arrow` to rotate.
