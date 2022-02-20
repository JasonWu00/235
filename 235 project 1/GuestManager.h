#pragma once

enum RoomType {
  Standard,
  Comfort
};

enum GuestType {
  Family,
  Businessman,
  Rockstar
};

class Guest {
  public:
    GuestType getGuestType();
    RoomType getRoomType();
    int getBookedDays();
    virtual int getRoomBusyDays();
    virtual int getAdditionalIncome();
    Guest(GuestType guest_type, RoomType room_type, int StayDuration);
    virtual ~Guest();
  protected:
    RoomType room_type;
    GuestType guest_type;
    int days_booked;
};

class Family: public Guest {

};

class Rockstar: public Guest {

};

class Businessman: public Guest {
  protected:
   int income;
   Businessman(GuestType guest_type, RoomType room_type, int StayDuration, int additionalIncome);
};