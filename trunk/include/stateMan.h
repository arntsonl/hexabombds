#pragma once

#include "stateNode.h"

class stateManager
{
public:
	stateManager();
	~stateManager();
	void addUnconnectedState(char*);
	void addConnectedState(char*, char*,char*,char*); // parent name, child name, trigger to parent, trigger to child
	void connectStateNames(char*,char*,char*,char*);
	void connectStatePtrs(stateNode*,stateNode*,char*);
	
	// Trigger: time delay, variable changing, manual changing
	void connectTriggerTimeDelay(char*,u16,stateNode*); // name, time delay
	void connectTriggerVariableInt(char*,int*,stateNode*); // name, int ptr changing
	
	char * getCurrentStateName();
	
	// Moving states
	bool sendTrigger(char*);
	
	// State manager update
	void update();
	
private:
	void getCurrentNode();
	stateNode * currentNode;
	stateNode * nodeList[MAX_STATE_NODES];
	int nodeCnt;
};
