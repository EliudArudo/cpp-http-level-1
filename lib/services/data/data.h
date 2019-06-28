#include <string>
#include <map>

class DataService
{
public:
    DataService();

    std::string static mapToString(std::map<std::string, std::string>);

    std::string static mapToVectorString(std::map<int, std::string> &);
};

// create object from string literal
// json j = "{ \"happy\": true, \"pi\": 3.141 }"_json;
// auto j3 = json::parse("{ \"happy\": true, \"pi\": 3.141 }");

// namespace ns
// {
//
// struct person // a simple struct to model a person
// {
//     std::string name;
//     std::string address;
//     int age;
// };
// } // namespace ns
// create a person
// ns::person p{"Ned Flanders", "744 Evergreen Terrace", 60};

// // conversion: person -> json
// json j = p;

// std::cout << j << std::endl;
// // {"address":"744 Evergreen Terrace","age":60,"name":"Ned Flanders"}

// // conversion: json -> person
// auto p2 = j.get<ns::person>();

// // that's it
// assert(p == p2);