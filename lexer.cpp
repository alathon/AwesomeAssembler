#include "lexer"
#include <quex/code_base/analyzer/C-adaptions.h>
QUEX_NAMESPACE_MAIN_OPEN
/* Global */QUEX_NAME(Mode)  QUEX_NAME(ONE_AND_ONLY);
#ifndef __QUEX_INDICATOR_DUMPED_TOKEN_ID_DEFINED
    static QUEX_TYPE_TOKEN_ID    QUEX_NAME_TOKEN(DumpedTokenIdObject);
#endif
#define self  (*(QUEX_TYPE_DERIVED_ANALYZER*)me)
#define __self_result_token_id    QUEX_NAME_TOKEN(DumpedTokenIdObject)

    void
    QUEX_NAME(ONE_AND_ONLY_on_entry)(QUEX_TYPE_ANALYZER* me, const QUEX_NAME(Mode)* FromMode) {
        (void)me;
        (void)FromMode;
#ifdef __QUEX_OPTION_RUNTIME_MODE_TRANSITION_CHECK
__quex_assert(me->ONE_AND_ONLY.has_entry_from(FromMode));
#endif

    }

    void
    QUEX_NAME(ONE_AND_ONLY_on_exit)(QUEX_TYPE_ANALYZER* me, const QUEX_NAME(Mode)* ToMode)  {
        (void)me;
        (void)ToMode;
#ifdef __QUEX_OPTION_RUNTIME_MODE_TRANSITION_CHECK
__quex_assert(me->ONE_AND_ONLY.has_exit_to(ToMode));
#endif

    }

#if defined(QUEX_OPTION_INDENTATION_TRIGGER) 
    void
    QUEX_NAME(ONE_AND_ONLY_on_indentation)(QUEX_TYPE_ANALYZER*    me, 
                                            QUEX_TYPE_INDENTATION  Indentation, 
                                            QUEX_TYPE_CHARACTER*   Begin) {
        (void)me;
        (void)Indentation;
        (void)Begin;
#   if defined(QUEX_OPTION_TOKEN_POLICY_SINGLE)
       return __self_result_token_id;
#   else
       return;
#   endif

    }
#endif

#ifdef __QUEX_OPTION_RUNTIME_MODE_TRANSITION_CHECK
    bool
    QUEX_NAME(ONE_AND_ONLY_has_base)(const QUEX_NAME(Mode)* Mode) {
        (void)Mode;
    return false;
    }
    bool
    QUEX_NAME(ONE_AND_ONLY_has_entry_from)(const QUEX_NAME(Mode)* Mode) {
        (void)Mode;
    return true; /* default */
    }
    bool
    QUEX_NAME(ONE_AND_ONLY_has_exit_to)(const QUEX_NAME(Mode)* Mode) {
        (void)Mode;
    return true; /* default */
    }
#endif    
#undef self
#undef __self_result_token_id
QUEX_NAMESPACE_MAIN_CLOSE

    /* 
     * MODE: ONE_AND_ONLY
     * 
     *     PATTERN-ACTION PAIRS:
     *       (  4) ONE_AND_ONLY: [ \t]+
     *       (  9) ONE_AND_ONLY: [\n]+
     *       ( 11) ONE_AND_ONLY: ","
     *       ( 13) ONE_AND_ONLY: "add"
     *       ( 15) ONE_AND_ONLY: "addi"
     *       ( 17) ONE_AND_ONLY: "sub"
     *       ( 19) ONE_AND_ONLY: "subi"
     *       ( 21) ONE_AND_ONLY: "assign"
     *       ( 23) ONE_AND_ONLY: "mul"
     *       ( 25) ONE_AND_ONLY: "muli"
     *       ( 27) ONE_AND_ONLY: "div"
     *       ( 29) ONE_AND_ONLY: "divi"
     *       ( 34) ONE_AND_ONLY: [0-9]+
     *       ( 39) ONE_AND_ONLY: [_a-zA-Z0-9]+
     *       ( 61) ONE_AND_ONLY: \"([^\"\\\\]|\\\\.)*\"
     * 
     * 
     */
/* #include "lexer"*/
QUEX_NAMESPACE_MAIN_OPEN
QUEX_TYPE_CHARACTER  QUEX_NAME(LexemeNullObject) = (QUEX_TYPE_CHARACTER)0;

#include <quex/code_base/analyzer/member/basic>
#include <quex/code_base/buffer/Buffer>
#ifdef QUEX_OPTION_TOKEN_POLICY_QUEUE
#   include <quex/code_base/token/TokenQueue>
#endif

#ifdef    CONTINUE
#   undef CONTINUE
#endif
#define   CONTINUE goto __REENTRY_PREPARATION; 

#ifdef    RETURN
#   undef RETURN
#endif

#if defined(QUEX_OPTION_TOKEN_POLICY_QUEUE)
#   define RETURN   return
#else
#   define RETURN   do { return __self_result_token_id; } while(0)
#endif
#include <quex/code_base/temporary_macros_on>

