#include "ui/view.h"

void UI::View::drawBoard(const Core::Game& g) const
{
    //TODO
}

void UI::View::draw(Core::Game& g)
{
    drawBoard(g);
    drawInfo(g);
    renderPlayerInfo(g);
}

void UI::View::drawCombat(Core::Game& g,
                          std::shared_ptr<Entities::Enemy> mob,
                          Systems::Turn currentTurn,
                          int selectedIndex,
                          bool isInventorySelected)
{
    SDL_SetRenderDrawColor(g.WindowRenderer.renderer, 0, 0, 0, 255);
    SDL_RenderClear(g.WindowRenderer.renderer);

    drawCombatSprites(g, mob);
    drawCombatHUD(g, mob);
    drawCombatTurn(g, mob, currentTurn);
    drawCombatMenu(g, selectedIndex);

    if (isInventorySelected)
    {
        getItemInventory(g);
    }
}

void UI::View::drawCombatSprites(Core::Game& g, std::shared_ptr<Entities::Enemy> mob)
{
    SDL_Rect playerRect = {100, 200, 128, 128};
    SDL_Rect mobRect = {400, 200, 128, 128};

    SDL_RenderCopy(g.WindowRenderer.renderer,
                   g.textureManager.get("player"),
                   nullptr, &playerRect);

    SDL_RenderCopy(g.WindowRenderer.renderer,
                   g.textureManager.get("enemy"),
                   nullptr, &mobRect);
}

void UI::View::drawCombatHUD(Core::Game& g, std::shared_ptr<Entities::Enemy> mob)
{
    auto player = g.player;

    std::string playerHpText = "Player HP: " +
        std::to_string((int)player->getStats().healthPoint) + "/" +
        std::to_string(player->getStats().maxHp);

    std::string mobHpText = "Enemy HP: " +
        std::to_string((int)mob->getStats().healthPoint) + "/" +
        std::to_string(mob->getStats().maxHp);

    renderText(g, playerHpText, 100, 150, {0,255,0});
    renderText(g, mobHpText, 400, 150, {255,0,0});
}

void UI::View::drawCombatTurn(Core::Game& g,
                              std::shared_ptr<Entities::Enemy> mob,
                              Systems::Turn turn)
{
    if (turn == Systems::Turn::ENEMY)
    {
        renderText(g,
                   mob->getName() + " is attacking",
                   250, 100, {255,0,0});
    }
    else
    {
        renderText(g, "Player turn", 250, 100, {255,255,255});
    }
}

void UI::View::drawCombatMenu(Core::Game& g, int selectedIndex)
{
    std::vector<std::string> options = {
        "Attack","Protect","Inventory","Run"
    };

    int menuX = 100;
    int menuY = 400;

    for (size_t i = 0; i < options.size(); i++)
    {
        bool selected = (static_cast<int>(i) == selectedIndex);

        std::string line = selected ? "> " + options[i] : "  " + options[i];
        SDL_Color color = selected ? SDL_Color{255,255,0} : SDL_Color{255,255,255};

        renderText(g, line, menuX + i * 200, menuY, color);
    }

    DisplayRect(g.WindowRenderer.renderer, menuX, menuY, options);
}

void DisplayRect(SDL_Renderer* renderer,int x, int y,const std::vector<std::string>& options){

    int SpacingX = 200;
    int padding = 10;

    for (size_t i = 0; i < options.size(); ++i) {
        int rectX = x + static_cast<int>(i) * SpacingX - padding;
        int rectY = y - padding;
        int rectW = 100 + 2 * padding;
        int rectH = 30 + 2 * padding;

        SDL_Rect rect = {rectX, rectY, rectW, rectH};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //white
        SDL_RenderDrawRect(renderer, &rect);
    }
}

