#ifndef CALCLIST_H
#define CALCLIST_H

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include "CalcListInterface.hpp"

// Class of a circularly linked list
class CalcNode {
        /*class of a circular list node*/
        friend class CalcList;
        CalcNode* next;
        FUNCTIONS nodeOperator;
        double nodeOperand;
        double nodeTotal;
};

class CalcList : public CalcListInterface{
private:
        CalcNode* current; // Tracker for the current node in the circularly linked list
protected:
        int counter = 0; // Counter for the number of operations completed
        void addNode(const double& rTotal); // Adds a node BEFORE current
        void removeNode(); // Removes the node AFTER current
        
public:
        // Constructor and destructor
        CalcList();
        ~CalcList();

        // Helper function to check if the linked list is empty or not
        bool isEmpty() const { return (counter == 0);}
        
        double total() const;
        void newOperation(const FUNCTIONS func, const double operand); 
        void removeLastOperation();
        std::string toString(unsigned short precision) const;
};

#endif