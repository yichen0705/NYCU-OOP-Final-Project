# NYCU-OOP-Final-Project

## Install CImg & libjpeg
```bash=
$ make install
```

## Compile the program
```bash=
$ make -j
```

### TODO
*   Finish Dataloader
*   Image_Processing class as base class and inherite by other image processing algorithm (operate on self)
*   Image operate with other image:
    *   concatenate (how to deal with not-match length)
    *   operator overloading