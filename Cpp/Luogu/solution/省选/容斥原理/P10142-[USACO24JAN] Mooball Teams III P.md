# [USACO24JAN] Mooball Teams III P

## 题目描述

Farmer John 在他的农场上有 $N$ 头牛（$2\le N\le 2\cdot 10^5$），编号为 $1\ldots N$。奶牛 $i$ 位于整数坐标 $(x_i,y_i)$（$1\le x_i,y_i\le N$）。Farmer John 想要挑选两支队伍来玩哞球游戏！

其中一支队伍将是「红队」；另一队将是「蓝队」。对组队只有很少的要求。两队都不能为空，并且 $N$ 头奶牛中的每一头至多只能在一个队中（可以两队都不在）。唯一的其他要求是基于哞球独特的特点：一个无限长的网，必须将其放置为平面中非整数坐标的水平或垂直直线，例如 $x=0.5$。FJ 挑选队伍必须使得可以用网将两队分开。奶牛们不愿意为此进行移动。

帮帮农夫吧！为 Farmer John 计算选择满足上述要求的红队和蓝队的方法数，对 $10^9+7$ 取模。

## 说明/提示

### 样例解释 1

我们可以选择红队为牛 1，蓝队为牛 2，或者相反。无论哪种情况，我们都可以用一个网将两支球队分开（例如，$x=1.5$）。

### 样例解释 2

以下是所有的十种可能的将奶牛分队的方法；第 $i$ 个字符表示第 $i$ 头奶牛的队伍，`R` 表示红队，`B` 表示蓝队，或 `.` 表示第 $i$ 头奶牛不在一个队伍中。 

```plain
RRB
R.B
RB.
RBB
.RB
.BR
BRR
BR.
B.R
BBR
```

### 样例解释 3

以下是所有的十二种可能的将奶牛分队的方法：

```plain
RRB
R.B
RBR
RB.
RBB
.RB
.BR
BRR
BR.
BRB
B.R
BBR
```

### 样例解释 4

确保输出答案对 $10^9+7$ 取模。

### 测试点性质

- 测试点 $5$：$N\le 10$。
- 测试点 $6-9$：$N\le 200$。
- 测试点 $10-13$：$N\le 3000$。
- 测试点 $14-24$：没有额外限制。

## 样例 #1

### 输入

```
2
1 2
2 1```

### 输出

```
2```

## 样例 #2

### 输入

```
3
1 1
2 2
3 3```

### 输出

```
10```

## 样例 #3

### 输入

```
3
1 1
2 3
3 2```

### 输出

```
12```

## 样例 #4

### 输入

```
40
1 1
2 2
3 3
4 4
5 5
6 6
7 7
8 8
9 9
10 10
11 11
12 12
13 13
14 14
15 15
16 16
17 17
18 18
19 19
20 20
21 21
22 22
23 23
24 24
25 25
26 26
27 27
28 28
29 29
30 30
31 31
32 32
33 33
34 34
35 35
36 36
37 37
38 38
39 39
40 40```

### 输出

```
441563023```

# 题解

## 作者：Lonely_NewYear (赞：6)

# P10142 题解

## 题目大意

有 $n$ 只奶牛，第 $i$ 只坐标为 $x_i,y_i$（$x,y$ 是两个排列），你要从中选出一些奶牛分为红队和蓝队（即两个不交的非空奶牛集合），问有多少种选择方案能够用一条平行于横轴或纵轴的直线区分红队和蓝队，对 $10^9+7$ 取模。

## 题目分析

容斥，总方案数为**能被横线分开的**加**能被竖线分开的**减掉**既能被横线也能被竖线分开的**。

以下部分只考虑红队最大的 $x$ 小于蓝队最小的 $x$（左红右蓝）的情况，显然最后方案数 $\times2$ 即可。

前两部分显然一样，下面只讨论能被竖线分开的部分。显然可以直接枚举 $i$ 表示 $x$ 最大的红队奶牛的 $x$ 坐标为 $i$，方案数为 $2^{i-1}(2^{n-i}-1)$（$x$ 小于 $i$ 的可以选是否加入红队，大于 $i$ 的可以选是否加入蓝队，但蓝队不能空），直接计算 $O(n)$。接下来是**既能被横线也能被竖线分开的**方案数。

考虑在 $x$ 上扫描线，假设扫到了 $i$，将奶牛按 $x$ 排序，前 $i$ 头奶牛只能参加红队（记为红牛），后 $n-i$ 头奶牛只能参加蓝队（记为蓝牛），这样就可以**被竖线分开**，我们现在对于每一头牛只有参加和不参加两种选择。把 $n$ 头奶牛按 $y$ 排序后，则要求选择参加的红牛全部在参加的蓝牛前或全部在后，考虑放在线段树上，每个线段树节点记录如下信息（均不考虑是否是空集）：

