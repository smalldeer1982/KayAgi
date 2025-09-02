# 题目信息

# ABBC or BACB

## 题目描述

You are given a string $ s $ made up of characters $ \texttt{A} $ and $ \texttt{B} $ . Initially you have no coins. You can perform two types of operations:

- Pick a substring $ ^\dagger $ $ \texttt{AB} $ , change it to $ \texttt{BC} $ , and get a coin.
- Pick a substring $ ^\dagger $ $ \texttt{BA} $ , change it to $ \texttt{CB} $ , and get a coin.

 What is the most number of coins you can obtain? $ ^\dagger $ A substring of length $ 2 $ is a sequence of two adjacent characters of a string.

## 说明/提示

In the first test case you can perform the following operations to get $ 2 $ coins: $ $$$\color{red}{\texttt{AB}}\texttt{BA} \to \texttt{BC}\color{red}{\texttt{BA}} \to \texttt{BCCB} $ $ </p><p>In the second test case you can perform the following operation to get  $ 1 $  coin:  $ $ \color{red}{\texttt{AB}}\texttt{A} \to \texttt{BCA} $ $ </p><p>In the third test case you can perform the following operations to get  $ 3 $  coins:  $ $ \color{red}{\texttt{BA}}\texttt{ABA} \to \texttt{CBA}\color{red}{\texttt{BA}} \to \texttt{C}\color{red}{\texttt{BA}}\texttt{CB} \to \texttt{CCBCB} $ $$$

## 样例 #1

### 输入

```
8
ABBA
ABA
BAABA
ABB
AAAAAAB
BABA
B
AAA```

### 输出

```
2
1
3
1
6
2
0
0```

# AI分析结果

### 题目翻译
给定一个由字符 `A` 和 `B` 组成的字符串 $s$。一开始你没有硬币。你可以执行两种类型的操作：

- 选择子字符串 `AB`，将其改为 `BC`，并获得一枚硬币。
- 选择子字符串 `BA`，将其改为 `CB`，并获得一枚硬币。

问最多能获得多少硬币？

注意，这里说的子字符串必须是连续的。

### 算法分类
贪心

### 题解分析与结论
本题的核心思路是通过贪心策略最大化硬币的获取。大多数题解都基于以下观察：连续的 `A` 串可以通过一个 `B` 进行消除，从而获得与 `A` 数量相等的硬币。难点在于如何高效地处理字符串中的 `A` 和 `B`，并确定哪些 `A` 串可以被消除。

### 精选题解
#### 1. 作者：__Star_Sky (赞：7)
**星级：4.5**  
**关键亮点：**
- 通过观察 `AAAB` 和 `BAAA` 的消除过程，得出连续的 `A` 串可以通过一个 `B` 消除。
- 提出如果字符串以 `B` 开头或结尾，或存在 `BB` 子串，则所有 `A` 都可以被消除。
- 否则，选择最小的连续 `A` 串不消除，以最大化硬币数量。

**核心代码：**
```cpp
for(int i=1;i<=n;i++) if(a[i]=='A') cnt++;
if(flag) printf("%d\n",cnt);
else printf("%d\n",cnt-ans);
```
**实现思想：** 统计 `A` 的总数，如果满足条件则全部消除，否则减去最小的连续 `A` 串长度。

#### 2. 作者：cqbzhr (赞：5)
**星级：4**  
**关键亮点：**
- 将问题转化为找出任意两个 `B` 之间最少的 `A` 的个数，答案就是整个字符串中 `A` 的数量减去这个最小值。
- 通过枚举字符串，统计 `A` 的数量和最小连续 `A` 串的长度。

**核心代码：**
```cpp
for(int i=0;i<l;i++){
    if(s[i]=='B'){
        y++;
        k+=x;
        minn=min(minn,x);
        x=0;
    }
    else x++;
}
```
**实现思想：** 遍历字符串，统计 `A` 的数量和最小连续 `A` 串的长度，最后输出 `A` 的总数减去最小值。

#### 3. 作者：_Ink (赞：3)
**星级：4**  
**关键亮点：**
- 通过探究两种操作的特性，得出每个 `B` 可以消除其左侧或右侧的 `A` 串。
- 记录 `A` 串的个数和能够消除 `A` 串的 `B` 的个数，根据两者的关系决定是否消除所有 `A` 串。

**核心代码：**
```cpp
if(kb < ka) ans -= minlen;
cout << ans << '\n';
```
**实现思想：** 统计 `A` 串的个数和能够消除 `A` 串的 `B` 的个数，如果 `B` 的个数不足以消除所有 `A` 串，则减去最小的 `A` 串长度。

### 最优关键思路
最优思路是通过贪心策略，统计字符串中 `A` 的总数和最小连续 `A` 串的长度，然后根据 `B` 的分布情况决定是否消除所有 `A` 串。如果 `B` 的个数不足以消除所有 `A` 串，则减去最小的 `A` 串长度。

### 拓展思路
类似的问题可以通过贪心策略解决，尤其是在处理字符串中的连续字符时。例如，处理连续的 `0` 或 `1` 串时，可以通过统计最小或最大长度来优化结果。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心策略的应用。
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223) - 贪心策略的经典问题。
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803) - 贪心策略在区间选择中的应用。

---
处理用时：26.01秒