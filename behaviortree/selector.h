#ifndef __SELECTOR_H__
#define __SELECTOR_H__

#include "group.h"

class Selector : public Group
{
protected:
	virtual void OnEnter();
	virtual Status Update(float step);

private:
	int mCurrentChildIndex;
};

#endif