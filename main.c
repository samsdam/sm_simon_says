#include <stdio.h>

//states for simon says
typedef enum
{
  Init_State,
  Idle_State,
  Display_Pattern_State,
  Button_Press_State,
  Correct_Button_State,
  Incorrect_Button_State
} eSystemState;

//Events for Simon Says
typedef enum
{
  Button_Press_Event,
  Correct_Button_Event,
  Incorrect_Button_Event,
  High_Score_Event
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




