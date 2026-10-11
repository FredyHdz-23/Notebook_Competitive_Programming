#include <template.h>

vector<string> rot(const vector<string>& a) { // rota 90°
    int n = a.size(), m = a[0].size();
    vector<string> b(m, string(n, '#'));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            b[j][n - 1 - i] = a[i][j];
    return b;
}

vector<string> flip(vector<string> a) { // espejo horizontal
    for (auto& row : a) reverse(row.begin(), row.end());
    return a;
}