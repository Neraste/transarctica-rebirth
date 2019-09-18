#include "merchandises.hpp"

merchandises::Merch::Merch() :
    id(0), name("null"), type(merchandises::nullMerchType) {}

merchandises::Merch::Merch(const types::id id, const std::string name, const merchTypes& type) :
    id(id), name(name), type(type) {}

bool merchandises::Merch::operator ==(const Merch& other) const {
    return (id == other.id);
}

bool merchandises::Merch::operator !=(const Merch& other) const {
    return (id != other.id);
}

types::id merchandises::Merch::getId() const {
    return id;
}

std::string merchandises::Merch::getName() const {
    return name;
}

const merchandises::merchTypes& merchandises::Merch::getType() const {
    return type;
}

merchandises::MerchLoad::MerchLoad() :
    merch(merchandises::nullMerch), quantity(0), price(0) {}

merchandises::MerchLoad::MerchLoad(const Merch& merch, const types::quantity quantity,
                                   const types::price price) :
    merch(merch), quantity(quantity), price(price) {}

const merchandises::Merch& merchandises::MerchLoad::getMerch() const {
    return merch;
}

types::quantity merchandises::MerchLoad::getQuantity() const {
    return quantity;
}

types::price merchandises::MerchLoad::getPrice() const {
    return price;
}

bool merchandises::MerchLoad::hasSameMerch(const MerchLoad& other) {
    return (hasSameMerch(other.merch));
}

bool merchandises::MerchLoad::hasSameMerch(const Merch& otherMerch) {
    return (merch == otherMerch);
}

void merchandises::MerchLoad::add(const types::quantity otherQuantity,
                                  const types::price otherPrice) {
    // average the price of the two loads
    price = (quantity * price + otherQuantity * otherPrice) / (quantity + otherQuantity);
    quantity += otherQuantity;
}

void merchandises::MerchLoad::add(const MerchLoad& other) {
    // check the merchs are the same
    if (!hasSameMerch(other)) throw NotSameMerchError();

    add(other.quantity, other.price);
}

void merchandises::MerchLoad::substract(const types::quantity otherQuantity) {
    split(otherQuantity);
}

void merchandises::MerchLoad::substract(const MerchLoad& other) {
    split(other);
}

merchandises::MerchLoad merchandises::MerchLoad::split(const types::quantity otherQuantity) {
    if (otherQuantity > quantity) throw NotEnoughLoadError();

    quantity -= otherQuantity;
    MerchLoad splittedLoad(merch, otherQuantity, price);

    return splittedLoad;
}

merchandises::MerchLoad merchandises::MerchLoad::split(const MerchLoad& other) {
    // check the merchs are the same
    if (!hasSameMerch(other)) throw NotSameMerchError();

    return split(other.quantity);
}

const char* merchandises::NotSameMerchError::what() const throw() {
    return "Merchs are different";
}

const char* merchandises::NotEnoughLoadError::what() const throw() {
    return "Not enough merch load to subsract";
}
