#include "Vibe404LookAndFeel.h"

Vibe404LookAndFeel::Vibe404LookAndFeel()
{
    setColour(juce::ResizableWindow::backgroundColourId, juce::Colour(COL_BG));
    setColour(juce::Slider::rotarySliderFillColourId,    juce::Colour(COL_ACCENT));
    setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(COL_BORDER));
    setColour(juce::Slider::thumbColourId,               juce::Colour(COL_KNOB));
    setColour(juce::Label::textColourId,                 juce::Colour(COL_LABEL));
    setColour(juce::ToggleButton::textColourId,          juce::Colour(COL_LABEL));
    setColour(juce::GroupComponent::outlineColourId,     juce::Colour(COL_BORDER));
    setColour(juce::GroupComponent::textColourId,        juce::Colour(COL_LABEL));
}

void Vibe404LookAndFeel::drawRotarySlider(juce::Graphics& g,
                                           int x, int y, int width, int height,
                                           float sliderPos,
                                           float rotaryStartAngle, float rotaryEndAngle,
                                           juce::Slider& /*slider*/)
{
    // Always use a square so the knob is a circle, never an oval
    float side = juce::jmin((float)width, (float)height) - 8.f;
    auto bounds = juce::Rectangle<float>((float)x + (width  - side) * 0.5f,
                                         (float)y + (height - side) * 0.5f,
                                         side, side);
    auto centre = bounds.getCentre();
    auto radius = side * 0.5f;

    // Body gradient
    juce::ColourGradient grad(juce::Colour(0xFF585858), centre.x, centre.y - radius,
                              juce::Colour(COL_KNOB),    centre.x, centre.y + radius, false);
    g.setGradientFill(grad);
    g.fillEllipse(bounds);

    // Border ring
    g.setColour(juce::Colour(COL_BORDER));
    g.drawEllipse(bounds, 1.5f);

    // Arc track (full range, dark)
    juce::Path arcTrack;
    arcTrack.addArc(bounds.getX() + 4, bounds.getY() + 4,
                    bounds.getWidth() - 8, bounds.getHeight() - 8,
                    rotaryStartAngle, rotaryEndAngle, true);
    g.setColour(juce::Colour(0xFF333333));
    g.strokePath(arcTrack, juce::PathStrokeType(3.f, juce::PathStrokeType::curved,
                                                 juce::PathStrokeType::rounded));

    // Arc fill (value, accent)
    float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    juce::Path arcFill;
    arcFill.addArc(bounds.getX() + 4, bounds.getY() + 4,
                   bounds.getWidth() - 8, bounds.getHeight() - 8,
                   rotaryStartAngle, angle, true);
    g.setColour(juce::Colour(COL_ACCENT));
    g.strokePath(arcFill, juce::PathStrokeType(3.f, juce::PathStrokeType::curved,
                                                juce::PathStrokeType::rounded));

    // Indicator line
    auto lineRadius = radius * 0.65f;
    juce::Point<float> tip(centre.x + lineRadius * std::sin(angle),
                            centre.y - lineRadius * std::cos(angle));
    g.setColour(juce::Colours::white.withAlpha(0.9f));
    g.drawLine({ centre, tip }, 2.f);
}

void Vibe404LookAndFeel::drawToggleButton(juce::Graphics& g,
                                           juce::ToggleButton& button,
                                           bool /*highlighted*/, bool /*down*/)
{
    auto bounds = button.getLocalBounds().toFloat().reduced(2.f);
    float cornerSize = bounds.getHeight() * 0.4f;

    bool isOn = button.getToggleState();
    g.setColour(isOn ? juce::Colour(COL_ACCENT) : juce::Colour(0xFF333333));
    g.fillRoundedRectangle(bounds, cornerSize);

    g.setColour(juce::Colour(COL_BORDER));
    g.drawRoundedRectangle(bounds, cornerSize, 1.f);

    g.setColour(isOn ? juce::Colours::white : juce::Colour(COL_LABEL));
    auto font = juce::Font(juce::FontOptions(bounds.getHeight() * 0.55f));
    g.setFont(font);
    g.drawFittedText(button.getButtonText(), bounds.toNearestInt(),
                     juce::Justification::centred, 1);
}

void Vibe404LookAndFeel::drawGroupComponentOutline(juce::Graphics& g,
                                                    int w, int h,
                                                    const juce::String& text,
                                                    const juce::Justification& /*just*/,
                                                    juce::GroupComponent& /*group*/)
{
    auto bounds = juce::Rectangle<float>(0.f, 8.f, (float)w, (float)h - 8.f);
    g.setColour(juce::Colour(COL_PANEL));
    g.fillRoundedRectangle(bounds, 4.f);
    g.setColour(juce::Colour(COL_BORDER));
    g.drawRoundedRectangle(bounds, 4.f, 1.f);

    if (text.isNotEmpty())
    {
        auto font = juce::Font(juce::FontOptions(11.f));
        float textW = juce::GlyphArrangement::getStringWidth(font, text) + 8.f;
        float textX = 12.f;
        juce::Rectangle<float> textBounds(textX, 0.f, textW, 16.f);

        g.setColour(juce::Colour(COL_PANEL));
        g.fillRect(textBounds);

        g.setColour(juce::Colour(COL_LABEL));
        g.setFont(font);
        g.drawText(text, textBounds, juce::Justification::centred);
    }
}

void Vibe404LookAndFeel::drawLabel(juce::Graphics& g, juce::Label& label)
{
    g.setColour(label.findColour(juce::Label::textColourId));
    auto font = juce::Font(juce::FontOptions(label.getFont().getHeight()));
    g.setFont(font);
    g.drawFittedText(label.getText(), label.getLocalBounds(),
                     label.getJustificationType(), 1, 1.f);
}