- $pa$：区间内只选红牛方案数（$2^\texttt{红牛个数}$）
- $pb$：区间内只选蓝牛方案数（$2^\texttt{蓝牛个数}$）
- $sa$：红牛在蓝牛前面方案数
- $sb$：蓝牛在红牛前面方案数

线段树 `pushup` 时记左右节点为 $l,r$，则：

- $pa=pa_l\times pa_r,pb=pb_l\times pb_r$
- $sa=sa_l\times pb_r+pa_l\times sa_r-pa_l\times pb_r$（注意把左节点全红，右节点全蓝去掉）
- $sb=sb_l\times pa_r+pb_l\times sb_r-pb_l\times pa_r$（同上）

假设当前扫描线到的牛 $i$ 的 $y$ 为 $j$，为了不算重，强制 $i$ 参加红队，记 $1\sim j-1$ 构成的区间为 $L$，$j+1\sim n$ 构成的区间为 $R$，对答案的贡献为：$pa_L\times(sa_R-pa_R)+(sb_L-pa_L)\times pa_R$（注意去掉蓝队为空的部分）。

扫描线移动时只需要将某一只蓝牛变为红牛，线段树上修改即可，合并两个线段树节点复杂度 $O(1)$，总复杂度 $O(n\log n)$。

边界等细节看代码。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=200001,mod=1e9+7;
int n;
struct node{
	int x,y;
}a[MAXN];
bool cmp(node i,node j){
	return i.x<j.x;
}
int p[MAXN];
struct data{
	int sa,sb,pa,pb;
}t[MAXN*4];
data operator + (data a,data b){
	data c;
	c.sa=(1ll*a.sa*b.pb+1ll*a.pa*b.sa+1ll*(mod-a.pa)*b.pb)%mod;
	c.sb=(1ll*a.sb*b.pa+1ll*a.pb*b.sb+1ll*(mod-a.pb)*b.pa)%mod;
	c.pa=1ll*a.pa*b.pa%mod;
	c.pb=1ll*a.pb*b.pb%mod;
	return c;
}
#define mid (l+r>>1)
#define ls (p<<1)
#define rs (p<<1|1)
void modify(int p,int l,int r,int x,bool v){
	if(l==r){
		if(v)t[p]=(data){2,2,1,2};
		else t[p]=(data){2,2,2,1};
		return;
	}
	if(x<=mid)modify(ls,l,mid,x,v);
	else modify(rs,mid+1,r,x,v);
	t[p]=t[ls]+t[rs];
}
data query(int p,int l,int r,int x,int y){
	if(x>y)return (data){1,1,1,1};
	if(x<=l&&r<=y)return t[p];
	data v=(data){1,1,1,1};
	if(x<=mid)v=v+query(ls,l,mid,x,y);
	if(mid<y)v=v+query(rs,mid+1,r,x,y);
	return v;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	p[0]=1;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
		p[i]=p[i-1]*2%mod;
	}
	int ans=0;
	for(int i=1;i<n;i++)ans=(ans+1ll*p[i-1]*(p[n-i]-1))%mod;
	ans=ans*2%mod;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)modify(1,1,n,i,1);
	for(int i=1;i<n;i++){
		int j=a[i].y;
		modify(1,1,n,j,0);
		data l=query(1,1,n,1,j-1),r=query(1,1,n,j+1,n);
		int res=(1ll*l.pa*(r.sa+mod-r.pa)+1ll*(l.sb+mod-l.pa)*r.pa)%mod;
		ans=(ans+mod-res)%mod;
	}
	cout<<ans*2%mod;
	return 0;
}
```

谢谢观看！

---

## 作者：Purslane (赞：2)

# Solution

比较简单小清新的计数题。

一种比较直接的思路是枚举分割奶牛们的横线或者竖线。但是非常容易发现你这样会算重！

算重差不多有两种：一种是奶牛们能被多条同一方向的线分割；另一种奶牛在横竖方向上都能分成两块。

考虑先求出横竖两个方向能被分割的组队的数量的总和；然后减掉两个方向组队都能被分割的队伍的总和。

前者相对容易。不妨设我们处理竖线分割。如果一种方案的奶牛，红蓝队在水平方向最近的距离是 $d$。考虑其实只有 $d$ 种 $x = \square.5$ 的竖线穿过这些奶牛，而 $1 = d - (d-1)$，所以我们很容易设计一种容斥：枚举竖线，如果这条竖线左右的奶牛分别有 $x$ 和 $y$ 只，产生答案贡献 $(2^x-1)(2^y-1)$；再强制性要求左边的奶牛严格远离这条线（和这条线的距离超过 $1$），如果这样左右奶牛分别有 $x$ 和 $y$ 只，产生答案贡献 $-(2^x-1)(2^y-1)$。甚至不需要任何数据结构维护。

后者就相对困难。如果不同队奶牛最近横向距离是 $d_1$，纵向距离是 $d_2$，那么由于 $1 = d_1d_2 - (d_1-1)d_2 - d_1(d_2-1) + (d_1-1)(d_2-1)$，我们可以采取和上文差不多的容斥手段。现在主要矛盾集中在容斥之后如何快速计算。不妨设我们的两条线分别是 $x = \alpha$ 和 $y = \beta$。不妨设这样的答案是 $f(\alpha,\beta)$。

按照惯例对第一维实行扫描线，维护 $g(x) = f(t,x)$ 的实时变化。用一个线段树维护当前 $g(x) = (2^l-1)(2^r-1) = 2^{l+r} - 2^l - 2^r +1$ 中四个项分别的和。发现移动一下竖线，顶多是对每一项乘或除以某个数。

注意，两方向都能分割的奶牛还分一三象限和二四象限两种情况。

于是就可以快乐的得出常数巨大的 $O(n \log n)$ 做法。只需要进行稍微的卡常即可通过。

> 常数有多大？每个点一共产生 $16$ 次线段树修改，每次线段树修改要带 $3$ 个值，所以是 $48$ 倍常数，堪比 $O(n \sqrt n)$。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10,MOD=1e9+7,_2=(MOD+1)/2;
int n,x[MAXN],y[MAXN],pw[MAXN],inv[MAXN],ans,cnt[MAXN],cntx[MAXN],cnty[MAXN];
inline int kmod(const int v) {if(v>=MOD) return v-MOD;if(v<0) return v+MOD; return v;}
vector<int> pt[MAXN];
namespace DS {
	#define lson (k<<1)
	#define rson (k<<1|1)
	#define mid (l+r>>1)
	int t[MAXN<<2][3],tag[MAXN<<2][3];
	inline void apply(const int k,const int op,const int v) {
		if(v>0) t[k][op]=1ll*t[k][op]*pw[v]%MOD;
		else t[k][op]=1ll*t[k][op]*inv[-v]%MOD;
		tag[k][op]+=v;
		return ;
	}
	inline void push_down(const int k,const int l,const int r,const int op) {
		if(tag[k][op]) return apply(lson,op,tag[k][op]),apply(rson,op,tag[k][op]),tag[k][op]=0,void();
	}
	inline void update(const int k,const int l,const int r,const int x,const int y,const int v,const int op1,const int op2) {
		if(x<=l&&r<=y) return apply(k,op1,v),apply(k,op2,v),void();
		push_down(k,l,r,op1),push_down(k,l,r,op2);
		if(x<=mid) update(lson,l,mid,x,y,v,op1,op2);
		if(y>mid) update(rson,mid+1,r,x,y,v,op1,op2);
		t[k][op1]=kmod(t[lson][op1]+t[rson][op1]),t[k][op2]=kmod(t[lson][op2]+t[rson][op2]);
		return ;
	}
	inline void build(const int k,const int l,const int r) {
		tag[k][0]=tag[k][1]=tag[k][2]=0;
		if(l!=r) build(lson,l,mid),build(rson,mid+1,r),t[k][0]=kmod(t[lson][0]+t[rson][0]),t[k][1]=kmod(t[lson][1]+t[rson][1]),t[k][2]=kmod(t[lson][2]+t[rson][2]);
		else t[k][0]=1,t[k][1]=t[k][2]=pw[cnt[l]];
		return ;
	}
};
inline void getans(const int mul) {
	ll res=1ll*DS::t[1][2]-1ll*DS::t[1][0]-1ll*DS::t[1][1]+n;
	return res=res*mul%MOD,ans=kmod(ans+res),void();
}
inline void add(const int pos,const int op) {
	if(op==0) {for(auto y:pt[pos]) if(y-1>0) DS::update(1,1,n,1,y-1,1,0,2);}
	else {for(auto y:pt[pos]) if(y-2>0) DS::update(1,1,n,1,y-2,1,0,2);}
	return ;
}
inline void del(const int pos) {
	for(auto y:pt[pos]) DS::update(1,1,n,y,n,-1,1,2);
	return ;
}
class IO_helper{
private:
	static const int L = 1 << 16;
	char in_buf[L], *in_st, *out_st;

	char _getc(){
		if (in_st == out_st)
		{
			out_st = (in_st = in_buf) + fread(in_buf, 1, L, stdin);
			if (in_st == out_st) return EOF;
		}
		return *in_st++;
	}
public:
	template <typename IntType>
	IO_helper &operator>>(IntType &x){
		bool ok=0;
		char c; while ((c = _getc()) < '0' || c > '9')ok|=c=='-';
		for (x = 0; c >= '0' && c <= '9'; c = _getc())
			x = x * 10 + c - '0';
		x=(ok?-x:x);
		return *this;
	}
} IO;
int main() {
	IO>>n; ffor(i,1,n) IO>>x[i]>>y[i],cntx[x[i]]++,cnty[y[i]]++;
	pw[0]=1; ffor(i,1,n) pw[i]=1ll*pw[i-1]*2%MOD; inv[0]=1; ffor(i,1,n) inv[i]=1ll*inv[i-1]*_2%MOD;
	
	int tmp=0; ffor(i,1,n) tmp=tmp+cntx[i],ans=kmod(ans+1ll*(pw[tmp]-1)*(pw[n-tmp]-1)%MOD);
	tmp=0; ffor(i,1,n) tmp=tmp+cnty[i],ans=kmod(ans+1ll*(pw[tmp]-1)*(pw[n-tmp]-1)%MOD);
	tmp=0; ffor(i,1,n) ans=kmod(ans-1ll*(pw[tmp]-1)*(pw[n-tmp-cntx[i]]-1)%MOD),tmp=tmp+cntx[i];
	tmp=0; ffor(i,1,n) ans=kmod(ans-1ll*(pw[tmp]-1)*(pw[n-tmp-cnty[i]]-1)%MOD),tmp=tmp+cnty[i];
	
	ffor(i,1,n) pt[x[i]].push_back(y[i]),cnt[y[i]]++; ffor(i,1,n) cnt[i]+=cnt[i-1];
	DS::build(1,1,n); ffor(i,1,n) del(i),add(i,0),getans(-1);
	DS::build(1,1,n); ffor(i,1,n) del(i),getans(1),add(i,0);
	DS::build(1,1,n); ffor(i,1,n) del(i),add(i,1),getans(1);	
	DS::build(1,1,n); ffor(i,1,n) del(i),getans(-1),add(i,1);
	ffor(i,1,n) pt[i].clear(); ffor(i,1,n) pt[n-x[i]+1].push_back(y[i]);
	DS::build(1,1,n); ffor(i,1,n) del(i),add(i,0),getans(-1);
	DS::build(1,1,n); ffor(i,1,n) del(i),getans(1),add(i,0); 
	DS::build(1,1,n); ffor(i,1,n) del(i),add(i,1),getans(1); 
	DS::build(1,1,n); ffor(i,1,n) del(i),getans(-1),add(i,1);
	
	cout<<kmod(ans+ans);
	return 0;
}
```

