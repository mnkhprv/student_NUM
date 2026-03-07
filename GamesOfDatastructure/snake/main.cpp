#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <deque>

using namespace std;

const int windowWidth = 800;
const int windowHeight = 600;
const int cellSize = 20;

deque<pair<int, int>> snake;
pair<int, int> food;
int direction = 0;
bool gameOver = false;
bool inMenu = true;
int selectedMenuOption = 0;
int gameSpeed = 100;
int score = 0;
int highScore = 0;
double lastUpdateTime = 0;

void SpawnFood() {
    food.first = (rand() % (windowWidth / cellSize)) * cellSize;
    food.second = (rand() % (windowHeight / cellSize)) * cellSize;
}

void UpdateGame() {
    if (!gameOver && !inMenu) {
        pair<int, int> head = snake.front();

        if (direction == 0) head.second -= cellSize;
        if (direction == 1) head.first += cellSize;
        if (direction == 2) head.second += cellSize;
        if (direction == 3) head.first -= cellSize;

        if (head.first < 0 || head.first >= windowWidth || head.second < 0 || head.second >= windowHeight) {
            gameOver = true;
            selectedMenuOption = 0;
            if (score > highScore) highScore = score; 
        } else {
            for (size_t i = 1; i < snake.size(); i++) {
                if (snake[i] == head) {
                    gameOver = true;
                    selectedMenuOption = 0;
                    if (score > highScore) highScore = score; 
                    break;
                }
            }
        }

        if (!gameOver) {
            snake.push_front(head);

            if (head == food) {
                score++;
                SpawnFood();
            } else {
                snake.pop_back();
            }
        }
    }
}

void HandleInput() {
    if (inMenu || gameOver) {
        if (IsKeyPressed(KEY_UP)) selectedMenuOption = (selectedMenuOption + 2) % 3;
        if (IsKeyPressed(KEY_DOWN)) selectedMenuOption = (selectedMenuOption + 1) % 3;
        if (IsKeyPressed(KEY_ENTER)) {
            if (selectedMenuOption == 0) {
                gameOver = false;
                inMenu = false;
                snake.clear();
                snake.push_back({windowWidth / 2, windowHeight / 2});
                score = 0;
                direction = 0;
                SpawnFood();
            } else if (selectedMenuOption == 1 && inMenu) {
                gameSpeed = (gameSpeed == 100) ? 50 : 100;
            } else if (selectedMenuOption == 2 || (gameOver && selectedMenuOption == 1)) {
                CloseWindow();
                exit(0);
            }
        }
    } else {
        if (IsKeyPressed(KEY_UP) && direction != 2) {
            direction = 0;
            printf("UP pressed, direction set to %d\n", direction);
        }
        if (IsKeyPressed(KEY_RIGHT) && direction != 3) {
            direction = 1;
            printf("RIGHT pressed, direction set to %d\n", direction);
        }
        if (IsKeyPressed(KEY_DOWN) && direction != 0) {
            direction = 2; 
            printf("DOWN pressed, direction set to %d\n", direction);
        }
        if (IsKeyPressed(KEY_LEFT) && direction != 1) {
            direction = 3;
            printf("LEFT pressed, direction set to %d\n", direction);
        }
        if (IsKeyPressed(KEY_ESCAPE)) {
            inMenu = true;
            gameOver = false;
            selectedMenuOption = 0;
            if (score > highScore) highScore = score;
        }
    }
}

int main(void) {
    srand((unsigned int)time(0));

    InitWindow(windowWidth, windowHeight, "Snake Game");
    SetTargetFPS(60);

    snake.push_back({windowWidth / 2, windowHeight / 2});
    SpawnFood();

    while (!WindowShouldClose()) {
        HandleInput();

        if (!inMenu && !gameOver && GetTime() - lastUpdateTime >= gameSpeed / 1000.0) {
            UpdateGame();
            lastUpdateTime = GetTime();
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (inMenu) {
            DrawText("SNAKE GAME", windowWidth / 2 - MeasureText("SNAKE GAME", 40) / 2, windowHeight / 2 - 100, 40, YELLOW);
            DrawText("Start", windowWidth / 2 - MeasureText("Start", 30) / 2, windowHeight / 2 - 50, 30, selectedMenuOption == 0 ? GREEN : WHITE);
            DrawText("Speed", windowWidth / 2 - MeasureText("Speed", 30) / 2, windowHeight / 2, 30, selectedMenuOption == 1 ? GREEN : WHITE);
            DrawText("Exit", windowWidth / 2 - MeasureText("Exit", 30) / 2, windowHeight / 2 + 50, 30, selectedMenuOption == 2 ? GREEN : WHITE);
            char highScoreMsg[32];
            snprintf(highScoreMsg, sizeof(highScoreMsg), "High Score: %d", highScore);
            DrawText(highScoreMsg, windowWidth / 2 - MeasureText(highScoreMsg, 20) / 2, windowHeight / 2 + 100, 20, WHITE);
        } else if (gameOver) {
            DrawText("GAME OVER", windowWidth / 2 - MeasureText("GAME OVER", 40) / 2, windowHeight / 2 - 50, 40, RED);
            char scoreMsg[32];
            snprintf(scoreMsg, sizeof(scoreMsg), "Score: %d", score);
            DrawText(scoreMsg, windowWidth / 2 - MeasureText(scoreMsg, 30) / 2, windowHeight / 2, 30, WHITE);
            char highScoreMsg[32];
            snprintf(highScoreMsg, sizeof(highScoreMsg), "High Score: %d", highScore);
            DrawText(highScoreMsg, windowWidth / 2 - MeasureText(highScoreMsg, 20) / 2, windowHeight / 2 + 50, 20, WHITE);
            DrawText("Restart", windowWidth / 2 - MeasureText("Restart", 30) / 2, windowHeight / 2 + 100, 30, selectedMenuOption == 0 ? GREEN : WHITE);
            DrawText("Exit", windowWidth / 2 - MeasureText("Exit", 30) / 2, windowHeight / 2 + 150, 30, selectedMenuOption == 1 ? GREEN : WHITE);
        } else {
            for (auto segment : snake) {
                DrawRectangle(segment.first, segment.second, cellSize, cellSize, GREEN);
            }
            DrawRectangle(food.first, food.second, cellSize, cellSize, RED);
            char scoreMsg[32];
            snprintf(scoreMsg, sizeof(scoreMsg), "Score: %d", score);
            DrawText(scoreMsg, 10, windowHeight - 30, 20, WHITE);
            DrawText("Press ESC to return to menu", 10, windowHeight - 50, 20, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}