#include <iostream>
#include <cstdlib>
#include "Building.h"

using namespace std;

/*------------------------CONSTRUCTORS-DESTRUCTORS------------------------------*/

Building::Building(int Npersons, int Nfloors, int Nground, int Noffice, int Nlift) {
	Max = Npersons;
	int counter = 0;
	for (counter = 0; counter < 4; counter++) {
		floor[counter] = new Floor(Nfloors, counter + 1, Noffice);
	}
	lift = new Lift(Nlift, *floor);
	entrance = new GroundEntrance(Nground);
	cout << "A new building is ready for serving citizens! " << endl;
}

Building::~Building() {
	int counter = 0;
	for (counter = 0; counter < 4; counter++) {
		delete floor[counter];
	}
	delete lift;
	delete entrance;
	cout << "Service not available any longer.Go elsewhere!" << endl;
}


/*-------------------------------------------------------------------------------*/

Floor::Floor(int Nf, int numOfFloor, int No) : numberOfFloor(numOfFloor) {
	Max = Nf;
	int counter = 0;
	waitingAreaOfFloor = new WaitingArea;
	for (counter = 0; counter < 10; counter++) {
		office[counter] = new Office(No, counter + 1);
	}
	cout << "A Floor has been created with number " << getNumberOfFloor() << endl;
}



Floor::~Floor() {
	int counter = 0;
	for (counter = 0; counter < 10; counter++) {
		delete office[counter];
	}
	delete waitingAreaOfFloor;
	cout << "End of service!" << endl;
}

/*-------------------------------------------------------------------------------*/

GroundEntrance::GroundEntrance(int Ng)  {
	Max = Ng;
	waitingAreaofGround = new WaitingArea;
	cout << "The entrance has been created!" << endl;
}

GroundEntrance::~GroundEntrance() {
	delete waitingAreaofGround;
	cout << "End of service(ground)!" << endl;
}

/*-------------------------------------------------------------------------------*/

Lift::Lift(int Nl, Space *&fl) : numberOfFloor(0) {
	floorAr = &fl;
	Max = Nl;

	cout << "A lift has been created " << endl;
}

Lift::~Lift() {
	cout << "No more ups and downs!" << endl;
}

/*-------------------------------------------------------------------------------*/

Office::Office(int No, int num): office(num) {
	Max = No;
	cout << "Office number " << getOffice() << " has been created" << endl;
}


Office::~Office() {
	cout << "End of the work!" << endl;
}
/*-------------------------------------------------------------------------------*/

WaitingArea::WaitingArea() {
	cout << "Create wait area" << endl;
}

WaitingArea::~WaitingArea() {
	cout << "Destroy wait area" << endl;

}

/*--------------------------------------------------------------------------------*/




Space::Space():Max(0),visitorsNow(0)
{
	cout<<"Creating new space..."<<endl;
}

Space::~Space()
{
	cout << "Destroying space..." << endl;
}



/*-------------------------------------------------------*/
void WaitingArea::setVisitorsNow(int n)
{
	visitorsNow = n;
}

int WaitingArea::getVisitorsNow()
{
	return visitorsNow;
}



int WaitingArea::enter()
{
	visitorsNow += 1;
	return 0;
}

void  WaitingArea::exit(Visitor &visitor)
{
	visitorsNow -= 1;
}
/*-------------------------------------------------------*/

int Office::getMax()
{
	return Max;
}
void Office::setVisitorsNow(int n)
{
	visitorsNow = n;
}
int Office::getVisitorsNow() {
	return visitorsNow;
}

int Office::getOffice() {
	return office;
}

int Office::enter()
{
	visitorsNow += 1;
	return 0;
}

void Office::exit(Visitor &visitor)
{
	visitorsNow -= 1;

}

/*-------------------------------------------------------*/


int Floor::getMax() {
	return Max;
}
void Floor::setVisitorsNow(int n) {
	visitorsNow = n;
}
int Floor::getVisitorsNow() {
	return visitorsNow;
}
void Floor::setNumberOfFloor(int f) {
	numberOfFloor = f;
}
int Floor::getNumberOfFloor() {
	return numberOfFloor;
}

int Floor::enter()
{
	visitorsNow += 1;
	return 0;
}

void Floor::exit(Visitor &visitor)
{
	visitorsNow -= 1;
}



/*-------------------------------------------------------*/

int Lift::getMax() {
	return Max;
}

void Lift::setVisitorsNow(int n) {
	visitorsNow = n;
}

int  Lift::getVisitorsNow() {
	return visitorsNow;
}

void Lift::setNumberOfFloor(int num)
{
	Lift::numberOfFloor = num;
}

int Lift::getNumberOfFloor()
{
	return Lift::numberOfFloor;
}

int Lift::enter() {
	visitorsNow += 1;
	return 0;
}

void Lift::exit(Visitor &visitor) {
	visitorsNow -= 1;
}

