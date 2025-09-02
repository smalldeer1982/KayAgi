# [IOI 2015] horses

## 题目描述

像他的祖先一样，Mansur 喜欢繁殖马匹。目前，他拥有哈萨克斯坦最大的马场。以前情况可不是这样，$N$ 年前 Mansur 年轻时，他只拥有一匹马，但他一直梦想着成为富豪，最终,他美梦成真。

按照时间的先后顺序将年份编号为 $0$ 到 $N-1$（即 $N-1$ 年是最近的一年）。每年的天气会影响马匹的繁殖。Mansur 用一个正整数 $X[i]$ 记录第 $i$ 年的繁殖系数，如果第 $i$ 年开始时有 $h$ 匹马，那么这一年结束时会有 $h \times X[i]$ 匹马。

每年，只有年底的时候可以出售马匹。Mansur 用一个正整数 $Y[i]$ 记录第 $i$ 年末卖出一匹马的售价。Mansur 可以卖出任意多匹马，每匹售价均为 $Y[i]$。

现在，Mansur 想知道如果在 $N$ 年中，他总能在最佳时间出售马匹，他能获得的最大收益是多少？你正好在 Mansur 家做客，所以他想请你帮他回答这个问题。

Mansur 对记录下的 $X$ 和 $Y$ 做了 $M$ 次更新，每次更新，Mansur 要么改变一个 $X[i]$，要么改变一个 $Y[i]$。每次更新后，他都会问你出售马匹能获得的最大收益。Mansur 的更新是累加的，即你的每个回答时都应该考虑之前的所有更新。注意：某个 $X[i]$ 或者 $Y[i]$ 可能会被更新多次。

对于 Mansur 的问题，实际的答案可能是一个非常大的数字，你只要给出实际答案模 $10^9+7$ 后的结果即可。

## 说明/提示

对于 $100\%$ 的数据，$1\le N\le 5\times 10^5$，$0 \le M \le 10^5$。

## 样例 #1

### 输入

```
3
2 1 3
3 4 1
1
2 1 2
```

### 输出

```
8
6
```

# 题解

## 作者：伟大的王夫子 (赞：14)

线段树题一遍就A了，写偏题解纪念一下

首先，假设$ans,mul$分别是区间的答案，以及所有$X$值的乘积

那么容易得出转移方程
首先，
$\max\limits_{l \le i \le r}{(\prod_{i=l}^r Y_i})\times X_i =\max(\max\limits_{l \le i \le mid}{(\prod_{i=l}^r Y_i})\times X_i,\max\limits_{mid +1\le i \le r}{(\prod_{i=l}^r Y_i})\times X_i)$

而$\max\limits_{mid \le i \le r}{(\prod_{i=l}^r Y_i})\times X_i) =\max\limits_{mid +1\le i \le r}{(\prod_{i=mid+1}^r Y_i})\times X_i
\times \prod_{i=l}^{mid} X_i$

那么转移就很好转移了

由于结果过大，而且取了模会影响比大小，所以我们取对数，乘法变为加法。

询问便直接返回根节点的值

这样写法比许多人写的维护一堆值方便的多，而且代码简洁易懂，目前最优解。

总之，这道题说白了就是道线段树模板题，一定要好好掌握

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const int N = 5e5 + 5; 
int n, m;
ll X[N], Y[N];

