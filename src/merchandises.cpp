#include "merchandises.hpp"

merchandises::Merch::Merch() :
    id(0), name(""), type(merchTypes::none) {}

merchandises::Merch::Merch(std::size_t id, std::string name, merchTypes type) :
    id(id), name(name), type(type) {}

bool merchandises::Merch::operator ==(const Merch& other) {
    return (id == other.id);
}

bool merchandises::Merch::operator !=(const Merch& other) {
    return !(*this == other);
}

std::size_t merchandises::Merch::getId() const {
    return id;
}

std::string merchandises::Merch::getName() const {
    return name;
}

merchandises::merchTypes merchandises::Merch::getType() const {
    return type;
}

merchandises::MerchLoad::MerchLoad() :
    merch(Merch()), quantity(0), price(0) {}

merchandises::MerchLoad::MerchLoad(const Merch& merch, const std::size_t quantity,
                                   const std::size_t price) :
    merch(merch), quantity(quantity), price(price) {}

merchandises::Merch merchandises::MerchLoad::getMerch() const {
    return merch;
}

std::size_t merchandises::MerchLoad::getQuantity() const {
    return quantity;
}

std::size_t merchandises::MerchLoad::getPrice() const {
    return price;
}

bool merchandises::MerchLoad::hasSameMerch(const MerchLoad& other) {
    return (hasSameMerch(other.merch));
}

bool merchandises::MerchLoad::hasSameMerch(const Merch& otherMerch) {
    return (merch == otherMerch);
}


void merchandises::MerchLoad::add(const std::size_t otherQuantity, const std::size_t otherPrice) {
    // average the price of the two loads
    price = (quantity * price + otherQuantity * otherPrice) / (quantity + otherQuantity);
    quantity += otherQuantity;
}

void merchandises::MerchLoad::add(const MerchLoad& other) {
    // check the merchs are the same
    if (!hasSameMerch(other)) throw NotSameMerchError();

    add(other.quantity, other.price);
}

void merchandises::MerchLoad::substract(const std::size_t otherQuantity) {
    quantity -= otherQuantity;
}

void merchandises::MerchLoad::substract(const MerchLoad& other) {
    // check the merchs are the same
    if (!hasSameMerch(other)) throw NotSameMerchError();

    substract(other.quantity);
}

const char* merchandises::NotSameMerchError::what() const throw() {
    return "Merchs are different";
}
