# Travelling Through the Snow Queen's Kingdom

## 题目描述

Gerda is travelling to the palace of the Snow Queen.

The road network consists of $ n $ intersections and $ m $ bidirectional roads. Roads are numbered from $ 1 $ to $ m $ . Snow Queen put a powerful spell on the roads to change the weather conditions there. Now, if Gerda steps on the road $ i $ at the moment of time less or equal to $ i $ , she will leave the road exactly at the moment $ i $ . In case she steps on the road $ i $ at the moment of time greater than $ i $ , she stays there forever.

Gerda starts at the moment of time $ l $ at the intersection number $ s $ and goes to the palace of the Snow Queen, located at the intersection number $ t $ . Moreover, she has to be there at the moment $ r $ (or earlier), before the arrival of the Queen.

Given the description of the road network, determine for $ q $ queries $ l_{i} $ , $ r_{i} $ , $ s_{i} $ and $ t_{i} $ if it's possible for Gerda to get to the palace on time.

## 样例 #1

### 输入

```
5 4 6
1 2
2 3
3 4
3 5
1 3 1 4
1 3 2 4
1 4 4 5
1 4 4 1
2 3 1 4
2 2 2 3
```

### 输出

```
Yes
Yes
Yes
No
No
Yes
```

# 题解

## 作者：FxorG (赞：5)

我们可以发现 $s->t$ 这条路径所经过的边的编号单增（且每条边的边号都是大于等于 $l$），假如不单增那么分界点后的边都不通。

那么，**题目中的走一条边花费 1 就是废的**。

对于一个询问，我们只需要把编号大于等于 $l$ 的拉出去跑最短路即可。

考虑在线过不去，有点 **图函数** 的意思。

离线询问，从大编号到小编号加入边，询问按 $l$ 降序排。

考虑加入这条边对最短路的影响。

首先，这条边所经过的时间一定是当前全局最小的。那么一定是 $from\to to\to i$ 或 $to\to from \to j$的形式（根据单增结论），考虑类 floyd 松弛即可。

需要注意的是，松弛的起点都必须是 $from \ or \  to$，能保证一定经过 $from\to to$

