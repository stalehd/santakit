#pragma once

#define OFF 1
#define ON_STEADY 2
#define ON_WAVES 3
#define ON_SEQUENTIAL 4
#define ON_SLOGLO 5
#define ON_CHASING 6
#define ON_SLOFADE 7
#define ON_EPILEPTIC 8

void setTreeState(int newState);
bool isState(int checkState);
int getTreeState();
