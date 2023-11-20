#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int head, start, end, n, seek_time = 0;
    int requests[100], path[100];

    cout << "Enter number of requests: ";
    cin >> n;

    cout << "Enter requests: ";
    for (int i = 0; i < n; i++) {
        cin >> requests[i];
    }

    cout << "Enter initial head position: ";
    cin >> head;

    cout << "Enter start and end positions of disk: ";
    cin >> start >> end;

    requests[n] = start;
    requests[n + 1] = end;
    n += 2;

    sort(requests, requests + n);

    int init_index = find(requests, requests + n, head) - requests;

    int path_index = 0;
    path[path_index++] = head;
    for (int i = init_index + 1; i < n; i++) {
        seek_time += abs(requests[i] - requests[i - 1]);
        path[path_index++] = requests[i];
    }

    seek_time += abs(requests[n - 2] - requests[init_index - 1]);

    for (int i = init_index - 1; i >= 0; i--) {
        seek_time += abs(requests[i] - requests[i + 1]);
        path[path_index++] = requests[i];
    }

    cout << "Path: ";
    for (int i = 0; i < path_index; i++) {
        cout << path[i] << " ";
    }
    cout << endl;

    cout << "Total seek time: " << seek_time << endl;

    return 0;
}