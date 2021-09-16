//
// Created by Varun Gangadharan on 3/16/21.
//

#include "Particle.h"

#include "cinder/gl/gl.h"

using glm::vec2;

namespace idealgas{

Particle::Particle(float radius, float mass, vec2 position, vec2 velocity, cinder::ColorT<float> color) {
  if (position[0] < 0  || position[1] < 0 || mass < 0) {
    throw std::invalid_argument("Invalid position input");
  }
  radius_ = radius;
  mass_ = mass;
  position_ = position;
  velocity_ = velocity;
  color_ = color;
}
void Particle::changePosition() {
  position_ += velocity_;
}
glm::vec2 Particle::getPosition(){
  return position_;
}
glm::vec2 Particle::getVelocity(){
  return velocity_;
}
float Particle::getSpeed(){
  return glm::length(velocity_);
}
float Particle::getMass(){
    return mass_;
}
void Particle::setPosition(glm::vec2 position_input){
    position_ = position_input;
}
void Particle::setVelocity(glm::vec2 velocity_input){
  velocity_ = velocity_input;
}
void Particle::DrawParticle() const {
  ci::gl::color(ci::Color(color_));
  ci::gl::drawSolidCircle(position_,radius_);
}
}
