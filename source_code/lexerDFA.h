#include "tokenType.h"

#ifndef LEXER_DFA_H
#define LEXER_DFA_H

// I means intermediary
// F means final
typedef enum{
    TRAP_STATE = 0,
    START_I,

    KW_INT_STATE_I1, 

    _STATE_SEPARATOR_, // Final state separator

    EOF_STATE_F,
    STMT_END_STATE_F,

    KW_INT_STATE_F,

    ADD_OP_STATE_F,

    ID_I_STATE_F,
    ID_STATE_F,

    INT_LITERAL_STATE_F,

    ASSIGN_STATE_F,

    L_PAREN_STATE_F,
    R_PAREN_STATE_F,
    STATE_COUNT

} STATE;



// IF the order is changed here update the TransitionTable in lexerDFA.c
typedef enum{

    CHAR_CLASS_i,
    CHAR_CLASS_n,
    CHAR_CLASS_t,
    CHAR_CLASS_OTHER_LETTER,

    CHAR_CLASS_DIGIT,
    CHAR_CLASS_SEMICOLON,
    CHAR_CLASS_PLUS,
    CHAR_CLASS_EQUAL,
    CHAR_CLASS_L_PAREN,
    CHAR_CLASS_R_PAREN,
    CHAR_CLASS_NULL,
    CHAR_CLASS_OTHER,

    CHAR_CLASS_COUNT
} CHAR_CLASS;

int isFinalState(STATE state);

TOKEN_TYPE getTokenTypeForFinalState(STATE state);
CHAR_CLASS getCharClass(char ch);
STATE getNextState(STATE currentState, char ch);

#endif