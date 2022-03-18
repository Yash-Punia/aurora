#include<iostream>
#include "Aurora/engine.h"

int main()
{
    std::cout<<"Aurora Engine Online!";

    aurora::Initialize();
    aurora::Shutdown();

    system("pause");
    return 0;
}