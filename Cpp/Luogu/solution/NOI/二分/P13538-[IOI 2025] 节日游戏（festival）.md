# [IOI 2025] 节日游戏（festival）

## 题目描述

节日上 Nayra 正在玩一个游戏，大奖是一次去红湖（Laguna Colorada）的旅行。游戏中玩家使用代币购买礼券。每购买一张礼券都有可能会获得额外的代币。游戏的目标是获得尽可能多的礼券。

开始时她有 $A$ 枚代币。游戏中一共有 $N$ 张礼券，从 $0$ 到 $N-1$ 编号。Nayra 需要支付 $P[i]$ 枚代币（$0 \leq i < N$）来购买礼券 $i$（购买前她至少要有 $P[i]$ 枚代币）。每张礼券最多只能购买一次。

此外，每张礼券 $i$（$0 \leq i < N$）都指定了**类型**，记为 $T[i]$，其值为 **$1$ 到 $4$ 之间**的整数。当 Nayra 购买礼券 $i$ 后，她剩余的代币数量将乘以 $T[i]$。形式化地，如果她在游戏的某个时刻有 $X$ 枚代币，并购买了礼券 $i$（要求 $X \geq P[i]$），那么购买后她将有 $(X - P[i]) \cdot T[i]$ 枚代币。

你的任务是确定 Nayra 应该购买哪些礼券以及按什么顺序来购买，使她最终拥有的**礼券**数量最大化。如果有多种购买序列能达成该目标，你可以回答其中任意一种。

### 实现细节

你要实现以下函数：

```
std::vector<int> max_coupons(int A, std::vector<int> P, std::vector<int> T)
```

* $A$: Narya 初始拥有的代币数量。
* $P$: 长度为 $N$ 的数组，表示礼券的价格。
* $T$: 长度为 $N$ 的数组，表示礼券的类型。
* 对每个测试用例，该函数恰好被调用一次。

该函数应返回一个数组 $R$，按以下规则表示 Narya 的购买计划：

* 数组 $R$ 的长度应等于她最多可以购买的礼券数量。 
* 数组中的元素为她购买的礼券编号，按购买的顺序排列。也就是说，她首先购买礼券 $R[0]$，然后购买礼券 $R[1]$，以此类推。
* $R$ 中所有的元素互不相同。

如果无法购买任何礼券，则 $R$ 应为空数组。

## 说明/提示

### 例 1

考虑以下调用。

```
max_coupons(13, [4, 500, 8, 14], [1, 3, 3, 4])
```

Narya 起初有 $A = 13$ 枚代币。她可以按以下顺序购买 $3$ 张礼券：

| 购买的礼券 | 礼券价格| 礼券类型 | 购买后的代币数量 |
| :-----------: | :----------: | :---------: | :---------------------------------: |
|      $2$      |     $8$      |     $3$     |       $(13 - 8) \cdot 3 = 15$       |
|      $3$      |     $14$     |     $4$     |       $(15 - 14) \cdot 4 = 4$       |
|      $0$      |     $4$      |     $1$     |        $(4 - 4) \cdot 1 = 0$        |

在这个例子中，Narya 不可能购买多于 $3$ 张的礼券，并且上述购买顺序是她购买这 $3$ 张礼券的唯一方式。因此，该函数应返回 $[2, 3, 0]$。

### 例 2

考虑以下调用。

```
max_coupons(9, [6, 5], [2, 3])
```

在这个例子中，Narya 可以以任意顺序购买两张礼券。因此，该函数可以返回 $[0, 1]$ 或 $[1,0]$。

### 例 3

考虑以下调用。

```
max_coupons(1, [2, 5, 7], [4, 3, 1])
```

在这个例子中，Narya 有 $1$ 枚代币，不足以购买任何一张礼券。因此，该函数应返回 $[\ ]$ （空数组）。

### 约束条件

* $1 \leq N \leq 200\,000$
* $1 \leq A \leq 10^{9}$
* 对每个满足 $0 \leq i < N$ 的 $i$，都有 $1 \leq P[i] \leq 10^{9}$。
* 对每个满足 $0 \leq i < N$ 的 $i$，都有 $1 \leq T[i] \leq 4$。

### 子任务

