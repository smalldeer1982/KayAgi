# [USACO25JAN] Photo Op G

## 题目描述

Farmer John 的农场充满了茂盛的植被，每头奶牛都想拥有一张这里的自然美景的照片。不幸的是，Bessie 还有其他地方要去，但她不想打扰任何摄影活动。

Bessie 目前站在 xy 平面上 $(X,0)$ 处，她想要前往 $(0,Y)$（$1\le X,Y\le 10^6$）。不幸的是，$N$（$1 \leq N \leq 3 \cdot 10^5$）头其他奶牛决定在 $x$ 轴上摆姿势。更具体地说，奶牛 $i$ 将位于 $(x_i,0)$，她的摄影师位于 $(0,y_i)$（$1 \leq x_i,y_i \leq 10^6$），准备拍摄她的照片。他们将在时刻 $s_i$（$1 \leq s_i < T$）开始摆姿势，并且他们会保持姿势很长时间（他们必须拍出完美的照片）。这里，$1\le T\le N+1$。

Bessie 知道每头奶牛的摄影安排，她将选择最短欧几里得距离到达目的地，而不穿越任何摄影师与其对应的奶牛之间的视线（她的路径将由一条或多条线段组成）。

如果 Bessie 在时刻 $t$ 出发，她将**需要**避开所有在时刻 $s_i \le t$ 开始摆姿势的摄影师-奶牛对的视线，此外令她到达最终目的地的距离为 $d_t$。求从 $0$ 到 $T-1$ 的每一个整数 $t$ 的 $\lfloor d_t\rfloor$ 的值。

注 1：Bessie 可以从摄影师或者奶牛的位置经过，这样不算穿越视线。

注 2：如果 Bessie 在时刻 $t$ 出发，她需要避开的是所有满足 $s_i \le t$ 的摄影师-奶牛对的视线，不需要考虑 $s_i\gt t$ 的摄影师-奶牛对。

## 说明/提示

样例 2 解释：

对于 $t=0$ 答案为 $\lfloor \sqrt{149} \rfloor=12$。

对于 $t=1$ 答案为 $\lfloor 14+\sqrt 5\rfloor=16$。

样例 3 解释：

对于 $t=5$ 答案为 $\lfloor 1+\sqrt{9^2+7^2}+2\rfloor=14$。路径：$(8,0)\to (9,0)\to (0,7)\to (0,9)$。

- 测试点 $4\sim 6$：$N\le 100$。
- 测试点 $7\sim 9$：$N\le 3000$。
- 测试点 $10\sim 12$：$T\le 10$。
- 测试点 $13\sim 18$：没有额外限制。

## 样例 #1

### 输入

```
4 5
6 7
1 7 5
2 4 4
3 1 6
4 2 9```

### 输出

```
9
9
9
10
12```

## 样例 #2

### 输入

```
2 3
10 7
1 2 10
1 9 1```

### 输出

```
12
16
16```

## 样例 #3

### 输入

```
5 6
8 9
1 3 5
1 4 1
3 10 7
4 9 2
5 6 6```

### 输出

```
12
12
12
12
14
14```

# 题解

## 作者：Demeanor_Roy (赞：12)

### 前言

好像大家都是同一个难写做法，这里分享我一个赛时的简单做法。

### 题解

一个初步结论是：

- 路线一定形如 $(X,0) \rightarrow (x_i,0) \rightarrow (0,y_i) \rightarrow (0,Y) $ 。

这是因为我们绕路的目的是避开一些 $(x_i,0) \rightarrow (0,y_i)$ 的线段，对于任意一条路线，我们都可以通过调整成上述形式使答案不劣。具体可以手玩一下。

令我们选择的中转点为 $(x',0),(0,y')$，那么一条线段 $(x_i,0) \rightarrow (0,y_i)$ 的限制可以表示为：

- $\forall x'< x_i,y'<y_i$。

- $\forall x'> x_i,y'>y_i$。

当 $x'$ 确定时，上述限制确定了合法的 $y'$ 为一个区间 $[l,r]$，显然我们存在以下贪心策略：

- $l>Y$：选取 $y'=l$。

- $r<Y$：选取 $y'=r$。

- $Y \in [l,r]$：选取 $y'=Y$。

到这里我们有一个 $O(n^2)$ 的暴力：对每个 $x'$ 暴力维护合法区间 $[l,r]$，每次加入线段后暴力枚举 $x'$ 更新答案。

