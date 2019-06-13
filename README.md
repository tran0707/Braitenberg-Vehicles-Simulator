### Project Overview

In this iteration, you will begin understanding the design of an existing simulation and then, update and augment the design, tests, and code to simulate the behavior of Braitenberg Vehicles. Braitenberg Vehicles (which we also refer to as Robots) are the thought experiments of Valentino Braitenberg, who imagined complex behavior emerging from simple design. His vehicles exhibit aggression, fear, exploration, and love through simple sensor-motor connections. You should review the following links to thoroughly  familiarize yourself with Braitenberg Vehicles.

- <a href="https://en.wikipedia.org/wiki/Braitenberg_vehicle" target="_blank">https://en.wikipedia.org/wiki/Braitenberg_vehicle</a>
- <a href="https://en.wikipedia.org/wiki/Valentino_Braitenberg" target="_blank">https://en.wikipedia.org/wiki/Valentino_Braitenberg</a>
- <a href="http://robohub.org/simple-robots-complex-behaviors-a-control-systems-perspective-on-braitenberg-vehicles/" target="_blank"> http://robohub.org/simple-robots-complex-behaviors-a-control-systems-perspective-on-braitenberg-vehicles/</a> (Watch this video for a quick, informative lesson on Braitenberg Vehicles).
- <a href="https://mitpress.mit.edu/books/vehicles" target="_blank">https://mitpress.mit.edu/books/vehicles</a>

The overall goal of the software project for this course is for you to develop a rudimentary robot simulator in which robot behavior is visualized within a graphics window, and to set up, observe, and document the results of experiments involving the entities in the simulator. The robots will be modeled after Braitenberg Vehicles, which use a simple design to realize complex behavior. The environment will have multiple robots, as well as stimuli such as lights and food. Robots will exhibit different behavior when they sense the stimuli in the environment, depending on their sensor-motor connections related to that stimulus. For example, some robots will be attracted to the light and some fear the light.

Iteration 1 is intended to introduce you to the problem domain, software development process, and code base you will be working with - and to get you more familiar with many of the tools and technologies that have been introduced to you to date (Git, Doxygen, UML, the C++ language, the C++ complier, Google style (compliant with cpplint), the build process (make), and design patterns).

Teaching staff will also be working diligently to provide the structure and support for development, testing, and documentation. Automation in unit testing, style compliance, in-house Github testing, and documentation will make this an easier process, however it means that you will have to develop within the constraints of these systems. Often there is a learning curve and a lot of systems trouble-shooting to get it all working, so start early!

<hr>

### Implementation Framework

You are being provided with a significant initial code base for this iteration. The first iteration is focused on enhancing functionality and getting practiced in the software design and development process. It is also a drop into the depths of C++ syntax. If you have any questions about the provided code, please ask. We do not expect you to understand all the constructs in this code. Below is an outline of the required functionality.

The code is organized such that robot behavior in the arena (i.e. the model) is separate from visualization (i.e. the view), which allows for automated unit testing using Google Test. There is also a controller that handles the communication between the model and the view. The Robot class is composed of many other classes that control various aspects of robot behavior and environment interaction. You will need to maintain this class structure to interface with Google Tests.

#### Robot Arena

The robot arena has entities that are specified in a configuration file. The intent is for the robots specified in the configuration file to carry out their behavior in the Arena with the other entities specified in the configuration file (lights and food). For example:
<ol>
<li>Besides the explore behavior, robots can be configured to exhibit love, fear, and or aggression toward food and/or light entities in the Arena </li>
<li> If a robot bumps into another robot or the wall it should reverse (turn around 180 degrees); advance for 20 simulation time steps, and then turn LEFT 45 degrees (from its current heading) to avoid another collision with the object it collided with. </li>
<li>A robot will change color to illustrate the sensor that is driving its behavior (food or light) </li>
</ol>

##### None of the functionality specified in the numbered items above is implemented in the base code. You will design it and implement it in this iteration.

#### Graphics Environment

The graphics environment consists primarily of a single window with robots, lights, and food. All objects (except for the wall) in the environment will be composed of circles, which greatly simplifies collision detection. You are welcome to add graphics enhancements, such as color, text, or decorations provided it does not interfere with required functionality. The basic graphics window framework has been provided. You will need to get familiar with the graphics library and with the provided code to learn how to draw objects of particular shape in the environment.

#### Graphical User Interface (GUI) and User Input (UI)

A basic GUI with user buttons and input via mouse and keyboard has been provided. The user currently has the following controls:

-  UI buttons Play and Reset
--  Press the Play  button to start the simulation.  Pressing the Play button again pauses the simulation.
--  The Reset button reloads the configuration file, so the simulation starts from the initial configuration
- UI Entity Button
--Pressing the Entity button enables a user to select and review and/or set the behaviors associated with an Entity in the Arena.

For example, when the default configuration file (default.json) is used to run the simulation:
<ul>
<li> there is one (mobile) Light entity, one (stationary) food entity, and one Braitenberg vehicle with default behavior toward light (meaning the robot ignores input from its light sensor) and explore behavior toward food. </li>
<li> The Entity button GUI enables the user to select a robot in the Arena and then change the robot's behavior toward food (to love, cower, explore, or default) and/or light (to aggressive, love, cower, or explore) - or to leave the current behavior in place.  </li>
<li>The GUI also enables the user to turn the robot's mobility off. </li>
<li>If the user selects a light via the Entity button, the user can turn the light's mobility on or off as well.</li>
</ul>

<hr>

### Compiling and Running the Simulation

After merging the iteration 1 code into your _devel_ branch, as discussed in lab10, you can compile the simulation with `make` at the top level of the project directory.

Unfortunately, despite valiant efforts by the TA's to keep the instructors from tinkering with the code after they declared a code freeze, your instructors have mistakenly left a few errors in your program.  **You ARE REQUIRED to complete lab10_advanced_git, and follow the process of finding, fixing, reporting, and tracking the errors (issues) using Git and GitHub issues before making ANY changes indicated here to the software that we have provided for you for iteration 1.**

After completing lab 10, you will have successfully created the simulation executable named <strong> arenaviewer </strong>, which can be found in the directory <strong> build/bin </strong> (assuming you are at the top level of your project directory). You can execute it from the top-level directory of your project directory (where you just "made" the simulation executable) by typing:

```
./build/bin/arenaviewer  scenes/default.json
```

Note, we have provided simulation configuration files to help you test your changes to the simulation - they are specified in JavaScript Object Notation (JSON) and can be found in the scenes directory / folder.  You can create you own configuration file as well!  You should review the following resources to familiarize yourself with JSON:

- <a href="https://en.wikipedia.org/wiki/JSON" target="_blank">https://en.wikipedia.org/wiki/JSON</a>
- <a href="https://www.copterlabs.com/json-what-it-is-how-it-works-how-to-use-it/" target="_blank">https://www.copterlabs.com/json-what-it-is-how-it-works-how-to-use-it/</a>
<p>
The JSON files are used to configure:
<ol> <ol>
<li> the size of the Arena, </li>
<li> the number of Food entities in the Arena, </li>
<li> the number of Light entities in the Arena, </li>
<li> and the number of Robot entities in the Arena</li>
</ol></ol>
when the simulation is initialized.
</p>
The initial position and radius of each entity in the Arena (Robots, Lights, and Food) must also be specified.
<ul>
<li>For food, heading (which should be 0.0 degrees) should also be specified </li>
<li> For robots, in addition to position, heading (in degrees) and sensor behavior toward light and food entities must be specified </li>
</ul>

<hr>
## <a name="resources">Resources</a>

Graphics Libraries :
- https://github.com/wjakob/nanogui
- https://nanogui.readthedocs.io/en/latest/
- https://github.com/memononen/NanoVG
- https://www.opengl.org/

Local System and Compilation:
- Repo: https://github.umn.edu/umn-csci-3081-S19/csci3081-shared-upstream
- Linking library: `/project/bin/obj/
- Compilation: https://gcc.gnu.org/
- Linux quick reference: http://www-users.cs.umn.edu/~larson/repo-website-resources/website/examples/csresources/linux.html
- Makefile Resources: http://www-users.cs.umn.edu/~larson/repo-website-resources/website/examples/csresources/cpp.html

Testing:
- https://github.com/google/googletest
- Unit Testing: https://martinfowler.com/bliki/UnitTest.html

Style:
- https://google.github.io/styleguide/cppguide.html
- https://github.com/google/styleguide/tree/gh-pages/cpplint
- https://www.python.org/downloads/

Documentation:
- http://www.stack.nl/~dimitri/doxygen/
- https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet

IDEs:
- Xemacs: https://www.xemacs.org/
- vi: http://www.lagmonster.org/docs/vi.html
- Atom: https://atom.io/
- Sublime: https://www.sublimetext.com/
- Eclipse: https://eclipse.org/

<hr>