---

## 作者：Nangu (赞：1)

### 题意

有 $n$ 个坐标点，这些点中一些属于红点，一些属于蓝点，求红蓝点能被一条横线或竖线分割的方案数。

### 题解
~~小清新容斥计数题。~~

考虑容斥，先分别算出横线和竖线的贡献，再减去既能被横线分割、又能被竖线分割的方案数。

由于红队和蓝队之间所有的操作都是对等的，下文只考虑红左蓝右的情况，最后将答案乘 $2$ 即可。

对于横线和竖线的贡献，为了不算重，我们枚举 $i$，满足 $i$ 属于红点，且 $i$ 以前的牛只能属于红点，以后的牛只能属于蓝点。总贡献即为 $2\times\sum2^{i-1}\times (2^{n-i}-1_)$，其中减一是为了舍去一个蓝点的牛都没有的情况。

对于既能被横线分割、又能被竖线分割的情况，我们先将点的坐标按 $x$ 排序，再考虑扫描线。当扫到 $i$ 时，满足 $i$ 属于红点，且 $i$ 以前的牛只能属于红点，以后的牛只能属于蓝点，这样就不会算重了。与上面不同的是，我们还需满足 $\max y_\text{red}<\min y_\text{blue}$ 或者 $\min y_\text{red}>\max y_\text{blue}$，这样才可以保证这种情况会被算重。

