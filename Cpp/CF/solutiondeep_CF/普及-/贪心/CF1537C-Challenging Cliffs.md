# 题目信息

# Challenging Cliffs

## 题目描述

You are a game designer and want to make an obstacle course. The player will walk from left to right. You have $ n $ heights of mountains already selected and want to arrange them so that the absolute difference of the heights of the first and last mountains is as small as possible.

In addition, you want to make the game difficult, and since walking uphill or flat is harder than walking downhill, the difficulty of the level will be the number of mountains $ i $ ( $ 1 \leq i < n $ ) such that $ h_i \leq h_{i+1} $ where $ h_i $ is the height of the $ i $ -th mountain. You don't want to waste any of the mountains you modelled, so you have to use all of them.

From all the arrangements that minimize $ |h_1-h_n| $ , find one that is the most difficult. If there are multiple orders that satisfy these requirements, you may find any.

## 说明/提示

In the first test case:

The player begins at height $ 2 $ , next going up to height $ 4 $ increasing the difficulty by $ 1 $ . After that he will go down to height $ 1 $ and the difficulty doesn't change because he is going downhill. Finally the player will go up to height $ 2 $ and the difficulty will increase by $ 1 $ . The absolute difference between the starting height and the end height is equal to $ 0 $ and it's minimal. The difficulty is maximal.

In the second test case:

The player begins at height $ 1 $ , next going up to height $ 3 $ increasing the difficulty by $ 1 $ . The absolute difference between the starting height and the end height is equal to $ 2 $ and it's minimal as they are the only heights. The difficulty is maximal.

## 样例 #1

### 输入

```
2
4
4 2 1 2
2
3 1```

### 输出

```
2 4 1 2 
1 3```

# AI分析结果



# 中文重写题目

## 题目名称：挑战悬崖

### 题目描述

你是一名游戏设计师，正在设计一个障碍赛道。玩家将从左到右行进。你已经选择了 $n$ 座山的高度，现在需要重新排列它们，使得第一座山和最后一座山的绝对高度差尽可能小。

此外，为了使游戏更具挑战性，赛道的难度定义为满足 $h_i \leq h_{i+1}$（$1 \leq i < n$）的 $i$ 的数量（因为上坡或平地行走比下坡更难）。你必须使用所有山，不能遗漏。

在所有能最小化 $|h_1 - h_n|$ 的排列中，你需要找到难度最大的那个。若存在多个满足条件的排列，输出任意一个即可。

### 输入输出样例

#### 样例 #1
**输入：**
```
2
4
4 2 1 2
2
3 1
```
**输出：**
```
2 4 1 2 
1 3
```

---

# 题解分析与结论

## 关键思路总结
1. **排序与最小相邻差**：所有题解均采用先对数组排序，寻找相邻元素差最小的位置作为首尾端点。
2. **构造最优排列**：将最小差的两个元素作为首尾，剩余元素按排序后的顺序拼接（后半段接前半段），保证中间部分尽可能保持递增趋势。
3. **边界处理**：需单独处理 $n=2$ 的情况，此时直接输出排序后的两个元素。

## 推荐题解

### Fire_flame（★★★★★）
**核心思路**：排序后找到最小相邻差的位置 $k$，构造排列为 $[a_k] + a_{k+2..n} + a_{1..k-1} + [a_{k+1}]$。  
**亮点**：代码简洁高效，直接通过遍历实现拼接，无需复杂结构。  
**代码片段**：
```cpp
sort(a+1, a+n+1);
int k, min_diff = INF;
for (int i=1; i<n; i++) {
    if (a[i+1]-a[i] < min_diff) {
        min_diff = a[i+1]-a[i];
        k = i;
    }
}
printf("%d ", a[k]);
for (int i=k+2; i<=n; i++) printf("%d ", a[i]);
for (int i=1; i<k; i++) printf("%d ", a[i]);
printf("%d\n", a[k+1]);
```

### xuanyuan_Niubi（★★★★☆）
**核心思路**：与 Fire_flame 类似，但显式处理 $n=2$ 的情况，代码逻辑更易理解。  
**亮点**：对 $n=2$ 的边界条件单独处理，增强鲁棒性。  
**代码片段**：
```cpp
sort(a+1, a+n+1);
if (n == 2) {
    printf("%d %d\n", a[1], a[2]);
    continue;
}
// 其余部分与 Fire_flame 类似
```

### lrmlrm_（★★★★☆）
**核心思路**：完全一致的构造方法，代码可读性较好。  
**亮点**：变量命名清晰，逻辑直白，适合新手学习。  
**代码片段**：
```cpp
sort(a+1, a+n+1);
printf("%d ", a[k]);
for (int i=k+1; i<=n; i++) printf("%d ", a[i]);
for (int i=1; i<=k; i++) printf("%d ", a[i]);
```

## 扩展思路
- **类似题型**：若题目要求首尾差最大的排列，可类似地取数组首尾元素，中间部分按降序排列。
- **算法套路**：排序后利用相邻差特性构造最优解，适用于需要极值端点+内部有序的场景。

## 推荐练习题
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)（贪心+排序）
2. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)（贪心构造特定序列）
3. [CF1385D Minimum Grid](https://codeforces.com/problemset/problem/1385/D)（排序后构造最优排列）

---
处理用时：70.64秒