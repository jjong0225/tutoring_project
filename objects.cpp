#include "objects.h"
#include "data_structure.h"
#include <iostream>

#define MAX_SIZE 100000
#define station_num 18 // 역의 수
#define INF 10000000
int way_num=0; // 경로의 수


vector<Node> node_array(station_num+1); //지하철 node 관리 벡터
vector<tuple<int,int,int>> input[MAX_SIZE]; // 노선정보데이터 : 출발점, 도착점, 호선
vector<Metro> Metro_array;


using namespace std;
// Schedule Class

Schedule::Schedule(string param_name, int param_start_time, int param_end_time, int param_station_code)
{
	// 생성자 코드
	this->name = param_name;
	this->start_time = param_start_time;
	this->end_time = param_end_time;
	this->station_code = param_station_code;
}

void Schedule::print_schedule()
{
	// 스케쥴 프린트
	cout << "[Schedule]" << endl;
	cout << this->name << endl;
	cout << this->start_time << endl;
	cout << this->end_time << endl;
	cout << this->station_code << endl;
}

// User Class

User::User(string param_string, int param_main_station_code)
{
	// 생성자 코드, id는 string hash로 할당해주기
	this->name = param_string;
	this->id = hash<string>{}(param_string);
	this->main_station_code = param_main_station_code;
}
void User::print()
{
	// 내 정보 출력
	cout << "[User Info]" << endl;
	cout << this->name << endl;
	cout << this->id << endl;
	cout << this->main_station_code << endl;
}           

void User::insert_schedule(Schedule schedule)
{
	this->my_schedule.push_back(schedule);
	// 스케쥴 삽입
}

void User::print_my_schedule()
{
	// 자신의 모든 스케쥴 출력
	for(auto schedule : this->my_schedule) {
		schedule.print_schedule();
	}
}

int User::get_id()
{
	return this->id;	
}

// Metro Class

Metro::Metro(string param_station_name, int param_station_code)
{
	// 생성자
	this->station_name = param_station_name;
	this->station_code = hash<string>{}(param_station_name);
}
int Metro::find_maximum_time(int param_time)
{
	// param_time보다 같거나 큰 departure_time 중 가장 가까운 값 리턴
	return 0;
}
int Metro::get_id() {
	return this->station_code;	
}
void Metro::insert_departure_info(Departure departure_info)
{
	this->departure_info_list.push_back(departure_info);	
}
void Metro::print() {
	cout << "[Metro]" << endl;
	cout << station_name << endl;
	cout << station_code << endl;
	for(auto departure_info : this->departure_info_list) {
		departure_info.print();
	}
}

// Departure Class

Departure::Departure(int destination_code, int line, int departure_time)
{
	this->destination_code = destination_code;
	this->line = line;
	this->departure_time = departure_time;
};

void Departure::print() {
	cout << "[Departure]" << endl;	
	cout << destination_code << endl;
	cout << line << endl;
	cout << departure_time << endl;
}

void make_Metro(){
   //알고리즘 구현을 위한 임의의 metro 객체 생성하는 함수
   //json 파일로 읽는 것으로 변경해야 함
   Metro temp("",0); 
   Metro_array.push_back(temp);
	for(int i=1;i<=station_num;i++){
        char name= 'A'+i-1; 
        string metro_name(1,name);
		Metro temp(metro_name,i); 
        //a,b,c 로 이름 임의 생성
		Metro_array.push_back(temp);
	}
}

