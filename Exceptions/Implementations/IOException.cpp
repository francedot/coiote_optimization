//
// Created by francesco on 24/11/16.
//

#include "../Headers/IOException.hpp"

class IOException : CoioteException {
public:
    IOException() {
        CoioteException::CoioteException();
    }
    IOException(std::string message) {
        CoioteException::CoioteException(message);
    }
};