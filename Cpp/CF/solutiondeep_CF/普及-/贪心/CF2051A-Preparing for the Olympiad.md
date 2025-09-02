# 题目信息

# Preparing for the Olympiad

## 题目描述

Monocarp 和 Stereocarp正在准备奥林匹克。现在仅剩 $ n $ 天奥林匹克就要开始了。在这第 $ i $天，如果Monocarp 准备训练，那么他将完成$ a_i $题，同样的，如果Stereocarp也在这天准备训练，那么他将完成$ b_i $题。

Monocarp 可以在任意一天进行训练，然而，Stereocarp在观察他，并且学习他的计划：如果Monocarp在第$ i $（$ i<n $）天进行训练,那么Stereocarp将在第（$i+1$）天进行训练。

Monocarp想要制定一个计划使得他与Stereocarp的训练题目量相差最大。形式化的：Monocarp想要使（$m-s$）的值最大，其中$m$表示他完成的题目量，$s$表示Stereocarp完成的题目量s是立体果解决的问题数。帮助Monocarp确定他们之间解决问题数量的最大可能差。

## 说明/提示

在第一个测试用例中，Monocarp最好两天都训练；然后Stereocarp将在第二天训练

在第二个测试用例中，Monocarp最好在唯一一天训练，Stereocarp根本不会训练。

在第三个测试用例中，Monocarp最好在最后一天训练（而且只在当天）。

在第四个测试用例中，Monocarp最好在几天内训练1,3,4,6; 然后Stereocarp将训练2,4,5天

## 样例 #1

### 输入

```
4
2
3 2
2 1
1
5
8
3
1 1 1
2 2 2
6
8 2 5 6 2 6
8 2 7 4 3 4```

### 输出

```
4
5
1
16```

# AI分析结果



# Preparing for the Olympiad

## 题目描述

Monocarp 和 Stereocarp 正在为奥林匹克竞赛做准备。现在距离奥林匹克开始仅剩 $n$ 天。在第 $i$ 天，如果 Monocarp 选择训练，他将解决 $a_i$ 道题；如果 Stereocarp 在该天训练，他将解决 $b_i$ 道题。

Monocarp 可以任意选择训练天数，但 Stereocarp 会根据 Monocarp 的选择进行训练：如果 Monocarp 在第 $i$ 天（$i < n$）训练，那么 Stereocarp 将在第 $i+1$ 天训练。

Monocarp 希望制定一个训练计划，使得他与 Stereocarp 的解题数量差最大化。具体来说，他希望最大化 $(m - s)$，其中 $m$ 是 Monocarp 的解题总数，$s$ 是 Stereocarp 的解题总数。请帮助 Monocarp 确定这个最大差值。

## 说明/提示

- 样例 1：Monocarp 两天都训练，Stereocarp 在第二天训练
- 样例 2：Monocarp 在唯一一天训练，Stereocarp 不训练
- 样例 3：Monocarp 只在最后一天训练
- 样例 4：Monocarp 选择第 1、3、4、6 天训练，Stereocarp 在 2、4、5 天训练

## 样例 #1

### 输入
```
4
2
3 2
2 1
1
5
8
3
1 1 1
2 2 2
6
8 2 5 6 2 6
8 2 7 4 3 4
```

### 输出
```
4
5
1
16
```

---

### 解题分析与结论

#### 关键思路
每个训练日 $i$ 的收益为 $a_i$，代价是若 $i < n$ 则需扣除 Stereocarp 在 $i+1$ 天的解题数 $b_{i+1}$。贪心策略：计算每个天数 $i$ 的净收益 $c_i = a_i - (i < n ? b_{i+1} : 0)$，累加所有正净收益的天数。

#### 算法优化
将复杂的选择问题转化为单日决策的贪心问题。通过预处理每个训练日的净收益，直接筛选出所有正收益的天数，时间复杂度 $O(n)$。

#### 解决难点
发现 Stereocarp 的训练天数完全由 Monocarp 的选择决定，且各天选择相互独立，从而将问题简化为独立的单日决策。

---

### 题解代码

```cpp
#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int a[n + 2], b[n + 2]; // 1-based索引
        for (int i = 1; i <= n; ++i) cin >> a[i];
        for (int i = 1; i <= n; ++i) cin >> b[i];
        
        long long sum = 0;
        for (int i = 1; i <= n; ++i) {
            int cost = (i < n) ? b[i + 1] : 0;
            int val = a[i] - cost;
            if (val > 0) sum += val;
        }
        cout << sum << endl;
    }
    return 0;
}
```

#### 代码要点
- **1-based索引** 处理天数与题目输入的对应关系
- **单次遍历计算净收益**，仅需判断 $i < n$ 时的 $b_{i+1}$
- **累加正收益**，直接得到最大差值

---

### 拓展应用
1. **贪心选择独立性问题**：如 LeetCode 122. 买卖股票的最佳时机 II
2. **条件收益计算**：如 CF 1526C2. Potions (Hard Version)
3. **动态规划替代思路**：当选择具有依赖关系时需考虑

### 推荐练习
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心策略
2. [P1208 混合牛奶](https://www.luogu.com.cn/problem/P1208) - 选择最优单价
3. [P4995 跳跳！](https://www.luogu.com.cn/problem/P4995) - 贪心排序

---
处理用时：213.41秒