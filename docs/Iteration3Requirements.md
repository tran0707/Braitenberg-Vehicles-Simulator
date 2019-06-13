# Braitenberg Vehicles Simulator: Iteration 3

### UPDATES

**Check this file regularly (that is, every day or two) for updates**

<hr>

This is YOUR project, and it is your decision in how you want to implement the various requirements (provided it meets the requirements). You may change the interface (and probably have to change the interface) of classes. You can add features that are not specified as long as they don't interfere with what is required.

_Your software is a reflection of your understanding of the requirements as specified in this document. If you do not understand any portion of the requirements or you think that the requirements are underspecified, it is your responsibility to get clarification from the instructor or a TA. Please read this document carefully and review it often WELL IN ADVANCE of turning in your iteration for assessment._

|*Due Date* | **Item(s) Due** |
|-----|-----|
| Friday,  April 26, 11:55pm | FINAL SUBMISSION: Predator disguises itself as food, light or another Braitenberg Vehicle. Predator starvation behavior implemented. On _devel_ branch.  
**Additional submission on Canvas -- see instructions below this table.** |
| MON,  May 6, 11:55pm | FINAL Submission of Remaining Iteration 3 Deliverables. On _master_ branch. |

> To simplify our grading process, we will compile and run the code from the _devel_ branch, and we will inspect the code and diagrams submitted on Canvas.

**Canvas Submission for Preliminary 1 (due April 26)**: In a **SINGLE** .pdf document (do not zip!), please include 
- Doxygen-generated generated UML diagrams for the classes that implement the decorator pattern
- code snippets of your implementation of the predator and other classes' functionality that enables a Predator to disguise itself as food, light,  or a Braitenberg vehicle
-code snippet of your implementation the predator classes' starvation behavior. 


### Project Overview

In this iteration, as with the last, you will continue to develop your Braitenberg Vehicle simulation to provide more functionality, to apply design patterns, and to expand documentation.

Feature enhancements include adding the ability for
Predators to disguise themselves as a food entity, a light entity or a Braitenberg vehicle depending on their need for sustenance (that is, food - which, for a predator, is any Braitenberg Vehicle).
 You will also incorporate functionality to enable factories to create entities from configuration files that do not use JSON.  For documentation, you should update your design document to include a description of your final implementation of the Strategy and Factory patterns. You should add a discussion of your implementation of the Decorator pattern, and your update to the the factory pattern.  Finally you will update your landing page for the Doxygen generated html pages and add Doxygen documentation to the classes, methods, and attributes added to your code.

<hr>

## Iteration 3 Requirements - Table of Contents

<ol type="I">
<li> <a href="#reqs">Iteration Requirements</a>
  <ol type="A">
    <li><a href="#reqs_design">Design Requirements</a>
  <li><a href="#reqs_doc">Documentation Requirements</a>
    <ol type="i">
    <li> <a href="#design_doc">Design Document</a>
    <li> <a href="#doxy">Doxygen</a>
    <li> <a href="#style">Style Compliance</a>
    <li> <a href="#self_doc">Self-Documenting Code</a>
    </ol>
  <li><a href="#reqs_dev">Code Development Requirements</a><ol>
  <li> <a href="#issue">Issue Report</a>
  <li> <a href="#git_usage">Git Usage</a></ol>
  <li><a href="#reqs_imp">Implementation Requirements</a>
    <ol type="i">
    <li><a href="#reqs1">Priority Level 1: Predator Disguises Itself and Predator Starvation Behavior</a>
    <li><a href="#reqs2">Priority Level 2: Factories can configure entities using JSON or a CSV format.</a>
       </ol>
  </ol>
<li> <a href="#deliver">Deliverables and Submission</a>
 <li> <a href="#resources">Resources</a>
</ol>

<hr>

### <a name="reqs_design">Design Requirements</a>

#### Decorator Design Pattern

Employ the Decorator pattern to implement the enable a Predator to assume the identities of a food, light, or a Braitenberg vehicle entity.   The Decorator can be implemented via inheritance or aggregation. You should read about the Decorator Pattern in Chapter 3 of your text Head First Design Patterns before deciding which approach you will follow to design and implement this functionality.

#### Factory Design Pattern

