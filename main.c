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



/*
C-Frameworks: Basic State Machine Implementation
How to Use State Tables for Implementing Finite State Machines
part 1: http://gedan.net/post/2018-09-29-c-state-machine1/
Part 2: http://gedan.net/post/2018-09-29-c-state-machine2/
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define APP_PATTERN_MAX_SIZE    128
#define APP_FRAME_DURATION      (APP_SYSTICKS_PER_SEC * 1)
#define APP_TRANSITION_DURATION (APP_SYSTICKS_PER_SEC / 2)
#define RGB_RED                 {0xFFFF,0x0000,0x0000}
#define RGB_GREEN               {0x0000,0xFFFF,0x0000}
#define RGB_BLUE                {0x0000,0x0000,0xFFFF}
#define RGB_PURPLE              {0xFFFF,0x0000,0xFFFF}
#define RGB_YELLOW              {0xFFFF,0xFFFF,0x0000}
#define RGB_BLACK               {0x0000,0x0000,0x0000}

//typedef for a function pointer to an action that shall be released in each state
typedef void (*action)();

void animate_correct_led(void);
void record_score(void);
void animate_highscore(void);

// states for simon game
typedef enum
{
  Init_State, //chirps and flashes all 4 colors in seccesion. then pauses for a .5 sec
  Display_Pattern_State, // shows current pattern after init/reset and after succesful user input
  Input_Pattern_State, // part of the game where its idle and waiting for button presses
  Lose_State
} state;

typedef enum
{
  Nil_Event,
  Animation_Finished_Event, // even to transision to user input state
  Correct_Button_Event, // flashes the correct button for a short duration but doesn't exit state, increments high score if cond met
  Incorrect_Button_Event, // all 4 flash red, records high score, resets to init state
  High_Score_Event, // flashes purple when the high score is excedded +1.
  Timeout_Event // when the user doesn't hit a button for 30 sec
} eSystemEvent;

// structure for the elements in the state-event matrix
typedef struct {
      state nextState; // Enumerator for the next state
      action actionToDo; // function-pointer to the action that shall be released in current state
}  stateElement;

// Transision Table
//
//                                                  EVENTS
//STATES                Animation Finished  | correct button            | incorrect button           | high score            | Timeout
//-------               ----------------------------------------------------------------------------------------------------------------------
//Init_State            | {Display_State, 0} | {Display_State, 0}       | {Display_State, 0}         | {Display_State, 0}    | {Lose_State, 0}
//Display_Pattern_State | {Input_State, 0}   | {Display_State,0}        | {Display_State,0}          | {Display_State,0}     | {Lose_State, 0}
//Input_Pattern_State   | {Input_State, 0}   | {Input_State, flash_led} | {Lose_State, record_score} | {Input_State, LED_HS} | {Lose_State, 0}
//Lose_State            | {Init_State, 0}    | {Lose_State, 0}          | {Init_State, 0}            | {Lose_State,0}        | {Init_state, 0}

//the state-event matrix
stateElement stateMatrix[3][3] = {
       { {Display_Pattern_State, NILACTION}, {STATE_1,ACTION_1}, {STATE_1,ACTION_4} },
       { {Input_Pattern_State, NILACTION},   {STATE_2,ACTION_3}, {STATE_2,ACTION_2} },
       { {High_Score_State ,NILACTION},      {STATE_0,ACTION_2}, {STATE_1,ACTION_3} }
}

/********************************************************************************
 * stateEval (event)
 * in Dependancy of an triggered event, the action wich is required by this
 * transition will be returned. The proper action is determined by the current state the
 * automat holds. The current state will then be transitioned to the requestet next
 * state
 ********************************************************************************/

void stateEval(event e)
{
    //determine the State-Matrix-Element in dependany of current state and triggered event
    stateElement stateEvaluation = stateMatrix[currentState][e];
    //do the transition to the next state (set requestet next state to current state)...
    currentState = stateEvaluation.nextState;
    //... and fire the proper action
    (*stateEvaluation.actionToDo)();
}

//// or 
action stateEval(event e) 
 {
     //determine the State-Matrix-Element in dependany of current state and triggered event
     stateElement stateEvaluation = stateMatrix[currentState][e];
  
     //do the transition to the next state (set requestet next state to current state)...
     currentState = stateEvaluation.nextState;
     //... and fire the proper action
     return stateEvaluation.actionToDo;
}

uint32_t ui32Pattern[APP_PATTERN_MAX_SIZE];
uint32_t ui32PatternPos; // current position of pattern 
uint32_t ui32PatternLen; // current pattern lenth
uint32_t event; //can be nil

// Sub animation for each color {on,off}
// ex | ui32Pattern[x] == blue                 |
//    | led blue for 1 sec, led off for .5 sec |
uint32_t ui32SequenceOnTimer; 
uint32_t ui32SequenceOffTimer;

typedef struct {
    bool bAnimationEnable;
    volatile uint32_t * pui32FrameArray;
    uint32_t ui32FrameArrayLen;
    uint32_t ui32FrameArrayPos;
    bool bIncludeFrameTransition;
    uint32_t ui32FrameTimer;
   uint32_t ui32TransitionTimer;
} tAnimationState;

uint32_t ui32LoseAnimation[3] = {RGB_RED,RGB_RED,RGB_RED};
uint32_t ui32CorrectButtonAnimation[1] = {BLUE}; // should be 
uint32_t ui32InitAnimation[4] = {RGB_GREEN, RGB_RED, RGB_BLUE, RGB_YELLOW};
uint32_t ui32HighScoreAnimation[1] = {RGB_PURPLE};

void init (void)
{
  return;
}

void AppPatternHandler(void)
{
    // if animation isn't enabled then return
    if(!g_sAnimationState.bAnimationEnable) return;
    
    uint32_t curPos = g_sAnimationState.ui32FrameArrayPos;
    volatile uint32_t * pFrameArray = g_sAnimationState.pui32FrameArray;

    if(g_sAnimationState.bIncludeFrameTransition)
    {
        if(g_sAnimationState.ui32FrameTimer < APP_FRAME_DURATION )
        {
            g_sAnimationState.ui32FrameTimer++;
            RGBColorSet(pFrameArray[curPos]);
        }
        else if (g_sAnimationState.ui32TransitionTimer < APP_TRANSITION_DURATION)
        {
            g_sAnimationState.ui32TransitionTimer++;
            RGBColorSet(RGB_BLACK);
        }
        else
        {
            g_sAnimationState.ui32FrameTimer = 0;
            g_sAnimationState.ui32TransitionTimer = 0;
            RGBColorSet(RGB_BLACK);
            g_sAnimationState.ui32FrameArrayPos++;
        }
    } 
    else
    {
        if(g_sAnimationState.ui32FrameTimer < APP_FRAME_DURATION )
        {
            g_sAnimationState.ui32FrameTimer++;
            RGBColorSet(pFrameArray[curPos]);
        }
        else
        {
            g_sAnimationState.ui32FrameTimer = 0;
            RGBColorSet(pFrameArray[curPos]);
            g_sAnimationState.ui32FrameArrayPos++;
        }
    }

    if(g_sAnimationState.ui32FrameArrayPos >= g_sAnimationState.ui32FrameArrayLen)
    {
        g_sAnimationState.bAnimationEnable = false;
        //send Animation_Finished_Event
    }
}
