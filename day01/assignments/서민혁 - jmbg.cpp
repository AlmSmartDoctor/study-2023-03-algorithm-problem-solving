#include <string>
#include <iomanip>
#include <utility>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <stdint.h>
#include <inttypes.h>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <regex>
#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <queue>
using namespace std;
typedef long long ll;
char pattern[20];


vector<ll> control_date(19, 0);
vector<int> days, months, years;
vector<int> days_in_month {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
void get_days()
{
    for (int i = 1; i <= 31; i++)
    {
        if (pattern[0] == 'X')
        {
            if (pattern[1] == 'X')
            {
                days.push_back(i);
                continue;
            }
            else if (i % 10 == pattern[1] - '0')
            {
                days.push_back(i);
                continue;
            }
        }
        else if (pattern[1] == 'X')
        {
            if (pattern[0] - '0' == i / 10)
            {
                days.push_back(i);
                continue;
            }
        }
        else
        {
            if (pattern[0] - '0' == i / 10 && pattern[1] - '0' == i % 10)
            {
                days.push_back(i);
            }
        }
    }
}
void get_months()
{
    for (int i = 1; i <= 12; i++)
    {
        if (pattern[2] == 'X')
        {
            if (pattern[3] == 'X')
            {
                months.push_back(i);
                continue;
            }
            else if (i % 10 == pattern[3] - '0')
            {
                months.push_back(i);
                continue;
            }
        }
        else if (pattern[3] == 'X')
        {
            if (pattern[2] - '0' == i / 10)
            {
                months.push_back(i);
                continue;
            }
        }
        else
        {
            if (pattern[2] - '0' == i / 10 && pattern[3] - '0' == i % 10)
            {
                months.push_back(i);
            }
        }
    }
}
void get_years()
{
    for (int i = 0; i < 10; i++)
        if (pattern[4] == 'X' || pattern[4] - '0' == i)
            for (int j = 0; j < 10; j++)
                if (pattern[5] == 'X' || pattern[5] - '0' == j)
                    for (int k = 0; k < 10; k++)
                        if (pattern[6] == 'X' || pattern[6] - '0' == k)
                            for (int l = 0; l < 10; l++)
                                if (pattern[7] == 'X' || pattern[7] - '0' == l)
                                    if (i + j + k + l != 0)
                                        years.push_back(i * 1000 + j * 100 + k * 10 + l);
}
int last_day_of_month(int year, int month)
{
    if (month != 2) return days_in_month[month];
    else
    {
        if (year % 400 == 0) return 29;
        else if (year % 100 == 0) return 28;
        else if (year % 4 == 0) return 29;
        else return 28;
    }

}
void get_date_possibilities()
{
    days.push_back(32);
    for (int i = 0; i < years.size(); i++)
    {
        int control_years = ((years[i] / 1000) * 6 + ((years[i] / 100) % 10) * 5 + ((years[i] / 10) % 10) * 4 + (years[i] % 10) * 3);
        for (int j = 0; j < months.size(); j++)
        {
            int control_months = ((months[j] / 10) * 8 + (months[j] % 10) * 7);
            for (int k = 0; days[k] <= last_day_of_month(years[i], months[j]); k++)
            {
                control_date[
                    ((days[k] / 10) * 10 + (days[k] % 10) * 9 + control_months + control_years) % 19
                ] += 1;
            }
        }
    }
}


vector<ll> control_arbitrary(19, 0);
void get_arbitrary_possibilities()
{
    vector<int> multiplier {0, 2, 10, 9, 8, 7, 6, 5, 4, 3, 2};
    vector<vector<ll>> arbitrary(11, vector<ll>(19, 0));
    arbitrary[0][0] = 1;
    for (int i = 1; i <= 10; i++)
    {
        for (int j = 0; j <= 9; j++)
        {
            if (pattern[i + 7] == 'X' || pattern[i + 7] - '0' == j)
            {
                for (int k = 0; k < 19; k++)
                {
                    arbitrary[i][(k + j * multiplier[i]) % 19] += arbitrary[i - 1][k];
                }
            }
        }
    }

    for (int i = 0; i < 19; i++)
    {
        control_arbitrary[i] = arbitrary[10][i];
    }
}
vector<ll> control(10, 0);
void get_combined_possibilities()
{
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            if ((i + j) % 19 <= 9)
            {
                control[(i + j) % 19] += control_date[i] * control_arbitrary[j];
            }
            else
            {
                control[19 - (i + j) % 19] += control_date[i] * control_arbitrary[j];
            }
        }
    }
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> pattern;
    // 주어진 패턴에서 가능한 일자를 구한다
    get_days();

    // 주어진 패턴에서 가능한 월을 구한다
    get_months();

    // 주어진 패턴에서 가능한 년도를 구한다
    get_years();

    // 위에서 구한 days, months, years 를 통해서 앞 8자리에 가능한 경우의 수 구한다
    // control number 제약 조건을 맞추기 위해서 19 로 나눈 나머지에 따라 분리해서 저장
    // 1 ~ 8 번째 자리까지의 경우의 수
    get_date_possibilities();

    // 주어진 패턴을 제외하고는 제약조건이 없는 자리에 대해서 경우의 수를 구한다
    // 마찬가지로 control number 제약 조건을 맞추기 위해서 19로 나눈 나머지에 따라 분리해서 저장
    // dynamic programming 활용
    // 9 ~ 18 번째 자리까지의 경우의 수
    get_arbitrary_possibilities();


    // 위에서 구한 두가지 벡터로 뒤에 control number 에 따라 나올 수 있는 합산된 경우의 수
    get_combined_possibilities();


    // 마지막 control number 가 X 면 모든 경우가 가능하므로 다 합쳐서 출력
    // X 가 아닌 경우 해당 경우에서 나올 수 있는 경우의 수만 출력
    if (pattern[18] == 'X')
    {
        ll sum = 0;
        for (int i = 0; i < 10; i++)
        {
            sum += control[i];
        }
        cout << sum;
    }
    else
    {
        cout << control[pattern[18] - '0'];
    }
}