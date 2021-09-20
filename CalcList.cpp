#include "CalcList.hpp"

// Constructor
CalcList::CalcList() : CalcListInterface(){
        // Default values
        current = new CalcNode;
        current->nodeOperator = ADDITION;
        current->nodeOperand = 0.0;
        current->nodeTotal = 0.0;
        current->next = current;
}


// Destructor
CalcList::~CalcList(){
        while(!isEmpty()) removeNode();
}


// Add node
void CalcList::addNode(const double& rTotal){
        ++counter; // Increment the counter for number of operations
        CalcNode* temp = new CalcNode; // Create a temporary node which will get added at the beginning 

        temp->nodeOperator = ADDITION;
        temp->nodeOperand = 0.0;
        temp->nodeTotal = 0.0;
        temp->next = nullptr;

        // If the linked list is empty, make a node and set its next to itself
        if(current == nullptr){ 
                temp->nodeTotal = rTotal;
                current = temp;
                current->next = temp;
        }
        else{
                temp->next = current->next;
                temp->nodeTotal = current->next->nodeTotal;
                current->next = temp;
        }
}


// Remove node
void CalcList::removeNode(){ 
        if (isEmpty()) { throw ("No existing nodes, cannot remove."); }
        else {
                --counter; // Decrement operation counter
                CalcNode* old = current->next; // Store node to be removed in a temprory pointer object
                if (old == current) { current = nullptr; } // If node to be removed happens to be the current node, set to null
                else { 
                        current->next = old->next;  
                }
                delete old;
        }
}

// Return total
double CalcList::total() const{              
        return current->next->nodeTotal; // Gets the total from any node
}

// Adds operation to the CalcList and updates the total
void CalcList::newOperation(const FUNCTIONS func, const double operand){

        addNode(0); // Add a default node first
        
        switch(func){ // Update the newly added default node with operator, operand, and total
        case ADDITION:
                current->next->nodeOperator = ADDITION;
                current->next->nodeOperand = operand;
                current->next->nodeTotal += operand;
                break;
        case SUBTRACTION:
                current->next->nodeOperator = SUBTRACTION;
                current->next->nodeOperand = operand;
                current->next->nodeTotal -= operand;
                break;
        case MULTIPLICATION:
                current->next->nodeOperator = MULTIPLICATION;
                current->next->nodeOperand = operand;
                current->next->nodeTotal *= operand;
                break;
        case DIVISION: // Throw an error if divison is bad 
                if(operand >= 0 && operand < 1.00) { removeLastOperation(); throw("Divide by zero."); }
                else {
                        current->next->nodeOperator = DIVISION;
                        current->next->nodeOperand = operand;
                        current->next->nodeTotal /= operand;
                        break; 
                }
        default: // Throw if enum is missing 
                throw ("Bad arithmetic operation. Use Addition, Substraction, Multiplication, or Divison.");
                break;
        }
}


// Remove last node
void CalcList::removeLastOperation(){ 
        removeNode();
}


// Returns a string of the list of operations completed formatted with a fixed point precision
std::string CalcList::toString(unsigned short precision) const{
        
        std::stringstream ss; // Using stringstream to get the previous operation in the string buffer
        std::string nodeData = ""; // Store converted buffer data in this variable
        int step = counter; // Temprory variable that holds the number of operations to display
        CalcNode* nodePtr = new CalcNode; // Temprory variable that holds current->next data
        nodePtr = current->next;

        ss.precision(precision); // Sets precision
        
        // Format the string as instructed
        while(nodePtr->nodeTotal != 0){ 
                ss << step << ": "; 
                ss << std::fixed << nodePtr->next->nodeTotal; 

                if(nodePtr->nodeOperator == ADDITION){
                        ss << "+";
                }
                else if(nodePtr->nodeOperator == SUBTRACTION){
                        ss << "-";
                }
                else if(nodePtr->nodeOperator == MULTIPLICATION){
                        ss << "*";
                }
                else if(nodePtr->nodeOperator == DIVISION){
                        ss << "/";
                }

                ss << nodePtr->nodeOperand;
                ss << "=";
                ss << nodePtr->nodeTotal;
                ss << std::endl;
                
                nodePtr = nodePtr->next;
                --step;
        }

        // Convert string buffer to stream object and return
        nodeData = ss.str(); 
        return nodeData;
}
