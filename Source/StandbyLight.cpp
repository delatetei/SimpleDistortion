#include "StandbyLight.h"

StandbyLight::StandbyLight()
{
}

StandbyLight::~StandbyLight()
{

}

void StandbyLight::paint(Graphics& g)
{
    g.setColour(findColour(0));
    g.fillEllipse(0, 0, 10, 10);
}