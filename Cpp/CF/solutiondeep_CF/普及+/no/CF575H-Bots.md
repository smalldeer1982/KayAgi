# 题目信息

# Bots

## 题目描述

Sasha and Ira are two best friends. But they aren’t just friends, they are software engineers and experts in artificial intelligence. They are developing an algorithm for two bots playing a two-player game. The game is cooperative and turn based. In each turn, one of the players makes a move (it doesn’t matter which player, it's possible that players turns do not alternate).

Algorithm for bots that Sasha and Ira are developing works by keeping track of the state the game is in. Each time either bot makes a move, the state changes. And, since the game is very dynamic, it will never go back to the state it was already in at any point in the past.

Sasha and Ira are perfectionists and want their algorithm to have an optimal winning strategy. They have noticed that in the optimal winning strategy, both bots make exactly $ N $ moves each. But, in order to find the optimal strategy, their algorithm needs to analyze all possible states of the game (they haven’t learned about alpha-beta pruning yet) and pick the best sequence of moves.

They are worried about the efficiency of their algorithm and are wondering what is the total number of states of the game that need to be analyzed?

## 说明/提示

Start: Game is in state A.

- Turn 1: Either bot can make a move (first bot is red and second bot is blue), so there are two possible states after the first turn – B and C.
- Turn 2: In both states B and C, either bot can again make a turn, so the list of possible states is expanded to include D, E, F and G.
- Turn 3: Red bot already did N=2 moves when in state D, so it cannot make any more moves there. It can make moves when in state E, F and G, so states I, K and M are added to the list. Similarly, blue bot cannot make a move when in state G, but can when in D, E and F, so states H, J and L are added.
- Turn 4: Red bot already did N=2 moves when in states H, I and K, so it can only make moves when in J, L and M, so states P, R and S are added. Blue bot cannot make a move when in states J, L and M, but only when in H, I and K, so states N, O and Q are added.

Overall, there are 19 possible states of the game their algorithm needs to analyze.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF575H/fe492a4b59f95857f16ee99d37e8da94ed083cf9.png)

## 样例 #1

### 输入

```
2
```

### 输出

```
19
```

# AI分析结果

### 题目内容
# Bots
## 题目描述
Sasha和Ira是两位挚友。但他们不仅是朋友，还是软件工程师和人工智能专家。他们正在开发一种算法，用于两个机器人进行双人游戏。该游戏是合作且回合制的。在每一回合中，其中一个玩家进行移动（具体是哪个玩家无关紧要，玩家的回合不一定交替进行）。

Sasha和Ira正在开发的机器人算法通过跟踪游戏所处的状态来运行。每次任何一个机器人进行移动，状态就会改变。而且，由于游戏非常动态，它永远不会回到过去任何时刻所处的状态。

Sasha和Ira是完美主义者，希望他们的算法具有最优获胜策略。他们注意到，在最优获胜策略中，两个机器人各自恰好进行 $N$ 次移动。但是，为了找到最优策略，他们的算法需要分析游戏的所有可能状态（他们还没有学习alpha - beta剪枝）并选择最佳的移动序列。

他们担心算法的效率，想知道需要分析的游戏总状态数是多少？
## 说明/提示
开始：游戏处于状态A。
 - 回合1：两个机器人中的任何一个都可以移动（第一个机器人为红色，第二个机器人为蓝色），所以第一回合后有两个可能的状态 - B和C。
 - 回合2：在状态B和C中，两个机器人中的任何一个都可以再次移动，所以可能状态列表扩展到包括D、E、F和G。
 - 回合3：当处于状态D时，红色机器人已经进行了N = 2次移动，所以它在那里不能再进行移动。当处于状态E、F和G时它可以移动，所以状态I、K和M被添加到列表中。类似地，当处于状态G时，蓝色机器人不能移动，但当处于D、E和F时可以移动，所以状态H、J和L被添加。
 - 回合4：当处于状态H、I和K时，红色机器人已经进行了N = 2次移动，所以它只能在J、L和M时进行移动，所以状态P、R和S被添加。蓝色机器人在状态J、L和M时不能移动，但只能在H、I和K时移动，所以状态N、O和Q被添加。

