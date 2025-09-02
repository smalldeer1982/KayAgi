# Permutation Problem (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference is that in this version $ n \leq 5 \cdot 10^5 $ and the sum of $ n $ for all sets of input data does not exceed $ 5 \cdot 10^5 $ .

You are given a permutation $ p $ of length $ n $ . Calculate the number of index pairs $ 1 \leq i < j \leq n $ such that $ p_i \cdot p_j $ is divisible by $ i \cdot j $ without remainder.

A permutation is a sequence of $ n $ integers, in which each integer from $ 1 $ to $ n $ occurs exactly once. For example, $ [1] $ , $ [3,5,2,1,4] $ , $ [1,3,2] $ are permutations, while $ [2,3,2] $ , $ [4,3,1] $ , $ [0] $ are not.

## 说明/提示

In the first set of input data, there are no index pairs, as the size of the permutation is $ 1 $ .

In the second set of input data, there is one index pair $ (1, 2) $ and it is valid.

In the third set of input data, the index pair $ (1, 2) $ is valid.

In the fourth set of input data, the index pairs $ (1, 2) $ , $ (1, 5) $ , and $ (2, 5) $ are valid.

## 样例 #1

### 输入

```
6
1
1
2
1 2
3
2 3 1
5
2 4 1 3 5
12
8 9 7 12 1 10 6 3 2 4 11 5
15
1 2 4 6 8 10 12 14 3 9 15 5 7 11 13```

### 输出

```
0
1
1
3
9
3```

# 题解

## 作者：TTpandaS (赞：6)

令 $x_i=i,y_i=p_i$，那么符合要求的 $i,j$ 满足 $x_i  x_j  \mid y_i y_j$。

将 $x_i$ 和 $y_i$ 都除以 $\gcd$，那么对条件 $x_i  x_j  \mid y_i y_j$ 不会产生影响， $x_i$ 和 $y_i$ 都将互质，那么只需要判断 $x_i  \mid y_j \wedge x_j \mid y_i$ 即可。

然后枚举 $i$，寻找 $j<i$ 的满足条件的 $j$ 的数量。

对于 $x_i> \sqrt n $ 的情况，直接枚举 $y_j$。在之前用一个 vector 记录每个 $y_j$ 对应了哪些 $x_j$，然后枚举判断即可。

对于 $x_i< \sqrt n $ 的情况，直接枚举 $x_j$，即找 $y_i$ 的因数，先质因数分解，在搜索即可。得到每一个因数后，在之前再用一个 vector 记录每个 $x_j$ 对应了哪些 $y_j$，然后枚举判断即可。

时间复杂度看上去是 $O(n^2)$ 的，但实际上是 $O(\text{稳过})$，倒数第二劣解。

---

## 作者：CCPSDCGK (赞：4)

被 Div.3 薄纱了。

神金题目，怎么还卡空间的。

首先将目标转化成 $\dfrac{p_i}i\times\dfrac{p_j}j$ 是否为整数。

如果将 $\dfrac{p_i}i$ 约分变为 $\dfrac{a_i}{b_i}$，那么对于 $\dfrac{a_i}{b_i}\times\dfrac{a_j}{b_j}$ 则满足 $\gcd(a_i,b_i)=\gcd(a_j,b_j)=1$，$\dfrac{a_i}{b_i}\times\dfrac{a_j}{b_j}$ 为整数当且仅当 $b_j|a_i$ 且 $b_i|a_j$。

我们知道 $1\sim n$ 的所有因子数之和为 $O(n\ln n)$，而由于 $a_i\le p_i$，所以 $\sum d(a_i)\le \sum d(p_i)=O(n\ln n)$。

所以枚举 $i$ 后暴力枚举 $a_i$ 的因子 $b_j$，然后查询有多少个 $a_j$ 满足 $b_i|a_j$。

查询可以做到 $O(1)$，只需要预处理对于每个 $b_i$，$a_i$ 是 $x$ 的倍数有多少个，相同的 $b_i$ 可以压在一块，如果用哈希表存所有可能的 $x$ 以及对应的值，复杂度只有 $O(\sum d(a_i))\le O(n\ln n)$。

最后预处理一下每个数的所有因子即可。

