#include "AI.h"
#include "gctypes.h"
#include "system.h"
#include "game_state.h"
#include "melee_info.h"
#include "string.h"

static ControllerInput processRawInput(u8 port, RawInput input)
{
    ControllerInput processed = {.controller = input.controller,
        .frame = CURRENT_FRAME + input.frameOffset};

    if (input.flags & JUMPSQUAT)
    {
        processed.frame += (u32) _gameState.playerData[port]->jumpSquat;
    }

    if (input.flags & SH_LENGTH)
    {
        processed.frame += _sh_length[CHAR_SELECT(port)];
    }

    return processed;
}

#define COND_FPTR       ai->logicQueue[i].condition.function
#define ACTION_FPTR     ai->logicQueue[i].action.function
#define COND_ARG_1      ai->logicQueue[i].condition.arg1
#define COND_ARG_2      ai->logicQueue[i].condition.arg2
#define ACTION_ARG_1    ai->logicQueue[i].action.arg1
#define ACTION_ARG_2    ai->logicQueue[i].action.arg2
static void checkLogic(AI* ai)
{
    for (unsigned i = 0; i < ai->logicSize; ++i)
    {
        bool (*condition)(FunctionArg, FunctionArg) = COND_FPTR;
        
        if (condition(COND_ARG_1, COND_ARG_2))
        {
            clearAI(ai);
            void (*action)(FunctionArg, FunctionArg) = ACTION_FPTR;
            action(ACTION_ARG_1, ACTION_ARG_2);
            return;
        }
    }
} 

#define CONTR_INPUT     ai->inputQueue[ai->inputSize - 1]
static void checkInput(AI* ai)
{
    if (CURRENT_FRAME >= CONTR_INPUT.frame)
    {
        setController(&ai->controller, CONTR_INPUT.controller);
        ai->inputSize--;
    }
}

#define LOGIC_SIZE      ai->logicCapacity * sizeof(Logic)
void addLogic(AI* ai, Logic* logic)
{
    if (ai->logicSize == ai->logicCapacity)
    {
        ai->logicCapacity += 5;
        ai->logicQueue = realloc(ai->logicQueue, LOGIC_SIZE);
    }
    memcpy(ai->logicQueue + ai->logicSize, logic, sizeof(Logic));
    ai->logicSize++;
}

#define MOVE_SIZE       move->size * sizeof(ControllerInput)
void addMove(AI* ai, Move* move)
{
    if (move->size > ai->inputCapacity)
    {
        ai->inputQueue = realloc(ai->inputQueue, MOVE_SIZE);
        ai->inputCapacity = move->size;
    }

    for (unsigned i = 0; i < move->size; ++i)
    {
        unsigned index = (move->size - 1) - i;
        ai->inputQueue[i] = processRawInput(ai->port, move->inputs[index]);
    }
    ai->inputSize = move->size;
}

bool needLogic(AI* ai)
{
    return ai->logicSize == 0 && ai->inputSize == 0;
}

void clearAI(AI* ai)
{
    ai->logicSize = 0;  
    ai->inputSize = 0;
    ai->controller = (Controller) {0, 0.f, 0.f, 0.f, 0.f};
}

static void initAI(AI* ai)
{
    clearAI(ai);
    ai->logicCapacity = 0;
    ai->inputCapacity = 0;
    ai->logicQueue = NULL;
    ai->inputQueue = NULL;
}

static void findOpponent(AI* ai)
{
    if       (playerData(1) && ai->port != 1) {ai->opponent = 1;}
    else if  (playerData(2) && ai->port != 2) {ai->opponent = 2;}
    else if  (playerData(3) && ai->port != 3) {ai->opponent = 3;}
    else if  (playerData(4) && ai->port != 4) {ai->opponent = 4;}
}

void updateAI(AI* ai)
{
    updateGameState();
    
    if (!ai->active && inGame() && playerData(ai->port) 
        && SLOT_TYPE(ai->port) == 0x01 && _gameState.stage.ledge > 0
        && ((ai->characters >> CHAR_SELECT(ai->port)) & 1))
    {
        ai->active = true;
        initAI(ai);
        SLOT_TYPE(ai->port) = 0x00;
        stockCount = STOCKS(ai->port);
        findOpponent(ai);
    }
    
    if (ai->active && !inGame())
    {
        ai->active = false;
        clearAI(ai);
        SLOT_TYPE(ai->port) = 0x01;
        writeController(&ai->controller, ai->port, false);
    }

    if (ai->active)
    {
        checkLogic(ai);
        if (ai->inputSize > 0) {checkInput(ai);}

        writeController(&ai->controller, ai->port, true);
    }
}

