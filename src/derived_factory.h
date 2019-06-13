/**
 * @file derived_factory.h
 *
 * @copyright 2019 tran0707 , All rights reserved.
 */

#ifndef SRC_DERIVED_FACTORY_H_
#define SRC_DERIVED_FACTORY_H_

#include "src/food.h"
#include "src/braitenberg_vehicle.h"
#include "src/light.h"
#include "src/predator.h"
#include "src/arena_entity.h"
#include "src/factory.h"
#include "src/behavior_enum.h"

//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);
/**
* @brief FoodFactory inherited from Factory.
* This method used to create a new Food and Load infos
* from json file
*/
class FoodFactory: public Factory{
 public:
        FoodFactory();
        virtual ~FoodFactory();
        /**
    	* @brief Create method override from Factory.
    	* This method is use a Food object.
    	*/ 
        Food *Create(__unused json_object* config) override;
};

/**
* @brief LightFactory inherited from Factory.
* This method used to create a new Light and Load infos
* from json file
*/
class LightFactory: public Factory{
 public:
        LightFactory();
        virtual ~LightFactory();
        /**
    	* @brief Create method override from Factory.
    	* This method is use a Light object.
    	*/ 
        Light *Create(__unused json_object* config) override;
};

/**
* @brief VehicleFactory inherited from Factory.
* This method used to create a new BraitenbergVehicle and Load infos
* from json file
*/

class VehicleFactory: public Factory{
 public:
        VehicleFactory();
        virtual ~VehicleFactory();
        /**
    	* @brief Create method override from Factory.
    	* This method is use a BraitenbergVehicle object.
    	*/ 
        BraitenbergVehicle *Create(__unused json_object* config) override;
};

/**
* @brief PredatorFactory inherited from Factory.
* This method used to create a new Predator and Load infos
* from json file
*/

class PredatorFactory: public Factory{
 public:
        PredatorFactory();
        virtual ~PredatorFactory();
        /**
        * @brief Create method override from Factory.
        * This method is use a Predator object.
        */ 
        Predator *Create(__unused json_object* config) override;
};

//! Namespaces for csci3081
NAMESPACE_END(csci3081);

#endif  // SRC_DERIVED_FACTORY_H_