__QUEX_TYPE_ANALYZER_RETURN_VALUE  
QUEX_NAME(ONE_AND_ONLY_analyzer_function)(QUEX_TYPE_ANALYZER* me) 
{
    /* NOTE: Different modes correspond to different analyzer functions. The analyzer  
             functions are all located inside the main class as static functions. That  
             means, they are something like 'globals'. They receive a pointer to the   
             lexical analyzer, since static member do not have access to the 'this' pointer.
     */
#   if defined(QUEX_OPTION_TOKEN_POLICY_SINGLE)
    register QUEX_TYPE_TOKEN_ID __self_result_token_id 
           = (QUEX_TYPE_TOKEN_ID)__QUEX_SETTING_TOKEN_ID_UNINITIALIZED;
#   endif
#   ifdef     self
#       undef self
#   endif
#   define self (*((QUEX_TYPE_ANALYZER*)me))
    /* me = pointer to state of the lexical analyzer */
#   define ONE_AND_ONLY    (QUEX_NAME(ONE_AND_ONLY))
    QUEX_TYPE_GOTO_LABEL           last_acceptance = QUEX_GOTO_TERMINAL_LABEL_INIT_VALUE;
    const size_t                   PostContextStartPositionN = (size_t)0;
    QUEX_TYPE_CHARACTER_POSITION*  post_context_start_position = 0x0;
    QUEX_TYPE_CHARACTER_POSITION   last_acceptance_input_position = (QUEX_TYPE_CHARACTER*)(0x00);
    QUEX_TYPE_CHARACTER            input = (QUEX_TYPE_CHARACTER)(0x00);

    /* Post context positions do not have to be reset or initialized. If a state
     * is reached which is associated with 'end of post context' it is clear what
     * post context is meant. This results from the ways the state machine is 
     * constructed. A post context positions live time looks like the following:
     *
     * (1)   unitialized (don't care)
     * (1.b) on buffer reload it may, or may not be adapted (don't care)
     * (2)   when a post context begin state is passed, the it is **SET** (now: take care)
     * (2.b) on buffer reload it **is adapted**.
     * (3)   when a terminal state of the post context is reached (which can only be reached
     *       for that particular post context, then the post context position is used
     *       to reset the input position.                                              */
#if    defined(QUEX_OPTION_AUTOMATIC_ANALYSIS_CONTINUATION_ON_MODE_CHANGE) \
    || defined(QUEX_OPTION_ASSERTS)
    me->DEBUG_analyzer_function_at_entry = me->current_analyzer_function;
#endif
__REENTRY:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: __REENTRY");
    me->buffer._lexeme_start_p = me->buffer._input_p;
    if( me->buffer._character_at_lexeme_start != (QUEX_TYPE_CHARACTER)'\0' ) {
        *(me->buffer._input_p) = me->buffer._character_at_lexeme_start;
        me->buffer._character_at_lexeme_start = (QUEX_TYPE_CHARACTER)'\0';
    }
    /* state machine */
    /* init-state = 327L
     * 00327() <~ (4, 12), (9, 28), (11, 33), (13, 39), (15, 48), (17, 57), (19, 66), (21, 78), (23, 89), (25, 98), (27, 107), (29, 116), (34, 133), (39, 148), (61, 210)
     *       == '\t', ' ' ==> 00337
     *       == '\n' ==> 00335
     *       == '"' ==> 00333
     *       == ',' ==> 00336
     *       == ['0', '9'] ==> 00334
     *       == ['A', 'Z'], '_', ['b', 'c'], ['e', 'l'], ['n', 'r'], ['t', 'z'] ==> 00331
     *       == 'a' ==> 00328
     *       == 'd' ==> 00332
     *       == 'm' ==> 00330
     *       == 's' ==> 00329
     *       <no epsilon>
     * 00337(A, S) <~ (4, 13, A, S)
     *       == '\t', ' ' ==> 00337
     *       <no epsilon>
     * 00335(A, S) <~ (9, 29, A, S)
     *       == '\n' ==> 00335
     *       <no epsilon>
     * 00333() <~ (61, 211)
     *       == [\2, '!'], ['#', '['], [']', 'ÿ'] ==> 00333
     *       == '"' ==> 00339
     *       == '\' ==> 00338
     *       <no epsilon>
     * 00339(A, S) <~ (61, 213, A, S)
     *       <no epsilon>
     * 00338() <~ (61, 214)
     *       == '\' ==> 00340
     *       <no epsilon>
     * 00340() <~ (61, 215)
     *       == [\2, '\t'], ['\v', 'ÿ'] ==> 00333
     *       <no epsilon>
     * 00336(A, S) <~ (11, 34, A, S)
     *       <no epsilon>
     * 00334(A, S) <~ (34, 134, A, S)
     *       == ['0', '9'] ==> 00334
     *       == ['A', 'Z'], '_', ['a', 'z'] ==> 00331
     *       <no epsilon>
     * 00331(A, S) <~ (39, 149, A, S)
     *       == ['0', '9'], ['A', 'Z'], '_', ['a', 'z'] ==> 00331
     *       <no epsilon>
     * 00328(A, S) <~ (39, 149, A, S), (13, 40), (15, 49), (21, 79)
     *       == ['0', '9'], ['A', 'Z'], '_', ['a', 'c'], ['e', 'r'], ['t', 'z'] ==> 00331
     *       == 'd' ==> 00350
     *       == 's' ==> 00351
     *       <no epsilon>
     * 00350(A, S) <~ (39, 149, A, S), (13, 41), (15, 50)
     *       == ['0', '9'], ['A', 'Z'], '_', ['a', 'c'], ['e', 'z'] ==> 00331
     *       == 'd' ==> 00356
     *       <no epsilon>
     * 00356(A, S) <~ (13, 42, A, S), (15, 51)
     *       == ['0', '9'], ['A', 'Z'], '_', ['a', 'h'], ['j', 'z'] ==> 00331
     *       == 'i' ==> 00357
     *       <no epsilon>
     * 00357(A, S) <~ (15, 52, A, S)
     *       == ['0', '9'], ['A', 'Z'], '_', ['a', 'z'] ==> 00331
     *       <no epsilon>
     * 00351(A, S) <~ (39, 149, A, S), (21, 80)
     *       == ['0', '9'], ['A', 'Z'], '_', ['a', 'r'], ['t', 'z'] ==> 00331
     *       == 's' ==> 00352
     *       <no epsilon>
     * 00352(A, S) <~ (39, 149, A, S), (21, 81)
     *       == ['0', '9'], ['A', 'Z'], '_', ['a', 'h'], ['j', 'z'] ==> 00331
     *       == 'i' ==> 00353
     *       <no epsilon>
     * 00353(A, S) <~ (39, 149, A, S), (21, 82)
     *       == ['0', '9'], ['A', 'Z'], '_', ['a', 'f'], ['h', 'z'] ==> 00331
     *       == 'g' ==> 00354
     *       <no epsilon>
     * 00354(A, S) <~ (39, 149, A, S), (21, 83)
     *       == ['0', '9'], ['A', 'Z'], '_', ['a', 'm'], ['o', 'z'] ==> 00331
     *       == 'n' ==> 00355
     *       <no epsilon>
     * 00355(A, S) <~ (21, 84, A, S)
     *       == ['0', '9'], ['A', 'Z'], '_', ['a', 'z'] ==> 00331
     *       <no epsilon>
     * 00332(A, S) <~ (39, 149, A, S), (27, 108), (29, 117)
     *       == ['0', '9'], ['A', 'Z'], '_', ['a', 'h'], ['j', 'z'] ==> 00331
     *       == 'i' ==> 00341
     *       <no epsilon>
     * 00341(A, S) <~ (39, 149, A, S), (27, 109), (29, 118)
     *       == ['0', '9'], ['A', 'Z'], '_', ['a', 'u'], ['w', 'z'] ==> 00331
     *       == 'v' ==> 00342
     *       <no epsilon>
     * 00342(A, S) <~ (27, 110, A, S), (29, 119)
     *       == ['0', '9'], ['A', 'Z'], '_', ['a', 'h'], ['j', 'z'] ==> 00331
     *       == 'i' ==> 00343
     *       <no epsilon>
     * 00343(A, S) <~ (29, 120, A, S)
     *       == ['0', '9'], ['A', 'Z'], '_', ['a', 'z'] ==> 00331
     *       <no epsilon>
     * 00330(A, S) <~ (39, 149, A, S), (23, 90), (25, 99)
     *       == ['0', '9'], ['A', 'Z'], '_', ['a', 't'], ['v', 'z'] ==> 00331
     *       == 'u' ==> 00344
     *       <no epsilon>
     * 00344(A, S) <~ (39, 149, A, S), (23, 91), (25, 100)
     *       == ['0', '9'], ['A', 'Z'], '_', ['a', 'k'], ['m', 'z'] ==> 00331
     *       == 'l' ==> 00345
     *       <no epsilon>
     * 00345(A, S) <~ (23, 92, A, S), (25, 101)
     *       == ['0', '9'], ['A', 'Z'], '_', ['a', 'h'], ['j', 'z'] ==> 00331
     *       == 'i' ==> 00346
     *       <no epsilon>
     * 00346(A, S) <~ (25, 102, A, S)
     *       == ['0', '9'], ['A', 'Z'], '_', ['a', 'z'] ==> 00331
     *       <no epsilon>
     * 00329(A, S) <~ (39, 149, A, S), (17, 58), (19, 67)
     *       == ['0', '9'], ['A', 'Z'], '_', ['a', 't'], ['v', 'z'] ==> 00331
     *       == 'u' ==> 00347
     *       <no epsilon>
     * 00347(A, S) <~ (39, 149, A, S), (17, 59), (19, 68)
     *       == ['0', '9'], ['A', 'Z'], '_', 'a', ['c', 'z'] ==> 00331
     *       == 'b' ==> 00348
     *       <no epsilon>
     * 00348(A, S) <~ (17, 60, A, S), (19, 69)
     *       == ['0', '9'], ['A', 'Z'], '_', ['a', 'h'], ['j', 'z'] ==> 00331
     *       == 'i' ==> 00349
     *       <no epsilon>
     * 00349(A, S) <~ (19, 70, A, S)
     *       == ['0', '9'], ['A', 'Z'], '_', ['a', 'z'] ==> 00331
     *       <no epsilon>
     * 
     */
STATE_327:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_327");
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_327_RELOAD;
    case 0x9: goto STATE_337;
    case 0xA: goto STATE_335;
    case 0x20: goto STATE_337;
    case 0x22: goto STATE_333;
    case 0x2C: goto TERMINAL_11;
    case 0x30: 
    case 0x31: 
    case 0x32: 
    case 0x33: 
    case 0x34: 
    case 0x35: 
    case 0x36: 
    case 0x37: 
    case 0x38: 
    case 0x39: goto STATE_334;
    case 0x41: 
    case 0x42: 
    case 0x43: 
    case 0x44: 
    case 0x45: 
    case 0x46: 
    case 0x47: 
    case 0x48: 
    case 0x49: 
    case 0x4A: 
    case 0x4B: 
    case 0x4C: 
    case 0x4D: 
    case 0x4E: 
    case 0x4F: 
    case 0x50: 
    case 0x51: 
    case 0x52: 
    case 0x53: 
    case 0x54: 
    case 0x55: 
    case 0x56: 
    case 0x57: 
    case 0x58: 
    case 0x59: 
    case 0x5A: 
    case 0x5F: goto STATE_331;
    case 0x61: goto STATE_328;
    case 0x62: 
    case 0x63: goto STATE_331;
    case 0x64: goto STATE_332;
    case 0x65: 
    case 0x66: 
    case 0x67: 
    case 0x68: 
    case 0x69: 
    case 0x6A: 
    case 0x6B: 
    case 0x6C: goto STATE_331;
    case 0x6D: goto STATE_330;
    case 0x6E: 
    case 0x6F: 
    case 0x70: 
    case 0x71: 
    case 0x72: goto STATE_331;
    case 0x73: goto STATE_329;
    case 0x74: 
    case 0x75: 
    case 0x76: 
    case 0x77: 
    case 0x78: 
    case 0x79: 
    case 0x7A: goto STATE_331;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_327_DROP_OUT_DIRECT");

    goto TERMINAL_FAILURE;

STATE_327_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_327_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( (me->buffer._memory._end_of_file_p != 0x0) ) {
        goto TERMINAL_END_OF_STREAM;
    }
    QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
    goto STATE_327_INPUT;
STATE_327_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_327_INPUT");
    ++(me->buffer._input_p);
    goto STATE_327;

    __quex_assert(false); /* No drop-through between states */
STATE_331:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_331");
STATE_331_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_331_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    if( input < 0x5B) {
        if( input < 0x30) {
            if( input == 0x0 ) {
                goto STATE_331_RELOAD;    /* \0 */
            }
        } else {
            if( input < 0x3A) {
                goto STATE_331;    /* ['0', '9'] */
            } else {
                if( input >= 0x41) {
                    goto STATE_331;    /* ['A', 'Z'] */
                }
            }
        }
    } else {
        if( input < 0x60) {
            if( input == 0x5F ) {
                goto STATE_331;    /* '_' */
            }
        } else {
            if( input != 0x60 ) {
                if( input < 0x7B) {
                    goto STATE_331;    /* ['a', 'z'] */
                }
            }
        }
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_331_DROP_OUT_DIRECT");

            goto TERMINAL_39_DIRECT;

STATE_331_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_331_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_331_INPUT;
    }
        goto TERMINAL_39_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_333:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_333");
STATE_333_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_333_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    if( input < 0x23) {
        if( input < 0x2) {
            if( input == 0x0 ) {
                goto STATE_333_RELOAD;    /* \0 */
            }
        } else {
            if( input != 0x22 ) {
                goto STATE_333;    /* [\2, '!'] */
            } else {
                goto TERMINAL_61;    /* '"' */
            }
        }
    } else {
        if( input < 0x5D) {
            if( input != 0x5C ) {
                goto STATE_333;    /* ['#', '['] */
            } else {
                goto STATE_338;    /* '\' */
            }
        } else {
            if( input < 0x100) {
                goto STATE_333;    /* [']', 'ÿ'] */
            }
        }
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_333_DROP_OUT_DIRECT");

        QUEX_GOTO_last_acceptance();


STATE_333_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_333_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_333_INPUT;
    }
    QUEX_GOTO_last_acceptance();



    __quex_assert(false); /* No drop-through between states */
STATE_334:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_334");
STATE_334_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_334_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    if( input < 0x5B) {
        if( input < 0x30) {
            if( input == 0x0 ) {
                goto STATE_334_RELOAD;    /* \0 */
            }
        } else {
            if( input < 0x3A) {
                goto STATE_334;    /* ['0', '9'] */
            } else {
                if( input >= 0x41) {
                    goto STATE_331;    /* ['A', 'Z'] */
                }
            }
        }
    } else {
        if( input < 0x60) {
            if( input == 0x5F ) {
                goto STATE_331;    /* '_' */
            }
        } else {
            if( input != 0x60 ) {
                if( input < 0x7B) {
                    goto STATE_331;    /* ['a', 'z'] */
                }
            }
        }
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_334_DROP_OUT_DIRECT");

            goto TERMINAL_34_DIRECT;

STATE_334_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_334_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_334_INPUT;
    }
        goto TERMINAL_34_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_335:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_335");
STATE_335_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_335_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_335_RELOAD;
    case 0xA: goto STATE_335;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_335_DROP_OUT_DIRECT");

            goto TERMINAL_9_DIRECT;

STATE_335_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_335_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_335_INPUT;
    }
        goto TERMINAL_9_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_337:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_337");
