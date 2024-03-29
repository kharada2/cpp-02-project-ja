#include "building.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>
#include <thread>

Building::Building() {}

std::vector<Passenger *> Building::getPassengers() { return passengers; }

std::vector<Elevator *> Building::getElevators() { return elevators; }

void Building::addElevator(Elevator *elevator) { elevators.push_back(elevator); }

void Building::addPassengers(Passenger *passenger) { passengers.push_back(passenger); }

Passenger *Building::getPassengersById(int id)
{
  for (Passenger *i : passengers)
  {
    if (i->getId() == id)
    {
      return i;
    }
  }
  return nullptr;
}

void Building::control(int time) {
  // 1. エレベータを呼ぶ（エレベーターのボタンを押す）
  for (auto passenger : passengers) {
    if (passenger->getStartFloorTop() != nullptr) {
      // 最も近いエレベータを呼び出す
      auto elevator = getNearestElevator(*passenger->getStartFloorTop());
      callElevator(elevator, passenger, time);
    }
  }

  for (auto elevator : elevators) {
    // 2. エレベータ制御
    elevator->control();

    // 3. 乗客の行先階についたので、エレベータから降ろす
    dropPassenger(elevator, time);

    // 4. 乗客が待つ階についたので、乗客がエレベータに乗る
    ridePassenger(elevator, time);
  }
}

bool Building::checkContinue()
{
  // 全ての乗客が行先に到着した
  bool returnVal{false};

  for (auto passenger : passengers)
  {
    if (passenger->getEndFloorTop() != nullptr)
    {
      returnVal = true;
    }
  }
  return returnVal;
}

void Building::callElevator(Elevator *elevator, Passenger *passenger, int time)
{
  if (!passenger->getIsBoarded() && !passenger->getIsCalled() && passenger->getCallTimeTop() != nullptr &&
      *passenger->getCallTimeTop() == time)
  {
    elevator->setCallFloor(passenger->getStartFloorTop());
    elevator->setCalledPassengers(passenger->getId());

    passenger->changeCalledState(true);
  }
}

void Building::ridePassenger(Elevator* elevator, int time) {
  for (auto passenger : passengers) {
    if (!passenger->getIsBoarded() &&  // 1. 乗っていない
        passenger->getStartFloorTop() != nullptr &&
        *passenger->getStartFloorTop() == elevator->getFloor() &&  // 2. 乗客が待つ階に到着　
        elevator->getCalledFloor() != nullptr &&
        *elevator->getCalledFloor() == elevator->getFloor() &&  // 3. 乗客の呼び出し階に到着
        passenger->getCallTimeTop() != nullptr && *passenger->getCallTimeTop() <= time  // 4. 乗客がコールした後　
    ) {
      int checkLoad = elevator->getCurrentLoad() + passenger->getWeight();
      // 最大重量のチェック
      if (checkLoad <= elevator->getMaxLoad())
      {
        elevator->addPassenger(passenger);
        elevator->setDestFloor(passenger->getEndFloorTop());
        elevator->removeCallFloor();

        passenger->changeBoardedState(true);
        passenger->setBoardElevatorId(elevator->getId());
        passenger->changeCalledState(false);
        passenger->removeCallTime();
        passenger->removeStartFloor();
      }
      else
      {
        std::cout << "\033[33mPassenger[" << passenger->getId() << "] is refused a ride because of overweight.\033[0m"
                  << std::endl;
      }
    }
  }
}

void Building::dropPassenger(Elevator* elevator, int time) {
  for (auto passenger : passengers) {
    if (passenger->getIsBoarded() && passenger->getBoardElevatorId() == elevator->getId() &&  // 1. 乗っている
        passenger->getEndFloorTop() != nullptr &&
        *passenger->getEndFloorTop() == elevator->getFloor())  // 2. 行先階についた
    {
      elevator->removePassenger(passenger);
      elevator->removeDestFloor();
      elevator->removeCalledPassengers(passenger->getId());

      passenger->changeBoardedState(false);
      passenger->setBoardElevatorId(-1);
      passenger->removeEndFloor();
    }
  }
}

void Building::printStatus()
{
  for (auto elevator : elevators)
  {
    std::cout << "elevator[" << elevator->getId() << "]:";
    std::cout << "Floor:" << elevator->getFloor() << ", ";
    std::cout << "State:" << elevator->enumToString(elevator->getState()) << ", ";
    // elevator->printCallFloor();
    // elevator->printDestFloor();
    std::cout << "Passengers:";
    for (auto passenger : elevator->getPassengers())
    {
      std::cout << passenger->getId() << " ";
    }
    std::cout << std::endl;
  }
}

Elevator *Building::getNearestElevator(int floor)
{
  Elevator *nearest = nullptr;
  int minDistance = std::numeric_limits<int>::max(); // 最大値で初期化

  for (Elevator *elevator : elevators)
  {
    // エレベーターの目的の階を取得
    int currentFloor = elevator->getFloor();

    // 指定した階とエレベーターの目的の階との距離を計算
    int distance = std::abs(floor - currentFloor);

    // 最も近いエレベーターを更新
    if (distance < minDistance)
    {
      minDistance = distance;
      nearest = elevator;
    }
  }

  return nearest;
}

void Building::waitForEnterKey()
{
  std::cout << "Press Enter to continue...";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Building::print_out()
{
  int maxFloors = 0;
  for (auto elevator : elevators)
  {
    maxFloors = std::max(maxFloors, elevator->getMaxFloor());
  }

    std::cout << "Waiting Passenger" << "\t\t\t";

  for (auto elevator : elevators)
  {
    std::cout << "Elevator " << elevator->getId() << "\t\t\t\t";
  }

  std::cout << "\n";

  // std::string elevatorNames;
  // for (auto elevator : elevators) {
  //   elevatorNames += elevator->getId() + "\t";  // Concatenate elevator names
  // }
  // std::cout << "\t" << elevatorNames << std::endl;

  for (int floor = maxFloors; floor >= 0; floor--)
  {
    std::string output;
    int waiting_pID = 0;
    int waiting_floor = 0;
    int flag = 0;

    for (auto passenger : passengers)
    {
      if (passenger->getIsCalled() == 1)
      {
        waiting_pID = passenger->getId();
        waiting_floor = *passenger->getStartFloorTop();
        if(floor == waiting_floor){
          std::cout << waiting_pID;
        }
        flag = 1;
      }
      else
      {
        waiting_pID = 0;
        flag = 0;
      }
    }

    std::cout << "\t\t\t\t";

    for (auto elevator : elevators)
    {
      if (floor <= elevator->getMaxFloor())
      {
        std::string floorStr = std::to_string(floor);
        if (floor == elevator->getFloor())
        {
          output += "\033[1;31m" + floorStr + "F\t[";
          for (auto passenger : elevator->getPassengers())
          {
            if (passenger->getIsBoarded())
            {
              output += " " + std::to_string(passenger->getId()) + " ";
            }
          }
          if(elevator->getState() == 0){
            output += "] ^\033[m\t\t\t\t";
          }
          else if(elevator->getState() == 1){
            output += "] v\033[m\t\t\t\t";
          }
          else{
            output += "]\033[m\t\t\t\t";
          }
        }
        else
        {
          output += floorStr + "F\t[]\t\t\t\t";
        }
      }
      else
      {
        output += "\t\t\t";
      }
    }
    std::cout << output << std::endl;
  }
  //  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  waitForEnterKey();
}
