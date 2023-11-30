cmake_minimum_required(VERSION 3.12)
project(OrderBook)

set(CMAKE_CXX_STANDARD 14)

# No need to set BOOST_ROOT when using Homebrew
# find_package(Boost REQUIRED COMPONENTS system thread)

# Find Boost (no need to specify components as they will be automatically found)
find_package(Boost REQUIRED)

# Set up the main executable
add_executable(order_book
        src/main.cpp
        src/orderbook.cpp
        src/server.cpp)

# Include Boost headers
target_include_directories(order_book PRIVATE ${Boost_INCLUDE_DIRS})

# Link against Boost libraries
target_link_libraries(order_book PRIVATE ${Boost_LIBRARIES})

