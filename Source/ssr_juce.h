/* 
* Point of Contact: Michael Sikora
* Email: sikora@student.chalmers.se
* Date: 2020.02.20
* 
* Purpose: Generalized C++ class for SSR renderers
* for use in the JUCE plugin framework
* 
*
*/

#pragma once

//#ifndef SSR_JUCE_H
//#define SSR_JUCE_H

#include <string>
#include <vector>

#define APF_MIMOPROCESSOR_SAMPLE_TYPE float

#define SSR_SHARED_IO_BUFFERS 1
  
#include "apf/pointer_policy.h"

//#include "src/geometry.h"  // for ssr::quat
//#include <gml/util.hpp>  // for gml::radians()

#include "effects.h" // for using distortion effect

template<typename Renderer>
class SsrJuce
{    
    public:
        using sample_type = typename Renderer::sample_type;
        
        explicit SsrJuce()
            : _engine(_setup_default_parameters())
        {
            _engine.load_reproduction_setup();  
        }
        ~SsrJuce(){}
        
        // This is a distortion effect to test the callback works
        inline void simpleAudioCallback(AudioBuffer<float>& buffer){
            applyDistortion(buffer);
        }
        
        // This is the callback to run the renderer on the buffer
        inline void rendererCallback(AudioBuffer<float>& buffer){
//            float** tempData = buffer.getArrayOfWritePointers();
            float* tempData = buffer.getWritePointer(0);
            float* const* channelData = &tempData;
            _engine.audio_callback(buffer.getNumSamples(), channelData, channelData);
        }
    
    private:
    
        apf::parameter_map _setup_default_parameters(){
            apf::parameter_map params;
            
            params.set("in_channels", 2);
            params.set("out_channels", 2);
            params.set("threads",1);
//            params.set("reproduction_setup", );
            params.set("hrir_file", "eq_filter_fabian_min_phase.wav");
            params.set("hrir_size", 0);
//            params.set("block_size", block_size());
//            params.set("sample_rate", sample_rate());
            
            return params;
        }
        
        
    Renderer _engine;
    
    int _in_channels;
    std::vector<sample_type*> _inputs, _outputs;
    std::vector<std::string> _source_ids;    
};

//#endif // SSR_JUCE_H
