# 题目信息

# Need for Pink Slips

## 题目描述

After defeating a Blacklist Rival, you get a chance to draw $ 1 $ reward slip out of $ x $ hidden valid slips. Initially, $ x=3 $ and these hidden valid slips are Cash Slip, Impound Strike Release Marker and Pink Slip of Rival's Car. Initially, the probability of drawing these in a random guess are $ c $ , $ m $ , and $ p $ , respectively. There is also a volatility factor $ v $ . You can play any number of Rival Races as long as you don't draw a Pink Slip. Assume that you win each race and get a chance to draw a reward slip. In each draw, you draw one of the $ x $ valid items with their respective probabilities. Suppose you draw a particular item and its probability of drawing before the draw was $ a $ . Then,

- If the item was a Pink Slip, the quest is over, and you will not play any more races.
- Otherwise, 
  1. If $ a\leq v $ , the probability of the item drawn becomes $ 0 $ and the item is no longer a valid item for all the further draws, reducing $ x $ by $ 1 $ . Moreover, the reduced probability $ a $ is distributed equally among the other remaining valid items.
  2. If $ a > v $ , the probability of the item drawn reduces by $ v $ and the reduced probability is distributed equally among the other valid items.

For example,

- If $ (c,m,p)=(0.2,0.1,0.7) $ and $ v=0.1 $ , after drawing Cash, the new probabilities will be $ (0.1,0.15,0.75) $ .
- If $ (c,m,p)=(0.1,0.2,0.7) $ and $ v=0.2 $ , after drawing Cash, the new probabilities will be $ (Invalid,0.25,0.75) $ .
- If $ (c,m,p)=(0.2,Invalid,0.8) $ and $ v=0.1 $ , after drawing Cash, the new probabilities will be $ (0.1,Invalid,0.9) $ .
- If $ (c,m,p)=(0.1,Invalid,0.9) $ and $ v=0.2 $ , after drawing Cash, the new probabilities will be $ (Invalid,Invalid,1.0) $ .

You need the cars of Rivals. So, you need to find the expected number of races that you must play in order to draw a pink slip.

## 说明/提示

For the first test case, the possible drawing sequences are:

- P with a probability of $ 0.6 $ ;
- CP with a probability of $ 0.2\cdot 0.7 = 0.14 $ ;
- CMP with a probability of $ 0.2\cdot 0.3\cdot 0.9 = 0.054 $ ;
- CMMP with a probability of $ 0.2\cdot 0.3\cdot 0.1\cdot 1 = 0.006 $ ;
- MP with a probability of $ 0.2\cdot 0.7 = 0.14 $ ;
- MCP with a probability of $ 0.2\cdot 0.3\cdot 0.9 = 0.054 $ ;
- MCCP with a probability of $ 0.2\cdot 0.3\cdot 0.1\cdot 1 = 0.006 $ .

 So, the expected number of races is equal to $ 1\cdot 0.6 + 2\cdot 0.14 + 3\cdot 0.054 + 4\cdot 0.006 + 2\cdot 0.14 + 3\cdot 0.054 + 4\cdot 0.006 = 1.532 $ .For the second test case, the possible drawing sequences are:

- P with a probability of $ 0.4 $ ;
- CP with a probability of $ 0.4\cdot 0.6 = 0.24 $ ;
- CMP with a probability of $ 0.4\cdot 0.4\cdot 1 = 0.16 $ ;
- MP with a probability of $ 0.2\cdot 0.5 = 0.1 $ ;
- MCP with a probability of $ 0.2\cdot 0.5\cdot 1 = 0.1 $ .

So, the expected number of races is equal to $ 1\cdot 0.4 + 2\cdot 0.24 + 3\cdot 0.16 + 2\cdot 0.1 + 3\cdot 0.1 = 1.86 $ .

## 样例 #1

### 输入

```
4
0.2 0.2 0.6 0.2
0.4 0.2 0.4 0.8
0.4998 0.4998 0.0004 0.1666
0.3125 0.6561 0.0314 0.2048```

### 输出

```
1.532000000000
1.860000000000
5.005050776521
4.260163673896```

# AI分析结果

### 题目内容重写

#### 题目描述

