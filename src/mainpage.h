/**
 * @file mainpage.h
 *
 * @copyright 2019 3071 Staff, All rights reserved.
 */

#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_
/*! \mainpage Robot Simulator Project
 *
 * \section indexing Index
 * 1. \link intro_sec Introduction \endlink <br>
 * 2. \link structure_sec Main Class Structure \endlink <br>
 * 3. \link flow_sec Flow of Control \endlink <br>
 * 4. \link design_sec Design Pattern \endlink <br>
 * 4.1 \link factory_sec Factory Pattern \endlink <br>
 * 4.2 \link structure_sec Strategy Pattern \endlink <br>
 * 4.3 \link observer_sec Observer Pattern \endlink <br>
 * 4.4 \link decorator_sec Decorator Pattern \endlink <br>
 * 5. \link user_sec User Guide \endlink <br>
 *
 * \section intro_sec Introduction
 *
 * A Braitenberg Vehicle is a concept conceived in a thought experiment by the Italian-Austrian cybernetics
 * Valentino Braitenberg. It is an agent that can move by itself based on the reading of sensors. This project
 * is my version of Braitenberg Vehicle that can change its speed based on the light sensor and food sensor
 * through the choice of user selected behaviors. In this simulation, every robot can sense the closest entity
 * around it and use the complex behavior set by the user can calculate the speed and direction of robots
 * should be. This project is implemented using the C++ programming language and used Nanogui library to
 * visualize GUI.
 *
 * \section structure_sec Main Class Structure
 * <B> Arena Class Structure </B> <br>
 *
 * \image html Arena.png
 * 
 * <B> GraphicsArenaViewer Class Structure </B> <br>
 *
 * \image html GAV.png
 *
 * <B> Controller Class Structure </B> <br>
 *
 * \image html Controller.png
 *
 * \section flow_sec Flow of Control
 * <B> Arena: </B> <br>
 * Arena is the most important part of this project. It handles all the data and all the entities. It also
 * manages the interaction among the entities in Arena. Generally, Arena can create entities, check for collision
 * between entities, adjust or handle collision, update entities time step. The Arena is where everything in this
 * simulator handle.
 *
 * <B>GraphicsArenaViewer: </B> <br>
 * GraphicsArenaViewer uses the Nanogui library to draw all the objects in this project. It is including drawing
 * all entities, selecting box, items, window. GraphicsArenaViewer keeps track of all location changing of each
 * object in Arena and then redraw it by each frame. This creates a feel of smooth movement of light and BV. 
 * GraphicsArenaViewer is also responsible for the changing of behaviors when user selection different behavior of
 * currently selected entity toward Food, light, or BV. It, then, calls the setback function to notify back to each
 * BV, so that BV can change the update behavior through a setter behavior method in BV. The left panel GUI also
 * allows the user to trigger to start to play or pause or reset of this simulation.
 * GraphicsArenaViewer has pause and resets buttons. These buttons work by GraphicsArenaViewer communication to
 * Controller and Controller control Arena to satisfy with the user request. 
 *
 * <B>Controller: </B> <br>
 * In this project, the Controller has the role of the mediates between Arena and GraphicsArenaViewer communication.
 * When we press on the play button, the Controller instantiates the Arena and the GraphicsArenaViwer.  The
 * Controller doesn’t know much about Arena, but it has the ability to control the Arena. For instance, when a user
 * press on the pause button, the GraphicsArenaViewer then communication with Controller about that press, then
 * Controller let Arena know about that request and pause to update any object in Arena. The same process happens
 * when the user presses the pause button again.
 *
 * \section design_sec Design Pattern
 *
 * \subsection factory_sec Factory Pattern
 * 
 * Factory Design Pattern is a creational Design pattern ralated to object creation. It helps to create object
 * without exposing the creation logic behind the Factory Class. In this simulator, we use the Factory Pattern
 * to create all Light, Food, and Braitenberg Vehicle objects. We have an abstract Factory and four derived
 * Factories including FoodFatory, LightFactory, VehicleFactory, and PredatorFactory. 
 *
 * \image html Factory.png
 *
 * \subsection strategy_sec Strategy Pattern
 *
 * For the Strategy pattern, we used it for all five behaviors of Braitenberg Vehicle including Love, Coward,
 * Aggressive, Explore, and None. I created one abstract Behavior with cal_wheel_velocity() method in it and
 * five derived class that corresponding with five different behaviors of the BraitenbergVehicle. The main purpose
 * of using this design pattern in this project is to improve the loose-coupling ability between five differences
 * behaviors of Braitenberg Vehicle.
 *
 * \image html Strategy.png
 *
 * \subsection observer_sec Observer Pattern
 *
 * In general, The Observer pattern defines as a one-to-many dependency between objects. When the subject changes state,
 * then the subject notifies all its observers for the changing information. In this project, we use this pattern to send
 * wheel velocity from BraintenbergVehicle to GraphicsArenaViewer instead of GraphicsArenaViewer constantly pulling
 * information from BraintenbergVehicle. <br>
 * I created an Observer class that contains three methods including Data_Setter, OnUpdate, and formatValue. The
 * Data_Setter uses to set data after observe it from BraintenbergVehicle and store it into the corresponding private
 * variable in Observer class. The OnUpdate uses to update the TextBox in GraphicsArenaViewer each time BraintenbergVehicle
 * call Notify method on the new change of WheelVelocity. The formatValue uses to convert float number back to a string,
 * so we can set it into the TextBox. <br>
 *
 * \image html Observer.png
 *
 * \subsection decorator_sec Decorator Pattern
 * Decorator Pattern is a pattern that allows a user to add functionality on top of the existing object without
 * destroying the structure of that object. In this iteration 3, I used the Decorator Pattern to implement Predator that
 * has the ability to disguise itself as food, light, or Braitenberg Vehicle. Once a new entity is wrapped on top of the
 * original object, this Predator should behave exactly as the new entity should behave. For instance, if a Predator that
 * disguise a Food, it should remain at one position but not get eaten by a Braitenberg Vehicle.
 * 
 * \image html Decorator.png
 * 
 * \section user_sec User Guide 
 *
 * The left panel in the GUI is all the extend control that user can change by selecting different Braitenberg vehicles,
 * mobile, food behavior, light behavior, and Braitenberg vehicle behavior. Below is a brief description of the elements
 * in the GUI.
 * <B>Entity</B> – A NanoGui Combo Box that allows the user to choose what entity user want to control 
 * <B>Mobile</B> – A checkout represent the Entity selected can move and not.
 * <B>Light Behavior</B> – A NanoGui Combo Box that allows the user to choose the behavior of BV toward Light including
 * Default, Love, Coward, and  Aggressive 
 * <B>Food Behavior</B> – A NanoGui Combo Box that allows the user to choose the behavior of BV toward Food including
 * Default, Love, Coward, and  Aggressive 
 * <B>BV Behavior</B> – A NanoGui Combo Box that allows the user to choose the behavior of BV toward the other BV
 * including Default, Love, Coward, and  Aggressive 
 * <B>Wheel Velocities </B> <br>
 * - <B>Left</B> – The left wheel velocity of either Food, Light, or BV
 * - <B>Right</B> – The right wheel velocity of either Food, Light, or BV
 * - <B>Light</B> – Shows the current Light wheel velocity
 * - <B>Food</B> – Shows the current Food Vehicle wheel velocity
 * - <B>BV</B> – Shows the current Braitenberg Vehicle wheel velocity
 * <B>Game Control</B> <br>
 * - <B>Play/Pause</B> – Play or pause the simulation.
 * - <B>Reset</B> – Restart the simulation with the default setting from the scene.
 * <br>
 * <br>
 * <br>
 * <CENTER><B> IMPORTANT: ANY CHANGE IN GUI WILL NOT TAKE EFFECT UNTIL PRESS THE PLAY BUTTON !!!</B></CENTER>
 */

#endif  // SRC_MAINPAGE_H_
