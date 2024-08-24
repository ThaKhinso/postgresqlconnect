#include <crow.h>
#include <crow/app.h>
#include <crow/json.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


void stdhandler(std::string& name){
    std::string filepath = "templates/" + name + ".html";
    
}

int main() {
    crow::SimpleApp simpleApp;
    CROW_ROUTE(simpleApp, "/<string>")(stdhandler);
}