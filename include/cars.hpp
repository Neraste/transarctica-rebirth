#ifndef CARS_HPP
#define CARS_HPP

#include <exception>
#include <string>
#include <vector>

#include "merchandises.hpp"
#include "types.hpp"

namespace cars {

/**
 * Generic car object.
 * This class is abstract.
 */
class Car {
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
    Car(const types::id id, const std::string name, const types::health health, const types::weight weight);

    /**
     * Usual constructor with maximum health.
     * @param id ID of the car.
     * @param name Human-readable name of the car.
     * @param weight Base weight of the car.
     */
    Car(const types::id id, const std::string name, const types::weight weight);

    /**
     * Maximum health points.
     */
    const static types::health maxHealth;

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
struct DestroyedCarError : public std::exception {

    /**
     * Error message.
     * @return Error message.
     */
    const char* what() const throw();
};

/**
 * Normal car object.
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
    const merchandises::merchTypes& merchType;

    /**
     * Merchandise container.
     */
    std::vector<merchandises::MerchLoad> merchContainer;

    /**
     * Setter for merch load.
     */
    void setMerchLoad(const merchandises::MerchLoad& merchLoad);

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
     * @param merchLoad Load in the car.
     */
    LoadCar(const types::id id, const std::string name, const types::health health, const types::weight weight,
            const types::quantity maxQuantity, const merchandises::merchTypes& merchType,
            const merchandises::MerchLoad& merchLoad);

    /**
     * Usual constructor for empty car.
     * @param id ID of the car.
     * @param name Human-readable name of the car.
     * @param health Health points of the car.
     * @param weight Base weight of the car.
     * @param maxQuantity Capacity of the car.
     * @param merchType Type of merch accepted in the car.
     */
    LoadCar(const types::id id, const std::string name, const types::health health, const types::weight weight,
            const types::quantity maxQuantity, const merchandises::merchTypes& merchType);

    /**
     * Usual constructor for car with full health points.
     * @param id ID of the car.
     * @param name Human-readable name of the car.
     * @param weight Base weight of the car.
     * @param maxQuantity Capacity of the car.
     * @param merchType Type of merch accepted in the car.
     * @param merchLoad Load in the car.
     */
    LoadCar(const types::id id, const std::string name, const types::weight weight,
            const types::quantity maxQuantity, const merchandises::merchTypes& merchType,
            const merchandises::MerchLoad& merchLoad);

    /**
     * Usual constructor for empty car with full health points.
     * @param id ID of the car.
     * @param name Human-readable name of the car.
     * @param weight Base weight of the car.
     * @param maxQuantity Capacity of the car.
     * @param merchType Type of merch accepted in the car.
     */
    LoadCar(const types::id id, const std::string name, const types::weight weight,
            const types::quantity maxQuantity, const merchandises::merchTypes& merchType);

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
     * Getter for remaining space in car.
     * @return Current capacity of the car.
     */
    types::quantity getRemainingQuantity() const;

    /**
     * Getter for accepted merch type.
     * @return Type of merch accepted in the car.
     */
    const merchandises::merchTypes& getMerchType() const;

    /**
     * Getter for merch load.
     * @return Load in the car.
     */
    const merchandises::MerchLoad& getMerchLoad() const;

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
     * Load a merch load in the car.
     * @param merchLoad Load to load in the car.
     */
    void load(merchandises::MerchLoad& merchLoad);

    /**
     * Load a certain quantity of a merch load in the car.
     * @param merchLoad Load to load in the car.
     * @param quantity Quantity of load to load only.
     */
    void load(merchandises::MerchLoad& merchLoad, const types::quantity quantity);

    /**
     * Unload merch loads from the car.
     * @param quantity Quantity of load to unload.
     */
    void unLoad(const types::quantity quantity);
};

/**
 * Error class used when a load cannot be loaded in the car.
 */
struct CannotLoadError : public std::exception {
    /**
     * Error message.
     * @return Error message.
     */
    const char* what() const throw();

};

/**
 * Error class used when there is not enough space in the car.
 */
struct NotEnoughSpaceError : public std::exception {
    /**
     * Error message.
     * @return Error message.
     */
    const char* what() const throw();
};

/**
 * Error class used when there is not enough load in the car.
 */
struct NotEnoughLoadError : public std::exception {
    /**
     * Error message.
     * @return Error message.
     */
    const char* what() const throw();
};

/**
 * Error class when the car is empty.
 */
struct IsEmptyError : public std::exception {
    /**
     * Error message.
     * @return Error message.
     */
    const char* what() const throw();
};

}

#endif // ifndef CARS_HPP
