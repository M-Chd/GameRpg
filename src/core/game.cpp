#include "core/game.h"

void Core::Game::initGame()
{
    if (!WindowRenderer.initWindow(900,608)) return;
    if (!WindowRenderer.initRenderer()) return;
    if (!WindowRenderer.initFonts()) return;

    textureManager.init(WindowRenderer.renderer);
    textureManager.load("player", "../assets/images/Miku_forgor.png");
    textureManager.load("enemy", "../assets/images/sinje.jpg");
    textureManager.load("sword", "../assets/images/minecraft_sword.jpg");
    textureManager.load("bow", "../assets/images/Minecraft_bow.jpg");
    textureManager.load("heal", "../assets/images/Heal_potion.png");
    
    board = std::make_unique<Board>();
    entityManager = std::make_unique<EntityManager>();

    entityManager->initEntities(*this);

}

void Core::Game::quit()
{
    WindowRenderer.quit();
}

void Core::Game::run()
{
    lastEnemyUpdate = SDL_GetTicks();

    bool running = true;

    while (running)
    {
        handleEvents(running);
        update(running);
        render();

        SDL_Delay(16); // ~60 FPS
    }
}

void Core::Game::handleEvents(bool& running)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT) { running = false; return; }

        if (e.type == SDL_KEYDOWN)
        {
            GameState currentState = state;

            switch (currentState)
            {
                case GameState::TITLE:
                    if (Systems::is_key_pressed(SDL_SCANCODE_SPACE))
                        state = GameState::GAMEPLAY;
                    break;

                case GameState::GAMEPLAY:
                    if      (Systems::is_key_pressed(SDL_SCANCODE_W)) player->move(*this, Utils::Direction::UP);
                    else if (Systems::is_key_pressed(SDL_SCANCODE_S)) player->move(*this, Utils::Direction::DOWN);
                    else if (Systems::is_key_pressed(SDL_SCANCODE_A)) player->move(*this, Utils::Direction::LEFT);
                    else if (Systems::is_key_pressed(SDL_SCANCODE_D)) player->move(*this, Utils::Direction::RIGHT);
                    else if (Systems::is_key_pressed(SDL_SCANCODE_RETURN)) state = GameState::PAUSE;
                    break;

                case GameState::FIGHT:
                    Systems::handlePlayerTurn(*this, currentTurn, currentEnemy,
                                              selectedIndex, inventorySelected, isCombatOver);
                    break;

                case GameState::PAUSE:
                    if (Systems::is_key_pressed(SDL_SCANCODE_ESCAPE)) state = GameState::GAMEPLAY;
                    else if (Systems::is_key_pressed(SDL_SCANCODE_RETURN)) running = false;
                    break;

                case GameState::GAMEOVER:
                    if (Systems::is_key_pressed(SDL_SCANCODE_RETURN)) running = false;
                    break;
            }
        }
    }
}

void Core::Game::update(bool& running)
{
    if (player->getStats().healthPoint <= 0)
    {
        state = GameState::GAMEOVER;
        return;
    }

    if (state == GameState::GAMEPLAY)
    {
        Uint32 currentTime = SDL_GetTicks();

        if (currentTime - lastEnemyUpdate > enemyUpdateInterval)
        {
            entityManager->enemyAlgorithm(*this);
            lastEnemyUpdate = currentTime;
        }

        if (board->getEnemies().empty())
            entityManager->spawnEnemy(*board, player);

        entityManager->spawnHeal(*board, player);
    }
    else if (state == GameState::FIGHT)
    {
        if (currentTurn == Systems::Turn::ENEMY && !isCombatOver)
        {
            Systems::handleMobTurn(*this, currentEnemy);
            currentTurn = Systems::Turn::PLAYER;
        }

        if (isCombatOver || currentEnemy->getStats().healthPoint <= 0)
        {
            if (currentEnemy->getStats().healthPoint <= 0) {
                player->getStats().gainXp(currentEnemy->getStats().level * 3);
                board->deleteEntityAt(currentEnemy->getPos());
            }
            state = GameState::GAMEPLAY;
            currentEnemy = nullptr;
        }
    }
}

void Core::Game::render()
{
    SDL_SetRenderDrawColor(WindowRenderer.renderer, 0, 0, 0, 255);
    SDL_RenderClear(WindowRenderer.renderer);

    switch (state)
    {
        case GameState::TITLE:
            view.drawTitleScreen(*this);
            break;

        case GameState::PAUSE:
            view.drawPauseScreen(*this);
            break;

        case GameState::GAMEOVER:
            view.drawGameOverScreen(*this);
            break;

        case GameState::FIGHT:
            if (currentEnemy) {
                view.drawCombat(*this, currentEnemy, currentTurn, selectedIndex, inventorySelected);
            }
            break;

        case GameState::GAMEPLAY:
            view.draw(*this);
            break;
    }

    SDL_RenderPresent(WindowRenderer.renderer);
}