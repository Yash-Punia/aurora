#pragma once

#include "aurora/engine.h"
#include "aurora/app.h"

/** To be implemented in Client app
 * The client returns pointer to instance of class derived from aurora app
 * The ownership of returned pointer belongs to aurora
 *
 * Eg:
 * class ClientApp : public aurora::App {};
 * aurora::App* CreateApp() { return new ClientApp; }
 * 
 */ 
aurora::App* CreateApp();

int main()
{
    aurora::App* app = CreateApp();
    aurora::Engine::Instance().Run(app);    

    /** we can delete this pointer because client never hold on to 
     * this memory and we manage it completely
     */
    delete app;

    return 0;
}