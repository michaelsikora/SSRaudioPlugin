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

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SoundScapeRendererAudioProcessorEditor::SoundScapeRendererAudioProcessorEditor (SoundScapeRendererAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p), valueTreeState (vts), footer (p.getOSCParameterInterface())
{
    // ============== BEGIN: essentials ======================
    // set GUI size and lookAndFeel
    setSize(500, 300); // use this to create a fixed-size GUI
    //setResizeLimits (500, 300, 800, 500); // use this to create a resizable GUI
    setLookAndFeel (&globalLaF);

    // make title and footer visible, and set the PluginName
    addAndMakeVisible (&title);
    title.setTitle (String ("SoundScape"), String ("Renderer"));
    title.setFont (globalLaF.robotoBold, globalLaF.robotoLight);
    addAndMakeVisible (&footer);
    // ============= END: essentials ========================

/*
    // create the connection between title component's comboBoxes and parameters
    cbInputChannelsSettingAttachment.reset (new ComboBoxAttachment (valueTreeState, "inputChannelsSetting", *title.getInputWidgetPtr()->getChannelsCbPointer()));
    cbNormalizationSettingAttachment.reset (new ComboBoxAttachment (valueTreeState, "useSN3D", *title.getOutputWidgetPtr()->getNormCbPointer()));
    cbOrderSettingAttachment.reset (new ComboBoxAttachment (valueTreeState, "outputOrderSetting", *title.getOutputWidgetPtr()->getOrderCbPointer()));
*/
    addAndMakeVisible (slParam1);
    slParam1Attachment.reset (new SliderAttachment (valueTreeState, "loc1x", slParam1));
    addAndMakeVisible (slParam2);
    slParam2Attachment.reset (new SliderAttachment (valueTreeState, "loc1y", slParam2));
    

//    chooseHrirFile();
    
    // start timer after everything is set up properly
    startTimer (20);
}

SoundScapeRendererAudioProcessorEditor::~SoundScapeRendererAudioProcessorEditor()
{
    setLookAndFeel (nullptr);
}

//==============================================================================
void SoundScapeRendererAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (globalLaF.ClBackground);
}

void SoundScapeRendererAudioProcessorEditor::resized()
{
    // ============ BEGIN: header and footer ============
    const int leftRightMargin = 30;
    const int headerHeight = 60;
    const int footerHeight = 25;
    Rectangle<int> area (getLocalBounds());

    Rectangle<int> footerArea (area.removeFromBottom (footerHeight));
    footer.setBounds (footerArea);

    area.removeFromLeft (leftRightMargin);
    area.removeFromRight (leftRightMargin);
    Rectangle<int> headerArea = area.removeFromTop (headerHeight);
    title.setBounds (headerArea);
    area.removeFromTop (10);
    area.removeFromBottom (5);
    // =========== END: header and footer =================


    // try to not use explicit coordinates to position your GUI components
    // the removeFrom...() methods are quite handy to create scalable areas
    // best practice would be the use of flexBoxes...
    // the following is medium level practice ;-)
    Rectangle<int> sliderRow = area.removeFromTop (50);
    slParam1.setBounds (sliderRow.removeFromLeft (150));
    slParam2.setBounds (sliderRow.removeFromRight (150));

}

void SoundScapeRendererAudioProcessorEditor::timerCallback()
{
    // === update titleBar widgets according to available input/output channel counts
    title.setMaxSize (audioProcessor.getMaxSize());
    // ==========================================

    // insert stuff you want to do be done at every timer callback
}

void SoundScapeRendererAudioProcessorEditor::chooseHrirFile()
{
    FileChooser myChooser ("Please select the hrir you want to load...",
                           File::getSpecialLocation (File::userHomeDirectory),
                           "*.wav");
                           
    if (myChooser.browseForFileToOpen())
    {
      //  auto file = myChooser.getResult();
     //   juce::String filePath = juce::String(file.getFullPathName());
//        printDebugMessage(filePath.toStdString(), 5);
       // printDebugMessage(filePath.toStdString(), 5);
    }
}
