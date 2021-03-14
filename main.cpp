#include <iostream>
#include <string>
#include "objects.h"
#include "data_structure.h"
#include "file_manager.h"
#include "algorithm.h"

using namespace std;

const int NUM_OF_STATION = 100;
Node STATION_NODE[NUM_OF_STATION] = {0};


int main()
{
    int command = 0;
	bool savecheck = 0;
    // 파일 읽는 부분
    UserTreeNode* user_root = read_user_data();
    MetroTreeNode* metro_root = read_metro_data();


    while(command != 3)
    {
        int sub_command, subb_command;
        string name, name1, fname, rmname, cname, cstation;
        string station, station1, station3;
        int time1, time2, savec, station2, redata, fdata, rmschedule, fstation; //station2는 Metro입력시
        cout << "========================================================="<< endl;
        cout << "안녕하세요 지하철 스케줄 관리 프로그램에 오신걸 환영합니다!" << endl;
        cout<< "1. 유저 데이터 관리"<< endl;
        cout<< "2. 스케줄 관리"<< endl;
        cout<< "3. 프로그램 종료"<< endl;

		cin >> command;

		cin.clear(); //failbit
		cin.ignore(10, '\n'); //

		cout << command;


	

    
        switch (command)
        {
            case 1:{
                while(sub_command != 5){
                    cout << "========================================================="<< endl;
                    cout << "유저 데이터 관리에 오신걸 환영합니다" <<endl;
                    cout<< "1. 유저 데이터 추가" << endl;
                    cout<< "2. 유저 데이터 찾기"<< endl;
                    cout<< "3. 유저 데이터 수정"<< endl;
                    cout<< "4. 유저 데이터 삭제"<< endl;
                    cout<< "5. 뒤로가기" <<endl;
                    cin >> sub_command;
                    switch(sub_command){ 
                        case 1:{
                            cout << "========================================================="<< endl;
                            cout <<"추가하려는 유저은 이름은 무엇입니까?"<< endl;
                            cin>> name;
                            cout <<"유저의 출발 역은 어디입니까?"<< endl;
                            cin >> station;
                            cout << "유저의 스케줄을 알려주세요"<< endl;
                            cout << "스케줄이름 시작시간 종료시간 도착역은?"<< endl;
                            cin >> name1 >> time1 >> time2 >>station3;

                            User user1 = User(name, station);
                            Schedule schedule1 = Schedule(name1, time1, time2, station3);
                            user1.insert_schedule(schedule1);
                            insert_node(user_root, user1);
                            cout << "유저의 id는 " << user1.get_id() <<"입니다."<< endl;
                            savecheck = 1;
                            
                            break;
                        }
                        case 2:{
                            cout <<"찾고싶은 유저의 이름을 입력하세요"<< endl;
                            cin >> fname;
                            UserTreeNode *user2 = search(user_root, hash<string>{}(fname));
                            cout << "유저정보"<< endl;
                            user2->data.print();
                            break;
                        }
                        case 3:{
                            while(subb_command != 5){
                                cout << "-------------------------------------------------" <<endl;
                                cout << "수정할 유저의 이름을 입력하세요!" << endl;
                                cin >> fname;
                                UserTreeNode *user2 = search(user_root, hash<string>{}(fname));
                                cout << "========================================================="<< endl;
                                cout << user2->data.get_name() <<"님의 어떤 정보를 수정하시겠습니까?"<<endl;
                                cout << "1. 유저 이름 수정"<< endl;
                                cout << "2. 출발역 수정" <<endl;
                                cout << "3. 스케줄 추가" <<endl;
                                cout << "4. 스케줄 삭제" <<endl;
                                cout << "5. 뒤로가기" <<endl;
                                cin >> subb_command;
                                cout << "-------------------------------------------------" <<endl;
                                switch (subb_command)
                                {
                                    case 1 :
                                    {
                                        cout << "바꿀 새로운 유저 이름을 입력해주세요" << endl;
                                        cin >> cname;
                                        user2->data.change_name(cname);
                                        cout << "유저 이름이" << user2->data.get_name() <<"으로 바뀌었습니다."<< endl;
										savecheck = 1;
                                        break;
                                    }
                                    case 2:
                                    {
                                        cout << "출발역을 어느역으로 바꾸시겠습니까? 바꿀 역이름을 입력해주세요" << endl;
                                        cin >> cstation;
                                        user2->data.change_station_name(cstation);
										savecheck = 1;
                                        break;
                                    
                                    }
                                    case 3:
                                    {
                                        cout << "추가하고 싶은 스케줄을 입력해주세요!" <<endl;
                                        cout << "스케줄이름 시작시간 종료시간 도착역은?"<< endl;
                                        cin >> name1 >> time1 >> time2 >>station;
                                        Schedule schedule2 = Schedule(name1, time1, time2, station);
                                        user2->data.insert_schedule(schedule2);
										savecheck = 1;
                                        break;
                                    }
                                    case 4:
                                    {
                                        cout << "오늘" << user2->data.get_name() << "님의 일정입니다." << endl;
                                        user2->data.print_schedule();
                                        cout << "몇번째 일정을 삭제하시겠습니까?" << endl;
                                        cin >> rmschedule;
                                        user2->data.delete_schedule(rmschedule);
                                        cout << "일정을 삭제하였습니다." << endl;
                    					savecheck = 1;
                                        break;
                                    }
									case 5:{
										break;
									}
									default :
									{
										cout << "번호를 잘못입력하셨습니다. 다시 입력해주세요!"<<endl;
										break;
									}
                                
								}

                            }
							subb_command = 0;
                            break;
							
                        }
                        case 4:{
                            cout << "삭제하려는  유저의 이름은 무엇입니까?"<< endl;
                            cin >> rmname;
                            delete_node(user_root, hash<string>{}(rmname));
                            savecheck = 1;
                            break;
                        }
						case 5:
						{
							break;
						}
						default :
						{
							cout << "번호를 잘못입력하셨습니다. 다시 입력해주세요!"<<endl;
							break;
						}
                    }
                }
				sub_command =0;
                break;
            }
            
            case 2:
            {  
                init_graph(metro_root);
				sub_command = 0;
                while(sub_command !=2){
                    cout << "========================================================="<< endl;
                    cout << "오늘 스케줄을 확인해보세요!" << endl;
                    cout<<"1. 스테줄 보기"<< endl;
                    cout<<"2. 뒤로가기"<< endl;
                    cin>> sub_command;

                    switch(sub_command){
                        case 1:
                        {
                            
                            cout << "보고 싶은 유저의 이름을 입력해주세요!" << endl;
                            cin >> fname;
                            
                            UserTreeNode *user3 = search(user_root, hash<string>{}(fname));
                            MetroTreeNode* metro1 = search(metro_root, hash<string>{}(user3->data.get_station_name()));
                            if(user3==NULL||metro1==NULL){cout<<"정보 조회 실패"<<endl; break;}
                            fstation = metro1->data.get_id();
                            int now_time;
                            cout<<"현재 시각을 입력하세요 [HHMM : 2400]"<<endl;
                            cin >> now_time;
                            list <Schedule> ::iterator it_s=user3->data.get_schedule_list().begin();
							list <Schedule> list_s=user3->data.get_schedule_list();
                             for(Schedule schedule : user3->data.get_schedule_list()) {
                                Schedule cur=schedule;
                            	int nx_id=hash<string>{}(cur.get_station_name());
                                if(cur.get_start_time() > now_time){
								cout<<"스케줄 ["+cur.get_name()+"]"<<endl;
								cout<<"스케줄 장소 : "<<cur.get_station_name()<<endl;
								cout<<"시작 시간: "<<cur.get_start_time()<<"  종료 시간: "<<cur.get_end_time()<<endl<<endl;
		                        tuple<string,Track_info,Track_info> schedule_result= find_optimized_schedule_path(fstation,nx_id,now_time, cur.get_start_time());
                                if(get<0>(schedule_result)!=" ") {
                                    printf("\n--------------------스케줄 조회--------------------\n\n");    
                                    cout<<get<0>(schedule_result)<<endl;
									int option=0;
									printf("[ Option 선택 ]\n\n");
									cout<<"1. 최소 도착 시간 경로 조회  "<<"2. 늦지 않을 최대 출발 시간 경로 조회"<<endl<<"3. 모두 조회 4. 조회하지 않음"<<endl;
									cin>>option;
									if(option==1 ||option ==3){
									printf("--------------바로 지금 출발 한다면 ?---------------\n");
                                    search_optimize_schedule(get<1>(schedule_result).path_list,get<1>(schedule_result).departure_time); // 최소 소요 시간 track
									}
									if(option==2 ||option ==3){
                                  	printf("\n---------------늦어도 이땐 출발해야 해!---------------\n");
                                    search_optimize_schedule(get<2>(schedule_result).path_list,get<2>(schedule_result).departure_time); // 최대 출발 track
									}
                                }else{cout<<"check input Data"<<endl;}
                                fstation=hash<string>{}(cur.get_station_name());
                                now_time=cur.get_end_time();
                                }
							 }./
                            cout << "오늘 스케줄이 끝났습니다." << endl;
							break;
                    	}
						case 2:
						{
							break;
						}
						default :
						{
							cout << "번호를 잘못입력하셨습니다. 다시 입력해주세요!"<<endl;
							break;
						}
                	}
                
            	}
				break;
			}
			
            case 3: {
                if(savecheck){
                    cout << "-------------------------------------------------" <<endl;
                    cout << "변경사항을 저장하시겠습니까? 1. 저장 2. 저장하지않음"<< endl;
                    cin>> savec;
                    if(savec == 1){
                        save_user_data(user_root);
                        savecheck = 0;
                        cout << "저장했습니다"<< endl;

                    }
					
                }
				break;
            }
			default :
				{
					cout << "번호를 잘못입력하셨습니다. 다시 입력해주세요!"<<endl;
					break;
				}


		}
    }
    return 0;
}