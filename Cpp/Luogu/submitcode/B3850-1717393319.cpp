#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string str;
        cin >> str;
        long long sum = 0;
        for (int j = str.length() - 1; j >= 0; j--) {
            int x = str[j] - '0';
            if ((str.length() - j) % 2 == 1) {  // 奇数位
                x *= 7;
                while (x > 9) {
                    x = x / 10 + x % 10;
                }
            }
            sum += x;
        }
        if (sum % 8 == 0) {
            cout << "T" << endl;
        } else {
            cout << "F" << endl;
        }
    }
    return 0;
}
