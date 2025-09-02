#include <bits/stdc++.h>
using namespace std;
int n, a[55];
struct data {
    int len, s[505];
    data() {
        memset(s, 0, sizeof(s));
        len = 1;
    }
    void init() {
        len = 500;

        for (int i = 1; i <= 500; i++) {
            s[i] = 9;
        }
    }
    data operator +(const data A) {
        data B;
        B.len = max(len, A.len);

        for (int i = 1; i <= B.len; i++) {
            B.s[i] += A.s[i] + s[i];
            B.s[i + 1] += B.s[i] / 10;
            B.s[i] = B.s[i] % 10;
        }

        if (B.s[B.len + 1]) {
            B.len++;
        }

        return B;
    }
    bool operator <(const data A) {
        if (len != A.len) {
            return len < A.len;
        }

        for (int i = len; i >= 1; i--) {
            if (s[i] != A.s[i]) {
                return s[i] < A.s[i];
            }
        }

        return false;
    }
    data operator *(const data A) {
        data B;
        B.len = len + A.len - 1;

        for (int i = 1; i <= A.len; i++) {
            for (int j = 1; j <= len; j++) {
                B.s[i + j - 1] += A.s[i] * s[j];
                B.s[i + j] += B.s[i + j - 1] / 10;
                B.s[i + j - 1] %= 10;
            }
        }

        if (B.s[B.len + 1]) {
            B.len++;
        }

        return B;
    }
    void write() {
        for (int i = len; i >= 1; i--) {
            printf("%d", s[i]);
        }
    }
} dp[55][55];
data change(int x) {
    data t;
    int cnt = 0;

    while (x) {
        t.s[++cnt] = x % 10, x /= 10;
    }

    t.len = cnt;
    return t;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int t = 2; t <= n - 1; t++) {
        for (int i = 1; i <= n - t; i++) {
            int j = i + t;
            dp[i][j].init();

            for (int k = i + 1; k <= j - 1; k++) {
                data t = change(a[i]) * change(a[j]) * change(a[k]);
                data tp = dp[i][k] + dp[k][j] + t;

                if (tp < dp[i][j]) {
                    dp[i][j] = tp;
                }
            }
        }
    }

    dp[1][n].write();
    return 0;
}