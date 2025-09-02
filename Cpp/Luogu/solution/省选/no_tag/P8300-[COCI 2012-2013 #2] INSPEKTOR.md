# [COCI 2012/2013 #2] INSPEKTOR

## 题目背景

**本题分值按 COCI 原题设置，满分 $160$。**

## 题目描述

一个新城镇刚刚在一个小国家落成。 像往常一样，Mirko 获得了首席税务监察员的职位。 他的职责是确保镇上所有不同公司的充分会计处理。

沿大街有 $N$ 个营业厅，从左到右编号为 $1\sim N$。一开始所有的办公室都是空的； 随着时间的推移，公司将进出这些办公室。 不时，Mirko 会经过一些办公室，只检查这些办公室中目前最富有的一家。

搬入的公司用四个整数来描述：

- $T$：搬入的日期。此处设小镇建成当天为 $1$。

- $K$：办公室序号。

- $Z$：公司的每日利润（如果公司亏损，则可能为负数）。

- $S$：搬入当天公司账户余额。

如果办公室 $K$ 中已经有一家公司，则当新公司搬入时，该公司搬出。

新公司直到搬入后的第二天才开始营业（或赚取利润）。

米尔科的巡视由三个整数描述：

- $T$：巡视的日期。小镇建成当天为 $1$。

- $A,B$：Mirko 将会经过 $[A,B]$ 内所有办公室。

由于 Mirko 只在一天结束时工作，所以到 Mirko 散步时，所有公司都已经完成了当天的业务并公布了当天的利润。

帮助 Mirko 编写一个程序，在每次闲逛时查找 Mirko 路过的当前最富有的公司的账户余额。

## 样例 #1

### 输入

```
2 4
1 1 1 2 4
1 2 2 3 2
2 5 1 2
2 7 1 2
```

### 输出

```
12
17
```

## 样例 #2

### 输入

```
3 6
1 1 1 4 -2
1 2 2 2 6
2 3 3 1
2 4 3 1
1 5 3 -6 20
2 6 2 3```

### 输出

```
8
10
14```

## 样例 #3

### 输入

```
5 9
1 1 5 4 -5
2 2 3 5
1 3 4 6 9
2 4 1 2
1 6 2 2 3
2 8 2 1
1 9 4 0 17
2 10 5 5
2 11 1 4```

### 输出

```
-1
nema
7
31
17```

# 题解

## 作者：伟大的王夫子 (赞：7)

这题其实想通了很简单。

就相当于是给你几个函数 $b = kx+y$，将当前时间 $T$ 代入到区间 $[A, B]$ 所有函数当中，求所得的最大值。还要求支持修改。

这个东西貌似很难维护。如果用线段树等数据结构，比较难维护区间凸包的合并。所以我们选择分块，每次修改暴力重构凸包，查询则可以在凸包上二分，边角暴力。

那我们先推一下式子。

当 $x_1 < x_2$ 时，

$kx_1 + y_1 \le kx_2 +y_2 \Leftrightarrow k(x_1-x_2)\le y_2-y_1 \Leftrightarrow -k \le\dfrac{y_2-y_1}{x_2-x_1}$。

故 $\forall x_1 < x_2 < x_3$，如果 $x_2$ 成为最优解，那么 $\dfrac{y_3-y_2}{x_3-x_2} \le -k \le \dfrac{y_2-y_1}{x_2-x_1}$。

即我们应该维护一个斜率递减的上凸包。

注意这里 $x$ 要保证有序，所以我们用一个可重集维护凸包中的点，否则每次排序常数太大。并且 $x$ 相等时，保留 $y$ 大的。

查询我们可以二分第一个满足其与下一个点的斜率 $\le -k$ 的点，并更新答案。

而修改就当于如果本来这个位置有公司了就删除，然后加入一个新的公司。用 multiset 维护点集，并且每次暴力重构凸包。

设分块一块长度为 $len$，那么时间复杂度为 $O(\dfrac{nm\log len}{len}+mlen)$。经实际测验，$len$ 取 100 最快。注意卡常，不要用 vector，可以加上快读、快输。~~如果实在卡不过去就开 O2 吧，反正我是卡过去了。~~

关于取等问题：这个我也没有细心研究过，一个很好的方法时要么全部加等号，要么全部不加。应该不会有大问题。

参考代码 （未加 O2，20.58s）
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
using LL = long long;
const int B = 100;//长度
template <class T>
inline void Rd(T &x) {
	x = 0;
	bool f = 0;
	char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
	if (f)
		x = -x;
}
template <class T>
inline void writeInt(T x) {
	if (x < 0) putchar('-'), x = -x;
	char c[50];
	int cnt = 0;
	do {
		c[++cnt] = x % 10 + '0';
		x /= 10;
	} while (x);
	for (int i = cnt; i; --i) putchar(c[i]);
}
struct Poi {
	LL x, y;
	Poi() {
	}
	Poi(LL _x, LL _y) {
		x = _x, y = _y;
	} //kx + y
	bool operator < (const Poi &a) const {
		return x < a.x || (x == a.x && y > a.y);
	}
} a[N];
bool v[N];
double slope(const Poi &a, const Poi &b) {
	return 1.0 * (a.y - b.y) / (a.x - b.x);
}
struct DS {
	int l = 1, r = 0;
	Poi q[B + 10], a[B + 10];
	multiset<Poi> s;
	void Del(Poi x) {
		s.erase(s.find(x));
	}
	void Ins(Poi x) {
		s.insert(x);
	}
	bool empty() {
		return s.empty();
	}
	void rebuild() {
		l = 1, r = 0;
		int n = 0;
		for (auto v : s) a[++n] = v;
		n = unique(a + 1, a + n + 1, [](const Poi &a, const Poi &b) {return a.x == b.x;}) - a - 1;
		for (int i = 1; i <= n; ++i) {
			while (l < r && slope(q[r - 1], q[r]) < slope(q[r], a[i])) --r;
			q[++r] = a[i];
		}
	}
	LL query(int v) {
		int L = l, R = r;
		while (L < R) {
			int mid(L + R >> 1);
			if (slope(q[mid], q[mid + 1]) < -v) R = mid;
			else L = mid + 1;
		}
		return 1ll * v * q[L].x + q[L].y;
	}
} b[N / B + 10];
int n, m;
int main() {
	Rd(n), Rd(m);
	for (int i = 1, op, T; i <= m; ++i) {
		Rd(op), Rd(T);
		if (op == 1) {
			int K, Z, S;
			Rd(K), Rd(Z), Rd(S);
			int bK = (K - 1) / B + 1;
			if (v[K]) b[bK].Del(a[K]);
			v[K] = 1;
			b[bK].Ins(a[K] = Poi(Z, S - 1ll * Z * T));
			b[bK].rebuild();
		} else {
			int l, r;
			bool flag = 0;
			LL ans = -1e18;
			Rd(l), Rd(r);
			if (l > r) swap(l, r);
			int bl = (l - 1) / B + 1, br = (r - 1) / B + 1;
			if (br - bl <= 1)
				for (int i = l; i <= r; ++i) {
					flag |= v[i];
					if (v[i]) ans = max(ans, a[i].x * T + a[i].y);
				}
			else {
				for (int i = l; i <= min(n, bl * B); ++i) {
					flag |= v[i];
					if (v[i]) ans = max(ans, a[i].x * T + a[i].y);
				}
				for (int i = (br - 1) * B + 1; i <= r; ++i) {
					flag |= v[i];
					if (v[i]) ans = max(ans, a[i].x * T + a[i].y);
				}
				for (int i = bl + 1; i < br; ++i) {
					flag |= !b[i].empty();
					if (!b[i].empty()) ans = max(ans, b[i].query(T));
				}
			}
			if (!flag) puts("nema");
			else writeInt(ans), putchar('\n');
		}
	}
//	O(m * len + m * (n / len * log(n) + len))
//	len = sqrt(n * log2(n));
}
```

---

## 作者：y0y68 (赞：3)

分块信仰

单点修改，区间查询，考虑分块。

根据题面，一个公司在时间 $tim$ 的财富 $M$ 为 $S+Z \times (tim-T)$，变一下得到 $M=(S-Z \times T)+Z \times tim$。

令 $S-Z \times T = y, Z=x, -tim=k,M=b,$，则有 $y=kx+b$，这里要使 $b$ 最大，直接对于每个块维护上凸包即可，斜率递减。查询时块内二分。

时间复杂度 $O(m \sqrt{n} \log \sqrt{n})$

不开 O2 只能过前三个点的代码，但不想卡常了。

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N=1e5+5;
const int M=350;
int n,m;
struct Block{
	bool v[N],tag[M];
	int siz,f[N],s[M],e[M];
	ll x[N],y[N];
	struct _Queue{
		int cnt;
		pair<ll,ll>q[M];
		ld k[M];
	}Q[M];
	struct Node{
	    ll _x,_y;int id;
	    bool operator < (const Node &rhs) const{
	        return _x==rhs._x?_y>rhs._y:_x<rhs._x;
	    }
	}tmp[N];
	inline void init(){
		siz=sqrt(n*1.0);
		for(int i=1;i<=n;i++)f[i]=(i-1)/siz+1;
		for(int i=1;i<=n;i++)e[f[i]]=i;
		for(int i=n;i>=1;i--)s[f[i]]=i;
	}
	inline ld K(ll x_1,ll y_1,pair<ll,ll>pr){
		ll x_2=pr.first,y_2=pr.second;
		return (ld)(y_1-y_2)/(ld)(x_1-x_2);
	}
	inline void update(int p,ll st,ll ad){
		v[p]=tag[f[p]]=1;
		x[p]=ad,y[p]=st;
		Q[f[p]].cnt=0;
		for(int i=s[f[p]];i<=e[f[p]];i++)
		    tmp[i]._x=x[i],tmp[i]._y=y[i],tmp[i].id=i;
		sort(tmp+s[f[p]],tmp+e[f[p]]+1);//块内横坐标排序
		for(int i=s[f[p]];i<=e[f[p]];i++){
			if(!v[tmp[i].id])continue;
			if(Q[f[p]].cnt>0&&tmp[i]._x==tmp[i-1]._x)continue;//横坐标相同只选最大的纵坐标，避免出现没有斜率的情况
			if(Q[f[p]].cnt<=1){
				Q[f[p]].q[++Q[f[p]].cnt]=make_pair(tmp[i]._x,tmp[i]._y);
				if(Q[f[p]].cnt==2)Q[f[p]].k[1]=K(tmp[i]._x,tmp[i]._y,Q[f[p]].q[1]);
				continue;
			}
			while(Q[f[p]].cnt>1&&K(tmp[i]._x,tmp[i]._y,Q[f[p]].q[Q[f[p]].cnt])>K(tmp[i]._x,tmp[i]._y,Q[f[p]].q[Q[f[p]].cnt-1]))Q[f[p]].cnt--;
			Q[f[p]].q[++Q[f[p]].cnt]=make_pair(tmp[i]._x,tmp[i]._y);
			Q[f[p]].k[Q[f[p]].cnt-1]=K(tmp[i]._x,tmp[i]._y,Q[f[p]].q[Q[f[p]].cnt-1]);
		}
	}
	inline bool check(int l,int r){
		bool ret=0;
		if(f[l]==f[r]){
			for(int i=l;i<=r;i++)
				ret|=v[i];
			return !ret;
		}
		for(int i=l;i<=e[f[l]];i++)
			ret|=v[i];
		for(int i=s[f[r]];i<=r;i++)
			ret|=v[i];
		for(int i=f[l]+1;i<f[r];i++)
			ret|=tag[i];
		return !ret;
	}
	inline ll CH(int p,ll d){
		int l=1,r=Q[p].cnt-1,res=-1;
		while(l<=r){
			int mid=l+r>>1;
			if(Q[p].k[mid]<(ld)(d))res=mid,r=mid-1;
			else l=mid+1;
		}
		ll ans=Q[p].q[Q[p].cnt].second-d*Q[p].q[Q[p].cnt].first;
		if(res!=-1)ans=max(ans,Q[p].q[res].second-d*Q[p].q[res].first);
		return ans;
	}
	inline void query(ll d,int l,int r){
		if(check(l,r)){
			puts("nema");return;
		}
		ll ans=-1e18;
		if(f[l]==f[r]){
			for(int i=l;i<=r;i++)
				if(v[i])ans=max(ans,y[i]-d*x[i]);
			printf("%lld\n",ans);
			return;
		}
		for(int i=l;i<=e[f[l]];i++)
			if(v[i])ans=max(ans,y[i]-d*x[i]);
		for(int i=s[f[r]];i<=r;i++)
			if(v[i])ans=max(ans,y[i]-d*x[i]);
		for(int i=f[l]+1;i<f[r];i++)
			if(tag[i])ans=max(ans,CH(i,d));
		printf("%lld\n",ans);
	}
}bk;
int main(){
	cin>>n>>m;
	bk.init();
	for(int i=1;i<=m;i++){
		int opt;
		scanf("%d",&opt);
		if(opt==1){
			int K;ll T,Z,S;
			scanf("%lld%d%lld%lld",&T,&K,&Z,&S);
			bk.update(K,S-T*Z,Z);
		}
		else{
			int A,B;ll T;
			scanf("%lld%d%d",&T,&A,&B);
			if(A>B)A^=B^=A^=B;
			bk.query(-T,A,B);
		}
	}
	return 0;
}
```

---

## 作者：2021cyq (赞：2)

# 题意

给定一个序列，每个位置对应一个一次函数，每次操作可以把某一位置的一次函数修改成另一个，或者查询位置在 $[l,r]$ 中的一次函数与直线 $x=z$ 的交点中，纵坐标的最大值。 

# 解法

以下设 $k_i$ 表示第 $i$ 条一次函数的斜率，$b_i$ 表示第 $i$ 条一次函数的截距。

观察到时限很大，数据范围也比较小，考虑分块。

具体的，对于每一次修改，把它所在的块内的所有一次函数拿出来，建出一个类似下凸壳的东西。即为求出对于这个块里的每一个 $k_i,b_i$ ，它在这个块内在 $L_i\leq x\leq R_i$ 时是这个块内的最大值，如果无法成为最大值，那么 $L_i=R_i=-1$。

先讲怎么查询，再讲怎么求 $L_i,R_i$。

我们可以先把查询变成在一个个块里查询，现在转化成怎么在一个块内查询。

我们可以把 $L_i\neq -1$ 的点按照 $L_i$ 排序，那么对于排序后相邻的两个下标 $n,m=n+1$ 一定有 $L_m=R_n$。

那么可以把排序后的 $L_i,R_i$ 放到一个 `vector` 里面，假设这些 $L_i,R_i$ 放到 `vector` 里面叫 $Left_i,Right_i$ 以及还要加入它的下标 $num_i$，如果要查询直线 $x=z$，可以在 `vector` 中二分一个 $i$ 使得 $Left_i\leq x\leq Right_i$ 那么在这个块内，对于直线 $x=z$，取 $num_i$ 这条一次函数可以使得交点的纵坐标最大。

这样一次查询的时间复杂度为$O(\sqrt n \log(\sqrt n))$，瓶颈在于二分。

现在讲怎么求 $L_i,R_i$。

可以先按照 $b_i$ 为第一关键字从大到小，$k_i$ 为第二关键字从大到小排序，先把那些在这个块内永远不可能成为最大值的一次函数踢出去，即为如果有 $i\neq j$ 使得 $k_i\leq k_j ,b_i\leq b_j$ 那么第 $i$ 条一次函数就永远不可能成为最大值。

然后就像求下凸壳一样，用一个栈，如果当前直线与栈顶直线的交点的横坐标是小于栈中第二条直线与当前直线的交点，那么可以把栈顶直线踢掉。

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/2acgnfpv.png)

