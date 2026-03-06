#include "WaveformSelector.h"
#include "Vibe404LookAndFeel.h"
#include <cmath>

WaveformSelector::WaveformSelector(juce::AudioProcessorValueTreeState& a,
                                   const juce::String& pid)
    : apvts(a), paramId(pid)
{
    if (auto* param = apvts.getRawParameterValue(paramId))
        selectedIndex = static_cast<int>(*param);

    apvts.addParameterListener(paramId, this);
}

WaveformSelector::~WaveformSelector()
{
    apvts.removeParameterListener(paramId, this);
}

void WaveformSelector::parameterChanged(const juce::String&, float newValue)
{
    selectedIndex = static_cast<int>(newValue);
    juce::MessageManager::callAsync([this] { repaint(); });
}

juce::Rectangle<int> WaveformSelector::cellBounds(int index) const
{
    int cellW = getWidth() / 6;
    return { index * cellW, 0, cellW, getHeight() };
}

void WaveformSelector::mouseDown(const juce::MouseEvent& e)
{
    for (int i = 0; i < 6; ++i)
    {
        if (cellBounds(i).contains(e.getPosition()))
        {
            if (auto* param = apvts.getParameter(paramId))
            {
                float norm = static_cast<float>(i) / 5.f;
                param->setValueNotifyingHost(norm);
            }
            break;
        }
    }
}

// Draw a small waveform icon for each shape index:
// 0=Sine, 1=Tri, 2=Saw, 3=RevSaw, 4=Square, 5=Noise
void WaveformSelector::drawWaveShape(juce::Graphics& g, int index, juce::Rectangle<float> area)
{
    juce::Path p;
    float x0 = area.getX(), x1 = area.getRight();
    float cy = area.getCentreY();
    float h  = area.getHeight() * 0.35f;
    float w  = area.getWidth();
    int pts  = 32;

    switch (index)
    {
        case 0: // Sine
            p.startNewSubPath(x0, cy);
            for (int i = 1; i <= pts; ++i)
            {
                float t = (float)i / pts;
                p.lineTo(x0 + t * w, cy - h * std::sin(t * juce::MathConstants<float>::twoPi));
            }
            break;

        case 1: // Triangle
            p.startNewSubPath(x0, cy);
            p.lineTo(x0 + w * 0.25f, cy - h);
            p.lineTo(x0 + w * 0.75f, cy + h);
            p.lineTo(x1, cy);
            break;

        case 2: // Saw (rising)
            p.startNewSubPath(x0, cy + h);
            p.lineTo(x1, cy - h);
            p.startNewSubPath(x1, cy - h);
            p.lineTo(x1, cy + h);
            break;

        case 3: // RevSaw (falling)
            p.startNewSubPath(x0, cy - h);
            p.lineTo(x1, cy + h);
            p.startNewSubPath(x0, cy - h);
            p.lineTo(x0, cy + h);
            break;

        case 4: // Square
            p.startNewSubPath(x0, cy - h);
            p.lineTo(x0 + w * 0.5f, cy - h);
            p.lineTo(x0 + w * 0.5f, cy + h);
            p.lineTo(x1, cy + h);
            break;

        case 5: // Noise (jagged)
        {
            juce::Random r(42);
            p.startNewSubPath(x0, cy);
            for (int i = 1; i <= 8; ++i)
            {
                float t = (float)i / 8.f;
                p.lineTo(x0 + t * w, cy + (r.nextFloat() * 2.f - 1.f) * h);
            }
            break;
        }
    }

    g.strokePath(p, juce::PathStrokeType(1.2f));
}

void WaveformSelector::paint(juce::Graphics& g)
{
    for (int i = 0; i < 6; ++i)
    {
        auto cell = cellBounds(i).toFloat();
        bool selected = (i == selectedIndex);

        // Background
        g.setColour(selected ? juce::Colour(Vibe404LookAndFeel::COL_ACCENT).withAlpha(0.3f)
                             : juce::Colour(0xFF2A2A2A));
        g.fillRoundedRectangle(cell.reduced(1.f), 2.f);

        // Border
        g.setColour(selected ? juce::Colour(Vibe404LookAndFeel::COL_ACCENT)
                             : juce::Colour(Vibe404LookAndFeel::COL_BORDER));
        g.drawRoundedRectangle(cell.reduced(1.f), 2.f, 1.f);

        // Waveform icon
        g.setColour(selected ? juce::Colour(Vibe404LookAndFeel::COL_ACCENT)
                             : juce::Colour(Vibe404LookAndFeel::COL_LABEL));
        drawWaveShape(g, i, cell.reduced(4.f, 3.f));
    }
}
