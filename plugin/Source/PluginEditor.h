#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "gui/Vibe404LookAndFeel.h"
#include "gui/panels/Osc1Panel.h"
#include "gui/panels/Osc2Panel.h"
#include "gui/panels/MixPanel.h"
#include "gui/panels/EnvelopePanel.h"
#include "gui/panels/FilterPanel.h"
#include "gui/panels/LFOPanel.h"
#include "gui/panels/DistortionPanel.h"

class Vibe404AudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit Vibe404AudioProcessorEditor(Vibe404AudioProcessor&);
    ~Vibe404AudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    Vibe404LookAndFeel laf;

    Osc1Panel       osc1Panel;
    Osc2Panel       osc2Panel;
    MixPanel        mixPanel;
    EnvelopePanel   envPanel;
    FilterPanel     filterPanel;
    LFOPanel        lfoPanel;
    DistortionPanel distPanel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Vibe404AudioProcessorEditor)
};