在击败一个黑名单对手后，你有机会从 $x$ 个隐藏的有效奖励券中抽取 $1$ 张。初始时，$x=3$，这些隐藏的有效奖励券分别是现金券、扣押解除标记和对手汽车的粉色券。初始时，随机抽取这些奖励券的概率分别为 $c$、$m$ 和 $p$。此外，还有一个波动因子 $v$。只要你不抽到粉色券，你可以进行任意次数的对手比赛。假设你每次比赛都获胜并获得一次抽取奖励券的机会。在每次抽取中，你会根据各自的概率抽取 $x$ 个有效奖励券中的一个。假设你抽取了某个奖励券，且其抽取前的概率为 $a$，那么：

- 如果抽取的是粉色券，任务结束，你将不再进行任何比赛。
- 否则：
  1. 如果 $a\leq v$，该奖励券的抽取概率变为 $0$，并且该奖励券在后续抽取中不再有效，$x$ 减 $1$。此外，减少的概率 $a$ 将平均分配给其他剩余的有效奖励券。
  2. 如果 $a > v$，该奖励券的抽取概率减少 $v$，减少的概率将平均分配给其他有效奖励券。

例如：

- 如果 $(c,m,p)=(0.2,0.1,0.7)$ 且 $v=0.1$，在抽取现金券后，新的概率将为 $(0.1,0.15,0.75)$。
- 如果 $(c,m,p)=(0.1,0.2,0.7)$ 且 $v=0.2$，在抽取现金券后，新的概率将为 $(Invalid,0.25,0.75)$。
- 如果 $(c,m,p)=(0.2,Invalid,0.8)$ 且 $v=0.1$，在抽取现金券后，新的概率将为 $(0.1,Invalid,0.9)$。
- 如果 $(c,m,p)=(0.1,Invalid,0.9)$ 且 $v=0.2$，在抽取现金券后，新的概率将为 $(Invalid,Invalid,1.0)$。

你需要对手的汽车，因此你需要找到为了抽取粉色券而必须进行的比赛的期望次数。

#### 说明/提示

对于第一个测试用例，可能的抽取序列为：

- P 的概率为 $0.6$；
- CP 的概率为 $0.2\cdot 0.7 = 0.14$；
- CMP 的概率为 $0.2\cdot 0.3\cdot 0.9 = 0.054$；
- CMMP 的概率为 $0.2\cdot 0.3\cdot 0.1\cdot 1 = 0.006$；
- MP 的概率为 $0.2\cdot 0.7 = 0.14$；
- MCP 的概率为 $0.2\cdot 0.3\cdot 0.9 = 0.054$；
- MCCP 的概率为 $0.2\cdot 0.3\cdot 0.1\cdot 1 = 0.006$。

因此，期望的比赛次数为 $1\cdot 0.6 + 2\cdot 0.14 + 3\cdot 0.054 + 4\cdot 0.006 + 2\cdot 0.14 + 3\cdot 0.054 + 4\cdot 0.006 = 1.532$。

对于第二个测试用例，可能的抽取序列为：

- P 的概率为 $0.4$；
- CP 的概率为 $0.4\cdot 0.6 = 0.24$；
- CMP 的概率为 $0.4\cdot 0.4\cdot 1 = 0.16$；
- MP 的概率为 $0.2\cdot 0.5 = 0.1$；
- MCP 的概率为 $0.2\cdot 0.5\cdot 1 = 0.1$。

因此，期望的比赛次数为 $1\cdot 0.4 + 2\cdot 0.24 + 3\cdot 0.16 + 2\cdot 0.1 + 3\cdot 0.1 = 1.86$。

#### 样例 #1

##### 输入

```
4
0.2 0.2 0.6 0.2
0.4 0.2 0.4 0.8
0.4998 0.4998 0.0004 0.1666
0.3125 0.6561 0.0314 0.2048
```

##### 输出

```
1.532000000000
1.860000000000
5.005050776521
4.260163673896
```

### 算法分类
概率论、深度优先搜索（DFS）

### 题解分析与结论

本题的核心是通过模拟抽奖过程，计算期望的抽奖次数。由于每次抽奖后概率会发生变化，且波动因子 $v$ 较大，导致抽奖次数不会太多，因此可以通过深度优先搜索（DFS）来枚举所有可能的抽奖序列，并计算期望值。

### 所选题解

#### 题解1：5ab_juruo (4星)

