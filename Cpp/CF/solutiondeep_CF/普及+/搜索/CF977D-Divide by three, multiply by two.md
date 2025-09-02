# 题目信息

# Divide by three, multiply by two

## 题目描述

有一个长度为 $n$ 的数列 $a_i$，要求你将这个数列重排成一个排列 $p_i$，使得对于任意的 $p_i(1 \le i < n)$：



- $p_i \times 2 = p_{i+1}$，或者

- 当 $p_i$ 可以被 $3$ 整除时，$p_i \div 3 = p_{i+1}$。



保证答案存在。

## 说明/提示

在第一个样例中，一种可能的合法排列为 $[9,3,6,12,4,8]$。

## 样例 #1

### 输入

```
6
4 8 6 3 12 9
```

### 输出

```
9 3 6 12 4 8 
```

## 样例 #2

### 输入

```
4
42 28 84 126
```

### 输出

```
126 42 84 28 
```

## 样例 #3

### 输入

```
2
1000000000000000000 3000000000000000000
```

### 输出

```
3000000000000000000 1000000000000000000 
```

# AI分析结果



### 中文重述题目
有一个长度为 $n$ 的数列 $a_i$，要求将其重排为排列 $p_i$，使得对于任意相邻元素满足以下条件之一：
1. $p_i \times 2 = p_{i+1}$
2. 当 $p_i$ 能被3整除时，$p_i \div 3 = p_{i+1}$

保证答案存在。

---

### 题解对比与结论
#### 关键思路总结
**最优解法**：通过分析每个数的3因子个数进行排序。具体策略：
1. 计算每个数中3的因子个数（除以3直到无法整除的次数）
2. 按3因子个数降序排序，若相同则按数值升序排列
3. 直接输出排序后的序列即为合法排列

**核心数学观察**：
- 每次除以3会减少3的因子数，而乘2不影响3的因子数
- 3因子数多的数必须排在链的前端，形成递减的结构
- 相同3因子数时，升序排列保证乘2连接的可行性

#### 高分题解推荐
1. **yuzhechuan的排序法**（⭐⭐⭐⭐⭐）
   - **亮点**：时间复杂度O(n log n)，代码极简，数学分析深刻
   - **核心代码**：
     ```cpp
     struct STR { long long a,b; }; // a存原数，b存3因子数
     sort(A+1, A+n+1, [](STR m, STR n) {
         return m.b != n.b ? m.b > n.b : m.a < n.a;
     });
     ```

2. **Islauso的拓扑排序法**（⭐⭐⭐⭐）
   - **亮点**：通用图论思路，严谨证明无环性，适用于复杂规则场景
   - **核心代码**：
     ```cpp
     // 建图规则：检查每个数是否能作为前驱
     if (a[i]*2 == a[j] || (a[i]%3==0 && a[i]/3 == a[j])) 
         add_edge(i, j);
     // 拓扑排序输出路径
     ```

3. **Tweetuzki的最长路动态规划法**（⭐⭐⭐⭐）
   - **亮点**：结合拓扑排序与DP记录路径，可扩展性强
   - **核心技巧**：用map快速查找可能的后继节点，DP转移时记录前驱

---

### 代码实现示例（排序法）
```cpp
#include <bits/stdc++.h>
using namespace std;

struct Node { 
    long long val; 
    int cnt3; 
};

int main() {
    int n;
    cin >> n;
    vector<Node> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i].val;
        long long x = arr[i].val;
        arr[i].cnt3 = 0;
        while (x % 3 == 0) x /= 3, arr[i].cnt3++;
    }
    
    sort(arr.begin(), arr.end(), [](const Node& a, const Node& b) {
        return a.cnt3 != b.cnt3 ? a.cnt3 > b.cnt3 : a.val < b.val;
    });
    
    for (auto& node : arr) cout << node.val << " ";
}
```

---

### 类似题目推荐
1. [CF977D](https://codeforces.com/problemset/problem/977/D)（本题原型）
2. [洛谷P1098 字符串的展开](https://www.luogu.com.cn/problem/P1098)（分层次处理）
3. [洛谷P1496 火烧赤壁](https://www.luogu.com.cn/problem/P1496)（区间排序与连接）
4. [CF1148C 奇偶排序](https://codeforces.com/problemset/problem/1148/C)（基于数值特性的排序）

---
处理用时：98.30秒