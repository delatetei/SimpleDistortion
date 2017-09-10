#pragma once
#include "../JuceLibraryCode/JuceHeader.h"


class StandbyLight: public Component
{
public:
    StandbyLight();
    ~StandbyLight();
    void paint(Graphics&) override;

private:

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StandbyLight)
};