#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <json/json.h>
#include <navigate.h>

using std::string;

typedef int ObjectID;

class Object {
private:
	ObjectID id;

	static int count;
	navigate::Point position;
	
public:
	static int getCount();

	Object(navigate::Point position);
	ObjectID getID() const;

	bool operator==(const Object&) const;

	navigate::Point getPosition() const;
	void setPosition(navigate::Point);
	
	virtual bool fights() = 0;
	virtual string toString() = 0;

	virtual ~Object() {};
};

#endif
