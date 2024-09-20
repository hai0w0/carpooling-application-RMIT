#include "Carpool.h"
#include <sstream>
using namespace std;

// Constructor for initializing a Carpool object with given details
Carpool::Carpool(const string &departureLocation, const string &destinationLocation,
                 const string &departureTime, const string &date, const string &vehicleModel,
                 const string &vehicleColor, const string &plateNumber, int availableSeats,
                 double contributionPerPassenger, double rating)
: departureLocation(departureLocation), destinationLocation(destinationLocation),
  departureTime(departureTime), date(date), vehicleModel(vehicleModel), vehicleColor(vehicleColor),
  plateNumber(plateNumber), availableSeats(availableSeats), contributionPerPassenger(contributionPerPassenger),
  rating(rating) {}

// Getter for departure location
const string& Carpool::getDepartureLocation() const {
    return departureLocation; // Returns the departure location of the carpool
}

// Getter for destination location
const string& Carpool::getDestinationLocation() const {
    return destinationLocation; // Returns the destination location of the carpool
}

// Getter for date
const string& Carpool::getDate() const {
    return date; // Returns the date of the carpool
}

// Getter for available seats
int Carpool::getAvailableSeats() const {
    return availableSeats; // Returns the number of available seats in the carpool
}

// Getter for contribution per passenger
double Carpool::getContributionPerPassenger() const {
    return contributionPerPassenger; // Returns the contribution amount per passenger
}

// Getter for rating
double Carpool::getRating() const {
    return rating; // Returns the rating of the carpool
}

// Method to get a string detailing carpool information
string Carpool::getCarpoolDetails() const {
    ostringstream details; // Create a string stream for assembling details
    details << departureLocation << " to " << destinationLocation
            << " on " << date << " - " << vehicleModel << " (" << vehicleColor << ")";
    return details.str(); // Convert the stream to string and return it
}
