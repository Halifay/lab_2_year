#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <zconf.h>
#include "matrix.cpp"

bool is_not_letter(char c)
{
    return (c < 'a' || c > 'z'+3);
}

std::string &lowercase(std::string &input)
{
    for(auto &letter : input)
    {
        if('A' <= letter && letter <= 'Z')
            letter -= 'A' - 'a';
    }
    return input;
}

int positive_modulo(int element, int modulo)
{
    return (element % modulo + modulo) % modulo;
}

int reverse_element(int element, int modulo)
{
    element = positive_modulo(element, modulo);
    for(int i = 1; i < modulo; i++)
        if ((i * element) % modulo == 1)
            return i;
    return 0;
}

int get_det(Matrix<int> &mat)
{
    return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
}

void modulo_matrix(Matrix<int> &mat, int modulo)
{
    auto sizes = mat.get_dimensions();
    for(int i = 0; i < sizes.first; i++)
        for(int j = 0; j < sizes.second; j++)
            mat[i][j] = positive_modulo(mat[i][j], modulo);
}

Matrix<int> inverse_modulo(Matrix<int> &matrix1, int modulo)
{
    Matrix<int> matrix2 = matrix1;
    std::swap(matrix2[0][0], matrix2[1][1]);
    matrix2[1][0] *= -1;
    matrix2[0][1] *= -1;
    int det = get_det(matrix1);
    int mult = reverse_element(positive_modulo(det, modulo), modulo);
    matrix2 *= mult;
    auto sizes = matrix2.get_dimensions();
    modulo_matrix(matrix2, modulo);
    return matrix2;
}

Matrix<int> result(Matrix<int> &first, Matrix<int> &second, int modulo)
{
    Matrix<int> result = first * second;
    auto sizes = result.get_dimensions();
    modulo_matrix(result, modulo);
    return result;
}

Matrix<int> get_matrix(int modulo)
{
    for(int i = 0; i < 100; i++)
    {
        // Matrix<int> first(2, 2, modulo, i);
        Matrix<int> first(2, 2, modulo, std::time(NULL) + i);
        // std::cout << std::time(NULL) << " \n";
        int det = get_det(first);
        if (det%13 * det%2 * det%modulo == 0)
            continue;
        std::cout << i+1 << "'th try" << std::endl;
        return first;
    }
    std::cout << "No eligible matrix found!" << std::endl;
}

std::vector<std::pair<char, int>> get_character_line(std::string &text, int block_size)
{
    std::vector<std::pair<char, int>> character_line;
    std::string lower_text = lowercase(text);
    for(int i = 0; i < text.size(); i++)
    {
        if(is_not_letter(lower_text[i]))
            continue;
        character_line.push_back({lower_text[i] - 'a', i});
    }
    if (character_line.size() % block_size > 0)
        for(int i = character_line.size()%block_size; i < block_size; i++)
        {
            character_line.push_back({0, -1});
        }
    return character_line;
}

std::string hill_cipher(std::string text, Matrix<int> key, int modulo)
{
    int block_size = key.get_dimensions().second;
    auto character_line = get_character_line(text, block_size);
    for(int i = 0; i < character_line.size()/block_size; i++)
    {
        std::vector<int> word(block_size, 0);
        for(int j = 0; j < block_size; j++)
            word[j] = character_line[i*block_size + j].first;
        Matrix<int> encoded(word);
        encoded *= key;
        // for(int letter : encoded[0])
        //     letter = positive_modulo(letter, modulo);
        for(int j = 0; j < block_size; j++)
            character_line[i*block_size + j].first = positive_modulo(encoded[0][j], modulo);
    }
    for(auto letter : character_line)
    {
        if(letter.second > -1)
            text[letter.second] = letter.first + 'a';
        else
            text.push_back(letter.first + 'a');
    }
    return text;
}

std::string hill_cipher_decoder(std::string cipher, Matrix<int> key, int modulo)
{
    Matrix<int> inversed = inverse_modulo(key, modulo);
    cipher = hill_cipher(cipher, inversed, modulo);
    return cipher;
}

std::string hill_recurrent_cipher(std::string text, Matrix<int> key1, Matrix<int> key2, int modulo, bool decode=false)
{
    int block_size = key1.get_dimensions().second;
    auto character_line = get_character_line(text, block_size);
    for(int i = 0; i < character_line.size()/block_size; i++)
    {
        std::vector<int> word(block_size, 0);
        for(int j = 0; j < block_size; j++)
            word[j] = character_line[i*block_size + j].first;
        Matrix<int> encoded(word);
        encoded *= key1;
        // for(int letter : encoded[0])
        //     letter = positive_modulo(letter, modulo);
        for(int j = 0; j < block_size; j++)
            character_line[i*block_size + j].first = positive_modulo(encoded[0][j], modulo);
        if(i == 0)
            std::swap(key1, key2);
        else
        {
            if(!decode)
                key2 *= key1;
            else
                key2 = key1*key2;
            std::swap(key1, key2);
        }
    }
    for(auto letter : character_line)
    {
        if(letter.second > -1)
            text[letter.second] = letter.first + 'a';
        else
            text.push_back(letter.first + 'a');
    }
    return text;
}

