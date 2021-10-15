#include <iostream>
#include "Visitor.h"

using namespace std;



Visitor::Visitor() :floor(0), office(0), id(0), counterOfVisitor(0), currentPositionOfVisitor(-1), statusOfService(0)
{

}

Visitor::~Visitor()
{

}

void Visitor::setFloor(int fl) {
	Visitor::floor = fl;
}
void Visitor::setOffice(int of) {
	Visitor::office = of;
}
int Visitor::getFloor() {
	return Visitor::floor;
}
int Visitor::getOffice() {
	return Visitor::office;
}
void Visitor::setId(int ID)
{
	Visitor::id = ID;
}

int Visitor::getId()
{
	return Visitor::id;
}

void Visitor::setCounterOfVisitor(int num)
{
	Visitor::counterOfVisitor = num;
}

int Visitor::getCounterOfVisitor()
{
	return Visitor::counterOfVisitor;
}

void Visitor::setCurrentPositionOfVisitor(int pos)
{
	Visitor::currentPositionOfVisitor = pos;
}

int Visitor::getCurrentPositionOfVisitor()
{
	return Visitor::currentPositionOfVisitor;
}

void Visitor::setStatusOfService(int stat)
{
	Visitor::statusOfService = stat;
}

int Visitor::getStatusOfService()
{
	return Visitor::statusOfService;
}


