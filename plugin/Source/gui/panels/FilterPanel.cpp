#include "FilterPanel.h"
#include "../../Parameters.h"

FilterPanel::FilterPanel(juce::AudioProcessorValueTreeState& a)
    : SectionPanel("FILTER"),
      apvts(a),
      cutoff(a, ParamID::filterCutoff, "CUT"),
      res   (a, ParamID::filterRes,    "RES"),
      envAmt(a, ParamID::filterEnv,    "ENV")
{
    juce::StringArray labels { "LP12", "LP24", "HP", "BP", "OFF" };
    for (int i = 0; i < 5; ++i)
    {
        auto* btn = typeButtons.add(new juce::TextButton(labels[i]));
        btn->setRadioGroupId(1001);
        btn->setClickingTogglesState(true);
        btn->onClick = [this, i]
        {
            if (auto* p = apvts.getParameter(ParamID::filterType))
                p->setValueNotifyingHost(static_cast<float>(i) / 4.f);
        };
        addAndMakeVisible(btn);
    }

    addAndMakeVisible(cutoff);
    addAndMakeVisible(res);
    addAndMakeVisible(envAmt);

    apvts.addParameterListener(ParamID::filterType, this);

    int current = static_cast<int>(*apvts.getRawParameterValue(ParamID::filterType));
    updateTypeButtons(current);
}

FilterPanel::~FilterPanel()
{
    apvts.removeParameterListener(ParamID::filterType, this);
}

void FilterPanel::parameterChanged(const juce::String&, float newValue)
{
    juce::MessageManager::callAsync([this, newValue]
    {
        updateTypeButtons(static_cast<int>(newValue));
    });
}

void FilterPanel::updateTypeButtons(int index)
{
    for (int i = 0; i < typeButtons.size(); ++i)
        typeButtons[i]->setToggleState(i == index, juce::dontSendNotification);
}

void FilterPanel::resized()
{
    auto area = getLocalBounds().reduced(6, 14);

    // Top row: type buttons
    auto btnRow = area.removeFromTop(22);
    int btnW = btnRow.getWidth() / 5;
    for (auto* btn : typeButtons)
        btn->setBounds(btnRow.removeFromLeft(btnW).reduced(1));

    area.removeFromTop(4);

    // Knobs row
    int knobW = area.getWidth() / 3;
    cutoff.setBounds(area.removeFromLeft(knobW));
    res   .setBounds(area.removeFromLeft(knobW));
    envAmt.setBounds(area);
}
