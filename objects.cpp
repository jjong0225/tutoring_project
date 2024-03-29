#include "objects.h"
#include "data_structure.h"
#include <iostream>
#include <list>
using namespace std;

// Schedule Class

Schedule::Schedule(string param_name, int param_start_time, int param_end_time, string param_station_name)
{
	// 생성자 코드
	this->name = param_name;
	this->id = hash<string>{}(param_name);
	this->start_time = param_start_time;
	this->end_time = param_end_time;
	this->station_name = param_station_name;
}
string Schedule::get_name() { 
	return this->name;	
}
int Schedule::get_id() {
	return this->id;
}
int Schedule::get_start_time() {
	return this->start_time;	
}
int Schedule::get_end_time() {
	return this->end_time;	
}
string Schedule::get_station_name() {
	return this->station_name;	
}
void Schedule::print()
{
	// 스케쥴 프린트
	cout << "스케줄 이름: " << this->name << endl;
	cout << "시작시간: " << this->start_time << endl;
	cout << "종료시간: " << this->end_time << endl;
	cout << "스케줄 장소: " << this->station_name << endl;
}

// User Class

User::User(string param_string, string param_main_station_name, int password)
{
	// 생성자 코드, id는 string hash로 할당해주기
	this->name = param_string;
	this->id = hash<string>{}(param_string);
	this->password = password;
	this->station_name = param_main_station_name;
}
User::User(const User &copy_user)
{
	name = copy_user.get_name();
    station_name = copy_user.get_station_name(); // 유저의 역, 스케쥴의 언제나 맨 처음이고 언제나 맨 마지막이다. 변하면 안됨
	password = copy_user.get_password();
    id = copy_user.get_id();
}
string User::get_name() const{
	return this->name;
}
string User::get_station_name() const{
	return this->station_name;
}
int User::get_id() const{
	return this->id;
}
int User::get_password() const{
	return this->password;
}
list<Schedule> User::get_schedule_list(){
	return this->schedule_list;
}
void User::insert_schedule(Schedule schedule)
{
	this->schedule_list.push_back(schedule);
	// 스케쥴 삽입
}
void User::print()
{
	// 내 정보 출력
	cout << "[User Info]" << endl;
	cout << this->name << endl;
	cout << this->id << endl;
	cout << this->station_name << endl;
	for(Schedule schedule : schedule_list) {
		schedule.print();
	}
}           
void User::print_schedule()
{
	int i=1;
	for(Schedule schedule : schedule_list) {
		cout << "\nSchedule #" << i << '\n';
		cout << "일정 : " << schedule.get_name() << '\n';
		printf("일정 시작 시간 : %d시 %02d분\n", schedule.get_start_time()/100, schedule.get_start_time()%100);
		printf("일정 종료 시간 : %d시 %02d분\n", schedule.get_end_time()/100, schedule.get_end_time()%100);
		cout << "역 이름 : " << schedule.get_station_name() << '\n';
		i++;
	}
}
void User::change_name(string new_name)
{
	this -> name = new_name;
	this -> id = hash<string>{}(new_name);
}
void User::delete_schedule(int index)
{
	list<Schedule>::iterator it;
	it = schedule_list.begin();
	advance(it, index-1);
	this -> schedule_list.erase(it);
}
void User::change_station_name(string new_name)
{
	this -> station_name = new_name;
}
void User::change_password(int newPW)
{
	this -> password = newPW;
}

// Metro Class

Metro::Metro(string param_station_name, int param_station_code)
{
	// 생성자
	this->station_name = param_station_name;
	this->id = hash<string>{}(param_station_name);
}
Metro::Metro(const Metro &copy_metro)
{
	station_name = copy_metro.get_station_name();
    id = copy_metro.get_id();
}
string Metro::get_station_name() const{
	return this->station_name;
}
int Metro::get_id() const{
	return this->id;	
}
list<Departure> Metro::get_departure_list() const{
	return this-> departure_list;
}
void Metro::insert_departure(Departure departure)
{
	this->departure_list.push_back(departure);	
}
void Metro::print() {
	cout << "[Metro]" << endl;
	cout << station_name << endl;
	cout << id << endl;
	for(auto departure_info : this->departure_list) {
		departure_info.print();
	}
}

// Departure Class

Departure::Departure(string station_name, int line, list<int> departure_time, int time_weight)
{
	this->station_name = station_name;
	this->id = hash<string>{}(station_name);
	this->line = line;
	this->departure_time = departure_time;
	this->time_weight = time_weight;
};
string Departure::get_station_name() {
	return this->station_name;	
}
int Departure::get_id() {
	return this->id;	
}
int Departure::get_line() {
	return this->line;	
}
list<int> Departure::get_departure_time() {
	return this->departure_time;	
}
int Departure::get_time_weight() {
	return this->time_weight;	
}
void Departure::print() {
	cout << "[Departure]" << endl;	
	cout << station_name << endl;
	cout << id << endl;
	cout << line << endl;
	for(auto i : departure_time)
		cout << i << " ";
	cout << endl;
	cout << time_weight << endl;
}
