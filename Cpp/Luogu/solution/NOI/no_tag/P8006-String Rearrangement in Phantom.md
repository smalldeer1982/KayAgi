# String Rearrangement in Phantom

## 题目描述

有一字符串 $S$，每次询问两串 $S[l_1,r_1]$，$S[l_2,r_2]$，问有多少划分方式使得 $S[l_1,r_1]=A+B+C$，$C+B^R+A=S[l_2,r_2]$。其中 $B^R$ 表示 $B$ 串的翻转，$+$ 表示字符串的拼接，$S[l,r]$ 表示提取串 $S$ 的第 $l$ 到第 $r$ 个字符。$A,B,C$ 可以为空。

## 说明/提示

**本题采用捆绑测试**

| 子任务编号 | 分值 | 特殊限制 |
| :----------: | :----------: | :----------:|
| $0$ | $10$ | $1\le n,m\le 100$ |
| $1$ | $10$ | $1\le n,m\le 500$ |
| $2$ | $20$ | $1\le n,m\le 3000$ |
| $3$ | $30$ | $1\le n,m\le 5\times 10^4$ |
| $4$ | $30$ | $1\le n\le 2\times 10^5$，$1\le m\le 10^5$ |

对于所有数据，保证 $1\le n\le 2\times 10^5$，$1\le m\le 10^5$，$1\le l_1\le r_1\le n$，$1\le l_2\le r_2\le n$，$r_1-l_1=r_2-l_2$。

对于编号为 $i$ 的 Subtask，其时限为 $i+1$ 秒。

## 样例 #1

### 输入

```
10 4
aabbaabbaa
1 6 5 10
3 6 5 8
1 3 5 7
1 10 1 10```

### 输出

```
11
9
2
17
```

# 题解

## 作者：zhouhuanyi (赞：6)

先考虑一个 $O(nq)$ 的暴力，令 $s_{1}=S[l_{1},r_{1}],s_{2}=S[l_{2},r_{2}]$，令 $t=\operatorname{rev}(s_{2})$，则我们仅需求 $s_{1}=A+B+C,t=\operatorname{rev}(A)+B+\operatorname{rev}(C)$ 的数量，对于每一个前缀和后缀求出其翻转是否与其相等即可，这个可以通过 $\text{kmp}$ 快速求出。

注意到翻转与自身相等的前缀为 $s_{1}+s_{2}$ 的一个 $\text{border}($后缀同理$)$，所以其也是满足 $\text{border}$ 理论的性质的，其形成了 $\log$ 段等差数列，如果使用基本子串字典模型求解出 $\log$ 段等差数列，那么如果能快速求解前缀与后缀两段等差数列之间的贡献，则可以做到 $O(q\log^2 n)$ 的复杂度。

现在快速求两段等差数列之间的贡献，考虑以下两种情况:

$1$.这两段等差数列对应的 $\text{border}$ 不交：

相当于 $s_{1}=(A+B+A+B+...+A)+E+(C+D+C+D+...+C),t=(\operatorname{rev}(A)+\operatorname{rev}(B)+\operatorname{rev}(A)+\operatorname{rev}(B)+...+\operatorname{rev}(A))+F+(\operatorname{rev}(C)+\operatorname{rev}(D)+\operatorname{rev}(C)+\operatorname{rev}(D)+...+\operatorname{rev}(C))$ 的一个形式，注意到我们统计答案时仅与 $E$ 是否 $F$ 相等，$B+A$ 是否与 $\operatorname{rev}(B)+\operatorname{rev}(A)$ 相等，$C+D$ 是否与 $\operatorname{rev}(C)+\operatorname{rev}(D)$ 相等有关，可以非常方便的统计。

$2$.这两段等差数列对应的 $\text{border}$ 有交：

比较难以处理的一部分，但可以发现必然有一个超过了一半，所以单组询问枚举的量级是 $O(\log n)$ 级别的，于是可以使用一些更加暴力的方法来维护。

判定中间的两个串相等需要一些证据的支持，但可以发现由于两段已经覆盖满了整个串，所以证据是充足的，即对于中间的两个串的每个位置两个中至少有一个可以参与判定，先将其中有一个取到最长的判掉，这部分在求出第一次使得两侧不交的位置后级可以转化为 $\text{case1}$ 的情况维护。

现在仅需考虑两侧均不取到最长的情况，容易发现判定相等的证据来源与 $A+B$ 与 $\operatorname{rev}(A)+\operatorname{rev}(B)$ 的 $\text{lcp}$ 与 $C+D$ 与 $\operatorname{rev}(C)+\operatorname{rev}(D)$ 的 $\text{lcs}$，特别的当 $A+B=\operatorname{rev}(A)+\operatorname{rev}(B)$ 与 $C+D=\operatorname{rev}(C)+\operatorname{rev}(D)$ 时其各自产生的限制是自由的，即认为时刻相等，但当这两个情况有任意一个不满足时，对应的 $\text{lcp},\text{lcs}$ 即可看作一条限制，限制中间的两个串的长度不能超过 $\text{lcp}$ 或 $\text{lcs}$。

至此我们将其转化为了纯粹的对中间的串的长度的限制，其要在 $[0,r]$ 内，那么相当于统计在两个等差序列 $A,B$ 分别取两个元素 $x,y$，$x+y\in [L,R]$ 的方案数，这个是经典类欧问题，可以做到 $O(\log n)$。

加上求解基本子串字典，复杂度为 $O(n\log^2 n+q\log^2 n)$，如果使用复杂度更小的基本子串字典可以做到 $O(n\log n+q\log^2 n)$。

---

