#ifndef MERCHANDISES_HPP
#define MERCHANDISES_HPP

#include <exception>
#include <string>

namespace merchandises {

enum merchTypes {
    none,
    box,
    liquidDrinkable,
    liquidToxic,
    vegetal,
};

class Merch {
    /**
     * ID of the merchandise.
     */
    std::size_t id;

    /**
     * Human-readable name of the merchandise.
     */
    std::string name;

    /**
     * Type of the merchandise.
     * Used to find cars that can store this merch.
     */
    merchTypes type;

  public:

    /**
     * Default constructor.
     */
    Merch();

    /**
     * Usual constructor.
     */
    Merch(const std::size_t id, const std::string name, const merchTypes type);

    /**
     * Equality operanot.
     */
    bool operator ==(const Merch& other);

    /**
     * Iniquality operator.
     */
    bool operator !=(const Merch& other);

    /**
     * Getter for ID.
     */
    std::size_t getId() const;

    /**
     * Getter for name.
     */
    std::string getName() const;

    /**
     * Getter for type.
     */
    merchTypes getType() const;
};

class MerchLoad {
    /**
     * Merchandise.
     */
    Merch merch;

    /**
     * Quantity of merchandise.
     */
    std::size_t quantity;

    /**
     * Price.
     */
    std::size_t price;

  public:

    /**
     * Default constructor.
     */
    MerchLoad();

    /**
     * Usual constructor.
     */
    MerchLoad(const Merch& merch, const std::size_t quantity, const std::size_t price);

    /**
     * Getter for merch.
     */
    Merch getMerch() const;

    /**
     * Getter for quantity.
     */
    std::size_t getQuantity() const;

    /**
     * Getter for price.
     */
    std::size_t getPrice() const;

    /**
     * Add merchandise loads.
     */
    void add(const std::size_t otherQuantity, const std::size_t otherPrice);

    /**
     * Add merchandise loads.
     */
    void add(const MerchLoad& other);

    /**
     * Substract mechandise loads.
     */
    void substract(const std::size_t otherQuantity);

    /**
     * Substract mechandise loads.
     */
    void substract(const MerchLoad& other);

    /**
     * Check two merchandise loads have the same merchandise.
     */
    bool hasSameMerch(const MerchLoad& other);

    /**
     * Check the merch is the same as the one of the load.
     */
    bool hasSameMerch(const Merch& otherMerch);

};

class NotSameMerchError : public std::exception {
    /**
     * First merch.
     */
    Merch merch1;

    /**
     * Second merch.
     */
    Merch merch2;

  public:

    /**
     * Usual constructor.
     */
    NotSameMerchError(const Merch& merch1, const Merch& merch2);

    /**
     * Get exception message.
     */
    const char* what() const throw();
};

}

#endif // ifndef MERCHANDISES_HPP
