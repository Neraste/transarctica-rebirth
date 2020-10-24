#ifndef TRAIN_HPP
#define TRAIN_HPP

#include <vector>

#include <boost/any.hpp>

#include "cars.hpp"
#include "merchandises.hpp"
#include "types.hpp"

namespace train {

class Train {
  protected:

    std::vector<boost::any> cars;

  public:

    Train();

    const std::vector<const merchandises::MerchLoad&> getMerchLoads() const;

    const std::vector<const cars::Car&> getCars() const;

    void buy(merchandises::MerchLoad& merchLoad, const types::quantity quantity);

    bool canBuy(merchandises::MerchLoad& merchLoad, const types::quantity quantity);

    void sell(merchandises::Merch& merch, const types::quantity quantity);

    bool canSell(merchandises::Merch& merch, const types::quantity quantity);

    void addCar(cars::Car& car);

    void removeCar(cars::Car& car);

};

}

#endif //ifndef TRAIN_HPP
