# 题目信息

# World is Mine

## 题目描述

Alice and Bob are playing a game. Initially, there are $ n $ cakes, with the $ i $ -th cake having a tastiness value of $ a_i $ .

Alice and Bob take turns eating them, with Alice starting first:

- In her turn, Alice chooses and eats any remaining cake whose tastiness is strictly greater than the maximum tastiness of any of the cakes she's eaten before that. Note that on the first turn, she can choose any cake.
- In his turn, Bob chooses any remaining cake and eats it.

The game ends when the current player can't eat a suitable cake. Let $ x $ be the number of cakes that Alice ate. Then, Alice wants to maximize $ x $ , while Bob wants to minimize $ x $ .

Find out how many cakes Alice will eat if both players play optimally.

## 说明/提示

In the first test case, one possible sequence of turns is:

1. Alice eats a cake with a tastiness value of $ 1 $ . The remaining cakes are $ [4, 2, 3] $ .
2. Bob eats a cake with a tastiness value of $ 2 $ . The remaining cakes are $ [4, 3] $ .
3. Alice eats a cake with a tastiness of $ 3 $ . The remaining cakes are $ [4] $ .
4. Bob eats a cake with a tastiness value of $ 4 $ . The remaining cakes are $ [] $ .
5. Since there are no more cakes left, the game ends.

In the second test case, one possible sequence of turns is:

1. Alice eats a cake with a tastiness value of $ 1 $ . The remaining cakes are $ [1, 1] $ .
2. Bob eats a cake with a tastiness value of $ 1 $ . The remaining cakes are $ [1] $ .
3. Since Alice has already eaten a cake with a tastiness value of $ 1 $ , she cannot make a turn, so the game ends.

## 样例 #1

### 输入

```
9
4
1 4 2 3
3
1 1 1
5
1 4 2 3 4
4
3 4 1 4
1
1
8
4 3 2 5 6 8 3 4
7
6 1 1 3 5 3 1
11
6 11 6 8 7 5 3 11 2 3 5
17
2 6 5 3 9 1 6 2 5 6 3 2 3 9 6 1 6```

### 输出

```
2
1
3
2
1
3
2
4
4```

# AI分析结果

### 题目内容重写

Alice 和 Bob 在玩游戏。最初，有 $n$ 个蛋糕，第 $i$ 个蛋糕的美味值为 $a_i$。

Alice 和 Bob 轮流吃蛋糕，Alice 先开始：

- 在 Alice 的回合，她选择并吃掉任意一个剩下的蛋糕，且该蛋糕的美味值必须**严格大于**她之前吃过的所有蛋糕的美味值。注意，在第一个回合，她可以选择任意一个蛋糕。
- 在 Bob 的回合，他可以选择并吃掉任意一个剩下的蛋糕。

当当前玩家无法吃到合适的蛋糕时，游戏结束。设 $x$ 为 Alice 吃掉的蛋糕数量。Alice 希望最大化 $x$，而 Bob 希望最小化 $x$。

求当双方都采取最优策略时，Alice 最终会吃掉多少个蛋糕。

### 题解综合分析

本题的核心在于分析 Alice 和 Bob 的最优策略，并通过动态规划来模拟双方的决策过程。Alice 的策略是固定的，即每次选择当前可选的最小美味值蛋糕，而 Bob 的策略则更为复杂，他需要在 Alice 吃掉某个蛋糕之前，尽可能多地拦截相同美味值的蛋糕。

### 所选高星题解

#### 题解1：Rnfmabj (5星)
**关键亮点**：
- 通过将相同美味值的蛋糕合并，简化了问题。
- 使用记忆化搜索来模拟 Bob 的决策过程，状态转移方程清晰。
- 代码简洁且高效，时间复杂度为 $O(n^2)$。

**核心代码**：
```cpp
ll dfs(ll x,ll t){//记忆化搜索
	if(x>tot)return 0;
	if(~f[x][t])return f[x][t];
	ll res=dfs(x+1,t+1)+1;
	if(t>=b[x])res=min(res,dfs(x+1,t-b[x]));
	return f[x][t]=res;
}
```
**核心思想**：通过记忆化搜索模拟 Bob 的决策，Bob 可以选择拦截当前批次的蛋糕或积累回合数来拦截后续的蛋糕。

#### 题解2：ben090302 (4星)
**关键亮点**：
- 通过排序和合并相同美味值的蛋糕，简化了问题。
- 使用动态规划来模拟 Bob 的决策，状态转移方程清晰。
- 代码实现较为简洁，时间复杂度为 $O(n^2)$。

**核心代码**：
```cpp
for(int i=1;i<=tot;i++){
    for(int j=0;j<=i;j++){
        dp[i][j] = min(dp[i][j],dp[i-1][j] + 1);
        if(j+V[i].num<=i-1) dp[i][j]=min(dp[i][j],dp[i-1][j+V[i].num]);
    }
}
```
**核心思想**：通过动态规划模拟 Bob 的决策，Bob 可以选择拦截当前批次的蛋糕或积累回合数来拦截后续的蛋糕。

#### 题解3：CCPSDCGK (4星)
**关键亮点**：
- 通过排序和合并相同美味值的蛋糕，简化了问题。
- 使用动态规划来模拟 Bob 的决策，状态转移方程清晰。
- 代码实现较为简洁，时间复杂度为 $O(n^2)$。

**核心代码**：
```cpp
for(int i=1;i<=n;i++){
    for(int j=a[i];j<=n;j++) dp[i][j-a[i]]=min(dp[i][j-a[i]],dp[i-1][j]);
    if(a[i]) for(int j=0;j<n;j++) dp[i][j+1]=min(dp[i][j+1],dp[i-1][j]+1);
}
```
**核心思想**：通过动态规划模拟 Bob 的决策，Bob 可以选择拦截当前批次的蛋糕或积累回合数来拦截后续的蛋糕。

### 最优关键思路与技巧

1. **合并相同美味值的蛋糕**：通过将相同美味值的蛋糕合并，可以简化问题，减少状态转移的复杂度。
2. **动态规划模拟 Bob 的决策**：通过动态规划来模拟 Bob 的决策过程，Bob 可以选择拦截当前批次的蛋糕或积累回合数来拦截后续的蛋糕。
3. **记忆化搜索**：通过记忆化搜索来优化动态规划的过程，减少重复计算。

### 可拓展之处

本题的解法可以拓展到类似的博弈论问题，特别是涉及到双方轮流决策且目标相反的情况。类似的题目可以通过分析双方的最优策略，并使用动态规划或记忆化搜索来模拟决策过程。

### 推荐题目

1. [P1280 尼克的任务](https://www.luogu.com.cn/problem/P1280)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1064 金明的预算方案](https://www.luogu.com.cn/problem/P1064)

---
处理用时：42.17秒