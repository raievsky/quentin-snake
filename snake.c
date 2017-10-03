#include <stdio.h>
#include <stdlib.h> // for atoi
#include <limits.h> // for NAME_MAX
#include <string.h> // for strcpy, strlen
#include <dirent.h> // for readdir and Co.
#include <pthread.h>
#include <unistd.h> // for usleep
#include <stdbool.h> // for bool type
#include <math.h> // for round

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

// Types
typedef struct{
    double x;
    double y;
} Position; 

typedef struct{
    int x;
    int y;
} Vitesse; 


// Variables globales
ALLEGRO_DISPLAY *gDisplay = NULL;
ALLEGRO_MOUSE_STATE gMouseState;
ALLEGRO_KEYBOARD_STATE gKbdstate;

Position snakePositions[3];
Vitesse snakeSpeed;

int largeur = 10;
ALLEGRO_COLOR gSnakeColor;


// Declaration des fonctions
void initWindow(int width, int height);
void moveSnake();
void drawSnake();





int main(int argc, char **argv)
{
    int width = 1000;
    int height = 1000;
    initWindow (width, height);
    
    // Initialisation des informations du serprent
    snakePositions[0].x = width/2.0;
    snakePositions[0].y = height/2.0;
    
    snakeSpeed.x = 0;
    snakeSpeed.y = -1;
    gSnakeColor = al_map_rgba(0, 0, 180, 100);
    
    // Pour toujours
    while (true)
    {
        
        // On bouge le serpent
        moveSnake();
        
        // On dessine le serpent
        drawSnake();
        
        // On récupère les entrées clavier
        al_get_keyboard_state(&gKbdstate);
        if ( al_key_down(&gKbdstate, ALLEGRO_KEY_ESCAPE))
            break;
        if ( al_key_down(&gKbdstate, ALLEGRO_KEY_DOWN))
        {
            snakeSpeed.x = 0;
            snakeSpeed.y = 5;
        }
        
        if ( al_key_down(&gKbdstate, ALLEGRO_KEY_UP))
        {
            snakeSpeed.x =0 ;
            snakeSpeed.y = -5;
        }
        
        if ( al_key_down(&gKbdstate, ALLEGRO_KEY_RIGHT))
        {
            snakeSpeed.x = 5;
            snakeSpeed.y = 0;
        }
        
        if ( al_key_down(&gKbdstate, ALLEGRO_KEY_LEFT))
        {
            snakeSpeed.x = -5;
            snakeSpeed.y = 0;
        }   
        
        
        
        
        
        usleep(10);
    }
    
    al_destroy_display(gDisplay);
    al_shutdown_primitives_addon();
}


void moveSnake()
{
    // On change la position du serpent
    Position newPosition = snakePositions[0];
    newPosition.x = newPosition.x + snakeSpeed.x;
    newPosition.y = newPosition.y + snakeSpeed.y;
    
    snakePositions[2] = snakePositions[1];
    snakePositions[1] = snakePositions[0];
    snakePositions[0] = newPosition;
    
}


void drawSnake()
{
    
    // On efface l'ecran
    al_clear_to_color(al_map_rgb(255,255,255));
    
    
    // On transforme les coordonnees en entiers
    int x = round(snakePositions[0].x);
    int y = round(snakePositions[0].y);
    
    // On dessine un cercle du serpent
    al_draw_filled_circle(x, y, largeur, gSnakeColor);
    
    // On transforme les coordonnees en entiers
    x = round(snakePositions[1].x);
    y = round(snakePositions[1].y);
    
    // On dessine un cercle du serpent
    al_draw_filled_circle(x, y, largeur, gSnakeColor);
    
    
    // On transforme les coordonnees en entiers
    x = round(snakePositions[2].x);
    y = round(snakePositions[2].y);
    
    // On dessine un cercle du serpent
    al_draw_filled_circle(x, y, largeur, gSnakeColor);
    
    
    al_flip_display();
}


// Toutes les initialisations allegro
void initWindow(int width, int height)
{
    if(!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        exit(-1);
    }
    
    if(!al_init_primitives_addon()) {
        fprintf(stderr, "failed to initialize allegro primitives addon!\n");
        exit(-1);
    }
    
    al_set_new_display_flags(ALLEGRO_OPENGL_3_0);
    gDisplay = al_create_display(width, height);
    if(!gDisplay) {
        fprintf(stderr, "failed to create display!\n");
        exit(-1);
    }
    
    if(!al_install_keyboard()) {
        fprintf(stderr, "Failed to initialize allegro keyboard handling!\n");
        exit(-1);
    }
    
    if(!al_install_mouse()) {
        fprintf(stderr, "Failed to initialize allegro mouse handling!\n");
        exit(-1);
    }
}