STATE_337_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_337_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_337_RELOAD;
    case 0x9: 
    case 0x20: goto STATE_337;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_337_DROP_OUT_DIRECT");

            goto TERMINAL_4_DIRECT;

STATE_337_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_337_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_337_INPUT;
    }
        goto TERMINAL_4_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_328:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_328");
STATE_328_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_328_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_328_RELOAD;
    case 0x30: 
    case 0x31: 
    case 0x32: 
    case 0x33: 
    case 0x34: 
    case 0x35: 
    case 0x36: 
    case 0x37: 
    case 0x38: 
    case 0x39: 
    case 0x41: 
    case 0x42: 
    case 0x43: 
    case 0x44: 
    case 0x45: 
    case 0x46: 
    case 0x47: 
    case 0x48: 
    case 0x49: 
    case 0x4A: 
    case 0x4B: 
    case 0x4C: 
    case 0x4D: 
    case 0x4E: 
    case 0x4F: 
    case 0x50: 
    case 0x51: 
    case 0x52: 
    case 0x53: 
    case 0x54: 
    case 0x55: 
    case 0x56: 
    case 0x57: 
    case 0x58: 
    case 0x59: 
    case 0x5A: 
    case 0x5F: 
    case 0x61: 
    case 0x62: 
    case 0x63: goto STATE_331;
    case 0x64: goto STATE_350;
    case 0x65: 
    case 0x66: 
    case 0x67: 
    case 0x68: 
    case 0x69: 
    case 0x6A: 
    case 0x6B: 
    case 0x6C: 
    case 0x6D: 
    case 0x6E: 
    case 0x6F: 
    case 0x70: 
    case 0x71: 
    case 0x72: goto STATE_331;
    case 0x73: goto STATE_351;
    case 0x74: 
    case 0x75: 
    case 0x76: 
    case 0x77: 
    case 0x78: 
    case 0x79: 
    case 0x7A: goto STATE_331;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_328_DROP_OUT_DIRECT");

            goto TERMINAL_39_DIRECT;

STATE_328_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_328_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_328_INPUT;
    }
        goto TERMINAL_39_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_329:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_329");
STATE_329_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_329_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_329_RELOAD;
    case 0x30: 
    case 0x31: 
    case 0x32: 
    case 0x33: 
    case 0x34: 
    case 0x35: 
    case 0x36: 
    case 0x37: 
    case 0x38: 
    case 0x39: 
    case 0x41: 
    case 0x42: 
    case 0x43: 
    case 0x44: 
    case 0x45: 
    case 0x46: 
    case 0x47: 
    case 0x48: 
    case 0x49: 
    case 0x4A: 
    case 0x4B: 
    case 0x4C: 
    case 0x4D: 
    case 0x4E: 
    case 0x4F: 
    case 0x50: 
    case 0x51: 
    case 0x52: 
    case 0x53: 
    case 0x54: 
    case 0x55: 
    case 0x56: 
    case 0x57: 
    case 0x58: 
    case 0x59: 
    case 0x5A: 
    case 0x5F: 
    case 0x61: 
    case 0x62: 
    case 0x63: 
    case 0x64: 
    case 0x65: 
    case 0x66: 
    case 0x67: 
    case 0x68: 
    case 0x69: 
    case 0x6A: 
    case 0x6B: 
    case 0x6C: 
    case 0x6D: 
    case 0x6E: 
    case 0x6F: 
    case 0x70: 
    case 0x71: 
    case 0x72: 
    case 0x73: 
    case 0x74: goto STATE_331;
    case 0x75: goto STATE_347;
    case 0x76: 
    case 0x77: 
    case 0x78: 
    case 0x79: 
    case 0x7A: goto STATE_331;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_329_DROP_OUT_DIRECT");

            goto TERMINAL_39_DIRECT;

STATE_329_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_329_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_329_INPUT;
    }
        goto TERMINAL_39_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_330:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_330");
STATE_330_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_330_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_330_RELOAD;
    case 0x30: 
    case 0x31: 
    case 0x32: 
    case 0x33: 
    case 0x34: 
    case 0x35: 
    case 0x36: 
    case 0x37: 
    case 0x38: 
    case 0x39: 
    case 0x41: 
    case 0x42: 
    case 0x43: 
    case 0x44: 
    case 0x45: 
    case 0x46: 
    case 0x47: 
    case 0x48: 
    case 0x49: 
    case 0x4A: 
    case 0x4B: 
    case 0x4C: 
    case 0x4D: 
    case 0x4E: 
    case 0x4F: 
    case 0x50: 
    case 0x51: 
    case 0x52: 
    case 0x53: 
    case 0x54: 
    case 0x55: 
    case 0x56: 
    case 0x57: 
    case 0x58: 
    case 0x59: 
    case 0x5A: 
    case 0x5F: 
    case 0x61: 
    case 0x62: 
    case 0x63: 
    case 0x64: 
    case 0x65: 
    case 0x66: 
    case 0x67: 
    case 0x68: 
    case 0x69: 
    case 0x6A: 
    case 0x6B: 
    case 0x6C: 
    case 0x6D: 
    case 0x6E: 
    case 0x6F: 
    case 0x70: 
    case 0x71: 
    case 0x72: 
    case 0x73: 
    case 0x74: goto STATE_331;
    case 0x75: goto STATE_344;
    case 0x76: 
    case 0x77: 
    case 0x78: 
    case 0x79: 
    case 0x7A: goto STATE_331;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_330_DROP_OUT_DIRECT");

            goto TERMINAL_39_DIRECT;

STATE_330_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_330_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_330_INPUT;
    }
        goto TERMINAL_39_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_332:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_332");
STATE_332_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_332_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_332_RELOAD;
    case 0x30: 
    case 0x31: 
    case 0x32: 
    case 0x33: 
    case 0x34: 
    case 0x35: 
    case 0x36: 
    case 0x37: 
    case 0x38: 
    case 0x39: 
    case 0x41: 
    case 0x42: 
    case 0x43: 
    case 0x44: 
    case 0x45: 
    case 0x46: 
    case 0x47: 
    case 0x48: 
    case 0x49: 
    case 0x4A: 
    case 0x4B: 
    case 0x4C: 
    case 0x4D: 
    case 0x4E: 
    case 0x4F: 
    case 0x50: 
    case 0x51: 
    case 0x52: 
    case 0x53: 
    case 0x54: 
    case 0x55: 
    case 0x56: 
    case 0x57: 
    case 0x58: 
    case 0x59: 
    case 0x5A: 
    case 0x5F: 
    case 0x61: 
    case 0x62: 
    case 0x63: 
    case 0x64: 
    case 0x65: 
    case 0x66: 
    case 0x67: 
    case 0x68: goto STATE_331;
    case 0x69: goto STATE_341;
    case 0x6A: 
    case 0x6B: 
    case 0x6C: 
    case 0x6D: 
    case 0x6E: 
    case 0x6F: 
    case 0x70: 
    case 0x71: 
    case 0x72: 
    case 0x73: 
    case 0x74: 
    case 0x75: 
    case 0x76: 
    case 0x77: 
    case 0x78: 
    case 0x79: 
    case 0x7A: goto STATE_331;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_332_DROP_OUT_DIRECT");

            goto TERMINAL_39_DIRECT;

STATE_332_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_332_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_332_INPUT;
    }
        goto TERMINAL_39_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_338:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_338");
STATE_338_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_338_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_338_RELOAD;
    case 0x5C: goto STATE_340;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_338_DROP_OUT_DIRECT");

        QUEX_GOTO_last_acceptance();


STATE_338_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_338_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_338_INPUT;
    }
    QUEX_GOTO_last_acceptance();



    __quex_assert(false); /* No drop-through between states */
STATE_340:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_340");
STATE_340_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_340_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    if( input < 0xA) {
        switch( input ) {
        case 0x0: goto STATE_340_RELOAD;
        case 0x2: 
        case 0x3: 
        case 0x4: 
        case 0x5: 
        case 0x6: 
        case 0x7: 
        case 0x8: 
        case 0x9: goto STATE_333;
        }
    } else {
        if( input != 0xA ) {
            if( input < 0x100) {
                goto STATE_333;    /* ['\v', 'ÿ'] */
            }
        }
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_340_DROP_OUT_DIRECT");

        QUEX_GOTO_last_acceptance();


STATE_340_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_340_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_340_INPUT;
    }
    QUEX_GOTO_last_acceptance();



    __quex_assert(false); /* No drop-through between states */
