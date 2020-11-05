#include "gameplay/train/cars.hpp"

types::id cars::Car::latestCarId = 0;

const types::health cars::Car::maxHealth = 100;

cars::Car::Car() :
    carId(++latestCarId), id(0), name(""), health(maxHealth), weight(0) {}

cars::Car::Car(const types::id id, const std::string name, const types::health health,
               const types::weight weight) :
    carId(++latestCarId), id(id), name(name), health(health), weight(weight) {}

cars::Car::Car(const types::id id, const std::string name, const types::weight weight) :
    carId(++latestCarId), id(id), name(name), health(maxHealth), weight(weight) {}

cars::Car::Car(const Car& car) :
    carId(++latestCarId), id(car.id), name(car.name), health(car.health), weight(car.weight) {}

types::id cars::Car::getCarId() const {
    return carId;
}

types::id cars::Car::getId() const {
    return id;
}

std::string cars::Car::getName() const {
    return name;
}

types::health cars::Car::getMaxHealth() const {
    return maxHealth;
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

types::weight cars::NormalCar::getWeight() const {
    return weight;
}

cars::LoadCar::LoadCar() :
    Car(), maxQuantity(0), merchType(merchandises::nullMerchType),
    merchLoad() {}

cars::LoadCar::LoadCar(const types::id id,
                       const std::string name,
                       const types::health health,
                       const types::weight weight,
                       const types::quantity maxQuantity,
                       const merchandises::MerchTypes merchType,
                       merchandises::MerchLoad& otherMerchLoad) :
    Car(id, name, health, weight), maxQuantity(maxQuantity), merchType(merchType), merchLoad() {
    setMerchLoad(otherMerchLoad);
}

cars::LoadCar::LoadCar(const types::id id,
                       const std::string name,
                       const types::health health,
                       const types::weight weight,
                       const types::quantity maxQuantity,
                       const merchandises::MerchTypes merchType,
                       std::shared_ptr<merchandises::MerchLoad>& otherMerchLoad) :
    Car(id, name, health, weight), maxQuantity(maxQuantity), merchType(merchType),
    merchLoad() {
    setMerchLoad(otherMerchLoad);
}

cars::LoadCar::LoadCar(const types::id id,
                       const std::string name,
                       const types::health health,
                       const types::weight weight,
                       const types::quantity maxQuantity,
                       const merchandises::MerchTypes merchType) :
    Car(id, name, health, weight), maxQuantity(maxQuantity), merchType(merchType),
    merchLoad() {}

cars::LoadCar::LoadCar(const types::id id,
                       const std::string name,
                       const types::weight weight,
                       const types::quantity maxQuantity,
                       const merchandises::MerchTypes merchType,
                       merchandises::MerchLoad& otherMerchLoad) :
    Car(id, name, weight), maxQuantity(maxQuantity), merchType(merchType), merchLoad() {
    setMerchLoad(otherMerchLoad);
}

cars::LoadCar::LoadCar(const types::id id,
                       const std::string name,
                       const types::weight weight,
                       const types::quantity maxQuantity,
                       const merchandises::MerchTypes merchType,
                       std::shared_ptr<merchandises::MerchLoad>& otherMerchLoad) :
    Car(id, name, weight), maxQuantity(maxQuantity), merchType(merchType),
    merchLoad() {
    setMerchLoad(otherMerchLoad);
}

cars::LoadCar::LoadCar(const types::id id,
                       const std::string name,
                       const types::weight weight,
                       const types::quantity maxQuantity,
                       const merchandises::MerchTypes merchType) :
    Car(id, name, weight), maxQuantity(maxQuantity), merchType(merchType),
    merchLoad() {}

void cars::LoadCar::setMerchLoad(const merchandises::MerchLoad& otherMerchLoad) {
    setMerchLoad(std::make_shared<merchandises::MerchLoad>(std::move(otherMerchLoad)));
}

void cars::LoadCar::setMerchLoad(const std::shared_ptr<merchandises::MerchLoad>& otherMerchLoad) {
    // do not set merch load if the load is empty
    if (!otherMerchLoad->getQuantity()) return;

    // check there is enouth place in the car
    if (otherMerchLoad->getQuantity() > maxQuantity) throw NotEnoughSpaceError();

    // load the merch on board
    merchLoad = otherMerchLoad;
}

types::weight cars::LoadCar::getWeight() const {
    // base weight if car is destroyed
    if (isDestroyed()) return weight;

    // base weight if car is empty
    if (isEmpty()) return weight;

    // base weight + load weight
    // 1 quantity is 1 ton
    return weight + getQuantity();
}

types::quantity cars::LoadCar::getMaxQuantity() const {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError();

    return maxQuantity;
}

types::quantity cars::LoadCar::getQuantity() const {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError();

    // nothing if empty
    if (isEmpty()) return 0;

    return merchLoad->getQuantity();
}

types::quantity cars::LoadCar::getRemainingQuantity() const {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError();

    if (isEmpty()) return maxQuantity;

    return maxQuantity - getQuantity();
}

merchandises::MerchTypes cars::LoadCar::getMerchType() const {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError();

    return merchType;
}

std::shared_ptr<merchandises::MerchLoad> cars::LoadCar::getMerchLoad() {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError();

    if (isEmpty()) throw IsEmptyError();

    return merchLoad;
}

bool cars::LoadCar::isEmpty() const {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError();

    return !bool(merchLoad);
}

bool cars::LoadCar::isFull() const {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError();

    if (isEmpty()) return false;

    return getRemainingQuantity() <= 0;
}

bool cars::LoadCar::canLoad(const merchandises::MerchLoad& otherMerchLoad) const {
    // copy the merch load
    return canLoad(std::make_shared<merchandises::MerchLoad>(otherMerchLoad));
}

bool cars::LoadCar::canLoad(const std::shared_ptr<merchandises::MerchLoad>& otherMerchLoad) const {
    // no if the car is destroyed
    if (isDestroyed()) return false;

    // no if the merch type are different
    if (otherMerchLoad->getMerch().getType() != getMerchType()) return false;

    // yes if the car is empty
    if (isEmpty()) return true;

    // no if the car is full
    if (isFull()) return false;

    // if the car contains the same merch
    return merchLoad->getMerch() == otherMerchLoad->getMerch();
}

void cars::LoadCar::load(merchandises::MerchLoad& otherMerchLoad) {
    load(otherMerchLoad, otherMerchLoad.getQuantity());
}

void cars::LoadCar::load(merchandises::MerchLoad& otherMerchLoad, const types::quantity quantity) {
    // copy the merch load in a teporary shared pointer
    std::shared_ptr<merchandises::MerchLoad> otherMerchLoadTemp =
        std::make_shared<merchandises::MerchLoad>(otherMerchLoad);

    load(otherMerchLoadTemp, quantity);

    // update the merch load
    otherMerchLoad.substract(quantity);
}

void cars::LoadCar::load(std::shared_ptr<merchandises::MerchLoad>& otherMerchLoad,
                         const types::quantity quantity) {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError();

    // check the merch load can be loaded at all
    if (!canLoad(otherMerchLoad)) throw CannotLoadError();

    // check there is enouth free space
    if (getRemainingQuantity() < quantity) throw NotEnoughSpaceError();

    // prepare to load it to the car
    auto toLoadMerchLoad = otherMerchLoad->split(quantity);

    if (isEmpty()) {
        // if the car is empty, load it with the new merch load
        merchLoad = std::make_shared<merchandises::MerchLoad>(std::move(toLoadMerchLoad));
    } else {
        // otherwise load more merch load
        merchLoad->add(toLoadMerchLoad);
    }
}

merchandises::MerchLoad cars::LoadCar::unLoad(const types::quantity quantity) {
    // impossible if the car is destroyed
    if (isDestroyed()) throw DestroyedCarError();

    // check the quantity is not more than current one
    if (quantity > getQuantity()) throw NotEnoughLoadError();

    // unload it from the car
    auto toUnloadMerchLoad = merchLoad->split(quantity);

    // check emptyness
    if (getQuantity() == 0) merchLoad.reset();

    return toUnloadMerchLoad;
}

cars::LoadCar cars::LoadCarModel::operator()(types::health requestedHealth,
        merchandises::MerchLoad& requestedMerchLoad) const {
    return LoadCar(id, name, requestedHealth, weight, maxQuantity, merchType, requestedMerchLoad);
}

cars::LoadCar cars::LoadCarModel::operator()(types::health requestedHealth) const {
    return LoadCar(id, name, requestedHealth, weight, maxQuantity, merchType);
}

cars::LoadCar cars::LoadCarModel::operator()(merchandises::MerchLoad& requestedMerchLoad) const {
    return LoadCar(id, name, weight, maxQuantity, merchType, requestedMerchLoad);
}

cars::LoadCar cars::LoadCarModel::operator()() const {
    return LoadCar(id, name, weight, maxQuantity, merchType);
}
