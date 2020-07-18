# ChaiScriptExample
Small project to learn about ChaiScript.
I needed to asses ChaiScript before integration in my game engine, and especially its interactions with an ECS based scene and a math lib. Here's the result.

## What it does
The program simulates the trajectories of several cannonballs shot at various angles. The actual physics simulation is performed by a script, so gravity and drag can be modified without needing to recompile.
Trajectories are exported and can be visualized via the plot.py script.

## What I learned
- Writing ChaiScript bindings for GLM
- Exposing a C++ struct/class to ChaiScript
- Writing ChaiScript bindings for a simplistic scene class organized around EnTT
- Splitting up ChaiScript compilation so as to optimize build times
- Calling C++ functions from Chai
- Calling Chai functions from C++

## Dependencies
glm, EnTT and ChaiScript must be installed and in the path.
The plot.py script uses Numpy and Matplotlib.

## Build (GNU/Linux)
mkdir build; cd build
cmake ..
make chai -j4
