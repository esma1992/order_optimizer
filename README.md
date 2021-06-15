# order_optimizer
Simple examle of ROS/C++ usage

# prerequirements
## install yaml-cpp 
- download yaml-cpp git project (https://github.com/jbeder/yaml-cpp.git) and install CMake (if you don't have root privileges, just install to a local directory, like ~/bin)
- from the source directory, run:
```
mkdir build
cd build
cmake ..
```

and then the usual

```
make
make install
```
**Note:** package is already integrated in CMake file.

# build node
## start ros2
- open linux terminal
- run
```
. ~/ros2_foxy/install/local_setup.bash
```
**Note:** at least this was by me, since I did all installations according to https://docs.ros.org/en/foxy/Installation/Ubuntu-Development-Setup.html

## clone my project
- run
```
git clone https://github.com/esma1992/order_optimizer.git
```
then navigate inside the project
```
cd order_optimizer
```
## install all depedencies with rosbuild
- run
```
rosdep install -i --from-path src --rosdistro foxy -y
```
**Note:** you are still in same terminal
## build node
- run
```
colcon build --packages-select order_optimizer
```
**Note:** you are still in same terminal
## source the setup files
- open new terminal
- navigate to our git project
```
cd .......git/order_optimizer
```
- run
```
. install/setup.bash
```
**Note:** you are now in second terminal

# start rviz
- to start rviz please run
```
ros2 run rviz2 rviz2
```
- add there MarkerArray

# run node 
our project has 2 nodes:
- SendOrder: sends input info about the order
- OrderOptimizer: receives order infos and do all logic of the project

## OrderOptimizer
To start this node please use one of already configured/set terminals.

Usage:
```
Usage: ros2 run order_optimizer OrderOptimizer 
       -p     ->     path to configuration files
```

Example of usage:
```
ros2 run order_optimizer OrderOptimizer -p /home/knapp/git/order_optimizer/etc
```

**Note:**
- input parameter path (-p) is required
- program checks if all input parameters are given
- program checks if path is real

### OrderOptimizer steps
- parse input arguments and check their values - path musst be real
- parse given yaml configuration file about products - with structs and vectors, since these values are constant, that happens only once
- subscribe to topics (currentPosition and nextOrder)
- pick up values
- according to given order id parse all yaml order files (parallel - threads)
- pick up all neccessary information about order (cx, cy, list of products - here is my idea to merge products information with order in same variable it is easier to manipulate with data)
- since now we have all places/parts in one variable, we create correlation matrix with size 
```
first position + positions of all parts + order destination
```
where matrix contains all distances between parts
- this matrix is input for dijkstra algorithm (stolen code from internet, but it is suspicious - I should research other algorithms or create my own logical alg.)
- results are printed in console - path (coordinates) of robot
- results are also published to topic order_path

**Note:**
- to check data published to topic order_path please look inside the rviz program

**Conclusion**
This node is used to send order to our robot

## SendOrder
To start this node please use one of already configured/set terminals.

Usage:
```
Usage: ros2 run order_optimizer SendOrder 
       -id    ->    order id
       -de    ->    order description
       -x     ->    x coordinate of current position
       -y     ->    y coordinate of current position
```

Example of usage:
```
ros2 run order_optimizer SendOrder -id 1000001 -x 6.6 -y 58.2 -de "some desciption"
```

**Note:**
- all input parameters are required
- program checks if all input parameters are given
- if we use more words by description we need to write it inside the "" signs. Otherwise the program will be stopped with the output message "Usage ..."
- program checks if id is number (int)
- program checks if x coordinate is number (if it can be converted to double)
- program checks if y coordinate is number (if it can be converted to double)

### SendOrder steps
- parse input arguments and check their values
- send given order publishing to given topis (currentPosition and nextOrder)

**Conclusion**
This node is used to send order to our robot

# My feedback
There is a lot of things I need to fix and optimize:
- change data types of publisher and sender for topics currentPosition and nextOrder
- probably I should parse my code in .cpp and .h files
- usage of TDD to have chance to do unittesting - in this case it hard - it is possible by mocking
- delete specific order from yaml file after its path is already calculated/found - it makes more sense - then I can also check if order id is in one of files, if not I need to write some message: order already sent or not exists...
- name of cpp files are not appropriate
- I should research other algorithms or create my own logical alg. to find shortest path

CI:
- I have not used direct GIT actions yet... I started to read about that ....
- what I know is to set a VM, connect Jenkins with VM and then execute what I will
- unittests - I commented them (depedency issues)

General:
- should gain knowledge with cpp libraries and cmake files - now I see how much company-libraries I use and dont have to thing about them...
- I deleted my VM from Mobile Robots - I could copy many things from there :(
- Task was funny :)
