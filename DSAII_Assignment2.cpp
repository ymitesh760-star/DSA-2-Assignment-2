// DSA-II Assignment 2: Sliding Window Technique
// C++17: reference and optimized solutions for both problems.
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
using namespace std;

long long maxSumBrute(const vector<int>& a, int k) {
    if (k < 1 || k > (int)a.size()) throw invalid_argument("Part A requires 1 <= K <= n.");
    long long best = a[0];
    for (int i = 0; i + k <= (int)a.size(); ++i) {
        long long sum = 0;
        for (int j = i; j < i + k; ++j) sum += a[j];
        best = (i == 0 ? sum : max(best, sum));
    }
    return best;
}
long long maxSumSliding(const vector<int>& a, int k) {
    if (k < 1 || k > (int)a.size()) throw invalid_argument("Part A requires 1 <= K <= n.");
    long long window = 0;
    for (int i = 0; i < k; ++i) window += a[i];
    long long best = window;
    for (int right = k; right < (int)a.size(); ++right) {
        window += a[right] - a[right-k];
        best = max(best, window);
    }
    return best;
}
struct WindowResult { int length, start, end; };
WindowResult longestBrute(const vector<int>& a, long long k) {
    if (k < 0) throw invalid_argument("Part B limit K must be non-negative.");
    for (int x : a) if (x < 0) throw invalid_argument("Part B requires non-negative array values.");
    WindowResult best{0, -1, -1};
    for (int left = 0; left < (int)a.size(); ++left) {
        long long sum = 0;
        for (int right = left; right < (int)a.size(); ++right) {
            sum += a[right];
            if (sum <= k && right-left+1 > best.length)
                best = {right-left+1, left, right};
        }
    }
    return best;
}
WindowResult longestSliding(const vector<int>& a, long long k) {
    if (k < 0) throw invalid_argument("Part B limit K must be non-negative.");
    for (int x : a) if (x < 0) throw invalid_argument("Part B requires non-negative array values.");
    int left = 0; long long sum = 0; WindowResult best{0, -1, -1};
    for (int right = 0; right < (int)a.size(); ++right) {
        sum += a[right];
        while (sum > k && left <= right) sum -= a[left++];
        int len = right-left+1;
        if (len > best.length) best = {len, left, right};
    }
    return best;
}
void show(const vector<int>& a, int k) {
    cout << "Array: [";
    for (int i=0;i<(int)a.size();++i) cout << (i?", ":"") << a[i];
    cout << "], K=" << k << " | brute=" << maxSumBrute(a,k)
         << " | sliding=" << maxSumSliding(a,k) << "\n";
}
void showB(const vector<int>& a, int k) {
    auto b=longestBrute(a,k), s=longestSliding(a,k);
    cout << "Array: [";
    for (int i=0;i<(int)a.size();++i) cout << (i?", ":"") << a[i];
    cout << "], limit=" << k << " | brute=(" << b.length << "," << b.start << "," << b.end
         << ") | sliding=(" << s.length << "," << s.start << "," << s.end << ")\n";
}
int main() {
    cout << "DSA-II Assignment 2: Sliding Window Technique\n\nPART A: Maximum sum of K consecutive elements\n";
    show({2,1,5,1,3,2},3); show({-4,-2,-7},2); show({6},1); show({1,2,3},3);
    cout << "\nPART B: Longest subarray with sum at most K (indices are 0-based)\n";
    showB({1,2,1,1,3},4); showB({5,1,1},2); showB({4,2,1},0); showB({0,0,1,0},1);
    return 0;
}