这样时空复杂度都是 $O(n\ln n)$，理论来说能过，但因为多了个哈希表导致 MLE，这就是这道题的神金之处。

那既然卡了，我们就改进改进。

注意到计算答案时枚举 $i$ 后枚举 $b_j$ 的复杂度为 $O(n\ln n)$，如果我们将相同的 $b_j$ 一块处理，我们就不用哈希表了，但将所有 $b_j$ 存下来还是需要 $O(n\ln n)$ 的额外空间，其实大可不必，当枚举到 $b_j=x$ 的时候，只需要找到所有 $x|a_i$，所以只需要将相同的 $a_i$ 用 vector 存起来然后暴力枚举即可，额外空间复杂度为 $O(n)$。

但由于存储 $1\sim n$ 的所有因子不可省略，所以时空复杂度还是 $O(n\ln n)$。
```
vector<int> d[500005],v2[500005],v1[500005];
int p[500005],a[500005],sum[500005];
int main(){
	for(int i=1;i<500001;i++) for(int j=i;j<500001;j+=i) d[j].eb(i);
	int t;cin>>t;
	while(t--){
		int n;cin>>n;
		for(int i=1;i<=n;i++) cin>>p[i],a[i]=__gcd(p[i],i),v1[i/a[i]].eb(p[i]/a[i]),v2[p[i]/a[i]].eb(i/a[i]);
		ll ans=0;
		for(int i=1;i<=n;i++){
			for(int j:v1[i]) for(int x:d[j]) sum[x]++;
			for(int j=i;j<=n;j+=i) for(int x:v2[j]) ans+=sum[x];
			for(int j:v1[i]) for(int x:d[j]) sum[x]=0;
		}
		for(int i=1;i<=n;i++) ans-=a[i]==i;
		cout<<(ans>>1)<<endl;
		for(int i=1;i<=n;i++) v1[i].clear(),v2[i].clear();
	}
	return 0;
}
```

---

## 作者：Mr_Az (赞：3)

## Question 问题 [CF1986G2 Permutation Problem (Hard Version)](https://www.luogu.com.cn/problem/CF1986G2)

