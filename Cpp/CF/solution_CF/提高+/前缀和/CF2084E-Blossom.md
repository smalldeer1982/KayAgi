# Blossom

## 题目描述

给定一个长度为 $n$ 的排列 $a$ $^{\text{∗}}$，其中部分元素缺失（用 $-1$ 表示）。

定义一个排列的值为其所有非空子段 $^{\text{‡}}$ 的 MEX $^{\text{†}}$ 之和。

求所有可能通过填充 $a$ 中缺失元素形成的有效排列的值的总和，结果对 $10^9 + 7$ 取模。

$^{\text{∗}}$ 长度为 $n$ 的排列是指由 $0$ 到 $n - 1$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[1,2,0,4,3]$ 是一个排列，但 $[0,1,1]$ 不是排列（因为 $1$ 在数组中出现了两次），$[0,2,3]$ 也不是排列（因为 $n=3$ 但数组中包含 $3$）。

$^{\text{†}}$ 整数集合 $c = \{c_1, c_2, \ldots, c_k\}$ 的最小排除值（MEX）定义为不包含在 $c$ 中的最小非负整数 $x$。

$^{\text{‡}}$ 序列 $a$ 是序列 $b$ 的子段，当且仅当 $a$ 可以通过从 $b$ 的开头和结尾删除若干（可能为零或全部）元素得到。

## 说明/提示

- 在第一个测试用例中，唯一有效的排列是 $[0, 1]$，其值为 $3$，因为：
  $$
  \operatorname{mex}([0]) + \operatorname{mex}([1]) + \operatorname{mex}([0, 1]) = 1 + 0 + 2 = 3
  $$
  因此答案为 $3$。

- 在第二个测试用例中，有两个有效排列：$[0, 1]$ 和 $[1, 0]$。$[0, 1]$ 和 $[1, 0]$ 的值均为 $3$，因此答案为 $3 + 3 = 6$。

- 在第四个测试用例中，有两个有效排列：$[0, 2, 1]$ 和 $[1, 2, 0]$。$[0, 2, 1]$ 的值为 $5$，因为：
  $$
  \operatorname{mex}([0]) + \operatorname{mex}([2]) + \operatorname{mex}([1]) + \operatorname{mex}([0, 2]) + \operatorname{mex}([2, 1]) + \operatorname{mex}([0, 2, 1]) = 1 + 0 + 0 + 1 + 0 + 3 = 5
  $$
  $[1, 2, 0]$ 的值也为 $5$，因为：
  $$
  \operatorname{mex}([1]) + \operatorname{mex}([2]) + \operatorname{mex}([0]) + \operatorname{mex}([1, 2]) + \operatorname{mex}([2, 0]) + \operatorname{mex}([1, 2, 0]) = 0 + 0 + 1 + 0 + 1 + 3 = 5
  $$
  因此答案为 $5 + 5 = 10$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
