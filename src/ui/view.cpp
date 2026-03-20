#include "ui/view.h"

void UI::View::drawBoard(Core::Game& g) const
{
    //TODO
}

void UI::View::drawInfo(Core::Game& g) const
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

    auto drawLine = [&](const std::string& text, SDL_Color color = white, int offsetX = 0) {
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

    //TODO Change this error

    if (IsPlayerNearMob(player, g.board)) {
        auto mob = getNearMob(player, g.board);
        drawLine(" - " + mob->getMobName() +
                " (HP: " + std::to_string(mob->getStats().hp) + ")", red, 100);
    } else {
        drawLine(" - None", white, 100);
    }

    y += 20;

    drawLine("Inventory:");

    auto items = player->getInventory().getItems(); //TODO Change this error

    if (items.empty()) {
        drawLine(" - (Empty)");
    } else {
        for (const auto& item : items) {
            drawLine(" - " + item->getName());
            y -= 5;
        }
    }   
}

void UI::View::renderText(Core::Game& g, const std::string& text,
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

void UI::View::drawTitleScreen(Core::Game& g)
{
    SDL_SetRenderDrawColor(g.WindowRenderer.renderer, 0, 0, 0, 255);
    SDL_RenderClear(g.WindowRenderer.renderer);
    SDL_Color white = {255, 255, 255, 255};

    renderText(g, "Mini RPG Game", 350, 200,white);
    renderText(g, "Press SPACE to start", 300, 300,white);
    renderText(g,"-personal project-",420,570,white);
}

void UI::View::drawPauseScreen(Core::Game& g)
{
    SDL_SetRenderDrawColor(g.WindowRenderer.renderer, 0, 0, 0, 255);
    SDL_RenderClear(g.WindowRenderer.renderer);
    SDL_Color white = {255, 255, 255, 255};

    renderText(g,"PAUSE",400,200,white);
    renderText(g,"Press ENTER to quit the game",260,300,white);
}

void UI::View::drawGameOverScreen(Core::Game& g)
{
    SDL_SetRenderDrawColor(g.WindowRenderer.renderer, 0, 0, 0, 255);
    SDL_RenderClear(g.WindowRenderer.renderer);
    SDL_Color white = {255, 255, 255, 255};

    renderText(g,"GAME OVER",350,200,white);
    renderText(g,"Press ENTER to quit the game",260,300,white);
}