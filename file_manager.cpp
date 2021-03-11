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
			std::string station_name = user["station_name"].asString();

			User userObj = User(name, station_name);

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
		std::cerr << "Failed to parse Json";
	
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

void save_metro_data(MetroTreeNode* root) {
    queue<MetroTreeNode*> s;
    s.push(root);

	ofstream json_file;
	json_file.open("metro.json");

	Json::Value metroData;

    while(!s.empty()){
        MetroTreeNode* now = s.front();
        s.pop();

		Json::Value metro;

		metro["station_name"] = now->data.get_station_name();

		Json::Value departure_list;

		for(auto departure : now->data.get_departure_list()) {
			Json::Value departureObj;			

			departureObj["station_name"] = departure.get_station_name();
			departureObj["line"] = departure.get_line();
			departureObj["time_weight"] = departure.get_time_weight();

			Json::Value departure_time_list;
			
			for(auto departure_time : departure.get_departure_time()) {
				departure_time_list.append(departure_time);
			}

			departureObj["departure_time"] = departure_time_list;

			departure_list.append(departureObj);
		}
		
		metro["departure_list"] = departure_list;
		metroData.append(metro);

        if(now->parent != NULL)
			;
        else
			;
        if(now->left != nullptr)
            s.push(now->left);
        if(now->right != nullptr)
            s.push(now->right);
    }
	Json::StreamWriterBuilder builder;
	builder["commentStyle"] = "None";
	builder["indentation"] = "    ";
	unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

	writer->write(metroData, &json_file);
	cout << endl;

	json_file.close();

}


void save_user_data(UserTreeNode* root) {
    queue<UserTreeNode*> s;
    s.push(root);

	ofstream json_file;
	json_file.open("user.json");

	Json::Value userData;

    while(!s.empty()){
        UserTreeNode* now = s.front();
        s.pop();

		Json::Value user;

		user["name"] = now->data.get_name();
		user["station_name"] = now->data.get_station_name();

		Json::Value schedule_list;

		for(auto schedule : now->data.get_schedule_list()) {
			Json::Value scheduleObj;			

			scheduleObj["name"] = schedule.get_name();
			scheduleObj["start_time"] = schedule.get_start_time();
			scheduleObj["end_time"] = schedule.get_end_time();
			scheduleObj["station_name"] = schedule.get_station_name();

			schedule_list.append(scheduleObj);
		}
		
		user["schedule_list"] = schedule_list;
		userData.append(user);
        if(now->parent != NULL)
			;
        else
			;
        if(now->left != nullptr)
            s.push(now->left);
        if(now->right != nullptr)
            s.push(now->right);
    }
	Json::StreamWriterBuilder builder;
	builder["commentStyle"] = "None";
	builder["indentation"] = "    ";
	unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

	writer->write(userData, &json_file);
	cout << endl;

	json_file.close();

}

