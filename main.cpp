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
    // 파일 읽는 부분
    UserTreeNode* user_root = read_user_data();
    MetroTreeNode* metro_root = read_metro_data();

    printf("------user nodes-------\n");
    print_node(user_root);
    printf("----------metro nodes---------\n");
    print_node(metro_root);

	save_user_data(user_root);
	save_metro_data(metro_root);

    
    //Algorithm 
   
    init_graph(metro_root);
    tuple<string,Track_info,Track_info> schedule_result= find_optimized_schedule_path(-152022995,248006855,1100,1500);
    //현재 station id, 다음 스케줄 station id, 현재 시간 cur time , 다음 스케줄 시작 시간 nex time
    if(get<0>(schedule_result)!=" ") {
    printf("----------------Optimize Schedules---------------\n\n");    
    cout<<get<0>(schedule_result)<<endl;
    printf("----------Mininmum estimated arrival time Path----------\n");
    search_optimize_schedule(get<1>(schedule_result).path_list,get<1>(schedule_result).departure_time); // 최소 소요 시간 track
    printf("\n-------------Maximum departure time Path-------------\n");
    search_optimize_schedule(get<2>(schedule_result).path_list,get<2>(schedule_result).departure_time); // 최대 출발 track
    } 


//    while(1)
//    {
//        string command;
//        cin >> command;
//        if(command == "4")
//            break;
//        else
//        {
//            // do something
//        }
//    }
    return 0;
}