重新思考上述过程，我们有以下观察：

- $\forall x_1 < x_2$，其对应的合法区间 $[l_1,r_1],[l_2,r_2]$ 有：$l_1 \leq l_2,r_1 \leq r_2$。

从这个结论下手分析：我们考察 $x_1 < x_2 \leq X,r_1 < Y$。如果 $r_2 < Y$，那么 $x_2$ 肯定优于 $x_1$，这种情况下最优的 $x'$ 肯定是 $\leq X$ 中最大的；若 $l_2 > Y$ 或 $Y \in [l_2,r_2]$，那么 $l_2/Y$ 一定是 $\geq Y$ 的所有合法 $y'$ 中最小的。

按照上面的分析，我们可以总结得出：

- 我们把不可能作为中转点的 $x_i,y_i$ 删去（即对应合法区间 $[l,r]$ 为空），最优解选择的中转点一定满足 $x_i$ 是 $\leq X$ 最大的；$x_i$ $\geq X$ 最小的；$y_i$ 是 $\leq Y$ 最大的；$y_i$ $\geq Y$ 最小的其中之一。

于是我们用树状数组维护每个 $x_i,y_i$ 对应的合法区间 $[l,r]$，每次取出上述 $O(1)$ 个 $x_i,y_i$ 得到答案即可。时间复杂度 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=3e5+10,M=1e6+10;
set<int> X1,X2,Y1,Y2;
vector<int> vec[N];
int n,T,xx[N],yy[N]; 
struct BIT1
{
	int C[M];
	BIT1(){for(int i=0;i<M;i++) C[i]=M-1;}
	inline void add(int x,int y){for(;x;x-=x&-x) C[x]=min(C[x],y);}
	inline int query(int x){int res=M-1;for(;x<M;x+=x&-x) res=min(res,C[x]);return res;}
}Xpre,Ypre;
struct BIT2
{
	int C[M];
	inline void add(int x,int y){if(!x) return;for(;x<M;x+=x&-x) C[x]=max(C[x],y);}
	inline int query(int x){int res=0;for(;x;x-=x&-x) res=max(res,C[x]);return res;}
}Xsuc,Ysuc;
inline void ins(int x,int y)
{
	if(x!=xx[0])
	{
		Xpre.add(x-1,y);Xsuc.add(x+1,y);
		Ypre.add(y-1,x);Ysuc.add(y+1,x);	
	}
	if(x<=xx[0]) X1.insert(x);else X2.insert(x);
	if(y<=yy[0]) Y1.insert(y);else Y2.insert(y);
}
inline int calcx(int x,int l,int r)
{
	if(r<yy[0]) return abs(x-xx[0])+yy[0]-r+sqrt(1ll*x*x+1ll*r*r);
	if(l>yy[0]) return abs(x-xx[0])+l-yy[0]+sqrt(1ll*x*x+1ll*l*l);
	return abs(x-xx[0])+sqrt(1ll*x*x+1ll*yy[0]*yy[0]);
}
inline int calcy(int x,int l,int r)
{
	if(r<xx[0]) return abs(x-yy[0])+xx[0]-r+sqrt(1ll*x*x+1ll*r*r);
	if(l>xx[0]) return abs(x-yy[0])+l-xx[0]+sqrt(1ll*x*x+1ll*l*l);
	return abs(x-yy[0])+sqrt(1ll*x*x+1ll*xx[0]*xx[0]);
}
inline int query()
{
	int ans=1e7;
	while(!X1.empty())
	{
		auto it=X1.end();--it;
		int rs=Xpre.query(*it),ls=Xsuc.query(*it);
		if(ls>rs) X1.erase(it);
		else
		{
			ans=min(ans,calcx(*it,ls,rs));
			break;
		}
	}
	while(!X2.empty())
	{
		auto it=X2.begin();
		int rs=Xpre.query(*it),ls=Xsuc.query(*it);
		if(ls>rs) X2.erase(it);
		else
		{
			ans=min(ans,calcx(*it,ls,rs));
			break;
		}
	}
	while(!Y1.empty())
	{
		auto it=Y1.end();--it;
		int rs=Ypre.query(*it),ls=Ysuc.query(*it);
		if(ls>rs) Y1.erase(it);
		else
		{
			ans=min(ans,calcy(*it,ls,rs));
			break;
		}
	}
	while(!Y2.empty())
	{
		auto it=Y2.begin();
		int rs=Ypre.query(*it),ls=Ysuc.query(*it);
		if(ls>rs) Y2.erase(it);
		else
		{
			ans=min(ans,calcy(*it,ls,rs));
			break;
		}
	}
	return ans;
}
int main()
{
	scanf("%d%d%d%d",&n,&T,&xx[0],&yy[0]);vec[0].push_back(0);
	for(int i=1;i<=n;i++)
	{
		int t;
		scanf("%d%d%d",&t,&xx[i],&yy[i]);
		vec[t].push_back(i);
	}
	for(int o=0;o<T;o++)
	{
		for(auto i:vec[o]) ins(xx[i],yy[i]);
		printf("%d\n",query());
	}
	return 0;
}
```

---

## 作者：_LiWenX_ (赞：6)

（为啥我要打金组???）这个题赛时确实是把我恶心到了，最后 $20$ 分治极限通过，甚至一个去年的Au选手都没能场上通过，所以我来篇题解纪念一下我的做法。

首先离线询问，然后添加线段，动态解决询问。

可以发现一个显然的结论，移动必然形如 $(X,0)\to(x_i,0)\to(0,y_j)\to (0,Y)$，其中 $x_i$ 和 $y_j$ 都是给出的线段端点，或者就是 $X,Y$。

我们不妨先假设必须走到两个给出的线段端点，也就是会有三次移动的情况下的答案。

在手玩之后，还可以发现另一个结论，假如把有交的线段合并到一起，形成两个区间 $[l_x,r_x],[l_y,r_y]$ 分别表示这个线段集合中最小最大的 $x_i$ 与 $y_i$，假如已经维护出来这些连通块了，显然这些集合区间都是单调不交的，对于一个连通块，可行的移动只会是从 $(X,0)\to(l_x,0)\to(0,l_y)\to (0,Y)$ 或是 $(X,0)\to(r_x,0)\to(0,r_y)\to (0,Y)$。

而且如果选择离询问点 $(X,0)$ 的前驱后继连通块，这个东西非常优，直接猜测它是答案，写出来发现过不了第三个样例，于是你会发现，我们还会出现跨越两个连通块的情况，但这个情况只能走相邻的两个连通块，然后就做完了。

至于怎么维护这些连通块，直接用 set 维护它，添加一个线段就先定位出来然后左右合并即可，求最小的两个相邻连通块答案，用一个支持添加，删除，求最小值的数据结构维护。

现在还有可能直接从 $(X,0)\to (0,y_j)$ 这种情况，直接把 $(X,Y)$ 看做一个线段添加进去，跑两次就可以得到答案了。

稍微有点难写，可能是因为在凌晨脑子不太清醒调了好久好久，我的代码也不见了，所以不能展示我写的史/ll。

---

## 作者：SFlyer (赞：5)

考虑路线的样式。发现我们一定是沿着 $x$ 轴走一点，斜着横跨，然后沿着 $y$ 轴走一点。并且，我们横跨以及横跨结束的坐标一定是 $X,Y,x_i,y_i$ 这些坐标。那么 $\mathcal{O}(n^2)$ 就很简单了，枚举横跨起点和时间，可以 $\mathcal{O}(1)$ 算出横跨终点。 

每一个“不能进入”的区域是由两条直线夹着的。例如进入下图黄色区域是不优的。

![image](https://cdn.luogu.com.cn/upload/image_hosting/cd9nzk17.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

这些黄色禁止进入区域构成连通块。那么我们如果可以快速维护连通块的合并（以及对于答案的影响就可以了）。具体的：

- 每一个连通块可以用 $min_x,max_x,min_y,max_y$ 表示。

- 答案和连通块可以用 multiset 维护。

- 相交的判断：不是 $max_{xa}\le min_{xb}$ 并且 $max_{ya}\le min_{yb}$
即可（$a$ 在 $b$ 左边）。

- 对于一个横跨起点的结束点最佳：如果我们可以直接到达 $[y_{mn},y_{mx}]$ 之间的点，那么 $Y<y_{mn}$ 则 $y_{mn}$ 最优，$Y>y_{mx}$ 则 $y_{mx}$ 最优，否则 $Y$ 就可以直接到，$Y$ 最优。其实和暴力一样。

- 两个连通块的并合并 $min_x,max_x,min_y,max_y$ 就可以了。

- 初始加入 $(0,0),(\infty,\infty)$ 两条线可以避免边界判断。

时间复杂度 $\mathcal{O}(n\log n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 3e5+5;

int Sqrt(ll a,ll b){
	ll c=a*a+b*b,y=sqrtl(c);
	while (y*y<=c) y++;
	while (y*y>c) y--;
	return y;
}

int n,T,X,Y;
vector<pair<int,int> > g[N];
multiset<ll> sns;

#define F first
#define S second
#define pi pair<int,int>
#define ppi pair<pi,pi>

set<ppi> cn; 

bool ist(ppi a,ppi b){
	if (a.F.S<=b.F.F && a.S.S<=b.S.F) return 0;
	return 1;
}

int bst(int l,int r,int x){
	return (x<l)?l:(x>r?r:x);
}

void Add(ppi l,ppi r,int f){
	pi xr={l.F.S,r.F.F};
	pi yr={l.S.S,r.S.F};
	ll cx=bst(xr.F,xr.S,X),cy=bst(yr.F,yr.S,Y);
	ll ans=abs(X-cx)+abs(Y-cy)+Sqrt(cx,cy);
	if (f==1) sns.insert(ans);
	else sns.erase(sns.find(ans));
}

void add(ppi x,int f){
	auto it=cn.lower_bound(x);
	if (it!=cn.begin()){
		Add(*prev(it),*it,f);
	}
	if (next(it)!=cn.end()){
		Add(*it,*next(it),f);
	}
	if (it!=cn.begin() && next(it)!=cn.end()){
		Add(*prev(it),*next(it),-f);
	}
}

void uni(ppi &a,ppi b){
	a.F.F=min(a.F.F,b.F.F);
	a.F.S=max(a.F.S,b.F.S);
	a.S.F=min(a.S.F,b.S.F);
	a.S.S=max(a.S.S,b.S.S);
}

void ins(int x,int y){
	ppi p={{x,x},{y,y}};
	while (1){
		auto it=cn.lower_bound(p);
		if (it!=cn.end() && ist(p,*it)){
			add(*it,-1),uni(p,*it);
			cn.erase(it);
			continue;
		}
		if (it!=cn.begin() && ist(*prev(it),p)){
			auto _it=prev(it);
			add(*_it,-1),uni(p,*_it);
			cn.erase(_it);
			continue;
		}
		break;
	}
	cn.insert(p);
	auto it=cn.lower_bound(p);
	add(*it,1);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>n>>T>>X>>Y;
	ins(0,0);
	ins(1e9,1e9);
	for (int i=1; i<=n; i++){
		int s,x,y;
		cin>>s>>x>>y;
		g[s].push_back({x,y});
	}
	for (int i=0; i<T; i++){
		for (auto u : g[i]){
			ins(u.first,u.second);
		}
		cout<<(*sns.begin())<<"\n";
	}
	return 0;
}
```

