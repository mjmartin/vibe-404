juce_add_plugin(Vibe404Synth
    FORMATS VST3 AU Standalone
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    PLUGIN_CODE Vi04
    PLUGIN_MANUFACTURER_CODE Vibe
    PRODUCT_NAME "Vibe404"
    COMPANY_NAME "Vibe"
    BUNDLE_ID "com.vibe.vibe404"
    PLUGIN_MANUFACTURER_URL "https://github.com/vibe404"
    VST3_CATEGORIES "Instrument|Synth"
    AU_MAIN_TYPE kAudioUnitType_MusicDevice
)

target_sources(Vibe404Synth
    PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginEditor.cpp
        Source/dsp/PolyBlepOscillator.cpp
        Source/dsp/CurvedADSR.cpp
        Source/dsp/SVFilter.cpp
        Source/dsp/LFO.cpp
        Source/dsp/Distortion.cpp
        Source/dsp/SynthVoice.cpp
        Source/gui/Vibe404LookAndFeel.cpp
        Source/gui/LabelledKnob.cpp
        Source/gui/WaveformSelector.cpp
        Source/gui/SectionPanel.cpp
        Source/gui/panels/Osc1Panel.cpp
        Source/gui/panels/Osc2Panel.cpp
        Source/gui/panels/MixPanel.cpp
        Source/gui/panels/EnvelopePanel.cpp
        Source/gui/panels/FilterPanel.cpp
        Source/gui/panels/LFOPanel.cpp
        Source/gui/panels/DistortionPanel.cpp
)

target_compile_definitions(Vibe404Synth
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

juce_generate_juce_header(Vibe404Synth)

target_link_libraries(Vibe404Synth
    PRIVATE
        juce::juce_audio_utils
        juce::juce_audio_processors
        juce::juce_dsp
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
