# [PA 2014] Muzeum

## 题目描述

吉丽的漫展有 $n$ 件手办和 $m$ 名警卫。

现在我们对其建立平面直角坐标系，每个手办和警卫都可以看做一个点。警卫们的目光都朝着 $y$ 轴负方向，且都有相同大小的视角。警卫可以看见自己视角内（包括边界上的点）的所有手办，不用考虑视线的遮挡。

你打算抢劫吉丽的漫展，但不想被警卫发现。为了实施这次抢劫计划，你可以事先贿赂某些警卫，让他们闭上眼睛。只要某件手办不在任何睁着眼睛的警卫的视野内，你就可以偷走它。你知道每件手办的价格，以及每位警卫需要接受多少钱的贿赂。你想知道自己的最大收益是多少。

## 说明/提示

对于 $100\%$ 的数据，$1\le n,m\le 2\times 10^5$，$1\le w,h\le 10^9$，$-10^9\le x_i,y_i\le 10^9$，$1\le v_i\le 10^9$。


----

### 样例解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/zxt0if8b.png)

贿赂 售价为 $3+6=9$ 元的两个警卫，偷走 价值共$2+8+4+1=15$ 元的 $4$ 个手办，收益 $15-9=6$ 元。


## 样例 #1

### 输入

```
5 3
2 3
2 6 2
5 1 3
5 5 8
7 3 4
8 6 1
3 8 3
4 3 5
5 7 6```

### 输出

```
6```

# 题解

## 作者：justin_cao (赞：3)

显然这个模型是一个最大权闭合子图的模型，但是直接连边跑显然复杂度爆炸。

于是可以想到最小割$=$最大流，那么考虑贪心模拟费用流。

首先这个坐标系看起来不太舒服，所以考虑转换一下坐标系。

如果一个警卫 $a$ 能够看到一个手办 $b$ ，那么需要满足：
$$
\frac{x_a-x_b}{y_a-y_b}\leq \frac{w}{h}
$$

$$
\frac{x_b-x_a}{y_a-y_b}\leq \frac{w}{h}
$$



那么将式子拆开可以得到：
$$
x_a\times h-y_a\times w\leq x_b\times h-y_b\times w
$$

$$
x_a\times h+y_a\times w\geq x_b\times h+y_b\times w
$$

那么我们如果将坐标 $(x,y)$ 转为坐标 $x\times h+y\times w,x\times h-y\times w$ ，那么限制条件显然就转化为了 $y_a\leq y_b,x_a\geq x_b$ 。

那么考虑将它们按照 $x$ 坐标排序，然后从小到大扫，扫到一个警卫时，由于已经排好序，所以只需要考虑 $y$ 坐标了。

考虑这个警卫向哪些手办流最优。显然往 $y$ 小的流最优（能够看到的），因为 $y$ 越大，能流到它的流就更多，所以要先流小的。

那么用这个贪心策略，我们开一个 $set$ 存一下当前还存在的手办的 $y$ 坐标和剩余的流量，每次用 $set$ 贪心的查找跑流即可。

复杂度$O(n \log n)$。

