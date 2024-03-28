#pragma once
#include <map>
#include <string>
#include <vector>

#include "passenger.hpp"
class Passenger;

enum State { Up, Down, Stop };

class Elevator {
 public:
  Elevator(int maxFloor, int maxLoad, int id);
  void addPassenger(Passenger* passenger);
  void removePassenger(Passenger* passenger);
  void control();
  void setMaxLoad(int* maxLoad);
  void setMaxFloor(int* maxFloor);
  void setCallFloor(int* floor);
  void setDestFloor(int* floor);
  void setCalledPassengers(int id);
  void printInfo();
  bool isBoarded(int id);
  int getFloor();
  int getId();
  int getMaxLoad();
  int getCurrentLoad();
  int getDestFloor();
  int* getCalledFloor();
  State getState();
  void printCallFloor();
  void printDestFloor();
  void removeDestFloor();
  void removeCallFloor();
  void removeCalledPassengers(int id);
  int getMaxFloor();
  std::vector<Passenger*> getPassengers() const;
  std::string enumToString(State state);

 private:
  State state;
  int id;
  int floor;
  int maxFloor;
  int maxLoad;
  int currentLoad;
  std::vector<Passenger*> passengers;
  std::vector<int> calledFloors;
  std::vector<int> calledPassengers;
  std::vector<int> destFloors;
  std::map<State, std::string> stateMap = {{Up, "UP"}, {Down, "DOWN"}, {Stop, "STOP"}};
};