void init_graph() // 그래프 초기화
{   
  
   // 정보 입력용 백터 생성 :시간/ 연결 번호/호선번호
          
  std::ifstream in("Metro_info.txt");
  std::string s;
  vector<string> read_Metro;
   int i=0;

  if (in.is_open()) {
    // 위치 지정자를 파일 끝으로 옮긴다.
    in.seekg(0, std::ios::end);
    int size = in.tellg();
    s.resize(size);
    in.seekg(0, std::ios::beg);
    in.read(&s[0], size);  
    string token;
	std:: stringstream ss(s);
    
	while (getline(ss, token,'\n')) {
        char temp[100];
        strcpy(temp,token.c_str());
	    char *ptr = strtok(temp, " "); 
	    while (ptr != NULL) {
        read_Metro.push_back(ptr);
        i++;
		ptr = strtok(NULL, " ");//strtok는 일치하는게 없으면 NULL 반환		
	    }
	}   
    }else{
        cout<<" open err";
        
    }
     way_num=i/4; // 경로 수 갱신
     int station,destination,line,time=0;

    for(int j=0;j<i;j++){
        if(j%4==0)station=atoi(read_Metro[j].c_str());
        else if(j%4==1)destination=atoi(read_Metro[j].c_str());
        else if(j%4==2) line=atoi(read_Metro[j].c_str());
        else{
            time=atoi(read_Metro[j].c_str());
            input[station].push_back(make_tuple(time,destination,line));
            input[destination].push_back(make_tuple(time,station,line));
        }
    } 
     
    in.close();
   
    for(int i=1;i<=station_num;i++){
        vector<tuple<int,Node *,int>> temp; // 연결 벡터 저장용 
        for(int j=0;j<input[i].size();j++){            
            tuple<int, Node *,int> a = make_tuple(
                                    get<0>(input[i][j]), 
                                    &node_array[get<1>(input[i][j])],
                                    get<2>(input[i][j])
                                    );
            temp.push_back(a); // 추가
        }
        node_array[i].station_id=i;
        node_array[i].station_ptr=temp;
    }   
}

vector<vector<int>> init_departure_info(){
  //임의의 출발 데이터 생성 추후 json 읽는 방식으로 변경

  vector<vector<int>> departure_array(station_num+1);
  std::ifstream in("departure_info.txt");
  std::string s;
  vector<string> read_departure;
   int i=0;

  if (in.is_open()) {
    in.seekg(0, std::ios::end);
    int size = in.tellg();
    s.resize(size);
    in.seekg(0, std::ios::beg);
    in.read(&s[0], size);  
    string token;
	std:: stringstream ss(s);
    
	while (getline(ss, token,'\n')) {
        char temp[100];
        strcpy(temp,token.c_str());
	    char *ptr = strtok(temp, " "); 
	    while (ptr != NULL) {
        read_departure.push_back(ptr);
        i++;
		ptr = strtok(NULL, " ");//strtok는 일치하는게 없으면 NULL 반환		
	    }
	}   
    }else{
        cout<<" open err";
        exit(1);
    }
    
    int iv_station,iv_time;
    for(int j=0;j<i;j++){
        if(j%2==0){
            iv_station=atoi(read_departure[j].c_str());}    
        else {iv_time=atoi(read_departure[j].c_str());
             if(iv_station<=station_num) departure_array[iv_station].push_back(iv_time);
            }       
        }  
    return departure_array;
    }

void insert_departure_data(Metro metro, int station_code,vector<vector<int>> Alldeparture_list){

    // 임의의 출발정보 데이터

    for(int i=0;i<node_array[5].station_ptr.size();i++){
		node * temp=get<1>(node_array[5].station_ptr[i]);
		int connect=temp->station_id;
		for(int j=0;j<Alldeparture_list[connect].size();j++){
			Departure data(5,connect,Alldeparture_list[connect][j]);
			Metro_array[5].insert_departure_info(data);
		}
	}
}

string convert_time(int time){
    
    string time_Str=to_string(time);
    if(time%100>=60){
        time+=100;
        time-=60;
        time_Str=to_string(time);
    }
    return time_Str;
}

int min_to_hour(int time){
    int hour=time/60;
    int min=time%60;
    return hour*100+min;
}
int hour_to_min(int time){
    int hour=time/60;
    int min=time%60;
    return hour*60+min;
}

