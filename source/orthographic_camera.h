// Orthographic camera class.

#ifndef ORTHOGRAPHIC_CAMERA_H_
#define ORTHOGRAPHIC_CAMERA_H_

#include "raycast.h"

class OrthographicCamera : public Camera {


public:

  Vec3f direction;
  Vec3f up;
  Vec3f centre;
  Vec3f horizontal;
  float size;

  // Constructor.
  OrthographicCamera(Vec3f centre, Vec3f direction, Vec3f up, float size);

  // Destructor
  ~OrthographicCamera();

  // Concrete implementation of pure virtual function in the
  // parent class.
  virtual Ray generateRay(Vec2f point);

};

#endif /* ORTHOGRAPHIC_CAMERA_H_ */
