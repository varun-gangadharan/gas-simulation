#include <catch2/catch.hpp>

#include <gas_container.h>

using idealgas::GasContainer;
using idealgas::Particle;

TEST_CASE("Collision test") {

  SECTION("Moving towards each other") {
    GasContainer container = {400, 400, 0};
    container.particleList_.push_back(Particle(10, 10, glm::vec2(51, 50), glm::vec2(5, 0), "white"));
    container.particleList_.push_back(Particle(10, 10, glm::vec2(71, 50), glm::vec2(-5, 0), "white"));
    container.AdvanceOneFrame();
    REQUIRE(container.particleList_[0].getVelocity()[0] > 0);
  }
  SECTION("Moving away from each other") {
    GasContainer container = {400, 400, 0};
    container.particleList_.push_back(Particle(10, 10, glm::vec2(51, 50), glm::vec2(5, 0), "white"));
    container.particleList_.push_back(Particle(10, 10, glm::vec2(71, 50), glm::vec2(5, 0), "white"));
    container.AdvanceOneFrame();
    REQUIRE(container.particleList_[0].getVelocity()[0] > 0);
  }
  SECTION("Moving towards wall to right") {
    GasContainer container = {400, 400, 0};
    container.particleList_.push_back(Particle(10, 10, glm::vec2(98, 50), glm::vec2(10, 0), "white"));
    container.AdvanceOneFrame();
    REQUIRE(container.particleList_[0].getVelocity()[0] > 0);
  }
  SECTION("Moving towards wall to left") {
    GasContainer container = {400, 400, 0};
    container.particleList_.push_back(Particle(10, 10, glm::vec2(5, 50), glm::vec2(-10, 0), "white"));
    container.AdvanceOneFrame();
    REQUIRE(container.particleList_[0].getVelocity()[0] > 0);
  }
  SECTION("Moving towards wall up") {
    GasContainer container = {400, 400, 0};
    container.particleList_.push_back(Particle(10, 10, glm::vec2(16, 95), glm::vec2(0, 10), "white"));
    container.AdvanceOneFrame();
    REQUIRE(container.particleList_[0].getVelocity()[1] > 0);
  }
  SECTION("Moving towards wall down") {
    GasContainer container = {400, 400, 0};
    container.particleList_.push_back(Particle(10, 10, glm::vec2(16, 5), glm::vec2(0, -10), "white"));
    container.AdvanceOneFrame();
    REQUIRE(container.particleList_[0].getVelocity()[1] > 0);
  }
}


TEST_CASE("edge cases") {
  SECTION("Particle collision but they are not moving towards each other X") {
    GasContainer container = {100, 100, 0};
    container.particleList_.push_back(Particle(10, 10, glm::vec2(51, 50), glm::vec2(5, 0), "white"));
    container.particleList_.push_back(Particle(10, 10, glm::vec2(55, 50), glm::vec2(-5, 0), "white"));
    container.AdvanceOneFrame();
    REQUIRE(container.particleList_[0].getVelocity()[0] < 0);
    REQUIRE(container.particleList_[1].getVelocity()[0] > 0);
  }
  SECTION("Particle collision but they are not moving towards each other Y") {
    GasContainer container = {100, 100, 0};
    container.particleList_.push_back(Particle(10, 10, glm::vec2(55, 50), glm::vec2(0, -5), "white"));
    container.particleList_.push_back(Particle(10, 10, glm::vec2(55, 54), glm::vec2(0, 5), "white"));
    container.AdvanceOneFrame();
    REQUIRE(container.particleList_[0].getVelocity()[1] < 0);
    REQUIRE(container.particleList_[1].getVelocity()[1] > 0);
  }
  SECTION("wall collision but not moving towards wall right") {
    GasContainer container = {100, 100, 0};
    container.particleList_.push_back(Particle(10, 10, glm::vec2(95, 50), glm::vec2(-5, 0), "white"));
    container.AdvanceOneFrame();
    REQUIRE(container.particleList_[0].getVelocity()[0] < 0);
  }
  SECTION("wall collision but not moving towards wall left") {
    GasContainer container = {100, 100, 0};
    container.particleList_.push_back(Particle(10, 10, glm::vec2(5, 50), glm::vec2(5, 0), "white"));
    container.AdvanceOneFrame();
    REQUIRE(container.particleList_[0].getVelocity()[0] > 0);
  }
  SECTION("wall collision but not moving towards wall up") {
    GasContainer container = {100, 100, 0};
    container.particleList_.push_back(Particle(10, 10, glm::vec2(5, 95), glm::vec2(0, -5), "white"));
    container.AdvanceOneFrame();
    REQUIRE(container.particleList_[0].getVelocity()[1] < 0);
  }
  SECTION("wall collision but not moving towards wall down") {
    GasContainer container = {100, 100, 0};
    container.particleList_.push_back(Particle(10, 10, glm::vec2(0, 5), glm::vec2(0, 5), "white"));
    container.AdvanceOneFrame();
    REQUIRE(container.particleList_[0].getVelocity()[1] > 0);
  }
}

