#include <iostream>
#include <string>
#include <cassert>
using namespace std;

bool isValidOrderString(string orders);
double cost(string orders);
int howManyCombos(string orders, int whichCombo);
int howManyShakes(string orders, string whichShake);



bool isValidOrderString(string orders) // returns true if parameter is a well-formed order string and false otherwise
{
    char c;
    bool quantity = true; // determines whether number is order quantity or type; !quantity means looking at order type
    bool underscore = false; // underscores can only come after order type; !underscore means there is no underscore
    int iq = 0; // counter to check if individual order quantity is > 50 or not
    int tq = 0; // counter to check if total order quantity is > 50 or not
   
    if (orders.size() == 0) // empty string cannot be valid
        return false;
    
    for (size_t i = 0; i < orders.size(); i++) // reads the string from beginning until end
    {
        c = orders[i]; // c is character at the position i which increments up from 0
        
        switch (c)
        {
            case '0':
                if (!quantity) // !quantity means looking at order type and order type cannot be 0
                    return false;
                else // looking at order quantity
                {
                    if (iq == 0) // there cannot be 0 orders of something
                        return false;
                    else // if there is some quantity of order with 0 in it (double digits)
                    {
                        iq *= 10; // multiply the individual quantity by 10
                        iq += 0;
                        if (iq >= 50) // individual order cannot be more than or equal to 50
                            return false;
                       if (i == orders.size() - 1) // if this is the last char then return false as it cannot end at order quantity without type
                           return false;
                    }
                }
                break;
            case '1':
            case '2':
            case '3': // 1-3 act the same as they can all be seen as quantity or order type
                if (underscore) // if there is an underscore, return false
                    return false;
                else if (!quantity) // !quantity means looking at order type
                {
                    quantity = true; // switches condition to now look at order quantity (after looking at order type)
                    underscore = true; // switches condition to now look for underscore (after looking at order type)
                }
                else // looking at order quantity
                {
                    iq *= 10; // multiply the individual quantity by 10
                    iq += (c - 48); // uses ASCII table to convert char to int as each int c is 48 away from decimal value
                    if (iq >= 50) // individual order cannot be more than or equal to 50
                        return false;
                    if (i == orders.size() - 1) // if this is the last char then return false as it cannot end at order quantity without type
                        return false;
                }
                break;
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': // 4-9 all act the same as they can only be seen as order quantity
                if (!quantity || underscore) // if looking at order type or underscore then return false
                    return false;
                if (quantity) // if looking at quantity
                {
                    iq *= 10; // multiply the individual quantity by 10
                    iq += (c - 48); // uses ASCII table to convert char to int as each int c is 48 away from decimal value
                    if (iq >= 50) // individual order cannot be more than or equal to 50
                        return false;
                    if (i == orders.size() - 1) // if this is the last char then return false as it cannot end at order quantity without type
                        return false;
                }
                break;
            case ':':
                if (!quantity || underscore) // if looking at order type or underscore or c is '0' then return false
                    return false;
                else // if looking at order quantity
                {
                    quantity = false; // looks at order type
                    tq += iq; // adds individual quantity to total quantity to check < 50
                    if (tq >= 50) // total quantity cannot be more than or equal to 50
                        return false;
                    iq = 0; // resets individual quantity to 0 for next upcoming order
                    if (i == orders.size() - 1) // if : is the last char then return false as it cannot end at :
                        return false;
                }
                break;
            case 'C':
            case 'V':
            case 'S': // c, v, s act the same as they are all shake types
                if (quantity || underscore) // if looking at order quantity or underscore then return false
                    return false;
                else // if looking at order type
                {
                    quantity = true; // looks at order quantity for next order (after looking at order type)
                    underscore = true; // looks for underscore for next order(afer looking at order type)
                }
                break;
            case '_':
                if (!underscore) // if not looking at underscore but there is an underscore, return false
                    return false;
                else // if looking at underscore and there is underscore
                {
                    quantity = true; // looks at order quantity for next order (after looking at underscore)
                    underscore = false; // no longer looks for underscore after underscore
                    if (i == orders.size() - 1) // if underscore is the last char then return false as it cannot end with underscore
                        return false;
                }
                break;
            default:
                return false;
                break;
        }
    }
    return true;
}



