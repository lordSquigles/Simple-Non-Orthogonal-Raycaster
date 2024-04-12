# Simple-Non-Orthogonal-Raycaster
An incredibly simple, non-orthogonal raycaster engine in C++

![raycastDemo](./raycastDemo.gif)

## Raycaster
  This 2.5D graphics engine is a raycaster. I wasn't sure entirely how a non-grid-based raycaster might be approached, so this is my unique stab at it. It uses line intersections (standard-form linear algebra) to determine if a ray hit a wall. This provides near-perfect floating-point accuracy for distances between the player and each point along the wall. Because the ray distances are not determined by incrementing and checking for a wall-hit, there are no limitations for draw-distance. The engine can draw player view-rays to any length without slowdown. I have also implemented small debugging features including a top-down minimap view shown by pressing "m" and a simple debugging stat overlay shown by pressing "/." The map is hardcoded, but could be adapted for implementation in a map file.
  
## Features
  This raycaster features light debugging tools and a minimap. It was more meant to teach myself 2.5D rendering than it is a complete product. My design, however, includes horizontal as well as vertical look (y-shearing) with the arrow keys and full "wasd" character movement, a map and distance-based lighting system, multi-height and multi-color walls, etc.
  
![raycastDebugDemo](./raycastDebugDemo.gif)
  
## Graphics
  I use the SDL library to output a frame buffer to the screen as a texture. I tried to make it as portable as possible by not utilizing any SDL-specific methods except those done to put the image on screen. All visuals are entirely software-rendered.
  
## Libraries
The libraries used are:
- [SDL](https://www.libsdl.org/download-2.0.php)
- [STB Image Loader](https://github.com/nothings/stb)
  
## Resources
  Check out [ssloy's](https://github.com/ssloy) [tinyracaster project](https://github.com/ssloy/tinyraycaster).

## Notes
  This was an educational project for myself.
