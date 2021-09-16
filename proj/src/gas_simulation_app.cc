#include "gas_simulation_app.h"

namespace idealgas {

IdealGasApp::IdealGasApp() {
  ci::app::setWindowSize(kWindowSizeX, kWindowSizeY);
}

void IdealGasApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);

  container_.Display();
}

void IdealGasApp::update() {
  container_.AdvanceOneFrame();
}

void IdealGasApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_UP:
      container_.setTemp(true);
      break;
    case ci::app::KeyEvent::KEY_DOWN:
      container_.setTemp(false);
      break;
    case ci::app::KeyEvent::KEY_RIGHT:
      container_.setEnergy(true);
      break;
    case ci::app::KeyEvent::KEY_LEFT:
      container_.setEnergy(false);
      break;
    case ci::app::KeyEvent::KEY_RETURN:
      container_.setGravity();
      break;
  }
}

}  // namespace idealgas
