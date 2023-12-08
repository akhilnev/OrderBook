// OrderBook.cpp
// USES THE FIFO ORDER MATCHING ALGORITHM - FIRST IN FIRST OUT

#include "orderbook.hpp"
#include <iostream>
#include <iomanip> // For setw() and setfill()

using namespace std;

int Order::order_counter_bid = 0;
int Order::order_counter_ask = 0;

// BIDDER , ASKER ,  QUANTITY, PRICE
void OrderBook::flipBalance(const std::string &userId1, const std::string &userId2, double quantity, double price)
{
    if (users.find(userId1) != users.end() && users.find(userId2) != users.end())
    {
        if (users[userId1].user_balance.balance["USD"] >= price * quantity)
        {
            if (users[userId2].user_balance.balance[TICKER] >= quantity)
            {
                users[userId1].user_balance.balance["USD"] -= price * quantity;
                users[userId1].user_balance.balance[TICKER] += quantity;
                users[userId2].user_balance.balance["USD"] += price * quantity;
                users[userId2].user_balance.balance[TICKER] -= quantity;
                cout << "Funds and stocks transfered!" << endl;
            }
            else
            {
                cout << "User does not have enough balance to sell the stock" << endl;
            }
        }
        else
        {
            cout << "User does not have enough balance to buy the stock" << endl;
        }
    }
    else
    {
        cout << "One or both users not found" << endl;
    }
}

OrderBook::OrderBook()
{
    // Implementation of OrderBook constructor

    // Creating a couple of market maker users with predefined balances and bids/asks
    Balances balance1("USD", 10000);
    balance1.addBalance(TICKER, 1000);
    User marketMaker1("MarketMaker1", balance1); // User is made
    users["MarketMaker1"] = marketMaker1;        // Adding bids and asks for market makers

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
    users["MarketMaker2"] = marketMaker2;        // Adding bids and asks for market makers
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
    users["MarketMaker3"] = marketMaker3;        // Adding bids and asks for market makers
    Order bid5("MarketMaker3", "bid", 105, 10);
    Order bid6("MarketMaker3", "bid", 108, 10);
    bids.push_back(bid5);
    bids.push_back(bid6);
}

std::string OrderBook ::makeUser(std::string Username)
{
    User user(Username);    // create a user with default balance
    users[Username] = user; // add user to the users map
    cout << "User: " << Username << " created successfully " << endl;
    return "User created successfully";
}



std::string OrderBook::add_bid(std ::string Username, int Price, int Quantity)
{
    // Implementation of add_bid
    // We need to check if the username exists in the users array, then we compare the value of the bid with the lowest ask price, if bid is higher or equal to ask then we start flipping balances and traversing through ask array and bid quantity till condition is false, then if remQty > 0
    // we add the remaining quantity to the bids array else we return a message saying Bid Satisfied Successfully
    int remQty = Quantity;
    // sort asks in ascending order of price
    // std::sort(asks.begin(), asks.end(), [](const Order &a, const Order &b)
    //           { return a.price < b.price; });

    // TO MAINTAIN THE ORDER OF INSERTION AND FIFO ORDER MATCHING
    std::stable_sort(asks.begin(), asks.end(), [](const Order &a, const Order &b) {
    // If prices are equal, maintain the original order
    if (a.price == b.price) {
        // Compare based on the order of insertion
        return a.insertion_order_ask < b.insertion_order_ask;
    }
    // Otherwise, sort by price
    return a.price < b.price;
});

    // use logic from the commented function above
    for (auto it = asks.begin(); it != asks.end(); /* no increment here */)
    {
        if (remQty > 0 && Price >= it->price)
        {
            if (it->quantity > remQty)
            {
                it->quantity -= remQty;
                flipBalance(Username, it->user_name, remQty, it->price);
                cout << "Bid Satisfied Successfully at price: " << it->price << " and quantity: " << remQty << endl;
                remQty = 0;
                break;
            }
            else
            {
                remQty -= it->quantity;
                flipBalance(Username, it->user_name, it->quantity, it->price);
                cout << "Bid Satisfied Partially at price: " << it->price << " and quantity: " << it->quantity << endl;
                it = asks.erase(it); // get the next valid iterator after erasing
            }
        }
        else
        {
            ++it; // increment only when not erasing
        }
    }

    if (remQty > 0)
    {
        Order bid(Username, "bid", Price, remQty);
        bids.push_back(bid);
        cout << "Remaining quantity of bids added to Orderbook" << endl;
    }

    if (remQty == 0)
    {
        cout << "Complete Bid Satisfied Successfully" << endl;
    }

    return "Bid added/satified successfully."; // Placeholder, adjust return type as needed
}

