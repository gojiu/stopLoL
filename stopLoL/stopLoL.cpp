// stopLoL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <string>
#include <vector>
#include <sstream>
#include <TlHelp32.h>



using namespace std;

void terminateLoL();
vector<string> split(string str, char delimiter);
int NumGames(string date);



int main()
{

	HWND window;
	AllocConsole();
	window = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(window, 0);


	// Get current date and convert it to a string with format yyyy-mm-dd  (so it fits with riot game logs)
	time_t t = time(NULL);  
	tm * now = localtime(&t);
	wchar_t currDate[100];
	wcsftime(currDate, 100, L"%Y-%m-%d", now);
	wstring currDateWideString(currDate);
	string currDateString(currDateWideString.begin(), currDateWideString.end());

	for (;;)
	{
		if (NumGames(currDateString) >= 3)
		{
			terminateLoL();
		}
		Sleep(10000);
	}


    return 0;
}




void terminateLoL()
{
	HANDLE hProcessus = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0); // Create a handle to a snapshot of running processes
	PROCESSENTRY32 processDetail; // Create a PROCESSENTRY32 structure to recieve informations about processes
	processDetail.dwSize = sizeof(PROCESSENTRY32); // sets the size of the structure to its size, it's obligatory
	if (hProcessus == INVALID_HANDLE_VALUE)
	{
		cerr << "wrong" << endl;
	}
	if (Process32First(hProcessus, &processDetail)) // if there are still processes and if Process32First function succeed
	{
		while (Process32Next(hProcessus, &processDetail)) // while there are still processes in the snapshot
		{
			if (_tcscmp(processDetail.szExeFile, _T("League of Legends.exe")) == 0 || _tcscmp(processDetail.szExeFile, _T("LolClient.exe")) == 0) // function to compare 2 wchar_t variables, here we check if League of Legends.exe is in the running processes
			{
				//If LoL is in currently running processes, kill it.
				HANDLE hTerProc = OpenProcess(PROCESS_TERMINATE, FALSE, processDetail.th32ProcessID); // opens a handle to the process
				TerminateProcess(hTerProc, 0); // terminate the process
				CloseHandle(hTerProc); // close the handle
			}
		}
	}
	CloseHandle(hProcessus); // close the handle
}



// Nice function I found online to split strings, can't give credit, can't remember where I found it -.-
vector<string> split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str); // Turn the string into a stream.
	string tok;

	while (getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}

	return internal;
}


int NumGames(string date)
{
	int count = 0; // number of games
	vector<string> dates; //vector to hold games dates
	vector<string> fileNames; //vector to hold complete file names of the logs
	WIN32_FIND_DATA findFileData; // WIN32_FIND_DATA structure to hold informations about the files

								  // HANDLE to the first file in the path, the path is of type wchar_t, backslashes have to be escaped
								  // and a wildcard is used to get every text files in the log folder
								  // then we use the adress-of operand with the name of our structure to get information about files
	HANDLE hFind = FindFirstFile(L"C:\\Riot Games\\League of Legends\\Logs\\Game - R3d Logs\\*.txt", &findFileData);

	// check if FindNextFile function succeeds
	while (FindNextFile(hFind, &findFileData) != 0)
	{
		// Convert wchar_t findFileData.cFileName into string name
		wstring ws(findFileData.cFileName);
		string name(ws.begin(), ws.end());

		// Here we split the name of the log file in two because the date is situated just before the T
		// in league of legends log files, so we store the date temporarly in the fileNames vector
		fileNames = split(name, 'T');

		//We erase the part after the T since we don't need it
		fileNames.erase(fileNames.begin() + 1);

		//We store the date in our dates vector
		dates.push_back(fileNames.at(0));
	}

	// For every dates in the vector
	for (unsigned int i = 0; i < dates.size(); ++i)
	{

		//We compare them to today's date, if it matches, then we increase count by one
		if (dates.at(i) == date)
		{
			count += 1;
		}
	}

	// return the number of games played today
	return count;
}