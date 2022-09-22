# mobilerobots

cd /usr/local/Aria
make clean
make -j4

cd ~/catkin_ws/src
git clone https://github.com/amor-ros-pkg/rosaria.git

cd ~/catkin_ws/
catkin_make

