#include <boost/test/unit_test.hpp>

#include "gameplay/train/cars.hpp"
#include "gameplay/train/train.hpp"

BOOST_AUTO_TEST_SUITE(train)

BOOST_AUTO_TEST_SUITE(consist)

BOOST_AUTO_TEST_CASE(testCreate) {
    // create an empty train
    train::Train train;

    // add some cars
    auto cargo1 = std::make_shared<cars::LoadCar>(cars::Merchandise());
    auto cargo2 = std::make_shared<cars::LoadCar>(cars::Merchandise());
    train.addCar(cargo1);
    train.addCar(cargo2);

    // check cars
    BOOST_TEST(train.getCar(cargo1->getCarId()) == cargo1);
    BOOST_TEST(train.getCar(cargo2->getCarId()) == cargo2);
}

BOOST_AUTO_TEST_SUITE_END() // consist

BOOST_AUTO_TEST_SUITE_END() // train
