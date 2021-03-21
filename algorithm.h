#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "data_structure.h"
#include "objects.h"
#include<string>
#include<vector>
#include<list>
#include<array>
#include<tuple>
#include<map>


using namespace std;

typedef struct track_info{
    vector<pair<int,int>> path_list;
    int departure_time;

}Track_info;
UserTreeNode * login(UserTreeNode *root, string username, string password);
void init_graph( MetroTreeNode * root_ptr);
bool schedule_cmp(Schedule  &a, Schedule  &b);
int GetTimeWeight(int start ,int end);
string convert_time(int time);
int min_to_hour(int time);
int cal_time(int input_time);
int hour_to_min(int time);
string print_HHMM(string  val );
bool Metro_check(MetroTreeNode * root_ptr, int id);
pair<Schedule *,int> Find_empty_time(list <Schedule> li_schedule, int meeting_start, int meeting_end );
int convert_time_input(int input);
pair<string, vector<pair<int,int>>> track_path(int departure_id,int arrive_id, map<int ,tuple<int,int,int>> path);
pair<int,int> find_min_path(int present_station,int next_station,int start_time,bool op);
pair<map<int,int>, map <int,tuple<int,int,int>>> trans_dijkstra(int departure_id ,int arrive_id,int time);
int transfer_num(vector<pair<int,int>>Track);
void search_optimize_schedule(vector<pair<int,int>> search_line, int departure_time);
int find_fair_station(map<int,int>a, map<int,int>b);
pair<int, pair<string,vector<pair<int,int>>>>find_max_departure_time(int A_station_id , int B_station_id ,int now_time,int deadline_time);
bool match_schedule(MetroTreeNode *metro_r, UserTreeNode * user_r, UserTreeNode *A,UserTreeNode *B, int meeting_start, int meeting_end, int now_time, string name);
tuple<string,Track_info,Track_info> find_optimized_schedule_path(int A_station, int B_station,int end_schedule_time, int next_schedule_time);

#endif