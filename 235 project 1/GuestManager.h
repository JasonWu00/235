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
    virtual ~Guest();
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
    int NumOfStandardRooms;//"available" rooms
    int totalStandardRooms;//all rooms including occupied ones
    int dayPriceStandard;

    int NumOfComfortRooms;
    int totalComfortRooms;
    int dayPriceComfort;

    int dayTilNextFreeStandard;//days until the next Standard guest leaves
    int dayTilNextFreeComfort;//see above, but for comfort rooms

    std::vector<Guest*> guests;
    int totalIncome();
  public:
    GuestManager(int NumOfStandardRooms, int dayPriceStandard, int NumOfComfortRooms, int dayPriceComfort);
    ~GuestManager();

    bool AddGuest(GuestType guest_type, RoomType room_type, int stayDays, int additionalIncome = 0);
    bool IsAvailable(RoomType type, int inDays = 0);

    int IncomingProfit();
    int profitPerDay() const;
    float EarningEfficiency() const;
    bool operator < (GuestManager& otherManager);
};