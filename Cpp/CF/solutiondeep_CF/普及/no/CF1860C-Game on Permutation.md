# 题目信息

# Game on Permutation

## 题目描述

Alice and Bob are playing a game. They have a permutation $ p $ of size $ n $ (a permutation of size $ n $ is an array of size $ n $ where each element from $ 1 $ to $ n $ occurs exactly once). They also have a chip, which can be placed on any element of the permutation.

Alice and Bob make alternating moves: Alice makes the first move, then Bob makes the second move, then Alice makes the third move, and so on. During the first move, Alice chooses any element of the permutation and places the chip on that element. During each of the next moves, the current player has to move the chip to any element that is simultaneously to the left and strictly less than the current element (i. e. if the chip is on the $ i $ -th element, it can be moved to the $ j $ -th element if $ j < i $ and $ p_j < p_i $ ). If a player cannot make a move (it is impossible to move the chip according to the rules of the game), that player wins the game.

Let's say that the $ i $ -th element of the permutation is lucky if the following condition holds:

- if Alice places the chip on the $ i $ -th element during her first move, she can win the game no matter how Bob plays (i. e. she has a winning strategy).

You have to calculate the number of lucky elements in the permutation.

## 说明/提示

In the first test case of the example, the $ 3 $ -rd element of the permutation is lucky.

In the second test case of the example, there are no lucky elements.

In the third test case of the example, the $ 2 $ -nd element of the permutation is lucky.

In the fourth test case of the example, the $ 3 $ -rd and the $ 4 $ -th element of the permutation are lucky.

## 样例 #1

### 输入

```
4
3
2 1 3
2
2 1
3
1 2 3
4
2 1 4 3```

### 输出

```
1
0
1
2```

# AI分析结果

### 题目内容重写

Alice和Bob正在玩一个游戏。他们有一个大小为$n$的排列$p$（排列是指一个大小为$n$的数组，其中每个元素从$1$到$n$恰好出现一次）。他们还有一个筹码，可以放在排列的任何元素上。

Alice和Bob轮流移动筹码：Alice先移动，然后Bob移动，接着Alice移动，依此类推。在第一次移动中，Alice选择排列中的任意一个元素并将筹码放在该元素上。在接下来的每次移动中，当前玩家必须将筹码移动到任何同时位于当前元素左侧且严格小于当前元素的元素（即如果筹码位于第$i$个元素，它可以移动到第$j$个元素，如果$j < i$且$p_j < p_i$）。如果一个玩家无法移动筹码（即无法根据游戏规则移动筹码），则该玩家获胜。

我们称排列中的第$i$个元素是幸运的，如果以下条件成立：

- 如果Alice在第一次移动中将筹码放在第$i$个元素上，无论Bob如何移动，Alice都能获胜（即她有必胜策略）。

你需要计算排列中幸运元素的数量。

### 算法分类
动态规划

### 题解分析与结论

题目要求找出排列中所有“幸运”元素的数量，即Alice在第一次移动中选择该元素后，无论Bob如何移动，Alice都能获胜的元素。通过分析，可以发现这类元素满足以该元素结尾的最长上升子序列（LIS）的长度为2。因此，问题转化为求排列中每个元素的LIS长度，并统计LIS长度为2的元素数量。

### 精选题解

#### 1. 作者：Crsuh2er0 (赞：8)
**星级：5星**
**关键亮点：**
- 通过维护两个变量`canTransferTo`和`winState`，分别记录当前元素可以转移的最小值和当前元素可以转移的必胜状态的最小值。
- 时间复杂度为$O(n)$，效率高。
- 代码简洁，逻辑清晰。

**核心代码：**
```cpp
int canTransferTo, winState, ans = 0;
canTransferTo = winState = INT_MAX;
for(int i = 1;i <= n;i++){
    if(canTransferTo < p[i] && p[i] < winState){
        ++ans, winState = min(winState, p[i]);
    }
    canTransferTo = min(canTransferTo, p[i]);
}
```

#### 2. 作者：_sunkuangzheng_ (赞：8)
**星级：4星**
**关键亮点：**
- 通过树状数组优化LIS的求解过程，时间复杂度为$O(n \log n)$。
- 思路清晰，代码实现较为简洁。

**核心代码：**
```cpp
int k = query(b[i]);
if(k == 1) ans++;
add(b[i], k+1);
```

#### 3. 作者：chlchl (赞：7)
**星级：4星**
**关键亮点：**
- 使用二分查找优化LIS的求解，时间复杂度为$O(n \log n)$。
- 代码结构清晰，逻辑明确。

**核心代码：**
```cpp
f[i] = lower_bound(q + 1, q + len + 1, a[i]) - q;
q[f[i]] = a[i];
len = max(len, f[i]);
if(f[i] == 2) ++cnt;
```

### 最优关键思路与技巧
- **维护最小值和必胜状态**：通过维护两个变量`canTransferTo`和`winState`，可以在一次遍历中高效地判断当前元素是否为幸运元素。
- **树状数组优化LIS**：通过树状数组优化LIS的求解过程，能够有效地降低时间复杂度。
- **二分查找优化LIS**：使用二分查找来优化LIS的求解，提高算法效率。

### 可拓展之处
- **类似问题**：可以扩展到其他与LIS相关的博弈问题，如求最长下降子序列（LDS）或最长不下降子序列（LNDS）。
- **其他优化**：可以考虑使用其他数据结构如线段树来进一步优化LIS的求解。

### 推荐题目
1. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)
2. [P1439 【模板】最长公共子序列](https://www.luogu.com.cn/problem/P1439)
3. [P2782 友好城市](https://www.luogu.com.cn/problem/P2782)

---
处理用时：27.19秒