当蓝色直线在加入的时候，红色直线为栈顶直线，黑色直线为栈中第二条直线。

一次修改时间复杂度 $O(\sqrt n\log(\sqrt n))$，瓶颈在于排序。

总时间复杂度 $O(m\sqrt n\log(\sqrt n))$。

块长取小一点，因为在一个块内有机会成为最大值的直线不多，所以二分跑不满。

```cpp
#include<bits/stdc++.h>
#define re register int
#define ll long long
using namespace std;
const int N=2e5+5,M=305;
struct node
{
	ll t,k,b;
	int num;
}a[N],b[N],c[N];
int n,m,nown,nowm;
int belong[N],L[N],R[N],tot,sqrtn;
int sta[M];
vector<double>g[N];
vector<int>itnum[N];
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){f=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
void pre()
{
	for(int i=1;i<=n;i++)
	{
		int nowl=i,nowr=i+sqrtn;
		nowr=min(nowr,n);
		i=nowr;
		tot++;
		L[tot]=nowl,R[tot]=nowr;
		for(int j=nowl;j<=nowr;j++)belong[j]=tot;
	}
	for(int i=1;i<=n;i++)a[i].num=i;
}
double jiao(node x,node y){return (x.b-y.b+0.0)/(y.k-x.k+0.0);}
bool cmp(node x,node y)
{
	if(x.b==y.b)return x.k>y.k;
	return x.b>y.b;
}
ll query(int x,ll y)
{
	re l=0,r=g[x].size()-1,nowans=0;
	ll ans=-1e18;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(y>g[x][mid])
		{
			nowans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	r=g[x].size()-1;
	int nowl=nowans-2;
	int nowr=nowans+2;
	if(nowl<0)nowl=0;
	if(nowr>r)nowr=r;
	for(int i=nowl;i<=nowr;i++)ans=max(ans,y*a[itnum[x][i]].k+a[itnum[x][i]].b);
	return ans;
}
int main()
{
	n=read(),m=read();
	sqrtn=sqrt(n)+1;
	sqrtn*=0.5;
	if(sqrtn<1)sqrtn=1;
	pre();
	for(int i=1;i<=m;i++)
	{
		int opt,num;
		ll t,x,y;
		opt=read();
		if(opt==1)
		{
			t=read(),num=read(),x=read(),y=read();
			a[num].k=x;
			a[num].b=y-x*t;
			nown=nowm=0;
			int nowl=L[belong[num]],nowr=R[belong[num]];
			for(re j=nowl;j<=nowr;j++)if(a[j].k!=0||a[j].b!=0)b[++nown]=a[j];
			sort(b+1,b+1+nown,cmp);
			ll lasmax=-1e18;
			for(re j=1;j<=nown;j++)
			{
				if(lasmax>=b[j].k)continue;
				lasmax=b[j].k;
				c[++nowm]=b[j];
			}
			g[belong[num]].clear(),itnum[belong[num]].clear();
			if(nowm==1)
			{
				g[belong[num]].push_back(0),itnum[belong[num]].push_back(c[1].num);
				continue;
			}
			sta[0]=2;
			sta[1]=1,sta[2]=2;
			for(re j=3;j<=nowm;j++)
			{
				while(sta[0]>1&&jiao(c[sta[sta[0]-1]],c[j])<jiao(c[sta[sta[0]-1]],c[sta[sta[0]]]))sta[0]--;
				sta[++sta[0]]=j;
			}
			g[belong[num]].push_back(0),itnum[belong[num]].push_back(c[sta[1]].num);
			for(re j=2;j<=sta[0];j++)
			{
				g[belong[num]].push_back(jiao(c[sta[j-1]],c[sta[j]]));
				itnum[belong[num]].push_back(c[sta[j]].num);
			}
		}
		if(opt==2)
		{
			t=read(),x=read(),y=read();
			if(x>y)swap(x,y);
			ll nowans=-1e18;
			if(y-x+1<=3*sqrtn)
			{
				for(re j=x;j<=y;j++)
				{
					if(a[j].k==0&&a[j].b==0)continue;
					nowans=max(nowans,a[j].k*t+a[j].b);
				}
				if(nowans==-1e18)printf("nema\n");
				else printf("%lld\n",nowans);
				continue;
			}
			int nowl=R[belong[x]]+1,nowr=L[belong[y]]-1;
			if(nowl<=nowr)for(re j=belong[nowl];j<=belong[nowr];j++)nowans=max(nowans,query(j,t));
			for(re j=x;j<nowl;j++)
			{
				if(a[j].k==0&&a[j].b==0)continue;
				nowans=max(nowans,a[j].k*t+a[j].b);
			}
			for(re j=nowr+1;j<=y;j++)
			{
				if(a[j].k==0&&a[j].b==0)continue;
				nowans=max(nowans,a[j].k*t+a[j].b);
			}
			if(nowans==-1e18)printf("nema\n");
			else printf("%lld\n",nowans);
		}
	}
}

---

## 作者：qwer6 (赞：1)

这道题我们第一眼并不好求解，一堆一次函数改来改去，加来加去的，一点都不好处理。

但是看到区间询问，我们可以凭借丰富的做题经验发现这应该是一道数据结构的题。

经过我们一番思考，直接放弃树状数组和线段树，考虑使用分块求解。

首先，这种题目，我们必定需要维护凸包，那我们列一下式子看看维护什么凸包。
$$
y=s+z\times(x-t)
$$
我们拆开并整理。
$$
y=zx+s-zt
$$
那我们将每一个一次函数视为在平面上的 $(z,s-zt)$ 的点，维护凸包之后每一次询问就是求斜率为 $T$ 的切线，显然维护上凸包。

那我们对于每一块维护一个凸包，每一次修改暴力重建凸包即可。

其他题解的修改都是重新对于点集排序，导致跑的效率并不高，但是真的需要重新排序吗？

我们考虑对于每一块，修改时只修改一个一次函数，而原来块内的点集有序，因此我们考虑使用一个类似于冒泡排序的方式去给块内点集排序，这样在修改部分可以少掉一个 $\log$ 的时间复杂度。

这样的代码是目前你谷的最优解。

```c++
#include<bits/stdc++.h>
#define int long long
#define Nxt puts("")
#define Spa putchar(32)
#define Pline puts("------------------------------")
namespace FastIO{
	inline int read(int &a){
		char c=getchar();
		int f=1;
		a=0;
		while(!isdigit(c)){
			if(c=='-')f=-1;
			c=getchar();
		}
		while(isdigit(c)){
			a=(a<<1)+(a<<3)+(c^48);
			c=getchar();
		}
		return a=a*f;
	}
	inline int read(){
		char c=getchar();
		int f=1,a=0;
		while(!isdigit(c)){
			if(c=='-')f=-1;
			c=getchar();
		}
		while(isdigit(c)){
			a=(a<<1)+(a<<3)+(c^48);
			c=getchar();
		}
		return a*f;
	}
	inline void write(int x){
		if(x<0)putchar('-'),x=-x;
		std::stack<int>st;
		do{
		   st.push(x%10);
		   x/=10;
		}while(x);
		while(!st.empty())putchar(st.top()+'0'),st.pop();
		return ;
	}
	inline void tomax(int &a,int b){
		if(a<b)a=b;
		return ;
	}
	inline void tomin(int &a,int b){
		if(a>b)a=b;
		return ;
	}
}
using namespace FastIO;
using namespace std;
const int N=1e5+5,M=400,inf=1e18;
int n,m,B;
int id[N],L[M],R[M];
struct Node{
	int x,y,id;
	Node(int a=0,int b=0,int c=0){x=a,y=b,id=c;}
	bool operator <(const Node &a)const{
		if(x!=a.x)return x<a.x;
		return y<a.y;
	}
	bool operator >(const Node &a)const{
		if(x!=a.x)return x>a.x;
		return y>a.y;
	}
}a[N];
bool check(Node &s,Node &mid,Node &t){return (mid.y-s.y)*(t.x-mid.x)<=(t.y-mid.y)*(mid.x-s.x);}
struct convex{
	int top,cnt,l,r;
	Node b[M],st[M];
	void build(){
		top=0;
		for(int i=1;i<=cnt;i++){
			while(top>1&&check(st[top-1],st[top],b[i]))top--;
			st[++top]=b[i];
		}
	}
	void change(int x,Node v){//表示将位于 x 的函数修改为 v
		int now;
		bool flag=0; 
		for(int i=1;i<=cnt;i++){
			if(b[i].id==x){
				flag=1;
				now=i;
				b[i]=v;
				break;
			}
		}
		if(!flag){
			b[++cnt]=v;
			now=cnt;
		}
		while(now<cnt&&b[now]>b[now+1]){
			swap(b[now],b[now+1]);
			now++;
		}
		while(now>1&&b[now]<b[now-1]){
			swap(b[now],b[now-1]);
			now--;
		}
		return build();
	}
	int query(int K){
		if(!top)return -inf;
		int l=1,r=top;
		while(l<r){
			int mid=l+r>>1;
			if(st[mid].y-st[mid+1].y<(st[mid+1].x-st[mid].x)*K)l=mid+1;
			else r=mid;
		}
		return st[l].x*K+st[l].y;
	}
}St[M];
void init(){
	B=sqrt(n)+1;
	tomax(B,min(100ll,n));
	for(int i=1,now;i<=n;i++){
		now=id[i]=(i-1)/B+1;
		if(!L[now])L[now]=i;
		R[now]=i;
	}
}
void query(int k,int l,int r){
	int idL=id[l],idR=id[r],ans=-inf;
	if(idR-idL<=1){
		for(int i=l;i<=r;i++)
			if(a[i].id)
				tomax(ans,a[i].x*k+a[i].y);			
	}else{
		for(int i=R[idL];i>=l;i--)
			if(a[i].id)
				tomax(ans,a[i].x*k+a[i].y);
		for(int i=L[idR];i<=r;i++)
			if(a[i].id)
				tomax(ans,a[i].x*k+a[i].y);
		for(int i=idL+1;i<idR;i++)
			tomax(ans,St[i].query(k));
	}
	if(ans==-inf)puts("nema");
	else write(ans),Nxt;
}
signed main(){
	read(n),read(m);
	init();
	for(int i=1,opt,t,k,s,z,l,r;i<=m;i++){
		read(opt);
		if(opt==1){
			read(t),read(k),read(z),read(s);
			a[k]={z,s-z*t,k};
			St[id[k]].change(k,Node{z,s-z*t,k});
		}else{
			read(t),read(l),read(r);
			if(l>r)swap(l,r);
			query(t,l,r);
		}
	}
}
```

---

## 作者：xuyiyang (赞：0)

### [P8300 [COCI 2012/2013 #2] INSPEKTOR](https://www.luogu.com.cn/problem/P8300)
### Solution
注意到是李超线段树的加强版，有了修改和区间查询。一开始胡了个 KTT，但是好像不怎么好做。所以考虑块块。$\\$
对于块内，考虑对直线 $y = kx + b$ 建立上凸壳，这样用斜率为 $-T$ 的直线去切这个凸包就是最优解。于是对于单点修改重构凸包，对于查询直接在凸包上二分即可。重构凸包归并可以线性。令块长为 $B$。则复杂度 $\mathcal O(mB +\frac{n}{B} \log B)$。取 $B = \sqrt {n \log n}$，则有复杂度 $\mathcal O(m \sqrt {n \log n})$。$\\$
这个做法还可以加强，可以做到区间直线平移。这样也是直接散块重构就好。这个东西似乎叫分块凸包？
```cpp
#define L(x) (x - 1) * B + 1
#define R(x) x * B
#define pos(x) (x + B - 1) / B