std::string OrderBook::add_ask(std ::string Username, int Price, int Quantity)
{
    // Implementation of add_ask
    // Similar to the add_bid function we need to check if the username exists in the users array, then we compare the value of the ask with the highest bid price, if ask is lower or equal to bid then we start flipping balances and traversing through bid array and ask quantity till condition is false, then if remQty > 0
    // we add the remaining quantity to the asks array else we return a message saying Ask Satisfied Successfully

    int remQty = Quantity;
    // sort bids in descending order of price
    // std::sort(bids.begin(), bids.end(), [](const Order &a, const Order &b)
    //           { return a.price > b.price; });

    // TO MAINTAIN FIFO ORDER OF INSERTION
    std::stable_sort(bids.begin(), bids.end(), [](const Order &a, const Order &b) {
    // If prices are equal, maintain the original order
    if (a.price == b.price) {
        // Compare based on the order of insertion
        return a.insertion_order_bid < b.insertion_order_bid;
    }
    // Otherwise, sort by price
    return a.price > b.price;
});

    // use logic from the commented function above
    for (auto it = bids.begin(); it != bids.end(); /* no increment here */)
    {
        if (remQty > 0 && Price <= it->price)
        {
            if (it->quantity > remQty)
            {
                it->quantity -= remQty;
                flipBalance(it->user_name, Username, remQty, it->price);
                cout << "Ask Satisfied Successfully at price: " << it->price << " and quantity: " << remQty << endl;
                remQty = 0;
                break;
            }
            else
            {
                remQty -= it->quantity;
                flipBalance(it->user_name, Username, it->quantity, it->price);
                cout << "Ask Satisfied Partially at price: " << it->price << " and quantity: " << it->quantity << endl;
                it = bids.erase(it); // get the next valid iterator after erasing
            }
        }
        else
        {
            it++; // increment only when not erasing
        }
    }

    if (remQty > 0)
    {
        Order ask(Username, "ask", Price, remQty);
        asks.push_back(ask);
        cout << "Remaining quantity of asks added to Orderbook" << endl;
    }

    if (remQty == 0)
    {
        cout << "Complete Ask Satisfied Successfully" << endl;
    }
    return "Ask added successfully."; // Placeholder, adjust return type as needed
}

// DONE
std::string OrderBook::getBalance(std::string username)
{
    // Check if username exists is users array if it does we cout the balances else we return an error message saying user not found
    if (users.find(username) != users.end())
    {
        cout << "User found" << endl;
        cout << "User balance is as follows: " << endl;
        // Balance is a map of string and int so we need to iterate through the map to get the values
        for (auto it = users[username].user_balance.balance.begin(); it != users[username].user_balance.balance.end(); ++it)
        {
            // Print key : value format
            cout << it->first << " : " << it->second << endl;
        }
        return "Balance retrieved successfully.";
    }
    else
    {
        cout << "User not found!!" << endl;
        return "User not found";
    }
}

