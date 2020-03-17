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
  
#include "apf/pointer_policy.h"

//#include "src/geometry.h"  // for ssr::quat
//#include <gml/util.hpp>  // for gml::radians()

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
        
        
    Renderer _engine;
        
    private:
    
        apf::parameter_map _setup_default_parameters(){
            apf::parameter_map params;
            
//            params.set("in_channels", 64);
//            params.set("out_channels", 64);
            params.set("threads",1);
//            params.set("reproduction_setup", );
//            params.set("hrir_file", );
//            params.set("block_size", block_size());
//            params.set("sample_rate", sample_rate());
            
            return params;
        }
        
    int _in_channels;
    std::vector<sample_type*> _inputs, _outputs;
    std::vector<std::string> _source_ids;    
};

//#endif // SSR_JUCE_H
