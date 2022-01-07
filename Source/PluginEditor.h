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

    void drawButtonBackground(juce::Graphics& g, juce::Button& button,
        const juce::Colour& backgroundColour,
        bool shouldDrawButtonAsHighlighted,
        bool shouldDrawButtonAsDown) override;
private:
    const juce::Colour mainColor = juce::Colour((uint8_t)45, 117, 150, 0.6f);
    const juce::Font mainFont = juce::Font(12.f, juce::Font::bold);

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
    int getTextHeight() const { return 12; }

private:
    juce::RangedAudioParameter* param;
    LookAndFeel lnf;
};

//struct Button : juce::ImageButton
//{
//    Button(const juce::String& title)
//    {
//        setName(title);
//        setLookAndFeel(&lnf);
//    }
//
//    ~Button()
//    {
//        setLookAndFeel(nullptr);
//    }
//
//    void paint(juce::Graphics& g) override;
//
//private:
//    LookAndFeel lnf;
//};

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

    RotarySlider roomSizeSlider, //sliders
        widthSlider,
        dampingSlider,
        dryWetSlider;

    juce::ImageButton freezeModeButton;

    // slider attachments
    using APVTS = juce::AudioProcessorValueTreeState;
    using Attachment = APVTS::SliderAttachment;

    Attachment roomSizeSliderAttachment, 
        widthSliderAttachment,
        dampingSliderAttachment,
        dryWetSliderAttachment;

    // button attachment
    using ButtonAttachment = APVTS::ButtonAttachment;

    ButtonAttachment freezeModeButtonAttachment;

    juce::Image normalImage = juce::ImageCache::getFromMemory(BinaryData::_1F976_color_png,
        BinaryData::_1F976_color_pngSize);
    juce::Image downImage = juce::ImageCache::getFromMemory(BinaryData::_1F975_color_png,
        BinaryData::_1F975_color_pngSize);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleReverbAudioProcessorEditor)
};