难度：$\colorbox{#8942cc}{\color{White}省选/NOI−}$

给定一个 $1\sim n$ 的排列 $p$，求整数对 $(i,j)$ 的数量，满足 $1\le i<j\le n$ 且 $p_i\cdot p_j$ 能被 $i\cdot j$ 整除。每个测试点 $t$ 组测试用例。

#### 数据范围

- $1\le n\le 5\cdot 10^5$；

- $\sum n\le 5\cdot 10^5$。

## Analysis 思路分析

首先对于 $\frac{p_i \cdot p_j}{i \cdot j}$ 是否为整数，我们会发现可能 $i,j$ 可能存在 $p_i$ 的因数，这让我们解题变得更加复杂。我们想让影响的因素尽可能减少。

发现该形式可以写作 $\frac{p_i}{i} \cdot \frac{p_j}{j}$，所以我们可以先将 $\{p_i,i\}$ 分别除去他们两个的 $\gcd$。这一步是为了避免 $p_i$ 和 $i$ 之间存在可能可以除的关系。

也就是令 $a_i=\frac{i}{\gcd(p_i,i)}$，$b_i=\frac{p_i}{\gcd(p_i,i)}$，该问题就转化为了求 $a_i \mid b_j$ 并且 $a_j \mid b_i$ 的 $\{i,j\}$ 有序二元组。思考如何计算。

## Solution 数学

感觉整体的思路就是 $b_i \stackrel{扩倍}\to a_i \stackrel{查询}\to \{a_j,b_j\}$ 如同通关游戏一样。我们可以先枚举 $b_i$ 在借此枚举出 $b_i$ 的倍数 $a_i$，并在此基础上查询有多少个 $b_j$ 符合 $a_i \mid b_j$，那这样子的话就符合了我们的 $a_i \mid b_j$ 并且 $a_j \mid b_i$ 的条件，关键在于如何查询。

最初的想法是维护一个二维数组 $cnt_{i,j}$ 表示满足 $a_k=i$ 并且 $j \mid b_k$。但是很容易发现我们连数组都开不下。即使考虑使用 `map` 维护，最坏的情况下空间会因为 `map` 被插入内容过大而爆炸，这也是很多人在此题 `128MiB` 的限制下 MLE 了。

考虑如何优化，我们会发现 $cnt_{x,...}$ 只会在所有 $x \mid b_j$ 的 $j$ 有贡献出现。那这样子我们只需要去枚举 $j$ 即可，压掉一维。

或者换一种方式思考，我们当前先枚举 $b_i$ 后可以通过我们建立的 $\{a_i\}$ 和 $\{b_i\}$ 双射找到其对应的所有 $\{a_i\}$。那这样下来，我们未知的就只剩下 $\{a_j,b_j\}$ 了。所以我们再度枚举 $a_j$ 并保证他是 $b_i$ 的倍数，去找对应满足 $b_j \mid a_i$ 的 $b_j$ 数量了。

我们预处理出该 $b_i$ 对应的所有 $\{a_i\}$ 的因数个数和。令 $cnt_i$ 表示有多少个 $a_i$ 拥有 $i$ 这个因数。接下来枚举 $a_i$ 的倍数，并计算出此时 $k\cdot b_i=a_j$ 对应的所有 $\{b_i\}$，那么 $a_j$ 对答案的贡献就是 $cnt_{b_i}$。

在最后，由于本题询问的是有序二元组，以上做法并没有考虑 $i < j$，所以最终答案需要除以二。同时当 $i=j$，只会在 $a_i \mid b_i$ 时产生一个贡献。所以提前减掉即可。

记得清空。

#### 时间复杂度：

因为 $[1,n]$ 之间的因数个数和的复杂度为 $O(n\ln n)$，下面统计答案首先枚举 $b_i$，并且还去寻找其对应的所有因数，整体的复杂度与上面同阶为 $O(\sum fac_{a_i}) \le O(n \ln n)$，所以整体复杂度为 $O(n \ln n)$。

## Code 代码

```cpp
signed main(){
    for(rint i=1;i<=N-7;i++) for(rint j=i;j<=N-7;j+=i) fac[j].pb(i);
    read(T);
    while(T--){
        ans=0;
        read(n);
        for(rint i=1,t;i<=n;i++){
            read(t);
            int x=i/__gcd(i,t),y=t/__gcd(i,t);//除去 gcd
            a[x].pb(y);b[y].pb(x);//建立双射，有利于计算答案
            if(x==1) ans--;//对于 i=j 且 ai|bi 的情况提前减掉
        }
        for(rint i=1;i<=n;i++){
            for(auto a1:a[i]) for(auto a2:fac[a1]) cnt[a2]++;//处理因数个数和
            for(rint a2=i;a2<=n;a2+=i) for(auto b1:b[a2]) ans+=cnt[b1];//计算贡献
            for(auto a1:a[i]) for(auto a2:fac[a1]) cnt[a2]=0;//清空
        }
        for(rint i=1;i<=n;i++) a[i].clear(),b[i].clear();//清空
        cout<<ans/2<<endl;//注意有序，除以二
    }
	return 0;
}
```

---

## 作者：Purslane (赞：3)

# Solution

显然设分数 $s_i = \dfrac{p_i}{i} = \dfrac{a_i}{b_i}$，其中 $(a_i,b_i)=1$。

显然 $s_is_j \in \mathbb Z$ 等价于 $b_i \mid a_j$ 且 $b_j \mid a_i$。

采取最暴力的计算方式：固定 $i$，计算有多少个满足条件的 $j$ 再求和。

考虑枚举 $b_i$。对于所有 $b_i$ 相同的  $i$，把 $a_i$ 的所有因数都扔进一个桶中。

然后枚举 $j$，查询所有这样的 $j$，$b_j$ 在桶中的值。

这样你得到了 $ij \mid p_ip_j$ 的有序对 $(i,j)$ 个数。

删去 $i=j$ 的部分，除以 $2$，就得到了答案。

------

复杂度分析：

把 $a$ 的因子扔进桶的部分，显然只会进行 $\sum_{i=1}^n d(a_i) \le \sum_{i=1}^n d(i) = O(n \ln n)$ 次。

暴力找 $j$ 的部分，一个 $j$ 只会被找 $d(a_j)$ 次，因此这部分复杂度也是 $O(n \ln n)$ 的。（还要记录那些无用功，也就是不存在 $a_j = t$ 的 $t$ 也会被枚举 $d(t)$ 次，不过这一部分的复杂度也是 $O(n \ln n)$ 的）。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5e5+10;
int T,n,a[MAXN],b[MAXN],cnt[MAXN];
vector<int> frac[MAXN],occa[MAXN],occb[MAXN];
ll ans;
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	n=500000;
	ffor(i,1,n) ffor(j,1,n/i) frac[i*j].push_back(i);
	cin>>T;
	while(T--) {
		cin>>n;
		ffor(i,1,n) cin>>a[i],b[i]=i;
		ffor(i,1,n) {
			int del=__gcd(a[i],b[i]);
			a[i]/=del,b[i]/=del;	
		}
		ffor(i,1,n) occb[b[i]].push_back(i),occa[a[i]].push_back(i);
		ffor(i,1,n) if(occb[i].size()) {
			for(auto id:occb[i]) for(auto div:frac[a[id]]) cnt[div]++;
			ffor(j,1,n/i) if(occa[i*j].size()) for(auto id:occa[i*j]) ans+=cnt[b[id]];
			for(auto id:occb[i]) for(auto div:frac[a[id]]) cnt[div]--;	
		}
		ffor(i,1,n) if(a[i]%b[i]==0) ans--;
		cout<<ans/2<<'\n';
		ans=0;
		ffor(i,1,n) occa[i].clear(),occb[i].clear();
	}
	return 0;
}
```

---

## 作者：Alex_Wei (赞：3)

### [CF1986G2 Permutation Problem (Hard Version)](https://www.luogu.com.cn/problem/CF1986G2)

设 $d_i = \gcd(p_i, i)$，$a_i = \frac {p_i} {d_i}$，$b_i = \frac i {d_i}$，则合法当且仅当 $b_i\mid a_j$ 且 $b_j\mid a_i$。

枚举 $b_j$（而不是 $j$）的值 $u$，以 $b_i$ 的值 $v$ 作为桶的下标。设 $buc_v$ 表示有多少 $i$ 满足 $b_j\mid a_i$ 且 $b_i = v$，可以暴力枚举 $u$ 的倍数计算。对于 $b_j = u$ 的 $j$，考虑到 $b_i\mid a_j$ 的限制，其贡献为所有 $buc_c$ 的和，其中 $c\mid a_j$。

时间复杂度 $\mathcal{O}(n\log n)$，空间复杂度 $\mathcal{O}(n)$。

为了避免预处理每个数的所有因数导致空间复杂度退化为 $\mathcal{O}(n\log n)$，[代码](https://codeforces.com/contest/1986/submission/269577205) 使用了根号分解法，时间复杂度为 $\mathcal {O} (n ^ {1.5})$。一种时空均优秀但较麻烦的实现方法是预处理每个数的最小质因子，从而求出 $a_j$ 的所有质因子，再通过 DFS 求出 $a_j$ 的所有因子。

---

## 作者：Albert_van (赞：3)

[题](https://www.luogu.com.cn/problem/CF1986G2) [题](https://codeforces.com/problemset/problem/1986/G2)。要求 $\frac {p_ip_j}{ij}$ 为整数。先行把确定部分的 $\gcd$ 约去能够简化问题。令 $\frac {p_i}i=\frac{a_i}{b_i}(\gcd(a_i,b_i)=1)$，$\frac{a_ia_j}{b_ib_j}$ 为整数，那么 $\frac{a_ia_j}{b_i}$ 要为整数，这意味着 $b_i|a_j$，同理 $b_j|a_i$。于是原条件转化为了 $b_i|a_j,b_j|a_i$。

接下来就是一系列枚举。先确定一个 $b$，对所有 $b_i=b$ 的 $i$ 尝试统计。枚举 $b$ 的倍数 $a$，对所有 $a_j=a$ 的 $j$，将 $b_j$ 扔到桶里（第一部分）。最后考虑所有 $b_i=b$ 的 $i$，枚举 $a_i$ 的因数，将对应桶里 $b_j$ 的个数加和即可（第二部分），得到答案 $k$。对所有 $b$ 的 $k$ 加和得到 $ans$，令 $i|p_i$ 的下标 $i$ 个数为 $t$，最终答案为 $\frac{ans-t}2$。

复杂度？乍看之下有 $\mathcal O(ns),s=\max\{d(i)\}$。然而，$p$ 是排列，这提供了好的性质。因为 $a_i|p_i$，而 $p_i$ 恰取遍 $[1,n]$，所以 $\sum d(a_i)=\mathcal O(n\ln n)$。因此第一部分（每个 $j$ 都会被枚举 $a_j$ 的因数个数次）和第二部分（对于每个 $i$ 运算次数与 $a_i$ 的因数个数相当）的总复杂度均为 $\mathcal O(n\ln n)$。

实现小心，不要直接在值域上操作。

```cpp
#include <cstdio>
#include <vector>

