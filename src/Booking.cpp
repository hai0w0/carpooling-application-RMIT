// booking.cpp
#include "Booking.h"
#include <fstream>
#include <sstream>
#include <iostream>

Booking::Booking(const std::string& filePath) {
    loadCarpools(filePath);
}

Booking::~Booking() {}

void Booking::loadCarpools(const std::string& filePath) {
    std::ifstream file(filePath);
    std::string line;
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return;
    }
    getline(file, line); // Skip the header if present
    while (getline(file, line)) {
        std::stringstream ss(line);
        Carpool carpool;
        try {
            std::getline(ss, carpool.departureLocation, ',');
            std::getline(ss, carpool.destinationLocation, ',');
            std::getline(ss, carpool.departureTime, ',');
            std::getline(ss, carpool.date, ',');
            std::getline(ss, carpool.vehicleModel, ',');
            std::getline(ss, carpool.vehicleColor, ',');
            std::getline(ss, carpool.plateNumber, ',');
            std::getline(ss, line, ',');
            carpool.availableSeats = std::stoi(line);
            std::getline(ss, line, ',');
            carpool.contributionPerPassenger = std::stod(line);
            std::getline(ss, line);
            carpool.rating = std::stod(line);
            carpools.push_back(carpool);
        } catch (const std::exception& e) {
            std::cerr << "Error parsing line: " << line << " | " << e.what() << std::endl;
            continue;
        }
    }
    file.close();
}

std::vector<Carpool> Booking::searchCarpools(const std::string& departure, the std::string& destination, const std::string& date) {
    std::vector<Carpool> found;
    for (const auto& carpool : carpools) {
        if (carpool.departureLocation == departure && carpool.destinationLocation == destination && carpool.date == date) {
            found.push_back(carpool);
        }
    }
    return found;
}

bool Booking::makeBooking(int carpoolID, Member& member) {
    for (auto& carpool : carpools) {
        if (carpool.plateNumber == carpoolID && carpool.availableSeats > 0) {  // Assuming plate number uniquely identifies a carpool
            carpool.availableSeats--;
            member.updateCredits(-carpool.contributionPerPassenger);  // Assuming Member class has a method to update credits
            return true;
        }
    }
    return false;
}
