#include <stdio.h>

//states for simon says
typedef enum
{
  Init_State, //chirps and flashes all 4 colors in seccesion. then pauses for a .5 sec
  Display_Pattern_State, // shows current pattern after init/reset and after succesful user input
  Input_Pattern_State, // part of the game where its idle and waiting for button presses
  Button_Press_State, // might not be needed. more of an event
  Win_State, // what are conditions of winnin? all 128 correct? maybe just show you when high score is met
  Lose_State
} eSystemState;

//Events for Simon Says
typedef enum
{
  Pattern_Display_End_Event, // even to transision to user input state
  Button_Press_Event, // when a button is pressed, might not be needed 
  Correct_Button_Event, // flashes the correct button for a short duration but doesn't exit state, increments high score if cond met
  Incorrect_Button_Event, // all 4 flash red, records high score, resets to init state
  High_Score_Event // flashes purple when the high score is excedded +1. 
} eSystemEvent;

//typedef of function pointer
typedef eSystemState (*pfEventHandler)(void);

//structure of state and event with event handler
typedef struct
{
  eSystemState eStateMachine;
  eSystemEvent eStateMachineEvent;
  pfEventHandler pfStateMachineEventHandler;
} sStateMachine;




