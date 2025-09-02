# 【MX-X16-T6】「DLESS-3」XOR and Powerless Suffix Mode

## 题目描述

我们称 $x$ 是序列 $a$ 的一个子序列中的 Powerless Suffix Mode，当且仅当：

- $x$ 是该子序列的众数$^{\dagger}$。
- 不存在满足 $i < j$ 的下标 $i, j$ 使得 $a_i = a_j = x$ 且 $a_i$ 属于该子序列、$a_j$ 不属于该子序列。
- $x$ 在子序列中出现次数不超过 $x$ 在整个序列中出现次数的 $p\%$。

给定长度为 $n$ 的非负整数序列 $a_1, \ldots, a_n$。给出 $q$ 次询问，每次询问给出整数 $l,r,p$（$1 \le l \le r \le n$，$1 \le p \le 100$），求序列 $b=[a_l,a_{l+1},\dots,a_{r-1},a_r]$ 所有非空子序列 Powerless Suffix Mode 的异或和（若某个子序列有多个 Powerless Suffix Mode 则全部异或，若没有则异或 $0$）。

**注意，此时判定一个数是否是 Powerless Suffix Mode 的条件中，“整个序列”为序列 $b$。**

---
$^{\dagger}$一个序列的众数是指序列中出现次数最多的数，一个序列可以有多个众数，例如序列 $[1,2,1,3,2]$ 的众数有 $1$ 和 $2$。

## 说明/提示

**【样例解释 #1】**

为了方便说明，以下简称 Powerless Suffix Mode 为 PSM。

对于第一组询问，考察的序列是 $b=[1, 9, 1]$。该序列的非空子序列有 $[1]$、$[9]$、$[1]$、$[1,9]$、$[1,1]$、$[9,1]$、$[1,9,1]$。子序列 $[9]$ 的 PSM 是 $9$；子序列 $[1,9]$ 的众数是 $1$ 和 $9$，但是由于 $b_1=b_3=1$ 且 $b_1$ 在子序列中而 $b_3$ 不在，所以其中只有 $9$ 是 PSM。枚举可得，将所有子序列的 PSM 全部异或起来，最终结果为 $9$。

对于第二组询问，考察的序列是 $b=[4, 5, 1, 4]$。$p=50\%$ 的限制意味着，若一个数在子序列中成为 PSM，它的出现次数不能超过它在 $b$ 中出现次数的 $50\%$。例如，对于数 $4$，它在 $b$ 中出现 $2$ 次，那么在子序列中最多出现 $2\times 50\%=1$ 次。枚举可得，所有非空子序列的 PSM 的异或和为 $0$。


**【数据范围】**

**本题采用捆绑测试。**

对于所有数据，保证 $1\le n\le 2.5\times10^5$，$1\le q\le 2.5\times10^5$，$0\le a_i<2^{24}$，$1\le l\le r\le n$，$1 \le p\le100$。

各子任务特殊限制如下：

| 子任务编号 | $n\le$ | $q\le$ | $a_i<$ | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $18$ | $20$ | $2^{24}$ | $7$ |
| $2$ | $500$ | $500$ | $2^{24}$ | $11$ |
| $3$ | $5000$ | $5000$ | $2^{24}$ | $15$ |
| $4$ | $2.5\times10^5$ | $2.5\times10^5$ | $2$ | $13$ |
| $5$ | $2.5\times10^5$ | $2.5\times10^5$ | $2^6$ | $14$ |
| $6$ | $2.5\times10^5$ | $2.5\times10^5$ | $2^8$ | $14$ |
| $7$ | $5\times10^4$ | $2.5\times10^5$ | $2^{24}$ | $14$ |
| $8$ | $2.5\times10^5$ | $2.5\times10^5$ | $2^{24}$ | $12$ |


## 样例 #1

### 输入

```
13 6
1 1 4 5 1 4 1 9 1 9 8 1 0
7 9 100
3 6 50
7 11 100
7 11 99
1 3 100
2 4 100```

