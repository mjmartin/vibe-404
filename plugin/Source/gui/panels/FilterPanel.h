#pragma once
#include <JuceHeader.h>
#include "../SectionPanel.h"
#include "../LabelledKnob.h"

class FilterPanel : public SectionPanel,
                    private juce::AudioProcessorValueTreeState::Listener
{
public:
    explicit FilterPanel(juce::AudioProcessorValueTreeState& apvts);
    ~FilterPanel() override;
    void resized() override;

private:
    void parameterChanged(const juce::String& paramID, float newValue) override;
    void updateTypeButtons(int index);

    juce::AudioProcessorValueTreeState& apvts;

    juce::OwnedArray<juce::TextButton> typeButtons;   // LP12 LP24 HP BP OFF
    LabelledKnob cutoff, res, envAmt;
};
