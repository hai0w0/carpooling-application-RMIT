#ifndef CARPOOL_H
#define CARPOOL_H

#include <string>

class Carpool {
public:
    // Constructor to initialize a Carpool object with specific attributes
    Carpool(const std::string &departureLocation, const std::string &destinationLocation,
            const std::string &departureTime, const std::string &date, const std::string &vehicleModel,
            const std::string &vehicleColor, const std::string &plateNumber, int availableSeats,
            double contributionPerPassenger, double rating);

    // Getter methods to access the private member variables
    const std::string& getDepartureLocation() const;
    const std::string& getDestinationLocation() const;
    const std::string& getDate() const;
    int getAvailableSeats() const;
    double getContributionPerPassenger() const;
    double getRating() const;
    std::string getCarpoolDetails() const;

private:
    // Private variables to store carpool details
    std::string departureLocation;
    std::string destinationLocation;
    std::string departureTime;
    std::string date;
    std::string vehicleModel;
    std::string vehicleColor;
    std::string plateNumber;
    int availableSeats;
    double contributionPerPassenger;
    double rating;
};

#endif