code：
```cpp
#include<bits/stdc++.h>
#define maxn 200010
using namespace std;
typedef long long ll;
int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch-'0'<0||ch-'0'>9){if(ch=='-') f=-1;ch=getchar();}
    while(ch-'0'>=0&&ch-'0'<=9){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,m,h,w;
struct P{
    ll x,y,v;
}a[maxn],b[maxn];
bool cmp(P a,P b)
{
    return a.x<b.x;
}
set<pair<ll,ll> >s;
ll ans;
int main()
{
    n=read();m=read();w=read();h=read();
    for(int i=1;i<=n;i++)
    {
        ll x=1ll*read()*h,y=1ll*read()*w,v=read();ans+=v;
        a[i].x=x+y;a[i].y=x-y;a[i].v=v;
    }
    for(int i=1;i<=m;i++)
    {
        ll x=1ll*read()*h,y=1ll*read()*w,v=read();
        b[i].x=x+y;b[i].y=x-y;b[i].v=v;
    }
    sort(a+1,a+n+1,cmp);sort(b+1,b+m+1,cmp);
    int now=0;
    for(int i=1;i<=m;i++)
    {
        while(now<n&&a[now+1].x<=b[i].x)  now++,s.insert(make_pair(a[now].y,a[now].v));
        set<pair<ll,ll> >::iterator it=s.lower_bound(make_pair(b[i].y,0));
        ll las=b[i].v;
        while(las&&it!=s.end())
        {
            pair<ll,ll> x=*it;s.erase(it);
            ll d=min(las,(ll)x.second);
            las-=d;x.second-=d;ans-=d;
            if(x.second)  s.insert(x);
            else          it=s.lower_bound(make_pair(b[i].y,0));
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：EuphoricStar (赞：3)

考虑最大权闭合子图，第 $i$ 个手办建点 $i$，第 $i$ 个警察建点 $i'$。我们有一些边：$\forall i, (S, i, v_i), (i', T, v_i)$，以及对于能看见第 $i$ 个手办的第 $j$ 个警察，有 $(i, j', \infty)$。手办的 $\sum v_i$ 减去最小割（最大流）即为答案。

考虑转换坐标系，$(x, y) \to (hx + wy, hx - wy)$。那么第 $i$ 个警察能看见第 $j$ 个手办当且仅当 $x_i \ge x_j \land y_i \le y_j$。

但是显然最大流复杂度会炸。考虑模拟最大流。下面部分和 [CF1895G Two Characters, Two Colors](https://www.luogu.com.cn/problem/CF1895G) 有点类似。

首先显然把警察和手办都按 $x$ 排序。那么我们扫警察时可以先处理 $x$ 这维的偏序。

我们可以先让 $v_i$ 的流量从 $S$ 流到 $i$。然后用一个二元组 $(y, v)$ 表示一个纵坐标为 $y$ 的点还有 $v$ 单位流量。那么我们扫警察时把所有 $x$ 比它小的二元组加入。

然后我们现在对于一个警察，它还能往汇点流 $v_i$ 的流量。考虑贪心地从 $y$ 坐标不小于它且最小的二元组获取流量。因为 $y$ 越小的二元组可能的连边就越少，我们从 $y$ 更大的二元组获取流量不会变优。

所以我们用 set 维护这些二元组，就可以直接 lower_bound 找对应的二元组了。

时间复杂度 $O((n + m) \log m)$。

```cpp
// Problem: P5996 [PA2014] Muzeum
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5996
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;

const int maxn = 200100;

ll n, m, A, B;
struct node {
	ll x, y, z;
} a[maxn], b[maxn];

void solve() {
	scanf("%lld%lld%lld%lld", &n, &m, &A, &B);
	ll ans = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%lld%lld%lld", &a[i].x, &a[i].y, &a[i].z);
		ll x = a[i].x * B + a[i].y * A, y = a[i].x * B - a[i].y * A;
		a[i].x = x;
		a[i].y = y;
		ans += a[i].z;
	}
	for (int i = 1; i <= m; ++i) {
		scanf("%lld%lld%lld", &b[i].x, &b[i].y, &b[i].z);
		ll x = b[i].x * B + b[i].y * A, y = b[i].x * B - b[i].y * A;
		b[i].x = x;
		b[i].y = y;
	}
	sort(a + 1, a + n + 1, [&](const node &a, const node &b) {
		return a.x < b.x;
	});
	sort(b + 1, b + m + 1, [&](const node &a, const node &b) {
		return a.x < b.x;
	});
	multiset<pii> S;
	for (int i = 1, j = 1; i <= m; ++i) {
		while (j <= n && a[j].x <= b[i].x) {
			S.emplace(a[j].y, a[j].z);
			++j;
		}
		ll d = b[i].z;
		while (d && S.size()) {
			auto it = S.lower_bound(mkp(b[i].y, 0));
			if (it == S.end()) {
				break;
			}
			pii p = *it;
			S.erase(it);
			ll mn = min(d, p.scd);
			d -= mn;
			p.scd -= mn;
			ans -= mn;
			if (p.scd) {
				S.insert(p);
			}
		}
	}
	printf("%lld\n", ans);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}

