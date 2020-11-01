#include <boost/test/unit_test.hpp>

#include "gameplay/train/cars.hpp"
#include "gameplay/train/train.hpp"

BOOST_AUTO_TEST_SUITE(train)

BOOST_AUTO_TEST_SUITE(consist)

BOOST_AUTO_TEST_CASE(testCreate) {
    // create an empty train
    train::Train train;

    // add some cars
    auto merch1 = std::make_shared<cars::LoadCar>(cars::Merchandise());
    auto merch2 = std::make_shared<cars::LoadCar>(cars::Merchandise());
    train.addCar(merch1);
    train.addCar(merch2);
}

BOOST_AUTO_TEST_SUITE_END() // consist

BOOST_AUTO_TEST_SUITE_END() // train
