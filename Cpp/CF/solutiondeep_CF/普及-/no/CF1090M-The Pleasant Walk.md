# 题目信息

# The Pleasant Walk

## 题目描述

There are $ n $ houses along the road where Anya lives, each one is painted in one of $ k $ possible colors.

Anya likes walking along this road, but she doesn't like when two adjacent houses at the road have the same color. She wants to select a long segment of the road such that no two adjacent houses have the same color.

Help Anya find the longest segment with this property.

## 说明/提示

In the example, the longest segment without neighboring houses of the same color is from the house 4 to the house 7. The colors of the houses are $ [3, 2, 1, 2] $ and its length is 4 houses.

## 样例 #1

### 输入

```
8 3
1 2 3 3 2 1 2 2
```

### 输出

```
4
```

# AI分析结果



# The Pleasant Walk

## 题目描述

路旁有 $n$ 栋房子，每栋涂有 $k$ 种颜色之一。求最长连续子段，使得相邻房子颜色不同。

## 算法分类
动态规划

---

## 题解分析

各题解均采用线性扫描策略，核心思路为维护当前合法区间的长度：  
1. **递推关系**：若当前颜色与前一个不同则长度+1，否则重置为1  
2. **状态压缩**：仅需记录前一个状态，空间复杂度优化至 $O(1)$  
3. **易错点**：最大值可能出现在序列末尾，需在循环内部持续更新最大值

---

## 精选题解

### [DeepSkyBlue__] ⭐⭐⭐⭐  
**亮点**：代码简洁，变量命名清晰  
**核心思路**：  
```cpp
int ans=0, ma=0;
for(int i=1;i<=n;i++) {
    cin>>a[i];
    if(a[i]==a[i-1]) ans=1;  // 重置当前长度
    else ans++;              // 延长当前序列
    ma = max(ma, ans);       // 实时更新最大值
}
```

### [一只大龙猫] ⭐⭐⭐⭐  
**动态规划视角**：  
```cpp
f[i] = (a[i] != a[i-1]) ? f[i-1]+1 : 1;
```
**优化技巧**：隐式状态转移，通过初始化 `f[i]=1` 省略 else 分支

### [lu_run_ting] ⭐⭐⭐⭐  
**调试经验**：循环内必须实时更新最大值，否则末尾序列可能丢失  
**双版本代码**：展示循环内外更新差异，强调实时维护的重要性

---

## 关键技巧总结

1. **滚动变量替代数组**：用单变量代替DP数组，将空间复杂度从 $O(n)$ 降至 $O(1)$  
2. **实时最大值更新**：在状态变化时立即比较，避免漏判末尾情况  
3. **边界处理**：初始值设为1（单元素自身构成合法序列）

---

## 拓展训练

1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115) - 线性递推求极值  
2. [P1567 统计天数](https://www.luogu.com.cn/problem/P1567) - 最长连续递增序列  
3. [P2367 语文成绩](https://www.luogu.com.cn/problem/P2367) - 差分与前缀和的综合应用

---
处理用时：108.83秒