Continue your use of the Factory pattern to instantiate and initialize Arena Entities. However, in this iteration you should update your factories so that they can configure entities using either a JSON configuration file or a text file that specifies the values for each entities with a comma separated value format.  We will provide the specification of the format of the csv file and some parsing functionality for the text-based configuration file. You should read about the Adapter Pattern in Chapter 7 of your text Head First Design Patterns before deciding which approach you will follow to design and implement this functionality. 

<hr>

## <a name="reqs_doc">Documentation Requirements</a>
- UML 
- Design Document
- Doxygen generated web pages including a landing page
- Self-Documenting code that is Google Style Compliant

Code documentation comes in many forms for many audiences. For this project, **your audience is other programmers** who need to understand class structure and relationships, interfaces, function parameters, function behavior, code organization, class organization, and code logic. Self-documenting code (i.e. using good organization and naming conventions) is an efficient means of communicating, since you have to write the code anyway. _Good_ comments - not too many, not too few - help guide others through the logic and class interfaces. For the larger picture of code and class structure, use UML diagrams and Doxygen-generated (automatic) web pages.

In this iteration you will be required to deliver a UML diagram again that represents your final implementation. This will include Classes and relationships between the Arena, Braitenberg Vehicle, Predator, Food, Light, all factories, Classes that implement the observer pattern, classes that implement the strategy pattern,  the classes that implement the Decorator Patten and any other classes used to implement the functionality for this iteration.

### <a name="design_doc">Design Document

Your final iteration of the design document should be updated to include your final design and implementation of the strategy pattern,   your design of the Decorator pattern, and a description of your final Factory Pattern design and implementation. 

For the strategy pattern, discuss how the design of the pattern you submitted at the end of iteration 1 differed from the design you implemented and submitted in iteration 2.  Your discussion should note any differences between the iteration 1 design and iteration 2 implementation and the primary reason they were different (if they were different). 

For the decorator pattern,  describe two alternative implementations, one pro and con for each, and the primary reason you chose the design that you implemented. One alternative is to implement the decorator pattern through aggregation, and another is to implement the decorator pattern using inheritance. 

For the factory pattern, describe how your simulation incorporates the functionality to configure the factory from configurations stored in a JSON file or from configurations stored in a file with comma separated values (a csv file). You should compare your design against one that employs the adapter pattern by noting one pro and con for each design. If your implementation employs the adapter pattern, you should discuss the primary reason you used it. 

In your comparisons, provide an overall description highlighting key points of the implementation and using UML and/or code snippets to clarify your ideas. Also provide at least one advantage and one disadvantage of each implementation.

Name the design document *iteration3_design.pdf*.

**You will submit your final version of the iteration 3 design document via Canvas.**


### <a name="style">Google Style Guide Compliance</a>

Please comply to the Google C++ Style. Running cpplint on your code should generate 0 errors, except we do allow the use of rand(). Check that your methods are CamelCase (except for getters and setters) and your class variables end in an underscore.

See the information at the URL: https://google.github.io/styleguide/cppguide.html  for more details.

### <a name="doxy">Doxygen</a>

Continue to refine your in-code Doxygen documentation including a brief description for all classes and a full documentation of Arena, Braitenberg Vehicles, and your factories with JSON including both methods and member variables. _You do not have to fully document your new factory classes that do not use JSON._

In addition to the code documentation, please update the first version of the _landing page_ (i.e. mainpage.h) that you created in iteration 2 in this iteration. This file is placed in the **src** directory for Doxygen to find. You can try it out by placing this text in _mainpage.h_ :

```
  /*! \mainpage My Personal Index Page
   *
   * \section intro_sec Introduction
   *
   * This is the introduction.
   *
   */
```

You should add and/or update instructions on how to run the simulation and tell the user how to build a configuration file (in JSON and a csv format).

<hr>

## <a name="reqs_dev">Code Development Requirements</a>

- Git Branches
- Git Issue Tracking
- Git Commits and Messages

### <a name="git_usage">Git Branches and Issues</a>

Again for this final iteration, create Git issues to document bugs, feature enhancements, refactoring, documentation, clean-up, etc. As you address significant issues, create a branch off of _devel_. Note: you can address several issues within a single branch.

