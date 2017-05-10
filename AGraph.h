//
// Created by mrfarinq on 10.05.17.
//

#pragma once

#include <iostream>

class AGraph {
    virtual void printGraph()=0;
    
    virtual void readFromFile(std::string path)=0;
    
    virtual void createGraphWithRandomIntegers(int numberOfElements)=0;
};

