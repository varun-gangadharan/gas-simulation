//
// Created by Varun Gangadharan on 3/16/21.
//

#ifndef IDEAL_GAS_PARTICLE_H
#define IDEAL_GAS_PARTICLE_H
#include "cinder/gl/gl.h"

namespace idealgas {
class Particle {
 public:
  Particle(float radius, float mass, glm::vec2 position, glm::vec2 velocity, cinder::ColorT<float> color);
  /**
   * This is a getter for the position vector
   * @return glm::vec2
   */
  glm::vec2 getPosition();
  /**
   * This is a getter for the velocity vector
   * @return glm::vec2
   */
  glm::vec2 getVelocity();
  /**
   * This is a getter for the speed
   * @return float
   */
  float getSpeed();
  void changePosition();
  /**
   * This is a setter for the position vector
   * @param position_input
   */
  void setPosition(glm::vec2 position_input);
  /**
   * This is a setter for the velocity vector
   * @param velocity_input
   */
  void setVelocity(glm::vec2 velocity_input);
  float getMass();
  void DrawParticle() const;

 private:
  //double gravity_val = -9.8;
  glm::vec2 position_;
  glm::vec2 velocity_;
  float radius_;
  float mass_;
  cinder::ColorT<float> color_;

};
}


#endif  // IDEAL_GAS_PARTICLE_H
