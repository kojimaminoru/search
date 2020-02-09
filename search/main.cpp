#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include "picojson.h"
using namespace std;

//class s_json{
//
//};

typedef struct agents{
    int agentID;
    int x;
    int y;
}agents;

typedef struct teams{
    int teamID;
    agents agent[8];
    int agcount;
    int tilePoint;
    int areaPoint;
}teams;

int main(int argc, const char * argv[]) {
    std::ifstream ifs("/Users/poisoned/all/search/search/field_turn0.json", ios::in);
    if (ifs.fail()) {
        cerr << "failed" << endl;
        return 1;
    }
    
    const string json((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
    picojson::value s_json;
    const string err = picojson::parse(s_json, json);
    if (err.empty() == false) {
        std::cerr << err << std::endl;
        return 2;
    }
    picojson::object& obj = s_json.get<picojson::object>();
    
    const int wth = obj["width"].get<double>(), hgh = obj["height"].get<double>();
    vector<vector<int>> field(wth, vector<int>(hgh));
    cout << "width : " << wth << endl;
    cout << "height : " << hgh << endl;
    picojson::array points = obj["points"].get<picojson::array>();
    for(int j = 0; j < hgh; j++){
        picojson::array pointss = points[j].get<picojson::array>();
        for (int i = 0; i < wth; i++) {
            field[j][i] = pointss[i].get<double>();
            cout << field[j][i] << " ";
        }
        cout << endl;
    }
    int turn = obj["turn"].get<double>();
    cout << endl << "turn : " << turn << endl;
    vector<vector<int>> tiled(wth, vector<int>(hgh));
    picojson::array tiles = obj["tiled"].get<picojson::array>();
    for(int j = 0; j < hgh; j++){
        picojson::array tiless = tiles[j].get<picojson::array>();
        for (int i = 0; i < wth; i++) {
            tiled[j][i] = tiless[i].get<double>();
            cout << tiled[j][i] << " ";
        }
        cout << endl;
    }
    
    teams team[2];
    picojson::array tm = obj["teams"].get<picojson::array>();
    int i = 0, is = 0;
    for (picojson::array::iterator it = tm.begin(); it != tm.end(); it++){
        is = 0;
        picojson::object& o = it->get<picojson::object>();
        picojson::array ag = o["agents"].get<picojson::array>();
        for (picojson::array::iterator its = ag.begin(); its != ag.end(); its++){
            picojson::object& e = its->get<picojson::object>();
            team[i].agent[is].agentID = e["agentID"].get<double>();
            team[i].agent[is].x = e["x"].get<double>();
            team[i].agent[is].y = e["y"].get<double>();
            is++;
        }
        team[i].agcount = is;
        team[i].teamID = o["teamID"].get<double>();
        team[i].tilePoint = o["tilePoint"].get<double>();
        team[i].areaPoint = o["areaPoint"].get<double>();
        i++;
    }
    for(int i = 0; i < 2; i++){
        cout << endl << "team" << i << " : " << endl;
        cout << "\tteamID : " << team[i].teamID << endl;
        cout << "\t" << team[i].agcount << "agents : " << endl;
        for(int j = 0; j < team[i].agcount; j++){
            cout << "\t\tagentID : " << team[i].agent[j].agentID << endl;
            cout << "\t\tx : " << team[i].agent[j].x << endl;
            cout << "\t\ty : " << team[i].agent[j].y << endl << endl;
        }
        cout << "\ttilePoint : " << team[i].tilePoint << endl;
        cout << "\tareaPoint : " << team[i].areaPoint << endl << endl;
    }
    return 0;
}