tuple<int,node *, int> find_connect_node(node departure_Station,int code){
    // code 로 연결된 node 정보를 전달하는 함수

    for(int i=0;i<departure_Station.station_ptr.size();i++){
        if(code==get<1>(departure_Station.station_ptr[i])->station_id){
            return departure_Station.station_ptr[i];
        }
    }
    cout<<"연결되지 않은 노선";
    exit(1);
}


int cal_time(int input_time){
    if(input_time%100!=0){
        input_time-=100;
        input_time+=60;
    }else{
        input_time-=100;
        input_time+=60;
    }
    return input_time;
}


string print_HHMM(string val){
    int temp=stoi(val);
    int hour=temp/100;
    int min=temp%100;
    
    string time="";
    if(min/10==0)time = to_string(hour)+":0"+to_string(min);
    else time = to_string(hour)+":"+to_string(min);
    return time;
}



pair<string,vector<pair<int,int>>> track_path(int departure,int arrive, vector<tuple<int,int,int>> path){ 
    // 최단거리 경로 추적
    // pair first: 해당 정류장 번호 , second: 노선 번호 , 시간
    
    int nodenum=arrive;
    vector<pair<int,int>> min_path; // 정류장 번호만 저장하는 벡터
    stack<string> st_path;
    string path_Str="";

    int Top=0;
    int past_rail=get<1>(path[nodenum]);

    st_path.push(to_string(nodenum)+"("+to_string(past_rail)+"호선)");
    min_path.push_back(make_pair(nodenum,(get<2>(path[nodenum]))));  

    while(1){

        nodenum=get<0>(path[nodenum]); // 정류장 번호     
        int newrail=get<1>(path[nodenum]); // 노선 정보       
        if(past_rail!=newrail &&nodenum!=departure){ // 이전 노선 정보와 새로 받은 노선 정보가 다를 때
            st_path.push("("+to_string(newrail)+"->"+to_string(past_rail)+"환승) ");           
            past_rail=newrail; // 노선정보 업데이트
            min_path.push_back(make_pair(0,(get<2>(path[nodenum]))));
        }
      
        if(nodenum==departure){  // 출발지점에 도착함
            st_path.push(to_string(nodenum)+"("+to_string(past_rail)+"호선)");
            int before=min_path.front().first;
            min_path.push_back(make_pair(nodenum,get<2>(path[nodenum])));          
            break;}
        else{
             st_path.push(to_string(nodenum)+"("+to_string(get<1>(path[nodenum]))+"호선)");
              min_path.push_back(make_pair(nodenum,get<2>(path[nodenum]))); }                     
    }

    reverse(min_path.begin(),min_path.end()); // 역추적이기 때문에 reverse
    
    while(!st_path.empty()){
        string cur= st_path.top();
        path_Str+=cur;
        st_path.pop();
        if(!st_path.empty())   
            path_Str+=" -> ";
    }
    return make_pair(path_Str,min_path);
}


pair<int,int> find_min_path(int present_station,int next_station,int start_time){
// 가장 짧은 대기시간, 열차 출발시간을 반환한다
// 실 소요시간= 이동 소요시간(가중치) + 대기시간(환승역 도착 시간 - 다음 지하철 출발시간)
   
   //node_Departure_list 는 metro 객체에서 present_station code 역의 departure 정보를 가져온다
   // 아래는 임의의 지하철 스캐줄
   vector<vector<int>> node_departure_list=init_departure_info();
   int wait_time=-1;
   int min_departure=0xfffff;
   tuple<int,node*,int> temp= find_connect_node(node_array[present_station],next_station);

   for(int i=0;i<node_departure_list[next_station].size();i++){
       if(min_departure >start_time && min_departure>node_departure_list[next_station][i]){
           wait_time=cal_time(node_departure_list[next_station][i])-start_time;
           min_departure=node_departure_list[next_station][i]; // 도착 지점이 같더라도 더 빠른 정보를 기록
       }
   } 
   if(wait_time<=-1 || min_departure==0xfffff){
        return make_pair(0,0); }
   else{
   return make_pair(stoi(convert_time(wait_time)),min_departure);
   }
    
}

