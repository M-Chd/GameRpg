#include "core/game.h"

void Core::Game::initGame()
{
    if (!WindowRenderer.initWindow(900,608)) return;
    if (!WindowRenderer.initRenderer()) return;
    if (!WindowRenderer.initFonts()) return;

    textureManager.init(WindowRenderer.renderer);
    textureManager.load("player", "assets/images/Miku_forgor.png");
    textureManager.load("enemy", "assets/images/sinje.jpg");
    textureManager.load("sword", "assets/images/minecraft_sword.jpg");
    textureManager.load("bow", "assets/images/Minecraft_bow.jpg");
    textureManager.load("heal", "assets/images/Heal_potion.png");

    entityManager.initEntities(*this);

}

void Core::Game::quit()
{
    WindowRenderer.quit();
}

void Core::Game::run()
{
    lastEnemyUpdate = SDL_GetTicks();

    SDL_Event e;
    int end = 0;
    while (!end) {
        while (SDL_PollEvent(&e)) {
            
            if (e.type == SDL_QUIT){
                end = 1;
                quit();
            }
            else if (e.type == SDL_KEYDOWN) {
                SDL_Scancode key = e.key.keysym.scancode;

                if (state == GameState::TITLE && key == SDL_SCANCODE_SPACE) {
                    state = GameState::GAMEPLAY;
                }
                else if (state == GameState::GAMEPLAY && key == SDL_SCANCODE_ESCAPE) {
                    state = GameState::PAUSE;
                }
                else if (state == GameState::PAUSE) {
                    if (key == SDL_SCANCODE_ESCAPE) {
                        state = GameState::GAMEPLAY;
                        std::cout << "Resume Game" << std::endl;
                    } else if (key == SDL_SCANCODE_RETURN) {
                        end = true;
                    }
                } else if (state == GameState::GAMEOVER){
                    view.drawGameOverScreen(*this);
                    if (key == SDL_SCANCODE_RETURN){
                        end = true;
                    }
                    SDL_RenderPresent(WindowRenderer.renderer);
                }
            }
		}
        if (state == GameState::TITLE){
            if (Utils::is_key_pressed(SDL_SCANCODE_SPACE)){
                state = GameState::GAMEPLAY;
            }

            view.drawTitleScreen(*this);
            SDL_RenderPresent(WindowRenderer.renderer);
            SDL_Delay(20);
        }
        else if (state == GameState::PAUSE){

            view.drawPauseScreen(*this);
            SDL_RenderPresent(WindowRenderer.renderer);
            SDL_Delay(20);

        }
        else if (state == GameState::GAMEPLAY){

            if (player->getStats().healthPoint == 0){
                state = GameState::GAMEOVER;
            }

            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - lastEnemyUpdate > enemyUpdateInterval) {
                entityManager.enemyAlgorithm(*this);
                lastEnemyUpdate = currentTime;
            }

            for (const auto& [key, dir] : Systems::keyToDirection) {
                if (Utils::is_key_pressed(key)) {
                    player->move(board,dir);
                }
            }

            if(board.getEnemies().empty()){
                entityManager.spawnEnemy(board,player);
            }

            entityManager.spawnHeal(board,player);

		    view.draw(*this);
		    SDL_RenderPresent(WindowRenderer.renderer);
            SDL_Delay(80);
        }
    }
}