2
0 -1
2
-1 -1
3
2 0 1
3
-1 2 -1
5
-1 0 -1 2 -1```

### 输出

```
3
6
7
10
104```

# 题解

## 作者：Accelessar (赞：3)

以下记 $\operatorname{mex}(l,r)$ 为区间 $[l,r]$ 的 $\operatorname{mex}$。

先考虑没有 $-1$ 怎么做。容易想到枚举 $\operatorname{mex}$，答案即 $\sum_{i=1}^ni\sum_{l,r}[\operatorname{mex}(l,r)=i]$。第二个求和号可以根据 $0\sim i-1$ 的数的最小下标 $mn$ 和最大下标 $mx$、$i$ 的下标 $p$ 得出，只需分讨 $p$ 与区间 $[mn,mx]$ 的相对位置即可，总复杂度 $O(n)$。

接下来考虑拓展到有 $-1$ 的情况。贡献显然与区间内 $-1$ 的个数 $c(l,r)$ 有关，而且数据范围允许我们枚举两个东西，那么自然可以再枚举 $c(l,r)$。记总共有 $C$ 个 $-1$，$0\sim i-1$ 中总共有 $w_i$ 个数需要填，则答案为：

$$
\sum_{i=1}^n i\sum_{j=w_i}^C\binom{j}{w_i}w_i!(C-w_i)!\sum_{l,r}[\operatorname{mex}(l,r)=i\land c(l,r)=j]
$$

然后我们发现接下来就不太会做了，其原因在于 $\operatorname{mex}(l,r)=i$ 这个限制太强，根据上文没有 $-1$ 的做法，甚至需要分讨，不好刻画。

观察式子结构，发现可以将其转化为

$$
\sum_{i=1}^n\sum_{j=w_i}^C\binom{j}{w_i}w_i!(C-w_i)!\sum_{l,r}[\operatorname{mex}(l,r)\ge i\land c(l,r)=j]
$$

这样看起来就好做很多，因为 $\operatorname{mex}(l,r)\ge i$ 这个条件只要求 $[l,r]$ 包含 $0\sim i-1$ 出现的区间 $[mn_i,mx_i]$。设最后一个求和号的结果为 $f_{i,j}$，那么我们只需求出 $f$ 即可 $O(n^2)$ 计算答案。

至于计算 $f$，我们考虑对每个区间算出它的贡献。具体地，由于 $[mn_i,mx_i]$ 随着 $i$ 的增加而逐渐扩大，那么 $[l,r]$ 可贡献到的 $f_{*,c}$ 第一维就是一段前缀。考虑 $l$ 固定时，随着 $r$ 的增加，$[l,r]$ 能贡献到的位置单调不减，那么我们双指针维护 $[l,r]$ 能贡献到的右端点，前缀加用差分处理即可。

总复杂度 $O(n^2)$。

---

## 作者：Piwry (赞：3)

发现自己做法的后半部分（**Part2**）和 tutorial 不太一样，于是写篇题解记录一下。

## ~~Part0~~

首先从一个错误且复杂度爆炸的 dp 引入。

设 dp 的状态记录 $\text{mex}, l, r, k$，每个状态表示的是已经填了一些数字的方案的集合，其中 $\text{mex}$ 表示当前 $[l, r]$ 区间内 “可以满足” 的 $\text{mex}$，$k$ 为区间内部尚未填的 $-1$ 位置数量；每个状态的值则是所表示方案的答案和（$\text{mex}$ 和）。

转移时，我们考虑填下一个数字使得 $\text{mex}$ 增加 $1$。那么如果下一个数字在 $a$ 里不存在，要么填在区间内减少一个未填的 $-1$ 位置，要么填在区间外并且扩张区间 $l, r$；如果下一个数字在 $a$ 里已经存在，那么直接扩张 $l, r$ 即可。

粗略估计一下复杂度至少是 $O(n^5)$ 的。并且我们还注意到一个致命问题，因为对于某一个特定的 $\text{mex}$ 能满足的所有状态，我们并没有限定 $l, r$ 的区间不能过大，这就有可能会导致重复统计。例如原序列 $a=(3, -1, 0, -1)$，有两个可能的状态 $(\text{mex}=2, l=3, r=4, k=0, a=(3, -1, 0, 1)$ 和 $(\text{mex}=2, l=2, r=4, k=1, a=(3, -1, 0, 1))$，都可以转移到完全一致的状态 $(\text{mex}=2, l=2, r=4, k=0, a=(3, 2, 0, 1))$，这会导致转移时很难去除多算的答案。

为了修复这个问题，我们可以限定状态的**填数状态**使得 $a[l, r]$ 是满足当前填数状态的 $\text{mex}$ 的最小的区间。这样限定后会导致我们的转移更加麻烦，因为填一个数字后状态的 $\text{mex}$ 增加量可能不止 $1$；例如状态 $(\text{mex}=2, l=1, r=4, k=1, a=(3, -1, 0, 1))$，我们在 $-1$ 位置填一个 $2$ 后 $\text{mex}$ 会直接增加到 $4$。

但是这造成重复统计的状态之间的关联的性质实际上启发了我们~~（至少启发了我...）~~对答案统计方式进行进一步的优化。具体来说，对于一个 $\text{mex}$，它能造成重复统计的对应的状态 $(\text{mex}, l, r, k)$ 一定有 $a[l, r]$ 实际的 $\text{mex}_{(l, r)}=\text{mex}(a[l, r])$ 不小于刚才指定的 $\text{mex}$；即：

$$
\forall \text{mex}'\in [1, n], \forall (\text{mex}', l, r, k, a)\in S, \text{mex}'\leq \text{mex}(a[l, r])
$$

其中 $S$ 是所有合法的 dp 状态集合，并且这里的 dp 状态我们最初版的定义，即在 “限定状态的**填数状态**...” 之前的定义。

于是这启发我们将 “统计 $\text{mex}$ 和” 转化为 “统计区间数量”。

## Part1

可以注意到，对于填完所有 $-1$ 位置后 $a$ 的某个区间 $a[l, r], \text{mex}_{(l, r)}=\text{mex}(a[l, r])$，根据题目其贡献为 $\text{mex}_{(l, r)}$；但如果我们转而对每个 $\text{mex}>0$ 统计满足 ”区间内包含 $\{0, 1, \cdots, \text{mex}\}$ 数字“ 的区间个数，刚才的区间 $a[l, r]$ 恰好会被 $\text{mex} =1, \text{mex} =2, \cdots, \text{mex}=\text{mex}_{(l, r)}$ 各统计一次，也就是说这种统计规则下区间 $a[l, r]$ 产生的贡献也是 $\text{mex}_{(l, r)}$。

（一句话：只统计能够包含当前 $\text{mex}$ 所需所有数字的区间个数；对于每个区间，且有其恰好包含的 $\text{mex}$，该区间会被内部 $[0, \text{mex}-1]$ 每个数字统计一次。）

形式化地讲，我们有：

$$
\sum\limits_{l=1}^n\sum\limits_{r=l}^n \text{mex}(a[l, r])=\sum\limits_{\text{mex}=1}^n\sum\limits_{l=1}^n\sum\limits_{r=l}^n [\{0, 1, \cdots, \text{mex}-1\}\in a[l, r]]
$$

基于这个转换，我们大可写出一种直接枚举的做法：依次枚举 $l, r, \text{mex}$，设当前区间 $a[l, r]$ 内有 $k$ 个 $-1$，而 $a$ 当中总共有 $K$ 个 $-1$，且 $[0, \text{mex}-1]$ 中有 $c$ 个数字在 $a$ 中并未出现，那么这个 $(l, r, \text{mex})$ 对的贡献就为 $\binom{k}{c}\cdot c!\cdot (K-c)!$，其中这个式子的意思是，“从区间内 $k$ 个 $-1$ 位置取 $c$ 个位置填当前 $\text{mex}$ 所缺少的数字” 的方案数，再乘上这 $c$ 个数字内部的排序方案数，最后乘上剩下要填的数字的内部的排序方案数；注意如果已经出现的 $\text{mex}-c$ 个数字有任意一个不在区间 $a[l, r]$里，那么这个 $(l, r, \text{mex})$ 对的贡献会直接变成 $0$。

（一句话：可以枚举区间 $[l, r]$，然后枚举其能满足的每种 $\text{mex}$，计算几种填数方案可以满足这个 $[l, r], \text{mex}$，求和即可。）

写成伪代码大概就是：

```cpp
int ans =0;
int pos[n]; // 每个数字的出现位置，未出现则记为 -1
int pre[n]; // a 前缀区间内的 -1 出现次数
for(int l =1; l <= n; ++l)
	for(int r =l; r <= n; ++r)
		for(int mex =1, c =0; mex <= n; ++mex){
            if(pos[mex-1] == -1)
                ++c;
			else if(pos[mex-1] < l || pos[mex-1] > r)
                break;
            int k =pre[r]-pre[l-1];
            int K =pre[n];
            ans +=C(k, c)*fact(c)*fact(K-c);
        }