不妨先考虑 $\max y_\text{red}<\min y_\text{blue}$ 的情况，对于后一种情况，我们将坐标轴反转即可。

考虑用线段树维护上一过程。设 $s$ 为区间内前面选红后边选蓝的贡献，$a$ 为全选红的贡献，$b$ 为全选蓝的贡献，显然有：
- $a=a_{ls}\times a_{rs}$
- $b=b_{ls}\times b_{rs}$
- $s=s_{ls}\times b_{rs}+a_{ls}\times s_{rs}-a_{ls}\times b_{rs}$

设小于 $y_i$ 的数构成的集合为 $L$，大于 $y_i$ 构成的集合为 $R$，则对答案的贡献即为：$a_L\times (s_L-a_R)$。其中减去 $a_R$ 是为了舍去没有蓝点的情况。由于 $i$ 已经是红点了，所以不存在没有红点的情况。

### 代码
~~写得太烂了，就不放了吧。~~

---

## 作者：qczrz6v4nhp6u (赞：1)

### Solution

本文的讨论不计算不同染色方案的贡献，即本文讨论的“答案”是原问题答案的 $\dfrac 12$。同时，我们认为问题中描述的直线仅包含形如 $y=a+0.5$ 与 $x=b+0.5$（$a,b\in\mathbb N\cap[1,n)$）的直线。

显然考虑枚举分割线。不难发现这样会算重，考虑分别计算平行于 $x$ 轴和 $y$ 轴分割的方案数，再减去既能平行于 $x$ 轴分割也能平行于 $y$ 轴分割的方案数。

