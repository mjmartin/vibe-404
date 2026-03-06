#include "EnvelopePanel.h"
#include "../../Parameters.h"

EnvelopePanel::EnvelopePanel(juce::AudioProcessorValueTreeState& apvts)
    : SectionPanel("ENV"),
      attack (apvts, ParamID::envAttack,  "ATT"),
      decay  (apvts, ParamID::envDecay,   "DEC"),
      sustain(apvts, ParamID::envSustain, "SUS"),
      slope  (apvts, ParamID::envSlope,   "SL"),
      release(apvts, ParamID::envRelease, "REL")
{
    addAndMakeVisible(attack);
    addAndMakeVisible(decay);
    addAndMakeVisible(sustain);
    addAndMakeVisible(slope);
    addAndMakeVisible(release);
}

void EnvelopePanel::resized()
{
    auto area = getLocalBounds().reduced(6, 14);
    int knobW = area.getWidth() / 5;
    attack .setBounds(area.removeFromLeft(knobW));
    decay  .setBounds(area.removeFromLeft(knobW));
    sustain.setBounds(area.removeFromLeft(knobW));
    slope  .setBounds(area.removeFromLeft(knobW));
    release.setBounds(area);
}