pair<int,int> print_find_min_path(int present_station,int next_station,int start_time,bool op){
// 가장 짧은 대기시간, 열차 출발시간을 반환한다
// 실 소요시간= 이동 소요시간(가중치) + 대기시간(환승역 도착 시간 - 다음 지하철 출발시간)
   
   //node_Departure_list 는 metro 객체에서 present_station code 역의 departure 정보를 가져온다
   // 아래는 임의의 지하철 스캐줄
    vector<vector<int>> node_departure_list=init_departure_info();

   int wait_time=-1;
   int min_departure=0xfffff;
 if(op){
   cout<<'\n'<<"=========================================="<<'\n'; 
   cout<<"< "<< present_station<<"역 (" << next_station<<")행 열차 정보 조회 >"<<'\n'<<endl;}
  //1. present-> next 로 가는 지하철 출발 정보를 찾는다 
  //2. 출발 시간 - 현재 시간으로 대기 시간 을 구한다
  //3. 새로운 가중치 값을 업데이트 한다
   
   
   tuple<int,node*,int> temp= find_connect_node(node_array[present_station],next_station);

   for(int i=0;i<node_departure_list[next_station].size();i++){
       start_time=stoi(convert_time(start_time));
      if(node_departure_list[next_station][i] >=start_time  && min_departure>node_departure_list[next_station][i])          
        {
           int param=node_departure_list[next_station][i];
           if( param/100>start_time/100) //앞자리가 더 클때 (시 단위가)
                    param=cal_time(node_departure_list[next_station][i]);
          // cout<< "Start time "<< start_time<<" param "<<param<<" node "<<node_departure_list[next_station][i]<<endl;  
           wait_time=param-start_time;
           min_departure=node_departure_list[next_station][i]; // 도착 지점이 같더라도 더 빠른 정보를 기록
       }
   } 
   if(wait_time<=-1 || min_departure==0xfffff){
      if(op){  cout<< "조회된 열차 정보 없음"<<wait_time<<","<<start_time;
                cout<<'\n'<<"=========================================="<<'\n'; }
        return make_pair(0,0); }
   else{
       if(op){
         cout<<"현재 시간: " <<print_HHMM(convert_time(start_time))<<endl;   
         cout<<"다음 역: "<<next_station<<" 행 "<<'\n'<<"가장 빠른 열차 출발 시간: "
         <<print_HHMM(convert_time(min_departure))<<'\n';
         cout<< "소요 대기 시간: "<< print_HHMM(convert_time(wait_time))<<"("<<wait_time<<")";
         cout<<'\n'<<"=========================================="<<'\n'; }
   return make_pair(stoi(convert_time(wait_time)),min_departure);
   }
    
}

