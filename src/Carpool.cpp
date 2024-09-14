#include "Carpool.h"
#include <sstream>
using namespace std;

Carpool::Carpool(const string &departureLocation, const string &destinationLocation,
                 const string &departureTime, const string &date, const string &vehicleModel,
                 const string &vehicleColor, const string &plateNumber, int availableSeats,
                 double contributionPerPassenger, double rating)
: departureLocation(departureLocation), destinationLocation(destinationLocation),
  departureTime(departureTime), date(date), vehicleModel(vehicleModel), vehicleColor(vehicleColor),
  plateNumber(plateNumber), availableSeats(availableSeats), contributionPerPassenger(contributionPerPassenger),
  rating(rating) {}

const string& Carpool::getDepartureLocation() const {
    return departureLocation;
}

const string& Carpool::getDestinationLocation() const {
    return destinationLocation;
}

const string& Carpool::getDate() const {
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

string Carpool::getCarpoolDetails() const {
    ostringstream details;
    details << departureLocation << " to " << destinationLocation
            << " on " << date << " - " << vehicleModel << " (" << vehicleColor << ")";
    return details.str();
}
