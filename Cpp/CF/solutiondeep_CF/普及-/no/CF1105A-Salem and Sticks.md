# 题目信息

# Salem and Sticks

## 题目描述

## 题目概述
$Salem$ 给了你 $n$ 个木棍，它们的长度分别为 $a_1,a_2,\cdot \cdot \cdot a_n$。

对于每一根木棍，你可以把它的长度变为任意整数（即收缩或者拉伸）。把一根木棍的长度 $a$ 变为 $b$ 将花费 $|a-b|$ 的价格。

如果说一根木棍对于整数 $t$ 是好的，则需要满足要求 $|a_i - t| \leq 1$。

现在 $Salem$ 让你去改变一些木棍的长度（可能全部或不改变），使所有木棍对于整数 $t$ 是好的，并让花费的价格尽可能小，$t$ 的值不是固定的值，您可以让它成为任意正整数。

现在请你输出 $t$ 的值和最小花费的价格。如果有多种情况，请输出任意一个。

## 说明/提示

对于第一个样例，我们可以把长度为 $1$ 的木棍变成 $2$，长度为 $10$ 的木棍变成 $4$，将花费 $|1-2|+|10-4|=1+6=7$ 的价格，最终长度 $[2,4,4]$ 是适合 $t=3$ 的。

对于第二个样例，我们不需要作出任何改变，所有木棍对于 $t=2$ 都是好的。

## 样例 #1

### 输入

```
3
10 1 4
```

### 输出

```
3 7
```

## 样例 #2

### 输入

```
5
1 1 2 2 3
```

### 输出

```
2 0
```

# AI分析结果



### 题目翻译
#### Salem and Sticks

**题目描述**  
Salem 给了你 $n$ 个木棍，它们的长度分别为 $a_1, a_2, \dots, a_n$。  
你可以改变每个木棍的长度为任意整数，改变长度为 $a$ 到 $b$ 的花费为 $|a - b|$。  
若一个木棍的长度为 $b$ 且满足 $|b - t| \leq 1$，则称它对整数 $t$ 是好的。  
你的任务是找到一个整数 $t$，使得所有木棍经过调整后都是好的，且总花费最小。输出任意一个满足条件的 $t$ 及对应的最小花费。

**样例解释**  
第一个样例中，将木棍调整为 $[2,4,4]$，$t=3$，总花费为 $7$。第二个样例中，所有木棍已经对 $t=2$ 是好的，无需调整。

---

### 算法分类
**枚举**

---

### 题解分析与结论

#### 核心思路
1. **暴力枚举所有可能的 $t$ 值**：由于 $a_i$ 的范围较小（1 ≤ $a_i$ ≤ 1000），直接枚举 $t$ 的候选范围（如 1 到 1000）。
2. **计算每个 $t$ 的最小总成本**：对于每个 $t$，若 $a_i$ 不在 $[t-1, t+1]$ 内，将其调整到最近端点，总成本为 $\sum \max(|a_i - t| - 1, 0)$。

#### 解决难点
- **正确枚举范围**：需覆盖所有可能的 $t$ 值，例如原题数据范围中 $a_i$ 最大为 1000，因此枚举到 1000 或更高。
- **高效计算成本**：通过数学推导，将调整成本简化为 $\max(|a_i - t| - 1, 0)$，避免复杂判断。

---

### 精选题解

#### 1. Lovely_Elaina（5星）
**关键亮点**  
- 枚举范围覆盖 1 到 1000，确保所有可能的最优解被覆盖。
- 通过直接判断 $a_i$ 是否在区间内，逻辑清晰，代码简洁。

```cpp
#include<iostream>
#include <bits/stdc++.h>
using namespace std;

int a[105], t, mi;

int main() {
    mi = 100000;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int k = 1; k <= 1000; k++) {
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            if (k-1 <= a[i] && a[i] <= k+1) continue;
            sum += (a[i] < k-1 ? k-1 - a[i] : a[i] - (k+1));
        }
        if (sum < mi) mi = sum, t = k;
    }
    printf("%d %d\n", t, mi);
    return 0;
}
```

#### 2. ssSSSss_sunhaojia（5星）
**关键亮点**  
- 枚举到 1000，覆盖所有可能的最优解。
- 直接分类讨论 $a_i$ 与 $t$ 的大小关系，计算方式直观。

```cpp
#include <bits/stdc++.h>
using namespace std;

long long n, a[1100], sum, mis = 1e14, miid; 

int main() {
    cin >> n; 
    for (int i = 1; i <= n; i++) cin >> a[i]; 
    for (int t = 1; t <= 1000; t++) {
        sum = 0; 
        for (int j = 1; j <= n; j++) {
           if (a[j] > t) sum += a[j] - (t + 1); 
           else if (a[j] < t) sum += (t - 1) - a[j]; 
        }
        if (sum < mis) mis = sum, miid = t;
    }
    cout << miid << " " << mis;
    return 0; 
}
```

#### 3. guozhetao（4星）
**关键亮点**  
- 封装计算函数，提高代码可读性。
- 枚举到 1000，覆盖正确范围。

```cpp
#include<bits/stdc++.h>
using namespace std;

int n, a[1005], ans1 = 0, ans2 = 1e9;

int find(int t) {
    int ans = 0;
    for (int i = 1; i <= n; i++) 
        if (abs(a[i] - t) > 1) ans += abs(a[i] - t) - 1;
    return ans;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int t = 1; t <= 1000; t++) {
        int cost = find(t);
        if (cost < ans2) ans1 = t, ans2 = cost;
    }
    printf("%d %d", ans1, ans2);
}
```

---

### 关键思路总结
- **暴力枚举**：数据范围小时，枚举所有可能的候选值。
- **数学优化**：利用区间特性将成本计算简化为 $\max(|a_i - t| - 1, 0)$。

---

### 拓展练习
1. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)（二分答案）
2. [P1217 回文质数](https://www.luogu.com.cn/problem/P1217)（枚举与质数判断）
3. [CF977B Two-gram](https://codeforces.com/problemset/problem/977/B)（字符串枚举）

---
处理用时：319.21秒