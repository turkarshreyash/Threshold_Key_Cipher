/*
Shreyash H. Turkar
29 April 2020
*/

#pragma once

//general
#include<iostream>
//containers
#include<inttypes.h>
//random function
#include<stdlib.h>
//power function
#include<cmath>

#define ENCRYP_LEN 32

#define DEBUG


struct shares_key{
    uint8_t y[ENCRYP_LEN];
    uint32_t x;
};


/*
Function to construct n shares of secret key in n parts with k threshold
@parameters:
secret key, n, k
*/
struct shares_key* construct_shares(uint8_t*, uint16_t, uint16_t);


/*
Function to reconstruct secret key from k parts
@parameters:
share keys[k], k
*/
uint8_t* construct_key(struct shares_key*, uint16_t);

/*
@turkarshreyash
c++
*/