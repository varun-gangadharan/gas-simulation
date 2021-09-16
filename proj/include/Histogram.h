//
// Created by Varun Gangadharan on 3/22/21.
//

#ifndef IDEAL_GAS_HISTOGRAM_H
#define IDEAL_GAS_HISTOGRAM_H

#include "Particle.h"
namespace idealgas {
class Histogram {
 public:
  /**
   * This constructor takes in attributes for the Histogram
   * @param mass, color, particleList
   */
  Histogram(float mass, cinder::ColorT<float> color, std::vector<Particle> particleList);

  /**
   * This is the method that overall draws all components of the histogram
   */
  void DrawHistogram();

  /**
   * This is the method that gives the amount of particles that fall in a certain range
   * @param upper_bound_
   * @return int
   */
  int getFrequency(float upper_bound_);

  /**
   * This is a getter that returns the X value of histogram
   */
  int getXValue();

  /**
   * This is a getter that returns the Y value of histogram
   */
  int getYValue();

  /**
   * This is a getter that returns the max speed of histogram
   */
  float getMaxSpeed();

  /**
   * This is a getter that returns the min speed of histogram
   */
  float getMinSpeed();

  /**
  * This is the helper method that sets up the position for histogram
  */
  void setHistogramPosition();

  /**
   * This is the helper method that updates the max speed
   */
  void updateSpeeds();

 private:

  /**
   * This is the helper method that specifically draws each bar for a histogram
   * @param upper_bound_
   */
  void DrawRectangle(float upper_bound_);

  /**
   * This is the helper method that specifically draws the lines
   * and labels for setting up each histogram
   */
  void SetUpHistogram();

  const int kHeight = 70;

  std::vector<Particle> particleList_;

  cinder::ColorT<float> color_;

  const int kBarWidth = 10;

  const float kMassOne = 10;

  const float kMassTwo = 6;

  const float kMassThree = 2;

  //const int kXPositionOne = 650;

  //const int kXPositionTwo = 100;

  //const int kYPositionOne = 760;

  //const int kYPositionTwo = 310;

  const int kXAxisLength = 100;

  const int kYAxisLength = 86;

  const int klabelAdjustmentXOne = 30;

  const int klabelAdjustmentXTwo = 70;

  const int klabelAdjustmentYOne = 6;

  const int klabelAdjustmentYTwo = 43;

  float mass_;

  float increment = 0.5;

  int x_value_;

  int y_value_;

  int ranges;

  float min_speed_ = 50;

  float max_speed_ = 1;

};
}

#endif  // IDEAL_GAS_HISTOGRAM_H
