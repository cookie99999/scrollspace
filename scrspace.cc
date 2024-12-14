#include <iostream>
#include <exception>
#include <cmath>
#include <ctime>
#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;

int main() try {  
  return 0;
} catch (std::exception& e) {
  std::cerr << e.what() << std::endl;
  return -1;
}

