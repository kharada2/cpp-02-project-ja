#include "elevator.hpp"

#include <algorithm>
#include <iostream>

Elevator::Elevator(int maxFloor, int maxLoad, int id) : maxFloor(maxFloor), maxLoad(maxLoad), id(id), floor(0){};

void Elevator::addPassenger(Passenger* passenger) {
  // Boarded状態の変更
  passenger->changeBoardedState(true);
  // 乗客の追加
  passengers.push_back(passenger);
  // 最大積算重量のチェック
  currentLoad += passenger->getWeight();
};

void Elevator::removePassenger(Passenger* passenger) {
  if (!passengers.empty()) {
    auto it = std::find(passengers.begin(), passengers.end(), passenger);
    if (it != passengers.end()) {
      passengers.erase(it);
      // currentLoad -= itgetWeight();
    }
  }
}

void Elevator::setMaxLoad(int* maxLoad) {
  if (maxLoad != nullptr) {
    this->maxLoad = *maxLoad;
  }
}

void Elevator::setMaxFloor(int* maxFloor) {
  if (maxFloor != nullptr) {
    this->maxFloor = *maxFloor;
  }
}

void Elevator::setCallFloor(int* floor) {
  if (floor != nullptr) {
    calledFloors.push_back(*floor);
  }
}

void Elevator::setDestFloor(int* floor) {
  if (floor != nullptr) {
    destFloors.push_back(*floor);
  }
}

void Elevator::printInfo() {
  std::cout << "maxLoad is: " << maxLoad << std::endl;
  std::cout << "maxFloor is: " << maxFloor << std::endl;
}

void Elevator::move() {
  // 乗り降りがあったステップでは稼働させなくてもいいかも
  if (!destFloors.empty() && floor < *destFloors.begin()) {
    floor++;
  } else if (!destFloors.empty() && floor > *destFloors.begin()) {
    floor--;
  } else if (!calledFloors.empty() && floor < *calledFloors.begin()) {
    floor++;
  } else if (!calledFloors.empty() && floor > *calledFloors.begin()) {
    floor--;
  }
}

int Elevator::getFloor() { return floor; }

void Elevator::printCallFloor() {
  std::cout << "printCallFloor" << std::endl;
  if (!calledFloors.empty()) {
    for (auto i : calledFloors) {
      std::cout << i << std::endl;
    }
  }
}

void Elevator::printDestFloor() {
  std::cout << "printDestFloor" << std::endl;
  if (!destFloors.empty()) {
    for (auto i : destFloors) {
      std::cout << i << std::endl;
    }
  }
}

void Elevator::removeDestFloor() {
  if (!destFloors.empty()) {
    destFloors.erase(destFloors.begin());
  }
}

void Elevator::removeCallFloor() {
  if (!calledFloors.empty()) {
    calledFloors.erase(calledFloors.begin());
  }
}

int Elevator::getId() { return id; }

std::vector<Passenger*> Elevator::getPassengers() const { return passengers; }