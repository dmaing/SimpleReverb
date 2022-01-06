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

void LookAndFeel::drawRotarySlider(juce::Graphics& g,
    int x, int y, int width, int height,
    float sliderPosProportional,
    float rotaryStartAngle,
    float rotaryEndAngle,
    juce::Slider& slider)
{
    using namespace juce;

    auto bounds = Rectangle<float>(x, y, width, height);

    g.setColour(juce::Colours::white);
    g.fillEllipse(bounds);

    g.setColour(Colour(147, 212, 245));
    g.drawEllipse(bounds, 1.2f);

    if (auto* rswl = dynamic_cast<RotarySlider*>(&slider))
    {
        auto center = bounds.getCentre();
        Path p;

        Rectangle<float> r;
        r.setLeft(center.getX() - 2);
        r.setRight(center.getX() + 2);
        r.setTop(bounds.getY());
        r.setBottom(center.getY() - rswl->getTextHeight() * 2.2f);

        p.addRoundedRectangle(r, 2.f);

        jassert(rotaryStartAngle < rotaryEndAngle);

        auto sliderAngRad = jmap(sliderPosProportional, 0.f, 1.f, rotaryStartAngle, rotaryEndAngle);

        p.applyTransform(AffineTransform().rotated(sliderAngRad, center.getX(), center.getY()));

        g.fillPath(p);

        g.setFont(rswl->getTextHeight());
        auto text = rswl->getName();
        auto strWidth = g.getCurrentFont().getStringWidth(text);

        // Rectangle in which text will go that describes slider function
        r.setSize(strWidth + 4, rswl->getTextHeight() + 2);
        r.setCentre(bounds.getCentre());

        g.setColour(Colour(147, 212, 245));
        g.drawFittedText(text, r.toNearestInt(), juce::Justification::centred, 1);
    }
}

void RotarySlider::paint(juce::Graphics& g)
{
    using namespace juce;

    auto startAng = degreesToRadians(180.f + 45.f);
    auto endAng = degreesToRadians(180.f - 45.f) + MathConstants<float>::twoPi;

    auto range = getRange();

    auto sliderBounds = getSliderBounds();

    getLookAndFeel().drawRotarySlider(g, sliderBounds.getX(), sliderBounds.getY(), sliderBounds.getWidth(),
        sliderBounds.getHeight(), jmap(getValue(), range.getStart(), range.getEnd(), 0.0, 1.0),
        startAng, endAng, *this);
}

juce::Rectangle<int> RotarySlider::getSliderBounds() const
{
    //return getLocalBounds();
    auto bounds = getLocalBounds();

    auto size = juce::jmin(bounds.getWidth(), bounds.getHeight());

    size -= getTextHeight() * 2;

    juce::Rectangle<int> r;
    r.setSize(size, size);
    r.setCentre(bounds.getCentreX(), bounds.getCentreY());
    //r.setY(2);

    return r;
}

//==============================================================================
SimpleReverbAudioProcessorEditor::SimpleReverbAudioProcessorEditor(SimpleReverbAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p),
    roomSizeSlider(*audioProcessor.apvts.getParameter("Room Size"), "Size"),
    widthSlider(*audioProcessor.apvts.getParameter("Width"), "Width"),
    dampingSlider(*audioProcessor.apvts.getParameter("Damping"), "Damping"),
    dryWetSlider(*audioProcessor.apvts.getParameter("Dry Wet"), "Dry/Wet"),
    freezeModeButton("Freeze Mode"),

    roomSizeSliderAttachment(audioProcessor.apvts, "Room Size", roomSizeSlider),
    widthSliderAttachment(audioProcessor.apvts, "Width", widthSlider),
    dampingSliderAttachment(audioProcessor.apvts, "Damping", dampingSlider),
    dryWetSliderAttachment(audioProcessor.apvts, "Dry Wet", dryWetSlider),
    freezeModeButtonAttachment(audioProcessor.apvts, "Freeze Mode", freezeModeButton)
{

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    freezeModeButton.setClickingTogglesState(true);

    auto normalImageFile = resources->getChildFile("1F976_color.png");
    auto downImageFile = resources->getChildFile("1F975_color.png");
    jassert(normalImageFile.existsAsFile() && downImageFile.existsAsFile());

    auto normalImage = juce::ImageCache::getFromFile(normalImageFile);
    auto downImage = juce::ImageCache::getFromFile(downImageFile);

    freezeModeButton.setImages(false,
        true,
        true,
        normalImage,
        1.f,
        {},
        normalImage,
        1.f,
        {},
        downImage,
        1.f,
        {});

    addAndMakeVisible(roomSizeSlider);
    addAndMakeVisible(widthSlider);
    addAndMakeVisible(dampingSlider);
    addAndMakeVisible(dryWetSlider);
    addAndMakeVisible(freezeModeButton);

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

    //g.setColour (juce::Colours::white);
    //g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void SimpleReverbAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    auto bounds = getLocalBounds();

    roomSizeSlider.setBounds(bounds.removeFromTop(bounds.getHeight() * 0.2));
    widthSlider.setBounds(bounds.removeFromTop(bounds.getHeight() * 0.25));
    dampingSlider.setBounds(bounds.removeFromTop(bounds.getHeight() * 0.33));
    dryWetSlider.setBounds(bounds.removeFromTop(bounds.getHeight() * 0.5));
    freezeModeButton.setBounds(bounds);

}
