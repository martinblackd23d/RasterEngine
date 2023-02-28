# RasterEngine
Application to rasterize multiple triangles and other primitives onto the screen.

Uses Windows API to create a window with a canvas, then send pixel data to that canvas.

The window creation code was almost entirely copied from the Windows API docs.

It utilizes the [ray casting algorithm](https://en.wikipedia.org/wiki/Point_in_polygon#Ray_casting_algorithm) to determine whether a point is inside a primitive or not, pixel by pixel.

This is mathematically more correct than scanline rendering, but is also more complicated and slower.

Limitations: it works pixel-by-pixel, utilizes only a single thread on the CPU and uses an inefficient algorithm.

Consequently, my next project, which was [procedural generation](https://github.com/martinblackd23d/ProceduralGeneration), I used OpenGL, even though that program used the same 2 dimensional pixel array to store the image.
