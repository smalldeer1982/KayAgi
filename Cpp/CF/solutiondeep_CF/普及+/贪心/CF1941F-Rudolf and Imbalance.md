# 题目信息

# Rudolf and Imbalance

## 题目描述

Rudolf has prepared a set of $ n $ problems with complexities $ a_1 < a_2 < a_3 < \dots < a_n $ . He is not entirely satisfied with the balance, so he wants to add at most one problem to fix it.

For this, Rudolf came up with $ m $ models of problems and $ k $ functions. The complexity of the $ i $ -th model is $ d_i $ , and the complexity of the $ j $ -th function is $ f_j $ . To create a problem, he selects values $ i $ and $ j $ ( $ 1 \le i \le m $ , $ 1 \le j \le k $ ) and by combining the $ i $ -th model with the $ j $ -th function, he obtains a new problem with complexity $ d_i + f_j $ (a new element is inserted into the array $ a $ ).

To determine the imbalance of the set, Rudolf sorts the complexities of the problems in ascending order and finds the largest value of $ a_i - a_{i - 1} $ ( $ i > 1 $ ).

What is the minimum value of imbalance that Rudolf can achieve by adding at most one problem, created according to the described rules?

## 样例 #1

### 输入

```
7
5 5 5
5 10 15 20 26
11 14 16 13 8
16 4 5 3 1
7 6 5
1 4 7 10 18 21 22
2 3 5 7 4 2
6 8 9 3 2
7 6 5
1 4 7 10 18 21 22
2 3 5 7 4 2
6 8 13 3 2
5 6 3
2 10 13 20 25
11 6 10 16 14 5
6 17 15
4 2 2
11 12 14 15
19 14
10 6
8 4 2
3 10 16 18 21 22 29 30
9 13 16 15
4 2
2 4 7
4 21
4 15 14 5
20 1 15 1 12 5 11```

### 输出

```
5
4
5
8
2
7
11```

# AI分析结果



### 题目内容重写（中文版）

# Rudolf 与问题平衡性

## 题目描述

Rudolf 准备了 $n$道难度递增的问题，复杂度满足 $a_1 < a_2 < \dots < a_n$。他认为当前的平衡性不够理想，希望通过添加最多一个新问题来改善。

他准备了 $m$ 个问题模型和 $k$ 个函数，第 $i$ 个模型的复杂度为 $d_i$，第 $j$ 个函数的复杂度为 $f_j$。通过组合模型和函数（即选择 $i$ 和 $j$）可以生成复杂度为 $d_i + f_j$ 的新问题。

不平衡值的定义为将问题复杂度排序后最大的相邻差值。求通过添加至多一个新问题后，能达到的最小不平衡值。

## 输入格式

多组测试数据。每组数据包含：
- 三个整数 $n, m, k$
- 递增的 $a$ 数组
- $m$ 个模型复杂度 $d$
- $k$ 个函数复杂度 $f$

## 输出格式

每组数据输出一个整数，表示最小可能的不平衡值。

---

### 题解综合分析

#### 核心思路
1. **预处理最大间隙**：首先在原数组中找出最大相邻差值区间 $[a_{left}, a_{right}]$ 和次大差值
2. **插入优化策略**：新问题应插入最大间隙区间，最优插入点为区间中点附近
3. **高效搜索算法**：对模型数组 $d$ 和函数数组 $f$ 排序后，使用二分/双指针寻找最接近中点的组合
4. **次大值约束**：最终答案需与次大差值比较取最大值

#### 最优解法特征
- **时间复杂度**：$O(n + (m+k)\log k)$ 预处理+双数组搜索
- **空间优化**：使用原地排序避免额外空间
- **边界处理**：正确处理多个最大间隙的特殊情况

---

### 高星题解推荐

#### 1. 题解作者：luobotianle（★★★★☆）
**关键亮点**：
- 精确锁定唯一最大间隙的优化场景
- 双二分法寻找最接近中点的组合
- 正确处理次大差值约束条件
```cpp
// 核心代码：双二分查找最优组合
ll tar = (a[ml] + a[mr]) >> 1;
for (int i = 1; i <= m; i++) {
    // 查找大于等于中点的最小组合
    ll now = merge1(1, k + 1, i, tar);
    if (now >= 1 && now <= k) update_answer();
    // 查找小于等于中点的最大组合
    now = merge2(1, k + 1, i, tar);
    if (now >= 1 && now <= k) update_answer();
}
```

#### 2. 题解作者：Ratio_Y（★★★★☆）
**关键亮点**：
- 利用 set 自动排序特性简化操作
- 结合 lower_bound 快速定位最优解
- 代码结构简洁高效
```cpp
// 核心代码：set与lower_bound结合
for (auto i : f) {
    auto dh = d.lower_bound((lb + rb) / 2 - i);
    ans = min(ans, max(*dh + i - lb, rb - *dh - i));
    if (dh != d.begin()) {
        dh--;
        ans = min(ans, max(*dh + i - lb, rb - *dh - i));
    }
}
```

#### 3. 题解作者：MrPython（★★★★☆）
**创新点**：
- 逆向思维使用二分答案框架
- 将问题转化为可行性判断问题
- 处理多间隙约束条件严谨
```cpp
// 核心二分框架
while (l < r) {
    int mid = (l + r) >> 1;
    if (check(mid)) r = mid;
    else l = mid + 1;
}
// 检查函数包含间隙分割验证
bool check(int x) {
    int cnt = 0;
    for (间隙验证) {
        if (需要分割) {
            if (超过分割次数) return false;
            验证是否存在可行组合
        }
    }
    return true;
}
```

---

### 关键优化技巧
1. **双数组排序预处理**：对 $d$ 和 $f$ 分别排序后，可以使用双指针/二分法快速定位
2. **中点逼近策略**：最优插入点必然出现在最大间隙的中点附近，缩小搜索范围
3. **次大值约束优化**：最终答案只需关注最大间隙优化后的值与原次大值

---

### 相似题目推荐
1. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094) - 双指针贪心策略
2. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678) - 二分答案经典题
3. [P1182 数列分段 II](https://www.luogu.com.cn/problem/P1182) - 最大最小值问题

---

### 调试经验总结
1. **数据类型陷阱**：多个题解强调使用 `long long` 防止溢出（如 __vector__ 的罚时教训）
2. **去重优化**：littlebug 题解通过 `unique` 去重减少无效计算
3. **边界验证**：必须验证插入值确实在目标区间内（如 haokee 的区间判断）
4. **次大值遗漏**：部分题解未正确处理多个最大间隙情况导致 WA

---
处理用时：54.24秒