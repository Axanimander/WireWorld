## Simple Implementation of Wire World

# To make it go
* You probably need to install libsfml-dev on Linux

    * on Ubuntu: `sudo apt-get install libsfml-dev`
* Use Git Bash to run build.sh
* Type the command `./build.sh buildrun Release`

# Instructions
* Place Conductors with Shift + left-click
* Place Heads with right-click
* T Remove Conductor Shift + left-click again
* Click and drag to pan




# Features
* Fully segfaultable limited grid
* Fairly fast simulation
* Click-n-Drag
* Completely Accurate Wireworld Simulation
* An FPS Counter!
* Theoretically Cross-platform

# Performance

This simulation is moderately efficient, the simulation only runs on active regions of wire and can therefore be (sparsely)
scaled to a much greater size than if every node was simulated at all times


# Bugs
* Program will segfault if one tries to place up and to the left, expand down and right
# Screenshots


### It really works
![Screen4](/readmeres/Wireworld4.gif)

### For some reason it rotates too, and is fully interactive
![Screen5](/readmeres/Wireworld5.gif)

### Zoom in and out of the simulation plane
![Screen3](/readmeres/Wireworld6.gif)





