#include "stateMan.h"

#include <string.h>
#include <stdio.h>

#include "stateNode.h"

stateManager::stateManager()
{
	nodeCnt = 0;
	currentNode = 0;
	for(int i=0;i<MAX_STATE_NODES;i++)
	{
		nodeList[i] = 0; // set all state node pointers to 0
	}
}

stateManager::~stateManager()
{
	for(int i = 0; i < nodeCnt; i++)
	{
		if ( nodeList[i] != 0 )
		{
			delete nodeList[i];
		}
	}
}

void stateManager::addUnconnectedState(char * nodeName)
{
	for(int i = 0; i < MAX_STATE_NODES; i++)
	{
		if ( nodeList[i] == 0 )
		{
			nodeList[i] = new stateNode(nodeName); // make a new node with a name
			currentNode = nodeList[i];
			break;
		}
	}
	nodeCnt++;
}

void stateManager::addConnectedState(char * nodeName, char * parentName, char * parentTrigger, char * childTrigger)
{
	stateNode * parentNode = 0;
	int i;
	for(i = 0; i < MAX_STATE_NODES; i++)
	{
		if ( ! strcmp(parentName, nodeList[i]->getName() ) )
		{
			parentNode = nodeList[i];
			break;
		}
	}
	for(i = 0; i < MAX_STATE_NODES; i++)
	{
		if ( nodeList[i] == 0 )
		{
			nodeList[i] = new stateNode(parentNode, nodeName, childTrigger); // make a new node with a name
			parentNode->addChild(nodeList[i], parentTrigger);
			break;
		}
	}
	nodeCnt++; // add another node
}

void stateManager::connectStateNames(char * firstName, char * secondName, char * firstTrigger, char * secondTrigger)
{
	stateNode * firstNode 	= 0;
	stateNode * secondNode 	= 0;
	int i;
	for(i=0; i < MAX_STATE_NODES; i++)
	{
		if ( nodeList[i] != 0 )
		{
			if ( ! strcmp(firstName, nodeList[i]->getName()) )
			{
				firstNode = nodeList[i];
				break;
			}
		}
	}
	for(i = 0; i < MAX_STATE_NODES; i++)
	{
		if ( nodeList[i] != 0 )
		{
			if ( ! strcmp(secondName, nodeList[i]->getName()) )
			{
				secondNode = nodeList[i];
				break;
			}
		}
	}
	firstNode->addChild(secondNode, firstTrigger);
	secondNode->addChild(firstNode, secondTrigger);
	if ( firstNode == 0)
	{
		iprintf("Could not find 1st node: %s\n", firstName);
	}
	else if (  secondNode == 0 ) 
	{
		iprintf("Could not find 2nd node: %s\n", secondName);
	}
}

void stateManager::connectTriggerTimeDelay(char* nodeName, u16 timer, stateNode * nextNode)
{
	for(int i=0; i < MAX_STATE_NODES; i++)
	{
		if ( nodeList[i] != 0 )
		{
			if ( ! strcmp(nodeName, nodeList[i]->getName()) )
			{
				nodeList[i]->setTriggerTime(timer, nextNode);
				break;
			}
		}
	}
}

void stateManager::connectTriggerVariableInt(char * nodeName, int * varPtr, stateNode * nextNode)
{
	for(int i=0; i < MAX_STATE_NODES; i++)
	{
		if ( nodeList[i] != 0 )
		{
			if ( ! strcmp(nodeName, nodeList[i]->getName()) )
			{
				nodeList[i]->setTriggerVariable(varPtr, nextNode);
				break;
			}
		}
	}
}

bool stateManager::sendTrigger(char * trigger)
{
	if ( currentNode != 0 )
	{
	/*  // Alternative approach
		if ( currentNode->hasChildName(moveName) )
		{
			currentNode = currentNode->getChildPtr(moveName);
			return true; // successfully changed states!
		}
		else
		{
			return false;
		}
		*/
		stateNode * nextNode = currentNode->getTriggerPtr(trigger);
		if ( nextNode != 0 )
		{
			currentNode = nextNode;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

char * stateManager::getCurrentStateName()
{
	if ( currentNode != 0 )
	{
		return currentNode->getName();
	}
	return 0; // return nothing if we don't have a current node
}

void stateManager::update()
{
	if ( currentNode == 0 )
	{
		return; // we don't have a current node, so return
		// should we error in this case?
	}
	// State manager updates to check for triggering node advancements, such as timers, etc.
	int currentStateRet; // current state's return
	currentStateRet = currentNode->update();
	if ( currentStateRet == ADVANCE_NODE )
	{
		// currentNode->advanceTriggerNode(); // tells node to check current trigger, and advance 
	}
	
}
