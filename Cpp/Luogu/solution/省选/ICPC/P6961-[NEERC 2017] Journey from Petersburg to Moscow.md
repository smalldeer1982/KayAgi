# [NEERC 2017] Journey from Petersburg to Moscow

## 题目描述

为了举办世界编程杯 $2112$，在俄罗斯的欧洲部分建造了一张奇妙的收费公路网络。这个网络由 $m$ 条双向道路组成，连接了 $n$ 座城市。每条道路连接恰好两座不同的城市，没有两条道路连接相同的城市对，并且可以仅使用这张公路网络从任何城市到达其他城市。此外，为了简化收费过程，没有两条道路在城市外相交。

每条道路都有一个单独的正费用。通常情况下，如果司机使用这些收费公路进行旅行，在旅程结束时，他将支付等于所使用的所有道路的单个费用之和的总费用。为了增加两座首都之间汽车旅行的受欢迎程度，运营公司 Radishchev Inc 推出了一项特别优惠：从圣彼得堡到莫斯科的旅程只需支付路径上 $k$ 条最贵道路的费用。

正式地，假设某条路径由 $l$ 条道路组成。记 $c_{1}$ 为该路径上最贵的道路的费用，$c_{2}$ 为第二贵的，以此类推。因此，我们有一个序列 $c_{1} \ge c_{2} \ge c_{3} \ge \ldots \ge c_{l}$，表示所选路径上所有道路的单个费用。如果 $l \le k$，则路径太短，司机按通常方式支付所有单个费用之和，即 $\Sigma^{l}_{i=1}c_{i}$。如果 $l > k$，则司机只需支付 $k$ 条最贵道路的费用，即 $\Sigma^{k}_{i=1}c_{i}$。

作为 Radishchev Inc 的首席分析师，你的任务是计算从圣彼得堡到莫斯科的最低可能旅程费用。

## 说明/提示

