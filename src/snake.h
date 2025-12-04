#include <vector>
#include "segment.h"

using namespace std;

class Snake
{
  private:
    vector<Segment> snake;
    Snake();

  public:
    

    void handleInput();
    void update();
    void render();
};