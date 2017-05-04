#include <stdlib.h>
#include <iostream>
#include <chrono> 
#include <thread> //this_thread::sleep_for
#include <exception>

using namespace std;

//----------Enums----------
enum LightSwitch
{
	On,
	Off
};

enum State 
{
	Idle, 
	One_Coin_in_Machine, 
	Two_Coins_in_Machine, 
	Selection_Validation, 
	Dispensing_Product,
	Refunding_Coin,
	Invalid_Product_Selection
};

enum Event
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
	void enableVerbose();
	void disableVerbose();
	void handleEvent(Event e);
	void test();


private:
	State current_state;
	LightSwitch product_backlights;
	LightSwitch product_NA_light;
	bool verbose;
};

//Class Method Implementation
VendingMachine::VendingMachine() : current_state(Idle), product_backlights(Off), product_NA_light(Off), verbose(false)
{
	if(verbose) cout << "VM initiliazed to (Idle)\n";
}

void VendingMachine::enableVerbose()
{
	verbose = true;
}

void VendingMachine::disableVerbose()
{
	verbose = false;
}

void VendingMachine::handleEvent(Event e)
{
	switch(e)
	{
		case Coin_Inserted:
			if(current_state == Idle)
			{
				if(verbose) cout << "\t{Coin Inserted} causes VM to switch from (Idle) to (One Coin in Machine)" << endl;
				current_state = One_Coin_in_Machine;
			}

			else if(current_state == One_Coin_in_Machine)
			{
				if(verbose) 
				{
					cout << "\t{Coin Inserted} causes VM to switch from (One Coin in Machine) to (Two Coins in Machine)" << endl;
					cout << "\t\tProduct Backlights turned on" << endl;
				}
				current_state = Two_Coins_in_Machine;
				product_backlights = On;
			}
			break;

		case Refund_Lever_Pulled:
			if(current_state == One_Coin_in_Machine)
			{
				if(verbose) 
				{
					cout << "\t{Refund Lever Pulled} causes VM to switch from (One Coin in Machine) to (Refunding Coin)" << endl;
					cout << "\t\tAfter refunding coin, VM switches to (Idle)" << endl;
				}
				current_state = Refunding_Coin;
				current_state = Idle;
			}

			else if(current_state == Two_Coins_in_Machine)
			{
				if(verbose) 
				{
					cout << "\t{Refund Lever Pulled} causes VM to switch from (Two Coins in Machine) to (Refunding Coin)" <<endl;
					cout << "\t\tAfter refunding coin, Product Backlights turned off" << endl;
				}
				current_state = Refunding_Coin;
				product_backlights = Off;
				this_thread::sleep_for(chrono::seconds(1));
				if(verbose)
				{
					cout << "\t\tAfter waiting one second, VM refunds another coin and switches to (Idle)" << endl;

				}
				current_state = Idle;
			}
			break;

		case Product_Select_Pressed:
			if(current_state == Two_Coins_in_Machine)
			{
				if(verbose) 
				{
					cout << "\t{Product Select Pressed} causes VM to switch from (Two Coins in Machine) to (Selection_Validation)" << endl;
				}
				current_state = Selection_Validation;
			}
			break;

		case Product_Not_in_Stock:
			if(current_state == Selection_Validation)
			{
				if(verbose) 
				{
					cout << "\t{Product Not in Stock} causes VM to switch from (Selection Validation) to (Invalid Product Selection)" << endl;
					cout << "\t\tProduct NA Light turned on" << endl;
				}
				product_NA_light = On;
				current_state = Invalid_Product_Selection;
			}
			break;

		case Product_Select_Released:
			if(current_state == Selection_Validation)
			{
				if(verbose) 
				{
					cout << "\t{Product Select Released} causes VM to switch from (Selection Validation) to (Dispensing Product)" << endl;
					cout << "\t\tDispensing product" << endl;
					cout << "\t\tProduct Backlights turned off" << endl;
					cout << "\t\tVM switches from (Dispensing Product) to (Idle)" << endl;
				}
				current_state = Dispensing_Product;
				//Dispense Product
				product_backlights = Off;
				current_state = Idle;
			}

			else if(current_state == Invalid_Product_Selection)
			{
				if(verbose) 
				{
					cout << "\t{Product Select Released} causes VM to switch from (Invalid Product Selection) to (Two Coins in Machine)" << endl;
					cout << "\t\tProduct NA light turned off" << endl;
				}
				product_NA_light = Off;
				current_state = Two_Coins_in_Machine;
			}
			break;

		default:
			cerr << "Not valid event!\n";
			break;
	}
}