| 子任务 | 分数 | 额外的约束条件                                              |
| :-----: | :---: | ------------------------------------------------------------------- |
|    1    |  $5$  | 对每个满足 $0 \leq i < N$ 的 $i$，都有 $T[i] = 1$。|
|    2    |  $7$  | $N \leq 3000$；对每个满足 $0 \leq i < N$ 的 $i$，都有 $T[i] \leq 2$。|
|    3    | $12$  | 对每个满足 $0 \leq i < N$ 的 $i$，都有 $T[i] \leq 2$。|
|    4    | $15$  | $N \leq 70$                                                         |
|    5    | $27$  | Nayra 可以购买所有 $N$ 张礼券（以某种顺序）。|
|    6    | $16$  | 对每个满足 $0 \leq i < N$ 的 $i$，都有 $(A - P[i]) \cdot T[i] < A$。|
|    7    | $18$  |        没有额外的约束条件。                             |

## 样例 #1

### 输入

```
4 13
4 1
500 3
8 3
14 4```

### 输出

```
3
2 3 0```

## 样例 #2

### 输入

```
2 9
6 2
5 3```

### 输出

```
2
0 1```

## 样例 #3

### 输入

```
3 1
2 4
5 3
7 1```

### 输出

```
0

```

# 题解

## 作者：sbno333 (赞：10)

特别典的题，vp 花了三小时做完了。

$5$ 分的子任务一点用都没有，我们考虑 $T_i\le 2$。

显然的是，手里硬币越多，买这个物品亏损越少（赚的越多）。

注意到可以分为 $T_i=1$ 和 $T_i=2$ 两类，分别考虑。对于每一类，我们显然按照 $p_i$ 排序，显然如果选了 $p_i$ 大的，不选小的是不优秀的，所以我们选一个前缀。

枚举 $T_i=2$ 选哪些前缀，然后 $T_i=1$ 前缀和二分即可。

这告诉我们似乎 $T_i=1$ 要单独考虑。

我们发现子任务 $5$ 的分数很多。

不用发现，其实当我们看到我们不知道什么顺序选的时候就可以试试排序贪心。

买不起如果硬买，卖完手里的钱肯定是负的，不用特殊考虑。

我们考虑两个物品怎么做。

为了好写，记第一个物品的 $P_1=a$，$T_1=b$，$P_2=c$，$T_2=d$。

设本来有 $x$ 硬币，都购买后为 $((x-a)\times b-c)\times d=bdx-abd-cd$。

反着买就是 $bdx-abd-cd>bdx-bcd-ab$。

得到 $abd+cd<bcd+ab$。

同时除以 $bd$，得到 $a+\frac{c}{b}<c+\frac{a}{d}$。

移项得到 $a-\frac{a}{d}<c-\frac{c}{b}$。

整理得到 $a(1-\frac{1}{d})<c(1-\frac{1}{b})$。

之后显然得到 $\frac{a}{1-\frac{1}{b}}<\frac{c}{1-\frac{1}{d}}$。

为了好看，得到 $\frac{ab}{b-1}<\frac{cd}{d-1}$。

显然有传递性！所以可以排序，注意 $T_i=1$ 单独处理，不过显然都是 $T_i=1$ 就按照 $P_i$ 升序排序，并且先吃 $T_i=1$，再吃 $T_i>1$，相当于让 $T_i>1$ 的变差了，其它不变，所以不好，所以 $T_i=1$ 排在最后。

最后就是在一个序列上求一个最长子序列，使得满足条件。

我们直接把排完序数组的返回就可以获得子任务分数。

如果没啥追求，这时候写部分分，$n\le70$ 其实就是把东西按照 $T_i$ 分类之后每类 $P_i$ 升序排序，然后类分别卖多少件为状态 DP。

这告诉我们这道题要 DP。

一个显然的平方 DP，就是只考虑前 $i$ 件，买了 $j$ 件，此时硬币最多。

平方没分啊。

我们这时候会思考子任务 $6$，不过如果我们继续想贪心会自然想到如果能完成子任务 $6$，那么这道题就做完了。

咋做呢？

我们排序贪心根据定义，有个性质就是先选后面的再选前面的不优秀。

如果我们考虑到我们购买可以分为两段，分别是买了赚硬币和买了亏硬币。

为啥呢？如果亏了之后再赚，还不如先赚再亏，这样二者都能变得优秀。

我们考虑从头开始跑，如果发现买了会赚就直接买，根据定义可知不能先买后面再买前面。

然后如果亏了呢？

如果我先买了后面的会赚，那么我们为了让二者更优秀，可以先买后面的再买这个，相比于先买这个再买后面优秀，不符合定义，所以不存在。

所以我们贪心的从头试图买，能赚（或者不赚不亏）就买，亏就直接跑，跳出循环。剩下的就是子任务 $6$ 了。

瓶颈在于平方 DP。

然而，我们突然发现，这个购买的式子足够特别，根据不考虑 $T_i=1$ 似乎能买的很少。

