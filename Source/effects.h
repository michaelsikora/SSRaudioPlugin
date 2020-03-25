/*
  ==============================================================================

    effects.h
    Created: 18 Mar 2020 2:24:54pm
    Author:  michaelsikora

  ==============================================================================
*/

#pragma once

// simple Distortion effect from this forum question:
// https://www.kvraudio.com/forum/viewtopic.php?t=517331

inline float distortion(float input) {
	float output = 0.1 * tanh(50 * input);
	return output;
}

inline void applyDistortion(AudioBuffer<float>& buf)
{
	for (int i = 0; i < buf.getNumChannels(); ++i)
	{
		float* chanbuf = buf.getWritePointer(i);
		for (int j = 0; j < buf.getNumSamples(); ++j)
		{
			chanbuf[j] = distortion(chanbuf[j]);
		}
	}
}
