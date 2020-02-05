#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<int> prefix(std::string s) {
    int n = s.length();
    std::vector<int> p(n);

    for (int i = 1; i < n; ++i) {
        int cur_idx = i - 1;
        while (p[cur_idx] > 0 && s[p[cur_idx]] != s[i]) {
            cur_idx = p[cur_idx] - 1;
        }
        p[i] = p[cur_idx] + (s[p[cur_idx]] == s[i]);
    }
    return p;
}

std::vector<int> z_func(std::string s) {
    int n = s.length();
    std::vector<int> z(n);
    int l = 0;
    int r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r)
            z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int main() {
    std::string sub = "";
    std::string s = "";

    std::cin >> sub;
    std::cin >> s;

    int n = s.length();
    int m = sub.length();

    std::vector<int> z = z_func(sub);
    int l = 0;
    int r = 0;

    for (int i = 0; i < n; i++) {
        int cur = 0;
        if (i <= r)
            cur = std::min(r - i + 1, z[i - l]);
        while (i + cur < n && sub[cur] == s[i + cur])
            ++cur;
        if (i + cur - 1 > r) {
            l = i;
            r = i + cur - 1;
        }
        if (cur == m) {
            std::cout << i << " ";
        }
    }

    return 0;
}
