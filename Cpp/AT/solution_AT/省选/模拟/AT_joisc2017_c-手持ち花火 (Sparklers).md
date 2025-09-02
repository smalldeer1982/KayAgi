# 手持ち花火 (Sparklers)

## 题目背景


**题目译自 [JOISC 2017](https://www.ioi-jp.org/camp/2017/2017-sp-tasks/index.html) Day1 T3「[手持ち花火](https://www.ioi-jp.org/camp/2017/2017-sp-tasks/2017-sp-d1.pdf)（[Sparklers](https://www.ioi-jp.org/camp/2017/2017-sp-tasks/2017-sp-d1-en.pdf)）」**


![JOISC17D1T3.md.png](http://www.z4a.net/images/2018/02/19/JOISC17D1T3.md.png)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2017/tasks/joisc2017_c



有 $N$ 人站在一条数轴上。他们人手一个烟花，每人手中的烟花都恰好能燃烧 $T$ 秒。每个烟花只能被点燃一次。  
$1$ 号站在原点，$i$ 号 $(1\le i\le N)$ 到 $1$ 号的距离为 $X_i$。保证 $X_1=0,$ $X_1, X_2, \dots, X_N$ **单调**递增（可能有人位置重叠）。  
开始时， $K$ 号的烟花刚开始燃烧,，其他人的烟花均未点燃。他们的点火工具坏了，只能用燃着的烟花将未点燃的烟花点燃。当两人位置重叠且其中一人手中的烟花燃着时，另一人手中的烟花就可以被点燃。忽略点火所需时间。  
求至少需要以多快的速度跑，才能点燃所有人的烟花（此时可能有些人的烟花已经熄灭了）。**速度必须是一个非负整数。**

## 说明/提示


#### 样例解释 1
开始时，$1$ 号向右，$2$ 号向左，$3$ 号向左。  
$50$ 秒后，$2$ 号传火给 $1$ 号 ~~我真的不是黑魂玩家~~。随后，$1$ 号和 $3$ 号继续移动。  
又过了 $25$ 秒，$1$ 号传火给 $3$ 号。

#### 样例解释 2
开始时，$1$ 号向右，$2$ 号向右，$3$ 号向左。  
$3$ 秒后，$2$ 号停止移动。  
又过了 $6.5$ 秒，$3$ 号到达 $2$ 号所在位置，$3$ 号停止移动。  
又过了 $0.5$ 秒，$2$ 号传火给 $3$ 号。  
又过了 $9$ 秒，$3$ 号传火给 $1$ 号。


## 限制与提示

对于 $30\%$ 的数据，$N \le 20$。  
对于 $50\%$ 的数据，$N \le 1000$。  
对于 $100\%$ 的数据，$1\le K, N \le 10^5, 1\le T\le 10^9, 0\le X_i\le 10^9 (1\le i\le N), X_1 = 0, \{X_N\}$ 单调递增。

感谢 Planet6174 提供的翻译


## 样例 #1

### 输入

```
3 2 50
0
200
300```

### 输出

```
2```

## 样例 #2

### 输入

```
3 2 10
0
200
300```

### 输出

```
8```

## 样例 #3

### 输入

```
20 6 1
0
2
13
27
35
46
63
74
80
88
100
101
109
110
119
138
139
154
172
192```

### 输出

```
6```

# 题解

## 作者：Alex_Wei (赞：18)

> [AT2535 手持ち花火 (Sparklers) ](https://www.luogu.com.cn/problem/solution/AT2535)。

今天（2021.11.11）模拟赛的最后一题。

一开始以为若相遇则必然点燃以为是神题，比赛结束后才发现看错了。不难发现题目具有可二分性，故将题目转化为给定一个速度 $v$，判断每个人按速度 $v$ 移动是否能够把光导给任何人：每个人必然向 $k$ 所在方向走，这一点显然。关键结论是若一个人跑到 $k$ 的位置必然跟上，并且等到燃烧完的时候立刻续上（**相遇不用立刻续**），即相当于让火炬燃烧时间增加 $t$ 秒。可通过若两人相遇时继续往相反方向走不优证明。

因此，按照每段区间 $[x_i,x_{i+1}]$ 在 $k$ 左边还是右边分成两个队列，时间代价都是 $\dfrac{x_{i+1}-x_i}{2v}$。问题转化为官方题解中所述的：两个队列 $a,b$，必须按顺序点燃，每个物品点燃要**先付** $a_i$ 或 $b_i$ 代价，**之后**会获得 $t$ 的收益。初始的收益为 $t$，要求任何时候收益非负，问是否能将所有物品点燃。

贪心考虑当前收益更大的决策显然错误，怎么办呢？DP 是不可能 DP 的，毕竟状态数是 $n^2$ 级别的。难道贪心的思想真的不可取吗？Nope. 注意到如果我们一直弹出某个队列直到这一次对时间的收益为正，就可以收手了。相当于将每个序列分成若干组（可能有一段后缀分不进一组），每一组的任一真前缀对时间贡献为负，而整组的贡献非负，不难证明**每一次扩展必然选一整组而非在中途改变方向**。因此，对于两个方向贪心地选**合法的**（即扩展时任意时刻时间非负）贡献最大的组直到所有组都被取完。若无法扩展则当前速度不合法。

对于剩下来的序列考虑将其翻转并时间倒流（因为最终获得的总收益固定），由于原序列剩下来的这一段后缀对于任意其前缀的贡献为负，所以计算贡献取相反数时最终必然能根据上述方法划分成若干个组。故翻转 $a,b$ 并时间倒流即可。时间复杂度 $\mathcal{O}(n\log V)$。

**启示：1. 如果贪心仅关注眼前决策不能保证正确性，不妨把眼光放长远一点。2. 时间倒流在优化一些贪心题时非常有用。**

```cpp
const int N = 1e5 + 5;
ll k, n, T, x[N];
int extend(int st, int sz, db &co, db &nd, db *a, int type) {
	nd = co = 0;
	for(int i = st; i <= sz; i++) {
		if(type == 1) cmax(nd, -co + a[i]), co += T - a[i];
		else cmax(nd, -co + T), co += a[i] - T;
		if(co >= 0) return i;
	} return sz + 1;
}
bool check(db v) {
	static db a[N], b[N];
	int ca = 0, cb = 0, la = 1, lb = 1, toa, tob, las = 0;
	for(int i = k - 1; i; i--) a[++ca] = (x[i + 1] - x[i]) / v / 2;
	for(int i = k + 1; i <= n; i++) b[++cb] = (x[i] - x[i - 1]) / v / 2;
	double nda, ndb, coa, cob, cur = T;
	while(la <= ca || lb <= cb) {
		if((las == 1 || !las) && la <= ca) toa = extend(la, ca, coa, nda, a, 1);
		if((las == 2 || !las) && lb <= cb) tob = extend(lb, cb, cob, ndb, b, 1);
		bool lea = toa <= ca && cur >= nda, leb = tob <= cb && cur >= ndb;
		if(lea && leb) {
			if(coa >= cob) toa = la = toa + 1, cur += coa, las = 1;
			else tob = lb = tob + 1, cur += cob, las = 2;
		} else if(lea) toa = la = toa + 1, cur += coa, las = 1;
		else if(leb) tob = lb = tob + 1, cur += cob, las = 2;
		else if(toa <= ca || tob <= cb) return 0;
		else break;
	}
	reverse(a + 1, a + ca + 1), reverse(b + 1, b + cb + 1);
	ca += 1 - la, cb += 1 - lb, la = lb = 1, las = 0, cur = n * T - (x[n] - x[1]) / v / 2;
	while(la <= ca || lb <= cb) {
		if((las == 1 || !las) && la <= ca) toa = extend(la, ca, coa, nda, a, 2);
		if((las == 2 || !las) && lb <= cb) tob = extend(lb, cb, cob, ndb, b, 2);
		bool lea = toa <= ca && cur >= nda, leb = tob <= cb && cur >= ndb;
		if(lea && leb) {
			if(coa >= cob) toa = la = toa + 1, cur += coa, las = 1;
			else tob = lb = tob + 1, cur += cob, las = 2;
		} else if(lea) toa = la = toa + 1, cur += coa, las = 1;
		else if(leb) tob = lb = tob + 1, cur += cob, las = 2;
		else return 0;
	} return 1;
}

int main(){
	cin >> n >> k >> T;
	for(int i = 1; i <= n; i++) scanf("%lld", &x[i]);
	if(!x[n]) return puts("0"), 0; 
	int l = 0, r = 1e9;
	while(l < r) {
		int m = l + r >> 1;
		check(m) ? r = m : l = m + 1;
	} cout << l << endl;
	return 0;
}
```

---

## 作者：风华正茂 (赞：11)

# 烟花棒题解报告


~~在考场上推了1个半小时，但还是没有推出来。~~


~~我一开始以为那个燃烧的烟花棒只要碰到其他的烟花棒，就会点燃。(于是样例都没过)~~


总结一下题目的意思吧：有n个烟花棒，要让第k个烟花棒不断引然其他的烟花棒，每根烟花棒只能烧**T秒**（烧完就没了），只有两个烟花棒在同一个位置时才能够引燃。在同一个位置的烟花棒**也可以暂时不点燃**。每根烟花棒都有一个**相同的速度v**，可以向左和向右运动，也可以静止。  
求速度至少为多少时，可以点燃所有烟花棒。（此时可能有些烟花棒已经烧完了）


题目让我们求速度的最小值，我们可以二分一个速度v，然后check(v)检验是否成立。


在check里面的部分才是真的精髓~~duliu~~。

首先，每个烟花棒都有一个$x[i]$，表示与1号烟花棒的距离。我们可以创造一个区间$[l,r]$，表示在$[l,r]$中有一个点燃的烟花棒，可以顺带着把其他的烟花棒都引燃。

我们可以发现，左右两端的烟花棒都会向中间点燃的烟花棒靠拢。~~大家都知道的吧~~。

另外，场上只能有一个点燃的烟花棒，因为在同一个位置可以不点燃，而且要让你的总时间尽可能大(因为你的速度是一定的，路程$S=vt$)，所以就可以让其他的烟花棒跟着你跑嘛，等到快熄灭的时候在点燃它们。

综合上面两条结论，我们就可以知道点燃$[l,r]$区间中的最后一个烟花棒，最大的消耗时间为$(r-l)*T$（就是烧掉除$r$外的其他烟花棒）。

但是烟花棒全部点燃的距离就是$x[r]-x[l]$，可以自己画个图理解一下，当你和其他烟花棒在往同一个方向跑动的时候，相对位置是不变的。

所以得出$[l,r]$合法的条件为

$$2*v*T*(r-l) \ge x[r]-x[l]$$

拆括号，移项可得

$$x[l]-2*v*T*l \ge x[r]-2*v*T*r$$

所以我们可令$a[i]=x[i]-2*v*T*i$，那么题目就可以转化为由区间$[k,k]$转移到$[1,n]$其中每一个区间都要合法。

所以一个可以拓展的区间$[l,r]$，对于$i<l$，如果满足条件  

$1.a[i] \ge a[l]$

$2.\forall j \in [i,l]$，有$a[j] \ge a[r]$

那这个区间就可以拓展为$[i,r]$。

通过上面的步骤，我们可以把区间$[k,k]$拓展为一个"极大"的区间$[L,R]$。在这个过程中，若是出现了$a[i]\ge a[l]$，但是$\exists j\in [i,l],a[j]<a[r]$，就可以返回$false$了。

第二步，我们从大区间$[1,n]$向里面缩小。

所以一个可以缩小的区间$[l,r]$，对于$l<i<r$，如果满足条件

$1.a[i] \le a[l]$

$2.\forall j \in [l,i]$，有$a[j] \ge a[r]$

那么这个区间就可以缩小为$[i,r]$。

可见缩小的过程与放大的过程是可逆的，若是可以再次得到区间$[L,R]$，那这个方案是可行的。反之，返回$false$。

**上代码吧。**


```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 100005
using namespace std;
ll n,k,t,x[N],ans,a[N];
bool check(ll v){
	for(int i=1;i<=n;++i)a[i]=(long double)x[i]-(long double)2*v*t*i;
	if(a[1]<a[n])return 0;
	int L=k,R=k;
	for(int i=k-1;i;--i){
		if(a[i]>=a[L])L=i;
	}
	for(int i=k+1;i<=n;++i){
		if(a[i]<=a[R])R=i;
	}
	int l=k,r=k;//从中心向两边拓展
	while(l!=L||r!=R){
		int ok=0,lll=l,rrr=r;//ok判断是否能够拓展到[L,R]
		while(lll>L&&a[lll-1]>=a[r]){
			if(a[--lll]>=a[l])break;
		}
		if(lll<l&&a[lll]>=a[l])ok=1,l=lll;//判断上一句是否拓展过
		while(rrr<R&&a[rrr+1]<=a[l]){
			if(a[++rrr]<=a[r])break;
		}
		if(rrr>r&&a[rrr]<=a[r])ok=1,r=rrr;
		if(!ok)return 0;//无法拓展到[L,R]，无解
	}
	l=1,r=n;//再从两端向中间缩小区间
	while(l!=L||r!=R){
		int ok=0,lll=l,rrr=r;
		while(lll<L&&a[lll+1]>=a[r]){
			if(a[++lll]>=a[l])break;
		}
		if(lll>l&&a[lll]>=a[l])ok=1,l=lll;
		while(rrr>R&&a[l]>=a[rrr-1]){
			if(a[--rrr]<=a[r])break;
		}
		if(rrr<r&&a[rrr]<=a[r])ok=1,r=rrr;
		if(!ok)return 0;
	}
	return 1;
}
int main(){
	cin>>n>>k>>t;
	for(int i=1;i<=n;++i)cin>>x[i];
	ll l=0,r=0x3f3f3f3f;//注意二分边界必须是0，因为当所有烟花棒重叠时是不需要速度的，我就错了几遍
	while(l<=r){
		ll mid=(l+r)>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<ans<<endl;
	return 0;
}

```


---

## 作者：wimg6_ (赞：10)

观察到，答案显然具有可二分性。为什么？因为速度越快，其点燃其他角色的花火所需要的时间就越小，相遇的可能也就越大。

观察到，区间 $[l,r]$ 合法当且仅当 $2\times v\times T\times (r-l)\geq x_r-x_l$。如何理解这个式子？假定最外面的两个人 $l$ 和 $r$ 做相遇运动，每个人速度为 $v$，然后拿着花火的人每到达一个人的位置，就让这个人和拿着花火的人一起跑，等到拿着花火的人的花火燃尽时再点燃陪跑那个人的花火，也就是花火最大可燃着的时间为 $T\times (r-l)$，而区间长度为 $x_r-x_l$，所以有上面那个式子。

拆开化简一下，令 $p_i=2\times v\times T\times i-x_i$，题目转化为：要从区间 $[S,S]$，每次要么左端点减一要么右端点加一，中途要求 $p_l<=p_r$，问能否拓展到 $[1,n]$。

不觉得熟悉么？这不就是[双序列拓展问题](https://www.luogu.com.cn/problem/P9870)么？具体地，我们令双序列拓展问题中的 $X_i=p_{S-i+1},Y_i=p_{i-S+1}$ 即可。代码太丑了就不放了。

---

## 作者：RedLycoris (赞：7)

![](https://cdn.luogu.com.cn/upload/image_hosting/lghiod3w.png)

单调性可以被感性发现。

但是我们要注意一点，就是“在碰到一个人之后立刻点燃烟花棒”是不优的。

显然，我们可以让上一个人一直跟着这个人跑，直到烟花棒耗完。同样，无论在耗完的路上遇到了多少人，他们都可以一起跑。可以发现，我们这么做，即等到它耗尽再传递，能够延长火种运输的时间。~~因为你不用考虑这些人是否会累死~~

然后我们贪心的考虑，肯定是 $1\dots k-1$ 号人向右跑，$k+1 \dots n$ 号人向左跑。然后第 $k$ 个人每传递到一个人后就选择下一个传递到左边还是右边。

如果一些人一直同向跑的话，那么他们之间的距离不会变。所以说，在这个过程中，只有 $k$ 号和他的目标之间的距离在变。（我们这种模式就保证了在一个时刻只会有一个烟花棒是点燃的，而为了方便起见我们让 $k$ 号人一直跟着这个烟花棒跑，反正也累不死）

所以，这道题就可以转化成有两列人，每次一个一个撞掉开头的一个，会消耗一定的时间，如果撞掉了就可以获得 $T$ 的时间，问你能否撞完。（每撞上一个人会让这个烟花棒续命 $T$ 时间）

考虑把前面的人和后面的人都分成一些连续的小段，满足每个段的所有前缀都满足 $cost>T \times c$ 而到了结束则 $cost \le T\times c$。（$c$ 代表这一段前缀中人的个数，$cost$ 代表总消耗时间）

如果这两列能够正好被分为一些小段，那么我们执行以下操作：

每次选择一个段然后撞完，如果不能撞则一定不行了。

证明：

如果你没有把一个段撞完就去撞另外一个段，那么你肯定不如不撞这个段直接去撞另外一个段来的优，毕竟我们这个“段”的定义是所有前缀的前缀和都是要亏本的。

那么撞段的顺序会不会影响呢？也是不会的，因为这个段同时还满足了总的是要赚时间的，所以撞完就一定会有盈利。假设你面对的是两个段，你都能撞完，那么你先撞完第一个是肯定能撞完第二个的，先撞第二个同理。

综上，这个贪心策略是可行的。

如果不能被正好分完，那么就可以发现这个后缀满足 $cost > T\times c$。由于最后剩下的时间是可以求出的，我们就可以把后缀的 $T$ 和 $C$ 翻转过来，然后用上述方法再求一遍即可。

感性证明的时候感觉会可能出现还需要再翻转再递归求下去的情况，但其实不会。因为如果出现了，那么我们可以吧这个后缀提出来，发现是满足 $cost \le T \times c$ 的，就可以组成一个段，分到第一次求解的末尾。

Talk is cheap, show me the code.

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int ll inf=1e9;
const int mxn=1e5+5;
ll n,k,t;
ll a[mxn],b[mxn];
inline bool check(int x){
	for(int i=1;i<=n;++i)b[i]=a[i]-2ll*t*x*i; //预处理然后就可以直接比大小
	if(b[1]<b[n])return 0;
	int lx=k,rx=k;
	for(int i=k-1;i;--i)if(b[i]>=b[lx])lx=i;
	for(int i=k+1;i<=n;++i)if(b[i]<=b[rx])rx=i;
	int l=k,r=k;
	for(;lx<l or r<rx;){//正着
		bool ok=0,f=0;
		int tl=l,tr=r;
		for(;tl>lx and b[tl-1]>=b[r];)if(b[--tl]>=b[l]){
			f=1;
			break;
		}
		if(f)ok=1,l=tl;
		f=0;
		for(;tr<rx and b[tr+1]<=b[l];)if(b[++tr]<=b[r]){
			f=1;
			break;
		}
		if(f)ok=1,r=tr;
		if(!ok)return 0;
	}
	l=1,r=n;
	for(;l<lx or rx<r;){//处理后缀
		bool ok=0,f=0;
		int tl=l,tr=r;
		for(;tl<lx and b[tl+1]>=b[r];)if(b[++tl]>=b[l]){
			f=1;
			break;
		}
		if(f)ok=1,l=tl;
		f=0;
		for(;tr>rx and b[tr-1]<=b[l];)if(b[--tr]<=b[r]){
			f=1;
			break;
		}
		if(f)ok=1,r=tr;
		if(!ok)return 0;
	}
	return 1;
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>k>>t;
	for(int i=1;i<=n;++i)cin>>a[i];
	int l=0,r=inf/t+1,md;
	for(;l<r-1;){
		md=l+r>>1;
		if(check(md))r=md;
		else l=md;
	}
	if(check(0))r=0;
	cout<<r<<endl;
}
```

---

## 作者：AzusaCat (赞：6)

[题意](https://loj.ac/problem/2392)

这题真的强orz

不难发现这个问题答案具有单调性，可以二分最小的速度 $v$，所以我们只需要判断当速度为 $v$ 时是否可以点燃所有的烟花棒。

首先不难发现，所有没点燃的人一定可以一直以最高速度向点燃的人跑，而且只会在碰到一个人时掉头。然后我们有一个重要结论：如果一个烟花棒点燃的人和没有点燃的人相遇，那么之后他们一定可以在一起跑，直到点燃的人的烟花棒熄灭，这时续给下一个人。

对于证明，我们考虑相遇后两人跑的方向是否相同：如果相同显然等一个人的灭的那一刻点燃不会劣；如果不同，设正在燃烧的烟花棒时间还剩 $c$ 秒，位置为 $x$，我们强制认为不同的话正在燃烧的那个人向右走。那么如果点燃然后分开跑，能扩展到的区间为 $[x-Tv,x+cv]$；如果我们让没有点燃的人先跟着点燃的人跑 $c$，然后再向回跑，这样能扩展的区间为 $[x+(T-c)v,x+cv]$。看似变少了，但是我们注意到第二种情况没被点燃的人跑到区间左端点的时间比第一种情况晚了 $c$ 秒，而在这段时间内所有比左端点还靠左的人可以向右跑 $cv$ 的距离，根据相对运动的思想，他们之间的相对距离没有变化。

这样的话，当两个人相遇的时候，我们可以认为是给烟花棒的延长时间续了 $T$ 秒。

同时，我们注意到，如果两个人走的方向相同，那么他们的相对位置不变，即如果某一刻掉头去点燃另外一边的人，所用时是不会因为你之前的选择而变化。这样的话，我们定义两个数列 $a_i=\frac{X_{i+1}-X_i}{2v},i<k$，$b_i=\frac{X_i-X_{i-1}}{2v},i>k$，即一开始从 $X_{i+1/i-1}$ 到 $X_i$ 的用时。则问题被转化为：你需要删掉这两个数列的所有数，且数列内部要按顺序删，每删掉一个数将先减少 $a_i/b_i$ 的剩余时间然后增加 $T$ 秒剩余时间，问是否存在一个方案使得任何时刻剩余时间都非负。

我们尝试把数列缩成若干段，使得每一段都有总获得时间大于等于总消耗时间，且对于该段不存在同样满足该性质的前缀（认为 $a_{k-1}$ 是头，$a_1$ 是尾）。这样每一段都可以用一个二元组 $(c,v)$ 表示消完这一组至少需要 $c$ 秒，消完后可以获得 $v$ 秒时间，显然我们一次只会消去一整组而不是某个前缀。

如果我们能把两个序列都分为这样的两个组，我们可以每次贪心选 $c$ 较小的然后看能不能全部选完，如果可以删完那么这个 $v$ 就合法，反之不合法。

如果某个序列不能，说明这个序列存在某个后缀，使得对任意该后缀的前缀，总消耗时间都大于总获得时间。我们发现实际上我们是知道最后的剩余时间的，所以我们考虑时间倒流，这样的话删掉一个数等价于先消耗 $T$ 时间再获得 $a_i/b_i$ 的时间，依旧是任何时刻剩余时间非负。由该后缀的性质可知反过来做不会再遇到一个这样的后缀了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,t,x[200005];
vector<double>a,b;
vector<pair<double,double> >c,d;
double const eps=1e-12;
bool check(int v)
{
    a.clear(),b.clear();
    for(int i=k-1;i>=1;i--)a.push_back(0.5*(x[i+1]-x[i])/v);
    for(int i=k+1;i<=n;i++)b.push_back(0.5*(x[i]-x[i-1])/v);
    double now=0,minn=1e18;
    int tmp1=-1,tmp2=-1;
    c.clear(),d.clear();
    for(int i=0;i<a.size();i++)
    {
        now-=a[i];
        minn=min(minn,now);
        now+=t;
        if(now>-eps)c.push_back(make_pair(-minn,now)),minn=1e18,now=0,tmp1=i;
    }
    now=0,minn=1e18;
    for(int i=0;i<b.size();i++)
    {
        now-=b[i];
        minn=min(minn,now);
        now+=t;
        if(now>-eps)d.push_back(make_pair(-minn,now)),minn=1e18,now=0,tmp2=i;
    }
    int p=0,q=0;
    now=t;
    while(p<c.size()||q<d.size())
    {
        if(p<c.size()&&now>=c[p].first)now+=c[p].second,p++;
        else if(q<d.size()&&now>=d[q].first)now+=d[q].second,q++;
        else return 0;
    }
    c.clear(),d.clear();
    now=0,minn=1e18;
    for(int i=a.size()-1;i>tmp1;i--)
    {
        now-=t;
        minn=min(minn,now);
        now+=a[i];
        if(now>-eps)c.push_back(make_pair(-minn,now)),minn=1e18,now=0;
    }
    now=0,minn=1e18;
    for(int i=b.size()-1;i>tmp2;i--)
    {
        now-=t;
        minn=min(minn,now);
        now+=b[i];
        if(now>-eps)d.push_back(make_pair(-minn,now)),minn=1e18,now=0;
    }
    p=0,q=0;
    now=t;
    for(int i=0;i<a.size();i++)now-=a[i],now+=t;
    for(int i=0;i<b.size();i++)now-=b[i],now+=t;
    if(now<0)return 0;
    while(p<c.size()||q<d.size())
    {
        if(p<c.size()&&now>=c[p].first)now+=c[p].second,p++;
        else if(q<d.size()&&now>=d[q].first)now+=d[q].second,q++;
        else return 0;
    }
    return 1;
}
int main()
{
    bool flag=0;
    scanf("%d%d%d",&n,&k,&t);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x[i]);
        if(x[i]!=x[i-1])flag=1;
    }
    if(!flag){puts("0");return 0;}
    int l=1,r=1e9;
    while(l<r)
    {
        int mid=(l+r)>>1;
        if(check(mid))r=mid;
        else l=mid+1;
    }
    printf("%d",l);
    return 0;
}
```



---

## 作者：liuyifan (赞：6)

## 二分答案+贪心
题目有中文了，这里就不说题意了

题目可以转化为能否覆盖整个区间。如果[i,j]都可以点燃，则满足xj+cal(j−i)≥xi−cal(j−i)。令a[i]=xi−2cal∗i，则a[i]≥a[j]。

然后求可不可以从[k,k]走到[1,n]，贪心即可

code:
```cpp
#include<bits/stdc++.h>//万能头文件
#define reg register//register卡常
#define ll long long//不开long long见祖宗
#define inf 0x3f3f3f3f
using namespace std;
ll n,k,t,x[100005],l,r=inf,mid,ans=inf,a[100005],bj;
inline bool cal(reg ll v)//二分答案+判断可行性
{
    int ql=k,qr=k,l=1,r=n,lll,rr;
    for(reg int i=1;i<=n;i++)a[i]=x[i]-2ll*t*v*i;
    if(a[1]<a[n])return 0;
    for(reg int i=k-1;i>=1;i--)if(a[i]>=a[ql])ql=i;
    for(reg int i=k+1;i<=n;i++)if(a[i]<=a[qr])qr=i;
    l=r=k;
    while(l!=ql||r!=qr)
    {
        bj=0;
        int lll=l,rr=r;
        while(lll>ql&&a[lll-1]>=a[r])if(a[--lll]>=a[l])break;
        if(lll<l&&a[lll]>=a[l])bj=1,l=lll;
        while(rr<qr&&a[rr+1]<=a[l])if(a[++rr]<=a[r])break;
        if(rr>r&&a[rr]<=a[r])bj=1,r=rr;
        if(!bj)return 0;//无解情况
    }//二分答案处理
    l=1,r=n;
    while(l!=ql||r!=qr)
    {
        bj=0,lll=l,rr=r;
        while(lll<ql&&a[lll+1]>=a[r])
        if(a[++lll]>=a[l])break;
        if(lll>l&&a[lll]>=a[l])bj=1,l=lll;
        while(rr>qr&&a[rr-1]<=a[l])
        if(a[--rr]<=a[r])break;
        if(rr<r&&a[rr]<=a[r])bj=1,r=rr;
        if(!bj)return 0;
    }//贪心查找
    return 1;
}
int main()
{
    scanf("%lld%lld%lld",&n,&k,&t);
    for(reg int i=1;i<=n;i++)scanf("%lld",&x[i]);
    while(l<=r)
    {
        mid=(l+r)>>1;
        cal(mid)?ans=mid,r=mid-1:l=mid+1;//三目运算符,如果cal(mid)为1则执行前一条语句，否则执行另一条
        //逗号运算符可以将多条语句连成一条,返回值取最后一条的
    }//二分的方案
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：do_it_tomorrow (赞：5)

[更差的阅读体验](https://www.doittomorrow.xyz/post/shou-chi-tihua-huo/)

看 deepl 翻译的 pdf 笑了一晚上，[Link](https://www.doittomorrow.xyz/media/deepl.pdf)。

## 单调性

首先发现答案具有单调性，可以二分求解。

十分容易证明，如果现在的速度是 $x$，那么对于答案大于 $x$ 的情况他们完全可以沿用速度为 $x$ 的方案跑完。

## 不必要的情况

接下来跟着官方题解手玩输入样例，发现了一下一些情况：

1. 对于一样的场面，似乎只改变 $T$ 也会影响答案的方案。
2. 有些人可能会停下来。
2. 有很多人的烟花在被同时点燃。

但是其实这些情况都是没有必要的，似乎有多人做题的时候被误导了（~~但是学校模拟赛没有给样例解释导致题目没有看懂~~）。

### 情况 $1$

显然会有一种通用的方式，如果这个方式可以满足较小的 $T$ 那么也一定可以满足较大的 $T$。

具体的，让本会熄灭的人拿着烟花在站着就行了。

### 情况 $2$

显然，停止是不必要的。

具体的，如果我们要停止 $t$ 秒那么我们可以向相反方向前进 $\dfrac{t}{2}$ 就行了。

因为我们考虑的是相对位置，所以整体一起向一个方向移动移动可是一种思路。

### 情况 $3$

只考虑 $2$ 个的情况，其他的情况容易拓展。

考虑分情况讨论：

- 如果 $2$ 个人相遇后向同一方向运动，那么显然我们可以让其中 $1$ 个人点火之后一起跑，等第 $1$ 个人熄灭之后再传递给第 $2$ 个人。这样有火的时间就从 $T$ 变成了 $2T$。
- 如果 $2$ 个人相遇之后向相反方向移动，那么我们考虑延迟第 $2$ 个人的点时间。为了不影响相对位置，我们可以让第 $1$ 个人先点火，然后让与第 $2$ 个人有关的人一起与第 $1$ 个人运动，保持相对位置不要变。这样当第 $1$ 个人的火将要熄灭的时候第 $2$ 个人再点燃。

## 规律

1. 因为情况 $3$，场上最多只有 $1$ 个人的火把被点燃。
1. 没点燃的人不会主动远离已经点燃的人，也就是会主动靠近被点燃的人。
2. 拿着烟花的人应该主动靠近下一个需要被点燃的人，这十分显然。

也就是说如果确定了点燃的顺序，那么点燃的最有方案就是确定的。

所以容易想到 $O(n\times n!\times \log V)$ 的做法，可惜题目没有给分。

## 可行性优化

如果有 $3$ 个人 $x,y,z$ 顺序排列，那么按照 $x\to z\to y$ 的顺序点火肯定没有按照 $x\to y\to z$ 或者 $z\to y\to x$ 的顺序点火优秀。

因此对于任意时刻，被点燃的火把一定是一个包含 $k$ 的连续区间。

那么我们就只需要讨论两侧的情况就行了，时间复杂度为 $O(n\times 2^n\times \log V)$，这样可以获得 $30$ 分。

## 最优性优化

因为我们发现点燃的一定是一个包含 $k$ 的连续的区间，那么容易想到将最初的 $[k,k]$ 逐步向外拓展到 $[1,n]$。

假设区间 $[l-1,r]$ 是合法的，那么需要满足一下不等式才能扩展到 $[l,r]$ 。

容易理解一个区间 $[l,r]$ 内的所有人汇聚到 $k$ 的时间为 $\dfrac{x_l-x_r}{2\times v}$。如果出现了 $l$ 或者 $r$ 距离 $k$ 比较近，提前到达了但是另一侧的点还没有到达，那么所有在 $k$ 点的人可以一起向另一侧运动。

那么如果区间 $[l,r]$ 满足条件可以拓展到 $[l,r+1]$  的要求就是：

$$x_{r+1}-x_l\le (r-l+1)\times T$$

其意义就是区间 $[l,r]$ 可以一直燃烧直到 $r+1$ 来到 $k$。

同理，如果区间 $[l,r]$ 满足条件可以拓展到 $[l-1,r]$ 的要求就是：

$$x_{r}-x_{l-1}\le (r-l+1)\times T$$

考虑维护 $f_{i,j}$ 表示区间 $[i,j]$ 能否被表示，直接 $O(1)$ 转移即可，时间复杂度为 $O(n^2\times \log V)$，可以获得 $50$ 分。

## 不知道叫什么的优化

按照套路，将上面的不等式移项，把 $l$ 和 $r$ 分开，得到：

$$x_{r+1}-2v\times T\times (r+1)\le x_{l}+2v\times T\times l$$

那么如果令 $x_i\gets x_i-2v\times T\times i$，就得到如果可以过渡到 $[l,r+1]$ 那么需要满足：

$$x_l\ge x_{r+1}$$

同理，如果要过度到 $[l-1,r]$ 需要满足：

$$x_{l-1}\ge x_r$$


那么我们可以转化题意：

初始时 $l=r=k$，始终需要满足 $x_l\le x_r$，每一次操作将 $l\gets l-1$ 或者 $r\gets r+1$，问是是否村子啊一个操作到最后使得 $l=1,r=n$。

如果存在一个 $l'$ 满足 $l'\le l$ 且 $\forall i\in [l',l]\cap\mathbb{N}\mid x_i\ge x_r$，那么显然 $[l',r]$ 也是合法的，对于 $[l,r']$ 也是同理。

令 $L$ 取小于 $k$ 的最大的 $x$ 的位置，$R$ 取大于 $k$ 的最小的 $x$ 的位置，那么我们的贪心在最极限的情况下可以到达 $[L,R]$。

考虑从 $[1,n]$ 向回推，如果可以推到 $[L,R]$ 那么就是合法的，反之如果推不到那么就是不合法的。

时间复杂度为 $O(n\log V)$，可以获得 $100$ 分。

## Code

过于的丑陋。

---

## 作者：xiezheyuan (赞：5)

前置知识：P9870 [NOIP2023] 双序列拓展，不妨先来做一遍，做过这道题的请跳过这一部分：

---

题面和分析相对于原题面有不影响大致思路的小改动。

> **P9870 [NOIP2023] 双序列拓展**
>
> 称某个序列 $B = \{b_1,b_2,\cdots,b_n\}$ 是另一个序列 $A = \{a_1,a_2,\cdots,a_m\}$ 的**拓展**当且仅当存在**正整数**序列 $L = \{l_1,l_2,\cdots,l_m\}$，将 $a_i$ 替换为 $l_i$ 个 $a_i$ 后得到序列 $B$。
>
> 小 R 给了你两个序列 $X$ 和 $Y$，他希望你找到 $X$ 的一个长度为 $l_0 = 10^{100}$ 的拓展 $F = \{f_i\}$ 以及 $Y$ 的一个长度为 $l_0$ 的拓展 $G = \{g_i\}$，使得任意 $1 \le i , j \le l_0$ 都有 $(f_i - g_i)(f_j - g_j) > 0$。由于序列太长，你只需要告诉小 R 是否存在这样的两个序列即可。
>
> $T$ 组数据。令 $X$ 长度为 $n$，$Y$ 长度为 $m$。$1\leq T\leq 61,1\leq n,m\leq 5\times 10^5$

首先 $(f_i - g_i)(f_j - g_j) > 0$ 等价于 $f_i<g_i$ 或 $f_i>g_i$，两者类似，下面默认前者。

先考虑一个可以获得 $35$ 分的 $O(Tnm)$ 做法。考虑到所谓扩展的过程，其实可以看成两个序列上各有一个指针在移动。

我们称两个指针分别在 $X_i,Y_j$，则移动到 $(X_i,Y_{j+1})$ 表示扩展中分别写下了 $X_i,Y_{j+1}$，$(X_{i+1},Y_{j})$ 和 $(X_{i+1},Y_{j+1})$ 是类似的。

于是我们可以设计一个 dp，设 $f(i,j)$ 表示两个指针分别位于 $X_i,Y_j$ 是否可行，不难列出转移方程：

$$
f(i,j)=\begin{cases}
f(i-1,j)\lor f(i,j-1)\lor f(i-1,j-1)& X_i<Y_j\\
\mathrm{false}& \text{otherwise}
\end{cases}
$$

边界 $f(1,1)=\mathrm{true}$。答案就是 $f(n,m)$。

然后考虑一个 $35$ 分的特殊性质：

> 特殊性质：对于每组数据，保证 $x_1 < y_1$，且 $x_n$ 是序列 $X$ 唯一的一个最小值，$y_m$ 是序列 $Y$ 唯一的一个最大值。

发现这个特殊性质实在是太奇怪了，不过不慌，观察上面的这个 dp 式子，是不是很像格路计数？那么我们不妨搬到平面上去观察。

则上面的 dp 就可以看成：如果 $(i,j)$ 可以经过的充要条件是 $X_i<Y_j$，那么相当于我们从 $(1,1)$ 出发，假如我们位于 $(i,j)$，则我们可以走到 $(i+1,j),(i,j+1),(i+1,j+1)$ 中的任意一个，问能否走到 $(n,m)$。下面称 $n$ 决定了行，$m$ 决定了列。

这个时候将特殊性质带上来。先考虑几种小情况，如果 $\min X\geq \min Y$，说明 $\min Y$ 那一列全部不可经过的，显然是无解的。

同理，$\max Y\leq \max X$ 的时候，$\max X$ 一行也是不可经过的，显然也是无解的。

然后考虑剩余的情况，则我们必然有 $X_n\leq Y_i,X_i\leq Y_m$。原因也很简单，就是 $X_n=\min X, Y_m=\max Y$ 而已。

也就是说，对于所有的形如 $(n,i)$ 或 $(i,m)$ 的格子，都是可以经过的，换句话说，只要存在一条路径可以到达这个“边框”，那么一定可以到达终点 $(n,m)$。

我们继续。到达边框的充要条件，就是到达第 $n-1$ 行或第 $m-1$ 列。

而由于之前的分析，我们到达去掉边框的那个小矩形的 $\min X$ 行或者 $m-1$ 列，或者到达 $\max Y$ 列或者 $n-1$ 行，都是可行的。

然后我们发现这就是原问题的两个子问题，直接分治去做就好了。

时间复杂度的话，写出代码就可以看出来是 $O(T(n+m))$ 的。

最后我们来考虑满分做法，特殊性质提醒我们需要找到 $\min X$ 和 $\max Y$ 的位置。

设 $\min X$ 行与 $\max Y$ 的交点为 $(a,b)$，则就是看 $(1,1)$ 是否可以走到 $(a,b)$，然后 $(a,b)$ 是否可以走到 $(n,m)$。

这就是我们刚刚在特殊性质中解决的问题做两次的结果。只是实现略有差异。

时间复杂度 $O(T(n+m))$ 可以通过本题。

---

回到本题。

第一个观察应该是假如我们设某一个合法的速度上界为 $v$，则对于任意的 $v'>v$，$v'$ 也是一个合法的速度上界。也就是说答案是单调的。

于是我们二分 $v$，转换为判定性问题。

> 引理：对于任意的 $1\leq L\lt R\leq n$，若 $L,R$ 两人均被点燃过，则存在一种最优策略，使得对于任意的 $i\in[L+1,R-1]$，$i$ 号人的烟花也被点燃过。

读者不难自证。PS：这好像是一个模型，也就是说在类似传递点火之类的问题时，一定是相邻传递更优。

通过这个引理，可以考虑我们假设当前的“被点燃过的人的区间”为 $[L,R]$，则可以转移到 $[L-1,R],[L,R+1],[L-1,R+1]$。也就是有一个人与 $L-1$ 相遇完成了点火，或与 $R+1$ 相遇完成了点火，或有两人分别于 $L-1,R+1$ 相遇完成了点火。

但是不难猜测并不是所有区间都可以转移到，要不然就会得到无论速度上界为多少都是有解的这一荒谬结论。

> 引理：如果区间 $[L,R]$ 可以由某一个区间转移得到，充分条件是：
>
> * 上一个区间是可以从 $[k,k]$ 直接或间接转移得到。
> * $T(R-L)\geq \frac{x_R-x_L}{2v}$。

第一个条件很容易理解，下面考虑第二个条件。

我们发现，由于每个人都是可以运动的，那么它们一定互相向 $k$ 靠拢肯定最优。我们倒着考虑 $L,R$ 点到火的过程，考虑当 $L$ 或 $R$ 遇到帮它点火的人后，陪着这个人继续向前（后？）跑，最后一定可以跑到 $k$，也就是相遇，中间可以合理分配速度。而 $T(r-l)$ 就是可以浪费在跑步过程中的最大时长。

对这个不等式进行合理的变形：

$$
\begin{aligned}
&T(R-L)\geq \frac{x_R-x_L}{2v} \\
&2vT(R-L)\geq x_R - x_L \\
&2vTR-x_R\geq  2vTL-x_L
\end{aligned}
$$

好，到此为止，我们回顾一下之前的思考过程，看看我们将原题面转化成了什么：有一个序列 $\{2vTR-x_R\}$ 和另一个序列 $\{2vTL-x_L\}$，我们需要构造两个序列，分别为两个序列中每一个元素重复正整数次得到，并且要求每位都必须满足 $\geq$ 的一个限制。

这不就是之前提到的双序列拓展一题吗？沿用那道题的做法，稍作修改即可。

时间复杂度 $O(n\log n)$。可以通过本题。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 5;
int n, k, x[N], t, a[N], b[N], n_, m_;
struct node{ int mint, maxt; } prea[N], sufa[N], preb[N], sufb[N];

node merge(node x, int *arr, int pos){
    x.mint = arr[x.mint] < arr[pos] ? x.mint : pos;
    x.maxt = arr[x.maxt] > arr[pos] ? x.maxt : pos;
    return x;
}

bool solve1(int x, int y){
    if(x == 1 || y == 1) return true;
    node px = prea[x - 1], py = preb[y - 1];
    if(a[px.mint] <= b[py.mint]) return solve1(px.mint, y);
    if(a[px.maxt] <= b[py.maxt]) return solve1(x, py.maxt);
    return false;
}

bool solve2(int x, int y){
    if(x == n_ || y == m_) return true;
    node px = sufa[x + 1], py = sufb[y + 1];
    if(a[px.mint] <= b[py.mint]) return solve2(px.mint, y);
    if(a[px.maxt] <= b[py.maxt]) return solve2(x, py.maxt);
    return false;
}

bool check(int v){
    n_ = m_ = 0;
    for(int i=k;i;i--) a[++n_] = 2 * v * t * i - x[i];
    for(int i=k;i<=n;i++) b[++m_] = 2 * v * t * i - x[i];
    if(a[1] > b[1]) return false;
    prea[1] = preb[1] = {1, 1}, sufa[n_] = {n_, n_}, sufb[m_] = {m_, m_};
    for(int i=2;i<=n_;i++) prea[i] = merge(prea[i - 1], a, i);
    for(int i=2;i<=m_;i++) preb[i] = merge(preb[i - 1], b, i);
    for(int i=n_-1;i;i--) sufa[i] = merge(sufa[i + 1], a, i);
    for(int i=m_-1;i;i--) sufb[i] = merge(sufb[i + 1], b, i);
    node px = prea[n_], py = preb[m_];
    if(a[px.mint] > b[py.mint] || b[py.maxt] < a[px.maxt]) return false;
    return solve1(px.mint, py.maxt) && solve2(px.mint, py.maxt);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> k >> t;
    for(int i=1;i<=n;i++) cin >> x[i];
    int L = 0, R = 2e9;
    while(L < R){
        int mid = (L + R) >> 1;
        if(check(mid)) R = mid;
        else L = mid + 1;
    }
    cout << L << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：DaiRuiChen007 (赞：5)

# JOISC2017C 题解



## 题目大意

> 数轴上有 $n$ 个人，其位置分别为 $x_1,x_2,\dots,x_n$，开始时，$k$ 号手中的烟花处于刚被点亮状态，若一个烟花不被点亮的人 $i$ 和一个烟花被点亮的的人到 $j$ 达同一位置后，$i$ 手中的烟花会被点亮
>
> 每个点亮的烟花可以持续燃烧 $T$ 秒，每个人可以以任意非负整数的速度移动，求所有人的最大速度至少是多少才能使每个人至少被点亮一次

## 思路分析

显然本题答案具有可二分性，二分一个最大速度 $v$ 之后可以让所有人都以 $v$ 的速度移动。

考虑刻画点燃烟花棒的过程，显然某个时刻场上有两个点燃的烟花一定不优于把后点燃的一个留住，跟着先点燃的那个人跑，直到先点燃的那个人燃烧结束时再传火，可以证明这样一定更优。

一个显然的观察是：对于任意时刻，点燃过烟花的人一定是一个包含 $k$ 的区间 $[l,r]$，并且每个人都会向 $[l,r]$ 靠近然后在区间终点依次传火，因此我们得到判定条件：**区间 $\mathbf{[l,r]}$ 中的所有人都能被点燃烟花的充分非必要 $\mathbf{(r-l)T\ge\dfrac{x_r-x_l}{2v}}$**，事实上，这个条件描述的是保证 $[l,r]$ 区间中最后一个被点燃烟花的人合法。

令 $e_i=x_i-2\times v\times T\times i$，根据归纳法，那么区间 $[l,r]$ 合法当且仅当 $e_l\ge e_r$ 且区间 $(l,r],[l,r)$ 中有一个合法。

因此我们需要从 $[k,k]$ 区间不断拓展，直到拓展到 $[1,n]$，考虑某个时刻我们让 $[l,r]\gets [l-1,r]$，若 $e_{l-1}<e_l$，那么我们继续拓展 $l$ 一定不劣，因为此时拓展 $r\to r'$ 的由于 $e_l>e_{l-1}\ge e_{r'}$，可以在拓展 $l$ 之前先做。

因此每次我们拓展 $[l,r]$ 到 $[l',r]$ 都会使得 $e_{l'}\ge e_l$，同理， 每次拓展 $[l,r]$ 到 $[l,r']$ 都会使得 $e_{r'}\le e_r$，不断根据这个贪心拓展区间 $[l,r]$，当然最终可能拓展到一个区间 $[l^*,r^*]$ 使得任何 $l'<l^*$ 都有 $e_{l'}<e_{l^*}$ 且任何 $r'>r*$ 都有 $e_{r'}>e_{r^*}$，此时无论如何都无法继续拓展。

考虑此时进行时光倒流，我们用类似的方法从区间 $[1,n]$ 开始逆向收缩，容易证明逆向收缩的过程根据刚才的贪心一定可以收缩到 $[l^*,r^*]$。

因此判断的时候后从 $[k,k]$ 和 $[1,n]$ 两端分别贪心地拓展和收缩到 $[l^*,r^*]$ 即可。

时间复杂度 $\mathcal O(n\log V)$。



## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e5+1,INF=1e9;
int n,k,T,x[MAXN],e[MAXN];
inline bool check(int v) {
	for(int i=1;i<=n;++i) e[i]=x[i]-2*T*v*i;
	if(e[1]<e[n]) return false;
	int lb=k,rb=k;
	for(int i=k-1;i>=1;--i) if(e[i]>=e[lb]) lb=i;
	for(int i=k+1;i<=n;++i) if(e[i]<=e[rb]) rb=i;
	int l=k,r=k;
	while(lb<l||r<rb) {
		bool ok=false;
		int lp=l;
		while(lb<lp&&e[lp-1]>=e[r]) {
			--lp; if(e[lp]>=e[l]) break;
		}
		if(lp<l&&e[lp]>=e[l]) l=lp,ok=true;
		int rp=r;
		while(rp<rb&&e[rp+1]<=e[l]) {
			++rp; if(e[rp]<=e[r]) break;
		}
		if(rp>r&&e[rp]<=e[r]) r=rp,ok=true;
		if(!ok) return false;
	}
	l=1,r=n;
	while(l<lb||rb<r) {
		bool ok=false;
		int lp=l;
		while(lp<lb&&e[lp+1]>=e[r]) {
			++lp; if(e[lp]>=e[l]) break;
		}
		if(lp>l&&e[lp]>=e[l]) l=lp,ok=true;
		int rp=r;
		while(rb<rp&&e[rp-1]<=e[l]) {
			--rp; if(e[rp]<=e[r]) break;
		}
		if(rp<r&&e[rp]<=e[r]) r=rp,ok=true;
		if(!ok) return false;
	}
	return true;
}
signed main() {
	scanf("%lld%lld%lld",&n,&k,&T);
	for(int i=1;i<=n;++i) scanf("%lld",&x[i]);
	int l=0,r=INF,res=INF;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(check(mid)) res=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",res);
	return 0;
}
```



---

## 作者：louhao088 (赞：5)

一道较为困难的贪心。


------------


首先看到题目要求最大的最小，马上想到二分速度，但是这个 $O(n)$ 的 check 函数并不是很好写。


------------


考虑贪心，读题我们可以先得到一些显然的结论：

1. 两个人相遇，肯定不会立刻点燃，而是会在一个人要灭的时候在点燃，这样可以使点燃的时间最长。

2. 人们肯定都会向手持烟火的那个人跑去。

3. 人们跑步的时候肯定会保持最大速度。


------------


通过以上几个结论，我们可以进行一些转换。

1. 我们发现可以把两个人相遇当成烟火燃烧时间加 $T$​​ 相遇后他们就相当于跟着拿烟火那个人跑。

2. 由于两两之间的距离是确定的，每个人的速度也是确定的，那么我们可以把他们之间的距离换成时间。
3. 手持烟花的人如果往一边跑，他另一边的人与他的距离不变，另一边以 2 倍速度减少。


------------


我们先想到了一个贪心，就是那烟火的人不停往离他最近的那个人跑。

看起来很有道理，但实际有反例。

![](https://cdn.luogu.com.cn/upload/image_hosting/dcnng91e.png)

如此图（三角形代表有烟火的人），原来他是可以走到左边，如按上述贪心，他会先向右走，如果这一段路程浪费了，他有可能走不到左边了，而他走到左边则能到右边。


------------


上述过程给我们了一个启示，就是我们可以把一些人当成一个组。

具体的，我们从拿烟花的那个人开始，到他左边第一个能使他烟火燃烧时间变长的位置分成一组，记录下这一组中能使他增长的时间与需要的时间，就是这个过程他烟火时间最少的时间。然后从这个点开始再一次找到第一个能使他烟火燃烧时间变长的位置分成一组，重复操作。

![](https://cdn.luogu.com.cn/upload/image_hosting/siotxm1a.png)

------------


如此图（三角形代表有烟火的人），需要时间为 2T，增加时间为 $\frac{1}{3}T$。

如果这样，我们发现当能选一组是一定要选，这样肯定不会使答案变劣。这样在除了最左边和最右边有一段不会优的，其他都可以处理。如果不行那么就是有一段没有解。

然后我们发现最后一段其实更与之前是一样的只要用相反的方法就好了。


------------


时间复杂度 $O(n \log n)$。

[代码](https://www.luogu.com.cn/paste/tgq12vhe)







---

## 作者：C20203030 (赞：3)


## 一、题目

[点此看题](https://www.luogu.org/problem/AT2535)

## 二、解法

这道题很容易想到二分答案，但是难点在于$O(n)$写$check$函数（~~不是一般的毒瘤~~）。

对于每一段区间（区间是指左右端点在人上的区间，区间中最初只有一个人带有火种），发现区间中的所有人都要向火种的方向靠近。运用相对运动的思想，运动$x[r]-x[l]$的距离，就可以视为点燃该区间所有的烟花棒，有了路程和速度，考虑时间，发现时间$T\times (r-l)$，即是点燃$r-l$根烟花棒争取到的时间，我们可以列出一个判断式：

$2v\times T\times(r-l)>=x[r]-x[l]$

这个判断式的理解很重要，你是否注意到，凭什么我们一定能点燃$r-l$根烟花棒呢？所以这个不是充要条件，因为我们要保证能点燃$r-l$个烟花棒，这个判断式是用来判断$[l+1,r]$能否扩展到$[l,r]$，所以还不如称它为扩展式。

受到扩展式的启发，问题变成了是否存在一种方案，使得$[k,k]$能扩展到$[1,n]$，要保证扩展过程中的每一个区间皆合法，为了方便表达，我们记$a[i]=x[i]-2v\times T\times i$，扩展式转化成了$a[l]>=a[r]$。

要保证扩展过程中每个区间都合法，扩展的顺序就即为重要（即先向左扩展还是先向右扩展），该问题的难点便在于如何决策，搜索是指数级的，我们不妨考虑贪心。
贪心地看，$a[l]$最大，$a[r]$最小的区间是“最合法”的（就称它为$std$区间吧），搜索为什么慢，因为它是毫无目的性的枚举，我们的扩展需要有很强的目的性，这给了我们一个思路，要把当前区间往$std$区间靠近，也就是扩展区间时要保证区间的$a[l]$单调递增，$a[r]$单调递减，这样我们就得到了$std$区间。

现在我们在考虑将$std$区间扩展到$[1,n]$，发现这样做的话我们会遇到相同的问题，由于扩展和缩小是互逆的操作，我们可以$[1,n]$缩小到$std$区间，还是要让$a[l]$递增，$a[r]$递减。

好优秀的贪心，总时间复杂度竟然只有$O(n\log n)$。


```cpp
#include <cstdio>
#define int long long
const int MAXN = 100005;
int read()
{
    int x=0,flag=1;
    char c;
    while((c=getchar())<'0' || c>'9') if(c=='-') flag=-1;
    while(c>='0' && c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*flag;
}
int n,k,T,ans,x[MAXN],a[MAXN];
bool check(int v)
{
    for(int i=1; i<=n; i++)
        a[i]=x[i]-2*T*v*i;
    if(a[1]<a[n]) return 0;
    int L=k,R=k;
    for(int i=1; i<=k-1; i++)
        if(a[i]>=a[L]) L=i;
    for(int i=k+1; i<=n; i++)
        if(a[R]>=a[i]) R=i;
    int l=k,r=k;
    while(l!=L || r!=R)
    {
        int ok=0,ll=l,rr=r;
        while(ll>L && a[ll-1]>=a[r])
        {
            if(a[--ll]>=a[l]) break;
        }
        if(ll<l && a[ll]>=a[l]) ok=1,l=ll;
        while(rr<R && a[rr+1]<=a[l])
        {
            if(a[++rr]<=a[r]) break;
        }
        if(rr>r && a[rr]<=a[r]) ok=1,r=rr;
        if(!ok) return 0;
    }
    l=1;
    r=n;
    while(l!=L || r!=R)
    {
        int ok=0,ll=l,rr=r;
        while(ll<L && a[ll+1]>=a[r])
        {
            if(a[++ll]>=a[l]) break;
        }
        if(ll>l && a[ll]>=a[l]) ok=1,l=ll;
        while(rr>R && a[rr-1]<=a[l])
        {
            if(a[--rr]<=a[r]) break;
        }
        if(rr<r && a[rr]<=a[r]) ok=1,r=rr;
        if(!ok) return 0;
    }
    return 1;
}
void conquer(int l,int r)
{
    if(l>r) return ;
    int mid=(l+r)>>1;
    if(check(mid))
    {
        ans=mid;
        conquer(l,mid-1);
    }
    else
        conquer(mid+1,r);
}
signed main()
{
    n=read();
    k=read();
    T=read();
    for(int i=1; i<=n; i++)
        x[i]=read();
    conquer(0,1e9);
    printf("%d\n",ans);
}
```



---

## 作者：櫻尘ིོི༹ (赞：3)

**一道有点难的贪心**


**Part 0 算法**

用什么算法不是很难想，数据范围提示性太强，明显$O(nlogn)$,就贪心加二分答案。

**Part 1 思路**

既然想要最大速度尽量的小，那我们就一定要让每一个人的烟花都燃烧完，让点燃的时间最长。

于此同时，让最大速度尽量小的第二点，就是让人们两两之间的距离尽量小，所以需要我们让所有人都尽量靠近那个烟花正在燃烧的人。

由于他们之间的距离是确定的，且每个人的速度也由二分答案枚举而确定，所以我们可以将他们之间的距离变成时间。

为了尽量压缩所枚举人的时间，我们将每一部分人当作一个集合。

从现在拿烟花的那个人开始，左边第一个可以使他烟花燃烧时间变长的人与他之间的一段人为一个集合，记录下这一集合中能使他增长的时间以及需要的时间，就是这个过程他烟火时间最少的时间。

由此，多次同样的操作。

注意的是，如果这个时间有集合可以选择，就一定要先看集合。

最后还剩一段时，原理相同，用相反的方法即可。

**Part 2 核心代码**

```cpp
bool check(int v){
    for(int i=1;i<=n;i++){
    	a[i]=x[i]-2*v*t*i;
	}
    if(a[1]<a[n]){
    	return 0;
	}
    int left=k,right=k;
    for(int i=k-1;i;i--){
        if(a[i]>=a[left])left=i;
    }
    for(int i=k+1;i<=n;i++){
        if(a[i]<=a[right])right=i;
    }
    int l=k,r=k;
    while(l!=left||r!=right){
        int key=0,lt=l,rt=r;
        while(lt>left&&a[lt-1]>=a[r]){
            if(a[--lt]>=a[l]){
            	break;
			}
        }
        if(lt<l&&a[lt]>=a[l])key=1,l=lt;
        while(rt<right&&a[rt+1]<=a[l]){
            if(a[++rt]<=a[r]){
				break;
			}
        }
        if(rt>r&&a[rt]<=a[r])key=1,r=rt;
        if(!key){
        	return false;
		}
    }
    l=1,r=n;
    while(l!=left||r!=right){
        int key=0,lt=l,rt=r;
        while(lt<left&&a[lt+1]>=a[r]){
            if(a[++lt]>=a[l]){
            	break;
			}
        }
        if(lt>l&&a[lt]>=a[l])key=1,l=lt;
        while(rt>right&&a[l]>=a[rt-1]){
            if(a[--rt]<=a[r]){
            	break;
			}
        }
        if(rt<r&&a[rt]<=a[r])key=1,r=rt;
        if(!key)return false;
    }
    return true;
}
```


---

## 作者：Mirasycle (赞：2)

很好的一道贪心题。不过就是这个第一步转化有点逆天，毕竟这个策略有点反常规，脑筋急转弯的感觉。

观察样例解释结合思考，我们可以发现其实并不是一见面就必须先点燃的，最优策略应该是跟随着当前手持烟花的人直到他的烟花熄灭之前跟随的人再续上。这样子可以最大化利用 $T$ 显然是最优的。

首先我们可以二分答案一个 $v$ 转化为判定问题。

思考一下整个过程，其实就是两边的人都往中间这个 $k$ 的位置来跑，同时 $k$ 也选择一个方向前来汇合。和 $k$ 相遇的第一个人要 $\dfrac{\Delta x}{2v}$ 的时间来遇见，追 $k$ 的另一部分人和 $k$ 的距离保持不变。每次相遇之后两个人何为一体，直到烟花时间耗尽之后还可以加 $T$。相遇之后手持烟花的人可以选择两个方向中的一个和那个方向的人相遇。

所以问题就转化为

> 有两个序列，我们要从两个序列的头部开始取。初始有一个值 $T$，每次取一个序列的数要把当前权值减去该数，然后再加上 $T$，必须保持序列时刻非负。要求判定能否取完两个序列。

我的想法是应该可以转化为同 NOIP 2023 T3 的那个双序列扩展走格子。就是设状态 $(i,j)$ 表示第一个序列扩展了 $i$ 个，第二序列扩展了 $j$ 能否可行。也就是要求 $\sum\limits_{k=1}^i a_k+\sum\limits_{k=1}^j b_k\le (i+j)\times T$。常用处理式子的手段就是把相同变量放到一边，也就是要求 $\sum\limits_{k=1}^i a_i-i\times T\ge j\times T-\sum\limits_{k=1}^jb_k$。令 $f_i=\sum\limits_{k=1}^ia_i-i\times T$,$g_i=i\times T-\sum\limits_{k=1}^i b_k$。扩展途中保证 $f_i\ge g_j$ 即可。

然后像那题一样双指针维护走格子即可。

不过看到了题解区一种更精妙的贪心解法。

首先，每次左右两个队列选可获权值最大的来扩展显然是不对的。因为可能会出现获得权值 $T-a_i<0$ 的情况，这样子虽然往前扩展了但是当前权值变小了，没有保证两个方面都是最优的，所以这个贪心就是错误的了。但是如果保证每次 $T>a_i$，那么这个贪心就是正确的了，因为我们不仅往前扩展了，而且当前权值还增大了，故此为最优解。

这启发我们每次选择往前扩展一段长度 $l$ 使得其中的 $l\times T-\sum a_i \ge 0$。

如果无法找到上述连续段，意味着达到了前缀贡献最大值，我们可以采用**时间倒流**。

因为在有解的情况下，序列扩展到终点权值是 $\ge 0$。所以末状态合法，我们只需要从末状态往前不断划分，由于终止位置到末尾的贡献是负的，所以我们倒着往前划分就是正的了。

![](https://cdn.luogu.com.cn/upload/image_hosting/kr4rlgfl.png)

画出贡献图象，其实本质就是从峰顶（蓝笔，也就是贡献前缀最大值位置）为分界点进行前后划分，跨过最大值点必然会使得贡献变小很难贪心，但是前后各走一遍就保证了可以不断往高处走。

时间复杂度 $O(n\log V)$。

---

