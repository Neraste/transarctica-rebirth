#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>

namespace exceptions {

/**
 * Generic error class for the project.
 */
struct TransarcticaRebirthError : public std::exception {};

}

#endif // ifndef EXCEPTIONS_HPP