int Lift::checkLiftSpace(Visitor & visitor)
{
	if (getVisitorsNow() < getMax()) {
		cout << "Visitor in the lift with Id:" << visitor.getId() << endl;
		return 0;
	}
	else {
		cout << "You are not allowed to enter with Id:" << visitor.getId() << endl;
		return 1;
	}
}

void Lift::operate(Visitor *&visitor, int Kvisitors)
{
	stopUp(visitor, Kvisitors);
	checkWhoIsServiced(visitor, Kvisitors);
	stopDown(visitor, Kvisitors);
	emptyAll(visitor, Kvisitors);
}

int Floor::getNof(int cell)
{
	return Floor::office[cell]->getMax();
}

int Floor::getVisitorsNowOfOffice(int cell)
{
	return Floor::office[cell]->getVisitorsNow();
}

int Floor::getNumOfOffice(int cell)
{
	return Floor::office[cell]->getOffice();
}

void Floor::enterAtOfice(int cell)
{
	Floor::office[cell]->enter();
}

void Floor::exitAtOffice(int cell,Visitor &visitor)
{
	Floor::office[cell]->exit(visitor);
}

void Floor::enterAtWaitArea()
{
	Floor::waitingAreaOfFloor->enter();
}

void Floor::exitAtWaitArea(Visitor &visitor)
{
	Floor::waitingAreaOfFloor->exit(visitor);
}



void Lift::stopUp(Visitor *& visitor, int Kvisitors)
{
	int destinationFloor = 0, counter = 0, destinationOffice = 0, numOffice = 0;
	for (destinationFloor = 0; destinationFloor < 4; destinationFloor++) {
		for (counter = 0; counter < Kvisitors; counter++) {
			if ((visitor[counter].getCurrentPositionOfVisitor()) == 2 && visitor[counter].getStatusOfService() == 0) {   //Check if visitor is at lift and he is not serviced yet
				if ((visitor[counter].getFloor()) == destinationFloor + 1) {
					if (floorAr[destinationFloor]->getVisitorsNow() < floorAr[destinationFloor]->getMax()) {		//Success to go to dest Floor					
						visitor[counter].setCurrentPositionOfVisitor(3);	//Visitor is at destination floor
						exit(visitor[counter]);
						floorAr[destinationFloor]->enter();
						cout << "Entering floor " << floorAr[destinationFloor]->getNumberOfFloor() << " Id:" << visitor[counter].getId() << endl;
						for (destinationOffice = 0; destinationOffice < 10; destinationOffice++) {
							if (visitor[counter].getOffice() == destinationOffice + 1) {
								if (floorAr[destinationFloor]->getVisitorsNowOfOffice(destinationOffice) < floorAr[destinationFloor]->getNof(destinationOffice)) {		//Success to go to dest office
									visitor[counter].setCurrentPositionOfVisitor(5);	//Visitor is at destination office
									floorAr[destinationFloor]->enterAtOfice(destinationOffice);
									cout << "Entering office " << floorAr[destinationFloor]->getNumOfOffice(destinationOffice) << " Id:" << visitor[counter].getId() << endl;
									//cout << "Visitor with id " << visitor[counter].getId() << " was sent at floor " << floorAr[destinationFloor]->getNumberOfFloor() <<" and office "<<floorAr[destinationFloor]->getNumOfOffice(destinationOffice)<< endl;
								}
								else {
									cout << "Please, wait outside for entrance in office number " << floorAr[destinationFloor]->getNumOfOffice(destinationOffice) << " .Id:" << visitor[counter].getId() << endl;
									floorAr[destinationFloor]->enterAtWaitArea();
									visitor[counter].setCurrentPositionOfVisitor(4);   //Visitor is at Waiting Area of dest floor 
								}
							}
						}
					}
					else {
						cout << "Sorry,floor number " << getNumberOfFloor() << " is full.Id: " << visitor[counter].getId() << endl;
						visitor[counter].setCurrentPositionOfVisitor(2);			//Visitor stays in lift
					}
				}
			}
		}
		setNumberOfFloor(destinationFloor + 1);
	}

}

void Lift::checkWhoIsServiced(Visitor *& visitor, int Kvisitors)
{

	int counter = 0;
	for (counter = 0; counter < Kvisitors; counter++) {
		if (visitor[counter].getCurrentPositionOfVisitor() == 5) {
			visitor[counter].setStatusOfService(rand() % 2);
		}
	}
}

