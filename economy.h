#ifndef ECONOMY_H_INCLUDED
#define ECONOMY_H_INCLUDED

#include "economyindex.h"
#include "inventoryindex.h"
#include "industryindex.h"

/// Components of value:
std::map<int,float>inputValue;
std::map<int,float>labourValue;

std::map<int,float>value;

void EvaluateInputValue();
void EvaluateLabourValue();
void EvaluateValue();



#endif // ECONOMY_H_INCLUDED
