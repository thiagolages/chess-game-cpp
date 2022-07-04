# Annotations

## [Const in C++](https://stackoverflow.com/questions/2328671/constant-variables-not-working-in-header)

- In order to use a const definition inside a header file, we have to separate the _declaration_ and _definition_ of consts. 
- The _declaration_ should be done inside a header file (.h) as an 
> //myClass.h
> 
> extern const int myConst; 

- The _definition_ should be done inside an implementation file (.cpp) as 
> //myClass.cpp
>
> const int myConst = myValue;

- That is the case of **maxNumPawns**, for example, inside Game.(h/cpp)

## [Vector of objects inside a header file](https://stackoverflow.com/questions/29298026/stdvector-size-in-header)

- 
