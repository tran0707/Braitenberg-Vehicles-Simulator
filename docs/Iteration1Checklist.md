### CSCI3081W: Iteration 1 Submission Checklist

>The iteration 1 code and documentation is due on Friday, March 15th at 11:55pm


Please ensure that this file is in your /docs folder. Place an 'x' in each of the `[ ]` boxes for items that are complete. Push this completed checklist to github. When it displays on Github, it will show an actual checkbox with a check mark.



### Compilation and Execution



- [x]  cloned **fresh** from github onto a cselabs machine to test compilation, style compliance, and execution
- [x] Submission is on the **master** branch in the project folder of your repo
- [x] _/project_ folder exists
- [x] _/build_ is not in the repo
- [x] _/html_  and _/latex_ is not in _docs_
- [x] **__`make` from within _project_ completes without error.__**
- [x] `./../build/bin/arenaviewer` executes without assert or a seg fault
- [x] `./../build/bin/unittest` executes without a seg fault
- [x] **_"make check-style" reports no errors when run in the master branch._**
- [x] `doxygen docs/Doxyfile` compiles



### Primary Functionality


> To make grading easier, we ask that you provide the status of each of the requirements. Do not lie about the status!! You might get partial credit for incomplete or erroneous functionality, however, if you fail to inform us of the issue, then you will definitely lose all the points for that functionality.


**__Please place an 'X' in the appropriate box for each requirement.__**

- Good = Fully Implemented. No _known_ bugs. No _obvious_ bugs.
- Okay = Works but some bugs (recorded as a bug/issue on github).
- Help = Attempted but not working.
- Time = No to Little Progress


| Functionality | Good | Okay | Help | Time |
| ------------- | ---- |----- | ---- | ---- |
| **__Priority Level 2__** |
| _Aggression_ Behavior implemented and operational for Braitenberg Vehicle behavior toward Lights. | X |  |  |  |
| _Aggression_  Behavior implemented and operational for Braitenberg Vehicle behavior toward Food. | X |  |  |  |
| _Love_  Behavior implemented and operational for Braitenberg Vehicle behavior toward Lights. | X |  |  |  |
| _Love_  Behavior implemented and operational for Braitenberg Vehicle behavior toward Food. | X |  |  |  |
| _Coward_  Behavior implemented and operational for Braitenberg Vehicle behavior toward Lights. | X |  |  |  |
| _Coward_  Behavior implemented and operational for Braitenberg Vehicle behavior toward Food. |X | | | |
|_Explore_  Behavior still operational for Braitenberg Vehicle behavior toward Lights. | X| | | |
| _Explore_  Behavior still operational for Braitenberg Vehicle behavior toward Food. | X |  |  | |
| Braitenberg Vehicle _new collision avoidance behavior_ (turn 180, advance 20 time steps, turn 180 + or - 45 degrees and continue) implemented and operational. | X |  |  |  |
| _Lights_ are colored white. | X |  |  |  |
| _Food_ is colored green. | X |  |  |  |
| _Vehicle_ is colored Maroon if both sensors are affecting vehicle behavior, or neither sensor is affecting vehicle behavior. | X |  |  |  |
| _Vehicle_ is colored Gold if only the Light sensor is affecting vehicle behavior.  | X |  |  |  |
| _Vehicle is colored Blue if only the Food sensor is affecting vehicle behavior. | X |  |  |  |







| Functionality | Good | Okay | Help | Time |
| -------- | -------- | -------- | -------- | --------- |
| **__Priority Level 3__** |
| Factories instantiate entities using JSON | X |  |  |   |
| All BraitenbergVehicle entities in Arena created with a factory | X |  |  |  |
| All Light entities in Arena created with a factory | X |  |  |  |
| All Food entities in Arena created with a factory | X |  |  |  |
| _Scenario 1_  visually inspected - Vehicle does not sense food (default) or light (default). | X |  |  |  |
| _Scenario 2_  visually inspected - Vehicle aggressive toward food, default toward light. | X |  |  |  |
| _Scenario 3_  visually inspected - Vehicle explore toward food, default toward light. | X |  |  |  |
| _Scenario 4_  visually inspected - Vehicle love toward food, default toward light. | X |  |  |  |
| _Scenario 5_  visually inspected - Vehicle coward toward food, default toward light. | X |  |  |  |
| _Scenario 6_  visually inspected - Vehicle aggressive toward light, default toward food. | X |  |  |  |
| _Scenario 7_  visually inspected - Vehicle explore toward light, default toward food. | X |  |  |  |
| _Scenario 8_  visually inspected - Vehicle love toward light, default toward food. | X |  |  |  |
| _Scenario 9_  visually inspected - Vehicle coward toward light, default toward food. | X |  |  |  | |


### Documentation

#### Design Document

- [x] The final version of your design document for iteration 1 exists in _docs_ (named **__iteration1\_design.pdf__**).
- [x] The final version of your design document discusses the tradeoffs of different implementations of the Factory Pattern and discusses which version you implemented, which might be some variation/hybrid of the factory pattern you discussed in the document.

#### UML
_
- [X] Final version of UML in a pdf file in the project/docs directory (named **__iteration1_UML.pdf__**).
- [X] The Factory classes in the UML reflect what was implemented.
- [X] The UML contains the BraitenbergVehicle, Light, and Food class.
- [X] The UML contains the Arena class.
- [X] The UML contains the _design_ of the Strategy Pattern.

#### Doxygen

- [X] All classes have a _brief_ description that appears in the doxygen web page class list.
- [X] The Arena class is fully documented with respect to methods and member variables. In other words, in the html generated pages of doxygen, the user can click on a class method and see more information about its purpose and parameters.
- [X] The BraitenbergVehicle class is fully documented with respect to methods and member variables.
- [X] The factory classes are fully documented with respect to methods and member variables.


### Linter and Git

- [X] All *.h and *.c files pass cpplint.
- [X] The code complies with naming conventions for Classes, ClassMethods, and class\_members\_.
- [X] There exists a history of git commit messages to show effort.
- [X] There exists a history of issues and branches to show effort.
- [X] Github issues include current unresolved bugs.
- [ ] Github issues include unresolved feature enhancements and refactoring that is due for this iteration.



### Testing

- [X] Unit tests are in the /project/tests folder.
- [X] Unit tests for different classes are in separate files.

- [x] Unit tests exist to test the creation of a BraitenbergVehicle.
- [x] Unit tests exist to test the creation of a Light.
- [x] Unit tests exist to test the creation of a Food.
- [X] Unit tests for the factories use JSON.
- [x] Unit tests for the factories test initialization of the entity.



## Ready For Submission



When everything above is as you want it or the deadline is upon you, it is time to submit!

- [X] I pushed this file and any changes resulting from this checklist.
- [X] Everything is in the **__master__** branch.

_One more thing_ -- check that what you think you pushed was really pushed to github. If you can see it, we can see it. If you can't, we can't.

**Congratulations on your submission!**
