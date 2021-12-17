// Tree state representation. The state of the tree is determined by
// the remote control commands that are set. If the state of tree is out of
// sync, just turn it off, then on again (this always works)
#include <Arduino.h>
#include "tree.h"

static int state = OFF;

void setTreeState(int newState) {
    state = newState;
}

bool isState(int checkState) {
    return (state == checkState);
}

int getTreeState() {
    return state;
}