#ifndef CARS_HPP
#define CARS_HPP

#include <exception>
#include <string>

#include "merchandises.hpp"

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
    std::size_t id;

    /**
     * Human-readable name of the car.
     */
    std::string name;

    /**
     * Health points.
     * The car is destroyed if the value is lower than or equal to 0.
     */
    int health;

    /**
     * Base weight of the car.
     * It does not include weight of the payload.
     */
    float weight;

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
    Car(const size_t id, const std::string name, const int health, const float weight);

    /**
     * Usual constructor with maximum health.
     * @param id ID of the car.
     * @param name Human-readable name of the car.
     * @param weight Base weight of the car.
     */
    Car(const size_t id, const std::string name, const float weight);

    /**
     * Maximum health points.
     */
    const static int maxHealth;

    /**
     * Getter for ID.
     * @return ID of the car.
     */
    std::size_t getId() const;

    /**
     * Getter for name.
     * @return Human-readable name of the car.
     */
    std::string getName() const;

    /**
     * Getter for health points.
     * @return Health points of the car.
     */
    int getHealth() const;

    /**
     * Getter for weight.
     * @return Total weight of the car.
     */
    virtual float getWeight() const = 0;

    /**
     * Indicate if the car is destroyed.
     * @return True if the car has 0 health points or lower.
     */
    bool isDestroyed() const;

    /**
     * Take dammage.
     * @param attack Value of the attack.
     */
    void takeDammage(int attack);

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
    float getWeight() const;
};

/**
 * Car that accept a load.
 */
class LoadCar : public Car {
  protected:

    /**
     * Maximum quantity of merchandise loads.
     */
    std::size_t maxQuantity;

    /**
     * Type of merch accepted.
     */
    merchandises::merchTypes merchType;

    /**
     * If the car is empty.
     */
    bool empty;

    /**
     * Merchandise load.
     */
    merchandises::MerchLoad merchLoad;

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
    LoadCar(const std::size_t id, const std::string name, const int health, const float weight,
            const std::size_t maxQuantity, const merchandises::merchTypes merchType,
            merchandises::MerchLoad& merchLoad);

    /**
     * Usual constructor for empty car.
     * @param id ID of the car.
     * @param name Human-readable name of the car.
     * @param health Health points of the car.
     * @param weight Base weight of the car.
     * @param maxQuantity Capacity of the car.
     * @param merchType Type of merch accepted in the car.
     */
    LoadCar(const std::size_t id, const std::string name, const int health, const float weight,
            const std::size_t maxQuantity, const merchandises::merchTypes merchType);

    /**
     * Usual constructor for car with full health points.
     * @param id ID of the car.
     * @param name Human-readable name of the car.
     * @param weight Base weight of the car.
     * @param maxQuantity Capacity of the car.
     * @param merchType Type of merch accepted in the car.
     * @param merchLoad Load in the car.
     */
    LoadCar(const std::size_t id, const std::string name, const float weight,
            const std::size_t maxQuantity, const merchandises::merchTypes merchType,
            merchandises::MerchLoad& merchLoad);

    /**
     * Usual constructor for empty car with full health points.
     * @param id ID of the car.
     * @param name Human-readable name of the car.
     * @param weight Base weight of the car.
     * @param maxQuantity Capacity of the car.
     * @param merchType Type of merch accepted in the car.
     */
    LoadCar(const std::size_t id, const std::string name, const float weight,
            const std::size_t maxQuantity, const merchandises::merchTypes merchType);

    /**
     * Getter for weight.
     * @return Base weight of the car and the weight of the load.
     */
    float getWeight() const;

    /**
     * Getter for max quantity of merch load.
     * @return Total capacity of the car.
     */
    std::size_t getMaxQuantity() const;

    /**
     * Getter for remaining space in car.
     * @return Current capacity of the car.
     */
    std::size_t getRemainingQuantity() const;

    /**
     * Getter for accepted merch type.
     * @return Type of merch accepted in the car.
     */
    merchandises::merchTypes getMerchType() const;

    /**
     * Getter for merch load.
     * @return Load in the car.
     */
    merchandises::MerchLoad getMerchLoad() const;

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
    void load(merchandises::MerchLoad& merchLoad, const std::size_t quantity);

    /**
     * Unload merch loads from the car.
     * @param quantity Quantity of load to unload.
     */
    void unLoad(const std::size_t quantity);
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

}

#endif // ifndef CARS_HPP
