#include "DistortionPanel.h"
#include "../../Parameters.h"

DistortionPanel::DistortionPanel(juce::AudioProcessorValueTreeState& a)
    : SectionPanel("DIST"),
      apvts(a),
      drive(a, ParamID::distDrive, "DRIVE")
{
    juce::StringArray labels { "OFF", "SOFT A", "HARD B" };
    for (int i = 0; i < 3; ++i)
    {
        auto* btn = modeButtons.add(new juce::TextButton(labels[i]));
        btn->setRadioGroupId(1002);
        btn->setClickingTogglesState(true);
        btn->onClick = [this, i]
        {
            if (auto* p = apvts.getParameter(ParamID::distMode))
                p->setValueNotifyingHost(static_cast<float>(i) / 2.f);
        };
        addAndMakeVisible(btn);
    }

    addAndMakeVisible(drive);

    apvts.addParameterListener(ParamID::distMode, this);
    int current = static_cast<int>(*apvts.getRawParameterValue(ParamID::distMode));
    updateModeButtons(current);
}

DistortionPanel::~DistortionPanel()
{
    apvts.removeParameterListener(ParamID::distMode, this);
}

void DistortionPanel::parameterChanged(const juce::String&, float newValue)
{
    juce::MessageManager::callAsync([this, newValue]
    {
        updateModeButtons(static_cast<int>(newValue));
    });
}

void DistortionPanel::updateModeButtons(int index)
{
    for (int i = 0; i < modeButtons.size(); ++i)
        modeButtons[i]->setToggleState(i == index, juce::dontSendNotification);
}

void DistortionPanel::resized()
{
    auto area = getLocalBounds().reduced(6, 14);

    // Mode buttons row
    auto btnRow = area.removeFromTop(22);
    int btnW = btnRow.getWidth() / 3;
    for (auto* btn : modeButtons)
        btn->setBounds(btnRow.removeFromLeft(btnW).reduced(1));

    area.removeFromTop(4);
    drive.setBounds(area);
}
