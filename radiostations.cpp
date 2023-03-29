#include <iostream>
#include <stdio.h>
#include <set>
#include <cstring>
#include <vector>

using namespace std;

struct station
{
    string name;
    set <string> states_covered;
};

void states_init(set <string> *states);
void stations_init(vector <struct station> &stations);

int main()
{
    set <string> states_needed;
    set <string> final_stations;
    int stations_numb = 5;
    vector <struct station> stations(stations_numb);

    states_init(&states_needed);
    stations_init(stations);

    set <string> states_covered;
    int best_station;

    vector <string> covered;
    while(!states_needed.empty())
    {
        for(int i = 0; i < stations_numb; i++)
        {
            covered.clear();
            set_intersection(states_needed.begin(), states_needed.end(),
                            stations[i].states_covered.begin(), stations[i].states_covered.end(),
                            back_inserter(covered));

            if(covered.size() > states_covered.size())
            {
                best_station = i;
                states_covered.clear();
                for(int z = 0; z < covered.size(); z++)
                    states_covered.insert(covered[z]);
            }
        }

        final_stations.insert(stations[best_station].name);
        while(!states_covered.empty())
        {
            states_needed.erase(*states_covered.begin());
            states_covered.erase(states_covered.begin());
        }
    }
    
    for(set<string>::iterator it = final_stations.begin(); it != final_stations.end(); it++)
        cout << *it << "\n";
    return 0;
}

void states_init(set <string> *states)
{
    states->insert("mt");
    states->insert("wa");
    states->insert("or");
    states->insert("id");
    states->insert("nv");
    states->insert("ut");
    states->insert("ca");
    states->insert("az");
}

void stations_init(vector <struct station> &stations)
{
    stations[0].name = "kone";
    stations[0].states_covered.insert("id");
    stations[0].states_covered.insert("nv");
    stations[0].states_covered.insert("ut");

    stations[1].name = "ktwo";
    stations[1].states_covered.insert("wa");
    stations[1].states_covered.insert("id");
    stations[1].states_covered.insert("mt");

    stations[2].name = "kthree";
    stations[2].states_covered.insert("or");
    stations[2].states_covered.insert("nv");
    stations[2].states_covered.insert("ca");

    stations[3].name = "kfour";
    stations[3].states_covered.insert("nv");
    stations[3].states_covered.insert("ut");
    
    stations[4].name = "kfive";
    stations[4].states_covered.insert("ca");
    stations[4].states_covered.insert("az");
}