# 题目信息

# Madoka and The Corruption Scheme

## 题目描述

Madoka decided to entrust the organization of a major computer game tournament "OSU"!

In this tournament, matches are held according to the "Olympic system". In other words, there are $ 2^n $ participants in the tournament, numbered with integers from $ 1 $ to $ 2^n $ . There are $ n $ rounds in total in the tournament. In the $ i $ -th round there are $ 2^{n - i} $ matches between two players (one of whom is right, the other is left), after which the winners go further along the tournament grid, and the losing participants are eliminated from the tournament. Herewith, the relative order in the next round does not change. And the winner of the tournament — is the last remaining participant.

But the smaller the participant's number, the more he will pay Madoka if he wins, so Madoka wants the participant with the lowest number to win. To do this, she can arrange the participants in the first round as she likes, and also determine for each match who will win — the participant on the left or right.

But Madoka knows that tournament sponsors can change the winner in matches no more than $ k $ times. (That is, if the participant on the left won before the change, then the participant on the right will win after the change, and if the participant on the right won, then the participant on the left will win after the change).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1717D/f3b4c42531ac8b0aab0fa40e7e46069a137caf77.png)So, the first image shows the tournament grid that Madoka made, where the red lines denote who should win the match. And the second one shows the tournament grid, after one change in the outcome of the match by sponsors (a match between $ 1 $ and $ 3 $ players).Print the minimum possible number of the winner in the tournament, which Madoka can get regardless of changes in sponsors. But since the answer can be very large, output it modulo $ 10^9 + 7 $ . Note that we need to minimize the answer, and only then take it modulo.

## 说明/提示

In the first example, there is only one match between players $ 1 $ and $ 2 $ , so the sponsors can always make player $ 2 $ wins.

The tournament grid from the second example is shown in the picture in the statement.

## 样例 #1

### 输入

```
1 1```

### 输出

```
2```

## 样例 #2

### 输入

```
2 1```

### 输出

```
3```

## 样例 #3

### 输入

```
3 2```

### 输出

```
7```

# AI分析结果



【题目翻译】
# Madoka 与腐败赛制

## 题目描述

Madoka 决定负责举办大型游戏比赛 "OSU"！

该比赛采用「奥林匹克制」，共有 $2^n$ 名参赛者（编号 1 到 $2^n$）。比赛进行 $n$ 轮，每轮进行若干场比赛，胜者晋级且保持相对顺序，败者淘汰。Madoka 可以任意安排首轮对阵表，并预设所有比赛的胜负结果。

赞助商最多可以改变 $k$ 场比赛结果（将原本的胜者改为败者，反之亦然）。求在最坏情况下（赞助商做出最不利于 Madoka 的调整），最终获胜者编号的最小可能值（需取模 $10^9+7$）。

## 输入样例
样例 #1：`1 1` → 输出 `2`  
样例 #2：`2 1` → 输出 `3`  
样例 #3：`3 2` → 输出 `7`

---

【题解分析与结论】
各题解核心思路一致：将比赛树建模为二进制路径，统计最多修改 k 次能到达的叶子数目。关键公式为 $\sum_{i=0}^{\min(k,n)} \binom{n}{i}$，当 $k \ge n$ 时结果为 $2^n$。

---

【高分题解】
## 题解作者：DaiRuiChen007（5星）
**关键亮点**：  
- 简洁的阶乘逆元预处理，清晰展示组合数计算逻辑  
- 正确处理边界条件（k ≥ n 时返回 $2^n$）  
**核心代码**：
```cpp
int main() {
    // 预处理阶乘及逆元
    fac[0] = inv[0] = 1;
    for(int i=1; i<=n; ++i) fac[i] = fac[i-1]*i % MOD;
    inv[n] = ksm(fac[n]); // 逆元预处理
    
    LL ans = 0;
    for(int i=0; i<=min(n,k); ++i) ans = (ans + C(n,i)) % MOD;
    printf("%lld\n", ans);
}
```

## 题解作者：Hedgehog_210508（4.5星）
**关键亮点**：  
- 树形结构逆向分析，直观图解说明  
- 快速幂优化组合数计算  
**代码亮点**：
```cpp
ll c(ll a, ll b) {
    return p[a] * qp(p[b], M-2) % M * qp(p[a-b], M-2) % M;
}
// 预处理阶乘数组 p，组合数通过逆元计算
```

## 题解作者：whhsteven（4.5星）
**关键亮点**：  
- 二进制属性值模型，清晰解释修改次数与位操作关系  
- 数学推导严谨，揭示组合数和的本质  

---

【最优思路提炼】
将比赛树视为二进制路径，每个叶子对应一个 n 位二进制数，其中 1 的个数表示需要修改的次数。统计二进制数中 1 的个数 ≤k 的数量，即 $\sum_{i=0}^k \binom{n}{i}$。预处理阶乘和逆元快速计算组合数。

---

【拓展与心得】
**调试心得**（来自 fast_photon）：  
> 当 k ≥ n 时直接返回 2^n 的结论需要特别注意，通过画树状图验证发现当修改次数足够覆盖所有层级时，所有节点均可到达。

**相似题型推荐**：  
1. P3414 SAC#1 - 组合数 (组合数奇偶性)  
2. P4345 [SHOI2015]超能粒子炮 (组合数前缀和)  
3. P1350 车的放置 (组合数应用)

---

【关键代码实现】
完整组合数预处理逻辑：
```cpp
const int MOD = 1e9+7;
ll fac[MAXN], inv[MAXN];

ll qpow(ll a, ll b) { // 快速幂
    ll res = 1;
    while(b) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void init(int n) { // 初始化阶乘和逆元
    fac[0] = 1;
    for(int i=1; i<=n; ++i) fac[i] = fac[i-1] * i % MOD;
    inv[n] = qpow(fac[n], MOD-2);
    for(int i=n-1; i>=0; --i) inv[i] = inv[i+1] * (i+1) % MOD;
}

ll C(int n, int m) { // 组合数计算
    return fac[n] * inv[m] % MOD * inv[n-m] % MOD;
}
```

---
处理用时：71.65秒