#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <json/json.h>
#include <navigate.h>

using std::string;

class Object {
private:
	static int count;
	string id;
	string genId();
	navigate::Point position;
	
public:
	static int getCount();

	Object(navigate::Point position);
	string getId() const;
	navigate::Point getPosition() const;
	void setPosition(navigate::Point);
	
	virtual bool fights() = 0;
	virtual string toString() = 0;

	virtual ~Object() {};
};

#endif
