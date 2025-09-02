# [RC-07] Game Theory

## 题目描述

给出长度为 $n$ 的 `01` 序列 $a_{1\sim n}$，**序列中有偶数个 `1`**。NIT 和 TIN 轮流做以下操作，NIT 先手：

- 选择位置 $i\ (1\le i\le n)$，满足区间 $[1,i]$ 中有奇数个 `1`。再选择位置 $j\ (i<j\le n)$。将 $a_i,a_j$ 都取反（即，`0` 变 `1`，`1` 变 `0`）

当整个序列中的所有元素都变为 `0` 时，当前轮到的人就无法操作，他就输了。假设 NIT 和 TIN 都*绝顶*聪明，谁会赢？可以证明，游戏总会结束。

$n$ 可能很大，但序列中 $1$ 的个数不超过 $2\times 10^5$。

## 说明/提示

**样例解释**

第一组数据中，NIT 选择 $i=1,j=3$ 就能把全部位置都变成 0，使得 TIN 无法操作。

第二组数据中，无论 NIT 先手怎么操作，都会剩下恰好两个 1 的位置。TIN 只需要选择这两个剩下的位置，就可以把全部位置都变成 0。

第三组数据中，一种可能的游戏进程如下（注意该进程里，每一步不一定是最优的）：

- NIT 选择 $i=2,j=3$ 并将这两个位置取反。现在 
`1` 的位置在 $1,2,7,8$。
- TIN 选择 $i=7,j=9$ 并将这两个位置取反。现在 
`1` 的位置在 $1,2,8,9$。
- NIT 选择 $i=1,j=5$ 并将这两个位置取反。现在 
`1` 的位置在 $2,5,8,9$。
- TIN 选择 $i=3,j=4$ 并将这两个位置取反。现在 
`1` 的位置在 $2,3,4,5,8,9$。
- NIT 选择 $i=4,j=5$ 并将这两个位置取反。现在 
`1` 的位置在 $2,3,8,9$。
- TIN 选择 $i=2,j=9$ 并将这两个位置取反。现在 
`1` 的位置在 $3,8$。
- NIT 选择 $i=3,j=8$ 并将这两个位置取反。现在序列里没有 `1` 了。
- TIN 无法操作，NIT 获胜。

**数据范围**

对于所有数据，$1\le T\le 10^4$，$1\le n\le 10^{18}$，$2\le m\le 2\times 10^5$，$\sum m\le 10^6$。保证 $m$ 是偶数，保证为 `1` 的下标是递增顺序给出的。

- 子任务 1（$1$ 分）$T\le 10^3$，$n\le 10$。
- 子任务 2（$9$ 分）序列中全是 `1`。
- 子任务 3（$40$ 分）$T\le 100$，$n\le 100$。
- 子任务 4（$10$ 分）$\sum n\le 10^6$。
- 子任务 5（$40$ 分）没有任何附加限制。

## 样例 #1

### 输入

```
3
4 2
1 3
4 4
1 2 3 4
10 4
1 3 7 8```

### 输出

```
NIT
TIN
NIT```

# 题解

## 作者：VinstaG173 (赞：5)

突然看到这题，发现竟然没做过，然后发现之前的题解饱受诟病后全被撤了，于是来写一发以免次次都要去找官方题解。

