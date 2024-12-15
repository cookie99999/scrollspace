#include <iostream>
#include <exception>
#include <cmath>
#include <ctime>
#include <SDL2pp/SDL2pp.hh>

#define TICKRATE_MS 500

using namespace SDL2pp;

long long clock_ms() {
  struct timespec t;
  clock_gettime(CLOCK_MONOTONIC, &t);
  return t.tv_sec * 1000LL + lround(t.tv_nsec / 1e6);
}

class System {
  std::array<int, 2> viewOrigin;
  std::array<int, 2> viewSize;
  SDL sdl;
  Window win;
  Renderer ren;
  Texture* stageBack;
  void scroll();
public:
  System();
  void render();
  void checkInput();
  void checkCollisions();
  bool isDone();
  void changeStage(std::string name);
};

System::System() : sdl(SDL_INIT_VIDEO), win("scrspace", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
					    480, 640, SDL_WINDOW_SHOWN), ren(win, -1, SDL_RENDERER_ACCELERATED) {
  ren.SetDrawBlendMode(SDL_BLENDMODE_BLEND);
  viewOrigin = {15, 20};
  viewSize = {15, 20};
}

void System::changeStage(std::string name) {
  stageBack = new Texture(ren, "res/" + name + ".png");
}

void System::render() {
  ren.Clear();

  ren.Copy(*stageBack, NullOpt, Point(0, 0));
  
  ren.Present();
}

int main() try {
  long long curtime, prevtime, deltatime, accumulator;
  prevtime = clock_ms();
  curtime = deltatime = accumulator = 0;
  bool done = false;
  System sys;

  sys.changeStage("stage01");

  while (!done) {
    while (accumulator >= TICKRATE_MS) {
      accumulator -= TICKRATE_MS;
    }

    //render input sound etc
    sys.render();

    deltatime = (curtime = clock_ms()) - prevtime;
    accumulator += deltatime;
    prevtime = curtime;
  }
  
  return 0;
} catch (std::exception& e) {
  std::cerr << e.what() << std::endl;
  return -1;
}

