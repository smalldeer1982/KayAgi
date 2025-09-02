# 题目信息

# Table Tennis Game 2

## 题目描述

Misha and Vanya have played several table tennis sets. Each set consists of several serves, each serve is won by one of the players, he receives one point and the loser receives nothing. Once one of the players scores exactly $ k $ points, the score is reset and a new set begins.

Across all the sets Misha scored $ a $ points in total, and Vanya scored $ b $ points. Given this information, determine the maximum number of sets they could have played, or that the situation is impossible.

Note that the game consisted of several complete sets.

## 说明/提示

Note that the rules of the game in this problem differ from the real table tennis game, for example, the rule of "balance" (the winning player has to be at least two points ahead to win a set) has no power within the present problem.

## 样例 #1

### 输入

```
11 11 5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
11 2 3
```

### 输出

```
-1
```

# AI分析结果



## 题目中文翻译
# 乒乓球游戏 2

## 题目描述

Misha 和 Vanya 进行了若干局乒乓球比赛。每局由多次发球组成，每次发球由其中一位选手得分，得1分，败者不得分。当某位选手的得分恰好达到 $k$ 分时，该局结束，得分重置并开始新的一局。

已知在所有比赛结束后，Misha 总得分为 $a$，Vanya 总得分为 $b$。根据这些信息，判断他们可能进行的最多完整局数，或该情况不可能发生。

## 说明/提示

注意：本题的规则与实际乒乓球比赛不同，例如不需要"净胜两分"规则。

## 样例 #1

### 输入
```
11 11 5
```

### 输出
```
1
```

## 样例 #2

### 输入
```
11 2 3
```

### 输出
```
-1
```

## 算法分类
数学

---

## 题解分析与结论

### 核心逻辑
1. **总局数计算**：最大可能局数为 $\lfloor a/k \rfloor + \lfloor b/k \rfloor$
2. **无效条件判断**：
   - 双方得分均小于 $k$ 时无解
   - 当一方得分不足 $k$ 时，另一方得分必须是 $k$ 的倍数

### 最优思路
通过数学整除特性快速判断边界条件：
- 双方得分均需满足至少一方的完整局数要求
- 当一方无法形成完整局时，另一方必须能整除 $k$ 才能保证剩余得分合法

---

## 精选题解

### 题解作者：DPseud（★★★★☆）
**关键亮点**：  
使用三目运算符简化条件判断，代码紧凑且正确处理所有边界情况  
**核心代码**：
```cpp
cout<<(((a>=k&&b>=k)||(a>=k&&b<k&&a%k==0)||(b>=k&&a<k&&b%k==0))?a/k+b/k:-1);
```
**实现思路**：  
组合三个有效条件（双方均达标/单方达标且余数合法）直接返回计算值，否则返回-1

---

### 题解作者：_Haoomff_（★★★★☆）
**关键亮点**：  
清晰的if-else结构便于理解，分情况处理所有无效场景  
**核心代码**：
```cpp
if(a<k&&b<k)cout<<-1;
else if(a/k==0&&b%k!=0)cout<<-1;
else if(b/k==0&&a%k!=0)cout<<-1;
else cout<<a/k+b/k;
```
**实现思路**：  
逐层排除无效情况（双方不足k/单方不足且余数不整除）

---

## 关键技巧总结
1. **整除特性应用**：利用 $a/k$ 和 $b/k$ 快速计算基础局数
2. **余数合法性验证**：当一方无法形成完整局时，通过余数判断对方能否容纳剩余得分
3. **条件组合优化**：将多种有效情况合并判断减少代码冗余

---

## 相似题目推荐
1. P1008 三连击（数学排列）
2. P1031 均分纸牌（整除与贪心）
3. P1087 FBI树（构造与分治）

---
处理用时：363.08秒