As in the previous iteration, code should be developed in a branch off of the _devel_ branch.  Please do not delete your branches after they are merged - that enables us to grade that aspect of your development.

Commit messages for less significant modification can be composed at the command line, but should be consistent in style and be informative with regard to what changes were made where. You can make minor edits on the _devel_ branch, but the version you keep in your development branch should always compile without compile errors and Google style issues and execute.

Do not merge the _devel_ branch with _master_ until the final implementation is ready for submission.

<hr>

## <a name="reqs_imp">Implementation Requirements</a>

The iterative method identifies and prioritizes feature enhancements and code refactoring over short intervals called sprints. Below is a prioritized list of feature enhancements, fixes, and refactoring of the code. **Complete all functionality in one priority level before moving on to the next.** In this way, if we run out of time, the low priority items will be dropped from the requirements.

### <a name="reqs1">Priority Level 1 : Add functionality for Predator to disguise itself as food, light or Braitenberg vehicle using the Decorator Pattern, and implement Predator starvation behavior</a>
### Due: Friday, April 26th at 11:55pm

- Implement Predator capability to disguise itself as food or a braitenberg vehicle using the decorator pattern. This can be accomplished via inheritance or via aggregation. 

One a new identity is assumed, the Predator should behave as the entity whose behavior it assumes. If a predator assumes the identity of food, it should remain at the location at which it assumed that identity. 

If the predator assumes the identity of a light, it should be a stationary light, and remain at the location at which it assumed that identity.  **NOTE** - this is requirement is subject to change as lights have the ability to move.

If the Predator assumes the identity of another Braitenberg vehicle, it should randomly set its behaviors towards food and light to explore, love, coward, aggression or none. However, its behaviors towards other robots should remain aggressive. 

Implement Starvation Behavior for Predators. Starvation will be the trigger which causes predators to disguise themselves. 
- If a predator has not eaten after 150 iterations, it should randomly switch identities to either food or a Braitenberg vehicle (so it has a 1 in 3 chance of assuming the identity of either food,light or a Braitenberg vehicle (bv)). 
- If a predator has still not eaten after 300 iterations, it should switch its identity to one of the remaining identities it has not assumed (if assumed the identity of food after 150 iterations, it should randomly assume the identity of either a bv or a light after 300 iterations (so it has a 50/50 chance of assumming the identity of either a light or bv). 
- If the predator has not eaten after 450 iterations, it should assume the identity of the entity it has not yet assumed. So if the predator assumed the identity of food after 150 iterations, and a bv after 300 iterations, it should assume the identity of a light after 450 iterations.  
- Finally, if a predator has not eaten after 600 iterations, it should starve and become a "ghost".

<hr>

### <a name="reqs2">Priority Level 2 : Functionality for Factories to configure entities using JSON specified configuration files, or CSV specified configuration files. 
### Due: May 6th at 11:55pm

- Add the functionality for factories to configure entities using Json configuration files or CSV specified configuration files.

-You will change your simulation so it can be executed in one of the two following ways from the Unix/Linux command line:

./build/bin/arenaviewer xdim ydim ConfigurationFile.json

or

./build/bin/areanviewer xdim ydim ConfigurationFile.csv



<hr>

## <a name="deliver">Deliverables and Submission Process</a>

For the final iteration submission, everything will be submitted via Github in the master branch of the project directory in your class repo **AND the design document will be submitted via Canvas**. We will pull your repository at the specified due dates and grade according to the contents at that time. You should be developing in your_ devel_ branch, but at the time of final submission, merge _devel_ with _master_.

For the preliminary submission, submit via Github on the _devel_ branch AND follow the directions at the top regarding a Canvas submission. We will look at both.

**Late assignments will not be accepted**, but you will receive partial credit for partial completion of the requirements.

Your software will be assessed through automatic testing and by the TA. The process for testing will be to start by typing  `make clean` then `make`. We **highly encourage** you to make a new clone of your repo on a **cselabs machine** and also `make clean` and `make` to confirm all is working well before submitting your iteration 3 code.

<hr>

## <a name="assessment">Assessment Weighting</a>

To be determined.  This will be posted in approximately 1 week. 

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
