//
// Created by Varun Gangadharan on 3/22/21.
//

#include "Histogram.h"

#include "Particle.h"
#include "cinder/gl/gl.h"

using glm::vec2;

namespace idealgas{
/**
   * This is the constructor for the histogram class that sets up particle list, mass, and color
   * variables while also setting up the position for histogram in question
   * @param mass, color, particleList
   */
Histogram::Histogram(float mass, cinder::ColorT<float> color, std::vector<Particle> particleList) {
  if (mass < 0 ) {
    throw std::invalid_argument("Invalid position input");
  }
  particleList_ = particleList;
  mass_ = mass;
  color_ = color;
}

/**
   * This is a getter method for the X value for testing purposes
   */
int Histogram::getXValue() {
  return x_value_;
}

/**
   * This is a getter method for the Y value for testing purposes
   */
int Histogram::getYValue() {
  return y_value_;
}

/**
   * This is a getter method for the max speed for testing purposes
   */
float Histogram::getMaxSpeed() {
  return max_speed_;
}

/**
   * This is a getter method for the min speed for testing purposes
   */
float Histogram::getMinSpeed() {
  return min_speed_;
}

/**
   * This is a helper that sets up the X and Y coordinates for the histogram depending on particle mass
   */
void Histogram::setHistogramPosition() {
  if (mass_ == kMassOne) {
    x_value_ = 600;
    y_value_ = 200;
  }
  if (mass_ == kMassTwo) {
    x_value_ = 850;
    y_value_ = 200;
  }
  if (mass_ == kMassThree) {
    x_value_ = 725;
    y_value_ = 350;
  }
}

/**
   * This is the main method that puts together all components of the histogram and draws it completely
   */
void Histogram::DrawHistogram() {
  updateSpeeds();
  SetUpHistogram();
  float upper_bound_ = x_value_ + increment;
  for (ranges = 0; ranges < (max_speed_ / increment) + 1; ranges++ ) {
    DrawRectangle(upper_bound_);
    upper_bound_+= increment + kBarWidth;
  }
}

/**
   * This is a helper drawing method that sets up the basis for each histogram such as the lines and labels
   */
void Histogram::SetUpHistogram() {
  ci::gl::color(ci::Color("grey"));
  ci::gl::drawLine(vec2(x_value_,y_value_ - kYAxisLength), vec2(x_value_, y_value_));
  ci::gl::drawLine(vec2(x_value_,y_value_), vec2(x_value_ + kXAxisLength, y_value_));
  ci::gl::color(color_);
  ci::gl::drawString(std::string("Histogram for Mass: " + std::to_string(mass_).substr(0,4)), vec2(x_value_ + klabelAdjustmentXOne - 30, y_value_ - 110));
  ci::gl::drawString(std::string("Speeds"), vec2(x_value_ + klabelAdjustmentXOne, y_value_ + klabelAdjustmentYOne));
  ci::gl::drawString(std::string("Frequencies"), vec2(x_value_ - klabelAdjustmentXTwo, y_value_ - klabelAdjustmentYTwo));
}

/**
   * This is the helper method that draws a rectangle for a specific range passed in by the upper bound
   * @param upper_bound_
   */
void Histogram::DrawRectangle(float upper_bound_) {
  ci::gl::color(color_);
  ci::gl::drawSolidRect(ci::Rectf(vec2((upper_bound_ - increment), y_value_ - kHeight - (getFrequency(upper_bound_))),
                                  vec2(upper_bound_ + kBarWidth, y_value_ - 1)));
}

/**
   * This is the helper method that updates the max speed of all particles tested so as to
   * constantly update the ranges of the histograms
   */
void Histogram::updateSpeeds() {
  for (Particle particle : particleList_) {
    if (particle.getMass() == mass_ && particle.getSpeed() > max_speed_) {
      max_speed_ = particle.getSpeed();
    }
    if (particle.getMass() == mass_ && particle.getSpeed() < min_speed_) {
      min_speed_ = particle.getSpeed();
    }
  }
}

/**
   * This is the helper method that returns the number of particles that fall in a passed in range
   * @param upper_bound_
   * @return int that is the number of particles that fall in said range
   */
int Histogram::getFrequency(float upper_bound_) {
  float toCheck = upper_bound_ - x_value_ - (kBarWidth * ranges);
  int toReturn = 0;
  for (Particle particle : particleList_) {
    if (particle.getSpeed() > (toCheck - increment) && particle.getSpeed() <= toCheck && particle.getMass() == mass_){
      toReturn++;
    }
  }
  return toReturn;
}
}
