#ifndef CARS_DATA_HPP
#define CARS_DATA_HPP

#include "gameplay/train/cars.hpp"

namespace cars {

// *INDENT-OFF*
const LoadCarModel Merchandise   ( 101 , "merchandise"    , 45 , 20 , merchandises::MerchTypes::box       ) ;
const LoadCarModel MerchandiseXL ( 102 , "merchandise XL" , 55 , 40 , merchandises::MerchTypes::box       ) ;
const LoadCarModel BioGreenhouse ( 103 , "bio greenhouse" , 40 , 10 , merchandises::MerchTypes::vegetal   ) ;
const LoadCarModel Tank          ( 104 , "tank"           , 40 , 20 , merchandises::MerchTypes::drinkable ) ;
const LoadCarModel OilTank       ( 105 , "oil tank"       , 45 , 20 , merchandises::MerchTypes::toxic     ) ;
// *INDENT-ON*

}

#endif // ifndef CARS_DATA_HPP
