#pragma once
#include <vector>
#include <iostream>
#include "entities/item.h"
#include <memory>

namespace Systems {

    class Inventory
    {
    public:
        
        Inventory();
        
        size_t getMaxSize() const;
        size_t getSize() const;
        const std::vector<std::shared_ptr<Entities::Item>>& getItems() const { return items; };
        
        void addItem(std::shared_ptr<Entities::Item> item);
        void removeItem(const std::string& name);
        void pop();
        
    private:
        std::vector<std::shared_ptr<Entities::Item>> items;
        const short InventorySize = 5;
    };
}