```


---

## 作者：gdf_yhm (赞：2)

### [P5996](https://www.luogu.com.cn/problem/P5996)

网络流。同 [P2762 太空飞行计划问题](https://www.luogu.com.cn/problem/P2762) 建图方式，将物品与 $s$ 连 $(s,i,v_i)$，警察与 $t$ 连 $(j+n,t,v_j)$，警察与对应的物品连 $(i,j+n,inf)$，答案为所有物品的收益和减最小割。割 $s,i,v_i$ 表示不选物品，收益减 $v_i$；割 $j+n,t,v_j$ 表示贿赂警察，收益减 $v_j$；警察与对应的物品的连边永远不被割，表示要么放弃物品要么贿赂警察。

$n,m\leq 10^5$，显然跑不了网络流。考虑模拟最大流。

首先要描述警察 $j$ 与物品 $i$ 的关系。要满足：

$$\mid \frac{x_i-x_j}{y_i-y_j} \mid \leq \frac{w}{h}$$

$$x_j\times h-y_j\times w\leq x_i\times h-y_i\times w$$

$$x_j\times h+y_j\times w\geq x_i\times h+y_i\times w$$

令 $x=x\times h+y\times w,y=x\times h-y\times w$。得到 $x_i\leq x_j,y_i\geq y_j$ ，能很好描述。

将物品和警察放在一起从左到右，从上到下考虑，自然满足 $x_i\leq x_j$。贪心，一个警察 $j$ 的流优先从 $y_i\geq y_j$ 且 $y_i$ 最小处流过来，因为更大的 $y_i$ 能满足更多人限制。用 set 储存物品，警察处 lower_bound 查找。set 的 erase 函数会返回删去的值的下一个的迭代器。

### code

```cpp
int n,m,w,h,ans;
struct nd{
	int x,y,v,op;
}a[maxn];
bool cmp(nd u,nd v){
	if(u.x!=v.x)return u.x<v.x;
	return u.y>v.y;
}
set<pii> s;
void work(){
	n=read();m=read();w=read();h=read();
	for(int i=1;i<=n;i++){
		int u=read(),v=read(),val=read();
		a[i]={u*h+v*w,u*h-v*w,val,1};ans+=a[i].v;
	}
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),val=read();
		a[i+n]={u*h+v*w,u*h-v*w,val,0};
	}
	sort(a+1,a+n+m+1,cmp);
	for(int i=1;i<=n+m;i++){
		if(a[i].op)s.insert({a[i].y,a[i].v});
		else{
			auto it=s.lower_bound({a[i].y,0});
			while(a[i].v){
				if(it==s.end())break;
				pii p=*it;it=s.erase(it);
				int d=min(a[i].v,p.second);
				a[i].v-=d;p.second-=d;ans-=d;
				if(p.second)s.insert(p);
			}
		}
	}
	printf("%lld\n",ans);
}
```


---

## 作者：Albert_van (赞：1)

这个最大权闭合子图的模型可以参照[原题](https://www.luogu.com.cn/problem/P2762)，推销[这篇](https://www.luogu.com.cn/article/uk0mkh37) [博客](https://www.cnblogs.com/vanspace/p/network_flow.html)。本题认为警卫 $j$ 即仪器，手办 $i$ 即实验，连边 $S\xrightarrow{v_i}i,i\xrightarrow{\infty}j,j\xrightarrow{v_j}T$，求最小割后令所有手办价值和与其作差。

首先要解决的问题是 $i\to j$ 的边有 $\mathcal O(n^2)$ 条，考虑对连边条件简化。要求：

$$|x_i-x_j|\le \frac wh(y_j-y_i)$$

拆成两个不等式：

$$\begin{cases}(x_i-x_j)h\le(y_j-y_i)w\\(x_j-x_i)h\le(y_j-y_i)w\end{cases}$$

将 $i$ 与 $j$ 相关项移到同一侧：

$$\begin{cases}x_ih+y_iw\le x_jh+y_jw\\x_jh-y_jw\le x_ih-y_iw\end{cases}$$

于是令 $X_i=x_ih+y_iw,Y_i=x_ih-y_iw$ 则条件转化为

$$\begin{cases}X_i\le X_j\\Y_i\ge Y_j\end{cases}$$

两维偏序就不好模拟最小割了。考虑最小割 $=$ 最大流模拟网络流，从大到小扫 $X$，数据结构维护 $Y$。

具体地，引一 `std::multiset` 维护 $X_j$ 大于当前 $X$ 值的所有警卫，内部按照 $Y$ 从大到小排序。对于一个 $X$，先插入警卫，再考虑每个手办。`lower_bound` 找出与这个手办有连边的警卫中，$Y$ 值最大的一个，以他为起点，按 $Y$ 从大到小枚举警卫，扣除对应的流量，若满流则将其从 `multiset` 中删除。

因为要求 $Y_j\le Y_i$，所以优先流 $Y$ 最大的警卫不劣。每个警卫每次被枚举到时，要么满流被删除，要么因为手办剩余流量不足而被保留。两种情况分别总计发生 $\mathcal O(m),\mathcal O(n)$ 次，因此总复杂度 $\mathcal O((n+m)\log m)$。

根据这个贪心的最优性，无需考虑退流。注意值域达到 $2\times 10^{18}$。

```cpp
#include <cstdio>
#include <algorithm>
#include <set>
#define ll long long

