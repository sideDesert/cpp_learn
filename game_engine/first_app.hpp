#pragma once 

#include "lve_window.hpp"
#include "lve_pipeline.hpp"

namespace lve {
class FirstApp {
public:
  static constexpr int WIDTH = 600;
  static constexpr int HEIGHT = 600;
  void run();
private:
  LveWindow lveWindow{WIDTH, HEIGHT, "Hello Vulan!"};
  LvePipeline lvePipeline{"shaders/simple_shader.vert.spv", "shaders/simple_shader.frag.spv"};
};
}