首先看到题意，选择“满足区间 $[1,i]$ 中有奇数个 $1$”的 $i$，并且序列中只有 $0$ 和 $1$，操作也是 $0,1$ 互换，看上去很像[翻棋子游戏](https://www.luogu.com.cn/article/1am7gm8b)。考虑 $A_i=\text{xor}_{l=1}^i a_l$，那么操作实际上就是选择 $A_i=1$ 的 $i$ 及一个 $j\in(i,n]$，翻动 $A_i,\dots,A _{j-1}$，同样是 $A_i$ 全部为 $0$ 时失败。那么由翻棋子游戏的结论，我们只需求所有 $A_i=1$ 的 $i$ 处的 $sg(i)$ 的异或和，SG 函数方程如下：

$$sg(i)=\text{mex}_{i<j\le n}\{\text{xor} _{l=i+1}^{j-1}sg(l)\}.$$

我们不妨换个方向看，重新定义 $sg(i)$ 表示 $A_{n-i}$ 处的 SG 值。重写一遍方程：

$$sg(i)=\text{mex}_{0\le j<i}\{\text{xor} _{l=j+1}^{i-1}sg(l)\}.$$

打个小表，我们容易发现结论：

**定理 $1$**. $sg(i)=\text{lowbit}(i)$，其中对正整数 $i$ 定义 $\text{lowbit}(i)$ 表示使得 $2^k\mid i$ 的最大的 $2^k$。特别地，在此定义 $\text{lowbit}(0)=0$。下面我们证明这个定理。

**定理证明**. 用归纳法。首先显然 $sg(0)=0$，因为不能对位置 $n$ 操作（事实上由题设条件 $A_n$ 始终为 $0$）。假设对 $i\in[0,2^k]$ 结论成立，接下来我们借助两个引理来完成证明：

**引理 $1$**. 对于 $i\in(2^k,2^{k+1})$，有 $sg(i)=sg(i-2^k)$。

**引理 $1$ 证明**. 同样用归纳法。首先看归纳奠基 $2^k+1$，由于 $\forall j\in[0,2^k]$ 有 $sg(j)=\text{lowbit}(j)$，故 $\forall j\in[0,2^k)$ 有 $sg(j)<2^k$ 且 $sg(2^k)=2^k$，由异或运算的性质知 $\forall j\in[0,2^k),\text{xor}_{l=j+1}^{2^k}sg(l)\ge2^k$。又 $j=2^k$ 时有 $\text{xor}_{l=j+1}^{i-1}sg_l=0$（$0$ 个数的异或和定义为异或运算的单位元 $0$，下同），从而 $sg(2^k+1)=1=sg(1)$。

对 $i\in(2^k+1,2^{k+1})$，假设对 $j\in(2^k,i)$ 引理结论已证明，则 $\forall j\in[2^k,i),\text{xor}_{l=j+1}^{i-1}sg(l)=\text{xor} _{l=j-2^k+1}^{i-2^k-1}sg(l)$，故

$$\begin{aligned}
\text{mex} _{2^k\le j<i}\{\text{xor} _{l=j+1}^{i-1}sg(l)\}&=\text{mex} _{0\le j<i-2^k}\{\text{xor} _{l=j+1}^{i-2^k-1}sg(l)\}\\
&=sg(i-2^k)<2^k,
\end{aligned}$$

而同上可知 $\forall j\in[0,2^k),\text{xor}_{l=j+1}^{i-1}sg(l)\ge2^k$，从而 $sg(i)=sg(i-2^k)$，证毕。

**引理 $2$**. $\forall i\ge0$，$\text{xor}_{l=0}^i\text{lowbit}(l)$ 的二进制表示为[格雷码](https://www.luogu.com.cn/problem/P5657)的第 $i$ 位。记这个前缀异或和为 $g(i)$。

**引理 $2$ 证明**. 简单计算即可，在介绍格雷码的许多文章中也有提及，在此不做赘述。由引理 $2$ 我们可自然得到推论：

**推论 $2$**. $sg(2^{k+1})=2^{k+1}$。

由于 $\forall i\in(0,2^{k+1})$，有 $\text{lowbit}(i)=\text{lowbit}(2^{k+1}-i)$，又由于格雷码的 $0\sim2^{k+1}-1$ 位可取遍 $0\sim2^{k+1}-1$ 中的整数，故由引理 $2$ 及 SG 函数递推方程即得证。

通过引理 $1$ 及推论 $2$ 我们即对 $i\in[0,2^{k+1}]$ 完成了结论的证明，从而定理证毕。

回到原问题，我们即求所有 $A_{n-i}=1$ 的 $i$ 的 $\text{lowbit}(i)$ 的异或和。由题设 $a_i=1$ 的位置为偶数，设 $m=2t$，$a_i=1$ 的 $i$ 从小到大排列为 $i_1,\dots,i_{2t}$，那么我们发现所有 $A_{n-i}=1$ 的位置 $i$ 为集合 $\bigcup_{s=1}^t(n-i_{2s}+1,n-i_{2s-1}]$。

我们发现由异或运算的性质，

$$\begin{aligned}
\text{xor}_{l=a+1}^b\text{lowbit}(l)&=(\text{xor} _{l=0}^a\text{lowbit}(l))\operatorname{xor}(\text{xor}_{l=0}^b\text{lowbit}(l))\\
&=g(a)\operatorname{xor}g(b).
\end{aligned}$$

因此我们需要求

$$\begin{aligned}
\text{xor} _{s=1}^{t}(\text{xor} _{l=n-i _{2s}+1}^{n-i _{2s-1}}\text{lowbit}(l))&=\text{xor} _{s=1}^t(g(n-i _{2s})\operatorname{xor}g(n-i _{2s-1}))\\
&=\text{xor} _{s=1}^mg(n-i_s).
\end{aligned}$$

由于格雷码的另一条性质：$g(i)=i\operatorname{xor}\left\lfloor\dfrac i2\right\rfloor$，容易 $O(m)$ 计算。

进一步地，通过如上性质容易发现 $\text{xor} _{s=1}^mg(n-i_s)=0$ 当且仅当 $\text{xor} _{s=1}^m(n-i_s)=0$。这就是官方题解中的最终结论。

综上所述，当且仅当 $\text{xor} _{s=1}^m(n-i_s)=0$ 时后手必胜。代码过于简单就不提供了。

---

## 作者：Undead2008 (赞：0)

令 $b_i=\operatorname{xor}_{j=1}^ia_j$，则操作变为选择满足 $1\le i<j\le n,b_i=1$ 的任意 $i,j$，翻转 $b$ 数组下标在 $[i,j)$ 中的元素。

可以把每个 $b_i=0/1$ 的位置 $i$ 看成偶数/奇数个独立的权值为 $i$ 的游戏，则操作变为选择当前局面中某个权值为 $i$ 的游戏和满足 $1\le i<j\le n$ 的 $j$，删除当前游戏并对于所有 $i<k<j$ 添加一个权值为 $k$ 的游戏。

设权值为 $i$ 的游戏的 SG 函数值为 $c_i$，$c_i$ 可以简单递推。进一步的，打表发现 $c_i=\text{lowbit}(n-i)$，证明可以直接归纳。

于是问题变成了对于区间 $[l,r]$ 求 $\text{lowbit}$ 等于某个值的数的个数，可以简单容斥解决。

```cpp
#include"bits/stdc++.h"
using namespace std;
#define int long long
int T,n,m,A;
void Solve(int &A,int l,int r){
	for(int i=61,K=0,V;i>=0;i--)
		V=((r>>i)^((l-1)>>i))&1,V^=K,A^=(V<<i),K^=V;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(nullptr),cin>>T;
	while(T--){
		cin>>n>>m,A=0;
		for(int i=0,l,r;i<m-1;i+=2)cin>>l>>r,Solve(A,n-r+1,n-l);
		cout<<(A==0?"TIN\n":"NIT\n");
	}
}
```

---

