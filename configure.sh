#!bin/sh
cd allLibs
mkdir -p temp_src
git clone https://github.com/davidsiaw/SDL2.git temp_src/SDL2-2
./temp_src/SDL2-2/configure --prefix $(PWD)/SDL2_lib/
make
make install
make clean
rm -rf temp_src/SDL2-2
git clone https://github.com/davidsiaw/SDL2_image.git temp_src/SDL2_image
./temp_src/SDL2_image/configure --prefix $(PWD)/SDL2_lib/
make
make install
make clean
rm -rf temp_src/SDL2_image
git clone https://github.com/davidsiaw/SDL2_mixer.git temp_src/SDL2_mixer
./temp_src/SDL2_mixer/configure --prefix $(PWD)/SDL2_lib/
make
make install
make clean
rm -rf temp_src/SDL2_mixer
 