#include "passenger.hpp"

#include <iostream>

Passenger::Passenger(int id, int weight) : id(id), weight(weight), isBoarded(false), isWaiting(false){};

int Passenger::getWeight() { return weight; }

void Passenger::printInfo() {
  std::cout << "id: " << id << ", ";
  std::cout << "weight: " << weight << ", ";

  std::cout << "callTime: ";
  for (auto i : callTime) {
    std::cout << i << " ";
  }
  std::cout << ", ";

  std::cout << "startFloor: ";
  for (auto i : startFloor) {
    std::cout << i << " ";
  }
  std::cout << ", ";

  std::cout << "endFloor: ";
  for (auto i : endFloor) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}

void Passenger::addCallInfo(int time, int pickUpFloor, int dropOffFloor) {
  callTime.push_back(time);
  startFloor.push_back(pickUpFloor);
  endFloor.push_back(dropOffFloor);
}

void Passenger::changeBoardedState(bool isBoarded) { this->isBoarded = isBoarded; }

void Passenger::changeCalledState(bool isWaiting) { this->isWaiting = isWaiting; }

int Passenger::getId() { return id; }

bool Passenger::getIsBoarded() const { return isBoarded; }
bool Passenger::getIsCalled() const { return isWaiting; }

std::vector<int> Passenger::getCallTime() { return callTime; }

std::vector<int> Passenger::getStartFloor() { return startFloor; }
std::vector<int> Passenger::getEndFloor() { return endFloor; }

void Passenger::removeCallTime() {
  if (!callTime.empty()) {
    callTime.erase(callTime.begin());
  }
}

void Passenger::removeStartFloor() {
  if (!startFloor.empty()) {
    startFloor.erase(startFloor.begin());
  }
}

void Passenger::removeEndFloor() {
  if (!endFloor.empty()) {
    endFloor.erase(endFloor.begin());
  }
}

int* Passenger::getStartFloorTop() {
  if (startFloor.size() != 0) {
    return &startFloor[0];
  }
  return nullptr;
}

int* Passenger::getCallTimeTop() {
  if (callTime.size() != 0) {
    return &callTime[0];
  }
  return nullptr;
}

int* Passenger::getEndFloorTop() {
  if (endFloor.size() != 0) {
    return &endFloor[0];
  }
  return nullptr;
}
