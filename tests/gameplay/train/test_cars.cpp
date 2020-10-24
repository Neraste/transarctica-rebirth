#include <iostream>

#include <boost/test/unit_test.hpp>

#include "gameplay/train/cars.hpp"

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(cars)

BOOST_AUTO_TEST_SUITE(normalCar)

BOOST_AUTO_TEST_CASE(testGetters) {
    // create car with usual constructor
    cars::NormalCar cargo(1, "cargo", 50, 100);
    BOOST_TEST(cargo.getId() == 1);
    BOOST_TEST(cargo.getName() == "cargo");
    BOOST_TEST(cargo.getHealth() == 50);
    BOOST_TEST(cargo.getWeight() == 100, tt::tolerance(0.01));
    BOOST_TEST(!cargo.isDestroyed());

    // create car with usual constructor and full health
    cars::NormalCar crane(2, "crane", 50);
    BOOST_TEST(crane.getId() == 2);
    BOOST_TEST(crane.getName() == "crane");
    BOOST_TEST(crane.getHealth() == cars::Car::maxHealth);
    BOOST_TEST(crane.getWeight() == 50, tt::tolerance(0.01));
    BOOST_TEST(!crane.isDestroyed());

    // create car with default constructor
    cars::NormalCar none;
    BOOST_TEST(none.getId() == 0);
    BOOST_TEST(none.getName() == "");
    BOOST_TEST(none.getHealth() == cars::Car::maxHealth);
    BOOST_TEST(none.getWeight() == 0, tt::tolerance(0.01));
    BOOST_TEST(!none.isDestroyed());
}

BOOST_AUTO_TEST_CASE(testDammage) {
    // create a car
    cars::NormalCar cargo(1, "cargo", 100);
    BOOST_TEST(cargo.getHealth() == cars::Car::maxHealth);
    BOOST_TEST(!cargo.isDestroyed());

    // deal dammages
    cargo.takeDammage(60);
    BOOST_TEST(cargo.getHealth() == 40);
    BOOST_TEST(!cargo.isDestroyed());

    // deal more dammages
    cargo.takeDammage(60);
    BOOST_TEST(cargo.getHealth() == -20);
    BOOST_TEST(cargo.isDestroyed());
}

BOOST_AUTO_TEST_CASE(testRepair) {
    // create a car with dammages, but not destroyed
    cars::NormalCar cargo(1, "cargo", 10, 100);
    BOOST_TEST(cargo.getHealth() == 10);
    BOOST_TEST(!cargo.isDestroyed());

    // repair it
    cargo.repair();
    BOOST_TEST(cargo.getHealth() == cars::Car::maxHealth);

    // destroy the car
    cargo.takeDammage(200);
    BOOST_TEST(cargo.getHealth() == -100);
    BOOST_TEST(cargo.isDestroyed());

    // try to repair it
    BOOST_CHECK_THROW(cargo.repair(), cars::DestroyedCarError);
}

BOOST_AUTO_TEST_SUITE_END() // normalCar

BOOST_AUTO_TEST_SUITE(loadCar)

