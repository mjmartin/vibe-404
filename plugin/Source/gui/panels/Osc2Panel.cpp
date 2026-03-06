#include "Osc2Panel.h"
#include "../../Parameters.h"

Osc2Panel::Osc2Panel(juce::AudioProcessorValueTreeState& apvts)
    : SectionPanel("OSC 2"),
      waveSelector(apvts, ParamID::osc2Wave),
      octave(apvts, ParamID::osc2Octave, "OCT"),
      semi  (apvts, ParamID::osc2Semi,   "SEMI"),
      fine  (apvts, ParamID::osc2Fine,   "FINE"),
      pw    (apvts, ParamID::osc2PW,     "PW")
{
    addAndMakeVisible(waveSelector);
    addAndMakeVisible(octave);
    addAndMakeVisible(semi);
    addAndMakeVisible(fine);
    addAndMakeVisible(pw);
}

void Osc2Panel::resized()
{
    auto area = getLocalBounds().reduced(6, 14);
    waveSelector.setBounds(area.removeFromTop(28));
    area.removeFromTop(4);

    int knobW = area.getWidth() / 4;
    octave.setBounds(area.removeFromLeft(knobW));
    semi  .setBounds(area.removeFromLeft(knobW));
    fine  .setBounds(area.removeFromLeft(knobW));
    pw    .setBounds(area);
}
