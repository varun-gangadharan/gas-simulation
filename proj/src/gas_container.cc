#include "gas_container.h"

#include "Histogram.h"
#include "Phase_Graph.h"

namespace idealgas {

using glm::vec2;

GasContainer::GasContainer(int width, int height, size_t particle_number) {
  width_ = width;
  height_ = height;
  particle_number_ = particle_number;
  temp_ = kStartingTemperature;
  left_wall_x_ = kContainerCoordinates;
  right_wall_x_ = width + kContainerCoordinates;
  top_wall_y_ = kContainerCoordinates;
  bottom_wall_y = height + kContainerCoordinates;
  int count = 1;
  for (int i = 0; i < particle_number_; i++) {
    double x_velocity = -2.5 + 5 * ((double) rand() / RAND_MAX);
    double y_velocity = -2.5 + 5 * ((double) rand() / RAND_MAX);
    if (count == kParticleTypeFirst) {
      particleList_.push_back(
          Particle(17, 10, glm::vec2(55, 150), glm::vec2(x_velocity, y_velocity), "red"));
    }
    if (count == kParticleTypeSecond) {
      particleList_.push_back(
          Particle(12, 6, glm::vec2(55, 150), glm::vec2(x_velocity, y_velocity), "blue"));
    }
    if (count == kParticleTypeThird) {
      particleList_.push_back(
          Particle(6, 2, glm::vec2(55, 150), glm::vec2(x_velocity, y_velocity), "white"));
    }
    if (count > kParticleTypeThird) {
      count = 0;
    }
    count++;
  }
}

void GasContainer::setTemp(bool direction) {
  if (direction == true) {
    temp_++;
  } else {
    temp_--;
  }
}

void GasContainer::setEnergy(bool direction) {
  if (direction == true) {
    energy_++;
  } else {
    energy_--;
  }
}

void GasContainer::Display() const {
  DrawBasicContainer();
  DrawHistograms();
  DrawPhaseGraphs();
}

void GasContainer::DrawBasicContainer() const{
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(vec2(left_wall_x_, top_wall_y_), vec2(right_wall_x_, bottom_wall_y)));
  ci::gl::drawString(std::string("Temperature: " + std::to_string(temp_ - 300)), vec2(left_wall_x_, bottom_wall_y + 15));
  ci::gl::drawString(std::string("Heat Energy: " + std::to_string(energy_)), vec2(left_wall_x_, bottom_wall_y + 30));
  for (Particle particle: particleList_) {
    particle.DrawParticle();
  }
  ci::gl::drawString(std::string("Average Speeds"), vec2(450, 250));
  ci::gl::drawString(std::string("Avg for Mass 1: " + std::to_string(avg_speed_one)), vec2(430, 290));
  ci::gl::drawString(std::string("Avg for Mass 2: " + std::to_string(avg_speed_two)), vec2(430, 310));
  ci::gl::drawString(std::string("Avg for Mass 3: " + std::to_string(avg_speed_three)), vec2(430, 330));
}

void GasContainer::DrawHistograms() const {
  idealgas::Histogram histogram(10, "red", particleList_);
  histogram.setHistogramPosition();
  histogram.DrawHistogram();
  idealgas::Histogram histogram2(6, "blue", particleList_);
  histogram2.setHistogramPosition();
  histogram2.DrawHistogram();
  idealgas::Histogram histogram3(2, "white", particleList_);
  histogram3.setHistogramPosition();
  histogram3.DrawHistogram();
}

void GasContainer::DrawPhaseGraphs() const {
  ci::gl::drawString(std::string("Heat Energies"), vec2(513, 760));
  ci::gl::drawString(std::string("Temps"), vec2(left_wall_x_, bottom_wall_y + 200));
  idealgas::Phase_Graph graphOne(10, "red", temp_, energy_, particleList_);
  graphOne.setGraphPosition();
  graphOne.DrawGraph();
  idealgas::Phase_Graph graphTwo(6, "blue", temp_, energy_, particleList_);
  graphTwo.setGraphPosition();
  graphTwo.DrawGraph();
  idealgas::Phase_Graph graphThree(2, "white", temp_, energy_, particleList_);
  graphThree.setGraphPosition();
  graphThree.DrawGraph();
}

