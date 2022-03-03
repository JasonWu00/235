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

int Guest::getRoomBusyDays() const {
    return days_booked;
}

int Guest::getAdditionalIncome() const {
    return 0;
}

Guest::Guest(GuestType guest_type, RoomType room_type, int StayDuration) {
    this->guest_type = guest_type;
    this->room_type = room_type;
    this->days_booked = StayDuration;
}

int Rockstar::getRoomBusyDays() const {
    return days_booked + 10;
}

int Businessman::getAdditionalIncome() const {
    return income;
}

Businessman::Businessman(GuestType guest_type, RoomType room_type, int StayDuration, int additionalIncome) {
    //Guest(guest_type, room_type, StayDuration);
    this->income = additionalIncome;
}