首先考虑第一个部分。以下只讨论平行于 $y$ 轴分割的方案数，$x$ 轴是类似的。

钦定一个方案包含两个点集 $S,T$，这个方案仅能在分割线为 $x=0.5+\max_{u\in S}x_u$（即所有能分割 $S$ 和 $T$ 的直线中最靠近 $y$ 轴的直线）时计算。

这一操作的效果相当于钦定横坐标为一个常数的点必须选，其他点随意。不难得到结果：

$$\sum_{i=1}^n2^{i-1}\times(2^{n-i}-1)$$

然后考虑第二个部分。不难发现被算重的有两种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/2e1uea2v.png)

以下只讨论第一种情况，第二种情况只需要翻转坐标系再做相同的统计即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/yugnrt09.png)

不难发现这样一种方案数在分割线为 $x=s+0.5$ 与 $y=u+0.5$ 时被计算，我们只需要减去 $1$ 的贡献即可。

类似第一部分，我们钦定这种方案计算时必须选择 $x=s$ 与 $y=u$ 的点。设有 $p$ 个点满足 $x<s\land y<u$，$w$ 个点满足 $(x=s\land y\le u)\lor(y=u\land x\le s)$，$q$ 个点满足 $x>s\land y>u$。不难得到 $q=n-s-u+p+w$，当 $w\ge 1$ 时贡献为 $2^p\times (2^q-1)=2^{p+q}-2^p$。

