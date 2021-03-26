#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include "json/json.h"
#include "data_structure.h"
#include "file_manager.h"

std::map<int, User> userMap;
std::map<int, Metro> metroMap;

UserTreeNode* read_user_data()
{
	std::ifstream jsonFile("user.json");
	
	Json::Value jsonData;
	Json::CharReaderBuilder jsonReader;
	std::string err;	
	UserTreeNode *root= nullptr;
	if(Json::parseFromStream(jsonReader, jsonFile, &jsonData, &err)) {
		Json::Value userData = jsonData;

		for(auto user : userData) {
			std::string name = user["name"].asString();
			int password = user["password"].asInt();
			std::string station_name = user["station_name"].asString();

			User userObj = User(name, station_name, password);

			for(auto schedule : user["schedule_list"]) {
				std::string name = schedule["name"].asString();
				int start_time = schedule["start_time"].asInt(); 
				int end_time = schedule["end_time"].asInt(); 
				std::string station_name = schedule["station_name"].asString();

				Schedule scheduleObj = Schedule(name, start_time, end_time, station_name);
				userObj.insert_schedule(scheduleObj);
			}
			User *userP= &userObj;
			insert_node(root, *userP);
			userMap.insert(std::pair<int, User>(userObj.get_id(), userObj));
		}
	}
	else
		std::cerr << "Failed to parse Json user";
	
	return root;
}

// 위와 같다, Metro 객체인것만 제외한다면
MetroTreeNode* read_metro_data()
{
	std::ifstream jsonFile("metro.json");
	
	Json::Value jsonData;
	Json::CharReaderBuilder jsonReader;
	std::string err;	
	MetroTreeNode *root= nullptr;
	if(Json::parseFromStream(jsonReader, jsonFile, &jsonData, &err)) {
		Json::Value metroData = jsonData;

		for(auto metro : metroData) {
			std::string station_name = metro["station_name"].asString();
			int station_code = metro["station_code"].asInt(); 

			Metro metroObj = Metro(station_name, station_code);

			for(auto departure : metro["departure_list"]) {
				string station_name = departure["station_name"].asString(); 
				int line = departure["line"].asInt(); 
				list<int> departure_time;
				for(auto i : departure["departure_time"]) {
					departure_time.push_back(i.asInt());
				}
				int time_weight = departure["time_weight"].asInt();

				Departure departureObj = Departure(station_name, line, departure_time, time_weight);
				metroObj.insert_departure(departureObj);
			}
			Metro *metroP= &metroObj;
			insert_node(root, *metroP);
			metroMap.insert(std::pair<int, Metro>(metroObj.get_id(), metroObj));
		}
	}
	else
		std::cerr << "Failed to parse Json";
	
	return root;
}

void save_user_data(UserTreeNode* root) {
	string ret = "";

	ret.append("[\n");

    queue<UserTreeNode*> s;
    s.push(root);

	bool isFirstUser = true;
    while(!s.empty()){
		if(isFirstUser)
			isFirstUser = false;
		else
			ret.append(",\n");
        UserTreeNode* now = s.front();
        s.pop();

		ret.append("\t{\n");

		ret.append("\t\t\"name\" : \"").append(now->data.get_name()).append("\",\n");
		ret.append("\t\t\"password\" : ").append(to_string(now->data.get_password())).append(",\n");
		ret.append("\t\t\"station_name\" : \"").append(now->data.get_station_name()).append("\",\n");
		ret.append("\t\t\"schedule_list\" :\n");

		ret.append("\t\t\[\n");

		bool isFirstSchedule = true;
		for(auto schedule : now->data.get_schedule_list()) {
			if(isFirstSchedule)
				isFirstSchedule = false;
			else
				ret.append(",\n");
			ret.append("\t\t\t{\n");

			ret.append("\t\t\t\t\"name\" : \"").append(schedule.get_name()).append("\",\n");
			ret.append("\t\t\t\t\"station_name\" : \"").append(schedule.get_station_name()).append("\",\n");
			ret.append("\t\t\t\t\"start_time\" : ").append(to_string(schedule.get_start_time())).append(",\n");
			ret.append("\t\t\t\t\"end_time\" : ").append(to_string(schedule.get_end_time())).append("\n");

			ret.append("\t\t\t}");
		}

		ret.append("\n");
		ret.append("\t\t]\n");

		ret.append("\t}");

        if(now->parent != NULL)
			;
        else
			;
        if(now->left != nullptr)
            s.push(now->left);
        if(now->right != nullptr)
            s.push(now->right);
    }
	ret.append("\n]");

	ofstream json_file("user.json", ofstream::trunc);
	json_file << ret;
	json_file.close();

}


