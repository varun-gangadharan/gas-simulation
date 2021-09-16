
#include "Histogram.h"

#include <gas_container.h>

#include <catch2/catch.hpp>

using idealgas::GasContainer;
using idealgas::Particle;
using idealgas::Histogram;

TEST_CASE("Histogram Constructor Invalid Input") {
  SECTION("invalid mass input negative") {
    GasContainer container = {100, 100, 0};
    REQUIRE_THROWS_AS(idealgas::Histogram(-10, "red", container.particleList_), std::invalid_argument);
  }
}
TEST_CASE("Histogram Position tests") {
  SECTION("check positions for mass one") {
    GasContainer container = {100, 100, 0};
    idealgas::Histogram histogram(10, "red", container.particleList_);
    histogram.setHistogramPosition();
    REQUIRE(histogram.getXValue() == 650);
    REQUIRE(histogram.getYValue() == 310);
  }
  SECTION("check positions for mass two") {
    GasContainer container = {100, 100, 0};
    idealgas::Histogram histogram(6, "blue", container.particleList_);
    histogram.setHistogramPosition();
    REQUIRE(histogram.getXValue() == 650);
    REQUIRE(histogram.getYValue() == 760);
  }
  SECTION("check positions for mass three") {
    GasContainer container = {100, 100, 0};
    idealgas::Histogram histogram(2, "white", container.particleList_);
    histogram.setHistogramPosition();
    REQUIRE(histogram.getXValue() == 100);
    REQUIRE(histogram.getYValue() == 760);
  }
}

TEST_CASE("Update Speed Helper tests") {
  SECTION("check updated max speed") {
    GasContainer container = {100, 100, 0};
    idealgas::Histogram histogram(2, "white", container.particleList_);
    float initialSpeed = 0;
    container.AdvanceOneFrame();
    histogram.updateSpeeds();
    REQUIRE(histogram.getMaxSpeed() > initialSpeed);
  }
  SECTION("check updated min speed") {
    GasContainer container = {100, 100, 0};
    idealgas::Histogram histogram(2, "white", container.particleList_);
    float initialCheck = 100;
    container.AdvanceOneFrame();
    histogram.updateSpeeds();
    REQUIRE(histogram.getMinSpeed() < initialCheck);
  }
}

TEST_CASE("freq tests") {
  SECTION("check to see if frequency for initial range updates") {

  }
}


