#include "Osc1Panel.h"
#include "../../Parameters.h"

Osc1Panel::Osc1Panel(juce::AudioProcessorValueTreeState& apvts)
    : SectionPanel("OSC 1"),
      waveSelector(apvts, ParamID::osc1Wave),
      octave(apvts, ParamID::osc1Octave, "OCT"),
      semi  (apvts, ParamID::osc1Semi,   "SEMI"),
      fine  (apvts, ParamID::osc1Fine,   "FINE"),
      pw    (apvts, ParamID::osc1PW,     "PW")
{
    addAndMakeVisible(waveSelector);
    addAndMakeVisible(octave);
    addAndMakeVisible(semi);
    addAndMakeVisible(fine);
    addAndMakeVisible(pw);
}

void Osc1Panel::resized()
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
