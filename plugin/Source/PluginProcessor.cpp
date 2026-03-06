#include "PluginProcessor.h"
#include "PluginEditor.h"

Vibe404AudioProcessor::Vibe404AudioProcessor()
    : AudioProcessor(BusesProperties()
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      apvts(*this, nullptr, "Vibe404State", Parameters::createLayout())
{
    for (int i = 0; i < kNumVoices; ++i)
        synth.addVoice(new SynthVoice());

    synth.enableLegacyMode(2);  // standard MIDI channel mode
}

void Vibe404AudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    lfo.prepare(sampleRate);

    for (int i = 0; i < synth.getNumVoices(); ++i)
        if (auto* voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
            voice->prepareToPlay(sampleRate, samplesPerBlock, 2);
}

void Vibe404AudioProcessor::releaseResources() {}

bool Vibe404AudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo()
        || layouts.getMainOutputChannelSet() == juce::AudioChannelSet::mono();
}

void Vibe404AudioProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                          juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    buffer.clear();

    // Snapshot all APVTS atomics
    VoiceParams vp;
    vp.osc1Wave    = static_cast<int>(*apvts.getRawParameterValue(ParamID::osc1Wave));
    vp.osc1Octave  = static_cast<int>(*apvts.getRawParameterValue(ParamID::osc1Octave));
    vp.osc1Semi    = static_cast<int>(*apvts.getRawParameterValue(ParamID::osc1Semi));
    vp.osc1Fine    = *apvts.getRawParameterValue(ParamID::osc1Fine);
    vp.osc1PW      = *apvts.getRawParameterValue(ParamID::osc1PW);

    vp.osc2Wave    = static_cast<int>(*apvts.getRawParameterValue(ParamID::osc2Wave));
    vp.osc2Octave  = static_cast<int>(*apvts.getRawParameterValue(ParamID::osc2Octave));
    vp.osc2Semi    = static_cast<int>(*apvts.getRawParameterValue(ParamID::osc2Semi));
    vp.osc2Fine    = *apvts.getRawParameterValue(ParamID::osc2Fine);
    vp.osc2PW      = *apvts.getRawParameterValue(ParamID::osc2PW);
    vp.osc2Sync    = *apvts.getRawParameterValue(ParamID::osc2Sync) > 0.5f;

    vp.oscMix      = *apvts.getRawParameterValue(ParamID::oscMix);
    vp.ringMod     = *apvts.getRawParameterValue(ParamID::ringMod) > 0.5f;

    vp.envAttack   = *apvts.getRawParameterValue(ParamID::envAttack);
    vp.envDecay    = *apvts.getRawParameterValue(ParamID::envDecay);
    vp.envSustain  = *apvts.getRawParameterValue(ParamID::envSustain);
    vp.envSlope    = *apvts.getRawParameterValue(ParamID::envSlope);
    vp.envRelease  = *apvts.getRawParameterValue(ParamID::envRelease);

    vp.filterType   = static_cast<int>(*apvts.getRawParameterValue(ParamID::filterType));
    vp.filterCutoff = *apvts.getRawParameterValue(ParamID::filterCutoff);
    vp.filterRes    = *apvts.getRawParameterValue(ParamID::filterRes);
    vp.filterEnv    = *apvts.getRawParameterValue(ParamID::filterEnv);

    vp.distMode     = static_cast<int>(*apvts.getRawParameterValue(ParamID::distMode));
    vp.distDrive    = *apvts.getRawParameterValue(ParamID::distDrive);

    // LFO
    lfo.setWaveShape(static_cast<WaveShape>(
        static_cast<int>(*apvts.getRawParameterValue(ParamID::lfoWave))));
    lfo.setRate(*apvts.getRawParameterValue(ParamID::lfoRate));
    float lfoVal = lfo.processSample();

    VoiceModulation vm;
    vm.lfoToPitch  = lfoVal * *apvts.getRawParameterValue(ParamID::lfoToPitch) * 12.f;
    vm.lfoToCutoff = lfoVal * *apvts.getRawParameterValue(ParamID::lfoToCutoff) * 5000.f;
    vm.lfoToRes    = lfoVal * *apvts.getRawParameterValue(ParamID::lfoToRes) * 0.5f;
    vm.lfoToPW     = lfoVal * *apvts.getRawParameterValue(ParamID::lfoToPW) * 0.4f;

    // Push params to all voices
    for (int i = 0; i < synth.getNumVoices(); ++i)
        if (auto* voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
            voice->setParams(vp, vm);

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

juce::AudioProcessorEditor* Vibe404AudioProcessor::createEditor()
{
    return new Vibe404AudioProcessorEditor(*this);
}

void Vibe404AudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void Vibe404AudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if (xml != nullptr && xml->hasTagName(apvts.state.getType()))
        apvts.replaceState(juce::ValueTree::fromXml(*xml));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Vibe404AudioProcessor();
}
