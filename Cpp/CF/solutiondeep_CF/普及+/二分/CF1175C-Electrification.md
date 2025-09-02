# 题目信息

# Electrification

## 题目描述

At first, there was a legend related to the name of the problem, but now it's just a formal statement.

You are given $ n $ points $ a_1, a_2, \dots, a_n $ on the $ OX $ axis. Now you are asked to find such an integer point $ x $ on $ OX $ axis that $ f_k(x) $ is minimal possible.

The function $ f_k(x) $ can be described in the following way:

- form a list of distances $ d_1, d_2, \dots, d_n $ where $ d_i = |a_i - x| $ (distance between $ a_i $ and $ x $ );
- sort list $ d $ in non-descending order;
- take $ d_{k + 1} $ as a result.

If there are multiple optimal answers you can print any of them.

## 样例 #1

### 输入

```
3
3 2
1 2 5
2 1
1 1000000000
1 0
4
```

### 输出

```
3
500000000
4
```

# AI分析结果



# Electrification 电气化

## 题目描述

最初，这个问题有一个与名称相关的传说，但现在它只是一个形式化的陈述。

在 $OX$ 轴上给定 $n$ 个点 $a_1, a_2, \dots, a_n$。要求找到一个整数点 $x$，使得函数 $f_k(x)$ 的值尽可能小。

函数 $f_k(x)$ 的定义如下：
- 计算各点与 $x$ 的距离 $d_i = |a_i - x|$；
- 将 $d$ 列表按非递减顺序排序；
- 取排序后的第 $k+1$ 个元素作为结果。

若存在多个最优解，可输出任意一个。

---

## 题解分析与结论

### 核心思路
所有题解均基于关键性质：**使第 $k+1$ 小的距离对应的点，必定是排序后数组中的连续区间**。最优解出现在最短的 $k+1$ 连续点区间的中点。

### 最优题解推荐

#### 1. wanghaoyu120104（★★★★★）
**关键亮点**：
- 直接枚举连续 $k+1$ 点的区间，计算区间中点
- $O(n)$ 时间复杂度，代码简洁高效
- 正确性基于排序后相邻点的连续性特性

**核心代码**：
```cpp
for(int i=1;i<=n-k;i++) { // 枚举区间左端点
    if(mi>a[i+k]-a[i]) {  // 计算区间长度
        mi = a[i+k]-a[i];
        ans = a[i] + mi/2; // 取中点作为候选解
    }
}
```

#### 2. SamuelXuch（★★★★☆）
**关键亮点**：
- 与第一解相同思路但代码更简洁
- 强调无需复杂数据结构，直接遍历维护最小值

**代码差异**：
```cpp
for(int i=1;i<=n-k;i++) {
    if(ans>a[i+k]-a[i]) {
        ans = a[i+k]-a[i];
        pos = a[i] + ans/2;
    }
}
```

#### 3. 米奇（★★★★☆）
**关键亮点**：
- 二分答案验证思路
- 通过二分查找最小可能距离，滑动窗口验证可行性
- 时间复杂度 $O(n\log V)$，适合更大数据范围

**验证函数片段**：
```cpp
bool check(int mid) {
    int r = 1, res = 0;
    for(int l=1; l<=n; l++) {
        while(r<=n && a[r]-a[l]<=mid*2) r++;
        if(r-l > k) ans_pos = (a[l]+a[r-1])/2;
        res = max(res, r-l);
    }
    return res > k;
}
```

---

## 关键技巧总结

1. **连续区间性质**：排序后，最优解的 $k+1$ 个点必为连续区间，利用排序后的数组性质简化计算。
2. **中点策略**：取最短区间的中点，保证该区间两端点的距离最小。
3. **滑动窗口优化**：无论是线性扫描还是二分验证，均通过滑动窗口快速定位有效区间。

---

## 拓展应用

### 类似题目推荐
1. [P1843 奶牛晒衣服](https://www.luogu.com.cn/problem/P1843) - 二分答案+贪心验证
2. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678) - 二分最小距离的最大化
3. [P1314 聪明的质检员](https://www.luogu.com.cn/problem/P1314) - 二分答案+前缀和优化

### 调试心得摘录
- **Leaper_lyc**：_"看了半小时才发现连续区间性质，二分验证时要注意区间长度的计算"_
- **cosf**：_"发现无需二分直接线性扫描后，代码量减少70%"_ 
- **Zekrom**：_"最初误用大根堆，后改用小根堆维护最短区间"_

---
处理用时：42.42秒