std::string hill_recurrent_cipher_decoder(std::string cipher, Matrix<int> key1, Matrix<int> key2, int modulo)
{
    Matrix<int> inversed1 = inverse_modulo(key1, modulo);
    Matrix<int> inversed2 = inverse_modulo(key2, modulo);
    cipher = hill_recurrent_cipher(cipher, inversed1, inversed2, modulo, true);
    return cipher;
}

// works only for block size of 2, because there is no automated equation solver
void hill_cipher_cracker(std::string cipher, std::string known_part, int modulo, int block_size=2)
{
    auto cipher_line = get_character_line(cipher, block_size);
    auto known_line = get_character_line(known_part, block_size);
    int a, b, c, d;
    a = positive_modulo(positive_modulo(cipher_line[2].first - cipher_line[0].first *
            reverse_element(known_line[1].first, modulo)*known_line[3].first, modulo) *
            reverse_element(positive_modulo(known_line[2].first - known_line[0].first *
            reverse_element(known_line[1].first, modulo) * known_line[3].first, modulo), modulo), modulo);
    c = positive_modulo((cipher_line[2].first - a*known_line[2].first) *
            reverse_element(known_line[3].first, modulo), modulo);
    b = positive_modulo(positive_modulo(cipher_line[3].first - cipher_line[1].first *
            reverse_element(known_line[1].first, modulo)*known_line[3].first, modulo) *
            reverse_element(positive_modulo(known_line[2].first - known_line[0].first *
            reverse_element(known_line[1].first, modulo) * known_line[3].first, modulo), modulo), modulo);
    d = positive_modulo((cipher_line[3].first - b*known_line[2].first) *
            reverse_element(known_line[3].first, modulo), modulo);
    Matrix<int> key(2, 2);
    key[0][0] = a; key[0][1] = b;
    key[1][0] = c; key[1][1] = d;
    std::cout << "cracked matrix is\n" << key << std::endl;
    std::string answer = hill_cipher_decoder(cipher, key, modulo);
    std::cout << "cracked answer is\n" << answer << std::endl;
}

std::string print_string_as_numbers(std::string text, int modulo)
{
    for(char letter : lowercase(text))
        if(is_not_letter(letter))
            std::cout << "  ";
        else
        std::cout << int(letter - 'a') << ' ';
}

void hill_cipher_test(std::string text, int modulo)
{
    Matrix<int> first = get_matrix(modulo);
    std::string cipher = hill_cipher(text, first, modulo);
    std::cout << "cipher matrix\n" << first << std::endl;
    std::cout << "inverse matrix\n" << inverse_modulo(first, modulo) << std::endl;
    std::cout << "starting text\n" << text << std::endl;
    print_string_as_numbers(text, modulo);
    std::cout << '\n';
    std::cout << "Encoded text\n" << cipher << std::endl;
    print_string_as_numbers(cipher, modulo);
    std::cout << '\n';
    std::cout << "Decoded text\n" << hill_cipher_decoder(cipher, first, modulo) << std::endl;
    hill_cipher_cracker(cipher, text, modulo);
}

void hill_recurrent_cipher_test(std::string text, int modulo)
{
    Matrix<int> first = get_matrix(modulo);
    usleep(1e6);
    Matrix<int> second = get_matrix(modulo);
    std::string cipher = hill_recurrent_cipher(text, first, second, modulo);
    std::cout << "Encoded text\n";
    std::cout << cipher << '\n' << std::endl;
    std::cout << "Decoded text\n";
    std::cout << hill_recurrent_cipher_decoder(cipher, first, second, modulo) << std::endl;
}

int main() {
    int modulo = 29;
    std::string test1 = "Hello there!";
    hill_recurrent_cipher_test(test1, modulo);
    hill_cipher_test(test1, modulo);
    // Matrix<int> first = get_matrix(modulo);
    // usleep(1e6);
    // Matrix<int> second = get_matrix(modulo);
    // std::string cipher = hill_recurrent_cipher(test1, first, second, modulo);
    // std::cout << cipher << std::endl;
    // std::cout << hill_recurrent_cipher_decoder(cipher, first, second, modulo);
    // first[0][0] = 4; first[0][1] = -5;
    // first[1][0] = -3; first[1][1] = 1;
    // Matrix<int> second = inverse_modulo(first, modulo);
    // std::cout << "start\n" << first << std::endl;
    // std::cout << "inverse\n" << second << std::endl;
    // std::cout << "inversed determinant\n" << positive_modulo(get_det(second), modulo) << std::endl;
    // std::cout << "mult\n" << result(second, first, modulo) << std::endl;
    // std::cout << "mult2\n" << result(first, second, modulo) << std::endl;
    // std::cout << -2634 % 26 << std::endl;
    return 0;
}
