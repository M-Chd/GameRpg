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
        if (e.type == SDL_QUIT)
        {
            running = false;
            quit();
        }
        else if (e.type == SDL_KEYDOWN)
        {
            SDL_Scancode key = e.key.keysym.scancode;

            switch (state)
            {
                case GameState::TITLE:
                    if (key == SDL_SCANCODE_SPACE)
                        state = GameState::GAMEPLAY;
                    break;

                case GameState::GAMEPLAY:
                    if (key == SDL_SCANCODE_ESCAPE)
                        state = GameState::PAUSE;
                    break;

                case GameState::PAUSE:
                    if (key == SDL_SCANCODE_ESCAPE)
                        state = GameState::GAMEPLAY;
                    else if (key == SDL_SCANCODE_RETURN)
                        running = false;
                    break;

                case GameState::GAMEOVER:
                    if (key == SDL_SCANCODE_RETURN)
                        running = false;
                    break;
            }
        }
    }
}

void Core::Game::update(bool& running)
{
    if (state != GameState::GAMEPLAY)
        return;

    if (player->getStats().healthPoint == 0)
    {
        state = GameState::GAMEOVER;
        return;
    }

    Uint32 currentTime = SDL_GetTicks();

    if (currentTime - lastEnemyUpdate > enemyUpdateInterval)
    {
        entityManager->enemyAlgorithm(*this);
        lastEnemyUpdate = currentTime;
    }

    for (const auto& [key, dir] : Systems::keyToDirection)
    {
        if (Systems::is_key_pressed(key))
        {
            player->move(*this, dir);
        }
    }

    if (board->getEnemies().empty())
    {
        entityManager->spawnEnemy(*board, player);
    }

    entityManager->spawnHeal(*board, player);
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

        case GameState::GAMEPLAY:
            view.draw(*this);
            break;
    }
    SDL_RenderPresent(WindowRenderer.renderer);
}