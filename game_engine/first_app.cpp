#include "first_app.hpp"
#include <GLFW/glfw3.h>

namespace lve {
void FirstApp::run(){
  while(!this->lveWindow.shouldClose()){
    glfwPollEvents();
  }
}
};
