### CSCI3081W: Iteration 2 Submission Checklist

>The iteration 2 code and documentation is due on Monday, April 15th at 11:55pm


Please ensure that this file is in your /docs folder. Place an 'x' in each of the `[ ]` boxes for items that are complete. Push this completed checklist to github. When it displays on Github, it will show an actual checkbox with a check mark.


### Compilation and Execution


- [X]  cloned **fresh** from github onto a cselabs machine to test compilation, style compliance, and execution
- [X] Submission is on the **master** branch in the project folder of your repo
- [X] _/project_ folder exists   <<<< I think we can remove this one.
- [X] _/build_ is not in the repo
- [X] _/html_  and _/latex_ is not in _docs_
- [X] **__`make` from within _project_ completes without error.__**
- [X] `./../build/bin/arenaviewer` executes without assert or a seg fault
- [X] `./../build/bin/unittest` executes without a seg fault
- [X] **_"make check-style" reports no errors when run in the master branch._**
- [X] `doxygen docs/Doxyfile` compiles and creates the html pages for all classes without errors.


### Functionality Checklist


> To expedite grading, you need to provide the status of your simulation and each of the requirements. Do not lie about the status!! You might get partial credit for incomplete or erroneous functionality, however, if you fail to inform us of the issue, then you will lose more (or all) the points for that functionality since we cannot partially grade it.

>If your source code or unit tests **do not compile** or if there is an obvious **seg fault** in either the arenaviewer or the unit tests, **__YOU MUST MODIFY THE COMMENT NEXT TO THE CHECKBOX BELOW__** to let us know what the problem is or you will lose all points for that item.

- [X] I have compiled and executed both the source code and unit tests using a fresh clone of my repo. They compile and execute without segmentation faults.

**__Next, please place an 'X' in the appropriate box for each requirement.__**

- Good = Fully Implemented. No _known_ bugs. No _obvious_ bugs.
- Okay = Works but some bugs (recorded as a bug/issue on github).
- Help = Attempted but not working.
- Time = No to Little Progress

| Functionality | Good | Okay | Help | Time |
| ------------- | ---- |----- | ---- | ---- |
| **__Priority Level 1__** |
| Braitenberg Vehicle Love Behavior implemented and operational. | X |  |  |  |
| Braitenberg Vehicle Explore Behavior implemented and operational. | X |  |  |  |
| Braitenberg Vehicle Coward Behavior implemented and operational. | X |  |  |  |
| Braitenberg Vehicle Aggression Behavior  implemented and operational. | X |  |  |  |
| Braitenberg Vehicle None Behavior  implemented and operational. | X |  |  |  |
| Strategy Pattern implemented and operates using Braitenberg Vehicle Behavior Classes. | X |  |  |  |
| Braitenberg Vehicle (BV) sensors implemented within the BV class, and are operational (used in the simulation). | X |  |  |  |
| The GUI includes an option to select robot/bv behavior. | X |  |  |  |
| The bv wheel velocity is incorporated into the total wheel velocity | X |  |  |  |
| “robot_behavior” in the JSON has been tested | X |  |  |  |


| Functionality | Good | Okay | Help | Time |
| ------------- | ---- |----- | ---- | ---- |
| **__Priority Level 2__** |
| Observer Pattern implemented and operational (wheel velocities for the Braitenberg Vehicle "Subject" are displayed in real time in the simulation control panel). | X |  |  |  |
| Simulation Control Panel updated to enable selection of any one Braitenberg Vehicle as the "Subject" whose wheel velocities are displayed. | X |  |  |  |
| JSON file or files updated to include configuration of a Predator.  | X |  |  |  |
| Predator class implemented and operational. | X |  |  |  |
| Predator consumes Braitenberg Vehicles. | X |  |  |  | 
| Braitenberg vehicles turn into "ghosts" as specified in the Iteration 2 requirements document (Iteration2Requirements.md), when consumed. | X |  |  |  |


