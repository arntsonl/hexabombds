#pragma once

#include "helper.h"

enum { NO_CHANGE=0, ADVANCE_NODE };

class stateNode
{
public:
	stateNode();
	stateNode(char*); // give me a name with no parents or triggers
	stateNode(stateNode*,char*,char*);//parent,my name, trigger
	~stateNode();
	char * getName();
	void addName(char*);
	void addParent(stateNode*, char*);
	void addChild(stateNode*, char*);
	
	bool hasChildName(char*);
	bool hasChild(stateNode*);
	
	stateNode * getTriggerPtr(char *);
	
	// How to add triggers to go from one state to another
	void setTriggerManual(stateNode*);
	void setTriggerTime(u16,stateNode*);
	void setTriggerVariable(int*,stateNode*);
	
	// Update, checks variables, timers for updating
	int update();
	
private:
	void initNode();

	char nodeName[MAX_NAME_LENGTH];
	stateNode* parentNode;		// parent node dictates who the direct parent of a node is
	char parentNodeTrigger[MAX_NAME_LENGTH];
	stateNode* childNodes[MAX_NODE_CONNECTIONS]; // state node pointers
	char childNodeTriggers[MAX_NODE_CONNECTIONS][MAX_NAME_LENGTH];
	
	// We need to have an ID system that connects child nodes to trigger events.
	
	int childNodeCnt;
	
	u16 triggerTmr;	 	// trigger timer
	u16 currentTmr;		// current timer when this trigger is gone
	int * variablePtr; 	// variable ptr
};
