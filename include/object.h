#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <json/json.h>
#include <navigate.h>

using navigate::Point;
using std::string;

class Object {
private:
	static int count;
	string id;
	string genId();

protected:	
	Point position;
	
public:
	static int getCount();

	Object();
	Object(Point);

	Point getPosition() const;
	void setPosition(Point);
	string getId() const;

	virtual bool movedBy(Object*) = 0;
	virtual bool reactTo(Object*) = 0;
	virtual string toString() = 0;
	virtual void getSettings();

	virtual ~Object() {};
};

#endif
