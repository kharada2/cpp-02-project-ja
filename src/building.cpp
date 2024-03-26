#include "building.hpp"

#include <iostream>

Building::Building() {}

std::vector<Passenger*> Building::getPassengers() { return passengers; }

std::vector<Elevator*> Building::getElevators() { return elevators; }

void Building::addElevator(Elevator* elevator) { elevators.push_back(elevator); }

void Building::addPassengers(Passenger* passenger) { passengers.push_back(passenger); }

Passenger* Building::getPassengersById(int id) {
  for (Passenger* i : passengers) {
    if (i->getId() == id) {
      return i;
    }
  }
  return nullptr;  // Passenger with given ID not found
}

void Building::runElevator(int time) {
  for (auto elevator : elevators) {
    // エレベータ稼働
    elevator->move();

    // 乗客が押した階についたので、エレベータから降りる
    dropPassenger(elevator, time);

    // 乗客が待つ階についたので、乗客がエレベータに乗る
    ridePassenger(elevator, time);

    // エレベータを呼ぶ
    callElevator(elevator, time);
  }
}

void Building::callElevator(Elevator* elevator, int time) {
  // std::cout << "DEBUG" << std::endl;
  // std::cout << passengers[0]->getIsBoarded() << " " << passengers[0]->getIsCalled() << " "
  //           << *passengers[0]->getCallTimeTop() << std::endl;
  for (auto passenger : passengers) {
    if (!passenger->getIsBoarded() && !passenger->getIsCalled() && passenger->getCallTimeTop() != nullptr &&
        *passenger->getCallTimeTop() >= time) {
      elevator->setCallFloor(passenger->getStartFloorTop());

      passenger->changeCalledState(true);
    }
  }
}

void Building::ridePassenger(Elevator* elevator, int time) {
  for (auto passenger : passengers) {
    if (!passenger->getIsBoarded() &&                                                                          //
        passenger->getStartFloorTop() != nullptr && *passenger->getStartFloorTop() == elevator->getFloor() &&  //
        passenger->getCallTimeTop() != nullptr && *passenger->getCallTimeTop() <= time) {
      elevator->addPassenger(passenger);
      elevator->setDestFloor(passenger->getEndFloorTop());
      elevator->removeCallFloor();

      passenger->changeBoardedState(true);
      passenger->changeCalledState(false);
      passenger->removeCallTime();
      passenger->removeStartFloor();
    }
  }
}

void Building::dropPassenger(Elevator* elevator, int time) {
  for (auto passenger : passengers) {
    if (passenger->getIsBoarded() && passenger->getEndFloorTop() != nullptr &&
        *passenger->getEndFloorTop() == elevator->getFloor()) {
      elevator->removePassenger(passenger);
      elevator->removeDestFloor();

      passenger->changeBoardedState(false);
      passenger->removeEndFloor();
    }
  }
}

void Building::printStatus() {
  for (auto elevator : elevators) {
    std::cout << "elevator[" << elevator->getId() << "]:";
    std::cout << "Floor:" << elevator->getFloor() << ", ";
    std::cout << "Passengers:";
    for (auto passenger : elevator->getPassengers()) {
      std::cout << passenger->getId() << " ";
    }
    std::cout << std::endl;
  }
}