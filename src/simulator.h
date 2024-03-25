#pragma once

#include <string>
#include <vector>

#include "building.hpp"
#include "elevator.hpp"
#include "passenger.hpp"

class Simulator {
 public:
  Simulator(int millisecondsDelay);

 public:
  void initializeFromFile(const std::string& filename);
  void run();
  void printResults() const;

 private:
  void parseElevators(std::ifstream& file);
  void parsePassengers(std::ifstream& file);
  void parseInputs(std::ifstream& file);
  void addElevator(Elevator elevator);
  void addPassenger(Passenger passenger);
  Passenger* getPassengerById(int id);

 private:
  int millisecondsDelay;
  Building building;
};