#include <iostream>
#include <vector>

template<int last=10>
class Fibonacci
{
public:
    std::vector<int> numbers;

    Fibonacci()
    {
        Fibonacci<last>::numbers.resize(std::max(last+1, 2));
        numbers[0] = 1;
        numbers[1] = 2;
        for(int i = 2; i < numbers.size(); i++)
        {
            numbers[i] = numbers[i - 2] + numbers[i - 1];
        }
    }

    class bidirectional_iterator
    {
    public:
        bidirectional_iterator(std::vector<int>::iterator pos): v_iter(pos){}
        bidirectional_iterator &operator ++(){v_iter++; return *this;}
        bidirectional_iterator &operator --(){v_iter--; return *this;}
        bidirectional_iterator operator +(int step){v_iter+=step;}
        bidirectional_iterator operator -(int step){v_iter-=step;}
        bool operator ==(const bidirectional_iterator& second){return v_iter == second.v_iter;}
        bool operator !=(const bidirectional_iterator& second){return v_iter != second.v_iter;}
        int &operator *() {return *v_iter;}
    private:
        std::vector<int>::iterator v_iter;
    };

    bidirectional_iterator begin()
    {
        return bidirectional_iterator(numbers.begin());
    }

    bidirectional_iterator end()
    {
        return bidirectional_iterator(numbers.end());
    }
};
int main() {
    const int row_length = 20;
    Fibonacci<row_length> row;

    std::cout << "Hello, Fibonacci!" << std::endl;
    for(Fibonacci<row_length>::bidirectional_iterator i = row.begin(); i != row.end(); ++i)
        std::cout << (*i) << ' ';
    return 0;
}
