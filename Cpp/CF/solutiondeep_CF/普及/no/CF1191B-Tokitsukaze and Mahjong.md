# 题目信息

# Tokitsukaze and Mahjong

## 题目描述

Tokitsukaze is playing a game derivated from Japanese mahjong. In this game, she has three tiles in her hand. Each tile she owns is a suited tile, which means it has a suit (manzu, pinzu or souzu) and a number (a digit ranged from $ 1 $ to $ 9 $ ). In this problem, we use one digit and one lowercase letter, which is the first character of the suit, to represent a suited tile. All possible suited tiles are represented as 1m, 2m, $ \ldots $ , 9m, 1p, 2p, $ \ldots $ , 9p, 1s, 2s, $ \ldots $ , 9s.

In order to win the game, she must have at least one mentsu (described below) in her hand, so sometimes she should draw extra suited tiles. After drawing a tile, the number of her tiles increases by one. She can draw any tiles she wants, including those already in her hand.

Do you know the minimum number of extra suited tiles she needs to draw so that she can win?

Here are some useful definitions in this game:

- A mentsu, also known as meld, is formed by a koutsu or a shuntsu;
- A koutsu, also known as triplet, is made of three identical tiles, such as \[1m, 1m, 1m\], however, \[1m, 1p, 1s\] or \[1m, 4m, 7m\] is NOT a koutsu;
- A shuntsu, also known as sequence, is made of three sequential numbered tiles in the same suit, such as \[1m, 2m, 3m\] and \[5s, 7s, 6s\], however, \[9m, 1m, 2m\] or \[1m, 2p, 3s\] is NOT a shuntsu.

Some examples:

- \[2m, 3p, 2s, 4m, 1s, 2s, 4s\] — it contains no koutsu or shuntsu, so it includes no mentsu;
- \[4s, 3m, 3p, 4s, 5p, 4s, 5p\] — it contains a koutsu, \[4s, 4s, 4s\], but no shuntsu, so it includes a mentsu;
- \[5p, 5s, 9m, 4p, 1s, 7p, 7m, 6p\] — it contains no koutsu but a shuntsu, \[5p, 4p, 6p\] or \[5p, 7p, 6p\], so it includes a mentsu.

Note that the order of tiles is unnecessary and you can assume the number of each type of suited tiles she can draw is infinite.

## 说明/提示

In the first example, Tokitsukaze already has a shuntsu.

In the second example, Tokitsukaze already has a koutsu.

In the third example, Tokitsukaze can get a shuntsu by drawing one suited tile — 1p or 4p. The resulting tiles will be \[3p, 9m, 2p, 1p\] or \[3p, 9m, 2p, 4p\].

## 样例 #1

### 输入

```
1s 2s 3s
```

### 输出

```
0
```

## 样例 #2

### 输入

```
9m 9m 9m
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3p 9m 2p
```

### 输出

```
1
```

# AI分析结果

### 题目内容重写（中文）

Tokitsukaze 正在玩一种源自日本麻将的游戏。在这个游戏中，她手中有三张牌。每张牌都是花色牌，意味着它有一个花色（万子、筒子或索子）和一个数字（1到9之间的数字）。在这个问题中，我们用一个数字和一个小写字母（花色的首字母）来表示一张花色牌。所有可能的花色牌表示为：1m, 2m, ..., 9m, 1p, 2p, ..., 9p, 1s, 2s, ..., 9s。

为了赢得游戏，她手中必须至少有一个“面子”（定义如下），因此有时她需要额外抽取花色牌。抽取一张牌后，她手中的牌数增加一张。她可以抽取任何她想要的牌，包括已经在她手中的牌。

你知道她最少需要抽取多少张额外的花色牌才能赢得游戏吗？

以下是一些有用的定义：

- 一个“面子”（mentsu），也称为“顺子”或“刻子”，由一个“刻子”或“顺子”组成；
- 一个“刻子”（koutsu），也称为“三张相同的牌”，例如 [1m, 1m, 1m]，但 [1m, 1p, 1s] 或 [1m, 4m, 7m] 不是“刻子”；
- 一个“顺子”（shuntsu），也称为“连续的三张牌”，由同一花色中三个连续数字的牌组成，例如 [1m, 2m, 3m] 和 [5s, 7s, 6s]，但 [9m, 1m, 2m] 或 [1m, 2p, 3s] 不是“顺子”。

### 算法分类
模拟

### 题解分析与结论

