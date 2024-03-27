#include "building.hpp"

#include <algorithm>
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
  for (auto passenger : passengers) {
    // エレベータを呼ぶ
    if (passenger->getStartFloorTop() != nullptr) {
      auto elevator = getNearestElevator(*passenger->getStartFloorTop());
      callElevator(elevator, passenger, time);
    }
  }

  for (auto elevator : elevators) {
    // エレベータ稼働
    elevator->move();

    // 乗客が待つ階についたので、乗客がエレベータに乗る
    ridePassenger(elevator, time);

    // 乗客が押した階についたので、エレベータから降りる
    dropPassenger(elevator, time);
  }
}

bool Building::checkContinue() {
  // 全ての乗客が行先に到着した
  bool returnVal{false};

  for (auto passenger : passengers) {
    if (passenger->getEndFloorTop() != nullptr) {
      std::cout << passenger->getId() << "," << *passenger->getEndFloorTop() << std::endl;
      returnVal = true;
    }
  }
  return returnVal;
}

void Building::callElevator(Elevator* elevator, Passenger* passenger, int time) {
  // std::cout << "DEBUG" << std::endl;
  // std::cout << passengers[0]->getIsBoarded() << " " << passengers[0]->getIsCalled() << " "
  //           << *passengers[0]->getCallTimeTop() << std::endl;
  if (!passenger->getIsBoarded() && !passenger->getIsCalled() && passenger->getCallTimeTop() != nullptr &&
      *passenger->getCallTimeTop() == time) {
    elevator->setCallFloor(passenger->getStartFloorTop());
    elevator->setCalledPassengers(passenger->getId());

    passenger->changeCalledState(true);
  }
}

void Building::ridePassenger(Elevator* elevator, int time) {
  for (auto passenger : passengers) {
    if (!passenger->getIsBoarded() &&  //
        passenger->getStartFloorTop() != nullptr && *passenger->getStartFloorTop() == elevator->getFloor() &&
        elevator->getCalledFloor() != nullptr && *elevator->getCalledFloor() == elevator->getFloor() &&  //
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
      elevator->removeCalledPassengers(passenger->getId());

      passenger->changeBoardedState(false);
      passenger->removeEndFloor();
    }
  }
}

void Building::printStatus() {
  for (auto elevator : elevators) {
    std::cout << "elevator[" << elevator->getId() << "]:";
    std::cout << "Floor:" << elevator->getFloor() << ", ";
    std::cout << "State:" << elevator->enumToString(elevator->getState()) << ", ";
    // elevator->printCallFloor();
    // elevator->printDestFloor();
    std::cout << "Passengers:";
    for (auto passenger : elevator->getPassengers()) {
      std::cout << passenger->getId() << " ";
    }
    std::cout << std::endl;
  }
}

Elevator* Building::getNearestElevator(int floor) {
  Elevator* nearest = nullptr;
  int minDistance = std::numeric_limits<int>::max();  // 最大値で初期化

  for (Elevator* elevator : elevators) {
    // エレベーターの目的の階を取得
    int currentFloor = elevator->getFloor();

    // 指定した階とエレベーターの目的の階との距離を計算
    int distance = std::abs(floor - currentFloor);

    // 最も近いエレベーターを更新
    if (distance < minDistance) {
      minDistance = distance;
      nearest = elevator;
    }
  }

  return nearest;
}