struct Ln {
	LL k, b;
	Ln () {}
	Ln (LL _k, LL _b) { k = _k, b = _b; }
	bool operator < (const Ln& t) const {
		if (k != t.k) return k < t.k;
		return b > t.b;
	}
} w[N]; bool st[N];

struct BL {
	Ln q[M];
	int hh, tt;
	multiset<Ln> S; 
	void ins(Ln x) { S.insert(x); }
	void del(Ln x) { S.erase(S.find(x)); }
	double slope(Ln x, Ln y) {
		return (y.b - x.b) * 1.0 / (y.k - x.k);
	}
	void rebuild() {
		hh = 1, tt = 0; 
		for (Ln it : S) {
			while (hh < tt && slope(q[tt - 1], q[tt]) < slope(q[tt], it)) tt -- ;
			q[ ++ tt] = it;
		}
	}
	LL qry(int K) {
		int l = hh, r = tt;
		while (l < r) {
			int mid = (l + r) >> 1;
			if (slope(q[mid], q[mid + 1]) <= -K) r = mid;
			else l = mid + 1;
		} return q[l].k * K + q[l].b;
	}
} b[M];
int main() {
	scanf("%d%d", &n, &m); B = sqrt(n);
	while (m -- ) {
		int op, x, y, z, p;
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d%d%d%d", &p, &x, &y, &z);
			if (st[x]) b[pos(x)].del(w[x]);
			w[x] = Ln(y, z - (LL)y * p); b[pos(x)].ins(w[x]);
			b[pos(x)].rebuild(); st[x] = 1;
		} else {
			scanf("%d%d%d", &p, &x, &y);
			if (x > y) swap(x, y);
			int bl = pos(x), br = pos(y);
			if (bl != br) {
				LL res = -1e18; bool flg = 0;
				for (int i = x; i <= R(bl); i ++ )
					if (st[i]) res = max(res, w[i].k * p + w[i].b), flg = 1;
				for (int i = L(br); i <= y; i ++ )
					if (st[i]) res = max(res, w[i].k * p + w[i].b), flg = 1;
				for (int i = bl + 1; i <= br - 1; i ++ )
					if (b[i].S.size()) res = max(res, b[i].qry(p)), flg = 1;
				if (!flg) puts("nema"); else printf("%lld\n", res);
			} else {
				LL res = -1e18; bool flg = 0;
				for (int i = x; i <= y; i ++ )
					if (st[i]) res = max(res, w[i].k * p + w[i].b), flg = 1;
				if (!flg) puts("nema"); else printf("%lld\n", res);
			}
		}
	} return 0;
}

---

