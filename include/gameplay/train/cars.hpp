#ifndef CARS_HPP
#define CARS_HPP

#include <memory>
#include <string>
#include <vector>

#include "exceptions.hpp"
#include "gameplay/train/merchandises.hpp"
#include "types.hpp"

namespace cars {

/**
 * Generic car object.
 * This class is abstract.
 */
class Car {
    /**
     * Unique ID of the latest car created.
     */
    static types::id latestCarId;

    /**
     * Unique ID of the car.
     */
    const types::id carId;

    /**
     * Maximum health points.
     */
    const static types::health maxHealth;

  protected:

    /**
     * ID of the car.
     */
    types::id id;

    /**
     * Human-readable name of the car.
     */
    std::string name;

    /**
     * Health points.
     * The car is destroyed if the value is lower than or equal to 0.
     */
    types::health health;

    /**
     * Base weight of the car.
     * It does not include weight of the payload.
     */
    types::weight weight;

  public:

    /**
     * Default constructor.
     */
    Car();

    /**
     * Usual constructor.
     * @param id ID of the car.
     * @param name Human-readable name of the car.
     * @param health Health points of the car.
     * @param weight Base weight of the car.
     */
    Car(const types::id id, const std::string name, const types::health health,
        const types::weight weight);

    /**
     * Usual constructor with maximum health.
     * @param id ID of the car.
     * @param name Human-readable name of the car.
     * @param weight Base weight of the car.
     */
    Car(const types::id id, const std::string name, const types::weight weight);

    /**
     * Copy constructor.
     * @param car Car to construct from.
     */
    Car(const Car& car);

    /**
     * Getter for the ID of the car.
     */
    types::id getCarId() const;

    /**
     * Getter for ID.
     * @return ID of the car.
     */
    types::id getId() const;

    /**
     * Getter for name.
     * @return Human-readable name of the car.
     */
    std::string getName() const;

    /**
     * Getter for maximum health points.
     * @return Maximum health points of the car.
     */
    types::health getMaxHealth() const;

    /**
     * Getter for health points.
     * @return Health points of the car.
     */
    types::health getHealth() const;

    /**
     * Getter for weight.
     * @return Total weight of the car.
     */
    virtual types::weight getWeight() const = 0;

    /**
     * Indicate if the car is destroyed.
     * @return True if the car has 0 health points or lower.
     */
    bool isDestroyed() const;

    /**
     * Take dammage.
     * @param attack Value of the attack.
     */
    void takeDammage(types::health attack);

    /**
     * Repair car and restore full helth points.
     */
    void repair();
};

/**
 * Error class used when trying to modify or querry a destroyed car.
 */
struct DestroyedCarError : public exceptions::TransarcticaRebirthError {

    /**
     * Error message.
     * @return Error message.
     */
    const char* what() const throw() {
        return "Car is destroyed";
    }
};

/**
 * Special car object.
 * Cars that cannot be purchased. If they are destroyed, the game ends.
 */
class SpecialCar : public Car {
    using Car::Car;
};

/**
 * Normal car object.
 * Cars that can be purchased, used, and destroyed.
 */
class NormalCar : public Car {
    using Car::Car;

  public:

    /**
     * Getter for weight.
     * It simply returns the base weight.
     */
    types::weight getWeight() const;
};

/**
 * Car that accept a load.
 * A load car cannot be redefined after being constructed.
 */
class LoadCar : public Car {
  protected:

    /**
     * Maximum quantity of merchandise loads.
     */
    types::quantity maxQuantity;

    /**
     * Type of merch accepted.
     */
    const merchandises::MerchTypes merchType;

    /**
     * Merchandise.
     */
    std::shared_ptr<merchandises::MerchLoad> merchLoad;

    /**
     * Setter for merch load.
     * @param merchLoad Merch load to put in the car. The variable passed as
     * argument will not be useable after the call, as the reference will be
     * moved in the object.
     */
    void setMerchLoad(const merchandises::MerchLoad& merchLoad);

    /**
     * Setter for merch load.
     * @param merchLoad Merch load to put in the car.
     */
    void setMerchLoad(const std::shared_ptr<merchandises::MerchLoad>& merchLoad);

