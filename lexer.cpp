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
     *       ( 15) ONE_AND_ONLY: "sub"
     *       ( 17) ONE_AND_ONLY: "mov"
     *       ( 19) ONE_AND_ONLY: "mul"
     *       ( 21) ONE_AND_ONLY: "div"
     *       ( 26) ONE_AND_ONLY: [0-9]+
     *       ( 31) ONE_AND_ONLY: [_a-zA-Z]+
     *       ( 53) ONE_AND_ONLY: \"([^\"\\\\]|\\\\.)*\"
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
    /* init-state = 246L
     * 00246() <~ (4, 12), (9, 28), (11, 33), (13, 39), (15, 47), (17, 55), (19, 63), (21, 71), (26, 87), (31, 102), (53, 164)
     *       == '\t', ' ' ==> 00252
     *       == '\n' ==> 00247
     *       == '"' ==> 00255
     *       == ',' ==> 00248
     *       == ['0', '9'] ==> 00249
     *       == ['A', 'Z'], '_', ['b', 'c'], ['e', 'l'], ['n', 'r'], ['t', 'z'] ==> 00253
     *       == 'a' ==> 00250
     *       == 'd' ==> 00256
     *       == 'm' ==> 00251
     *       == 's' ==> 00254
     *       <no epsilon>
     * 00252(A, S) <~ (4, 13, A, S)
     *       == '\t', ' ' ==> 00252
     *       <no epsilon>
     * 00247(A, S) <~ (9, 29, A, S)
     *       == '\n' ==> 00247
     *       <no epsilon>
     * 00255() <~ (53, 165)
     *       == [\2, '!'], ['#', '['], [']', 'ÿ'] ==> 00255
     *       == '"' ==> 00260
     *       == '\' ==> 00259
     *       <no epsilon>
     * 00260(A, S) <~ (53, 167, A, S)
     *       <no epsilon>
     * 00259() <~ (53, 168)
     *       == '\' ==> 00261
     *       <no epsilon>
     * 00261() <~ (53, 169)
     *       == [\2, '\t'], ['\v', 'ÿ'] ==> 00255
     *       <no epsilon>
     * 00248(A, S) <~ (11, 34, A, S)
     *       <no epsilon>
     * 00249(A, S) <~ (26, 88, A, S)
     *       == ['0', '9'] ==> 00249
     *       <no epsilon>
     * 00253(A, S) <~ (31, 104, A, S)
     *       == ['A', 'Z'], '_', ['a', 'z'] ==> 00253
     *       <no epsilon>
     * 00250(A, S) <~ (31, 104, A, S), (13, 40)
     *       == ['A', 'Z'], '_', ['a', 'c'], ['e', 'z'] ==> 00253
     *       == 'd' ==> 00268
     *       <no epsilon>
     * 00268(A, S) <~ (31, 104, A, S), (13, 41)
     *       == ['A', 'Z'], '_', ['a', 'c'], ['e', 'z'] ==> 00253
     *       == 'd' ==> 00269
     *       <no epsilon>
     * 00269(A, S) <~ (13, 42, A, S)
     *       == ['A', 'Z'], '_', ['a', 'z'] ==> 00253
     *       <no epsilon>
     * 00256(A, S) <~ (31, 104, A, S), (21, 72)
     *       == ['A', 'Z'], '_', ['a', 'h'], ['j', 'z'] ==> 00253
     *       == 'i' ==> 00257
     *       <no epsilon>
     * 00257(A, S) <~ (31, 104, A, S), (21, 73)
     *       == ['A', 'Z'], '_', ['a', 'u'], ['w', 'z'] ==> 00253
     *       == 'v' ==> 00258
     *       <no epsilon>
     * 00258(A, S) <~ (21, 74, A, S)
     *       == ['A', 'Z'], '_', ['a', 'z'] ==> 00253
     *       <no epsilon>
     * 00251(A, S) <~ (31, 104, A, S), (17, 56), (19, 64)
     *       == ['A', 'Z'], '_', ['a', 'n'], ['p', 't'], ['v', 'z'] ==> 00253
     *       == 'o' ==> 00265
     *       == 'u' ==> 00264
     *       <no epsilon>
     * 00265(A, S) <~ (31, 104, A, S), (17, 57)
     *       == ['A', 'Z'], '_', ['a', 'u'], ['w', 'z'] ==> 00253
     *       == 'v' ==> 00266
     *       <no epsilon>
     * 00266(A, S) <~ (17, 58, A, S)
     *       == ['A', 'Z'], '_', ['a', 'z'] ==> 00253
     *       <no epsilon>
     * 00264(A, S) <~ (31, 104, A, S), (19, 65)
     *       == ['A', 'Z'], '_', ['a', 'k'], ['m', 'z'] ==> 00253
     *       == 'l' ==> 00267
     *       <no epsilon>
     * 00267(A, S) <~ (19, 66, A, S)
     *       == ['A', 'Z'], '_', ['a', 'z'] ==> 00253
     *       <no epsilon>
     * 00254(A, S) <~ (31, 104, A, S), (15, 48)
     *       == ['A', 'Z'], '_', ['a', 't'], ['v', 'z'] ==> 00253
     *       == 'u' ==> 00262
     *       <no epsilon>
     * 00262(A, S) <~ (31, 104, A, S), (15, 49)
     *       == ['A', 'Z'], '_', 'a', ['c', 'z'] ==> 00253
     *       == 'b' ==> 00263
     *       <no epsilon>
     * 00263(A, S) <~ (15, 50, A, S)
     *       == ['A', 'Z'], '_', ['a', 'z'] ==> 00253
     *       <no epsilon>
     * 
     */
