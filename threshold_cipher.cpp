#include"threshold_cipher.hpp"


struct shares_key* construct_shares(uint8_t* secret_key, uint16_t n, uint16_t k){

    //container to store shares
    struct shares_key* __share = new struct shares_key[n];

    //container to store coeffiecents for calculation of f(x)
    uint8_t *__coeffiecents = new uint8_t[k];

    uint64_t __random_in;
    //contruct coeffecient which are nothing but random numbers
    //coeffecient 0 is key it self hence excluded!  
    for(uint16_t i = 1 ; i <  k ; i++){
        __random_in = rand();
        //GF(256)
        __coeffiecents[i] = __random_in % 0xFF; 
    }

    uint64_t __temp,__f_x;

    //loop for calculating threshold __share for each byte in key
    //bp -> byte pointer will run from 0 to alway to ENCRYPT_LEN
    for(uint16_t bp = 0 ; bp < ENCRYP_LEN ; bp++){
    
        //coeffecient for each byte will be secret keys bp
        __coeffiecents[0] = secret_key[bp];


        //x for each key
        //x = 0 => secret key hence excluded! 
        for(uint32_t x = 1 ; x <= n ; x++){
            //starting to calculate f(x)
            __f_x = 0;
            
            for(uint16_t i = 0 ; i < k ; i++){
                //coeffecient
                __temp = __coeffiecents[i];
                //multiple coeffecient wil x^i
                __temp *= pow(x,i);
                //GF(256)
                __temp = __temp%0xFF;
                
                __f_x += __temp;
            }

            __share[x-1].y[bp] = __f_x;
            __share[x-1].x = x;
        }
    }

    return __share;
}

uint8_t* construct_key(struct shares_key* shares, uint16_t k){
    //output
    uint8_t* __secret_key = new uint8_t[ENCRYP_LEN];
    uint64_t __yi;
    uint8_t __y;

    for(uint16_t bp = 0; bp < ENCRYP_LEN ; bp++){

        __yi = 0;

        for (uint16_t i = 0; i < k ; i++) { 
            // Compute individual terms of above formula 
            __y = shares[i].y[bp];
            for (uint16_t j = 0 ; j < k ; j++){ 
                if (j!=i) 
                    __yi = __yi*(shares[j].x)/(shares[j].x - shares[i].x); 
            } 
    
            // Add current term to __yi 
            __yi += __yi; 
        } 
        __yi = __yi % 0xff;
        __secret_key[bp] = __yi;
    }
    return __secret_key;
}