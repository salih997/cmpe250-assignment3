#ifndef CMPE250_ASSIGNMENT3_SEATOPERATIONS_H
#define CMPE250_ASSIGNMENT3_SEATOPERATIONS_H
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Person{
    int type=0;
    int line=0, seatNumber=0;

    int type3LastOperation=0;

    int currSeatIndex=0;
    int currLine=0;
};

class SeatOperations{

private:
    vector<Person*> lines[2];
    int N, M;



public:
    SeatOperations(int N, int M);
    void addNewPerson(int personType, const string& ticketInfo);
    void printAllSeats(ofstream& outFile);


    void collisionResolution(Person* person);
    void collision1(Person* person);
    void collision2(Person* person);
    void collision3(Person* person);
    // YOU CAN ADD YOUR HELPER FUNCTIONS

};

#endif //CMPE250_ASSIGNMENT3_SEATOPERATIONS_H