STATE_246:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_246");
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_246_RELOAD;
    case 0x9: goto STATE_252;
    case 0xA: goto STATE_247;
    case 0x20: goto STATE_252;
    case 0x22: goto STATE_255;
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
    case 0x39: goto STATE_249;
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
    case 0x5F: goto STATE_253;
    case 0x61: goto STATE_250;
    case 0x62: 
    case 0x63: goto STATE_253;
    case 0x64: goto STATE_256;
    case 0x65: 
    case 0x66: 
    case 0x67: 
    case 0x68: 
    case 0x69: 
    case 0x6A: 
    case 0x6B: 
    case 0x6C: goto STATE_253;
    case 0x6D: goto STATE_251;
    case 0x6E: 
    case 0x6F: 
    case 0x70: 
    case 0x71: 
    case 0x72: goto STATE_253;
    case 0x73: goto STATE_254;
    case 0x74: 
    case 0x75: 
    case 0x76: 
    case 0x77: 
    case 0x78: 
    case 0x79: 
    case 0x7A: goto STATE_253;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_246_DROP_OUT_DIRECT");

    goto TERMINAL_FAILURE;

STATE_246_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_246_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( (me->buffer._memory._end_of_file_p != 0x0) ) {
        goto TERMINAL_END_OF_STREAM;
    }
    QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
    goto STATE_246_INPUT;
STATE_246_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_246_INPUT");
    ++(me->buffer._input_p);
    goto STATE_246;

    __quex_assert(false); /* No drop-through between states */
STATE_253:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_253");
STATE_253_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_253_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    if( input < 0x5F) {
        if( input < 0x41) {
            if( input == 0x0 ) {
                goto STATE_253_RELOAD;    /* \0 */
            }
        } else {
            if( input < 0x5B) {
                goto STATE_253;    /* ['A', 'Z'] */
            }
        }
    } else {
        if( input < 0x61) {
            if( input == 0x5F ) {
                goto STATE_253;    /* '_' */
            }
        } else {
            if( input < 0x7B) {
                goto STATE_253;    /* ['a', 'z'] */
            }
        }
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_253_DROP_OUT_DIRECT");

            goto TERMINAL_31_DIRECT;

STATE_253_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_253_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_253_INPUT;
    }
        goto TERMINAL_31_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_255:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_255");
STATE_255_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_255_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    if( input < 0x23) {
        if( input < 0x2) {
            if( input == 0x0 ) {
                goto STATE_255_RELOAD;    /* \0 */
            }
        } else {
            if( input != 0x22 ) {
                goto STATE_255;    /* [\2, '!'] */
            } else {
                goto TERMINAL_53;    /* '"' */
            }
        }
    } else {
        if( input < 0x5D) {
            if( input != 0x5C ) {
                goto STATE_255;    /* ['#', '['] */
            } else {
                goto STATE_259;    /* '\' */
            }
        } else {
            if( input < 0x100) {
                goto STATE_255;    /* [']', 'ÿ'] */
            }
        }
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_255_DROP_OUT_DIRECT");

        QUEX_GOTO_last_acceptance();


STATE_255_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_255_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_255_INPUT;
    }
    QUEX_GOTO_last_acceptance();



    __quex_assert(false); /* No drop-through between states */