using namespace std;

const int N=414514;

enum typ{obj,plc};
struct xzr{ll x,y;int w;typ t;}a[N];

struct pol{ll y;mutable int r;bool operator<(const pol &t)const{return y>t.y;}};
multiset<pol> s;

int main()
{
	int n,m,x,y,v;ll w,h,ans=0;scanf("%d%d%lld%lld",&n,&m,&w,&h);
	for(int i=1;i<=n;++i) scanf("%d%d%d",&x,&y,&v),ans+=v,a[i]=(xzr){x*h+y*w,x*h-y*w,v,obj};
	for(int i=1;i<=m;++i) scanf("%d%d%d",&x,&y,&v),a[i+n]=(xzr){x*h+y*w,x*h-y*w,v,plc};
	n+=m;sort(a+1,a+n+1,[](xzr u,xzr t){return u.x==t.x?u.t>t.t:u.x>t.x;});
	for(int i=1;i<=n;++i) switch(a[i].t){
		case obj:{
			auto p=s.lower_bound((pol){a[i].y,0});
			for(int r=a[i].w,d;r&&p!=s.end();){
				d=min(r,p->r);r-=d;p->r-=d;ans-=d;++p;
				if(!prev(p)->r) s.erase(prev(p));
			}break;
		}
		case plc:s.insert((pol){a[i].y,a[i].w});break;
	}
	printf("%lld",ans);
}

---

## 作者：Ethan_gong (赞：1)

# 分析
不难看出一个最大权闭合子图的模型，然而直接求最大流显然过不了，于是可以考虑模拟最大流。

首先把这个坐标系变换一下。如果警卫  能看到手办 ，则应有
$$
-\frac{w}{h}\leq \frac{x_a-x_b}{y_a-y_b}\leq\frac{w}{h}
$$
推一推可以得到
$$
\begin{cases}
h\times x_a-w\times y_a\leq h\times x_b-w\times y_b\\
h\times x_a+w\times y_a\geq h\times x_b+w\times y_b
\end{cases}
$$
于是可以把 $(h\times x+w\times y,h\times x-w\times y)$ 作为每个点的坐标，这样子警卫 $a$ 能看到手办 $b$ 当且仅当 $x_b\leq x_a,y_a\leq y_b$。

考虑把所有点按照变换后的横坐标从小到大排序，则我们每次只需要考虑纵坐标了。

假设当前扫到了一个警卫，则我们需要流一些流量，贪心地想一想可以发现往纵坐标尽量小的手办流更好，因为纵坐标大的能被更多的警卫看到。

于是只需要开一个 std::multiset 维护一下所有还没流满的手办及其纵坐标，每次二分一下即可。
# 代码

