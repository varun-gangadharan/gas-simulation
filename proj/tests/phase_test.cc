
#include <Phase_Graph.h>
#include <gas_container.h>

#include <catch2/catch.hpp>

#include "Histogram.h"

using idealgas::GasContainer;
using idealgas::Particle;
using idealgas::Histogram;


TEST_CASE("graph Position tests") {
  SECTION("check positions for mass one") {
    GasContainer container = {100, 100, 0};
    idealgas::Phase_Graph graphOne(10, "red", 300, 0, container.particleList_);
    graphOne.setGraphPosition();
    REQUIRE(graphOne.getXValue() == 85);
    REQUIRE(graphOne.getYValue() == 735);
  }
  SECTION("check positions for mass two") {
    GasContainer container = {100, 100, 0};
    idealgas::Phase_Graph graphTwo(6, "blue", 300, 0, container.particleList_);
    graphTwo.setGraphPosition();
    REQUIRE(graphTwo.getXValue() == 420);
    REQUIRE(graphTwo.getYValue() == 735);

  }
  SECTION("check positions for mass three") {
    GasContainer container = {100, 100, 0};
    idealgas::Phase_Graph graphThree(2, "white", 300, 0, container.particleList_);
    graphThree.setGraphPosition();
    REQUIRE(graphThree.getXValue() == 755);
    REQUIRE(graphThree.getYValue() == 735);
  }
}

TEST_CASE("calculation fusion heattests") {
  SECTION("check updated fusion heat after temp increase") {
    GasContainer container = {100, 100, 0};
    container.particleList_.push_back(
        Particle(10, 10, glm::vec2(0, 5), glm::vec2(0, 5), "white"));
    idealgas::Phase_Graph graphThree(2, "white", 300, 0, container.particleList_);
    for (int count = 0; count < 20; count++) {
      container.setTemp(true);
    }
    container.AdvanceOneFrame();
    graphThree.calcTemps();
    REQUIRE(0 == graphThree.getFusionTemp());
  }
  SECTION("check updated fusion heat after temp decrease") {
    GasContainer container = {100, 100, 0};
    container.particleList_.push_back(
        Particle(10, 10, glm::vec2(0, 5), glm::vec2(0, 5), "white"));
    idealgas::Phase_Graph graphThree(2, "white", 300, 0, container.particleList_);
    for (int count = 0; count < 20; count++) {
      container.setTemp(false);
    }
    container.AdvanceOneFrame();
    graphThree.calcTemps();
    REQUIRE(0 == graphThree.getFusionTemp());
  }
  SECTION("check updated fusion heat after energy increase") {
    GasContainer container = {100, 100, 0};
    container.particleList_.push_back(
        Particle(10, 10, glm::vec2(0, 5), glm::vec2(0, 5), "white"));
    idealgas::Phase_Graph graphThree(2, "white", 300, 0, container.particleList_);
    for (int count = 0; count < 20; count++) {
      container.setEnergy(true);
    }
    graphThree.calcTemps();
    container.AdvanceOneFrame();
    REQUIRE(0 == graphThree.getFusionTemp());
  }
  SECTION("check updated fusion heat after energy decrease") {
    GasContainer container = {100, 100, 0};
    container.particleList_.push_back(
        Particle(10, 10, glm::vec2(0, 5), glm::vec2(0, 5), "white"));
    idealgas::Phase_Graph graphThree(2, "white", 300, 0, container.particleList_);
    for (int count = 0; count < 20; count++) {
      container.setEnergy(false);
    }
    graphThree.calcTemps();
    container.AdvanceOneFrame();
    REQUIRE(0 == graphThree.getFusionTemp());
  }
}

TEST_CASE("calculations for vaporization heat") {
  SECTION("check updated vaporization heat after temp increase") {
    GasContainer container = {100, 100, 0};
    container.particleList_.push_back(
        Particle(10, 10, glm::vec2(0, 5), glm::vec2(0, 5), "white"));
    idealgas::Phase_Graph graphThree(2, "white", 300, 0, container.particleList_);
    for (int count = 0; count < 20; count++) {
      container.setTemp(true);
    }
    container.AdvanceOneFrame();
    graphThree.calcTemps();
    REQUIRE(0 == graphThree.getVaporizationTemp());
  }
  SECTION("check updated vaporization heat after temp decrease") {
    GasContainer container = {100, 100, 0};
    container.particleList_.push_back(
        Particle(10, 10, glm::vec2(0, 5), glm::vec2(0, 5), "white"));
    idealgas::Phase_Graph graphThree(2, "white", 300, 0, container.particleList_);
    for (int count = 0; count < 20; count++) {
      container.setTemp(false);
    }
    container.AdvanceOneFrame();
    graphThree.calcTemps();
    REQUIRE(0 == graphThree.getVaporizationTemp());
  }
  SECTION("check updated vaporization heat after energy increase") {
    GasContainer container = {100, 100, 0};
    container.particleList_.push_back(
        Particle(10, 10, glm::vec2(0, 5), glm::vec2(0, 5), "white"));
    idealgas::Phase_Graph graphThree(2, "white", 300, 0, container.particleList_);
    for (int count = 0; count < 20; count++) {
      container.setEnergy(true);
    }
    graphThree.calcTemps();
    container.AdvanceOneFrame();
    REQUIRE(0 == graphThree.getVaporizationTemp());
  }
  SECTION("check updated vaporization heat after energy decrease") {
    GasContainer container = {100, 100, 0};
    container.particleList_.push_back(
        Particle(10, 10, glm::vec2(0, 5), glm::vec2(0, 5), "white"));
    idealgas::Phase_Graph graphThree(2, "white", 300, 0, container.particleList_);
    for (int count = 0; count < 20; count++) {
      container.setEnergy(false);
    }
    graphThree.calcTemps();
    container.AdvanceOneFrame();
    REQUIRE(0 == graphThree.getVaporizationTemp());
  }
}

TEST_CASE("constructor invalid input") {
  SECTION("invalid mass input negative") {
    GasContainer container = {100, 100, 0};
    REQUIRE_THROWS_AS(idealgas::Phase_Graph (-2, "white", 300, 0, container.particleList_), std::invalid_argument);
  }
}



