#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Building.h"

using namespace std;

int main(int argc, char *argv[]) {
	srand((unsigned int)time(NULL));
	if (argc < 8) {                     //Check if all args are given
		cout << "Missing Arguments" << endl;
		return 1;
	}

	int Npersons = 0, Nfloors = 0, Nground = 0, Noffice = 0, Nlift = 0, Kvisitors = 0, Lrounds = 0;
	int randomfloor = 0,randomOffice=0;
	int person, round = 0;
	Visitor *personArray = NULL;
	
	Npersons = atoi(argv[1]);  //Capacity of building
	Nfloors = atoi(argv[2]);   //Capacity of each floor
	Nground = atoi(argv[3]);   //Capacity of ground
	Noffice = atoi(argv[4]);   //Capacity of each office
	Nlift = atoi(argv[5]);     //Capacity of lift 
	Kvisitors = atoi(argv[6]); // K Visitors
	Lrounds = atoi(argv[7]);   //L rounds of lift 
	
	Building building(Npersons, Nfloors, Nground, Noffice, Nlift);

	personArray = new Visitor[Kvisitors];
	for (int person = 0; person < Kvisitors; person++) {
		personArray[person].setCounterOfVisitor(person + 1);
		randomfloor = rand() % 4 + 1;
		randomOffice = rand() % 10 + 1;
		personArray[person].setFloor(randomfloor);
		personArray[person].setOffice(randomOffice);
		cout << "No: " << personArray[person].getCounterOfVisitor() << " Dest floor: " << personArray[person].getFloor() << " Dest off: " << personArray[person].getOffice() << endl;
	}

	person = 0;
	for (round = 1; round <= Lrounds; round++)
	{
		for (; person < Kvisitors; person++) {
			if (building.enter() == 0) {						//Success to enter at Building
				if (building.enterAtGroundEntrance() == 0) {			//Success to enter At Ground entrance
					personArray[person].setCurrentPositionOfVisitor(0);
					building.enterAtWaitingArea();
					personArray[person].setCurrentPositionOfVisitor(1);
					building.waitTheLift(personArray[person], person + 1);		//Wait and take id
					if (building.checkLiftSpace(personArray[person]) == 0) {   //Success to enter at lift
						building.enterAtLift(personArray[person]);
						personArray[person].setCurrentPositionOfVisitor(2);
						building.exitAtWaitingArea(personArray[person]);
						building.exitAtGroundEntrance(personArray[person]);
					}
					else {		//Visitor wait till the lift comes again	
						personArray[person].setCurrentPositionOfVisitor(1);
						break;
					}
				}
				else {				//Wait someone to finish
					personArray[person].setCurrentPositionOfVisitor(-1);
					break;
				}
			}
			else {				//Visitor cannot enter to building
				personArray[person].setCurrentPositionOfVisitor(-1);
				break;
			}

		}
		building.operate(personArray, Kvisitors);
		/*-------------------Its time to go ------------------------------*/
		for (int i = 0; i < Kvisitors; i++) {
			if (personArray[i].getCurrentPositionOfVisitor() == 0 && personArray[i].getStatusOfService() == 1) {
				building.exit(personArray[i]);
				personArray[i].setCurrentPositionOfVisitor(-1);
			}
		}
	}





	for (int i = 0; i < Kvisitors; i++) {
		cout << "Visitor with id " << personArray[i].getId() << " has position and status " << personArray[i].getCurrentPositionOfVisitor() << " " << personArray[i].getStatusOfService() << endl;
	}
	delete	[]personArray;
	return 0;
}