#pragma once
class RCObject
{
public:
	RCObject();
	RCObject(const RCObject&);
	RCObject& operator = (const RCObject&);
	virtual ~RCObject() = 0;
protected:
	bool isShareable() const;
	bool isShare() const;
	void addRefCount();
	void removeRefCount();
	void unShare();
private:
	bool shareable;
	int  refCount;
};

