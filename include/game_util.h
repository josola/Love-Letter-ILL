/*
 * Helper utility for game state.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef GAME_UTIL_h
#define GAME_UTIL_h

#include <utility>
#include "game.h"
#include "player.h"

using std::pair;

class GameUtil
{
public:
    GameUtil(Game game);

    int RoundCount();
    void GetPlayerCount();
    bool CorrectPlayerCount(int input);
    void FixPlayerCount();
    void SetPlayerCount(int output);
    void SetOriginalPlayerCount(int output);
    void SetPlayers();
    vector<PlayerUtil> PlayerBuilder(int output);
    void SetWinningTokenCount();
    int PlayerCount();
    void BuildStartingPlayer();
    int GenerateNumberWithinRange(int range);
    int GetPlayerGuess();
    bool CorrectGuessInput(int output);
    void FixGuessInput(int input);
    bool DuplicateGuess(vector<int> guess_container, int guess);
    vector<PlayerUtil> Players();

private:
    Game game;
};

#endif