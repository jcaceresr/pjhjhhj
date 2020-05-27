
#include <raylib.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "level.h"
#include "draw.h"
#include "state.h"
#include "files.h"


int main(int argc, char const *argv[]){

    // Initialization
    const int screen_width = 800;
    const int screen_height = 600;

    InitWindow(screen_width,screen_height,"Presente - the game");

    InitAudioDevice();//start audio 
    Music ost = LoadMusicStream("../presente/musica/ost_metal.ogg");
    Music final = LoadMusicStream("../presente/musica/win.mp3");
    Music dead = LoadMusicStream("../presente/musica/mission_Failed.mp3");
    PlayMusicStream(ost);//play ost

    SetTargetFPS(60);

    int puntaje = 0;
    int hiscore = retorna_puntaje();//return the hiscore from the txt





    // Initialize level and fill randomly
    level *lvl = level_new(50,40);
    level_fill_random(lvl,6);

    // Initialize state (and add enemies)
    state *sta = state_new();
    state_populate_random(lvl,sta,40);




    // Main loop
    while(!WindowShouldClose()){
        //load the music
        UpdateMusicStream(ost);
        UpdateMusicStream(final);
        UpdateMusicStream(dead);


        // Update input depending if keys are pressed or not
        sta->button_state[0] = IsKeyDown(KEY_D);
        sta->button_state[1] = IsKeyDown(KEY_W);
        sta->button_state[2] = IsKeyDown(KEY_A);
        sta->button_state[3] = IsKeyDown(KEY_S);
        sta->button_state[4] = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
        // Compute the angle the player is looking at from the mouse's position relative to the screen's center
        float mouse_y = GetMouseY()-GetScreenHeight()/2;
        float mouse_x = GetMouseX()-GetScreenWidth()/2;
        sta->aim_angle = atan2(-mouse_y,mouse_x);

        // Update the state
        state_update(lvl,sta,&puntaje);

        // Drawing
        BeginDrawing();

            ClearBackground(RAYWHITE);

            draw_state(lvl, sta);
            //write
            DrawText("Presente profe!",190,200,20,LIGHTGRAY);
            DrawText(FormatText("HighScore: %06i", hiscore),5,40,20,BLUE);
            DrawText(FormatText("Puntaje: %06i", puntaje),5,0,20,RED);
            


        EndDrawing();

        // if there aren't enemies
        if(sta->n_enemies == 0){ 
            PlayMusicStream(final);
            StopMusicStream(ost);
            cambia_puntaje(&puntaje);
        }  
        // if the player dies
        if(sta->pla.ent.hp <=0){
            PlayMusicStream(dead);
            StopMusicStream(ost);
            cambia_puntaje(&puntaje);
        }



    }
    //closer music
    UnloadMusicStream(final);
    UnloadMusicStream(ost);
    UnloadMusicStream(dead);

    CloseAudioDevice();
    // Closer window
    CloseWindow();
    

    // Free memory
    state_free(sta);
    level_free(lvl);

    return 0;
}
