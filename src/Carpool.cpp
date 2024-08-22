/*#include "Carpool.h"
#include <iostream>

using namespace std;

Carpool::Carpool(const std::string& driverUsername, const std::string& departureLocation, 
                 const std::string& destinationLocation, const std::string& date, 
                 const std::string& time, const std::string& vehicleModel, 
                 const std::string& vehicleColor, const std::string& vehiclePlate, 
                 int availableSeats, int contributionPerPassenger)
    : driverUsername(driverUsername), departureLocation(departureLocation), 
      destinationLocation(destinationLocation), date(date), time(time), vehicleModel(vehicleModel), 
      vehicleColor(vehicleColor), vehiclePlate(vehiclePlate), availableSeats(availableSeats), 
      contributionPerPassenger(contributionPerPassenger), isActive(true) {}

std::string Carpool::getDriverUsername() const {
    return driverUsername;
}

void Carpool::displayDetails() const {
    cout << "Driver: " << driverUsername << endl;
    cout << "Departure: " << departureLocation << endl;
    cout << "Destination: " << destinationLocation << endl;
    cout << "Date: " << date << endl;
    cout << "Time: " << time << endl;
    cout << "Vehicle: " << vehicleModel << " (" << vehicleColor << ", Plate: " << vehiclePlate << ")" << endl;
    cout << "Available Seats: " << availableSeats << endl;
    cout << "Contribution per Passenger: " << contributionPerPassenger << " points" << endl;
}

void Carpool::addPassenger(const std::string& passengerUsername) {
    if (availableSeats > 0) {
        passengers.push_back(passengerUsername);
        availableSeats--;
    }
}

void Carpool::removePassenger(const std::string& passengerUsername) {
    auto it = find(passengers.begin(), passengers.end(), passengerUsername);
    if (it != passengers.end()) {
        passengers.erase(it);
        availableSeats++;
    }
}

bool Carpool::isSeatAvailable() const {
    return availableSeats > 0;
}

bool Carpool::isListingActive() const {
    return isActive;
}

void Carpool::deactivateListing() {
    isActive = false;
}

void Carpool::activateListing() {
    isActive = true;
}
*/