#include <iostream>
#include <fstream>
#include <utility>
#include "json/json.h"
#include "jsoncpp.cpp" //변겅
#include "objects.h" // 변경
#include "objects.cpp" // 변경
#include "data_structure.h"

std::vector<User> userObjs;
std::vector<Metro> metroObjs;

std::map<int, User> userMap;
std::map<int, Metro> metroMap;

/* 
JSON파일 읽고 User Object들로 만든다. 
만들고 data_structure에 정의된 함수들을 이용해 tree를 구성한다.
    (힌트 1. tree가 구현이 잘 되어있고, parsing이 잘 되어있다면 parsing한 object를 insert만 계속 하면 된다 )
    (힌트 2. Custom tree를 구현하기 전에 STL의 map을 이용하여 미리 구현하면 협업이 쉬울것이다.)
*/

template <typename T>
void init_map(std::map<int, T>& map, std::vector<T>& objs) {
	for(auto obj : objs) 
		map.insert(std::pair<int, T>(obj.get_id(), obj));
}

template <typename T>
void travel_map(std::map<int, T>& map) {
	for(auto obj : map)
		cout << obj.first << " >> ";	
	cout << endl;
}

template <typename T>
void find_item(std::map<int, T>& map, string item) {
	int id=hash<string>{}(item);
	typename std::map<int, T>::iterator it = map.find(id);
	if(it != map.end()) {
		it->second.print();
	} else 
		cout << "can't find" << endl;
}

UserTreeNode* read_user_data()
{
	std::ifstream jsonFile("user.json");
	
	Json::Value jsonData;
	Json::CharReaderBuilder jsonReader;
	std::string err;	

	if(Json::parseFromStream(jsonReader, jsonFile, &jsonData, &err)) {
		Json::Value userData = jsonData;

		for(auto user : userData) {
			std::string name = user["name"].asString();
			int id = user["id"].asInt(); 
			int main_station_code = user["main_station_code"].asInt();

			User userObj = User(name, main_station_code);

			for(auto schedule : user["my_schedule"]) {
				std::string name = schedule["name"].asString();
				int start_time = schedule["start_time"].asInt(); 
				int end_time = schedule["end_time"].asInt(); 
				int station_code = schedule["station_code"].asInt();

				Schedule scheduleObj = Schedule(name, start_time, end_time, station_code);
				userObj.insert_schedule(scheduleObj);
			}

			userObjs.push_back(userObj);
		}
	}
	else
		std::cerr << "Failed to parse Json";
	
//	for(auto obj : userObjs) {
//		obj.print();
//		obj.print_my_schedule();
//	}

	UserTreeNode* temp;
	return temp;
}

// 위와 같다, Metro 객체인것만 제외한다면
MetroTreeNode* read_metro_data()
{
	std::ifstream jsonFile("metro.json");
	
	Json::Value jsonData;
	Json::CharReaderBuilder jsonReader;
	std::string err;	

	if(Json::parseFromStream(jsonReader, jsonFile, &jsonData, &err)) {
		Json::Value metroData = jsonData;

		for(auto metro : metroData) {
			std::string station_name = metro["station_name"].asString();
			int station_code = metro["station_code"].asInt(); 

			Metro metroObj = Metro(station_name, station_code);

			for(auto departureInfo : metro["departure_info"]) {
				int destination_code = departureInfo["destination_code"].asInt(); 
				int line = departureInfo["line"].asInt(); 
				int departure_time = departureInfo["departure_time"].asInt();

				Departure scheduleObj = Departure(destination_code, line, departure_time);
				metroObj.insert_departure_info(scheduleObj);
			}

			metroObjs.push_back(metroObj);
		}
	}
	else
		std::cerr << "Failed to parse Json";
	
	// for(auto obj : metroObjs) {
	// 	obj.print();
	// }

    // metro 파일을 읽어 tree구조로 저장한다.
	MetroTreeNode* temp;
	return temp;
}
int main() {

	
    
	read_user_data();
	read_metro_data();

	init_map(userMap, userObjs);
	init_map(metroMap, metroObjs);

	travel_map(metroMap);
	travel_map(userMap);

	//  find_item(userMap, "James");
	//  find_item(metroMap, "고속버스터미널");

    init_graph();//노선 그래프 생성	
	make_Metro(); // 임의로 객체 생성, JSON 파일을 읽는 방식으로 변경해야함
	vector<vector<int>> Alldeparture_list=init_departure_info();

    insert_departure_data(Metro_array[5],5,Alldeparture_list);
	// Metro_array[5].print();

	/* 노선, 현재 시간, 다음 스케줄 시작 시간으로 최적의 스케줄 출력
	int now_time=1000;
	find_optimized_schedule_path(node_array[16],node_array[7],now_time);
	find_optimized_schedule_path(node_array[3],node_array[12],now_time-100);
	*/

	Schedule schedule1("person A",800,1000,4);
	Schedule schedule2("person B",800,1100,5);
	User A("person A",2);
	User B("person B",17);
	A.insert_schedule(schedule1);
	B.insert_schedule(schedule2);
	
	cout<<"============ < 중간 역 조회 >=========="<< endl;

	int now_time=1000;
	int get_A_main_station_code=2; //main station 정보 읽기
	int get_B_main_station_code=15; 
	
	pair<vector<int>,vector<tuple<int,int,int>>> a_result= trans_dijkstra(get_A_main_station_code,get_B_main_station_code,now_time);
    pair<vector<int>,vector<tuple<int,int,int>>> b_result= trans_dijkstra(get_B_main_station_code,get_A_main_station_code,now_time);
	int fair_station= find_fair_station( a_result.first,b_result.first,get_A_main_station_code,get_B_main_station_code);

    cout<<"A path: "<< track_path(get_A_main_station_code,fair_station,a_result.second).first<<endl<<endl;
	find_optimized_schedule_path(node_array[get_A_main_station_code],node_array[fair_station],now_time);
    cout<<"B path: "<<track_path(get_B_main_station_code,fair_station,b_result.second).first<<endl; 
	find_optimized_schedule_path(node_array[get_B_main_station_code],node_array[fair_station],now_time);
   

 

	return 0;
}



