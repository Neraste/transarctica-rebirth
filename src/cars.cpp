#include "cars.hpp"

const types::health cars::Car::maxHealth = 100;

cars::Car::Car() :
    id(0), name(""), health(maxHealth), weight(0) {}

cars::Car::Car(const types::id id, const std::string name, const types::health health,
               const types::weight weight) :
    id(id), name(name), health(health), weight(weight) {}

cars::Car::Car(const types::id id, const std::string name, const types::weight weight) :
    id(id), name(name), health(maxHealth), weight(weight) {}

types::id cars::Car::getId() const {
    return id;
}

std::string cars::Car::getName() const {
    return name;
}

types::health cars::Car::getHealth() const {
    return health;
}

bool cars::Car::isDestroyed() const {
    return health <= 0;
}

void cars::Car::takeDammage(types::health attack) {
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

types::weight cars::NormalCar::getWeight() const {
    return weight;
}

cars::LoadCar::LoadCar() :
    Car(), maxQuantity(0), merchType(merchandises::nullMerchType),
    merchContainer(std::vector<merchandises::MerchLoad>()) {}

cars::LoadCar::LoadCar(const types::id id, const std::string name, const types::health health,
                       const types::weight weight, const types::quantity maxQuantity, const merchandises::merchTypes& merchType,
                       const merchandises::MerchLoad& otherMerchLoad) :
    Car(id, name, health, weight), maxQuantity(maxQuantity), merchType(merchType), merchContainer(std::vector<merchandises::MerchLoad>()) {
    setMerchLoad(otherMerchLoad);
}

cars::LoadCar::LoadCar(const types::id id, const std::string name, const types::health health,
                       const types::weight weight, const types::quantity maxQuantity,
                       const merchandises::merchTypes& merchType) :
    Car(id, name, health, weight), maxQuantity(maxQuantity), merchType(merchType), merchContainer(std::vector<merchandises::MerchLoad>()) {}

cars::LoadCar::LoadCar(const types::id id, const std::string name, const types::weight weight,
                       const types::quantity maxQuantity, const merchandises::merchTypes& merchType,
                       const merchandises::MerchLoad& otherMerchLoad) :
    Car(id, name, weight), maxQuantity(maxQuantity), merchType(merchType), merchContainer(std::vector<merchandises::MerchLoad>()) {
    setMerchLoad(otherMerchLoad);
}

cars::LoadCar::LoadCar(const types::id id, const std::string name, const types::weight weight,
                       const types::quantity maxQuantity, const merchandises::merchTypes& merchType) :
    Car(id, name, weight), maxQuantity(maxQuantity), merchType(merchType), merchContainer(std::vector<merchandises::MerchLoad>()) {}

void cars::LoadCar::setMerchLoad(const merchandises::MerchLoad& otherMerchLoad) {
    // do not set merch load if the load is empty
    if (!otherMerchLoad.getQuantity()) return;

    // check there is enouth place in the car
    if (otherMerchLoad.getQuantity() > maxQuantity) throw NotEnoughSpaceError();

    // load the car
    merchContainer.push_back(otherMerchLoad);
}

types::weight cars::LoadCar::getWeight() const {
    // base weight if car is destroyed
    if (isDestroyed()) return weight;

    // base weight if car is empty
    if (isEmpty()) return weight;

    // base weight + load weight
    // 1 quantity is 1 ton
    return weight + merchContainer.at(0).getQuantity();
}

types::quantity cars::LoadCar::getMaxQuantity() const {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError();

    return maxQuantity;
}

types::quantity cars::LoadCar::getRemainingQuantity() const {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError();

    if (isEmpty()) return maxQuantity;

    return maxQuantity - merchContainer.at(0).getQuantity();
}

const merchandises::merchTypes& cars::LoadCar::getMerchType() const {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError();

    return merchType;
}

const merchandises::MerchLoad& cars::LoadCar::getMerchLoad() const {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError();

    if (isEmpty()) throw IsEmptyError();

    return merchContainer.at(0);
}

bool cars::LoadCar::isEmpty() const {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError();

    return merchContainer.empty();
}

bool cars::LoadCar::isFull() const {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError();

    if (isEmpty()) return false;

    return (getRemainingQuantity() <= 0);
}

bool cars::LoadCar::canLoad(const merchandises::MerchLoad& otherMerchLoad) const {
    // no if the car is destroyed
    if (isDestroyed()) return false;

    // no if the merch type are different
    if (otherMerchLoad.getMerch().getType() != getMerchType()) return false;

    // yes if the car is empty
    if (isEmpty()) return true;

    // no if the car is full
    if (isFull()) return false;

    // if the car contains the same merch
    return (merchContainer.at(0).getMerch() == otherMerchLoad.getMerch());
}

void cars::LoadCar::load(merchandises::MerchLoad& otherMerchLoad) {
    load(otherMerchLoad, otherMerchLoad.getQuantity());
}

void cars::LoadCar::load(merchandises::MerchLoad& otherMerchLoad, const types::quantity quantity) {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError();

    // check the merch load can be loaded at all
    if (!canLoad(otherMerchLoad)) throw CannotLoadError();

    // check there is enouth free space
    if (getRemainingQuantity() < quantity) throw NotEnoughSpaceError();

    // load it to the car
    otherMerchLoad.substract(quantity);

    if (isEmpty()) {
        // if the car is empty, load it with the new merch load
        merchContainer.push_back(merchandises::MerchLoad(otherMerchLoad.getMerch(), quantity,
                                            otherMerchLoad.getPrice()));
    } else {
        // otherwise load more merch load
        merchContainer.at(0).add(quantity, otherMerchLoad.getPrice());
    }
}

void cars::LoadCar::unLoad(const types::quantity quantity) {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError();

    // check the quantity is not more than current one
    if (quantity > merchContainer.at(0).getQuantity()) throw NotEnoughLoadError();

    // unload it from the car
    merchContainer.at(0).substract(quantity);

    // check emptyness
    if (merchContainer.at(0).getQuantity() == 0) merchContainer.clear();
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

const char* cars::IsEmptyError::what() const throw() {
    return "Car is empty";
}
