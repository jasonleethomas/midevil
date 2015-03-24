#include <wizard.h>
#include <navigate.h>
#include <classify.h>
#include <string>

using std::string;
using navigate::Point;
using classify::Type;
using classify::Level;

Wizard::Wizard(Point position, Level level) 
	: Character(position, level, classify::Wizard) {}

GrandWizard::GrandWizard(Point position) 
	: Wizard(position, classify::Grand) {}

MasterWizard::MasterWizard(Point position) 
	: Wizard(position, classify::Master) {}

LightWizard::LightWizard(Point position) 
	: Wizard(position, classify::Light) {}

DarkWizard::DarkWizard(Point position)
	: Wizard(position, classify::Dark) {}

string GrandWizard::toString() {
	return " Zg ";
}

string MasterWizard::toString() {
	return " Zm ";
}

string LightWizard::toString() {
	return " Zl ";
}

string DarkWizard::toString() {
	return " Zd ";
}
