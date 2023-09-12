/*
** EPITECH PROJECT, 2022
** fatalException
** File description:
** The class for the Custom exception of the ZIA project
*/

#ifndef FATALEXCEPTION_HPP_
#define FATALEXCEPTION_HPP_

#include <string>

namespace Zia
{
    class fatalException : public std::exception
    {
        private:
            std::string msg; // The message of the error
            std::string function; // The function where the error occured
        public:
            fatalException(const std::string &msg, const std::string &func); // The constructor of the error. It takes has parameters a message, and the name of the function.
            /* Here is how you should throw this error :  
            * throw(Zia::fatalException(YOUR_MESSAGE, YOUR FUNCTION));
            */
            const char *what() const throw(); // Returns the error message
            const char *getErrorFunction() const throw(); // Returns the name of the function given in the constructor
            ~fatalException() throw();
    };
    
}

#endif /* !fatalException_HPP_ */