---

## 作者：dahuiji (赞：5)

[原题链接](https://www.luogu.com.cn/problem/P11675)

~~人生中第一次写题解~~

首先，容易证明，答案路线一定由一条沿 $y$ 轴线段，一条沿 $x$ 轴线段，以及一条斜插线段组成（两点之间直线最短）

我们看图分析：图中黑色线条为摄影视线，橙色区域为可通行部分，白色为不可通行部分。均为四边形。
不难发现可以维护可通行部分，或者不可通行部分的每个四边形。这里选择维护可通行部分（以下简称块）~~但貌似另一种会更好写~~
![](https://cdn.luogu.com.cn/upload/image_hosting/fqvl5gpu.png)

对于每个块，我们需要维护其在每个坐标轴的上下端点，及通过其的最小 $ans$ 。具体维护方式下面会讲。

---


对于新增一条摄影视线，有以下情况：

情况 $1$ , $2$ ：
![](https://cdn.luogu.com.cn/upload/image_hosting/b12p8hzk.png)
图中蓝线为新增，浅蓝区为新增后块。可以看到， $1$、新增线段可能导致旧块整块被删除。不难发现，当新增线段一段点位于一块上端点之上，另一端点位于一块下端点之下时，这块需要删除。

$2$、新增线段可能造成块端点更新。具体存在 $4$ 种不同情况，包括 $x$ 坐标位于两端点区间内时更新 $x$ 轴下端点（ $y$ 坐标位于本块 $y$ 轴下端点之下），更新 $x$ 轴上端点（ $y$ 坐标位于本块 $y$ 轴上端点之上）； $y$ 坐标位于两端点区间内时更新 $y$ 轴下端点（ $x$ 坐标位于本块 $x$ 轴下端点之下），更新 $y$ 轴上端点（ $x$ 坐标位于本块 $x$ 轴上端点之上）。一条新增最多造成 $2$ 个块端点更新

这两种情况可能同时存在。

情况 $3$ ：
![](https://cdn.luogu.com.cn/upload/image_hosting/tfbgtvzu.png)
图中绿线为新增。可以发现，绿线将原来的一个区间一分为二。此时这条线不会再满足情况 $1$ 或情况 $2$ 。

情况 $4$ ：与任何块均无交，不造成任何影响。



---

情况讨论完了，现在来讲讲怎么维护。
对于线段的两端点，很容易想到需要一种数据结构快速确定其属于哪块。考虑开两个 ```set< pair<int,int> >``` 。 ```first``` 存每一块在该维度的上端点， ```second``` 存块号。然后完成上述操作即可。

对于维护合法答案，我们对每一种块都定一个唯一编号，并搞一个优先队列维护最优答案。当块被更改，则将其编号标记。每次取优先队列队头第一个未被标记的 $ans$ 即可。

对于答案计算，枚举贴边走两种情况，以及走对角线两种情况。注意特判起点、终点在该块内情况。


---

时间复杂度： $O(n \log n)$ 

证明：对于每一条新增摄影视线，最多删去一块，产生两块。最多同时存在块数量为 $n$ ，最多总计存在过 $2n$ 块。每一块复杂度 $\log n$ 。


---
思路不难代码写死。调了好久才调出来。

~~码风奇丑，不要嘲笑~~
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<ll,ll>
ll n,t;
ll x,y;
ll sj[301100],qx[301100],qy[301100];//输入
ll cnt=0,jant=0;
struct z{
	ll xl,xr,yl,yr;//块两坐标轴上下端点
	ll abh;//该块ans编号
}sr[600005];//块
pii jpl;
set< pii > jxr,jyr;//维护块上端点以及块编号
priority_queue< pii > q;//维护ans
bool cz[600005];//记录该ans是否被标记
ll pf(ll a){
	return a*a;
}
ll jdz(ll a){
	if(a<0)return -a;
	return a;
}
void qans(ll i){//对于新块计算ans
	ll jans=1000000000000000000;
	if(x>=sr[i].xl&&x<=sr[i].xr&&y>=sr[i].yl&&y<=sr[i].yr)jans=(ll)(sqrt(pf(x)+pf(y)));
	if(x>=sr[i].xl&&x<=sr[i].xr)jans=min(jans,min((ll)(sqrt(pf(x)+pf(jdz(sr[i].yl))))+jdz(sr[i].yl-y),(ll)(sqrt(pf(x)+pf(jdz(sr[i].yr))))+jdz(sr[i].yr-y)));
	if(y>=sr[i].yl&&y<=sr[i].yr)jans=min(jans,min((ll)(sqrt(pf(y)+pf(jdz(sr[i].xl))))+jdz(sr[i].xl-x),(ll)(sqrt(pf(y)+pf(jdz(sr[i].xr))))+jdz(sr[i].xr-x)));
	jans=min(jans,(ll)(sqrt(pf(jdz(sr[i].xr))+pf(jdz(sr[i].yr))))+jdz(sr[i].xr-x)+jdz(sr[i].yr-y));
	jans=min(jans,(ll)(sqrt(pf(jdz(sr[i].xl))+pf(jdz(sr[i].yr))))+jdz(sr[i].xl-x)+jdz(sr[i].yr-y));
	jans=min(jans,(ll)(sqrt(pf(jdz(sr[i].xr))+pf(jdz(sr[i].yl))))+jdz(sr[i].xr-x)+jdz(sr[i].yl-y));
	jans=min(jans,(ll)(sqrt(pf(jdz(sr[i].xl))+pf(jdz(sr[i].yl))))+jdz(sr[i].xl-x)+jdz(sr[i].yl-y));
	jant++;
	cz[sr[i].abh]=1;//将旧ans标记
	sr[i].abh=jant;
	jpl.first=-jans;
	jpl.second=jant;
	q.push(jpl);
	return;
}
int main(){
	cin>>n>>t>>x>>y;
	for(ll i=1;i<=n;i++)cin>>sj[i]>>qx[i]>>qy[i];
	cnt++;
	jant++;
	sr[cnt].xl=0;
	sr[cnt].yl=0;
	sr[cnt].xr=1000005;
	sr[cnt].yr=1000005;
	sr[cnt].abh=jant;//初始化：全场随便走
	jpl.first=-int(sqrt(pf(x)+pf(y)));
	jpl.second=1;
	q.push(jpl);//初始化ans：起点终点连线
	jpl.first=1000005;
	jpl.second=1;
	jxr.insert(jpl);//初始化区间入set
	jyr.insert(jpl);
	ll jt=0;
	for(ll i=1;i<=n;i++){
		while(jt<sj[i]){//输出前序时间答案
			if(q.empty())break;
			pii jl=q.top();
			while(cz[jl.second]==1){
				q.pop();
				jl=q.top();
			}
			jt++;
			cout<<-jl.first<<endl;
		}
		set< pii >::iterator jjx,jjy;
		jpl.first=qx[i];
		jpl.second=0;
		jjx=jxr.lower_bound(jpl);
		jpl.first=qy[i];
		jpl.second=0;
		jjy=jyr.lower_bound(jpl);
		ll jx=jjx->second,jy=jjy->second;
		if(jx==jy){
			if(qx[i]<=sr[jx].xl&&qy[i]<=sr[jy].yl)continue;
			if(qx[i]>sr[jx].xl&&qy[i]>sr[jy].yl){//切区间情况（情况3）
				cnt++;
				sr[cnt].xl=sr[jx].xl;
				sr[cnt].yl=sr[jx].yl;
				sr[jx].xl=sr[cnt].xr=qx[i];
				sr[jx].yl=sr[cnt].yr=qy[i];
				qans(jx);
				qans(cnt);
				jpl.first=sr[cnt].xr;
				jpl.second=cnt;
				jxr.insert(jpl);
				jpl.first=sr[cnt].yr;
				jpl.second=cnt;
				jyr.insert(jpl);
				continue;
			}
		}
		if(qx[i]>sr[jx].xl){//情况2
			if(qy[i]>sr[jx].yr){
				jxr.erase(jjx);
				sr[jx].xr=qx[i];
				qans(jx);
				jpl.first=sr[jx].xr;
				jpl.second=jx;
				jxr.insert(jpl);
			}
			else{
				sr[jx].xl=qx[i];
				qans(jx);
			}
		}
		if(qy[i]>sr[jy].yl){//情况2
			if(qx[i]>sr[jy].xr){
				jyr.erase(jjy);
				sr[jy].yr=qy[i];
				qans(jy);
				jpl.first=sr[jy].yr;
				jpl.second=jy;
				jyr.insert(jpl);
			}
			else{
				sr[jy].yl=qy[i];
				qans(jy);
			}
		}
		jpl.first=qx[i];
		jpl.second=0;
		jjx=jxr.lower_bound(jpl);
		if(jjx!=jxr.begin())jjx--;
		while(1){//情况1:从本块向下遍历，找不合法块并删去
			jx=jjx->second;
			if(sr[jx].xr<qx[i]&&sr[jx].yl>qy[i]){
				jxr.erase(jjx);
				cz[sr[jx].abh]=1;
				jpl.first=sr[jx].yr;
				jpl.second=jx;
				jyr.erase(jpl);
				}
			else break;
			jpl.first=qx[i];
			jpl.second=0;
			jjx=jxr.lower_bound(jpl);
			jjx--;
		}
		jpl.first=qy[i];
		jpl.second=0;
		jjy=jyr.lower_bound(jpl);
		if(jjy!=jyr.begin())jjy--;
		while(1){//情况1
			jy=jjy->second;
			if(sr[jy].yr<qy[i]&&sr[jy].xl>qx[i]){
				jyr.erase(jjy);
				cz[sr[jy].abh]=1;
				jpl.first=sr[jy].xr;
				jpl.second=jy;
				jxr.erase(jpl);
			}
			else break;
			jpl.first=qy[i];
			jpl.second=0;
			jjy=jyr.lower_bound(jpl);
			jjy--;
		}
	}
	while(jt<t){//输出剩余部分
		if(q.empty())break;
		pii jl=q.top();
		while(cz[jl.second]==1){
			q.pop();
			jl=q.top();
		}
		jt++;
		cout<<-jl.first<<endl;
	}
	return 0;
}
```

---

