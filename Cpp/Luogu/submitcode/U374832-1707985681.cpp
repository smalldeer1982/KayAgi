#include <bits/stdc++.h>
using namespace std;

int main() {
    int L, R;
    cin >> L >> R;
    int count = 0;

    for (int a = 0; (1LL << a) <= R && a <= 30; ++a) {
        for (int b = 0; pow(3, b) <= R && b <= 19; ++b) {
            for (int c = 0; pow(5, c) <= R && c <= 13; ++c) {
                for (int d = 0; pow(7, d) <= R && d <= 11; ++d) {
                    long long val = 1LL * pow(2, a) * pow(3, b) * pow(5, c) * pow(7, d);
                    if (val >= L && val <= R) {
                        ++count;
                    }
                    if (val > R) break; // 当前值已超出R，无需继续计算更大的d
                }
                if (pow(2, a) * pow(3, b) * pow(5, c) > R) break; // 优化退出条件
            }
            if (pow(2, a) * pow(3, b) > R) break; // 进一步优化退出条件
        }
        if (pow(2, a) > R) break; // 最外层循环的退出条件
    }

    cout << count << endl;
    return 0;
}
