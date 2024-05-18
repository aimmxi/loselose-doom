# loselose-doom
 A fork of dsda-doom inspired by Lose/Lose and a recreation of DOOM/DOOM from Vargskelethor's HML stream.

 ## Rules
 Upon killing an enemy a random file will get picked and deleted from the filesystem. 
 **PLAY AT YOUR OWN RISK**

## Building
This modification heavily relies on Linux' file hierarchy, so it probably won't work on Windows.

1) Download all required dependencies. For Ubuntu based distros this should be enough:
```
apt-get install libsdl2-dev libsdl2-image-dev \
         libsdl2-mixer-dev libfluidsynth-dev \
         libportmidi-dev libmad0-dev libdumb1-dev \
	        libvorbis-dev cmake make git libzip-dev
```
2) Clone the repository:
```
	git clone https://github.com/aimmxi/loselose-doom.git
```
3) Build the project:
```
	cd loselose-doom
	cmake -Sprboom2 -Bbuild -DCMAKE_BUILD_TYPE=Release -DENABLE_LTO=ON
	cmake --build build
```

After that, the main binary will be available on the build folder.

 ## How it works
 A new loselose-doom.c file has been created in the prboom2/src directory. It contains a remove_random() function which calls random_file() to get a random file and deletes it afterwards.
 The random_file() function first picks a starting folder, travels randomly to some of its children and picks a file. 
 p_inter.c's P_KillMobj has been modified to call remove_random(), so that when you kill an enemy, everything described above happens.

It's not efficient by any means and hiccups are noticeable after killing a bunch of enemies, but being efficient and stable is not the point of this fork.
