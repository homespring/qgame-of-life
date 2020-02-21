#include "life_like_game.h"

using namespace LifeLike;

Game::Game() {}

Game::Game(int width, int height)
    : width_(width), height_(height) {}

Game::Game(int width, int height, const Rule &rule)
    : width_(width), height_(height), rule_(rule) {}