void Lift::stopDown(Visitor *& visitor, int Kvisitors)
{
	int floor = 0, office = 0, counter = 0, counter2 = 0, destinationOffice = 0;

	for (floor = 3; floor >= 0; floor--) {
		setNumberOfFloor(floor + 1);
		for (counter = 0; counter < Kvisitors; counter++) {
			for (counter2 = 0; counter2 < Kvisitors; counter2++) {		//Check if someone at waiting area can get in the lift
				if (visitor[counter2].getCurrentPositionOfVisitor() == 4 && visitor[counter2].getStatusOfService() == 1) {
					floorAr[floor]->exitAtWaitArea(visitor[counter2]);
					floorAr[floor]->exit(visitor[counter2]);
					enter();							//Enter to lift
					visitor[counter2].setCurrentPositionOfVisitor(2);
					cout << "Visitor with id " << visitor[counter2].getId() << " was at waiting Area,now entering lift" << endl;
				}
			}
			if (visitor[counter].getCurrentPositionOfVisitor() == 5 && visitor[counter].getStatusOfService() == 1) { //Check if visitor can enter lift
				if (getVisitorsNow() < getMax()) {
					floorAr[floor]->exitAtOffice(visitor[counter].getOffice() - 1,visitor[counter]);		//Exit from office
					floorAr[floor]->exit(visitor[counter]);					//Exit from floor
					for (int i = 0; i < Kvisitors; i++)
						if (visitor[i].getCurrentPositionOfVisitor() == 4 && visitor[i].getStatusOfService() == 0) {			//Visitor try to enter office
							for (destinationOffice = 0; destinationOffice < 10; destinationOffice++)
								if (visitor[counter].getOffice() == destinationOffice + 1) {
									if (floorAr[floor]->getVisitorsNowOfOffice(destinationOffice) < floorAr[floor]->getNof(destinationOffice)) {		//Success to go to dest office
										visitor[counter].setCurrentPositionOfVisitor(5);	//Visitor is at destination office
										floorAr[floor]->enterAtOfice(destinationOffice);
										cout << "Visitor with id " << visitor[counter].getId() << " was at waiting Area, now entering office " << floorAr[floor]->getNumOfOffice(destinationOffice) << " Id:" << visitor[counter].getId() << endl;
									}
								}
						}
					enter();							//Enter to lift
					visitor[counter].setCurrentPositionOfVisitor(2);
				}
				else {			//Visitor goes to waiting area 
					floorAr[floor]->enterAtWaitArea();
					visitor[counter].setCurrentPositionOfVisitor(4);
				}
			}
		}

	}
	setNumberOfFloor(0);		//Lift arrives to entrance

}

void Lift::emptyAll(Visitor *&visitor, int Kvisitors)
{
	int counter = 0;
	for (counter = 0; counter < Kvisitors; counter++) {
		if (visitor[counter].getCurrentPositionOfVisitor() == 2 && visitor[counter].getStatusOfService() == 1) {
			exit(visitor[counter]);
			visitor[counter].setCurrentPositionOfVisitor(0);  //Road to Ground entrance and exit 

		}
		else if (visitor[counter].getCurrentPositionOfVisitor() == 2 && visitor[counter].getStatusOfService() == 0) {
			visitor[counter].setCurrentPositionOfVisitor(2); //Stay at lift
		}
	}
}
/*-------------------------------------------------------*/

int GroundEntrance::getMax() {
	return Max;
}

void GroundEntrance::setVisitorsNow(int n) {
	visitorsNow = n;
}

int GroundEntrance::getVisitorsNow() {
	return visitorsNow;
}


int GroundEntrance::enter() {
	if (getVisitorsNow() < getMax()) {
		visitorsNow += 1;
		return 0;
	}
	else {
		return 1;
	}
}

void GroundEntrance::exit(Visitor &visitor) {
	visitorsNow -= 1;
}

void GroundEntrance::waitForTheLift(Visitor &visitor, int id)
{
	cout << "Waiting for the lift" << endl;
	visitor.setId(id);
}

int GroundEntrance::enterAtWaitingArea()
{
	return waitingAreaofGround->enter();
}

void GroundEntrance::exitAtWaitingArea(Visitor &visitor)
{
	waitingAreaofGround->exit(visitor);
}



/*-------------------------------------------------------*/

int Building::getMax() {
	return Max;
}

void Building::setVisitorsNow(int n) {
	visitorsNow = n;
}

int Building::getVisitorsNow() {
	return visitorsNow;
}

int Building::enter() {
	if (getVisitorsNow() <= getMax()) {
		visitorsNow += 1;
		return 0;
	}
	else {
		cout << "Please, come tomorrow" << endl;
		return 1;
	}
}

void Building::exit(Visitor &visitor) {
	visitorsNow -= 1;
	cout << "I cannot believe I finished! Id: " << visitor.getCounterOfVisitor() << endl;
}

void Building::operate(Visitor *& visitor, int Kvisitors)
{
	Building::lift->operate(visitor, Kvisitors);
}

int Building::checkLiftSpace(Visitor &visitor)
{
	return lift->checkLiftSpace(visitor);
}

void Building::enterAtLift(Visitor & visitor)
{
	Building::lift->enter();
}

void Building::waitTheLift(Visitor & visitor, int id)
{
	entrance->waitForTheLift(visitor, id);
}

int Building::enterAtGroundEntrance()
{
	return entrance->enter();
}

void Building::exitAtGroundEntrance(Visitor &visitor)
{
	entrance->exit(visitor);
}

int Building::enterAtWaitingArea()
{
	return entrance->enterAtWaitingArea();
}

void Building::exitAtWaitingArea(Visitor &visitor)
{
	entrance->exitAtWaitingArea(visitor);
}