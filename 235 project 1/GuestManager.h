#pragma once
#include <vector>

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
    Family(GuestType guest_type, RoomType room_type, int StayDuration);
    int getAdditionalIncome() const override;
    int getRoomBusyDays() const override;
};

class Rockstar: public Guest {
  public:
    Rockstar(GuestType guest_type, RoomType room_type, int StayDuration);
    int getAdditionalIncome() const override;
    int getRoomBusyDays() const override;
};

class Businessman: public Guest {
  public:
    int getAdditionalIncome() const override;
    int getRoomBusyDays() const override;
    Businessman(GuestType guest_type, RoomType room_type, int StayDuration, int additionalIncome);
  protected:
    int income;
};

class GuestManager {
  protected:
    int NumOfStandardRooms;
    int dayPriceStandard;
    int NumOfComfortRooms;
    int dayPriceComfort;
    std::vector<Guest*> guests;
    int totalIncome();
  public:
    GuestManager(int NumOfStandardRooms, int dayPriceStandard, int NumOfComfortRooms, int dayPriceComfort);
    ~GuestManager();
    bool AddGuest(GuestType guest_type, RoomType room_type, int stayDays, int additionalIncome);
    bool IsAvailable(RoomType type, int inDays);
    int IncomingProfit();
    float EarningEfficiency();
    bool operator<(GuestManager otherManager);
};

class test {
  public:
    int example;
    test();
    test(int input);
    virtual int random() = 0;
    virtual int random2() = 0;
};

class test2: public test {
  public:
    int example2;
    test2();
    test2(int input, int input2);
    int random() override;
};