考虑对 $x$ 轴做扫描线，发现问题即为维护序列 $A,B,C$（还有一个序列 $C$ 是因为要查询 $w$ 是否 $\ge 1$），支持 $A,B$ 区间乘和 $C$ 单点加，查询区间 $\sum (A_i+B_i)\times C_i$。这是一个很容易的线段树问题，直接做即可。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr int N=2e5+5,mod=1e9+7,inv2=(mod+1)>>1;
int n,a[N];
inline ll qpow(ll a,ll b){
	ll res=1;
	for(;b;b>>=1,a=a*a%mod)
		if(b&1)res=res*a%mod;
	return res;
}
struct Mnode{
	ll l,a,b,ac,bc;
	Mnode(){l=a=b=ac=bc=0;}
	Mnode(ll _l,ll _a,ll _b,ll _ac,ll _bc){l=_l,a=_a,b=_b,ac=_ac,bc=_bc;}
	friend Mnode operator +(const Mnode &A,const Mnode &B){ // merge
		return Mnode((A.l+B.l)%mod,(A.a+B.a)%mod,(A.b+B.b)%mod,(A.ac+B.ac)%mod,(A.bc+B.bc)%mod);
	}
};
struct Tnode{
	ll p,q;
	Tnode(){p=q=0;}
	Tnode(ll _p,ll _q){p=_p,q=_q;}
	friend Mnode operator *(const Tnode &A,const Mnode &B){ // apply
		return Mnode(B.l,A.p*B.a%mod,A.q*B.b%mod,A.p*B.ac%mod,A.q*B.bc%mod);
	}
	friend Tnode operator *(const Tnode &A,const Tnode &B){ // compose
		return Tnode(A.p*B.p%mod,A.q*B.q%mod);
	}
};
#define lc (p<<1)
#define rc (p<<1|1)
int L[N<<2],R[N<<2],M[N<<2];
Mnode Msg[N<<2];Tnode Tag[N<<2];
const Tnode eps=Tnode(1,1);
inline void pushup(int p){
	Msg[p]=Msg[lc]+Msg[rc];
}
inline void pushdown(int p){
	Msg[lc]=Tag[p]*Msg[lc];
	Msg[rc]=Tag[p]*Msg[rc];
	Tag[lc]=Tag[p]*Tag[lc];
	Tag[rc]=Tag[p]*Tag[rc];
	Tag[p]=eps;
}
void build(int l,int r,int p=1){
	L[p]=l,R[p]=r,M[p]=(l+r)>>1;
	Tag[p]=eps;
	if(l==r){
		Msg[p]=Mnode(1,qpow(2,n-l),mod-1,0,0);
		return;
	}
	build(L[p],M[p],lc);
	build(M[p]+1,R[p],rc);
	pushup(p);
}
void modify(int l,int r,const Tnode &v,int p=1){
	if(l<=L[p]&&R[p]<=r){
		Msg[p]=v*Msg[p];
		Tag[p]=v*Tag[p];
		return;
	}
	pushdown(p);
	if(l<=M[p])modify(l,r,v,lc);
	if(M[p]<r)modify(l,r,v,rc);
	pushup(p);
}
void update(int x,int p=1){
	if(L[p]==R[p]){
		Msg[p].ac=Msg[p].a;
		Msg[p].bc=Msg[p].b;
		return;
	}
	pushdown(p);
	if(x<=M[p])update(x,lc);
	else update(x,rc);
	pushup(p);
}
ll query(int l,int r,int p=1){
	if(l<=L[p]&&R[p]<=r)
		return Msg[p].ac+Msg[p].bc;
	pushdown(p);ll res=0;
	if(l<=M[p])res=(res+query(l,r,lc))%mod;
	if(M[p]<r)res=(res+query(l,r,rc))%mod;
	return res;
}
ll calc(){
	ll ans=0;
	build(1,n);
	for(int i=1;i<=n;i++){
		modify(1,n,Tnode(inv2,1));
		modify(a[i],n,Tnode(2,1));
		update(a[i]);
		ans=(ans+query(a[i],n))%mod;
		if(a[i]<n)modify(a[i]+1,n,Tnode(2,2));
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		int x,y;
		cin>>x>>y;
		a[x]=y;
	}
	ll ans=0;
	for(int i=1;i<=n;i++)
		ans=(ans+qpow(2,i-1)*(qpow(2,n-i)-1))%mod;
	ans=(ans<<1)%mod;
	ans=(ans-calc()+mod)%mod;
	reverse(a+1,a+n+1);
	ans=(ans-calc()+mod)%mod;
	cout<<(ans<<1)%mod<<'\n';
	return 0;
}
```

---

## 作者：qwer6 (赞：0)

[Link](https://www.luogu.com.cn/problem/P10142)

## 1. Description

有 $n$ 个点，现在需要在所有点中选出一个子集，并且将这个子集分成两个不交的非空集合，称为红队和蓝队，要求满足存在一条水平或竖直的直线可以将红队和蓝队分开，问选取红队和蓝队的方案数。

## 2. Solution

注：下文假定奶牛在一个平面直角坐标系中，$x$ 坐标的正方向为右侧，$y$ 坐标的正方向为上方。

首先，红队和蓝队没有本质区别，所以我们考虑求出其中一种然后乘二就是答案。

考虑容斥，求出可以被水平直线分开的方案数和可以被竖直直线分开的方案数之和，然后减掉既可以被水平直线分开，又可以被竖直直线分开的方案数。

可以被水平直线分开的方案数和可以被竖直直线分开的方案数之和很好求。
首先考虑可以被水平直线分开的方案数，枚举分界线 $mid$，指定 $x=mid$ 的奶牛一定在红队，且 $x\in[1,mid-1]$ 的奶牛要么不选，要么在红队，$x\in [mid+1,n]$ 的奶牛要么不选，要么在蓝队中。

显然，两部分奶牛分别有 $mid-1$ 和 $n-mid$ 头。那么红队的选择方案就有 $2^{mid-1}$ 种，蓝队的选择方案有 $2^{n-mid}-1$ 种，这里红队无需考虑空集问题，但是蓝队需要考虑，那么一共有 $2^{mid-1}\times (2^{n-mid}-1)=2^{n-1}-2^{mid-1}$ 种情况，直接求解即可。

而可以被竖直直线分开的方案数和可以被水平直线分开的方案数相等，可以直接乘二。

现在的问题是怎么求解可以同时被水平直线和竖直直线分开的方案数，有一个 naive 的想法，就是直接枚举水平和竖直的直线，然后红队在左上角中选，蓝队在右下角中选；红队在右上角中选，蓝队在左下角中选，同时，直线上的点一定在红队中，时间复杂度为 $O(n^2)$，显然需要优化。

我们不妨枚举竖直直线 $x$，同时钦定在竖直直线上的奶牛一定在红队中，那么根据上面的算法，假定竖直直线上的奶牛 $y$ 坐标为 $now$，我们可以将此时的方案数分为两种：$x\in [now+1,n],y\in [now+1,n]$ 的只能为红，$x\in [1,now-1],y\in [1,now-1]$ 的奶牛中右红，左蓝；$x\in [1,now-1],y\in [now+1,n]$ 的只能为红，$x\in [now+1,n],y\in [1,now-1]$ 的奶牛中左红，右蓝，显然可以使用线段树加扫描线维护，节点中保存只选红色的方案数，只选蓝色的方案数，左红右蓝的方案数，左蓝右红的方案数即可。

## 3. Code

```c++
/*by qwer6*/
/*略去缺省源和快读快写*/
const int mod=1e9+7,N=2e5+5;
int n,ans;
int y[N],pw[N];
struct Node{
    int R,B,rb,br;
    //这里的方案数均计算空集的情况 
    Node(int _R=0,int _B=0,int _rb=0,int _br=0){
        R=_R,B=_B,rb=_rb,br=_br;
    }
    Node friend operator +(Node x,Node y){
        Node res;
        res.R=mul(x.R,y.R),res.B=mul(x.B,y.B);
        res.rb=sub(add(mul(x.rb,y.B),mul(x.R,y.rb)),mul(x.R,y.B));
        //这里是因为左边只有红色且右边只有蓝色的方案数算了两次
        //为了防止重复计算，所以减掉，下一行同 
        res.br=sub(add(mul(x.br,y.R),mul(x.B,y.br)),mul(x.B,y.R));
        return res;
    }
};
struct Segment_tree{
    Node c[N<<2];
    #define ls p<<1
    #define rs p<<1|1
    #define mid (l+r>>1)
    void pushup(int p){
        c[p]=c[ls]+c[rs];
    }
    void build(int p,int l,int r){
        if(l==r){
            c[p]=Node(1,2,2,2);
            //注意初始值的设置，需要计算有空集的情况
            return ;
        }
        build(ls,l,mid),build(rs,mid+1,r);
        pushup(p);
    }
    void change(int p,int l,int r,int x){
        if(l==r){
            c[p]=Node(2,1,2,2);
            return ; 
        }
        if(mid>=x)change(ls,l,mid,x);
        else change(rs,mid+1,r,x);
        pushup(p);
    }
    Node query(int p,int l,int r,int L,int R){
        if(L<=l&&r<=R)return c[p];
        if(mid>=L&&mid<R)return query(ls,l,mid,L,R)+query(rs,mid+1,r,L,R);
        if(mid>=L)return query(ls,l,mid,L,R);
        return query(rs,mid+1,r,L,R);
    }
}Set;
int add(int x,int y){
	x+=y;
	return x>=mod?x-mod:x;
}
int sub(int x,int y){
	x-=y;
	return x<0?x+mod:x;
}
int mul(int x,int y){
	long long res=1ll*x*y;
	return res>=mod?res%mod:res;
}
signed main(){
	read(n);
	pw[0]=1;
    for(int i=1,_x,_y;i<=n;i++){
        read(_x),read(_y);
        y[_x]=_y;
        pw[i]=mul(pw[i-1],2);
    }
    for(int i=1;i<=n;i++)ans=add(ans,mul(pw[i-1],sub(pw[n-i],1)));
    ans=mul(ans,2);
    Set.build(1,1,n);
    for(int i=1;i<=n;i++){
        Set.change(1,1,n,y[i]);
        Node L,R;
        if(1<=y[i]-1)L=Set.query(1,1,n,1,y[i]-1);
        else L=Node(1,1,1,1);
        if(y[i]+1<=n)R=Set.query(1,1,n,y[i]+1,n);
        else R=Node(1,1,1,1);
        //去掉蓝队为空的情况！
        ans=sub(ans,mul(L.R,sub(R.rb,R.R)));
        ans=sub(ans,mul(sub(L.br,L.R),R.R));
    }
    write(mul(ans,2));
}
```

---

## 作者：Acoipp (赞：0)

## 题意

给定平面上若干个点，你需要求出满足以下条件的划分数量：

- 划分出来的两个集合每个集合必须非空。
- 每个元素至多在一个集合内。
- 存在一条平行于 $x$ 轴或者 $y$ 轴的直线把这两个集合隔开。

数据范围 $n \le 2 \times 10^5$ 并且 $x$ 坐标和 $y$ 坐标都是 $1 \sim n$ 的一个排列。

## 分析

首先考虑容斥，用能够被平行于 $x$ 轴的直线划分的方案加上能被平行于 $y$ 轴的直线划分的方案减去能被平行于 $x,y$ 轴的直线划分的方案就行了。

前两个是十分好算的，就是考虑固定一个点，然后进行计算就可以了，这部分的和是 $2 \sum_{i=1}^n 2^{i-1}(2^{n-i}-1)$。

接下来考虑能被平行于 $x,y$ 轴的直线划分的方案。

考虑划分出两个集合，一个集合在矩阵的左上角，一个集合在矩阵的右下角。（左下角+右上角的情况同理）

设左上角集合为 $S$，右下角集合为 $T$，则 $\max_{p \in S}\{p_x\}< \min_{q \in T}\{q_x\}$ 并且 $\max_{p \in S}\{p_y\}< \min_{q \in T}\{q_y\}$。

由此可见我们考虑 $S$ 集合两个维度的 $\max$ 的“控制点”在哪里，然后算出来上述问题的答案。

如果这两个维度 $\max$ 的所属点是同一个，这个情况是非常好算的，用树状数组 $O(n \log n)$ 统计即可。

否则我们考虑枚举一个点，然后用线段树记录另外一个点，设枚举的点的下标是 $(i,y)$，记录的点的下标是 $(x,j)$，则满足 $i \le x,j \le y$。

如果控制点是这两个的话，设 $cnt_{i,j}$ 表示所有 $1 \le x_k \le i,1 \le y_k \le j$ 的 $k$ 的个数，$cnt2_{i,j}$ 表示所有 $i \le x_k \le n,j \le y_k \le n$ 的方案数，答案就是 $2^{cnt_{x-1,y-1}}(2^{cnt2_{x+1,y+1}}-1)$。

后面那一项可以拆出来，变成 $2^{cnt_{x-1,y-1}}2^{cnt2_{x+1,y+1}}-2^{cnt_{x-1,y-1}}$，前后两项分别开线段树处理就可以做到 $O(n \log n)$ 了。

我们以前一项举例来说，就是枚举 $i$（$x$ 坐标从小到大排序），线段树记录所有 $j$ 的答案，新进来一个 $i$ 之后，所有 $j<y_i$ 的答案都要除以 $2$；而 $j=y_i$ 的答案需要预处理出来；$j>y_i$ 的答案都要乘以 $2$，证明可以画图理解一下。

## 代码

由于是大常 $O(n \log n)$ 所以代码基本上是卡着 $2$ 秒通过。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
#define mod 1000000007
using namespace std;
struct node{ll x,y;}p[N];
struct TREE{
	struct tree{ll s,t1,t2;}tr[N<<2];
	inline void pushtag(ll p,ll s,ll t,ll c1,ll c2){
		tr[p].s = (tr[p].s*c1%mod+c2*(t-s+1))%mod;
		tr[p].t1 = tr[p].t1*c1%mod,tr[p].t2 = (tr[p].t2*c1+c2)%mod;
	}
	inline void pushdown(ll p,ll s,ll t){
		pushtag(2*p,s,(s+t)/2,tr[p].t1,tr[p].t2);
		pushtag(2*p+1,(s+t)/2+1,t,tr[p].t1,tr[p].t2);
		tr[p].t1 = 1,tr[p].t2 = 0;
	}
	inline void pushup(ll p){tr[p].s = (tr[2*p].s+tr[2*p+1].s)%mod;}
	inline void build(ll s,ll t,ll p){
		tr[p].t1 = 1,tr[p].t2 = 0;
		if(s==t){
			tr[p].s = 0;
			return ;
		}
		build(s,(s+t)/2,2*p),build((s+t)/2+1,t,2*p+1);
		pushup(p);
	}
	inline void modify(ll l,ll r,ll c1,ll c2,ll s,ll t,ll p){
		if(l>r) return ;
		if(l<=s&&t<=r) return pushtag(p,s,t,c1,c2);
		pushdown(p,s,t);
		if(l<=(s+t)/2) modify(l,r,c1,c2,s,(s+t)/2,2*p);
		if(r>(s+t)/2) modify(l,r,c1,c2,(s+t)/2+1,t,2*p+1);
		pushup(p); 
	}
	inline ll query(ll l,ll r,ll s,ll t,ll p){
		if(l>r) return 0;
		if(l<=s&&t<=r) return tr[p].s;
		pushdown(p,s,t);
		ll ans = 0;
		if(l<=(s+t)/2) ans+=query(l,r,s,(s+t)/2,2*p);
		if(r>(s+t)/2) ans+=query(l,r,(s+t)/2+1,t,2*p+1);
		return ans%mod;
	}
}t1,t2;
bool cmp(node a,node b){return a.x<b.x;}
ll n,i,qmi[N],cnt[N],cnt2[N],ans,inv;
inline ll solve(){
	ll res = 0;
	sort(p+1,p+n+1,cmp);
	t1.build(1,n,1);
	for(ll i=1;i<=n;i++){
		ll cnt1 = t1.query(1,p[i].y,1,n,1);
		ll cnt23 = n-p[i].y-t1.query(p[i].y+1,n,1,n,1);
		cnt[i] = qmi[cnt1]*qmi[cnt23]%mod,cnt2[i] = qmi[cnt1];
		res = (res+cnt[i]-cnt2[i]+mod)%mod;
		t1.modify(p[i].y,p[i].y,1,1,1,n,1);
	}
	t1.build(1,n,1),t2.build(1,n,1);
	for(ll i=1;i<=n;i++){
		res = (res+t1.query(p[i].y+1,n,1,n,1)-t2.query(p[i].y+1,n,1,n,1)+mod)%mod;
		t1.modify(p[i].y+1,n,2,0,1,n,1),t2.modify(p[i].y+1,n,2,0,1,n,1);
		t1.modify(p[i].y,p[i].y,0,cnt[i],1,n,1),t2.modify(p[i].y,p[i].y,0,cnt2[i],1,n,1);
		t1.modify(1,p[i].y-1,inv,0,1,n,1);
	}
	return res;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	inv = (mod+1)/2;
	qmi[0] = 1;
	for(i=1;i<=n;i++) qmi[i] = qmi[i-1]*2%mod;
	for(i=1;i<=n;i++) cin>>p[i].x>>p[i].y;
	for(i=1;i<=n;i++) ans=(ans+qmi[i-1]*(qmi[n-i]-1+mod))%mod;
	for(i=1;i<=n;i++) ans=(ans+qmi[i-1]*(qmi[n-i]-1+mod))%mod;
	ans = (ans-solve()+mod)%mod;
	for(i=1;i<=n;i++) p[i].x=n-p[i].x+1;
	ans = (ans-solve()+mod)%mod;
	cout<<ans*2%mod<<endl;
	return 0;
}
/*
Input:
8
1 4
5 2
3 6
4 7
2 8
6 1
7 3
8 5

Ouput:
2552
*/ 
```

---

