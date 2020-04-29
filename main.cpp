/*
Driver Code
Shreyash H. Turkar
29 April 2020
*/

#include<iostream>

#include"threshold_cipher.hpp"



void display_key(struct shares_key*);

int main(int argc, char *args[]){
    //secret_key in array format
    uint8_t key_string[ENCRYP_LEN]= {
                                        0x12, 0x56, 0xab, 0xc0, 0x00, 0x89, 0xa2, 0xc9,
                                        0x00, 0x89, 0xa2, 0xc9, 0x12, 0x56, 0xab, 0xc0,
                                        0x25, 0x10, 0x56, 0xbf, 0xae, 0x8a, 0x4a, 0xc0,
                                        0x56, 0xef, 0xe5, 0xa4, 0xcf, 0x45, 0xf5, 0xa3
                                    };
    
    std::cout<<"Key: ";
    for(uint16_t i = 0 ; i < ENCRYP_LEN ; i++){
        std::cout<<(uint16_t)key_string[i]<<" ";
    }
    std::cout<<'\n';

    uint16_t n = 4;
    uint16_t k = 2;

    struct shares_key* shares = construct_shares(key_string,n,k);

    for(uint16_t i = 0 ; i < n ; i++){
        std::cout<<"Share ("<<i<<"): ";
        display_key(&shares[i]);
    }

    uint8_t *recostructed = construct_key(shares,k);

    std::cout<<"Key Reconstructed: ";
    for(uint16_t i = 0 ; i < ENCRYP_LEN ; i++){
        std::cout<<(uint16_t)key_string[i]<<" ";
    }
    std::cout<<'\n';    
}

void display_key(struct shares_key* input){
    for(uint16_t i = 0 ; i < ENCRYP_LEN ; i++){
        std::cout<<(uint16_t)input->y[i]<<" ";
    }
    std::cout<<"\n";
}