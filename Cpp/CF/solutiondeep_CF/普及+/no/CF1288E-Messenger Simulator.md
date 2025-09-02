# 题目信息

# Messenger Simulator

## 题目描述

Polycarp is a frequent user of the very popular messenger. He's chatting with his friends all the time. He has $ n $ friends, numbered from $ 1 $ to $ n $ .

Recall that a permutation of size $ n $ is an array of size $ n $ such that each integer from $ 1 $ to $ n $ occurs exactly once in this array.

So his recent chat list can be represented with a permutation $ p $ of size $ n $ . $ p_1 $ is the most recent friend Polycarp talked to, $ p_2 $ is the second most recent and so on.

Initially, Polycarp's recent chat list $ p $ looks like $ 1, 2, \dots, n $ (in other words, it is an identity permutation).

After that he receives $ m $ messages, the $ j $ -th message comes from the friend $ a_j $ . And that causes friend $ a_j $ to move to the first position in a permutation, shifting everyone between the first position and the current position of $ a_j $ by $ 1 $ . Note that if the friend $ a_j $ is in the first position already then nothing happens.

For example, let the recent chat list be $ p = [4, 1, 5, 3, 2] $ :

- if he gets messaged by friend $ 3 $ , then $ p $ becomes $ [3, 4, 1, 5, 2] $ ;
- if he gets messaged by friend $ 4 $ , then $ p $ doesn't change $ [4, 1, 5, 3, 2] $ ;
- if he gets messaged by friend $ 2 $ , then $ p $ becomes $ [2, 4, 1, 5, 3] $ .

For each friend consider all position he has been at in the beginning and after receiving each message. Polycarp wants to know what were the minimum and the maximum positions.

## 说明/提示

In the first example, Polycarp's recent chat list looks like this:

- $ [1, 2, 3, 4, 5] $
- $ [3, 1, 2, 4, 5] $
- $ [5, 3, 1, 2, 4] $
- $ [1, 5, 3, 2, 4] $
- $ [4, 1, 5, 3, 2] $

So, for example, the positions of the friend $ 2 $ are $ 2, 3, 4, 4, 5 $ , respectively. Out of these $ 2 $ is the minimum one and $ 5 $ is the maximum one. Thus, the answer for the friend $ 2 $ is a pair $ (2, 5) $ .

In the second example, Polycarp's recent chat list looks like this:

- $ [1, 2, 3, 4] $
- $ [1, 2, 3, 4] $
- $ [2, 1, 3, 4] $
- $ [4, 2, 1, 3] $

## 样例 #1

### 输入

```
5 4
3 5 1 4```

### 输出

```
1 3
2 5
1 4
1 5
1 5```

## 样例 #2

### 输入

```
4 3
1 2 4```

### 输出

```
1 3
1 2
3 4
1 4```

# AI分析结果

### 题目内容中文重写
# 消息模拟器

## 题目描述
波利卡普是一款非常流行的即时通讯软件的常客。他总是和朋友们聊天。他有 $n$ 个朋友，编号从 $1$ 到 $n$。

回顾一下，长度为 $n$ 的排列是一个长度为 $n$ 的数组，使得从 $1$ 到 $n$ 的每个整数在这个数组中恰好出现一次。

所以他最近的聊天列表可以用一个长度为 $n$ 的排列 $p$ 来表示。$p_1$ 是波利卡普最近交谈的朋友，$p_2$ 是第二近交谈的朋友，依此类推。

最初，波利卡普的最近聊天列表 $p$ 看起来像 $1, 2, \dots, n$（换句话说，它是一个单位排列）。

在那之后，他收到 $m$ 条消息，第 $j$ 条消息来自朋友 $a_j$。这会导致朋友 $a_j$ 移动到排列的第一个位置，将第一个位置和 $a_j$ 当前位置之间的每个人都向后移动一位。注意，如果朋友 $a_j$ 已经在第一个位置，那么什么都不会发生。

例如，假设最近的聊天列表是 $p = [4, 1, 5, 3, 2]$：
- 如果他收到朋友 $3$ 的消息，那么 $p$ 变为 $[3, 4, 1, 5, 2]$；
- 如果他收到朋友 $4$ 的消息，那么 $p$ 不变，仍然是 $[4, 1, 5, 3, 2]$；
- 如果他收到朋友 $2$ 的消息，那么 $p$ 变为 $[2, 4, 1, 5, 3]$。

