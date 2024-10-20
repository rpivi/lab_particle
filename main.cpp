#include<iostream>
#include"ParticleType.hpp"
#include"ResonanceType.hpp"

int main(){
    char a_='e';
    char* na= &a_;
    ParticleType a(na, 12., 1);
    ResonanceType b(na, 48., 3, 44.);

    ParticleType* es[2]=(a, b);

    for(int i=0; i<=1; i++){
        es[i]->Print();
    }
}