STATE_341:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_341");
STATE_341_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_341_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_341_RELOAD;
    case 0x30: 
    case 0x31: 
    case 0x32: 
    case 0x33: 
    case 0x34: 
    case 0x35: 
    case 0x36: 
    case 0x37: 
    case 0x38: 
    case 0x39: 
    case 0x41: 
    case 0x42: 
    case 0x43: 
    case 0x44: 
    case 0x45: 
    case 0x46: 
    case 0x47: 
    case 0x48: 
    case 0x49: 
    case 0x4A: 
    case 0x4B: 
    case 0x4C: 
    case 0x4D: 
    case 0x4E: 
    case 0x4F: 
    case 0x50: 
    case 0x51: 
    case 0x52: 
    case 0x53: 
    case 0x54: 
    case 0x55: 
    case 0x56: 
    case 0x57: 
    case 0x58: 
    case 0x59: 
    case 0x5A: 
    case 0x5F: 
    case 0x61: 
    case 0x62: 
    case 0x63: 
    case 0x64: 
    case 0x65: 
    case 0x66: 
    case 0x67: 
    case 0x68: 
    case 0x69: 
    case 0x6A: 
    case 0x6B: 
    case 0x6C: 
    case 0x6D: 
    case 0x6E: 
    case 0x6F: 
    case 0x70: 
    case 0x71: 
    case 0x72: 
    case 0x73: 
    case 0x74: 
    case 0x75: goto STATE_331;
    case 0x76: goto STATE_342;
    case 0x77: 
    case 0x78: 
    case 0x79: 
    case 0x7A: goto STATE_331;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_341_DROP_OUT_DIRECT");

            goto TERMINAL_39_DIRECT;

STATE_341_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_341_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_341_INPUT;
    }
        goto TERMINAL_39_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_342:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_342");
STATE_342_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_342_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_342_RELOAD;
    case 0x30: 
    case 0x31: 
    case 0x32: 
    case 0x33: 
    case 0x34: 
    case 0x35: 
    case 0x36: 
    case 0x37: 
    case 0x38: 
    case 0x39: 
    case 0x41: 
    case 0x42: 
    case 0x43: 
    case 0x44: 
    case 0x45: 
    case 0x46: 
    case 0x47: 
    case 0x48: 
    case 0x49: 
    case 0x4A: 
    case 0x4B: 
    case 0x4C: 
    case 0x4D: 
    case 0x4E: 
    case 0x4F: 
    case 0x50: 
    case 0x51: 
    case 0x52: 
    case 0x53: 
    case 0x54: 
    case 0x55: 
    case 0x56: 
    case 0x57: 
    case 0x58: 
    case 0x59: 
    case 0x5A: 
    case 0x5F: 
    case 0x61: 
    case 0x62: 
    case 0x63: 
    case 0x64: 
    case 0x65: 
    case 0x66: 
    case 0x67: 
    case 0x68: goto STATE_331;
    case 0x69: goto STATE_343;
    case 0x6A: 
    case 0x6B: 
    case 0x6C: 
    case 0x6D: 
    case 0x6E: 
    case 0x6F: 
    case 0x70: 
    case 0x71: 
    case 0x72: 
    case 0x73: 
    case 0x74: 
    case 0x75: 
    case 0x76: 
    case 0x77: 
    case 0x78: 
    case 0x79: 
    case 0x7A: goto STATE_331;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_342_DROP_OUT_DIRECT");

            goto TERMINAL_27_DIRECT;

STATE_342_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_342_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_342_INPUT;
    }
        goto TERMINAL_27_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_343:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_343");
STATE_343_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_343_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    if( input < 0x5B) {
        if( input < 0x30) {
            if( input == 0x0 ) {
                goto STATE_343_RELOAD;    /* \0 */
            }
        } else {
            if( input < 0x3A) {
                goto STATE_331;    /* ['0', '9'] */
            } else {
                if( input >= 0x41) {
                    goto STATE_331;    /* ['A', 'Z'] */
                }
            }
        }
    } else {
        if( input < 0x60) {
            if( input == 0x5F ) {
                goto STATE_331;    /* '_' */
            }
        } else {
            if( input != 0x60 ) {
                if( input < 0x7B) {
                    goto STATE_331;    /* ['a', 'z'] */
                }
            }
        }
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_343_DROP_OUT_DIRECT");

            goto TERMINAL_29_DIRECT;

STATE_343_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_343_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_343_INPUT;
    }
        goto TERMINAL_29_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_344:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_344");
STATE_344_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_344_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_344_RELOAD;
    case 0x30: 
    case 0x31: 
    case 0x32: 
    case 0x33: 
    case 0x34: 
    case 0x35: 
    case 0x36: 
    case 0x37: 
    case 0x38: 
    case 0x39: 
    case 0x41: 
    case 0x42: 
    case 0x43: 
    case 0x44: 
    case 0x45: 
    case 0x46: 
    case 0x47: 
    case 0x48: 
    case 0x49: 
    case 0x4A: 
    case 0x4B: 
    case 0x4C: 
    case 0x4D: 
    case 0x4E: 
    case 0x4F: 
    case 0x50: 
    case 0x51: 
    case 0x52: 
    case 0x53: 
    case 0x54: 
    case 0x55: 
    case 0x56: 
    case 0x57: 
    case 0x58: 
    case 0x59: 
    case 0x5A: 
    case 0x5F: 
    case 0x61: 
    case 0x62: 
    case 0x63: 
    case 0x64: 
    case 0x65: 
    case 0x66: 
    case 0x67: 
    case 0x68: 
    case 0x69: 
    case 0x6A: 
    case 0x6B: goto STATE_331;
    case 0x6C: goto STATE_345;
    case 0x6D: 
    case 0x6E: 
    case 0x6F: 
    case 0x70: 
    case 0x71: 
    case 0x72: 
    case 0x73: 
    case 0x74: 
    case 0x75: 
    case 0x76: 
    case 0x77: 
    case 0x78: 
    case 0x79: 
    case 0x7A: goto STATE_331;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_344_DROP_OUT_DIRECT");

            goto TERMINAL_39_DIRECT;

STATE_344_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_344_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_344_INPUT;
    }
        goto TERMINAL_39_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_345:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_345");
STATE_345_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_345_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_345_RELOAD;
    case 0x30: 
    case 0x31: 
    case 0x32: 
    case 0x33: 
    case 0x34: 
    case 0x35: 
    case 0x36: 
    case 0x37: 
    case 0x38: 
    case 0x39: 
    case 0x41: 
    case 0x42: 
    case 0x43: 
    case 0x44: 
    case 0x45: 
    case 0x46: 
    case 0x47: 
    case 0x48: 
    case 0x49: 
    case 0x4A: 
    case 0x4B: 
    case 0x4C: 
    case 0x4D: 
    case 0x4E: 
    case 0x4F: 
    case 0x50: 
    case 0x51: 
    case 0x52: 
    case 0x53: 
    case 0x54: 
    case 0x55: 
    case 0x56: 
    case 0x57: 
    case 0x58: 
    case 0x59: 
    case 0x5A: 
    case 0x5F: 
    case 0x61: 
    case 0x62: 
    case 0x63: 
    case 0x64: 
    case 0x65: 
    case 0x66: 
    case 0x67: 
    case 0x68: goto STATE_331;
    case 0x69: goto STATE_346;
    case 0x6A: 
    case 0x6B: 
    case 0x6C: 
    case 0x6D: 
    case 0x6E: 
    case 0x6F: 
    case 0x70: 
    case 0x71: 
    case 0x72: 
    case 0x73: 
    case 0x74: 
    case 0x75: 
    case 0x76: 
    case 0x77: 
    case 0x78: 
    case 0x79: 
    case 0x7A: goto STATE_331;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_345_DROP_OUT_DIRECT");

            goto TERMINAL_23_DIRECT;

STATE_345_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_345_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_345_INPUT;
    }
        goto TERMINAL_23_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_346:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_346");
STATE_346_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_346_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    if( input < 0x5B) {
        if( input < 0x30) {
            if( input == 0x0 ) {
                goto STATE_346_RELOAD;    /* \0 */
            }
        } else {
            if( input < 0x3A) {
                goto STATE_331;    /* ['0', '9'] */
            } else {
                if( input >= 0x41) {
                    goto STATE_331;    /* ['A', 'Z'] */
                }
            }
        }
    } else {
        if( input < 0x60) {
            if( input == 0x5F ) {
                goto STATE_331;    /* '_' */
            }
        } else {
            if( input != 0x60 ) {
                if( input < 0x7B) {
                    goto STATE_331;    /* ['a', 'z'] */
                }
            }
        }
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_346_DROP_OUT_DIRECT");

            goto TERMINAL_25_DIRECT;

STATE_346_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_346_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_346_INPUT;
    }
        goto TERMINAL_25_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_347:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_347");
STATE_347_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_347_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_347_RELOAD;
    case 0x30: 
    case 0x31: 
    case 0x32: 
    case 0x33: 
    case 0x34: 
    case 0x35: 
    case 0x36: 
    case 0x37: 
    case 0x38: 
    case 0x39: 
    case 0x41: 
    case 0x42: 
    case 0x43: 
    case 0x44: 
    case 0x45: 
    case 0x46: 
    case 0x47: 
    case 0x48: 
    case 0x49: 
    case 0x4A: 
    case 0x4B: 
    case 0x4C: 
    case 0x4D: 
    case 0x4E: 
    case 0x4F: 
    case 0x50: 
    case 0x51: 
    case 0x52: 
    case 0x53: 
    case 0x54: 
    case 0x55: 
    case 0x56: 
    case 0x57: 
    case 0x58: 
    case 0x59: 
    case 0x5A: 
    case 0x5F: 
    case 0x61: goto STATE_331;
    case 0x62: goto STATE_348;
    case 0x63: 
    case 0x64: 
    case 0x65: 
    case 0x66: 
    case 0x67: 
    case 0x68: 
    case 0x69: 
    case 0x6A: 
    case 0x6B: 
    case 0x6C: 
    case 0x6D: 
    case 0x6E: 
    case 0x6F: 
    case 0x70: 
    case 0x71: 
    case 0x72: 
    case 0x73: 
    case 0x74: 
    case 0x75: 
    case 0x76: 
    case 0x77: 
    case 0x78: 
    case 0x79: 
    case 0x7A: goto STATE_331;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_347_DROP_OUT_DIRECT");

            goto TERMINAL_39_DIRECT;

