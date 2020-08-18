# Author: Michael Sikora

BUILD_DIR = Builds/LinuxMakefile

.PHONY = main_project

main_project:
	$(MAKE) -C $(BUILD_DIR) -j4

setup:
	# adds inline keywords to ssr to prevent compiler errors
	cp binauralrenderer_inline.h ./ssr/src/binauralrenderer.h
	cp convolver_inline.h ./ssr/apf/apf/convolver.h

clean:
	$(MAKE) -C $(BUILD_DIR) clean

install:
	# install in local bin
	cp $(BUILD_DIR)/build/SoundScapeRenderer.so ./bin/SoundScapeRenderer.so
	# install in system vst3 directory
	cp $(BUILD_DIR)/build/SoundScapeRenderer.so $(HOME)/.vst3/SoundScapeRenderer.so
	# install in shared Windows drive
	# cp $(BUILD_DIR)/build/SoundScapeRenderer.so /mnt/hgfs/CHALMERS/SoundScapeRenderer.so

