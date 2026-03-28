#pragma once
#include <iostream>
#include <memory>
#include "board.h"
#include "entities/player.h"
#include "gamestate.h"
#include "textureManager.h"
#include "window.h"
#include "entities/swordItem.h"
#include "utils/util.h"
#include "ui/view.h"
#include "core/entityManager.h"
#include "systems/inputs.h"
#include "systems/input.h"

namespace Core {

    struct Game
    {
        std::unique_ptr<Board> board;
        std::shared_ptr<Entities::Player> player;

        TextureManager textureManager;
        WindowRenderer WindowRenderer;
        EntityManager entityManager;

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