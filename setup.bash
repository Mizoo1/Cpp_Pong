 #!/bin/bash         
echo -e "\n---------------------------------------------------"
echo -e " setting up for C++ and SDL2 Development"
echo -e "---------------------------------------------------\n"

sudo apt update
sudo apt upgrade

#Installing GCC
sudo apt install build-essential

# install CMake (optional)
sudo snap install cmake --classic

#install sdl2
sudo apt install libsdl2-dev libsdl2-2.0-0 -y;

#install sdl image  - if you want to display images
sudo apt install libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0 -y;

#install sdl mixer  - if you want sound
sudo apt install libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0 -y;

#install sdl true type fonts - if you want to use text
sudo apt install libfreetype6-dev libsdl2-ttf-dev libsdl2-ttf-2.0-0 -y;

# install SQLite3
sudo apt install sqlite3


# check intalled versions
echo -e "\n---------------------------------------------------"
echo -e " installed versions"
echo -e "---------------------------------------------------\n"
gcc --version
echo -e "---------------------------------------------------"
cmake --version
echo -e "---------------------------------------------------"
echo sqlite3 version:
sqlite3 --version
echo -e "---------------------------------------------------"
