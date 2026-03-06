#pragma once
#include <JuceHeader.h>

class LabelledKnob : public juce::Component
{
public:
    LabelledKnob(juce::AudioProcessorValueTreeState& apvts,
                 const juce::String& paramId,
                 const juce::String& labelText);

    void resized() override;

    juce::Slider slider;

private:
    juce::Label  label;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
};