int howManyCombos(string orders, int whichCombo) // if the parameter is a valid string, the function should count up how many of the particular ordered combo has been requested. the only valid values for the int parameter is the number 1, 2 or 3. any other int parameter value should result in a count of -1. if the order string is itself not a well-formed order string, return -1.
{
    if (whichCombo != 1 && whichCombo != 2 && whichCombo != 3)
        return -1;
    
    if (!isValidOrderString(orders)) // if the order string is invalid, return -1
        return -1;

    char c;
    bool quantity = true; // determines whether number is order quantity or type; !quantity means looking at order type
    int iq = 0;
    int tq = 0;
        
    for (size_t i = 0; i < orders.size(); i++) // reads the string from beginning until end
    {
        c = orders[i]; // c is character at the position i which increments up from 0
            
        switch (c)
        {
            case '1':
            case '2':
            case '3': // 1-3 act the same as they can all be seen as quantity or order type
                if (!quantity) // !quantity means looking at order type
                {
                    if (c == (whichCombo + 48)) // if order type matches the int the user input
                        tq += iq; // add individual total to final total
                    iq = 0; // resets individual total to 0
                    quantity = true; // switches condition to now look at order quantity (after looking at order type)
                }
                else // looking at order quantity
                {
                    iq *= 10; // multiply the individual quantity by 10
                    iq += (c - 48); // uses ASCII table to convert char to int as each int c is 48 away from decimal value
                }
                break;
            case '0':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': // 4-9 all act the same as they can only be seen as order quantity
                iq *= 10; // multiply the individual quantity by 10
                iq += (c - 48); // uses ASCII table to convert char to int as each int c is 48 away from decimal value
                quantity = false; // looks at order type now
                break;
            case 'C':
            case 'V':
            case 'S': // c, v, s act the same as they are all shake types and are still valid order types
                quantity = true; // looks at order quantity for next order (after looking at order type)
                iq = 0; // resets individual quantity to 0
                break;
            case ':':
                if (quantity) // if looking at order quantity
                {
                    quantity = false; // looks at order type
                }
                break;
        }
    }
    return tq;
}



int howManyShakes(string orders, string whichShake) // if the string parameter is a valid order string, the function should count up how many of the particular ordered shake has been requested. the only valid values for the whichShake parameter are "Chocolate", "Vanilla" or "Strawberry". any other whichShake value should result in a count of -1. if the order string is not a well-formed order string, return -1.
{
    if (whichShake != "Chocolate" && whichShake != "Vanilla" && whichShake != "Strawberry") // invalid values for whichShake
        return -1;
    
    if (!isValidOrderString(orders)) // if the order string is invalid, return -1
        return -1;
    
    char c;
    bool quantity = true; // determines whether number is order quantity or type; !quantity means looking at order type
    int iq = 0;
    int tq = 0;
    
    for (size_t i = 0; i < orders.size(); i++) // reads the string from beginning until end
    {
        c = orders[i]; // c is character at the position i which increments up from 0
        
        switch (c)
        {
            case '1':
            case '2':
            case '3':
                if (quantity)
                {
                    iq *= 10; // multiply the individual quantity by 10
                    iq += (c - 48); // uses ASCII table to convert char to int as each int c is 48 away from decimal value
                }
                break;
            case '0':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                if (quantity)
                {
                    iq *= 10; // multiply the individual quantity by 10
                    iq += (c - 48); // uses ASCII table to convert char to int as each int c is 48 away from decimal value
                }
                quantity = false; // looks at order type now
                break;
            case 'C':
            case 'V':
            case 'S':
                if (!quantity) // !quantity means looking at order type
                {
                    if (whichShake[0] == c) // if order type matches the int the user input
                        tq += iq; // add individual total to final total
                    iq = 0; // resets individual total to 0
                    quantity = true; // switches condition to now look at order quantity (after looking at order type)
                }
                break;
            case ':':
                quantity = false; // looks at order type
                break;
            case '_':
                quantity = true; // looks at order quantity now
                iq = 0;
        }
    }
    return tq;
}



double cost(string orders) // if the parameter is a valid string, the function should read each order and return the total cost but invalid order strings should return a cost of -1.00
{
    const double combo1 = 9.45; // double-double combo (combo 1) costs $9.45 each
    const double combo2 = 7.95; // cheeseburger combo (combo 2) costs $7.95 each
    const double combo3 = 7.55; // hamburger combo (combo 3) costs $7.55 each
    const double shake = 2.85; // each shake costs $2.85 each
    double costcombo1 = 0;
    double costcombo2 = 0;
    double costcombo3 = 0;
    double costsshake = 0;
    double costcshake = 0;
    double costvshake = 0; // cost of each order type respectively that buyer will pay
    double totalprice = 0.0;
    
    if (!isValidOrderString(orders)) // if the order string is invalid, return -1.00
        return -1.00;
    
    // if the order string is valid
    // for food combos
    costcombo1 += howManyCombos(orders, 1) * combo1; // total cost of combo 1
    costcombo2 += howManyCombos(orders, 2) * combo2; // total cost of combo 2
    costcombo3 += howManyCombos(orders, 3) * combo3; // total cost of combo 3
    
    // for shakes
    costsshake += howManyShakes(orders, "Strawberry") * shake; // total cost of strawberry shake
    costcshake += howManyShakes(orders, "Chocolate") * shake; // total cost of chocolate shake
    costvshake += howManyShakes(orders, "Vanilla") * shake; // total cost of vanilla shake
    
    totalprice += costcombo1 + costcombo2 + costcombo3 + costsshake + costcshake + costvshake; // total price is that price of all of order types added up
    
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2); // makes sure cost is in 2 decimal points
    return totalprice;
}