**关键亮点**：
- 使用DFS模拟抽奖过程，枚举所有可能的抽奖序列。
- 通过递归计算期望值，代码简洁明了。
- 处理了概率变化的细节，特别是当概率小于 $v$ 时的特殊情况。

**核心代码**：
```cpp
db dfs(db c, db m, db p)
{
    db ret = 0;
    
    if (c > v)
    {
        if (m > eps)
            ret += c * dfs(c - v, m + v / 2, p + v / 2);
        else
            ret += c * dfs(c - v, 0, p + v);
    }
    else if (c > eps)
    {
        if (m > eps)
            ret += c * dfs(0, m + c / 2, p + c / 2);
        else
            ret += c;
    }
    
    if (m > v)
    {
        if (c > eps)
            ret += m * dfs(c + v / 2, m - v, p + v / 2);
        else
            ret += m * dfs(0, m - v, p + v);
    }
    else if (m > eps)
    {
        if (c > eps)
            ret += m * dfs(c + m / 2, 0, p + m / 2);
        else
            ret += m;
    }
    
    return ret + 1;
}
```

#### 题解2：言琢დ (4星)

**关键亮点**：
- 详细解释了题意，特别是概率变化的规则。
- 使用DFS进行模拟，并处理了浮点数精度问题。
- 代码结构清晰，注释详细，便于理解。

**核心代码**：
```cpp
double go(double c, double m, double p, double t){
    if (equal(p, 1)) return t; // 中奖率 100 %
    double ans = 0;
    if (!equal(c, 0))
        if (c <= v)
            if (equal(m, 0)) ans += c * go(0, 0, 1, t+1); // c 给 t
        else ans += c * go(0, m + c / 2, p + c / 2, t+1); // c 均分给 m 和 t
        else
            if (equal(m, 0)) ans += c * go(c - v, 0, p + v, t+1); // c 按 v 给 p
        else ans += c * go(c - v, m + v / 2, p + v / 2, t+1); // c 按 v 均分
    if (!equal(m, 0))
        if (m <= v)
            if (equal(c, 0)) ans += m * go(0, 0, 1, t+1); // m 给 p
        else ans += m * go(c + m / 2, 0, p + m / 2, t+1); // m 均分给 c 和 t
        else
            if (equal(c, 0)) ans += m * go(0, m - v, p + v, t+1); // m 按 v 给 p
        else ans += m * go(c + v / 2, m - v, p + v / 2, t+1); // m 按 v 均分给 c 和 t
    ans += p * t; // 直接抽中 p
    return ans;
}
```

#### 题解3：liuli688 (4星)

**关键亮点**：
- 使用DFS模拟抽奖过程，处理了概率变化的细节。
- 代码简洁，逻辑清晰，易于理解。
- 通过递归计算期望值，处理了浮点数精度问题。

**核心代码**：
```cpp
void dfs(double c, double m, double p, double P, int step)
{
    if (c > 1e-6)
        dfs(std::max(c - v, 0.0), m + (m < 1e-6 ? 0 : std::min(c, v) / 2), p + std::min(c, v) / 2 * ((m < 1e-6) + 1), P * c, step + 1);
    if (m > 1e-6)
        dfs(c + (c < 1e-6 ? 0 : std::min(m, v) / 2), std::max(m - v, 0.0), p + std::min(m, v) / 2 * ((c < 1e-6) + 1), P * m, step + 1);
    ans += P * p * step;
}
```

### 最优关键思路或技巧

- **DFS模拟**：通过深度优先搜索模拟所有可能的抽奖序列，计算期望值。
- **概率变化处理**：根据题意，处理每次抽奖后概率的变化，特别是当概率小于 $v$ 时的特殊情况。
- **浮点数精度处理**：使用一个极小的误差量（如 `eps = 1e-10`）来判断浮点数是否相等，避免精度问题。

### 可拓展之处

- **类似问题**：可以扩展到其他类似的概率问题，如多阶段决策问题、马尔可夫链等。
- **优化方法**：可以考虑使用动态规划（DP）来优化DFS，减少重复计算。

### 推荐题目

1. [P1850 换教室](https://www.luogu.com.cn/problem/P1850)
2. [P3802 小魔女帕琪](https://www.luogu.com.cn/problem/P3802)
3. [P4316 绿豆蛙的归宿](https://www.luogu.com.cn/problem/P4316)

---
处理用时：73.44秒