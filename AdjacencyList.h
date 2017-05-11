//
// Created by mrfarinq on 10.05.17.
//

#pragma once


template<class T>
struct AdjacencyList {
    struct AdjacencyListNode {
        T vertex;
        T weight;
        AdjacencyListNode *next;
    };
    AdjacencyListNode *head;
};
