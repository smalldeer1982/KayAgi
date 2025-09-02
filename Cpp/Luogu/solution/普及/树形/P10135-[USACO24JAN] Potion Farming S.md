# [USACO24JAN] Potion Farming S

## 题目描述

你正在玩你最喜欢的手机游戏。为了有机会击败传说中的奶牛 Boss，你正在试着刷药水。游戏地图是由 $N$（$2\le N\le 10^5$）个编号为 $1\ldots N$ 的房间组成，由 $N−1$ 条边连接，形成一棵树。

你可以通过一系列的「遍历」来探索地图。一次遍历是从房间 $1$ 到树中任何其他房间的一条简单路径。当你完成一次遍历后，你可以从房间 $1$ 再次开始遍历。一旦地图的每个房间都被至少一次遍历访问过，这个地图就通关了。你的主要目标是以最小的遍历次数通关这一地图。

你的次要目标是刷到尽可能多的药水。在一次遍历开始前，地图上的某个房间内会生成一瓶药水。你可以通过在当次遍历中访问生成药水的房间来拾取药水。如果你没有拾取药水，那么当次遍历结束它就会消失，你无法在未来的遍历中拾取它。

由于你是一位聪明的程序员，在查看游戏文件后，你成功知道了在接下来的 $N$ 次遍历之前药水的出现位置。如果你以最小的遍历次数通关地图，你可以从地图内刷到的最大药水数量是多少？ 

## 说明/提示

### 样例解释 1

在这个测试用例中，通关地图所需的最小遍历次数为 $3$。

一个在三次遍历中拾取两瓶药水的最佳方案如下：

- 遍历 $1$：$1\to 3\to 5$（于房间 $5$ 拾取药水）
- 遍历 $2$：$1\to 3\to 4$（于房间 $4$ 拾取药水）
- 遍历 $3$：$1\to 2$（被迫通关地图，无视房间 $3$ 的药水）

或者，我们也可以计划我们的遍历如下：

- 遍历 $1$：$1\to 2$（没有药水）
- 遍历 $2$：$1\to 3\to 4$（于房间 $4$ 拾取药水）
- 遍历 $3$：$1\to 3\to 5$（于房间 $3$ 拾取药水）

### 测试点性质

- 测试点 $2-7$：$N\le 1000$。
- 测试点 $8-15$：没有额外限制。

## 样例 #1

### 输入

```
5
5 4 3 2 1
1 2
1 3
3 4
3 5```

### 输出

```
2```

# 题解

## 作者：Loser_Syx (赞：9)

我们考虑最小的遍历次数如何得来，应该是要每个节点都被访问过且遍历链的次数最少，那么我们就应该要让链最长，显然是需要一口气遍历一个最长的链，也就是到叶子结点，那么最小遍历次数应为叶子结点个数。

因为最小遍历次数是叶子节点个数，所以只有 $p_1 \sim p_{cnt}$ 对答案有效，$cnt$ 为叶子结点个数。

因为每个叶子节点只会被遍历到一次，所以不妨初始时将叶子节点视为一个可行方案进行 dp。  
具体地，按深度由深到浅的顺序进行 dp，每次将当前节点的方案数转移给它的父亲，这个是每个父亲所拥有的叶子节点个数（被遍历到的次数）。

我们再来考虑如何得到答案，首先记录 $p_1 \sim p_{cnt}$ 的药水会生成在哪里，然后在 dp 过程中求解。  
因为我们是按照深度从深到浅 dp 的，所以如果当前 $i$ 有剩余的没有遍历过的叶子节点，且 $i$ 会生成药水，那么我们就可以领取 $i$ 上部分的药水（越多越好），不过方案数也要减去对应数量，所以我们 dp 转移的并非叶子结点个数，而是剩余没有遍历到过的叶子结点个数。  
不妨想想为什么是对的，因为当前节点 $i$ 的子树被遍历过了（深度原因），而我们的 $i$ 的子树内，一定是不能再获得药水了的情况，而如果我们不拿 $i$ 的药水或是不最大化拿的数量的话，可能会导致 $i$ 的祖先的某个节点，方案数多于其药水数，而不能达到最大化的效果。

至此，复杂度 $O(n)$，可以通过。

```cpp
const int N=1e5+19;
int p[N], cnt[N], dep[N], tot, mx, f[N], fa[N];
vector<int> g[N], depid[N];
void dfs(int u, int fat) {
	dep[u] = dep[fat]+1;
	fa[u] = fat;
	mx = max(dep[u], mx);
	depid[dep[u]].emplace_back(u);
	bool flg=0;
	for (const int i : g[u]) {
		if (i != fat) dfs(i, u), flg=1;
	}
	if (!flg) {
		tot++; f[u]++; 
	}
}
signed main() {
	int n = read();
	for (int i=1;i<=n;++i) read(p[i]);
	for (int i=1;i<n;++i) {
		int a, b; read(a, b);
		g[a].emplace_back(b);
		g[b].emplace_back(a);
	}
	dfs(1, 1);
	for (int i=1;i<=tot;++i) cnt[p[i]]++;
	int ans=0;
	while (mx) {
		for (const int i : depid[mx]) {
			if (f[i]) {
				if (cnt[i] <= f[i]) f[i] -= cnt[i], ans += cnt[i];
				else ans += f[i], f[i] = 0;
			}
			f[fa[i]] += f[i];
		}
		--mx;
	}
	write(ans, '\n');
	return 0;
}
```

---

## 作者：Genius_Star (赞：8)

### 思路：

#### 贪心法：

注意到“最小的遍历次数”就是“树中叶子节点”的个数 $k$。

因为顺序是不重要的，所以就按照从左到右进行，那么路线就固定了，我们要做的就是将前 $k$ 个药水放在树上去。

考虑贪心，如果一条路径上有多瓶药水时，显然放深度最大的是最优的，那么线段树维护一下即可。

时间复杂度为 $O(N \log N)$。

**这个写的有点儿丑，代码就不放了。**

#### 树形 DP：

定义 $p_u$ 表示 $u$ 这个子树内叶子节点的个数（即经过 $u$ 点的路径条数），定义 $dp_u$ 表示 $u$ 这个子树内得到的最大药水数量。

前者可以 dfs 一遍得到；后者初始先将 $dp_{a_i} \to 1$，满足 $1 \le i \le k$，即将药水先放上去。

然后状态转移方程为：

$$dp_u=\min(\sum_{v \in E_u} dp_v,p_u)$$

就是看对于每一个儿子子树的答案累加起来，因为最多经过该点 $p_u$ 次，所以要取一个 $\min$。

时间复杂度为 $O(N)$。