总体而言，他们的算法需要分析19种可能的游戏状态。

![题目配图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF575H/fe492a4b59f95857f16ee99d37e8da94ed083cf9.png)
## 样例 #1
### 输入
```
2
```
### 输出
```
19
```

### 算法分类
组合数学

### 综合分析与结论
这些题解主要围绕计算两个机器人各走 $n$ 步的游戏状态总数展开。思路上，有的将问题转化为网格路径问题，利用组合数公式求解；有的通过分析不合法状态，从满二叉树节点总数中减去不合法部分得到答案。算法要点在于对组合数的计算和运用，以及对游戏状态结构的理解。解决难点在于如何准确地将游戏状态与数学模型对应，以及对组合恒等式的运用或不合法状态的准确枚举。

### 所选的题解
- **作者：Siegerkranz_2735 (5星)**
    - **关键亮点**：将游戏状态转化为网格路径问题，通过一系列数学推导得出简洁的组合数公式 $C_{2n + 2}^{n + 1} - 1$，思路清晰且数学功底深厚。
    - **重点代码**：无（未给出代码）
    - **核心实现思想**：利用差分运算、定和式、下降幂等知识对组合数求和公式进行推导化简。
- **作者：yuanzhiteng (4星)**
    - **关键亮点**：先将题目转换为网格图上的路径方案数问题，再通过组合恒等式或杨辉三角性质对组合数求和公式进行化简，步骤详细易懂。
    - **重点代码**：无（未给出完整代码，仅提供代码链接）
    - **核心实现思想**：运用组合恒等式 $\sum_{i=0}^n C_{j}^m = C_{n + 1}^{m + 1}$ 和杨辉三角性质 $C_n^m = C_{n - 1}^{m - 1} + C_{n - 1}^m$ 对双重求和的组合数公式进行化简。
- **作者：262620zzj (4星)**
    - **关键亮点**：把所有状态看作二叉树，通过计算满二叉树节点总数并减去不合法状态数来求解，思路独特，代码实现完整。
    - **个人心得**：无
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
ll n, ans, fac[2000005];
template<typename T>
ll qpow(T a, int b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
ll C(int n, int k) {
    ll res = fac[n] * qpow(fac[n - k], mod - 2) % mod;
    res = res * qpow(fac[k], mod - 2) % mod;
    return res;
}
int main() {
    fac[0] = 1;
    for (int i = 1; i <= 2000000; i++) fac[i] = fac[i - 1] * i % mod;
    cin >> n;
    ans = (qpow(2ll, 2 * n + 1) - 1 + mod) % mod;
    for (int i = n + 1; i <= 2 * n; i++)
        ans = (ans - C(i - 1, n) * (qpow(2ll, 2 * n - i + 1) - 1 + mod) * 2 % mod + mod) % mod;
    cout << ans;
    return 0;
}
```
    - **核心实现思想**：先预处理阶乘用于计算组合数，通过快速幂计算 $2$ 的幂次方，然后根据公式 $2\times\sum_{i=n + 1}^{2n}\binom{i - 1}{n}\times (2^{2n - i + 1} - 1)$ 从满二叉树节点总数中减去不合法状态数。

### 最优关键思路或技巧
将游戏状态与网格路径或二叉树结构对应，利用组合数学知识，如组合数公式、组合恒等式等进行求解。在实现过程中，通过预处理阶乘和快速幂运算来提高计算效率。

### 可拓展之处
此类题目属于组合数学在实际问题中的应用，类似套路是将实际问题抽象为数学模型，利用组合数性质进行求解。同类型题可能会改变移动规则、限制条件等，但核心仍是对组合情况的分析。

### 推荐题目
- [P3807 【模板】卢卡斯定理](https://www.luogu.com.cn/problem/P3807)
- [P2822 [NOIP2016 提高组] 组合数问题](https://www.luogu.com.cn/problem/P2822)
- [P1313 计算系数](https://www.luogu.com.cn/problem/P1313)

### 个人心得摘录与总结
无

---
处理用时：71.97秒