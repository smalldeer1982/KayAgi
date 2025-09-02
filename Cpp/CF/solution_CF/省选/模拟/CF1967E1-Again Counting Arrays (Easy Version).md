# Again Counting Arrays (Easy Version)

## 题目描述

This is the easy version of the problem. The differences between the two versions are the constraints on $ n, m, b_0 $ and the time limit. You can make hacks only if both versions are solved.

Little R has counted many sets before, and now she decides to count arrays.

Little R thinks an array $ b_0, \ldots, b_n $ consisting of non-negative integers is continuous if and only if, for each $ i $ such that $ 1 \leq i \leq n $ , $ \lvert b_i - b_{i-1} \rvert = 1 $ is satisfied. She likes continuity, so she only wants to generate continuous arrays.

If Little R is given $ b_0 $ and $ a_1, \ldots, a_n $ , she will try to generate a non-negative continuous array $ b $ , which has no similarity with $ a $ . More formally, for all $ 1 \leq i \leq n $ , $ a_i \neq b_i $ holds.

However, Little R does not have any array $ a $ . Instead, she gives you $ n $ , $ m $ and $ b_0 $ . She wants to count the different integer arrays $ a_1, \ldots, a_n $ satisfying:

- $ 1 \leq a_i \leq m $ ;
- At least one non-negative continuous array $ b_0, \ldots, b_n $ can be generated.

Note that $ b_i \geq 0 $ , but the $ b_i $ can be arbitrarily large.

Since the actual answer may be enormous, please just tell her the answer modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, for example, when $ a = [1, 2, 1] $ , we can set $ b = [1, 0, 1, 0] $ . When $ a = [1, 1, 2] $ , we can set $ b = [1, 2, 3, 4] $ . In total, there are $ 6 $ valid choices of $ a_1, \ldots, a_n $ : in fact, it can be proved that only $ a = [2, 1, 1] $ and $ a = [2, 1, 2] $ make it impossible to construct a non-negative continuous $ b_0, \ldots, b_n $ , so the answer is $ 2^3 - 2 = 6 $ .

## 样例 #1

### 输入

```
6
3 2 1
5 5 3
13 4 1
100 6 7
100 11 3
1000 424 132```

### 输出

```
6
3120
59982228
943484039
644081522
501350342```

# 题解

## 作者：MiniLong (赞：2)

考虑固定序列 $a$ 时 $b$ 会怎么变化最优，发现如果 $b$ 序列可以是负数的话，那么所有序列都可以作为 $a$。但由于不能小于 $0$ 这个限制，所以 $b$ 肯定是越大越好（没有上界）。所以有个贪心，只有当 $a_{i+1} = b_i + 1$ 时，$b_{i+1} = b_i - 1$，否则 $b_{i+1} = b_i + 1$。

那么一个 $a$ 就可以唯一对应这样一个 $b$，考虑通过这个 $b$ 计数。设 $f_{i,j}$ 表示 $a_1 \cdots a_i$ 组成的 $b$ 最后一位 $b_i = j$ 的 $a$ 方案数。转移有 $(m-1)f_{i,j}  \to f_{i+1,j+1},f_{i,j}[j<m] \to f_{i+1,j-1},m \cdot f_{i,m} \to f_{i+1,m}$。这个复杂度是 $\Theta(nm)$ 的，显然无法通过。

考虑换一种方式，这个 dp 看起来很像网格图计数，且贡献系数相同，那我们考虑从 $(0,b_0)$ 开始走，每次往右上或右下走，不能低于直线 $y=0$，且第一次碰到直线 $y=m$ 时结束，或最后走到 $(n,i)(i < m)$。可以直接枚举结束位置 $(i,m),(n,i)$。然后坐标轴旋转一下，就是从 $(0,0)$ 走到 $(\dfrac{i-m+b_0}{2},\dfrac{i+m-b_0}{2} - 1)$ 和走到 $(\dfrac{n-i}{2},\dfrac{n+i}{2})$ 且不碰到直线 $y=m-b_0$ 和直线 $y=-b_0 -1$ 的方案数，可以简单反射容斥求出，最后前面的乘上 $(m-1)^{\frac{i+m-b_0}{2}}m^{n-i}$ 的系数，后面乘上 $(m-1)^{\frac{i+n}{2}}$ 的系数就行了。分别计算复杂度是 $\Theta(\dfrac{n^2}{m} +n)$ 的。

那么两个方法平衡一下，当 $m \le B$ 时写 dp，否则写下面的计数。

复杂度 $\Theta(nB+\dfrac{n^2}{B})$。

---

## 作者：critnos (赞：1)

基础计数题。考虑判定一个序列是否合法，显然只用考虑让 $b$ 最大（理解一下就是这个 $b$ 有若干取值，因为奇偶性所以最大值是最优的）。如果 $a_i=b_{i-1}+1$ 那么 $b_i=b_{i-1}-1$，否则 $b_i=b_{i-1}+1$。不合法就是 $b_{i-1}=0$ 且 $a_i=1$。

考虑一个 $b$ 对应的 $a$ 的数量，就是，如果这个 $b_i=b_{i-1}+1$ 那么有 $m-1$ 种选择，否则有唯一选择。特殊情况就是 $b_{i-1}=m-1,b_i=m$，此后 $b_i>m$，$a$ 就随便放了。这样子有 $(m-1)m^{n-i}$ 种选择。显然上面转移的时候 $m-1$ 的次数可以直接算出来，于是就变成了一个格路计数问题。

大概要算的就是一个矩形边界上的贡献。暴力 dp 的时间复杂度是 $O(nm)$，反射容斥的时间复杂度是 $O(n^2/m)$（需要控制矩形右边界长度），平衡一下就是 $O(n\sqrt n)$ 的。瓶颈在于计算上边界的答案。

[提交记录](https://codeforces.com/problemset/submission/1967/263130173)

---

