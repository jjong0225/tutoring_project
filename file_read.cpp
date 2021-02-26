#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include "json/json.h"
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
	
//	for(auto obj : metroObjs) {
//		obj.print();
//	}

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


	find_item(userMap, "James");
	find_item(metroMap, "고속버스터미널");
	

	return 0;
}



