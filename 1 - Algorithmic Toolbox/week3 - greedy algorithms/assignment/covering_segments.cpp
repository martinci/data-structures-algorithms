#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using std::vector;

struct Segment {
    int start, end;
};

int find_samallest_end(vector<Segment> &segments) {
    int min_end = segments[0].end;
    for (auto &seg : segments) {
        if (seg.end < min_end) {
            min_end = seg.end;
        }
    }
    return min_end;
}

vector<Segment> purge(vector<Segment> &segments, int &min_end) {
    vector<Segment> new_segments;
    for (auto seg : segments) {
        if (seg.start > min_end) {
            new_segments.push_back(seg);
        }
    }
    return new_segments;
}

vector<int> optimal_points(vector<Segment> &segments) {
    vector<int> points;
    // The first point is on the smallest end. Then we can repeat with remaining segments.
    while (not segments.empty()) {
        int min_end = find_samallest_end(segments);
        points.push_back(min_end);
        segments = purge(segments, min_end);
    }
    return points;
}

int main() {
    int n;
    std::cin >> n;
    vector<Segment> segments(n);
    for (size_t i = 0; i < segments.size(); ++i) {
        std::cin >> segments[i].start >> segments[i].end;
    }
    vector<int> points = optimal_points(segments);
    std::cout << points.size() << "\n";
    for (size_t i = 0; i < points.size(); ++i) {
        std::cout << points[i] << " ";
    }
    // std::cin >> n;
}
