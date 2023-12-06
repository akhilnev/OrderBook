// OrderBook.cpp

#include "OrderBook.hpp"
#include <iostream>
#include <iomanip>  // For setw() and setfill()


using namespace std;

std::string TICKER = "GOOGL"; // Say we are making this ticker to trade for a dummy google stock

// BIDDER , ASKER , PRICE , QUANTITY
void OrderBook::flipBalance(const std::string& userId1, const std::string& userId2, double quantity, double price) {
    // Implementation of flipBalance
    // This function is not defined in the provided header file, so you need to provide its implementation based on your requirements.
    // We need to check if the user exists in the users array if it does we can proceed to flip the balances else we return an error message
    if(users.find(userId1) != users.end() && users.find(userId2) != users.end()){
        // We need to check if the user has enough balance to buy the stock if it does we proceed to flip the balances else we return an error message
        if(users[userId1].user_balance.balance["USD"] >= price * quantity){
            // We need to check if the user has enough balance to sell the stock if it does we proceed to flip the balances else we return an error message
            if(users[userId2].user_balance.balance[TICKER] >= quantity){
                // We flip the balances
                users[userId1].user_balance.balance["USD"] -= price * quantity;
                users[userId1].user_balance.balance[TICKER] += quantity;
                users[userId2].user_balance.balance["USD"] += price * quantity;
                users[userId2].user_balance.balance[TICKER] -= quantity;
                cout << "Balances flipped successfully" << endl;
            }else{
                cout << "User does not have enough balance to sell the stock" << endl;
            }
        }else{
            cout << "User does not have enough balance to buy the stock" << endl;
        }
}
}

double OrderBook::fillOrders(const std::string& side, double price, double quantity, const std::string& userId) {
    // Implementation of fillOrders
    // This function is not defined in the provided header file, so you need to provide its implementation based on your requirements.
    return 0.0; // Placeholder, adjust return type as needed
}

OrderBook::OrderBook() {
    // Implementation of OrderBook constructor

    // Creating a couple of market maker users with predefined balances and bids/asks
    Balances balance1("USD", 10000);
    balance1.addBalance(TICKER, 1000);
    User marketMaker1("MarketMaker1", balance1); // User is made 
    users["MarketMaker1"] = marketMaker1;    // Adding bids and asks for market makers

    Order bid1("MarketMaker1", "bid", 110, 10);
    Order ask1("MarketMaker1", "ask", 115, 5);
    Order bid2("MarketMaker2", "bid", 111, 8);
    Order ask2("MarketMaker2", "ask", 119, 12);

    bids.push_back(bid1);
    asks.push_back(ask1);
    bids.push_back(bid2);
    asks.push_back(ask2);

    // Creating a couple of market maker users with predefined balances and bids/asks, with different balances to start maintaining liquidity in the order book
    Balances balance2("USD", 10000);
    balance2.addBalance(TICKER, 2000);
    User marketMaker2("MarketMaker2", balance2); // User is made
    users["MarketMaker2"] = marketMaker2;    // Adding bids and asks for market makers
    Order bid3("MarketMaker2", "bid", 109, 10);
    Order ask3("MarketMaker2", "ask", 125, 5);
    Order bid4("MarketMaker2", "bid", 112, 8);
    Order ask4("MarketMaker2", "ask", 120, 12);

    bids.push_back(bid3);
    asks.push_back(ask3);
    bids.push_back(bid4);
    asks.push_back(ask4);


    // Creating user 3 with predefined balances and bids/asks
    // market maker 3 has a lot of USD and wants to buy GOOGL
    Balances balance3("USD", 50000);
    balance3.addBalance(TICKER, 0);
    User marketMaker3("MarketMaker3", balance3); // User is made
    users["MarketMaker3"] = marketMaker3;    // Adding bids and asks for market makers
    Order bid5("MarketMaker3", "bid", 105, 10);
    Order bid5("MarketMaker3", "bid", 108, 10);
    bids.push_back(bid5);
}

std:: string OrderBook :: makeUser(std::string Username){
    User user(Username);
    cout << "User created successfully" << endl;
    return "User created successfully";
}



std::string OrderBook::add_bid(std :: string Username, int Price, int Quantity) {
    // Implementation of add_bid
    // We need to check if the username exists in the users array, then we compare the value of the bid with the lowest ask price, if bid is higher or equal to ask then we start flipping balances and traversing through ask array and bid quantity till condition is false, then if remQty > 0 
    //we add the remaining quantity to the bids array else we return a message saying Bid Satisfied Successfully
    int remQty = Quantity;
    //sort asks in ascending order of price
    std::sort(asks.begin(), asks.end(), [](const Order& a, const Order& b) {
        return a.price < b.price;
    });
    // CONTNUE FROM HERE

    return "Bid added successfully."; // Placeholder, adjust return type as needed
}

std::string OrderBook::add_ask(std :: string Username, int Price, int Quantity) {
    // Implementation of add_ask

    return "Ask added successfully."; // Placeholder, adjust return type as needed
}


// DONE 
std::string OrderBook::getBalance(std::string username) {
    // Check if username exists is users array if it does we cout the balances else we return an error message saying user not found
    if(users.find(username) != users.end()){
        cout << "User found" << endl;
        cout << "User balance is as follows: " << endl;
        // Balance is a map of string and int so we need to iterate through the map to get the values
        for(auto it = users[username].user_balance.balance.begin(); it != users[username].user_balance.balance.end(); ++it){
           // Print key : value format
              cout << it->first << " : " << it->second << endl;
        }
        return "Balance retrieved successfully.";
    }else{
        cout << "User not found!!" << endl;
        return "User not found";
    }
}



// DONE 
std::string OrderBook::getQuote(int qty) {
    // Implementation of getQuote
    // We will need to find lowest ask prices till the qty passed in is met we keep displaying lowest ask prices

    for(auto it = asks.begin(); it != asks.end(); ++it){
        if(qty > 0 && qty <= it->quantity){
            cout << TICKER << "-> " << "Quantity available: " << qty << "at" << it->price <<  endl;
            return "Quote retrieved successfully.";
        }else if (qty > 0 && qty > it->quantity){
            cout << TICKER << "-> " << "Quantity available: " << it->quantity << "at" << it->price <<  endl;
            qty -= it->quantity;
    }else {
        return "Quote retrieved successfully.";
    }
   
}
    return "Quote retrieved successfully."; 
}


// DONE
std::string OrderBook::getDepth() {
    // Sort asks in descending order of price
    std::sort(asks.begin(), asks.end(), [](const Order& a, const Order& b) {
        return a.price > b.price;
    });

    // Sort bids in descending order of price
    std::sort(bids.begin(), bids.end(), [](const Order& a, const Order& b) {
        return a.price > b.price;
    });

    // Construct a string representation of the depth
    std::string depthString = "Asks:\n";
    for (const auto& ask : asks) {
        depthString += "\x1b[31m";  // Set color to red
        depthString += "Price: " + std::to_string(ask.price) + ", Quantity: " + std::to_string(ask.quantity) + "\n";
        depthString += "\x1b[0m";   // Reset color to default
    }

    depthString += "Bids:\n";
    for (const auto& bid : bids) {
        depthString += "\x1b[32m";  // Set color to green
        depthString += "Price: " + std::to_string(bid.price) + ", Quantity: " + std::to_string(bid.quantity) + "\n";
        depthString += "\x1b[0m";   // Reset color to default
    }

    cout << depthString << endl;
    return depthString;
}
