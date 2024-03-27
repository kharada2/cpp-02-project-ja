#include "simulator.h"

#include <fstream>
#include <iostream>
#include <sstream>

std::ifstream openFile(const std::string& filename);

Simulator::Simulator(int millisecondsDelay) : millisecondsDelay(millisecondsDelay) {}

void Simulator::initializeFromFile(const std::string& filename) {
  auto file{openFile(filename)};
  parseElevators(file);
  parsePassengers(file);
  parseInputs(file);
}

std::ifstream openFile(const std::string& filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    throw std::runtime_error("Exception! Cannot open file!");
  }

  return file;
}

void Simulator::parseElevators(std::ifstream& file) {
  std::string line;
  std::getline(file, line);
  std::istringstream iss{line};

  int numberOfElevators{};
  int numberOfFloors{};
  int elevatorCapacity{};

  if (!(iss >> numberOfElevators >> numberOfFloors >> elevatorCapacity)) {
    throw std::runtime_error("Exception! Cannot parse the first line of the file!");
  } else {
    for (int i = 1; i <= numberOfElevators; ++i) {
      building.addElevator(new Elevator(numberOfFloors, elevatorCapacity, i));
    }
  }
}

void Simulator::parsePassengers(std::ifstream& file) {
  std::string line;
  std::getline(file, line);
  std::istringstream iss{line};

  int numberOfPassengers{};

  if (!(iss >> numberOfPassengers)) {
    throw std::runtime_error("Exception! Cannot parse the number of passengers!");
  }

  while (numberOfPassengers-- && std::getline(file, line)) {
    iss = std::istringstream{line};

    int id;
    int weight;

    if (!(iss >> id >> weight)) {
      throw std::runtime_error("Exception! Cannot parse the remaining lines of the file!");
    } else {
      building.addPassengers(new Passenger(id, weight));
    }
  }
}

void Simulator::parseInputs(std::ifstream& file) {
  std::string line;
  while (std::getline(file, line)) {
    auto iss = std::istringstream{line};

    int time{};
    int id{};
    int pickUpFloor{};
    int dropOffFloor{};

    if (!(iss >> time >> id >> pickUpFloor >> dropOffFloor)) {
      throw std::runtime_error("Exception! Cannot parse the remaining lines of the file!");
    } else {
      // 同じIDの乗客を取得
      auto passenger = building.getPassengersById(id);
      passenger->addCallInfo(time, pickUpFloor, dropOffFloor);
      // std::cout << "ID: " << id << " " << pickUpFloor << std::endl;
    }
  }

  for (auto i : building.getPassengers()) {
    i->printInfo();
  }
}

void Simulator::run() {
  int time = 0;
  while (building.checkContinue() && time < 100) {
    building.runElevator(time);
    std::cout << "[SimulationStep: " << time << "]:" << std::endl;
    building.printStatus();
    time += 1;
  }
}

void Simulator::printResults() const {}