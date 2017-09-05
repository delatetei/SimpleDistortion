/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SimpleDistortionAudioProcessorEditor::SimpleDistortionAudioProcessorEditor (SimpleDistortionAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (300, 400);

    level.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    level.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
    levelLabel.setText(valueTreeState.getParameter("level")->label, dontSendNotification);
    levelLabel.setJustificationType(Justification::centred);
    dist.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    dist.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
    distLabel.setText(valueTreeState.getParameter("dist")->label, dontSendNotification);
    distLabel.setJustificationType(Justification::centred);

    addAndMakeVisible(&level);
    addAndMakeVisible(&levelLabel);
    addAndMakeVisible(&dist);
    addAndMakeVisible(&distLabel);

    levelAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "level", level);
    distAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "dist", dist);
}

SimpleDistortionAudioProcessorEditor::~SimpleDistortionAudioProcessorEditor()
{
}

//==============================================================================
void SimpleDistortionAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
}

void SimpleDistortionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    Rectangle<int> area(getLocalBounds());
    Rectangle<int> parameterArea(area.removeFromTop(110));
    Rectangle<int> levelArea(parameterArea.removeFromLeft(150));
    Rectangle<int> distArea(parameterArea.removeFromLeft(150));
    level.setBounds(levelArea.removeFromTop(100));
    levelLabel.setBounds(levelArea.removeFromTop(10));
    dist.setBounds(distArea.removeFromTop(100));
    distLabel.setBounds(distArea.removeFromTop(10));
}
