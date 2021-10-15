class Visitor {
private:
	int floor;  //1-4
	int office; //1-10
	int id;     // Priority number of visitor
	int counterOfVisitor;
	int currentPositionOfVisitor;
	int statusOfService;  // 1 is ok--0 is not ok
public:
	Visitor();
	~Visitor();
	void setFloor(int fl);
	int getFloor();
	void setOffice(int of);
	int getOffice();
	void setId(int ID);
	int getId();
	void setCounterOfVisitor(int num);
	int getCounterOfVisitor();
	void setCurrentPositionOfVisitor(int pos);
	int  getCurrentPositionOfVisitor();
	void setStatusOfService(int stat);
	int  getStatusOfService();

};

/*-1->outside of building // 0->GroundEntrance // 1->WaitingAreaOfGround
   2->Lift // 3->DestinationFloor // 4->WaitingAreaOfDestinationFloor
   5->DestinationOffice */
