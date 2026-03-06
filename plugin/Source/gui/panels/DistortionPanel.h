#pragma once
#include <JuceHeader.h>
#include "../SectionPanel.h"
#include "../LabelledKnob.h"

class DistortionPanel : public SectionPanel,
                        private juce::AudioProcessorValueTreeState::Listener
{
public:
    explicit DistortionPanel(juce::AudioProcessorValueTreeState& apvts);
    ~DistortionPanel() override;
    void resized() override;

private:
    void parameterChanged(const juce::String& paramID, float newValue) override;
    void updateModeButtons(int index);

    juce::AudioProcessorValueTreeState& apvts;
    juce::OwnedArray<juce::TextButton> modeButtons;   // OFF, A, B
    LabelledKnob drive;
};
