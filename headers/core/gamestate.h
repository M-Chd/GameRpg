#pragma once

namespace Core {
    
    enum class GameState {
        /// the player is free to move
        GAMEPLAY,
        /// Fight mode
        FIGHT,
        /// Title screen
        TITLE,
        /// Pause mode
        PAUSE,
        /// Game over, player is at 0 hp.
        GAMEOVER
    };
}