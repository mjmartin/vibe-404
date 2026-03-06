#pragma once
#include <JuceHeader.h>
#include "../SectionPanel.h"
#include "../WaveformSelector.h"
#include "../LabelledKnob.h"

class LFOPanel : public SectionPanel
{
public:
    explicit LFOPanel(juce::AudioProcessorValueTreeState& apvts);
    void resized() override;

private:
    WaveformSelector waveSelector;
    LabelledKnob     rate, toPitch, toCutoff, toRes, toPW;
};