// DONE
std::string OrderBook::getQuote(int qty)
{
    // Implementation of getQuote
    // We will need to find lowest ask prices till the qty passed in is met we keep displaying lowest ask prices

    std::stable_sort(asks.begin(), asks.end(), [](const Order &a, const Order &b) {
    // If prices are equal, maintain the original order
    if (a.price == b.price) {
        // Compare based on the order of insertion
        return a.insertion_order_ask < b.insertion_order_ask;
    }
    // Otherwise, sort by price
    return a.price < b.price;
});

    for (auto it = asks.begin(); it != asks.end(); ++it)
    {
        if (qty > 0 && qty <= it->quantity)
        {
            cout << TICKER << "-> "
                 << "Quantity available: " << qty << " at " << it->price << " USD" << endl; // make the output look better

            return "Quote retrieved successfully.";
        }
        else if (qty > 0 && qty > it->quantity)
        {
            cout << TICKER << "-> "
                 << "Quantity available: " << it->quantity << " at " << it->price << " USD" << endl;
            qty -= it->quantity;
        }
        else
        {

            return "Quote retrieved successfully.";
        }
    }
    cout << "Quote retrieved successfully." << endl;
    return "Quote retrieved successfully.";
}

// DONE
std::string OrderBook::getDepth()
{
    // Sort asks in descending order of price
    std::sort(asks.begin(), asks.end(), [](const Order &a, const Order &b)
              { return a.price > b.price; });

    // Sort bids in descending order of price
    std::sort(bids.begin(), bids.end(), [](const Order &a, const Order &b)
              { return a.price > b.price; });
    std::string depthString = TICKER + " Depth:\n";
    // Construct a string representation of the depth

    for (const auto &ask : asks)
    {
        depthString += "\x1b[31m"; // Set color to red
        depthString += "Price: " + std::to_string(ask.price) + ", Quantity: " + std::to_string(ask.quantity) + "\n";
        depthString += "\x1b[0m"; // Reset color to default
    }
    depthString += "Asks above:\n";
    depthString += "Bids below:\n";
    for (const auto &bid : bids)
    {
        depthString += "\x1b[32m"; // Set color to green
        depthString += "Price: " + std::to_string(bid.price) + ", Quantity: " + std::to_string(bid.quantity) + "\n";
        depthString += "\x1b[0m"; // Reset color to default
    }

    cout << depthString << endl;
    return depthString;
}

std::string OrderBook ::addBalanace(std::string Username, std::string market, int value)
{
    if (users.find(Username) != users.end())
    {
        users[Username].user_balance.addBalance(market, value);
        cout << "Balance added successfully" << endl;
        return "Balance added successfully";
    }
    cout << "User not found!! Please enter the right Username to add balance!" << endl;
    return "User not found";
}

OrderBook::~OrderBook()
{
    // Implementation of the destructor, if needed
    // For example, you might need to release any allocated resources here
}

// SIMILARLY I WILL IMPLEMENT cancelAsk() function

void OrderBook :: cancelAsk(std:: string Username, int Price, int Quantity){

    // I need to go through the asks array and find the ask with the same price and quantity and then delete it from the array placed by the same User
    for(auto it = asks.begin() ; it!=asks.end(); ++it){
        if(it->user_name == Username && it->price == Price && it->quantity == Quantity){
            asks.erase(it);
            cout << "Ask cancelled successfully" << endl;
            return;
        }else if (it->user_name == Username && it->price == Price && it->quantity > Quantity){
            it->quantity -= Quantity;
            cout << "Ask cancelled successfully" << endl;
            return;
        }else if(it->user_name == Username && it->price == Price && it->quantity < Quantity){
            cout << "Ask quantity is less than the quantity you want to cancel\n\n";
            cout << "Please enter the right quantity to cancel and retry!\n\n";
            return;
            // RETHINK MAYBE - I will not return I will continue search as maybe some other order was placed by the same user with the same price and quantity

        }   
    }

}

