//
// Created by francesco on 24/11/16.
//

#include "../Headers/CoioteBaseException.hpp"

class CoioteBaseException : public std::exception {
public:
    const char* what() const throw() {
        return getMessage();
    }
    std::string getMessage() {
        return this->message;
    }
    std::string setMessage(std::string message){
        this->message = message;
    }

protected:
    CoioteBaseException() {
        this->message = "";
    }
    CoioteBaseException(std::string message) {
        this->message = message;
    }
    std::string message;
};

#endif //COIOTE_PROJECT_IOEXCEPTION_H
