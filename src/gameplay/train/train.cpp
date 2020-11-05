#include <typeinfo>

#include "gameplay/train/train.hpp"

train::Train::Train() {}

void train::Train::addCar(std::shared_ptr<cars::Car> car) {
    cars.push_back(car);
}

std::shared_ptr<cars::Car> train::Train::removeCar(const std::size_t carId) {
    // esp. cannot remove SpecialCar
    auto it = getCarIterator(carId);
    auto car = *it;

    // check car is not special
    // this means we can't move a special car for now
    if (typeid(car).hash_code() == typeid(cars::SpecialCar).hash_code()) throw SpecialCarRemoveError();

    cars.erase(it);
    return car;
}

std::shared_ptr<cars::Car> train::Train::getCar(const std::size_t carId) {
    return *getCarIterator(carId);
}

void train::Train::moveCar(const std::size_t carId, const std::size_t position) {
    // check position
    if (position >= cars.size()) throw CarInvalidPositionError();

    auto car = removeCar(carId);
    cars.emplace(cars.begin() + position, car);
}

std::vector<std::shared_ptr<cars::Car>>::iterator train::Train::getCarIterator(
const std::size_t carId) {
    auto it = cars.begin();

    for (const auto car : cars) {
        if (car->getCarId() == carId) {
            return it;
        }

        it++;
    }

    throw CarNotFoundError();
}