void UI::View::drawInfo(const Core::Game& g) const
{
    if(!g.player) return;

    short boardSize = 19;
    short BoardTileSize = 32;

    const int boardPixelsize = boardSize * boardPixelsize;

    SDL_Rect infoBox = {
        boardPixelsize, 0,
        900 - boardPixelsize, 608
    };

    SDL_SetRenderDrawColor(g.WindowRenderer.renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(g.WindowRenderer.renderer, &infoBox);
}

void UI::View::getItemInventory(Core::Game& g)
{
    int space = 50;
    auto& items = g.player->getInventory().getItems();

    if (!items.empty())
    {
        for (auto& i : items){
            renderText(g,"> " + i->getName(),0 + space,500,{255,255,255});
            space += 100;
        }
    }
    renderText(g,"- Inventory is empty",50,500,{255,255,255});
}

void UI::View::renderPlayerInfo(Core::Game& g)
{
    auto player = g.player;

    if (!player) return;

    short boardSize = 19;
    short BoardTileSize = 32;

    SDL_Color white = {255, 255, 255, 255};
    SDL_Color red   = {255, 0, 0, 255};

    int x = boardSize * BoardTileSize + 10;
    int y = 10;

    auto pos   = player->getPos();
    auto stats = player->getStats();
    int nextXp = stats.getXpToNxtLvl();

    auto drawLine = [&](const std::string& text, SDL_Color color = {255, 255, 255, 255}, int offsetX = 0) {
        renderText(g, text, x + offsetX, y, color);
        y += 30;
    };

    drawLine("Position: (" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ")");
    drawLine("HP: " + std::to_string(stats.healthPoint));
    drawLine("Attack: " + std::to_string(stats.attackPoint));
    drawLine("Defense: " + std::to_string(stats.defensePoint));
    drawLine("XP: " + std::to_string(stats.xp) +
            " | Level: " + std::to_string(stats.level) +
            " | next lvl in: " + std::to_string(nextXp) + " XP");


    renderText(g, "near Enemy:", x, y, white);

    auto enemy = player->getNearEnemy(g.board);

    if (enemy) {
        drawLine(" - " + enemy->getName() +
                " (HP: " + std::to_string(enemy->getStats().healthPoint) + ")", red, 100);
    } else {
        drawLine(" - None", white, 100);
    }

    y += 20;

    drawLine("Inventory:");

    auto items = player->getInventory().getItems();

    if (items.empty()) {
        drawLine(" - (Empty)");
    } else {
        for (const auto& item : items) {
            drawLine(" - " + item->getName());
            y -= 5;
        }
    }   
}

void UI::View::renderText(const Core::Game& g, const std::string& text,
                int x, int y, SDL_Color c)
{
    SDL_Surface* surface = TTF_RenderText_Solid(g.WindowRenderer.font, text.c_str(), c );
	if (!surface) return;

	SDL_Texture* texture = SDL_CreateTextureFromSurface(g.WindowRenderer.renderer, surface);
	SDL_Rect destRect = { x, y, surface->w, surface->h };
	SDL_RenderCopy(g.WindowRenderer.renderer, texture, nullptr, &destRect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void UI::View::drawTitleScreen(const Core::Game& g)
{
    SDL_SetRenderDrawColor(g.WindowRenderer.renderer, 0, 0, 0, 255);
    SDL_RenderClear(g.WindowRenderer.renderer);
    SDL_Color white = {255, 255, 255, 255};

    renderText(g, "Mini RPG Game", 350, 200,white);
    renderText(g, "Press SPACE to start", 300, 300,white);
    renderText(g,"-personal project-",420,570,white);
}

void UI::View::drawPauseScreen(const Core::Game& g)
{
    SDL_SetRenderDrawColor(g.WindowRenderer.renderer, 0, 0, 0, 255);
    SDL_RenderClear(g.WindowRenderer.renderer);
    SDL_Color white = {255, 255, 255, 255};

    renderText(g,"PAUSE",400,200,white);
    renderText(g,"Press ENTER to quit the game",260,300,white);
}

void UI::View::drawGameOverScreen(const Core::Game& g)
{
    SDL_SetRenderDrawColor(g.WindowRenderer.renderer, 0, 0, 0, 255);
    SDL_RenderClear(g.WindowRenderer.renderer);
    SDL_Color white = {255, 255, 255, 255};

    renderText(g,"GAME OVER",350,200,white);
    renderText(g,"Press ENTER to quit the game",260,300,white);
}