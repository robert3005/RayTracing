#include "raycast.h"

// Globals:

// File names
char *_inputName       = nullptr;
char *_outputNameRGB   = nullptr;
char *_outputNameDepth = nullptr;

// Image parameters.
int _width      = 100;
int _height     = 100;
float _depthMin = 0;
float _depthMax = 1;

// Render a color image of objects in a scene.
void renderRGBImage(SceneParser &, Image &);

// Render an image showing the depth of objects from the camera.
void renderDepthImage(SceneParser &, Image &);

int main(int argc, char** argv) {

  int i;
  // sample command lines:
  // raycast -input input.txt -size 100 100 -output output.ppm
  // raycast -input input.txt -size 100 100 -depth 5.5 8.8 output.ppm

  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-input") == 0) {
      i++;assert (i < argc);
      _inputName = argv[i];
    } else if (strcmp(argv[i], "-size") == 0) {
      i++;assert (i < argc);
      _width = atoi(argv[i]);
      i++;assert (i < argc);
      _height = atoi(argv[i]);
    } else if (strcmp(argv[i], "-output") == 0) {
      i++;assert (i < argc);
      _outputNameRGB = argv[i];
    } else if (strcmp(argv[i], "-depth") == 0) {
      i++;assert (i < argc);
      _depthMin = atof(argv[i]);
      i++;assert (i < argc);
      _depthMax = atof(argv[i]);
      i++;assert (i < argc);
      _outputNameDepth = argv[i];
    } else {
      printf(
          "Error with command line argument %d: '%s'\n",
          i, argv[i]);
      assert(0);
    }
  }

  // Read in the scene description file, parsing the objects,
  // camera details, etc.
  SceneParser scene(_inputName);

  // Color and depth images.
  Image rgbImage(_width, _height);
  Image depthImage(_width, _height);

  // Do the rendering.
  renderRGBImage(scene, rgbImage);
  renderDepthImage(scene, depthImage);

  // Write results if necessary.
  if (_outputNameRGB != nullptr) {
    rgbImage.SavePPM(_outputNameRGB);
  }

  if (_outputNameDepth != nullptr){
    depthImage.SavePPM(_outputNameDepth);
  }

}

// Render a color image of objects in a scene.
void renderRGBImage(SceneParser &scene, Image &image) {
  Group * objGroup       = scene.getGroup();
  Camera * sceneCamera   = scene.getCamera();
  Vec3f backgroundColour = scene.getBackgroundColor();
  float h = image.Height();
  float w = image.Width();
  Hit hit(numeric_limits<float>().max(), backgroundColour);
  for(int y = 0; y < h; y++) {
    for(int x = 0; x < w; x++) {
      Vec2f v(x / w, (h - y - 1) / h);
      Ray r = sceneCamera->generateRay(v);
      objGroup->intersect(r, hit);
      image.SetPixel(x, y, hit.getColor());
      hit.set(numeric_limits<float>().max(), backgroundColour);
    }
  }
}

Vec3f distanceToColour(float t) {
  Vec3f colour;
  if(t <= _depthMin) {
    t = _depthMin;
  } else if (t >= _depthMax) {
    t = _depthMax;
  }

  float component = 1 - (t - _depthMin)/(_depthMax - _depthMin);
  colour.Set(component, component, component);
  return colour;
}

// Render an image showing the depth of objects from the camera.
void renderDepthImage(SceneParser &scene, Image &image) {
  Group * objGroup       = scene.getGroup();
  Camera * sceneCamera   = scene.getCamera();
  Vec3f backgroundColour = scene.getBackgroundColor();
  float h = image.Height();
  float w = image.Width();
  Hit hit(numeric_limits<float>().max(), backgroundColour);
  for(int y = 0; y < h; y++) {
    for(int x = 0; x < w; x++) {
      Vec2f v(x / w, (h - y - 1) / h);
      Ray r = sceneCamera->generateRay(v);
      objGroup->intersect(r, hit);
      Vec3f colour = distanceToColour(hit.getT());
      image.SetPixel(x, y, colour);
      hit.set(numeric_limits<float>().max(), backgroundColour);
    }
  }
}
