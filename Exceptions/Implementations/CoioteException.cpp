//
// Created by francesco on 24/11/16.
//

#include "../Headers/CoioteException.hpp"

CoioteException::CoioteException() {}

CoioteException::CoioteException(std::string message) : CoioteBaseException(message) {
    // Delegates base class
}