const ll P = 1e9 + 7;
struct {
	int l, r;
	db sum, mx;
	ll mul, ans;
} t[N << 2];
inline void push_up(int p) {
	t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
	t[p].mx = max(t[p << 1].mx, t[p << 1].sum + t[p << 1 | 1].mx);
	t[p].mul = t[p << 1].mul * t[p << 1 | 1].mul % P;
	if (t[p << 1].mx >= t[p << 1].sum + t[p << 1 | 1].mx) 
		t[p].ans = t[p << 1].ans;
	else t[p].ans = t[p << 1 | 1].ans * t[p << 1].mul % P; 
}
void build(int p, int l, int r) {
	t[p].l = l, t[p].r = r;
	if (l == r) {
		t[p].mx = log(1.0 * X[l] * Y[l]);
		t[p].sum = log(1.0 * X[l]);
		t[p].ans = X[l] % P * Y[l] % P;
		t[p].mul = X[l] % P;
		return; 
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	push_up(p); 
}
void change(int p, int x) {
	if (t[p].l == t[p].r) {
		t[p].mx = log(1.0 * X[x] * Y[x]);
		t[p].sum = log(1.0 * X[x]);
		t[p].ans = X[x] % P * Y[x] % P;
		t[p].mul = X[x] % P; 
		return;
	}
	int mid = (t[p].l + t[p].r) >> 1;
	if (x <= mid) change(p << 1, x);
	else change(p << 1 | 1, x);
	push_up(p);
}
main() {
	cin >> n;
	for (register int i = 1; i <= n; ++i) scanf("%lld", X + i);
	for (register int i = 1; i <= n; ++i) scanf("%lld", Y + i);
	build(1, 1, n);
	printf("%lld\n", t[1].ans);
	cin >> m;
	while (m--) {
		int type, pos;
		ll val;
		scanf("%d%d%lld", &type, &pos, &val);
		if (type == 1) X[pos + 1] = val;
		else Y[pos + 1] = val;
		change(1, pos + 1);
		printf("%lld\n", t[1].ans); 
	}
}
```

---

## 作者：muyang_233 (赞：9)

[原题传送门](https://www.luogu.com.cn/problem/P5874)  

动态区间最值问题再加上 $N = 5 \times 10 ^ 5$，容易想到线段树维护。  
定义 ${maxn}$ 为对于区间 $[l,r]$ 的  
$$\max\limits_{i=l}^{r}\{(\prod\limits_{k=l}^{i}x_{k}) \times y_{i}\}\ \ \ \ (*)$$  
分析题目，发现我们需要求的答案就是区间 $[1,n]$ 的答案。  

那么我们来考虑 ${maxn}$ 的更新。  
事实上，对于区间 $[l,r]$ 及其中点 $mid$，$(*)$ 式中提到的 $i$ 有 $i \leq mid$ 及 $i > mid$ 两种情况。  
对于第一种情况，区间 $[l,r]$ 的 $maxn$ 值等于左子区间 $[l,mid]$ 的 $maxn$ 值。  
对于第二种情况，注意到  
$$\prod\limits_{k=l}^{i}x_{k} = \prod\limits_{k=l}^{mid}x_{k} \times \prod\limits_{k=mid+1}^{i}x_{k}$$
故区间 $[l,r]$ 的 $maxn$ 值，等于左子区间 $[l,mid]$ 所有 $x_{k}$ 之积乘上右子区间 $[mid+1,r]$ 的$maxn$ 值。  
这样我们在线段树中再引入 $timesn$ 这个变量表示区间 $[l,r]$ 的所有 $x$ 之积，它的更新是显然的，不再赘述。  
于是我们有这样的伪代码：对于区间 $q$，  
```
	q.maxn=max(q.lson.maxn,q.lson.timesn*q.rson.maxn)
```  

这样去做线段树就对了吗？我们发现这样做下去 $maxn$ 和 $timesn$ 都会爆 $long\ long$ ，而我们本就要记录的答案是取过模的，不能用来比较大小。  
这时候我们想到
$$\log_{a}(x \times y) = \log_{a}(x) + \log_{a}(y)$$  
于是我们在线段树中，不再存储 $maxn$ 和 $timesn$ 的值，转而去存储 $\ln(maxn)$ 和 $\ln(timesn)$ 的值，处理的时候乘都改为加即可。  
代码：  
```cpp
#include <cmath>
#include <cstdio>
using namespace std;
#define ll long long
#define p (ll)(1e9+7)
#define debug puts("qaq")
ll val;
int n,m; 
int type,pos;
ll x[500005];
ll y[500005];
struct node{
	double rmax=0.0,rtimes=0.0;//两个数以e为底的对数
	ll maxn,timesn;//取模后的值，输出答案用的
}TREE[2000005];
inline double max(double _1,double _2){
	return _1>_2?_1:_2;
}
inline void pushup(int res){//上传函数
	TREE[res].rmax=max(TREE[res<<1].rmax,TREE[res<<1].rtimes+TREE[res<<1|1].rmax);//更新，可以发现使用的是加法
	TREE[res].rtimes=TREE[res<<1].rtimes+TREE[res<<1|1].rtimes;//同样是加法
	if (TREE[res<<1].rmax>=TREE[res<<1].rtimes+TREE[res<<1|1].rmax){
		TREE[res].maxn=TREE[res<<1].maxn;
	}
	else{
		TREE[res].maxn=TREE[res<<1].timesn*TREE[res<<1|1].maxn%p;
	}
	TREE[res].timesn=TREE[res<<1].timesn*TREE[res<<1|1].timesn%p;
}
inline void build(int l,int r,int res){//建树函数
//	printf("%d %d %d\n",l,r,res);
	if (l==r){
//		printf("%lf\n",TREE[res].rmax);
		TREE[res].rmax=log(1.0*x[l]*y[l]);
		TREE[res].rtimes=log(1.0*x[l]);
		TREE[res].maxn=(x[l]%p)*(y[l]%p)%p;
		TREE[res].timesn=x[l]%p;
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,res<<1);
	build(mid+1,r,res<<1|1);
	pushup(res);
}
inline void update(int l,int r,int res,int qwq){//更新函数
	if (l==r){
		TREE[res].rmax=log(1.0*x[l]*y[l]);
		TREE[res].rtimes=log(1.0*x[l]);
		TREE[res].maxn=(x[l]%p)*(y[l]%p)%p;
		TREE[res].timesn=x[l]%p;
		return;
	}
	int mid=(l+r)>>1;
	if (qwq<=mid){
		update(l,mid,res<<1,qwq);
	}
	else{
		update(mid+1,r,res<<1|1,qwq);
	}
	pushup(res);
}
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		scanf("%lld",&x[i]);
	}
	for (int i=1;i<=n;i++){
		scanf("%lld",&y[i]);
	}
	build(1,n,1);
	printf("%lld\n",TREE[1].maxn);
	scanf("%d",&m);
	while(m--){
		scanf("%d%d",&type,&pos);
		scanf("%lld",&val);
		if(type==1){
			x[pos+1]=val;
            //一点小细节：为方便处理，我们的数组下标从1开始，所以这里pos要加1
		}
		else{
			y[pos+1]=val;
		}
		update(1,n,1,pos+1);
		printf("%lld\n",TREE[1].maxn);
	}
	return 0;
}
```

---

## 作者：红火恍惚cxy (赞：5)

## 题目描述  
开始有一匹马，每年马的数量会乘 $x_i$，每年末卖出一匹马单价为 $y_i$。$x_i$ 或 $y_i$ 会有 $m$ 次更改，求所有更改前和每次更改后的最大利润。  

## 题目分析  
一个比较巧妙的想法。每年马的数量乘 $x_i$，其实相当于将之后**所有年份马的单价乘上** $x_i$。这样一来从头到尾**只会存在一匹马**，所以最优答案一定是选择一个单价最高的年份将马**全部卖出**。  
所以对 $x_i$ 的处理其实是将当年及以后年份都乘上一个数，即**区间乘法**，可以利用**线段树**来维护。  

本题还有一点需要处理，$x_i$ 与 $y_i$ 值均很大无法直接存储，取模后又无法比较大小。很巧妙的一点是**将答案取对数**，既将答案降到可以存储的大小，也不会破坏大小关系。这样就可以轻松用线段树维护了。

注意取对数后会**将乘法转化为加法**！

## 完整代码
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
    char ch=getchar();
    int w=0;
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9'){
        w=(w<<1)+(w<<3)+(ch^48);
        ch=getchar();
    }
    return w;
}
const int p=1e9+7;
int n,m;
ll a[500005],b[500005];
struct qwq{
    int l,r;
    double maxx,sumlog;
    ll ans,sum;
}tr[2000005];
inline void pushup(int x){
    tr[x].sumlog=tr[x<<1].sumlog+tr[x<<1|1].sumlog;
    tr[x].sum=tr[x<<1].sum*tr[x<<1|1].sum%p;
    if(tr[x<<1].maxx<tr[x<<1].sumlog+tr[x<<1|1].maxx){
        tr[x].maxx=tr[x<<1].sumlog+tr[x<<1|1].maxx;
        tr[x].ans=tr[x<<1].sum*tr[x<<1|1].ans%p;
    }
    else{
        tr[x].maxx=tr[x<<1].maxx;
        tr[x].ans=tr[x<<1].ans;
    }
}
inline void cr(int x,int l,int r){
    tr[x].l=l;
    tr[x].r=r;
    if(l==r){
        tr[x].ans=a[l]*b[l]%p;
        tr[x].sumlog=log(a[l]);
        tr[x].maxx=log(a[l]*b[l]);
        tr[x].sum=a[l]%p;
        return;
    }
    int mid=(l+r)>>1;
    cr(x<<1,l,mid);
    cr(x<<1|1,mid+1,r);
    pushup(x);
    return;
}
inline void chang(int x,int l){
    if(tr[x].l==tr[x].r){
        tr[x].ans=a[l]*b[l]%p;
        tr[x].sumlog=log(a[l]);
        tr[x].maxx=log(a[l]*b[l]);
        tr[x].sum=a[l]%p;
        return;
    }
    int mid=(tr[x].l+tr[x].r)>>1;
    if(l<=mid) chang(x<<1,l);
    if(l>mid) chang(x<<1|1,l);
    pushup(x);
    return;
}
int main(){
    n=read();
    for(int i=1;i<=n;++i) a[i]=read();
    for(int i=1;i<=n;++i) b[i]=read();
    cr(1,1,n);
    printf("%lld\n",tr[1].ans);
    m=read();
    int opt,whe;
    ll val;
    for(int i=1;i<=m;++i){
        opt=read();
        whe=read()+1;
        val=read();
        if(opt==1){
            a[whe]=val;
        }
        else b[whe]=val;
        chang(1,whe);
        printf("%lld\n",tr[1].ans);
    }
    return 0;
}
```

