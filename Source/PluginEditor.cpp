/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

Placeholder::Placeholder()
{
    juce::Random r;
    customColor = juce::Colour(r.nextInt(255), r.nextInt(255), r.nextInt(255));
}

//==============================================================================
SimpleReverbAudioProcessorEditor::SimpleReverbAudioProcessorEditor (SimpleReverbAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible(roomSize);
    addAndMakeVisible(width);
    addAndMakeVisible(damping);
    addAndMakeVisible(dryWet);
    addAndMakeVisible(freezeMode);

    setSize (180, 540);
}

SimpleReverbAudioProcessorEditor::~SimpleReverbAudioProcessorEditor()
{
}

//==============================================================================
void SimpleReverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::ivory);

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void SimpleReverbAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    auto bounds = getLocalBounds();

    roomSize.setBounds(bounds.removeFromTop(bounds.getHeight() * 0.2));
    width.setBounds(bounds.removeFromTop(bounds.getHeight() * 0.25));
    damping.setBounds(bounds.removeFromTop(bounds.getHeight() * 0.33));
    dryWet.setBounds(bounds.removeFromTop(bounds.getHeight() * 0.5));
    freezeMode.setBounds(bounds);

}
