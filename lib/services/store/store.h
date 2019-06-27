// static:
// Once the variable has been initialized, it remains in memory until the end of the program

#include <string>
#include <map>

class Store
{
public:
    Store();

    struct Animal
    {
        int id;
        std::string name;
    };

    typedef std::map<int, std::string> animal_map;

    static int addItem(int, std::string);
    static animal_map readItem(int);
    static int modifyItem(int, std::string);
    static int removeItem(int);
    static animal_map readItems();

private:
    static animal_map animals;
};