void VendingMachine::test()
{
	try
	{
		//-----ATTEMPTS ALL  VALID TRANSITIONS FOR EVERY STATE-----
		Event valid_transitions[] = 
		{
			Coin_Inserted,
			Refund_Lever_Pulled,
			Coin_Inserted,
			Coin_Inserted,
			Refund_Lever_Pulled,
			Coin_Inserted,
			Coin_Inserted,
			Product_Select_Pressed,
			Product_Not_in_Stock,
			Product_Select_Released,
			Product_Select_Pressed,
			Product_Select_Released
		}; 

		handleEvent(valid_transitions[0]);
		if(current_state != One_Coin_in_Machine || product_backlights != Off || product_NA_light != Off)
			throw logic_error("***FAILED TRANSITION AT INDEX 0***");
		handleEvent(valid_transitions[1]);
		if(current_state != Idle || product_backlights != Off || product_NA_light != Off)
			throw logic_error("***FAILED TRANSITION AT INDEX 1***");
		handleEvent(valid_transitions[2]);
		if(current_state != One_Coin_in_Machine || product_backlights != Off || product_NA_light != Off)
			throw logic_error("***FAILED TRANSITION AT INDEX 2***");
		handleEvent(valid_transitions[3]);
		if(current_state != Two_Coins_in_Machine || product_backlights != On || product_NA_light != Off)
			throw logic_error("***FAILED TRANSITION AT INDEX 3***");
		handleEvent(valid_transitions[4]);
		if(current_state != Idle || product_backlights != Off || product_NA_light != Off)
			throw logic_error("***FAILED TRANSITION AT INDEX 4***");
		handleEvent(valid_transitions[5]);
		if(current_state != One_Coin_in_Machine || product_backlights != Off || product_NA_light != Off)
			throw logic_error("***FAILED TRANSITION AT INDEX 5***");
		handleEvent(valid_transitions[6]);
		if(current_state != Two_Coins_in_Machine || product_backlights != On || product_NA_light != Off)
			throw logic_error("***FAILED TRANSITION AT INDEX 6***");
		handleEvent(valid_transitions[7]);
		if(current_state != Selection_Validation || product_backlights != On || product_NA_light != Off)
			throw logic_error("***FAILED TRANSITION AT INDEX 7***");
		handleEvent(valid_transitions[8]);
		if(current_state != Invalid_Product_Selection || product_backlights != On || product_NA_light != On)
			throw logic_error("***FAILED TRANSITION AT INDEX 8***");
		handleEvent(valid_transitions[9]);
		if(current_state != Two_Coins_in_Machine || product_backlights != On || product_NA_light != Off)
			throw logic_error("***FAILED TRANSITION AT INDEX 9***");
		handleEvent(valid_transitions[10]);
		if(current_state != Selection_Validation || product_backlights != On || product_NA_light != Off)
			throw logic_error("***FAILED TRANSITION AT INDEX 10***");
		handleEvent(valid_transitions[11]);
		if(current_state != Idle || product_backlights != Off || product_NA_light != Off)
			throw logic_error("***FAILED TRANSITION AT INDEX 11***");

		//SUCCESSFUL
		cout << "\t***Testing Passed***" << endl;
	}

	catch(const exception& e)
	{
		cerr << e.what() << endl;
	}
}	

//----------MAIN----------
int main()
{
	VendingMachine vm;
	VendingMachine test_vm;
	vm.enableVerbose();

	int choice;
	do
	{
		cout << "Command (0~insert // 1~refund // 2~press p.s. // 3~release p.s. // 4~p.n.i.stock // 5~test): ";
		cin >> choice;
		switch(choice)
		{
			case 5:
				test_vm.test();
				break;
			case 0:
				vm.handleEvent(Coin_Inserted);
				break;
			case 1:
				vm.handleEvent(Refund_Lever_Pulled);
				break;
			case 2:
				vm.handleEvent(Product_Select_Pressed);
				break;
			case 3:
				vm.handleEvent(Product_Select_Released);
				break;
			case 4:
				vm.handleEvent(Product_Not_in_Stock);
				break;
			default:
				cerr << "Invalid Selection!" << endl;
				break;
		}
	} while(choice >= 0);
	return 0;
}