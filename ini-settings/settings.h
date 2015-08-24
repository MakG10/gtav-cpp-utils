#ifndef MODSBINDER_SETTINGS_H_
#define MODSBINDER_SETTINGS_H_

#include <stdlib.h>
#include <map>
#include <boost/property_tree/ptree.hpp>

using namespace std;

class Settings
{
	map<string, map<string, string> > options;
	string filename;
	boost::property_tree::ptree propertyTree;

public:

	Settings();
	Settings(string filename);
	map<string, map<string, string> > load(string filename);
		
	void save(string filename, map<string, map<string, string> > options);
	void save(string filename);
	void save();
	

	void setOption(string section, string name, string value);
	map<string, map<string, string> > getOptions();
	map<string, string> getOptions(string section);
		
	string getOption(string name);
	string getOption(string name, string section);
		
	bool getOptionBool(string name);
	bool getOptionBool(string name, string section);
};

#endif