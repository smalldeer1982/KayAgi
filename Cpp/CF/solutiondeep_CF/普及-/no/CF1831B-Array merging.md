# 题目信息

# Array merging

## 题目描述

给定两个长度为 $n$ 的数组 $a$ 和 $b$。

猫猫让你合并这些数组，形成另一个长度为 $2n$ 的数组 $c$。你需要找到所有 $c$ 中元素值相同的子串长度的最大值。


合并过程是：每次选择任一非空数组中的第一个元素，将其添加到 $c$ 的末尾后从原数组中删除，这样的操作进行 $2n$ 次，直到两个数组都为空为止。

## 样例 #1

### 输入

```
4
1
2
2
3
1 2 3
4 5 6
2
1 2
2 1
5
1 2 2 2 2
2 1 1 1 1```

### 输出

```
2
1
2
5```

# AI分析结果

### 题目分类
贪心

### 综合分析与结论
这些题解的核心思路基本一致，都是基于贪心策略。由于原数组中不相邻的元素合并后也不相邻，相邻元素合并后可以相邻，所以对于每个数，分别统计其在两个数组中最长连续出现的次数，然后将对应次数相加，最后取最大值即为答案。

各题解的主要区别在于代码实现细节和优化方式，如输入方式（`cin`、快读、`scanf`）、数组清空（`memset` 或手动清零）、答案更新时机等。

### 所选题解
- **作者：Untitled10032 (4星)**
  - **关键亮点**：思路清晰，代码结构良好，使用 `get` 函数封装统计最长连续子串长度的逻辑，提高了代码的复用性。
  - **个人心得**：无

### 重点代码
```cpp
#include <iostream>
#include <cstring>

using namespace std;
constexpr int N = 2e5 + 5;
int ca[N * 2], cb[N * 2];

void get(int n, int *bucket) {
    memset(bucket, 0, sizeof(int) * (n * 2 + 3));
    int last = 0, cnt = 0;
    for (int i = 1; i <= n; i++) {
        int temp;
        cin >> temp;
        if (temp == last)
            cnt++;
        else {
            bucket[last] = max(bucket[last], cnt);
            last = temp;
            cnt = 1;
        }
    }
    bucket[last] = max(bucket[last], cnt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        get(n, ca);
        get(n, cb);
        int ans = 0;
        for (int i = 1; i <= (n << 1); i++)
            ans = max(ans, ca[i] + cb[i]);
        cout << ans << '\n';
    }
    return 0;
}
```
**核心实现思想**：`get` 函数用于统计一个数组中每个数的最长连续子串长度，存储在 `bucket` 数组中。在 `main` 函数中，分别对两个数组调用 `get` 函数，然后遍历所有可能的数，将对应最长连续子串长度相加，取最大值即为答案。

### 最优关键思路或技巧
- **贪心策略**：利用原数组中元素相邻关系的性质，将每个数在两个数组中的最长连续子串长度相加，得到合并后该数的最长连续子串长度，最后取最大值。
- **桶数组**：使用桶数组存储每个数的最长连续子串长度，方便统计和计算。

### 可拓展之处
同类型题或类似算法套路：
- 合并多个数组，求合并后数组中满足特定条件的子串或子数组的最值问题。
- 处理多个序列的合并问题，需要考虑元素的顺序和相邻关系。

### 推荐题目
- [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

### 个人心得摘录与总结
- **slzx_CPS**：做题时错了三次，发现用 `memset` 清零可能超时，要注意数组处理时最后一个连续子数组也要再处理一次，数组范围不要开太小。
- **xkcdjerry**：送分题吃了 3 发罚时，原因是没有考虑到可能有些 `a` 中出现的值 `b` 中不会出现，但这些值可能是最大结果，所以在统计 `a` 数组时也要更新答案。 

---
处理用时：26.70秒