
### Author: Michael Sikora
### Date: 16.03.2020
### Project: A Self-Contained audio plugin for the SoundScapeRenderer software. The SoundScape Renderer software is hosted [here (SSR repository)](https://github.com/SoundScapeRenderer/ssr).

### Example Audio

https://soundcloud.com/paper_architect/ssrtestvoicereading

### Development Environment:
**OS** - Linux Ubuntu 18.04.4 LTS

**compiler** - gcc 7.5.0

**DAW** - Reaper version 5.978

I made two tiny bash scripts to make development a little easier on me. They are run as:

```shell
bash make.sh
bash install.sh
```

The first changes directory to the Linux makefile and runs make using two cores (-j2). The second copies the compiles .so file to the bin/ directory for easy access to the plugin. 

The JUCE git repository is added as a submodule.
Make sure the global paths in Projucer point to a valid JUCE path before compiling. 
For instance, during development the JUCE library was included at /home/michaelsikora/JUCE/. 


