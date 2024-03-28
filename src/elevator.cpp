#include "elevator.hpp"

#include <algorithm>
#include <iostream>

Elevator::Elevator(int maxFloor, int maxLoad, int id)
    : maxFloor(maxFloor), maxLoad(maxLoad), id(id), floor(0), currentLoad(0), state(Stop){};

void Elevator::addPassenger(Passenger* passenger) {
  // Boarded状態の変更
  passenger->changeBoardedState(true);

  // 乗客の追加
  passengers.push_back(passenger);
  // 最大積算重量のチェック
  currentLoad += passenger->getWeight();
};

void Elevator::removePassenger(Passenger* passenger) {
  int passengerID = passenger->getId();
  // if (!passengers.empty()) {
  //   auto it = std::find(passengers.begin(), passengers.end(), passenger);
  //   // if (it != passengers.end()) {
  //   //   passengers.erase(it);
  //   //   // currentLoad -= itgetWeight();
  //   // }
  //   passengers.erase(it);
  // }

  // IDで削除
  auto it = std::find_if(passengers.begin(), passengers.end(),
                         [passengerID](const auto p) { return p->getId() == passengerID; });

  if (it != passengers.end()) {
    passengers.erase(it);
    currentLoad -= passenger->getWeight();
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

void Elevator::setCalledPassengers(int id) { calledPassengers.push_back(id); }
void Elevator::printInfo() {
  std::cout << "maxLoad is: " << maxLoad << std::endl;
  std::cout << "maxFloor is: " << maxFloor << std::endl;
}

void Elevator::move() {
  if (!destFloors.empty() && floor < *destFloors.begin()) {
    floor++;
    state = Up;
  } else if (!destFloors.empty() && floor > *destFloors.begin()) {
    floor--;
    state = Down;
  } else if (!calledFloors.empty() && floor < *calledFloors.begin()) {
    floor++;
    state = Up;
  } else if (!calledFloors.empty() && floor > *calledFloors.begin()) {
    floor--;
    state = Down;
  } else {
    state = Stop;
  }
}

int Elevator::getFloor() { return floor; }

void Elevator::printCallFloor() {
  std::cout << "printCallFloor:";
  if (!calledFloors.empty()) {
    for (auto i : calledFloors) {
      std::cout << i << " ";
    }
  }
  std::cout << std::endl;
}

void Elevator::printDestFloor() {
  std::cout << "printDestFloor:";
  if (!destFloors.empty()) {
    for (auto i : destFloors) {
      std::cout << i << " ";
    }
  }
  std::cout << std::endl;
}

void Elevator::removeDestFloor() {
  if (!destFloors.empty()) {
    auto it = std::find(destFloors.begin(), destFloors.end(), floor);
    if (it != destFloors.end()) {
      destFloors.erase(it);
    }
  }
}

void Elevator::removeCallFloor() {
  if (!calledFloors.empty()) {
    auto it = std::find(calledFloors.begin(), calledFloors.end(), floor);
    if (it != calledFloors.end()) {
      calledFloors.erase(it);
    }
  }
}

void Elevator::removeCalledPassengers(int id) {
  if (!calledPassengers.empty()) {
    auto it = std::find(calledPassengers.begin(), calledPassengers.end(), id);
    if (it != calledPassengers.end()) {
      calledPassengers.erase(it);
    }
  }
}

int Elevator::getId() { return id; }

std::vector<Passenger*> Elevator::getPassengers() const { return passengers; }

State Elevator::getState() { return state; }

std::string Elevator::enumToString(State state) {
  if (auto it = stateMap.find(state); it != stateMap.end()) {
    return it->second;
  } else {
    return "Unknown";
  }
}

int* Elevator::getCalledFloor() {
  if (calledFloors.size() != 0) {
    return &calledFloors[0];
  }
  return nullptr;
}

int Elevator::getMaxFloor() { return maxFloor; }

int Elevator::getMaxLoad() { return maxLoad; }
int Elevator::getCurrentLoad() { return currentLoad; }
