#include "cars.hpp"

const int cars::Car::maxHealth = 100;

cars::Car::Car() :
    id(0), name(""), health(maxHealth), weight(0) {}

cars::Car::Car(const size_t id, const std::string name, const int health,
               const float weight) :
    id(id), name(name), health(health), weight(weight) {}

cars::Car::Car(const size_t id, const std::string name, const float weight) :
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
    if (isDestroyed()) throw DestroyedCarError();

    health = maxHealth;
}

const char* cars::DestroyedCarError::what() const throw() {
    return "Car is destroyed";
}

float cars::NormalCar::getWeight() const {
    return weight;
}

cars::LoadCar::LoadCar() :
    Car(), maxQuantity(0), merchType(merchandises::merchTypes::none),
    empty(true) {}

cars::LoadCar::LoadCar(const std::size_t id, const std::string name, const int health,
                       const float weight, const std::size_t maxQuantity, const merchandises::merchTypes merchType,
                       merchandises::MerchLoad& otherMerchLoad) :
    Car(id, name, health, weight), maxQuantity(maxQuantity), merchType(merchType), empty(true) {
    setMerchLoad(otherMerchLoad);
}

cars::LoadCar::LoadCar(const std::size_t id, const std::string name, const int health,
                       const float weight, const std::size_t maxQuantity,
                       const merchandises::merchTypes merchType) :
    Car(id, name, health, weight), maxQuantity(maxQuantity), merchType(merchType), empty(true) {}

cars::LoadCar::LoadCar(const std::size_t id, const std::string name, const float weight,
                       const std::size_t maxQuantity, const merchandises::merchTypes merchType,
                       merchandises::MerchLoad& otherMerchLoad) :
    Car(id, name, weight), maxQuantity(maxQuantity), merchType(merchType), empty(true) {
    setMerchLoad(otherMerchLoad);
}

cars::LoadCar::LoadCar(const std::size_t id, const std::string name, const float weight,
                       const std::size_t maxQuantity, const merchandises::merchTypes merchType) :
    Car(id, name, weight), maxQuantity(maxQuantity), merchType(merchType), empty(true) {}

void cars::LoadCar::setMerchLoad(const merchandises::MerchLoad& otherMerchLoad) {
    // do not set merch load if the load is empty
    if (!otherMerchLoad.getQuantity()) return;

    // check there is enouth place in the car
    const merchandises::MerchLoad* otherMerchLoadP = &otherMerchLoad;
    if (otherMerchLoad.getQuantity() > maxQuantity) throw NotEnoughSpaceError();

    // load the car
    merchLoad = otherMerchLoad;
    empty = false;
}

float cars::LoadCar::getWeight() const {
    // base weight if car is destroyed
    if (isDestroyed()) return weight;

    // base weight if car is empty
    if (isEmpty()) return weight;

    // base weight + load weight
    // 1 quantity is 1 ton
    return weight + merchLoad.getQuantity();
}

std::size_t cars::LoadCar::getMaxQuantity() const {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError();

    return maxQuantity;
}

std::size_t cars::LoadCar::getRemainingQuantity() const {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError();

    if (empty) return maxQuantity;

    return maxQuantity - merchLoad.getQuantity();
}

merchandises::merchTypes cars::LoadCar::getMerchType() const {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError();

    return merchType;
}

merchandises::MerchLoad cars::LoadCar::getMerchLoad() const {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError();

    // if (empty) return;

    return merchLoad;
}

bool cars::LoadCar::isEmpty() const {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError();

    return empty;
}

bool cars::LoadCar::isFull() const {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError();

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
    // TODO remove this
    const merchandises::MerchLoad* otherMerchLoadP = &otherMerchLoad;

    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError();

    // check the merch load can be loaded at all
    if (!canLoad(otherMerchLoad)) throw CannotLoadError();

    // check there is enouth free space
    if (getRemainingQuantity() < quantity) throw NotEnoughSpaceError();

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
    if (isDestroyed()) throw DestroyedCarError();

    // check the quantity is not more than current one
    if (quantity > merchLoad.getQuantity()) throw NotEnoughLoadError();

    // unload it from the car
    merchLoad.substract(quantity);

    // check emptyness
    if (merchLoad.getQuantity() == 0) empty = true;
}

const char* cars::CannotLoadError::what() const throw () {
    return "Car cannot load this merch";
}

const char* cars::NotEnoughSpaceError::what() const throw () {
    return "Car cannot load this merch load: not enough space";
}

const char* cars::NotEnoughLoadError::what() const throw() {
    return "Car cannot unload this merch load: not enough load";
}
