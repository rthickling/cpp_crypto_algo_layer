#include "CcexOrderExecutor.h"

#include <ccapi_cpp/ccapi_macro.h>

#include <boost/log/trivial.hpp>
#include <boost/json.hpp>

#include <iostream>
#include <string>
#include <map>

auto main(int argc, char* argv[]) -> int
{
    if(argc < 3) 
    {
        std::cout 
            << "Usage: " << argv[0] 
            << " API_key API_secret [Passphrase]"
            << std::endl;
        return 1;
    }

    const std::map<std::string, std::string> exchange_names = {
        {"ftx", CCAPI_EXCHANGE_NAME_FTX},
        {"coinbase", CCAPI_EXCHANGE_NAME_COINBASE},
        {"bitmex", CCAPI_EXCHANGE_NAME_BITMEX},
    };

    BOOST_LOG_TRIVIAL(info) << "Running Ccex test.";

    enum {name_arg, market_arg, symbol_arg, side_arg, size_arg, type_arg, price_arg, key_arg, secret_arg, phrase_arg};

    CcexOrderExecutor executor{exchange_names.at(argv[market_arg]), 0, argv[key_arg], argv[secret_arg], argc > 9 ? argv[phrase_arg] : ""};

    using Side = OrderExecutor::Side;
    using OrderType = OrderExecutor::OrderType;
    BOOST_LOG_TRIVIAL(info) << argv[symbol_arg] << "Running: " << std::endl; 
    executor.new_order(
        argv[symbol_arg], 
        std::string(argv[side_arg]) == "buy" ? Side::buy : Side::sell, 
        std::stod(argv[size_arg]), 
        std::string(argv[type_arg]) == "limit" ? OrderType::limit : OrderType::market, 
        std::stod(argv[price_arg]));

    return 0;
}