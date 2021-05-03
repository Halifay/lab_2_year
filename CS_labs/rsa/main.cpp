#include <iostream>
#include <vector>

typedef long long desired_type;
class RSA
{
public:
    desired_type p, q, n;
    desired_type e, phi, d;

    static RSA create_receiver()
    {
        desired_type p, q;
        // TODO: initialize p and q here
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
                // result.e = rand()%result.phi;
                // result.e = rand()%result.n;
                result.e = 7;
                if(are_mutually_simple(result.e, result.phi));
                // if(are_mutually_simple(result.e, result.n));
                    break;
            }
        else
            result.e = e;
        desired_type second;
        euclid(result.e, result.phi, result.d, second);
        result.d = (result.d + result.phi)%result.phi;
        // euclid(result.e, result.n, result.d, second);
        // result.d = (result.d + result.n)%result.n;
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

    static bool are_mutually_simple(desired_type first, desired_type second)
    {
        if(second == 0)
            return first == 1;
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

    desired_type pow(desired_type word, desired_type power, desired_type modulo)
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

    std::vector<unsigned char> decode_message(std::vector<unsigned char> message)
    {
        int bytes = module_bytes();
        std::vector<unsigned char> answer(0);
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

int main() {
    std::string text = "Hello there!";
    std::vector<unsigned char> uctext;
    for(char letter : text)
        uctext.push_back(letter);
    RSA A = RSA::create_receiver(997, 887);
    RSA B = RSA::create_sender(A.n, A.e);
    std::vector<unsigned char> cipher = A.encode_message(text);
    // std::string message = A.decode_message(cipher);
    std::vector<unsigned char> message = A.decode_message(cipher);
    // std::cout << "Encoded message\n" << cipher << "\n" << std::endl;
    // std::cout << "Decoded message \n" << message << "\n" << std::endl;
    return 0;
}
