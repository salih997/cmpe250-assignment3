/*
Student Name:Salih Bedirhan EKER
Student Number:2017400030
Project Number: 3
Compile Status: [SUCCESS/FAIL]
Running Status: [SUCCESS/FAIL]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/
#include "SeatOperations.h"

using namespace std;

SeatOperations::SeatOperations(int N, int M){
    // IMPLEMENT ME!
    this->N=N;
    this->M=M;
    lines[0].resize(N);
    lines[1].resize(M);
}

void SeatOperations::collisionResolution(Person* getUpPtr){     //// decides which type of collision occured
        if((*getUpPtr).type == 1)
            collision1(getUpPtr);
        else if((*getUpPtr).type == 2)
            collision2(getUpPtr);
        else
            collision3(getUpPtr);
}

void SeatOperations::collision1(Person* person){                //// find a seat and put it type 1 person

    if(person->currLine == 0){
        int seat = ((person->seatNumber)+M-1)%M;
        if(lines[1][seat] == nullptr){
            person->currLine = 1;
            person->currSeatIndex = seat;
            lines[1][seat] = person;
            return;
        }else{
            Person* getUpPtr = lines[1][seat];
            person->currLine = 1;
            person->currSeatIndex = seat;
            lines[1][seat] = person;
            collisionResolution(getUpPtr);
        }
    }else {
        int seat = ((person->seatNumber)+N-1)%N;
        if(lines[0][seat] == nullptr){
            person->currLine = 0;
            person->currSeatIndex = seat;
            lines[0][seat] = person;
            return;
        }else{
            Person* getUpPtr = lines[0][seat];
            person->currLine = 0;
            person->currSeatIndex = seat;
            lines[0][seat] = person;
            collisionResolution(getUpPtr);
        }
    }
}

void SeatOperations::collision2(Person* person){                    //// find a seat and put it type 2 person

    if(person->currLine == 0){
        if(person->currSeatIndex < N-1){
            if(lines[0][person->currSeatIndex+1] == nullptr){
                person->currSeatIndex++;
                lines[0][person->currSeatIndex] = person;
                return;
            }else{
                Person* getUpPtr = lines[0][person->currSeatIndex+1];
                person->currSeatIndex++;
                lines[0][person->currSeatIndex] = person;
                collisionResolution(getUpPtr);
            }
        }else if(person->currSeatIndex = N-1){
            if(lines[1][0] == nullptr){
                person->currSeatIndex = 0;
                person->currLine = 1;
                lines[1][0] = person;
                return;
            }else {
                Person* getUpPtr = lines[1][0];
                person->currSeatIndex = 0;
                person->currLine = 1;
                lines[1][0] = person;
                collisionResolution(getUpPtr);
            }
        }
    }else{
        if(person->currSeatIndex < M-1){
            if(lines[1][person->currSeatIndex+1] == nullptr){
                person->currSeatIndex++;
                lines[1][person->currSeatIndex] = person;
                return;
            }else{
                Person* getUpPtr = lines[1][person->currSeatIndex+1];
                person->currSeatIndex++;
                lines[1][person->currSeatIndex] = person;
                collisionResolution(getUpPtr);
            }
        }else if(person->currSeatIndex = M-1){
            if(lines[0][0] == nullptr){
                person->currSeatIndex = 0;
                person->currLine = 0;
                lines[0][0] = person;
                return;
            }else {
                Person* getUpPtr = lines[0][0];
                person->currSeatIndex = 0;
                person->currLine = 0;
                lines[0][0] = person;
                collisionResolution(getUpPtr);
            }
        }
    }
}




void SeatOperations::collision3(Person* person){                                    //// find a seat and put it type 3 person

    int newSeatIndex = (person->currSeatIndex+((person->type3LastOperation)*2)+1)%(M+N);

    if(person->currLine == 0){
        if(newSeatIndex < N){
            if(lines[0][newSeatIndex] == nullptr){
                person->type3LastOperation++;
                person->currSeatIndex = newSeatIndex;
                lines[0][newSeatIndex] = person;
                return;
            }else{

                Person* getUpPtr = lines[0][newSeatIndex];
                person->type3LastOperation++;
                person->currSeatIndex = newSeatIndex;
                lines[0][newSeatIndex] = person;
                collisionResolution(getUpPtr);
            }
        }else{
            int otherLineSeatIndex = newSeatIndex-N;
            if(lines[1][otherLineSeatIndex] == nullptr){
                person->type3LastOperation++;
                person->currSeatIndex = otherLineSeatIndex;
                person->currLine = 1;
                lines[1][otherLineSeatIndex] = person;
                return;
            }else{
                Person* getUpPtr = lines[1][otherLineSeatIndex];
                person->type3LastOperation++;
                person->currSeatIndex = otherLineSeatIndex;
                person->currLine = 1;
                lines[1][otherLineSeatIndex] = person;
                collisionResolution(getUpPtr);
            }
        }
    }else{
        if(newSeatIndex < M){
            if(lines[1][newSeatIndex] == nullptr){
                person->type3LastOperation++;
                person->currSeatIndex = newSeatIndex;
                lines[1][newSeatIndex] = person;
                return;
            }else{

                Person* getUpPtr = lines[1][newSeatIndex];
                person->type3LastOperation++;
                person->currSeatIndex = newSeatIndex;
                lines[1][newSeatIndex] = person;
                collisionResolution(getUpPtr);
            }
        }else{
            int otherLineSeatIndex = newSeatIndex-M;
            if(lines[0][otherLineSeatIndex] == nullptr){
                person->type3LastOperation++;
                person->currSeatIndex = otherLineSeatIndex;
                person->currLine = 0;
                lines[0][otherLineSeatIndex] = person;
                return;
            }else{
                Person* getUpPtr = lines[0][otherLineSeatIndex];
                person->type3LastOperation++;
                person->currSeatIndex = otherLineSeatIndex;
                person->currLine = 0;
                lines[0][otherLineSeatIndex] = person;
                collisionResolution(getUpPtr);
            }
        }
    }

}


void SeatOperations::addNewPerson(int personType, const string& ticketInfo){            //// adds new person
    // IMPLEMENT ME!
    Person* person  = new Person();
    person->type = personType;

    char line =  ticketInfo[0];

    if(line == 'A') {
        person->line = 0;
        person->currLine = 0;
    }
    else{
        person->line = 1;
        person->currLine = 1;
    }


    person->seatNumber = stoi(ticketInfo.substr(1,ticketInfo.size()));

    if(person->line == 0){
        int seat = ((person->seatNumber)+N-1)%N;
        if(lines[0][seat] == nullptr){
            person->currSeatIndex = seat;
            lines[0][seat] = person;
            return;
        }else{
            Person* getUpPtr = lines[0][seat];
            person->currSeatIndex = seat;
            lines[0][seat] = person;
            collisionResolution(getUpPtr);
        }
    }else if(person->line == 1) {
        int seat = ((person->seatNumber)+M-1)%M;
        if(lines[1][seat] == nullptr){
            person->currSeatIndex = seat;
            lines[1][seat] = person;
            return;
        }else{
            Person* getUpPtr = lines[1][seat];
            person->currSeatIndex = seat;
            lines[1][seat] = person;
            collisionResolution(getUpPtr);

        }
    }

}

void SeatOperations::printAllSeats(ofstream& outFile){                      //// prints the output to the file
    // IMPLEMENT ME!
    for(int i=0; i<N; i++) {
        string write;
        if(lines[0][i] == nullptr)
            outFile << 0 << endl;
        else{
            if(lines[0][i]->line == 0)
                write = "A";
            else
                write = "B";

            outFile << lines[0][i]->type << " " << write << lines[0][i]->seatNumber << endl;
        }
    }
    for(int i=0; i<M; i++) {
        string write;
        if(lines[1][i] == nullptr)
            outFile << 0 << endl;
        else{
            if(lines[1][i]->line == 0)
                write = "A";
            else
                write = "B";

            outFile << lines[1][i]->type << " " << write << lines[1][i]->seatNumber << endl;
        }
    }
}

// YOU CAN ADD YOUR HELPER FUNCTIONS
