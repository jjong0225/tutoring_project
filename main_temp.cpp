#include <iostream>
#include <string>
#include "objects.h"
#include "data_structure.h"
#include "file_manager.h"
#include "algorithm.h"

using namespace std;

const int NUM_OF_STATION = 100;
Node STATION_NODE[NUM_OF_STATION] = {0};

enum Command {
	// for start menu
	startLogin = 1,
	startRegister = 2,
	startDescription = 3,
	startQuit = 4,

	// for main menu
	mainManageMyInfo = 1,
	mainManageSchedule = 2,
	mainFindPath = 3,
	mainUserMatch = 4,
	mainLogout = 5,

	// for manage my info
	changeName = 1,
	changeStation = 2,
	changePassword = 3,
	unsubscribe = 4,
	backFromMyInfo = 5,

	// for manage schedule
	printSchedule = 1,
	addSchedule = 2,
	deleteSchedule = 3,	
	backFromSchedule = 4

	
};

class MainObj {
	private:
		bool savecheck, findcheck;

		int sub_command, subb_command;

		string name, name1, fname, rmname, cname, cstation;
		string station, station1, station3, password;

		int time1, time2, savec, station2, redata, fdata, rmschedule, fstation;

		UserTreeNode* user_root;
		MetroTreeNode* metro_root;

	public:
		MainObj() {
			bool savecheck = 0;
			bool findcheck = 0;

			user_root = read_user_data();
			metro_root = read_metro_data();
		}
		int accept() {
			int command;

			cout << "> ";
			cin >> command;

			cin.clear();
			cin.ignore(10, '\n'); 
			
			return command;
		}
		void clear() {
			if(system("CLS")) system("clear");
		}
		void enter() {
			
		}
		void enterWithComment() {

		}
		void enterDoubleWithComment() {

		}
		void printStartMenu() {
			
		}
		void printMainMenu() {
			
		}
		void printManageMyInfoMenu() {
			
		}
		void printManageScheduleMenu() {
			
		}
		void acceptLoginInfo() {
			
		}
		bool tryLogin() {
			return false;	
		}
	
};

int main() {
	int command = 0;
	MainObj mainObj = MainObj();

	mainObj.clear();

	while(command != startQuit) {
		mainObj.printStartMenu();	
		command = mainObj.accept();

		switch(command) {
			case startLogin:
				mainObj.acceptLoginInfo();

				if(mainObj.tryLogin() == true) {

					while(command != mainLogout) {
						mainObj.printMainMenu();	
						command = mainObj.accept();

						switch(command) {
							case mainManageMyInfo:
								while(command != backFromMyInfo) {
									mainObj.printManageMyInfoMenu();	
									command = mainObj.accept();

									switch(command) {
										case changeName:
											break;

										case changeStation:
											break;

										case changePassword:
											break;

										case unsubscribe:
											break;

										default:
											break;

										
									}
									mainObj.clear();
									command = 0;
								}

								break;

							case mainManageSchedule:
								while(command != backFromSchedule) {
									mainObj.printManageScheduleMenu();	
									command = mainObj.accept();

									switch(command) {
										case printSchedule:
											break;

										case addSchedule:
											break;

										case deleteSchedule:
											break;

										default:
											break;

										
									}
									mainObj.clear();
									command = 0;
								}
								break;

							case mainFindPath:
								break;

							case mainUserMatch:
								break;
							
							default:
								break;
							
						}
						mainObj.clear();
						command = 0;
					}
					
				} else {

				}
				
				break;

			case startRegister:
				break;

			case startDescription:
				break;

			default:
				break;

			
		}
		mainObj.clear();
		command = 0;
	}
	
}
