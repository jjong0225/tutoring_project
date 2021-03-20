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
		void enter(int type=2) {
			switch(type) {
				case 1:
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
		bool tryRegister() {
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

					fname = name;

					cout << "새로운 유저로 등록되었습니다." << endl;

					return true; 

					}else{
						cout<<"입력하신 출발 역은 노선에 존재하지 않습니다. 재시도 해주세요 \n";
					}		
				}
				else{
					cout << "이미 존재하는 아이디입니다.\n";
					cout << "다른 아이디를 입력해주세요!\n"; 
				}
			}

			return false;
			
		}
		void changeName() {
			cout << "새로운 아이디(유저 이름)을 입력해주세요." << endl;
			cout << "> ";
			cin >> cname;
			user->data.change_name(cname);
			cout << "아이디(유저 이름)이 [" << user->data.get_name() <<"] 으로 변경되었습니다."<< endl;
			savecheck = 1;

		}
		void changeStation() {
			cout << "새로운 기준 출발역을 입력해주세요." << endl;
			cout << "> ";
			cin >> cstation;
			if(Metro_check(metro_root,hash<string>{}(cstation))){
			user->data.change_station_name(cstation);
			savecheck = 1;
			cout << "변경되었습니다. " << endl;
			}else{
			cout<<"해당 역이 노선에 존재하지 않습니다."<<endl;
			}
			
		}
		void changePassword() {
			cout << "구현 예정" << endl;
			
		}
		void unsubscribe() {
			int recheck;
			cout << "정말로 탈퇴하시겠습니까?"<< endl;
			cout << "1. 네" << endl;
			cout << "2. 아니요" << endl;
			
			recheck = accept();

			if(recheck == 1) {
				delete_node(user_root, hash<string>{}(fname));
				save_user_data(user_root);
				cout << "회원 탙퇴가 성공적으로 완료되었습니다. 프로그램을 다시 시작해 주세요." << endl;
				enter(1);
				exit(1);

			} else {
				cout << "취소되었습니다." << endl;
				return;
			}
			
		}
		void printSchedule() {
			user->data.print_schedule();
			cout << endl;
			cout << "모든 스케줄을 출력하였습니다." << endl;
			
		}
		void addSchedule() {
			cout << "새로운 스케줄을 추가합니다." << endl;
			cout << "스케줄이름: ";
			cin >> name1;
			cout<< "스케줄 시작시간 [HHMM : 2400]: ";
			cin>> time1; 
			while(cin.fail()==true){
				cin.clear();
				cin.ignore(10, '\n');
				cout<<"시간은 숫자로 입력해주세요!\n재입력 : ";
				cin>>time1;
			}
			cout<< "스케줄 종료시간 [HHMM : 2400]: ";
			cin>> time2;
			while(cin.fail()==true){
				cin.clear();
				cin.ignore(10, '\n');
				cout<<"시간은 숫자로 입력해주세요!\n재입력 : ";
				cin>>time2;
			}
			cout<< "스케줄 장소: ";
			cin >>station;
			if(Metro_check(metro_root,hash<string>{}(station))){
				time1=convert_time_input(time1);
				time2=convert_time_input(time2);
				list <Schedule> li = user->data.get_schedule_list();	
				if(Find_empty_time(li,time1,time2).second ==1 ){
				Schedule schedule2 = Schedule(name1, time1, time2, station);
				user->data.insert_schedule(schedule2);
				savecheck = 1;
				cout << "스케줄이 추가되었습니다." << endl;
				}else{
					cout<<"입력하신 시간에 이미 스케줄이 꽉 차있습니다."<<endl;
				}
			}else{
				cout<<"도착역이 노선에 존재하지 않습니다. 스케줄 추가가 취소되었습니다."<<endl;}
		}
		void deleteSchedule() {
			cout << "오늘" << user->data.get_name() << "님의 일정입니다." << endl;
			user->data.print_schedule();                                                             
			cout << endl;
			cout << "몇번째 일정을 삭제하시겠습니까? 삭제를 취소하려면 숫자 [0]을 입력해 주세요." << endl;
			rmschedule = accept();

			if(rmschedule == 0) {
				cout << "취소되었습니다." << endl;;
				return;
			}

			user->data.delete_schedule(rmschedule);
			cout << "일정을 삭제하였습니다." << endl;
			savecheck = 1;

		}
		void findPath() {
			
		}
		void userMatch() {
			
		}
		void logout() {
			if(savecheck){
				cout << "변경사항을 저장하시겠습니까?\n1. 네\n2. 아니오"<< endl;
				cout << "> ";
				cin>> savec;
				if(savec == 1){
					save_user_data(user_root);
					savecheck = 0;
					cout << "저장완료"<< endl;
				}
			}
			savecheck = 0;
			cout << "로그아웃 되었습니다." << endl;
		}
};

int main() {
	int command = 0;
	int isFirstLogin;
	bool isNewUser = false;
	MainObj mainObj = MainObj();

	mainObj.clear();

	while(command != startQuit) {
		isFirstLogin = true;

		if(!isNewUser) {
			mainObj.clear();
			mainObj.printLogo();
			mainObj.printStartMenu();	
			command = mainObj.accept();
		}
		else {
			command = startLogin;
		}

		switch(command) {
			case startLogin:
				if(!isNewUser)
					mainObj.acceptLoginInfo();

				if(mainObj.tryLogin() == false) {
					cout << "아이디/비밀번호가 잘못되었습니다."<< endl;
					mainObj.enter();

				} else {
					isNewUser = false;

					while(command != mainLogout) {
						if(isFirstLogin) {
							isFirstLogin = false;
							mainObj.printWelcomMsg();
							mainObj.enter();
						}

						mainObj.clear();
						mainObj.printLogo();
						mainObj.printMainMenu();	
						command = mainObj.accept();

						switch(command) {
							case mainManageMyInfo:
								while(command != backFromMyInfo) {
									mainObj.clear();
									mainObj.printLogo();
									mainObj.printManageMyInfoMenu();	
									command = mainObj.accept();

									switch(command) {
										case changeName:
											mainObj.changeName();
											mainObj.enter();
											break;

										case changeStation:
											mainObj.changeStation();
											mainObj.enter();
											break;

										case changePassword:
											mainObj.changePassword();
											mainObj.enter(1);
											break;

										case unsubscribe:
											mainObj.unsubscribe();
											mainObj.enter(1);
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
									mainObj.printLogo();
									mainObj.printManageScheduleMenu();	
									command = mainObj.accept();

									switch(command) {
										case printSchedule:
											mainObj.printSchedule();
											mainObj.enter(1);
											break;

										case addSchedule:
											mainObj.addSchedule();
											mainObj.enter();
											break;

										case deleteSchedule:
											mainObj.deleteSchedule();
											mainObj.enter(1);
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
				if(mainObj.tryRegister() == true)
					isNewUser = true;
				break;

			case startDescription:
				mainObj.printDescription();
				break;

			default:
				break;

		}
		if(!isNewUser)
			mainObj.clear();
	}
	command = 0;
}
