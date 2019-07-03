#ifndef RUNTIMEEXCEPTION_H
#define RUNTIMEEXCEPTION_H
// Modified for CSCI 220 Fall 13

#include <exception>

using namespace std;

class RuntimeException : public exception 
{
public:
    RuntimeException(const char *err) { cout << "RunTimeException";}
};

class NonexistentElement : public RuntimeException
{
public:
	NonexistentElement(const char *err) : RuntimeException(err) {}
};

class BoundaryViolation : public RuntimeException 
{
public:
	BoundaryViolation(const char *err) : RuntimeException(err) {}
};
#endif
