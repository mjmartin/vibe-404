#pragma once
#include <JuceHeader.h>
#include "../SectionPanel.h"
#include "../WaveformSelector.h"
#include "../LabelledKnob.h"

class Osc1Panel : public SectionPanel
{
public:
    explicit Osc1Panel(juce::AudioProcessorValueTreeState& apvts);
    void resized() override;

private:
    WaveformSelector waveSelector;
    LabelledKnob     octave, semi, fine, pw;
};