```cpp
#include <bits/stdc++.h>
#define file(x) freopen(#x".in","r",stdin); freopen(#x".out","w",stdout)
#define mp make_pair
using namespace std;
typedef long long ll;

int read() {
    int X=0,w=1; char c=getchar();
    while (c<'0'||c>'9') { if (c=='-') w=-1; c=getchar(); }
    while (c>='0'&&c<='9') X=X*10+c-'0',c=getchar();
    return X*w;
}

const int N=200000+10;

int n,m,w,h;
struct node { ll x,y,w; } a[N],b[N];
bool operator <(node a,node b) { return a.x<b.x; }
multiset<pair<ll,int> > S;

int main() {
    n=read(),m=read(),w=read(),h=read(); ll ans=0;
    for (int i=1;i<=n;++i) {
        ll x=1ll*read()*h,y=1ll*read()*w,c=read();
        a[i]=(node){x+y,x-y,c},ans+=c;
    }
    for (int i=1;i<=m;++i) {
        ll x=1ll*read()*h,y=1ll*read()*w,c=read();
        b[i]=(node){x+y,x-y,c};
    }
    sort(a+1,a+n+1),sort(b+1,b+m+1);
    for (int i=1,j=1;i<=m;++i) {
        while (j<=n&&a[j].x<=b[i].x) S.insert(mp(a[j].y,j)),++j;
        while (b[i].w&&!S.empty()) {
            auto it=S.lower_bound(mp(b[i].y,0));
            if (it==S.end()) break;
            int p=it->second,f=min(a[p].w,b[i].w);
            ans-=f,a[p].w-=f,b[i].w-=f;
            if (!a[p].w) S.erase(it);
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```
求过QAQ

---

## 作者：Pink_Dove (赞：0)

[更好吃的食用体验](https://yumomeow.github.io/2025/03/16/solution-LuoguP5996/)

### 题解
首先可以想到一个很显然的最大权闭合子图做法，连边 $(s,i,v_i)$ 表示贿赂第 $i$ 个警卫的代价，连边 $(j,t,v_j)$ 表示不拿第 $j$ 个手办的代价，警卫向能看到的手办连权值为 $\infty$ 的边，用手办价值和减去最小割即为答案。但是本题数据范围过大，无法直接求最小割，考虑**模拟最大流**。

首先考虑转换题目中给的坐标形式。对于警卫 $i$ 和手办 $j$，仅当
$$
|\frac{x_i-x_j}{y_i-y_j}|\le \frac{w}{h}
$$
手办才能被看到。上式等价于
$$
x_ih-y_iw\le x_jh-y_jw\\
x_ih+y_iw\ge x_jh+y_jw
$$
令 $x=xh+yw,y=xh-yw$，限制就可以转化为 $x_i\ge x_j,y_i\le y_j$。

这样我们就可以用扫描线求解，用 set 维护手办的坐标和剩余流量，从左往右扫描求最大流。对每个警卫**贪心地取 $y$ 最小的手办的流量**直到警卫和 $t$ 之间的边流满或找不到满足的手办，因为更大的 $y$ 可以被更多的警卫取到。这里我们直接二分查找满足条件的手办。

### 代码
```cpp
#include<iostream>
#include<algorithm>
#include<set>
#define int long long
#define pii pair<int,int>
using namespace std;
const int N=2e5+10;
int n,m,w,h,sum;
struct Node{
	int x,y,v;
	bool operator < (const Node &t) const{return x<t.x;}
}a[N],b[N];
multiset<pii> s;
signed main(){
	cin>>n>>m>>w>>h;
	for(int i=1,x,y;i<=n;i++){
		cin>>x>>y>>a[i].v;
		a[i].x=x*h+y*w,a[i].y=x*h-y*w;//转换坐标
		sum+=a[i].v;
	}
	for(int i=1,x,y;i<=m;i++){
		cin>>x>>y>>b[i].v;
		b[i].x=x*h+y*w,b[i].y=x*h-y*w;
	}	
    //扫描线
	sort(a+1,a+n+1);sort(b+1,b+m+1);
	for(int i=1,j=1;i<=m;i++){
		while(j<=n&&a[j].x<=b[i].x) s.insert({a[j].y,a[j++].v});//将手办加入
		int limit=b[i].v;
		while(limit&&s.size()){
			auto it=s.lower_bound({b[i].y,0});//二分
			if(it==s.end()) break;
			pii u=*it;s.erase(it);
			int flow=min(limit,u.second);
			sum-=flow;u.second-=flow;limit-=flow;//增广流量
			if(u.second) s.insert(u);//手办没被榨干，则再次加入 set
		}
	}
	cout<<sum;
	return 0;
}
```

---

