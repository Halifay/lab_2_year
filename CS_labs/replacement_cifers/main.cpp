#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <set>
#include <functional>

using namespace std;
const int base = 26;

bool is_not_letter(char c)
{
    return (c < 'a' || c > 'z');
}

string &lowercase(string &input)
{
    for(auto &letter : input)
    {
        if('A' <= letter && letter <= 'Z')
            letter -= 'A' - 'a';
    }
    return input;
}

int almost_euclid(int a)
{
    for(int result = 1; result < base; result++)
    {
        if( (a * result)%base == 1)
            return result;
    }
    throw invalid_argument("no reverse element for " + to_string(a) + " with base " + to_string(base));
}

string substitution(string input, vector<char> table)
{
    string output = input;
    lowercase(output);
    for(char &letter :output)
    {
        if(is_not_letter(letter))
            continue;
        letter = table[letter];
    }
    return output;
}

string de_substitution(string input, vector<char> table)
{
    vector<char> de_table(table.size(), 0);
    for(int i = 'a'; i <='z'; i++)
        de_table[table[i]] = i;
    for(char &letter : input)
    {
        if(is_not_letter(letter))
            continue;
        letter = de_table[letter];
    }
    return input;
}

string athens(string input, int a, int b)
{
    if(a % 2 == 0 || a % 13 == 0)
        throw invalid_argument("26 and a should not have common dividers");
    // string output = input;
    vector<char> table('z' + 1, 0);
    for(int i = 'a'; i <= 'z'; i++)
        table[i] = (char)(((i - 'a' + 1) * a + b - 1)%base + (int)'a');
    return substitution(input, table);
    // for(auto &letter : output)
    // {
    //     if ('A' <= letter && letter <= 'Z')
    //         letter -= 'A' - 'a';
    //     if (letter < 'a' || 'z' < letter)
    //         continue;
    //     letter = (char)(((letter - 'a' + 1) * a + b - 1)%base + (int)'a');
    // }
    // return output;
}

string de_athens(string input, int a, int b)
{
    vector<char> table('z' + 1, 0);
    for(int i = 'a'; i <= 'z'; i++)
        table[i] = (char)(((i - 'a' + 1) * a + b - 1)%base + (int)'a');
    return de_substitution(input, table);
    // string output = input;
    // for(auto &letter : output)
    // {
    //     if (letter < 'a' || 'z' < letter)
    //         continue;
    //     letter = (((letter - 'a' + 1) - b + base) * almost_euclid(a) - 1) % base + 'a';
    // }
    // return output;
}

string caesar(string input, int b)
{
    return athens(input, 1, b);
}

string de_caesar(string input, int b)
{
    return de_athens(input, 1, b);
}

string rec_athens(string input, int a1, int b1, int a2, int b2)
{
    int a = a1, b = b1;
    if(a % 2 == 0 || a2 % 2 == 0 || a % 13 == 0 || a2 % 13 == 0)
        throw invalid_argument("26 and a should not have common dividers");
    string output = input;
    for(int i = 0; i < input.size(); i++)
    {
        auto &letter = output[i];
        if ('A' <= letter && letter <= 'Z')
            letter -= 'A' - 'a';
        if (letter < 'a' || 'z' < letter)
            continue;
        letter = ((letter - 'a' + 1) * a + b - 1)%base + (int)'a';
        if(i == 0)
        {
            a = a2; b = b2;
        } else{
            a = (a1*a2 - 1)%base + 1;
            a1 = a2; a2 = a;
            b = (b1+b2 - 1)%base + 1;
            b1 = b2; b2 = b;
        }
    }
    return output;
}

string de_rec_athens(string input, int a1, int b1, int a2, int b2)
{
    int a = a1, b = b1;
    string output = input;
    for(int i = 0; i < output.size(); i++)
    {
        auto &letter = output[i];
        if (letter < 'a' || 'z' < letter)
            continue;
        int a_rev = almost_euclid(a);
        letter = ((letter - 'a' + 1 - b + base) * a_rev - 1) % base + 'a';
        if(i == 0)
        {
            a = a2; b = b2;
        } else{
            a = (a1*a2 - 1)%base + 1;
            a1 = a2; a2 = a;
            b = (b1 + b2 - 1)%base + 1;
            b1 = b2; b2 = b;
        }
    }
    return output;
}

