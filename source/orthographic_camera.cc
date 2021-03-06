#include "raycast.h"

// Constructor with parameters.
OrthographicCamera::OrthographicCamera(Vec3f centre, Vec3f direction, Vec3f up, float size) {
  // Normalise up and direction vector
  this->direction = direction;
  this->centre = centre;
  this->size = size;
  // Store horizontal vector for further use
  Vec3f::Cross3(this->horizontal, direction, up);
  // Project up vector onto plane of which direction is a normal of
  Vec3f::Cross3(this->up, this->horizontal, direction);
  // Normalise all vectors
  this->up.Normalize();
  this->direction.Normalize();
  this->horizontal.Normalize();
}

OrthographicCamera::~OrthographicCamera() {}

Ray OrthographicCamera::generateRay(Vec2f point)
{
  Vec3f rayOrigin(this->centre);
  // Start from zero and move from there according to the point
  rayOrigin += this->up * this->size * (point[1] - 0.5) + this->horizontal * this->size * (point[0] - 0.5);
  Ray r(direction, rayOrigin);
  return r;
}