### 输出

```
9
0
8
0
4
0```

## 样例 #2

### 输入

```
18 1
1 1 1 1 1 1 2 2 2 2 2 2 4 4 4 4 4 4
1 18 40```

### 输出

```
7```

# 题解

## 作者：vegetable_king (赞：6)

[可能更好的阅读体验](https://yjh965.github.io/post/p13688-xor-and-powerless-suffix-mode-ti-jie/)

已被严肃卡常，呃呃。你说得对，但是我们有
$$
\sum_{j = 0}^a \binom bj \equiv \binom{b - 1}a \pmod 2
$$
考虑证明。首先把左半边改写为 $0 \le j \le a$ 且 $j \subseteq b$ 的 $j$ 个数。那么显然可以把 $a$ 的低位删掉变为 $a'$，使得 $\mathrm{lowbit}(a’) \ge \mathrm{lowbit}(b)$，这不影响答案。

接下来考虑一种计算方式是，枚举 $p$ 使得前面的位上 $a', j$ 相同，第 $p$ 位上 $a'$ 严格比 $j$ 大，然后后面的位任取（或者这样的 $p$ 不存在）。显然当 $p > \mathrm{lowbit}(b)$ 的时候后面任取的方案肯定有偶数种（因为 $j$ 在 $\mathrm{lowbit}(b)$ 这一位上可以取 $0, 1$），这是无意义的，因为我们只关心答案 $\bmod 2$。那么我们只需要考虑 $p = \mathrm{lowbit}(b)$ 与不存在这样的 $p$ 的两种情况，不难发现后者满足则前者一定满足，前者不满足则后者一定满足，此时答案为 $0$；则答案为 $1$ 等价于 $a' \subseteq b - 2^{\mathrm{lowbit}(b)}$，这又等价于 $a \subseteq b - 1$。

下面令 $p$ 为题目中的 $\frac p{100}$。考虑计算一个数被异或的次数。令这个数出现了 $a_0$ 次，其他数分别出现了 $a_1, a_2, \dots, a_k$ 次，可以写出式子：
$$
\begin{aligned}
&\sum_{c = 1}^{\lfloor a_0 p \rfloor} \prod_{i = 1}^k \sum_{j = 0}^c \binom{a_i}j\\
=& \sum_{c = 1}^{\lfloor a_0 p \rfloor} \prod_{i = 1}^k \binom{a_i - 1}c\\
=& \sum_{c = 1}^{\lfloor a_0 p \rfloor} \binom{\cap_{i = 1}^k (a_i - 1)}c\\
=& \binom{\cap_{i = 1}^k (a_i - 1) - 1}{\lfloor a_0 p \rfloor} - 1\\
\end{aligned}
$$
对于出现次数相等的数，它们的异或次数显然也是相等的，可以合并计算。根据经典结论本质不同的出现次数只有 $\mathcal{O}(\sqrt n)$ 种，于是我们只需要知道所有可能的出现次数，以及对于一个出现次数 $x$，出现次数为 $x$ 的数的个数，以及所有出现次数为 $x$ 的数的异或和就可以暴力算答案了。直接上莫队即可做到单根号。

---

## 作者：Gold14526 (赞：2)

首先，众数这一条件只跟元素出现的个数有关，而一个区间里元素的出现次数只有 $O(\sqrt{n})$ 种，于是我们考虑处理出每种出现次数有关的信息，然后计算答案。

首先考虑需要什么信息，我们考虑处理出区间内每种出现次数 $cnt$ 的出现次数，以及出现 $cnt$ 次的数的异或和，这看上去是够用了。

考虑莫队，每次移动时修改以上两个信息，时间复杂度 $O(n\sqrt{q})$。

每次询问时，我们把有用的 $cnt$ 找出来，这一部分使用根号分治：

- 对于每个小于 $\sqrt{n}$ 的 $cnt$ 判断其是否有用。
- 对于每个在序列中总出现次数大于 $\sqrt{n}$ 的数判断其是否出现了至少 $\sqrt{n}$ 次。

接下来我们开始考虑如何计算答案。

不妨先考虑暴力，对于一个 $cnt_i$，考虑求出出现 $cnt_i$ 次的数作为 Powerless Suffix Mode 出现的次数，我们枚举它在子序列中出现了几次，假设是 $cnt_i'$ 次，由于它是众数，那么对于另一种出现次数 $cnt_j$，我们要求出它在子序列中出现小于等于 $cnt_i'$ 次的方案数，即 $\sum_{x=0}^{cnt_i'}\binom{cnt_j}{x}$。

这是一个组合数行前缀和的形式，貌似并不可求，但是如果你因此放弃了这种做法，那就大错特错了。

注意到我们只要求它模 $2$ 的余数，我们惊人地发现：

$$
\begin{aligned}
\sum_{x=0}^{cnt_i'}\binom{cnt_j}{x} &= \sum_{x=0}^{cnt_i'}(\binom{cnt_j-1}{x}+\binom{cnt_j-1}{x-1}) \\
&= 2\sum_{x=0}^{cnt_i'-1}\binom{cnt_j-1}{x}+\binom{cnt_j-1}{cnt_i'}
\end{aligned}
$$

所以，$\sum_{x=0}^{cnt_i'}\binom{cnt_j}{x}\equiv \binom{cnt_j-1}{cnt_i'}\pmod{2}$。

根据 Lucas 定理或 Kummer 定理，我们可以得到 $\binom{cnt_j-1}{cnt_i'}\bmod 2=[cnt_i'\sube(cnt_j-1)]$，于是我们可以 $O(1)$ 求出组合数行前缀和对 $2$ 取模后的结果。

那么对于一个 $cnt_i'$，它是否是其它所有 $cnt_j-1$ 的子集显然等价于它是否是其它所有 $cnt_j-1$ 的按位与的子集。

于是，我们处理出前后缀与，即可对于一个 $cnt_i'$ 做到 $O(1)$ 求出结果。

但是仍然有问题，因为我们考虑的是枚举 $cnt_i'$ 然后计算出现 $cnt_i$ 次的数出现 $cnt_i'$ 次的时候方案数模 $2$ 的值，如果我们这样枚举的话时间复杂度仍然是 $O(n)$ 的。

也就是说，现在我们要求小于等于 $cnt_i\times p\%$ 的正整数中，是其余 $cnt_j-1$ 按位与的子集的个数，设 $asum$ 表示其余 $cnt_j-1$ 的按位与，显然可以数位 dp 做到单 $\log$，但是我们有更聪明的处理方法。

设 $c_i=\lfloor cnt_i\times p\% \rfloor$，现在我们要求 $\sum_{x=1}^{c_i}[x\sube asum] \bmod 2$，发现这正好等于 $\sum_{x=0}^{c_i}\binom{asum}{x} - \binom{asum}{0} \bmod 2$，所以便等于 $[x\not\sube (asum-1)]$，于是我们可以对于一个 $cnt_i$ 做到 $O(1)$ 算出答案，这一部分时间复杂度为 $O(q\sqrt{n})$，注意需要特判 $asum=0$ 的情况。

总时间复杂度为 $\mathcal O(n\sqrt{q}+q\sqrt{n})$。

---

## 作者：diqiuyi (赞：1)

被做局了。

考虑枚举众数，记 $c_i$ 为出现次数，那么它对答案的贡献次数是 $\sum_{T=1}^{pc_i\over 100}\prod_{i\neq j} \sum_{k=0}^T\binom{c_j}{k}$。

根据 lucas 定理，容易得到 $x!$ 的质因数分解有 $x-\text{popcnt}(x)$ 个 2，所以 $\binom{n}{m}\equiv [n\operatorname{and} m=m]\pmod 2$。

所以关于 $\sum_{k=0}^T\binom{c_j}{k}$，我们只要判断 $\le T$ 的最大的 $c_j$ 的子集的最低位是否和 $c_j$ 相同即可。仔细分析可以得到这等价于 $T\operatorname{and}  c_j-1=T$。那我们把 $j\neq i$ 的 $c_j-1\ \operatorname{and}$ 起来以后只要求一个 $\sum_{T=1}^{pc_i\over 100}[T\operatorname{and}x=T]$，这个跟刚刚的形式完全一样，所以只要做一个前后缀和就可以 $O(nq)$ 了。

然后这个贡献次数只和 $c_i$ 有关，$c_i$ 又只有 $O(\sqrt{n})$ 种，所以直接莫队+链表维护即可 $O((n+q)\sqrt{n+q})$。

但是直接写这个会 TLE，原因是虽然 $2^{24}$ 可以开桶存，但是寻址很慢，所以加上离散化就可以过了。

还有一个优化是把链表改成只加数，最后再把不合法的数删掉，这样常数小很多。
```cpp
#include <bits/stdc++.h>
#define uint unsigned int
using namespace std;
inline int read(){
	int x=0;bool f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=0;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return f?x:-x;
}
int n,m,B,tot,a[250005],A[250005],bl[250005],ans[250005],cnt[250005],val[250005],
v[250005],ccnt[250005],pre[1145],suf[1145],b[250005];
bitset<250005> vis;
struct qr{
	int l,r,p,id;
	bool operator <(qr &x) const{
		return bl[l]^bl[x.l]?l<x.l:bl[l]&1?r<x.r:r>x.r;
	}
}q[250005];
void Add(int x,int vl=1){
	int v=cnt[x];
	ccnt[v]--,val[v]^=A[x];
	cnt[x]+=vl,v+=vl;
	if(!vis[v]) b[++tot]=v,vis[v]=1;
	ccnt[v]++,val[v]^=A[x];
}
bool check(int x,int v){
	return (x&v)==x;
}
int main(){
	n=read(),m=read(),B=sqrt(n);
	for(int i=1;i<=n;i++) A[i]=a[i]=read(),bl[i]=(i-1)/B+1;
	sort(A+1,A+n+1);
	int nn=unique(A+1,A+n+1)-A-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(A+1,A+nn+1,a[i])-A;
	for(int i=1;i<=m;i++) q[i]={read(),read(),read(),i};
	sort(q+1,q+m+1),ccnt[0]=n+1;
	int T=0;
	for(int L=1,R=0,i=1;i<=m;i++){
		while(L>q[i].l) Add(a[--L]);
		while(R<q[i].r) Add(a[++R]);
		while(L<q[i].l) Add(a[L++],-1);
		while(R>q[i].r) Add(a[R--],-1);
		for(int i=1;i<=tot;i++)
			if(!ccnt[b[i]])
				vis[b[i]]=0,swap(b[i],b[tot]),tot--,i--;
//		cout<<tot<<'\n';
		pre[0]=suf[tot+1]=(1<<18)-1;
		int lp=0,ls=tot+1;
		for(int j=1;pre[j-1]&&j<=tot;j++) lp=j,pre[j]=pre[j-1]&(b[j]-1);
		for(int j=tot;suf[j+1]&&j;j--) ls=j,suf[j]=suf[j+1]&(b[j]-1);
		for(int j=max(ls-1,1);j<=min(lp+1,tot);j++){
			int c=(ccnt[b[j]]>1?(lp==tot?pre[tot]:0):pre[j-1]&suf[j+1]);
			if(!check(b[j]*q[i].p/100,c-1)) ans[q[i].id]^=val[b[j]];
		}
	}
	for(int i=1;i<=m;i++) cout<<ans[i]<<'\n';
    return 0;
}
```

---

