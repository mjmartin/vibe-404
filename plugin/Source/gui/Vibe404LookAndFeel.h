#pragma once
#include <JuceHeader.h>

class Vibe404LookAndFeel : public juce::LookAndFeel_V4
{
public:
    static constexpr uint32_t COL_BG     = 0xFF1A1A1A;
    static constexpr uint32_t COL_PANEL  = 0xFF252525;
    static constexpr uint32_t COL_KNOB   = 0xFF404040;
    static constexpr uint32_t COL_LABEL  = 0xFFCCCCCC;
    static constexpr uint32_t COL_ACCENT = 0xFFFF7700;
    static constexpr uint32_t COL_BORDER = 0xFF555555;

    Vibe404LookAndFeel();

    void drawRotarySlider(juce::Graphics&, int x, int y, int width, int height,
                          float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
                          juce::Slider&) override;

    void drawToggleButton(juce::Graphics&, juce::ToggleButton&,
                          bool shouldDrawButtonAsHighlighted,
                          bool shouldDrawButtonAsDown) override;

    void drawGroupComponentOutline(juce::Graphics&, int w, int h,
                                   const juce::String& text,
                                   const juce::Justification&,
                                   juce::GroupComponent&) override;

    void drawLabel(juce::Graphics&, juce::Label&) override;
};
