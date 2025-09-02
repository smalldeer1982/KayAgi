# [ABC401G] Push Simultaneously

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc401/tasks/abc401_g

平面上有 $N$ 个高桥君和 $N$ 个按钮。平面上设有原点，从原点向东移动 $x$ 米、向北移动 $y$ 米的位置用坐标 $(x,y)$ 表示。第 $i$ 个高桥君 $(1 \leq i \leq N)$ 初始位于坐标 $(\mathit{sx}_i, \mathit{sy}_i)$，第 $i$ 个按钮位于坐标 $(\mathit{gx}_i, \mathit{gy}_i)$。

高桥君们需要在移动后**同时**按下这 $N$ 个按钮。每个按钮只能由位于该按钮坐标的高桥君按下。从到达按钮所在坐标到按下按钮所需的时间为 $0$ 秒。

每个高桥君可以以不超过 $1$ 米/秒的速度向任意方向移动。更严格地说，设第 $i$ 个高桥君在开始后 $t$ 秒时的坐标为 $(x_i(t), y_i(t))$，则必须满足以下所有条件：

- $x_i(0) = \mathit{sx}_i$
- $y_i(0) = \mathit{sy}_i$
- 对于所有非负实数 $t_0, t_1$，点 $(x_i(t_0), y_i(t_0))$ 和点 $(x_i(t_1), y_i(t_1))$ 之间的距离不超过 $|t_0 - t_1|$

请计算高桥君们达成目标所需的最短时间。严格来说，求满足以下条件的最小 $t$ 值：

- 适当定义满足上述条件的 $x_i, y_i$ 后，对于所有整数 $j$ $(1 \leq j \leq N)$ 和实数 $t'$ $(t' > t)$，存在整数 $i$ $(1 \leq i \leq N)$ 使得 $(x_i(t'), y_i(t')) = (\mathit{gx}_j, \mathit{gy}_j)$ 成立。

## 说明/提示

### 约束条件

- $1 \leq N \leq 300$
- $0 \leq \mathit{sx}_i \leq 10^{18}$ $(1 \leq i \leq N)$
- $0 \leq \mathit{sy}_i \leq 10^{18}$ $(1 \leq i \leq N)$
- $0 \leq \mathit{gx}_i \leq 10^{18}$ $(1 \leq i \leq N)$
- $0 \leq \mathit{gy}_i \leq 10^{18}$ $(1 \leq i \leq N)$
- $(\mathit{sx}_i, \mathit{sy}_i) \neq (\mathit{sx}_j, \mathit{sy}_j)$ $(1 \leq i < j \leq N)$
- $(\mathit{gx}_i, \mathit{gy}_i) \neq (\mathit{gx}_j, \mathit{gy}_j)$ $(1 \leq i < j \leq N)$
- $(\mathit{sx}_i, \mathit{sy}_i) \neq (\mathit{gx}_j, \mathit{gy}_j)$ $(1 \leq i \leq N, 1 \leq j \leq N)$
- 输入的所有数值均为整数

### 样例解释 1

初始时，高桥君和按钮的位置关系如图所示。

