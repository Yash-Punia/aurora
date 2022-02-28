#include<iostream>
#include "Aurora/engine.h"

int main()
{
    int a, b;
    std::cout<<"Aurora Engine Online!";
    std::cin>>a>>b;
    std::cout<<"\nAnd the sum is"<<aurora::Add(a,b);
    std::cin>>a;
    return 0;
}