---

## 作者：寒冰大大 (赞：3)

分析这个题目，首先每匹马可以单独考虑，如果一匹马在第 $y$ 天卖出利润最高，那么显然另外的马在这一天卖利润一样，并且没有更高的，因此我们一定可以在一天卖出所有马

但是这个数字太大了，因此我们考虑取对数来维护，每一个位置卖出的利润就是 $\sum{\log (x)}+\log(y)$ ，对于每一次修改，修改 $x$ 对应前缀和的区间修改，修改 $y$ 就是单点修改。

此时维护最大值的位置，然后用线段树再算一遍，修改 $x$ 就是区间乘原来的数的逆元再乘现在这个数，修改 $y$ 不用管，然后求到 $1$ 到最大值的位置并且乘 $y$ 就是答案了。

另外还得注意，`log` 函数会炸精度，你需要使用 `log2` 这个函数

调试太久了代码太丑了，选择性地看吧（



```cpp
#include<touwenjian.h>

#define ll long long
#define lson i<<1,l,mid
#define rson i<<1|1,mid+1,r
#define ls i<<1
#define rs i<<1|1 
#define log log2

using namespace std;

const int maxn=500500;
const int modp=1e9+7;
const double eps=1e-14;

int n,m,_x[maxn],_y[maxn],looker[maxn];
double tmpx[maxn];

struct segment_tree{
	
	
	struct tree{
		int maxpos;
		ll sum,mul;
		double add,mmx;
	}t[maxn<<2];
	
	inline void pushup(int i)
	{
		if((t[ls].mmx-t[rs].mmx)>eps) t[i].maxpos=t[ls].maxpos,t[i].mmx=t[ls].mmx;
		else t[i].maxpos=t[rs].maxpos,t[i].mmx=t[rs].mmx;
		t[i].sum=(1ll*t[ls].sum*t[rs].sum)%modp;
	}
	
	inline void pushdown(int i)
	{
		if(fabs(t[i].add)>eps) 
		{
			t[ls].add+=t[i].add;
			t[rs].add+=t[i].add;
			t[ls].mmx+=t[i].add;
			t[rs].mmx+=t[i].add;
			t[i].add=0;	
		}
		if(t[i].mul!=1)
		{
			t[ls].mul=(t[ls].mul*t[i].mul)%modp;
			t[rs].mul=(t[ls].mul*t[rs].mul)%modp;
			t[ls].sum=(t[ls].sum*t[i].mul)%modp;
			t[rs].sum=(t[rs].sum*t[i].mul)%modp;
			t[i].mul=1;
		}
		return ;
	}
	
	void build_tree(int i,int l,int r)
	{
		t[i].mul=1;
		if(l==r)
		{
			t[i].mmx=tmpx[l]+log(_y[l]);
			t[i].maxpos=l;
			t[i].sum=_x[l];
			return ;
		}
		int mid=(l+r)>>1;
		build_tree(lson);
		build_tree(rson);
		pushup(i);
		return ;
	}
	
	void change_x_tree(int i,int l,int r,int x,int y,double target,int _target)
	{
		if(l>=x&&r<=y)
		{
			t[i].add+=target;
			t[i].mmx+=target;
			return ;
		}
		int mid=(l+r)>>1;
		pushdown(i);
		if(x<=mid) change_x_tree(lson,x,y,target,_target);
		if(y>mid) change_x_tree(rson,x,y,target,_target);
		pushup(i);
		return ;
	}
	
	void ano_change_tree(int i,int l,int r,int x,int _target)
	{
		if(l==r)
		{
			t[i].sum=(1ll*t[i].sum*_target)%modp; 
			return ;
		}
		int mid=(l+r)>>1;
		pushdown(i);
		if(x<=mid) ano_change_tree(lson,x,_target);
		else ano_change_tree(rson,x,_target);
		pushup(i);
		return ;		
	}
	
	void change_y_tree(int i,int l,int r,int x,int target)
	{
		if(l==r)
		{
			t[i].mmx=t[i].mmx-log(_y[l])+log(target);
			return ;
		}
		int mid=(l+r)>>1;
		pushdown(i);
		if(x<=mid) change_y_tree(lson,x,target);
		else change_y_tree(rson,x,target);
		pushup(i);
		return ;
	}
	
	int getsum(int i,int l,int r,int x,int y)
	{
		if(l>=x&&r<=y) return t[i].sum;
		int mid=(l+r)>>1;
		int ans=1;
		pushdown(i); 
		if(x<=mid) ans=(1ll*ans*getsum(lson,x,y))%modp;
		if(y>mid) ans=(1ll*ans*getsum(rson,x,y))%modp;
		return ans;
	}
	
	int ask_tree(int i,int l,int r,int x)
	{
		return (1ll*getsum(1,1,n,1,x)*_y[x])%modp;
	}
	
}st;

int ksm(int x,int y)
{
	int ans=1;
	while(y)
	{
		if(y&1) ans=(1ll*x*ans)%modp;
		x=(1ll*x*x)%modp;
		y>>=1;
	}
	return ans;
}

int main()
{
	register int i,j;
	ios::sync_with_stdio(false);
	cin>>n;
	for(i=1;i<=n;i++) cin>>_x[i];
	for(i=1;i<=n;i++) cin>>_y[i];
	for(i=1;i<=n;i++) tmpx[i]=log(_x[i]);
	for(i=1;i<=n;i++) tmpx[i]+=tmpx[i-1];
	cin>>m;
	st.build_tree(1,1,n);
	cout<<st.ask_tree(1,1,n,st.t[1].maxpos)<<endl;
	int opt,l,r;
	for(i=1;i<=m;i++)
	{
		cin>>opt>>l>>r;
		l++;	
		if(opt==1)
		{
			st.change_x_tree(1,1,n,l,n,-log(_x[l]),ksm(_x[l],modp-2));
			st.ano_change_tree(1,1,n,l,ksm(_x[l],modp-2));
			_x[l]=r;
			st.change_x_tree(1,1,n,l,n,log(_x[l]),_x[l]);
			st.ano_change_tree(1,1,n,l,_x[l]);
		}
		if(opt==2)
		{
			st.change_y_tree(1,1,n,l,r);
			_y[l]=r;
		}
		cout<<st.ask_tree(1,1,n,st.t[1].maxpos)<<endl;
	}
	return 0;
}
```



