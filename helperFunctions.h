#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <numeric>
#include <stdexcept>
#include <string>

//basic math functions
bool isPrime(int n);
int generatePrime();
int gcd(int a, int b);

//RSA functions
int modInverse(int e, int phi);
int modExp(int base, int exp, int mod);
int generateE(int phi);

//display functions
void displayEnhancedOutput(int message, int intMessage, int p, int q, int n, int phi, int e, int d, int ciphertext, int decryptedMessage);
std::string intToHex(int number);

#endif // FUNCTIONS_H
