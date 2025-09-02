# [COCI 2015/2016 #4] GALAKSIJA

## 题目描述

很久以前，在一个很远很远的星系里，有 $n$ 颗行星和 $n−1$ 条连接所有行星的边。换句话说，行星和边形成了一棵树。此外，每条边上都有一个权值。

行星对 $(A,B)$ 是**无聊的**，当且仅当如下条件成立：

- $A\neq B$。
- 行星 $A,B$ 可以互相到达。
- 行星 $A,B$ 之间的路径上的所有边的权值的**异或和**等于 $0$。

现在，由于不可控力，该星系的所有边会**按一定顺序**摧毁。请求出初始时和每次摧毁一条边之后**无聊的**行星对数量。

## 说明/提示

**【样例 1 解释】**

初始时，只有行星对 $(1,2)$ 是无聊的。在毁坏了唯一的一条边之后，就不再存在无聊的行星对了。

**【样例 2 解释】**

初始时，只有行星对 $(1,3)$ 是无聊的。在破坏了 $1$ 号边之后，由于行星 $1,3$ 之间不能互相到达，因此之后不再存在无聊的行星对了。

**【样例 3 解释】**

初始时，所有的行星对都是无聊的，因为所有行星对中的两个行星之间的路径上的所有边的权值的异或和是 $0$。

**【数据范围】**

对于所有数据，$1\leqslant n\leqslant 10^5$，$1\leqslant a_i,b_i\leqslant n$，$0\leqslant z_i\leqslant 10^9$。

本题一共 $10$ 个测试点，每个测试点的数据范围如下：

| 测试点 | $n\leqslant $ | 特殊性质 A |
| :-----------: | :-----------: | :-----------: |
| $1$ | $1000$ | $\surd$ |
| $2$ | $1000$ | $\times$ |
| $3\sim 4$ | $10^5$ | $\surd$ |
| $5\sim 10$ | $10^5$ | $\times$ |

特殊性质 A：每条边的权值为 $0$。换句话说，$\forall i\in[1,n)$，$z_i=0$。

**【题目来源】**

