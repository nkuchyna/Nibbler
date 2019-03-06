#!/bin/bash
git clone https://github.com/vinzmq/SDL_lib.git SDL
git clone https://github.com/vinzmq/SFML.git SFML
git clone https://github.com/vinzmq/glm.git glm
brew install glm
brew install ftgl
brew install sfml
brew install cmake
cd ./glm/test/
cmake ..
#cd SFML/lib
#export LD_LIBRARY_PATH=$PWD
