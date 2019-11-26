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
};
struct team
{
    int teamID;
    vector<agent> A, B;
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
        now.tA.A.push_back(tmp);
        now.tB.A.push_back(tmp);
    }
    FOR (i,0,j["teams"][1]["agents"].size())
    {
        agent tmp;
        tmp.agentID=j["teams"][1]["agents"][i]["agentID"];
        tmp.x=j["teams"][1]["agents"][i]["x"];
        tmp.y=j["teams"][1]["agents"][i]["y"];
        now.tA.B.push_back(tmp);
        now.tB.B.push_back(tmp);
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
        out["actions"].push_back("{ \"agentID\": 15, \"type\": 15,\"dx\": 15,\"dy\": 15 }"_json);
        out["actions"][i]["agentID"]=decide[i].id;
        out["actions"][i]["type"]=decide[i].type;
        out["actions"][i]["dx"]=decide[i].dx;
        out["actions"][i]["dy"]=decide[i].dy;
    }
    ifs.open("decide.json",ios::out);
    ifs<<std::setw(4)<<out;
    ifs.close();
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
    writeOutput(decide);
    return 0;
}
