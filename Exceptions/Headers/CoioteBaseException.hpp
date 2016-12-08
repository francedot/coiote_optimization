//
// Created by francesco on 24/11/16.
//

#ifndef coiote_project_ioexception_hpp
#define coiote_project_ioexception_hpp

#include <exception>
#include <string>

/*
 * Base Coiote Program Exception.
 * All exceptions will inherit from here
 */
class CoioteBaseException : public std::exception {
public:
//    const char* what();
    std::string getMessage();
    std::string setMessage(std::string message);
protected:
    /*
     * Hidden Constructor for Base abstract class
     */
    CoioteBaseException();
    CoioteBaseException(std::string message);

    std::string message;
};

#endif //COIOTE_PROJECT_IOEXCEPTION_H
