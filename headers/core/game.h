#pragma once
#include <iostream>
#include <memory>
#include "board.h"
#include "ui/view.h"
#include "entities/player.h"
#include "gamestate.h"
#include "textureManager.h"
#include "window.h"
#include "entities/swordItem.h"
#include "utils/util.h"
#include "core/entityManager.h"
#include "systems/inputs.h"
#include "systems/input.h"


namespace Core {

    class Board;
    struct EntityManager;

    struct Game
    {
        std::unique_ptr<Board> board;
        std::shared_ptr<Entities::Player> player;
        std::shared_ptr<Entities::Enemy> currentEnemy;
        
        Systems::Turn currentTurn = Systems::Turn::PLAYER;
        int selectedIndex = 0;
        bool inventorySelected = false;
        bool isCombatOver = false;
        Uint32 enemyTurnStartTime = 0;
        bool enemyTurnPending = false;

        TextureManager textureManager;
        WindowRenderer WindowRenderer;
        std::unique_ptr<EntityManager> entityManager;

        UI::View view;

        GameState state = GameState::TITLE;
        Uint32 lastEnemyUpdate = 0;
        const Uint32 enemyUpdateInterval = 800;

        void initGame();
        void run();
        void quit();

        void handleEvents(bool& r);
        void update(bool& r);
        void render();
    };
}