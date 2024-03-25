#pragma once
#include <vector>

#include "passenger.hpp"

class Passenger;

// enum class ElevatorState { up, down, stop };

class Elevator {
 public:
  Elevator(int maxFloor, int maxLoad, int id);
  void addPassenger(Passenger* passenger);
  void removePassenger(Passenger* passenger);
  void move();
  void setMaxLoad(int* maxLoad);
  void setMaxFloor(int* maxFloor);
  void setCallFloor(int* floor);
  void setDestFloor(int* floor);
  void printInfo();
  bool isBoarded(int id);
  int getFloor();
  int getId();
  int getDestFloor();
  void printCallFloor();
  void printDestFloor();
  void removeDestFloor();
  void removeCallFloor();
  std::vector<Passenger*> getPassengers() const;

 private:
  int id;
  int floor;
  int maxFloor;
  int maxLoad;
  int currentLoad;
  std::vector<Passenger*> passengers;
  std::vector<int> calledFloors;
  std::vector<int> destFloors;
};