BOOST_AUTO_TEST_CASE(testGetters) {
    // create a merch and a merch load
    merchandises::Merch lumber(1, "lumber", merchandises::merchTypes::box);
    merchandises::MerchLoad lumberLoad(lumber, 10, 100);

    // create car with usual constructor
    cars::LoadCar cargo1(1, "dummy", 50, 100, 50, lumber.getType(), lumberLoad);
    BOOST_TEST(cargo1.getWeight() == 110, tt::tolerance(0.01));
    BOOST_TEST(cargo1.getMaxQuantity() == 50);
    BOOST_TEST(cargo1.getMerchType() == lumber.getType());
    BOOST_TEST((cargo1.getMerchLoad().getMerch() == lumber));
    BOOST_TEST(cargo1.getRemainingQuantity() == 40);
    BOOST_TEST(!cargo1.isEmpty());
    BOOST_TEST(!cargo1.isFull());

    // create car with usual constructor for empty car
    cars::LoadCar cargo2(2, "cargo", 50, 200, 60, lumber.getType());
    BOOST_TEST(cargo2.getWeight() == 200, tt::tolerance(0.01));
    BOOST_TEST(cargo2.getMaxQuantity() == 60);
    BOOST_TEST(cargo2.getMerchType() == lumber.getType());
    BOOST_CHECK_THROW(cargo2.getMerchLoad(), cars::IsEmptyError);
    BOOST_TEST(cargo2.getRemainingQuantity() == 60);
    BOOST_TEST(cargo2.isEmpty());
    BOOST_TEST(!cargo2.isFull());

    // create car with usual constructor for car with full health points
    cars::LoadCar cargo3(3, "cargo", 150, 10, lumber.getType(), lumberLoad);
    BOOST_TEST(cargo3.getWeight() == 160, tt::tolerance(0.01));
    BOOST_TEST(cargo3.getMaxQuantity() == 10);
    BOOST_TEST(cargo3.getMerchType() == lumber.getType());
    BOOST_TEST((cargo3.getMerchLoad().getMerch() == lumber));
    BOOST_TEST(cargo3.getRemainingQuantity() == 0);
    BOOST_TEST(!cargo3.isEmpty());
    BOOST_TEST(cargo3.isFull());

    // create car with usual constructor for empty car with full health points
    cars::LoadCar cargo4(4, "cargo", 250, 100, lumber.getType());
    BOOST_TEST(cargo4.getWeight() == 250, tt::tolerance(0.01));
    BOOST_TEST(cargo4.getMaxQuantity() == 100);
    BOOST_TEST(cargo4.getMerchType() == lumber.getType());
    BOOST_CHECK_THROW(cargo4.getMerchLoad(), cars::IsEmptyError);
    BOOST_TEST(cargo4.getRemainingQuantity() == 100);
    BOOST_TEST(cargo4.isEmpty());
    BOOST_TEST(!cargo4.isFull());

    // create a destroyed car
    cars::LoadCar cargo5(5, "cargo", 0, 100, 50, lumber.getType(), lumberLoad);
    BOOST_TEST(cargo5.getWeight() == 100, tt::tolerance(0.01));
    BOOST_CHECK_THROW(cargo5.getMaxQuantity(), cars::DestroyedCarError);
    BOOST_CHECK_THROW(cargo5.getMerchType(), cars::DestroyedCarError);
    BOOST_CHECK_THROW(cargo5.getMerchLoad(), cars::DestroyedCarError);
    BOOST_CHECK_THROW(cargo5.getRemainingQuantity(), cars::DestroyedCarError);
    BOOST_CHECK_THROW(cargo5.isEmpty(), cars::DestroyedCarError);
    BOOST_CHECK_THROW(cargo5.isFull(), cars::DestroyedCarError);

    // create car with too much load
    merchandises::MerchLoad anotherLumberLoad(lumber, 100, 100);
    BOOST_CHECK_THROW(
    ([lumber, anotherLumberLoad]()->void {
        cars::LoadCar cargo6(3, "cargo", 150, 10, lumber.getType(), anotherLumberLoad);
    }()),
    cars::NotEnoughSpaceError
    );
}

