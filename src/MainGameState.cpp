#include <MainGameState.hpp>
#include <iostream>

MainGameState::MainGameState()
{
}

void MainGameState::init()
{
    // Inicialización del personaje de Fuego
    fire_player.position = { 100.0f, 300.0f };
    fire_player.velocity = { 0.0f, 0.0f };
    fire_player.bounds = { fire_player.position.x, fire_player.position.y, 30, 30 };
    fire_player.type = FIRE;

    // Inicialización del personaje de Agua
    water_player.position = { 150.0f, 300.0f };
    water_player.velocity = { 0.0f, 0.0f };
    water_player.bounds = { water_player.position.x, water_player.position.y, 30, 30 };
    water_player.type = WATER;

    // Creación de plataformas para el nivel de prueba
    Platform ground = { { 0, 400, 800, 50 } };
    level_platforms.push_back(ground);
    
    Platform p1 = { { 300, 300, 200, 20 } };
    level_platforms.push_back(p1);

}

void MainGameState::handleInput()
{

}

void MainGameState::update(float deltaTime)
{

}

void MainGameState::render()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Dibujar el personaje de Fuego
    DrawRectangleRec(fire_player.bounds, RED);
    
    // Dibujar el personaje de Agua
    DrawRectangleRec(water_player.bounds, BLUE);

    // Dibujar las plataformas del nivel
    for (const auto& platform : level_platforms) {
        DrawRectangleRec(platform.bounds, GRAY);
    }
    
    EndDrawing();
}