STATE_347_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_347_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_347_INPUT;
    }
        goto TERMINAL_39_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_348:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_348");
STATE_348_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_348_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_348_RELOAD;
    case 0x30: 
    case 0x31: 
    case 0x32: 
    case 0x33: 
    case 0x34: 
    case 0x35: 
    case 0x36: 
    case 0x37: 
    case 0x38: 
    case 0x39: 
    case 0x41: 
    case 0x42: 
    case 0x43: 
    case 0x44: 
    case 0x45: 
    case 0x46: 
    case 0x47: 
    case 0x48: 
    case 0x49: 
    case 0x4A: 
    case 0x4B: 
    case 0x4C: 
    case 0x4D: 
    case 0x4E: 
    case 0x4F: 
    case 0x50: 
    case 0x51: 
    case 0x52: 
    case 0x53: 
    case 0x54: 
    case 0x55: 
    case 0x56: 
    case 0x57: 
    case 0x58: 
    case 0x59: 
    case 0x5A: 
    case 0x5F: 
    case 0x61: 
    case 0x62: 
    case 0x63: 
    case 0x64: 
    case 0x65: 
    case 0x66: 
    case 0x67: 
    case 0x68: goto STATE_331;
    case 0x69: goto STATE_349;
    case 0x6A: 
    case 0x6B: 
    case 0x6C: 
    case 0x6D: 
    case 0x6E: 
    case 0x6F: 
    case 0x70: 
    case 0x71: 
    case 0x72: 
    case 0x73: 
    case 0x74: 
    case 0x75: 
    case 0x76: 
    case 0x77: 
    case 0x78: 
    case 0x79: 
    case 0x7A: goto STATE_331;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_348_DROP_OUT_DIRECT");

            goto TERMINAL_17_DIRECT;

STATE_348_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_348_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_348_INPUT;
    }
        goto TERMINAL_17_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_349:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_349");
STATE_349_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_349_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    if( input < 0x5B) {
        if( input < 0x30) {
            if( input == 0x0 ) {
                goto STATE_349_RELOAD;    /* \0 */
            }
        } else {
            if( input < 0x3A) {
                goto STATE_331;    /* ['0', '9'] */
            } else {
                if( input >= 0x41) {
                    goto STATE_331;    /* ['A', 'Z'] */
                }
            }
        }
    } else {
        if( input < 0x60) {
            if( input == 0x5F ) {
                goto STATE_331;    /* '_' */
            }
        } else {
            if( input != 0x60 ) {
                if( input < 0x7B) {
                    goto STATE_331;    /* ['a', 'z'] */
                }
            }
        }
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_349_DROP_OUT_DIRECT");

            goto TERMINAL_19_DIRECT;

STATE_349_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_349_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_349_INPUT;
    }
        goto TERMINAL_19_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_350:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_350");
STATE_350_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_350_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_350_RELOAD;
    case 0x30: 
    case 0x31: 
    case 0x32: 
    case 0x33: 
    case 0x34: 
    case 0x35: 
    case 0x36: 
    case 0x37: 
    case 0x38: 
    case 0x39: 
    case 0x41: 
    case 0x42: 
    case 0x43: 
    case 0x44: 
    case 0x45: 
    case 0x46: 
    case 0x47: 
    case 0x48: 
    case 0x49: 
    case 0x4A: 
    case 0x4B: 
    case 0x4C: 
    case 0x4D: 
    case 0x4E: 
    case 0x4F: 
    case 0x50: 
    case 0x51: 
    case 0x52: 
    case 0x53: 
    case 0x54: 
    case 0x55: 
    case 0x56: 
    case 0x57: 
    case 0x58: 
    case 0x59: 
    case 0x5A: 
    case 0x5F: 
    case 0x61: 
    case 0x62: 
    case 0x63: goto STATE_331;
    case 0x64: goto STATE_356;
    case 0x65: 
    case 0x66: 
    case 0x67: 
    case 0x68: 
    case 0x69: 
    case 0x6A: 
    case 0x6B: 
    case 0x6C: 
    case 0x6D: 
    case 0x6E: 
    case 0x6F: 
    case 0x70: 
    case 0x71: 
    case 0x72: 
    case 0x73: 
    case 0x74: 
    case 0x75: 
    case 0x76: 
    case 0x77: 
    case 0x78: 
    case 0x79: 
    case 0x7A: goto STATE_331;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_350_DROP_OUT_DIRECT");

            goto TERMINAL_39_DIRECT;

STATE_350_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_350_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_350_INPUT;
    }
        goto TERMINAL_39_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_351:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_351");
STATE_351_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_351_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_351_RELOAD;
    case 0x30: 
    case 0x31: 
    case 0x32: 
    case 0x33: 
    case 0x34: 
    case 0x35: 
    case 0x36: 
    case 0x37: 
    case 0x38: 
    case 0x39: 
    case 0x41: 
    case 0x42: 
    case 0x43: 
    case 0x44: 
    case 0x45: 
    case 0x46: 
    case 0x47: 
    case 0x48: 
    case 0x49: 
    case 0x4A: 
    case 0x4B: 
    case 0x4C: 
    case 0x4D: 
    case 0x4E: 
    case 0x4F: 
    case 0x50: 
    case 0x51: 
    case 0x52: 
    case 0x53: 
    case 0x54: 
    case 0x55: 
    case 0x56: 
    case 0x57: 
    case 0x58: 
    case 0x59: 
    case 0x5A: 
    case 0x5F: 
    case 0x61: 
    case 0x62: 
    case 0x63: 
    case 0x64: 
    case 0x65: 
    case 0x66: 
    case 0x67: 
    case 0x68: 
    case 0x69: 
    case 0x6A: 
    case 0x6B: 
    case 0x6C: 
    case 0x6D: 
    case 0x6E: 
    case 0x6F: 
    case 0x70: 
    case 0x71: 
    case 0x72: goto STATE_331;
    case 0x73: goto STATE_352;
    case 0x74: 
    case 0x75: 
    case 0x76: 
    case 0x77: 
    case 0x78: 
    case 0x79: 
    case 0x7A: goto STATE_331;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_351_DROP_OUT_DIRECT");

            goto TERMINAL_39_DIRECT;

STATE_351_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_351_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_351_INPUT;
    }
        goto TERMINAL_39_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_352:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_352");
STATE_352_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_352_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_352_RELOAD;
    case 0x30: 
    case 0x31: 
    case 0x32: 
    case 0x33: 
    case 0x34: 
    case 0x35: 
    case 0x36: 
    case 0x37: 
    case 0x38: 
    case 0x39: 
    case 0x41: 
    case 0x42: 
    case 0x43: 
    case 0x44: 
    case 0x45: 
    case 0x46: 
    case 0x47: 
    case 0x48: 
    case 0x49: 
    case 0x4A: 
    case 0x4B: 
    case 0x4C: 
    case 0x4D: 
    case 0x4E: 
    case 0x4F: 
    case 0x50: 
    case 0x51: 
    case 0x52: 
    case 0x53: 
    case 0x54: 
    case 0x55: 
    case 0x56: 
    case 0x57: 
    case 0x58: 
    case 0x59: 
    case 0x5A: 
    case 0x5F: 
    case 0x61: 
    case 0x62: 
    case 0x63: 
    case 0x64: 
    case 0x65: 
    case 0x66: 
    case 0x67: 
    case 0x68: goto STATE_331;
    case 0x69: goto STATE_353;
    case 0x6A: 
    case 0x6B: 
    case 0x6C: 
    case 0x6D: 
    case 0x6E: 
    case 0x6F: 
    case 0x70: 
    case 0x71: 
    case 0x72: 
    case 0x73: 
    case 0x74: 
    case 0x75: 
    case 0x76: 
    case 0x77: 
    case 0x78: 
    case 0x79: 
    case 0x7A: goto STATE_331;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_352_DROP_OUT_DIRECT");

            goto TERMINAL_39_DIRECT;

STATE_352_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_352_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_352_INPUT;
    }
        goto TERMINAL_39_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_353:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_353");
STATE_353_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_353_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_353_RELOAD;
    case 0x30: 
    case 0x31: 
    case 0x32: 
    case 0x33: 
    case 0x34: 
    case 0x35: 
    case 0x36: 
    case 0x37: 
    case 0x38: 
    case 0x39: 
    case 0x41: 
    case 0x42: 
    case 0x43: 
    case 0x44: 
    case 0x45: 
    case 0x46: 
    case 0x47: 
    case 0x48: 
    case 0x49: 
    case 0x4A: 
    case 0x4B: 
    case 0x4C: 
    case 0x4D: 
    case 0x4E: 
    case 0x4F: 
    case 0x50: 
    case 0x51: 
    case 0x52: 
    case 0x53: 
    case 0x54: 
    case 0x55: 
    case 0x56: 
    case 0x57: 
    case 0x58: 
    case 0x59: 
    case 0x5A: 
    case 0x5F: 
    case 0x61: 
    case 0x62: 
    case 0x63: 
    case 0x64: 
    case 0x65: 
    case 0x66: goto STATE_331;
    case 0x67: goto STATE_354;
    case 0x68: 
    case 0x69: 
    case 0x6A: 
    case 0x6B: 
    case 0x6C: 
    case 0x6D: 
    case 0x6E: 
    case 0x6F: 
    case 0x70: 
    case 0x71: 
    case 0x72: 
    case 0x73: 
    case 0x74: 
    case 0x75: 
    case 0x76: 
    case 0x77: 
    case 0x78: 
    case 0x79: 
    case 0x7A: goto STATE_331;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_353_DROP_OUT_DIRECT");

            goto TERMINAL_39_DIRECT;

