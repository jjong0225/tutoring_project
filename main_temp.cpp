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
		bool savecheck, findcheck, isNewUser;

		char ch;

		int sub_command, subb_command;

		string name, name1, fname, rmname, cname, cstation;
		string station, station1, station3, password;

		int time1, time2, savec, station2, redata, fdata, rmschedule, fstation;

		UserTreeNode* user;
		UserTreeNode* user_root;
		MetroTreeNode* metro_root;

	public:
		MainObj() {
			savecheck = 0;
			findcheck = 0;
			isNewUser = false;
			ch = '0';

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
		void enter(int type=0) {
			switch(type) {
				case 1:
						ch = fgetc(stdin);
						cout << "엔터키를 입력해 주세요..";
						ch = fgetc(stdin);
					break;
				case 2:
						cout << "엔터키를 입력해 주세요..";
						ch = fgetc(stdin);
						ch = fgetc(stdin);
					break;
				case 3:
						ch = fgetc(stdin);
					break;
				default:
					break;	
			}
			
		}
		void printLogo() {
			cout << "                                __                   " << endl;
			cout << "|\\/| _.._  _. _  _  \\_/_    ._ (_  _|_  _  _|   | _  " << endl;
			cout << "|  |(_|| |(_|(_|(/_  |(_)|_||  __)(_| |(/_(_||_||(/_" << endl;
			cout << "              _|" << endl;
			cout << "                	                   version 0.0" << endl;
			cout << endl;
			
		}
		void printStartMenu() {
			cout << "[시작 메뉴]" << endl;
			cout << "1. 로그인" << endl;
			cout << "2. 회원가입" << endl;
			cout << "3. 프로그램 설명" << endl;
			cout << "4. 프로그램 종료" << endl;
			
		}
		void printMainMenu() {
			cout << "[메인 메뉴]" << endl;
			cout << "1. 내 정보 관리" << endl;
			cout << "2. 스케줄 관리" << endl;
			cout << "3. 지하철 경로 탐색" << endl;
			cout << "4. 다른 유저와의 스케줄 매칭" << endl;
			cout << "5. 로그아웃" << endl;
			
		}
		void printManageMyInfoMenu() {
			cout << "[내 정보 관리]" << endl;
			cout << "1. 이름 변경" << endl;
			cout << "2. 기준 출발역 변경" << endl;
			cout << "3. 비밀번호 변경" << endl;
			cout << "4. 회원 탈퇴" << endl;
			cout << "5. 뒤로가기" << endl;
			
		}
		void printManageScheduleMenu() {
			cout << "[스케줄 관리]" << endl;
			cout << "1. 스케줄 출력" << endl;
			cout << "2. 스케줄 추가" << endl;
			cout << "3. 스케줄 삭제" << endl;
			cout << "4. 뒤로가기" << endl;
			
		}
		void printDescription() {
		}
		void printWelcomMsg() {
			cout << "로그인 성공" << endl;
			cout << "안녕하세요, " << user->data.get_name() << "님. 반갑습니다!" << endl;
			
		}
		void acceptLoginInfo() {
				cout << "# 로그인" << endl;	
				cout << "아이디(유저 이름): ";
				cin >> fname;
				cout << "비밀번호: ";
				cin >> password;

		}
		bool tryLogin() {
			UserTreeNode *user = search(user_root, hash<string>{}(fname));
			UserTreeNode *log = login(user_root, fname, password);

			if(log == nullptr){
				return false;
			} else {
				this->user = user;
				return true;	
			}
		}
		void tryRegister() {
			cout << "# 회원가입" <<endl;
			cout << "회원가입을 진행합니다."<<endl;
			while(!findcheck){
				cout <<"아이디(유저 이름): ";
				cin>> name;
				UserTreeNode *user4 = search(user_root, hash<string>{}(name));
				if(!user4){
					cout << "비밀번호: ";
					cin >> password;
					cout <<"기준 출발역: ";
					cin >> station;
					if(Metro_check(metro_root,hash<string>{}(station))){

					User user1 = User(name, station, password);
					insert_node(user_root, user1);
					savecheck = 1;
					findcheck = 1;

					isNewUser = true;
					fname = name;

					cout << "새로운 유저로 등록되었습니다." << endl;

					}else{
						cout<<"입력하신 출발 역은 노선에 존재하지 않습니다. 재시도 해주세요 \n";
					}		
				}
				else{
					cout << "이미 존재하는 아이디입니다.\n";
					cout << "다른 아이디를 입력해주세요!\n"; 
				}
			}
			
		}
		void changeName() {
			
		}
		void changeStation() {
			
		}
		void changePassword() {
			
		}
		void unsubscribe() {
			
		}
		void printSchedule() {
			
		}
		void addSchedule() {
			
		}
		void deleteSchedule() {
			
		}
		void findPath() {
			
		}
		void userMatch() {
			
		}
		void logout() {
			if(savecheck){
				cout << "변경사항을 저장하시겠습니까?\n1. 저장\n2. 저장하지않음"<< endl;
				cout << "> ";
				cin>> savec;
				if(savec == 1){
					save_user_data(user_root);
					savecheck = 0;
					cout << "저장완료"<< endl;
				}
			}
			cout << "로그아웃 되었습니다." << endl;
		}
};

int main() {
	int command = 0;
	int isFirstLogin;
	MainObj mainObj = MainObj();

	mainObj.clear();

	while(command != startQuit) {
		isFirstLogin = true;

		mainObj.clear();
	   	mainObj.printLogo();
		mainObj.printStartMenu();	
		command = mainObj.accept();

		switch(command) {
			case startLogin:
				mainObj.acceptLoginInfo();

				if(mainObj.tryLogin() == false) {
					cout << "아이디/비밀번호가 잘못되었습니다."<< endl;
					mainObj.enter(2);

				} else {

					while(command != mainLogout) {
						if(isFirstLogin) {
							isFirstLogin = false;
							mainObj.printWelcomMsg();
							mainObj.enter(2);
						}

						mainObj.clear();
						mainObj.printLogo();
						mainObj.printMainMenu();	
						command = mainObj.accept();

						switch(command) {
							case mainManageMyInfo:
								while(command != backFromMyInfo) {
									mainObj.clear();
									mainObj.printManageMyInfoMenu();	
									command = mainObj.accept();

									switch(command) {
										case changeName:
											mainObj.changeName();
											break;

										case changeStation:
											mainObj.changeStation();
											break;

										case changePassword:
											mainObj.changePassword();
											break;

										case unsubscribe:
											mainObj.unsubscribe();
											break;

										default:
											break;
									}
									mainObj.clear();
								}
								command = 0;
								break;

							case mainManageSchedule:
								while(command != backFromSchedule) {
									mainObj.clear();
									mainObj.printManageScheduleMenu();	
									command = mainObj.accept();

									switch(command) {
										case printSchedule:
											mainObj.printSchedule();
											break;

										case addSchedule:
											mainObj.addSchedule();
											break;

										case deleteSchedule:
											mainObj.deleteSchedule();
											break;

										default:
											break;
									}
									mainObj.clear();
								}
								command = 0;
								break;

							case mainFindPath:
								mainObj.findPath();
								break;

							case mainUserMatch:
								mainObj.userMatch();
								break;
							
							case mainLogout:
								mainObj.logout();
								mainObj.enter();
								break;
							
							default:
								break;
							
						}
						mainObj.clear();
					}
					
				}
				
				break;

			case startRegister:
				mainObj.tryRegister();
				mainObj.enter();
				break;

			case startDescription:
				mainObj.printDescription();
				break;

			default:
				break;

		}
		mainObj.clear();
	}
	command = 0;
}
