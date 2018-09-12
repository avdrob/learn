#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void process_jobs(const vector<unsigned long long> &process_time, int n)
{
    vector<unsigned long long> finish_times(n);
    auto cmp = [&finish_times](int i, int j)
    {
        if (finish_times[i] != finish_times[j]) {
            return finish_times[i] > finish_times[j];
        }
        else {
            return i > j;
        }
    };
    priority_queue<int, vector<int>, decltype(cmp)> pqueue(cmp);

    for (int i = 0; i < n; i++) {
        pqueue.push(i);
    }

    for (int job_time : process_time) {
        int thr_id = pqueue.top();
        cout << thr_id << ' ' << finish_times[thr_id] << endl;
        finish_times[thr_id] += job_time;
        pqueue.pop();
        pqueue.push(thr_id);
    }
}

int main(int argc, char *argv[])
{
    int n, m;
    cin >> n >> m;

    vector<unsigned long long> process_time(m);
    for (int i = 0; i < m; i++) {
        cin >> process_time[i];
    }

    process_jobs(process_time, n);
    return 0;
}