对于每个朋友，考虑他在开始时以及收到每条消息后所处的所有位置。波利卡普想知道每个朋友所处位置的最小值和最大值。

## 说明/提示
在第一个示例中，波利卡普的最近聊天列表如下：
- $[1, 2, 3, 4, 5]$
- $[3, 1, 2, 4, 5]$
- $[5, 3, 1, 2, 4]$
- $[1, 5, 3, 2, 4]$
- $[4, 1, 5, 3, 2]$

所以，例如，朋友 $2$ 的位置分别是 $2, 3, 4, 4, 5$。在这些位置中，$2$ 是最小值，$5$ 是最大值。因此，朋友 $2$ 的答案是一对 $(2, 5)$。

在第二个示例中，波利卡普的最近聊天列表如下：
- $[1, 2, 3, 4]$
- $[1, 2, 3, 4]$
- $[2, 1, 3, 4]$
- $[4, 2, 1, 3]$

## 样例 #1
### 输入
```
5 4
3 5 1 4
```
### 输出
```
1 3
2 5
1 4
1 5
1 5
```

## 样例 #2
### 输入
```
4 3
1 2 4
```
### 输出
```
1 3
1 2
3 4
1 4
```

### 算法分类
模拟

### 综合分析与结论
这些题解主要围绕模拟消息接收过程来计算每个朋友出现位置的最小值和最大值。思路上，大家普遍先确定最小值的计算方法：若朋友发过消息，最小值为 $1$，否则为其初始编号。对于最大值的计算，不同题解采用了不同方法，如直接模拟、树状数组或线段树维护位置信息、统计区间不同数字个数等。

### 所选题解
- **作者：YLWang (赞：31)，4星**
    - **关键亮点**：思路清晰，通过在数组左端添加虚点，利用树状数组维护点的状态，进而确定每个朋友在原数组中的位置，代码实现简洁。
    - **个人心得**：认为正解很有创造力，两个月没碰 OI 水平下降，自认为思路比其他题解清晰。

### 重点代码
```cpp
const int MAXN = 600005;
int n, m, mini[MAXN], maxi[MAXN], c[MAXN], pos[MAXN];
void update(int x, int v) {for(; x <= n+m; x += (x&-x)) c[x] += v;}
int query(int x) {int ans = 0;for(; x; x -= (x&-x)) ans += c[x];return ans;}
signed main()
{
    cin >> n >> m;
    For(i, 1, n) mini[i] = maxi[i] = i, pos[i] = m+i, update(pos[i], 1);
    int now = m;
    For(k, 1, m) {
        int i = read(); mini[i] = 1;
        ckmax(maxi[i], query(pos[i]));
        update(pos[i], -1); 
        pos[i] = now--;
        update(pos[i], 1);
    }
    For(i, 1, n) ckmax(maxi[i], query(pos[i]));
    For(i, 1, n) printf("%d %d\n", mini[i], maxi[i]);
    return 0;
}
```
**核心实现思想**：在数组左端添加 $m$ 个虚点，将实际有点的位置标记为 $1$，无点的位置标记为 $0$。通过树状数组的 `update` 函数更新点的状态，`query` 函数查询某个位置前 $1$ 的个数，从而确定朋友在原数组中的位置。在处理每条消息时，更新朋友的位置和状态，并更新其最大值。最后再遍历一次所有朋友，更新其最大值，输出每个朋友的最小值和最大值。

### 关键思路或技巧
- **添加虚点**：在数组左端添加虚点，避免了频繁移动数组元素的麻烦，简化了位置的计算。
- **树状数组或线段树维护**：利用树状数组或线段树可以高效地进行单点修改和区间查询，从而快速确定每个朋友的位置。

### 拓展思路
同类型题可能会有不同的操作规则，如消息接收的顺序变化、消息的优先级等，但核心思路仍然是模拟操作过程，利用合适的数据结构维护状态。类似算法套路包括使用树状数组或线段树维护区间信息、处理区间不同元素个数等问题。

### 推荐题目
- [P1903 [国家集训队]数颜色](https://www.luogu.com.cn/problem/P1903)
- [P1972 [SDOI2009]HH的项链](https://www.luogu.com.cn/problem/P1972)
- [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)

---
处理用时：52.44秒