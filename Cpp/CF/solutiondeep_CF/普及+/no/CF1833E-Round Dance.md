# 题目信息

# Round Dance

## 题目描述

$ n $ people came to the festival and decided to dance a few round dances. There are at least $ 2 $ people in the round dance and each person has exactly two neighbors. If there are $ 2 $ people in the round dance then they have the same neighbor on each side.

You decided to find out exactly how many dances there were. But each participant of the holiday remembered exactly one neighbor. Your task is to determine what the minimum and maximum number of round dances could be.

For example, if there were $ 6 $ people at the holiday, and the numbers of the neighbors they remembered are equal $ [2, 1, 4, 3, 6, 5] $ , then the minimum number of round dances is $ 1 $ :

- $ 1 - 2 - 3 - 4 - 5 - 6 - 1 $

 and the maximum is $ 3 $ : - $ 1 - 2 - 1 $
- $ 3 - 4 - 3 $
- $ 5 - 6 - 5 $

## 样例 #1

### 输入

```
10
6
2 1 4 3 6 5
6
2 3 1 5 6 4
9
2 3 2 5 6 5 8 9 8
2
2 1
4
4 3 2 1
5
2 3 4 5 1
6
5 3 4 1 1 2
5
3 5 4 1 2
6
6 3 2 5 4 3
6
5 1 4 3 4 2```

### 输出

```
1 3
2 2
1 3
1 1
1 2
1 1
1 1
2 2
1 2
1 1```

# AI分析结果

### 题目内容重写
$n$ 个人来到节日并决定跳几轮圆舞。每轮圆舞至少有 $2$ 个人，且每个人恰好有两个邻居。如果有 $2$ 个人在圆舞中，那么他们每侧的邻居相同。

你决定找出到底有多少轮圆舞。但每个参与者只记得一个邻居。你的任务是确定圆舞的最小和最大可能数量。

例如，如果有 $6$ 个人参加节日，且他们记得的邻居编号为 $[2, 1, 4, 3, 6, 5]$，那么圆舞的最小数量为 $1$：
- $1 - 2 - 3 - 4 - 5 - 6 - 1$

而最大数量为 $3$：
- $1 - 2 - 1$
- $3 - 4 - 3$
- $5 - 6 - 5$

### 算法分类
并查集、图论

### 题解分析与结论
本题的核心在于通过并查集或图论的方法，确定圆舞的最小和最大可能数量。最大数量可以通过并查集直接求出连通块的数量，而最小数量则需要通过统计连通块中度为 $1$ 的点的数量，进一步优化连通块的数量。

### 精选题解
#### 1. 作者：guanyf (5星)
**关键亮点**：
- 使用并查集处理连通块，思路清晰。
- 通过统计度为 $1$ 的点的数量，优化最小圆舞数量的计算。
- 代码简洁，逻辑严密。

**核心代码**：
```cpp
for (int i = 1; i <= n; i++) {
    st.insert(find(i));
    cnt += (du[i] == 1);
}
cout << min(st.size(), st.size() - cnt / 2 + 1) << ' ' << st.size() << '\n';
```
**实现思想**：
通过并查集合并相邻的人，统计连通块数量和度为 $1$ 的点的数量，最终计算最小和最大圆舞数量。

#### 2. 作者：sz_jinzikai (4星)
**关键亮点**：
- 使用并查集处理连通块，思路清晰。
- 通过统计度为 $1$ 的点的数量，优化最小圆舞数量的计算。
- 代码简洁，逻辑严密。

**核心代码**：
```cpp
for (int i = 1; i <= n; i++) {
    if (find(i) == i) ++ sum;
    if (du[i] == 1) ++ cnt;
}
cout << min(sum, sum - cnt / 2 + 1) << ' ' << sum << '\n';
```
**实现思想**：
通过并查集合并相邻的人，统计连通块数量和度为 $1$ 的点的数量，最终计算最小和最大圆舞数量。

#### 3. 作者：Coffee_zzz (4星)
**关键亮点**：
- 使用并查集处理连通块，思路清晰。
- 通过统计环的数量，优化最小圆舞数量的计算。
- 代码简洁，逻辑严密。

**核心代码**：
```cpp
for (int i = 1; i <= n; i++) {
    if (find(i) == i) {
        if (circle[i] && sz[i] != 2) sum_circle++;
    }
}
printf("%d %d\n", min(sum, sum_circle + 1), sum);
```
**实现思想**：
通过并查集合并相邻的人，统计连通块数量和环的数量，最终计算最小和最大圆舞数量。

### 最优关键思路
使用并查集处理连通块，通过统计度为 $1$ 的点的数量或环的数量，优化最小圆舞数量的计算。

### 拓展思路
类似的问题可以通过并查集或图论的方法解决，尤其是在处理连通性和环的问题时。可以通过统计特定点的度或环的数量，进一步优化结果。

### 推荐题目
1. [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)
2. [P3388 【模板】割点（割顶）](https://www.luogu.com.cn/problem/P3388)
3. [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)

---
处理用时：35.51秒