```

这样实现复杂度即为 $O(n^3)$ 的。

## Part2

考虑继续优化。

首先重点关注我们计算贡献的式子：

$$
\binom{k}{c}\cdot c!\cdot (K-c)!
$$

注意到，其中 $K$ 为定值，$c$ 仅仅与 $\text{mex}$ 有关联且随着 $\text{mex}$ 增大单调不减；$k$ 和具体的 $l, r$ 其实也不 “强关联”（不需要显式枚举 $l, r$），我们其实只需要统计 $-1$ 出现次数为 $k$ 的区间数量就可以了，但有一个麻烦在于我们还要求 $(l, r)$ 满足在原序列 $a$ 的区间 $a[l, r]$ 内必须包含所有 “在 $a$ 中已经出现的且在 $[0, \text{mex}-1]$ 范围内” 的数字。但是，我们接着可以注意到，随着 $\text{mex}$ 增大，满足条件的 $(l, r)$ 集合的变化是存在某种单调性的；具体来说，**最小的**满足条件的区间 $a[l, r]$ 是单调不减的，而这会大大方便我们的计算。

我们可以考虑先枚举 $\text{mex}$；$O(n^2)$ 预处理出不考虑其它任何条件的，$-1$ 出现次数为（每个）$k$ 的区间的个数，记为 $s[k]$；然后随着 $\text{mex}$ 的增加，我们动态维护 $c$，并且也动态维护满足当前 $\text{mex}$ 要求的、每个 $k$ 对应的区间数量。

这样的话，我们先枚举 $\text{mex}$ 得到 $c$，然后再枚举 $k$，就有答案计算式：

$$
\sum\limits_{\text{mex}=1}^n\sum\limits_{k=c}^n s[k]\cdot\binom{k}{c}\cdot c!\cdot (K-c)!
$$

关于维护，具体来说，我们需要维护变量 $c$、数组 $s[k]$ 和能包含当前 $\text{mex}$ 的所有 “初始已经在 $a$ 中出现的数字” 的最小区间 $a[l, r]$。当 $\text{mex}$ 增加 $1$ 时，若新的数字 $\text{mex}-1$ 在 $a$ 内尚未出现，那么 $c$ 会增加 $1$，$s[k], a[l, r]$ 无需调整；若新的数字 $\text{mex}-1$ 在 $a$ 内已经出现，我们则需要扩大 $a[l, r]$ 直至 $a[l, r]$ 包含数字 $\text{mex}-1$ 并同时维护 $s[k]$，为了做到这点，我们可以逐步移动 $l, r$ 指针，对于 $l$ 减少 $1$，在移动 $l$ 前我们需要删除所有 $a[l, r']|r\leq r'\leq n$ 区间对 $s[k]$ 的贡献，同理，对于 $r$ 增加 $1$，在移动 $r$ 前我们需要删除所有 $a[l', r]|1\leq l'\leq l$ 区间对 $s[k]$ 的贡献，这是因为这些删除的区间在移动 $l$ 或 $r$ 指针后无法包含所有当前 $\text{mex}$ 所必要的数字。另外注意，初始的 $a[l, r]$ 区间是完全为空的，因此遇到第一个在 $a$ 中已经出现的数字需要做些特殊处理；具体来说，若这个数字的位置为 $p$，那么我们需要将 $a[l, r]$ 置为 $a[p, p]$，并且删除所有 $a[l', r']|1\leq l'\leq r'< p$ 和 $a[l', r']|p< l'\leq r'\le n$ 区间的贡献，因为这些区间无法包含 $p$ 位置。

（一句话：式子只和 $c$ 和 $k$ 有关，$c$ 只和 $\text{mex}$ 有关，考虑最先枚举 $\text{mex}$（再枚举 $k$）；对每个 $k$，计算满足它的 $[l, r]$ 个数，再动态维护失效的 $[l, r]$ 个数。）

关于复杂度的话，不太明显的地方在我们维护 $s[k]$ 的部分的复杂度。可以发现，由于 $l, r$ 指针各自均为单调移动，于是每个区间对 $s[k]$ 的贡献只会被我们删除最多一次，因此维护 $s[k]$ 的复杂度也即为 $O(n^2)$ 的。

更多细节请详见代码。

## CODE

```cpp
#include <cstdio>
#include <vector>
#define ll long long
using namespace std;