---

## 作者：DaiRuiChen007 (赞：2)

# P5874 题解

[Problem Link](https://www.luogu.com.cn/problem/P5874)



## 题目大意

> 你有 $1$ 只马，第 $i$ 年后马的数量会变成原来的 $p_i$ 倍，每年你可以以 $q_i$ 每只的价格售出任意数量的马。
>
> 求 $n$ 年后你的最大收益 $\bmod 10^9+7$ 的余数。支持 $m$ 次修改 $p_i/q_i$。
>
> 数据范围 $n\le 5\times 10^5,m\le 10^5,p_i,q_i\le 10^9$。

## 思路分析

记 $V=\max{q_i}\le 10^9$。

注意到一个观察：所有的马都会在同一时刻 $t$ 卖出，此时的 $t$ 最大化 $q_t\prod_{i\le t} p_i$，否则把其他时间卖出的向 $t$ 调整一定会更优。

考虑如何求 $t$ 满足 $q_t\prod_{i\le t}p_i$ 最大，首先考虑 $t=n$ 的情况，对于另一个 $i$ 来说，$t=i$ 时优于 $t=n$ 当且仅当 $q_i>q_n\prod_{j>i}p_j$，因此此时 $\prod_{j>i}p_j<\dfrac{q_i}{q_n}\le V$。

根据一个经典的结论，我们知道此时 $p_{i+1}\sim p_n$ 中 $>1$ 的元素只有 $\mathcal O(\log V)$ 个，因此对应的 $\prod_{i\le t}p_i$ 只有 $\mathcal O(\log V)$ 个。

用 `std::set` 维护所有非 $1$ 的位置，得到相同前缀积对应的区间，此时我们求出对应区间里 $q_i$ 的最大值即可，用线段树维护此操作。

比较时两个位置的取值注意到 $\prod_{j>i}p_j<V$，因此可以直接用 $\dfrac{q_i}{\prod _{j>i} p_j}$ 比较，求答案的时候算一下乘法逆元即可。

时间复杂度 $\mathcal O(q\log n\log V)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=5e5+5,MOD=1e9+7,LIM=1e9;
int n,m,p[MAXN],q[MAXN];
class SegmentTree {
    private:
        int tr[MAXN<<2];
        inline int L(int p) { return p<<1; }
        inline int R(int p) { return p<<1|1; }
        inline void pushup(int p) { tr[p]=max(tr[L(p)],tr[R(p)]); }
    public:
        inline void Build(int l=1,int r=n,int p=1) {
            if(l==r) return (void)(tr[p]=q[l]);
            int mid=(l+r)>>1;
            Build(l,mid,L(p)),Build(mid+1,r,R(p));
            pushup(p);
        }
        inline void Modify(int u,int l=1,int r=n,int p=1) {
            if(l==r) return (void)(tr[p]=q[l]);
            int mid=(l+r)>>1;
            if(u<=mid) Modify(u,l,mid,L(p));
            else Modify(u,mid+1,r,R(p));
            pushup(p);
        }
        inline int Query(int ul,int ur,int l=1,int r=n,int p=1) {
            if(ul<=l&&r<=ur) return tr[p];
            int mid=(l+r)>>1;
            if(ur<=mid) return Query(ul,ur,l,mid,L(p));
            if(mid<ul) return Query(ul,ur,mid+1,r,R(p));
            return max(Query(ul,ur,l,mid,L(p)),Query(ul,ur,mid+1,r,R(p)));
        }
}    TQ;
set <int,decltype(greater<int>())> pos;
int P=1;
inline int ksm(int a,int b=MOD-2,int p=MOD) {
    int ret=1;
    while(b) ret=(b&1?ret*a%p:ret),a=a*a%p,b=b>>1;
    return ret;
}
inline int calc() {
    int prod=1,qres=0,pres=0;
    for(auto it1=pos.begin(),it0=it1++;it1!=pos.end();++it0,++it1) {
        int l=*it1,r=*it0-1;
        int tmp=TQ.Query(l,r);
        if(!pres||pres*tmp>qres*prod) pres=prod,qres=tmp;
        prod=prod*p[l];
        if(prod>=LIM) break;
    }
    return P*ksm(pres)%MOD*qres%MOD;
}
signed main() {
    freopen("horses.in","r",stdin);
    freopen("horses.out","w",stdout);
    scanf("%lld",&n);
    for(int i=1;i<=n;++i) {
        scanf("%lld",&p[i]),P=P*p[i]%MOD;
        if(p[i]>1) pos.insert(i);
    }
    pos.insert(1),pos.insert(n+1);
    for(int i=1;i<=n;++i) scanf("%lld",&q[i]);
    TQ.Build();
    printf("%lld\n",calc());
    scanf("%lld",&m);
    for(int op,i,v;m--;) {
        scanf("%lld%lld%lld",&op,&i,&v),++i;
        if(op==1) {
            P=P*ksm(p[i])%MOD*v%MOD;
            if(i>1&&p[i]>1) pos.erase(i);
            if((p[i]=v)>1) pos.insert(i);
        } else q[i]=v,TQ.Modify(i);
        printf("%lld\n",calc());
    }
    return 0;
}
```



---

## 作者：BaCO3 (赞：2)

设第 $i$ 天存在一匹马，如果它在第 $i$ 天卖出，收益为 $y_i$；如果在第 $j$ 天卖出，收益为 $y_j\times \prod \limits_{k=i+1}^j x_i$。若 $y_i>y_j\times \prod \limits_{k=i+1}^j x_i$，肯定会在第 $i$ 天卖完所有的马，反之会留下所有的马。所以可以发现，一定只会在一天卖出 **所有** 的马。

因为这题涉及单点修改，考虑用线段树维护每个区间的答案。对于线段树每一个节点 $[l,r]$，维护当前区间内在哪一天卖出最优，合并两个区间的时候比较一下收益即可。最终答案即为根节点的答案。

但是有一个问题，就是最后的收益可能很大，没有办法直接比较。

设左区间在 $pos_l$ 卖出最优，右区间在 $pos_r$ 卖出最优，那么区间 $[l,r]$ 在两个点卖出的收益分别为：$y_{pos_l}\times \prod\limits_{i=l}^{pos_l} x_i$，$y_{pos_r}\times \prod\limits_{i=l}^{pos_r} x_i$。

去掉相同的部分，即比较 $y_{pos_l}$ 与 $y_{pos_r}\times \prod\limits_{i={pos_l+1}}^{pos_r} x_i$ 的大小。考虑到 $y_i\le 10^9$，所以我们只需要记录一下 $x_i$ 的乘积是否 $>10^9$ 即可，并不需要知道具体的值。具体地，维护 $is_l,is_r$ 表示当前区间答案左边和右边的 $\prod x_i$ 是否 $>10^9$，$mul_l,mul_r$ 表示当它们 $\le 10^9$ 时乘积的真实值，`update` 的时候讨论一下即可。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ls(k) k<<1
#define rs(k) k<<1|1
#define lc L,mid,ls(k)
#define rc mid+1,R,rs(k)
using namespace std;

const __int128 I=1;
const int N=5e5+10,mod=1e9+7,MAX=1e9;
int n,m;
ll x[N],y[N],op,pos,val;
struct sgt{
	ll mul[N<<2],ml[N<<2],mr[N<<2]; int ans[N<<2],isl[N<<2],isr[N<<2];
	void update(int k){
		if(isr[ls(k)]||isl[rs(k)]||I*mr[ls(k)]*ml[rs(k)]*y[ans[rs(k)]]>y[ans[ls(k)]]){
			ans[k]=ans[rs(k)];
			if(isl[ls(k)]||isr[ls(k)]||isl[rs(k)]||I*ml[ls(k)]*mr[ls(k)]*ml[rs(k)]>MAX) isl[k]=1;
			else isl[k]=0,ml[k]=ml[ls(k)]*mr[ls(k)]*ml[rs(k)];
			isr[k]=isr[rs(k)]; if(!isr[k]) mr[k]=mr[rs(k)];
		}
		else{
			ans[k]=ans[ls(k)];
			if(isr[ls(k)]||isl[rs(k)]||isr[rs(k)]||I*mr[ls(k)]*ml[rs(k)]*mr[rs(k)]>MAX) isr[k]=1;
			else isr[k]=0,mr[k]=mr[ls(k)]*ml[rs(k)]*mr[rs(k)];
			isl[k]=isl[ls(k)]; if(!isl[k]) ml[k]=ml[ls(k)];
		}
		mul[k]=mul[ls(k)]*mul[rs(k)]%mod;
	}
	void build(int L,int R,int k){
		if(L==R){mul[k]=ml[k]=x[L]; mr[k]=1; ans[k]=L; isl[k]=isr[k]=0; return;}
		int mid=(L+R)>>1; build(lc); build(rc);
		update(k);
	}
	void modify(int L,int R,int k,int tar){
		if(L==R){mul[k]=ml[k]=x[L]; mr[k]=1; ans[k]=L; return;}
		int mid=(L+R)>>1;
		if(tar<=mid) modify(lc,tar); else modify(rc,tar);
		update(k);
	}
	ll query(int L,int R,int k,int l,int r){
		if(L==l&&R==r) return mul[k];
		int mid=(L+R)>>1;
		if(r<=mid) return query(lc,l,r); else if(l>mid) return query(rc,l,r);
		else return query(lc,l,mid)*query(rc,mid+1,r)%mod;
	}
}a;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&x[i]);
	for(int i=1;i<=n;i++) scanf("%lld",&y[i]);
	a.build(1,n,1);
	printf("%d\n",a.query(1,n,1,1,a.ans[1])*y[a.ans[1]]%mod);
	scanf("%d",&m);
	while(m--){
		scanf("%d%d%d",&op,&pos,&val); pos++;
		if(op==1) x[pos]=val; else y[pos]=val;
		a.modify(1,n,1,pos);
		printf("%d\n",a.query(1,n,1,1,a.ans[1])*y[a.ans[1]]%mod);
	}

	return 0;
}

```

---

## 作者：Genius_Star (赞：1)

### 思路：

首先需要注意到所有的马肯定会在一天全部卖出，故对于区间 $[l,r]$ 的答案为：

$$\operatorname{ans}(l,r) = \max\limits_{i=l}^r \Big(y_i  \prod_{j=l}^i x_j \Big)$$

因为有修改操作，考虑使用线段树区间合并快速更新答案，设我们要由 $[l_1,r_1],[l_2,r_2]$ 的答案推出 $[l_1,r_2]$ 的答案：

$$\begin{aligned} \operatorname{ans}(l_1,r_2) &= \max\limits_{i=l_1}^{r_2}\Big(y_i \prod\limits_{j=l_1}^i x_j \Big) \\ & = \max \Big( \max\limits_{i=l_1}^{r_1} \Big(y_i \prod_{j=l_1}^i x_j \Big), \max\limits_{i=l_2}^{r_2} \Big( y_i \prod_{j=l_1}^i x_j\Big) \Big) \\ & = \max \Big(\operatorname{ans}(l_1,r_1),\Big( \prod_{j=l_1}^{r_1} x_j  \Big) \Big(\max\limits_{i=l_2}^{r_2} \Big(y_i \prod_{j=l_2}^{r_2} x_j \Big) \Big) \Big) \\ & = \max \Big(\operatorname{ans}(l_1,r_1),\Big(\prod_{j=l_1}^{r_1} x_j \Big) \operatorname{ans}(l_2,r_2) \Big)\end{aligned}$$

故我们只需要维护一个区间的答案和这个区间的 $x$ 乘积 $\operatorname{mul}(l,r)$ 即可。

但是由于乘积过大，取模后又无法取 $\max$，估考虑先对于每个数 $x \gets \log_2(x)$，这样：

$$\log_2 \Big(\prod_{j=l}^r x_j \Big) = \sum_{j=l}^r \log_2(x_j)$$

故我们可以令 $\operatorname{ans'}(l,r)$ 表示 $\log_2 \Big(\operatorname{ans}(l,r) \Big)$，$\operatorname{mul'}(l,r)$ 同理，则有转移方程：

$$\operatorname{mul'}(l_1,r_2) = \operatorname{mul'}(l_1,r_1) + \operatorname{mul'}(l_2,r_2)$$

$$\operatorname{ans'}(l_1,r_2) = \max \Big(\operatorname{ans'}(l_1,r_1),\operatorname{mul'}(l_1,r_1) + \operatorname{ans'}(l_2,r_2) \Big)$$

这样就可以通过比较大小求出 $\operatorname{ans}(l,r)$ 的值了。

时间复杂度为 $O(N \log N)$。

### 思路：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
#define For(i,l,r) for(register int i=l;i<=r;i++)
#define _For(i,l,r) for(register int i=r;i>=l;i--)
using namespace std;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const ll N=5e5+10,mod=1e9+7;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Node{
	int l,r;
	db ans_,mul_;
	int ans,mul;
}X[N<<2];
int n,q,op,x,y;
int a[N],b[N];
inline void pushup(ll k){
	X[k].mul=1ll*X[k<<1].mul*X[k<<1|1].mul%mod;
	X[k].mul_=X[k<<1].mul_+X[k<<1|1].mul_;
	X[k].ans_=max(X[k<<1].ans_,X[k<<1].mul_+X[k<<1|1].ans_);
	if(X[k<<1].ans_>=X[k<<1].mul_+X[k<<1|1].ans_)
	  X[k].ans=X[k<<1].ans;
	else
	  X[k].ans=1ll*X[k<<1].mul*X[k<<1|1].ans%mod;
}
inline void build(ll k,ll l,ll r){
	X[k].l=l,X[k].r=r;
	if(l==r){
		X[k].mul=a[l];
		X[k].ans=1ll*a[l]*b[l]%mod;
		X[k].mul_=log2(a[l]);
		X[k].ans_=log2(1ll*a[l]*b[l]);
		return ;
	}
	ll mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	pushup(k);
}
inline void update(ll k,ll i){
	if(X[k].l==i&&i==X[k].r){
		X[k].mul=a[i];
		X[k].ans=1ll*a[i]*b[i]%mod;
		X[k].mul_=log2(a[i]);
		X[k].ans_=log2(1ll*a[i]*b[i]);		
		return ;
	}
	ll mid=(X[k].l+X[k].r)>>1;
	if(i<=mid)
	  update(k<<1,i);
	else
	  update(k<<1|1,i);
	pushup(k);
}
bool End;
int main(){
	n=read();
	For(i,1,n)
	  a[i]=read();
	For(i,1,n)
	  b[i]=read();
	build(1,1,n);
	write(X[1].ans);
	putchar('\n');
	q=read();
	while(q--){
		op=read(),x=read()+1,y=read();
		if(op==1)
		  a[x]=y;
		else
		  b[x]=y;
		update(1,x);
		write(X[1].ans);
		putchar('\n');
	}
	cerr<<'\n'<<abs(&Begin-&End)/1048576<<"MB";
	return 0;
}
```

---

## 作者：Lotus_Land (赞：0)

## 题目描述

开始时有一匹马，第 $i(0\leq i \leq n-1)$ 年马的数量会乘 $x_i$，第 $i$ 年末卖出马的单价为 $y_i$，每年末可以卖出任意匹马。有 $m$ 次更改，每次更改一个 $x_i$ 或 $y_i$，求更改前和每次更改后的最大收益。

## 题目解法

首先易证得，获得最大收益时，一定是选取某一年把已有的马全部卖出。

证明：每匹马单独考虑，假设有一匹马，它在第 $i$ 年卖出的收益为 $y_i$，在第 $j(j>i)$ 年卖出的收益为 $y_j\times\prod\limits_{k=i+1}^{j}x_k$，如果 $y_i<y_j\times\prod\limits_{k=i+1}^{j}x_k$，那么就要在第 $j$ 年卖出所有的马，否则在第 $i$ 年卖出所有的马。

那么 $[l,r]$ 年份的最大收益为：

$$S_{[l,r]}=\underset{l\leq i\leq r}{\max}\{\prod_{k=l}^{i}x_k\times y_i\}$$

题目要求的答案就是 $S_{[1,n]}$。

用线段树维护上式中的两个值：$x_l$ 到 $x_r$ 的乘积，记为 $sum_{[l,r]}$； $S_{[l,r]}$，记为 $ans_{[l,r]}$。

更新方法：

$sum$ 为左右两个子节点的 $sum$ 的乘积取模。

$$\begin{aligned}
ans=S_{[l,r]}&=\underset{l\leq i\leq r}{\max}\{\prod_{k=l}^{i}x_k\times y_i\}\\
&=\max(\underset{l\leq i\leq mid}{\max}\{\prod_{k=l}^{i}x_k\times y_i\},
\prod_{k=l}^{mid}x_k\times\underset{mid+1\leq i\leq r}{\max}\{\prod_{k=l}^{i}x_k\times y_i\})\\
&=\max(S_{[l,mid]},sum_{[l,mid]}\times S_{[mid+1,r]})
\end{aligned}$$

但 $ans$ 和 $sum$ 都是取过模的，不能直接用来比较大小。

因为 $\log_a(xy)=\log_ax+\log_by$，

所以可以再维护两个值，将 $ans$ 和 $sum$ 分别取对数，记为 $al$ 和 $sl$。更新方法就把 $ans$ 和 $sum$ 中的乘号换成加号，而且不需要取模。

## 注意事项

题目中 $x,y$ 的下标是 $0\leq i \leq n-1$，询问给出的 $pos$ 也是 $0\leq pos \leq n-1$，如果习惯下标从 $1$ 开始，那么 $pos$ 也要加 $1$。

```cpp
#include<bits/stdc++.h>
#define lc(p) ((p)*2)
#define rc(p) ((p)*2+1)
#define MAXN 500005
#define MOD 1000000007
#define LL long long
#define db double
using namespace std;
int n,m;
LL x[MAXN],y[MAXN];
struct Tree{
	db al,sl;
	LL ans,sum;
	//sl是区间x[i]的乘积取log 
	//sum是区间x[i]的乘积取模
}tr[MAXN<<2];
void pushup(int p){
	tr[p].sl=tr[lc(p)].sl+tr[rc(p)].sl;
	tr[p].sum=tr[lc(p)].sum*tr[rc(p)].sum%MOD;
	if(tr[lc(p)].al<tr[lc(p)].sl+tr[rc(p)].al){
		//比较大小用的是取过log的数
		tr[p].al=tr[lc(p)].sl+tr[rc(p)].al;
		tr[p].ans=tr[lc(p)].sum*tr[rc(p)].ans%MOD; 
	} else{
		tr[p].al=tr[lc(p)].al;
		tr[p].ans=tr[lc(p)].ans;
	}
}
void build(int p,int l,int r){
	if(l==r){
		tr[p].ans=x[l]*y[l]%MOD;
		tr[p].sum=x[l]%MOD;
		tr[p].al=log(x[l]*y[l]);
		tr[p].sl=log(x[l]);
		return ;
	}
	int mid=(l+r)>>1;
	build(lc(p),l,mid);
	build(rc(p),mid+1,r);
	pushup(p);
}
void modify(int p,int l,int r,int k){//单点修改 
	if(l==r){
		tr[p].ans=x[l]*y[l]%MOD;
		tr[p].sum=x[l]%MOD;
		tr[p].al=log(x[l]*y[l]);
		tr[p].sl=log(x[l]);
		return;
	}
	int mid=(l+r)>>1;
	if(k<=mid)modify(lc(p),l,mid,k);
	else modify(rc(p),mid+1,r,k);
	pushup(p);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&x[i]);
	}
	for(int i=1;i<=n;i++){
		scanf("%lld",&y[i]);
	}
	build(1,1,n);
	cout<<tr[1].ans<<endl;	
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		int op,pos;
		LL val;
		scanf("%d%d%lld",&op,&pos,&val);
		if(op==1){
			x[pos+1]=val;
		}else{
			y[pos+1]=val;
		}
		modify(1,1,n,pos+1);
		cout<<tr[1].ans<<endl;
	}
	return 0;
}

```


---

## 作者：Lates (赞：0)

关于昨天刚考的模拟赛题出现在智能推荐这件事。。。

容易发现是找一个 $i$ 使得 $Y_{i}\prod\limits_{j=1}^{i}X_{j}$ 最大。

由于有取模这件事，而这个高精度数需要比大小。

于是可以对于每个点维护一个 pair，表示 上面那个式子取 log，和 上面那个式子取模的答案。

那么可以用取完 log 比大小变成一个和的形式。

至于修改上一个线段树支持区间修改即可。



---

