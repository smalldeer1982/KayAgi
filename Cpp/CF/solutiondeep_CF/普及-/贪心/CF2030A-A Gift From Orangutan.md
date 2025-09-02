# 题目信息

# A Gift From Orangutan

## 题目描述

在丛林探险的时候，你遇到了一只罕见的戴着领结的猩猩！你和猩猩握了握手并给了它一些食物和水。作为回报……

猩猩给了你一个长度为 $n$ 的数组 $a$。通过数组 $a$ 你将会以下列的方式构造两个长度都为 $n$ 的数组 $b$ 和 $c$：

* $b_i = \text{min}(a_1,a_2,…,a_i),1 \le i \le n$。  
* $c_i = \text{max}(a_1,a_2,…,a_i),1 \le i \le n$。

定义 $a$ 的得分为 $\sum^n_{i=1} c_i-b_i$。在你计算分数之前，你可以任意修改 $a$ 中元素的顺序。

你需要求出可以获得的最高得分。

## 说明/提示

对于第一组数据，没有其他方法来重新排列 $a$，所以，$b=[69]$ 并且 $c=[69]$。唯一可能的得分为 $69-69=0$。

对于第二组数据，可以将 $a$ 重新排列为 $[7,5,6]$。这样，$b=[7,5,5]$ 并且 $c=[7,7,7]$。这种情况下的得分为 $(7-7)+(7-5)+(7-5)=4$。可以证明，这是可能的最高分数。

翻译来自 [Jason_Ming](https://www.luogu.com.cn/user/1014421)。

## 样例 #1

### 输入

```
3
1
69
3
7 6 5
5
1 1 1 2 2```

### 输出

```
0
4
4```

# AI分析结果



# A Gift From Orangutan

## 题目描述

在丛林探险时，你遇到了一只罕见的戴着领结的猩猩！你和猩猩握了握手并给了它一些食物和水。作为回报……

猩猩给了你一个长度为 $n$ 的数组 $a$。通过数组 $a$ 你将构造两个长度都为 $n$ 的数组 $b$ 和 $c$：

* $b_i = \min(a_1,a_2,…,a_i), \quad 1 \le i \le n$  
* $c_i = \max(a_1,a_2,…,a_i), \quad 1 \le i \le n$

定义 $a$ 的得分为 $\sum_{i=1}^n (c_i - b_i)$。在计算分数前，你可以任意修改 $a$ 中元素的顺序。需要求出可以获得的最高得分。

---

## 题解分析与结论

### 关键思路
最优解的得分为 `(数组最大值 - 数组最小值) × (n-1)`。无论数组如何排列，只要保证第一个元素是最大值，第二个元素是最小值，后续所有位置的贡献均为最大值与最小值的差。这使得总和最大化。

### 算法实现
1. 计算数组的最大值 `max_val` 和最小值 `min_val`
2. 若数组长度为 1，返回 0
3. 否则返回 `(max_val - min_val) * (n-1)`

### 代码示例
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        if (n == 1) {
            cout << 0 << endl;
            continue;
        }
        int max_val = *max_element(a.begin(), a.end());
        int min_val = *min_element(a.begin(), a.end());
        cout << (max_val - min_val) * 1LL * (n - 1) << endl;
    }
}
```

---

## 举一反三
1. **贪心极值应用**：本题核心在于通过极值构造最优解，类似问题如[CF1768B Quick Sort](https://www.luogu.com.cn/problem/CF1768B)
2. **前缀极值性质**：涉及前缀最大/最小值的题目，例如[P2947 Look Up](https://www.luogu.com.cn/problem/P2947)
3. **极值差分问题**：极值差与数组长度的组合问题，例如[P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)

---
处理用时：68.32秒