const int M =1e9+7;

int Pow(int x, int k){
	int ret =1;
	for(ll p =1; p <= k; p <<=1, x =1ll*x*x%M)
		if((p&k) != 0)
			ret =1ll*ret*x%M;
	return ret;
}

int main(){
    int t;
    scanf("%d", &t); 
    while(t--){
		int n;
		scanf("%d", &n); 
		vector<int> a(n+1), pos(n, -1), pre(n+1);
		int totm1 =0;
		for(int i =1; i <= n; ++i){
			scanf("%d", &a[i]); 
			totm1 +=(a[i] == -1);
			if(a[i] != -1)
				pos[a[i]] =i;
			pre[i] =pre[i-1]+(a[i] == -1);
		}
		
		vector<int> fact(n+1), fact_inv(n+1);
		fact[0] =1;
		for(int i =1; i <= n; ++i)
			fact[i] =1ll*fact[i-1]*i%M;
		fact_inv[n] =Pow(fact[n], M-2);
		for(int i =n-1; i >= 0; --i)
			fact_inv[i] =1ll*fact_inv[i+1]*(i+1)%M;
		auto C =[&](int nn, int mm){
			return 1ll*fact[nn]*fact_inv[mm]%M*fact_inv[nn-mm]%M;
		};
		
		vector<int> cntm1_cntlr(n+1); /*即 s[k]*/
		for(int l =1; l <= n; ++l)
			for(int r =l; r <= n; ++r)
				cntm1_cntlr[pre[r]-pre[l-1]] =(cntm1_cntlr[pre[r]-pre[l-1]] +1)%M;
		int ans =0;
		for(int mex =1, basel =-1/*即 l*/, baser =-1/*即 r*/, cntneed =0/*即 c*/; mex <= n; ++mex){
			if(pos[mex-1] != -1){
				if(basel == -1){
					basel =baser =pos[mex-1];
					for(int l =1; l < basel; ++l)
						for(int r =l; r < basel; ++r)
							cntm1_cntlr[pre[r]-pre[l-1]] =(cntm1_cntlr[pre[r]-pre[l-1]] -1ll+M)%M;
					for(int l =basel+1; l <= n; ++l)
						for(int r =l; r <= n; ++r)
							cntm1_cntlr[pre[r]-pre[l-1]] =(cntm1_cntlr[pre[r]-pre[l-1]] -1ll+M)%M;
				}
				else{
					while(basel > pos[mex-1]){
						for(int l =basel, r =baser; r <= n; ++r)
							cntm1_cntlr[pre[r]-pre[l-1]] =(cntm1_cntlr[pre[r]-pre[l-1]] -1ll+M)%M;
						--basel;
					}
					while(baser < pos[mex-1]){
						for(int l =basel, r =baser; l >= 1; --l)
							cntm1_cntlr[pre[r]-pre[l-1]] =(cntm1_cntlr[pre[r]-pre[l-1]] -1ll+M)%M;
						++baser;
					}
				}
			}
			else
				++cntneed;

			int sum =0;
			for(int cntm1/*即 k*/ =cntneed; cntm1 <= n; ++cntm1){
				sum =(sum+1ll*cntm1_cntlr[cntm1]*C(cntm1, cntneed)%M)%M;
			}	

			ans =(ans+1ll*sum*fact[cntneed]%M*fact[totm1-cntneed]%M)%M;
		}

		printf("%d\n", ans);
	}
}
```

P.S. 文内 “一句话” 其实都是我的赛时草稿，感觉还挺精简舍不得删于是改了改写进文章了。

---

## 作者：Xy_top (赞：2)

简单题。

首先正难则反，发现一个区间内的 ``MEX`` 并不好求，此时看到题目解释中的 ``deletion``，发现它其实就是删除的元素当中最小的，那么显然有 $O(n^3)$ 做法。

具体思路如下，枚举 ``MEX`` 与删掉的前缀和后缀，然后按照这个数有没有出现过分类，就是一个简单的组合数学问题，代码：


```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n;
int a[5005], loc[5005], fac[5005], inv[5005];
int pre[5005], suf[5005], sum[5005], ssum[5005];
const int mod = 1000000007;
int q_pow (int x, int y) {
	if (y == 0) return 1;
	if (y & 1) return x * q_pow (x * x % mod, y >> 1) % mod;
	return q_pow (x * x % mod, y >> 1);
}
void init () {
	fac[0] = 1;
	For (i, 1, 5000) fac[i] = fac[i - 1] * i % mod;
	inv[5000] = q_pow (fac[5000], mod - 2);
	foR (i, 4999, 0) inv[i] = inv[i + 1] * (i + 1) % mod;
}
int A (int n, int m) {
	if (n < m) return 0;
	return fac[n] * inv[n - m] % mod;
}
void solve () {
	cin >> n;
	For (i, 0, n + 1) a[i] = loc[i] = pre[i] = suf[i] = sum[i] = ssum[i] = 0;
	For (i, 1, n) {
		cin >> a[i];
		sum[i] = sum[i - 1];
		if (a[i] != -1) loc[a[i] ] = i;
		else {
			++ sum[i];
			a[i] = 100000;
		}
	}
	ssum[0] = (loc[0] != 0);
	For (i, 1, n - 1) {
		if (!loc[i]) ssum[i] = ssum[i - 1] + 1;
		else ssum[i] = ssum[i - 1];
	}
	pre[0] = suf[n + 1] = 100000;
	For (i, 1, n) pre[i] = min (pre[i - 1], a[i]);
	foR (i, n, 1) suf[i] = min (suf[i + 1], a[i]);
	int ans = 0;
	For (i, 1, n - 1) {
		For (j, 0, n - 1) {
			For (k, j + 2, n + 1) {
				if (j == 0 && k == n + 1) continue;
				if (pre[j] >= i && suf[k] >= i) {
					if (loc[i]) {
						if (min (pre[j], suf[k]) == i) ans = (ans + (i * A (ssum[n - 1] - ssum[i], sum[j] + sum[n] - sum[k - 1]) % mod * fac[sum[k - 1] - sum[j] ] % mod) ) % mod;
					} else {
						//填 i ~ n 的答案减去填 i + 1 ~ n 的答案
						ans = (ans + (i * A (ssum[n - 1] - ssum[i - 1], sum[j] + sum[n] - sum[k - 1]) % mod - i * A (ssum[n - 1] - ssum[i], sum[j] + sum[n] - sum[k - 1]) % mod + mod) * fac[sum[k - 1] - sum[j] ] % mod) % mod;
					}
				}
			}
		}
	}
	cout << (ans + n * fac[sum[n] ] % mod) % mod;
}
signed main () {
	init ();
	int _ = 1;
	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}
