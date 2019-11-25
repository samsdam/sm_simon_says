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
} enumSystemState;

typedef enum
{
  Button_Press_Event,
  Correct_Button_Event,
  Incorrect_Button_Event,
  High_Score_Event
} enumSystemEvent;


