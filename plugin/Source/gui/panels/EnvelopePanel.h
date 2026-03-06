#pragma once
#include <JuceHeader.h>
#include "../SectionPanel.h"
#include "../LabelledKnob.h"

class EnvelopePanel : public SectionPanel
{
public:
    explicit EnvelopePanel(juce::AudioProcessorValueTreeState& apvts);
    void resized() override;

private:
    LabelledKnob attack, decay, sustain, slope, release;
};
