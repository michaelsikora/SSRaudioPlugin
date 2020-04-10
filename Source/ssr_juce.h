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

#include <string>
#include <vector>

//#include "src/geometry.h"  // for ssr::quat
//#include <gml/util.hpp>  // for gml::radians()

#define SSR_SHARED_IO_BUFFERS

#define ERR(msg) printDebugFile(msg)

#include "../ssr/apf/apf/pointer_policy.h"

#include "effects.h" // for using distortion effect

#include "linuxDebugTools.h" // for printing debug messages

template<typename Renderer>
class SsrJuce
{    
    public:
        explicit inline SsrJuce(int ins = 2, int outs = 2, int sampleRate = 44100, int blockSize = 2048)
            : _engine(Renderer(setEngineParams(ins, outs, 1, sampleRate, blockSize))),
              _in_channels(ins),
              _out_channels(outs)
        {
        }
        
        ~SsrJuce(){}
        
        // Setup the reproduction setup (outputs) and the sources (inputs) of the renderer
        // Called from prepareToPlay
        inline void setupIO()
        {
            // setup outputs
            try {
                this->_engine.load_reproduction_setup();
            } catch(const std::exception& e) {
                printDebugFile(std::string(e.what()));
            }
            
            _inputs.resize(_in_channels);
            _outputs.resize(_out_channels);
            
            // setup inputs
            try {
                for (size_t i = 0; i < _in_channels; ++i)
                {
                    auto id = _engine.add_source("");
                    this->_engine.get_source(id)->active = true;
                    _source_ids.push_back(id);
                }
            
                this->_engine.activate();  // start parallel processing (if threads > 1) 
            } catch(const std::exception& e) {
                printDebugFile(std::string(e.what()));
            }
        }
        
        
        // This is a distortion effect to test the callback works
        inline void simpleAudioCallback(AudioBuffer<float>& buffer)
        {
            applyDistortion(buffer);
        }
        
        
        // This is the callback to run the renderer on the buffer
        inline void rendererCallback(AudioBuffer<float>& buffer)
        {
            float* const* channelData = buffer.getArrayOfWritePointers();
            this->_engine.audio_callback(buffer.getNumSamples(), channelData, channelData);
        }
         
    private:
        
        apf::parameter_map setEngineParams(int inputs, int outputs, int threads
            , int sample_rate, int block_size)
        {
            apf::parameter_map params;

            params.set("threads", threads);
//            params.set("reproduction_setup", "2.0.asd");
            params.set("hrir_file", "/home/michaelsikora/opt/SoundScapeRenderer/ssr/data/impulse_responses/hrirs/hrirs_fabian_min_phase_eq.wav");
//            params.set("hrir_file", "data/impulse_responses/hrirs/hrirs_fabian_min_phase.wav");
            params.set("hrir_size", 0);
            params.set("block_size", block_size);
            params.set("sample_rate", sample_rate);
            
            _in_channels = inputs;
            _out_channels = outputs;
            
            return params;
        }
        
    Renderer _engine;
    
    int _in_channels, _out_channels;
    std::vector<float*> _inputs, _outputs;
    std::vector<std::string> _source_ids;    
};

