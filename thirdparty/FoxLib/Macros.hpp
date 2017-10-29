/*Macros for common things needed in C++*/
#pragma once
#define fox_min(a, b) (a) < (b) ? (a) : (b) 
#define fox_max(a, b) (a) > (b) ? (a) : (b)
//For unimplemented code
#define fox_unimplemented(returnVal) { assert(false && "unimplemented"); return returnVal; }
//The most common for loop written in C++
#define fox_for(iterName, iterCount) for (fuint iterName = 0; iterName < iterCount; ++iterName)
//A cast that only changes percieved type
#define fox_interpCast(toType, obj) (*reinterpret_cast<toType*>(&(obj)))
//Gets the length of a C array (not a foxlib array)
#define fox_arrayLen(a) (sizeof(a) / sizeof((a)[0]))
