#pragma once
#include <vector>

#include "elevator.hpp"

class Elevator;

class Passenger {
 public:
  Passenger(int id, int weight);
  int getWeight();
  int getId();
  void printInfo();
  void addCallInfo(int time, int pickUpFloor, int dropOffFloor);
  void changeBoardedState(bool isBoarded);
  void changeCalledState(bool isWaiting);
  bool getIsBoarded() const;
  bool getIsCalled() const;
  std::vector<int> getCallTime();
  std::vector<int> getStartFloor();
  std::vector<int> getEndFloor();
  int* getStartFloorTop();
  int* getCallTimeTop();
  int* getEndFloorTop();
  void removeCallTime();
  void removeStartFloor();
  void removeEndFloor();
  void removeFloor(int floor);

 private:
  int id;
  int weight;
  std::vector<int> callTime;
  std::vector<int> startFloor;
  std::vector<int> endFloor;
  bool isBoarded;
  bool isWaiting;
};