TEST_CASE("making sure speed is properly affected by temp and energy changes") {
  SECTION("checking when temp increases") {
    GasContainer container = {100, 100, 0};
    container.particleList_.push_back(
        Particle(10, 10, glm::vec2(0, 5), glm::vec2(0, 5), "white"));
    float initial_speed = 0;
    for (int count = 0; count < 20; count++) {
      container.setTemp(true);
    }
    container.AdvanceOneFrame();
    REQUIRE(container.getAverageSpeed() > initial_speed);
  }

  SECTION("checking when temp decreases") {
    GasContainer container = {100, 100, 0};
    container.particleList_.push_back(
        Particle(10, 10, glm::vec2(0, 5), glm::vec2(0, 5), "white"));
    float initial_speed = 0;
    for (int count = 0; count < 20; count++) {
      container.setTemp(true);
    }
    container.AdvanceOneFrame();
    REQUIRE(container.getAverageSpeed() > initial_speed);

  }
  SECTION("checking when energy increases") {
    GasContainer container = {100, 100, 0};
    container.particleList_.push_back(
        Particle(10, 10, glm::vec2(0, 5), glm::vec2(0, 5), "white"));
    float initial_speed = 0;
    for (int count = 0; count < 20; count++) {
      container.setEnergy(true);
    }
    container.AdvanceOneFrame();
    REQUIRE(container.getAverageSpeed() > initial_speed);
  }
  SECTION("checking when energy decreases") {
    GasContainer container = {100, 100, 0};
    container.particleList_.push_back(
        Particle(10, 10, glm::vec2(0, 5), glm::vec2(0, 5), "white"));
    float initial_speed = 0;
    for (int count = 0; count < 20; count++) {
      container.setEnergy(true);
    }
    container.AdvanceOneFrame();
    REQUIRE(container.getAverageSpeed() > initial_speed);
  }
}

TEST_CASE("edge cases for temp and energy changes") {
  SECTION("checking when temp increases and energy increases") {
    GasContainer container = {100, 100, 0};
    container.particleList_.push_back(
        Particle(10, 10, glm::vec2(0, 5), glm::vec2(0, 5), "white"));
    float initial_speed = 0;
    for (int count = 0; count < 20; count++) {
      container.setEnergy(true);
      container.setTemp(true);
    }
    container.AdvanceOneFrame();
    REQUIRE(container.getAverageSpeed() > initial_speed);
  }
  SECTION("checking when temp increases and energy decreases") {
    GasContainer container = {100, 100, 0};
    container.particleList_.push_back(
        Particle(10, 10, glm::vec2(0, 5), glm::vec2(0, 5), "white"));
    float initial_speed = 0;
    for (int count = 0; count < 20; count++) {
      container.setEnergy(false);
      container.setTemp(true);
    }
    container.AdvanceOneFrame();
    REQUIRE(container.getAverageSpeed() > initial_speed);
  }
  SECTION("checking when temp decreases and energy increases") {
    GasContainer container = {100, 100, 0};
    container.particleList_.push_back(
        Particle(10, 10, glm::vec2(0, 5), glm::vec2(0, 5), "white"));
    float initial_speed = 0;
    for (int count = 0; count < 20; count++) {
      container.setEnergy(true);
      container.setTemp(false);
    }
    container.AdvanceOneFrame();
    REQUIRE(container.getAverageSpeed() > initial_speed);
  }
  SECTION("checking when temp decreases and energy decreases") {
    GasContainer container = {100, 100, 0};
    container.particleList_.push_back(
        Particle(10, 10, glm::vec2(0, 5), glm::vec2(0, 5), "white"));
    float initial_speed = 0;
    for (int count = 0; count < 20; count++) {
      container.setEnergy(false);
      container.setTemp(false);
    }
    container.AdvanceOneFrame();
    REQUIRE(container.getAverageSpeed() > initial_speed);
  }
}

TEST_CASE("gravity tests") {
  SECTION("checking when temp decreases and gravity is on") {
    GasContainer container = {100, 100, 0};
    container.particleList_.push_back(
        Particle(10, 10, glm::vec2(0, 5), glm::vec2(0, 5), "white"));
    for (int count = 0; count < 20; count++) {
      container.setTemp(false);
    }
    container.setGravity();
    container.AdvanceOneFrame();
    REQUIRE(container.particleList_[0].getVelocity()[1] == 5.08f);

  }
  SECTION("checking when temp increases and gravity is on") {
    GasContainer container = {100, 100, 0};
    container.particleList_.push_back(
        Particle(10, 10, glm::vec2(0, 5), glm::vec2(0, 5), "white"));
    for (int count = 0; count < 20; count++) {
      container.setTemp(true);
    }
    container.setGravity();
    container.AdvanceOneFrame();
    REQUIRE(container.particleList_[0].getVelocity()[1] == 5.08f);
  }
  SECTION("checking when energy decreases and gravity is on") {
    GasContainer container = {100, 100, 0};
    container.particleList_.push_back(
        Particle(10, 10, glm::vec2(0, 5), glm::vec2(0, 5), "white"));
    for (int count = 0; count < 20; count++) {
      container.setEnergy(false);
    }
    container.setGravity();
    container.AdvanceOneFrame();
    REQUIRE(container.particleList_[0].getVelocity()[1] == 5.08f);
  }
  SECTION("checking when energy increases and gravity is on") {
    GasContainer container = {100, 100, 0};
    container.particleList_.push_back(
        Particle(10, 10, glm::vec2(0, 5), glm::vec2(0, 5), "white"));
    for (int count = 0; count < 20; count++) {
      container.setEnergy(true);
    }
    container.setGravity();
    container.AdvanceOneFrame();
    REQUIRE(container.particleList_[0].getVelocity()[1] == 5.08f);
  }

}