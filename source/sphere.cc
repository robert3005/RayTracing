#include "raycast.h"

Sphere::Sphere() {

}

Sphere::Sphere(Vec3f centre, float radius, Vec3f colour) {
  this->centre = centre;
  this->radius = radius;
  this->colour = colour;
}

Sphere::~Sphere() {}

// Find intersection between this object and ray
// In general there can be up to two solutions and we want to reduce the one closer to the screen
// i.e. has smaller distance
bool Sphere::intersect(const Ray &r, Hit &h) {
  Vec3f d = r.getDirection();
  Vec3f orig = r.getOrigin();
  Vec3f deltaP = orig - this->centre;
  float modifier = pow(d.Dot3(deltaP),2) - deltaP.Dot3(deltaP) + pow(radius,2);
  if(modifier < 0) {
    return false;
  }
  modifier = sqrt(modifier);
  float termOne = -d.Dot3(deltaP);
  float u1 = termOne + modifier;
  float u2 = termOne - modifier;
  float smaller = min(u1, u2);
  if(smaller < h.getT()) {
    h.set(smaller, this->colour);
  }
  return true;
}
