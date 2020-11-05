#ifndef TRAIN_HPP
#define TRAIN_HPP

#include <memory>
#include <vector>

#include "cars.hpp"
#include "merchandises.hpp"
#include "types.hpp"

namespace train {

class Train {
  protected:

    std::vector<std::shared_ptr<cars::Car>> cars;

    std::vector<std::shared_ptr<cars::Car>>::iterator getCarIterator(const std::size_t carId);

  public:

    Train();

    const std::vector<const merchandises::MerchLoad&> getMerchLoads() const;

    const std::vector<const cars::Car&> getCars() const;

    void buy(merchandises::MerchLoad& merchLoad, const types::quantity quantity);

    bool canBuy(merchandises::MerchLoad& merchLoad, const types::quantity quantity);

    void sell(merchandises::Merch& merch, const types::quantity quantity);

    bool canSell(merchandises::Merch& merch, const types::quantity quantity);

    void addCar(std::shared_ptr<cars::Car> car);

    std::shared_ptr<cars::Car> removeCar(const std::size_t carId);

    void moveCar(const std::size_t carId, const std::size_t position);

    std::shared_ptr<cars::Car> getCar(const std::size_t carId);
};

/**
 * Error class when a car cannot be found.
 */
struct CarNotFoundError : public exceptions::TransarcticaRebirthError {
    /**
     * Error message.
     * @return Error message.
     */
    const char* what() const throw() {
        return "Car not found";
    }
};

/**
 * Error class when a car is moved to invalid position.
 */
struct CarInvalidPositionError : public exceptions::TransarcticaRebirthError {
    /**
     * Error message.
     * @return Error message.
     */
    const char* what() const throw() {
        return "Position not possible";
    }
};

/**
 * Error class used when trying to remove a special car.
 */
struct SpecialCarRemoveError : public exceptions::TransarcticaRebirthError {

    /**
     * Error message.
     * @return Error message.
     */
    const char* what() const throw() {
        return "This car cannot be removed";
    }
};

}

#endif //ifndef TRAIN_HPP
