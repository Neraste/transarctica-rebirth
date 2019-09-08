#ifndef CARS_HPP
#define CARS_HPP

#include <exception>
#include <string>

#include "merchandises.hpp"

namespace cars {

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
     */
    std::size_t weight;

  public:

    /**
     * Default constructor.
     */
    Car();

    /**
     * Usual constructor.
     */
    Car(const size_t id, const std::string name, const int health, const std::size_t weight);

    /**
     * Usual constructor with maximum health.
     */
    Car(const size_t id, const std::string name, const std::size_t weight);

    /**
     * Maximum health points.
     */
    const static int maxHealth;

    /**
     * Getter for ID.
     */
    std::size_t getId() const;

    /**
     * Getter for name.
     */
    std::string getName() const;

    /**
     * Getter for health points.
     */
    int getHealth() const;

    /**
     * Getter for weight.
     */
    virtual std::size_t getWeight() const = 0;

    /**
     * Indicate if the car is destroyed.
     */
    bool isDestroyed() const;

    /**
     * Take dammage.
     */
    void takeDammage(int attack);

    /**
     * Repair car and restore full helth points.
     */
    void repair();
};

class DestroyedCarError : public std::exception {
    /**
     * Destroyed car.
     */
    const Car* car;

  public:

    /**
     * Usual constructor.
     */
    DestroyedCarError(const Car* car);

    /**
     * Error message.
     */
    const char* what() const throw();
};

class NormalCar : public Car {
    using Car::Car;

  public:

    /**
     * Getter for weight.
     * It simply returns the base weight.
     */
    std::size_t getWeight() const;
};

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
     */
    LoadCar(const std::size_t id, const std::string name, const int health, const std::size_t weight,
            const std::size_t maxQuantity, const merchandises::merchTypes merchType,
            merchandises::MerchLoad& merchLoad);

    /**
     * Usual constructor for empty car.
     */
    LoadCar(const std::size_t id, const std::string name, const int health, const std::size_t weight,
            const std::size_t maxQuantity, const merchandises::merchTypes merchType);

    /**
     * Usual constructor for car with full health points.
     */
    LoadCar(const std::size_t id, const std::string name, const std::size_t weight,
            const std::size_t maxQuantity, const merchandises::merchTypes merchType,
            merchandises::MerchLoad& merchLoad);

    /**
     * Usual constructor for empty car with full health points.
     */
    LoadCar(const std::size_t id, const std::string name, const std::size_t weight,
            const std::size_t maxQuantity, const merchandises::merchTypes merchType);

    /**
     * Getter for weight.
     * It adds the base weight of the car and the weight of the merch load.
     */
    std::size_t getWeight() const;

    /**
     * Getter for max quantity of merch load.
     */
    std::size_t getMaxQuantity() const;

    /**
     * Getter for remaining space in car.
     */
    std::size_t getRemainingQuantity() const;

    /**
     * Getter for accepted merch type.
     */
    merchandises::merchTypes getMerchType() const;

    /**
     * Getter for merch load.
     */
    merchandises::MerchLoad getMerchLoad() const;

    /**
     * Tells if the car is empty.
     */
    bool isEmpty() const;

    /**
     * Tells if the car is full.
     */
    bool isFull() const;

    /**
     * Tell if the car can load this merch load.
     */
    bool canLoad(const merchandises::MerchLoad& merchLoad) const;

    /**
     * Load a merch load in the car.
     */
    void load(merchandises::MerchLoad& merchLoad);

    /**
     * Load a certain quantity of a merch load in the car.
     */
    void load(merchandises::MerchLoad& merchLoad, const std::size_t quantity);

    /**
     * Unload merch loads from the car.
     */
    void unLoad(const std::size_t quantity);
};
}

#endif // ifndef CARS_HPP
