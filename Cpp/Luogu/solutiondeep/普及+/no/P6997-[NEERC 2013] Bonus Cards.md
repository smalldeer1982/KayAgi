# 题目信息

# [NEERC 2013] Bonus Cards

## 题目描述



Dmitry loves programming competitions very much. The Finals of the famed Champions League are taking place in Dmitry's home city, so he wants to visit the competition. The competition is very popular, but most tickets to the competition are reserved for VIPs and for sponsors.

For the general public tickets to the Champions League Finals are distributed in the following way. Spectators, that want to see the competition, submit their request that states the payment method they want to use to pay for their ticket. Suppose there are $n$ seats available. Several draw round are conducted. In each round every request that is not yet fulfilled receives some number of slots depending on the payment method. Then one of those slots is selected uniformly at random. The request to which this slot belongs is considered fulfilled and does not take part in subsequent drawing rounds. Draw ends after $n$ rounds or when there are no more unfulfilled requests, whichever occurs first. An International Card Processing Corporation (ICPC) is a sponsor of the Champions League. Those who chose ICPC card as a payment method receive two slots in each draw round, while users of other payment methods receive only one.

Dmitry has a card from ICPC, but he also has a card from Advanced Credit Merchandise $(ACM),$ which offers him a bonus on all his spendings. His brother Petr works in a company that conducts draw to distribute tickets, so he told Dmitry in advance how many people had already decided to use ICPC card and how many had decided to use other methods. Now Dmitry want to know the probabilities he would get a ticket if he would use his ICPC card or if he would use his ACM card, so that he can make an informed choice. His request is going to be in addition to the number of requests Petr had told him about.

Can you help?



## 说明/提示

Time limit: 1 s, Memory limit: 128 MB. 



## 样例 #1

### 输入

```
1 1 2
```

### 输出

```
0.3333333333333333
0.2
```

## 样例 #2

### 输入

```
10 10 10
```

### 输出

```
0.5870875690480144
0.3640355515319861
```

# AI分析结果

### 算法分类
概率论、动态规划

### 综合分析与结论
本题的核心在于计算Dmitry在两种不同支付方式下获得门票的概率。由于每轮抽奖的概率分布与剩余人数和支付方式相关，因此需要使用动态规划（DP）来模拟每一轮的抽奖过程，并计算Dmitry最终被选中的概率。

### 所选题解
#### 1. 作者：fervency (赞：5)
**星级：5星**
**关键亮点：**
- 使用动态规划（DP）模拟每一轮的抽奖过程，状态设计清晰，转移方程合理。
- 代码简洁明了，逻辑清晰，易于理解。
- 通过状态转移方程准确计算了Dmitry在两种支付方式下的中奖概率。

**核心代码：**
```cpp
for(int i=0;i<n;i++)
for(int j=0;j<=i&&j<=A;j++)
{
    if(f[i][j][0]==0) continue;
    if(A-j>0) f[i+1][j+1][0]+=f[i][j][0]*(2*(A-j)/(2*(A-j)+(B-i+j)+2));
    if(B-i+j>0) f[i+1][j][0]+=f[i][j][0]*((B-i+j)/(2*(A-j)+(B-i+j)+2));
}
```
**实现思想：**
通过状态转移方程，计算每一轮中Dmitry被选中的概率，并根据剩余人数和支付方式调整概率分布。

#### 2. 作者：Arson1st (赞：1)
**星级：4星**
**关键亮点：**
- 使用记忆化搜索（记搜）实现动态规划，逻辑清晰，易于理解。
- 状态设计合理，通过压缩状态减少空间复杂度。
- 代码结构清晰，变量命名直观，便于阅读。

**核心代码：**
```cpp
double dfs1(int x, int y, int m) {
    if (m == n) return 0;
    if (x == a) return 1;
    if (y == b + 1) return 0;
    if (f[m][x] != -1) return f[m][x];
    double all = 2.0*(a-x) + b-y;
    double won = 2.0 / all, Awon = 2.0*(a-x-1) / all, Bwon = 1.0*(b-y) / all;
    double res1 = 0, res2 = 0;
    if (x < a) res1 = dfs1(x+1, y, m+1);
    if (y < b) res2 = dfs1(x, y+1, m+1);
    f[m][x] = won + Awon * res1 + Bwon * res2;
    return f[m][x];
}
```
**实现思想：**
通过记忆化搜索，递归计算每一轮中Dmitry被选中的概率，并根据剩余人数和支付方式调整概率分布。

### 最优关键思路或技巧
- **状态设计**：通过设计状态 `f[i][j]` 表示已经进行 `i` 轮抽奖，且一类名额中有 `j` 个人被选中，能够有效地模拟每一轮的抽奖过程。
- **概率计算**：在每一轮中，根据剩余人数和支付方式调整概率分布，确保计算的准确性。
- **记忆化搜索**：通过记忆化搜索减少重复计算，提高算法效率。

### 可拓展之处
- **类似问题**：可以扩展到其他类似的概率计算问题，如多轮抽奖、不同权重的中奖概率等。
- **优化思路**：可以通过进一步优化状态转移方程，减少空间复杂度，提高计算效率。

### 推荐题目
1. [P3802 小魔女帕琪](https://www.luogu.com.cn/problem/P3802)
2. [P1850 换教室](https://www.luogu.com.cn/problem/P1850)
3. [P4550 收集邮票](https://www.luogu.com.cn/problem/P4550)

### 个人心得
- **调试经历**：在调试过程中，发现状态转移方程的设计对算法的正确性至关重要，需要仔细检查每一轮的概率计算是否正确。
- **踩坑教训**：在实现记忆化搜索时，忘记初始化状态数组，导致计算结果错误，提醒了初始化的重要性。
- **顿悟感想**：通过本题，深刻理解了动态规划在概率计算中的应用，以及状态设计对算法效率的影响。

---
处理用时：26.89秒