/*
假设留区间 [l, r]，mex 为 k

那么 [1, l - 1] 与 [r + 1, n] 中不能有比 k 小的，
且如果出现 k，问号中都得填 > k 的，如果没有出现 k，选一个问号填 k，剩下的填 > k 的

0 2 1

1 2 0
*/
```

但是会超时，考虑优化。发现我们如果只枚举一个左端点 $l$，设所有右端点答案和为 $sum$，然后发现每次 $sum$ 的变化都只是加减第一项再乘除一个数，于是可以做到 $O(n^2)$。

代码改天闲着没事干再写。

---

## 作者：Unnamed114514 (赞：1)

首先我们把 $MEX(a_{l,r})$ 转化为 $\sum\limits_{k=0}^{n-1}[\forall i\in [0,k],i \in a_{l,r}]$，容易发现这显然是成立的，因为当 $k<MEX$ 时，值显然为 $1$，当 $k\ge MEX$ 时，$MEX$ 一定不出现，所以为 $0$。然后一个 $MEX$ 会贡献 $[0,MEX-1]$ 的 $k$，恰好为 $MEX$ 次。

我们先来想一个 $O(n^3)$ 的最暴力的解法。枚举 $k,l,r$，记 $[l,r]$ 中的 $-1$ 个数为 $c_1$，我们需要的 $-1$ 个数为 $c_2$，总的 $-1$ 个数为 $c_3$，容易得到该对 $(k,l,r)$ 的贡献是 ${c_1\choose c_2}c_2!(c_3-c_2)!$。

这个做法是 $O(n^3)$ 的，注意到 $c_2$ 随着 $k$ 的递增简单处理即可，$c_3$ 是定值，考虑钦定 $c_1$ 统计合法的 $[l,r]$。

- 若 $[0,k]$ 均未出现，那么区间可以在任意位置。我们统计全局每种 $-1$ 数量的区间有多少个，记作 $t$。然后枚举 $c_1$，容易发现式子是 $t_{c_1}{c_1\choose c_2}c_2!(c_3-c_2)$。

- 若 $[0,k]$ 中有数出现过，我们记 $i$ 出现的位置为 $pos_i$，那么选择的区间必须包含 $pos_0,\cdots,pos_k$，即包含 $[\min\{pos_i\},\max\{pos_i\}]$。

注意到我们直接算包含是不好算的，但是容易发现随着 $k$ 的增大，包含它的区间只减不增，因此每个区间只会删一次，每次更新区间的时候直接把它从 $t$ 里面扣掉就行了。

常数很小，跑得很快，从时间上来说是 CF 的最优解，但是空间打不过。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
const int N=5005,mod=1e9+7;
int T,n,a[N],s[N],pos[N],fac[N],inv[N],t[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<=5000;++i){
		fac[i]=1ll*fac[i-1]*i%mod;
		inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	}
	for(int i=2;i<=5000;++i) inv[i]=1ll*inv[i]*inv[i-1]%mod;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=0;i<n;++i) pos[i]=-1;
		for(int i=1;i<=n;++i){
			cin>>a[i];
			s[i]=s[i-1];
			if(~a[i]) pos[a[i]]=i;
			else ++s[i];
		}
		for(int i=0;i<=s[n];++i) t[i]=0;
		for(int l=1;l<=n;++l) for(int r=l;r<=n;++r) ++t[s[r]-s[l-1]];
		int ll=0,rr=-1,ans=0,cnt=0;
		for(int i=0;i<n;++i){
			if(~pos[i]){
				if(rr==-1){
					for(int l=1;l<pos[i];++l) for(int r=l;r<pos[i];++r) --t[s[r]-s[l-1]];
					for(int l=pos[i]+1;l<=n;++l) for(int r=l;r<=n;++r) --t[s[r]-s[l-1]];
					ll=rr=pos[i];
				} else if(pos[i]>rr){
					for(int l=1;l<=ll;++l) for(int r=rr;r<pos[i];++r) --t[s[r]-s[l-1]];
					rr=pos[i];
				} else if(pos[i]<ll){
					for(int l=pos[i]+1;l<=ll;++l) for(int r=rr;r<=n;++r) --t[s[r]-s[l-1]];
					ll=pos[i];
				}
			} else ++cnt;
			for(int k=cnt;k<=s[n];++k) ans=(ans+1ll*t[k]*fac[k]%mod*inv[k-cnt]%mod*fac[s[n]-cnt])%mod;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：ax_by_c (赞：0)

令 $-1$ 个数前缀和为 $sum$。

考虑拆贡献，对于每一个数 $x$ 计算有多少种排列和区间的组合方案使得这个区间的 mex 为 $x$。

首先 $<x$ 且存在的数是必选的，容易求出它们构成的极大区间。

令 $<x$ 且不存在的数的个数为 $h_x$。

设包含这个极大区间且有 $i$ 个 $-1$ 的区间个数为 $f_i$，那么答案就是 $\sum_i i!(sum_n-i)!\binom{sum_n-h_x}{i-h_x}f_i$（还要减去包含 $x$ 在内的方案数，先不管）。

那么 $f$ 就是前缀和后缀做卷积的结果了。直接做肯定是不行的，所以考虑从大到小扫 $x$，每次区间会往里面缩（直到缩到没有，先不管）。那么每次缩一个位置后可以 $O(n)$ 更新卷积结果，所以是对的。

接下来要减去 $x$ 在内的方案数。如果 $x$ 没有出现的话就减去 $h_x\leftarrow h_x+1$ 的结果即可。否则要减去这一轮缩之前的卷积结果（下标平移这一轮缩的 $-1$ 个数）再算。

接下来考虑没有区间的情况，那么 $<x$ 的数都不存在。不考虑减去包含 $x$ 在内的方案数的话就直接预处理即可。

考虑减去包含 $x$ 在内的方案数，因为 $x$ 没有出现时是好算的，而只会有最大的一个 $x$ 出现，所以暴力即可。

时间复杂度 $O(n^2)$。

[赛时代码](https://codeforces.com/contest/2084/submission/314145157)

整理后的代码：

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define per(i,r,l) for(int i=(r);i>=(l);i--)
#define repll(i,l,r) for(ll i=(l);i<=(r);i++)
#define perll(i,r,l) for(ll i=(r);i>=(l);i--)
#define pb push_back
#define ins insert
#define clr clear
using namespace std;
namespace ax_by_c{
typedef long long ll;
const ll mod=1e9+7;
const int N=5005;
ll ksm(ll a,ll b,ll p){
	a=a%p;
	ll r=1;
	while(b){
		if(b&1)r=r*a%p;
		a=a*a%p;
		b>>=1;
	}
	return r%p;
}
ll fac[N],inv[N];
void Init(int n){
	fac[0]=1;
	rep(i,1,n)fac[i]=fac[i-1]*i%mod;
	inv[n]=ksm(fac[n],mod-2,mod);
	per(i,n,1)inv[i-1]=inv[i]*i%mod;
}
ll C(int n,int m){
	if(n<m||n<0||m<0)return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int n,a[N],pos[N],sum[N],l[N],r[N],hh[N];
ll pre[N],suf[N],f1[N],f2[N],rf[N];
void slv(){
	scanf("%d",&n);
	Init(n);
	rep(i,0,n){
		pos[i]=0;
		pre[i]=0;
		suf[i]=0;
		f1[i]=0;
		hh[i]=0;
		f2[i]=0;
	}
	rep(i,1,n){
		sum[i]=sum[i-1];
		scanf("%d",&a[i]);
		if(a[i]!=-1)pos[a[i]]=i;
		else sum[i]++;
	}
	l[0]=n+1,r[0]=0;
	rep(i,1,n){
		l[i]=l[i-1],r[i]=r[i-1],hh[i]=hh[i-1];
		if(pos[i-1])l[i]=min(l[i],pos[i-1]),r[i]=max(r[i],pos[i-1]);
		else hh[i]++;
	}
	pre[0]=1;
	suf[0]=1;
	f1[0]=1;
	int cl=0,cr=n+1;
	ll ans=0;
	rep(l,1,n)rep(r,l,n)f2[sum[r]-sum[l-1]]++;
	per(x,n,1){
		if(l[x]<=r[x]){
			int oth_rm=0;
			if(pos[x])rep(i,0,n)rf[i]=(mod-f1[i])%mod;
			else rep(i,0,n)rf[i]=0;
			while(cl<l[x]-1){
				cl++;
				if(a[cl]==-1){
					oth_rm++;
					per(i,n,1)pre[i]=pre[i-1];
					pre[0]=1;
					per(i,n,1)f1[i]=f1[i-1];
					f1[0]=0;
					rep(i,0,n)f1[i]=(f1[i]+suf[i])%mod;
				}
				else{
					pre[0]=(pre[0]+1)%mod;
					rep(i,0,n)f1[i]=(f1[i]+suf[i])%mod;
				}
			}
			while(r[x]+1<cr){
				cr--;
				if(a[cr]==-1){
					oth_rm++;
					per(i,n,1)suf[i]=suf[i-1];
					suf[0]=1;
					per(i,n,1)f1[i]=f1[i-1];
					f1[0]=0;
					rep(i,0,n)f1[i]=(f1[i]+pre[i])%mod;
				}
				else{
					suf[0]=(suf[0]+1)%mod;
					rep(i,0,n)f1[i]=(f1[i]+pre[i])%mod;
				}
			}
			if(pos[x]){
				per(i,n,0){
					if(i>=oth_rm)rf[i]=rf[i-oth_rm];
					else rf[i]=0;
				}
			}
			rep(i,0,n)rf[i]=(rf[i]+f1[i])%mod;
			ll __s=0;
			rep(y,(sum[r[x]]-sum[l[x]-1]),n){
				ll tt=y;
				if(hh[x]<=tt&&tt<=n){
					__s=(__s+fac[tt]*C(sum[n]-hh[x],tt-hh[x])%mod*rf[y-(sum[r[x]]-sum[l[x]-1])]%mod*fac[sum[n]-y]%mod)%mod;
					if(tt>hh[x]&&!pos[x]&&x<n){
						__s=(__s-fac[tt]*C(sum[n]-hh[x]-1,tt-hh[x]-1)%mod*rf[y-(sum[r[x]]-sum[l[x]-1])]%mod*fac[sum[n]-y]%mod+mod)%mod;
					}
				}
			}
			ans=(ans+__s*x%mod)%mod;
		}
		else{
			if(pos[x]){
				rep(i,0,n)rf[i]=0;
				rep(l,1,n)rep(r,l,n){
					if(l<=pos[x]&&pos[x]<=r)continue;
					rf[sum[r]-sum[l-1]]++;
				}
			}
			else rep(i,0,n)rf[i]=f2[i];
			ll __s=0;
			rep(y,0,n){
				if(hh[x]<=y&&y<=n){
					__s=(__s+fac[y]*C(sum[n]-hh[x],y-hh[x])%mod*rf[y]%mod*fac[sum[n]-y]%mod)%mod;
					if(y>hh[x]&&!pos[x]&&x<n){
						__s=(__s-fac[y]*C(sum[n]-hh[x]-1,y-hh[x]-1)%mod*rf[y]%mod*fac[sum[n]-y]%mod+mod)%mod;
					}
				}
			}
			ans=(ans+__s*x%mod)%mod;
		}
	}
	printf("%lld\n",ans);
}
void main(){
	int T=1;
	scanf("%d",&T);
	while(T--)slv();
}
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ax_by_c::main();
	return 0;
}
```

