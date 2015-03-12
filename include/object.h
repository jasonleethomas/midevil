#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <json/json.h>
#include <cell.h>
#include <navigation.h>

using nav::Position;
using std::string;

class Object {
private:
	string id;
	Position position;
	
public:
	Object();
};
#endif
