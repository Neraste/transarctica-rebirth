#include <stdexcept>

#include <boost/format.hpp>

#include "cars.hpp"

const int cars::Car::maxHealth = 100;

cars::Car::Car() :
    id(0), name(""), health(maxHealth), weight(0) {}

cars::Car::Car(const size_t id, const std::string name, const int health,
               const std::size_t weight) :
    id(id), name(name), health(health), weight(weight) {}

cars::Car::Car(const size_t id, const std::string name, const std::size_t weight) :
    id(id), name(name), health(maxHealth), weight(weight) {}

std::size_t cars::Car::getId() const {
    return id;
}

std::string cars::Car::getName() const {
    return name;
}

int cars::Car::getHealth() const {
    return health;
}

bool cars::Car::isDestroyed() const {
    return health <= 0;
}

void cars::Car::takeDammage(int attack) {
    if (isDestroyed()) return;

    health -= attack;
}

void cars::Car::repair() {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError(this);

    health = maxHealth;
}

cars::DestroyedCarError::DestroyedCarError(const Car* car) :
    car(car) {}

const char* cars::DestroyedCarError::what() const throw() {
    const char* message = (boost::format("Car %1% (%2%) is destroyed") % car->getName() %
                           car->getId()).str().c_str();
    return message;
}

std::size_t cars::NormalCar::getWeight() const {
    return weight;
}

cars::LoadCar::LoadCar() :
    Car(), maxQuantity(0), merchType(merchandises::merchTypes::none),
    empty(true) {}

cars::LoadCar::LoadCar(const std::size_t id, const std::string name, const int health,
                       const std::size_t weight, const std::size_t maxQuantity, const merchandises::merchTypes merchType,
                       merchandises::MerchLoad& otherMerchLoad) :
    Car(id, name, health, weight), maxQuantity(maxQuantity), merchType(merchType), empty(true) {
    setMerchLoad(otherMerchLoad);
}

cars::LoadCar::LoadCar(const std::size_t id, const std::string name, const int health,
                       const std::size_t weight, const std::size_t maxQuantity,
                       const merchandises::merchTypes merchType) :
    Car(id, name, health, weight), maxQuantity(maxQuantity), merchType(merchType), empty(true) {}

cars::LoadCar::LoadCar(const std::size_t id, const std::string name, const std::size_t weight,
                       const std::size_t maxQuantity, const merchandises::merchTypes merchType,
                       merchandises::MerchLoad& otherMerchLoad) :
    Car(id, name, weight), maxQuantity(maxQuantity), merchType(merchType), empty(true) {
    setMerchLoad(otherMerchLoad);
}

cars::LoadCar::LoadCar(const std::size_t id, const std::string name, const std::size_t weight,
                       const std::size_t maxQuantity, const merchandises::merchTypes merchType) :
    Car(id, name, weight), maxQuantity(maxQuantity), merchType(merchType), empty(true) {}

void cars::LoadCar::setMerchLoad(const merchandises::MerchLoad& otherMerchLoad) {
    if (!otherMerchLoad.getQuantity()) return;

    if (otherMerchLoad.getQuantity() > maxQuantity) throw std::runtime_error("Excessive quantity");

    merchLoad = otherMerchLoad;
    empty = false;
}

std::size_t cars::LoadCar::getWeight() const {
    return weight;
}

std::size_t cars::LoadCar::getMaxQuantity() const {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError(this);

    return maxQuantity;
}

std::size_t cars::LoadCar::getRemainingQuantity() const {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError(this);

    if (empty) return maxQuantity;

    return maxQuantity - merchLoad.getQuantity();
}

merchandises::merchTypes cars::LoadCar::getMerchType() const {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError(this);

    return merchType;
}

merchandises::MerchLoad cars::LoadCar::getMerchLoad() const {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError(this);

    // if (empty) return;

    return merchLoad;
}

bool cars::LoadCar::isEmpty() const {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError(this);

    return empty;
}

bool cars::LoadCar::isFull() const {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError(this);

    if (empty) return false;

    return (getRemainingQuantity() <= 0);
}

bool cars::LoadCar::canLoad(const merchandises::MerchLoad& otherMerchLoad) const {
    // no if the car is destroyed
    if (isDestroyed()) return false;

    // no if the merch type are different
    if (otherMerchLoad.getMerch().getType() != getMerchType()) return false;

    // yes if the car is empty
    if (empty) return true;

    // no if the car is full
    if (isFull()) return false;

    // if the car contains the same merch
    return (merchLoad.getMerch() == otherMerchLoad.getMerch());
}

void cars::LoadCar::load(merchandises::MerchLoad& otherMerchLoad) {
    load(otherMerchLoad, otherMerchLoad.getQuantity());
}

void cars::LoadCar::load(merchandises::MerchLoad& otherMerchLoad, const std::size_t quantity) {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError(this);

    // check the merch load can be loaded at all
    if (!canLoad(otherMerchLoad)) throw std::runtime_error("Cannot load this load");

    // check there is enouth free space
    if (getRemainingQuantity() < quantity) throw std::runtime_error("Quantity larger than remaining");

    // load it to the car
    otherMerchLoad.substract(quantity);

    if (empty) {
        // if the car is empty, load it with the new merch load
        merchLoad = merchandises::MerchLoad(otherMerchLoad.getMerch(), quantity,
                                            otherMerchLoad.getPrice());
        empty = false;
    } else {
        // otherwise load more merch load
        merchLoad.add(quantity, otherMerchLoad.getPrice());
    }
}

void cars::LoadCar::unLoad(const std::size_t quantity) {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError(this);

    // check the quantity is not more than current one
    if (quantity > merchLoad.getQuantity()) {
        throw std::runtime_error("Quantity fewer than requested");
    }

    // unload it from the car
    merchLoad.substract(quantity);

    // check emptyness
    if (merchLoad.getQuantity() == 0) empty = true;
}