---

## 作者：cyc001 (赞：0)

非官方做法，图一乐

~~想了 1h 没有别的 idea 写了个感觉过不了一点的 FFT $\sout{O(n^2\log n)}$ 过了 /ll。早知道就直接写了。~~

### 题意简述

给你一个部分位置确定的排列，定义一个排列的代价为：

$$
\sum\limits_{l=1}^n\sum\limits_{r=l}^n \text{MEX}(p_l,\dots,p_r)
$$

问所有可能的排列的代价和。

### Solution

考虑对每个 $k$ 对满足 $\text{MEX}(p_l,\dotsm,p_r)\ge k$ 的 $(p,l,r)$ 三元组数量求和。

定义 $c(l,r)$ 表示 $[l,r]$ 中还没确定的位置个数。

定义 $h(l,r,k)$ 表示 $[l,r]$ 的答案是否可以为 $k$。

定义 $q(k)$ 表示未确定的 $\le k$ 的元素个数。

则

$$
Ans=\sum\limits_{l=1}^n\sum\limits_{r=l}^n\sum\limits_{k=1}^{n} h(l,r,k)\binom{c(l,r)}{q(k)}q(k)!(c(1,n)-q(k))!
$$

考虑优化

$q(k)=k$ 的情况直接 dp 是好做的。