### 树形 DP 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=100100;
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
ll n,x,ans=0,cnt=0;
ll a[N],p[N],dp[N];
vector<ll> E[N];
bool f[N];
void add(ll u,ll v){
	E[u].push_back(v);
	E[v].push_back(u);
}
ll dfs1(ll u,ll fa){
	ll son=0;
	for(auto v:E[u]){
		if(v==fa)
		  continue;
		son++;
		p[u]+=dfs1(v,u);
	}
	if(!son){
		cnt++;
		p[u]=1;
   }
	return p[u];
}
void dfs2(ll u,ll fa){
	for(auto v:E[u]){
		if(v==fa)
		  continue;
		dfs2(v,u);
		dp[u]+=dp[v];
	}
	dp[u]=min(dp[u],p[u]);
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)
	  a[i]=read();
	for(int u,v,i=1;i<n;i++){
		u=read(),v=read();
		add(u,v); 
	}
	dfs1(1,0);
	for(int i=1;i<=cnt;i++)
	  dp[a[i]]++;
	dfs2(1,0);
	write(dp[1]);
	return 0;
}
```


---

## 作者：云雷心柠檬听 (赞：4)

[博客食用更佳](https://www.cnblogs.com/lemon-cyy/p/18010674)

### 题意简述

给点一棵有 $n$ 个节点的树，在每个时间点都会在某个节点出现一瓶药水，记 $p_i$ 为第 $i$ 个时间点出现药水的节点，定义一次遍历为从 $1$ 号节点走到任意节点，要求在遍历次数最少的情况下拾取最多数量的药水。

### 思维路径

首先我们要探讨遍历次数最少的状态是怎样的。由于每一次遍历都是从 $1$ 号节点开始，我们可以把整棵树看作根为 $1$ 的有根树。即要求用最少的从根出发的路径覆盖整棵树。

通过画图可以发现每次遍历都从根节点到叶节点是最优的，因为假如存在一次遍历从根节点到非叶节点，那么一定存在一条从根节点到其后代的叶节点的遍历完全覆盖它，一定不是最少的。

那么可以确定总的遍历次数为叶节点的个数，记为 $nleaf$，也就是说我们只需要考虑前 $n$ 个时间点出现的药水。注意可能有大于 $1$ 瓶药水出现在同一个节点，我在这上面挂了挺久。

接着就很明显是一个树上 dp 了。

定义 $f_i$ 表示以 $i$ 为根的子树中最多可以拿到 $f_i$ 瓶药水。

定义 $lf_i$ 表示以 $i$ 为根的子树中有 $lf_i$ 个节点是叶节点

那么 $f_i$ 的值就是 $\sum_{u \in son_i}f_u$ 和 $lf_i$ 中较小的值。最终的答案就是 $f_1$

### AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=200009;
ll n,a[N],t;
ll hd[N],nE,f[N],in[N],lf[N];
struct edge{
	ll to,nxt;
} e[N<<1];

void add(ll u,ll v){
	e[++nE]=(edge){v,hd[u]};
	hd[u]=nE;
}

void input(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin>>n;
	for(ll i=1;i<=n;i++) cin>>a[i];
	for(ll i=1;i<n;i++){
		ll u,v;
		cin>>u>>v;
		in[u]++; in[v]++;
		add(u,v);
		add(v,u);
	}
}

void dfs(ll u,ll fa){
	for(ll i=hd[u];i;i=e[i].nxt){
		ll v=e[i].to;
		if(v==fa) continue;
		dfs(v,u);
		f[u]+=f[v];
		lf[u]+=lf[v];
	}
	f[u]=min(f[u],lf[u]);
}

void solve(){
	for(ll i=2;i<=n;i++)if(in[i]==1){
		t++;
		lf[i]=1;
	}
	for(ll i=1;i<=t;i++) f[a[i]]++;
	dfs(1,0);
	cout<<f[1];
}

int main(){
	input();
	solve();
	return 0;
}
```

---

## 作者：gcx114514 (赞：4)

首先可以发现一颗树的最小遍历次数等于其叶子结点个数，且每个点的遍历次数等于其子树内的叶子节点个数。

我们假设共有叶子结点 $a$ 个，那么只有前 $a$ 个出现的药水才会被捡到。设 $le[x]$ 表示 $x$ 子树内的叶子结点个数，$ans[x]$ 表示 $x$ 子树内最多可以获得的药水个数，那么：
$$
ans[x]=\min(\sum_{to}ans[to],le[x])
$$

其中 $to$ 表示从1号开始遍历的 $x$ 的儿子，于是答案就为 $ans[1]$。

### code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int Max=1e5+10;

int b[Max];
int val[Max];

struct node{
	int to,next;
	node(int to=0,int next=0):
		to(to),next(next){;}
}a[Max<<1];
int head[Max],cnt;
void add(int x,int y){
	a[++cnt]=node(y,head[x]);
	head[x]=cnt;
}

int fl[Max],pos[Max],siz[Max];

void dfs(int now,int fa){
	siz[now]=val[now];
	for(int i=head[now];i;i=a[i].next){
		int to=a[i].to;
		if(to!=fa){
			dfs(to,now);
			siz[now]+=siz[to];
			fl[now]+=fl[to];
		}
	}
//	if(!tag){
//		fl[now]=1;
//	}
	siz[now]=min(siz[now],fl[now]);
}

int d[Max];

signed main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&b[i]);
	}
	for(int i=1;i<n;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
		d[x]++;
		d[y]++;
	}
	int res=0;
	for(int i=2;i<=n;++i){
		if(d[i]==1)res++,fl[i]++;
	}
	for(int i=1;i<=res;++i){
		val[b[i]]++;
	}
	dfs(1,0);
