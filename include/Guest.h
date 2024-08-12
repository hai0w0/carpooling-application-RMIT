#ifndef GUEST_H
#define GUEST_H

//Avoid using namespace std for all .h files because it can lead to name conflicts in the files that include these headers

#include <vector>
#include <string>

class CarpoolListing {
public:
    std::string location;
    std::string date;
    std::string time;
    std::string driver;
    int seatsAvailable;

    CarpoolListing(std::string loc, std::string dat, std::string tim, std::string drv, int seats)
        : location(loc), date(dat), time(tim), driver(drv), seatsAvailable(seats) {}
};

class Guest {
public:
    // Function to display carpool listings
    static void showCarpoolListings(const std::vector<CarpoolListing>& listings);
};

#endif // GUEST_H
