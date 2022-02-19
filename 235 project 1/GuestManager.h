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
    Guest();
    Guest(GuestType guest_type, RoomType room_type, int StayDuration);
    ~Guest();
  protected:
    RoomType room_type;
    GuestType guest_type;
    int days_booked;
};