因为原来买就是亏得，假设亏 $1$。

买了前面的，硬币个数变小，根据式子显然亏得更多，减少多少就多亏多少倍 $T_i-1$。

最坏就是 $T_i=2$，然而即使这样，我们亏得也是一倍一倍增长的，所以我们最多能买 $O(\log A)$ 个产品！

于是我们 DP 的第二维就变成了 $\log$ 量级的。

处理完 $T_i\not=1$，再随便枚举前面选几个，前缀和二分就能处理。

于是我们就做完了。

```cpp
//#include "festival.h"
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct st{
	int p,t,c;
}a[1000009];
int n;
bool cmp(st a1,st a2){
	if(a1.t==a2.t&&a1.t==1){
		return a1.p<a2.p;
	}
	return a1.p*a1.t*(a2.t-1)<a2.p*a2.t*(a1.t-1);
}
vector<int> dp;
vector<bool> zz[200009];
int l,r;vector<signed> ans;
void dfs(int x,int y){
	if(x<l){
		return;
	}
	if(y==0){
		return;
	}
	if(zz[x][y]){
		dfs(x-1,y-1);
		ans.push_back(a[x].c);
	}else{
		dfs(x-1,y);
	}
}
std::vector<signed> max_coupons(signed aa, std::vector<signed> pp, std::vector<signed> tt) {
	int A;
	A=aa;
	vector<int> P,T;
	P.clear(),T.clear();
	for(int i=0;i<pp.size();i++){
		P.push_back(pp[i]);
		T.push_back(tt[i]);
	}
	for(int i=0;i<(int)P.size();i++){
		a[i]={P[i],T[i],i};
	}
	n=P.size();
	sort(a,a+n,cmp);
	r=n;
	while(r>0&&a[r-1].t==1){
		r--;
	}
	l=r;
	
	ans.clear();
	for(int i=0;i<r;i++){
		if((A-a[i].p)*a[i].t>=A){
			A=(A-a[i].p)*a[i].t;ans.push_back(a[i].c);
			if(A>1e16){
				ans.clear();
				for(int i=0;i<n;i++){
					ans.push_back(a[i].c);
                }
				return ans;
			}
		}else{
			l=i;
			break;
		}
	}
	for(int i=r+1;i<n;i++){
		a[i].p+=a[i-1].p;
	}
	dp.clear();
	dp.push_back(A);
	for(int i=0;i<n;i++){
		zz[i].clear();
	}
	for(int i=l;i<r;i++){
		int g;
		g=dp.size();
		for(int j=0;j<g;j++){
			zz[i].push_back(0);
		}
		if((dp[g-1]-a[i].p)*a[i].t>=0){
			dp.push_back((dp[g-1]-a[i].p)*a[i].t);
			zz[i].push_back(1);
		}
		for(int j=g-2;j>=0;j--){
			if((dp[j]-a[i].p)*a[i].t>dp[j+1]){
				dp[j+1]=(dp[j]-a[i].p)*a[i].t;
				zz[i][j+1]=1;
			}
		}
	}
	int ma,ms;
	ma=ms=0;
	for(int i=0;i<dp.size();i++){
		int p;
		p=0;
		int ll,rr;
		ll=r,rr=n-1;
		while(ll<rr){
			int mid;
			mid=ll+rr+1;
			mid>>=1;
			if(dp[i]>=a[mid].p){
				p=mid-r+1;
				ll=mid;
			}else{
				rr=mid-1;
			}
		}
		if(i+p>ma){
			ma=i+p;
			ms=i;
		}
	}
	dfs(r-1,ms);
	A=dp[ms];
	for(int i=n-1;i>r;i--){
		a[i].p-=a[i-1].p;
	}
	for(int i=r;i<n;i++){
		if(A>=a[i].p){
			A-=a[i].p;
			ans.push_back(a[i].c);
		}
	}
  	return ans;
}
```

注意可能会爆 long long，这时候显然可以一锅端，特殊处理一下即可。

不处理会获得 $66$ 分，但是最后两个子任务都能过，别问我咋知道的。

---

## 作者：IvanZhang2009 (赞：3)

这个题是拼尽全力无法战胜之后学习了 lhx 大神的代码，茅塞顿开！为什么人类可以这么智慧？

首先这个 $(P,T)$ 的东西买一次会把 $x$ 的钱变成 $Tx-TP$。这是一个一次函数 $f(x)=kx-b$。相当于选若干个函数迭代，每一步都不能小于 $0$。

