#pragma once // what Does this do ?  --> https://stackoverflow.com/questions/1653958/why-are-ifndef-and-define-used-in-c-header-files

#ifndef ORDERBOOK_HPP
#define ORDERBOOK_HPP
#include <string>
#include <unordered_map>
#include <vector>


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
private:

    std :: vector<Order> bids;
    std :: vector<Order> asks;
    std :: unordered_map <std :: string,User> users; // stores unique user name and balances for each user
    void flipBalance(const std::string& userId1, const std::string& userId2, double quantity, double price);
    double fillOrders(const std::string& side, double price, double quantity, const std::string& userId);

    public:
    OrderBook(); // constructor
   ~OrderBook();
    std:: string add_bid(Order bid, User user); // adds a bid or ask to the order book
    std:: string add_ask(Order ask, User user); // adds a bid or ask to the order book
    std:: string getBalance(User username); // returns the balance of a user
    std:: string getQuote(); // returns the best bid and ask prices and quantities
    std:: string getDepth(); // returns the entire order book and shows all bids and asks

};


#endif