剩下的情况发现 $h(l,r,k)=1$ 是只需要 $[l',r']\subset [l,r]$，其中 $[l',r']$ 是最小满足每个确定的 $\le k$ 的元素位置都包含的区间。

然后修改一下式子

$$
\sum\limits_{l=1}^{l'}\sum\limits_{r=r'}^{n}\sum\limits_{k=1}^n \binom{c(l,l'-1)+c(l',r')+c(r'+1,r)}{q(k)}q(k)!(c(1,n)-q(k))!\\
$$

容易发现可以用 FFT 优化。

时间复杂度 $O(n^2\log n)$，我也不知道为什么能过。

```cpp
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
class mathbase{
private:
    vector<lint> fct,ifct;
public:
    constexpr auto qpow(lint a,auto b) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x) const{return qpow(x,MOD-2);}
    auto init(const auto n){
        fct.resize(n,1);
        cir(i,1,n) fct[i]=fct[i-1]*i%MOD;
        ifct.resize(n);
        ifct[n-1]=inv(fct[n-1]);
        for(auto i=n-2;~i;--i) ifct[i]=ifct[i+1]*(i+1)%MOD;
    }
    auto C(const auto a,const auto b) const{
        if(a<b||b<0) return 0ll;
        return fct[a]*ifct[b]%MOD*ifct[a-b]%MOD;
    }
    auto fact(const auto x) const{return x>-1?fct[x]:0;}
} math;
using complf=complex<double>;
class basic_poly{
private:
    static constexpr auto pi=acosl(-1);
    auto change(vector<complf>&a,const int n){
        vector<int> rev(n);
        cir(i,0,n) rev[i]=((rev[i>>1]>>1)|((n>>1)*(i&1)));
        cir(i,0,n) if(i<rev[i]) swap(a[i],a[rev[i]]);
    }
    template<const int type>
    auto fft(vector<complf>&a,const int n){
        change(a,n);
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h/2;
            const auto wx=complf(cos(pi*2/h),sin(pi*2*type/h));
            for(auto i=0;i<n;i+=h){
                auto u=complf(1,0);
                cir(k,i,i+midh){
                    const auto wy=u*a[k+midh];
                    a[k+midh]=a[k]-wy;a[k]+=wy;
                    u*=wx;
                }
            }
        }
        if(type==-1) for(auto&i:a) i/=n;
    }
public:
    auto mul(vector<lint> a,vector<lint> b){
        const auto n=1<<((int)(log2(a.size()+b.size()))+1);
        vector<complf> fx(n);
        cir(i,0,(int)(a.size())) fx[i]+=complf(a[i],0);
        cir(i,0,(int)(b.size())) fx[i]+=complf(0,b[i]);
        fft<1>(fx,n);
        for(auto&i:fx) i*=i;
        fft<-1>(fx,n);
        vector<lint> res(n);
        cir(i,0,n) res[i]=roundl(fx[i].imag()/2);
        return res;
    }
} poly;
static constexpr auto maxn=5007;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    math.init(maxn);
    while(T--) [&]{
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i;
        const auto m=ranges::count(a,-1);
        vector<lint> cur(m+1);
        vector<lint> qans(m+1);
        cir(i,0,n){
            if(a[i]==-1){
                for(auto i=m;i;--i) (cur[i]+=cur[i-1])%=MOD;
                (++cur[1])%=MOD;
            }
            ++cur[0];
            cir(i,0,m+1) (qans[i]+=cur[i])%=MOD;
        }
        auto ans=0ll;
        vector<int> pos(n,-1);
        cir(i,0,n) if(a[i]>-1) pos[a[i]]=i;
        cir(w,1,n+1){
            auto l=n,r=0,cnt=0;
            cir(x,0,w) if(pos[x]>-1){
                l=min(l,pos[x]);
                r=max(r,pos[x]);
            }else{
                ++cnt;
            }
            if(l>r){
                cir(c,cnt,cnt+1) (ans+=qans[c]*math.fact(m-c)%MOD*math.fact(c))%=MOD;
            }else{
                auto mc=0;
                cir(i,l,r+1) mc+=(a[i]==-1);
                vector<lint> al(l+1),ar(n-r+1);
                auto wcnt=0;
                al[0]=ar[0]=1;
                for(auto i=l-1;~i;--i) wcnt+=(a[i]==-1),++al[wcnt];
                wcnt=0;
                cir(i,r+1,n) wcnt+=(a[i]==-1),++ar[wcnt];
                const auto res=poly.mul(al,ar);
                cir(i,0,(int)(res.size())) if(res[i]) (ans+=(res[i]%MOD)*math.C(i+mc,cnt)%MOD*math.fact(m-cnt)%MOD*math.fact(cnt))%=MOD;
            }
        }
        cout<<ans<<'\n';
    }();
    return 0;
}

```

令人忍俊不禁。

---

## 作者：DengDuck (赞：0)

經典 Trick：
$$
\sum_{i=0}^n[x>i]=x
$$

所以我們統計區間的 MEX 等價於對於當前形態統計所有的“MEX 比 $i$ 大的區間數量”的和。

枚舉形態不可行，所以考慮枚舉區間然後考慮這個區間所有形態的貢獻。

那麼不難想到枚舉上面那個式子的 $i$，然後我們的目標是湊出來 $[0,i]$，首先對於我們肯定得包含真實出現的 $[0,i]$ 的數字，那麼我們求出這樣的一個最小區間，則合法區間必然有此區間作為子區間。

同時顯然還要滿足區間內的 $-1$ 可以把剩下的部分補上。

然後滿足的條件的區間我們可以這麼計算方案數：設區間內 $-1$ 數量為 $C$，設總 $-1$ 數量為 $S$，然後區間內需要填充 $K$ 個 $-1$，可以得到 $\binom {C}{K}(S-K)!K!$。

我們發現對於固定的 $i$ 有固定的 $K$，然後我們枚舉 $C$ 就行，需要統計這麼多 $-1$ 的區間數量。

---

