//
// Created by francesco on 24/11/16.
//

#ifndef coiote_project_coioteexception_h
#define coiote_project_coioteexception_h

#include "CoioteBaseException.hpp"

/*
 * Root Coiote Concrete Exception
 */
class CoioteException : public CoioteBaseException {
public:
    CoioteException();
    CoioteException(std::string message);
};

#endif //coiote_project_coioteexception_h
