#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int a[100005];

    // 读取输入
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // 输出朋友数列
    for (int i = 0; i < n; ++i) {
        cout << -a[i] << " ";
    }
    cout << endl;

    return 0;
}