STATE_353_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_353_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_353_INPUT;
    }
        goto TERMINAL_39_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_354:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_354");
STATE_354_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_354_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_354_RELOAD;
    case 0x30: 
    case 0x31: 
    case 0x32: 
    case 0x33: 
    case 0x34: 
    case 0x35: 
    case 0x36: 
    case 0x37: 
    case 0x38: 
    case 0x39: 
    case 0x41: 
    case 0x42: 
    case 0x43: 
    case 0x44: 
    case 0x45: 
    case 0x46: 
    case 0x47: 
    case 0x48: 
    case 0x49: 
    case 0x4A: 
    case 0x4B: 
    case 0x4C: 
    case 0x4D: 
    case 0x4E: 
    case 0x4F: 
    case 0x50: 
    case 0x51: 
    case 0x52: 
    case 0x53: 
    case 0x54: 
    case 0x55: 
    case 0x56: 
    case 0x57: 
    case 0x58: 
    case 0x59: 
    case 0x5A: 
    case 0x5F: 
    case 0x61: 
    case 0x62: 
    case 0x63: 
    case 0x64: 
    case 0x65: 
    case 0x66: 
    case 0x67: 
    case 0x68: 
    case 0x69: 
    case 0x6A: 
    case 0x6B: 
    case 0x6C: 
    case 0x6D: goto STATE_331;
    case 0x6E: goto STATE_355;
    case 0x6F: 
    case 0x70: 
    case 0x71: 
    case 0x72: 
    case 0x73: 
    case 0x74: 
    case 0x75: 
    case 0x76: 
    case 0x77: 
    case 0x78: 
    case 0x79: 
    case 0x7A: goto STATE_331;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_354_DROP_OUT_DIRECT");

            goto TERMINAL_39_DIRECT;

STATE_354_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_354_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_354_INPUT;
    }
        goto TERMINAL_39_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_355:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_355");
STATE_355_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_355_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    if( input < 0x5B) {
        if( input < 0x30) {
            if( input == 0x0 ) {
                goto STATE_355_RELOAD;    /* \0 */
            }
        } else {
            if( input < 0x3A) {
                goto STATE_331;    /* ['0', '9'] */
            } else {
                if( input >= 0x41) {
                    goto STATE_331;    /* ['A', 'Z'] */
                }
            }
        }
    } else {
        if( input < 0x60) {
            if( input == 0x5F ) {
                goto STATE_331;    /* '_' */
            }
        } else {
            if( input != 0x60 ) {
                if( input < 0x7B) {
                    goto STATE_331;    /* ['a', 'z'] */
                }
            }
        }
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_355_DROP_OUT_DIRECT");

            goto TERMINAL_21_DIRECT;

STATE_355_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_355_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_355_INPUT;
    }
        goto TERMINAL_21_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_356:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_356");
STATE_356_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_356_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_356_RELOAD;
    case 0x30: 
    case 0x31: 
    case 0x32: 
    case 0x33: 
    case 0x34: 
    case 0x35: 
    case 0x36: 
    case 0x37: 
    case 0x38: 
    case 0x39: 
    case 0x41: 
    case 0x42: 
    case 0x43: 
    case 0x44: 
    case 0x45: 
    case 0x46: 
    case 0x47: 
    case 0x48: 
    case 0x49: 
    case 0x4A: 
    case 0x4B: 
    case 0x4C: 
    case 0x4D: 
    case 0x4E: 
    case 0x4F: 
    case 0x50: 
    case 0x51: 
    case 0x52: 
    case 0x53: 
    case 0x54: 
    case 0x55: 
    case 0x56: 
    case 0x57: 
    case 0x58: 
    case 0x59: 
    case 0x5A: 
    case 0x5F: 
    case 0x61: 
    case 0x62: 
    case 0x63: 
    case 0x64: 
    case 0x65: 
    case 0x66: 
    case 0x67: 
    case 0x68: goto STATE_331;
    case 0x69: goto STATE_357;
    case 0x6A: 
    case 0x6B: 
    case 0x6C: 
    case 0x6D: 
    case 0x6E: 
    case 0x6F: 
    case 0x70: 
    case 0x71: 
    case 0x72: 
    case 0x73: 
    case 0x74: 
    case 0x75: 
    case 0x76: 
    case 0x77: 
    case 0x78: 
    case 0x79: 
    case 0x7A: goto STATE_331;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_356_DROP_OUT_DIRECT");

            goto TERMINAL_13_DIRECT;

STATE_356_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_356_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_356_INPUT;
    }
        goto TERMINAL_13_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_357:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_357");
STATE_357_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_357_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    if( input < 0x5B) {
        if( input < 0x30) {
            if( input == 0x0 ) {
                goto STATE_357_RELOAD;    /* \0 */
            }
        } else {
            if( input < 0x3A) {
                goto STATE_331;    /* ['0', '9'] */
            } else {
                if( input >= 0x41) {
                    goto STATE_331;    /* ['A', 'Z'] */
                }
            }
        }
    } else {
        if( input < 0x60) {
            if( input == 0x5F ) {
                goto STATE_331;    /* '_' */
            }
        } else {
            if( input != 0x60 ) {
                if( input < 0x7B) {
                    goto STATE_331;    /* ['a', 'z'] */
                }
            }
        }
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_357_DROP_OUT_DIRECT");

            goto TERMINAL_15_DIRECT;

STATE_357_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_357_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_357_INPUT;
    }
        goto TERMINAL_15_DIRECT;


    __quex_assert(false); /* No drop-into __TERMINAL_ROUTER */
__TERMINAL_ROUTER: {
        /*  if last_acceptance => goto correspondent acceptance terminal state */
        /*  else               => execute defaul action                        */
        if( last_acceptance == QUEX_GOTO_TERMINAL_LABEL_INIT_VALUE) {
            goto TERMINAL_FAILURE;
        }
        /* When a terminal router is used, the terminal is determined dynamically,
         * thus the last_acceptance_input_position **must** be set. 
         * Exception: Template States, where acceptance states of post conditions
         *            do not set the acceptance position (because its retrieved
         *            anyway from post_context_start_position[i]).               */
        if(last_acceptance_input_position != 0x0) {
QUEX_NAME(Buffer_seek_memory_adr)(&me->buffer, last_acceptance_input_position);

        }
#ifdef  QUEX_OPTION_COMPUTED_GOTOS
        goto *last_acceptance;
#else
        /* Route according variable 'last_acceptance'. */
        switch( last_acceptance ) {
            case 34: goto TERMINAL_34_DIRECT;
            case 4: goto TERMINAL_4_DIRECT;
            case 39: goto TERMINAL_39_DIRECT;
            case 9: goto TERMINAL_9_DIRECT;
            case 11: goto TERMINAL_11_DIRECT;
            case 29: goto TERMINAL_29_DIRECT;
            case 13: goto TERMINAL_13_DIRECT;
            case 15: goto TERMINAL_15_DIRECT;
            case 17: goto TERMINAL_17_DIRECT;
            case 19: goto TERMINAL_19_DIRECT;
            case 21: goto TERMINAL_21_DIRECT;
            case 23: goto TERMINAL_23_DIRECT;
            case 25: goto TERMINAL_25_DIRECT;
            case 27: goto TERMINAL_27_DIRECT;
            case 61: goto TERMINAL_61_DIRECT;

            default: goto TERMINAL_FAILURE;; /* nothing matched */
        }
#endif /* QUEX_OPTION_COMPUTED_GOTOS */
    }

  /* (*) Terminal states _______________________________________________________*/
  /**/
  /* Acceptance terminal states, i.e. the 'winner patterns'. This means*/
  /* that the last input dropped out of a state where the longest matching*/
  /* pattern was according to the terminal state. The terminal states are */
  /* numbered after the pattern id.*/
  /**/

/* Lexeme descriptions: There is a temporary zero stored at the end of each
 * lexeme. A pointer to the zero provides the Null-lexeme.                     */
#if defined(QUEX_OPTION_ASSERTS)
#   define Lexeme       QUEX_NAME(access_Lexeme)((const char*)__FILE__, (size_t)__LINE__, &me->buffer)
#   define LexemeBegin  QUEX_NAME(access_Lexeme)((const char*)__FILE__, (size_t)__LINE__, &me->buffer)
#   define LexemeL      QUEX_NAME(access_LexemeL)((const char*)__FILE__, (size_t)__LINE__, &me->buffer)
#   define LexemeEnd    QUEX_NAME(access_LexemeEnd)((const char*)__FILE__, (size_t)__LINE__, &me->buffer)
#else
#   define Lexeme       (me->buffer._lexeme_start_p)
#   define LexemeBegin  (me->buffer._lexeme_start_p)
#   define LexemeL      ((size_t)(me->buffer._input_p - me->buffer._lexeme_start_p))
#   define LexemeEnd    (me->buffer._input_p)
#endif

#define LexemeNull   (&QUEX_NAME(LexemeNullObject))

            
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_34");

    ++(me->buffer._input_p);