void GasContainer::getAverageSpeeds(){
  int sumSpeedsOne = 0;
  int countOne = 0;
  int sumSpeedsTwo = 0;
  int countTwo = 0;
  int sumSpeedsThree = 0;
  int countThree = 0;
  for (Particle particle : particleList_) {
    if (particle.getMass() == kParticleMassFirst){
      sumSpeedsOne += particle.getSpeed();
      countOne++;
    }
    if (particle.getMass() == kParticleMassSecond){
      sumSpeedsTwo += particle.getSpeed();
      countTwo++;
    }
    if (particle.getMass() == kParticleMassThird){
      sumSpeedsThree += particle.getSpeed();
      countThree++;
    }
  }
  if (countOne > 0 && countTwo > 0 && countThree > 0) {
    avg_speed_one = sumSpeedsOne/countOne;
    avg_speed_two = sumSpeedsTwo/countTwo;
    avg_speed_three = sumSpeedsThree/countThree;
  }
}

void GasContainer::setGravity() {
  gravity = !gravity;
}

void GasContainer::adjustForTemp() {
  float temp_diff = temp_ - kStartingTemperature;
  if (temp_diff > 0) {
    temp_diff = (temp_diff * 0.000005);
    for (Particle &particle : particleList_) {
      if (particle.getVelocity()[0] > 0 && particle.getVelocity()[1] > 0) {
        particle.setVelocity(vec2(particle.getVelocity()[0] + sqrt(temp_diff), particle.getVelocity()[1] - sqrt(temp_diff)));

      }
      if (particle.getVelocity()[0] > 0 && particle.getVelocity()[1] < 0) {
        particle.setVelocity(vec2(particle.getVelocity()[0] + sqrt(temp_diff), particle.getVelocity()[1] + sqrt(temp_diff)));

      }
      if (particle.getVelocity()[0] < 0 && particle.getVelocity()[1] > 0) {
        particle.setVelocity(vec2(particle.getVelocity()[0] - sqrt(temp_diff), particle.getVelocity()[1] - sqrt(temp_diff)));

      }
      if (particle.getVelocity()[0] < 0 && particle.getVelocity()[1] < 0) {
        particle.setVelocity(vec2(particle.getVelocity()[0] - sqrt(temp_diff), particle.getVelocity()[1] + sqrt(temp_diff)));

      }
    }
  }
  if (temp_diff < 0) {
    temp_diff /= (temp_diff + 25);
    temp_diff *= -1;
    for (Particle &particle : particleList_) {
      if (particle.getVelocity()[0] > 0 && particle.getVelocity()[1] > 0) {
        particle.setVelocity(vec2(particle.getVelocity()[0] - (temp_diff), particle.getVelocity()[1] - (temp_diff)));
      }
      if (particle.getVelocity()[0] > 0 && particle.getVelocity()[1] < 0) {
        particle.setVelocity(vec2(particle.getVelocity()[0] - (temp_diff), particle.getVelocity()[1] + (temp_diff)));
      }
      if (particle.getVelocity()[0] < 0 && particle.getVelocity()[1] > 0) {
        particle.setVelocity(vec2(particle.getVelocity()[0] + (temp_diff), particle.getVelocity()[1] - (temp_diff)));
      }
      if (particle.getVelocity()[0] < 0 && particle.getVelocity()[1] < 0) {
        particle.setVelocity(vec2(particle.getVelocity()[0] + (temp_diff), particle.getVelocity()[1] + (temp_diff)));
      }
    }
  }
}

void GasContainer::AdvanceOneFrame() {
  checkCollisionWall();
  checkCollisionParticle();
  for (Particle &particle : particleList_) {
    if (gravity) {
      particle.setVelocity(vec2(particle.getVelocity()[0], particle.getVelocity()[1] + 0.08));
    }
    particle.changePosition();
  }
  adjustForTemp();
  adjustForEnergy();
  getAverageSpeeds();
}

