#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <numeric>
#include <stdexcept>
#include <string>
#include "helperFunctions.h"

/**
 * @brief Check if a number is prime.
 * 
 * @param n The number to check.
 * @return true If the number is prime.
 * @return false If the number is not prime.
 */
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

/**
 * @brief Generate a large prime number.
 * 
 * @return int The generated prime number.
 */
int generatePrime() {
    int prime;
    do {
        prime = rand() % 100 + 100; // Adjust range for larger primes
    } while (!isPrime(prime));
    return prime;
}

/**
 * @brief Calculate the greatest common divisor (gcd) using Euclidean algorithm.
 * 
 * @param a The first integer.
 * @param b The second integer.
 * @return int The gcd of a and b.
 */
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

/**
 * @brief Generate e such that 1 < e < phi and gcd(e, phi) = 1.
 * 
 * @param phi Euler's Totient function value.
 * @return int The generated e value.
 */
int generateE(int phi) {
    int e;
    do {
        e = rand() % (phi - 2) + 2; // e must be between 2 and phi-1
    } while (gcd(e, phi) != 1);
    return e;
}

/**
 * @brief Compute the modular multiplicative inverse of e modulo phi.
 * 
 * @param e The value e.
 * @param phi Euler's Totient function value.
 * @return int The modular multiplicative inverse of e modulo phi.
 * @throws std::runtime_error If e is not invertible.
 */
int modInverse(int e, int phi) {
    int t = 0, newT = 1;
    int r = phi, newR = e;
    while (newR != 0) {
        int quotient = r / newR;
        std::tie(t, newT) = std::make_pair(newT, t - quotient * newT);
        std::tie(r, newR) = std::make_pair(newR, r - quotient * newR);
    }
    if (r > 1) {
        throw std::runtime_error("e is not invertible");
    }
    if (t < 0) t += phi;
    return t;
}

/**
 * @brief Perform modular exponentiation.
 * 
 * @param base The base value.
 * @param exp The exponent value.
 * @param mod The modulus value.
 * @return int The result of (base^exp) % mod.
 */
int modExp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

/**
 * @brief Display detailed output of the RSA process.
 * 
 * @param message The original message.
 * @param intMessage The integer representation of the message.
 * @param p Prime number p.
 * @param q Prime number q.
 * @param n The modulus n (product of p and q).
 * @param phi Euler's Totient function value.
 * @param e The public exponent e.
 * @param d The private exponent d.
 * @param ciphertext The encrypted message.
 * @param decryptedMessage The decrypted message.
 */
void displayEnhancedOutput(int message, int intMessage, int p, int q, int n, int phi, int e, int d, int ciphertext, int decryptedMessage) {
	
    int digitCount = std::log10(std::abs(e)) + 1;
    const std::string blue = "\033[34m";
    const std::string reset = "\033[0m";
		
    std::cout << R"(
    ____  _____ ___ 
   / __ \/ ___//   |
  / /_/ /\__ \/ /| |
 / _, _/___/ / ___ |
/_/ |_|/____/_/  |_|
                    
----------------------------------
NOTE: This is an oversimplified RSA encryption and decryption demo. 
      It is not secure for production use. At all.
----------------------------------

)";
    std::cout << "Message = " << std::hex << message << std::endl;
    // Convert message to display int using
    std::cout << "Message as int = " << std::to_string(intMessage) << std::endl;
    std::cout << "-------------------------------\n\n";

    // Graph
    std::cout << "     Generate Prime numbers:" << std::endl;
    std::cout << "     " << blue << "p" << reset << " = " << std::dec << p << " ------- " << blue << "q" << reset << " = " << std::dec << q << "" << std::endl;
    std::cout << "                |" << std::endl;
    std::cout << "                |                             __" << std::endl;
    std::cout << "                |--> " << blue << "n" << reset << " = " << n << "                  |" << std::endl;
    std::cout << "           /    |                               |" << std::endl;
    std::cout << "           \\    |--> " << blue << "phi" << reset << " = (" << p << "-1) x (" << q << "-1)    |- " << blue << "d" << reset << " = e^(phi(n))^-1 (mod n)" << std::endl; 
    std::cout << "            \\   |                               |       |" << std::endl;
    if(digitCount == 4){
        std::cout << "            /\\  |--> " << blue << "e" << reset << " = " << e << ", a coprime of phi |       |" << std::endl;
    } else {
        std::cout << "            /\\  |--> " << blue << "e" << reset << " = " << e << ", a coprime of phi|       |" << std::endl;
    }
    std::cout << "           /  \\                               __|       |" << std::endl;
    std::cout << "          /    \\/                                       |" << std::endl;
    std::cout << "         /                                              V" << std::endl;
    std::cout << "encrypt() = (message)^e mod(n)          decrypt() = (ciphertext)^d mod(n)" << std::endl;
    std::cout << "message: " << std::hex << message << "                            ciphertext: " << std::hex << ciphertext << std::endl;
    std::cout << "  |                                                     |" << std::endl;
    std::cout << "  v                                                     v" << std::endl;
    std::cout << "message as int: " << std::to_string(intMessage) << "                    ciphertext as int: " << std::to_string(ciphertext) << std::endl;
    std::cout << "  |                                                     |" << std::endl;
    std::cout << "  v                                                     v" << std::endl;
    std::cout << "encrypted message: " << std::to_string(ciphertext) << "               decrypted message: " << std::to_string(decryptedMessage) << std::endl;
    std::cout << "  |                                                     |" << std::endl;
    std::cout << "  v                                                     V" << std::endl;
    std::cout << "encrypted message(in hex): " << std::hex << ciphertext << "           decrypted message(in hex): " << std::hex << decryptedMessage << std::endl;
    std::cout << std::endl;
    std::cout << "-------------------------------\n\n";
    std::cout << "Public key (e, n): (" << std::to_string(e) << ", " << std::to_string(n) << ")\n";
    std::cout << "Private key (d, n): (" << d << ", " << std::to_string(n) << ")\n";
    std::cout << "-------------------------------\n\n";
    std::cout << std::endl;
}

/**
 * @brief Convert an integer to its hexadecimal string representation.
 * 
 * @param number The integer to convert.
 * @return std::string The hexadecimal string representation of the number.
 */
std::string intToHex(int number) {
    std::string hexStr = std::to_string(number);
    return hexStr;
}
