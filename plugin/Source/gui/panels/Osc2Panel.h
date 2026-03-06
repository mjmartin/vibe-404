#pragma once
#include <JuceHeader.h>
#include "../SectionPanel.h"
#include "../WaveformSelector.h"
#include "../LabelledKnob.h"

class Osc2Panel : public SectionPanel
{
public:
    explicit Osc2Panel(juce::AudioProcessorValueTreeState& apvts);
    void resized() override;

private:
    WaveformSelector waveSelector;
    LabelledKnob     octave, semi, fine, pw;
};
