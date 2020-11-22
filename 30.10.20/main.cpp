#include <iostream>
#include <exception>
#include <vector>

class NegativeSizeException: std::exception{};
class StackOverflowException: std::exception{};
class StackEmptyException: std::exception{};

template<class T, int size>
class stack{
    std::vector<T> storage;
public:

    stack()
    {
        static_assert(std::is_arithmetic<T>(), "Not an arithmetic type passed");
        if(size < 0)
            throw (NegativeSizeException());
        storage.reserve(size);
    }

    void push(T new_elem)
    {
        if(storage.size() >= size)
            throw(StackOverflowException());
        storage.push_back(new_elem);
    }

    T pop()
    {
        if(storage.empty())
            throw(StackEmptyException());
        T result = storage.back();
        storage.pop_back();
        return result;
    }
};

int main() {
    stack<char, 1> first;

    first.push(49); //ASCII code for '1'
    try{
        first.push(49); //ASCII code for '1'
    }
    catch (StackOverflowException) {
        std::cout << "StackOverflow caught!\n";
    }

    std::cout << "popped symbol is " << first.pop() << std::endl;
    try{
        std::cout << first.pop() << std::endl;
    }
    catch (StackEmptyException){
        std::cout << "StackEmpty caught!\n";
    }

    try{
        stack<char, -1> second;
    }
    catch(NegativeSizeException){
        std::cout << "NegativeSize caught!\n";
    }

    return 0;
}
