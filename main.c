#include <stdio.h>

//states for simon says
typedef enum
{
  Init_State, //chirps and flashes all 4 colors in seccesion. then pauses for a .5 sec
  Display_Pattern_State, // shows current pattern after init/reset and after succesful user input
  Input_Pattern_State, // part of the game where its idle and waiting for button presses
  Button_Press_State, // might not be needed. more of an event
  High_Score_State, // what are conditions of winnin? all 128 correct? maybe just show you when high score is met
  Last_State
} eSystemState;

//Events for Simon Says
typedef enum
{
  Nil_Event,
  Init_Finished_Event,
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

typedef struct
{
    uint32_t ui32Pattern[APP_PATTERN_MAX_SIZE];
    uint32_t ui32Mode;
    uint32_t ui32Buttons;
    uint32_t ui32ManualIndex;
    uint32_t ui32ModeTimer;
    float fColorWheelPos;
    float fIntensity;

}tAppState;

eSystemState PatternDisplayHandler(void)
{
    
    return Display_Pattern_State;
}

eSystemState InputPatternHandler(void)
{
    return 
}



sStateMachine asStateMachine [] = {
    {Idle_State,Init_Finished_Event,PatternDisplayHandler},
    {Display_Pattern_State,Button_Press_Event,EnterPinHandler},
    {Pin_Eentered_State,Option_Selection_Event,OptionSelectionHandler},
    {Option_Selected_State,Amount_Enter_Event,EnterAmountHandler},
    {Amount_Entered_State,Amount_Dispatch_Event,AmountDispatchHandler}

};

typedef enum
{
  Nil_Event,
  Init_Finished_Event,
  Pattern_Display_End_Event, // even to transision to user input state
  Button_Press_Event, // when a button is pressed, might not be needed 
  Correct_Button_Event, // flashes the correct button for a short duration but doesn't exit state, increments high score if cond met
  Incorrect_Button_Event, // all 4 flash red, records high score, resets to init state
  High_Score_Event // flashes purple when the high score is excedded +1. 
} eSystemEvent;

//events                 Animation Finished  | correct button           | incorrect button           | high score            | Timeout
//states                ---------------------------------------------------------------
//Init_State            | {Display_State, 0} | {Display_State, 0}       | {Display_State, 0}         | {Display_State, 0}    | {Lose_State, 0}
//Display_Pattern_State | {Input_State, 0}   | {Display_State,0}        | {Display_State,0}          | {Display_State,0}     | {Lose_State, 0}
//Input_Pattern_State   | {Input_State, 0}   | {Input_State, flash_led} | {Lose_State, record_score} | {Input_State, LED_HS} | {Lose_State, 0}
//Lose_State            | {Init_State, 0}    | {Lose_State, 0}          | {Init_State, 0}            | {Lose_State,0}        | {Init_state, 0}

stateElement stateMatrix[3][3] = {
       { {Display_Pattern_State, NILACTION}, {STATE_1,ACTION_1}, {STATE_1,ACTION_4} },
       { {Input_Pattern_State, NILACTION},   {STATE_2,ACTION_3}, {STATE_2,ACTION_2} },
       { {High_Score_State ,NILACTION},      {STATE_0,ACTION_2}, {STATE_1,ACTION_3} }
}



