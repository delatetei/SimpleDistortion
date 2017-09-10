/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "StandbyLight.h"


//==============================================================================
/**
*/
class SimpleDistortionAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    SimpleDistortionAudioProcessorEditor (SimpleDistortionAudioProcessor&, AudioProcessorValueTreeState&);
    ~SimpleDistortionAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    //==============================================================================
    void changeStandbyLightState(float value);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleDistortionAudioProcessor& processor;
    AudioProcessorValueTreeState& valueTreeState;

    //==============================================================================
    const int WINDOW_HEIGHT = 400;
    const int WINDOW_WIDTH = 300;

    //==============================================================================
    // Standby Light
    Label checkLabel;
    StandbyLight standbyLight;

    // Parameter
    Slider level;
    Label levelLabel;
    Slider dist;
    Label distLabel;

    // Product Name
    Label productNameLabel1;
    Label productNameLabel2;
    Label productNameLabel3;

    // Bypass Switch
    TextButton bypass;

    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> levelAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> distAttachment;
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> bypassAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDistortionAudioProcessorEditor)
};
