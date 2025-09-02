#include <bits/stdc++.h>
using namespace std;

int n, k, a[100005];

// 判断能否通过给定长度 length 切割出至少 k 段木材
bool can_cut(int length) {
    long long count = 0;  // 计算总共能切割出来的段数
    for (int i = 1; i <= n; i++) {
        count += a[i] / length;  // 计算每根木头可以切出多少段
        if (count >= k) return true;  // 如果已经超过 k 段，提前返回
    }
    return count >= k;
}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);  // 读取每根木材的长度
    }

    // 手动查找数组 a 中的最大元素，作为二分查找的右边界
    int left = 1;
    int right = 0;  // 初始化为 0，表示没有找到最大值前

    for (int i = 1; i <= n; i++) {
        if (a[i] > right) {
            right = a[i];  // 更新最大值
        }
    }

    int result = 0;  // 存储最后的结果

    // 二分查找最大长度
    while (left <= right) {
        int mid = (left + right) / 2;
        if (can_cut(mid)) {
            result = mid;  // mid 是可行的，尝试更大的长度
            left = mid + 1;  // 尝试更大的木段长度
        } else {
            right = mid - 1;  // mid 不可行，尝试更短的木段长度
        }
    }

    cout << result << endl;  // 输出最大木段长度
    return 0;
}

