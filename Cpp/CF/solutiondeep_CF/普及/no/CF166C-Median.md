# 题目信息

# Median

## 题目描述

A median in an array with the length of $ n $ is an element which occupies position number ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF166C/a3cce6c26f6207c41846eedd0e6a59cdcc521015.png) after we sort the elements in the non-decreasing order (the array elements are numbered starting with $ 1 $ ). A median of an array $ (2,6,1,2,3) $ is the number $ 2 $ , and a median of array $ (0,96,17,23) $ — the number $ 17 $ .

We define an expression ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF166C/ff48225f7f772c08409f2d464b02c44cf20620e2.png) as the integer part of dividing number $ a $ by number $ b $ .

One day Vasya showed Petya an array consisting of $ n $ integers and suggested finding the array's median. Petya didn't even look at the array and said that it equals $ x $ . Petya is a very honest boy, so he decided to add several numbers to the given array so that the median of the resulting array would be equal to $ x $ .

Petya can add any integers from $ 1 $ to $ 10^{5} $ to the array, including the same numbers. Of course, he can add nothing to the array. If a number is added multiple times, then we should consider it the number of times it occurs. It is not allowed to delete of change initial numbers of the array.

While Petya is busy distracting Vasya, your task is to find the minimum number of elements he will need.

## 说明/提示

In the first sample we can add number $ 9 $ to array $ (10,20,30) $ . The resulting array $ (9,10,20,30) $ will have a median in position ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF166C/087e5fa70c281cf5e7b5f392e766cd46089615e4.png), that is, $ 10 $ .

In the second sample you should add numbers $ 4 $ , $ 5 $ , $ 5 $ , $ 5 $ . The resulting array has median equal to $ 4 $ .

## 样例 #1

### 输入

```
3 10
10 20 30
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 4
1 2 3
```

### 输出

```
4
```

# AI分析结果



## 中位数

### 题目描述
给定一个长度为 $n$ 的数组，定义中位数为排序后位于 $\lfloor \frac{n+1}{2} \rfloor$ 位置的元素。现需向数组中添加最少数量的元素（仅允许添加 $1$ 到 $10^5$ 的整数），使得指定值 $x$ 成为新数组的中位数。

### 输入样例
#### 样例1
输入：
3 10
10 20 30
输出：
1

#### 样例2
输入：
3 4
1 2 3
输出：
4

---

### 算法分类
**排序**、**贪心**

---

## 题解综合分析

### 关键思路总结
1. **预处理排序**：将原数组排序以确定元素位置关系。
2. **存在性检查**：若目标值 $x$ 不在数组中，强制添加至少一个 $x$。
3. **位置分析**：计算 $x$ 在排序数组中的位置区间，通过数学推导确定最少添加次数。
4. **边界调整**：当原数组中 $x$ 的位置无法满足中位数条件时，通过添加 $x$ 调整左右元素数量差。

### 最优题解推荐

#### 题解1：飞啾6373（4星）
**亮点**：通过遍历每个等于 $x$ 的位置计算最小调整次数，利用绝对值差优化计算逻辑。
```cpp
int main() {
    int n, k, ans = 0;
    cin >> n >> k;
    vector<int> a(n+1);
    bool exist = false;
    for (int i=1; i<=n; i++) {
        cin >> a[i];
        if (a[i] == k) exist = true;
    }
    if (!exist) { a[++n] = k; ans = 1; }
    sort(a.begin()+1, a.end());
    
    int min_add = INT_MAX;
    for (int i=1; i<=n; i++) {
        if (a[i] != k) continue;
        int left = i-1, right = n-i;
        int diff = abs(left - right);
        if (left < right) diff--;
        min_add = min(min_add, diff);
    }
    cout << ans + min_add;
}
```

#### 题解2：Lucifer_Bartholomew（4星）
**亮点**：利用 `lower_bound` 和 `upper_bound` 快速定位区间，通过逐步添加元素模拟中位数变化。
```cpp
int main() {
    int n, k, ans = 0;
    scanf("%d%d", &n, &k);
    vector<int> a(n);
    for (int &x : a) scanf("%d", &x);
    sort(a.begin(), a.end());
    
    int l = lower_bound(a.begin(), a.end(), k) - a.begin();
    int r = upper_bound(a.begin(), a.end(), k) - a.begin();
    int mid_pos = (n-1)/2;
    
    while (mid_pos < l || mid_pos >= r) {
        ans++;
        r++; // 视为添加一个k
        mid_pos = (++n - 1)/2;
    }
    printf("%d", ans);
}
```

---

### 拓展与技巧
- **同类问题**：涉及中位数调整的问题通常需要排序后分析位置关系。
- **优化思维**：当允许添加相同元素时，优先添加目标值以最小化操作次数。
- **调试要点**：注意处理目标值不在原数组的边界情况，需验证所有可能的位置区间。

---

### 推荐练习
1. [P1168 中位数](https://www.luogu.com.cn/problem/P1168) - 动态维护中位数
2. [P1138 第k小整数](https://www.luogu.com.cn/problem/P1138) - 排序与位置分析
3. [P5149 会议座位](https://www.luogu.com.cn/problem/P5149) - 中位数性质应用

---
处理用时：171.82秒