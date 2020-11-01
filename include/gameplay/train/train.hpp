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

}

#endif //ifndef TRAIN_HPP