//	for(int i=1;i<=n;++i){
//		cout <<i<< ' '<< fl[i] << ' '<< siz[i]<< ' '<< pos[i]<< "\n";
//	} 
int ans=0;
//	for(int i=1;i<=n;++i){
//		ans=max(ans,siz[i]);
//	}
	printf("%d",siz[1]);
	
	return 0;
}
```

---

## 作者：1234567890regis (赞：3)

# 思路分析：
看着大佬们都用树上 dp，本蒟蒻终究还是蒟蒻，只会用 dfs。。。

首先，你会发现首先要求最小的遍历次数，否则如果遍历次数多一个，即使你能多捡好几瓶药水，都不是最优的。

而这个最小遍历次数是一个定值，而且是和药水位置无关的。而每次遍历，总是会刚好通过一个叶子结点。这说明最小遍历次数 $\ge$ 叶子结点的数量。

如果你把所有的叶子结点全部都遍历完，那么整个树也就遍历完了。所以最小遍历次数 $\le$ 叶子结点的数量。

以上就能说明，这个次数就是叶子结点的数量！可以对树进行 dfs，如果 用 `nols[i]` 表示 $i$ 结点下的叶子结点数量，那么容易写下如下代码：

```cpp
struct node {
	int fa = -1; // 表示节点的父亲
	vector<int> to; // 表示本结点所能达到的所有结点，包括父亲
};
vector<node> tree;
int dfs1(int start = 1) // 默认从根节点开始
{
	if (tree[start].to.size() == 1 && start != 1) // 如果是叶子结点
		return nols[start] = 1;
	int cnt = 0;
	for (int& i : tree[start].to)
		if (i != tree[start].fa)
			cnt += random_dfs1(i);
	return nols[start] = cnt;
}
```
请你不要忘记这个 `nols` 数组，之后我们还要用的。

这样，因为根节点是 $1$，所以叶子结点数量就是 $k=$ `nols[1]`。就这样，我们就可以过滤掉第 $k+1$ 到 $n$ 个时态出现的药水，这些药水我们捡不到。

那么怎样拿到更多的药水呢？不难发现，这些药水出现的顺序是无关紧要的，反证顺序可以变换。还有，在一个结点下的子树内捡到的药水数量一定要 $\le$ 子树的叶子结点数量，否则达不到最小遍历次数。

记 `pots[i]` 为第 $i$ 个结点总共出现了多少瓶药水，那么你会写下如下的代码：

```cpp
int dfs2(int start = 1) // 默认从根节点开始
{
	if (tree[start].to.size() == 1 && start != 1) // 如果是叶子结点
    	return min(pots[start], 1ll); // 0 或 1
	int cnt = 0;
	for (int& i : tree[start].to)
		if (i != tree[start].fa)
			cnt += random_dfs2(i); // 将子结点的药水数量加起来
	cnt += pots[start]; // 别忘加上自己的
	return min(cnt, nols[start]); // 一定要小于叶子结点数量，所以取 min
}
```

这样就差不多结束了。
# AC 代码：
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#define int long long
using namespace std;

const int MAXN = 1e5 + 7;
int temp[MAXN], nols[MAXN], pots[MAXN];

class Tree
{
private:
	const int n;
	int root;
public:
	struct node {
		int fa = -1;
		vector<int> to;
	};
	vector<node> tree;
	Tree(int n) : n(n), root(1) { tree = vector<node>(n + 1); }
	void init(int now, int father = -1)
	{
		tree[now].fa = father;
		for (int& i : tree[now].to)
			if (i != father)
				init(i, now);
	}
	void insert(int l, int r)
	{
		tree[l].to.push_back(r);
		tree[r].to.push_back(l);
	}
	int dfs1(int start = 1)
	{
		if (tree[start].to.size() == 1 && start != 1) return nols[start] = 1;
		int cnt = 0;
		for (int& i : tree[start].to)
		{
			if (i != tree[start].fa)
			{
				cnt += random_dfs1(i);
			}
		}
		return nols[start] = cnt;
	}
	int dfs2(int start = 1)
	{
		if (tree[start].to.size() == 1 && start != 1) return min(pots[start], 1ll);
		int cnt = 0;
		for (int& i : tree[start].to)
		{
			if (i != tree[start].fa)
			{
				cnt += random_dfs2(i);
			}
		}
		cnt += pots[start];
		return min(cnt, nols[start]);
	}
};

signed main()
{
	int n;
	cin >> n;
	Tree tr(n);
	for (int i = 1; i <= n; i++) cin >> temp[i];
	for (int i = 1; i < n; i++)
	{
		int l, r;
		cin >> l >> r;
		tr.insert(l, r);
	}
	tr.init(1); // 初始化树，这里不多说了
	// 初始化完毕
	int k = tr.dfs1(); // k 为最小遍历数
	for (int i = 1; i <= k; i++) pots[temp[i]]++;
	cout << tr.dfs2();
}
```

---

## 作者：封禁用户 (赞：2)

### 题意

懒得写了，而且也很简单

### 思路

我们看到这一句：**你的主要目标是以最小的遍历次数通关这一地图**

就是假设有 $x$ 个叶节点，我们就只能遍历 $x$ 次，并且 $P_{x+1} \sim P_{n}$ 我们都不用管。

接下来我们就可以把 $P_1 \sim P_x$ 和每个叶节点一一对应起来，但是怎么对应呢？

看一个图：~~其实就是样例~~

