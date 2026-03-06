#include "MixPanel.h"
#include "../../Parameters.h"

MixPanel::MixPanel(juce::AudioProcessorValueTreeState& apvts)
    : SectionPanel("MIX"),
      mixKnob(apvts, ParamID::oscMix, "MIX")
{
    addAndMakeVisible(mixKnob);

    ringModButton.setButtonText("RM");
    addAndMakeVisible(ringModButton);
    ringAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
        apvts, ParamID::ringMod, ringModButton);

    syncButton.setButtonText("SYNC");
    addAndMakeVisible(syncButton);
    syncAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
        apvts, ParamID::osc2Sync, syncButton);
}

void MixPanel::resized()
{
    auto area = getLocalBounds().reduced(6, 14);
    // MIX knob takes top half, RM + SYNC split the bottom half
    mixKnob.setBounds(area.removeFromTop(area.getHeight() / 2));
    int btnH = area.getHeight() / 2;
    ringModButton.setBounds(area.removeFromTop(btnH).reduced(2, 1));
    syncButton   .setBounds(area.reduced(2, 1));
}
