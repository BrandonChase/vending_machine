#include <stdlib.h>
#include <iostream>

//----------Enums----------
enum class LightSwitch
{
	On.
	Off
};

enum class State 
{
	Idle, 
	One_Coin_in_Machine, 
	Two_Coins_in_Machine, 
	Selection_Validation, 
	Dispensing_Product,
	Refunding_Coin,
	Invalid_Product_Selection
};

enum class Event
{
	Coin_Inserted,
	Refund_Lever_Pulled,
	Product_Select_Pressed,
	Product_Select_Released,
	Product_Not_in_Stock
};

//----------Vending Machine Class----------
class VendingMachine
{
public:
	VendingMachine();
	void handleEvent(Event e);
	void test();

private:
	State current_state;
	int num_coins;
	LightSwitch product_backlights;
	LightSwitch product_NA_light;
};

//Class Method Implementation

//----------MAIN----------
int main()
{
	return 0;
}