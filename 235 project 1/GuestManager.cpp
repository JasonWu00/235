#include <iostream>
#include "GuestManager.h"

GuestType Guest::getGuestType() {
    return this->guest_type;
}

RoomType Guest::getRoomType() {
    return this->room_type;
}

int Guest::getBookedDays() {
    return days_booked;
}

/* the following two implementations are unnecessary
and are thus commented out
int Guest::getRoomBusyDays() const {
    return days_booked;
}

int Guest::getAdditionalIncome() const {
    return 0;
}*/

Guest::Guest(GuestType guest_type, RoomType room_type, int StayDuration) {
    this->guest_type = guest_type;
    this->room_type = room_type;
    this->days_booked = StayDuration;
}

Guest::~Guest() {

}

Rockstar::Rockstar(GuestType guest_type, RoomType room_type, int StayDuration)
: Guest(guest_type, room_type, StayDuration) {

}

Family::Family(GuestType guest_type, RoomType room_type, int StayDuration)
: Guest(guest_type, room_type, StayDuration) {
    
}

//Implementing overrides of getRoomBusyDays and getAdditionalIncome 
//for Rockstar, Family, and Businessman so they will not be abstract
//so that they can be initialized

int Family::getRoomBusyDays() const {
    return days_booked;
}

int Family::getAdditionalIncome() const {
    return 0;
}

int Rockstar::getRoomBusyDays() const {
    return days_booked + 10;
}

int Rockstar::getAdditionalIncome() const {
    return 0;
}

int Businessman::getAdditionalIncome() const {
    return income;
}

int Businessman::getRoomBusyDays() const {
    return days_booked;
}



Businessman::Businessman(GuestType guest_type, RoomType room_type, int StayDuration, int additionalIncome) 
: Guest(guest_type, room_type, StayDuration) { //invoking the Guest constructor
    this->income = additionalIncome;
}

GuestManager::GuestManager(int NumOfStandardRooms, int dayPriceStandard, int NumOfComfortRooms, int dayPriceComfort) {
    this->NumOfStandardRooms = NumOfStandardRooms;
    this->dayPriceStandard = dayPriceStandard;
    this->NumOfComfortRooms = NumOfComfortRooms;
    this->dayPriceComfort = dayPriceComfort;
}

GuestManager::~GuestManager() {
    for (Guest* pointer : guests) {
        delete pointer;
    }
    // std::cout << "Deleting GuestManager" << std::endl;
}

bool GuestManager::AddGuest(GuestType guest_type, RoomType room_type, int stayDays, int additionalIncome) {
    Guest *guest;

    if (guest_type == GuestType::Family) {
        guest = new class Family(guest_type, room_type, stayDays);
    }
    else if (guest_type == GuestType::Businessman) {
        guest = new class Businessman(guest_type, room_type, stayDays, additionalIncome);
    }
    else if (guest_type == GuestType::Rockstar) {
        guest = new class Rockstar(guest_type, room_type, stayDays);
    }
    else {//the guest type isn't any of the known types
        return false;
    }
    
    //see if the room is available, then subtract 1
    if (room_type == RoomType::Standard && NumOfStandardRooms >= 1) {
        NumOfStandardRooms -=1;
        if (dayTilNextFreeStandard > stayDays) {
            //nextFreeStandard stores the days left 
            //until the next Standard guest leaves
            //if the new guest will stay for a shorter time
            //update nextFreeStandard to match.
            dayTilNextFreeStandard = stayDays;
        }
    }
    else if (room_type == RoomType::Comfort && NumOfComfortRooms >= 1) {
        NumOfComfortRooms -= 1;
        if (dayTilNextFreeComfort > stayDays) {
            //see nextFreeStandard
            dayTilNextFreeComfort = stayDays;
        }
    }
    else {//there aren't enough rooms of this type
          //or the room type isn't a known type
        delete guest;
        return false;
    }

    guests.push_back(guest);//add guest to the vector of guests
    return true;
}

bool GuestManager::IsAvailable(RoomType type, int inDays) {
    if (type == RoomType::Standard) {
        return (NumOfStandardRooms > 0 || dayTilNextFreeStandard < inDays);
    }
    else if (type == RoomType::Comfort || dayTilNextFreeComfort < inDays) {
        return (NumOfComfortRooms > 0);
    }
    else {//type specified is not a known type
        return false;
    }
}