#pragma once

#include "Particle.h"
#include "cinder/gl/gl.h"

using glm::vec2;

namespace idealgas {

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
class GasContainer {
 public:
  /**
   * This constructor takes in attributes for the container
   * @param width, height, particle_number
   */
  GasContainer(int width, int height, size_t particle_number);

  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display() const;

  /**
   * helper for display just with the basic container
   */
  void DrawBasicContainer() const;

  /**
   * helper for display just with histograms
   */
  void DrawHistograms() const;

  /**
  * helper for display just with phase change graphs
  */
  void DrawPhaseGraphs() const;

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

  /**
   * This  method sets gravity on or off based on user input
   */
  void setGravity();

  /**
   * This  method sets temperature based on user input
   */
  void setTemp(bool direction);

  /**
   * This  method sets pressure based on user input
   */
  void setEnergy(bool direction);
  /**
   * This  method gets average velocity for each particle
   */
  void getAverageSpeeds();

  std::vector<Particle> particleList_;

  /**
   * This helper method is for testing purposes, returns an avg speed
   * @return float
   */
   float getAverageSpeed();
 private:
  /**
   * This helper method adjusts velocities based on the temperature at the time
   */
  void adjustForTemp();
  /**
   * This helper method adjusts velocities based on the temperature at the time
   */
  void adjustForEnergy();
  /**
   * This helper method checks for wall collisions
   */
  void checkCollisionWall();
  /**
   * This helper method checks for particle collisions
   */
  void checkCollisionParticle();
  /**
   * This helper method checks for horizontal collisions
   * @param Particle
   * @return bool
   */
  bool checkHorizontalWall(Particle particle_);
  /**
   * This helper method checks for vertical collisions
   * @param Particle
   * @return bool
   */
  bool checkVerticalWall(Particle particle_);

  /**
   * This helper method checks for the condition for particle collisions
   * @param particle1, particle2
   * @return float
   */
  float checkConditionHelper(Particle particle1, Particle particle2);

  void setPostCollisionVelocity(Particle particle1, Particle particle2, float condition_input, float distance);


  const int kContainerCoordinates = 25;
  const int kParticleTypeFirst = 1;
  const int kParticleTypeSecond = 2;
  const int kParticleTypeThird = 3;
  const int kParticleMassFirst = 10;
  const int kParticleMassSecond = 6;
  const int kParticleMassThird = 2;
  const float kStartingTemperature = 300;
  const float kParticleRadius = 10.0;
  size_t width_;
  size_t height_;
  float temp_;
  float energy_;
  bool gravity = false;
  size_t particle_number_ = 100;
  int left_wall_x_;
  int right_wall_x_;
  int top_wall_y_;
  int bottom_wall_y;
  float avg_speed_one;
  float avg_speed_two;
  float avg_speed_three;

};

}  // namespace idealgas
