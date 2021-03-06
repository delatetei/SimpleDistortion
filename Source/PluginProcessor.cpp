/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SimpleDistortionAudioProcessor::SimpleDistortionAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
:parameters(*this, nullptr)
{
    auto valueToInvertText = [](float value) {return String(value); };
    auto valueToInvertOnOff = [](float value) { return value == 0.0f ? "OFF" : "ON"; };
    auto textToInvertValue = [](const String& text) {return text.getFloatValue(); };
    auto onOffToInvertValue = [](const String& text) { return text == "ON" ? 1.0f : 0.0f; };
    parameters.createAndAddParameter("level", "LEVEL", "", NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.7f, valueToInvertText, textToInvertValue);
    parameters.createAndAddParameter("dist", "DIST", "", NormalisableRange<float>(1.0f, 5.0f, 0.1f), 1.0f, valueToInvertText, textToInvertValue);
    parameters.createAndAddParameter("bypass", "BYPASS SWITCH", "", NormalisableRange<float>(0.0f, 1.0f, 1.0f), 1.0f, valueToInvertOnOff, onOffToInvertValue);

    parameters.addParameterListener("bypass", new ParameterListener(*this));

    parameters.state = ValueTree(Identifier("SimpleDistortion"));
}

SimpleDistortionAudioProcessor::~SimpleDistortionAudioProcessor()
{
}

//==============================================================================
const String SimpleDistortionAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SimpleDistortionAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SimpleDistortionAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double SimpleDistortionAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleDistortionAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SimpleDistortionAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleDistortionAudioProcessor::setCurrentProgram (int index)
{
}

const String SimpleDistortionAudioProcessor::getProgramName (int index)
{
    return {};
}

void SimpleDistortionAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SimpleDistortionAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void SimpleDistortionAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimpleDistortionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SimpleDistortionAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    if (*(parameters.getRawParameterValue("bypass")) == 0.0f) return;

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);
        for (int buffNum = 0; buffNum < buffer.getNumSamples(); ++buffNum)
        {
            float data = channelData[buffNum];
            int sign = (data > 0) - (data < 0);
            data = data * *(parameters.getRawParameterValue("dist"));
            channelData[buffNum] = sign * (1.0f - std::exp(-5.0f * std::abs(data)));
        }
    }

    buffer.applyGain(*(parameters.getRawParameterValue("level")));
}

//==============================================================================
bool SimpleDistortionAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SimpleDistortionAudioProcessor::createEditor()
{
    editor = new SimpleDistortionAudioProcessorEditor(*this, parameters);
    return editor;
}

//==============================================================================
void SimpleDistortionAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    ScopedPointer<XmlElement> xml(parameters.state.createXml());
    copyXmlToBinary(*xml, destData);
}

void SimpleDistortionAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.state = ValueTree::fromXml(*xmlState);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleDistortionAudioProcessor();
}

//==============================================================================
// Inner Class
SimpleDistortionAudioProcessor::ParameterListener::ParameterListener(SimpleDistortionAudioProcessor & p)
:_p(p)
{
}

void SimpleDistortionAudioProcessor::ParameterListener::parameterChanged(const String & parameterID, float newValue)
{
    if (parameterID == "bypass")
    {
        dynamic_cast<SimpleDistortionAudioProcessorEditor*>(_p.editor)->changeStandbyLightState(newValue);
    }
    else
    {
        // nothing to do
    }
} 
