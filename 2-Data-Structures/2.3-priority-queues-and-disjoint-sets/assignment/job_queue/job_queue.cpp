#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;

struct Worker {
    int id;
    long long next_free_time;
};

class WorkerHeap {
  private:
    vector<Worker> _workers;

    bool _compare(Worker a, Worker b) {
        if (a.next_free_time != b.next_free_time) {
            return a.next_free_time < b.next_free_time;
        }
        return a.id < b.id;
    }

    int _get_min_child(int idx) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        if (left >= _workers.size()) {
            return idx;
        } else if (right >= _workers.size()) {
            return left;
        } else {
            return _compare(_workers[left], _workers[right]) ? left : right;
        }
    }

    void _bubble_down(int idx) {
        Worker worker = _workers[idx];
        int min_child_idx = _get_min_child(idx);
        Worker min_child = _workers[min_child_idx];
        while (_compare(min_child, worker)) {
            // Swap workers
            _workers[idx] = min_child;
            _workers[min_child_idx] = worker;
            idx = min_child_idx;
            min_child_idx = _get_min_child(idx);
            min_child = _workers[min_child_idx];
        }
    }

  public:
    void initialize(int size) {
        _workers.resize(size);
        for (int i = 0; i < size; ++i) {
            _workers[i].id = i;
            _workers[i].next_free_time = 0;
        }
    }

    std::pair<int, long long> process(int duration) {
        auto &worker = _workers[0];
        int id = worker.id;
        long long start_time = worker.next_free_time;
        // Equivalent to change priority in a min heap
        worker.next_free_time += duration;
        _bubble_down(0);
        return {id, start_time};
    }
};

class JobQueue {
  private:
    int _num_workers;
    vector<int> _jobs;
    WorkerHeap _worker_heap;

    vector<int> _assigned_workers;
    vector<long long> _start_times;

    void WriteResponse() const {
        for (int i = 0; i < _jobs.size(); ++i) {
            cout << _assigned_workers[i] << " " << _start_times[i] << "\n";
        }
    }

    void ReadData() {
        int m;
        cin >> _num_workers >> m;
        // Initialize worker min heap.
        _worker_heap.initialize(_num_workers);
        _jobs.resize(m);
        for (int i = 0; i < m; ++i)
            cin >> _jobs[i];
    }

    void AssignJobs() {
        _assigned_workers.resize(_jobs.size());
        _start_times.resize(_jobs.size());
        for (int i = 0; i < _jobs.size(); ++i) {
            int duration = _jobs[i];
            auto result = _worker_heap.process(duration);
            _assigned_workers[i] = result.first;
            _start_times[i] = result.second;
        }
    }

  public:
    void Solve() {
        ReadData();
        AssignJobs();
        WriteResponse();
    }
};

int main() {
    JobQueue job_queue;
    job_queue.Solve();
    return 0;
}