![](https://cdn.luogu.com.cn/upload/image_hosting/8w8esmum.png)

我们把每个点所能到达的叶节点个数算出来。

![](https://cdn.luogu.com.cn/upload/image_hosting/vr2o6qit.png)

对于每一次的药水，我们把节点 $1$ 到它的所有节点 $-1$，相当于从节点 $1$ 走到那里。

注意，这里不能走到叶节点，万一下次药水在叶节点上就走不到了。

于是我们可以得到这两张图

![](https://cdn.luogu.com.cn/upload/image_hosting/nw73nia3.png)![](https://cdn.luogu.com.cn/upload/image_hosting/msvour7i.png)

但是有时候 $1$ 到药水位置接着所能到的叶节点已经没有了，这时我们就不要这瓶药水了，因为**你的主要目标是以最小的遍历次数通关这一地图**。

上述的操作均可以用树剖解决。

### 代码
马蜂**有点丑**，能看则看。
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){f=c=='-'?-f:f;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return f*x;
}
const int N=1e5+5;
int n,h[N],t[N<<1],ne[N<<1],cnt,a[N],b[N],c__,ans;
int dep[N],si[N],fa[N],son[N],rev[N],top[N],seg[N];
int ad[N<<2],s[N<<2],w[N<<2],mi[N<<2];
int Min(int x,int y){return x<y?x:y;}
void _(int x,int y){
	t[++cnt]=y;
	ne[cnt]=h[x];
	h[x]=cnt;
}
void dfs(int u,int f){
	dep[u]=dep[f]+1;
	fa[u]=f;
	si[u]=1;
	for(int e=h[u];e;e=ne[e]){
		if(t[e]==f)continue;
		dfs(t[e],u);
		si[u]+=si[t[e]];
		if(si[t[e]]>si[son[u]])son[u]=t[e];
	}
	if(si[u]==1)b[++c__]=u;
}
void dfs2(int u,int fa){
	if(son[u]){
		seg[son[u]]=++seg[0];
		rev[seg[0]]=son[u];
		top[son[u]]=top[u];
		dfs2(son[u],u);
	}
	for(int e=h[u];e;e=ne[e]){
		if(top[t[e]])continue;
		seg[t[e]]=++seg[0];
		rev[seg[0]]=t[e];
		top[t[e]]=t[e];
		dfs2(t[e],u);
	}
}
void add(int k,int l,int r,int v){
	s[k]+=v*(r-l+1);
	ad[k]+=v;
	mi[k]+=v;
	if(l==r&&s[k]==0)w[k]=0;
	if(l==r&&s[k]!=0)w[k]=1;
}
void pd(int k,int l,int r,int mid){
	if(ad[k]){
		add(k<<1,l,mid,ad[k]);
		add(k<<1|1,mid+1,r,ad[k]);
		ad[k]=0;
	}
}
void c(int k,int l,int r,int x,int y,int v){
	if(l>=x&&r<=y){
		add(k,l,r,v);
		return;
	}
	if(l>y||r<x)return; 
	int mid=l+r>>1;
	pd(k,l,r,mid);
	c(k<<1,l,mid,x,y,v);c(k<<1|1,mid+1,r,x,y,v);
	s[k]=s[k<<1]+s[k<<1|1];
	mi[k]=Min(mi[k<<1],mi[k<<1|1]);
}
int find(int k,int l,int r,int x,int y){
	if(l>=x&&r<=y)return mi[k];
	if(l>y||r<x)return 1;
	int mid=l+r>>1;
	pd(k,l,r,mid);
	return find(k<<1,l,mid,x,y)&&find(k<<1|1,mid+1,r,x,y);
}
int find2(int k,int l,int r,int x,int y){
	if(l>=x&&r<=y)return s[k];
	if(l>y||r<x)return 0;
	int mid=l+r>>1;
	pd(k,l,r,mid);
	return find2(k<<1,l,mid,x,y)+find2(k<<1|1,mid+1,r,x,y);
}
void C(int x,int v){
	int fx=top[x];
	while(x){
		c(1,1,n,seg[fx],seg[x],v);
		x=fa[fx];fx=top[x];
	}
}
int F(int x){
	int fx=top[x];
	while(x){
		if(!find(1,1,n,seg[fx],seg[x]))return 0;
		x=fa[fx];fx=top[x];
	}
	return 1;
}
int F2(int x){
	int fx=top[x];
	int ans=0;
	while(x!=x){
		ans+=find2(1,1,n,seg[fx],seg[x]);
		x=fa[fx];fx=top[x];
	}
	return find2(1,1,n,seg[x],seg[x]);
}
int main(){
	freopen("explore.in","r",stdin);
	freopen("explore.out","w",stdout);
	n=read();
	for(int i=1;i<=n;++i)a[i]=read();
	for(int i=1;i<n;++i){
		int x=read(),y=read();
		_(x,y);_(y,x);
	}
	seg[0]=seg[1]=rev[1]=top[1]=1;
	dfs(1,0);
	dfs2(1,0);
	for(int i=1;i<=c__;++i)C(b[i],1);
	for(int i=1;i<=c__;++i){
		if(F(a[i])){
			++ans;
			C(a[i],-1);
		}
	}cout<<ans;
}
//带2的函数是用来调试的
```

### 后言
该不会只有我用的树剖吧

---

## 作者：Y2y7m (赞：2)

考场上认为所有药水出现的房间不同挂了，再加上 USACO 炸了，最后喜提银组刚好三位数的好成绩。

首先可以想到最短的遍历次数就是这棵树中叶子的数量。

然后我们把那些出现时间晚于叶子数量的药水直接删掉。

接下来考虑贪心，贪心的过程就相当于把每个叶子的所有祖先节点上会出现的药水往叶子上填，每个叶子只能填一个药水，而且填的这个药水出现的节点位置要尽可能深。这个过程我们可以用栈来模拟，栈中存储药水出现的位置，当我们要离开某一节点时，就把这个节点上还未被填入叶子的药水从栈中弹出即可。

代码很好写。

```cpp
#include <bits/stdc++.h>

using namespace std;
const int maxn=6e5+10;
int n;
int a[maxn],c[maxn];
vector<int> edge[maxn];
int cntleaf;
bool isleaf[maxn];
void dfs(int u,int fa)
{
	bool flag=0;
	for(int i=0;i<edge[u].size();i++)
	{
		int v=edge[u][i];
		if(v==fa) continue;
		dfs(v,u);
		flag=1;
	}
	if(!flag) cntleaf++,isleaf[u]=1;
}
stack<int> s;
int ans;
void sol(int u,int fa)
{
	for(int i=1;i<=c[u];i++) s.push(u);
	if(isleaf[u])
	{
		if(!s.empty())
		{
			s.pop();
			ans++;
			while(!s.empty()&&s.top()==u) s.pop();
			return ;
		}
	}
	for(int i=0;i<edge[u].size();i++)
	{
		int v=edge[u][i];
		if(v==fa) continue;
		sol(v,u);
	}
	while(!s.empty()&&s.top()==u) s.pop();
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	int u,v;
	for(int i=1;i<n;i++)
	{
		cin>>u>>v;
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	dfs(1,0);
	for(int i=1;i<=cntleaf;i++) c[a[i]]++;
	sol(1,0);
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：LiaoYF (赞：2)

银组只会这个。

## 做法

首先要从 $1$ 出发每次走一条到其他节点的简单路径，用最小的次数把树上每个节点都走一遍。

每一条路径结尾肯定是叶子结点（如果还能走，那接着走肯定不劣），并且每一条路径都不会经过 $1$ 个以上的叶子结点，所以至少要走叶子结点个数次。显然如果一个节点的后代中有一个被走过的叶子结点，那么它就一定被走过了。如果我们已经走了所有的叶子结点，那么整棵树一定被走完了。所以走的次数就是叶子结点的个数。

然后来解决怎么样获得最多的药水。

在某一个节点刷药水的那一轮，去它的子树中一个没有被走过的叶子结点。如果有没有被走过的叶子结点，就能拿到药水，否则一定有不能拿药水的叶子结点走，不会影响其他轮的答案。

记录前叶子结点个数轮每个结点的药水数量，第 $i$ 个节点的数量设为 $cnt_i$。设 $f_i$ 表示以 $i$ 为根的子树中有多少个没有走过的叶子结点进行 dp。如果 $f_i \geq cnt_i$，那么所有的药水都能拿到，否则就只能拿到 $f_i$ 瓶药水。具体细节见代码。


## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,head[100005],nxt[200005],to[200005],cnt,a[100005],deg[100005],cntleaf;
int cntp[100005],ans,f[100005];
void add(int u,int v){
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
void dfs(int u,int fa){
    if(deg[u]==1&&u!=1){
        f[u]=1;
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa)continue;
        dfs(v,u);
        f[u]+=f[v];
    }
    if(cntp[u]){
        if(f[u]<=cntp[u]){
            ans+=f[u];
            f[u]=0;
        }else{
            f[u]-=cntp[u];
            ans+=cntp[u];
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
        deg[u]++;
        deg[v]++;
    }
    for(int i=1;i<=n;i++){
        if(deg[i]==1&&i!=1){// 特判1不是叶子
            cntleaf++;
        }
    }
    for(int i=1;i<=cntleaf;i++){
        cntp[a[i]]++;
    }
    dfs(1,-1);
    cout<<ans;
    return 0;
}
```

---

## 作者：koobee (赞：1)

一道树形动态规划题目。

分析：通过分析一些例子，我们发现，有的子树会剩下一些拿药水的机会，机会不够。是否能均衡一下呢？我们想到了树上贪心。由于顺序不影响药水的结果，因此令 $s_i$ 为 $i$ 的药水数量。以 $i$ 为根的子树有 $s_i$ 次机会。

设 $f_i$ 为以 $i$ 为根节点剩下的未遍历到的叶节点个数（剩下拿药水的机会），先令 $f_i = \sum_{v \in son_i} f_v$。

然后，如果这个点上的药水小于等于剩下的机会，就能拿走这个节点的全部药水；否则就要牺牲一些。具体来讲，这个单独的节点拿到的药水 $k$ = $\min(f_i,s_i)$，最后 $f_i $ 减去 $k$，更新答案。更多详见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int n, cnt, sz, head[N], s[N], f[N], p[N], ans;
//s[i]:i的药水数量 f[i]:以i为根的子树中有多少个没有走过的叶子结点
struct edge{
	int to, nxt;
} e[N];
void add(int x, int y){
	e[++cnt] = {y, head[x]}, head[x] = cnt;
}
void exdfs(int x, int fa){
	bool f = 0;
	for(int i = head[x]; i; i = e[i].nxt){
		int y = e[i].to;
		if(y == fa) continue;
		f = 1, exdfs(y, x);
	}
	if(f == 0) sz++;
}
void dfs(int x, int fa){
	bool fl = 0;
	for(int i = head[x]; i; i = e[i].nxt){
		int y = e[i].to;
		if(y == fa) continue;
		fl = 1, dfs(y, x), f[x] += f[y];
	}
	if(fl == 0) f[x] = 1;
	if(f[x] >= s[x]) f[x] -= s[x], ans += s[x];
	else ans += f[x], f[x] = 0;
}
int main(){
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin>>n;
	for(int i = 1; i <= n; i++) cin>>p[i];
	for(int i = 1; i < n; i++){
		int a, b;
		cin>>a>>b;
		add(a, b), add(b, a);
	}
	exdfs(1, 0);
	for(int i = 1; i <= sz; i++) s[p[i]]++;
	dfs(1, 0);
	cout<<ans;
	return 0;
}

```

---

## 作者：zrl123456 (赞：1)

[题目](https://www.luogu.com.cn/problem/P10135)  
目标：在以最小的遍历次数通关地图的前提下，从地图内刷到的药水最多，输出药水数量。  
下面我们开始分析。  
### 最小的遍历次数：
在最优策略下，我们到达任意一点后，如果他有子节点，那么我们会继续向下遍历。  
故最小的遍历次数为子树内叶结点的数量，我们可以用一遍 dfs 来统计以 $u$ 点为根节点的子树内叶结点的数量，我们用 $g_u$ 表示。  
设 $v$ 点为 $u$ 点的子结点，易得转移方程：  
$$g_u=\sum g_v$$
### 最大药水数量：  
在以 $u$ 点位根节点的子树内能拾取到的药水数量我们用 $f_u$ 表示，其必然由其子结点转移而来，设其子结点为 $v$ 点。  
在遍历之后出现的药水自然无法捡到，那设 $u$ 点能捡到的药水的数量为 $a_u$，那么在任意一颗子树内，它最多遍历 $g_u$ 次，最多能拾取到的药水数量为 $(\sum f_v)+a_u$，易得转移方程：  
$$f_u=\max(g_u,(\sum f_v)+a_u)$$
$f_1$ 便为答案。  
代码：
```cpp
#include<bits/stdc++.h>
#define INF 2147483647
#define int long long
#define endl '\n'
#define inl inline
#define reg register
using namespace std;
const int N=1e5+5;
vector<int>g[N];
int n,p[N],u,v,ye[N],yao[N];
bool flag[N],vis[N];
/*
n,p如题所述，g,u,v为了建树，ye,yao等同于上述g,f,a(yao代替了f,a)
*/
inl int read(){//快读
	reg int f=1,x=0;
	reg char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
inl void write(int x){//快写
	if(x<0) x=-x;
	if(x>=10) write(x/10);
	putchar(x%10^48);
}
inl void dfs1(int now){//求叶结点数
	flag[now]=true;
	for(reg int i=0;i<g[now].size();++i)
		if(!flag[g[now][i]]){
			dfs1(g[now][i]);
			ye[now]+=ye[g[now][i]];
		}
	flag[now]=false;
	return;
}
inl void dfs2(int now){//求拾取药水数
	flag[now]=true;
	for(reg int i=0;i<g[now].size();++i)
		if(!flag[g[now][i]]){
			dfs2(g[now][i]);
			yao[now]+=yao[g[now][i]];
		}
	yao[now]=min(yao[now],ye[now]);
	flag[now]=false;
	return;
}
signed main(){
	n=read();
	for(reg int i=1;i<=n;++i) p[i]=read();
	for(reg int i=1;i<n;++i){
		u=read();
		v=read();
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for(reg int i=2;i<=n;++i)
		if(g[i].size()==1) ye[i]+=1;
	dfs1(1);
	for(reg int i=1;i<=ye[1];++i) ++yao[p[i]];
	dfs2(1);
	write(yao[1]);
	return 0;//结束
} 
```


---

## 作者：masonpop (赞：1)

~~我来帮助大家化简为繁。~~

场外选手无脑做法，喜提最劣解，思路仅供参考。

首先最优的遍历方式肯定是每个叶子节点各去一次。对每个叶子节点，贪心的往上走，取走第一个遇到的物品。考虑这样做的正确性，首先能取肯定会取，然后为了减少对其它点的影响，肯定取走最深的那个。

往上跳的过程显然倍增维护，现在问题就变成了：查询 $x\to y$ 的链上的和（$x$ 是 $y$ 的祖先），单点修改。维护 $c_x$ 表示 $x$ 到根路径上的和，这样 $1$ 操作直接差分，$2$ 操作转换成了子树加，用 dfs 序映射到数列上之后就变成了区间加，线段树维护即可。

复杂度 $O(n\log^2 n)$。[代码](https://www.luogu.com.cn/paste/tof10c54)。

---

## 作者：Cuiyi_SAI (赞：1)

## $\large{\text{Question}}$

给出一棵 $n$ 个节点的树，定义一次遍历为从根节点 $1$ 出发走最短路径到任意节点，每次遍历以前树上会在某个节点生成一个药水，若在此次遍历中经过这个节点就可以拿到药水，否则药水消失。要求最小化遍历次数使得每个节点至少被经过 $1$ 次，并在保证这个的同时使得拿到的药水最多，输出最大的药水数量。

## $\large{\text{Solution}}$

由于要走最短路径还每次要从根出发，所以显然每次走到叶子节点最优，**最小遍历次数即为叶子的个数**。  
因此，对于**编号大于叶子结点个数的那些药水我们是取不到的**，是无效的。下面讨论的药水都是有效药水。

由于每次遍历时树上有且仅有一个药水，而每次遍历都对应一个叶子结点，所以药水和叶子节点是**一一对应**的关系。  
于是我们不难想到建立一个这样的**二分图**模型：左部点表示叶子结点，右部点表示药水编号，**若从根到叶子结点 $x$ 的简单路径上的某一点会在某一时刻出现药水 $y$**，那么连接 $(x,y)$。然后在这张二分图上跑最大匹配，就得到了正确答案。但是这个做法无论是在时间还是空间上都爆炸（也可能是我太弱了实现问题），所以只能拿到 50 分。

暴力匹配过不去，还是得回到这种题的老路子，树形 DP。由于叶节点与药水的一一对应，我们只需要考虑子**树内的叶子结点是否够分这么多药水即可**。设 $sze_x$ 表示以 $x$ 为根的子树内叶子结点的个数，$f_x$ 表示以 $x$ 为根的子树最多能那多少药水。若 $x$ 节点无论何时都没有有效药水，则
$$
f_x=\sum_{v~\in~{son}} f_v
$$
若总共有 $p$ 个有效药水会在不同时间生成在点 $x$ 上，则

$$
S=\sum_{v~\in~{son}} f_v
$$
$$
f_x=S+\min\left(sze_x-S~,~p\right)
$$

$S$ 的实际意义是**已经和药水匹配好了**的叶子结点数量，因此 $x$ 节点的贡献就是「**还未匹配**的叶节点数量 和 $x$ 节点上药水数」的较小值。

最后 $f_1$ 即为答案。

其实这其中就蕴涵着官方题解中的那种贪心思想：对于每个叶子找到是其祖先且与它最近的药水配对，这样得到的答案是最优的。证明的话就是：无论最优解如何变化匹配方式，我们都可以将其转化为上述的贪心思路，同时保证最优解不变。

## $\large{\text{Code}}$


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100010],f[100010],sze[100010];
vector<int> g[100010],p[100010];
int num;
void dfs(int u,int fa){
    int son=0;
    for(auto v:g[u]){
        if(v==fa) continue;
        dfs(v,u);
        sze[u]+=sze[v];
        f[u]+=f[v];
        son++;
    }
    if(son==0) sze[u]=1;
    if(sze[u]>f[u]&&p[u].size()>0) f[u]+=min(int(p[u].size()),sze[u]-f[u]);
    return ;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<n;i++){
        int aa,bb;
        cin>>aa>>bb;
        g[aa].push_back(bb);
        g[bb].push_back(aa);
    }
    for(int i=2;i<=n;i++) if(g[i].size()==1) num++;
    for(int i=1;i<=num;i++) p[a[i]].push_back(i);
    dfs(1,0);
    cout<<f[1];
    return 0;
}
```

---

## 作者：_qhbd_ (赞：0)

# 题意
给定一棵有 $n$ 个节点的树，现在需要将每个节点至少遍历一次。每次选择一条从节点 $1$ 到另一个节点的简单路径遍历，对于每次遍历前将告知某一特殊节点，若此次遍历经过此点则有 $1$ 贡献。现在问最少遍历次数下最大贡献。
# 思路
不难明白最小遍历次数等于叶子节点数量，若你某次从节点 $1$ 开始的遍历的终点不是叶子节点，那么它肯定可以遍历它的子节点，如果其子节点都被遍历过则说明这次遍历的路径之前已经遍历过了，是多余的遍历。

所以每次遍历完一个叶子节点，最终最小遍历次数就等于叶子节点数量。知道了最小遍历次数，从而可以初步知道有哪些贡献是有可能得到的。

然后我们遍历一遍树。遍历时，我们先遍历其子树，然后统计有多少未遍历的叶子节点，然后判断是否有遍历当前节点时可能得到的贡献，同时判断是否有叶子节点可以遍历，因为如果要得到贡献，就需要遍历到当前节点，而如果没有未遍历的叶节点，则说明当前节点已不可被遍历即不能再对答案有贡献。

然后在往父亲节点上传可遍历叶子节点的数量时要去除为了得到贡献而需要的遍历的叶节点数量。

最后用总叶节点数量减去 $1$ 节点可遍历的叶节点数量就是答案了。因为总叶节点数量减去 $1$ 节点可遍历的叶节点数量得到的值就是在统计可遍历叶节点数量的过程中为了得到贡献而没有计算的叶节点数量，所以少算了多少，即得到了多少贡献。
# 实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,num,in[N];
vector<int> w[N],r[N];
inline int dfs(int u,int fa){
    int siz=0;
    for(auto v:r[u])
        if(v!=fa)
            siz+=dfs(v,u);
    if(u!=1&&r[u].size()==1)
        siz=1;
    if(siz){
        for(auto v:w[u])
            if(v<=num){
                siz--;
            if(!siz)
                break;
        }
    }
    return siz;
}
int main(){
    scanf("%d",&n);
    for(int i=1,p;i<=n;i++){
        scanf("%d",&p);
        w[p].emplace_back(i);
    }
    for(int i=2,u,v;i<=n;i++){
        scanf("%d%d",&u,&v);
        r[u].emplace_back(v);
        r[v].emplace_back(u);
        in[u]++;
        in[v]++;
    }
    for(int i=2;i<=n;i++)
        num+=(in[i]==1);
    printf("%d",num-dfs(1,1));
    return 0;
}
```

---

## 作者：_qingshu_ (赞：0)

# 题意：

给定一颗有 $N$ 个节点的树，编号为 $1,2\cdots N$。当所有的节点至少都被遍历一次的情况下我们将会通关，每一次遍历都是一条从节点 $1$ 开始的简单路径，设至少需要 $k$ 次遍历才可以通关游戏。

我们知道接下来的第 $i(i\in[1,N])$ 次遍历的药水出现的节点 $p_i$，如果我们在第 $i$ 次遍历的路径上经过了点 $p_i$，我们的得分加一。

询问在保证只能使用 $k$ 次遍历的情况下的最大得分。

# 思路：

首先考虑至少需要多少次遍历？显而易见的，遍历次数等于叶子节点数，那么实际可能获取到的药水数为前 $k$ 个。

对于每一次遍历，我们等同于消除掉一个叶子节点。那么我们考虑从叶子节点开始往上跑（在当前节点为根的子树遍历完之后再操作），记录子树内剩余叶子节点的个数，如果在当前节点在 $k$ 次遍历以内存在药水，那么考虑消除到当前子树的一个叶子节点，我们不需要知道具体的是哪一个（因为都是一样的）。

# Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
int p[5200010];
vector<int>e[5200010],now[5200010];
int in[5200010];
int ans,cnt;
int dfs(int u,int fa){
    int num=0;
    bool flag=true;
    for(int v : e[u]){
        if(v!=fa){
            num+=dfs(v, u);
            flag=false;
        }
    }
    if(flag)num++;
    if(num){
        for(int x : now[u]){
            if(x>cnt){
            	break;
            } 
            ans++;num--;
            if(!num)break;
        }   
    }
    return num;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>p[i];
    }
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
        in[u]++;in[v]++;
    }
    for(int i=1;i<=n;i++){
    	now[p[i]].push_back(i);
    }
    for(int i=2;i<=n;i++){
    	if(in[i]==1)cnt++;
    }
    dfs(1,0);
    cout<<ans;
}
```

---

## 作者：ethan0328 (赞：0)

简单题。

## 思路

注意到先保证遍历次数最小，所以显然每次遍历都是从根走向一个未被遍历过的叶子。所以每个点被遍历过的次数是它子树内叶节点个数。

考虑树形 DP，令 $dp_i$ 表示第 $i$ 个节点的子树至多能拿到多少药水。$dp_i$ 就是所有子树的 $dp$ 值的和加这个节点上出现过多少药水，因为每次遍历只有一瓶药水出现，所以取这些药水不会冲突。

当 $dp_i$ 大于以 $i$ 的遍历次数时，将 $dp$ 值变为遍历上线。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,a[N],cnt[N],lef[N],dp[N];
vector<int> e[N];
void dfs1(int x,int fa)
{
	int flg=1;
	for(auto y:e[x])
	{
		if(y!=fa)
		{
			flg=0;
			dfs1(y,x);
			lef[x]+=lef[y];
		}
	}
	lef[x]+=flg;
}
void dfs2(int x,int fa)
{
	for(auto y:e[x])
	{
		if(y!=fa)
		{
			dfs2(y,x);
			dp[x]+=dp[y];
		}
	}
	if(dp[x]+cnt[x]<=lef[x])
	{
		dp[x]+=cnt[x];
	}else
	{
		dp[x]=lef[x];
	}
}
signed main()
{
	int x,y;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<n;i++)
	{
		cin>>x>>y;
		e[x].push_back(y);
		e[y].push_back(x);
	}
	dfs1(1,0);
	for(int i=1;i<=lef[1];i++)
	{
		cnt[a[i]]++;
	}
	dfs2(1,0);
	cout<<dp[1];
}
```


---

## 作者：fcy20180201 (赞：0)

首先要让探险的次数少，相当于不重不漏地**遍历到所有叶子结点**，所以先数出叶子结点的个数，设有 $x$ 个。**则 $p$ 中只有 $p_1,p_2,\cdots,p_x$ 有用**。现在的问题是把每次探险经过的路径排序，对应到 $p_1,p_2,\cdots,p_x$，使满足第 $i$ 条路径上有 $p_i$ 的 $i$ 尽可能多。

我们可以把问题转化为每个点最多能对应上的 $p_i$ 个数，而不是考虑路径。首先给每个**叶子**对应的机会，对于某个叶子结点 $j$，如果 $p$ 中没有 $j$，就把这个机会让给父亲；否则这个叶子结点就对应上了一次，对答案产生 $1$ 的贡献，但由于它对应时带上了一整条路径，因此这个机会就不能给父亲了。每个节点得到机会以后，都**尽可能多地匹配** $p$，然后把剩余的机会给父亲，以此类推。时间复杂度 $\mathcal O(N)$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,p[100005],a[100005],rest[100005],sum[100005];
vector<int>con[100005];

void prep(int u,int fa){
	if(con[u].size()==1 && con[u][0]==fa){sum[u]=1;return ;}
	for(int v:con[u])if(v!=fa)prep(v,u),sum[u]+=sum[v];
	return ;
}

void dfs(int u,int fa){
	if(con[u].size()==1 && con[u][0]==fa){//给叶子结点机会
		if(!a[u])rest[u]=1;
		//如果 p 中没有出现，就还剩一个机会
		else ans++;//否则对应上，答案加 1
		return ;
	}
	for(int v:con[u])if(v!=fa)dfs(v,u),rest[u]+=rest[v];
	//搜刮儿子节点的剩余机会
	ans+=min(a[u],rest[u]),rest[u]=max(0,rest[u]-a[u]);
	//尽量多地匹配，算出剩余机会
	return ;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&p[i]);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		con[u].push_back(v);
		con[v].push_back(u);
	}
	prep(1,0);//算叶子结点的个数
	for(int i=1;i<=sum[1];i++)a[p[i]]++;//计算有效的 p 中每个点出现了几次
	dfs(1,0);//算答案
	printf("%d",ans);
	return 0;
}
```

---

## 作者：tanghg (赞：0)

首先最少步数取法就是每一次都取到一个没有取过的叶子，因为一定要有一次遍历到叶子，那不如直接按照最长遍历。

之后只要保证遍历的顺序最优即可。假设有 $l$ 个叶子，那么我们显然只关心 $[1,l]$ 时间内出现的药水。那么就先开一个桶子表示 $u$ 上在这个时间内有几个药水出现。之后我们发现，因为药水等价，所以取哪个都一样。那么我们不妨从深度深的往上取。然后一个结点能取多少药水是由它的子树有几个叶子节点的路径没有取过决定的。那我们枚举然后向上更新即可。
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
typedef long long ll;
const ll MAXN=1e5+5;
ll n;
vector<ll>adj[MAXN];
ll vis[MAXN];
ll ans,leaf;
ll sz[MAXN],dep[MAXN],fa[MAXN];
void dfs(ll u,ll f){
    bool l=false;
    for(auto v:adj[u]){
        if(v==f){
            continue;
        }
        dfs(v,u);
        l=true;
    }
    if(!l){
        leaf++;
    }
}
ll p[MAXN];
void val(ll u,ll f){
    sz[u]=0;
    bool l=false;
    for(auto v:adj[u]){
        if(v==f){
            continue;
        }
        l= true;
        val(v,u);
        sz[u]+=sz[v];
    }
    if(!l){
        sz[u]++;
    }
    //cout<<u<<" "<<vis[u]<<" "<<sz[u]<<endl;
    ans+= min(vis[u],sz[u]);
    sz[u]-= min(vis[u],sz[u]);
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>p[i];
    }
    for(int i=1;i<n;++i){
        ll u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    for(int i=1;i<=leaf;++i){
        vis[p[i]]++;
    }
    val(1,0);
    cout<<ans<<endl;
    return 0;
}

```

---

## 作者：yyrwlj (赞：0)

## 思路

每次遍历能走到一个叶子结点，所以显然最小的遍历次数就是叶节点个数。

那么就只用考虑前叶子结点个数瓶药水，从节点 $1$ 开始向所有叶节点 dfs 遍历，回朔时如果当前节点有药水而且当前路径没有药水，就把药水给这条路径。

特判：如果叶节点有药水就不用等回朔了。

## Code

```cpp
#include <iostream>
using namespace std;
const int N = 100005;
struct Edge{
    int to, nxt;
}g[N << 1];
int h[N], idx;
int d[N], p[N], have[N], ans;
void add(int a,int b)
{
    g[++idx].to = b, g[idx].nxt = h[a], h[a] = idx;
}
int dfs(int u,int fa)
{
    bool leaf = true;
    int sum = 0; //没有药水的路径有几条
    for (int i = h[u]; i; i = g[i].nxt)
    {
        int j = g[i].to;
        if (j == fa)
            continue;
        leaf = false;
        sum += dfs(j, u);
    }
    if (!leaf)
    {
        if (have[u] > sum)
            have[u] = sum;
        ans += have[u];
        return sum - have[u];
    }
    if (have[u])
    {
        ans ++;
        return 0;
    }
    return 1;
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i=1;i<=n;i++)
        scanf("%d", &p[i]);
    for (int i=1;i<n;i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
        add(b, a);
        d[a] ++;
        d[b] ++;
    }
    int leaf = 0;
    for (int i=2;i<=n;i++)//从2开始，防止根节点度数为1
        if (d[i] == 1)
            leaf ++;
    for (int i=1;i<=leaf;i++)
        have[p[i]] ++;
    dfs(1, 1);
    printf("%d", ans);
    return 0;
}
```

---

## 作者：hytallenxu (赞：0)

## 题目大意
给定一颗树，有 $n-1$ 条无向边和 $n$ 个节点。每走到任意一个节点记作一次 ```Traversal```，然后返回根节点。

同时，在第 $i$ 次 ```Traveral``` 前，一个奖励会出现在第 $a_i$ 节点。

问在最快遍历整图的情况下最多情况能拿多少奖励。

## 思路
树形动态规划。

先统计出叶子节点有多少个（即贪心的快速遍历整图），然后就能判断出来最多能拿几个奖励，用 $check$ 数组来存。

然后全图扫一遍，每次取 $dp_u$ 和 $check_u$ 的最小值。

最后再减掉就做完了。

## Code
```cpp
#include <iostream>
using namespace std;

const int maxn=4e5+10;
int n,head[maxn],cnt=0,arr[maxn],check[maxn],dp[maxn],ans=0,leaf=0,ed[maxn];
struct{
    int from,to,next;
}edge[maxn];

inline void init(){
    for(int i=0;i<maxn;++i)head[i]=-1,edge[i].next=-1; //fun init
}

inline void add(int u, int v){
    edge[cnt].from=u;
    edge[cnt].to=v;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}

void ddfs(int u, int fa){
    bool flag=0;
    dp[u]=0;
    for(int i=head[u];~i;i=edge[i].next){
        if(edge[i].to==fa) continue;
        flag=1;
        ddfs(edge[i].to,u);
        dp[u]+=dp[edge[i].to]; //simple dfs!!
    }
    if(!flag) dp[u]=1;
}

void dfs(int u, int fa){
    bool flag=0;
    dp[u]=0;
    for(int i=head[u];~i;i=edge[i].next){
        if(edge[i].to==fa) continue;
        flag=1;
        dfs(edge[i].to,u);
        dp[u]+=dp[edge[i].to]; //simple dfs!!
    }
    if(!flag) dp[u]=1;
    if(dp[u]){
        int tmp=min(dp[u],check[u]); //dp on tree lol
        dp[u]-=tmp;
        ans+=tmp;
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(NULL),cout.tie(NULL);
    init();
    cin>>n;
    for(int i=1;i<=n;i++)cin>>arr[i];
    for(int i=1;i<n;i++){
        register int u,v; // hope register with me
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    ddfs(1,-1);
    for(int i=1;i<=dp[1];i++) check[arr[i]]++; 
    dfs(1,-1);
    cout<<ans;
    return 0;
}
```

---

## 作者：_anll_ (赞：0)

## 题目大意
给你一棵有 $n$ 个节点的树，以及 $n$ 次遍历前出现药水的点，问你在遍历次数最少的情况下，可以获得最多几瓶药水。

## 大体思路
不难发现，最少遍历次数等于叶子节点点数 $k$。这个用 dfs 扫一遍即可求出，在题解区也已经有很多大佬分析，本蒟蒻在此就不再赘述。

于是思考如何计算获得药水的最大值。显然，我们只考虑前 $k$ 次药水出现的次数。我们先扫一次叶子节点，处理已经在前 $k$ 次出现过的情况。之后再去处理剩下的叶子节点到根的简单路径是否出现过未拾取的药水。最初我的做法是从叶子节点往上暴力查找，会 T 一个点，所以换成了从根到叶子 dfs 去跑。

具体来讲，对于当前节点 $x$，遍历每一个它的子节点 $l$，子节点向上传递它未被使用的叶子节点个数，如果 $x$ 节点还有未被匹配拾取的药水，就将未被使用的叶子节点与其配对，直到药水耗尽或叶子节点均被匹配上为止。

## 代码演示
大体思路就是这样，如果还有不清晰的地方可以结合代码理解。
```cpp
#include<iostream>
#include<set>
#define int long long
using namespace std;
struct Edge{
    int l,nxt;
}edges[200005];
int n,q,c,ans,num[100005],tt=1,head[100005];
int vu[100005],vo[100005];
int fas[100005],dep[100005],siz[100005];
set<int> so;
void add_edge(int f,int l){
    tt+=1;
    edges[tt]={l,head[f]};
    head[f]=tt;
}
void dfs(int x,int fa){
    bool state=0;fas[x]=fa;
    for(int i=head[x];i;i=edges[i].nxt){
        int l=edges[i].l;
        if(l==fa) continue;
        dfs(l,x);
        state=1;
    }
    if(!state)so.insert(x);
}
int dfs2(int x,int fa){
    int son=0;
    for(int i=head[x];i;i=edges[i].nxt){
        int l=edges[i].l;
        if(l==fa) continue;
        int awa=dfs2(l,x);
        ans+=min(awa,vu[x]);
        if(vu[x]<awa) son+=awa-vu[x];
        vu[x]-=awa;
        if(vu[x]<0) vu[x]=0;
    }
    if(so.find(x)!=so.end()&&!vo[x]) son=1;
    return son;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int f,l;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>num[i];
    for(int i=1;i<n;i++){
        cin>>f>>l;
        add_edge(f,l);
        add_edge(l,f);
    }
    dfs(1,0);
    for(int i=1;i<=so.size();i++) vu[num[i]]+=1;
    for(int i=1;i<=so.size();i++){
        if(so.find(num[i])!=so.end()&&!vo[num[i]]) ans+=1,vu[num[i]]-=1,vo[num[i]]=1;
    }
    dfs2(1,0);
    cout<<ans;
    return 0;
}
```


---