STATE_247:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_247");
STATE_247_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_247_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_247_RELOAD;
    case 0xA: goto STATE_247;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_247_DROP_OUT_DIRECT");

            goto TERMINAL_9_DIRECT;

STATE_247_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_247_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_247_INPUT;
    }
        goto TERMINAL_9_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_249:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_249");
STATE_249_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_249_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_249_RELOAD;
    case 0x30: 
    case 0x31: 
    case 0x32: 
    case 0x33: 
    case 0x34: 
    case 0x35: 
    case 0x36: 
    case 0x37: 
    case 0x38: 
    case 0x39: goto STATE_249;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_249_DROP_OUT_DIRECT");

            goto TERMINAL_26_DIRECT;

STATE_249_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_249_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_249_INPUT;
    }
        goto TERMINAL_26_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_252:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_252");
STATE_252_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_252_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_252_RELOAD;
    case 0x9: 
    case 0x20: goto STATE_252;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_252_DROP_OUT_DIRECT");

            goto TERMINAL_4_DIRECT;

STATE_252_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_252_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_252_INPUT;
    }
        goto TERMINAL_4_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_256:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_256");
STATE_256_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_256_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_256_RELOAD;
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
    case 0x68: goto STATE_253;
    case 0x69: goto STATE_257;
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
    case 0x7A: goto STATE_253;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_256_DROP_OUT_DIRECT");

            goto TERMINAL_31_DIRECT;

STATE_256_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_256_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_256_INPUT;
    }
        goto TERMINAL_31_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_257:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_257");
STATE_257_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_257_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_257_RELOAD;
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
    case 0x75: goto STATE_253;
    case 0x76: goto STATE_258;
    case 0x77: 
    case 0x78: 
    case 0x79: 
    case 0x7A: goto STATE_253;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_257_DROP_OUT_DIRECT");

            goto TERMINAL_31_DIRECT;

STATE_257_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_257_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_257_INPUT;
    }
        goto TERMINAL_31_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_258:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_258");
STATE_258_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_258_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    if( input < 0x5F) {
        if( input < 0x41) {
            if( input == 0x0 ) {
                goto STATE_258_RELOAD;    /* \0 */
            }
        } else {
            if( input < 0x5B) {
                goto STATE_253;    /* ['A', 'Z'] */
            }
        }
    } else {
        if( input < 0x61) {
            if( input == 0x5F ) {
                goto STATE_253;    /* '_' */
            }
        } else {
            if( input < 0x7B) {
                goto STATE_253;    /* ['a', 'z'] */
            }
        }
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_258_DROP_OUT_DIRECT");

            goto TERMINAL_21_DIRECT;

STATE_258_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_258_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_258_INPUT;
    }
        goto TERMINAL_21_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_259:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_259");
STATE_259_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_259_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_259_RELOAD;
    case 0x5C: goto STATE_261;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_259_DROP_OUT_DIRECT");

        QUEX_GOTO_last_acceptance();


STATE_259_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_259_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_259_INPUT;
    }
    QUEX_GOTO_last_acceptance();



    __quex_assert(false); /* No drop-through between states */
STATE_261:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_261");
STATE_261_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_261_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    if( input < 0xA) {
        switch( input ) {
        case 0x0: goto STATE_261_RELOAD;
        case 0x2: 
        case 0x3: 
        case 0x4: 
        case 0x5: 
        case 0x6: 
        case 0x7: 
        case 0x8: 
        case 0x9: goto STATE_255;
        }
    } else {
        if( input != 0xA ) {
            if( input < 0x100) {
                goto STATE_255;    /* ['\v', 'ÿ'] */
            }
        }
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_261_DROP_OUT_DIRECT");

        QUEX_GOTO_last_acceptance();


STATE_261_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_261_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_261_INPUT;
    }
    QUEX_GOTO_last_acceptance();



    __quex_assert(false); /* No drop-through between states */
