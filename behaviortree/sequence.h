#ifndef __SEQUENCE_H__
#define __SEQUENCE_H__

#include "group.h"

class Sequence : public Group
{
protected:
	virtual void OnEnter();
	virtual Status Update(float step);

private:
	int mCurrentChildIndex;
};

#endif
