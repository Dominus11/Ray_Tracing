# Ray Tracing 

This is an implementation of a ray-tracer, currently following the [Ray-Tracing In One Weekend(RTIOW)](https://raytracing.github.io/) book series. I was inspired by my courses [Intro To Graphics](https://www.cl.cam.ac.uk/teaching/2425/Graphics/) and [Further Graphics](https://www.cl.cam.ac.uk/teaching/2526/FGraphics/) and wanted to start coding up some of the concepts!

---

## How To Use

To build the renderer and get it to render the image shown beneath (the cover of RTIOW) to the file `image.ppm`, enter the project directory and run:

```bash
> make
> ./raytracer > image.ppm
```

For now, to create your own scenes, go into `main.cc` and edit the 'Scene Initialisation' part of the code. (I will improve the I/O soon!)

---

## Upcoming Extensions

Some extensions I would like to try:

- Book 2 (notably distribution over time, light sources and BVH)
- Book 3 (notably the content on importance sampling for indirect illumination)
- Improved user-facing I/O via the command-line
- Metal Acceleration
- Import geometries from other sources (libgl?)