| Functionality | Good | Okay | Help | Time |
| -------- | -------- | -------- | -------- | --------- |
| **__Priority Level 3__** |
| Braitenberg Vehicle (BV) starvation functionality implemented and operational (BV's starve if they do not consume food after 600 simulation time steps). | X |  |  |   |
| Upon starvation, Braitenberg vehicles turn into ghosts as specified in the Iteration 2 requirements document (Iteration2Requirements.md). | X |  |  |  |
| The functionality to dynamically calculate Braitenberg Vehicle wheel velocities based on a weighted combination of wheel velocities is implemented and operational (or behaviors are dynamically modified). Note, you are to design and create the formula to dynamically combine the wheel velocities.  See the iteration 2 requirements (Iteration2Requiments.md) for ideas on how to do this.  | X |  |  |  |

### Documentation

#### IN THIS DOCUMENT, after the checkbox below, provide the following information about your implementation of dynamic wheel velocity calculation:

-In at __**most**__ three sentences, describe your approach to dynamically calculating wheel velocities (e.g. “I used coefficients to weight wheel velocities that depend on the current situation”).

-Indicate the file, method, and line numbers associated with your implementation of dynamically calculated wheel velocities. If it is in multiple places, indicate where the primary functionality resides (e.g. “BraitenbergVehicle::Update on line 255 implements the dynamic equation using the coefficients that are set in BraitenbergVehicle::DetermineCoefficients”).

- [X] The information specified above regarding my implementation of dynamic wheel velocity caculation is as follows:

I implemented the dynamic calculation of WheelVelocity using the reading of all food, light, and BV. 
If any of the three entities above have WheelVelocity reading of 0 then the WheelVelocity will be calculated by adding all left of entity with reading not 0 and divided by the number of entity with reading not 0. Same thing with calcuating the WheelVelocity for the right. If all of readings is not zero, then left and right all divided by 3.
For example, BV reading is (0,0), Food reading is (1,2), and Light reading is (3, 3). Then WheelVelocity will be:
Left = (1 + 3)/2 and right = (2 + 3)/2.
**__Insert the information requested above here__**

#### Design Document

- [X] The final version of the design document includes a description of two different implementations that enable the observation of Braitenberg Vehicle wheel velocities as specified in the the requirements, and one of the implementations discussed should be the implementation of the Observer pattern that you used. Another possibility for comparision to your implementation is to compare it to another implementation of the observer pattern that you did not implement.  In any case, describe your implementation of the observer pattern and one alternative implementation and discuss them as specified in the requirements.
- [X] The final version of your design document for iteration 2 (named **__iteration2\_design.pdf__**) has been submitted via Canvas (See the Iteration 2 Final Design Document Item on Canvas for the submission link).


#### UML

- [X] UML for project can be generated without errors using Doxygen,  and can be viewed in the docs directory.


#### Doxygen

- [X] All classes have a _brief_ description that appears in the Doxygen web page class list.
- [X] The Arena class is fully documented with respect to methods and member variables. In other words, in the html generated pages of Doxygen, the user can click on a class method and see more information about its purpose and parameters.
- [X] The BraitenbergVehicle class is fully documented with respect to methods and member variables.
- [X] All new and updated/refactored code (classes and methods) is fully documented with respect to methods and member variables.
- [X] A landing page that meets the requirements specified in the Iteration 2 Requirements (in the file Iteration2Requiements.md) exists in the file named **__mainpage.h__** and is in the src directory.
- [X] Doxygen successfully generates the main page (verify by running Doxygen and then opening the resulting **_index.html__** page). 
 

### Linter and Git

- [X] All *.h and *.c files pass cpplint.
- [X] The code complies with naming conventions for Classes, ClassMethods, and class\_members\_.
- [X] There exists a history of git commit messages to show effort.
- [X] There exists a history of issues and branches to show effort.
- [ ] Github issues include current unresolved bugs.
- [ ] Github issues include unresolved feature enhancements and refactoring that is due for this iteration.


## Ready For Submission


When everything above is as you want it or the deadline is upon you, it is time to submit!

- [X] I pushed this file and any changes resulting from this checklist.
- [X] Everything is in the **__master__** branch.

_One more thing_ -- check that what you think you pushed was really pushed to github. If you can see it, we can see it. If you can't, we can't.

**Congratulations on your submission!**
