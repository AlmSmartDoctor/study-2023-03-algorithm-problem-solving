#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


map<string, string> kingdoms;
// 토막상식: 종주국은 Suzerain, 속국은 Vassal 이라고 한다!

// 종주국 구하는 기능
string get_suzerain(string vassal)
{
    if (kingdoms[vassal] == vassal) return vassal;
    
    kingdoms[vassal] = get_suzerain(kingdoms[vassal]);
    return kingdoms[vassal];
    
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N, M;

    cin >> N >> M;
    
    // 왕국명 입력 받기
    string kingdom;
    getline(cin, kingdom);
    for (int i = 0; i < N; i++)
    {
        getline(cin, kingdom);
        kingdoms[kingdom] = kingdom;
    }


    for (int i = 0; i < M; i++)
    {
        string battle;
        getline(cin, battle);
        int first = battle.find(',');
        int second = battle.find_last_of(',');
        string first_kingdom = battle.substr(0, first);
        string second_kingdom = battle.substr(first + 1, second - first - 1);
        char result = battle[second + 1];
        if (result == 49)
        {
            // 속국이 종주국과 싸운 경우
            if (get_suzerain(first_kingdom) == second_kingdom) 
            {
                kingdoms[first_kingdom] = first_kingdom;
                kingdoms[second_kingdom] = first_kingdom;
            }
            else
            {
                kingdoms[get_suzerain(second_kingdom)] = get_suzerain(first_kingdom);
            }
        }
        else
        {
            // 속국이 종주국과 싸운 경우
            if (get_suzerain(second_kingdom) == first_kingdom)
            {
                kingdoms[second_kingdom] = second_kingdom;
                kingdoms[first_kingdom] = second_kingdom;
            }
            else
            {
                kingdoms[get_suzerain(first_kingdom)] = get_suzerain(second_kingdom);
            }
        }
    }
    
    vector<string> suzerains;
    for (auto kingdom : kingdoms)
    {
        if (kingdom.first == kingdoms[kingdom.first])
        {
            suzerains.push_back(kingdom.first);
        }
    }
    cout << suzerains.size() << "\n";
    for (int i = 0; i < suzerains.size(); i++)
    {
        cout << suzerains[i] << "\n";
    }
}
