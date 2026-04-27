/*******************************************************************************************
*
*   rini example
*
*   This example has been created using rini (github.com/raysan5/rini)
*
*
*   LICENSE: MIT
*
*   Copyright (c) 2022-2026 Ramon Santamaria (@raysan5)
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy
*   of this software and associated documentation files (the "Software"), to deal
*   in the Software without restriction, including without limitation the rights
*   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*   copies of the Software, and to permit persons to whom the Software is
*   furnished to do so, subject to the following conditions:
*
*   The above copyright notice and this permission notice shall be included in all
*   copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*   SOFTWARE.
*
**********************************************************************************************/

#include "raylib.h"

#define RINI_IMPLEMENTATION
#include "rini.h"

#define INI_FILE "resources/rini_example.ini"

int main(void)
{
    rini_data config = rini_load(INI_FILE);

    int screen_width  = rini_get_value_fallback(config, "screen_width",  800);
    int screen_height = rini_get_value_fallback(config, "screen_height", 450);
    const char *title = rini_get_value_text_fallback(config, "title", "rini example");

    InitWindow(screen_width, screen_height, title);
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            int y = 20;
            for (unsigned int i = 0; i < config.count; i++)
            {
                rini_value *v = &config.values[i];
                if (v->key[0] == '\0') continue;

                DrawText(v->key, 20, y, 20, DARKGRAY);
                DrawText(v->text, 200, y, 20, DARKGRAY);
                y += 28;
            }

        EndDrawing();
    }

    rini_unload(&config);
    CloseWindow();

    return 0;
}
