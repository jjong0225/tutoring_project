#ifndef OBJECTS_H
#define OBJECTS_H

#include<string>
#include<vector>
#include<list>
#include<array>

using namespace std;

class Schedule
{
    private :
        string name; // 스케쥴 이름
		int id;
        int start_time; // 시작 시간, HHMM 형식
        int end_time; // 종료 시간, HHMM 형식
        string station_name; // 역 코드
    public :
        Schedule(string param_name, int param_start_time, int param_end_time, string param_station_code);
		string get_name();
		int get_id();
		int get_start_time();
		int get_end_time();
		string get_station_name();
        void print();
};

class User
{
    private :
        string name; // 유저 이름
        string station_name; // 유저의 역, 스케쥴의 언제나 맨 처음이고 언제나 맨 마지막이다. 변하면 안됨
        int id; // 유저 아이디
		string password;
        list<Schedule> schedule_list; // 스케쥴의 백터
    public :
        User(string param_string, string param_main_station_code, string password);
        User(const User &copy_user);
		string get_name() const;
		string get_station_name() const;
		int get_id() const;
		string get_password() const;
		list<Schedule> get_schedule_list();
        void insert_schedule(Schedule schedule);
        string find_optimized_schedule_path();
        void print();
		void print_schedule();
		void change_name(string);
		void delete_schedule(int);
		void change_station_name(string);
		void change_password(string);
};

class Departure
{
	private:
		string station_name;
		int id;
		int line;	
		list<int> departure_time;
		int time_weight;
	public:	
        Departure(string station_name, int line, list<int> departure_time, int time_weight);
		string get_station_name();
		int get_id();
		int get_line();
		list<int> get_departure_time();
		int get_time_weight();
        void print();
};

class Metro
{
    private :
        string station_name;
        int id;
		list<Departure> departure_list;
    public :
        Metro(string param_station_name, int param_station_code);
        Metro(const Metro &copy_metro);
		string get_station_name() const;
		int get_id() const;
		list<Departure> get_departure_list() const;
		void insert_departure(Departure departure);
        int find_maximum_time(int param_time);
		void print();
};

#endif
