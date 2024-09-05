// booking.h
#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <vector>
#include "Member.h"  // Assuming Member class handles member-related information

struct Carpool {
    std::string departureLocation;
    std::string destinationLocation;
    std::string departureTime;
    std::string date;
    std::string vehicleModel;
    std::string vehicleColor;
    std::string plateNumber;
    int availableSeats;
    double contributionPerPassenger;
    double rating;  // Assuming this is the average rating
};

class Booking {
public:
    Booking(const std::string& filePath);
    ~Booking();

    std::vector<Carpool> searchCarpools(const std::string& departure, const std::string& destination, const std::string& date);
    bool makeBooking(int carpoolID, Member& member);

private:
    std::vector<Carpool> carpools;  // List of all carpools
    void loadCarpools(const std::string& filePath);
};

#endif
