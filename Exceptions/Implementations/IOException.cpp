//
// Created by francesco on 24/11/16.
//

#include "../Headers/IOException.hpp"

IOException::IOException() {}

IOException::IOException(std::string message) : CoioteException(message) {}