BOOST_AUTO_TEST_CASE(testCanLoad) {
    // create merchs and merch loads
    merchandises::Merch lumber(100, "lumber", merchandises::merchTypes::box);
    merchandises::Merch fish(101, "fish", merchandises::merchTypes::box);
    merchandises::Merch oil(102, "oil", merchandises::merchTypes::toxic);
    merchandises::MerchLoad lumberInCity(lumber, 50, 100);
    merchandises::MerchLoad fishInCity(fish, 30, 10);
    merchandises::MerchLoad oilInCity(oil, 60, 50);
    merchandises::MerchLoad lumberInTrain(lumber, 10, 40);

    // create empty cargo car
    cars::LoadCar emptyCargo(1, "cargo", 100, 25, merchandises::merchTypes::box);
    BOOST_TEST(emptyCargo.isEmpty());
    BOOST_TEST(!emptyCargo.isFull());
    BOOST_TEST(emptyCargo.canLoad(lumberInCity));
    BOOST_TEST(emptyCargo.canLoad(fishInCity));
    BOOST_TEST(!emptyCargo.canLoad(oilInCity));

    // create a cargo with some lumber
    cars::LoadCar lumberCargo(2, "cargo", 100, 25, merchandises::merchTypes::box, lumberInTrain);
    BOOST_TEST(!lumberCargo.isEmpty());
    BOOST_TEST(!lumberCargo.isFull());
    BOOST_TEST(lumberCargo.canLoad(lumberInCity));
    BOOST_TEST(!lumberCargo.canLoad(fishInCity));
    BOOST_TEST(!lumberCargo.canLoad(oilInCity));

    // create a cargo with full lumber
    cars::LoadCar fullLumberCargo(3, "cargo", 100, 10, merchandises::merchTypes::box, lumberInTrain);
    BOOST_TEST(!fullLumberCargo.isEmpty());
    BOOST_TEST(fullLumberCargo.isFull());
    BOOST_TEST(!fullLumberCargo.canLoad(lumberInCity));
    BOOST_TEST(!fullLumberCargo.canLoad(fishInCity));
    BOOST_TEST(!fullLumberCargo.canLoad(oilInCity));

    // create a destroyed empty cargo
    cars::LoadCar destroyedCargo(4, "cargo", 0, 100, 25, merchandises::merchTypes::box);
    BOOST_TEST(destroyedCargo.isDestroyed());
    BOOST_TEST(!destroyedCargo.canLoad(lumberInCity));
    BOOST_TEST(!destroyedCargo.canLoad(fishInCity));
    BOOST_TEST(!destroyedCargo.canLoad(oilInCity));
}

BOOST_AUTO_TEST_CASE(testLoad) {
    // create merchs and merch loads
    merchandises::Merch lumber(100, "lumber", merchandises::merchTypes::box);
    merchandises::Merch oil(101, "oil", merchandises::merchTypes::toxic);
    merchandises::MerchLoad lumberInCity(lumber, 50, 100);
    merchandises::MerchLoad oilInCity(oil, 50, 100);

    // create empty cargo car
    cars::LoadCar cargo(1, "cargo", 100, 25, merchandises::merchTypes::box);
    BOOST_TEST(cargo.isEmpty());
    BOOST_TEST(cargo.getWeight() == 100, tt::tolerance(0.01));
    BOOST_TEST(cargo.getQuantity() == 0);
    BOOST_TEST(cargo.getRemainingQuantity() == 25);

    // load 10 oil in the car and get exception
    BOOST_CHECK_THROW(cargo.load(oilInCity, 10), cars::CannotLoadError);

    // load 10 lumber in the car
    cargo.load(lumberInCity, 10);
    BOOST_TEST(!cargo.isEmpty());
    BOOST_TEST(cargo.getQuantity() == 10);
    BOOST_TEST(cargo.getRemainingQuantity() == 15);
    BOOST_TEST(cargo.getMerchLoad().getQuantity() == 10);
    BOOST_TEST(cargo.getWeight() == 110, tt::tolerance(0.01));
    BOOST_TEST(lumberInCity.getQuantity() == 40);

    // load 10 more lumber in the car
    cargo.load(lumberInCity, 10);
    BOOST_TEST(cargo.getQuantity() == 20);
    BOOST_TEST(cargo.getRemainingQuantity() == 5);
    BOOST_TEST(cargo.getMerchLoad().getQuantity() == 20);
    BOOST_TEST(cargo.getWeight() == 120, tt::tolerance(0.01));
    BOOST_TEST(lumberInCity.getQuantity() == 30);

    // load 10 more and get exception
    BOOST_CHECK_THROW(cargo.load(lumberInCity, 10), cars::NotEnoughSpaceError);

    // load a negative amount, the negative value should represent a crazy high positive value
    BOOST_CHECK_THROW(cargo.load(lumberInCity, -10), cars::NotEnoughSpaceError);
}