string athens_cracker(string input)
{
    string output = input;
    output.erase(remove_if(output.begin(), output.end(), is_not_letter), output.end());
    map<string, int> bag;
    for(int i = 0; i < output.size() - 2; i++)
    {
        string word = "";
        word = word + output[i] + output[i + 1] + output[i + 2];
        if(bag.find(word) == bag.end())
            bag[word] = 1;
        else
            bag[word] += 1;
    }
    vector<pair<int, string>> stat;
    for(auto word : bag)
    {
        stat.push_back(make_pair(word.second, word.first));
    }
    sort(stat.begin(), stat.end());
    cout << "pretendents to be 'the':" << endl;
    for(int i = stat.size() - 1; i >= 0; i--) {
        cout << stat[i].second << ' ' << stat[i].first << " times" << endl;
        string the = stat[i].second;
        for (int a = 1; a < base; a++) {
            int b;
            int first, second, third, fourth, fifth;
            first = ('t' - 'h');
            second = (first * a) % base;
            third = (the[0] - the[1] + base) % base;
            // if (second >= third - 2 && second <= third)
            if(second == third)
                b = (the[0] - 'a' + 1 - ((('t' + 1 - 'a') * a - 1) % base + 1) + base) % base;
            else
                continue;
            if (the[1] == ((('h' + 1 - 'a') * a + b - 1) % base + 'a') &&
                the[2] == ((('e' + 1 - 'a') * a + b - 1) % base + 'a')) {
                string result = de_athens(input, a, b);
                cout << result << endl;
                return result;
            }
        }
    }
    cout << "wasn't able to find word";
}

void substitution_cracker(string input, string example)
{
    lowercase(example);
    example.erase(remove_if(example.begin(), example.end(), is_not_letter), example.end());
    string output = input;
    output.erase(remove_if(output.begin(), output.end(), is_not_letter), output.end());
    lowercase(output);
    vector<int> exbag('z' + 1, 0), inbag('z' + 1, 0);
    for(char &letter : example)
    {
        exbag[letter]++;
    }
    for(char &letter : output)
    {
        inbag[letter]++;
    }
    set<pair<int, char>, greater<pair<int, char>>> exset, inset;
    vector<char> sub_table('z' + 1, 0);
    for(int i = 'a'; i <= 'z'; i++)
    {
        exset.insert(make_pair(exbag[i], (char)i));
        inset.insert(make_pair(inbag[i], (char)i));
    }
    while(!exset.empty())
    {
        pair<int, char> from, to;
        from = *exset.begin();
        to = *inset.begin();
        // cout << from.first << ' ' << from.second << endl;
        // cout << to.first << ' ' << to.second << endl;
        sub_table[to.second] = from.second;
        exset.erase(exset.begin());
        inset.erase(inset.begin());
    }
    output = input;
    lowercase(output);
    for(char &letter : output)
    {
        if (is_not_letter(letter))
            continue;
        letter = sub_table[letter];
    }
    cout << output << endl;
}

