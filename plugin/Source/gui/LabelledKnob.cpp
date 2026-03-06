#include "LabelledKnob.h"

LabelledKnob::LabelledKnob(juce::AudioProcessorValueTreeState& apvts,
                             const juce::String& paramId,
                             const juce::String& labelText)
{
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    slider.setPopupDisplayEnabled(true, true, nullptr);
    addAndMakeVisible(slider);

    label.setText(labelText, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.setFont(juce::Font(juce::FontOptions(10.f)));
    addAndMakeVisible(label);

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        apvts, paramId, slider);
}

void LabelledKnob::resized()
{
    auto bounds = getLocalBounds();
    int labelH = 14;
    label.setBounds(bounds.removeFromBottom(labelH));
    // Constrain slider to a square so the rotary always draws a circle
    int side = juce::jmin(bounds.getWidth(), bounds.getHeight());
    slider.setBounds(bounds.withSizeKeepingCentre(side, side));
}
