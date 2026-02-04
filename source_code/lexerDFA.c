#include "lexerDFA.h"

// Heavily depend on Trapstate being 0 and default behavior of C global arrays to init to 0
const STATE TransitionTable[][CHAR_CLASS_COUNT] = {

    [START_I] =
    {
        [CHAR_CLASS_i] = ID_I_STATE_F,
        [CHAR_CLASS_n] = ID_STATE_F,
        [CHAR_CLASS_t] = ID_STATE_F,
        [CHAR_CLASS_OTHER_LETTER] = ID_STATE_F,
        [CHAR_CLASS_DIGIT] = INT_LITERAL_STATE_F,
        [CHAR_CLASS_SEMICOLON] = STMT_END_STATE_F,
        [CHAR_CLASS_PLUS] = ADD_OP_STATE_F,
        [CHAR_CLASS_EQUAL] = ASSIGN_STATE_F,
        [CHAR_CLASS_L_PAREN] = L_PAREN_STATE_F,
        [CHAR_CLASS_R_PAREN] = R_PAREN_STATE_F,
        [CHAR_CLASS_NULL] = EOF_STATE_F,
    },

    [ID_I_STATE_F] =
    {
        [CHAR_CLASS_i] = ID_STATE_F,
        [CHAR_CLASS_n] = KW_INT_STATE_I1,
        [CHAR_CLASS_t] = ID_STATE_F,
        [CHAR_CLASS_OTHER_LETTER] = ID_STATE_F,
        [CHAR_CLASS_DIGIT] = ID_STATE_F,
    },

    [KW_INT_STATE_I1] =
    {
        [CHAR_CLASS_i] = ID_STATE_F,
        [CHAR_CLASS_n] = ID_STATE_F,
        [CHAR_CLASS_t] = KW_INT_STATE_F,
        [CHAR_CLASS_OTHER_LETTER] = ID_STATE_F,
        [CHAR_CLASS_DIGIT] = ID_STATE_F,
    },

    [KW_INT_STATE_F] =
    {
        [CHAR_CLASS_i] = ID_STATE_F,
        [CHAR_CLASS_n] = ID_STATE_F,
        [CHAR_CLASS_t] = ID_STATE_F,
        [CHAR_CLASS_OTHER_LETTER] = ID_STATE_F,
        [CHAR_CLASS_DIGIT] = ID_STATE_F,
    },

    [ID_STATE_F] =
    {
        [CHAR_CLASS_i] = ID_STATE_F,
        [CHAR_CLASS_n] = ID_STATE_F,
        [CHAR_CLASS_t] = ID_STATE_F,
        [CHAR_CLASS_OTHER_LETTER] = ID_STATE_F,
        [CHAR_CLASS_DIGIT] = ID_STATE_F,
    },
    [INT_LITERAL_STATE_F] =
    {
        [CHAR_CLASS_DIGIT] = INT_LITERAL_STATE_F,
    },

};

int isFinalState(STATE state){
    return state >= _STATE_SEPARATOR_;
}

TOKEN_TYPE getTokenTypeForFinalState(STATE state){
    switch(state){
        case EOF_STATE_F:
            return TOKEN_EOF;
        case STMT_END_STATE_F:
            return TOKEN_STMT_END;
        case KW_INT_STATE_F:
            return TOKEN_KW_INT;
        case ADD_OP_STATE_F:
            return TOKEN_ADD_OP;

        case ID_I_STATE_F:
        case ID_STATE_F:
            return TOKEN_ID;

        case INT_LITERAL_STATE_F:
            return TOKEN_INT_LITERAL;
        case ASSIGN_STATE_F:
            return TOKEN_ASSIGN;
        case L_PAREN_STATE_F:
            return TOKEN_L_PAREN;
        case R_PAREN_STATE_F:
            return TOKEN_R_PAREN;
        default:
            return TOKEN_INVALID;
    }
}

CHAR_CLASS getCharClass(char ch){
    if(ch >= 'a' && ch <= 'z'){
        switch(ch){
            case 'i':
                return CHAR_CLASS_i;
            case 'n':
                return CHAR_CLASS_n;
            case 't':
                return CHAR_CLASS_t;
            default:
                return CHAR_CLASS_OTHER_LETTER;
        }
    }else if(ch >= '0' && ch <= '9'){
        return CHAR_CLASS_DIGIT;
    }else{
        switch(ch){
            case ';':
                return CHAR_CLASS_SEMICOLON;
            case '+':
                return CHAR_CLASS_PLUS;
            case '=':
                return CHAR_CLASS_EQUAL;
            case '(':
                return CHAR_CLASS_L_PAREN;
            case ')':
                return CHAR_CLASS_R_PAREN;
            case '\0':
                return CHAR_CLASS_NULL;
            default:
                return CHAR_CLASS_OTHER;
        }
    }
}

STATE getNextState(STATE currentState, char ch){
    CHAR_CLASS charClass = getCharClass(ch);
    return TransitionTable[currentState][charClass];
}