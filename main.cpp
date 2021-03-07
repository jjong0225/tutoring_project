#include <iostream>
#include <string>
#include "objects.h"
#include "data_structure.h"
#include "file_manager.h"

using namespace std;

const int NUM_OF_STATION = 100;
Node STATION_NODE[NUM_OF_STATION] = {0};


int main()
{
    // 파일 읽는 부분
    UserTreeNode* user_root = read_user_data();
    MetroTreeNode* metro_root = read_metro_data();

	travel_map(userMap);
	travel_map(metroMap);
    printf("------user nodes-------\n");
    print_node(user_root);
    printf("----------metro nodes---------\n");
    print_node(metro_root);
    

	//find_item(userMap, "안종훈");
	//find_item(metroMap, "고속터미널");



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
