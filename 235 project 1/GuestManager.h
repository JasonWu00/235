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
    virtual int getRoomBusyDays() const = 0;
    virtual int getAdditionalIncome() const = 0;
    Guest();
    Guest(GuestType guest_type, RoomType room_type, int StayDuration);
    ~Guest();
  protected:
    RoomType room_type;
    GuestType guest_type;
    int days_booked;
};

class Family: public Guest {
  public:
    
};

class Rockstar: public Guest {
  public:
    int getRoomBusyDays() const override;
};

class Businessman: public Guest {
  public:
    int getAdditionalIncome() const override;
  protected:
    int income;
    Businessman(GuestType guest_type, RoomType room_type, int StayDuration, int additionalIncome);
};

class GuestManager {
  public:
    GuestManager(int NumOfStandardRooms, int dayPriceStandard, int NumOfComfortRooms, int dayPriceComfort);
    ~GuestManager();
    bool AddGuest(GuestType guest_type, RoomType room_type, int stayDays, int additionalIncome);
    bool IsAvailable(RoomType, int inDays);
    int IncomingProfit();
    float EarningEfficiency();
    bool operator<(GuestManager otherManager);
};