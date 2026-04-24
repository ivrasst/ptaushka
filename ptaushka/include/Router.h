#pragma once

#include "Config.h"
#include "Solver.h"
#include "Navigator.h"
#include "Arduino.h"
#include "Types.h"

#define ROUTER_PATH_BUFFER_SIZE 128



// Absolute  (NESW) to relative (FLRS)
char router_path_buffer[ROUTER_PATH_BUFFER_SIZE];
size_t router_path_index = 0;

Vec2 router_look = Vec2{0, 0};
char router_state = 0;

// Relative (FLRS) to cyclogram

ASMR_Entry router_cyc_buffer[ROUTER_PATH_BUFFER_SIZE];
size_t router_cyc_index = 0;
ASMR_Entry router_cyc_state = {0};



void router_init()
{
    for(int i = 0; i < ROUTER_PATH_BUFFER_SIZE; i++)
    {
        router_path_buffer[i] = 0;
        router_cyc_buffer[i] = {0};
    }
    router_path_index = 0;
    router_cyc_index = 0;

    router_look = nav_get_pos();
    
    char symbs[] = {'E', 0, 'N', 0, 'W', 0, 'S', 0};
    router_state = symbs[nav_get_sigma()];
    router_cyc_state = {0};
    Serial.println(router_state);
}

void router_add_step(char step)
{
    if(router_state != 'G')
    {
        router_path_buffer[router_path_index] = step;
        router_path_index++;
    }
}
void router_tick()
{
    for(size_t i = 0; i < ROUTER_PATH_BUFFER_SIZE && router_state != 'G'; i++)
    {
        char input = solver_get_where_from(router_look);
        Serial.print(input);
        switch (router_state)
        {
        case 'N':
            if(input == 'N')
                router_add_step('F');

            if(input == 'E')
                router_add_step('R');

            if(input == 'W')
                router_add_step('L');

            if(input == 'S')
                router_add_step('I');
            if(input == 'G')
                router_add_step('S');

            break;

        case 'W':
            if(input == 'N')
                router_add_step('R');

            if(input == 'E')
                router_add_step('I');

            if(input == 'G')
                router_add_step('S');

            if(input == 'W')
                router_add_step('F');

            if(input == 'S')
                router_add_step('L');

            break;

        case 'S':
            if(input == 'W')
                router_add_step('R');

            if(input == 'N')
                router_add_step('I');

            if(input == 'G')
                router_add_step('S');

            if(input == 'S')
                router_add_step('F');

            if(input == 'E')
                router_add_step('L');
                
            break;

        case 'E':
            if(input == 'S')
                router_add_step('R');

            if(input == 'W')
                router_add_step('I');

            if(input == 'G')
                router_add_step('S');

            if(input == 'E')
                router_add_step('F');

            if(input == 'N')
                router_add_step('L');
                
            break;

        case 'G':
            
            break;

        default:
            break;
        }
        router_state = input;

        if(router_state == 'N')
            router_look.y -= 1;
        else if(router_state == 'S')
            router_look.y += 1;
        else if(router_state == 'E')
            router_look.x += 1;
        else if(router_state == 'W')
            router_look.x -= 1;
    }
    
}


void router_add_cyc(int cyc)
{
    if(router_cyc_index < ROUTER_PATH_BUFFER_SIZE)
    {
        router_cyc_buffer[router_cyc_index].raw = cyc;
        router_cyc_index++;
    }
}
void router_path_to_cyc(char path[])
{
    // router_add_cyc(SWD05);
    for(size_t i = 0; i < ROUTER_PATH_BUFFER_SIZE; i++)
    {
        if(path[i] == 'F')
            router_add_cyc(SWD1);
        else if(path[i] == 'R')
            router_add_cyc(SS90SER);
        else if(path[i] == 'L')
            router_add_cyc(SS90SEL);
        else if(path[i] == 'I'){
            router_add_cyc(SS180I);
            router_add_cyc(LINEUP_PART_A);
            router_add_cyc(LINEUP_PART_B);
            router_add_cyc(SWD05);
        }
        else if(path[i] == 'S'){
            router_add_cyc(SWD05);
            router_add_cyc(STOP);
        }
    }
}