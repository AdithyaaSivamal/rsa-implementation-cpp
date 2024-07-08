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
 * @brief Main function to demonstrate simplified RSA encryption and decryption.
 * 
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 * @return int Exit status of the program.
 */
int main(int argc, char* argv[]) {
    srand(static_cast<unsigned int>(time(0)));

    // Validate command line arguments
    if (argc < 2 || argc > 3) {
        std::cerr << "Usage: " << argv[0] << " <hex_message> [-i]\n";
        return 1;
    }

    // Check if detailed output is requested
    bool detailedOutput = (argc == 3 && std::string(argv[2]) == "-i");

    // Step 1: Generate two large prime numbers p and q
    int p = generatePrime();
    int q = generatePrime();

    // Step 2: Compute n = p * q
    int n = p * q;

    // Step 3: Calculate Euler's Totient function phi = (p-1) * (q-1)
    int phi = (p - 1) * (q - 1);

    // Step 4: Generate a suitable public exponent e
    int e = generateE(phi);

    // Step 5: Calculate the private exponent d
    int d;
    try {
        d = modInverse(e, phi);
    } catch (const std::runtime_error& ex) {
        std::cerr << ex.what() << "\n";
        return 1;
    }

    // Step 6: Convert the input message from hexadecimal to an integer
    int message;
    try {
        message = std::stoi(argv[1], nullptr, 16);
    } catch (const std::invalid_argument& ex) {
        std::cerr << "Invalid hexadecimal input.\n";
        return 1;
    }

    // Encrypt the message using the public key (e, n)
    int ciphertext = modExp(message, e, n);

    // Decrypt the message using the private key (d, n)
    int decryptedMessage = modExp(ciphertext, d, n);

    // Display the results based on the requested output detail level
    if (detailedOutput) {
        displayEnhancedOutput(message, message, p, q, n, phi, e, d, ciphertext, decryptedMessage);
    } else {
        std::cout << "Encrypted message (as hex): " << std::hex << ciphertext << "\n";
        std::cout << "Decrypted message (as hex): " << std::hex << decryptedMessage << "\n";
    }

    return 0;
}