这个东西就是经典的 exchange argument。把函数 $ax-b$ 和 $cx-d$ 迭代起来得到：$c(ax-b)-d$ 和 $a(cx-d)-b$，相当于比较 $bc+d$ 和 $ad+b$。也就是比较 $\frac{b}{a-1}$ 和 $\frac{d}{c-1}$。这里需要特殊处理斜率为 $1$：由于作用纯菜，显然是把所有 $T=1$ 的放最后，然后按 $P$ 升序。然后排完序可以通过 sub5。

然后有一个暴力的平方 dp：$f_{i,j}$ 表示前 $i$ 个函数选了 $j$ 个，当前最多剩多少钱。可以获得没多少分。拼所有包可以获得 $66$。

然后观察一下 sub6 的性质，只能得到如下结论：注意到如果一段前缀会让钱变多，那选上这个就不劣。剩下的东西一定会让钱变少。

然后有一个写乱搞的想法就是控制 $j$ 的值域。但是我们竟然可以分析出 $j$ 的值域真的很小！不妨设 $T$ 相同。记价格是 $p_i$ 序列。找到第一个会让钱严格变少的地方开始 dp，然后第一次会让钱变成 $T(x-p_i)<x$。这里至少会让钱数变少 $1$。然后在买第二份的时候，这个 $-1$ 会放到前面的括号里，至少乘上 $T$，然后后面的 $-T\times p_i$ 由于排序的原因一定会变小。于是整个东西都会变小，而且第 $i$ 次买至少会比原来少 $2^i$！！！（因为这个 delta 每次都至少会乘 $T$）

于是显然只考虑 $T>1$ 的情况下，$j$ 的范围只有 $O(\log V)$。最后和 $T=1$ 拼一下就好了。

时间复杂度 $O(n\log V)$。注意 `long long` 问题。

```cpp
#include "festival.h"
#include<bits/stdc++.h>
using namespace std;
#define MOD         998244353
#define ll         long long
#define pii         pair<int,int>
#define all(v)      v.begin(),v.end()
#define pb          push_back
#define REP(i,b,e)  for(int i=(b);i<(int)(e);++i)
#define over(x)     {cout<<(x)<<endl;return;}
#define lowbit(x)   ((x)&(-(x)))
#define cntbit(x)   __builtin_popcount(x)
#define deal(v)     sort(all(v));v.erase(unique(v.begin(),v.end()),v.end())
#define lbound(v,x) lower_bound(all(v),x)-v.begin()
ll inf=1'000'000'000'000'000ll;
struct node{
	ll k,b;int id;
	bool operator <(node a){
		return k*a.b+b<a.k*b+a.b;
	}
	ll calc(ll x){return min(k*x+b,inf);}
};
int n,M=100;
ll f[200005][105];
vector<int>max_coupons(int AA,vector<int>P,vector<int>T){
	ll A=AA;
	vector<node>a,b;n=P.size();
	REP(i,0,n)if(T[i]>1)a.pb({T[i],-1ll*P[i]*T[i],i});
	else b.pb({0,P[i],i});
	sort(all(a));sort(all(b));
	vector<int>res;
	int st=0;
	REP(i,0,a.size())if(a[i].calc(A)>=A){
		res.pb(a[i].id);
		A=a[i].calc(A);
		++st;
	}else break;
	REP(i,st,a.size())a[i-st]=a[i];
	int m=a.size()-st;
	REP(i,0,m+1){
		REP(j,0,M+1)f[i][j]=-1;
	}
	f[0][0]=A;
	REP(i,0,m){
		REP(j,0,M)if(a[i].calc(f[i][j])>=0){
			f[i+1][j+1]=max(f[i+1][j+1],a[i].calc(f[i][j]));
		}
		REP(j,0,M+1)f[i+1][j]=max(f[i+1][j],f[i][j]);
	}
	vector<int>t;
	int x=m,y=M;
	while(f[x][y]<0)--y;
	vector<ll>s;ll sum=0;
	REP(i,0,b.size())s.pb(sum+=b[i].b);
	int mx=-1,mp=0;
	REP(i,0,y+1){
		int t=i+(upper_bound(all(s),f[m][i])-s.begin());
		if(mx<=t)mx=t,mp=i;
	}
	y=mp;
	while(x){
		if(y&&a[x-1].calc(f[x-1][y-1])==f[x][y])t.pb(a[x-1].id),--y;
		--x;
	}
	reverse(all(t));
	for(auto i:t)res.pb(i);
	A=f[m][mp];
	for(auto &[k,b,id]:b)if(A>=b)res.pb(id),A-=b;
	return res;
}
```

---