![](https://cdn.luogu.com.cn/upload/image_hosting/1bseseut.png)

途中绿色和蓝色即为路径，保证一定经过新边。

```cpp
#include <bits/stdc++.h>
using namespace std;
int rd() {
    int f=1,sum=0; char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-') f=-1; ch=getchar();}
    while(isdigit(ch)) {sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
    return sum*f;
}
void pr(int x) {
	int f=1,tot=0; static int st[30];
	if(x<0) x=-x,f=-1;
	while(x) st[++tot]=x%10,x/=10;
	if(!tot) putchar('0');
	else for(int i=tot;i>=1;i--) putchar(st[i]+'0');
}

#define N 1005
#define M (int)(2e5+5)
struct edge {
	int l,r,s,t,id;
}Q[M];
bool ans[M];
int fr[M],to[M];
int n,m,q,f[N][N];

bool cmp(edge x,edge y) {
	return x.l>y.l;
}

int main() {
	n=rd(); m=rd(); q=rd();
	for(int i=1;i<=m;i++) fr[i]=rd(),to[i]=rd();
	for(int i=1;i<=q;i++) {
		Q[i].l=rd(); Q[i].r=rd(); Q[i].s=rd(); Q[i].t=rd(); Q[i].id=i;
	}
	sort(Q+1,Q+1+q,cmp); int nw=1;
	memset(f,0x3f,sizeof(f));
	for(int i=m;i>=1;i--) {
		f[fr[i]][to[i]]=f[to[i]][fr[i]]=i;
		for(int j=1;j<=n;j++) {
			f[to[i]][j]=min(f[to[i]][j],f[fr[i]][j]);
			f[fr[i]][j]=min(f[fr[i]][j],f[to[i]][j]);
		}
		while(nw<=q&&Q[nw].l==i) {
			if(f[Q[nw].s][Q[nw].t]<=Q[nw].r) ans[Q[nw].id]=1;
			++nw;
		} 
	}
	for(int i=1;i<=q;i++) {
		if(ans[i]) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
```

---

## 作者：Kreado (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF685E)。

## 思路

我们发现如果能在 $l$ 时刻从 $s$ 在 $r$ 时刻之前走到 $t$ 当且仅当我们走过的路径的边编号集合单调递增而且路径上经过的最小的边的编号大于等于 $l$，经过最大的边的编号小于等于 $r$。

每次询问也就是把编号大于 $l$ 的边拿出来跑一遍最短路，最后看一下总的用时是否小于等于 $r$，这样我们每次询问遍历一下该图就能得到一个时间复杂度 $O(q(n+m))$ 的做法。

当然这样我们是肯定不能过的，但是我们发现 $n$ 很小，$q,m$ 很大，考虑离线做。

对于一个询问，我们只关注图中编号大于等于 $l$ 的，我们不妨将每个询问按照 $l$ 降序排，每次从大到小加入一条新边。

加入这条新边，我们考虑这条新边对当前最短路的影响。

我们设 $dis_{i,j}$ 表示**当前** $i$ 到 $j$ 的最短路，现在我们要加入边 $(u,v,i)$，$dis_{x,y},(x,y\in\mathbb{Z})$ 会被更新当且仅当 $x=u$ 或 $ x=v$。

我们使用类 Floyd 最短路的思想，将这条边中间加入一个节点 $j$ 进行松弛操作。

松弛完之后，当前的一定是最短路。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define nxt k=min(f[u[i]][j],f[v[i]][j])
using namespace std;
const int Maxn=2e5+7;
int n,m,Q;
int u[Maxn],v[Maxn],ans[Maxn];
int f[1010][1010];
struct ques{
	int l,r,s,t,id;
}q[Maxn]; 
int main(){
	scanf("%d%d%d",&n,&m,&Q);
	for(int i=1;i<=m;i++) scanf("%d%d",&u[i],&v[i]);
	for(int i=1;i<=Q;i++) scanf("%d%d%d%d",&q[i].l,&q[i].r,&q[i].s,&q[i].t),q[i].id=i;
	sort(q+1,q+Q+1,[](const ques x,const ques y){return x.l>y.l;});
	memset(f,0x3f,sizeof f);
	int now=1;
	for(int i=m;i;i--){
		f[u[i]][v[i]]=f[v[i]][u[i]]=i;
		for(int j=1,nxt;j<=n;j++,nxt) f[u[i]][j]=f[v[i]][j]=k;
		while(now<=Q&&q[now].l==i){
			if(f[q[now].s][q[now].t]<=q[now].r) ans[q[now].id]=1;
			now++;
		}
	}
	for(int i=1;i<=Q;i++)
		printf("%s\n",ans[i]?"Yes":"No");
	return 0; 
}



```


---

## 作者：xzggzh1 (赞：3)

题意：

给你一张图，每一条边都有一个编号 $i$ ，经过每条边的时间为 $1$ ，如果当你到达这条边的时间小于 $i$ 的话，就必须等到i才能走出这条边，如果大于 $i$ ，就走不出去了，也就是不通了。然后给你一些询问 $l$ , $r$ , $s$ , $t$ ，问你是否可以从 $s$ 出发，时间为 $l$，在 $r$ 时间之前到达 $t$ 。

---

注意到 $n \leq 1000 \ , m\leq 200000$ ，我们直接考虑 $O(n*m)$ 的算法。

首先考虑只有一个询问，那么直接把编号大于某个值的边取出再类似地跑一边“最短路”，看最后的时间是否小于 $r$。

但是现在有许多询问，对于每一个询问重新建图显然时间上无法满足题目的要求，那么我们可以容易得想到：离线处理每一个询问，将询问的 $l$ 按照降序排列，同时每一次取出编号最大的边加入，并更新“距离”（最小所需时间），这样就可以轻易处理出所有询问。

至于如何加入边并同时维护距离，我们先记录每两个点之间的“距离”，每次加边并对每个点到这条边的端点进行松弛操作。

这样总的时间复杂度为 $O(n*m)$ 。

---

代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=1e3+5;
const int Maxm=2e5+5;
inline int R(){char c;int res,sign=1;while((c=getchar())>'9'||c<'0') if(c=='-') sign=-1;res=c-'0';while((c=getchar())>='0'&&c<='9') res=res*10+c-'0';return res*sign;}
struct query
{
	int l,r,s,t,num,ans;
}a[Maxm];
inline bool cmp(query x,query y)
{
	return x.l>y.l;
}
inline bool Cmp(query x,query y)
{
	return x.num<y.num;
}
int n,m,q,st[Maxm],to[Maxm],dp[Maxn][Maxn];//dp[i][j]表示i到j至少的时间 
int main()
{
	n=R();m=R();q=R();
	for(int i=1;i<=m;i++)
	{
		st[i]=R();to[i]=R();
	}
	for(int i=1;i<=q;i++)
	{
		a[i].l=R();a[i].r=R();
		a[i].s=R();a[i].t=R();
		a[i].num=i;
	}
	sort(a+1,a+1+q,cmp);
	int now=1;
	memset(dp,0x3f,sizeof dp);
	for(int i=m;i>0;i--)
	{
		dp[st[i]][to[i]]=dp[to[i]][st[i]]=i;
		for(int j=1;j<=n;j++)
		{
			dp[to[i]][j]=min(dp[st[i]][j],dp[to[i]][j]);
			dp[st[i]][j]=min(dp[to[i]][j],dp[st[i]][j]);
		}
		while (now<=q&&a[now].l>=i)
		{
			a[now].ans=dp[a[now].s][a[now].t]<=a[now].r?1:0;
			++now;
		}
	}
	sort(a+1,a+1+q,Cmp);
	for(int i=1;i<=q;i++)
		puts(a[i].ans?"Yes":"No");
}

```

---

## 作者：zifanwang (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF685E)

一道 CF~~2800~~2000。

考虑离线，倒着加入每条边。

记 $f_{i,j}$ 表示点 $i$ 为起点，点 $j$ 为终点时路径上最后一条边的编号的最小值。由于每次加入的边 $(x,y)$ 的编号是当前边集内最小的，只需要更新所有的 $f_{x,i}$ 和 $f_{y,i}$，更新显然。单次更新的时间复杂度是 $O(n)$，每个询问是 $O(1)$ 判断的，总时间复杂度 $O(mn+q)$。

参考代码：
```cpp
#include<bits/stdc++.h>
#define mxn 200003
#define pb push_back
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define drep(i,a,b) for(int i=a;i>=b;--i)
using namespace std;
struct node{
	int x,y;
}a[mxn];
struct ask{
	int r,s,t,i;
};
int n,m,q,f[1002][1002];
bool ans[mxn];
vector<ask>d[mxn];
signed main(){
	scanf("%d%d%d",&n,&m,&q);
	rep(i,1,m)scanf("%d%d",&a[i].x,&a[i].y);
	memset(f,0x3f,sizeof(f)); 
	int l,r,s,t;
	rep(i,1,q){
		scanf("%d%d%d%d",&l,&r,&s,&t);
		d[l].pb({r,s,t,i});
	}
	drep(i,m,1){
		int x=a[i].x,y=a[i].y;
		f[x][y]=min(f[x][y],i);
		rep(j,1,n)f[x][j]=min(f[x][j],f[y][j]);
		f[y][x]=min(f[y][x],i);
		rep(j,1,n)f[y][j]=min(f[y][j],f[x][j]);
		for(ask j:d[i])ans[j.i]=f[j.s][j.t]<=j.r;
	}
	rep(i,1,q)puts(ans[i]?"Yes":"No");
	return 0;
}
```

---

## 作者：L_zaa_L (赞：2)

## 分析
对于每次询问，我们实际上就是询问 $u$ 到 $v$ 中只经过 $l$ 到 $r$ 的边是否能够通过。

然后可以发现我们经过第 $i$ 条边一定是在第 $i$ 个时刻的，这样我们就不难发现这个路径是单调上升的。

那么其实我们每一次处理询问的时候对于小于 $l_i$ 的边我们是可以直接不用计算的。那么我们可以考虑直接从大到小加边。这样我们考虑换一个角度考虑，将删变变为从编号大的边开始想图中加边，同时我们用新加的这条边对于先前有的边进行一个更新就行。

但我们怎么进行更新呢？

我们可以先记录每两个点之间的距离，每次加边并对每个点到这条边的端点进行松弛操作，就像 Floyd 一样。但是因为每次只需要松弛两个点，所以时间复杂度只需要 $O(n)$ 来松弛。

最后询问需要离线，然后根据左端点从大到小判断是否在区间内即可。

时间总复杂度：$O(nm)$。

## Code
```cpp
#include<bits/stdc++.h> 
#define int long long
using namespace std;
int n,m,k;
int u[300005],v[300005];
int nw=1;
int f[2005][2005];
int ans[3000005];
struct XXX{
	int l,r,s,t,id;	
}qu[3000005];
bool cmp(XXX a,XXX b){
	return a.l>b.l;	
}
signed main() {
	//freopen("journey.in","r",stdin);
	//freopen("journey.out","w",stdout);
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1;i<=m;++i){
		scanf("%lld%lld",&u[i],&v[i]);
	}
	for(int i=1;i<=k;i++){
		scanf("%lld%lld%lld%lld",&qu[i].l,&qu[i].r,&qu[i].s,&qu[i].t);
		qu[i].id=i;
	}
	sort(qu+1,qu+k+1,cmp);
	memset(f,0x3f3f,sizeof(f));
	for(int i=m;i>=1;i--) {
		f[u[i]][v[i]]=f[v[i]][u[i]]=i;
		for(int j=1;j<=n;j++)
			f[u[i]][j]=f[v[i]][j]=min(f[v[i]][j],f[u[i]][j]);//将加进来的边左右端点进行松弛
		while(nw<=k&&qu[nw].l==i) {
			if(f[qu[nw].s][qu[nw].t]<=qu[nw].r||qu[nw].s==qu[nw].t) ans[qu[nw].id]=1;
			++nw;//判断是否在这个区间内
		} 
	}
	for(int i=1;i<=k;i++)
		puts(((ans[i]==1)?"Yes":"No"));

	return 0;
}

```

---

## 作者：OIerBoy (赞：2)

# Sol
这道题有一个很有意思的地方，就是我们经过第 $i$ 条边一定是在第 $i$ 个时刻的，这样我们就不难发现这个路径是单调上升的。所以走一条边花费 $1$ 根本没有用。

那么其实我们每一次处理询问的时候对于 $<l_i$ 的边我们是可以直接不用计算的，就相当于是把 $<l_i$ 的边删掉一样。这样我们考虑换一个角度，我们从编号大的边开始想图中加边，同时我们用新加的这条边对于先前有的边进行一个更新就行 Floyd 一样。这样也可以达到相同的效果。

这样我们只需要把 $q$ 次询问离线下来，当加到第 $l_i$ 时再更新答案即可。
# Code
```cpp
#include<bits/stdc++.h>
#define inf LONG_LONG_MAX
#define fir first
#define sec second
#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((l+r)>>1)
#define Pr(i,j) pair<i,j>
#define PB(i) push_back(i)
#define MP(i,j) make_pair(i,j)
#define Fo(i,j) for(auto i:j)
#define mem(i,j) memset(i,j,sizeof(i))
#define FO(i,j,k) for(int i=j;i;i=k)
#define FFF(i,j,k) for(auto i=j;i!=k;++i)
#define For(i,j,k) for(int i=j;i<=k;++i)
#define FoR(i,j,k) for(int i=j;i^k;++i)
#define FOR(i,j,k) for(int i=j;i>=k;--i)
using namespace std;
template <typename _Tp>void read(_Tp& first) {
    _Tp x = 0, f = 1; char c = getchar();
    while (!isdigit(c)) {if (c == '-') f = -1; c = getchar();}
    while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ '0'), c = getchar();
    first = x * f;
}inline void write(int x){
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
#define N 1005
#define M 1000005
#define Mod 998244353
#define int long long
struct Edge{
	int u,v;
}e[M];
struct Query{
	int l,r,s,t,i;
}q[M];
int n,m,Q,tot=1,ans[M],f[N][N];
bool cmp(Query a,Query b){return a.l>b.l;}
signed main(){
//	freopen("journey2.in","r",stdin);
//	freopen("journey.out","w",stdout);
	mem(f,0x7f);
	read(n),read(m),read(Q);
	For(i,1,m)read(e[i].u),read(e[i].v);
	For(i,1,Q){
		read(q[i].l),read(q[i].r);
		read(q[i].s),read(q[i].t);
		q[i].i=i;
	}sort(q+1,q+1+Q,cmp);
	FOR(i,m,1){
		int u=e[i].u,v=e[i].v;
		f[u][v]=i;f[v][u]=i;
		For(j,1,n){
			f[v][j]=f[u][j]=min(f[v][j],f[u][j]);
		}while(q[tot].l==i&&tot<=Q){
			if(f[q[tot].s][q[tot].t]<=q[tot].r&&q[now].s!=q[now].t)ans[q[tot].i]=1;
			tot++;
		}
	}For(i,1,Q){
		if(ans[i])puts("Yes");
		else puts("No");
	}
    return 0;
}

```

---

## 作者：max0810 (赞：1)

吐槽一下，为啥这道题 $\mathcal{O}(nm)$ 可以过。联考的时候做到了这道题，还一直在想更快的算法。。。

然后，这联考的数据是自己出的，有 $s=t$ 的情况，我反正是完全没有想到，又因为是捆绑测试，直接痛失 $100pts$。

---

首先考虑转化一下题目。对于一个询问 $l,r,s,t$，就相当于是让你从第 $l$ 到 $r$ 条边中选出一些边，使得**依次**按这些边走可以从 $s$ 到 $t$。

先考虑只有这一个询问的情况。我们可以令数组 $a_{i,j}$ 表示 $i$ 能否到达 $j$，然后按顺序枚举第 $l$ 到 $r$ 条边。设现在这条边是 $u,v$，考虑应该更新哪些值。可以发现如果有一个点 $x$ 能到达 $u$，那么将 $u,v$ 这条边加进来之后 $x$ 就也能到达 $v$ 了。所以如果 $a_{x,u}=1$ 或 $a_{x,v}=1$，那么就应该更新 $a_{x,v}=1$ 或 $a_{x,u}=1$，简化一下就是对于所有 $1\le x\le n$，$a_{x,u} = a_{x,v} = a_{x,u}|a_{x,v}$。

现在是多组询问，我们可以将询问按 $r$ 排一遍序，然后还是依次枚举每一条边，每次更新所有 $r$ 为当前边的询问。

但是每个询问还有 $l$ 的限制，所以 $a$ 数组就不能只单纯地记 $0$ 和 $1$ 了，而应该记一个数 $x$。$a_{i,j}=x$ 就表示从 $i$ 到 $j$ 的所有路径中第一条边编号最大能是多少，这样子如果 $a_{s,t}\ge l$，那就说明询问是可以做到的，而转移的时候只需要把 $a_{x,u}|a_{x,v}$ 改成 $\max({a_{x,u},a_{x,v}})$ 即可。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 1005,M = 2e5+5,Q = 1e6+5;
int a[N][N],e[M][2],n,m,q;
bool ans[Q];
struct node{int l,r,s,t,id;}que[Q];
bool cmp(node x,node y){return x.r < y.r;}
inline int rd()
{
    char c;int f = 1;
    while(!isdigit(c = getchar()))if(c=='-')f = -1;
    int x = c-'0';
    while(isdigit(c = getchar()))x = x*10+(c^48);
    return x*f;
}
int main()
{
	n = rd();m = rd();q = rd();
	for(int i = 1;i <= m;i++)
		e[i][0] = rd(),e[i][1] = rd();
	for(int i = 1;i <= q;i++)
		que[i] = {rd(),rd(),rd(),rd(),i};
	sort(que+1,que+q+1,cmp);int now = 1;
	for(int i = 1;i <= m;i++)
	{
		int u = e[i][0],v = e[i][1];
		a[u][u] = i;a[v][v] = i;
		for(int j = 1;j <= n;j++)
			a[j][u] = a[j][v] = max(a[j][u],a[j][v]);
		for(node x;now <= q&&(x = que[now]).r <= i;now++)
			ans[x.id] = a[x.s][x.t] >= x.l;
	}
	for(int i = 1;i <= q;i++)puts(ans[i]?"Yes":"No");
    return 0;
}
```

---

## 作者：木棉絮123 (赞：0)

模拟赛的原题，赛时想到正解~~但没写出来~~，感觉应该是蓝。

------

### 形式化题意

给定一张 $n$ 个点 $m$ 条边的图，第 $i$ 条边将会在第 $i$ 天开放。今有 $q$ 个询问，问你第 $l$ 天由 $s$ 出发，能否在第 $r$ 天**那天及以前**到达 $t$。

### 思路

暴力我相信大家都会写，就不提了。

注意到 $n$ 很小，我们可以设计一个复杂的大概是 $O(nm)$ 或 $O(nq)$ 的算法。对于前者，不难发现有一种对询问按 $l_i$ 由大到小离线的做法，考虑到 $l_i$ 由大到小，每个点到每个点的最晚时间一定是不会变大的。

于是我们倒着加入每条边，因为每次加入的边都是时间最早的边，所以仅需要更新这条边两端的节点到其他节点的最晚时间即可。然后更新该时间下开始的询问。

复杂度是 $O(nm+q)$ 的，可以通过本题。~~大常数选手第一发 TLE 了~~

### 核心片段

```cpp
void solve()
{
	go(i,m,1)
	{
		int x=a[i].first,y=a[i].second;
		f[x][y]=min(f[x][y],i);
    f[y][x]=min(f[y][x],i);
		fo(j,1,n)f[x][j]=min(f[x][j],f[y][j]);//relax
		fo(j,1,n)f[y][j]=min(f[y][j],f[x][j]);
		for(auto v:qu[i])ans[v.id]=f[v.s][v.t]<=v.r;
	}
}
```

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fo(a,b,c) for(int a=b;a<=c;a++)
#define go(a,b,c) for(int a=b;a>=c;a--)
#define debug(x) printf("debug:%d",x)
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int MAX=2e3+5,MAXM=2e5+5;
const int p=1e9+7;
int n,m,q,f[MAX][MAX];
struct query
{
	int r,s,t,id;
};
vector<query>qu[MAXM];
pii a[MAXM];
bool ans[MAXM];
void init()
{
	cin>>n>>m>>q;
	int u,v;
    fo(i,1,m)
    {
		cin>>u>>v;
		a[i]={u,v};
	}
    int l,r,s,t;
	fo(i,1,q)
    {
		cin>>l>>r>>s>>t;
        qu[l].push_back({r,s,t,i});
	}
	memset(f,0x3f,sizeof(f));
}
void solve()
{
	go(i,m,1)
    {
		int u=a[i].first,v=a[i].second;
		f[u][v]=min(f[u][v],i);
		f[v][u]=min(f[v][u],i);
        fo(j,1,n)f[u][j]=min(f[u][j],f[v][j]);//relax
		fo(j,1,n)f[v][j]=min(f[v][j],f[u][j]);
		for(auto v:qu[i])ans[v.id]=f[v.s][v.t]<=v.r;
	}
}
void output()
{
	fo(i,1,q)
		if(ans[i])
			cout<<"Yes"<<'\n';
		else
			cout<<"No"<<'\n';
}
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
//	freopen("plan.in","r",stdin);
//	freopen("plan.out","w",stdout);
	init();
	solve();
	output();
}
```

---

## 作者：daniEl_lElE (赞：0)

考虑离线，倒序插入每一条边。

利用 Floyd 的思路更新。记录 $f_{i,j}$ 表示从目前时刻 $i$ 位置开始走最短多久到 $j$。不难发现当添加一条边 $x\to y$ 的时候，只有 $f_{x,v}$ 会被 $f_{y,v}$ 和 $f_{y,v}$ 会被 $f_{x,v}$ 更新。于是我们其实可以 $O(n)$ 更新，总复杂度就是 $O(nm+q)$，可以通过。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
int d[1005][1005],ans[200005];
struct qry{
	int r,s,t,pos;
};
vector<qry> g[200005];
int u[200005],v[200005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	memset(d,1,sizeof(d));
	int n,m,q; cin>>n>>m>>q;
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i];
	}
	for(int i=1;i<=q;i++){
		int l; cin>>l;
		qry tmp; cin>>tmp.r>>tmp.s>>tmp.t,tmp.pos=i;
		g[l].push_back(tmp);
	}
	for(int i=m;i>=1;i--){
		for(int j=1;j<=n;j++) d[j][j]=i;
		for(int j=1;j<=n;j++) d[u[i]][j]=min(d[u[i]][j],d[v[i]][j]),d[v[i]][j]=min(d[v[i]][j],d[u[i]][j]);
		for(auto v:g[i]){
			if(d[v.s][v.t]<=v.r){
				ans[v.pos]=1;
			}
		}
	}
	for(int i=1;i<=q;i++) cout<<(ans[i]?"Yes":"No")<<"\n";
	return 0;
}
```

---

## 作者：o51gHaboTei1 (赞：0)

**CF685E sol**

水了点。这个怎么 2800 啊。

~~虽然还读错题了（~~

考虑我们最后的路径显然是编号单增的。

一个简单的想法是我们扫描线，倒序加入所有边，维护每个点通过走递增路径走到另一个点最小化的最大编号，定义其为距离。

我们发现每次加入一条边，只需要更新两者之间的距离，显然的是其余点不会过这个路径否则破坏了路径单增的性质。

因为新的转移必须要经过当前边，线性更新两个点到其他点的距离即可。

时间复杂度 $O(nm)$。

```cpp
/*
编号是单增的，所以就相当于问是否存在一条路径编号只在 [l,r] 内。
也相当于保留路径编号在 l , r 内的边是否能联通。
一个显然的做法是根号。
考虑倒序加边，然后有一个巨大的问题就是青蛙是 zx。
此时我们知道编号单调递增，所以其它点是不可能通过这条边的。
可以线性的更新一个从 s -> t 的过程。 
*/
#include "bits/stdc++.h"
using namespace std;
inline int read() {
    char ch = getchar();
    int x = 0, f = 1;
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while ('0' <= ch && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
inline void write(int x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
const int Len = 1e3 + 5 , M = 2e5 + 5 , Inf = 1e9 + 1;
int n,m,q,ds[Len][Len];
struct node
{
	int x,y;
	node(){x = y = 0;}
	node(int X,int Y){x = X , y = Y;}
}ed[M];
struct Q
{
	int l,r,s,t,id;
	Q(){l = r = s = t = 0;}
	Q(int L,int R,int S,int T){l = L , r = R , s = S , t = T;}
	bool operator < (const Q &Ano) const
	{return l > Ano.l;}
}qs[M];
int Print[M];
int main()
{
	n = read() , m = read() , q = read();
	for(int i = 1 ; i <= m ; i ++) ed[i].x = read() , ed[i].y = read();
	for(int i = 1 ; i <= q ; i ++) qs[i].l = read() , qs[i].r = read() , qs[i].s = read() , qs[i].t = read() , qs[i].id = i;
	sort(qs + 1 , qs + 1 + q);
	int idx = 0;
	for(int i = 1 ; i <= n ; i ++)
		for(int j = 1 ; j <= n ; j ++) ds[i][j] = Inf;
	for(int i = m ; i >= 1 ; i --)
	{
		ds[ed[i].x][ed[i].y] = ds[ed[i].y][ed[i].x] = i;
		for(int j = 1 ; j <= n ; j ++) ds[ed[i].x][j] = min(ds[ed[i].x][j] , ds[ed[i].y][j]);
		for(int j = 1 ; j <= n ; j ++) ds[ed[i].y][j] = min(ds[ed[i].y][j] , ds[ed[i].x][j]); 
		while(idx + 1 <= q && qs[idx + 1].l == i)
		{
			idx ++;
			Print[qs[idx].id] = (ds[qs[idx].s][qs[idx].t] <= qs[idx].r);
		}
	}
	for(int i = 1 ; i <= q ; i ++) (Print[i]) ? puts("Yes") : puts("No"); 
	return 0;
}
```

---

## 作者：hfjh (赞：0)

## Travelling Through the Snow Queen's Kingdom

### 题意.

给你一张图，每一条边都有一个编号 $i$，经过每条边的时间为 $1$，如果当你到达这条边的时间小于 $i$ 的话，就必须等到 $i$ 才能走出这条边，如果大于 $i$，就走不出去了，也就是不通了。然后给你一些询问 $l$, $r$, $s$, $t$，问你是否可以从 $s$ 出发，时间为 $l$，在 $r$ 时间之前到达 $t$。

### 题解

将边建立时间轴，倒叙插入边，记录 $d_{s,t}$ 代表从 $s$ 到 $t$ 从当前时间 $i$ 开始到终点的**最早时间**。 

每次更新 $d$ 只需要更新以 $s,t$ 为起点的部分。

如果询问时间 $[q_i,q_j]\in[i,d_{s,t}]$ 那么就是 `Yes`。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10, M = 1e6 + 10, inf = 1e9;
int n, m, Q, now;
int d[N][N];
int ans[M];
struct node{
	int x, y;
}e[M];
struct Node{
	int l, r, s, t;
	int id;
}q[M];
bool cmp(Node a, Node b){
	return a.l > b.l;
}
void input(){
	cin>> n >> m >> Q;
	for(int i = 1; i <= m; ++i){
		cin>> e[i].x >> e[i].y;
	}
	for(int i = 1; i <= Q; ++i){
		cin>> q[i].l >> q[i].r >> q[i].s >> q[i].t;
		q[i].id = i;
	}
	sort(q + 1, q + 1 + Q, cmp);
}
void op(){
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= n; ++j){
			d[i][j] = inf;
		}
	}
	now = 1;
	for(int i = m; i >= 1; --i){
		d[e[i].x][e[i].y] = d[e[i].y][e[i].x] = i;
		for(int j = 1; j <= n; ++j){
			d[e[i].x][j] = d[e[i].y][j] = min(d[e[i].y][j], d[e[i].x][j]);			
		}
		while(q[now].l == i){
			ans[q[now].id] = (bool)(q[now].r >= d[q[now].s][q[now].t] || q[now].s == q[now].t);
			++now;
		}
	}
}
void output(){
	for(int i = 1; i <= Q; ++i){
		if(ans[i]) cout<<"Yes"<<'\n';
		else cout<<"No"<<'\n';
	}
}
int main(){
	cin.tie(0)->sync_with_stdio(false);
	input();
	op();
	output();
	return 0;
} 
```

---

