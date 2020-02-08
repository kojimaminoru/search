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
    return 0;
}
