#include "raycast.h"

// Constructor with parameters.
OrthographicCamera::OrthographicCamera(Vec3f centre, Vec3f direction, Vec3f up, float size) {
  // Normalise up and direction vector
  direction.Normalize();
  up.Normalize();
  this->direction = direction;
  this->centre = centre;
  this->size = size;
  // Project up vector onto plane of which direction is a normal of
  Vec3f projectedUp;
  Vec3f::Cross3(projectedUp, up, direction);
  Vec3f::Cross3(projectedUp, direction, projectedUp);
  this->up = projectedUp;
  // Store horizontal vector for further use
  Vec3f horizontal;
  Vec3f::Cross3(horizontal, projectedUp, direction);
  this->horizontal = horizontal;
}

OrthographicCamera::~OrthographicCamera() {}

Ray OrthographicCamera::generateRay(Vec2f point)
{
  Vec3f rayOrigin(this->centre);
  rayOrigin -= this->up * (this->size / 2) + this->horizontal * (this->size / 2);
  rayOrigin += this->up * this->size * point[1] + this->horizontal * this->size * point[0];
  Ray r(direction, rayOrigin);
  return r;
}