TERMINAL_34_DIRECT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_34_DIRECT");

    {
        {
        #   ifdef __QUEX_OPTION_COUNTER
        __QUEX_IF_COUNT_LINES(self.counter._line_number_at_begin     = self.counter._line_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_begin = self.counter._column_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end += ((size_t)(self.buffer._input_p - self.buffer._lexeme_start_p)));
        __QUEX_ASSERT_COUNTER_CONSISTENCY(&self.counter);
        #   endif
        
        #line 21 "lexer.qx"
        QUEX_NAME_TOKEN(take_text)(self_write_token_p(), &self, self.buffer._lexeme_start_p, self.buffer._input_p);
        self_send(QUEX_TKN_NUMBER);
        QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
        
#line 2507 "lexer.cpp"
        
        }
    }

    goto __REENTRY_PREPARATION;

           
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_4");

    ++(me->buffer._input_p);
TERMINAL_4_DIRECT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_4_DIRECT");

    {
        {
        #   ifdef __QUEX_OPTION_COUNTER
        __QUEX_IF_COUNT_LINES(self.counter._line_number_at_begin     = self.counter._line_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_begin = self.counter._column_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end += ((size_t)(self.buffer._input_p - self.buffer._lexeme_start_p)));
        __QUEX_ASSERT_COUNTER_CONSISTENCY(&self.counter);
        #   endif
        
        }
    }

    goto __REENTRY_PREPARATION;

            
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_39");

    ++(me->buffer._input_p);
TERMINAL_39_DIRECT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_39_DIRECT");

    {
        {
        #   ifdef __QUEX_OPTION_COUNTER
        __QUEX_IF_COUNT_LINES(self.counter._line_number_at_begin     = self.counter._line_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_begin = self.counter._column_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end += ((size_t)(self.buffer._input_p - self.buffer._lexeme_start_p)));
        __QUEX_ASSERT_COUNTER_CONSISTENCY(&self.counter);
        #   endif
        
        #line 22 "lexer.qx"
        QUEX_NAME_TOKEN(take_text)(self_write_token_p(), &self, self.buffer._lexeme_start_p, self.buffer._input_p);
        self_send(QUEX_TKN_IDENTIFIER);
        QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
        
#line 2556 "lexer.cpp"
        
        }
    }

    goto __REENTRY_PREPARATION;

           
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_9");

    ++(me->buffer._input_p);
TERMINAL_9_DIRECT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_9_DIRECT");

    {
        {
        #   ifdef __QUEX_OPTION_COUNTER
        __QUEX_IF_COUNT_LINES(self.counter._line_number_at_begin     = self.counter._line_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_begin = self.counter._column_number_at_end);
        QUEX_NAME(Counter_count)(&self.counter, self.buffer._lexeme_start_p, self.buffer._input_p);
        __QUEX_ASSERT_COUNTER_CONSISTENCY(&self.counter);
        #   endif
        
        #line 10 "lexer.qx"
        self_send(QUEX_TKN_EOL);
        QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
        
#line 2583 "lexer.cpp"
        
        }
    }

    goto __REENTRY_PREPARATION;

TERMINAL_11:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_11");

    ++(me->buffer._input_p);
TERMINAL_11_DIRECT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_11_DIRECT");

    {
        {
        #   ifdef __QUEX_OPTION_COUNTER
        __QUEX_IF_COUNT_LINES(self.counter._line_number_at_begin     = self.counter._line_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_begin = self.counter._column_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end += 1);
        __QUEX_ASSERT_COUNTER_CONSISTENCY(&self.counter);
        #   endif
        
        #line 11 "lexer.qx"
        self_send(QUEX_TKN_COMMA);
        QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
        
#line 2610 "lexer.cpp"
        
        }
    }

    goto __REENTRY_PREPARATION;

            
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_29");

    ++(me->buffer._input_p);
TERMINAL_29_DIRECT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_29_DIRECT");

    {
        {
        #   ifdef __QUEX_OPTION_COUNTER
        __QUEX_IF_COUNT_LINES(self.counter._line_number_at_begin     = self.counter._line_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_begin = self.counter._column_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end += 4);
        __QUEX_ASSERT_COUNTER_CONSISTENCY(&self.counter);
        #   endif
        
        #line 20 "lexer.qx"
        self_send(QUEX_TKN_OP_DIVIDEI);
        QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
        
#line 2637 "lexer.cpp"
        
        }
    }

    goto __REENTRY_PREPARATION;

            
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_13");

    ++(me->buffer._input_p);
TERMINAL_13_DIRECT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_13_DIRECT");

    {
        {
        #   ifdef __QUEX_OPTION_COUNTER
        __QUEX_IF_COUNT_LINES(self.counter._line_number_at_begin     = self.counter._line_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_begin = self.counter._column_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end += 3);
        __QUEX_ASSERT_COUNTER_CONSISTENCY(&self.counter);
        #   endif
        
        #line 12 "lexer.qx"
        self_send(QUEX_TKN_OP_ADD);
        QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
        
#line 2664 "lexer.cpp"
        
        }
    }

    goto __REENTRY_PREPARATION;

            
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_15");

    ++(me->buffer._input_p);
TERMINAL_15_DIRECT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_15_DIRECT");

    {
        {
        #   ifdef __QUEX_OPTION_COUNTER
        __QUEX_IF_COUNT_LINES(self.counter._line_number_at_begin     = self.counter._line_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_begin = self.counter._column_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end += 4);
        __QUEX_ASSERT_COUNTER_CONSISTENCY(&self.counter);
        #   endif
        
        #line 13 "lexer.qx"
        self_send(QUEX_TKN_OP_ADDI);
        QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
        
#line 2691 "lexer.cpp"
        
        }
    }

    goto __REENTRY_PREPARATION;

            
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_17");

    ++(me->buffer._input_p);
TERMINAL_17_DIRECT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_17_DIRECT");

    {
        {
        #   ifdef __QUEX_OPTION_COUNTER
        __QUEX_IF_COUNT_LINES(self.counter._line_number_at_begin     = self.counter._line_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_begin = self.counter._column_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end += 3);
        __QUEX_ASSERT_COUNTER_CONSISTENCY(&self.counter);
        #   endif
        
        #line 14 "lexer.qx"
        self_send(QUEX_TKN_OP_SUB);
        QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
        
#line 2718 "lexer.cpp"
        
        }
    }

    goto __REENTRY_PREPARATION;

            
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_19");

    ++(me->buffer._input_p);
TERMINAL_19_DIRECT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_19_DIRECT");

    {
        {
        #   ifdef __QUEX_OPTION_COUNTER
        __QUEX_IF_COUNT_LINES(self.counter._line_number_at_begin     = self.counter._line_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_begin = self.counter._column_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end += 4);
        __QUEX_ASSERT_COUNTER_CONSISTENCY(&self.counter);
        #   endif
        
        #line 15 "lexer.qx"
        self_send(QUEX_TKN_OP_SUBI);
        QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
        
#line 2745 "lexer.cpp"
        
        }
    }

    goto __REENTRY_PREPARATION;

            
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_21");

    ++(me->buffer._input_p);
TERMINAL_21_DIRECT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_21_DIRECT");

    {
        {
        #   ifdef __QUEX_OPTION_COUNTER
        __QUEX_IF_COUNT_LINES(self.counter._line_number_at_begin     = self.counter._line_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_begin = self.counter._column_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end += 6);
        __QUEX_ASSERT_COUNTER_CONSISTENCY(&self.counter);
        #   endif
        
        #line 16 "lexer.qx"
        self_send(QUEX_TKN_OP_ASSIGN);
        QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
        
#line 2772 "lexer.cpp"
        
        }
    }

    goto __REENTRY_PREPARATION;

            
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_23");

    ++(me->buffer._input_p);
TERMINAL_23_DIRECT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_23_DIRECT");

    {
        {
        #   ifdef __QUEX_OPTION_COUNTER
        __QUEX_IF_COUNT_LINES(self.counter._line_number_at_begin     = self.counter._line_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_begin = self.counter._column_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end += 3);
        __QUEX_ASSERT_COUNTER_CONSISTENCY(&self.counter);
        #   endif
        
        #line 17 "lexer.qx"
        self_send(QUEX_TKN_OP_MULTIPLY);
        QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
        
#line 2799 "lexer.cpp"
        
        }
    }

    goto __REENTRY_PREPARATION;

            
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_25");

    ++(me->buffer._input_p);
TERMINAL_25_DIRECT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_25_DIRECT");

    {
        {
        #   ifdef __QUEX_OPTION_COUNTER
        __QUEX_IF_COUNT_LINES(self.counter._line_number_at_begin     = self.counter._line_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_begin = self.counter._column_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end += 4);
        __QUEX_ASSERT_COUNTER_CONSISTENCY(&self.counter);
        #   endif
        
        #line 18 "lexer.qx"
        self_send(QUEX_TKN_OP_MULTIPLYI);
        QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
        
#line 2826 "lexer.cpp"
        
        }
    }

    goto __REENTRY_PREPARATION;

            
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_27");

    ++(me->buffer._input_p);
TERMINAL_27_DIRECT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_27_DIRECT");

    {
        {
        #   ifdef __QUEX_OPTION_COUNTER
        __QUEX_IF_COUNT_LINES(self.counter._line_number_at_begin     = self.counter._line_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_begin = self.counter._column_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end += 3);
        __QUEX_ASSERT_COUNTER_CONSISTENCY(&self.counter);
        #   endif
        
        #line 19 "lexer.qx"
        self_send(QUEX_TKN_OP_DIVIDE);
        QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
        
#line 2853 "lexer.cpp"
        
        }
    }

    goto __REENTRY_PREPARATION;

TERMINAL_61:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_61");

    ++(me->buffer._input_p);