pair<vector<int>, vector<tuple<int,int,int>>> trans_dijkstra(int departure,int arrive,int time){
    //출발점, 도착점 , 현재 시간
    // 환승시간까지 고려한 최단거리
      // first: 각 정류장에 대한 최단거리 정보  second: 역추적을 위해 출발점에서 부터의 경로가 저장된 정보

   priority_queue <tuple<int,node*,int>,vector<tuple<int,node*,int>>,greater<tuple<int,node*,int>>> q;
   // 가중치, 노선 번호, 노드

   vector<int> dist(station_num+1,INF);// station num 만큼 초기화 0 값 포함하여 +1
   
   vector<tuple<int,int,int>> path(station_num+1,make_tuple(-1,-1,0)); // 정류장 , 노선 번호
    
   dist[departure]=0; 
   q.push(make_tuple(0,&node_array[departure],0)); // 시작점을 처음으로 우선순위 큐에 추가
  
   int start_time=time; // 현재 시간 입력
   int j=0;
   int here_rail=0;

    while (!q.empty())
    {
        // 우선순위 큐에 음의 가중치로 들어가 있으니 양으로 바꾸어준다.
        int cost =get<0>(q.top()); //가중치
        int rail_num=get<2>(q.top());
        int here =get<1>(q.top())->station_id;// 정류장
        int save=0;     
        q.pop();
    
        if (dist[here] < cost)
            continue;
       
        for (int i = 0; i < node_array[here].station_ptr.size(); i++)
        {           
            tuple<int,node*,int> cur =node_array[here].station_ptr[i]; // 현재 연결된 호선 노드

            int there =get<1>(cur)->station_id; // 인접 호선
            int nextDist = cost + get<0>(cur);
            int there_rail=get<2>(cur);//해당 경로의 호선
         //   cout<<here<<"->"<<there <<" 소요시간(대기+이동): "<<nextDist<<endl;  
            if(departure==here) here_rail=there_rail;
                         
            if( there_rail!=rail_num ){  // 환승지점
                save=print_find_min_path(here,there,dist[here]+start_time,false).first;
                nextDist+=save; 
                 //cout<<"[실제 소요시간]: "<<nextDist<<endl;       
            }
            if (dist[there] > nextDist)
            {                         
                dist[there] = nextDist;   
              
                //cout<<"update: "<<nextDist<<" time "<< convert_time(nextDist)<<endl;                 
                q.push(make_tuple(nextDist, &node_array[there],there_rail));
               // path[there]=make_tuple(here,there_rail,stoi(convert_time(nextDist))); // 역추적을 위한 경로 저장
                path[there]=make_tuple(here,there_rail,min_to_hour(nextDist));                        
            }else{
               // cout<<"no update: "<<dist[there]<<" time "<< convert_time(dist[there])<<endl;
            }
        }
    }     
    return make_pair(dist,path); // 각 정류장에 대한 최소 소요 시간 반환
}

int transfer_num(vector<pair<int,int>>Track){

    int cnt=0;
    for(int i=0;i<Track.size();i++){
        //cout<<Track[i]<< " "; // 경로 출력
        if(Track[i].first==0) cnt++;
    }
    cout<<endl;
    return cnt;
}

void search_optimize_schedule(vector<pair<int,int>> search_line, int departure_time){
    //노드 정보, 경과 시간
    // 연결 노선에 대한 최적의 지하철 스케줄 제공
    int a=departure_time;
    int save_time=0;
    //for(int i=0;i< search_line.size();i++) cout<< search_line[i].first<<"|"<<search_line[i].second<< " ";
    for(int i=0;i< search_line.size();i++){
        if(search_line[i].first==0){
             cout<<"<Trans station>" ;    
            tuple<int,node*,int> temp=find_connect_node(node_array[search_line[i-1].first],search_line[i+1].first);
            pair<int,int> temp_min= print_find_min_path(search_line[i-1].first,search_line[i+1].first, search_line[i].second+departure_time,true);
        }else{
            if(i==0){ 
             print_find_min_path(search_line[i].first,search_line[i+1].first, departure_time,true); }
             else if(i==search_line.size()-1){
                 
                    tuple<int,node*,int> temp;
                    if(search_line[i-1].first!=0) temp=find_connect_node(node_array[search_line[i].first],search_line[i-1].first);
                    else temp=find_connect_node(node_array[search_line[i].first],search_line[i-2].first);
                    int time=get<0>(temp);
                    
                    //cout<< " 최종 도착 시간: "<<print_HHMM(convert_time( search_line[i].second+departure_time))<<endl;
                     cout<<'\n'<<"최종 목적지 "<<search_line[i].first<<" 역 도착"<<endl;
                     cout<<"최종 도착 시간: "<<print_HHMM(convert_time(search_line[i].second+departure_time))<<endl;
                    cout<<'\n'<<"=========================================="<<'\n'; 
                     break;
             }
             else {
                if(search_line[i+1].first!=0)
                    save_time=get<0>(print_find_min_path(search_line[i].first, search_line[i+1].first, search_line[i].second+departure_time,false));
             }
        }
    }
}

