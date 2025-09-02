# 题目信息

# Make Equal

## 题目描述

There are $ n $ containers of water lined up, numbered from left to right from $ 1 $ to $ n $ . Each container can hold any amount of water; initially, the $ i $ -th container contains $ a_i $ units of water. The sum of $ a_i $ is divisible by $ n $ .

You can apply the following operation any (possibly zero) number of times: pour any amount of water from the $ i $ -th container to the $ j $ -th container, where $ i $ must be less than $ j $ (i.e. $ i<j $ ). Any index can be chosen as $ i $ or $ j $ any number of times.

Determine whether it is possible to make the amount of water in all containers the same using this operation.

## 说明/提示

In the third test case of the example ( $ a=[4, 5, 2, 1, 3] $ ), you can proceed as follows:

- pour $ 1 $ unit of water from the first vessel to the fourth, then $ a=[3, 5, 2, 2, 3] $ ;
- pour $ 1 $ unit of water from the second vessel to the third, then $ a=[3, 4, 3, 2, 3] $ ;
- pour $ 1 $ unit of water from the second vessel to the fourth, then $ a=[3, 3, 3, 3, 3] $ .

## 样例 #1

### 输入

```
6
1
43
2
1 3
5
4 5 2 1 3
3
1 2 3
7
4 5 5 0 6 4 4
7
6 5 5 1 3 4 4```

### 输出

```
YES
NO
YES
NO
NO
YES```

# AI分析结果



### 题目翻译

# Make Equal

## 题目描述

有 $n$ 个容器排成一行，编号从左到右为 $1$ 到 $n$。每个容器可以装任意多的水，初始时第 $i$ 个容器装有 $a_i$ 单位水。所有容器中水的总量是 $n$ 的倍数。

你可以进行任意次（包括零次）如下操作：将任意量的水从第 $i$ 个容器倒入第 $j$ 个容器，要求 $i < j$。判断是否可以通过这些操作使所有容器中的水量相同。

---

### 题解综合分析与结论

**核心思路**：  
所有容器最终水量为平均值 $\text{avg} = \frac{\sum a_i}{n}$。从左到右遍历容器，维护一个累计变量（表示可用的盈余水量）。若当前容器水量超过 $\text{avg}$，盈余部分加入累计；若不足，则从累计中扣除缺口。若累计出现负数，说明无法满足条件。

**关键难点**：  
需确保每个容器的水量调整必须依赖左侧的盈余，不能预支右侧容器的水量。例如，若某容器需要补水，必须由之前容器的盈余提供，否则无法操作。

**最优技巧**：  
贪心策略 + 单次遍历。时间复杂度 $O(n)$，空间复杂度 $O(1)$。

---

### 精选题解（评分≥4星）

#### 题解1：RyanLi（⭐⭐⭐⭐⭐）
**亮点**：代码简洁，逻辑清晰，直接维护差值变量。
```cpp
#include <iostream>
using namespace std;
using ll = long long;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        ll sum = 0;
        for (int i=0; i<n; i++) {
            int x; cin >> x;
            sum += x;
        }
        ll avg = sum / n, diff = 0;
        bool ok = true;
        for (int i=0; i<n; i++) {
            int x; cin >> x;
            diff += x - avg;
            if (diff < 0) ok = false;
        }
        cout << (ok ? "YES" : "NO") << "\n";
    }
    return 0;
}
```
**核心思想**：遍历时计算每个容器与平均值的差，累加差值。若累计值出现负数，则无法满足条件。

---

#### 题解2：vectorxyz（⭐⭐⭐⭐）
**亮点**：变量命名清晰，逻辑与题解1一致，但更易理解。
```cpp
int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        ll sum = 0;
        for (auto &x : a) {
            cin >> x;
            sum += x;
        }
        ll avg = sum / n;
        ll spare = 0;
        bool ok = true;
        for (auto x : a) {
            if (x > avg) spare += x - avg;
            else if (spare < avg - x) { ok = false; break; }
            else spare -= (avg - x);
        }
        cout << (ok ? "YES" : "NO") << "\n";
    }
}
```
**核心思想**：使用 `spare` 变量存储盈余水量，明确分为多余和不足两种情况的处理。

---

### 关键思路总结
- **贪心策略**：从左到右遍历，确保每个容器的调整仅依赖左侧已处理的盈余。
- **累计差值**：维护一个累计变量记录可用的盈余水量，实时判断是否满足条件。

---

### 拓展与同类题目
**类似题目套路**：  
- 只能单向调整资源的问题（如分糖果、均分纸牌）。
- 需实时验证局部可行性的贪心问题。

**推荐练习**：  
1. [P1031 均分纸牌](https://www.luogu.com.cn/problem/P1031)  
2. [P701B Cells Not Under Attack](https://www.luogu.com.cn/problem/CF701B)  
3. [LeetCode 135. Candy](https://leetcode.com/problems/candy/)

---
处理用时：45.77秒