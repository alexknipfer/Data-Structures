#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

struct NodeType
{
  string firstName;
  string lastName;
  string address;
  string city;
  string state;
  string zipCode;
  
  NodeType *next;
};

class LinkedListClass
{
  public:
  LinkedListClass();
    void InsertCustomer(NodeType, ofstream &);
    void DeleteCustomer(ifstream &, ofstream &);
    void ChangeCustomer(ifstream &, ofstream &);
    void InsertAsFirstElement(NodeType);
    void PrintMailingList(ofstream &);
    bool isEmpty();

  private:
    NodeType *head;
    NodeType *last;
    NodeType *current;
};

//******************************************************************************

int main()
{
  NodeType Temp, Node;
  
    //instantiate object for customer
  LinkedListClass LinkedList;
  
  ifstream inputFile("data.txt");
  ofstream outputFile("output.txt");
  
  
    //add, delete, change, or print records
  char transactionType;
  
    //done reading data from file once Q is hit
  char done = 'Q';
  
    //read in first character to figure out what to do with data
  inputFile >> transactionType;
  
    //continue reading in data until a "Q" is read in
  while(transactionType != done)
  {
      //check to see what to do with customer data
    switch(transactionType)
    {
        //add customer if transaction type is A
      case 'A':   inputFile >> ws;
                  getline(inputFile, Node.firstName);
                  inputFile >> ws;
                  getline(inputFile, Node.lastName);
                  inputFile >> ws;
                  getline(inputFile, Node.address);
                  inputFile >> ws;
                  getline(inputFile, Node.city);
                  inputFile >> ws;
                  getline(inputFile, Node.state);
                  inputFile >> ws;
                  getline(inputFile, Node.zipCode);
                  LinkedList.InsertCustomer(Node, outputFile);
                  break;
                  
      case 'D':   LinkedList.DeleteCustomer(inputFile, outputFile);
                  break;
                  
      case 'P':   LinkedList.PrintMailingList(outputFile);
                  break;
                  
      case 'C':   LinkedList.ChangeCustomer(inputFile, outputFile);
                  break;
    }
    
      //read in next transaction type
    inputFile >> transactionType;
  }
}

//******************************************************************************

LinkedListClass::LinkedListClass()
{
  head = NULL;
  last = NULL;
}

//******************************************************************************

bool LinkedListClass::isEmpty()
{
  if(head == NULL)
  {
    return true;
  }
  
  else
  {
    return false;
  }
}

//******************************************************************************

void LinkedListClass::InsertAsFirstElement(NodeType Node)
{
  NodeType *temp = new(NodeType);
  temp -> firstName = Node.firstName;
  temp -> lastName = Node.lastName;
  temp -> address = Node.address;
  temp -> city = Node.city;
  temp -> state = Node.state;
  temp -> zipCode = Node.zipCode;
  temp -> next = NULL;
  head = temp;
  last = temp;
}

//******************************************************************************

void LinkedListClass::InsertCustomer(NodeType Node, ofstream &outputFile)
{
  current = head;
  string tempFirst;
  string tempLast;
  string tempAddress;
  string tempCity;
  string tempState;
  string tempZip;
  
   if(isEmpty())
   {
     InsertAsFirstElement(Node);
   }
   
   else
   {
      NodeType *temp = new(NodeType);
      
      temp -> firstName = Node.firstName;
      temp -> lastName = Node.lastName;
      temp -> address = Node.address;
      temp -> city = Node.city;
      temp -> state = Node.state;
      temp -> zipCode = Node.zipCode;
      
      while (current != NULL)
      {
        if((temp -> firstName == current -> firstName) && (temp -> lastName == current -> lastName))
            {
              outputFile << temp -> firstName << " " << temp -> lastName << " ";
              outputFile << "is already in the list. Attempt to add duplicate record failed!";
              outputFile << endl;
              outputFile << endl;
              temp -> firstName = "DELETED";
            }
        
        current = current -> next;
      }
      
      current = head;
      
      
     while(current != NULL)
      {
          if(temp->lastName < current->lastName)
            {
                    //Swap first names.
                tempFirst = current->firstName;
                current->firstName = temp->firstName;
                temp->firstName = tempFirst;
                
                tempLast = current->lastName;
                current->lastName = temp->lastName;
                temp->lastName = tempLast;
                
                tempAddress = current->address;
                current->address = temp->address;
                temp->address = tempAddress;
                
                tempCity = current->city;
                current->city = temp->city;
                temp->city = tempCity;
                
                tempState = current->state;
                current->state = temp->state;
                temp->state = tempState;
                
                tempZip = current->zipCode;
                current->zipCode = temp->zipCode;
                temp->zipCode = tempZip;
            }
            
            current = current -> next;
      }
      
            
      temp -> next = NULL;
      last -> next = temp;
      last = temp;
   }
}