  public:

    /**
     * Default constructor.
     */
    LoadCar();

    /**
     * Usual constructor.
     * @param id ID of the car.
     * @param name Human-readable name of the car.
     * @param health Health points of the car.
     * @param weight Base weight of the car.
     * @param maxQuantity Capacity of the car.
     * @param merchType Type of merch accepted in the car.
     * @param merchLoad Load in the car. The variable passed as argument will
     * not be useable after the call, as the reference will be moved in the
     * object.
     */
    LoadCar(const types::id id,
            const std::string name,
            const types::health health,
            const types::weight weight,
            const types::quantity maxQuantity,
            const merchandises::MerchTypes merchType,
            merchandises::MerchLoad& merchLoad);

    /**
     * Usual constructor.
     * @param id ID of the car.
     * @param name Human-readable name of the car.
     * @param health Health points of the car.
     * @param weight Base weight of the car.
     * @param maxQuantity Capacity of the car.
     * @param merchType Type of merch accepted in the car.
     * @param merchLoad Load in the car.
     */
    LoadCar(const types::id id,
            const std::string name,
            const types::health health,
            const types::weight weight,
            const types::quantity maxQuantity,
            const merchandises::MerchTypes merchType,
            std::shared_ptr<merchandises::MerchLoad>& merchLoad);

    /**
     * Usual constructor for empty car.
     * @param id ID of the car.
     * @param name Human-readable name of the car.
     * @param health Health points of the car.
     * @param weight Base weight of the car.
     * @param maxQuantity Capacity of the car.
     * @param merchType Type of merch accepted in the car.
     */
    LoadCar(const types::id id,
            const std::string name,
            const types::health health,
            const types::weight weight,
            const types::quantity maxQuantity,
            const merchandises::MerchTypes merchType);

    /**
     * Usual constructor for car with full health points.
     * @param id ID of the car.
     * @param name Human-readable name of the car.
     * @param weight Base weight of the car.
     * @param maxQuantity Capacity of the car.
     * @param merchType Type of merch accepted in the car.
     * @param merchLoad Load in the car. The variable passed as argument will
     * not be useable after the call, as the reference will be moved in the
     * object.
     */
    LoadCar(const types::id id,
            const std::string name,
            const types::weight weight,
            const types::quantity maxQuantity,
            const merchandises::MerchTypes merchType,
            merchandises::MerchLoad& merchLoad);

    /**
     * Usual constructor for car with full health points.
     * @param id ID of the car.
     * @param name Human-readable name of the car.
     * @param weight Base weight of the car.
     * @param maxQuantity Capacity of the car.
     * @param merchType Type of merch accepted in the car.
     * @param merchLoad Load in the car.
     */
    LoadCar(const types::id id,
            const std::string name,
            const types::weight weight,
            const types::quantity maxQuantity,
            const merchandises::MerchTypes merchType,
            std::shared_ptr<merchandises::MerchLoad>& merchLoad);

    /**
     * Usual constructor for empty car with full health points.
     * @param id ID of the car.
     * @param name Human-readable name of the car.
     * @param weight Base weight of the car.
     * @param maxQuantity Capacity of the car.
     * @param merchType Type of merch accepted in the car.
     */
    LoadCar(const types::id id,
            const std::string name,
            const types::weight weight,
            const types::quantity maxQuantity,
            const merchandises::MerchTypes merchType);

    /**
     * Getter for weight.
     * @return Base weight of the car and the weight of the load.
     */
    types::weight getWeight() const;

    /**
     * Getter for max quantity of merch load.
     * @return Total capacity of the car.
     */
    types::quantity getMaxQuantity() const;

    /**
     * Getter for quantity currently loaded.
     * @return Current quantity in the car.
     */
    types::quantity getQuantity() const;

    /**
     * Getter for remaining space in car.
     * @return Current capacity of the car.
     */
    types::quantity getRemainingQuantity() const;

    /**
     * Getter for accepted merch type.
     * @return Type of merch accepted in the car.
     */
    merchandises::MerchTypes getMerchType() const;