![](https://img.atcoder.jp/abc401/c384b713a3b955d1450b7c503cb429cd.png)

假设第 $1,2,3,4$ 个高桥君分别直接向第 $1,3,2,4$ 个按钮移动。

![](https://img.atcoder.jp/abc401/9e54567c2b21a9757d3769ea756ab892.png)

这样，高桥君们分别在开始后 $2$ 秒、$\sqrt{2}$ 秒、$1$ 秒、$\sqrt{2}$ 秒时到达对应按钮的坐标。因此，可以在开始后 $2$ 秒时同时按下所有按钮。反之，无法在 $2$ 秒之前同时按下所有按钮，所以输出 `2`。只要输出值与真实值的相对误差不超过 $10^{-6}$，例如 `1.999998` 或 `2.00000014` 也会被判定为正确。

### 样例解释 2

注意输入的坐标可能超出 $32$ 位整数的范围。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
0 0
0 1
2 0
3 1
0 2
1 0
1 2
2 2```

### 输出

```
2```

## 样例 #2

### 输入

```
3
1 4
1 5
9 2
653589793238462643 383279502884197169
399375105820974944 592307816406286208
99862803482534211 706798214808651328```

### 输出

```
757682516069002110.04581169374262658710741005525```

## 样例 #3

### 输入

```
12
4459915897 5789359311
4393259463 4247016333
4827828467 4179021045
2654035685 3406423989
1790405301 4886103164
2978675817 4818583236
5912369644 5824121992
6016882384 4165667191
4305949638 3454894060
6545166942 5390976281
4043403253 4019611554
3462096432 4117859301
3528911877 4631601790
4627979431 4814676729
3810130146 5728760563
5586470124 3310360339
3664130072 4525834271
1710246881 3750440871
3143440609 5038869551
2294021341 3965849888
6189106395 4499485672
4799619607 5151972020
6905793542 3976136296
1764267574 4525373194```

### 输出

```
1299999319.116399442508650717909981965254```

# 题解

## 作者：laiyouming (赞：2)

#### 思路
 先预处理出任意两点间的距离，然后按照路径长度排序，接着二分答案，判断条件是将所有边权小于二分值的边建图，看一下是否是二分图完备匹配，如果是那就将二分值缩小，否则就增大。
#### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,top,c[3001],d[3001];
long long s1[301],s2[301],s3[301],s4[301];
vector<pair<long double,pair<int,int>>>a;
vector<int>b[3001];
bool dfs(int x){
	d[x]=1;
	for(auto j:b[x]){
		if(!c[j]||(!d[c[j]]&&dfs(c[j]))){
			c[j]=x;
			return 1;
		}
	}
	return 0;
}
bool ok(long long x){
	for(int i=1;i<=2*n;i++){
		c[i]=0,b[i].clear();
	}
	for(auto i:a){
		if(!x){
			break;
		}
		x--;
		b[i.second.first].push_back(i.second.second);
		b[i.second.second].push_back(i.second.first);
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=2*n;j++){
			d[j]=0;
		}
		if(dfs(i)){
			ans++;
		}
	}
	if(ans==n){
		return 1;
	}
	return 0;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&s1[i],&s2[i]);
	}
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&s3[i],&s4[i]);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			top++;
			a.push_back({sqrt((__int128)abs(s1[i]-s3[j])*abs(s1[i]-s3[j])+(__int128)abs(s2[i]-s4[j])*abs(s2[i]-s4[j])),{i,n+j}});
		}
	}
	sort(a.begin(),a.end());
	long long l=0,r=top+1;
	for(;l+1<r;){
		long long x=(l+r)/2;
		if(ok(x)){
			r=x;
		}
		else{
			l=x;
		}
	}
	printf("%.20Lf",a[r-1].first);
}
```c

---

## 作者：wmrqwq (赞：0)

这是一篇视频题解。

![](bilibili:BV1pydkYuEoc?t=581)

[参考代码](https://atcoder.jp/contests/abc401/submissions/64826536)

---

## 作者：ran_qwq (赞：0)

最大值最小容易想到二分，二分距离 $x$。如果 $(sx_i,sy_i)$ 和 $(gx_i,gy_i)$ 距离 $\le x$ 则表示 $(sx_i,sy_i)$ 能到达 $(gx_i,gy_i)$，连一条边。

如果建出来的二分图存在完美匹配（不会二分图匹配的[点我](https://www.luogu.com.cn/problem/P3386)），则可行，否则不可行。

注意精度，代码中 eps 取 $10^{-8}$，可以判断相对误差和绝对误差，如果有一个满足条件则不继续二分。

```cpp
int n,vs[N],d[N],mp[N][N]; ldb as,x[N],y[N],xx[N],yy[N];
ldb ds(int i,int j) {return sqrtl((x[i]-xx[j])*(x[i]-xx[j])+(y[i]-yy[j])*(y[i]-yy[j]));}
int dfs(int u) {
	for(int i=1;i<=n;i++) if(mp[u][i]&&!vs[i]) {
		vs[i]=1;
		if(!d[i]||dfs(d[i])) {d[i]=u; return 1;}
	}
	return 0;
}
int chk(ldb x) {
	int c=0; mst(mp,0),mst(d,0);
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(ds(i,j)<=x) mp[i][j]=1;
	for(int i=1;i<=n;i++) mst(vs,0),c+=dfs(i);
	return c==n;
}
void QwQ() {
	n=rd();
	for(int i=1;i<=n;i++) x[i]=rdll(),y[i]=rdll();
	for(int i=1;i<=n;i++) xx[i]=rdll(),yy[i]=rdll();
	for(ldb l=0,r=2e18,md;r-l>eps&&abs(r/l-1)>eps/100;) chk(md=(l+r)/2)?r=as=md:l=md;
	printf("%.8Lf\n",as);
}
```

---

## 作者：cheng2010 (赞：0)

## 思路

显然答案具有单调性。

二分答案，把在限定时间可以走到的点与人连边，再定睛一看，嗯？这不是二分图最大匹配吗？直接上 dinic。

具体地，建一个超级源点和终点，分别于左部点与右部点连边，流量为 $1$，再在左右部点间连流量为 $1$ 的边，跑最大流即可。

## code

[link](https://atcoder.jp/contests/abc401/submissions/64789213)

---

## 作者：WuMin4 (赞：0)

## [[ABC401G] Push Simultaneously](https://atcoder.jp/contests/abc401/tasks/abc401_g)

## 题意

给出 $N$ 个人的坐标和 $N$ 个目标位置的坐标，一个人走到另一个位置的时间为两点欧几里得距离的长度。每个人同时开始移动，问每个目标位置都有人需要花费的最小时间为多少。

$1\le N\le 300,1\le sx_i,sy_i,ex_i,ey_i\le 10^{18}$。

## 思路

不确定，再看一眼，这不是裸的二分图最大匹配？？

我们二分一个最小时间 $t$。设二分图左部点为每个人，右部点为每个目标位置，于是可以将每个人跟可以到达的目标位置连边。跑一遍二分图最大匹配，若存在完美匹配，则表示该时间满足要求，否则不满足要求。

注意直接枚举 $t$ 可能会导致丢失精度，所以我们可以枚举 $t^2$，最后再进行开根，但是由于坐标数据范围在 $10^{18}$ 内，平方后来到了 $10^{36}$，所以需要开 `__int128` 来保存坐标。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
namespace mf{
	const int N=605,INF=0x3f3f3f3f;
	struct node{
		int x,w,rev;
	};
	vector<node> t[N];
	int dep[N],gap[N],maxflow;
	int n,S,T;
	void init(int nn){
		for(int i=1;i<=nn+2;i++)
			t[i].clear();
		n=nn+2,S=nn+1,T=nn+2;
	}
	void add(int x,int y,int w){
		t[x].push_back({y,w,t[y].size()});
		t[y].push_back({x,0,t[x].size()-1});
	}
	void bfs(){
		memset(gap,0,sizeof(gap));
		memset(dep,-1,sizeof(dep));
		queue<int> q;
		q.push(T),dep[T]=0,gap[dep[T]]++;
		while(!q.empty()){
			int u=q.front();q.pop();
			for(node v:t[u])
				if(!~dep[v.x])
					dep[v.x]=dep[u]+1,gap[dep[v.x]]++,q.push(v.x);
		}
	}
	int dfs(int x,int flow){
		if(x==T) return maxflow+=flow,flow;
		int used=0;
		for(auto&[v,w,rev]:t[x]){
			if(w&&dep[v]+1==dep[x]){
				int mn=dfs(v,min(w,flow-used));
				if(mn) w-=mn,t[v][rev].w+=mn,used+=mn;
				if(flow==used) return used;
			}
		}
		gap[dep[x]]--;
		if(!gap[dep[x]]) dep[S]=n+1;
		dep[x]++,gap[dep[x]]++;
		return used;
	}
	int isap(){
		maxflow=0;
		bfs();
		while(dep[S]<n) dfs(S,INF);
		return maxflow;
	}
}
int n;
struct node{
	__int128 x,y;
}a[305],b[305];
bool check(__int128 x){
	mf::init(2*n);
	for(int i=1;i<=n;i++)
		mf::add(mf::S,i,1),mf::add(i+n,mf::T,1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if((a[i].x-b[j].x)*(a[i].x-b[j].x)+(a[i].y-b[j].y)*(a[i].y-b[j].y)<=x)
				mf::add(i,j+n,1);
		}
	}
	return mf::isap()==n;
}
signed main() {
	cin>>n;
	for(int x,y,i=1;i<=n;i++)
		cin>>x>>y,a[i].x=x,a[i].y=y;
	for(int x,y,i=1;i<=n;i++)
		cin>>x>>y,b[i].x=x,b[i].y=y;
	__int128 l=0,r=2,mid,res;
	for(int i=1;i<=36;i++) r*=10;
	while(l<=r){
		mid=(l+r)/2;
		if(check(mid)) r=mid-1,res=mid;
		else l=mid+1;
	}
	printf("%.10Lf",sqrtl(res));
	return 0; 
}
```

---

## 作者：Ivan422 (赞：0)

弱智题，但是赛时被 F 卡死了，笑不死我。

我们发现这个东西本质是二分图最大匹配。

看到 $n\leq 300$，直接匈牙利。

~~[不会的小伙伴看这里。](https://www.luogu.me/article/bthendy2)~~

我们考虑二分最大时间，然后输出即可。

但是我们注意到坐标 $0\leq x_i,y_i\leq 10^{18}$。

那么我们最大坐标绝对值为 $10^{18}$。

求距离时最大达到 $2\times10^{36}$。

我们注意到有一个神奇的东西叫做 `__int128`，最大可存储范围大约是 $10^{37}$。

这警示我们检查一下二分边界最大值。

我们发现，我们可以让两点距离最远在大约 $1.5\times{10}^{18}$ 距离。

这就很毒瘤了，小伙伴们千万不要开 $10^{18}$。

我们注意到你这时样例二会过不去。

可以考虑把 `__int128` 的兄弟 `__float128` 请出来，我是这样干的，但是翻了翻有位大佬[直接 `double` 过了](https://atcoder.jp/contests/abc401/submissions/64889790)，抽象。

然后就是我们发现匈牙利是 $\mathcal O(n^3)$ 的，加上各种大大小小的常数。

我们二分次数过多就会炸掉。

所以我们考虑优化一下：预先建图，不枚举每一个点作为匹配节点，这样常数就小一点。

但是我们如何设定误差值呢？

我菜，算不出来，所以用了二分 $200$ 次作为临界值。

然后就结束了，上代码吧。

---

此题解第一次审核时因为错别字被拒绝，笑死我了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define i128 __int128   // 范围 10^37
#define f128 __float128 // 查不到，好像是 18 位小数
#define ld long double
const int N=300+10;
struct pos{
	ll x,y;
}a[N],b[N];
int npy[N],cnt;
f128 lmt;
int found[N];
vector<int>e[N];
i128 dis(pos pa,pos pb){ // 求距离，不要开方保持精度
	return (i128)(pa.x-pb.x)*(i128)(pa.x-pb.x)+(i128)(pa.y-pb.y)*(i128)(pa.y-pb.y);
}
int n;
bool dfs(int p){ // 简单匈牙利
	for(auto v:e[p])if(!npy[v]){
		npy[v]=1;
		if(!found[v]||dfs(found[v])){
			found[v]=p;
			return 1;
		}
	}
	return 0;
}
bool check(f128 tim){
	memset(found,0,sizeof(found));
	for(int i=1;i<=n;i++)
		e[i].clear();
	cnt=0,lmt=tim; // 这个 tim 是旧代码遗留的，无用
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(dis(a[i],b[j])<=lmt*lmt)
				e[i].push_back(j); // 预先建图优化
	for(int i=1;i<=n;i++){
		memset(npy,0,sizeof(npy));
		if(dfs(i))++cnt;
	}
	return cnt==n; // 找到可行
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].x>>a[i].y;
	for(int i=1;i<=n;i++)
		cin>>b[i].x>>b[i].y;
	f128 l=0,r=5e18,mid; // 边界，保险一点为好
	int src=0; // 二分次数统计
	while((++src)<=200){ // 二分
		mid=(l+r)/2;
		if(check(mid))
			r=mid;
		else 
			l=mid;
	}
	printf("%.20Lf",(ld)l); // 输出，直接输出即可
	return 0;
}
```

---

## 作者：cyq32ent (赞：0)

可能是有史以来最简单的 G 题了。

题意：有 $N$ 个人和 $N$ 个按钮，给每个人匹配一个按钮，使得人和对应的按钮之间的最大值最小。

显然二分答案。判断答案有效性时，只需要添加人和按钮之间长度小于时间 $T$ 的边，跑一边二分图即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
int N;
pair<int,int>S[333],G[333];
vector<int>g[333];
int Mr[333],vis[333];
int dfs(int u){
	for(auto v:g[u])if(!vis[v]){
		vis[v]=1;
		if(Mr[v]==-1||dfs(Mr[v])){Mr[v]=u;return 1;}
	}return 0;
}int chk(ld T){
	for(int i=0;i<N;i++)g[i].clear();
	for(int i=0;i<N;i++)for(int j=0;j<N;j++){
		ld dx=S[i].first-G[j].first,
		   dy=S[i].second-G[j].second;
		if(dx*dx+dy*dy<=T*T)g[i].push_back(j);
	}for(int i=0;i<N;i++)Mr[i]=-1;
	int cnt=0;
	for(int i=0;i<N;i++){
		for(int i=0;i<N;i++)vis[i]=0;
		if(dfs(i))cnt++;
	}return cnt==N;
}
signed main(){
	cin>>N;
	for(int i=0,x,y;i<N;i++)cin>>x>>y,S[i]={x,y};
	for(int i=0,x,y;i<N;i++)cin>>x>>y,G[i]={x,y};
	ld L=0,R=1.5e18;
	for(int i=0;i<100;i++){
		ld mid=(L+R)/2;
		if(chk(mid))R=mid;
		else L=mid;
	}cout<<fixed<<setprecision(10)<<R<<endl;
	return 0;
}
```

---

## 作者：Inv_day_in_R (赞：0)

这道题很容易想到从所有 $s$ 点向所有 $t$ 点建边，问这个二分图的完美匹配中边最小权值是多少。

不妨二分权值，建出所有权值在 `mid` 以下的边，每次跑最大匹配，检验最大匹配是否等于 $n$。但是计算两点距离和二分权值的过程中精度掉太多了，其实可以提前把所有边建好，用 `__int128` 存下权值的平方，然后以权值的平方为关键字升序排列，只要二分加入前几条边即可。这样不仅优化了常数，还优化了精度。

而二分图最大匹配的算法自然是转化为最大流然后跑 dinic 了，复杂度 $O(m\sqrt n)$，而本题中 $m=O(n^2)$，复杂度为 $O(n^{2.5})$，加上二分，复杂度 $O(n^{2.5}\log n)$。

最后别忘了开个根号。

代码的话：（要是连 Dinic 都不会写还来做这题干什么？自己去[这里](https://oi-wiki.org/graph/graph-matching/bigraph-match/#%E8%BD%AC%E4%B8%BA%E7%BD%91%E7%BB%9C%E6%9C%80%E5%A4%A7%E6%B5%81%E6%A8%A1%E5%9E%8B)学）


```cpp
struct Edge{
	int v,bkid;
	int cap;
};
struct Flow{/*防抄袭。Dinic 最大流模板都会写吧，此处省略 1180 个字符*/}fl;
int n;
int sx[610],sy[610],tx[610],ty[610];
void solve(){
	cout<<fixed<<setprecision(12);
	cin>>n;
	for(int i=0;i<n;i++) cin>>sx[i]>>sy[i];
	for(int i=0;i<n;i++) cin>>tx[i]>>ty[i];
	vector<pair<__int128,pair<int,int> > > ord;
	for(int i=0;i<n;i++) for(int j=0;j<n;j++){
		ord.push_back(make_pair((__int128)(sx[i]-tx[j])*(__int128)(sx[i]-tx[j])+(__int128)(sy[i]-ty[j])*(__int128)(sy[i]-ty[j]),make_pair(i,j)));
	}
	sort(ord.begin(),ord.end());
	int l=0,r=ord.size()-1;
	while(l<r){
		int mid=(l+r)>>1;
		fl.init(n*2+2);
		for(int i=0;i<n;i++) fl.addedge(fl.s,i,1),fl.addedge(i+n,fl.t,1);
		for(int i=0;i<=mid;i++) fl.addedge(ord[i].second.first,ord[i].second.second+n,1);
		if(fl.maxflow()>=n) r=mid;
		else l=mid+1;
	}
	cout<<sqrt((long double)ord[l].first);
}
```

---

