// cribber.cpp : Defines the entry point for the console application.
//

#include	<iostream>
#include	<fstream>

#include	<windows.h>

#include	<conio.h>
#include	<stdio.h>

#pragma warning (disable : 4100)

#include	"ri.h"
#include	"argparse.h"
#include	"librib.h"
#include	"librib2ri.h"

void RenderFile(std::istream& file, const char* name);
static void arg_filename(int argc, char**argv);

bool g_pause;
int g_cFiles=0;
int g_Verbose=0;


int main(int argc, const char** argv)
{
	ArgParse ap;
	ap.usageHeader(ArgParse::apstring("Usage: ") + argv[0] + " [options] files(s) to render");
	ap.argFlag("pause", "\await for a keypress on completion", &g_pause);
	ap.argInt("endofframe", "=integer\aequivalent to \"endofframe\" option", &g_Verbose);
	if (!ap.parse(argc-1, argv+1))
	{
		std::cerr << ap.errmsg() << std::endl << ap.usagemsg();
		exit(1);
	}

	if(ap.leftovers().size()==0) // If no files specified, take input from stdin.
	{
		RenderFile(std::cin, "stdin");
	}
	else
	{
		for (ArgParse::apstringvec::const_iterator e = ap.leftovers().begin(); e != ap.leftovers().end(); e++)
		{
			std::ifstream file(e->c_str());
			RenderFile(file, e->c_str());
		}
	}

	// Wait for a keypress
	if(g_pause)
	{
		std::cout << "Press any key to continue..." << std::endl;
		while(!kbhit())	_sleep(1000);
		getche();
	}

	return(0);
}


void RenderFile(std::istream& file, const char* name)
{
	librib2ri::Engine renderengine;

	// Store the current working directory for later use
	char strCurrWD[255];
	GetCurrentDirectory(255,strCurrWD);

	RiBegin("CRIBBER");

	// Read config file name out of the ini file.
	char strExe[255];
	char strDrive[10];
	char strPath[255];
	char strCFGFile[255];
	GetModuleFileName(NULL, strExe, 255);
	_splitpath(strExe,strDrive,strPath,NULL,NULL);
	_makepath(strCFGFile,strDrive,strPath,"ribber",".cfg");

	std::ifstream cfgfile(strCFGFile);
	if(cfgfile.is_open())
	{
		librib::Parse(cfgfile,"config file",renderengine,std::cerr);
		cfgfile.close();
	}
	else
		std::cerr << "Config file not found " << strCFGFile << std::endl;

	char strDir[255];
	_splitpath(name,strDrive,strPath,NULL,NULL);
	_makepath(strDir, strDrive, strPath, NULL, NULL);
	SetCurrentDirectory(strDir);

	RiOption("statistics", "endofframe", &g_Verbose, RI_NULL);

	librib::Parse(file,name,renderengine,std::cerr);

	SetCurrentDirectory(strCurrWD);

	RiEnd();
}

static void arg_filename(int argc, char**argv)
{
    int i;
	g_cFiles++;

	for(i=0; i<argc; i++)
	{
		std::ifstream file(argv[i]);
		RenderFile(file,argv[i]);
	}
}
