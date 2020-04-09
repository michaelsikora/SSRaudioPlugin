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

//#include "src/geometry.h"  // for ssr::quat
//#include <gml/util.hpp>  // for gml::radians()

#include "../ssr/apf/apf/pointer_policy.h"
#include "../ssr/src/legacy_source.h"

#include "effects.h" // for using distortion effect

#include "linuxDebugTools.h"

template<typename Renderer>
class SsrJuce
{    
    public:
        using sample_type = typename Renderer::sample_type;
        
        explicit inline SsrJuce(int ins = 2, int outs = 2, int sampleRate = 44100, int blockSize = 2048)
            : _engine(new Renderer(setEngineParams(ins, outs, 1, sampleRate, blockSize)))
        {
            _in_channels = ins; 
            _out_channels = outs;
                      
//            printDebugMessage("Number_of_input_channels_is_" + std::to_string(_in_channels), 3);
            printDebugMessage("Number_of_output_channels_is_" + std::to_string(_out_channels), 3);
//           printDebugMessage("SsrJuceConstructed", 3);
           
        }
        
        ~SsrJuce(){ delete _engine; }
        
        inline void setupIO()
        {
            this->_engine->load_reproduction_setup();
            
            printDebugMessage("reproduction_setup_loaded", 3);
            
            _inputs.resize(_in_channels);
            _outputs.resize(_out_channels);
            
            for (size_t i = 0; i < _in_channels; ++i)
            {
                auto id = _engine->add_source("");
                this->_engine->get_source(id)->active = true;
                _source_ids.push_back(id);
            }
            
            this->_engine->activate();  // start parallel processing (if threads > 1) 
        
        }
        
        
        // This is a distortion effect to test the callback works
        inline void simpleAudioCallback(AudioBuffer<float>& buffer)
        {
            applyDistortion(buffer);
        }
        
        // This is the callback to run the renderer on the buffer
        inline void rendererCallback(AudioBuffer<float>& buffer)
        {
            float* tempData = buffer.getWritePointer(0);
            float* const* channelData = &tempData;
            //float* const* channelData = buffer.getArrayOfWritePointers();
            _engine->audio_callback(buffer.getNumSamples(), channelData, channelData);
        }
         
    private:
        
        apf::parameter_map setEngineParams(int inputs, int outputs, int threads
            , int block_size, int sample_rate)
        {
            apf::parameter_map params;
            
            params.set("in_channels", inputs);
            params.set("out_channels", outputs);
            params.set("threads", threads);
            params.set("reproduction_setup", "2.0.asd");
//            params.set("hrir_file", "eq_filter_fabian_min_phase.wav");
//            params.set("hrir_size", 0);
            params.set("block_size", block_size);
            params.set("sample_rate", sample_rate);
            
            _in_channels = inputs;
            _out_channels = outputs;
            
            return params;
        }
        
    Renderer* _engine;
    
    int _in_channels, _out_channels;
    std::vector<sample_type*> _inputs, _outputs;
    std::vector<std::string> _source_ids;    
};

//#endif // SSR_JUCE_H