void GasContainer::adjustForEnergy(){
  float to_multiply_ = energy_;
  if (to_multiply_ > 0) {
    to_multiply_ = (to_multiply_  * 0.000005);
    for (Particle &particle : particleList_) {
      if (particle.getVelocity()[0] > 0 && particle.getVelocity()[1] > 0) {
        particle.setVelocity(vec2(particle.getVelocity()[0] + sqrt(to_multiply_), particle.getVelocity()[1] - sqrt(to_multiply_)));

      }
      if (particle.getVelocity()[0] > 0 && particle.getVelocity()[1] < 0) {
        particle.setVelocity(vec2(particle.getVelocity()[0] + sqrt(to_multiply_), particle.getVelocity()[1] + sqrt(to_multiply_)));

      }
      if (particle.getVelocity()[0] < 0 && particle.getVelocity()[1] > 0) {
        particle.setVelocity(vec2(particle.getVelocity()[0] - sqrt(to_multiply_), particle.getVelocity()[1] - sqrt(to_multiply_)));

      }
      if (particle.getVelocity()[0] < 0 && particle.getVelocity()[1] < 0) {
        particle.setVelocity(vec2(particle.getVelocity()[0] - sqrt(to_multiply_), particle.getVelocity()[1] + sqrt(to_multiply_)));

      }
    }
  }
  if (to_multiply_ < 0) {
    to_multiply_ /= (to_multiply_ + 25);
    to_multiply_ *= -1;
    for (Particle &particle : particleList_) {
      if (particle.getVelocity()[0] > 0 && particle.getVelocity()[1] > 0) {
        particle.setVelocity(vec2(particle.getVelocity()[0] - (to_multiply_), particle.getVelocity()[1] - (to_multiply_)));
      }
      if (particle.getVelocity()[0] > 0 && particle.getVelocity()[1] < 0) {
        particle.setVelocity(vec2(particle.getVelocity()[0] - (to_multiply_), particle.getVelocity()[1] + (to_multiply_)));
      }
      if (particle.getVelocity()[0] < 0 && particle.getVelocity()[1] > 0) {
        particle.setVelocity(vec2(particle.getVelocity()[0] + (to_multiply_), particle.getVelocity()[1] - (to_multiply_)));
      }
      if (particle.getVelocity()[0] < 0 && particle.getVelocity()[1] < 0) {
        particle.setVelocity(vec2(particle.getVelocity()[0] + (to_multiply_), particle.getVelocity()[1] + (to_multiply_)));
      }
    }
  }
}

void GasContainer::checkCollisionWall(){
    for (Particle &particle : particleList_) {
    if (checkHorizontalWall(particle)) {
        particle.setVelocity(vec2(-1 * particle.getVelocity()[0], particle.getVelocity()[1]));
    }
    if (checkVerticalWall(particle)) {
      particle.setVelocity(vec2(particle.getVelocity()[0], -1 * particle.getVelocity()[1]));
    }
  }
}

/**
 * loops through list of particles in simulation and checks if there are collisions between any two particles
 * then updates velocities
 */
void GasContainer::checkCollisionParticle() {
  for (Particle &first_particle: particleList_) {
    for (Particle &second_particle: particleList_) {
      float distance_ = glm::distance(first_particle.getPosition(), second_particle.getPosition());
      float condition1_ = checkConditionHelper(first_particle, second_particle);
      float condition2_ = checkConditionHelper(second_particle, first_particle);
      if (distance_ < kParticleRadius * 2) {
        if (condition1_ < 0) {
          first_particle.setVelocity(first_particle.getVelocity()
                                     - ((2 * second_particle.getMass())/(first_particle.getMass() +
                                     second_particle.getMass())) * ((condition1_ / (distance_ * distance_))
                                      * (first_particle.getPosition() - second_particle.getPosition())));
          second_particle.setVelocity(second_particle.getVelocity()
                                      - ((2 * first_particle.getMass())/(second_particle.getMass() +
                                      first_particle.getMass())) * ((condition2_ / (distance_ * distance_))
                                       * (second_particle.getPosition() - first_particle.getPosition())));
        }
      }
    }
  }
}

bool GasContainer::checkHorizontalWall(Particle particle_) {
  if (((particle_.getPosition()[0] + kParticleRadius > right_wall_x_) && (particle_.getVelocity()[0] > 0))
      || ((particle_.getPosition()[0] - kParticleRadius < left_wall_x_) && (particle_.getVelocity()[0] < 0))) {
    return true;
  } else {
    return false;
  }
}


bool GasContainer::checkVerticalWall(Particle particle_) {
  if (((particle_.getPosition()[1] + kParticleRadius > bottom_wall_y)  && (particle_.getVelocity()[1] > 0))
      || ((particle_.getPosition()[1] - kParticleRadius < top_wall_y_) && (particle_.getVelocity()[1] < 0))) {
    return true;
  } else {
    return false;
  }
}

float GasContainer::checkConditionHelper(Particle particle1, Particle particle2) {
  return glm::dot((particle1.getVelocity() - particle2.getVelocity())
      , (particle1.getPosition() - particle2.getPosition()));
}

void GasContainer::setPostCollisionVelocity(Particle particle1, Particle particle2, float condition_input, float distance) {
  particle1.setVelocity(particle1.getVelocity()
               - ((condition_input / (distance * distance))
                  * (particle1.getPosition() - particle2.getPosition())));
}

float GasContainer::getAverageSpeed() {
  //return avg_speed_one;
  return 3;
}

}


// namespace idealgas
