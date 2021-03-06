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
    setSize (WINDOW_WIDTH, WINDOW_HEIGHT);

    // Standby Light
    checkLabel.setText("CHECK", dontSendNotification);
    checkLabel.setFont(Font(10));
    checkLabel.setJustificationType(Justification::centred);
    changeStandbyLightState(*(vts.getRawParameterValue("bypass")));
    addAndMakeVisible(&standbyLight);
    addAndMakeVisible(&checkLabel);

    // Parameter
    level.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    level.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
    levelLabel.setText(valueTreeState.getParameter("level")->name, dontSendNotification);
    levelLabel.setJustificationType(Justification::centred);
    dist.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    dist.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
    distLabel.setText(valueTreeState.getParameter("dist")->name, dontSendNotification);
    distLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&level);
    addAndMakeVisible(&levelLabel);
    addAndMakeVisible(&dist);
    addAndMakeVisible(&distLabel);

    // ProductName
    productNameLabel1.setText("Simple", dontSendNotification);
    productNameLabel1.setFont(Font(35));
    productNameLabel2.setText("Distortion", dontSendNotification);
    productNameLabel2.setJustificationType(Justification::centred);
    productNameLabel2.setFont(Font(35));
    productNameLabel3.setText("SD-0", dontSendNotification);
    productNameLabel3.setJustificationType(Justification::right);
    productNameLabel3.setFont(Font(20));
    addAndMakeVisible(&productNameLabel1);
    addAndMakeVisible(&productNameLabel2);
    addAndMakeVisible(&productNameLabel3);

    // Bypass Switch
    bypass.setButtonText(valueTreeState.getParameter("bypass")->name);
    bypass.setToggleState(true, sendNotification);
    bypass.setClickingTogglesState(true);
    addAndMakeVisible(&bypass);

    levelAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "level", level);
    distAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "dist", dist);
    bypassAttachment = new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "bypass", bypass);
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
    area.removeFromTop(10);

    // Standby Light
    Rectangle<int> standbyLightArea(area.removeFromTop(25));
    checkLabel.setBounds(standbyLightArea.removeFromTop(10));
    standbyLightArea.removeFromLeft(145);
    standbyLightArea.removeFromTop(5);
    standbyLight.setBounds(standbyLightArea.removeFromTop(10));
    area.removeFromTop(-15);

    // Parameter
    Rectangle<int> parameterArea(area.removeFromTop(110));
    
    // Level Knob
    Rectangle<int> levelArea(parameterArea.removeFromLeft(150));
    level.setBounds(levelArea.removeFromTop(100));
    levelLabel.setBounds(levelArea.removeFromTop(10));

    // Dist Knob
    Rectangle<int> distArea(parameterArea.removeFromLeft(150));
    dist.setBounds(distArea.removeFromTop(100));
    distLabel.setBounds(distArea.removeFromTop(10));

    // Product Name 1
    area.removeFromTop(10);
    Rectangle<int> productNameArea1(area.removeFromTop(35));
    productNameArea1.removeFromLeft(10);
    productNameLabel1.setBounds(productNameArea1.removeFromTop(35));


    // Product Name 2
    Rectangle<int> productNameArea2(area.removeFromTop(35));
    productNameLabel2.setBounds(productNameArea2.removeFromTop(35));

    // Product Name 3
    Rectangle<int> productNameArea3(area.removeFromTop(20));
    productNameArea3.removeFromRight(10);
    productNameLabel3.setBounds(productNameArea3.removeFromTop(20));

    // Bypass Button
    area.removeFromTop(5);
    Rectangle<int> bypassButtonArea(area.removeFromTop(180));
    bypassButtonArea.removeFromTop(5);
    bypassButtonArea.removeFromBottom(5);
    bypassButtonArea.removeFromLeft(5);
    bypassButtonArea.removeFromRight(5);
    bypass.setBounds(bypassButtonArea.removeFromTop(170));
}

void SimpleDistortionAudioProcessorEditor::changeStandbyLightState(float value)
{
    standbyLight.setColour(0, value == 1.0f ? Colours::red : Colours::grey);
    repaint();
}