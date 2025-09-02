# 题目信息

# Turtle and an Infinite Sequence

## 题目描述

There is a sequence $ a_0, a_1, a_2, \ldots $ of infinite length. Initially $ a_i = i $ for every non-negative integer $ i $ .

After every second, each element of the sequence will simultaneously change. $ a_i $ will change to $ a_{i - 1} \mid a_i \mid a_{i + 1} $ for every positive integer $ i $ . $ a_0 $ will change to $ a_0 \mid a_1 $ . Here, $ | $ denotes [bitwise OR](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

Turtle is asked to find the value of $ a_n $ after $ m $ seconds. In particular, if $ m = 0 $ , then he needs to find the initial value of $ a_n $ . He is tired of calculating so many values, so please help him!

## 说明/提示

After $ 1 $ second, $ [a_0, a_1, a_2, a_3, a_4, a_5] $ will become $ [1, 3, 3, 7, 7, 7] $ .

After $ 2 $ seconds, $ [a_0, a_1, a_2, a_3, a_4, a_5] $ will become $ [3, 3, 7, 7, 7, 7] $ .

## 样例 #1

### 输入

```
9
0 0
0 1
0 2
1 0
5 2
10 1
20 3
1145 14
19198 10```

### 输出

```
0
1
3
1
7
11
23
1279
19455```

# AI分析结果

### 题目内容中文重写
## 乌龟与无限序列

### 题目描述
存在一个无限长的序列 $ a_0, a_1, a_2, \ldots $。初始时，对于每个非负整数 $ i $，都有 $ a_i = i $。

每秒过后，序列的每个元素都会同时发生变化。对于每个正整数 $ i $，$ a_i $ 将变为 $ a_{i - 1} \mid a_i \mid a_{i + 1} $；$ a_0 $ 将变为 $ a_0 \mid a_1 $。这里的 $ | $ 表示[按位或](https://en.wikipedia.org/wiki/Bitwise_operation#OR)。

乌龟需要找出 $ m $ 秒后 $ a_n $ 的值。特别地，如果 $ m = 0 $，则他需要找出 $ a_n $ 的初始值。他厌倦了计算这么多值，所以请你帮助他！

### 说明/提示
1 秒后，$ [a_0, a_1, a_2, a_3, a_4, a_5] $ 将变为 $ [1, 3, 3, 7, 7, 7] $。
2 秒后，$ [a_0, a_1, a_2, a_3, a_4, a_5] $ 将变为 $ [3, 3, 7, 7, 7, 7] $。

### 样例 #1
#### 输入
```
9
0 0
0 1
0 2
1 0
5 2
10 1
20 3
1145 14
19198 10
```
#### 输出
```
0
1
3
1
7
11
23
1279
19455
```

### 题解综合分析与结论
这些题解的核心思路都是先确定 $m$ 秒后 $a_n$ 的值是区间 $[\max(0, n - m), n + m]$ 内所有数的按位或结果，然后重点解决如何快速计算该区间按位或和的问题。不同题解在计算区间按位或和时采用了不同的方法。

|作者|思路|算法要点|解决难点|评分|
| ---- | ---- | ---- | ---- | ---- |
|Louis_lxy|结果是 $n - m$ 到 $n + m$ 的按位或和，通过找到 $l$ 与 $r$ 相同的最后一位，其后每一位必为 1，可 $O(\log n)$ 或 $O(1)$ 求解|令 $l = \max(n - m, 0), r = n + m$，构造长度为 $l$ 异或 $r$ 加一的二进制数，减 1 后与 $l$ 按位或|快速计算区间按位或和|4星|
|ikunTLE|从高位到低位逐位判断，若符合条件则更新答案|对于每一位，判断 $(a + b) >> i & 1$、$\max(0, a - b) >> i & 1$ 或 $(a + b - \max(0, a - b) >= (1 << i))$ 是否成立|确定每一位是否为 1|3星|
|linjunye|先明确 $m$ 秒后 $a_n$ 是区间 $[n - m, n + m]$ 按位或，枚举 $r$ 二进制位，若为 0 则查找区间内此位为 1 的数|分类讨论查找区间内某二进制位为 1 的数，若 $l$ 此位为 1 则返回 $l$，否则构造最小满足数与 $r$ 比较|快速查找区间内某二进制位为 1 的数|3星|
|OIratrace|明确 $m$ 秒后 $a_n$ 是区间 $[n - m, n + m]$ 按位或，用循环计算区间按位或和|`while (r > l) { l |= (l + 1); }`|快速计算区间按位或和|3星|
|EuphoricStar|答案二进制位互相独立，分别计算每一位取值，根据 $1$ 的扩散情况判断|设当前考虑第 $d$ 个二进制位，$a_i = \left\lfloor\frac{i}{2^d}\right\rfloor \bmod 2$，计算 $0$ 连续段左右 $1$ 扩散到 $a_n$ 的时间|判断每一位是否为 1|3星|
|Special_Tony|每一秒每个格子或区间左右各延伸一格，$n$ 号节点 $m$ 秒后是 $\max(n - m, 0)\sim n + m$ 按位或和，通过找特殊数与 $r$ 按位或求解|假设 $l = x0a, r = x1b$，得数为 $x0111\dots|r$|快速计算区间按位或和|3星|
|imsbNR|求 $\max(n - m, 0) \sim n + m$ 区间或，对比两数二进制位，从最高位找第一个不同位，将此位及后面位变 1 后与左端点按位或|从最高位找 $l$ 和 $r$ 第一个不同位，构造全 1 数与 $l$ 按位或|快速计算区间按位或和|4星|
|2huk|所求为 $\operatorname{or}_{i = l}^r i$，逐位考虑，判断区间内是否存在某二进制位为 1 的数|分类讨论求 $\ge l$ 的最小第 $i$ 个二进制位为 1 的数 $f(l)$，判断 $f(l) \le r$ 是否成立|判断区间内是否存在某二进制位为 1 的数|3星|
|qzmoot|$m$ 次变化后 $a_n$ 是 $a_{n - m}|a_{n - m + 1}|\ldots|a_{n + m - 1}|a_{n + m}$，枚举每一位，根据边界和差值最高位判断|拆分 $a_{n - m}$ 和 $a_{n + m}$，若某一位有 1 则结果有 1，否则看差值最高位|快速计算区间按位或和|3星|
|OPEC|答案是范围 $[\max(0, n - m), n + m]$ 按位或，根据 $l$、$r$ 二进制位和 $\frac{l}{2^{i + 1}} \neq \frac{r}{2^{i + 1}}$ 判断每一位是否为 1|逐位判断 $l$、$r$ 二进制位和 $\frac{l}{2^{i + 1}} \neq \frac{r}{2^{i + 1}}$ 是否成立|判断每一位是否为 1|3星|
|sbno333|$k$ 次操作后 $a^{k}_i = \mid_{j = -k}^k a_{i + j}$，处理负数情况，拆位统计每一位|对于每一位，计算至少加多少得到 1，判断是否满足条件|判断每一位是否为 1|3星|
|Dream_Mr_li|范围是 $\max(0, n - m) \sim n + m$，判断是否在范围内决定是否更新答案|对于每一位，判断 $(a + b) >> i & 1$、$\max(0, a - b) >> i & 1$ 或 $(a + b - \max(0, a - b) >= (1 << i))$ 是否成立|判断每一位是否为 1|3星|

### 所选题解
- **Louis_lxy（4星）**
    - **关键亮点**：思路清晰，详细讲解了快速位运算（或、与、异或）的方法，提供了 $O(\log n)$ 和 $O(1)$ 两种解法。
    - **核心代码**：
```cpp
// O(1) 解法
int getor(int l, int r)
{
    if (l == r) return l;
    return l | ((1 << ( __lg(l ^ r) + 1)) - 1);
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n, m;
        scanf("%d %d", &n, &m);
        printf("%d\n", getor(max(0, n - m), n + m));
    }
}
```
- **imsbNR（4星）**
    - **关键亮点**：通过对比两数二进制位，找到第一个不同位，将此位及后面位变 1 后与左端点按位或，思路简洁，代码实现简单。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n, m, ans, x, t, q, l, r;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> q;
    while (q--)
    {
        cin >> n >> m;
        l = max(0, n - m);
        r = n + m;
        if (l == r)
        {
            cout << l << endl;
            continue;
        }
        for (int i = 30; i >= 0; i--)
        {
            if ((l >> i & 1)!= (r >> i & 1))
            {
                cout << (l | ((1 << (i + 1)) - 1)) << endl;
                break;
            }
        }
    }
    return 0;
}
```

### 最优关键思路或技巧
- 确定 $m$ 秒后 $a_n$ 的值是区间 $[\max(0, n - m), n + m]$ 内所有数的按位或结果。
- 利用二进制位的性质，通过对比区间左右端点的二进制位，找到第一个不同位，将此位及后面位变 1 后与左端点按位或，可快速计算区间按位或和。

### 可拓展之处
同类型题可能会改变序列的初始值、变化规则或按位运算方式，但核心思路仍是分析变化规律，确定最终计算的区间，然后解决区间内按位运算的问题。类似算法套路可用于解决其他涉及按位运算和区间计算的问题。

### 推荐题目
- [P1888 三角函数](https://www.luogu.com.cn/problem/P1888)：考察最大公约数和三角函数基础知识，涉及简单的数学计算和位运算。
- [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)：需要分析地毯覆盖的范围，与本题确定区间的思路类似。
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：需要处理区间的覆盖问题，可通过标记数组或其他方法解决，与本题确定区间和处理区间内元素的思路有一定相似性。

### 个人心得摘录与总结
- **Louis_lxy**：表示题目比较简单，但场上没想到，看到大佬做法看不懂只能自己想，体现了独立思考和探索的重要性。
- **qzmoot**：提到在计算区间左端点时被 $n - m$ 要大于等于 $0$ 卡了好久，提醒我们在处理边界条件时要格外小心。
- **Dream_Mr_li**：强调多测不清空会爆 0，提醒我们在处理多组测试数据时要注意清空变量。 

---
处理用时：58.44秒