STATE_262:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_262");
STATE_262_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_262_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_262_RELOAD;
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
    case 0x61: goto STATE_253;
    case 0x62: goto STATE_263;
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
    case 0x7A: goto STATE_253;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_262_DROP_OUT_DIRECT");

            goto TERMINAL_31_DIRECT;

STATE_262_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_262_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_262_INPUT;
    }
        goto TERMINAL_31_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_263:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_263");
STATE_263_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_263_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    if( input < 0x5F) {
        if( input < 0x41) {
            if( input == 0x0 ) {
                goto STATE_263_RELOAD;    /* \0 */
            }
        } else {
            if( input < 0x5B) {
                goto STATE_253;    /* ['A', 'Z'] */
            }
        }
    } else {
        if( input < 0x61) {
            if( input == 0x5F ) {
                goto STATE_253;    /* '_' */
            }
        } else {
            if( input < 0x7B) {
                goto STATE_253;    /* ['a', 'z'] */
            }
        }
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_263_DROP_OUT_DIRECT");

            goto TERMINAL_15_DIRECT;

STATE_263_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_263_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_263_INPUT;
    }
        goto TERMINAL_15_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_264:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_264");
STATE_264_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_264_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_264_RELOAD;
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
    case 0x6B: goto STATE_253;
    case 0x6C: goto STATE_267;
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
    case 0x7A: goto STATE_253;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_264_DROP_OUT_DIRECT");

            goto TERMINAL_31_DIRECT;

STATE_264_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_264_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_264_INPUT;
    }
        goto TERMINAL_31_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_265:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_265");
STATE_265_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_265_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_265_RELOAD;
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
    case 0x75: goto STATE_253;
    case 0x76: goto STATE_266;
    case 0x77: 
    case 0x78: 
    case 0x79: 
    case 0x7A: goto STATE_253;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_265_DROP_OUT_DIRECT");

            goto TERMINAL_31_DIRECT;

STATE_265_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_265_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_265_INPUT;
    }
        goto TERMINAL_31_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_266:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_266");
STATE_266_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_266_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    if( input < 0x5F) {
        if( input < 0x41) {
            if( input == 0x0 ) {
                goto STATE_266_RELOAD;    /* \0 */
            }
        } else {
            if( input < 0x5B) {
                goto STATE_253;    /* ['A', 'Z'] */
            }
        }
    } else {
        if( input < 0x61) {
            if( input == 0x5F ) {
                goto STATE_253;    /* '_' */
            }
        } else {
            if( input < 0x7B) {
                goto STATE_253;    /* ['a', 'z'] */
            }
        }
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_266_DROP_OUT_DIRECT");

            goto TERMINAL_17_DIRECT;

STATE_266_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_266_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_266_INPUT;
    }
        goto TERMINAL_17_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_267:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_267");
STATE_267_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_267_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    if( input < 0x5F) {
        if( input < 0x41) {
            if( input == 0x0 ) {
                goto STATE_267_RELOAD;    /* \0 */
            }
        } else {
            if( input < 0x5B) {
                goto STATE_253;    /* ['A', 'Z'] */
            }
        }
    } else {
        if( input < 0x61) {
            if( input == 0x5F ) {
                goto STATE_253;    /* '_' */
            }
        } else {
            if( input < 0x7B) {
                goto STATE_253;    /* ['a', 'z'] */
            }
        }
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_267_DROP_OUT_DIRECT");

            goto TERMINAL_19_DIRECT;

STATE_267_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_267_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_267_INPUT;
    }
        goto TERMINAL_19_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_268:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_268");
STATE_268_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_268_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_268_RELOAD;
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
    case 0x63: goto STATE_253;
    case 0x64: goto STATE_269;
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
    case 0x7A: goto STATE_253;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_268_DROP_OUT_DIRECT");

            goto TERMINAL_31_DIRECT;

STATE_268_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_268_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_268_INPUT;
    }
        goto TERMINAL_31_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_269:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_269");