时间限制：3 秒，内存限制：512 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
6 7 2
1 2 6
2 3 1
2 4 3
2 5 5
3 6 10
4 6 9
5 6 8
```

### 输出

```
14
```

## 样例 #2

### 输入

```
5 5 3
2 1 1
3 2 1
4 3 1
4 5 1
1 5 2
```

### 输出

```
2
```

# 题解

## 作者：Youth518 (赞：9)

### 分析：

前排先 **stO** 一下题面里的 $\color{black}{K}\color{red}{arry5307}$

对于这个题来说，我们发现没有办法直接找到每条路径第 $k$ 大的边是谁，所以我们考虑直接钦定每一条边是第 $k$ 大的情况

假设我们钦定一条边权为 $w$ 的边为第 $k$ 大的边，那么所有小于 $w$ 的边边权变为 $0$ ,大于等于 $w$ 的边权变为 $x-w$ ，这样跑完最短路后的代价就是 $ans=dis_n+k*w$ 

但是我们发现，这样做的话可能存在三种情况

1. $w$ 恰好为此时最短路上第 $k$ 大的边，不影响

2. $w$ 为此时最短路上小于第 $k'\ (k'<k)$ 大的边，那么我们求得的答案一定大于实际情况

    证明：因为这种情况下，我们得到的答案等价于将第 $1$ 大到第 $k'$ 大边的边权不变，但第 $k'+1$ 到第 $k$ 大的边的边权变大为 $w$ ,所以答案偏大

3. $w$ 为此时最短路上大于第 $k'\ (k'>k)$ 大的边，那么我们求得的答案还是大于实际情况的，因为有一些原本该变成 $0$ 的边没有变成 $0$ 

由此看来我们枚举边得到的答案是**不小于实际答案**的，那么我们只需要钦定每一条边，然后对所有的答案取最小值那么一定会得到恰好第 $k$ 大的情况，复杂度 $O(m^2\log )$

**tip：** 

可能存在一种情况就是不钦定任何边的情况下，原图的最短路小于 $k$ 条边，那么这种情况直接是最优解，因为至少需要付前 $k$ 条边的费用，所以最后的答案还要和这种情况也取一下 $\min$

### 代码：

~~~cpp
#include<bits/stdc++.h>
#define inl inline
#define reg register
#define pll pair<long long,long long>
#define mk(x,y) make_pair(x,y)
#define fir first
#define sec second

using namespace std;

namespace zzc
{
    typedef long long ll;
    inl ll read()
    {
        ll x=0,f=1;char ch=getchar();
        while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
        while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
        return x*f;
    }

    const ll maxn = 3005;
    const ll inf = 0x3f3f3f3f3f3f3f3f;
    ll n,m,k,cnt,ans;
    ll head[maxn],dis[maxn];
    bool vis[maxn];
    priority_queue<pll> q;

    struct edge
    {
        ll to,nxt,w;
    }e[maxn<<1];

    inl void add(ll u,ll v,ll w)
    {
        e[++cnt].to=v;
        e[cnt].w=w;
        e[cnt].nxt=head[u];
        head[u]=cnt;
    }
    
    inl void dijkstra(ll x)//x 表示我们钦定的第 k 大的边的边权
    {
        memset(dis,0x3f,sizeof(dis));
        memset(vis,false,sizeof(vis));
        dis[1]=0;q.push(mk(0,1));
        while(!q.empty())
        {
            ll u=q.top().sec;q.pop();
            if(vis[u]) continue;
            vis[u]=true;
            for(reg ll i=head[u];i;i=e[i].nxt)
            {
                ll v=e[i].to;
                ll w=max(0ll,e[i].w-x);//记得要和 0 取 max
                if(dis[v]>dis[u]+w)
                {
                    dis[v]=dis[u]+w;
                    q.push(mk(-dis[v],v));
                }
            }
        }
         
    }

    void work()
    {
        ll a,b,c;
        n=read();m=read();k=read();
        for(reg ll i=1;i<=m;i++)
        {
            a=read();b=read();c=read();
            add(a,b,c);add(b,a,c);
        }
        dijkstra(0);ans=dis[n];//tip 里提到的情况
        for(ll i=1;i<=(m<<1);i+=2)
        {
            dijkstra(e[i].w);
            ans=min(ans,dis[n]+k*e[i].w);
        }
        printf("%lld\n",ans);
    }


}

int main()
{
    zzc::work();
    return 0;
}
~~~



---

## 作者：whhsteven (赞：3)

试着将现存这篇题解的做法讲得更清楚些。

&nbsp;

尝试枚举每一条边，钦定其为答案路径上的第 $k$ 长的边，记其边权为 $w_0$。将权值 $w < w_0$ 的边的权值都看成 $0$，将权值 $w \ge w_0$ 的边的权值看成 $w - w_0$，然后跑最短路，取 $\mathrm{dis}_n + kw_0$ 为这次钦定的答案。

考察这个答案和实际答案的关系。

- 若 $w_0$ 正好等于当前某条最短路上的第 $k$ 大边权，则当前答案大于等于实际答案；

- 若 $w_0$ 大于当前某条最短路上的第 $k$ 大边权，则当前答案还是大于等于实际答案。这是因为：在当前最短路上，存在若干条边（可以是 $0$ 条）本应贡献的小于 $w_0$ 的边权被放大成了 $w_0$；

- 若 $w_0$ 小于当前某条最短路上的第 $k$ 大边权，则当前答案同样大于等于实际答案。这是因为：在当前最短路上，存在若干条边（可以是 $0$ 条）本不应对最短路长度贡献却实际上产生了贡献。

由此可见，每次钦定出来的答案都是大于等于实际答案的。

还可以看到，只要存在一条答案路径边数不小于 $k$，答案路径上的第 $k$ 长边就是客观存在的，所以我们一定会至少一次枚举到，并且在这时就一定得到了正确答案。

不过还要注意一个事实：有可能所有的答案路径边数都不足 $k$。可以发现这时按照上面的方式不能得到正确答案。

当所有的答案路径边数都不足 $k$ 时，按题意显然有答案路径上每一条边对最短路答案的贡献都是其原始边权。所以我们不钦定任何边，直接在原图上跑最短路，就得到了这种情况的正确答案。

易见，在不是这种情况时，原图最短路一定不短于实际答案。

实现时，我们只需要把所有钦定答案和直接在原图上跑出来的最短路取最小值，即可一定得到正确答案。

&nbsp;

这道题的难点在于想到枚举一条边钦定其边权为路径上第 $k$ 大边权这样的操作，以及这样操作后的处理方式及其正确性。

---

## 作者：covonant (赞：2)

先看数据范围，$2\leq n\leq 3000,1\leq m\leq 3000$，考虑枚举每一条边，让它是最短路上的第 $k$ 大的边(当然，如果不在最短路上，则对答案没有影响)，并把边权大于等于 $w_k$ 的边边权减掉 $w_k$，小于则直接设置为 $0$，此时贡献为 $dis_n+k\times w_k$。此时，会存在 $3$ 种情况 ：

- 若这条边刚好是实际的最短路上的第 $k$ 大边，则不会对答案产生影响，若最短路存在第 $k$ 大的边，**则此种情况一定存在**。
- 若这条边比实际的最短路上的第 $k$ 大边要大，则会有一些边权不该变为 $0$ 的边的边权变为 $0$。此时的答案偏大。
- 若这条边比实际的最短路上的第 $k$ 大边要小，则会有一些边权原本小于 $w_k$ 的边，贡献相当于 $w_k$。此时的答案仍偏大。

综上，只需枚举每一条边，跑最短路，同时记录贡献最小值，便能得到答案。注意，若最短路的长度不足 $k$，此时贡献则为原图的最短路。总时间复杂度 $O(m^2\log m)$。

code:

```cpp
#include<bits/stdc++.h>
#define LL long long
#define maxn 30005
#define maxm 60005
using namespace std;
LL n,m,k;
LL ans=1e17;
LL h[maxn],vis[maxn];
LL dis[maxn];
LL to[maxm],nxt[maxm],w[maxm],cnt;
priority_queue<pair<LL,LL> >q;
void addedge(LL a,LL b,LL c){
	//链式前向星  
	to[++cnt]=b;
	w[cnt]=c;
	nxt[cnt]=h[a];
	h[a]=cnt;
}
LL dijkstra(LL x){
	memset(dis,0x7f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	dis[1]=0;
	q.push({0,1});
	while(!q.empty()){
		LL u=q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(LL i=h[u];i;i=nxt[i]){
			LL t=to[i];
			LL v=max(0ll,w[i]-x);
			if(dis[t]>dis[u]+v){
				dis[t]=dis[u]+v;
				q.push({-dis[t],t});
			}
		}
	}
	return dis[n]+k*x;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m>>k;
	for(LL i=1;i<=m;i++){
		LL x,y,z;
		cin>>x>>y>>z;
		//双向边 
		addedge(x,y,z);
		addedge(y,x,z); 
	}
	for(LL i=0;i<=m*2;i+=2){//注意这里！
		//尝试将第 i 条边设置为第k大的边
		ans=min(ans,dijkstra(w[i])); 
	}
	cout<<ans<<"\n";
	return 0;
}

```

---

## 作者：yuxuzhehuan (赞：1)

# [P6961](https://www.luogu.com.cn/problem/P6961)
## Step1 暴力枚举
直接求出每条路径第 $k$ 大边是比较麻烦的，所以可以假设其中一条边是第 $k$ 大边，边权为 $w$，那么可以先将边权小于 $w$ 的变成 $0$，边权大于等于 $w$ 的减小 $w$，即将边权为 $t$ 变为 $\max(0,t-w)$，然后求出 $1$ 与 $n$ 的最短路，而 $a=dis_n+k \times w$。最后枚举每一条边下的 $a$,答案为 $\min(a)$。

这样做可能会有以下 $3$ 种情况。

- $w$ 恰好为此时最短路上的第 $k$ 大边边权,无影响。
- $w$ 比此时最短路上的第 $k$ 大边边权小，这样会使本该变成 $0$ 的边未变成 $0$，答案会偏大。
- $w$ 比此时最短路上的第 $k$ 大边边权大，这样会使本来边权小于 $w$ 的边的贡献变成 $w$。

因此，$a$ 一定不小于真实答案，且在 $\min(a)$ 一定是真实答案。

代码如下。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int _=3003;
int n,m,l,u,v;
ll W,w,dis[_],ans;
set<ll>s;
struct edge
{	int v;
	ll w;
	bool operator<(const edge &o)const{	return w>o.w;}
}	;
vector<edge>e[_];
priority_queue<edge>q;
inline void dij(ll x)
{	for(int i=2;i<=n;i++)	dis[i]=1e18;
	q.push({1,dis[1]=0});
	while(!q.empty())
	{	u=q.top().v,w=q.top().w,q.pop();
		if(dis[u]!=w)	continue;
		for(auto t:e[u])	if(dis[t.v]>w+(W=max(0ll,t.w-x)))	q.push({t.v,dis[t.v]=w+W});
	}
}
signed main()
{	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>l;
	for(int i=1;i<=m;i++)	cin>>u>>v>>w,e[u].push_back({v,w}),e[v].push_back({u,w}),s.insert(w);
	dij(0),ans=dis[n];
	for(auto w:s)	dij(w),ans=min(ans,dis[n]+l*w);
	cout<<ans;
	return 0;
}
```
时间复杂度为 $O(m^2\log m)$。
## Step2 二分
对于求值函数而言，仔细观察后会发现这类似于开口向上的二次函数，而答案便是其最小值值。因此我们可以用类似二分的方法求出最小值。实现如下。


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int _=3003;
int n,m,l,u,v,sl,L,R,M;
ll W,w,dis[_],ans,s[_],a,b,c,A[_];
struct edge
{	int v;
	ll w;
	bool operator<(const edge &o)const{	return w>o.w;}
}	;
vector<edge>e[_];
priority_queue<edge>q;
inline ll dij(int p)
{	ll x=s[p];
	if(A[p])	return A[p];
	for(int i=1;i<=n;i++)	dis[i]=1e18;
	q.push({1,dis[1]=0});
	while(!q.empty())
	{	u=q.top().v,w=q.top().w,q.pop();
		if(dis[u]!=w)	continue;
		for(auto t:e[u])	if(dis[t.v]>w+(W=max(0ll,t.w-x)))	q.push({t.v,dis[t.v]=w+W});
	}
	return A[p]=dis[n]+l*x;
}
signed main()
{	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>l;
	for(int i=1;i<=m;i++)	cin>>u>>v>>w,e[u].push_back({v,w}),e[v].push_back({u,w}),s[i]=w;
	sort(s+1,s+m+1),sl=unique(s+1,s+m+1)-s-1,ans=dij(0),L=1,R=sl,s[0]=s[sl+1]=1e9+9;
	while(L<=R)
	{	M=(L+R)/2,a=dij(M-1),b=dij(M),c=dij(M+1);
		if(a>=b&&b<=c)	return cout<<min(b,ans),0;
		else if(a<=b&&b<=c)	R=M-1;
		else	L=M+1;
	}
	cout<<ans;
	return 0;
}
```
时间复杂度降到了 $O(m \log^2 m)$，用时 $636$ 毫秒。

## 后记
校内模拟赛时做到了这题，时间限制是 $1$ 秒。结果 std 是用 $O(m^2\log m)$ 的做法做的。导致写正解的值得了 $10$ 分，写部分分的拿了 $30$ 分。

---

## 作者：_jimmywang_ (赞：1)

神奇图论。

我们钦定第 $k$ 大是边 $(u,v,w_0)$，然后把小于 $w_0$ 的边权改写为 0，大于等于 $w_0$ 的边权改写为 $w-w_0$ ，然后跑最短路，答案为 $dis_n+kw_0$。

结论：每个 $dis_n+kw_0$ 一定不小于最终答案且一定会包含最终答案。

包含这个点好说，毕竟最终答案一定会有第 $k$ 大边，那么跑这条边的时候就是最终答案。

那么为什么不小于最终答案？

记改边权后最短路上边权集合为 $W$。如果 $W$ 里的前 $k$ 大中不止一个 0（即没有选够 $k$ 条边权 $\ge w_0$ 的边，“不止一个”是因为 $w_0$ 自己会变成 0），那么把前 $k$ 大的边权加上 $w_0$ 后，会有一些原本 $\le w_0$ 的边权被抬到 $w_0$，因此该答案不小于**更小的 $w_0$** 对应的答案。

相应的，如果 $W$ 里的第 $k$ 大不是 0（即选了超过 $k$ 条边权 $\ge w_0$ 的边），那么把前 $k$ 大的边权加上 $w_0$ 后，会有一些不是前 $k$ 大但是被算进答案的边。因此该答案不小于**更大的 $w_0$** 对应的答案。

证完了。特殊情况是根本选不够 $k$ 条边。此时答案是原图最短路，不难得到改造边权后的答案在选不够 $k$ 条边时不小于原图最短路。于是直接和原图最短路取 $\min$ 即可。

---

## 作者：Xuan_qwq (赞：1)

**题目中的边是双向边。**

发现主要难处理的就是如何确定前 $k$ 大的边。直接枚举肯定不现实，因此我们考虑临界的边，也就是选择哪一条边的权值作为第 $k$ 大的权值。鉴于 $m$ 最大只有 $3000$，枚举边权是可做的。

接下来我们考虑如何确定最优方案。我们发现确定了第 $k$ 大边的权值 $W$ 之后，对于所有权值小于等于 $W$ 的边，边权 $w$ 都变为 $w'=0$。而对于权值大于 $W$ 的边，其边权可以拆分成 $w=w'+W$ 的形式。

将所有 $w'$ 拿出来跑最短路，得到的值再加上 $k\times W$，结果肯定大于等于最优解答案。下面来证明这件事：
- 当选定的边在最短路上时：
  - 若 $W$ 恰好是第 $k$ 大，则显然成立。
  - 若 $W$ 是第 $k'\ (k'>k)$ 大，则取这条最短路第 $k$ 大的边作为我们钦定的第 $k$ 大边，仍然将这条路径作为最短路，那么得到的结果比我们跑出来的结果少了第 $k+1,\dots,k'-1$ 大的边权，显然更优。
  - 若 $W$ 是第 $k'\ (k'<k)$ 大，仍然取这条最短路第 $k$ 大的边作为我们钦定的第 $k$ 大边，还是将这条路径作为最短路，那么得到的结果中第 $k'+1,\dots,k$ 大的边权是小于 $W$ 的，而我们在统计答案时以 $W$ 计算，结果肯定偏大，所以有更优方案。
- 当选定的边不在最短路上时，设路径上第 $k$ 大边权为 $w$：
  - 若 $W>w$，则肯定有边的权值小于 $W$，而我们计算时算作 $W$，结果肯定偏大，所以有更优方案。
  - 若 $W\le w$，则该路径上前 $k$ 大边的边权一定全都计算在答案里，我们得到的结果肯定不小于最优解。

然后要注意判断边数本身就不够 $k$ 的情况，直接把原图的最短路跑一遍就好了

### code
```
#include<bits/stdc++.h>
using namespace std;
#define int long long//偷懒qwq
int n,m,k,ans=1e17;//答案初始设为无穷大
int dis[3005];
bool vis[3005];
struct edge{
	int v,w;
	edge(){}
	edge(int v,int w):v(v),w(w){}
	bool operator < (const edge & B) const {
		return w>B.w;
	}
};
priority_queue<edge>q;
vector<edge>G[3005];
void dij(int x){
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	dis[1]=0;
	q.push(edge(1,0));
	while(q.size()){
		int u=q.top().v;q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i].v,w=max(0ll,G[u][i].w-x);//这里注意不要把边变成负权，不然Dij就跑错了
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				q.push(edge(v,dis[v]));
			}
		}
	}
	ans=min(ans,dis[n]+k*x);//统计答案
}
vector<int>val;
signed main(){
	cin>>n>>m>>k;
	val.push_back(0);//这是原图最短路
	for(int i=1;i<=m;i++){
		int u,v,w;cin>>u>>v>>w;
		G[u].push_back(edge(v,w));
		G[v].push_back(edge(u,w));
		val.push_back(w);
	}
	for(int i=0;i<val.size();i++)dij(val[i]);//直接枚举边权即可
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：WrongAnswer_90 (赞：1)

感觉很神奇的题。

一条路径的代价是前 $k$ 大的边的权值和，有个假的做法是每个点维护一个堆，表示走到这个点前 $k$ 大边的权值，读者可以思考一下这个做法为什么是假的。

既然直接最短路不好处理，自己观察性质，可以发现前 $k$ 条边权值和等价于每条边边权变为 $\max(val-val_k,0)$，然后跑最短路后 $dis_n+k\times val_k$。

一开始的想法是三分，因为感觉这个东西是凸的。

![image.png](https://s2.loli.net/2023/09/19/5zXCY6EasKxBWRM.png)

上图的矩形高度代表一条路径每条边的权值（已进行排序），显然黄色的部分是实际的路径权值。

如果你选的 $val_1 < val_k$，那么相当于多算了红色的部分。而如果选的 $val_2>val_k$，那么相当于多算了绿色的部分，所以这个函数是凸的（感性理解）。

但是如果直接三分会有问题，这个函数可能有连续函数值相等的一段，所以不能三分。

发现 $val$ 只有在等于原图中边的权值才是有意义的，结合数据范围，可以直接枚举每一条边作为 $val_k$，取最小值。

注意题目要求：如果经过的边数小于 $k$，权值为路径权值，所以先跑一边 dijistra，初始答案为 $dis_n$。

```cpp
int n,m,p,cnt,l,r,mid,ans=INF,vis[3001],d[3001],e[3001],head[3001],v[6001],to[6001],nex[6001],numa[6001];
inline void add(int x,int y,int z){to[++cnt]=y,v[cnt]=z,nex[cnt]=head[x],head[x]=cnt;}
priority_queue<pii> q;
void dijkstra(int val)
{
	q.e(mp(0,1)),memset(d,127,sizeof(d)),memset(vis,0,sizeof(vis)),d[1]=0;
	while(!q.empty())
	{
		int now=q.top().se;q.pop();
		if(vis[now])continue;
		vis[now]=1;
		for(int i=head[now],va;i;i=nex[i])
		{
			va=max(v[i]-val,0ll);
			if(d[to[i]]>d[now]+va)
			d[to[i]]=d[now]+va,q.e(mp(-d[to[i]],to[i]));
		}
	}
}
inline void mian()
{
	read(n,m,p);int x,y,z;
	for(int i=1;i<=m;++i)read(x,y,z),numa[i]=z,add(x,y,z),add(y,x,z);
	sort(numa+1,numa+1+m);
	dijkstra(0),ans=d[n];
	for(int i=1;i<=m;++i)if(numa[i]!=numa[i-1])dijkstra(numa[i]),ans=min(ans,d[n]+p*numa[i]);
	write(ans);
}
```

---

## 作者：小木虫 (赞：0)

### Preface  
最短路思维题。  
### Problem  
给你一张带权无向图，定义一条路径的花费为这条路径上前 $k$ 大的边权的和，问你在这个定义下这张图的最短路。  
### Solution  
发现题目的数据范围并不大，所以考虑钦定路径前 $k$ 大中最小的那个边权，设为 $x$。  
显然，钦定之后权值小于 $x$ 的边没有意义，即边权为 0，然后你考虑跑最短路。  
你发现这样做可能不是很对，因为你并没有钦定大于等于 $x$ 的边至少走 $k$ 次。  

显然不能直接钦定，但是你可以钦定在一条路径中若干个小于 $x$ 的边的权值为 $x$，使得大于等于 $x$ 的边走 $k$ 次，这样跑出来的答案不小于真实答案，且一定在某次钦定后运算中取得真实答案，这个操作的本质是将一个不合法方案转为更劣方案，是一个图论中的经典套路。  

你如果不能把一个东西加上一个不确定的值，那就把另一个东西减去一个确定的值，你考虑这个操作等价于将所有边权小于 $x$ 的边的边权设为 0，所有大于等于的边权 $w$ 设为 $w-x$，最后最短路跑出来统一加 $k\times x$。  

那么这个题就做完了，复杂度 $O(m^2 \log m)$：  
```cpp
#include <bits/stdc++.h>
#define mp make_pair
#define int long long
using namespace std;
const int N=3010;
int n,m,k,u,v,w,b[N],res=1e18,dis[N],vis[N];
struct EDGE{int v,w;};
vector <EDGE> edge[N];
struct node{
	int u,dis;
	bool operator <(const node &a)const{
		return a.dis<dis;
	}
};
priority_queue <node> Q;
int solve(int x){
	for(int i=1;i<=n;i++)vis[i]=0,dis[i]=1e18;
	dis[1]=0;Q.push((node){1,0});
	while(Q.size()){
		int u=Q.top().u;Q.pop();
		if(vis[u])continue;vis[u]=1;
		for(auto to:edge[u]){
			int v=to.v;int w=max(to.w,x)-x;
			if(vis[v])continue;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				Q.push((node){v,dis[v]});
			}
		}
	}return dis[n]+x*k;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		cin>>u>>v>>w;b[i]=w;
		edge[u].push_back((EDGE){v,w});
		edge[v].push_back((EDGE){u,w});
	}sort(b+1,b+1+m);
	for(int i=0;i<=m;i++)res=min(res,solve(b[i]));
	cout<<res;
	return 0;
}
```


---

