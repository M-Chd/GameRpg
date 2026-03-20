#include "systems/inventory.h"

Systems::Inventory::Inventory()
{
    items.reserve(5);
}

size_t Systems::Inventory::getMaxSize() const 
{
    return InventorySize;
}

size_t Systems::Inventory::getSize() const
{
    return items.size();
}

void Systems::Inventory::addItem(std::shared_ptr<Entities::Item> item)
{
    if (!item)
        std::cerr << "Item is null" << std::endl;

    if (items.size() >= InventorySize)
    {
        std::cout << "Inventory is full !" << "\n";
        return;
    }
    
    items.push_back(item);
}

void Systems::Inventory::removeItem(const std::string& name)
{
    for (auto it = items.begin(); it != items.end(); ++it) {
        if ((*it)->getName() == name) {
            items.erase(it);
            return;
        }
    }
}

void Systems::Inventory::pop()
{
    if (!items.empty()) items.pop_back();
}