# 题目信息

# Too Min Too Max

## 题目描述

Given an array $ a $ of $ n $ elements, find the maximum value of the expression:

 $ $$$|a_i - a_j| + |a_j - a_k| + |a_k - a_l| + |a_l - a_i| $ $ </p><p>where  $ i $ ,  $ j $ ,  $ k $ , and  $ l $  are four <span class="tex-font-style-bf">distinct</span> indices of the array  $ a $ , with  $ 1 \\le i, j, k, l \\le n $ .</p><p>Here  $ |x| $  denotes the absolute value of  $ x$$$.

## 说明/提示

In the first test case, for any selection of $ i $ , $ j $ , $ k $ , $ l $ , the answer will be $ 0 $ . For example, $ |a_1 - a_2| + |a_2 - a_3| + |a_3 - a_4| + |a_4 - a_1| = |1 - 1| + |1 - 1| + |1 - 1| + |1 - 1| = 0 + 0 + 0 + 0 = 0 $ .

In the second test case, for $ i = 1 $ , $ j = 3 $ , $ k = 2 $ , and $ l = 5 $ , the answer will be $ 6 $ . $ |a_1 - a_3| + |a_3 - a_2| + |a_2 - a_5| + |a_5 - a_1| = |1 - 2| + |2 - 1| + |1 - 3| + |3 - 1| = 1 + 1 + 2 + 2 = 6 $ .

## 样例 #1

### 输入

```
5
4
1 1 1 1
5
1 1 2 2 3
8
5 1 3 2 -3 -1 10 3
4
3 3 1 1
4
1 2 2 -1```

### 输出

```
0
6
38
8
8```

# AI分析结果



# Too Min Too Max

## 题目描述

给定一个包含 $n$ 个元素的数组 $a$，找出四个不同的下标 $i, j, k, l$，使得表达式：

$$|a_i - a_j| + |a_j - a_k| + |a_k - a_l| + |a_l - a_i|$$

的值最大化。其中 $|x|$ 表示 $x$ 的绝对值。

## 说明/提示

在第一个测试用例中，所有元素相同，无论选择哪四个下标，结果均为 0。例如：$|1-1| + |1-1| + |1-1| + |1-1| = 0$。

在第二个测试用例中，选择 $i=1, j=3, k=2, l=5$ 时结果为 6：$|1-2| + |2-1| + |1-3| + |3-1| = 1+1+2+2 = 6$。

---

## 题解分析与结论

### 关键思路
将问题转化为寻找数组中的极值组合。经过数学推导可知，当选取最大的两个元素和最小的两个元素时，表达式可简化为 **2×(最大两数之和 - 最小两数之和)**。这一思路通过极值间的差值最大化总和的绝对值之和。

### 算法步骤
1. **排序数组**，便于快速获取最大和最小元素。
2. **取最大两个元素和最小两个元素**，计算其组合的总和。

### 复杂度
- 时间复杂度：$O(n \log n)$（排序时间复杂度）
- 空间复杂度：$O(1)$（原地排序）

---

## 精选题解

### 题解（5星）
**关键亮点**：  
- 利用极值特性简化问题，推导出直接公式。  
- 代码简洁高效，仅需排序后计算极值组合。

**核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        sort(a.begin(), a.end());
        int ans = 2 * (a[n-1] + a[n-2] - a[0] - a[1]);
        cout << ans << endl;
    }
    return 0;
}
```

**实现思想**：  
排序数组后，直接取首尾各两个元素计算最大值。公式 `2*(max1 + max2 - min1 - min2)` 来源于表达式在极值组合下的对称性推导。

---

## 拓展与练习

### 类似题型
1. **洛谷 P1094**：纪念品分组（贪心选择极值配对）
2. **洛谷 P1102**：最大差值（极值差问题）
3. **洛谷 P1031**：均分纸牌（极值平衡思想）

### 心得总结
- **极值优先**：在涉及绝对值的最大化问题中，优先考虑极值的组合。  
- **公式推导**：通过数学简化避免暴力枚举，显著提升效率。

---
处理用时：119.71秒