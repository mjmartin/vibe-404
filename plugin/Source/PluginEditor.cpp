#include "PluginEditor.h"

Vibe404AudioProcessorEditor::Vibe404AudioProcessorEditor(Vibe404AudioProcessor& p)
    : AudioProcessorEditor(&p),
      osc1Panel  (p.apvts),
      osc2Panel  (p.apvts),
      mixPanel   (p.apvts),
      envPanel   (p.apvts),
      filterPanel(p.apvts),
      lfoPanel   (p.apvts),
      distPanel  (p.apvts)
{
    setLookAndFeel(&laf);
    setSize(700, 480);

    addAndMakeVisible(osc1Panel);
    addAndMakeVisible(osc2Panel);
    addAndMakeVisible(mixPanel);
    addAndMakeVisible(envPanel);
    addAndMakeVisible(filterPanel);
    addAndMakeVisible(lfoPanel);
    addAndMakeVisible(distPanel);
}

Vibe404AudioProcessorEditor::~Vibe404AudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

void Vibe404AudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(Vibe404LookAndFeel::COL_BG));
}

void Vibe404AudioProcessorEditor::resized()
{
    // Layout — 700 x 480  (472px usable after reduced(4))
    //
    // Row 1 (h=130): [OSC 1 — 270] [OSC 2 — middle] [MIX strip — 84]
    // Row 2 (h=130): [ENVELOPE — full width]
    // Row 3 (h=76):  [FILTER — full width]
    // Row 4 (h=136): [LFO — rest] [DIST — 132]

    auto area = getLocalBounds().reduced(4);

    // Row 1: oscillators + mix strip
    auto row1 = area.removeFromTop(130);
    osc1Panel.setBounds(row1.removeFromLeft(270));
    mixPanel .setBounds(row1.removeFromRight(84));
    osc2Panel.setBounds(row1);

    // Row 2: envelope
    envPanel.setBounds(area.removeFromTop(130));

    // Row 3: filter
    filterPanel.setBounds(area.removeFromTop(76));

    // Row 4: LFO + dist
    distPanel.setBounds(area.removeFromRight(132));
    lfoPanel .setBounds(area);
}
