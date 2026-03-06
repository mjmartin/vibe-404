#pragma once
#include <JuceHeader.h>

// A titled group component with the dark metal background fill.
class SectionPanel : public juce::GroupComponent
{
public:
    explicit SectionPanel(const juce::String& title);
    void paint(juce::Graphics&) override;
};
