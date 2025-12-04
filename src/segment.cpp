#include "segment.h"

void Segment::draw()
{
    rect.Draw(color);
}

void Segment::drawOutline() 
{
    rect.DrawLines(BLACK,2);
}
