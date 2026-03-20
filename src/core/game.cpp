#include "core/game.h"

void Core::Game::initGame()
{
    if (!WindowRenderer.initWindow(900,608)) return;
    if (!WindowRenderer.initRenderer()) return;
    if (!WindowRenderer.initFonts()) return;

    if(!textureManager.surfaceManager->initSurfaces(WindowRenderer.font)) return;

    textureManager.initTexture(WindowRenderer.font,WindowRenderer.renderer);

    state = GameState::TITLE;

    initEntities();

}

void Core::Game::initEntities()
{
    int boardSize = 19;

    //TODO SPAWN ENEMY FUNCTION HERE
    //TODO? Make an EntityManager ?

    player = std::make_unique<Entities::Player>(Utils::Position{0,0});
    board.setEntityAt(Utils::Position{boardSize/2,boardSize/2},player);

    auto sword = std::make_shared<Entities::SwordItem>("Sword",5,NULL);
    Utils::Position randomPos = Utils::generateRandomItemPosition(boardSize,board);
    board.setEntityAt(Utils::Position{randomPos.x,randomPos.y},sword);
}

void Core::Game::quit()
{
    WindowRenderer.quit();
}

void Core::Game::run()
{
    //TODO
}