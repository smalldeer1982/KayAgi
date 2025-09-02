#include <bits/stdc++.h>
using namespace std;

int main() {
    int L, R;
    cin >> L >> R; // 输入区间[L, R]
    int count = 0; // 用于计数区间内奇妙数的数量

    // 主要优化在于枚举a, b, c, d的范围，根据R值动态调整
    for (int a = 0; (1LL << a) <= R && a <= 30; ++a) { // 优化1：使用位移计算2^a，限制a的最大值以避免无效计算
        for (int b = 0; pow(3, b) <= R && b <= 19; ++b) { // 优化2：限制b的最大值，避免计算超出R的值
            for (int c = 0; pow(5, c) <= R && c <= 13; ++c) { // 优化3：限制c的最大值，避免无效计算
                for (int d = 0; pow(7, d) <= R && d <= 11; ++d) { // 优化4：限制d的最大值，减少迭代次数
                    long long val = 1LL * pow(2, a) * pow(3, b) * pow(5, c) * pow(7, d); // 计算当前的奇妙数
                    if (val >= L && val <= R) { // 判断是否在区间内
                        ++count; // 在区间内则计数增加
                    }
                    if (val > R) break; // 如果当前值已经超过R，后续的d无需再计算
                }
                if (pow(2, a) * pow(3, b) * pow(5, c) > R) break; // 如果a, b, c组合已超R，后续的c无需计算
            }
            if (pow(2, a) * pow(3, b) > R) break; // 如果a, b组合已超R，后续的b无需计算
        }
        if (pow(2, a) > R) break; // 如果2^a已超R，后续的a无需计算
    }

    cout << count << endl; // 输出区间内奇妙数的数量
    return 0;
}