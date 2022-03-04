#include <iostream>

#include "GuestManager.h"

int main()
{
    GuestManager hotel_1{ 5, 10, 2, 20 };

    hotel_1.AddGuest(GuestType::Family, RoomType::Standard, 5, 4); 
    hotel_1.AddGuest(GuestType::Businessman, RoomType::Comfort, 3, 4); 
    
    if (hotel_1.AddGuest(GuestType::Rockstar, RoomType::Comfort, 2, 4) != true)
        std::cout << "TEST 1.1 ERROR: AddGuest malfunctions" << std::endl;

    if (hotel_1.AddGuest(GuestType::Rockstar, RoomType::Comfort, 15, 4) != false)
        std::cout << "TEST 1.2 ERROR: AddGuest malfunctions" << std::endl;

    ///////////////////////////////////////////////////////////////////////////////

    if (hotel_1.IsAvailable(RoomType::Standard, 5) != true)
        std::cout << "TEST 2.1 ERROR: IsAvailable malfunctions" << std::endl;

    if (hotel_1.IsAvailable(RoomType::Comfort, 4) != false)
        std::cout << "TEST 2.2 ERROR: IsAvailable malfunctions" << std::endl;

    if (hotel_1.IsAvailable(RoomType::Comfort, 1) != false)
        std::cout << "TEST 2.3 ERROR: IsAvailable malfunctions" << std::endl;

    if (hotel_1.IsAvailable(RoomType::Comfort, 2) != true)
        std::cout << "TEST 2.4 ERROR: IsAvailable malfunctions" << std::endl;

    if (hotel_1.IsAvailable(RoomType::Comfort, 3) != true)
        std::cout << "TEST 2.5 ERROR: IsAvailable malfunctions" << std::endl;

    ///////////////////////////////////////////////////////////////////////////////

    if(hotel_1.IncomingProfit() != 162)  
        std::cout << "TEST 3.1 ERROR: IncomingProfit malfunctions" << std::endl;

    GuestManager hotel_2{ 10, 5, 0, 0 };
    hotel_2.AddGuest(GuestType::Family, RoomType::Standard, 2, 4);
    hotel_2.AddGuest(GuestType::Family, RoomType::Standard, 2, 4);
    hotel_2.AddGuest(GuestType::Family, RoomType::Standard, 2, 4);
    hotel_2.AddGuest(GuestType::Businessman, RoomType::Standard, 1, 5);

    if (hotel_2.IncomingProfit() != 40)
        std::cout << "TEST 3.2 ERROR: IncomingProfit malfunctions" << std::endl;

    GuestManager hotel_3{ 0, 0, 10, 20 };
    hotel_3.AddGuest(GuestType::Rockstar, RoomType::Comfort, 10, 4);

    if (hotel_3.IncomingProfit() != 200)
        std::cout << "TEST 3.3 ERROR: IncomingProfit malfunctions" << std::endl;

    ///////////////////////////////////////////////////////////////////////////////

    if (hotel_1.EarningEfficiency() != 54.f / 90.f)
        std::cout << "TEST 4.1 ERROR: EarningEfficiency malfunctions" << std::endl;

    if (hotel_2.EarningEfficiency() != 25.f / 50.f)
        std::cout << "TEST 4.2 ERROR: EarningEfficiency malfunctions" << std::endl;

    // Bonus test
    // GuestManager hotel_4{ 0, 0, 0, 0 };
    // hotel_4.EarningEfficiency();
    
    ///////////////////////////////////////////////////////////////////////////////

    if(( hotel_1 < hotel_2) != false)
        std::cout << "TEST 5.1 ERROR: operator< malfunctions" << std::endl;

    if ((hotel_2 < hotel_3) != true)
        std::cout << "TEST 5.2 ERROR: operator< malfunctions" << std::endl;

    ///////////////////////////////////////////////////////////////////////////////

    std::cout << "^^^^^^^^^^^^ Any found problems should appear above this line ^^^^^^^^^^^^" << std::endl;

    return 0;
}