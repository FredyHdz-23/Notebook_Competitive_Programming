// d[i]: radio (contando el centro) del palíndromo en t = "#s0#s1#...#" centrado en i
// el palíndromo correspondiente en s tiene largo d[i] - 1
#include <template.h>

vi manacher(const string &s) {
    string t = "#";
    for (char c : s) t += c, t += '#';
    int n = sz(t); vi d(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        d[i] = i > r ? 1 : min(d[l + r - i], r - i + 1);
        while (i - d[i] >= 0 && i + d[i] < n && t[i - d[i]] == t[i + d[i]]) d[i]++;
        if (i + d[i] - 1 > r) l = i - d[i] + 1, r = i + d[i] - 1;
    }
    return d;
}