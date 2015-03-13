#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <json/json.h>
#include <navigate.h>

using navigate::Position;
using std::string;

class Object {
private:
	static int count;
	string id;
	string genId();

protected:	
	Position position;
	
public:
	static int getCount();

	Object();
	Object(Position);

	Position getPosition() const;
	string getId() const;

};

#endif
