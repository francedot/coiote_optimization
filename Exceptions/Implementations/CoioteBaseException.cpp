//
// Created by francesco on 24/11/16.
//

#include "../Headers/CoioteBaseException.hpp"

//class CoioteBaseException : public std::exception {
//public:
//const char* CoioteBaseException::what() const throw() {
//const char* CoioteBaseException::what() { //TODO: Had to comment it out since it gave me an error for the return type
//    return getMessage();
//}

std::string CoioteBaseException::getMessage() {
    return this->message;
}

std::string CoioteBaseException::setMessage(std::string message) {
    this->message = message;
}

//protected:
CoioteBaseException::CoioteBaseException() {
    this->message = "";
}

CoioteBaseException::CoioteBaseException(std::string message) {
    this->message = message;
}
//    std::string message;
//};
