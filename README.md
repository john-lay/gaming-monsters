# Gaming monsters
Working through GBDK [tutorials](https://www.youtube.com/watch?v=HIsWR_jLdwo&list=PLeEj4c2zF7PaFv5MPYhNAkBGrkx4iPGJo) with GBDK 2020 [v3.2](https://github.com/Zal0/gbdk-2020/releases/tag/v3.2)

Edit VS Code `includePath` settings and add `C:\gbdk\include\**`

## Lesson 1
* [Hello world](https://github.com/john-lay/gaming-monsters/tree/master/lesson1)
* Writes hello world to the screen

## Lesson 2
* [Sprites](https://github.com/john-lay/gaming-monsters/tree/master/lesson2)
* Draws a sprite to screen and transforms the position to animate it off screen while flipping between 2 frames.
* sprites created with [GB Tile Designer](http://www.devrs.com/gb/hmgd/gbtd.html)

## Lesson 3
* [Joypad Inputs](https://github.com/john-lay/gaming-monsters/tree/master/lesson3)
* Moves a sprite around the screen using the d-pad

## Lesson 4
* [background tiles](https://github.com/john-lay/gaming-monsters/tree/master/lesson4)
* Draw a background and scroll across it
* Tiles created with [GB Map Builder](http://www.devrs.com/gb/hmgd/gbmb.html)

## ggbgfx (A variation on Lesson 4)
* [background tiles created with ggbgfx](https://github.com/john-lay/gaming-monsters/tree/master/ggbgfx)
* uses ggbgfx (`npm install -g ggbgfx-cli`) to create tileset and tile map from image
* Original `vision-henge.png` scene taken from https://github.com/john-lay/dmg-adventure
1. Generate a `png` tile-set from the original image with `ggbgfx tileset -o tileset.png .\vision-henge.png` This is the unique tiles used to build a scene
2. Transform this tileset image into a `.c` tiledata array with `ggbgfx tiledata -o tileset.c -n mytileset .\tileset.png`
3. Generate a tile-map using the tileset and the original image `ggbgfx tilemap -o tilemap.c -n mytilemap .\vision-henge.png .\tileset.png ` This is the scene data

## Lesson 5
* [Windows Layer](https://github.com/john-lay/gaming-monsters/tree/master/lesson5)
* Add a heads-up display along the bottom of the screen

## Lesson 6
* [Sound](https://github.com/john-lay/gaming-monsters/tree/master/lesson6)
* Play a jumping sound when any input is pressed

## Lesson 7
* [Noise](https://github.com/john-lay/gaming-monsters/tree/master/lesson7)
* Play a static scratching noise when any input is pressed

## Mix Assembly (asm) with C
* [mix](https://github.com/john-lay/gaming-monsters/tree/master/mixasmc)
* Call a function defined in assembly from c

## Lesson 8
* [Jumping](https://github.com/john-lay/gaming-monsters/tree/master/lesson8)
* Move a sprite left and right with a natural (gravity influencing) jump

## Lesson 9
* [Meta-sprites](https://github.com/john-lay/gaming-monsters/tree/master/lesson9)
* Combine multiple 8x8 sprites into larger sprites and move them together
