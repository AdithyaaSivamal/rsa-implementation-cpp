
---

# RSA Encryption Demo

This project is a supplementary example for a post on my blog, [Threat  Treks](https://threattreks.wordpress.com/). It demonstrates the mechanism behind RSA encryption and decryption.<br>
**Note:** This code is not intended for use as a secure encryption tool. It is a personal project aimed at researching and understanding RSA.

## Prerequisites

To run this project, you need to have a C++ compiler and `make` installed on your system.

### Install `make` on Windows

1. **Install Chocolatey** (if not already installed):

```powershell
Set-ExecutionPolicy Bypass -Scope Process -Force; \
[System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor [System.Net.SecurityProtocolType]::Tls12; \
iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))
```

2. **Install `make`**:

```powershell
choco install make
```

3. **Run `make`**:

```powershell
make
```

### Install `make` on Linux

1. **Install `make`** (if not already installed):

```bash
sudo apt-get update
sudo apt-get install build-essential
```

2. **Run `make`**:

```bash
make
```

## Compilation

You can compile the project using `make`:

```bash
make
```

Alternatively, you can compile using `g++`:

```bash
g++ -o rsa_example rsa.cpp helperFunctions.cpp
```

## Usage

Run the executable with the following syntax:

```bash
./rsa_example.exe <hex value> [-i]
```

### Example:

```bash
./rsa_example.exe 1a2b -i
```

### Options

- `<hex value>`: A hexadecimal value representing the message to encrypt. The value must be 4 digits or less and less than `n`.
- `-i`: (Optional) Provides additional information about how the RSA algorithm works.

## Enhanced Output with -i
When you run the program with the -i flag will illustrate the RSA encryption and decryption mechanism. 

![-i example image](https://github.com/AdithyaaSivamal/Cyber-Security-Portfolio/assets/91487335/e60529d5-52f2-461c-a7ec-d166e567af3d)





## Notes

- The `-i` tag will give you detailed information about each step of the RSA algorithm.
- This program will only work correctly with hexadecimal values that are 4 digits or less, and the value must be less than `n`.


## Disclaimer

This code is for educational purposes only and should never be used for real encryption tasks. It is an oversimplified demonstration of the RSA algorithm.

---
