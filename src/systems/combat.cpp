#include "systems/combat.h"
#include "core/gamestate.h"
#include <iostream>

void Systems::handlePlayerTurn(Core::Game& game,
                               Turn& turn,
                               std::shared_ptr<Entities::Enemy> enemy,
                               int& selectedIndex,
                               bool& inventorySelected,
                               bool& isCombatOver)
{
    SDL_Event e;
    std::vector<std::string> options = {"Attack", "Protect", "Inventory", "Run"};

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT) exit(0);

        if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.scancode)
            {
                case SDL_SCANCODE_RIGHT:
                    selectedIndex = (selectedIndex + 1) % options.size();
                    break;

                case SDL_SCANCODE_LEFT:
                    selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
                    break;

                case SDL_SCANCODE_RETURN:
                {
                    auto player = game.player;
                    std::string choice = options[selectedIndex];

                    if (choice == "Attack") {
                        inventorySelected = false;
                        player->attack(enemy);
                        player->setPlayerProtecting();
                    }
                    else if (choice == "Protect") {
                        inventorySelected = false;
                        player->setPlayerProtecting();
                    }
                    else if (choice == "Inventory") {
                        inventorySelected = true;
                    }
                    else if (choice == "Run") {
                        inventorySelected = false;
                        if (player->run(rand() % 2, rand() % 6)) {
                            std::cout << "Player tried to run..." << std::endl;
                            isCombatOver = true;
                        } else {
                            std::cout << "The run failed!" << std::endl;
                        }
                    }

                    if (!isCombatOver)
                        turn = Turn::ENEMY;

                    break;
                }

                default: break;
            }
        }
    }
}

void Systems::handleMobTurn(Core::Game& game, std::shared_ptr<Entities::Enemy> enemy)
{
    SDL_Delay(500);
    enemy->attack(game.player);
    SDL_Delay(500);
}

void Systems::StartFight(Core::Game& game, std::shared_ptr<Entities::Enemy> enemy)
{
    game.state = Core::GameState::FIGHT;
    game.currentEnemy = enemy; 
    game.currentTurn = Turn::PLAYER;
    game.isCombatOver = false;
    
    std::cout << "Combat started against: " << enemy->getName() << std::endl;
}