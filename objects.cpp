#include "objects.h"
using namespace std;

class Schedule
{
    private :
        string name; // 스케쥴 이름
        int start_time; // 시작 시간, HHMM 형식
        int end_time; // 종료 시간, HHMM 형식
        int station_code; // 역 코드
    public :
        Schedule(string param_name, int param_start_time, int param_end_time, int param_station_code)
        {
            // 생성자 코드
        }
        void print_schedule()
        {
            // 스케쥴 프린트
        }
};

class User
{
    private :
        string name; // 유저 이름
        int id; // 유저 아이디
        int main_station_code; // 유저의 역, 스케쥴의 언제나 맨 처음이고 언제나 맨 마지막이다. 변하면 안됨
        list<Schedule> my_schedule; // 스케쥴의 백터
    public :
        User(string param_string, int param_main_station_code)
        {
            // 생성자 코드, id는 string hash로 할당해주기
        }
        void print_my_info()
        {
            // 내 정보 출력
        }

        void insert_schedule(string param_schedule_name, int param_start_time, int param_end_time, int param_station_code)
        {
            // 스케쥴 삽입
        }

        void print_my_schedule()
        {
            // 자신의 모든 스케쥴 출력
        }
};

class Metro
{
    private :
        string station_name;
        int station_code;
        vector<array<int,3>> departure_time; // 도착역,호선,출발시간
    public :
        Metro(string param_station_name, int param_station_code, vector<int> param_departure_time)
        {
            // 생성자
        }
        int find_maximum_time(int param_time)
        {
            // param_time보다 같거나 큰 departure_time 중 가장 가까운 값 리턴
        }
};

void init_graph()
{
    // STATION_NODE의 초기화
    // tree의 모든 노드를 순회하면서 graph를 만든다. 
}

string find_optimized_schedule_path(Node A, Node B)
{
    // 스케쥴에 따라 최적화 된 path 출력
    // 여기서 최적화된 내용은 station A -> station B의 최소시간을 갖는 최단거리여야 한다.
    // 리턴 string은 다음과 같다.
    /*
    스케쥴 : A -> B
    최단경로의 시간 : X분
    가장 늦게 출발하는 시간 : HH:MM
    Path : xx(a호선) -> xx_1(a호선) -> (a->b환승) ->  xx_2(b호선) ...
    */
   /*
    Node 그래프에서 dijstra를 통해 최단경로를 얻는다.
    Metro 트리에서 출발역의 find_maximum_time를 이용하여 최소 출발시간을 구한다
        -방법 1. 최대 출발시간 = 도착예정시간 - 최단경로의 시간 (난이도 1)
        -방법 2. 최대 출발시간 = A역의 가장 가까운 출발 시간(도착예정시간 - 최단경로의 시간) (난이도 2)
            즉, 걸리는 시간과 출발역의 스케쥴까지 고려하는 것
        -방법 3. 방법2에서 환승역의 스케쥴까지 고려하는 것
   */
}