本题的核心是通过模拟来判断最少需要抽取多少张牌才能组成一个“面子”。由于牌的种类和数量有限，可以通过枚举所有可能的情况来解决问题。大多数题解都采用了分类讨论的方式，通过判断牌的花色和数字关系来确定是否需要抽取牌以及抽取的数量。

### 精选题解

#### 题解1：作者：GONGX (赞：5)
**星级：4.5**
**关键亮点：**
- 通过排序简化了判断逻辑，先按花色排序，再按数字排序。
- 详细分类讨论了所有可能的情况，逻辑清晰。
- 代码简洁，易于理解。

**核心代码：**
```cpp
sort(a,a+3,cmp);
if(a[0]==a[1]&&a[1]==a[2])puts("0");
else if(a[0][1]==a[1][1]&&a[0][1]==a[2][1]&&a[0][0]+1==a[1][0]&&a[1][0]+1==a[2][0])puts("0");
else{
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(i==j||a[i][1]!=a[j][1])continue;
            if(a[i]==a[j]){puts("1");return 0;}
            else if(a[i][1]==a[j][1]&&(a[i][0]+1==a[j][0]||a[i][0]+2==a[j][0])){puts("1");return 0;}
        }
    }puts("2");
}
```

#### 题解2：作者：hsfzLZH1 (赞：3)
**星级：4**
**关键亮点：**
- 使用二维数组记录牌的出现次数，简化了判断逻辑。
- 通过枚举花色和数字的最小值来计算需要补全的牌数。
- 代码结构清晰，逻辑严谨。

**核心代码：**
```cpp
for(int i=1;i<=3;i++)scanf(" %c%c",s[i]+1,s[i]+2),tf[(int)s[i][1]][(int)s[i][2]]++;
for(int i=0;i<128;i++)for(int j=0;j<128;j++)maxx=max(maxx,tf[i][j]);
ans=3-maxx;
for(int j=0;j<128;j++){
    maxx=0;
    for(int i=0;i<128;i++){
        if(tf[i][j])maxx++;
        else maxx=0;
        ans=min(ans,3-maxx);
        if(i-2>=0&&tf[i][j]&&tf[i-2][j])ans=min(ans,1);
    }
}
printf("%d\n",ans);
```

#### 题解3：作者：Alex_Wei (赞：2)
**星级：4**
**关键亮点：**
- 通过排序和简单的条件判断，快速确定需要抽取的牌数。
- 代码简洁，逻辑清晰，易于理解。

**核心代码：**
```cpp
sort(a,a+3,cmp);
if(a[0]==a[1]&&a[1]==a[2])cout<<0,exit(0);
if(a[0][1]==a[1][1]&&a[1][1]==a[2][1]&&a[0][0]+1==a[1][0]&&a[1][0]+1==a[2][0])cout<<0,exit(0);
if(a[0][1]==a[1][1]&&a[0][0]+1==a[1][0])cout<<1,exit(0);
if(a[1][1]==a[2][1]&&a[1][0]+1==a[2][0])cout<<1,exit(0);
if(a[0][1]==a[1][1]&&a[0][0]+2==a[1][0])cout<<1,exit(0);
if(a[1][1]==a[2][1]&&a[1][0]+2==a[2][0])cout<<1,exit(0);
if(a[0]==a[1]||a[1]==a[2])cout<<1,exit(0);
cout<<2;
```

### 最优关键思路
通过排序和分类讨论，快速判断是否需要抽取牌以及抽取的数量。排序可以简化判断逻辑，分类讨论则确保所有情况都被覆盖。

### 可拓展之处
类似的问题可以通过枚举和分类讨论来解决，尤其是在数据量较小的情况下。这类问题通常需要仔细分析所有可能的情况，并设计相应的判断条件。

### 推荐题目
1. [P1191 麻将](https://www.luogu.com.cn/problem/P1191)
2. [P1192 麻将游戏](https://www.luogu.com.cn/problem/P1192)
3. [P1193 麻将游戏2](https://www.luogu.com.cn/problem/P1193)

### 个人心得
- **调试经历**：在分类讨论时，容易遗漏某些特殊情况，导致结果错误。通过仔细检查每种情况，可以避免这类错误。
- **踩坑教训**：在排序时，需要注意排序规则，确保所有情况都被正确处理。
- **顿悟感想**：通过枚举和分类讨论，可以有效地解决这类问题，尤其是在数据量较小的情况下。

---
处理用时：50.64秒