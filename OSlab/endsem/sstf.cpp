#include<iostream>
#include<cstdlib>
#include<cmath>

using namespace std;

int main()
{
    int n,head,seek_time=0,min=0;
    cout<<"Enter the number of requests: ";
    cin>>n;
    int requests[n],visited[n];
    cout<<"Enter the requests: ";
    for(int i=0;i<n;i++)
    {
        cin>>requests[i];
        visited[i]=0;
    }
    cout<<"Enter the initial head position: ";
    cin>>head;
    cout<<head<<"->";
    visited[min]=1;
    for(int j=1;j<n;j++)
    {
        for(int i=0;i<n;i++)
        {
            if(visited[i]==0)
            {
                min=i;
                break;
            }
        }
        for(int i=0;i<n;i++)
        {
            if(abs(requests[i]-head)<abs(requests[min]-head) && visited[i]==0)
            {
                min=i;
            }
        }
        visited[min]=1;
        seek_time+=abs(requests[min]-head);
        head=requests[min];
        cout<<head<<"->";
    }
    cout<<"Total seek time: "<<seek_time;
    return 0;
}