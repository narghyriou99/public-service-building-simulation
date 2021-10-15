#include "Visitor.h"

class Space {
private:
protected:
	int Max;
	int visitorsNow;
public:
	virtual void setVisitorsNow(int n)=0;
	virtual int  getVisitorsNow()=0;
	virtual int  getMax()=0;
	virtual int  enter()=0;
	virtual void exit(Visitor &visitor)=0;
	virtual void operate(Visitor *&visitor, int Kvisitors) {}
	virtual int checkLiftSpace(Visitor &visitor) { return 0; }
	virtual int getOffice() { return 0; }
	virtual void waitForTheLift(Visitor &visitor, int id){}
	virtual int enterAtWaitingArea() { return 0; }
	virtual void exitAtWaitingArea(Visitor &visitor){}
	virtual int getNof(int cell) { return 0; }
	virtual int getVisitorsNowOfOffice(int cell) { return 0; }
	virtual int getNumOfOffice(int cell) { return 0; }
	virtual void enterAtOfice(int cell){}
	virtual void exitAtOffice(int cell, Visitor &visitor){}
	virtual void enterAtWaitArea(){}
	virtual void exitAtWaitArea(Visitor &visitor){}
	virtual int getNumberOfFloor() { return 0; }
	Space();
	virtual ~Space();
};


class WaitingArea:public Space {

public:
	WaitingArea();
	~WaitingArea();

	void  setVisitorsNow(int n);
	int getVisitorsNow();
	/*------------------------------------------------------------------*/
	int enter();
	void exit(Visitor &visitor);
	int getMax() { return 0; }
	
};



class Office :public Space {
private:
	int office; // 1-10
public:
	Office(int No, int num);
	~Office();

	int getMax();
	void setVisitorsNow(int n);
	int getVisitorsNow();
	int getOffice();
	int enter();
	void exit(Visitor &visitor);

};

class Floor :public Space {
private:
	int numberOfFloor;  //1-4
	Space *office[10];  //Array with 10 offices
	Space *waitingAreaOfFloor;  //Wait Area

	
public:
	Floor(int Nf, int numOfFloor, int No);
	~Floor(); //Destructor

	int getMax();
	void setVisitorsNow(int n);
	int getVisitorsNow();
	void setNumberOfFloor(int f);
	int getNumberOfFloor();
	int enter();
	void exit(Visitor &visitor);

	/*----------------From Class Office---------------------*/
	int getNof(int cell);
	int getVisitorsNowOfOffice(int cell);
	int getNumOfOffice(int cell);
	void enterAtOfice(int cell);
	void exitAtOffice(int cell,Visitor &visitor);

	/*----------------From Waiting Area---------------------*/
	void enterAtWaitArea();
	void exitAtWaitArea(Visitor &visitor);
};

class Lift :public Space {
private:
	int numberOfFloor;
	Space **floorAr;   //Αuxiliary ptr for access at Floor
public:
	Lift(int Nl, Space *&fl);
	~Lift();

	int getMax();
	void setVisitorsNow(int n);
	int getVisitorsNow();
	void setNumberOfFloor(int num);
	int  getNumberOfFloor();
	int enter();
	void exit(Visitor &visitor);

	int checkLiftSpace(Visitor &visitor);
	void operate(Visitor *&visitor, int Kvisitors);
	void stopUp(Visitor *&visitor, int Kvisitors);
	void checkWhoIsServiced(Visitor *&visitor, int Kvisitors);
	void stopDown(Visitor *&visitor, int Kvisitors);
	void emptyAll(Visitor *&visitor, int Kvisitors);
};

class GroundEntrance :public Space {
private:
	Space *waitingAreaofGround;

public:
	GroundEntrance(int Ng);
	~GroundEntrance();

	int getMax();
	void setVisitorsNow(int n);
	int getVisitorsNow();
	int enter();
	void exit(Visitor &visitor);

	void waitForTheLift(Visitor &visitor, int id);

	/*------------------From-Class-Waiting-Area---------------------*/
	int enterAtWaitingArea();
	void exitAtWaitingArea(Visitor &visitor);

};

class Building :public Space {
private:
	Space *floor[4];  //Array of 4 floors  (*floor)  *(floor[4])
	Space *entrance;
	Space *lift;
public:
	Building(int Npersons, int Nfloors, int Nground, int Noffice, int Nlift);	 //Constructor that takes  values
	~Building(); //Destructor
	
	int getMax();
	void setVisitorsNow(int n);
	int getVisitorsNow();
	int enter();
	void exit(Visitor &visitor);

	/*-----------------From-Class-Lift----------------------*/
	void operate(Visitor *&visitor, int Kvisitors);
	int  checkLiftSpace(Visitor &visitor);
	void enterAtLift(Visitor &visitor);

	/*----------------From-Class-Ground-Entrance---------------*/
	void waitTheLift(Visitor &visitor, int id);
	int enterAtGroundEntrance();
	void exitAtGroundEntrance(Visitor &visitor);

	int  enterAtWaitingArea();
	void exitAtWaitingArea(Visitor &visitor);
};

