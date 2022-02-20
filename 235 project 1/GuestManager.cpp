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

int Guest::getRoomBusyDays() {
    return 0;
}

int Guest::getAdditionalIncome() {
    return 0;
}