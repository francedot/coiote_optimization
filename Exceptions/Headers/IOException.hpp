//
// Created by francesco on 24/11/16.
//

#ifndef coiote_project_ioexception_h
#define coiote_project_ioexception_h

#include "CoioteException.hpp"

class IOException : CoioteException {
public:
    IOException();
    IOException(std::string message);
};

#endif //coiote_project_ioexception_h