int find_fair_station(vector<int>a, vector<int>b,int a_departure, int b_departure){
  
    pair<int,int> min_node=make_pair(0xfffff,0); // 공정성 , 노선역 
    for(int i=1;i<station_num+1;i<i++){
        int gap=abs(a[i]-b[i]);
        //cout<<gap<<endl;
        if(gap<min_node.first) min_node=make_pair(gap,i);
    }
    cout<<"Fair_Station: "<<min_node.second<<endl;
    int station=min_node.second;
    cout<<"A 소요시간: "<<print_HHMM(to_string(min_to_hour(a[min_node.second])))<<endl;
    cout<<"B 소요시간: "<<print_HHMM(to_string(min_to_hour(b[min_node.second])))<<endl;
    cout<<endl;
    return min_node.second;
}

int find_max_departure_time(Node A, Node B,int now_time,int deadline_time){
    int departure=now_time;
    int max=0;
    cout<<"NOW: "<<departure<<" Deadline: "<<deadline_time<<'\n'<<'\n';
    pair<vector<int>,vector<tuple<int,int,int>>> schedule_optimize_path;
    pair<string,vector<pair<int,int>>> track_optimize_path;
    int time_cur=departure;
    int tot=0;
    int i=0;
    int before=0;
    while(time_cur<deadline_time){
    schedule_optimize_path=trans_dijkstra(A.station_id,B.station_id,time_cur);
    track_optimize_path=track_path(A.station_id,B.station_id,schedule_optimize_path.second);
    int destination=track_optimize_path.second.size()-1;
    tot=track_optimize_path.second[destination].second;
    if(stoi(convert_time(tot+time_cur))>deadline_time){
         schedule_optimize_path=trans_dijkstra(A.station_id,B.station_id,before);
        track_optimize_path=track_path(A.station_id,B.station_id,schedule_optimize_path.second);   
         break;    
    }else{
         max=tot;
         before=time_cur;
         time_cur=stoi(convert_time(departure+(i++))); 
        } 
    }
   
     //search_optimize_schedule(track_optimize_path.second,before); 
     
    return before;
}

string find_optimized_schedule_path(Node A, Node B,int time){
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

    int estimated_departure=time; // 출발 시간 가정
    int estimated_arrive=1300; // 도착 예정 시간 가정 (다음 스케줄 시작 시간으로 추후 변경)

    pair<vector<int>,vector<tuple<int,int,int>>> schedule_optimize_path=trans_dijkstra(A.station_id,B.station_id,estimated_departure);
    pair<string,vector<pair<int,int>>> track_optimize_path=track_path(A.station_id,B.station_id,schedule_optimize_path.second);
    
     cout<<'\n'<<"========= < Optimize Schedule > =========="<<endl;
     cout<< '\n'<<"현재 시각 "<<print_HHMM(convert_time(estimated_departure));
     string schedule_Str= "스케줄 : " +  to_string(A.station_id) +" -> "+to_string(B.station_id)+'\n';
    
    int destination=track_optimize_path.second.size()-1;

    string minimum_schecdule_path_Str="최소 소요 시간: "+print_HHMM(to_string(track_optimize_path.second[destination].second))+'\n';
    string schedule_transfer_num_str="환승 횟수: "+to_string(transfer_num(get<1>(track_optimize_path)))+'\n';
    string schedule_Path_str="Path :"+get<0>(track_optimize_path)+'\n';
    
    int min_arrive_time= track_optimize_path.second[destination].second + estimated_departure ;// 출발 시간+ 최단 시간 경로의 시간
    string min_arrive_time_str="최소 도착 시간 "+print_HHMM(convert_time(min_arrive_time))+'\n';
     
    string max_time_Str="최대 출발 시간 "+print_HHMM(convert_time(find_max_departure_time(A,B,estimated_departure,estimated_arrive)))+'\n';
    string result= schedule_Str+minimum_schecdule_path_Str+schedule_transfer_num_str+ schedule_Path_str+min_arrive_time_str+max_time_Str;
    cout<<result;
    search_optimize_schedule(track_optimize_path.second,estimated_departure);  
    // 최소 도착 시간 열차 조회 함수 
    return result;
      
}
