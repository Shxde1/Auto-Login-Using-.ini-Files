#pragma once
#include <filesystem> 
#include <string> 
#include <fstream>
#include "skStr.h"
#include "mini.h"

bool WriteLicense(std::string path, std::string license)
{
	mINI::INIFile inifile(path);

	mINI::INIStructure config;

	config["User Info"]["License"] = license;

	bool check = inifile.write(config, true);
	//the second paramter makes it look good to the eye so change if you want it to look ugly
	if (!check)
	{
		return false;
	}
	return true;
}

bool WriteUserPass(std::string path, std::string username, std::string password)
{
	mINI::INIFile inifile(path);

	mINI::INIStructure config;

	config["User Info"].set({
	{"Username", username},
	{"Password", password}
		});

	bool check = inifile.write(config, true);
	//the second paramter makes it look good to the eye so change if you want it to look ugly
	if (!check)
	{
		return false;
	}
	return true;
}

std::string ReadFromIniFile(std::string path, std::string sectionname, std::string subsectionname) 
{
	mINI::INIFile inifile(path);

	mINI::INIStructure config;

	inifile.read(config);

	if (config[sectionname].has(subsectionname))
	{
		std::string content = config.get(sectionname).get(subsectionname);

		return content;
	}
	else
	{
		return skCrypt("Key Doesnt Exist Doesnt Exist").decrypt();
	}
}

bool verifykey(std::string path, std::string sectionname, std::string subsectionname)
{
	mINI::INIFile inifile(path);

	mINI::INIStructure config;

	inifile.read(config);

	if (config[sectionname].has(subsectionname))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UpdateIniValue(std::string path, std::string sectionname, std::string subsection, std::string newvalue) 
{
	mINI::INIFile inifile(path);

	mINI::INIStructure config;

	inifile.read(config);

	config[sectionname][subsection] = newvalue;

	bool check = inifile.write(config, true);
	if (!check)
	{
		return false;
	}
	return true;
}