int main() {
    // string text = "Play The Guessing Game: This can be one of the most useful skills for a cryptanalyst to employ - the ability to identify words, or even entire phrases, based on experience or sheer guesswork. Al-Khalil, an early Arabian cryptanalyst, demonstrated this talent when he cracked a Greek ciphertext. He guessed that the ciphertext began with the greeting 'In the name of God'. Having established that these letters corresponded to a specific section of ciphertext, he could use them as a crowbar to prise open the rest of the ciphertext. This is known as a crib.";
    // string text = "More generally, cryptography is about constructing and analyzing protocols that prevent third parties or the public from reading private messages;[3] various aspects in information security such as data confidentiality, data integrity, authentication, and non-repudiation[4] are central to modern cryptography. Modern cryptography exists at the intersection of the disciplines of mathematics, computer science, electrical engineering, communication science, and physics. Applications of cryptography include electronic commerce, chip-based payment cards, digital currencies, computer passwords, and military communications.";
    string text = "Cryptography prior to the modern age was effectively synonymous with encryption, converting information from a readable state to unintelligible nonsense. The sender of an encrypted message shares the decoding technique only with intended recipients to preclude access from adversaries. The cryptography literature often uses the names Alice ('A') for the sender, Bob ('B') for the intended recipient, and Eve ('eavesdropper') for the adversary.[5] Since the development of rotor cipher machines in World War I and the advent of computers in World War II, cryptography methods have become increasingly complex and its applications more varied.\nModern cryptography is heavily based on mathematical theory and computer science practice; cryptographic algorithms are designed around computational hardness assumptions, making such algorithms hard to break in actual practice by any adversary. While it is theoretically possible to break into a well-designed system, it is infeasible in actual practice to do so. Such schemes, if well designed, are therefore termed 'computationally secure'; theoretical advances, e.g., improvements in integer factorization algorithms, and faster computing technology require these designs to be continually reevaluated, and if necessary, adapted. There exist information-theoretically secure schemes that provably cannot be broken even with unlimited computing power, such as the one-time pad, but these schemes are much more difficult to use in practice than the best theoretically breakable but computationally secure schemes.\nThe growth of cryptographic technology has raised a number of legal issues in the information age. Cryptography's potential for use as a tool for espionage and sedition has led many governments to classify it as a weapon and to limit or even prohibit its use and export.[6] In some jurisdictions where the use of cryptography is legal, laws permit investigators to compel the disclosure of encryption keys for documents relevant to an investigation.[7][8] Cryptography also plays a major role in digital rights management and copyright infringement disputes in regard to digital media.[9]";
    string bigtext = "The main classical cipher types are transposition ciphers, which rearrange the order of letters in a message (e.g., 'hello world' becomes 'ehlol owrdl' in a trivially simple rearrangement scheme), and substitution ciphers, which systematically replace letters or groups of letters with other letters or groups of letters (e.g., 'fly at once' becomes 'gmz bu podf' by replacing each letter with the one following it in the Latin alphabet). Simple versions of either have never offered much confidentiality from enterprising opponents. An early substitution cipher was the Caesar cipher, in which each letter in the plaintext was replaced by a letter some fixed number of positions further down the alphabet. Suetonius reports that Julius Caesar used it with a shift of three to communicate with his generals. Atbash is an example of an early Hebrew cipher. The earliest known use of cryptography is some carved ciphertext on stone in Egypt (ca 1900 BCE), but this may have been done for the amusement of literate observers rather than as a way of concealing information. More generally, cryptography is about constructing and analyzing protocols that prevent third parties or the public from reading private messages;[3] various aspects in information security such as data confidentiality, data integrity, authentication, and non-repudiation[4] are central to modern cryptography. Modern cryptography exists at the intersection of the disciplines of mathematics, computer science, electrical engineering, communication science, and physics. Applications of cryptography include electronic commerce, chip-based payment cards, digital currencies, computer passwords, and military communications. Prior to the early 20th century, cryptography was mainly concerned with linguistic and lexicographic patterns. Since then the emphasis has shifted, and cryptography now makes extensive use of mathematics, including aspects of information theory, computational complexity, statistics, combinatorics, abstract algebra, number theory, and finite mathematics generally. Cryptography is also a branch of engineering, but an unusual one since it deals with active, intelligent, and malevolent opposition; other kinds of engineering (e.g., civil or chemical engineering) need deal only with neutral natural forces. There is also active research examining the relationship between cryptographic problems and quantum physics. Just as the development of digital computers and electronics helped in cryptanalysis, it made possible much more complex ciphers. Furthermore, computers allowed for the encryption of any kind of data representable in any binary format, unlike classical ciphers which only encrypted written language texts; this was new and significant. Computer use has thus supplanted linguistic cryptography, both for cipher design and cryptanalysis. Many computer ciphers can be characterized by their operation on binary bit sequences (sometimes in groups or blocks), unlike classical and mechanical schemes, which generally manipulate traditional characters (i.e., letters and digits) directly. However, computers have also assisted cryptanalysis, which has compensated to some extent for increased cipher complexity. Nonetheless, good modern ciphers have stayed ahead of cryptanalysis; it is typically the case that use of a quality cipher is very efficient (i.e., fast and requiring few resources, such as memory or CPU capability), while breaking it requires an effort many orders of magnitude larger, and vastly larger than that required for any classical cipher, making cryptanalysis so inefficient and impractical as to be effectively impossible.";
    // string first_example = "The quick brown fox jumps over the lazy dog.";
    // string first_example = "Amazingly few discotheques provide jukeboxes";
    // string second_example = "Hello there!";
    // std::cout << de_rec_athens(rec_athens(second_example, 3, 2, 5, 3), 3, 2, 5, 3) << '\n' << std::endl;
    // std::cout << "Starting text\n" << text << std::endl;
    string cipher = athens(text, 3, 2);
    // string cipher = rec_athens(text, 5, 3, 7, 5);
    cout << "\nencoded text\n" << cipher << endl;
    cout << "\ndecoded text\n" << de_athens(cipher, 3, 2) << endl;
    // cout << de_rec_athens(cipher, 5, 3, 7, 5) << endl;
    cout << "\ncracker for simple substitution cipher gives:" << endl;
    substitution_cracker(ciaher, bigtext);
    cout << "\ncracker for shift cipher gives:" << endl;
    athens_cracker(cipher);
    return 0;
}
