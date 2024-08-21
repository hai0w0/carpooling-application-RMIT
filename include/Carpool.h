#ifndef CARPOOL_H
#define CARPOOL_H

#include <string>
#include <vector>

class Carpool {
private:
    std::string driverUsername;
    std::string departureLocation;
    std::string destinationLocation;
    std::string date;
    std::string time;
    std::string vehicleModel;
    std::string vehicleColor;
    std::string vehiclePlate;
    int availableSeats;
    int contributionPerPassenger;
    std::vector<std::string> passengers;
    bool isActive;

public:
    Carpool(const std::string& driverUsername, const std::string& departureLocation, 
            const std::string& destinationLocation, const std::string& date, const std::string& time, 
            const std::string& vehicleModel, const std::string& vehicleColor, 
            const std::string& vehiclePlate, int availableSeats, int contributionPerPassenger);

    std::string getDriverUsername() const;
    void displayDetails() const;
    void addPassenger(const std::string& passengerUsername);
    void removePassenger(const std::string& passengerUsername);
    bool isSeatAvailable() const;
    bool isListingActive() const;
    void deactivateListing();
    void activateListing();
};

#endif
