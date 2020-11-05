#ifndef MERCHANDISES_HPP
#define MERCHANDISES_HPP

#include <memory>
#include <string>

#include "exceptions.hpp"
#include "types.hpp"

namespace merchandises {

/**
 * Types of merchs.
 */
enum class MerchTypes {
    /**
     * Null type.
     */
    null,

    /**
     * Can be stored in a box.
     */
    box,

    /**
     * Drinkable liquid.
     */
    drinkable,

    /**
     * Toxic liquid.
     */
    toxic,

    /**
     * Living vegetal.
     */
    vegetal,
};

/**
 * Shorthand for null merch type.
 */
const auto nullMerchType = MerchTypes::null;

/**
 * Merch object.
 */
class Merch {
    /**
     * ID of the merchandise.
     */
    types::id id;

    /**
     * Human-readable name of the merchandise.
     */
    std::string name;

    /**
     * Type of the merchandise.
     * Used to find cars that can store this merch.
     */
    const MerchTypes type;

  public:

    /**
     * Default constructor.
     */
    Merch();

    /**
     * Usual constructor.
     * @param id ID of the merch.
     * @param name Human-readable name of the merch.
     * @param type Type of the merch.
     */
    Merch(const types::id id, const std::string name, const MerchTypes type);

    // Merch& operator=(const Merch&);

    /**
     * Equality operator.
     * Equality based on ID only.
     * @param other Other merch to compare to.
     * @return True if the argument is equal to the current object.
     */
    bool operator ==(const Merch& other) const;

    /**
     * Iniquality operator.
     * Equality based on ID only.
     * @param other Other merch to compare to.
     * @return False if the argument is equal to the current object.
     */
    bool operator !=(const Merch& other) const;

    /**
     * Getter for ID.
     * @return ID of the merch.
     */
    types::id getId() const;

    /**
     * Getter for name.
     * @return Human-readable name of the merch.
     */
    std::string getName() const;

    /**
     * Getter for type.
     * @return Type of the merch.
     */
    MerchTypes getType() const;
};

/**
 * Shorthand for null merch.
 */
const Merch nullMerch;

/**
 * Load of merch object.
 */
class MerchLoad {
    /**
     * Merchandise.
     */
    const merchandises::Merch& merch;

    /**
     * Quantity of merchandise.
     */
    types::quantity quantity;

    /**
     * Price.
     */
    types::price price;

  public:

    /**
     * Default constructor.
     */
    MerchLoad();

    /**
     * Usual constructor.
     * @param merch Merch of the load.
     * @param quantity Quantity of merch in the load.
     * @param price Average price of the load.
     */
    MerchLoad(const Merch& merch,
              const types::quantity quantity,
              const types::price price);

    /**
     * Getter for merch.
     * @return Merch of the load.
     */
    const Merch& getMerch() const;

    /**
     * Getter for quantity.
     * @return Quantity of merch in the load.
     */
    types::quantity getQuantity() const;

    /**
     * Getter for price.
     * @return Average price of the load.
     */
    types::price getPrice() const;

    /**
     * Add merchandise loads.
     * @param otherQuantity Quantity to add to the load.
     * @param otherPrice Average price of the quantity to add. The final price
     * will be the weighted average of the prices.
     */
    void add(const types::quantity otherQuantity, const types::price otherPrice);

    /**
     * Add merchandise loads.
     * @param other Load to add.
     */
    void add(const MerchLoad& other);

    /**
     * Substract mechandise loads.
     * @param otherQuantity Quantity to substract to the load.
     */
    void substract(const types::quantity otherQuantity);

    /**
     * Substract mechandise loads.
     * @param other Load to substract.
     */
    void substract(const MerchLoad& other);

    /**
     * Split merchandise loads in another load.
     * @param otherQuantity Quantity to split to the load.
     */
    MerchLoad split(const types::quantity otherQuantity);

    /**
     * Split merchandise loads in another load.
     * @param other Load to split.
     */
    MerchLoad split(const MerchLoad& other);

    /**
     * Check two merchandise loads have the same merchandise.
     * @param other Load to compare the merch with.
     * @return True if the two loads have the same merch.
     */
    bool hasSameMerch(const MerchLoad& other);

    /**
     * Check two merchandise loads have the same merchandise.
     * @param other Load to compare the merch with.
     * @return True if the two loads have the same merch.
     */
    bool hasSameMerch(const std::shared_ptr<MerchLoad>& other);

    /**
     * Check the merch is the same as the one of the load.
     * @param otherMerch Merth to compare with the merch of the current object.
     * @return True in the merch and the one of the current object are the
     * same.
     */
    bool hasSameMerch(const Merch& otherMerch);

};

/**
 * Error class used when trying to manipulate two loads of different merch.
 */
struct NotSameMerchError : public exceptions::TransarcticaRebirthError {
    /**
     * Get exception message.
     * @return Error message.
     */
    const char* what() const throw() {
        return "Merchs are different";
    }
};

/**
 * Error class when trying to substract more merch load than possible.
 */
struct NotEnoughLoadError : public exceptions::TransarcticaRebirthError {
    /**
     * Get exception message.
     * @return Error message.
     */
    const char* what() const throw() {
        return "Not enough merch load to subsract";
    }
};

}

#include "merchandises_data.hpp"

#endif // ifndef MERCHANDISES_HPP
