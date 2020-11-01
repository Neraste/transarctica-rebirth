#include "gameplay/train/train.hpp"

train::Train::Train() {}

void train::Train::addCar(cars::Car& car) {
    cars.push_back(std::shared_ptr<cars::Car>(&car));
}

std::shared_ptr<cars::Car> train::Train::removeCar(const std::size_t carId) {
    // TODO check car type
    // esp. cannot remove SpecialCar
    auto it = getCarIterator(carId);
    auto car = *it;
    cars.erase(it);
    return car;
}

std::shared_ptr<cars::Car> train::Train::getCar(const std::size_t carId) {
    return *getCarIterator(carId);
}

void train::Train::moveCar(const std::size_t carId, const std::size_t position) {
    // TODO check position
    auto car = removeCar(carId);
    cars.emplace(cars.begin() + position, car);
}

std::vector<std::shared_ptr<cars::Car>>::iterator train::Train::getCarIterator(
const std::size_t carId) {
    auto it = cars.begin();

    for (const auto car : cars) {
        if (car->getId() == carId) {
            return it;
        }

        it++;
    }

    // TODO raise exception if not found
}
