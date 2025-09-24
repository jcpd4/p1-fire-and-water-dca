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

struct Hazard {
    Rectangle bounds;
    ElementType type;
};


struct Player {
    Vector2 position;
    Vector2 velocity;
    Rectangle bounds;
    ElementType type;
    // Debes añadir estas dos variables en tu struct para que el código compile
    float width;
    float height;
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
    // Variables para controlar si los jugadores están en el suelo
    bool fire_on_ground = false;
    bool water_on_ground = false;
    // Nueva variable para almacenar los peligros del nivel
    std::vector<Hazard> level_hazards;
};