using namespace std;

void re(int &x){}

int gcd(int a,int b){return a%b==0?b:gcd(b,a%b);}

const int N=514114;

vector<int> cra[N],crb[N],cla,clb,dv[N],mtp[N];

int c[N];bool vis[N],ex[N];

int main()
{
	for(int i=1;i<N;++i) for(int j=i;j<N;j+=i) dv[j].push_back(i); 
	int T;re(T);while(T--){
		int n,x,t=0;long long ans=0;re(n);
		for(int i=1,a,b;i<=n;++i) re(x),a=x/gcd(i,x),b=i/gcd(i,x),ex[b]=1,t+=x%i==0,
			cla.push_back(a),clb.push_back(b),cra[a].push_back(b),crb[b].push_back(a);
		for(int a:cla) if(!vis[a]){
			for(int b:dv[a]) if(ex[b]) mtp[b].push_back(a);
			vis[a]=1;
		}
		for(int b:clb) if(ex[b]){
			for(int a:mtp[b]) for(int b:cra[a]) ++c[b];
			for(int a:crb[b]) for(int b:dv[a]) ans+=c[b];
			for(int a:mtp[b]) for(int b:cra[a]) c[b]=0;
			ex[b]=0;
		}
		printf("%lld\n",(ans-t)>>1);
		for(int a:cla) cra[a].clear(),vis[a]=0;
		for(int b:clb) crb[b].clear(),mtp[b].clear();
		cla.clear();clb.clear();
	}
}
```

---

## 作者：lfxxx (赞：2)

这怎么可能有 2500？

考虑对于每个 $\frac{p_i}{i}$ 约分后变为 $\frac{a}{b}$，对于两组 $\frac{a_1}{b_1},\frac{a_2}{b_2}$ 相乘后为整数等价于 $b_1|a_2,b_2|a_1$，因为 $a_1,b_1$ 与 $a_2,b_2$ 都是互质数对。

考虑同时处理 $b_1$ 相同的所有 $a_1$，我们枚举 $b_1$ 的所有倍数作为 $a_2$，假若不约分由于 $a_2$ 是排列，因此每对 $a_2,b_2$ 对被枚举的次数之和是 $O(n \log n)$，但是注意到约分后因数数量减少，因此每对 $a_2,b_2$ 被枚举的次数之和最多还是 $O(n \log n)$，将对应的 $b_2$ 加到桶中后，考虑枚举 $b_1$ 对应的所有 $a_1$ 的因数 $b_2$，不约分枚举总量是 $O(n \log n)$，而约分后因数数量减少因此枚举总量还是不超过 $O(n \log n)$，枚举时直接在桶中查询一下存在的 $b_2$ 的数量即可。

总时间复杂度 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5+114;
vector<int> d[maxn];
long long ans;
int cnt[maxn];
int n,p[maxn];
vector<int> A[maxn];//A[i] b=i 的所有 a
vector<int> B[maxn];//B[i] a=i 的所有 b;
void work(){
    ans=0;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i];
        int a=p[i]/__gcd(p[i],i),b=i/__gcd(p[i],i);
        A[b].push_back(a);
        B[a].push_back(b);
        if(b==1) ans--;//自己不能与自己贡献
    }
    for(int b=1;b<=n;b++){
        // a/b x/y
        for(int x=b;x<=n;x+=b){
            for(int y:B[x]) cnt[y]++;
        }
        for(int a:A[b]){
            for(int D:d[a]) ans+=cnt[D];
        }
        for(int x=b;x<=n;x+=b){
            for(int y:B[x]) cnt[y]--;
        }
    }
    cout<<(ans/2)<<'\n';
    for(int i=1;i<=n;i++) A[i].clear(),B[i].clear();
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    for(int i=1;i<=500000;i++){
        for(int j=i;j<=500000;j+=i) d[j].push_back(i);
    }
    int T;
    cin>>T;
    while(T--) work();
    return 0;
}
```