int main ()
{
    //asserts for isValidOrderString
    assert(isValidOrderString("4:1") == true); // 4 orders of double-doubles
    assert(isValidOrderString("2:1_2:1") == true); // splitting the 4 orders of double-doubles into 2
    assert(isValidOrderString("2:2_2:1") == true); // 2 orders of double-doubles and 2 orders of cheeseburgers
    assert(isValidOrderString("2:1_1:C") == true); // 2 orders of double-doubles and 1 order of chocolate shake
    assert(isValidOrderString("30:1_5:1_14:1") == true); // 49 orders total
    assert(isValidOrderString("1:1_1:2_1:3_1:C_1:S_1:V") == true); // 1 order of each item menu
    assert(isValidOrderString("") == false); // empty string
    assert(isValidOrderString(" ") == false); // string with space
    assert(isValidOrderString("40 : C ") == false); // spaces in between
    assert(isValidOrderString("1_1") == false); // invalid string
    assert(isValidOrderString("4:5") == false); // invalid order type with number
    assert(isValidOrderString("4:0") == false); // invalid order type with number
    assert(isValidOrderString("1:1abc") == false); // invalid order type with letters
    assert(isValidOrderString("+4:1") == false); // invalid order quantity with + sign
    assert(isValidOrderString("1:1_-12:2") == false); // invalid order quantity with - sign
    assert(isValidOrderString("0:1") == false); // 0 orders of double-double
    assert(isValidOrderString("1:1_2:2_0:3") == false); // invalid order quantity "0"
    assert(isValidOrderString("100:1") == false); // invalid order quantity > 49 individually
    assert(isValidOrderString("40:1_10:1_1:1") == false); // invalid order quantity > 49 total
    assert(isValidOrderString("500:1_500:2") == false); // invalid order quantity > 49 total and individually
    assert(isValidOrderString("xyz") == false); // bad characters
    assert(isValidOrderString("1:c") == false); // invalid order type with lowercase
    assert(isValidOrderString("1:1 zzz") == false); // extra characters at the end
    assert(isValidOrderString("20:1_30:2") == false); // 50 total orders
    assert(isValidOrderString("1:1_") == false); // incomplete order ending with _
    assert(isValidOrderString("1:1_2:") == false); // incomplete order ending with :
    assert(isValidOrderString("1:1_2") == false); // incomplete order ending with order quantity
    assert(isValidOrderString("001:1") == false); // leading zeros
    
    cout << "ALL STRING CASES PASSED!" << endl;
    
    //asserts for howManyCombos
    assert(howManyCombos("5:4", 4) == -1); // invalid string type
    assert(howManyCombos("5:3", 6) == -1); // invalid parameter of combo type
    assert(howManyCombos("4:1", 1) == 4); // 4 orders of double-double combo
    assert(howManyCombos("2:1_2:1", 1) == 4); // 4 orders of double-double combo split into 2 orders
    assert(howManyCombos("2:2_2:1", 2) == 2); // split into 2 orders and different types
    assert(howManyCombos("4:2_2:1_3:1", 1) == 5); // split into 3 orders and different types
    assert(howManyCombos("10:2_2:1_3:1", 2) == 10); // double digit order quantity
    assert(howManyCombos("1:C_2:2", 2) == 2); // includes shake
    
    cout << "ALL COMBO CASES PASSED!" << endl;

    //asserts for howManyShakes
    assert(howManyShakes("5:4", "Strawberry") == -1); // invalid string order
    assert(howManyShakes("5:c", "Strawberry") == -1); // invalid string order
    assert(howManyShakes("1:C", "oops") == -1); // invalid parameter of string shake
    assert(howManyShakes("4:C", "Chocolate") == 4); // 4 orders of chocolate shake
    assert(howManyShakes("2:C_2:C", "Chocolate") == 4); // 4 orders of chocolate shake split into 2 orders
    assert(howManyShakes("2:C_2:S", "Chocolate") == 2); // split into 2 orders and different types
    assert(howManyShakes("2:C_2:S_9:V", "Vanilla") == 9); // split into 3 orders and different types
    assert(howManyShakes("1:2_2:S", "Strawberry") == 2); // includes burger combo order
    
    cout << "ALL SHAKE CASES PASSED!" << endl;
    
    //asserts for cost
    assert(cost("") == -1.00); // invalid string order
    assert(cost("4:1") == 37.80);
    assert(cost("2:1_2:1") == 37.80);
    assert(cost("2:2_2:1") == 34.80);
    assert(cost("2:1") == 18.90);
    assert(cost("3:2") == 23.85);
    assert(cost("4:3") == 30.20);
    assert(cost("30:C") == 85.50);
    assert(cost("15:S_1:3") == 50.30);
    assert(cost("1:1_1:2_1:3_1:C_1:S_1:V") == 33.50); // 1 of each type
    
    cout << "ALL COST CASES PASSED!" << endl;
    return 0;
}
