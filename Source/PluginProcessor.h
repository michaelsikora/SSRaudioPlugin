/*
 ==============================================================================
 This file is part of the IEM plug-in suite.
 Author: Daniel Rudrich
 Copyright (c) 2017 - Institute of Electronic Music and Acoustics (IEM)
 https://iem.at

 The IEM plug-in suite is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 The IEM plug-in suite is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this software.  If not, see <https://www.gnu.org/licenses/>.
 ==============================================================================
 */

#pragma once

//#ifndef PLUGIN_PROCESSOR_H
//#define PLUGIN_PROCESSOR_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "../IEMPluginSuite/resources/AudioProcessorBase.h"

//#define APF_MIMOPROCESSOR_SAMPLE_TYPE float
  
#include "ssr_juce.h"

//#include "../ssr/src/binauralrenderer.h"
//#define RendererType ssr::BinauralRenderer

#include "../ssr/src/vbaprenderer.h"
#include "../ssr/src/legacy_source.h"
#define RendererType ssr::VbapRenderer

#define ProcessorClass SoundScapeRendererAudioProcessor

//==============================================================================
class SoundScapeRendererAudioProcessor  :  public AudioProcessorBase<IOTypes::AudioChannels<2>,
                                                                     IOTypes::AudioChannels<2>>
{
public:

    constexpr static int numberOfInputChannels = 2;
    constexpr static int numberOfOutputChannels = 2;
    //==============================================================================
    SoundScapeRendererAudioProcessor();
    ~SoundScapeRendererAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;


    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    void parameterChanged (const String &parameterID, float newValue) override;
    void updateBuffers() override; // use this to implement a buffer update method


    //======= Parameters ===========================================================
    std::vector<std::unique_ptr<RangedAudioParameter>> createParameterLayout();
    //==============================================================================


private:
    //==============================================================================
    // list of used audio parameters
    float *inputChannelsSetting, *outputOrderSetting, *useSN3D, *param1, *param2;
    
    //==============================================================================
    SsrJuce<RendererType> *SsrJuceInstance;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundScapeRendererAudioProcessor)
};

//#endif // PLUGIN_PROCESSOR_H
