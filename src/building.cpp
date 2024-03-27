#include "building.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>
#include <thread>

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

    // 乗客が押した階についたので、エレベータから降りる
    dropPassenger(elevator, time);

    // 乗客が待つ階についたので、乗客がエレベータに乗る
    ridePassenger(elevator, time);
  }
}

bool Building::checkContinue() {
  // 全ての乗客が行先に到着した
  bool returnVal{false};

  for (auto passenger : passengers) {
    if (passenger->getEndFloorTop() != nullptr) {
      // std::cout << passenger->getId() << "," << *passenger->getEndFloorTop() << std::endl;
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
      
      int checkLoad = elevator->getCurrentLoad() + passenger->getWeight();
      // 最大重量のチェック
      if (checkLoad <= elevator->getMaxLoad()) {
        elevator->addPassenger(passenger);
        elevator->setDestFloor(passenger->getEndFloorTop());
        elevator->removeCallFloor();

        passenger->changeBoardedState(true);
        passenger->changeCalledState(false);
        passenger->removeCallTime();
        passenger->removeStartFloor();
      } else {
        std::cout << "!!!! Over the weight limit !!!!" << std::endl;
      }
    }
  }
}

void Building::dropPassenger(Elevator* elevator, int time) {
  // std::cout << "e ID:" << elevator->getId() << "\n";

  for (auto passenger : passengers) {
    // std::cout << ",end flooe: " << *passenger->getEndFloorTop() << std::endl;
    if (passenger->getIsBoarded() && passenger->getEndFloorTop() != nullptr &&
        *passenger->getEndFloorTop() == elevator->getFloor()) {
      elevator->removePassenger(passenger);

      // std::cout << "e ID: " << elevator->getId() << std::endl;
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

void Building::waitForEnterKey() {
  std::cout << "Press Enter to continue...";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Building::print_out() {
  int maxFloors = 0;  // Find the maximum number of floors among all elevators
  for (auto elevator : elevators) {
    maxFloors = std::max(maxFloors, elevator->getMaxFloor());
  }

  // std::string elevatorNames;
  // for (auto elevator : elevators) {
  //   elevatorNames += elevator->getId() + "\t";  // Concatenate elevator names
  // }
  // std::cout << "\t" << elevatorNames << std::endl;

  for (int floor = maxFloors; floor >= 0; floor--) {
    std::string output;

    for (auto elevator : elevators) {
      if (floor <= elevator->getMaxFloor()) {
        std::string floorStr = std::to_string(floor);
        if (floor == elevator->getFloor()) {
          output += "\033[1;31m" + floorStr + "F\t[";
          for (auto passenger : elevator->getPassengers()) {
            if (passenger->getIsBoarded()) {
              output += " " + std::to_string(passenger->getId()) + " ";
            }
          }
          output += "]\033[m\t\t\t\t";
        } else {
          output += floorStr + "F\t[]\t\t\t\t";
        }
      } else {
        output += "\t\t\t";  // Placeholder for floors that don't exist for this elevator
      }
    }
    std::cout << output << std::endl;
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  // waitForEnterKey();
}