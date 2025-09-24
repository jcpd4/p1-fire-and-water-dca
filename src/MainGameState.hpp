#pragma once
#include <GameState.hpp>
#include <vector>

extern "C" {
    #include <raylib.h>
}

enum ElementType {
    FIRE,
    WATER
};

struct Player {
    Vector2 position;
    Vector2 velocity;
    Rectangle bounds;
    ElementType type;
};

struct Platform {
    Rectangle bounds;
};


class MainGameState : public GameState
{
    public:
        MainGameState();
        ~MainGameState() = default;

        void init() override;
        void handleInput() override;
        void update(float deltaTime) override;
        void render() override;

        void pause(){};
        void resume(){};

    
    private:
        char entered_key;
        Player fire_player;
        Player water_player;
        std::vector<Platform> level_platforms;
};