#pragma once
#include <vector>

#include "elevator.hpp"
#include "passenger.hpp"

class Building {
 public:
  Building();
  std::vector<Passenger*> getPassengers();
  std::vector<Elevator*> getElevators();
  void addElevator(Elevator* elevator);
  void addPassengers(Passenger* passengers);
  Passenger* getPassengersById(int id);
  void runElevator(int time);
  void printStatus();
  bool checkContinue();
  Elevator* getNearestElevator(int floor);

 private:
  std::vector<Passenger*> passengers;
  std::vector<Elevator*> elevators;
  void callElevator(Elevator* elevator, Passenger* passenger, int time);
  void ridePassenger(Elevator* elevator, int time);
  void dropPassenger(Elevator* elevator, int time);
};