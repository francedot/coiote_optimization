//
// Created by francesco on 24/11/16.
//

#include "../Headers/CoioteException.hpp"

class CoioteException : public CoioteBaseException {
public:
    CoioteException() {
        // Delegates base class
        CoioteBaseException::CoioteBaseException();
    }
    CoioteException(std::string message) {
        // Delegates base class
        CoioteBaseException::CoioteBaseException(message);
    }
};