void OrderBook :: cancelBid(std:: string Username, int Price, int Quantity){


    // I need to go through the bids array and find the bid with the same price and quantity and then delete it from the array placed by the same User 
    for(auto it = bids.begin(); it != bids.end(); ++it){
        if(it->user_name == Username && it->price == Price && it->quantity == Quantity){
            bids.erase(it);
            cout << "Bid cancelled successfully" << endl;
            return;
        }else if (it->user_name == Username && it->price == Price && it->quantity > Quantity){
            it->quantity -= Quantity;
            cout << "Bid cancelled successfully" << endl;
            return;
        }else if(it->user_name == Username && it->price == Price && it->quantity < Quantity){
            cout << "Bid quantity is less than the quantity you want to cancel\n\n";
            cout << "Please enter the right quantity to cancel and retry!\n\n";
            return;
            // RETHINK MAYBE - I will not return I will continue search as maybe some other order was placed by the same user with the same price and quantity

        }   
    }
    cout << "Bid not found!! Please enter the right Username, Price and Quantity to cancel the bid!" << endl;
    return;
}

int main()
{
    OrderBook EXCH;

    std::string market;
    int choice;
    std::string username;
    int price, quantity;

    cout << "\n=========== " <<"WELCOME TO THE " << TICKER << " MARKET "  << "AND HAPPY TRADING" << " =========== \n\n" << endl;
    cout << "\n=========== " << "CURRENT MARKET PRICES " << " =========== " << endl;
    EXCH.getDepth(); // getDepth() is called to display the current market

    while (true)
    {
        cout << "\n=========== " << TICKER << " Trading Platform ===========\n\n";
        cout << "\n========== Trading Platform Menu ==========\n";
        cout << "1. Sign Up User\n";
        cout << "2. Add Balance to User Account\n";
        cout << "3. Check Current Market Prices\n";
        cout << "4. Add Bid to " << TICKER << " v USD market\n";
        cout << "5. Sell your stocks in " << TICKER << " v USD Market\n";
        cout << "6. Get Current Quote to buy " << TICKER << " stocks\n";
        cout << "7. Check your current User Balance\n";
        cout << "8. Cancel Bid\n";
        cout << "9. Cancel Ask\n";
        cout << "10. Exit\n\n";
        cout << "Enter your choice: ";

        std::cin >> choice;

        switch (choice)
        {
        case 1:
            std::cout << "Enter username for new user: \n";
            std::cin >> username;
            EXCH.makeUser(username);
            break;
        case 2:
            std::cout << "Enter username to add balance: \n";
            std::cin >> username;
            std::cout << "Enter market (e.g., USD): \n";
            std::cin >> market;
            std::cout << "Enter balance value: \n";
            int value;
            std::cin >> value;
            EXCH.addBalanace(username, market, value);
            break;
        case 3:
            EXCH.getDepth();
            break;
        case 4:
            std::cout << "Enter username for bid: \n";
            std::cin >> username;
            std::cout << "Enter bid price: \n";
            std::cin >> price;
            std::cout << "Enter bid quantity: \n";
            std::cin >> quantity;
            EXCH.add_bid(username, price, quantity);
            break;
        case 5:
            std::cout << "Enter username for ask: \n";
            std::cin >> username;
            std::cout << "Enter ask price: \n";
            std::cin >> price;
            std::cout << "Enter ask quantity: \n";
            std::cin >> quantity;
            EXCH.add_ask(username, price, quantity);
            break;
        case 6:
            std::cout << "Enter quantity for quote: \n";
            std::cin >> quantity;
            EXCH.getQuote(quantity);
            break;
        case 7:
            std::cout << "Enter username to get balance: \n";
            std::cin >> username;
            EXCH.getBalance(username);
            break;
        case 8:
            std::cout << "Enter username to cancel bid: \n";
            std::cin >> username;
            std::cout << "Enter bid price: \n";
            std::cin >> price;
            std::cout << "Enter bid quantity: \n";
            std::cin >> quantity;
            EXCH.cancelBid(username, price, quantity);
            break;
        case 9:
            std::cout << "Enter username to cancel ask: \n";
            std::cin >> username;
            std::cout << "Enter ask price: \n";
            std::cin >> price;
            std::cout << "Enter ask quantity: \n";
            std::cin >> quantity;
            EXCH.cancelAsk(username, price, quantity);
            break;
        case 10:
            std::cout << "Exiting the trading platform. Goodbye!\n\n";
            return 0;
        default:
            std::cout << "Invalid choice. Please try again.\n\n";
        }
    }

    return 0;
}
