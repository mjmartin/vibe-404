#pragma once
#include <JuceHeader.h>

// Row of 6 clickable waveform icons. Bound to a Choice APVTS parameter.
class WaveformSelector : public juce::Component,
                         private juce::AudioProcessorValueTreeState::Listener
{
public:
    WaveformSelector(juce::AudioProcessorValueTreeState& apvts,
                     const juce::String& paramId);
    ~WaveformSelector() override;

    void paint(juce::Graphics&) override;
    void mouseDown(const juce::MouseEvent&) override;

private:
    void parameterChanged(const juce::String& paramID, float newValue) override;

    juce::Rectangle<int> cellBounds(int index) const;
    static void drawWaveShape(juce::Graphics&, int index, juce::Rectangle<float> area);

    juce::AudioProcessorValueTreeState& apvts;
    juce::String paramId;
    int selectedIndex = 0;
};
