### CSCI3081W: Iteration 3 Submission Checklist

>The iteration 3 code and documentation is due on Monday, May 6th at 11:55pm

Please ensure that this file is in your /docs folder. Place an 'x' in each of the `[ ]` boxes for items that are complete. Push this completed checklist to github. When it displays on Github, it will show an actual checkbox with a check mark.

### Compilation and Execution

- [X]  cloned **fresh** from github onto a cselabs machine to test compilation, style compliance, and execution
- [X] Submission is on the **master** branch in the project folder of your repo
- [X] _/project_ folder exists   <<<< I think we can remove this one.
- [X] _/build_ is not in the repo
- [X] _/html_  and _/latex_ is not in _docs_
- [X] **__`make` from within _project_ completes without error.__**
- [X] `./../build/bin/arenaviewer  xdim dim configfile.json` executes without assert or a seg fault
- [X] `./../build/bin/arenaviewer  xdim dim configfile.csv` executes without assert or a seg fault
- [X] `./../build/bin/unittest` executes without a seg fault
- [X] **_"make check-style" reports no errors when run in the master branch._**
- [X] `doxygen docs/Doxyfile` compiles and creates the html pages for you main page and  all classes without errors.



# Functionality Checklist


> To expedite grading, you need to provide the status of your simulation and each of the requirements. Do not lie about the status!! You might get partial credit for incomplete or erroneous functionality, however, if you fail to inform us of the issue, then you will lose more (or all) the points for that functionality since we cannot partially grade it.

>If your source code  **does not compile** or if there is an obvious **seg fault** in either the arenaviewer or the unit tests, **__YOU MUST MODIFY THE COMMENT NEXT TO THE CHECKBOX BELOW__** to let us know what the problem is or you will lose all points for that item.

- [X] I have compiled and executed both the source code and unit tests using a fresh clone of my repo. They compile and execute without segmentation faults.

**__Next, please place an 'X' in the appropriate box for each requirement.__**

- Good = Fully Implemented. No _known_ bugs. No _obvious_ bugs.
- Okay = Works but some bugs (recorded as a bug/issue on github).
- Help = Attempted but not working.
- Time = No to Little Progress
##

#### **_NOTE:  The final delivery for  Priority 1 functionality and documentation was due Friday April 26th at 11:55pm.  We will use those deliverables (documentation and code) to evaluate Predator disguise functionality using the Decorator Pattern and Predator starvation behavior.   However, your final deliverable has to successfully demonstrate the configuration (and some execution of) predator functionality, and thus we ask for status on Priority 1 items._** 

##
| Functionality | Good | Okay | Help | Time |
| ------------- | ---- |----- | ---- | ---- |
| **__Priority Level 1__** |
| Predator Behavior implemented and operational. | X |  |  |  |
| Predator Disguise functionality (ability to behave as Food, Light, or BV) implemented and operational | X |  |  |  |
| Predator starvation behavior implemented (triggers switches between disguises | X |  |  |  |

| Functionality | Good | Okay | Help | Time |
| ------------- | ---- |----- | ---- | ---- |
| **__Priority Level 2__** |
| Functionality to enable Factories to configure the entities used in the Arena using Json configuration files or csv configuration files is implemented and operational.   | X |  |  |  |

### Documentation


#### Design Document 

- [X] Your final iteration of the design document should be updated (that is,  add the following to the previous version of your design document) to include a discussion of  your final design and implementation of the observer pattern, your design of the Decorator pattern, and a description of your final Factory Pattern design and implementation.

For the observer pattern, discuss any differences between your design and your final implementation and the primary reason they were different (if they were different).

For the decorator pattern, describe two alternative implementations, one pro and con for each, and the primary reason you chose the design that you implemented. One alternative is to implement the decorator pattern through aggregation, and another is to implement the decorator pattern using inheritance. CLARIFICATION: You may also compare and contrast implementations that would not be considered the decorator pattern.

For the factory pattern, describe how your simulation incorporates the functionality to configure the factory from configurations stored in a JSON file or from configurations stored in a file with comma separated values (a csv file). You should compare your design against one that employs the adapter pattern by noting one pro and con for each design. If your implementation employs the adapter pattern, you should discuss the primary reason you used it.

In your comparisons, provide an overall description highlighting key points of the implementation and using UML and/or code snippets to clarify your ideas. Also provide at least one advantage and one disadvantage of each implementation.

- [X] The final version of your design document for iteration 2 (named **__iteration3\_design.pdf__**) has been submitted via Canvas (See the **_Iteration 3  Design Doc Complete_** Item on Canvas for the submission link).


#### UML 

- [x] UML for project can be generated without errors using Doxygen,  and can be viewed in the docs directory.
- [x]  Deliver a UML diagram  that represents your final implementation. This will include Classes and relationships between the Arena, Braitenberg Vehicle, Predator, Food, Light, all factories, Classes that implement the observer pattern, classes that implement the strategy pattern, the classes that implement the Decorator Patten and any other classes used to implement the functionality for this iteration.
- [x] The final version of your UML design document for iteration 3 (named **__UML\_finaldesign.pdf__**) has been submitted via Canvas (See the **_Iteration 3  UML Complete_** Item on Canvas for the submission link).


#### Doxygen

- [x] All classes have a _brief_ description that appears in the Doxygen web page class list.
- [x] The Arena, Braitenberg vehicle and Factories using JSON  are fully documented with respect to methods and member variables. In other words, in the html generated pages of Doxygen, the user can click on a class method and see more information about its purpose and parameters.
- [x] A landing page that updates the landing page you submitted for iteration 2 and  meets the requirements specified in the Iteration 3 Requirements (in the file Iteration3Requiements.md located here: https://github.umn.edu/umn-csci-3081-S19/csci3081-shared-upstream/blob/support-code/project/docs/Iteration3Requirements.md ) exists in the file named **__mainpage.h__** and is in the src directory.
- [x] Doxygen successfully generates the main page (verify by running Doxygen and then opening the resulting **_index.html__** page). 
 

### Linter and Git

- [x] All *.h and *.c files pass cpplint.
- [x] The code complies with naming conventions for Classes, ClassMethods, and class\_members\_.
- [x] There exists a history of git commit messages to show effort.
- [x] There exists a history of issues and branches to show effort.
- [ ] Github issues include current unresolved bugs.
- [ ] Github issues include unresolved feature enhancements and refactoring that is due for this iteration.


## Ready For Submission


When everything above is as you want it or the deadline is upon you, it is time to submit!

- [x] I pushed this file and any changes resulting from this checklist.
- [x] Everything is in the **__master__** branch.

_One more thing_ -- check that what you think you pushed was really pushed to github. If you can see it, we can see it. If you can't, we can't.

**Congratulations on your submission and on your accomplishments this semester!**





