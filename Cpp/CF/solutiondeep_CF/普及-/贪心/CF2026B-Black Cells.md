# 题目信息

# Black Cells

## 题目描述

You are given a strip divided into cells, numbered from left to right from $ 0 $ to $ 10^{18} $ . Initially, all cells are white.

You can perform the following operation: choose two white cells $ i $ and $ j $ , such that $ i \ne j $ and $ |i - j| \le k $ , and paint them black.

A list $ a $ is given. All cells from this list must be painted black. Additionally, at most one cell that is not in this list can also be painted black. Your task is to determine the minimum value of $ k $ for which this is possible.

## 说明/提示

In the first example, with $ k=1 $ , it is possible to paint the cells $ (1, 2) $ .

In the second example, with $ k=1 $ , it is possible to paint the cells $ (7, 8) $ .

In the third example, with $ k=2 $ , it is possible to paint the cells $ (2, 4) $ and $ (8, 9) $ .

In the fourth example, with $ k=3 $ , it is possible to paint the cells $ (0, 1) $ , $ (5, 8) $ and $ (10, 13) $ .

## 样例 #1

### 输入

```
4
2
1 2
1
7
3
2 4 9
5
1 5 8 10 13```

### 输出

```
1
1
2
3```

# AI分析结果



# 题目内容

## 题目描述

你被给定一个被分割成单元格的条带，从左到右编号从 $0$ 到 $10^{18}$。初始时所有单元格都是白色的。

你可以进行如下操作：选择两个白色单元格 $i$ 和 $j$，满足 $i \ne j$ 且 $|i - j| \le k$，并将它们涂黑。

给定一个列表 $a$，其中的所有单元格必须被涂黑。此外，最多可以涂黑一个不在该列表中的单元格。你的任务是确定使得这成为可能的最小 $k$ 值。

---

# 题解综合分析

## 核心思路总结
所有题解主要分为两类思路：
1. **贪心策略**：基于数组奇偶性处理，当 $n$ 为奇数时枚举插入一个虚拟点来分割数组，使得剩余点能两两配对，取最大间距的最小值。时间复杂度 $O(n^2)$。
2. **二分答案**：在 $[1, 10^{18}]$ 范围内二分 $k$，每次检查是否能用该 $k$ 覆盖至少 $n-1$ 个点。检查时暴力匹配点对，复杂度 $O(n^2 \log D)$，对 $n=2000$ 存在超时风险。

## 最优题解推荐

### 1. 作者：Yxy7952 & zhouruoheng（评分：4★）
**关键亮点**：
- 利用奇偶性分类讨论，直接构造最优配对方式。
- 当 $n$ 为奇数时，枚举每个可能的插入点，分割数组为两部分计算最大间隔。
- 时间复杂度稳定为 $O(n^2)$，适合题目给定的数据范围（$n \leq 2000$）。

**核心代码**：
```cpp
if(n%2) {
    ans = INF;
    for(int i=1; i<=n; i++) { // 枚举插入点
        ll s = 0;
        // 前半部分配对
        for(int j=1; j<i; j+=2) 
            s = max(s, a[j+1]-a[j]);
        // 后半部分配对
        for(int j=i+1; j<=n; j+=2) 
            s = max(s, a[j+1]-a[j]);
        ans = min(ans, s);
    }
    cout << max(1ll, ans) << '\n';
} else {
    // 直接两两配对取最大值
    ll mx = 0;
    for(int i=2; i<=n; i+=2) 
        mx = max(mx, a[i]-a[i-1]);
    cout << mx << '\n';
}
```

### 2. 作者：xxxalq（评分：4★）
**关键亮点**：
- 通过插入虚拟点（$a_i \pm 1$）模拟额外涂黑点，转化为偶数情况。
- 使用 vector 动态维护数组，灵活处理插入与删除。

**核心代码**：
```cpp
for(int i=1; i<=n; i++) {
    // 在 a[i] 附近插入虚拟点
    if(i%2 == 1) 
        vec.insert(vec.begin()+i-1, a[i]-1);
    else 
        vec.insert(vec.begin()+i-1, a[i-1]+1);
    // 计算新数组的最大间隔
    for(int j=0; j<=n; j+=2) 
        d2 = max(d2, vec[j]-vec[j-1]);
    d1 = min(d1, d2);
    vec.erase(vec.begin()+i-1);
}
```

---

# 关键思路与技巧
1. **奇偶性分治**：当 $n$ 为奇数时，必须且只能引入一个外部点，将其转化为偶数问题。
2. **枚举分割点**：遍历每个可能的分割位置，计算剩余区间的最大间隔，取全局最小值。
3. **贪心配对**：相邻两两配对能最小化最大间隔，直接取排序后的相邻差值。

---

# 拓展与相似题目
1. **[CF1005E2 Median on Segments](https://www.luogu.com.cn/problem/CF1005E2)**：利用奇偶性统计满足条件的子数组。
2. **[P1090 合并果子](https://www.luogu.com.cn/problem/P1090)**：贪心策略选择最小代价合并。
3. **[P1873 砍树](https://www.luogu.com.cn/problem/P1873)**：二分答案求最大高度。

---
处理用时：53.33秒