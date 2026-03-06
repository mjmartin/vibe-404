#include "SectionPanel.h"
#include "Vibe404LookAndFeel.h"

SectionPanel::SectionPanel(const juce::String& title)
{
    setText(title);
}

void SectionPanel::paint(juce::Graphics& g)
{
    // Fill background before the LookAndFeel draws the border+title
    g.setColour(juce::Colour(Vibe404LookAndFeel::COL_PANEL));
    g.fillRoundedRectangle(getLocalBounds().toFloat().reduced(1.f), 4.f);

    // Delegate outline + title to LookAndFeel
    getLookAndFeel().drawGroupComponentOutline(g, getWidth(), getHeight(),
                                               getText(), getTextLabelPosition(), *this);
}
