//
// Created by Varun Gangadharan on 3/22/21.
//

#include "Phase_Graph.h"

#include "Particle.h"
#include "cinder/gl/gl.h"

using glm::vec2;

namespace idealgas{

Phase_Graph::Phase_Graph(float mass, cinder::ColorT<float> color, float temp, float heatEnergy, std::vector<Particle> particleList) {
  if (mass < 0 ) {
    throw std::invalid_argument("Invalid position input");
  }
  particleList_ = particleList;
  mass_ = mass;
  temp_ = temp;
  heat_energy = heatEnergy;
  color_ = color;
}


void Phase_Graph::DrawGraph() {
  calcTemps();
  setGraphPosition();
  DrawLines();
}

void Phase_Graph::setGraphPosition() {
  if (mass_ == kMassOne) {
    x_value_ = kPositionOne;
    y_value_ = kPositionTwo;
  }
  if (mass_ == kMassTwo) {
    x_value_ = kPositionThree;
    y_value_ = kPositionTwo;
  }
  if (mass_ == kMassThree) {
    x_value_ = kPositionTwo + kAdjustment;
    y_value_ = kPositionTwo;
  }
}




void Phase_Graph::DrawLines() {
  ci::gl::color(ci::Color("grey"));
  ci::gl::drawLine(vec2(x_value_,y_value_ - kYAxisLength), vec2(x_value_, y_value_));
  ci::gl::drawLine(vec2(x_value_,y_value_), vec2(x_value_ + kXAxisLength, y_value_));
  ci::gl::drawString(std::string("Phase Change Graph for Mass: " + std::to_string(mass_).substr(0,4)), vec2(x_value_ + klabelAdjustmentXOne - 30, y_value_ - kYAxisLength));
  ci::gl::color(color_);
  ci::gl::drawLine(vec2(x_value_,y_value_), vec2(x_value_ + kLinesConstantOne + fusion_heat/kLinesDivisor, y_value_ - kLinesConstantTwo));
  ci::gl::drawLine(vec2(x_value_ + fusion_heat/kLinesDivisor + kLinesConstantOne,y_value_ - kLinesConstantTwo ), vec2(x_value_ + fusion_heat/kLinesDivisor + kLinesConstantThree, y_value_ - kLinesConstantTwo));
  ci::gl::drawLine(vec2(x_value_ + fusion_heat/kLinesDivisor + kLinesConstantThree,y_value_ - kLinesConstantTwo), vec2(x_value_ + fusion_heat/kLinesDivisor + vaporization_heat/3 + kLinesConstantFive, y_value_ - kLinesConstantFour  - temp_gap/kLinesDivisor));
  ci::gl::drawLine(vec2(x_value_ + fusion_heat/kLinesDivisor + vaporization_heat/kLinesDivisor + kLinesConstantFive,y_value_ - kLinesConstantFour - temp_gap/kLinesDivisor), vec2(x_value_ + fusion_heat/kLinesDivisor + vaporization_heat/kLinesDivisor + kLinesConstantSix, y_value_ - kLinesConstantFour  - temp_gap/kLinesDivisor));
  ci::gl::drawLine(vec2(x_value_ + fusion_heat/kLinesDivisor + vaporization_heat/kLinesDivisor + kLinesConstantSix, y_value_ - kLinesConstantFour - temp_gap/kLinesDivisor), vec2(x_value_ + fusion_heat/kLinesDivisor + vaporization_heat/kLinesDivisor + kLinesConstantSeven, y_value_ - kLinesConstantEight  - temp_gap/kLinesDivisor));

}

void Phase_Graph::calcTemps() {
  if (heat_energy > max_energy) {
    max_energy = heat_energy;
  }
  temp_gap = temp_ - kStartingTemperature;
  fusion_heat = (mass_ * heat_energy) + temp_gap;
  vaporization_heat = (mass_ * heat_energy) + temp_gap;
}

int Phase_Graph::getXValue() {
  return x_value_;
}

int Phase_Graph::getYValue() {
  return y_value_;
}

float Phase_Graph::getFusionTemp() {
  return fusion_heat;
}

float Phase_Graph::getVaporizationTemp() {
  return vaporization_heat;
}

}
