#include "stateNode.h"

#include <stdio.h>
#include <string.h>

// default constructor
stateNode::stateNode()
{
	this->parentNode = 0;
	this->initNode();
}

// name-defined constructor
stateNode::stateNode(char * inputName)
{
	sprintf(nodeName, inputName);
	this->initNode();
}

// constructor with a name & parent node
stateNode::stateNode(stateNode * parent, char * inputName, char * trigger)
{
	sprintf(nodeName, inputName);
	this->parentNode = parent;
	sprintf(parentNodeTrigger, trigger);
	this->initNode();
}

// default deconstructor
stateNode::~stateNode()
{
}

void stateNode::initNode()
{
	this->childNodeCnt = 0;
	this->triggerTmr = 0x0;	 	// trigger timer
	this->currentTmr = 0x0;		// current timer when this trigger is gone
	this->variablePtr = 0; 	// variable ptr
	for(int i = 0; i < MAX_NODE_CONNECTIONS; i++)
	{
		childNodes[i] = 0;
		strcpy(childNodeTriggers[i],"");
	}
	
}

char * stateNode::getName()
{
	return nodeName;
}

void stateNode::addName(char * inputName)
{
	sprintf(nodeName, inputName);
}

void stateNode::addParent(stateNode * parent, char * trigger)
{
	strcpy(this->parentNodeTrigger,trigger);
	this->parentNode = parent;
}

void stateNode::addChild(stateNode * inputNode, char * trigger)
{
	if ( this->childNodeCnt < MAX_NODE_CONNECTIONS )
	{
		this->childNodes[this->childNodeCnt] = inputNode;
		strcpy(this->childNodeTriggers[this->childNodeCnt],trigger);
		this->childNodeCnt++;
	}
	else
	{
		iprintf("Could not add child...\n");
	}
}

// This function is mainly used to see if our current node actually
// has the child asked for. It does not return any pointers or names.
bool stateNode::hasChildName(char * childName)
{
	for(int i = 0; i < this->childNodeCnt; i++)
	{
		if ( ! strcmp(this->childNodes[i]->getName(), childName) )
		{
			// Found the child node!
			return true;
		}
	}
	return false; // could not find a child!
}

// This function will actually return the child pointer we are requesting.
stateNode * stateNode::getTriggerPtr(char * triggerName)
{
	if ( ! strcmp(this->parentNodeTrigger, triggerName) )
	{
		return this->parentNode;
	}
	for(int i = 0; i < this->childNodeCnt; i++)
	{
		if ( ! strcmp(this->childNodeTriggers[i], triggerName) )
		{
			return this->childNodes[i];
		}
	}
	return 0; // could not find a child!
}

void stateNode::setTriggerTime(u16 newTimer, stateNode * nextNode)
{
	this->triggerTmr = newTimer;	 	// trigger timer
}

void stateNode::setTriggerVariable(int * varPtr, stateNode * nextNode)
{
	this->variablePtr = varPtr; 	// variable ptr
}

int stateNode::update()
{
	// We can have 3 types of nodes in the state machine:
	//
	// 1st node is controlled by a wait trigger, which will only respond when
	//    the state machine tells the node to change.
	//
	// 2nd node is controlled by a timer, which will only respond when the
	//    the timer reaches its max/peak
	//
	// 3rd node is controlled by a variable pointer, which has become a certain
	//    trigger number. This would be for health being less than 0, etc.

	if ( triggerTmr == 0 && variablePtr == 0 )
	{
		return NO_CHANGE;
	}
	else if ( triggerTmr > 0 )
	{
		// increment timers
	}
	else if ( variablePtr != 0 )
	{
		// check to see if our variable has changed?
	}
	else
	{
		// default return, no changing!
		return NO_CHANGE;
	}
	return NO_CHANGE; // get rid of warning
}

