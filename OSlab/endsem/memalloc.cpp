#include <bits/stdc++.h>
using namespace std;

void bestfit(vector<int> b, vector<int> p)
{
    vector<int> allocation(p.size(), -1);
    for (int i = 0; i < p.size(); i++)
    {
        int in = -1;
        for (int j = 0; j < b.size(); j++)
        {
            if (b[j] >= p[i])
            {
                if (in == -1)
                    in = j;
                else if (b[j] < b[in])
                    in = j;
            }
        }
        if (in != -1)
        {
            allocation[i] = in;
            b[in] -= p[i];
        }
    }
    for (int i = 0; i < p.size(); i++)
    {
        cout << i + 1 << "\t" << p[i] << "\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1 << endl;
        else
            cout << "Not allocated" << endl;
    }
}
void worstfit(vector<int> b, vector<int> p)
{
    vector<int> allocation(p.size(), -1);
    for (int i = 0; i < p.size(); i++)
    {
        int in = -1;
        for (int j = 0; j < b.size(); j++)
        {
            if (b[j] >= p[i])
            {
                if (in == -1)
                    in = j;
                else if (b[j] > b[in]) // only line diff from best fit
                    in = j;
            }
        }
        if (in != -1)
        {
            allocation[i] = in;
            b[in] -= p[i];
        }
    }
    for (int i = 0; i < p.size(); i++)
    {
        cout << i + 1 << "\t" << p[i] << "\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1 << endl;
        else
            cout << "Not allocated" << endl;
    }
}

void firstfit(vector<int> b, vector<int> p)
{
    vector<int> allocation(p.size(), -1);
    for (int i = 0; i < p.size(); i++)
    {
        for (int j = 0; j < b.size(); j++)
        {
            if (b[j] >= p[i])
            {
                allocation[i] = j;
                b[j] -= p[i];
                break;
            }
        }
    }
    for (int i = 0; i < p.size(); i++)
    {
        cout << i + 1 << "\t" << p[i] << "\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1 << endl;
        else
            cout << "Not allocated" << endl;
    }
}
int main()
{
    vector<int> blocks = {100, 600, 500, 200, 300};
    vector<int> processes = {212, 417, 112, 426};
    bestfit(blocks, processes);
}