---

## 作者：Wuyanru (赞：2)

神秘的消 $\log$ 题。

[题目链接](https://www.luogu.com.cn/problem/CF1986G2)。

## 题意

给定一个长为 $n$ 的排列 $p$，求 $1\le i<j\le n$ 且 $(i\times j)\mid(p_i\times p_j)$ 的 $(i,j)$ 对数。

$1\le \sum n\le 5\times 10^5$。

## 题解

考虑令 $g_i=\gcd(i,p_i)$，并使用 $x_i=\dfrac{i}{g_i},y_i=\dfrac{p_i}{g_i}$。

那么 $(i\times j)\mid(p_i\times p_j)$ 相当于 $(x_i\times x_j)\mid (y_i\times y_j)$。

注意到此时 $x_i$ 与 $y_i$ 互质，且 $x_j$ 与 $y_j$ 互质，所以上述条件相当于 $x_i\mid y_j$ 且 $x_j\mid y_i$。

考虑忽略 $i<j$ 的条件，先求出所有满足的 $(i,j)$，再去掉 $i\ge j$ 的情况。

维护数组 $vis_{u,v}$ 表示所有 $(x_k,y_k)$ 中，满足 $x_k=u$ 且 $v\mid y_k$ 的 $k$ 的数量。

那么可以发现，对于一个 $i$ 来说，合法的 $j$ 的数量便是 $\sum_{d\mid y_i}vis_{d,x_i}$。

（自己思考一下 $x_i\mid y_j$ 且 $x_j\mid y_i$ 的条件就能明白这为什么是对的。）

考虑这样做的时间复杂度，首先 $vis$ 是一个 $n\times n$ 的数组，显然开不下，所以需要使用 map 维护。

再来计算处理 $vis$ 数组的复杂度，可以发现最坏需要在 map 中插入 $O(n\ln n)$ 次，所以这部分复杂度是 $O(n\log^2n)$ 的。

查询的复杂度完全相同，这样就得到了一个 $O(n\log^2n)$ 的做法，可以通过 G1。

核心代码大概长这个样子（其中 $d_i$ 存储所有 $i$ 的因数）：

```c++
for(int i=1;i<=n;i++) for(int j:d[y[i]]) vis[x[i]][j]++;
for(int i=1;i<=n;i++) for(int j:d[y[i]]) ans+=vis[j][x[i]];
```

如果要优化这个做法，必须要去掉一个 $\log$，考虑避免使用 map 来消掉一个 $\log$。

想想我们为什么要用 map，原因是 $n\times n$ 的数组开不下。

但是一个 $1\times n$ 的数组是开的下的，那么我们枚举一个 $x$，考虑能否计算所有 $vis_{x,\ast}$ 的贡献。

维护 $vis_x$ 是容易的，找到所有 $x_i=x$ 的 $i$，像上面一样插入即可。

查询也是容易的，发现 $vis_x$ 只会给所有 $x\mid y_j$ 的 $j$ 产生贡献，那么我们直接枚举 $j$ 就可以了。

特别地，这里我们可以先枚举 $y_j$ 再枚举 $j$，这样这里的枚举总复杂度是 $O(n\ln n)$ 的。

所以我们得到了一个复杂度是 $O(n\ln n)$ 的做法。非常神奇。

## 代码

上述做法并没有保证 $i<j$，所以需要先把 $i\ge j$ 的情况去掉。

容易发现 $i=j$ 的情况只会在 $x_i\mid y_i$ 时恰好被计算一次（这个条件与 $x_i=1$ 等价），减掉之后就只剩 $i\ne j$ 的情况了，显然 $i<j$ 与 $i>j$ 的方案数相同。

```c++
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f3f3f3f3fll
#define debug(x) cerr<<#x<<"="<<x<<endl
using namespace std;
using ll=long long;
using ld=long double;
using pli=pair<ll,int>;
using pi=pair<int,int>;
template<typename A>
using vc=vector<A>;
inline int read()
{
    int s=0,w=1;char ch;
    while((ch=getchar())>'9'||ch<'0') if(ch=='-') w=-1;
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
vc<int>num1[500001];
vc<int>num2[500001];
int val[500001];
vc<int>d[500001];
int a[500001];
int n;
int main()
{
    for(int i=1;i<=500000;i++) for(int j=1;i*j<=500000;j++) d[i*j].push_back(i);
    int T=read();
    while(T--)
    {
        n=read();
        for(int i=1;i<=n;i++) a[i]=read();

        ll ans=0;
        for(int i=1;i<=n;i++)
        {
            int x=i,y=a[i],g=__gcd(x,y);
            x/=g,y/=g;
            num1[x].push_back(y);
            num2[y].push_back(x);
            if(y%x==0) ans--;
        }
        for(int x=1;x<=n;x++)
        {
            for(int j:num1[x]) for(int k:d[j]) val[k]++;
            for(int y=x;y<=n;y+=x) for(int k:num2[y]) ans+=val[k];
            for(int j:num1[x]) for(int k:d[j]) val[k]--;
        }
        for(int i=1;i<=n;i++) num1[i].clear(),num2[i].clear();
        printf("%lld\n",ans/2);
    }
    return 0;
}
```

感谢观看！

---

## 作者：_Cheems (赞：0)

直接统计是困难的，考虑简化条件，令 $p_i,i$ 除以它们的最大公因数，分别得到 $a_i,b_i$，这样的好处是 $a,b$ 互质。因此，$\frac{a_ia_j}{b_ib_j}$ 为整数当且仅当 $b_j\mid a_i$ 且 $b_i\mid a_j$。

记 $d(n)$ 为 $n$ 的因数个数。显然 $\sum d(b_i)=\sum d(p_i)=O(n\ln n)$，由于 $a_i\mid p_i$，所以也有 $\sum d(a_i)=O(n\ln n)$。利用这一点统计答案。

具体而言，枚举值域。枚举数对 $b\mid a$，然后用桶 $buc$ 统计 $a_j=a$ 的 $b_j$ 个数；最后对 $b_i=b$ 的 $a_i$ 大力枚举其因数 $d$，贡献就是 $buc_d$。 

上述过程可以视为两部分，由先前的讨论，每一部分的复杂度都是 $O(n\ln n)$ 的，所以总复杂度 $O(n\ln n)$。注意下循环顺序不然复杂度会退化。
#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;
int T, n, a[N], b[N], buc[N];
long long ans;
vector<int> x[N], y[N], ys[N]; 

signed main(){
	cin >> T;
	while(T--){
		scanf("%d", &n);
		ans = 0;
		for(int i = 1; i <= n; ++i) x[i].clear(), y[i].clear(), ys[i].clear();
		for(int i = 1; i <= n; ++i){
			scanf("%d", &a[i]), b[i] = i;
			int d = __gcd(a[i], b[i]);	a[i] /= d, b[i] /= d;		
			x[b[i]].push_back(a[i]), y[a[i]].push_back(b[i]); 
			if(a[i] % b[i] == 0) --ans;
		}
		for(int i = 1; i <= n; ++i)
			for(int j = i; j <= n; j += i) ys[j].push_back(i); //预处理因数 
		for(int i = 1; i <= n; ++i){
			for(int j = i; j <= n; j += i)
					for(auto _s : y[j]) ++buc[_s];
			for(auto s : x[i])	
				for(auto _s : ys[s]) ans += buc[_s];
			for(int j = i; j <= n; j += i)
				for(auto _s : y[j]) --buc[_s];
		}
		printf("%lld\n", ans / 2);
	}
	return 0;
}
```

---

