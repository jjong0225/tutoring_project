#include <iostream>
#include <string>
#include "objects.h"
#include "data_structure.h"
#include "file_manager.h"
#include "algorithm.h"
#include "time.h"

using namespace std;

const int NUM_OF_STATION = 100;
Node STATION_NODE[NUM_OF_STATION] = {0};

// main loop를 위한 커맨드 목록
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
// 프로그램을 위한 정보, 함수를 저장하는 객체
class MainObj {
	private:
		bool savecheck, findcheck;

		char ch;

		int sub_command, subb_command;

		string name, name1, fname, rmname, cname, cstation;
		string station, station1, station3, password, currTime;

		int time1, time2, savec, station2, redata, fdata, rmschedule, fstation;

		UserTreeNode* user;

		UserTreeNode* user_root;
		MetroTreeNode* metro_root;

	public:
		MainObj() {
			savecheck = 0;
			findcheck = 0;
			ch = '0';

			user_root = read_user_data(); // Json file로 부터 user data를 메모리로 읽어 Tree로 저장함
			metro_root = read_metro_data(); // Json file로 부터 metro data를 메모리로 읽어 Tree로 저장함

			init_graph(metro_root); // 지하철간의 관계를 표현하기 위해 Tree구조에서 Graph를 만듦
			update_time(); // 현재 시간을 가져옴
		}
		void update_time() { // 현재 시간을 가져옴
			time_t temp_time = time(NULL);		
			struct tm *pLocal = localtime(&temp_time);

			int tm_hour = pLocal->tm_hour;
			int tm_min = pLocal->tm_min;

			string tm_min_str;

			if(tm_min < 10) {
				tm_min_str = "0" + to_string(tm_min);	
			} else {
				tm_min_str = to_string(tm_min);	
			}

			currTime = to_string(tm_hour) + tm_min_str;
				
		}
		int accept() { // command를 받는다, command외의 값을 입력받으면 오류비트를 삭제하고 입력스트림을 비워준다.
			int command;

			cout << "> ";
			cin >> command;

			cin.clear();
			cin.ignore(10, '\n'); 
			
			return command;
		}
		void clear() { // System call clear호출
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
		void printLogo() { // 로고 호출
			cout << "                                __                   " << endl;
			cout << "|\\/| _.._  _. _  _  \\_/_    ._ (_  _|_  _  _|   | _  " << endl;
			cout << "|  |(_|| |(_|(_|(/_  |(_)|_||  __)(_| |(/_(_||_||(/_" << endl;
			cout << "              _|" << endl;
			cout << "                	                version 1.0" << endl;
			cout << endl;
			
		}
		void printStartMenu() { // 로그인, 회원가입을 관리하는 첫번째 메뉴 
			cout << "[시작 메뉴]" << endl;
			cout << "1. 로그인" << endl;
			cout << "2. 회원가입" << endl;
			cout << "3. 프로그램 설명" << endl;
			cout << "4. 프로그램 종료" << endl;
			
		}
		void printMainMenu() { // 로그인 된 유저의 기능을 실행해주는 두번째 메뉴 
			cout << "[메인 메뉴]" << endl;
			cout << "1. 내 정보 관리" << endl;
			cout << "2. 스케줄 관리" << endl;
			cout << "3. 지하철 경로 탐색" << endl;
			cout << "4. 다른 유저와의 스케줄 매칭" << endl;
			cout << "5. 로그아웃" << endl;
			
		}
		void printManageMyInfoMenu() { //로그인 된 유저의 정보를 수정하는 세번째 메뉴 
			cout << "[내 정보 관리]" << endl;
			cout << "1. 이름 변경" << endl;
			cout << "2. 기준 출발역 변경" << endl;
			cout << "3. 비밀번호 변경" << endl;
			cout << "4. 회원 탈퇴" << endl;
			cout << "5. 뒤로가기" << endl;
			
		}
		void printManageScheduleMenu() { // 스케쥴 출력 
			cout << "[스케줄 관리]" << endl;
			cout << "1. 스케줄 출력" << endl;
			cout << "2. 스케줄 추가" << endl;
			cout << "3. 스케줄 삭제" << endl;
			cout << "4. 뒤로가기" << endl;
			
		}
		void printDescription() { // 프로그램의 개요 및 코맨트를 출력한다
			int option;

			cout << "[Manage Your Schedule v1.0]" << endl;
			cout << "final update 2021-03-24" << endl;

			cout << endl;
			cout << "스케줄 관리 프로그램에 오신걸 환영합니다 :)" << endl;
			cout << "지하철 최단거리 탐색 및 중간 역 매칭 등을 통하여 나의 스케줄을 관리 및 경로탐색 뿐만 아니라 다른 유저와 스케줄을 매칭할 수 있습니다!" << endl;
			cout << "변경된 데이터는 저장되어 다음 프로그램 실행시에도 유지됩니다." << endl;

			cout << endl;

			cout << "제작자 코멘트를 보시겠습니까?" << endl; 

			cout << "1. 네\n2. 아니오" << endl;
			option = accept();

			if(option == 1) {
				cout << endl;
				cout << "안종훈: 멘티분들이 아이디어도 많이 내주시고 프로젝트에 적극적으로 참여해주셔서 너무 감사하고 죄송했습니다. 저 또한 전공의 측면에서도, 전공 외의 측면에서도 많은 것을 멘티분들게 배우는 좋은 경험이었습니다. 감사합니다!" << endl;
				cout << "김효민: 처음 배우는 것이 많아 순탄하지는 않았지만, 여러 자료구조를 배우고 직접 응용하면서 프로그래밍 실력을 키울 수 있었고, 협업 프로젝트라는 좋은 경험을 할 수 있었습니다." << endl;
				cout << "백성준: 평소에 궁금했던 json parsing 부터, 데이터를 가져오는데 추가로 진행하였던 크롤링까지 어려운 점도 많았지만 결과적으로 즐기면서 많은걸 얻어갈 수 있었던 좋은 기회였습니다:D 또, 팀과 소통해  가면서 점차 결과를 만들어 가는 과정도 정말 좋았습니다. 팀원분들 정말 고생하셨고, 제가 열정이 과했다면 죄송합니다.. ㅎ" << endl;
				cout << "박상욱: 악명높은 포인터와 메모리는 명성에 걸맞게 역시 구현이 어려웠고, 객체와 깃이 처음에는 낯설었지만 프로젝트를 진행하면서 자신감이 생겼습니다!" << endl;
				cout << "나보영: 처음에는 모르는 것도 많고 내용도 어려워 힘들었지만 프로젝트를 진행하면서 팀원들과 협업하고 하나하나씩 배워가며 성장할 수 있어서 좋았습니다!" << endl;
				cout << endl;
			}

			/*
				@ BFS를 통해 Red black tree 를 탐색하여 지하철 graph를 생성함.
			    @이동시간과 열차 대기 시간을 포함한 최소 소요 시간을 구하기 위해 다익스트라 알고리즘을 사용하였으며, 우선순위 큐를 이용해 다익스트라의 시간을 단축함.
				@다익스트라에 저장된 path 배열을 Stack을 사용해 역추적하여 최단거리 이동경로를 얻어냄.
				@이진 검색 알고리즘을 사용하여 마지막 열차 시간을 찾는 시간을 단축함.
				@다익스트라를 통해 얻은 두 user의 최소 이동 소요시간을 비교하여 이동거리가 비슷한 중간역을 찾아줌.
				
			*/	
		}
		void printWelcomMsg() { // 웰컴 메세지 출력
			cout << "안녕하세요, " << user->data.get_name() << "님. 반갑습니다!" << endl;
			
		}
		void acceptLoginInfo() { // 로그인 정보 받기
				cout << "# 로그인" << endl;	
				cout << "아이디(유저 이름): ";
				cin >> fname;
				cout << "비밀번호: ";
				cin >> password;

		}
		bool tryLogin() { // 받은 로그인 정보를 토대로 로그인
			UserTreeNode *user = search(user_root, hash<string>{}(fname));
			UserTreeNode *log = login(user_root, fname, password);

			if(log == nullptr){
				return false;
			} else {
				this->user = user;
				return true;	
			}
		}
		bool tryRegister() { // 회원가입
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
		void changeName() { // 이름 수정
			cout << "새로운 아이디(유저 이름)을 입력해주세요." << endl;
			cout << "> ";
			cin >> cname;
			user->data.change_name(cname);
			cout << "아이디(유저 이름)이 [" << user->data.get_name() <<"] 으로 변경되었습니다."<< endl;
			savecheck = 1;

		}
		void changeStation() { // 기준 출발역 수정
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
		void changePassword() { // 비밀번호 변경
			string currPW, newPW1, newPW2;
			int pwQuery;
			while(true){
				cout << "기존 비밀번호를 입력해주세요." << endl;
				cout << "> ";
				cin >> currPW;
				if(user->data.get_password()==currPW) break;
				else{
					cout << "비밀번호가 일치하지 않습니다." << endl;
					cout << "1. 재입력" << endl;
					cout << "2. 뒤로가기" << endl;
					pwQuery = accept();
					if(pwQuery == 2) return;
					else continue;
				}
			}
			while(true){
				cout << "새로운 비밀번호를 입력해주세요." << endl;
				cout << "> ";
				cin >> newPW1;
				cout << "새로운 비밀번호를 다시 입력해주세요." << endl;
				cout << "> ";
				cin >> newPW2;
				if(newPW2 == newPW1){
					user->data.change_password(newPW1);
					savecheck = true;
					cout << "비밀번호가 변경되었습니다!" << endl;
					enter(3);
					return;
				}
				else{
					cout << "새로운 비밀번호가 일치하지 않습니다." << endl;
					cout << "1. 재입력" << endl;
					cout << "2. 뒤로가기" << endl;
					pwQuery = accept();
					if(pwQuery == 2) return;
					else continue;
				}
			}
		}
		void unsubscribe() { // 탈퇴(유저 삭제)
			int recheck;
			cout << "정말로 탈퇴하시겠습니까?"<< endl;
			cout << "1. 네" << endl;
			cout << "2. 아니요" << endl;
			
			recheck = accept();

			if(recheck == 1) {
				delete_node(user_root, hash<string>{}(fname));
				savecheck = 1;
				save_user_data(user_root);
				cout << "회원 탙퇴가 성공적으로 완료되었습니다. 프로그램을 다시 실행해 주세요." << endl;
				enter(1);
				exit(1);

			} else {
				cout << "취소되었습니다." << endl;
				return;
			}
			
		}
		void printSchedule() { // 모든 스케쥴 정보를 출력한다
			int i = 1;
			for(auto schedule : user->data.get_schedule_list()) {
				cout << "[# " << i++ << "번째 스케줄]" << endl;;
				schedule.print();
				cout << endl;

			}

			//user->data.print_schedule();
			//cout << endl;
			cout << "모든 스케줄을 출력하였습니다." << endl;
			
		}
		void addSchedule() { // 스케쥴을 추가한다.
			cout << "새로운 스케줄을 추가합니다." << endl;
			cout << "스케줄 이름: ";
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
			cout << "몇번째 일정을 삭제하시겠습니까? 삭제를 취소하려면 \"-1\" 을 입력해 주세요." << endl;
			rmschedule = accept();

			if(rmschedule == -1) {
				cout << "취소되었습니다." << endl;;
				return;
			}

			user->data.delete_schedule(rmschedule);
			cout << "일정을 삭제하였습니다." << endl;
			savecheck = 1;

		}
		void findPath() { // 최적경로를 찾는다
			int choice;
			int now_time;
			string now_time_str;

			MetroTreeNode* metro1 = search(metro_root, hash<string>{}(user->data.get_station_name()));
			if(user==NULL||metro1==NULL){cout<<"정보 조회 실패"<<endl; return;}
			   fstation = metro1->data.get_id();

			cout << "지하철 경로 탐색을 시작합니다." << endl;
			cout << "1. 현재 시간을 기준으로 탐색하기" << endl;
			cout << "2. 직접 기준 시간 입력하기" << endl;

			choice = accept();

			if(choice == 1) {
				update_time();
				now_time_str = currTime;
				now_time = stoi(now_time_str);

			} else if (choice == 2) {
				cout<< "기준 시간을 입력해주세요 [HHMM : 2400]: ";
				cin>> now_time; 
				while(cin.fail()==true){
					cin.clear();
					cin.ignore(10, '\n');
					cout<<"시간은 숫자로 입력해주세요.\n재입력 : ";
					cin>>now_time;
				}
				now_time_str = to_string(now_time);

			} else {
				cout << "잘못된 입력입니다." << endl;
				return;
			}

			list <Schedule> list_s=user->data.get_schedule_list();
			list_s.sort(schedule_cmp);
			list <Schedule> ::iterator it_s=list_s.begin();
			for(int i=0;i<list_s.size();i++) {
				Schedule cur=*it_s;
				int nx_id=hash<string>{}(cur.get_station_name());
				if(cur.get_start_time() > now_time){

				clear();
				printLogo();

				cout << "기준시간: " << now_time_str << endl;
				cout << endl;

				cout << "[# " << i+1 << "번째 스케줄]" << endl;;
				cur.print();

				if(nx_id!=fstation){
				tuple<string,Track_info,Track_info> schedule_result= find_optimized_schedule_path(fstation,nx_id,now_time, cur.get_start_time());
				if(get<0>(schedule_result)!=" ") {
					printf("\n[스케줄 조회]\n\n");    
					cout<<get<0>(schedule_result)<<endl;
					int option=0;
					printf("[추가 조회 선택]\n\n");
					printf("1. 최소 도착 시간 경로 조회\n2. 늦지 않을 최대 출발 시간 경로 조회\n3. 모두 조회\n4. 조회하지 않음\n");
					option = accept();
					
					if(option==1 || option ==3){
					clear();
					printLogo();

					printf("[바로 지금 출발 한다면?]\n");
					search_optimize_schedule(get<1>(schedule_result).path_list,get<1>(schedule_result).departure_time); // 최소 소요 시간 track

					enter(1);
					}
					if(option==2 ||option ==3){
					clear();
					printLogo();

					printf("[늦어도 이땐 출발해야 해!]\n");
					search_optimize_schedule(get<2>(schedule_result).path_list,get<2>(schedule_result).departure_time); // 최대 출발 track
					enter(1);
					}
					if(option==4) {
						printf("다음 스케줄을 조회합니다. 엔터키를 입력해 주세요.\n");
						enter(3);
					}
					}else{cout<<"check input Data"<<endl;}
				 
				  }else{
					cout<<"이전 스케줄과 스케줄 장소가 같습니다."<<endl;
				}
				fstation=hash<string>{}(cur.get_station_name());
				now_time=cur.get_end_time();
					
				}
			it_s++;
			}
			cout << "모든 스케줄 출력이 끝났습니다." << endl;
			
		}
		void userMatch() { // 유저를 매칭한 후 스케쥴을 매치한다
			int choice;
			int now_time;
			string now_time_str;

			MetroTreeNode* metro1 = search(metro_root, hash<string>{}(user->data.get_station_name()));
			if(user==NULL||metro1==NULL){cout<<"정보 조회 실패"<<endl; return;}
			   fstation = metro1->data.get_id();

			cout << "유저 매칭을 시작합니다." << endl;
			cout << "1. 현재 시간을 기준으로 매칭하기" << endl;
			cout << "2. 직접 기준 시간 입력하기" << endl;

			choice = accept();

			if(choice == 1) {
				update_time();
				now_time_str = currTime;
				now_time = stoi(now_time_str);

			} else if (choice == 2) {
				cout<< "기준 시간을 입력해주세요 [HHMM : 2400]: ";
				cin>> now_time; 
				while(cin.fail()==true){
					cin.clear();
					cin.ignore(10, '\n');
					cout<<"시간은 숫자로 입력해주세요.\n재입력 : ";
					cin>>now_time;
				}
				now_time_str = to_string(now_time);

			} else {
				cout << "잘못된 입력입니다." << endl;
				return;
			}

			string name_a,name_b,name;
			int start_time,end_time;
			
			name_a=user->data.get_name();
			cout<<"상대 유저의 이름: " ;
			cin>>name_b;
			cout<<"스케줄 이름: ";
			cin>>name;
			cout<<"스케줄 시작 시간: ";
			cin>>start_time;
			while(cin.fail()==true){
				cin.clear();
				cin.ignore(10, '\n');
				cout<<"시간은 숫자로 입력해주세요!\n재입력 : ";
				cin>>start_time;
			}
			cout<< "스케줄 종료 시간: "; 
			cin>>end_time;
			while(cin.fail()==true){
				cin.clear();
				cin.ignore(10, '\n');
				cout<<"시간은 숫자로 입력해주세요!\n재입력 : ";
				cin>>end_time;
			}
			
			start_time=convert_time_input(start_time);
			end_time=convert_time_input(end_time);
			
			int id_a=hash<string>{}(name_a);
			int id_b=hash<string>{}(name_b);
			
			UserTreeNode*B =search(user_root,id_b);
			if(B==NULL){cout<<name_b<<"님은 등록되지 않은 회원 입니다.\n"; enter(3); return;}

			bool success= match_schedule(metro_root,user_root,user,B,start_time,end_time,now_time,name);
			if(success) savecheck = 1;

			
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
					cout << "로그아웃 되었습니다" << endl;
				}
				else {
					cout << "변경사항을 삭제 하였습니다. 프로그램을 다시 실행해 주세요." << endl;
					enter();
					exit(1);
					
				}
			}

		}
};

int main() {
	int command = 0;
	int isFirstLogin;
	bool isNewUser = false;
	MainObj mainObj = MainObj(); // 메인 객체 생성

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
								mainObj.enter(1);
								break;

							case mainUserMatch:
								mainObj.userMatch();
								mainObj.enter(1);
								break;
							
							case mainLogout:
								mainObj.logout();
								mainObj.enter(1);
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
				mainObj.enter(1);
				break;

			default:
				break;

		}
		if(!isNewUser)
			mainObj.clear();
	}
	command = 0;
}