    /**
     * Getter for merch load.
     * @return Load in the car.
     */
    std::shared_ptr<merchandises::MerchLoad> getMerchLoad();

    /**
     * Tell if the car is empty.
     * @return True if the car has no load.
     */
    bool isEmpty() const;

    /**
     * Tell if the car is full.
     * @return True if there is no space left.
     */
    bool isFull() const;

    /**
     * Tell if the car can load this merch load.
     * @param merchLoad Load to consider.
     * @return True if the load cand be loaded.
     */
    bool canLoad(const merchandises::MerchLoad& merchLoad) const;

    /**
     * Tell if the car can load this merch load.
     * @param merchLoad Load to consider.
     * @return True if the load cand be loaded.
     */
    bool canLoad(const std::shared_ptr<merchandises::MerchLoad>& merchLoad) const;

    /**
     * Load a merch load in the car.
     * @param merchLoad Load to load in the car. After the call, the merch load
     * is empty.
     */
    void load(merchandises::MerchLoad& merchLoad);

    /**
     * Load a merch load in the car.
     * @param merchLoad Load to load in the car. After the call, the merch load
     * is empty.
     */
    void load(std::shared_ptr<merchandises::MerchLoad>& merchLoad);

    /**
     * Load a certain quantity of a merch load in the car.
     * @param merchLoad Load to load in the car. After the call, the merch load
     * quantity is reduced.
     * @param quantity Quantity of load to load only.
     */
    void load(merchandises::MerchLoad& merchLoad, const types::quantity quantity);

    /**
     * Load a certain quantity of a merch load in the car.
     * @param merchLoad Load to load in the car. After the call, the merch load
     * quantity is reduced.
     * @param quantity Quantity of load to load only.
     */
    void load(std::shared_ptr<merchandises::MerchLoad>& merchLoad, const types::quantity quantity);

    /**
     * Unload merch loads from the car.
     * @param quantity Quantity of load to unload.
     * @return Load unloaded, containing the required quantity.
     */
    merchandises::MerchLoad unLoad(const types::quantity quantity);
};

/**
 * Error class used when a load cannot be loaded in the car.
 */
struct CannotLoadError : public exceptions::TransarcticaRebirthError {
    /**
     * Error message.
     * @return Error message.
     */
    const char* what() const throw() {
        return "Car cannot load this merch";
    }

};

/**
 * Error class used when there is not enough space in the car.
 */
struct NotEnoughSpaceError : public exceptions::TransarcticaRebirthError {
    /**
     * Error message.
     * @return Error message.
     */
    const char* what() const throw() {
        return "Car cannot load this merch load: not enough space";
    }
};

/**
 * Error class used when there is not enough load in the car.
 */
struct NotEnoughLoadError : public exceptions::TransarcticaRebirthError {
    /**
     * Error message.
     * @return Error message.
     */
    const char* what() const throw() {
        return "Car cannot unload this merch load: not enough load";
    }
};

/**
 * Error class when the car is empty.
 */
struct IsEmptyError : public exceptions::TransarcticaRebirthError {
    /**
     * Error message.
     * @return Error message.
     */
    const char* what() const throw() {
        return "Car is empty";
    }
};

/**
 * Model for load cars.
 */
class LoadCarModel : public LoadCar {
    using LoadCar::LoadCar;

  public:

    /**
     * Generate a new load car.
     * @param health Health points of the car.
     * @param merchLoad Load in the car.
     * @return New load car instance.
     */
    LoadCar operator()(types::health health, merchandises::MerchLoad& merchLoad) const;

    /**
     * Generate a new empty load car.
     * @param health Health points of the car.
     * @return New load car instance.
     */
    LoadCar operator()(types::health health) const;

    /**
     * Generate a new load car with full health.
     * @param merchLoad Load in the car.
     * @return New load car instance.
     */
    LoadCar operator()(merchandises::MerchLoad& merchLoad) const;

    /**
     * Generate a new empty load car with full health.
     * @return New load car instance.
     */
    LoadCar operator()() const;
};

}

#include "cars_data.hpp"

#endif // ifndef CARS_HPP
