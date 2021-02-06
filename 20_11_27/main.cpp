#include <iostream>
#include <map>
#include <vector>
#include <set>


class Property
{
public:
    std::string name;
    std::vector<std::string> descriptions;

    Property(std::string name): name(name){}

};

class Item
{
public:
    std::string name;
    std::map<std::string, Property> properties;

    Item(std::string name): name(name){}

    Property add_property(Property new_property)
    {
        return properties.insert({new_property.name, new_property}).first->second;
    }
};

class Bag
{
public:
    std::multimap<std::string, Item> items;
    std::set<std::string> names;

    auto add_item(Item new_item)
    {
        names.insert(new_item.name);
        return items.insert(std::pair<std::string, Item>(new_item.name, new_item));
    }

    Item get_item(std::string name)
    {
        auto item = items.find(name);
        items.erase(item);
        if(items.find(name) == items.end())
            names.erase(name);
        return item->second;
    }
};

void print_item(Item item)
{
    std::cout << "Item name: " << item.name << '.';
    for(auto prop : item.properties)
        std::cout << " Item property: " << prop.second.name << ' .';
    std::cout << std::endl;
}

int main() {
    Property first_p("first"), second_p( "second"),
        third_p( "third");
    Item first_i( "first item"), second_i( "first item"),
        third_i( "third item");
    first_i.add_property(first_p); second_i.add_property(second_p); third_i.add_property(third_p);

    Bag bag;
    bag.add_item(first_i); bag.add_item(second_i); bag.add_item(third_i);
    //check that values are in the bag
    for(auto & item : bag.items)
    {
        Item current_item = item.second;
        print_item(current_item);
    }
    std::cout << std::endl;

    //check that set deletes name when there is no such item in the bag
    for(auto & item_name : bag.names)
    {
        std::cout << "Item name: " << item_name << std::endl;
    }
    std::cout << std::endl;
    for(auto & item_name : bag.names)
    {
        std::cout << "Item name: " << item_name << std::endl;
    }
    std::cout << std::endl;


    bag.get_item("third item");
    for(auto & item_name : bag.names)
    {
        std::cout << "Item name: " << item_name << std::endl;
    }
    bag.get_item("first item");
    std::cout << bag.names.size() << std::endl;
    bag.get_item("first item");
    std::cout << bag.names.size() << std::endl;
    std::cout << std::endl;

    return 0;
}
