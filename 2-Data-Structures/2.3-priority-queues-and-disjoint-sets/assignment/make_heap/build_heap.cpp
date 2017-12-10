#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
  private:
    vector<int> _data;
    vector<pair<int, int>> _swaps;

    void WriteResponse() const {
        cout << _swaps.size() << "\n";
        for (int i = 0; i < _swaps.size(); ++i) {
            cout << _swaps[i].first << " " << _swaps[i].second << "\n";
        }
    }

    void ReadData() {
        int n;
        cin >> n;
        _data.resize(n);
        for (int i = 0; i < n; ++i)
            cin >> _data[i];
    }

    int GetMinChild(int idx) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        if (left >= _data.size()) {
            return idx;
        } else if (right >= _data.size()) {
            return left;
        } else {
            return _data[left] < _data[right] ? left : right;
        }
    }

    void SiftDown(int idx) {
        int val = _data[idx];
        int min_child = GetMinChild(idx);
        while (_data[min_child] < val) {
            _swaps.push_back(make_pair(idx, min_child));
            _data[idx] = _data[min_child];
            _data[min_child] = val;
            idx = min_child;
            min_child = GetMinChild(idx);
        }
    }

    void GenerateSwaps() {
        _swaps.clear();
        for (int i = (int)_data.size() / 2; i >= 0; i--) {
            SiftDown(i);
        }
    }

  public:
    void Solve() {
        ReadData();
        GenerateSwaps();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    HeapBuilder heap_builder;
    heap_builder.Solve();
    // int n;
    // cin >> n;
    return 0;
}
