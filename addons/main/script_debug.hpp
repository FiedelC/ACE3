/**
STACK TRACING
**/
//#define ENABLE_CALLSTACK

#ifdef ENABLE_CALLSTACK

#define CALLSTACK(function) {private ['_ret']; if(ACE_IS_ERRORED) then { ['AUTO','AUTO'] call ACE_DUMPSTACK_FNC; ACE_IS_ERRORED = false; }; ACE_IS_ERRORED = true; ACE_STACK_TRACE set [ACE_STACK_DEPTH, [diag_tickTime, __FILE__, __LINE__, ACE_CURRENT_FUNCTION, 'ANON', _this]]; ACE_STACK_DEPTH = ACE_STACK_DEPTH + 1; ACE_CURRENT_FUNCTION = 'ANON'; _ret = _this call ##function; ACE_STACK_DEPTH = ACE_STACK_DEPTH - 1; ACE_IS_ERRORED = false; _ret;}
#define CALLSTACK_NAMED(function, functionName) {private ['_ret']; if(ACE_IS_ERRORED) then { ['AUTO','AUTO'] call ACE_DUMPSTACK_FNC; ACE_IS_ERRORED = false; }; ACE_IS_ERRORED = true; ACE_STACK_TRACE set [ACE_STACK_DEPTH, [diag_tickTime, __FILE__, __LINE__, ACE_CURRENT_FUNCTION, functionName, _this]]; ACE_STACK_DEPTH = ACE_STACK_DEPTH + 1; ACE_CURRENT_FUNCTION = functionName; _ret = _this call ##function; ACE_STACK_DEPTH = ACE_STACK_DEPTH - 1; ACE_IS_ERRORED = false; _ret;}
#define DUMPSTACK ([__FILE__, __LINE__] call ACE_DUMPSTACK_FNC)

#define FUNC(var1) {private ['_ret']; if(ACE_IS_ERRORED) then { ['AUTO','AUTO'] call ACE_DUMPSTACK_FNC; ACE_IS_ERRORED = false; }; ACE_IS_ERRORED = true; ACE_STACK_TRACE set [ACE_STACK_DEPTH, [diag_tickTime, __FILE__, __LINE__, ACE_CURRENT_FUNCTION, 'TRIPLES(ADDON,fnc,var1)', _this]]; ACE_STACK_DEPTH = ACE_STACK_DEPTH + 1; ACE_CURRENT_FUNCTION = 'TRIPLES(ADDON,fnc,var1)'; _ret = _this call TRIPLES(ADDON,fnc,var1); ACE_STACK_DEPTH = ACE_STACK_DEPTH - 1; ACE_IS_ERRORED = false; _ret;}
#define EFUNC(var1,var2) {private ['_ret']; if(ACE_IS_ERRORED) then { ['AUTO','AUTO'] call ACE_DUMPSTACK_FNC; ACE_IS_ERRORED = false; }; ACE_IS_ERRORED = true; ACE_STACK_TRACE set [ACE_STACK_DEPTH, [diag_tickTime, __FILE__, __LINE__, ACE_CURRENT_FUNCTION, 'TRIPLES(DOUBLES(PREFIX,var1),fnc,var2)', _this]]; ACE_STACK_DEPTH = ACE_STACK_DEPTH + 1; ACE_CURRENT_FUNCTION = 'TRIPLES(DOUBLES(PREFIX,var1),fnc,var2)'; _ret = _this call TRIPLES(DOUBLES(PREFIX,var1),fnc,var2); ACE_STACK_DEPTH = ACE_STACK_DEPTH - 1; ACE_IS_ERRORED = false; _ret;}

#else
#define CALLSTACK(function) function
#define CALLSTACK_NAMED(function, functionName) function
#define DUMPSTACK

#define FUNC(var1) TRIPLES(ADDON,fnc,var1)
#define EFUNC(var1,var2) TRIPLES(DOUBLES(PREFIX,var1),fnc,var2)

#endif


/**
PERFORMANCE COUNTERS SECTION
**/
//#define ENABLE_PERFORMANCE_COUNTERS

#ifdef ENABLE_PERFORMANCE_COUNTERS
	#define ADDPFH(function, timing, args) call { _ret = [function, timing, args, #function] call EFUNC(sys_sync,perFrame_add); if(isNil "ACE_PFH" ) then { ACE_PFH=[]; }; ACE_PFH pushBack [[_ret, __FILE__, __LINE__], [function, timing, args]];  _ret }
	
	#define CREATE_COUNTER(x) if(isNil "ACE_COUNTERS" ) then { ACE_COUNTERS=[]; }; GVAR(DOUBLES(x,counter))=[]; GVAR(DOUBLES(x,counter)) set[0, QUOTE(GVAR(DOUBLES(x,counter)))];  GVAR(DOUBLES(x,counter)) set[1, diag_tickTime]; ACE_COUNTERS pushBack GVAR(DOUBLES(x,counter));
	#define BEGIN_COUNTER(x) if(isNil QUOTE(GVAR(DOUBLES(x,counter)))) then { CREATE_COUNTER(x) }; GVAR(DOUBLES(x,counter)) set[2, diag_tickTime];
	#define END_COUNTER(x) GVAR(DOUBLES(x,counter)) pushBack [(GVAR(DOUBLES(x,counter)) select 2), diag_tickTime];

	#define DUMP_COUNTERS ([__FILE__, __LINE__] call ACE_DUMPCOUNTERS_FNC)
#else
	#define ADDPFH(function, timing, args)	[function, timing, args, #function] call EFUNC(sys_sync,perFrame_add)
	
	#define CREATE_COUNTER(x) /* disabled */
	#define BEGIN_COUNTER(x) /* disabled */
	#define END_COUNTER(x) /* disabled */
	#define DUMP_COUNTERS  /* disabled */
#endif