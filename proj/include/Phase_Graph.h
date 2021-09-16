//
// Created by Varun Gangadharan on 3/22/21.
//

#ifndef IDEAL_GAS_PHASE_GRAPH_H
#define IDEAL_GAS_PHASE_GRAPH_H

#include "Particle.h"
namespace idealgas {
class Phase_Graph {
 public:
  /**
    * This constructor takes in attributes for the phase change graph
    * @param mass, temp, pressure, particleList
    */
  Phase_Graph(float mass, cinder::ColorT<float> color, float temp, float pressure, std::vector<Particle> particleList);

  /**
   * This is the method that overall draws all components of the phase change graph
   */
  void DrawGraph();


  /**
  * This is the helper method that sets up the position for graph
  */
  void setGraphPosition();

  /**
   * This is the helper method that updates the temperatures
   */
  void calcTemps();

  /**
   * Getter for X value for testing purposes
   */
  int getXValue();

  /**
   * Getter for Y value for testing purposes
   */
  int getYValue();

  /**
   * Getter for Fusion Temp for testing purposes
   */
  float getFusionTemp();

  /**
   * Getter for Vaporization Temp for testing purposes
   */
  float getVaporizationTemp();

 private:

  /**
   * This is the helper method that specifically draws lines for each phase change
   */
  void DrawLines();

  /**
   * This is the helper method that specifically draws the lines
   * and labels for setting up each graph
   */
  void SetUpGraph();

  const int kPositionOne = 85;

  const int kPositionTwo = 735;

  const int kPositionThree = 420;

  std::vector<Particle> particleList_;

  float temp_;

  float heat_energy;

  float max_energy;

  const float kStartingTemperature = 300;

  const float kMassOne = 10;

  const float kMassTwo = 6;

  const float kMassThree = 2;

  const int kXAxisLength = 280;

  const int kYAxisLength = 240;

  const int klabelAdjustmentXOne = 90;

  const int kAdjustment = 20;

  const int kLinesConstantOne = 60;

  const int kLinesConstantTwo = 54;

  const int kLinesConstantThree = 120;

  const int kLinesConstantFour = 108;

  const int kLinesConstantFive = 180;

  const int kLinesConstantSix = 240;

  const int kLinesConstantSeven = 280;

  const int kLinesConstantEight = 160;

  const int kLinesDivisor = 3;

  float mass_;

  cinder::ColorT<float> color_;

  float fusion_heat;

  float vaporization_heat;

  float temp_gap;

  int x_value_;

  int y_value_;

  int ranges;

};
}

#endif  // IDEAL_GAS_PHASE_GRAPH_H
