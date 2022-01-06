/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
struct Placeholder : juce::Component
{
    Placeholder();

    void paint(juce::Graphics& g) override
    {
        g.fillAll(customColor);
    }

    juce::Colour customColor;
};

struct LookAndFeel : juce::LookAndFeel_V4
{
    void drawRotarySlider(juce::Graphics& g,
        int x, int y, int width, int height,
        float sliderPosProportional,
        float rotaryStartAngle,
        float rotaryEndAngle,
        juce::Slider& slider) override;
};

struct RotarySlider : juce::Slider
{
    RotarySlider(juce::RangedAudioParameter& rap,
        const juce::String& title) :
        juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
        juce::Slider::TextEntryBoxPosition::NoTextBox),
        param(&rap)
    {
        setName(title);
        setLookAndFeel(&lnf);
    }

    ~RotarySlider()
    {
        setLookAndFeel(nullptr);
    }

    void paint(juce::Graphics& g) override;
    juce::Rectangle<int> getSliderBounds() const;
    int getTextHeight() const { return 14; }

private:
    juce::RangedAudioParameter* param;
    LookAndFeel lnf;
};

/**
*/
class SimpleReverbAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SimpleReverbAudioProcessorEditor (SimpleReverbAudioProcessor&);
    ~SimpleReverbAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleReverbAudioProcessor& audioProcessor;

    RotarySlider roomSizeSlider, widthSlider, dampingSlider, dryWetSlider;

    juce::ImageButton freezeModeButton;

    using APVTS = juce::AudioProcessorValueTreeState;
    using Attachment = APVTS::SliderAttachment;

    Attachment roomSizeSliderAttachment, widthSliderAttachment,
        dampingSliderAttachment, dryWetSliderAttachment;

    using ButtonAttachment = APVTS::ButtonAttachment;

    ButtonAttachment freezeModeButtonAttachment;

    

    juce::File* normalImageFile = new juce::File("C:/JUCE/SimpleReverb/1F976_color.png");

    juce::ImageCache *normalImageCache;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleReverbAudioProcessorEditor)
};
