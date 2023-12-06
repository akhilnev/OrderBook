#pragma once // what Does this do ?  --> https://stackoverflow.com/questions/1653958/why-are-ifndef-and-define-used-in-c-header-files

#ifndef ORDERBOOK_HPP
#define ORDERBOOK_HPP

#include <string>
#include <unordered_map>


std :: string TICKER = "GOOGL"; // ticker for the stock we are trading
struct Balances{
    std:: unordered_map <std :: string,int> balance; // STORES USD : VALUE, GOOGE : VALUE 
};


struct User{
    std :: string user_name;
    Balances balances;
};
// stores unique user name and balances for each user

struct Order{
    std :: string user_name;
    std :: string side;
    int price;
    int quantity;
};
// User can place an order to buy or sell a certain quantity of a stock at a certain price, and this order is stored in the order book or is matched and balances are exchanged 




class OrderBook{



    public:

}







#endif