本题来源自 **_[COCI 2015-2016](https://hsin.hr/coci/archive/2015_2016/) [CONTEST 4](https://hsin.hr/coci/archive/2015_2016/contest4_tasks.pdf) T5 GALAKSIJA_**，按照原题数据配置，满分 $140$ 分。

由 [Eason_AC](https://www.luogu.com.cn/user/112917) 翻译整理提供。

## 样例 #1

### 输入

```
2
1 2 0
1```

### 输出

```
1
0```

## 样例 #2

### 输入

```
3
1 2 4
2 3 4
1 2```

### 输出

```
1
0
0```

## 样例 #3

### 输入

```
4
1 2 0
2 3 0
2 4 0
3 1 2```

### 输出

```
6
3
1
0```

# 题解

## 作者：Zom_j (赞：5)

观察题意，首先删边这个操作本身就不好做，在删边的过程中，连通块也会越来越多，并不见得删边是好做的。
所以考虑正难则反，在加边的过程中统计新增的行星对。

由于加到最后是一棵树，所以不会出现加边加到同一个连通块里，即每次加边统计两个连通块之间的点是否合法即可,考虑如何去统计方案数。
![](https://cdn.luogu.com.cn/upload/image_hosting/5wgbulgf.png)

对于每个联通块，钦定一个点作为根，统计与它相连的点的距离记为数组 $dis$，不难发现，对于此刻与根相连的连通块，内部的点可以被递推出来。
这样做对统计方案有什么帮助吗？
![](https://cdn.luogu.com.cn/upload/image_hosting/v3j5dfdo.png)
对于两个即将相连的联通块（红色边为新连的边），设红边的权值为 $w$。

若判断点 $1$ 与点 $2$ 是否合法，那么就看是否满足 $dis_3⊕dis_1⊕w=0$ 由于我们之前预处理过，所以判断的时间复杂度是 $O(1)$。

稍微转换一下，我们可以求出使 $dis_1⊕w=0$ 的值 $x$ 并判断在集合中有哪些 $dis$ 符合要求，这可以用 map 在 $O(1)$ 的时间内处理整个集合，扩充到整个连通块就只需要遍历一遍。

遍历的时候遍历点更少的连通块,这样最劣情况时间为 $O(n\log n)$ 算上 map 和并查集的时间复杂度是足以通过此题的，将求出新的 $x$ 然后再次判断即可，在遍历集合的时候顺便统计新的 $dis$，将点归为同一个根，就这样处理完整个连通块，一些细节问题就见代码了。
```
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=1e5+10;
int h[N];
int cnt;
struct Edge{
	int to;
	int next;
	int w;
}e[N<<1];
void add(int a,int b,int w){
	e[cnt].to=b;
	e[cnt].next=h[a];
	e[cnt].w=w;
	h[a]=cnt++;
	return ;
}
struct Edge1{
	int u,v,w;
}q[N];
int w[N];
int del[N];
int ans[N];  
int n;
int dis[N];
int size[N]; 
int f[N];
unordered_map<int,int> Xor[N];
void init(){
	cin>>n;
	for(int i=1;i<=n-1;i++){
		cin>>q[i].u>>q[i].v>>q[i].w;
	}
	for(int i=1;i<=n-1;i++){
		cin>>del[i];
	}
	for(int i=1;i<=n;i++){
		Xor[i][0]++;//初始每个点为自己的根,到自己的距离为0
		dis[i]=0;
		f[i]=i;
		size[i]=1;
	}
	memset(h,-1,sizeof h);
}
int find(int a){
	if(f[a]==a) return a;
	return f[a]=find(f[a]);
}
int now;
void dfs(int u,int fa,int x)
{
	ans[now]+=Xor[find(fa)][x];//联通块内满足要求的点的数量 
	dis[u]=x;
	f[u]=f[find(fa)];
	for(int i=h[u];~i;i=e[i].next){
		int v=e[i].to;
		if(v==fa){
			continue;
		}
		dfs(v,u,x^e[i].w);
	}
}
void dfs1(int u,int fa){
	//将新的点加入
	Xor[find(u)][dis[u]]++; 
	size[find(u)]++;
	for(int i=h[u];~i;i=e[i].next){
		int v=e[i].to;
		if(v==fa){
			continue;
		}
		dfs1(v,u);
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);     cout.tie(0);
	init();
	for(int i=n-1;i>=1;i--){
		now=i;
		ans[i]=ans[i+1];
		int u=q[del[i]].u;
		int v=q[del[i]].v;
		add(u,v,q[del[i]].w);
		add(v,u,q[del[i]].w);
		if(size[find(u)]>size[find(v)]){
			dfs(v,u,dis[u]^q[del[i]].w);
			dfs1(v,u); 
		}
		else{
			dfs(u,v,dis[v]^q[del[i]].w);
			dfs1(u,v); 
		}
	}
	for(int i=1;i<=n-1;i++){
		cout<<ans[i]<<endl;
	}
	cout<<"0"<<endl;
	return 0;
}
```

---

## 作者：Feyn (赞：3)

[link](https://www.luogu.com.cn/problem/P8047)

经典思路，正难则反。一般而言合并两个集合总是比拆分两个集合来得容易的，于是考虑从 $N$ 个散点开始，把删边操作改成加边操作然后统计答案。然后由于是树，每次加边都一定会是合并两个不相交的集合，这样一来就可以用到启发式合并了。

现在剩下的唯一问题就是如何统计答案了。显然两个点在同一个集合内的答案已经累加过了，所以考虑如何求得两个点分属两个集合的方案。由于是启发式合并，考虑先确定小集合内一个点作为方案的一个点，然后思考如何快速求得大集合内有多少点可以和这个点配对即可。放个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/tekpsd49.png)

个人感觉挺简单明了的。紫色是合并的两个点，绿色是一种合法的方案，两个框框自然是两个还未合并的集合啦。

当我吗遍历小集合的时候可以轻松求得上紫点到上绿点的异或值，假设为 $A$ 。假设粉边是 $B$，那么一个合法的下绿点应该满足它到下紫点的路径异或和 $C=A\oplus B$ 。现在问题来了，咋快速地求 $C$ 的值呢？重新遍历一遍还不如打暴力。为了解决这个问题，我们假设已经求得了下绿点到黑点的值（怎么求得后面说） $D$ 和下紫点到黑点的值 $E$ ，根据异或的基本性质显然有 $C=D\oplus E$，那么我们希望求的东西就转变成了满足 $D_i\oplus E=A\oplus B$，即 $D_i=A\oplus B\oplus E$ 的 $i$ 的个数，这就可以直接用 map 来统计了。

然后呢考虑前面留下的问题，怎么求出每个点到黑点的值呢？已知紫点到黑点的值和紫点到上绿点的值可以很容易求得黑点到上绿点的值，这可以在遍历小集合的时候求出。所以发现每次合并都相当于是求出每个新加入集合的点到黑点的值，这样就可以快速求解啦。

复杂度 $O(N\log N^2)$。代码还是挺好写的。

```cpp
#include<bits/stdc++.h>
//#define feyn
#define int long long
const int N=100010;
using namespace std;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}
inline void swap(int &s1,int &s2){
	int s3=s1;s1=s2;s2=s3;return;
}

int m,sk[N],an[N],ans;
struct node{
	int a,b,val;
}se[N];

struct edge{
	int t,v,next;
}e[N<<1];
int head[N],esum;
inline void add(int fr,int to,int val){
	e[++esum]=(edge){to,val,head[fr]};head[fr]=esum;
}

int f[N];
inline int find(int wh){
	return f[wh]==wh?wh:f[wh]=find(f[wh]);
}

map<int,int>d[N];
int dis[N],size[N];
inline void dfs(int wh,int now_dis,int fa,int data,int pl){
	dis[wh]=now_dis^data;ans+=d[pl][dis[wh]];
	for(int i=head[wh],th;i;i=e[i].next){
		if((th=e[i].t)==fa)continue;
		dfs(th,(now_dis^e[i].v),wh,data,pl);
	}
}
inline void add_data(int wh,int fa,int pl){
	d[pl][dis[wh]]++;
	for(int i=head[wh],th;i;i=e[i].next){
		if((th=e[i].t)==fa)continue;
		add_data(th,wh,pl);
	}
}

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);
	for(int i=1;i<=m;i++)f[i]=i,size[i]=1,d[i][0]=1;
	for(int i=1;i<m;i++){
		read(se[i].a);read(se[i].b);read(se[i].val);
	}
	for(int i=1;i<m;i++)read(sk[m-i+1]);
	for(int i=2;i<=m;i++){
		int j=i;i=sk[i];
		int a=se[i].a,b=se[i].b;
		//printf("now:%lld %lld %lld\n",a,b,se[i].val);
		int fa=find(a),fb=find(b);
		if(size[fa]<size[fb])swap(a,b),swap(fa,fb);
		f[fb]=fa;size[fa]+=size[fb];d[fb].clear();
		
		int dd=dis[a];
		dfs(b,0,0,dd^se[i].val,fa);
		add_data(b,0,fa);
		add(a,b,se[i].val);add(b,a,se[i].val);
		an[j]=ans;i=j;
	}
	for(int i=m;i;i--)printf("%lld\n",an[i]);
	
	return 0;
}
```

---

## 作者：Computer1828 (赞：2)

删边不好做，正难则反，倒着就是加边，加边，加边，并查集查询。

考虑加边会贡献多少，显然是一边某个点 $u'$ 经过新连的边 $(u,v)$ 连到另一边某个点 $v'$ 的路径异或和是零才会有贡献。

直接计算这个贡献不好算，我们考虑放在完整的树上计算。假设我们有一个完整的树，点 $u$ 到根的路径异或和叫做 $dis[u]$，那么我们要计算的就是有多少个点 $v'$ 满足 $dis[u'] \oplus dis[u] \oplus w \oplus dis[v] = dis[v']$。

然后就对 $dis[u]$ 进行启发式合并就行了。

代码中 $mp[u][dis] = num$ 表示以 $u$ 为根的并查集里所有点到整棵树的根路径异或和是 $dis$ 的点个数是 $num$。
```cpp
#include<bits/stdc++.h>
#define N 100005
#define ll long long
using namespace std;
int n;ll ans[N];
struct edge{int to,nxt,w;}e[N*2];
int hed[N],cnt;
inline void add(int u,int v,int w){
	e[++cnt] = (edge){v,hed[u],w};
	hed[u] = cnt;
}
int dis[N];
inline void dfs(int u,int ff){
	for(int i = hed[u];i;i = e[i].nxt){
		int v = e[i].to,w = e[i].w;
		if(v != ff) dis[v] = dis[u]^w,dfs(v,u);
	}
}
int a[N],b[N],w[N],p[N];
map<int,int> mp[N];
map<int,int>::iterator it;
int fa[N],si[N];
inline int getf(int x){
	if(x == fa[x]) return x;
	return fa[x] = getf(fa[x]);
}
inline ll merge(int u,int v,int w){
	int x = getf(u),y = getf(v);
	ll res = 0;
	if(x != y){
		if(si[x] < si[y]) swap(x,y),swap(u,v);
		fa[y] = x,si[x] += si[y];
		for(it = mp[y].begin();it != mp[y].end();it++){
			int np = it->first;
			np = np^dis[v]^w^dis[u];
			if(mp[x].count(np)) res += 1ll*(it->second)*mp[x][np];
		}
		for(it = mp[y].begin();it != mp[y].end();it++) mp[x][it->first] += (it->second);
	}
	return res;
}
int main(){
	scanf("%d",&n);
	for(int i = 1;i<n;++i) scanf("%d%d%d",a+i,b+i,w+i),add(a[i],b[i],w[i]),add(b[i],a[i],w[i]);
	dfs(1,0);
	for(int i = 1;i<=n;++i) fa[i] = i,si[i] = 1,mp[i][dis[i]] = 1;
	for(int i = 1;i<n;++i) scanf("%d",p+i);
	for(int i = n-1;i;--i) ans[i] = ans[i+1]+merge(a[p[i]],b[p[i]],w[p[i]]);
	for(int i = 1;i<=n;++i) printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：_Kenma_ (赞：1)

## 前言

大量 trick 拼接在了一起，很久没见过这样的缝合怪了。

但是题目感觉出的还可以，比较自然。

## 思路分析

树上路径异或和为 $0$ 是一个 trick，我们利用树上前缀和转化为判断两点点权是否相等。

时光倒流是一个 trick，因为删边难做，考虑离线下来从后往前加边。

并查集启发式合并是一个 trick，考虑用 map 维护相同点权的点的个数，合并时让小的往大的中插入，复杂度多一个 $\log$。

然后就做完了，总体复杂度 $O(n \alpha(n) \log n)$。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x[100005],y[100005],p[100005],w,sum;
int head[100005],nxt[200005],targetx[200005],targetw[200005],tot;
void add(int x,int y,int w){
	tot++;
	nxt[tot]=head[x];
	head[x]=tot;
	targetx[tot]=y;
	targetw[tot]=w;
}
int a[100005],ans[100005];
void dfs(int x,int fa){
	for(int i=head[x];i;i=nxt[i]){
		int y=targetx[i],w=targetw[i];
		if(y==fa) continue;
		a[y]=a[x]^w;
		dfs(y,x);
	}
}
int fa[100005];
map<int,int> mp[100005];
void init(){
	for(int i=1;i<=n;i++){
		fa[i]=i;
		mp[i][a[i]]=1;
	}
}
int find(int x){
	if(fa[x]==x) return x;
	else return fa[x]=find(fa[x]);
}
void merge(int x,int y){
	x=find(x);
	y=find(y);
	if(mp[x].size()<mp[y].size()) swap(x,y);
	fa[y]=x;
	for(map<int,int>::iterator it=mp[y].begin();it!=mp[y].end();it++){
		sum+=mp[x][it->first]*(it->second);
		mp[x][it->first]+=it->second; 
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>x[i]>>y[i]>>w;
		add(x[i],y[i],w);
		add(y[i],x[i],w);
	}
	dfs(1,0);
	init();
	for(int i=1;i<n;i++){
		cin>>p[i];
	}
	for(int i=n-1;i>=1;i--){
		ans[i+1]=sum;
		merge(x[p[i]],y[p[i]]);
	}
	ans[1]=sum;
	for(int i=1;i<=n;i++){
		cout<<ans[i]<<'\n';
	}
	return 0;
}
```

## 后记

我愿称之为并查集常见 trick 大一统题。

---

## 作者：X____ (赞：1)

# P8047 [COCI2015-2016#4] GALAKSIJA

### 题目大意

给定一棵树，每次删边并询问边权异或和为零的路径数量。

### 解题思路

首先观察到每次询问路径异或和为零的数量，显然可以转化为前缀异或和，可以先将前缀异或和预处理出来。

再观察到每次删除边并不是很好维护，那么可以转化为一次次添边。

那么问题就转化为增添一条新边会产生多少贡献。

因为所给的图是一棵树，所以每次加边必然会连接两个不相交的集合，显然加的边只会对连接的这两个集合产生贡献。

![](https://cdn.luogu.com.cn/upload/image_hosting/osg3k602.png?x-oss-process=image/resize,m_lfit,h_500,w_700)

设新加了一条边权为 $w$ 的边，其连接节点 $u$ 和 节点 $v$，其中节点 $x$ 到节点 $y$ 的边权异或和为 $0$。设 $f_x$ 表示节点 $x$ 到根节点的异或和，易得 $f_x \oplus f_u \oplus w \oplus f_v \oplus f_y = 0$。

那么我们只需要求得对于节点 $u$ 所在的集合中的任意一个节点 $x$ ，在节点 $v$ 所在的集合中有多少个节点 $y$ 满足 $f_u \oplus w \oplus f_v \oplus f_y = f_x$。

用 $m_{u,k}$ 表示以节点 $u$ 为根节点的子树中，到根节点 $u$ 的异或值为 $k$ 的节点个数，用 $map$ 来维护。

代码如下：

```cpp
#define F(i, l, r) for(int (i) = (l); (i) <= (r); (i) ++)
map<int, int>mp[N];
map<int, int>::iterator it;
void dfs(int x, int f) {
	for(int i = head[x]; i; i = e[i].nxt) {
		int to = e[i].to;
		if(to == f) continue;
		dis[to] = dis[x] ^ e[i].w;
		dfs(to, x);
	}
}
int Find(int x) {
	return fa[x] == x ? x : fa[x] = Find(fa[x]);
}
ll merge(int x, int y, int z) {
	int fx = Find(x), fy = Find(y);
	ll res = 0;
	if(fx != fy) {
        //启发式合并
		if(siz[fx] < siz[fy]) {
			swap(x, y);
			swap(fx, fy);
		}
		fa[fy] = fx;
		siz[fx] += siz[fy];
		for(it = mp[fy].begin(); it != mp[fy].end(); it ++) {
			int now = it->first;
			now = now ^ dis[x] ^ z ^ dis[y];
            //求在该集合中满足 dis[x]^dis[fx]^z^dis[fy]^dis[y] = 0 的数量
			if(mp[fx].count(now)) res += 1ll * mp[fx][now] * (it -> second);
		}
        //将 y 所在的集合中的节点数据更新到 x 的所在集合中
		for(it = mp[fy].begin(); it != mp[fy].end(); it ++) {
			mp[fx][it->first] += mp[fy][it->first];
		}
	} 
	return res;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n;
	cin >> n;
	F(i, 1, n-1) {
		cin >> u[i] >> v[i] >> w[i];
		add(u[i], v[i], w[i]);
		add(v[i], u[i], w[i]);
	}
	dfs(1, 0);
	F(i, 1, n) fa[i] = i, siz[i] = 1, mp[i][dis[i]] = 1;
	F(i, 1, n-1) cin >> p[i];
	for(int i = n-1; i >= 0; i --) {
		ans[i] = ans[i+1] + merge(u[p[i]], v[p[i]], w[p[i]]);
	}
	F(i, 1, n) cout << ans[i] << "\n";
	return 0;
}
```

---

## 作者：operator_ (赞：1)

# P8047 [COCI2015-2016#4] GALAKSIJA

[题目传送门](https://www.luogu.com.cn/problem/P8047)

## 题解

显然是要删边变加边的，然后联通性也是显然要用并查集维护的，就是路径异或和需要一个数据结构来维护。

发现：加边删边不影响两个点的路径异或和。所以我们可以处理出每个点到 $1$ 号节点的路径异或和 $d$，于是 $Path_{u,v}=d_u\operatorname{xor}d_v$，我们需要支持的就是查询在两个集合中分别取一个点使其 $d$ 相等的方案数，用 map 启发式合并即可。由于复杂度瓶颈不在合并而在查询，所以可以直接把其中一个 map 所有点丢到另一个里，手写合并也不会更优。

时间复杂度 $O(n\log^2n)$。

代码：

```cpp
/*
 * @Author: operator_ 
 * @Date: 2024-01-09 12:45:43 
 * @Last Modified by: operator_
 * @Last Modified time: 2024-01-09 13:18:26
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int rd() {
    int s=0,m=0;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')m=1;ch=getchar();}
    while( isdigit(ch)) s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
    return m?-s:s;
}
int n,u[100005],v[100005],w[100005],p[100005],d[100005],Ans[100005];
vector<int> g[100005],gw[100005];
void dfs(int u,int fa) {
    for(int i=0;i<g[u].size();i++) if(g[u][i]!=fa) 
        d[g[u][i]]=d[u]^gw[u][i],dfs(g[u][i],u);
}
int f[100005];map<int,int> mp[100005];
int Find(int x) {return f[x]==x?x:f[x]=Find(f[x]);}
signed main(){
    cin>>n;
    for(int i=1;i<n;i++) {
        u[i]=rd(),v[i]=rd(),w[i]=rd();
        g[u[i]].push_back(v[i]),gw[u[i]].push_back(w[i]);
        g[v[i]].push_back(u[i]),gw[v[i]].push_back(w[i]);
    }
    dfs(1,0);
    for(int i=1;i<n;i++) p[i]=rd();
    for(int i=1;i<=n;i++) f[i]=i,mp[i][d[i]]++;
    for(int i=n-1;i;i--) {
        Ans[i]=Ans[i+1];
        int x=Find(u[p[i]]),y=Find(v[p[i]]);
        if(mp[x].size()>mp[y].size()) swap(x,y);f[x]=y;
        for(auto it=mp[x].begin();it!=mp[x].end();it++)
            Ans[i]+=mp[y][it->first]*it->second,mp[y][it->first]+=it->second;
    }
    for(int i=1;i<=n;i++)
        printf("%lld\n",Ans[i]);
    return 0;
}
```

---

## 作者：zsq147258369 (赞：1)

摧毁一条边不太好搞，那就时光回溯，从后面往前面做，摧毁一条边相当于出现一条边。

连一条边 $(u,v)$，考虑合并这两个点所在的点集。

在连这条边之前，已经求出了点集 $u$ 和 $v$ 内部对答案的贡献，要处理的是跨过边 $(u,v)$ 的点对的贡献，再加到总答案里。

对于 $u$ 和 $v$ 的点集可以分别建棵 01tire，存每个点到 $u$ 的异或值，然后 dfs 一遍，求出相同的数的个数再乘起来即可。

我们不可能每次都建两颗树。考虑开始时建 $n$ 棵树，每棵树先存一个 $0$，然后再合并两棵树。

每棵树存的就应该是点到点集中的根的异或值，换根就把树全局异或 $fir_{root}~\text{xor}~fir_u$（$fir_u$ 表示 $u$ 到 $1$ 的异或值）。

合并时，因为 $u$ 为 $v$ 的父亲，故 $v$ 即为该点集的根，把 $v$ 点集的树全局异或个 $fir_{root_u}~\text{xor}~fir_u~\text{xor}~w_{u,v}$ 即可表示每个点到 $u$ 的根的异或值，再用线段树合并的方法合并。记得记录一个 $la$ 标记表示该节点子树要全异或的值，每次访问下传标记即可。

# $code$

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+50;

struct node
{
	int u,v,w,nxt;
}e[N<<1];

int n,cnt,head[N],t[N*36][3],rev[N*36],tot,ro[N],fa[N],a[N],fir[N];
ll ans,res[N];

void add(int u,int v,int w)
{
	e[++cnt]=(node){u,v,w,head[u]};head[u]=cnt;
	e[++cnt]=(node){v,u,w,head[v]};head[v]=cnt;
}

void dfs(int x)
{
	for(int i=head[x];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa[x])continue;
		fa[v]=x;fir[v]=fir[x]^e[i].w;
		dfs(v);
	}
}

int find(int x)
{
	return x==ro[x]?x:(ro[x]=find(ro[x]));
}

void down(int x,int dep)
{
	if(!rev[x])return;
	if((rev[x]>>dep)&1)swap(t[x][0],t[x][1]);
	rev[t[x][0]]^=rev[x];
	rev[t[x][1]]^=rev[x];
	rev[x]=0;
	return;
}

ll dfss(int a,int b,int dep)
{
	if(dep==-1)return 1ll*t[a][2]*t[b][2];
	down(a,dep),down(b,dep);
	ll ans=0;
	if(t[a][0]&&t[b][0])ans+=dfss(t[a][0],t[b][0],dep-1);
	if(t[a][1]&&t[b][1])ans+=dfss(t[a][1],t[b][1],dep-1);
	return ans;
}

void build(int x)
{
	for(int i=31;i>=0;i--)
	{
		t[x][0]=++tot;
		x=tot;
	}
	t[x][2]++;
}

void Add(int a,int b,int dep)
{
	if(dep==-1)
	{
		t[a][2]+=t[b][2];
		return;
	}
	down(a,dep),down(b,dep);
	if(t[a][0]&&t[b][0])Add(t[a][0],t[b][0],dep-1);
	if(t[a][1]&&t[b][1])Add(t[a][1],t[b][1],dep-1);
	if(!t[a][0]&&t[b][0])t[a][0]=t[b][0];
	if(!t[a][1]&&t[b][1])t[a][1]=t[b][1];
	return;
}

void merge(int u,int v,int w)
{
	int ru=find(u),rv=v;
	int re=fir[u]^fir[ru]^w;
	rev[v]^=re;
	ans+=dfss(ru,v,31);Add(ru,v,31);
	ro[v]=ru;
}

main()
{
	std::ios::sync_with_stdio(false);
    std::cin.tie(0);
	cin>>n;
	int u,v,w;
	for(int i=1;i<n;i++)
	{
		cin>>u>>v>>w;
		add(u,v,w);
	}
	for(int i=1;i<=n;i++)ro[i]=i;
	dfs(1);tot=n;
	for(int i=1;i<=n;i++)build(i);
	for(int i=1;i<n;i++)cin>>a[i];
	for(int i=n-1;i;i--)
	{
		u=e[a[i]*2].u,v=e[a[i]*2].v,w=e[a[i]*2].w;
		if(v==fa[u])swap(u,v);
		merge(u,v,w);
		res[i]=ans;
	}
	for(int i=1;i<=n;i++)cout<<res[i]<<'\n';
}
```

---

## 作者：内拉组里 (赞：0)

一道启发式合并好题。

# Thoughts :

首先对题目中的几个条件进行分析。

- $ A \neq B $，废话。

- 行星 $ A,B $ 可以互相到达。

  涉及到连通性问题，应该能想到 DSU 并查集吧。

- 行星 $ A,B $ 之间的路径上的所有边的权值的**异或和**等于 $ 0 $。

  被异或折磨过的应该都能想到，算出每条边到根的异或和即可实现。

  原理就是两行星的 $ lcp $ 到根的异或和会被计算两次，相互抵消了。

这里涉及到的**摧毁**操作不太好实现，故考虑离线倒着做。

每次连接两行星，在合并的同时计算多出来的**无聊的**行星对。

异或和部分很简单，这里就不展开了。

本文主要讲一下 DSU 中的 unite 函数，其他的都是板子。

当合并两颗行星时，实际上是在合并以两颗行星为根的树。

考虑开个 map，$ mp[i][j] $ 记录以 $ i $ 为根的子树中到 $ i $ 的异或和为 $ j $ 的叶子结点数。

那么新增加的**无聊的**行星对数就是两颗行星的 mp 中异或和对应处数量相乘（乘法原理）。

每一次先计算增加的**无聊的**行星对数再合并即可。

算一下时间复杂度，最坏情况下，共 $ \Theta (N) $ 次合并，每次需要遍历 $ \Theta (N) $ 个叶子结点。

$ \Theta (N^2) $？你搞笑吧，这能过 :) 

别忘了最前面还提到一个非常关键的思想：**启发式合并**。

怎么启发。

观察到合并时会 $ \Theta (N) $ 地遍历其中一个节点，而 $ \Theta (\log{N}) $ 地在另一个节点的 mp 中查找。

故考虑在轻节点中遍历，在重节点中查找。

再算一下时间复杂度，

这种算法下的最坏情况时两棵树大小相近，那就形成了一个接近满二叉树。

故合并的平均时间复杂度就是 $ \log{N} $，收工。

# Analyses :

> 总时间复杂度 $ \Theta (N \log{N}) $ 
>
> 总空间复杂度 $ \Theta (N) $ 

# Code :

```cpp
#include	<iostream>
#include	<vector>
#include	<map>
#define		int		long long
using namespace std;
using pii = pair<int,int>;
constexpr int maxn = 1e5+4;

int n;
int q[maxn];
pii e[maxn];
int xr[maxn];
int ans[maxn];
vector<pii> G[maxn];	//destination,distance
map<int,int> mp[maxn];
namespace DSU
{
	int rt[maxn];
	
	void init (int n)
	{
		for (int i = 1; i <= n; i++)
		{
			rt[i] = i;
			mp[i][xr[i]] = 1;
		}
	}
	
	int find (int x)
	{
		if (rt[x] == x) return x;
		return rt[x] = find (rt[x]);
	}
	
	void unite (int x, int y, int &ans)
	{
		x = find (x);
		y = find (y);
		if (x == y) return ;
		if (mp[x].size() > mp[y].size()) swap (x, y);
		for (auto i : mp[x])
		{
			ans += i.second * mp[y][i.first];
			mp[y][i.first] += i.second;
		}
		rt[x] = y;
	}
}
using namespace DSU;

void build (int u, int rt)
{
	for (auto i : G[u]) if (i.first != rt)
	{
		xr[i.first] = xr[u] ^ i.second;
		build (i.first, u);
	}
}

signed main (void)
{
	cin >> n;
	for (int w, i = 1; i < n; i++)
	{
		cin >> e[i].first >> e[i].second >> w;
		G[e[i].first].push_back({e[i].second, w});
		G[e[i].second].push_back({e[i].first, w});
	}
	build (1, 0);		/* free to choose the root */
	for (int i = 1; i < n; i++) cin >> q[i];
	init (n);
	for (int i = n - 1; i; i--) unite (e[q[i]].first, e[q[i]].second, ans[i] = ans[i + 1]);
	for (int i = 1; i <= n; i++) cout << ans[i] << endl;
	return 0;
}
```

---

## 作者：CatFromMars (赞：0)

经典套路题。

如果没有删边操作，对全局进行统计怎么办？对于无根树假定 $1$ 为根，令 $d_u$ 为 $1$ 到 $u$ 边权的异或和，那么 $u$ 到 $v$ 路径上边的异或和就是 $(d_u \operatorname{xor} d_{c}) \operatorname{xor} (d_v \operatorname{xor} d_{c}) = d_u \operatorname{xor} d_v$。其中 $c$ 是 $u,v$ 的 LCA。对于 $d_u\operatorname{xor} d_v = 0$ 即 $d_u = d_v$，问题转化为统计有多少点对满足 $d_u = d_v$，用哈希表维护即可。

加上了删边操作，参考[这道题](https://www.luogu.com.cn/problem/P1197)倒序操作，将删边改为加入边，不难发现要求合并后的两点要在同一个连通分量中才会被统计。

因此用并查集维护每个点在哪个连通分量，用对于每一个联通分量维护一个哈希表，当遇到加边，即合并两个联通分量，启发式合并（将小的哈希表合并到大的哈希表里面）即可。时间复杂度是 $O(n\log_2 n)$。

代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5;
struct node {
	int to, val;
	node(int T, int V) {
		to = T, val = V;
	}
};
vector <node> gra[N + 10];
void link(int x, int y, int z) {
	gra[x].push_back(node(y, z));
	gra[y].push_back(node(x, z));
}

int d[N + 10];
void getd(int u, int fa) {
	for(int i = 0; i < gra[u].size(); i++) {
		int v = gra[u][i].to, w = gra[u][i].val;
		if(v == fa) continue;
		d[v] = d[u] ^ w;
		getd(v, u);
	}
}
int n;
int X[N + 10], Y[N + 10], P[N + 10];

int fa[N + 10], siz[N + 10];   
int Find(int x) {//并查集维护所在联通分量编号。
	if(x == fa[x]) return x;
	else return Find(fa[x]);
}
unordered_map <int, int> mp[N + 10];
ll sum = 0;
ll ans[N + 10];
void Union(int u, int v) {
	int U = Find(u), V = Find(v);
	if(siz[U] > siz[V]) {
		swap(u, v);
		swap(U, V);
	}

	for(unordered_map <int, int>::iterator it = mp[U].begin(); it != mp[U].end(); it++) {//统计合并后增加的点对
		int a = (it -> first), b = (it -> second);
		sum += ((ll)b * (ll)mp[V][a]);
	}
	for(unordered_map <int, int>::iterator it = mp[U].begin(); it != mp[U].end(); it++) {//合并哈希表
		int a = (it -> first), b = (it -> second);
		mp[V][a] += b;
	}
	mp[U].clear();
	fa[U] = V;
	siz[V] += siz[U];
}

void work() {
	getd(1, 0);
	for(int i = 1; i <= n; i++) {
		fa[i] = i, siz[i] = 1;
		mp[i][d[i]] = 1;
	}

	for(int i = n - 1; i >= 1; i--) {
		int u = X[P[i]], v = Y[P[i]];
		Union(u, v);
		ans[i] = sum;
	}
	for(int i = 1; i <= n - 1; i++)
		cout << ans[i] << '\n';
	cout << 0 << '\n';
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1, w; i < n; i++) {
		cin >> X[i] >> Y[i] >> w;
		link(X[i], Y[i], w);
	}
	for(int i = 1; i <= n - 1; i++)
		cin >> P[i];
	work();
}
```

---

## 作者：happybob (赞：0)

考虑倒着做，将删边变成加边，用并查集启发式合并维护并且在合并时更新贡献。

考虑现在有两个集合 $S$ 和 $T$，设两点树上距离为 $dis(u, v)$，则添加一条边时添加的贡献为 $\sum \limits_{(u,v)(u\in S,v\in T)}[dis(u,v)=0]$。

把 $dis$ 变成树上前缀和异或的形式，设 $s_u$ 表示 $u$ 到根的路径异或和。则原式变成 $\sum \limits_{(u,v)(u\in S,v\in T)}[s_u=s_v]$。并查集维护 $g_{u,x}$ 表示以 $u$ 为根的并查集中 $s_u=x$ 的 $u$ 的数量。启发式合并时枚举较小的那一个集合并累加贡献即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

struct Node
{
	int u, v, w;
	Node(int u, int v, int w): u(u), v(v), w(w){}
	Node() = default;
};

vector<Node> v;
int p[N];
int n;
long long ans = 0LL;
long long res[N];

int dis[N];
vector<pair<int, int>> G[N];

void dfs(int u, int f, int w)
{
	dis[u] = dis[f] ^ w;
	for (auto &[j, v] : G[u])
	{
		if (j ^ f) dfs(j, u, v);
	}
}

class Union_Find
{
public:
	int fa[N], sz[N];
	map<pair<int, int>, int> mp;
	vector<int> total[N];
	void Init()
	{
		for (int i = 0; i < N; i++) 
		{
			fa[i] = i, sz[i] = 1;
			if (i >= 1 && i <= n) mp[make_pair(i, dis[i])]++, total[i].emplace_back(i);
		} 
	}
	int find(int u)
	{
		return (fa[u] == u ? u : fa[u] = find(fa[u]));
	}
	void merge(int u, int v)
	{
		if ((u = find(u)) == (v = find(v))) return;
		if (sz[u] < sz[v]) swap(u, v);
		fa[v] = u;
		sz[u] += sz[v];
		for (auto &j : total[v])
		{
			total[u].emplace_back(j);
			ans += (mp.count(make_pair(u, dis[j])) ? mp[make_pair(u, dis[j])] : 0);
		}
		for (auto &j : total[v])
		{
			mp[make_pair(u, dis[j])]++;
			mp.erase(make_pair(j, dis[j]));
		}
		total[v].clear();
		total[v].shrink_to_fit(); 
	}
}uf;

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		Node g;
		cin >> g.u >> g.v >> g.w;
		v.emplace_back(g);
		G[g.u].emplace_back(make_pair(g.v, g.w));
		G[g.v].emplace_back(make_pair(g.u, g.w));
	}
	for (int i = 1; i < n; i++)
	{
		cin >> p[i];
	}
	dfs(1, 1, 0);
	uf.Init();
	for (int i = n - 1; i >= 1; i--)
	{
		uf.merge(v[p[i] - 1].u, v[p[i] - 1].v);
		res[i] = ans;
	}
	for (int i = 1; i < n; i++)
	{
		cout << res[i] << "\n";
	}
	cout << "0\n";
	return 0;	
} 
```


---

