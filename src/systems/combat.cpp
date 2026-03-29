#include "systems/combat.h"
#include "core/gamestate.h"
#include <iostream>

void Systems::handlePlayerTurn(Core::Game &game,
                               Turn &turn,
                               std::shared_ptr<Entities::Enemy> enemy,
                               int &selectedIndex,
                               bool &inventorySelected,
                               bool &isCombatOver)
{

    const Uint8 *keys = SDL_GetKeyboardState(NULL);

    {
        if (keys[SDL_SCANCODE_RIGHT])
            selectedIndex = (selectedIndex + 1) % Utils::options.size();

        if (keys[SDL_SCANCODE_LEFT])
            selectedIndex = (selectedIndex - 1 + Utils::options.size()) % Utils::options.size();

        if (keys[SDL_SCANCODE_RETURN])
        {
            auto player = game.player;
            std::string choice = Utils::options[selectedIndex];

            if (choice == "Attack")
            {
                inventorySelected = false;
                player->attack(enemy);
            }
            else if (choice == "Protect")
            {
                inventorySelected = false;
                player->setPlayerProtecting();
            }
            else if (choice == "Inventory")
            {
                inventorySelected = true;
            }
            else if (choice == "Run")
            {
                inventorySelected = false;
                if (player->run(rand() % 2, rand() % 6))
                {
                    std::cout << "Player tried to run..." << std::endl;
                    isCombatOver = true;
                }
                else
                {
                    std::cout << "The run failed!" << std::endl;
                }
            }

            if (!isCombatOver && choice != "Inventory")
                turn = Turn::ENEMY;
        }
    }
}

void Systems::handleMobTurn(Core::Game &game, std::shared_ptr<Entities::Enemy> enemy)
{
    enemy->attack(game.player);
}

void Systems::StartFight(Core::Game &game, std::shared_ptr<Entities::Enemy> enemy)
{
    game.state = Core::GameState::FIGHT;
    game.currentEnemy = enemy;
    game.currentTurn = Turn::PLAYER;
    game.isCombatOver = false;

    std::cout << "Combat started against: " << enemy->getName() << std::endl;
}