# Raytracer In A Weekend 

### Description:

This is a basic implementation of a raytracer, as described in book 1 of the raytracer in a weekend.  The program will render an image comprised of a series of spheres with a few different textures.  It simulates light rays travelling from a camera into a scene, and how the light rays interact with the objects in the scene in order to produce realistic effects such as the reflection of light and color depending on the material that the object is made of. 

My primary goals for this project wer to write a program that functions from scratch, and to refresh myself on linear algebra topics through application.   A major opportunity for improvement for this program would be to parallelize the rendering function in an effort to process multiple lines simultaneously.  The rendering process is incredibly slow in it's current state.  This, along with the completion of the rest of the series, will be a challenge for a later date.

### Using the Program:
1. Clone the repository.
2. Ensure that CMake is installed and useable on your machine.
3. compile the program with make.
4. Run ./ImageGenerator >> image.ppm in the command line.

After some time, the program should produce the image.ppm file in this repository.  

### Credit: 
Raytracer In One Weekend (book 1): https://raytracing.github.io/books/raytracinginoneweekend.html