BOOST_AUTO_TEST_CASE(testUnLoad) {
    // create merchs and merch loads
    merchandises::Merch lumber(100, "lumber", merchandises::merchTypes::box);
    merchandises::MerchLoad lumberInCity(lumber, 50, 100);
    merchandises::MerchLoad lumberInTrain(lumber, 25, 40);

    // create full cargo car
    cars::LoadCar cargo(1, "cargo", 100, 25, merchandises::merchTypes::box, lumberInTrain);
    BOOST_TEST(cargo.isFull());
    BOOST_TEST(!cargo.canLoad(lumberInCity));
    BOOST_TEST(cargo.getRemainingQuantity() == 0);
    BOOST_TEST(cargo.getWeight() == 125, tt::tolerance(0.01));

    // unload 10 lumber from the car
    merchandises::MerchLoad lumberUnLoaded1 = cargo.unLoad(10);
    BOOST_TEST(!cargo.isFull());
    BOOST_TEST(cargo.canLoad(lumberInCity));
    BOOST_TEST(cargo.getRemainingQuantity() == 10);
    BOOST_TEST(cargo.getWeight() == 115, tt::tolerance(0.01));
    BOOST_TEST(lumberUnLoaded1.getQuantity() == 10);

    // unload 10 more lumber from the car
    merchandises::MerchLoad lumberUnLoaded2 = cargo.unLoad(10);
    BOOST_TEST(!cargo.isFull());
    BOOST_TEST(cargo.canLoad(lumberInCity));
    BOOST_TEST(cargo.getRemainingQuantity() == 20);
    BOOST_TEST(cargo.getWeight() == 105, tt::tolerance(0.01));
    BOOST_TEST(lumberUnLoaded2.getQuantity() == 10);

    // unload 10 more and get exception
    BOOST_CHECK_THROW(cargo.unLoad(10), cars::NotEnoughLoadError);

    // unload a negative amount, the negative value should represent a crazy high positive value
    BOOST_CHECK_THROW(cargo.unLoad(-10), cars::NotEnoughLoadError);
}

BOOST_AUTO_TEST_SUITE_END() // loadCar

BOOST_AUTO_TEST_SUITE(loadCarModel)

BOOST_AUTO_TEST_CASE(testCallOperator) {
    // create merchs and merch loads
    merchandises::Merch lumber(100, "lumber", merchandises::merchTypes::box);
    merchandises::MerchLoad lumberInCity(lumber, 10, 100);

    // create a car model
    const cars::LoadCarModel Cargo(1, "cargo", 45, 20, merchandises::merchTypes::box);

    // create an empty cargo with full health from car model
    cars::LoadCar cargo1 = Cargo();
    BOOST_TEST(cargo1.getName() == "cargo");
    BOOST_TEST(cargo1.isEmpty());
    BOOST_TEST(cargo1.getHealth() == cars::Car::maxHealth);

    // create an empty cargo from car model
    cars::LoadCar cargo2 = Cargo(50);
    BOOST_TEST(cargo2.getName() == "cargo");
    BOOST_TEST(cargo2.isEmpty());
    BOOST_TEST(cargo2.getHealth() == 50);

    // create a cargo with full health from car model
    cars::LoadCar cargo3 = Cargo(lumberInCity);
    BOOST_TEST(cargo3.getName() == "cargo");
    BOOST_TEST(!cargo3.isEmpty());
    BOOST_TEST(cargo3.getHealth() == cars::Car::maxHealth);

    // create a cargo from car model
    cars::LoadCar cargo4 = Cargo(50, lumberInCity);
    BOOST_TEST(cargo4.getName() == "cargo");
    BOOST_TEST(!cargo4.isEmpty());
    BOOST_TEST(cargo4.getHealth() == 50);
}

BOOST_AUTO_TEST_SUITE_END() // loadCarModel

BOOST_AUTO_TEST_SUITE_END() // cars
