// Created by Jesus Vasquez-Cipriano on 3/21/2021.
// Copyright © 2021 Jesus Vasquez-Cipriano. All rights reserved.

// Description: A program to encrypt and decrypt a message using a shift cipher.
// The plaintext message must only contain the codebook characters
//
// command line arguments
// -p ThePla!Nt#xTM#ss2ge1 - the plaintext (p) message to be encrypted
// -C pC9lG1VjOwSpiwNNXB9x - the cipher (C) text to be decrypted
// -k  9                   - the key (k) shift value
// -E                        - the option to encrypt (E)
// -D                        - the option to decrypt (D)
//

#include <iostream> //std::cout, std::cin, etc.
#include <cstdlib> //C++ version of stdlib.h
#include <cstring> //C++ version of string.h -- for C-Style string functions like std::strcmp and std::strlen
#include <string> //For Review: Why is this needed?
#define CBL 64 //Code Book Length:

char codebook [] = {'Z','z','Y','y','X','x','W','w','V','v','U','u','T','t','S','s','R','r','Q','q', 'P','p','O','o','N','n','M','m','L','l','K','k','J','j','I','i','H','h','G','g', 'F','f','E','e','D','d','C','c','B','b','A','a','9','8','7','6','5','4','3','2','1','0','#','!'};
unsigned long int msg_length = 0;
std::string converted_msg;
std::string output_str1;
std::string output_str2;

void encrypt (std::string& plaintext, int k);
void decrypt (std::string& ciphertext, int k);

int main(int argc, const char * argv[])
{
    int k = 0;
    std::string msg;
    int msg_index = 0;
    bool do_encrypt = false;
    
    //Parse argv[] to process and store command-line arguments.
    for (int i = 1; i < argc; i++)
    {
        if (!(strcmp(argv[i], "-k")))
        {
            k = atoi(argv[i+1]);
        }
        else if (!(strcmp(argv[i], "-p")) || !(strcmp(argv[i], "-C")))
        {
            msg_index = i+1;
            msg = argv[i+1];
            msg_length = msg.length();
        }
        else if (!(strcmp(argv[i], "-E")))
        {
            do_encrypt = true;
        }
        else if (!(strcmp(argv[i], "-D")))
        {
            do_encrypt = false;
        }
    }
    
    if (do_encrypt) //encrypt plaintext
    {
        encrypt(msg,k);
        output_str1 = "plaintext";
        output_str2 = "ciphertext";
    }
    else
    {
        decrypt(msg,k); //decrypt ciphertext
        output_str1 = "ciphertext";
        output_str2 = "plaintext";
    }
    
    std::cout << "The " << output_str1 << " was: " << msg << std::endl;
    std::cout << "The " << output_str2 << " is: " << converted_msg  << std::endl;
    
    return 0;
}

void encrypt (std::string& plaintext, int k)
{
    int p = 0; // p is the original index found in codebook.
    int new_index = 0; //the index in codebook of the new character.
    
    //Convert plaintext string into character array
    char msg_array[msg_length + 1];
    std::strcpy(msg_array, plaintext.c_str());
    
    for (int i = 0; i < msg_length; i++)
    {
        for (int j = 0; j < CBL; j++)
        {
            if (msg_array[i]==codebook[j])
            {
                p =  j;
                new_index = (p + k) % CBL;
                converted_msg = converted_msg + codebook[new_index];
            }
        }
    }
    return;
}

void decrypt (std::string& ciphertext, int k)
{
    int p = 0; // p is the original text index found in codebook.
    int new_index = 0; //the index in codebook of the new character.
    
    //Convert ciphertext string into character array
    char msg_array[msg_length + 1];
    std::strcpy(msg_array, ciphertext.c_str());

       for (int i = 0; i < msg_length; i++)
       {
           for (int j = 0; j < CBL; j++)
           {
               if (msg_array[i]==codebook[j])
               {
                   p =  j;
                   if ((p-k) >= 0)
                   {
                       new_index = (p - k) % CBL;
                   }
                   else
                   {
                       new_index = (((p - k) % CBL) + CBL) % CBL; 
                   }
                   converted_msg = converted_msg + codebook[new_index];
               }
           }
       }
    return;
}
