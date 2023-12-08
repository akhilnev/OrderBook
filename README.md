# OrderBook

## Notes to TA:

- I have implemented an Orderbook in C++ which uses the FIFO order matching algorithm!
- The orderbook is currently designed for the GOOGL v USD market to simplify bids and asks.
- Market makers are initialized with predefined balances and bids/asks, akin to NPC characters in a game.
- To run the program, use `make`, and to clean executables, use `make clean`.

**Quick Demo:** [Click here](#) <!-- Provide the link to your demo here -->

## Working of the OrderBook

### Overview
The OrderBook is a C++ implementation of a financial order book, focusing on a sample GOOGL v USD market. It uses the FIFO (First In, First Out) order matching algorithm.

### Initialization
- Market makers are initialized with predefined balances and bids/asks in the constructor.
- Users can be created using the `makeUser` function.

### Trading
- Users can place bids (`add_bid`) and asks (`add_ask`) to the order book.
- The order book matches bids and asks based on price and quantity.
- Balances are adjusted using the `flipBalance` function.

### User Interaction
- Users can check their balance using `getBalance`.
- The `getQuote` function provides the best bid and ask prices and quantities.
- `getDepth` displays the entire order book, showing all bids and asks.

### Additional Features
- Users can add balance (`addBalance`) to their accounts.
- Bids and asks can be canceled using `cancelBid` and `cancelAsk`.

## Code Overview

### OrderBook.cpp
- Implements the OrderBook class, including functions for bid/ask, balance, quote, depth, user creation, and balance addition.

### orderbook.hpp
- Defines the structures for Balances, User, and Order.
- Declares the OrderBook class with member functions and the TICKER variable.

## How to Run

```bash
make        # Compile the program
./orderbook # Run the compiled executable
make clean  # Remove the executable

## Trading Platform Menu Options

1. **Sign Up User (`1`):**
   - Creates a new user with a specified username.

2. **Add Balance to User Account (`2`):**
   - Adds balance to a user's account in a specified market (e.g., USD).

3. **Check Current Market Prices (`3`):**
   - Displays the current bid and ask prices.

4. **Add Bid to GOOGL v USD market (`4`):**
   - Places a bid in the GOOGL v USD market.

5. **Sell your stocks in GOOGL v USD Market (`5`):**
   - Places an ask in the GOOGL v USD market.

6. **Get Current Quote to buy GOOGL stocks (`6`):**
   - Retrieves the best bid and ask prices for a specified quantity.

7. **Check your current User Balance (`7`):**
   - Displays the balance for a specific user.

8. **Cancel Bid (`8`):**
   - Cancels a previously placed bid.

9. **Cancel Ask (`9`):**
   - Cancels a previously placed ask.

10. **Exit (`10`):**
    - Exits the trading platform.

**Note:** This is mainly a Template right now and my next steps would be to integrate the same with real-time Market data 