STATE_269_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_269_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    if( input < 0x5F) {
        if( input < 0x41) {
            if( input == 0x0 ) {
                goto STATE_269_RELOAD;    /* \0 */
            }
        } else {
            if( input < 0x5B) {
                goto STATE_253;    /* ['A', 'Z'] */
            }
        }
    } else {
        if( input < 0x61) {
            if( input == 0x5F ) {
                goto STATE_253;    /* '_' */
            }
        } else {
            if( input < 0x7B) {
                goto STATE_253;    /* ['a', 'z'] */
            }
        }
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_269_DROP_OUT_DIRECT");

            goto TERMINAL_13_DIRECT;

STATE_269_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_269_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_269_INPUT;
    }
        goto TERMINAL_13_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_250:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_250");
STATE_250_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_250_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_250_RELOAD;
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
    case 0x63: goto STATE_253;
    case 0x64: goto STATE_268;
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
    case 0x7A: goto STATE_253;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_250_DROP_OUT_DIRECT");

            goto TERMINAL_31_DIRECT;

STATE_250_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_250_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_250_INPUT;
    }
        goto TERMINAL_31_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_251:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_251");
STATE_251_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_251_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_251_RELOAD;
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
    case 0x6E: goto STATE_253;
    case 0x6F: goto STATE_265;
    case 0x70: 
    case 0x71: 
    case 0x72: 
    case 0x73: 
    case 0x74: goto STATE_253;
    case 0x75: goto STATE_264;
    case 0x76: 
    case 0x77: 
    case 0x78: 
    case 0x79: 
    case 0x7A: goto STATE_253;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_251_DROP_OUT_DIRECT");

            goto TERMINAL_31_DIRECT;

STATE_251_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_251_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_251_INPUT;
    }
        goto TERMINAL_31_DIRECT;


    __quex_assert(false); /* No drop-through between states */
STATE_254:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_254");
STATE_254_INPUT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_254_INPUT");

    ++(me->buffer._input_p);
    input = *(me->buffer._input_p); QUEX_DEBUG_PRINT_INPUT(&me->buffer, input);
    switch( input ) {
    case 0x0: goto STATE_254_RELOAD;
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
    case 0x74: goto STATE_253;
    case 0x75: goto STATE_262;
    case 0x76: 
    case 0x77: 
    case 0x78: 
    case 0x79: 
    case 0x7A: goto STATE_253;
    }

                          
        QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_254_DROP_OUT_DIRECT");

            goto TERMINAL_31_DIRECT;

STATE_254_RELOAD:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: STATE_254_RELOAD");

    __quex_assert(input == QUEX_SETTING_BUFFER_LIMIT_CODE);
    if( ! ((me->buffer._memory._end_of_file_p != 0x0)) ) {
        QUEX_NAME(buffer_reload_forward_LA_PC)(&me->buffer, &last_acceptance_input_position,
                                       post_context_start_position, PostContextStartPositionN);
        goto STATE_254_INPUT;
    }
        goto TERMINAL_31_DIRECT;


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
            case 4: goto TERMINAL_4_DIRECT;
            case 9: goto TERMINAL_9_DIRECT;
            case 11: goto TERMINAL_11_DIRECT;
            case 13: goto TERMINAL_13_DIRECT;
            case 15: goto TERMINAL_15_DIRECT;
            case 17: goto TERMINAL_17_DIRECT;
            case 19: goto TERMINAL_19_DIRECT;
            case 53: goto TERMINAL_53_DIRECT;
            case 26: goto TERMINAL_26_DIRECT;
            case 21: goto TERMINAL_21_DIRECT;
            case 31: goto TERMINAL_31_DIRECT;

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
        
#line 1706 "lexer.cpp"
        
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
        
#line 1733 "lexer.cpp"
        
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
        
#line 1760 "lexer.cpp"
        
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
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end += 3);
        __QUEX_ASSERT_COUNTER_CONSISTENCY(&self.counter);
        #   endif
        
        #line 13 "lexer.qx"
        self_send(QUEX_TKN_OP_SUB);
        QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
        
#line 1787 "lexer.cpp"
        
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
        self_send(QUEX_TKN_OP_MOVE);
        QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
        
#line 1814 "lexer.cpp"
        
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
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end += 3);
        __QUEX_ASSERT_COUNTER_CONSISTENCY(&self.counter);
        #   endif
        
        #line 15 "lexer.qx"
        self_send(QUEX_TKN_OP_MULTIPLY);
        QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
        
