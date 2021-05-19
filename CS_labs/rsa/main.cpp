#include <iostream>
#include <vector>
#include <cmath>

typedef unsigned long long desired_type;
class RSA
{
public:
    desired_type p, q, n;
    desired_type e, phi, d = 0;

    static RSA create_receiver(desired_type maxlen = 1e4)
    {
        desired_type p, q;
        // TODO: initialize p and q here
        do{
            p = rand()%maxlen + 2;
        }
        while(! is_prime(p));

        do{
            q = rand()%maxlen + 2;
        }
        while(! is_prime(q));

        return create_receiver(p, q);
    };

    static RSA create_receiver(desired_type p, desired_type q, desired_type e=0)
    {
        RSA result = RSA();
        result.p = p; result.q = q;
        result.n = p*q;
        result.phi = (p-1)*(q-1);
        if(e == 0)
            for(int i = 0; i < 100; i++)
            {
                result.e = rand()%result.phi;
                if(are_mutually_simple(result.e, result.phi))
                    break;
            }
        else
            result.e = e;
        desired_type second;
        euclid(result.e, result.phi, result.d, second);
        result.d = (result.d + result.phi)%result.phi;
        return result;
    }

    static RSA create_sender(desired_type n, desired_type e)
    {
        RSA result;
        result.n = n; result.e = e;
        return result;
    }

    static void euclid(desired_type a, desired_type b, desired_type &x, desired_type &y)
    {
        if(b == 0)
        { x = 1; y = 0; return;}

        desired_type x2, y2;
        euclid(b, a%b, x2, y2);
        x = y2; y = x2 - a/b*y2;
        return;
    }

    static bool is_prime(desired_type p)
    {
        for(int i = 2; i < 30; i++)
            if(p%i == 0)
                return false;
        for(int i = 0; i < 30; i++)
        {
            if(pow(rand()%p + 1, p-1, p) != 1)
                return false;
        }
        return true;
    }

    static bool are_mutually_simple(desired_type first, desired_type second)
    {
        if(second == 0)
            return (first == 1);
        return are_mutually_simple(second, first%second);
    }

    int module_bytes()
    {
        int i = 1;
        while((n >> i) > 0)
            i++;
        i--;
        return i/8;
    }

    static desired_type pow(desired_type word, desired_type power, desired_type modulo)
    {
        if(power == 0)
            return 1;
        if(power == 1)
            return word;
        return (pow((word * word)%modulo, power/2, modulo) * pow(word, power%2, modulo))%modulo;
    }

    std::vector<unsigned char> encode_message(std::string message)
    {
        int bytes = module_bytes();
        std::vector<unsigned char> cipher(0);
        while(message.size()%bytes > 0)
            message.push_back((unsigned char)0);
        for(int i = 0; i < message.size()/bytes; i++)
        {
            desired_type number = 0;
            for(int j = 0; j < bytes; j++)
            {
                number = number << 8;
                number += message[i*bytes + j];
            }
            number = pow(number, e, n);
            // for(int j = 0; j < bytes + 1; j++)
            for(int j = bytes; j >= 0; j--)
            {
                cipher.push_back((unsigned char)(number >> (j*8)));
                // cipher.push_back((unsigned char)(number % (1 << 8)));
                number = number % (1 << (j*8));
            }
        }
        return cipher;
    }

    std::string decode_message(std::vector<unsigned char> message)
    {
        if(d == 0)
            throw std::out_of_range("invalid decipher exponent");
        int bytes = module_bytes();
        std::string answer;
        for(int i = 0; i < message.size()/(bytes + 1); i++)
        {
            desired_type number = 0;
            for(int j = 0; j < bytes+1; j++)
            {
                number  = number << 8;
                number += message[i*(bytes + 1) + j];
            }
            number = pow(number, d, n);
            // for(int j = 0; j < bytes; j++)
            for(int j = bytes-1; j >= 0; j--)
            {
                answer.push_back((unsigned char)(number >> (j * 8)));
                // answer.push_back((unsigned char)(number%(1 << 8)));
                number = number%(1 << (j*8));
            }
        }
        return answer;
    }

};

void example_of_work(std::string text="Hello there!")
{
    srand(time(0));
    // RSA A = RSA::create_receiver(887, 997, 7);
    RSA A = RSA::create_receiver();
    // RSA A = RSA::create_receiver();
    RSA B = RSA::create_sender(A.n, A.e);
    std::vector<unsigned char> cipher = B.encode_message(text);
    std::string message = A.decode_message(cipher);
    std::cout << "Encoded message\n";
    for(unsigned char letter : cipher)
        std::cout << letter;
    std::cout << '\n' << std::endl;
    std::cout << "Decoded message \n" << message << "\n" << std::endl;
}

void example_of_cracking(std::string text="Hello there!")
{
    RSA A = RSA::create_receiver(997, 887, 7);
    // we know only e and n, so we can bruteforce divisors of n
    desired_type e = A.e, n = A.n;
    desired_type q, p;
    auto cipher = A.encode_message(text);
    std::cout << "Encoded message\n";
    for(unsigned char letter : cipher)
        std::cout << letter;
    std::cout << '\n' << std::endl;
    // brute force for q and p
    for(q = 2; q < std::sqrt((double)n) + 1; q++)
    {
        if(n%q == 0)
            break;
    }
    p = n/q;
    std::cout << "p and q are " << p << " and " << q << std::endl;
    RSA B = RSA::create_receiver(p, q, e);
    std::cout << "cracked message:\n" << B.decode_message(cipher) << std::endl;
}

void print_bytes(unsigned char byte)
{
    for(int i = 0; i < 8; i++)
    {
        std::cout << (byte & 1);
        byte = byte >> 1;
    }
}

int main() {
    example_of_work();
    std::cout << std::endl;
    example_of_cracking();

    return 0;
}
