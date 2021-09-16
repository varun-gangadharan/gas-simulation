
#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "gas_container.h"

namespace idealgas {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
class IdealGasApp : public ci::app::App {
 public:
  IdealGasApp();

  void draw() override;
  void update() override;
  void keyDown(ci::app::KeyEvent event) override;

  // provided that you can see the entire UI on your screen.
  const int kWindowSizeX = 1100;
  const int kWindowSizeY = 800;
  const int kMargin = 100;
  const size_t kWidth = 400;
  const size_t kHeight = 400;

 private:
  GasContainer container_ = {400, 400, 100};
};

}  // namespace idealgas
