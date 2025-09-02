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



**算法分类**：组合数学

---

### 题解思路与算法要点
1. **模型转化**：  
   将比赛视为二叉树结构，每个叶子节点到根的路径对应一个二进制数（左胜为0，右胜为1）。赞助商修改k次等价于在二进制数中选最多k个位将0变为1，使得对应节点成为冠军。

2. **组合数核心**：  
   最终答案为所有二进制数中0的数量≤k的情况数，即 $\sum_{i=0}^{\min(k,n)} C(n,i)$。当 $k \geq n$ 时所有情况均合法，答案为 $2^n$。

3. **快速计算组合数**：  
   预处理阶乘数组和逆元数组，通过 $C(n,i) = \frac{n!}{i!(n-i)!}$ 快速计算组合数。利用费马小定理求逆元实现除法取模。

---

### 题解评分（≥4星）
1. **Hedgehog_210508（5星）**  
   - 思路清晰，代码简洁高效  
   - 预处理阶乘数组，直接累加组合数  
   - 特判 $k \geq n$ 的情况

2. **DaiRuiChen007（5星）**  
   - 完整数学推导，规范代码结构  
   - 预处理阶乘+逆元数组，线性时间复杂度  
   - 清晰的组合数计算函数

3. **Plozia（4星）**  
   - 详细数学证明，代码结构规范  
   - 利用逆元预处理优化计算  
   - 缺乏对k≥n的特判说明（代码中实际处理）

---

### 最优思路提炼
**关键技巧**：  
- **二进制路径模型**：将比赛路径抽象为二进制数，0表示需要修改的次数。  
- **组合数前缀和**：通过 $\sum_{i=0}^k C(n,i)$ 快速计算合法情况数。  
- **费马小定理优化**：预处理阶乘与逆元数组实现O(1)组合数计算。

**代码实现要点**：  
```cpp
// 预处理阶乘与逆元
fact[0] = 1;
for(int i = 1; i <= n; ++i) 
    fact[i] = fact[i-1] * i % MOD;
inv[n] = ksm(fact[n], MOD-2);
for(int i = n-1; i >= 0; --i)
    inv[i] = inv[i+1] * (i+1) % MOD;

// 计算组合数前缀和
LL ans = 0;
for(int i = 0; i <= min(n,k); ++i)
    ans = (ans + fact[n] * inv[i] % MOD * inv[n-i] % MOD) % MOD;
```

---

### 同类型题推荐
1. [CF1342E - Placing Rooks](https://www.luogu.com.cn/problem/CF1342E)（组合数+容斥原理）  
2. [P3197 越狱](https://www.luogu.com.cn/problem/P3197)（快速幂+组合计数）  
3. [AT_abc281G - Farthest City](https://www.luogu.com.cn/problem/AT_abc281G)（树形结构+组合DP）

---

### 可视化算法演示
**动画设计**：  
1. **树形结构**：展示二叉树比赛路径，高亮当前计算的组合数对应的路径（如C(3,1)时高亮所有单右转路径）。  
2. **像素风格**：  
   - 使用16色像素画风绘制二叉树，路径用红蓝区分原始/修改状态  
   - 每步计算时，对应路径闪烁，右侧显示累加的组合数值  
3. **音效交互**：  
   - 组合数累加时播放8-bit“收集金币”音效  
   - 特判k≥n时播放胜利音乐

**关键帧示例**：  
```
[初始状态] 展示完整二叉树，所有路径为左胜（红色）
[计算C(n,1)] 高亮所有含1次右转的路径，播放"滴"声
[累加完成] 显示ΣC(n,i)数值，背景变绿表示计算完成
```

---

### 个人心得摘录
**Hedgehog_210508**：  
> "突然意识到k>n的情况可以直接返回2^n，节省了不必要的计算，这个特判让代码效率大幅提升"

**DaiRuiChen007**：  
> "将路径抽象为二进制数的0/1序列是关键，这个转化让复杂的树形问题变成了简单的组合计数问题"

---
处理用时：65.68秒