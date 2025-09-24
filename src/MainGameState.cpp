#include <MainGameState.hpp>
#include <iostream>

extern "C" {
    #include <raylib.h>
}

MainGameState::MainGameState()
{
}

void MainGameState::init()
{
    // Inicialización del personaje de Fuego
    fire_player.position = { 100.0f, 300.0f };
    fire_player.velocity = { 0.0f, 0.0f };
    fire_player.bounds = { fire_player.position.x, fire_player.position.y, 30.0f, 30.0f };
    fire_player.type = FIRE;

    // Inicialización del personaje de Agua
    water_player.position = { 150.0f, 300.0f };
    water_player.velocity = { 0.0f, 0.0f };
    water_player.bounds = { water_player.position.x, water_player.position.y, 30.0f, 30.0f };
    water_player.type = WATER;

    // Creación de plataformas para el nivel de prueba
    Platform ground = { { 0, 400, 800, 50 } };
    level_platforms.push_back(ground);
    
    Platform p1 = { { 300, 300, 200, 20 } };
    level_platforms.push_back(p1);
}

void MainGameState::handleInput()
{
    // Control del personaje de Fuego (teclas A y D)
    if (IsKeyDown(KEY_A)) {
        fire_player.velocity.x = -200.0f;
    } else if (IsKeyDown(KEY_D)) {
        fire_player.velocity.x = 200.0f;
    } else {
        fire_player.velocity.x = 0.0f;
    }

    // Control del personaje de Agua (flechas izquierda y derecha)
    if (IsKeyDown(KEY_LEFT)) {
        water_player.velocity.x = -200.0f;
    } else if (IsKeyDown(KEY_RIGHT)) {
        water_player.velocity.x = 200.0f;
    } else {
        water_player.velocity.x = 0.0f;
    }
}

void MainGameState::update(float deltaTime)
{
    // Resetea el estado de "en el suelo" al principio del frame
    fire_on_ground = false;
    water_on_ground = false;

    // Aplica gravedad a los jugadores
    const float gravity = 800.0f;
    fire_player.velocity.y += gravity * deltaTime;
    water_player.velocity.y += gravity * deltaTime;

    // Actualiza las posiciones de los jugadores según su velocidad
    fire_player.position.x += fire_player.velocity.x * deltaTime;
    fire_player.position.y += fire_player.velocity.y * deltaTime;
    water_player.position.x += water_player.velocity.x * deltaTime;
    water_player.position.y += water_player.velocity.y * deltaTime;

    // Actualiza los límites (bounds) de colisión
    fire_player.bounds.x = fire_player.position.x;
    fire_player.bounds.y = fire_player.position.y;
    water_player.bounds.x = water_player.position.x;
    water_player.bounds.y = water_player.position.y;

    // Colisiones con plataformas
    for (const auto& platform : level_platforms) {
        // Revisa colisión con el personaje de Fuego
        if (CheckCollisionRecs(fire_player.bounds, platform.bounds)) {
            // Detiene el movimiento vertical
            fire_player.velocity.y = 0;
            // Corrige la posición del jugador para que no caiga
            fire_player.position.y = platform.bounds.y - fire_player.bounds.height;
            fire_player.bounds.y = fire_player.position.y;
            fire_on_ground = true; // El jugador está en el suelo
        }
        // Revisa colisión con el personaje de Agua
        if (CheckCollisionRecs(water_player.bounds, platform.bounds)) {
            // Detiene el movimiento vertical
            water_player.velocity.y = 0;
            // Corrige la posición del jugador
            water_player.position.y = platform.bounds.y - water_player.bounds.height;
            water_player.bounds.y = water_player.position.y;
            water_on_ground = true; // El jugador está en el suelo
        }
    }

    // Lógica de Salto (movida aquí)
    if (IsKeyPressed(KEY_W) && fire_on_ground) {
        fire_player.velocity.y = -400.0f; // Impulso de salto
    }
    if (IsKeyPressed(KEY_UP) && water_on_ground) {
        water_player.velocity.y = -400.0f; // Impulso de salto
    }
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