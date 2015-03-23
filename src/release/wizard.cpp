#include <wizard.h>
#include <navigate.h>
#include <classify.h>
#include <string>

using std::string;
using classify::Type;
using classify::Level;

Wizard::Wizard(Level level) 
	: Character(level, classify::Wizard) {}

GrandWizard::GrandWizard() 
	: Wizard(classify::Grand) {}

MasterWizard::MasterWizard() 
	: Wizard(classify::Master) {}

LightWizard::LightWizard() 
	: Wizard(classify::Light) {}

DarkWizard::DarkWizard()
	: Wizard(classify::Dark) {}

string GrandWizard::toString() {
	return "Zg";
}

string MasterWizard::toString() {
	return "Zm";
}

string LightWizard::toString() {
	return "Zl";
}

string DarkWizard::toString() {
	return "Zd";
}