TERMINAL_61_DIRECT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_61_DIRECT");

    {
        {
        #   ifdef __QUEX_OPTION_COUNTER
        __QUEX_IF_COUNT_LINES(self.counter._line_number_at_begin     = self.counter._line_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_begin = self.counter._column_number_at_end);
        QUEX_NAME(Counter_count)(&self.counter, self.buffer._lexeme_start_p, self.buffer._input_p);
        __QUEX_ASSERT_COUNTER_CONSISTENCY(&self.counter);
        #   endif
        
        #line 23 "lexer.qx"
        QUEX_NAME_TOKEN(take_text)(self_write_token_p(), &self, (LexemeBegin+1), (LexemeEnd-1));
        self_send(QUEX_TKN_STRING);
        QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
        
#line 2881 "lexer.cpp"
        
        }
    }

    goto __REENTRY_PREPARATION;



TERMINAL_END_OF_STREAM:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_END_OF_STREAM");

                {
                    {
        #   ifdef __QUEX_OPTION_COUNTER
        __QUEX_IF_COUNT_LINES(self.counter._line_number_at_begin     = self.counter._line_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_begin = self.counter._column_number_at_end);
        #   endif
        
        #line 7 "lexer.qx"
        self_send(QUEX_TKN_TERMINATION);
        
#line 2903 "lexer.cpp"
        
        }
                }

     /* End of Stream causes a return from the lexical analyzer, so that no
      * tokens can be filled after the termination token.                    */
     RETURN;          

TERMINAL_FAILURE:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_FAILURE");

me->buffer._input_p = me->buffer._lexeme_start_p;
if(QUEX_NAME(Buffer_is_end_of_file)(&me->buffer)) {

    /* Next increment will stop on EOF character. */
}

else {
    /* Step over nomatching character */
    ++(me->buffer._input_p);
}

                {
                    {
        #   ifdef __QUEX_OPTION_COUNTER
        __QUEX_IF_COUNT_LINES(self.counter._line_number_at_begin     = self.counter._line_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_begin = self.counter._column_number_at_end);
        QUEX_NAME(Counter_count)(&self.counter, self.buffer._lexeme_start_p, self.buffer._input_p);
        #   endif
        QUEX_ERROR_EXIT("\n    Match failure in mode 'ONE_AND_ONLY'.\n"
                        "    No 'on_failure' section provided for this mode.\n"
                        "    Proposal: Define 'on_failure' and analyze 'Lexeme'.\n");
        
        }
                }

     goto __REENTRY_PREPARATION;

#undef Lexeme
#undef LexemeBegin
#undef LexemeEnd
#undef LexemeNull
#undef LexemeL

  
__REENTRY_PREPARATION:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: __REENTRY_PREPARATION");

    /* (*) Common point for **restarting** lexical analysis.
     *     at each time when CONTINUE is called at the end of a pattern. */
    
#ifndef   __QUEX_OPTION_PLAIN_ANALYZER_OBJECT
#   ifdef QUEX_OPTION_TOKEN_POLICY_QUEUE
    if( QUEX_NAME(TokenQueue_is_full)(&self._token_queue) ) RETURN;
#   else
    if( self_token_get_id() != __QUEX_SETTING_TOKEN_ID_UNINITIALIZED) RETURN;
#   endif
#endif

    last_acceptance = QUEX_GOTO_TERMINAL_LABEL_INIT_VALUE;


    /* Post context positions do not have to be reset or initialized. If a state
     * is reached which is associated with 'end of post context' it is clear what
     * post context is meant. This results from the ways the state machine is 
     * constructed. A post context positions live time looks like the following:
     *
     * (1)   unitialized (don't care)
     * (1.b) on buffer reload it may, or may not be adapted (don't care)
     * (2)   when a post context begin state is passed, the it is **SET** (now: take care)
     * (2.b) on buffer reload it **is adapted**.
     * (3)   when a terminal state of the post context is reached (which can only be reached
     *       for that particular post context, then the post context position is used
     *       to reset the input position.                                              */

    /*  If a mode change happened, then the function must first return and
     *  indicate that another mode function is to be called. At this point, 
     *  we to force a 'return' on a mode change. 
     *
     *  Pseudo Code: if( previous_mode != current_mode ) {
     *                   return 0;
     *               }
     *
     *  When the analyzer returns, the caller function has to watch if a mode change
     *  occured. If not it can call this function again.                               */
#if    defined(QUEX_OPTION_AUTOMATIC_ANALYSIS_CONTINUATION_ON_MODE_CHANGE)     || defined(QUEX_OPTION_ASSERTS)
    if( me->DEBUG_analyzer_function_at_entry != me->current_analyzer_function ) 
#endif
    { 
#if defined(QUEX_OPTION_AUTOMATIC_ANALYSIS_CONTINUATION_ON_MODE_CHANGE)
    self_token_set_id(__QUEX_SETTING_TOKEN_ID_UNINITIALIZED);
    RETURN;
#elif defined(QUEX_OPTION_ASSERTS)
    QUEX_ERROR_EXIT("Mode change without immediate return from the lexical analyzer.");
#endif
    }

    goto __REENTRY;

    /* Prevent compiler warning 'unused variable': use variables once in a part of the code*/
    /* that is never reached (and deleted by the compiler anyway).*/
    (void)ONE_AND_ONLY;
    (void)QUEX_NAME(LexemeNullObject);
    (void)QUEX_NAME_TOKEN(DumpedTokenIdObject);
    QUEX_ERROR_EXIT("Unreachable code has been reached.\n");
    /* In some scenarios, the __TERMINAL_ROUTER is never required.
     * Still, avoid the warning of 'label never used'.             */
    goto __TERMINAL_ROUTER;
#   undef ONE_AND_ONLY
#undef self
}
#include <quex/code_base/temporary_macros_off>
QUEX_NAMESPACE_MAIN_CLOSE


QUEX_NAMESPACE_TOKEN_OPEN

const char*
QUEX_NAME_TOKEN(map_id_to_name)(const QUEX_TYPE_TOKEN_ID TokenID)
{
   static char  error_string[64];
   static const char  uninitialized_string[] = "<UNINITIALIZED>";
   static const char  termination_string[]   = "<TERMINATION>";
#  if defined(QUEX_OPTION_INDENTATION_TRIGGER)
   static const char  indent_string[]        = "<INDENT>";
   static const char  dedent_string[]        = "<DEDENT>";
   static const char  nodent_string[]        = "<NODENT>";
#  endif
   static const char  token_id_str_COMMA[]         = "COMMA";
   static const char  token_id_str_EOL[]           = "EOL";
   static const char  token_id_str_IDENTIFIER[]    = "IDENTIFIER";
   static const char  token_id_str_NUMBER[]        = "NUMBER";
   static const char  token_id_str_OP_ADD[]        = "OP_ADD";
   static const char  token_id_str_OP_ADDI[]       = "OP_ADDI";
   static const char  token_id_str_OP_ASSIGN[]     = "OP_ASSIGN";
   static const char  token_id_str_OP_DIVIDE[]     = "OP_DIVIDE";
   static const char  token_id_str_OP_DIVIDEI[]    = "OP_DIVIDEI";
   static const char  token_id_str_OP_MULTIPLY[]   = "OP_MULTIPLY";
   static const char  token_id_str_OP_MULTIPLYI[]  = "OP_MULTIPLYI";
   static const char  token_id_str_OP_SUB[]        = "OP_SUB";
   static const char  token_id_str_OP_SUBI[]       = "OP_SUBI";
   static const char  token_id_str_STRING[]        = "STRING";
       

   /* NOTE: This implementation works only for token id types that are 
    *       some type of integer or enum. In case an alien type is to
    *       used, this function needs to be redefined.                  */
   switch( TokenID ) {
   default: {
       __QUEX_STD_sprintf(error_string, "<UNKNOWN TOKEN-ID: %i>", (int)TokenID);
       return error_string;
   }
   case __QUEX_SETTING_TOKEN_ID_TERMINATION:       return termination_string;
   case __QUEX_SETTING_TOKEN_ID_UNINITIALIZED:     return uninitialized_string;
#  if defined(QUEX_OPTION_INDENTATION_TRIGGER)
   case __QUEX_SETTING_TOKEN_ID_INDENT:     return indent_string;
   case __QUEX_SETTING_TOKEN_ID_DEDENT:     return dedent_string;
   case __QUEX_SETTING_TOKEN_ID_NODENT:     return nodent_string;
#  endif
   case QUEX_TKN_COMMA:         return token_id_str_COMMA;
   case QUEX_TKN_EOL:           return token_id_str_EOL;
   case QUEX_TKN_IDENTIFIER:    return token_id_str_IDENTIFIER;
   case QUEX_TKN_NUMBER:        return token_id_str_NUMBER;
   case QUEX_TKN_OP_ADD:        return token_id_str_OP_ADD;
   case QUEX_TKN_OP_ADDI:       return token_id_str_OP_ADDI;
   case QUEX_TKN_OP_ASSIGN:     return token_id_str_OP_ASSIGN;
   case QUEX_TKN_OP_DIVIDE:     return token_id_str_OP_DIVIDE;
   case QUEX_TKN_OP_DIVIDEI:    return token_id_str_OP_DIVIDEI;
   case QUEX_TKN_OP_MULTIPLY:   return token_id_str_OP_MULTIPLY;
   case QUEX_TKN_OP_MULTIPLYI:  return token_id_str_OP_MULTIPLYI;
   case QUEX_TKN_OP_SUB:        return token_id_str_OP_SUB;
   case QUEX_TKN_OP_SUBI:       return token_id_str_OP_SUBI;
   case QUEX_TKN_STRING:        return token_id_str_STRING;

   }
}

QUEX_NAMESPACE_TOKEN_CLOSE

