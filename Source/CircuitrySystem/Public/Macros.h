
#pragma once

#include "Engine/GameEngine.h"
/*----------------------------------------------------Section 1--------------------------------------------------------*/

//Prints Variables Data using key method
#define PRINT(Key, Timer, Color, Text) if(GEngine){GEngine->AddOnScreenDebugMessage(Key, Timer, Color, TEXT(Text));}
#define PRINTF(Key, Timer, Color, Format, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(Key, Timer, Color, FString::Printf(TEXT(Format), ##__VA_ARGS__));}
//-------------//
//we can use -1, 1 and 2 for the keys, check examples below. 
//1 to replace the new data, avoid filling the screen.
//-1 to not replace, fil the screen in the up direction.
//2 to replace the new data, avoid filling the screen. (still need to practice)
//-------------//
// %f = float value
// %d = int value
// %s = string value
//float pi = 3.14f;
//int32 a = 5;
//FString s(TEXT("ANONYMOUS"));
//ex: PRINTF(1, "Calling printf with the value: %f", pi); //printing a value from a single variable.
//ex: PRINTF(1, "Calling printf with the values: %f, %d, %s", pi, a, *s ); //printing values from multiple variables.
//ex: PRINTF(-1, "Calling printf with the value: %f", pi); //printing a value from a single variable.
//ex: PRINTF(-1, "Calling printf with the values: %f, %d, %s", pi, a, *s ); //printing values from multiple variables.
//ex: PRINTF(2, "Calling printf with the value: %f", pi); //printing a value from a single variable.
//ex: PRINTF(2, "Calling printf with the values: %f, %d, %s", pi, a, *s ); //printing values from multiple variables.
/*----------------------------------------------------Section 3--------------------------------------------------------*/

