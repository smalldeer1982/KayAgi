#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<string> b(n), c(n), d(n), e(n);

    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i] >> c[i] >> d[i] >> e[i];
    }

    for (int i = 0; i < n; ++i) {
        int result;
        if (b[i] == "km" && e[i] == "m") {
            result = a[i] * 1000;
        } else if (b[i] == "km" && e[i] == "mm") {
            result = a[i] * 1000000;
        } else if (b[i] == "m" && e[i] == "mm") {
            result = a[i] * 1000;
        } else if (b[i] == "kg" && e[i] == "g") {
            result = a[i] * 1000;
        } else if (b[i] == "kg" && e[i] == "mg") {
            result = a[i] * 1000000;
        } else if (b[i] == "g" && e[i] == "mg") {
            result = a[i] * 1000;
        } else {
            continue; // 如果没有匹配的条件，跳过当前迭代
        }
        // 更新转换结果
        d[i] = to_string(result);

        cout << a[i] << " " << b[i] << " " << c[i] << " " << d[i] << " " << e[i] << endl;
    }
    return 0;
}
