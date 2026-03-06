#pragma once
#include <JuceHeader.h>
#include "../SectionPanel.h"
#include "../LabelledKnob.h"

class MixPanel : public SectionPanel
{
public:
    explicit MixPanel(juce::AudioProcessorValueTreeState& apvts);
    void resized() override;

private:
    LabelledKnob       mixKnob;
    juce::ToggleButton ringModButton;
    juce::ToggleButton syncButton;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> ringAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> syncAttachment;
};
