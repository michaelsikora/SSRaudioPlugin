
### Author: Michael Sikora
### Date: 16.03.2020
### Project: A Self-Contained audio plugin for the SoundScapeRenderer software. The SoundScape Renderer software is hosted [here (SSR repository)](https://github.com/SoundScapeRenderer/ssr).

### Example Audio

https://soundcloud.com/paper_architect/ssrtestvoicereading

### Development Environment:
**OS** - Linux Ubuntu 18.04.4 LTS

**compiler** - gcc 7.5.0

**DAW** - Reaper version 5.978

To compile you can use the Makefile in the main directory. Run make setup if you get the compiler error requesting the ssr and apf functions be explicitly defined as inline. For example:

```shell
make setup
make
make install
```

The compiled binary is installed in the bin/ directory as well as the system vst3 directory. 

The JUCE git repository is added as a submodule.
Make sure the global paths in Projucer point to a valid JUCE path before compiling.  


