# 题目信息

# Sakurako, Kosuke, and the Permutation

## 题目描述

Sakurako's exams are over, and she did excellently. As a reward, she received a permutation $ p $ . Kosuke was not entirely satisfied because he failed one exam and did not receive a gift. He decided to sneak into her room (thanks to the code for her lock) and spoil the permutation so that it becomes simple.

A permutation $ p $ is considered simple if for every $ i $ $ (1\le i \le n) $ one of the following conditions holds:

- $ p_i=i $
- $ p_{p_i}=i $

For example, the permutations $ [1, 2, 3, 4] $ , $ [5, 2, 4, 3, 1] $ , and $ [2, 1] $ are simple, while $ [2, 3, 1] $ and $ [5, 2, 1, 4, 3] $ are not.

In one operation, Kosuke can choose indices $ i,j $ $ (1\le i,j\le n) $ and swap the elements $ p_i $ and $ p_j $ .

Sakurako is about to return home. Your task is to calculate the minimum number of operations that Kosuke needs to perform to make the permutation simple.

## 说明/提示

In the first and second examples, the permutations are already simple.

In the fourth example, it is sufficient to swap $ p_2 $ and $ p_4 $ . Thus, the permutation will become $ [2, 1, 4, 3] $ in $ 1 $ operation.

## 样例 #1

### 输入

```
6
5
1 2 3 4 5
5
5 4 3 2 1
5
2 3 4 5 1
4
2 3 4 1
3
1 3 2
7
2 3 1 5 6 7 4```

### 输出

```
0
0
2
1
0
2```

# AI分析结果

### 题目内容重写（中文）

Sakurako的考试结束了，她表现得非常出色。作为奖励，她得到了一个排列 $p$。Kosuke因为有一门考试没过，没有得到礼物，因此决定潜入她的房间（多亏了她的锁密码）并破坏这个排列，使其变得简单。

一个排列 $p$ 被认为是简单的，如果对于每一个 $i$ $ (1\le i \le n) $，以下条件之一成立：

- $ p_i=i $
- $ p_{p_i}=i $

例如，排列 $ [1, 2, 3, 4] $、$ [5, 2, 4, 3, 1] $ 和 $ [2, 1] $ 是简单的，而 $ [2, 3, 1] $ 和 $ [5, 2, 1, 4, 3] $ 不是。

在一次操作中，Kosuke可以选择索引 $i,j$ $ (1\le i,j\le n) $ 并交换元素 $p_i$ 和 $p_j$。

Sakurako即将回家。你的任务是计算Kosuke需要执行的最少操作次数，以使排列变得简单。

### 说明/提示

在第一个和第二个样例中，排列已经是简单的。

在第四个样例中，只需交换 $p_2$ 和 $p_4$。因此，排列将变为 $ [2, 1, 4, 3] $，仅需 $1$ 次操作。

### 样例 #1

#### 输入

```
6
5
1 2 3 4 5
5
5 4 3 2 1
5
2 3 4 5 1
4
2 3 4 1
3
1 3 2
7
2 3 1 5 6 7 4
```

#### 输出

```
0
0
2
1
0
2
```

### 题解分析与结论

#### 综合分析与结论

本题的核心是将排列 $p$ 转化为简单排列，要求每个元素 $i$ 满足 $p_i=i$ 或 $p_{p_i}=i$。通过分析，可以发现这等价于将排列中的环（即 $i$ 和 $p_i$ 形成的环）的长度限制为 $1$ 或 $2$。最优策略是通过交换操作将大环拆分为长度为 $1$ 或 $2$ 的小环。

各题解的思路基本一致，主要采用并查集或直接遍历的方法来统计环的大小，然后计算需要的最小交换次数。具体来说，对于一个长度为 $k$ 的环，需要的交换次数为 $\lfloor \frac{k-1}{2} \rfloor$。

#### 所选高分题解

1. **作者：zhouruoheng (赞：4)**
   - **星级：5星**
   - **关键亮点：** 使用并查集统计环的大小，思路清晰，代码简洁，时间复杂度低。
   - **代码核心思想：** 通过并查集合并 $i$ 和 $p_i$，统计每个环的大小，计算需要的最小交换次数。
   ```cpp
   void solve() {
       cin >> n;
       for (int i = 1; i <= n; i++) cin >> a[i];
       for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1, v[i] = 0;
       for (int i = 1; i <= n; i++) merge(i, a[i]);
       int ans = 0;
       for (int i = 1; i <= n; i++) {
           int x = find(i);
           if (!v[x]) ans += (siz[x] - 1) / 2;
           v[x] = 1;
       }
       cout << ans << '\n';
   }
   ```

2. **作者：lailai0916 (赞：3)**
   - **星级：4星**
   - **关键亮点：** 直接遍历统计环的大小，代码简洁，思路清晰。
   - **代码核心思想：** 通过遍历数组，标记已访问的节点，统计每个环的大小，计算需要的最小交换次数。
   ```cpp
   int ans = 0;
   for (int i = 1; i <= n; i++) {
       if (vis[i]) continue;
       int now = i, cnt = 0;
       while (!vis[now]) {
           vis[now] = 1;
           now = a[now];
           cnt++;
       }
       ans += cnt - 1 >> 1;
   }
   cout << ans << '\n';
   ```

3. **作者：chenxi2009 (赞：1)**
   - **星级：4星**
   - **关键亮点：** 通过统计不同大小的环的数量，直接计算需要的最小交换次数，思路清晰。
   - **代码核心思想：** 统计每个环的大小，然后通过拆环的方式计算需要的最小交换次数。
   ```cpp
   for (int i = n; i > 2; i--) {
       cnt[i - 2] += cnt[i];
       ans += cnt[i];
   }
   printf("%d\n", ans);
   ```

### 最优关键思路或技巧

1. **环的拆分：** 通过交换操作将大环拆分为长度为 $1$ 或 $2$ 的小环，每次交换可以减少环的长度 $2$。
2. **并查集的使用：** 使用并查集来统计环的大小，能够高效地合并和查找环的根节点。
3. **直接遍历统计：** 通过遍历数组，标记已访问的节点，统计每个环的大小，计算需要的最小交换次数。

### 可拓展之处

1. **类似题目：** 可以拓展到其他需要将排列或图结构转化为特定形式的题目，如将图分解为若干个特定大小的连通分量。
2. **算法优化：** 可以进一步优化并查集的路径压缩和按秩合并，以提高效率。

### 推荐题目

1. [洛谷 P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)
2. [洛谷 P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
3. [洛谷 P3388 【模板】割点（割顶）](https://www.luogu.com.cn/problem/P3388)

### 个人心得摘录

- **zhouruoheng：** 通过并查集统计环的大小，思路清晰，代码简洁，时间复杂度低。
- **lailai0916：** 直接遍历统计环的大小，代码简洁，思路清晰。
- **chenxi2009：** 通过统计不同大小的环的数量，直接计算需要的最小交换次数，思路清晰。

---
处理用时：52.16秒