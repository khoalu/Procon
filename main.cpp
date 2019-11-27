#include <bits/stdc++.h>
#include <nlohmann/json.hpp>

#define FOR(i,a,b) for(long long i = (a); i < (b); i++)
#define FORD(i,a,b) for(int i = (a); i >= (b); i--)
#define REP(i,a) for(int i = 0; i < (a); i++)
#define REPD(i,a) for(int i = (a)-1; i >= 0; i--)
#define sz(a) (int)a.size()
#define ALL(a) a.begin(),a.end()

#define ii pair<int,int>
#define fi first
#define se second
#define ll long long
#define N 1e5

using namespace std;
using json = nlohmann::json;
json j;
json out;
struct action
{
    int id;
    int dx;
    int dy;
    int turn;
    int apply;
    string type;
};

struct agent
{
    int agentID;
    int x, y;
    int prevX,prevY;
    string type;
};
struct team
{
    int teamID;
    vector<agent> ag;
    int tilePoint;
    int areaPoint;
};

struct match
{
    int width;
    int height;
    vector<vector<int>>points;
    int startedAtUnixTime;
    int turn;
    vector<vector<int>>tiled;
    team tA, tB;
    vector<action> act;
};
match now;
fstream ifs;
void readMap(int i)
{
    ifs.open("fieldInfo_turn"+to_string(i)+".json",ios::in);
    ifs>>j;
    now.width=j["width"];
    now.height=j["height"];
    now.startedAtUnixTime=j["startedAtUnixTime"];
    now.turn=j["turn"];
    int ind=0;
    string s=j["teams"].dump(2);
    now.tA.teamID=j["teams"][0]["teamID"];
    now.tA.tilePoint=j["teams"][0]["tilePoint"];
    now.tA.areaPoint=j["teams"][0]["areaPoint"];
    now.tB.teamID=j["teams"][1]["teamID"];
    now.tB.tilePoint=j["teams"][1]["tilePoint"];
    now.tB.areaPoint=j["teams"][1]["areaPoint"];
    FOR (i,0,j["teams"][0]["agents"].size())
    {
        agent tmp;
        tmp.agentID=j["teams"][0]["agents"][i]["agentID"];
        tmp.x=j["teams"][0]["agents"][i]["x"];
        tmp.y=j["teams"][0]["agents"][i]["y"];
        now.tA.ag.push_back(tmp);
    }
    FOR (i,0,j["teams"][1]["agents"].size())
    {
        agent tmp;
        tmp.agentID=j["teams"][1]["agents"][i]["agentID"];
        tmp.x=j["teams"][1]["agents"][i]["x"];
        tmp.y=j["teams"][1]["agents"][i]["y"];
        now.tB.ag.push_back(tmp);
    }
    FOR(i,0,now.height)
    {
        vector<int>tmp;
        j["points"][i].get_to(tmp);
        now.points.push_back(tmp);
    }
    FOR(i,0,now.height)
    {
        vector<int>tmp;
        j["tiled"][i].get_to(tmp);
        now.tiled.push_back(tmp);
    }
    FOR(i,0,j["actions"].size())
    {
        action tmp;
        tmp.id=j["actions"][i]["agentID"];
        tmp.type=j["actions"][i]["type"];
        tmp.dx=j["actions"][i]["dx"];
        tmp.dy=j["actions"][i]["dy"];
        tmp.turn=j["actions"][i]["turn"];
        tmp.apply=j["actions"][i]["apply"];
        now.act.push_back(tmp);
    }
    ifs.close();
}
void writeOutput(vector<action> decide)
{
    out=
    {
        {"actions",{}},
    };
    FOR(i,0,decide.size())
    {
        /*auto text=R"(
        {
            "agentID" : 15,
            "type": "move",
            "dx": 15,
            "dy": 15
        }
        )";*/
 //       out["actions"].push_back(json::get_to<string>("{ \"agentID\": 15, \"type\": 15,\"dx\": 15,\"dy\": 15 }"));
        //out["actions"].push_back(json::parse(text));
      /*  out["actions"]="{ \"agentID\": 15, \"type\": 15,\"dx\": 15,\"dy\": 15 }"_json;
        string s;
        out["actions"].get_to(s);
        cout<<s<<endl;*/
        //out.push_back(json::object_t::value_type("agentID", 15));
        //string s="{ \"agentID\": 15, \"type\": 15,\"dx\": 15,\"dy\": 15 }";
        //out["actions"].get_to(s);
        //
        //out["actions"].push_back(json::object_t::value_type("xhree", 3));
        //out["actions"][i] += json::object_t::value_type("four", 4);
        out["actions"][i]["agentID"]=decide[i].id;
       // out["actions"][i] += json::object_t::value_type("four", 4);
        //out["actions"][i] += json::object_t::value_type("bour", 4);
        out["actions"][i]["type"]=decide[i].type;
        out["actions"][i]["dx"]=decide[i].dx;
        out["actions"][i]["dy"]=decide[i].dy;
    }
    ifs.open("decide.json",ios::out);
    cout<<std::setw(4)<<out;
    ifs.close();
}
action decideEachAgent(int& staX,int& staY, agent &Ag,match Map,int teamID)
{
    action decideOut;
    int dx_des,dy_des;
    if(staX<=2)dx_des=1;
    else
    {
        if((staX-2)%4==1)dx_des=-1;
        else dx_des=1;
    }
    if(staY%4==1)dy_des=-1;
    else dy_des=1;
    if(Ag.x+dx_des>Map.width || Ag.x+dx_des<1 )
    {
        return false;
    }
    else if( Ag.y+dy_des <1||Ag.y+dy_des>Map.height)
    {
        return false;
    }
    else if(Map.tiled[Ag.x+dx_des][Ag.y+dy_des]==0)
    {

        Ag.type="move";

        Ag.x+=dx_des;
        Ag.y+=dy_des;
        Ag.prevX=Ag.x;
        Ag.prevY=Ag.y;
        decideOut.type="move";
        decideOut.dx=dx_des;
        decideOut.dy=dy_des;
        decideOut.id=Ag.agentID;
        staX++;
        staY++;

    }
    else if(Map.tiled[Ag.x+dx_des][Ag.y+dy_des]==teamID)
    {
        bool trang=false;
        FOR(i,-1,2)
        {
            FOR(j,-1,2)
            {
                if(i==0 && j==0)continue;
                if(abs(i)==abs(j))continue;
                if(Map.tiled[Ag.x+i][Ag.y+j]==0)
                {

                    Ag.type="move";

                    Ag.x+=i;
                    Ag.y+=j;
                    Ag.prevX=Ag.x;
                    Ag.prevY=Ag.y;
                    decideOut.type="move";
                    decideOut.dx=i;
                    decideOut.dy=j;
                    decideOut.id=Ag.agentID;
                    trang=true;
                    break;
                }
            }
            if(trang)break;
        }
        if(!trang)
        {
            FOR(i,-1,2)
            {
                FOR(j,-1,2)
                {
                    if(i==0 && j==0)continue;
                    //if(abs(i)==abs(j))continue;
                    if(Map.tiled[Ag.x+i][Ag.y+j]==teamID)
                    {

                        Ag.type="move";

                        Ag.x+=i;
                        Ag.y+=j;
                        Ag.prevX=Ag.x;
                        Ag.prevY=Ag.y;
                        decideOut.type="move";
                        decideOut.dx=i;
                        decideOut.dy=j;
                        decideOut.id=Ag.agentID;
                        trang=true;
                        break;
                    }
                }
                if(trang)break;
            }
        }
        if(!trang)
        {
            /*if(Ag.prevX==Ag.x && Ag.prevY==Ag.Y)
            {
                Ag.type="remove";
                Ag.prevX=-1;
                Ag.prevY=-1;
                decideOut.type="remove"     ;
                decideOut.dx=-1;
                decideOut.dy=-1;
                decideOut.id=Ag.agentID;
            }
            else
            {
                FOR(i,-1,2)
                {
                    FOR(j,-1,2)
                    {
                        if(j<=Ag.prevX && i<=Ag.prevY)continue;
                        Ag.type="remove";
                        Ag.prevX=j;
                        Ag.prevY=i;
                        decideOut.type="remove"     ;
                        decideOut.dx=j;
                        decideOut.dy=i;
                        decideOut.id=Ag.agentID;
                        i=5;j=5;
                    }
                }
            }*/
            vector<pair<  >>>
            for((prevX,prevY)==vector[i])prevx, prev=vector[i+1];
        }
    }
    else
    {

        Ag.type="remove";
     //   Ag.x+=dx_des;
       // Ag.y+=dy_des;
        Ag.prevX=Ag.x;
        Ag.prevY=Ag.y;
        decideOut.type="remove";
        decideOut.dx=dx_des;
        decideOut.dy=dy_des;
        decideOut.id=Ag.agentID;
    }
    return decideOut;
}
void strategy2(int teamID,int numOfTurns)
{
    cout<<"Press enter to print output.json"<<endl;
    while(true)
    {
        char x;
        cin>>x;
        if(x=='\n')break;
    }
    readMap(1);
    int numOfAgent;
    vector<action>decision;
    static int staX[10];
    static int staY[10];
    FOR(i,0,10)staX[i]=1,staY[i]=1;

    if(teamID==now.tA.teamID)
    {
        numOfAgent=now.tA.ag.size();
        FOR(i,0,now.act.size())
        {
            if(now.act[i].apply==-1)
            {
                FOR()
            }
        }
    }
        FOR(i,0,numOfAgent)
        {
            decision.push_back(decideEachAgent2(staX[i],staY[i],now.tA.ag[i],now,teamID,numOfTurns));
        }
    }
    else
    {
        numOfAgent=now.tB.ag.size();
        FOR(i,0,numOfAgent)
        {
            decision.push_back(decideEachAgent2(staX[i],staY[i],now.tB.ag[i],now,teamID,numOfTurns));
        }
    }
    writeOutput(decision);
    strategy2(teamID);
}
void strategy1(int teamID)
{
    cout<<"Press enter to print output.json"<<endl;
    while(true)
    {
        char x;
        cin>>x;
        if(x=='\n')break;
    }
    int numOfAgent;
    vector<action>decision;
    static int staX[10];
    static int staY[10];
    FOR(i,0,10)staX[i]=1,staY[i]=1;
    if(teamID==now.tA.teamID)
    {
        numOfAgent=now.tA.ag.size();
        FOR(i,0,numOfAgent)
        {
            bool check=true;
            action tmp=decideEachAgent(staX[i],staY[i],now.tA.ag[i],now,teamID,check);
            if(check)decision.push_back(action);
            else
        {

            }
        }
    }
    else
    {
        numOfAgent=now.tB.ag.size();
        FOR(i,0,numOfAgent)
        {
            decision.push_back(decideEachAgent(staX[i],staY[i],now.tB.ag[i],now,teamID));
        }
    }

    writeOutput(decision);
    strategy1(teamID);
}
int main()
{
    readMap(0);
    vector<action> decide;
    action tmp;
    tmp.apply=5;
    tmp.dx=1;
    tmp.dy=2;
    tmp.id=3;
    tmp.turn=4;
    tmp.type="fdas";
    decide.push_back(tmp);
    decide.push_back(tmp);
    //writeOutput(decide);
    strategy1(5);
    return 0;
}
