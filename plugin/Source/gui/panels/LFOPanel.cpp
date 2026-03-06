#include "LFOPanel.h"
#include "../../Parameters.h"

LFOPanel::LFOPanel(juce::AudioProcessorValueTreeState& apvts)
    : SectionPanel("LFO"),
      waveSelector(apvts, ParamID::lfoWave),
      rate    (apvts, ParamID::lfoRate,     "SPD"),
      toPitch (apvts, ParamID::lfoToPitch,  "PCH"),
      toCutoff(apvts, ParamID::lfoToCutoff, "CUT"),
      toRes   (apvts, ParamID::lfoToRes,    "RES"),
      toPW    (apvts, ParamID::lfoToPW,     "PW")
{
    addAndMakeVisible(waveSelector);
    addAndMakeVisible(rate);
    addAndMakeVisible(toPitch);
    addAndMakeVisible(toCutoff);
    addAndMakeVisible(toRes);
    addAndMakeVisible(toPW);
}

void LFOPanel::resized()
{
    auto area = getLocalBounds().reduced(6, 14);
    // Wave selector as a top strip, knobs fill the row below
    waveSelector.setBounds(area.removeFromTop(28));
    area.removeFromTop(4);

    int knobW = area.getWidth() / 5;
    rate    .setBounds(area.removeFromLeft(knobW));
    toPitch .setBounds(area.removeFromLeft(knobW));
    toCutoff.setBounds(area.removeFromLeft(knobW));
    toRes   .setBounds(area.removeFromLeft(knobW));
    toPW    .setBounds(area);
}
