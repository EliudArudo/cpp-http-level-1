#include <string>
#include "store.h"

Store::animal_map Store::animals;

int Store::addItem(int id, std::string animal)
{
    Store::animals.insert(std::pair<int, std::string>(id, animal));

    return 0;
}

int Store::modifyItem(int id, std::string animal)
{

    Store::animal_map::iterator it;

    it = Store::animals.find(id);

    if (it == Store::animals.end())
        return 1;

    it->second = animal;

    return 0;
}

int Store::removeItem(int id)
{

    Store::animal_map::iterator it;

    it = Store::animals.find(id);

    if (it == Store::animals.end())
        return 1;

    Store::animals.erase(it);

    return 0;
}

Store::animal_map Store::readItem(int id)
{
    Store::animal_map::iterator it;

    it = Store::animals.find(id);

    if (it == Store::animals.end())
        return {};

    Store::animal_map item = {{it->first, it->second}};

    return item;
}

Store::animal_map Store::readItems()
{
    return Store::animals;
}
