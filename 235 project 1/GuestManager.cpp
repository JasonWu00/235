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
    Guest *guest;/*
    if (guest_type = Family) {
        guest = new Family(guest_type, room_type, stayDays);
    }
    else if (guest_type = Businessman) {
        guest = new Businessman(guest_type, room_type, stayDays, additionalIncome);
    }
    else if (guest_type = Rockstar) {
        guest = new Rockstar(guest_type, room_type, stayDays);
    }
    else {
        return false;
    }*/
    return true;
}