#include "RCObject.h"
RCObject::RCObject():shareable(true),refCount(0)
{
}
RCObject::RCObject(const RCObject&):shareable(true),refCount(0)
{
}
RCObject& RCObject::operator=(const RCObject&)
{
	return *this;
}
void RCObject::addRefCount()
{
	++refCount;
}
void RCObject::removeRefCount()
{
	if (--refCount == 0)
	{
		delete this;
	}
}
RCObject::~RCObject()
{
}
bool RCObject::isShareable() const
{
	return shareable;
}
bool RCObject::isShare() const
{
	return refCount > 1;
}
void RCObject::unShare()
{
	shareable = false;
}