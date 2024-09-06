// Carpool.cpp
#include "Carpool.h"
#include <sstream>

Carpool::Carpool(const std::string &departureLocation, const std::string &destinationLocation,
                 const std::string &departureTime, const std::string &date, const std::string &vehicleModel,
                 const std::string &vehicleColor, const std::string &plateNumber, int availableSeats,
                 double contributionPerPassenger, double rating)
: departureLocation(departureLocation), destinationLocation(destinationLocation),
  departureTime(departureTime), date(date), vehicleModel(vehicleModel), vehicleColor(vehicleColor),
  plateNumber(plateNumber), availableSeats(availableSeats), contributionPerPassenger(contributionPerPassenger),
  rating(rating) {}

const std::string& Carpool::getDepartureLocation() const {
    return departureLocation;
}

const std::string& Carpool::getDestinationLocation() const {
    return destinationLocation;
}

const std::string& Carpool::getDate() const {
    return date;
}

int Carpool::getAvailableSeats() const {
    return availableSeats;
}

double Carpool::getContributionPerPassenger() const {
    return contributionPerPassenger;
}

double Carpool::getRating() const {
    return rating;
}

std::string Carpool::getCarpoolDetails() const {
    std::ostringstream details;
    details << departureLocation << " to " << destinationLocation
            << " on " << date << " - " << vehicleModel << " (" << vehicleColor << ")";
    return details.str();
}
