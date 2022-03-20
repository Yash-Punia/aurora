#include<iostream>
#include "Aurora/engine.h"

int main()
{
    std::cout<<"Aurora Engine Online!" << std::endl;

    aurora::Engine& engine = aurora::Engine::Instance();
      
    engine.Run();    

    std::cout<<"\n\nPress ENTER to continue...";
    std::cin.ignore();

    return 0;
}