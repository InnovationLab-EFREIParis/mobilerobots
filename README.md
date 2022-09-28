# mobilerobots
## Instalation de la librairie Aria
Cette procedure n'est valable que pour un systeme 64 bits.
Version du systeme lscpu

Installer les paquets mobilesim et libaria situé dans le dossier 01_deb

sudo dpkg -i NOM_DU_PAQUET

## Si problème de dépendance
sudo apt --fix-broken install

## Recompiler la librairie Aria

cd /usr/local/Aria

make clean

make -j4

cd ~/catkin_ws/src

git clone https://github.com/amor-ros-pkg/rosaria.git

cd ~/catkin_ws/

catkin_make

## Exemple d'utilisation de rosaria

https://github.com/pengtang/rosaria_client

