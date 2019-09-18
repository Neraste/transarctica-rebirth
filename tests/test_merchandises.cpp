#include <boost/test/unit_test.hpp>

#include "merchandises.hpp"

BOOST_AUTO_TEST_SUITE(merchandises)

BOOST_AUTO_TEST_SUITE(merch)

BOOST_AUTO_TEST_CASE(testGetters) {
    // create merch with usual constructor
    merchandises::Merch lumber(1, "lumber", merchandises::merchTypes::box);
    BOOST_TEST(lumber.getId() == 1);
    BOOST_TEST(lumber.getName() == "lumber");
    BOOST_TEST(lumber.getType() == merchandises::merchTypes::box);

    // create merch with default constructor
    merchandises::Merch nullMerch;
    BOOST_TEST(nullMerch.getId() == 0);
    BOOST_TEST(nullMerch.getName() == "null");
    BOOST_TEST(nullMerch.getType() == merchandises::merchTypes::null);
}

BOOST_AUTO_TEST_CASE(testEquality) {
    // create merchs with usual constructor
    merchandises::Merch lumber(1, "lumber", merchandises::merchTypes::box);
    merchandises::Merch lumber2(1, "lumber2", merchandises::merchTypes::box);
    merchandises::Merch fish(2, "fish", merchandises::merchTypes::box);
    BOOST_TEST((lumber == lumber2));
    BOOST_TEST((lumber != fish));

    // create merch with default constructor
    merchandises::Merch nullMerch;
    BOOST_TEST((lumber != nullMerch));
}

BOOST_AUTO_TEST_SUITE_END() // merch

BOOST_AUTO_TEST_SUITE(merchLoad)

BOOST_AUTO_TEST_CASE(testGetters) {
    // create merch
    merchandises::Merch lumber(1, "lumber", merchandises::merchTypes::box);

    // create merch load with usual constructor
    merchandises::MerchLoad lumberLoad1(lumber, 10, 100);
    BOOST_TEST((lumberLoad1.getMerch() == lumber));
    BOOST_TEST(lumberLoad1.getQuantity() == 10);
    BOOST_TEST(lumberLoad1.getPrice() == 100);

    // create merch load with default constructor
    merchandises::MerchLoad lumberLoad2;
    BOOST_TEST((lumberLoad2.getMerch() == Merch()));
    BOOST_TEST(lumberLoad2.getQuantity() == 0);
    BOOST_TEST(lumberLoad2.getPrice() == 0);

    // create merch load with copy constructor
    merchandises::MerchLoad lumberLoad3(lumberLoad1);
    BOOST_TEST((lumberLoad3.getMerch() == lumber));
    BOOST_TEST(lumberLoad3.getQuantity() == 10);
    BOOST_TEST(lumberLoad3.getPrice() == 100);
}

BOOST_AUTO_TEST_CASE(testSameMerch) {
    // create two merchs
    merchandises::Merch lumber(1, "lumber", merchandises::merchTypes::box);
    merchandises::Merch fish(2, "fish", merchandises::merchTypes::box);

    // create merch loads
    merchandises::MerchLoad lumberLoad1(lumber, 10, 100);
    merchandises::MerchLoad lumberLoad2(lumber, 10, 120);
    merchandises::MerchLoad fishLoad(fish, 10, 50);

    // lumber loads have the same merch
    BOOST_TEST(lumberLoad1.hasSameMerch(lumberLoad2));

    // lumber loads and fish loads have different merchs
    BOOST_TEST(!lumberLoad1.hasSameMerch(fishLoad));
}

BOOST_AUTO_TEST_CASE(testAdditions) {
    // create merch
    merchandises::Merch lumber(1, "lumber", merchandises::merchTypes::box);

    // create two merch loads to add
    merchandises::MerchLoad lumberLoad1(lumber, 10, 100);
    merchandises::MerchLoad lumberLoad2(lumber, 10, 50);

    // add them
    lumberLoad1.add(lumberLoad2);
    BOOST_TEST(lumberLoad1.getQuantity() == 20);
    BOOST_TEST(lumberLoad1.getPrice() == 75);

    // add quantity at a certain price
    lumberLoad1.add(20, 75);
    BOOST_TEST(lumberLoad1.getQuantity() == 40);
    BOOST_TEST(lumberLoad1.getPrice() == 75);

    // substract them
    lumberLoad1.substract(lumberLoad2);
    BOOST_TEST(lumberLoad1.getQuantity() == 30);
    BOOST_TEST(lumberLoad1.getPrice() == 75);

    // substract a quantity
    lumberLoad1.substract(10);
    BOOST_TEST(lumberLoad1.getQuantity() == 20);

    // split a load
    merchandises::MerchLoad lumberLoad3 = lumberLoad1.split(lumberLoad2);
    BOOST_TEST(lumberLoad1.getQuantity() == 10);
    BOOST_TEST(lumberLoad3.getQuantity() == 10);

    // split a quantity
    merchandises::MerchLoad lumberLoad4 = lumberLoad1.split(10);
    BOOST_TEST(lumberLoad1.getQuantity() == 0);
    BOOST_TEST(lumberLoad4.getQuantity() == 10);

    // substract/split too much
    BOOST_CHECK_THROW(lumberLoad1.substract(10), merchandises::NotEnoughLoadError);
    BOOST_CHECK_THROW(lumberLoad1.split(10), merchandises::NotEnoughLoadError);
}

BOOST_AUTO_TEST_CASE(testAdditionsError) {
    // create two merchs
    merchandises::Merch lumber(1, "lumber", merchandises::merchTypes::box);
    merchandises::Merch fish(2, "fish", merchandises::merchTypes::box);

    // create two merch loads
    merchandises::MerchLoad lumberLoad(lumber, 10, 100);
    merchandises::MerchLoad fishLoad(fish, 10, 50);

    // they cannot be added or substracted
    BOOST_CHECK_THROW(lumberLoad.add(fishLoad), merchandises::NotSameMerchError);
    BOOST_CHECK_THROW(lumberLoad.substract(fishLoad), merchandises::NotSameMerchError);
}

BOOST_AUTO_TEST_SUITE_END() // merchLoad

BOOST_AUTO_TEST_SUITE_END() // merchandises