#line 1841 "lexer.cpp"
        
        }
    }

    goto __REENTRY_PREPARATION;

TERMINAL_53:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_53");

    ++(me->buffer._input_p);
TERMINAL_53_DIRECT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_53_DIRECT");

    {
        {
        #   ifdef __QUEX_OPTION_COUNTER
        __QUEX_IF_COUNT_LINES(self.counter._line_number_at_begin     = self.counter._line_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_begin = self.counter._column_number_at_end);
        QUEX_NAME(Counter_count)(&self.counter, self.buffer._lexeme_start_p, self.buffer._input_p);
        __QUEX_ASSERT_COUNTER_CONSISTENCY(&self.counter);
        #   endif
        
        #line 19 "lexer.qx"
        QUEX_NAME_TOKEN(take_text)(self_write_token_p(), &self, (LexemeBegin+1), (LexemeEnd-1));
        self_send(QUEX_TKN_STRING);
        QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
        
#line 1869 "lexer.cpp"
        
        }
    }

    goto __REENTRY_PREPARATION;

            
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_26");

    ++(me->buffer._input_p);
TERMINAL_26_DIRECT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_26_DIRECT");

    {
        {
        #   ifdef __QUEX_OPTION_COUNTER
        __QUEX_IF_COUNT_LINES(self.counter._line_number_at_begin     = self.counter._line_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_begin = self.counter._column_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end += ((size_t)(self.buffer._input_p - self.buffer._lexeme_start_p)));
        __QUEX_ASSERT_COUNTER_CONSISTENCY(&self.counter);
        #   endif
        
        #line 17 "lexer.qx"
        QUEX_NAME_TOKEN(take_text)(self_write_token_p(), &self, self.buffer._lexeme_start_p, self.buffer._input_p);
        self_send(QUEX_TKN_NUMBER);
        QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
        
#line 1897 "lexer.cpp"
        
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
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end += 3);
        __QUEX_ASSERT_COUNTER_CONSISTENCY(&self.counter);
        #   endif
        
        #line 16 "lexer.qx"
        self_send(QUEX_TKN_OP_DIVIDE);
        QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
        
#line 1924 "lexer.cpp"
        
        }
    }

    goto __REENTRY_PREPARATION;

            
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_31");

    ++(me->buffer._input_p);
TERMINAL_31_DIRECT:
    QUEX_DEBUG_PRINT(&me->buffer, "LABEL: TERMINAL_31_DIRECT");

    {
        {
        #   ifdef __QUEX_OPTION_COUNTER
        __QUEX_IF_COUNT_LINES(self.counter._line_number_at_begin     = self.counter._line_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_begin = self.counter._column_number_at_end);
        __QUEX_IF_COUNT_COLUMNS(self.counter._column_number_at_end += ((size_t)(self.buffer._input_p - self.buffer._lexeme_start_p)));
        __QUEX_ASSERT_COUNTER_CONSISTENCY(&self.counter);
        #   endif
        
        #line 18 "lexer.qx"
        QUEX_NAME_TOKEN(take_text)(self_write_token_p(), &self, self.buffer._lexeme_start_p, self.buffer._input_p);
        self_send(QUEX_TKN_IDENTIFIER);
        QUEX_SETTING_AFTER_SEND_CONTINUE_OR_RETURN();
        
#line 1952 "lexer.cpp"
        
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
        
#line 1974 "lexer.cpp"
        
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
   static const char  token_id_str_OP_DIVIDE[]     = "OP_DIVIDE";
   static const char  token_id_str_OP_MOVE[]       = "OP_MOVE";
   static const char  token_id_str_OP_MULTIPLY[]   = "OP_MULTIPLY";
   static const char  token_id_str_OP_SUB[]        = "OP_SUB";
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
   case QUEX_TKN_OP_DIVIDE:     return token_id_str_OP_DIVIDE;
   case QUEX_TKN_OP_MOVE:       return token_id_str_OP_MOVE;
   case QUEX_TKN_OP_MULTIPLY:   return token_id_str_OP_MULTIPLY;
   case QUEX_TKN_OP_SUB:        return token_id_str_OP_SUB;
   case QUEX_TKN_STRING:        return token_id_str_STRING;

   }
}

QUEX_NAMESPACE_TOKEN_CLOSE

