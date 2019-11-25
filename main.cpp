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
    int **points;
    int startedAtUnixTime;
    int turn;
    int **tiled;
    team tA, tB;
    action A, B;
};
match now;
void readMap(int i)
{
    fstream ifs;
    ifs.open("fieldInfo_turn"+to_string(i)+".json",ios::in);
    ifs>>j;
    now.width=j["width"];
    now.height=j["height"];
    now.startedAtUnixTime=j["startedAtUnixTime"];
    now.turn=j["turn"];
    int ind=0;
    //j["teams"].get_to(now.te);
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
   // cout<<s;
    for (json::iterator it = j["teams"].begin(); it != j["teams"].end(); ++it) {
        //std::cout << it["agents"] << '\n';
 //       cout<<*it<<endl;

        //string s=*it;
        //cout<<s<<endl;
    }

    //now
//    cout<<now.tA.teamID;
}
int main()
{
    readMap(0);

    return 0;
}
