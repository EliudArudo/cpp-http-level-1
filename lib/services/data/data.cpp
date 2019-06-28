#include <string>
#include <map>

#include "data.h"
#include "../../nlohmann/json.hpp"

using nlohmann::json;

std::string DataService::mapToString(std::map<std::string, std::string> victim)
{
    std::string result;

    json jmap(victim);
    return jmap.dump(4); // '4' there is for nice indentation
};

std::string DataService::mapToVectorString(std::map<int, std::string> &map_)
{
    typename std::map<int, std::string>::iterator it;

    std::string result = "[ ";

    auto final_iter = map_.end();
    for (it = map_.begin(); it != map_.end(); ++it)
    {

        json j;
        j[std::to_string(it->first)] = it->second;

        result += j.dump();

        if (std::next(it) != map_.end())
            result += ",";
    }

    result += " ]";

    return result;
}