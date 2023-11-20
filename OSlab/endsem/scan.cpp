#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int head, n, seek_time = 0;
    int requests[100];

    cout << "Enter number of requests: ";
    cin >> n;

    cout << "Enter requests: ";
    for (int i = 0; i < n; i++) {
        cin >> requests[i];
    }

    cout << "Enter initial head position: ";
    cin >> head;

    requests[n] = 0;
    requests[n + 1] = 199;
    n += 2;

    sort(requests, requests + n);

    int init_index = 0;
    for (int i = 0; i < n; i++) {
        if (requests[i] == head) {
            init_index = i;
            break;
        }
    }

    cout << "Path: ";
    for (int i = init_index; i < n - 1; i++) {
        cout << requests[i] << " ";
        seek_time += abs(requests[i] - requests[i + 1]);
    }

    for (int i = init_index - 1; i >= 0; i--) {
        cout << requests[i] << " ";
        seek_time += abs(requests[i] - requests[i + 1]);
    }
    cout << endl;

    cout << "Total seek time: " << seek_time << endl;

    return 0;
}