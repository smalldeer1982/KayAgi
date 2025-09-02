# 题目信息

# Primal Sport

## 题目描述

Alice and Bob begin their day with a quick game. They first choose a starting number $ X_{0}>=3 $ and try to reach one million by the process described below.

Alice goes first and then they take alternating turns. In the $ i $ -th turn, the player whose turn it is selects a prime number smaller than the current number, and announces the smallest multiple of this prime number that is not smaller than the current number.

Formally, he or she selects a prime $ p&lt;X_{i-1} $ and then finds the minimum $ X_{i}>=X_{i-1} $ such that $ p $ divides $ X_{i} $ . Note that if the selected prime $ p $ already divides $ X_{i-1} $ , then the number does not change.

Eve has witnessed the state of the game after two turns. Given $ X_{2} $ , help her determine what is the smallest possible starting number $ X_{0} $ . Note that the players don't necessarily play optimally. You should consider all possible game evolutions.

## 说明/提示

In the first test, the smallest possible starting number is $ X_{0}=6 $ . One possible course of the game is as follows:

- Alice picks prime 5 and announces $ X_{1}=10 $
- Bob picks prime 7 and announces $ X_{2}=14 $ .

In the second case, let $ X_{0}=15 $ .

- Alice picks prime 2 and announces $ X_{1}=16 $
- Bob picks prime 5 and announces $ X_{2}=20 $ .

## 样例 #1

### 输入

```
14
```

### 输出

```
6
```

## 样例 #2

### 输入

```
20
```

### 输出

```
15
```

## 样例 #3

### 输入

```
8192
```

### 输出

```
8191
```

# AI分析结果



### 题目重写
# 质数游戏

## 题目描述

Alice和Bob以快速游戏开始新的一天。他们首先选择一个起始数 $X_0 \geq 3$，并通过以下过程尝试达到一百万。

Alice先手，两人交替操作。在第 $i$ 回合，当前玩家选择一个小于当前数的质数，并宣布这个质数的最小倍数且不小于当前数的值。

形式化地说，玩家选择质数 $p < X_{i-1}$，然后找到满足 $p$ 整除的 $X_i \geq X_{i-1}$ 的最小值。注意如果当前数已经是该质数的倍数，则数值不变。

Eve看到了两回合后的游戏状态。给定 $X_2$，帮她确定可能的最小起始数 $X_0$。注意玩家不一定采取最优策略，需考虑所有可能的游戏进程。

---

### 综合题解分析

各题解核心思路一致：逆向推导确定可能的最小$X_0$。关键点在于预处理最大质因数和逆向枚举范围。

#### 关键思路
1. **最大质因数预处理**：使用线性筛法为每个数记录其最大质因数
2. **逆向推导范围**：$X_1 \in [X_2-P_2+1, X_2]$，其中$P_2$是$X_2$的最大质因数
3. **最小化$X_0$**：对每个可能的$X_1$，求其对应的$X_0 = X_1-P_1+1$，取最小值

---

### 高分题解选评

#### 1. 作者：ModestCoder_（4星）
**亮点**：
- 线性筛法预处理最大质因数，时间复杂度$O(n)$
- 简洁的区间枚举和最小值维护
- 代码结构清晰易读

**核心代码**：
```cpp
int flag[maxn], a[maxn]; // flag标记是否为合数，a存储最大质因数
for (int i = 2; i <= n; ++i) {
    if (!flag[i]) prime[++tot] = a[i] = i;
    for (int j = 1; j <= tot && i*prime[j] <= n; ++j) {
        flag[i*prime[j]] = 1;
        a[i*prime[j]] = a[i]; // 关键：继承生成数的最大质因数
        if (i % prime[j] == 0) break;
    }
}
// 枚举区间求最小X0
for (int i = n - a[n] + 1; i <= n; ++i)
    if (flag[i]) ans = min(ans, i - a[i] + 1);
```

#### 2. 作者：Patrickpwq（4星）
**亮点**：
- 线性筛与位标记结合，节省空间
- 明确注释说明逆向推导逻辑
- 处理边界情况严谨

**代码亮点**：
```cpp
bitset <1000005> is; // 位标记节省空间
big[i*prime[j]] = big[i]; // 记录最大质因数
// 枚举范围时自动排除质数情况
for(int i = n - big[n] + 1; i <= n; i++)
    if(is[i]) ans = min(ans, i - big[i] + 1);
```

---

### 关键技巧总结
1. **线性筛预处理**：在筛质数时同步记录每个数的最大质因数，通过继承生成数的最大质因数实现$O(n)$预处理
2. **逆向区间计算**：$X_{i}$的可能取值范围为$[X_{i+1}-P_{i+1}+1, X_{i+1}]$，利用最大质因数缩小枚举范围
3. **剪枝优化**：仅需处理合数的$X_1$，因为质数的$X_1$无法继续缩小$X_0$

---

### 同类题目推荐
1. P1075 [质因数分解](https://www.luogu.com.cn/problem/P1075) - 基础质因数处理
2. P2568 [GCD](https://www.luogu.com.cn/problem/P2568) - 质数筛法与数论结合
3. P3601 [签到题](https://www.luogu.com.cn/problem/P3601) - 区间质因数预处理技巧

---

### 心得摘录
> "在线性筛质数的时候还要把所有合数的最大质因子处理出来" —— 预处理技巧的关键在于同步记录属性，而非单独计算

> "分解质因数的方法在$X_2$很大时效率低" —— 线性筛法预处理显著优于即时分解质因数的方法

> "注意$X_0$必须≥3的边界判断" —— 逆向推导时容易忽略初始条件的约束

---
处理用时：64.23秒