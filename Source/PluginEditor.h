/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


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

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleDistortionAudioProcessor& processor;
    AudioProcessorValueTreeState& valueTreeState;

    Slider level;
    Slider dist;
    TextButton bypass;
    Path path;
    ShapeButton standbyLight;
    Label checkLabel;
    
    Label levelLabel;
    Label distLabel;
    Label productNameLabel1;
    Label productNameLabel2;
    Label productNameLabel3;

    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> levelAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> distAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDistortionAudioProcessorEditor)
};
