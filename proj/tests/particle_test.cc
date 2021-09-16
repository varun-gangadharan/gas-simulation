#include <catch2/catch.hpp>

#include <gas_container.h>


using idealgas::GasContainer;
using idealgas::Particle;

TEST_CASE("Draw test") {

}

TEST_CASE("edge cases for particles") {
  SECTION("invalid position value x") {
    REQUIRE_THROWS_AS(Particle(10, 10, glm::vec2(-1, 5), glm::vec2(0, -10), "white"), std::invalid_argument);
  }
  SECTION("invalid position value y") {
    REQUIRE_THROWS_AS(Particle(10, 10, glm::vec2(1, -5), glm::vec2(0, -10), "white"), std::invalid_argument);
  }
  SECTION("invalid mass input negative") {
    REQUIRE_THROWS_AS(Particle(10, -10, glm::vec2(-1, 5), glm::vec2(0, -10), "white"), std::invalid_argument);
  }
}