//******************************************************************************
void LinkedListClass::DeleteCustomer(ifstream &inputFile, ofstream &outputFile)
{
  if(isEmpty())
  {
    cout << "The database is empty" << endl;
  }
  
  else
  {
    string first;
    string last;
    bool found = false;
    
    NodeType *temp, *prev, *curr, *Node;
    
    //Node = head;
    
    temp = head;
    
    inputFile >> ws;
    getline(inputFile, first);
    inputFile >> ws;
    getline(inputFile, last);

    
    while(temp != NULL)
    {
      if(temp -> firstName == first && temp -> lastName == last)
      {
        temp -> firstName = "DELETED";
        found = true;
      }
      temp = temp -> next;
    }
    
    if(found == false)
    {
      outputFile << "Record of " << first << last;
      outputFile << " not found. Attempt to delete record failed!" << endl;
      outputFile << endl;
    }
    
    /*if(Node -> firstName == first && Node -> lastName == last)
    {
      temp = head;
      head = head -> next;
      delete(temp);
    }
    
    else
    {
      prev = head;
      curr = head -> next;
      
      while((curr != NULL) && (curr -> firstName != first && curr -> lastName != last))
      {
        prev = curr;
        curr = curr -> next;
      }
      
      outputFile << "Record of " << prev -> firstName << prev -> lastName;
      outputFile << " not found. Attempt to delete record failed!" << endl;
      outputFile << endl;
      
      if(curr != NULL)
      {
        temp = curr;
        prev -> next = curr -> next;
        
        delete(temp);
      }
    }*/
  }
}
//******************************************************************************
void LinkedListClass::ChangeCustomer(ifstream &inputFile, ofstream &outputFile)
{
  string first;
  string last;
  string newInfo;
  int fieldNumber;
  
  current = head;
  
  inputFile >> ws;
  getline(inputFile, first);
  inputFile >> ws;
  getline(inputFile, last);
  inputFile >> fieldNumber;
  inputFile >> ws;
  getline(inputFile, newInfo);
  
  
  while(current != NULL)
  {
    if(current -> firstName == "DELETED" && current -> firstName == first)
    {
      outputFile << "attempt to change invalid customer" << endl;
      break;
    }
    
    else if((current -> firstName == first) && (current -> lastName == last))
    {
      cout << "HELLO" << endl;
      switch(fieldNumber)
      {
        case 1: current -> firstName = newInfo;
                break;
        case 2: current -> lastName = newInfo;
                break;
        case 3: current -> address = newInfo;
                break;
        case 4: current -> city = newInfo;
                break;
        case 5: current -> state = newInfo;
                break;
        case 6: current -> zipCode = newInfo;
                break;
      }
      break;
    }
    
    current = current -> next;
  }
}

//******************************************************************************

void LinkedListClass::PrintMailingList(ofstream &outputFile)
{
  current = head;

  if(isEmpty())
  {
    cout << "The database is empty!" << endl;
  }
  
  else
  {
    
    
    //Print a heading for the mailing list table.
    outputFile << setw(50) << "MAILING LIST" << endl;
    outputFile << "Last Name" << "       ";
    outputFile << "First Name" << "       ";
    outputFile << "Address" << "                ";
    outputFile << "City" << "        ";
    outputFile << "State" << "     ";
    outputFile << "Zip Code" << endl;
    outputFile << "==============================================";
    outputFile << "============================================" << endl;
    
    
    while(current != NULL)
    {
      if(current -> firstName != "DELETED")
      {
        outputFile << left << setw(16) << current -> lastName;
        outputFile << left << setw(17) << current -> firstName;
        outputFile << left << setw(23) << current -> address;
        outputFile << left << setw(13) << current -> city;
        outputFile << left << setw(11) << current -> state;
        outputFile << current -> zipCode;
        outputFile << endl;
      }
      current = current -> next;
    }
    
    for(int x = 0; x < 3; x++)
    {
      outputFile << endl;
    }
  }
}


