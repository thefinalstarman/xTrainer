/*
 * main.cpp
 *
 *  Created on: Oct 27, 2017
 *      Author: shado
 */
#define _WIN32_WINNT 0x0501

#include <conio.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include <map>
#include <exception>
#include <functional>

#include "tools/tools.h"
#include "tools/trainer.h"

#include "cli/BasicCLI.h"

using namespace std;

//Register page, base address: 0x7ff622da6000
bool verbose = false;

int main(int argc, char** argv){
	if(argc > 1){
		if(argv[1][0] == '-'){//it's a flag
			switch(argv[1][1]){
			case 'v'://Verbose
				verbose = true;
				break;
			default:
				cout << "Unknown flag, " << argv[1][1] << ", ignoring." << endl;
			}
		}
	}//TODO: implement proper argument processing

	default_logger.openLogFile("log.txt");
	default_logger.useStdErr(verbose);

	cout << "Dolphin Trainer: Console\n" << endl;

	auto procs = enumerateProcesses("dolphin");

	int option;
	unsigned long pid;
	if(procs.size() != 0){
		cout << "Found 1 or more potential Dolphin instances.\n Select one, or select \'Not listed\' to input the PID manually." << endl;
		cout << "\tExecutable Name                                              | PID" << endl;
		int i = 0;
		for(; i < procs.size(); i++){
			cout << (i+1) << ".\t";
			if(procs[i].second.size() > 60){
				cout << "...";
				cout << procs[i].second.substr(procs[i].second.size() - 57);
			}else{
				cout << procs[i].second;
				for(int j = 0; j < 60 - procs[i].second.size(); j++)cout << " ";
			}cout << " | ";
			cout << procs[i].first << endl;
		}cout << (i+1) << ". Not listed." << endl;

		cin >> option;
	}if(procs.size() == 0 || option > procs.size()){
		cout << "Input the PID of the target process: ";
		cin >> pid;
	}else pid = procs[option - 1].first;

	cout << '\n';

	Process* process = new Process(pid);
	Dolphin* dolphin;

	try{
		dolphin = new Dolphin(process);
	}catch(runtime_error& e){
		cerr << e.what() << endl;
		cerr << "Make sure the game is running." << endl;
		system("PAUSE");
		return -1;
	}
	BasicCLI cli(dolphin);

	while(cli.getState() == State::RUN){
		cli.update();
	}

	delete process, dolphin;

	return 0;
}
