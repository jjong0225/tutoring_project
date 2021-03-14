#include "objects.h"
#include "data_structure.h"
#include "algorithm.h"
#include <iostream>
#include <list>
#include<map>
#include<queue>
#include<stack>
#include<tuple>
#include<vector>
#include<algorithm>
#define INF 10000000
using namespace std;

int station_num=0; 
MetroTreeNode *r;
map<int,Node> Node_map;
map<int, Node> ::iterator it_node = Node_map.begin();


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

int hour_to_min(int time){
    int hour=time/100;
    int min=time%100;
    return hour*60+min;
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


void init_graph(MetroTreeNode * root_ptr){
	 r=root_ptr;
     MetroTreeNode *root_node=r;
     queue< MetroTreeNode * > q;
     
     q.push(root_node);
     Node root;
     root.station_id=r->data.get_id();
     Node_map.insert(make_pair(root.station_id,root)); //root node

     int node_cnt=1;
     while(!q.empty()){
        MetroTreeNode * n= q.front();
        q.pop();
		Node temp;
        temp.station_id=n->data.get_id();
		Node_map.insert(make_pair(temp.station_id,temp));
        if(n->left!=nullptr){
            q.push(n->left);         
            node_cnt++;
            }
        if(n->right!=nullptr){
            q.push(n->right);
            node_cnt++;
            };
    } 

     station_num=node_cnt;
	 it_node=Node_map.begin();	
     q.push(root_node);
     while(!q.empty()){
        MetroTreeNode * n= q.front();
        q.pop();
	
        list<Departure> departure_li = n->data.get_departure_list();
        list <Departure> ::iterator it=departure_li.begin();
        int list_size= departure_li.size();

		for(int i=0;i<list_size;++i){
			Departure cur=*it;
            int nex_id=cur.get_id();
             int nex_weight=cur.get_time_weight();  
            int nex_line=cur.get_line();       
            it_node=Node_map.find(nex_id);
            Node newtemp;

            if(it_node ==Node_map.end()){         
                newtemp.station_id=nex_id;               
                cout<<"NEW STATION TREE NODE"<<newtemp.station_id<<endl;
		        Node_map.insert(make_pair(newtemp.station_id,newtemp));
                station_num++;}

             list<int> time_li = it->get_departure_time();
             list <int> ::iterator time_it=time_li.begin();
             int time_size= time_li.size(); 
             vector<int>time_Vec;  

             for(int j=0;time_size>j;j++){
             time_Vec.push_back(*time_it);    
             int nex_departure=*time_it;
             time_it++;}

            Node_Info info;
            info.departure_data=time_Vec;
            info.line_num=nex_line;
            info.time_weight=nex_weight;
            pair<node*,node_info> temp;


            if(it_node ==Node_map.end())  temp= make_pair(&newtemp,info);
            else temp= make_pair(&it_node->second,info);
            Node_map[n->data.get_id()].station_ptr.push_back(temp);
            it++;
		}

        if(n->left!=nullptr){
            q.push(n->left); }
        if(n->right!=nullptr){
            q.push(n->right); };
    } 
	
}



pair<string,vector<pair<int,int>>> track_path(int departure_id,int arrive_id, map<int ,tuple<int,int,int>> path){ 
     
    int node_id=arrive_id;
    vector<pair<int,int>> min_path; 
    stack<string> st_path;
    string path_Str="";
    
    int past_rail=get<1>(path[node_id]);
    MetroTreeNode * temp=search(r,node_id);
    if(temp==NULL){cout<<"TRACK PATH ERROR CAN'T FIND NODE"; exit(1); }
    st_path.push(temp->data.get_station_name()+"("+to_string(past_rail)+" 호선)");
    if(get<2>(path[node_id])==INF){cout<<"TRACK PATH CAN'T VISITED NODE"; exit(1);}
    min_path.push_back(make_pair(node_id,(get<2>(path[node_id]))));  

    while(1){
        node_id=get<0>(path[node_id]);    
        int newrail=get<1>(path[node_id]);     
        if(past_rail!=newrail &&node_id!=departure_id){ 
            st_path.push("("+to_string(newrail)+"->"+to_string(past_rail)+" 환승) ");           
            past_rail=newrail;
            min_path.push_back(make_pair(0,(get<2>(path[node_id]))));
        }
      
        if(node_id==departure_id){ 
            temp=search(r,node_id);
             if(temp==NULL){cout<<"TRACK PATH ERROR CAN'T FIND NODE"; exit(1); }
            st_path.push(temp->data.get_station_name()+"("+to_string(past_rail)+"호선)");
            min_path.push_back(make_pair(node_id,get<2>(path[node_id])));          
            break;}
        else{
              temp=search(r,node_id);
               if(temp==NULL){cout<<"TRACK PATH ERROR CAN'T FIND NODE"; exit(1); }
              st_path.push(temp->data.get_station_name()+"("+to_string(get<1>(path[node_id]))+"호선)");
              min_path.push_back(make_pair(node_id,get<2>(path[node_id]))); }                     
    }

    reverse(min_path.begin(),min_path.end());
    
    while(!st_path.empty()){
        string cur= st_path.top();
        path_Str+=cur;
        st_path.pop();
        if(!st_path.empty())   
            path_Str+=" -> ";
    }
   // cout<<path_Str<<endl;
    return make_pair(path_Str,min_path);
}



pair<int,int> find_min_path(int present_station,int next_station,int start_time,int op){

   int wait_time=-1;
   int min_departure=0xfffff;
   MetroTreeNode *temp=search(r,present_station);
  if(temp==NULL){cout<<"Can't find Data"; exit(1);}
  
  if(op){
    string pr_station_name=temp->data.get_station_name();
    int pr_line=op;
    int nx_line=0;
    it_node=Node_map.find(present_station);
    if(it_node!=Node_map.end()){
        for(int i=0;i<it_node->second.station_ptr.size();i++){
            if(next_station ==it_node->second.station_ptr[i].first->station_id ) 
            nx_line=it_node->second.station_ptr[i].second.line_num;
        }
    }
    temp=search(r,next_station);
    if(temp==NULL){cout<<"Can't find Data"; exit(1);}
    string nx_station_name=temp->data.get_station_name();
    if(pr_line!=-1) cout<<'\n'<<'\n'<<"< "<< pr_station_name<<"("<<pr_line<<"호선)"<<" -> " <<nx_station_name<<"("<<nx_line<<"호선)" <<" 환승 데이터 조회 >"<<'\n'<<endl;
    else cout<<'\n'<<'\n'<<"< "<< pr_station_name<<" -> " <<nx_station_name<<"("<<nx_line<<"호선)" <<" 데이터 조회 >"<<'\n'<<endl;
 }

   map<int,Node>::iterator it;
   it=Node_map.find(present_station);
   int size=it->second.station_ptr.size();
   
   for(int i=0;i<size;i++){
       start_time=stoi(convert_time(start_time));
       pair<node*,node_info>cur=it->second.station_ptr[i];
       if(cur.first->station_id==next_station){
       for(int j=0;j<it->second.station_ptr[i].second.departure_data.size();j++){    
       if( cur.second.departure_data[j] >=start_time && min_departure>cur.second.departure_data[j])
        { int param=cur.second.departure_data[j];
           if( param/100>start_time/100) 
                    param=cal_time(cur.second.departure_data[j]);
           wait_time=param-start_time;
           min_departure=cur.second.departure_data[j];}             
             } 
        }
   }

   if(wait_time<=-1 || min_departure==0xfffff){
      if(op){  cout<< "None Data"<<wait_time<<","<<start_time;
                cout<<'\n'<<"----------------------------------------------------"<<'\n'; }
        return make_pair(0,0); }
   else{
       if(op){
         temp=search(r,next_station);
         if(temp==NULL){cout<<"Can't find Data"; exit(1);}
         cout<<"현재 시각: " <<print_HHMM(convert_time(start_time))<<endl;   
         cout<<temp->data.get_station_name()<< " 행 가장 빠른 열차 : "  <<print_HHMM(convert_time(min_departure))<<'\n';
         cout<< "소요 대기 시간 : "<< print_HHMM(convert_time(wait_time));
         cout<<'\n'<<"----------------------------------------------------"<<'\n'; }
   return make_pair(stoi(convert_time(wait_time)),min_departure);
   }
    
}

pair<map<int,int>, map <int,tuple<int,int,int>>> trans_dijkstra(int departure_id ,int arrive_id,int time){
 
   priority_queue <tuple<int,int, int>,vector<tuple<int,int, int>>,greater<tuple<int,int,int>>> q;
   map <int, int> dist;
   map<int,tuple<int,int,int>> path; 
   map<int,Node> ::iterator it_new=Node_map.begin();
   int cnt=0;
   MetroTreeNode * k=search(r,departure_id);
   if(k==NULL){cout<<"DIJKSTRA ERROR CAN'T FIND NODE"; exit(1); }

   for(int i=1;i<=station_num;i++){ 
       int id= it_new->second.station_id; 
       dist.insert(make_pair(id,INF)); 
       path.insert(make_pair(id,make_tuple(-1,-1,-1))); 
       cnt++;
       it_new++;
   }

   dist[departure_id]=0; 
   q.push(make_tuple(0,departure_id,0)); 
  
   int start_time=time; 
   int j=0;
   int here_rail=0;
 
    while (!q.empty())
    {
      
        int cost =get<0>(q.top()); 
        int here =get<1>(q.top());
        int rail_num=get<2>(q.top());//line
       
        int save=0;     
        q.pop();

        map<int,int> :: iterator it;
        it=dist.find(here);
        
        if(it==dist.end()){
            cout<<"Can't find id";
            exit(2);
        }
        else{  if (it-> second < cost)  continue; }
                
        map<int,Node>::iterator it_node;
        it_node=Node_map.find(here);
        Node * tempnode= &it_node->second;
        if(it_node->second.station_ptr.size()==0){ 
            if(departure_id==here) cout<<"CAN'T GO ANYWHERE";
            continue;}
        for(int i=0;i<tempnode->station_ptr.size();i++){
           pair<Node*, node_info> cur;
           cur=tempnode->station_ptr[i];

           int there=cur.first->station_id;
           int nextDist=cost+cur.second.time_weight;
           int there_rail=cur.second.line_num;

           if(departure_id==here) here_rail=there_rail;

            if( there_rail!=rail_num ){ 
                it=dist.find(here);
                if(it!=dist.end()){
                int move_time=(it->second);
                save=find_min_path(here,there,move_time+start_time,0).first;
                nextDist+=save; 
                }else{ cout<<here<<"Transfer! Can't find departure_time "; exit(1); }    
            }

            it=dist.find(there);
            if(it!=dist.end()){
                int renewal_time=it->second;
                if (renewal_time > nextDist){                         
                dist[there] = nextDist;                 
                q.push(make_tuple(nextDist, there,there_rail));
                path[there]=make_tuple(here,there_rail,min_to_hour(nextDist)); }                  
            }
                   
        }
    }
  
    return make_pair(dist,path); 
}

int transfer_num(vector<pair<int,int>>Track){

    int cnt=0;
    for(int i=0;i<Track.size();i++){
        if(Track[i].first==0) cnt++;
    }
    return cnt;
}

void search_optimize_schedule(vector<pair<int,int>> search_line, int departure_time){
    int line=-1;
    for(int i=0;i< search_line.size();i++){
        if(search_line[i].first==0){
             cout<<"                 < 환승 지점 >"<<'\n';    
            pair<int,int> temp_min= find_min_path(search_line[i-1].first,search_line[i+1].first, search_line[i].second+departure_time,line);
        }else{
            if(i==0){
              it_node=Node_map.find(search_line[i].first);
             if(it_node!=Node_map.end()){
                for(int j=0;j<it_node->second.station_ptr.size();j++){
                    if(search_line[i+1].first ==it_node->second.station_ptr[j].first->station_id ) 
                     line=it_node->second.station_ptr[j].second.line_num;  
                }
            }else cout<<"NONE NODE STATION" <<endl;    
             find_min_path(search_line[i].first,search_line[i+1].first, departure_time,-1); }
             else if(i==search_line.size()-1){
                    MetroTreeNode *temp= search(r,search_line[i].first);
                    if(temp==NULL) {cout<<"SEARCH OPTIMIZE SCHEDULE ERROR CAN'T FIND NODE"; exit(2);}               
                     string destination_name=temp->data.get_station_name();
					 cout<<'\n'<<destination_name<<" 역에 도착하였습니다. "<<endl;
                     cout<<"예상 도착 시간 : "<<print_HHMM(convert_time(search_line[i].second+departure_time))<<endl<<endl;
                     break;
             }
           
        }
    }
}

int find_fair_station(map<int,int>a, map<int,int>b){
  
    pair<int,int> min_node=make_pair(0xfffff,0);
    int size=a.size();
    map<int, int> :: iterator it_a=a.begin();
    map<int, int> :: iterator it_b=b.begin();
    for(int i=0;i<size;i++){
        if(it_a->second !=INF|| it_b->second !=INF){
        int gap=abs(it_a->second - it_b->second);
        if( it_a->second != it_b->second ){ cout<< "Dist Map ERROR "; exit(-1); 
        } else{ 
            if(gap<min_node.first) min_node=make_pair(gap,it_a->first); }      
        }
    }

    MetroTreeNode *temp=search(r,min_node.second);
    if(temp==NULL){cout<<"FIND FAIR STATION CAN'T FIND NODE";exit(1);}
    cout<<"Fair_Station: "<<temp->data.get_station_name()<<endl;
    int station_id =temp->data.get_id();
    it_a=a.find(station_id);
    it_b=b.find(station_id);
    cout<<"A estimated time: "<<print_HHMM(to_string(min_to_hour( it_a -> second )))<<endl;
    cout<<"B estimated time: "<<print_HHMM(to_string(min_to_hour( it_b -> second )))<<endl;
    cout<<endl;
    return station_id;
}


pair<int, pair<string,vector<pair<int,int>>>>find_max_departure_time(int A_station_id , int B_station_id ,int now_time,int deadline_time){
  
   int departure=now_time;
    pair<map<int,int>, map <int,tuple<int,int,int>>> schedule_optimize_path;
    pair<string,vector<pair<int,int>>> track_optimize_path;
    int tot=0;
    int before=0;
    pair<int,int> gap=make_pair(0,0); 
	it_node=Node_map.find(A_station_id);
	vector<pair<node*,node_info>> start_node=it_node->second.station_ptr;
	int size=start_node.size();

	int wait=0;
	for(int i=0;i<size;i++){
        for(int j=0;j<it_node->second.station_ptr[i].second.departure_data.size();j++){
		if(start_node[i].second.departure_data[j] > deadline_time || start_node[i].second.departure_data[j] < now_time) continue;
		else{
            int cur=start_node[i].second.departure_data[j];
			wait=start_node[i].second.departure_data[j]-now_time;
			schedule_optimize_path=trans_dijkstra(A_station_id,B_station_id,cur);
  			track_optimize_path=track_path(A_station_id,B_station_id,schedule_optimize_path.second);
			int destination=track_optimize_path.second.size()-1;
   			tot=track_optimize_path.second[destination].second;
			int result=stoi(convert_time(tot+now_time+wait));
         	if(result<deadline_time && gap.second <wait &&gap.first <cur){
                  gap=make_pair(cur,wait);
             }
		  }
        }
	}

    schedule_optimize_path=trans_dijkstra(A_station_id,B_station_id,gap.first);
    track_optimize_path=track_path(A_station_id,B_station_id,schedule_optimize_path.second);
     
    return make_pair(gap.first,track_optimize_path);
}


tuple<string,Track_info,Track_info> find_optimized_schedule_path(int A_station, int B_station,int end_schedule_time, int next_schedule_time){
 
    
    int estimated_departure=end_schedule_time; 
    int estimated_arrive=next_schedule_time;
    
     MetroTreeNode * A_NODE=search(r,A_station );
     MetroTreeNode * B_NODE=search(r,B_station );
     Track_info none;   
     if(A_NODE==NULL){cout<< "This station is not the departure station"; return make_tuple(" ",none, none);}
     if(B_NODE==NULL){cout<< "Destination data is not in TREE DATA"; exit(1);}
	 string A_NAME= A_NODE->data.get_station_name();
	 string B_NAME=B_NODE->data.get_station_name();

    pair<map <int, int >, map<int, tuple<int,int,int>>> schedule_dijkstra= trans_dijkstra(A_station ,B_station ,estimated_departure);
    pair<string,vector<pair<int,int>>> track_optimize_path=track_path(A_station ,B_station ,schedule_dijkstra.second);
    
     
    string schedule_Str= "Schedule : " + A_NAME   +" -> "+ B_NAME+'\n';
    
    int destination=track_optimize_path.second.size()-1;

    string minimum_schecdule_path_Str="최소 소요 시간 : "+print_HHMM(to_string(track_optimize_path.second[destination].second))+'\n';
    string schedule_transfer_num_str="환승 횟수 : "+to_string(transfer_num(get<1>(track_optimize_path)))+'\n';
    string schedule_Path_str="Path : "+get<0>(track_optimize_path)+'\n';
    
    int min_arrive_time= track_optimize_path.second[destination].second + estimated_departure ;
    string min_arrive_time_str="최소 도착 시간 : "+print_HHMM(convert_time(min_arrive_time))+'\n';
     
    pair<int, pair<string,vector<pair<int,int>>>> max_time= find_max_departure_time(A_station,B_station,estimated_departure,estimated_arrive); 
    string max_Path_str="Path : "+get<1>(max_time).first+'\n';
    string max_time_Str="놓치면 안되는 마지막 열차 : "+print_HHMM(convert_time(max_time.first))+'\n';
    string max_transfer_num_str="환승 횟수 : "+to_string(transfer_num(get<1>(max_time).second))+'\n';
    string result= schedule_Str+'\n'+minimum_schecdule_path_Str+schedule_transfer_num_str+min_arrive_time_str+ schedule_Path_str+
    '\n'+max_time_Str+max_transfer_num_str+max_Path_str;
 
    Track_info min_arrive={track_optimize_path.second,estimated_departure};
    Track_info max_departure={max_time.second.second,max_time.first};
   
    return make_tuple(result,min_arrive,max_departure);
      
};
