# Regular Forestation

## 题目描述

A forestation is an act of planting a bunch of trees to grow a forest, usually to replace a forest that had been cut down. Strangely enough, graph theorists have another idea on how to make a forest, i.e. by cutting down a tree!

A tree is a graph of $ N $ nodes connected by $ N - 1 $ edges. Let $ u $ be a node in a tree $ U $ which degree is at least $ 2 $ (i.e. directly connected to at least $ 2 $ other nodes in $ U $ ). If we remove $ u $ from $ U $ , then we will get two or more disconnected (smaller) trees, or also known as forest by graph theorists. In this problem, we are going to investigate a special forestation of a tree done by graph theorists.

Let $ V(S) $ be the set of nodes in a tree $ S $ and $ V(T) $ be the set of nodes in a tree $ T $ . Tree $ S $ and tree $ T $ are identical if there exists a bijection $ f : V(S) \rightarrow V(T) $ such that for all pairs of nodes $ (s_i, s_j) $ in $ V(S) $ , $ s_i $ and $ s_j $ is connected by an edge in $ S $ if and only if node $ f(s_i) $ and $ f(s_j) $ is connected by an edge in $ T $ . Note that $ f(s) = t $ implies node $ s $ in $ S $ corresponds to node $ t $ in $ T $ .

We call a node $ u $ in a tree $ U $ as a good cutting point if and only if the removal of $ u $ from $ U $ causes two or more disconnected trees, and all those disconnected trees are pairwise identical.

Given a tree $ U $ , your task is to determine whether there exists a good cutting point in $ U $ . If there is such a node, then you should output the maximum number of disconnected trees that can be obtained by removing exactly one good cutting point.

For example, consider the following tree of $ 13 $ nodes.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1252F/3ac5ebb3c1888c727ec26f8cc5bfb5407a38403b.png)

There is exactly one good cutting point in this tree, i.e. node $ 4 $ . Observe that by removing node $ 4 $ , we will get three identical trees (in this case, line graphs), i.e. $ \{5, 1, 7, 13\} $ , $ \{8, 2, 11, 6\} $ , and $ \{3, 12, 9, 10\} $ , which are denoted by $ A $ , $ B $ , and $ C $ respectively in the figure.

- The bijection function between $ A $ and $ B $ : $ f(5) = 8 $ , $ f(1) = 2 $ , $ f(7) = 11 $ , and $ f(13) = 6 $ .
- The bijection function between $ A $ and $ C $ : $ f(5) = 3 $ , $ f(1) = 12 $ , $ f(7) = 9 $ , and $ f(13) = 10 $ .
- The bijection function between $ B $ and $ C $ : $ f(8) = 3 $ , $ f(2) = 12 $ , $ f(11) = 9 $ , and $ f(6) = 10 $ .

 Of course, there exists other bijection functions for those trees.

## 说明/提示

Explanation for the sample input/output #1

This is the example from the problem description.

## 样例 #1

### 输入

```
13
1 5
1 7
2 4
2 8
2 11
3 12
4 7
4 12
6 11
7 13
9 10
9 12
```

### 输出

```
3
```

## 样例 #2

### 输入

```
6
1 2
1 3
2 4
3 5
3 6
```

### 输出

```
-1
```

# 题解

## 作者：ran_qwq (赞：8)

其他题解都太具体了，所以我要提供个抽象的做法，时间 $966$ ms，空间 $189600$ KB，喜提最劣解。时空都可以优化但是都懒得优化，反正能过。

## Step $1$：$O(n^3\log n)$ 或 $O(n^3)$ 做法

看到树同构，想到树哈希。

但是这道题的出题人~~也许是想报复社会~~，卡自然溢出的哈希，所以我想到了一种抽象至极的哈希方法。

如果两棵树同构，则它们的度数对应，从小到大排序后得到的两个序列相同。

我们对于每棵子树都搞一个 multiset，存子树内节点的度数。直接判断两个节点的 multiset 是否相等即可，简单、粗暴。这么粗糙的哈希出题人居然没卡？！

然而，$n\le4000$，可以用归并优化到 $O(n^3)$，但是还是过不了一点。我们需要发掘一些性质。

## Step $2$：$O(n^2\log n)$ 或 $O(n^2)$ 做法

因为至少要有两棵子树同构，所以每棵子树大小不超过 $\lfloor\dfrac{n}{2}\rfloor$。

我们发现这就是树的重心的充要条件，一棵树的重心最多两个，所以只用枚举所有重心即可。

```cpp
int n,id,mn=INF,to[N<<1],ne[N<<1],head[N],siz[N],deg[N];vi a;unordered_multiset<int>b[N];
void add(int x,int y) {to[++id]=y,ne[id]=head[x],head[x]=id;} 
void dfs1(int u,int fa) {
	int mx=0;siz[u]=1;
	for(int i=head[u];i;i=ne[i]) {
		int v=to[i];if(v==fa) continue;
		dfs1(v,u),siz[u]+=siz[v],mx=max(mx,siz[v]);
	}
	mx=max(mx,n-siz[u]);
	if(mx<mn) a.clear(),a.pb(u),mn=mx; 
	else if(mx==mn) a.pb(u);
}	
void dfs2(int u,int fa,int rt) {
	b[u].insert(fa==rt?deg[u]-1:deg[u]);
	for(int i=head[u];i;i=ne[i]) {
		int v=to[i];if(v==fa) continue;
		dfs2(v,u,rt);
		for(int x:b[v]) b[u].insert(x);
	}
}
void QwQ() {
	n=rd();
	for(int i=1,x,y;i<n;i++) x=rd(),y=rd(),add(x,y),add(y,x),deg[x]++,deg[y]++;
	dfs1(1,0);
	for(int i:a) {
		for(int j=1;j<=n;j++) b[j].clear();
		dfs2(i,0,i);int fg=1,cnt=0;
		for(int j=head[i];j;j=ne[j]) {
			int v=to[j];cnt++;
			if(b[v]!=b[to[head[i]]]) fg=0;
		}
		if(fg) wr(cnt,""),exit(0);
	}
	puts("-1");
}
```

---

## 作者：cppcppcpp3 (赞：1)

[Link](https://codeforces.com/problemset/problem/1252/F)

直接考虑模拟题意：枚举断点 $u$，判断 $u$ 的所有子树是否同构。判断树的同构可以直接用树哈希。这里用的是 [OI-Wiki 上的哈希方式](https://oiwiki.org/graph/tree-hash/)：记 $hs_u$ 表示以 $u$ 为根的子树的哈希值，定义一个多重集的哈希函数

$$f(S)=(1+\sum_{v \in S} hs_v) \bmod m$$

以 $u$ 为根的子树的哈希值，等于所有 $u$ 的儿子 $v$ 的子树的哈希值构成的多重集 $S$ 对应的 $f(S)$。

$$hs_u=f(\{hs_v\mid v \in son_u\})$$

这样一次 DFS 就可以求出有根树的哈希值。而对于本题中断开而成的某棵无根树，则可以用换根 dp 求出以每个点为根时的哈希值 $hs1_i$，再利用上面的多重集函数即可得到最终整棵树的哈希值。

这样对于每个断点处理是 $O(n)$ 的，总的时间复杂度 $O(n^2)$，足以通过此题。

但是还有更优的做法：观察到同构的树至少两棵，同构的树大小相同，则断开后每棵子树大小 $\le \frac{n}{2}$，符合重心的定义。然后把重心找出来，仍用上述方式判断断开重心后的子树是否同构即可，时间复杂度 $O(n)$。

下面的代码实现是 $O(n^2)$ 的做法。

[Submission](https://codeforces.com/contest/1252/submission/247735020)

```cpp
// Problem: Regular Forestation
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1252F
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int N=4005;
const ull mask=chrono::steady_clock::now().time_since_epoch().count();

inline int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1; c=getchar();}
	while(isdigit(c)){x=x*10+c-48,c=getchar();}
	return x*f;
}

ull shift(ull x){
	x^=mask,x^=x<<13,x^=x>>7,x^=x<<17,x^=mask;
	return x;
}

int n,bl[N],as=-1;
ull hs[N],hs1[N],a[N];
vector<int> g[N];

void dfs(int u,int fa,int c){
	hs[u]=1,bl[u]=c;
	for(int v:g[u]){
		if(v==fa) continue;
		dfs(v,u,c),hs[u]+=shift(hs[v]);
	}
}

void dfs1(int u,int fa){
	for(int v:g[u]){
		if(v==fa) continue;
		hs1[v]=hs[v]+shift(hs1[u]-shift(hs[v]));
		dfs1(v,u);
	}
}

signed main(){
	n=wrd();
	for(int i=1;i<n;++i){
		int u=wrd(),v=wrd();
		g[u].push_back(v),g[v].push_back(u);
	}
	
	for(int u=1;u<=n;++u){
		int cnt=0;
		for(int v:g[u]){
			a[++cnt]=1;
			dfs(v,u,cnt),hs1[v]=hs[v];
			dfs1(v,u);
		}
		for(int i=1;i<=n;++i) if(i^u) a[bl[i]]+=shift(hs1[i]);
		for(int i=2;i<=cnt;++i) if(a[i]!=a[1]) cnt=-1; 
		if(cnt>1) as=max(as,cnt);
	}
	return printf("%d",as),0;
}
```

---

## 作者：max67 (赞：1)

## 前言

由于这是一场 ICPC，所以 luogu 评测机抓取结果好像出了一些小问题，这里推荐直接上 CF 交。

推荐先去了解[同构](https://oi-wiki.org/graph/concept/)和[树 hash](https://oi-wiki.org/graph/tree-hash/)

**update** 

20220220 ，感谢 @[lyzqs](https://www.luogu.com.cn/user/19172) 指出的一处错误：代码中第 $57$ 行中的 ``` f[x]=1``` 码成了 ```f[x]=0```，会导致哈希值全为 $0$。

## 题解

虽然 $n\le 4000$，但是暴力 $O(n^2)$ 还是不能过的（有可能我常数大）~~，严重怀疑出题人时故意引诱我们。~~

观察题目，发现 "剩下来的几棵树同构"，显然的，他们的大小也是相同的。由于同构的树至少需要两颗，则它们的大小最多为 $\frac{n}{2}$——与树的重心定义相同。

再观察一下，我们会得到更为清晰的条件——这样的节点有且仅有一颗。我们用反证法证明：

> 假设有两个不同的节点满足条件，先考虑其中一个节点，设他的每一颗子树的大小为 $siz$。此时另外一个节点只能在子树内，因为他的子树同构，所以他必然有两颗以上的子树。当断开第二个节点时，一定有一颗子树与第一个节点联通，此时他的大小大于 $siz$。他一定有另外一颗子树满足他不与第一个节点联通，此时他最大的大小为这个子树的大小（还不到），此时大小小于等于 $siz$。因为两颗子树大小不相同，所以与同构的条件不符，不成立。

然后，上普通的树同构 hash 模板即可（这里用的是 [OI wiki]((https://oi-wiki.org/graph/tree-hash/)) 上的第三种方法）。

（pass:式子上的 $prime(size_{son(now,i)}$ 中的函数在一般情况下可以换成其他有关于 $son(now,i)$ 的函数，这样子更不容易被卡。）

```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
const int N=1e6+1e3;
int n;
int root;
vector<int>g[N];
int pri[N],v[N],tot;
void Prepare(int n)//求素数
{
    for(int i=2;i<=n;i++)
    {
        if(!v[i])pri[++tot]=i;
        for(int j=1;j<=tot&&i*pri[j]<=n;j++)
        {
            v[i*pri[j]]=1;
            if(i%pri[j]==0)break;
        }
    }
}
int sz;
int dfs_dp(int x,int fa)//求满足条件的点
{
    int sum=-1,siz=1;
    bool pd=1;
    for(auto y:g[x])
    {
        if(y==fa)continue;
        int tmp=dfs_dp(y,x);
        if(sum==-1)sum=tmp;
        else if(sum!=tmp)pd=0;
        siz+=tmp;
    }
    if(pd&&sum!=-1&&(n-siz==sum||(n-siz==0&&g[x].size()>1)))root=x,sz=sum;
    //至少有两颗以上子树大小相等
    return siz;
}
vector<int>rt;
int dfs_root(int x,int fa)//求重心
{
    int siz=1,mx=0;
    for(auto y:g[x])
    {
        if(y==fa)continue;
        int tmp=dfs_root(y,x);
        siz+=tmp;mx=max(mx,tmp);
    }
    mx=max(mx,sz-siz);
    if(mx<=sz/2)rt.push_back(x);//每颗子树大小相等
    return siz;
}
int f[N];
int dfs_hash(int x,int fa)
{
    int siz=1;
    f[x]=0;
    for(auto y:g[x])
    {
        if(y==fa||y==root)continue;
        int tmp=dfs_hash(y,x);
        f[x]+=f[y]*pri[tmp];
        siz+=tmp;
    }
    return siz;
}
signed main()
{
    Prepare(1e6+1e3);
    scanf("%lld",&n);
    for(int i=1,x,y;i<n;i++)
    {
        scanf("%lld%lld",&x,&y);
        g[x].pb(y);g[y].pb(x);
    }
    dfs_dp(1,0);
    if(root==0)return puts("-1"),0;
    bool pd=0;
    int tmp=0;
    for(auto y:g[root])
    {
        rt.clear();
        dfs_root(y,root);
        //对于第一颗子树，任取一个重心
        //对于其他子树，枚举所有重心
        //如果是同构的，两颗子树必然会找到一个相等重心
        if(!pd)dfs_hash(rt[0],0),tmp=f[rt[0]],pd=1;
        else 
        {
            bool pd1=0;
            for(auto z:rt)if(dfs_hash(z,0)&&(f[z]==tmp)){pd1=1;break;}
            if(!pd1)return puts("-1");
        }
    }
    printf("%lld\n",g[root].size());
    return 0;
}
```

## 后话

CF 评分 2400，感觉评个蓝差不多。

---

## 作者：mango2011 (赞：0)

非常简单的题目。

随便构造一个哈希函数 $f(u)=(B+\displaystyle\sum_{v\in son_u} f(v))\bmod M$（$B$ 为全局定值，$M$ 为全局模数）。

枚举每一个“断开节点”，并且不是叶子，以其为根跑一遍树哈希，看看每个儿子对应的哈希值是否相同即可，总复杂度 $O(n^2)$ 可以通过。

想要继续优化也是容易的，我们只需要借用换根 dp 的思想，在递归的时候同时加入父亲节点的哈希值（不要忘了自己的兄弟），进行检查就可以做到 $O(n)$ 了。

综上，我们没有用到任何观察和性质，解决了这个题目，而且时间复杂度 $O(n^2)$ 就足以[通过](https://codeforces.com/contest/1252/submission/288423221)了。

---

## 作者：happybob (赞：0)

无脑题，甚至范围只开到了 $n\leq 4000$。

比较显然的枚举那个点，然后分成若干连通块，每个连通块以重心为根算树哈希即可做到 $O(n^2)$，实现如果不够精细或者使用了奇怪的哈希可能退化到 $O(n^2 \log n)$，但甚至也可以通过。

这种做法太无脑了。事实上我们有线性做法。注意到题目要求删掉这个点后至少有 $2$ 个连通块，而分出来每个连通块同构，所以这个点必然是原树重心，然后我们就得到了线性做法。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;

using ull = unsigned long long;

const int N = 4005;
const ull B = 114514;

int n;
vector<int> G[N];

inline ull shift(ull x)
{
	if (x == 0) return 0ll;
	x ^= B;
	x ^= (x << 13);
	x ^= (x >> 7);
	x ^= (x << 17);
	x ^= B;
	return x;
}

ull f[N];

bool vis[N];

int sz[N], tot;
vector<int> wc;

void dfs_sz(int u, int fa)
{
	sz[u] = 1;
	tot++;
	for (auto& j : G[u])
	{
		if (j == fa) continue;
		dfs_sz(j, u);
		sz[u] += sz[j];
	}
}

void get_wc(int u, int fa)
{
	int maxsz = tot - sz[u];
	for (auto& j : G[u])
	{
		if (j == fa) continue;
		get_wc(j, u);
		maxsz = max(maxsz, sz[j]);
	}
	if (maxsz <= tot / 2) wc.emplace_back(u);
}

void dfs(int u, int fa)
{
	if (vis[u])
	{
		f[u] = 0;
		return;
	}
	vis[u] = 1;
	f[u] = 1;
	for (auto& j : G[u])
	{
		if (j == fa || vis[j]) continue;
		dfs(j, u);
		f[u] += shift(f[j]);
	}
}

inline bool solve(int x)
{
	for (int i = 1; i <= n; i++) vis[i] = 0;
	vis[x] = 1;
	vector<vector<ull>> hs;
	for (auto& j : G[x])
	{
		tot = 0;
		wc.clear(), wc.shrink_to_fit();
		dfs_sz(j, x);
		get_wc(j, x);
		vector<ull> ve;
		for (auto& k : wc)
		{
			dfs(k, 0);
			ve.emplace_back(f[k]);
		}
		hs.emplace_back(ve);
	}
	if (hs.empty()) return 0;
	for (auto& j : hs[0])
	{
		bool flag = 1;
		for (int k = 1; k < hs.size(); k++)
		{
			bool tag = 0;
			for (auto& y : hs[k]) tag |= (y == j);
			flag &= tag;
			if (!flag) break;
		}
		if (flag)
		{
			return 1;
		}
	}
	return 0;
}

int nsz[N];
int fa[N];

void predfs(int u, int fa)
{
	::fa[u] = fa;
	nsz[u] = 1;
	for (auto& j : G[u])
	{
		if (j ^ fa)
		{
			predfs(j, u);
			nsz[u] += nsz[j];
		}
	}
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	predfs(1, 1);
	int ans = -1;
	for (int i = 1; i <= n; i++)
	{
		int maxn = n - nsz[i];
		for (auto& j : G[i])
		{
			if (j ^ fa[i]) maxn = max(maxn, nsz[j]);
		}
		if (maxn <= n / 2)
		{
			if (solve(i)) ans = max(ans, (int)G[i].size());
		}
	}
	cout << ans << "\n";
	return 0;
}
```

---

## 作者：DengDuck (赞：0)

![](https://cdn.luogu.com.cn/upload/image_hosting/9hxxet3z.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/dhfnnyt1.png)

思路非常显然，满足条件的点必然是重心，但是重心不一定满足条件，所以我们还是要判断一手树同构。

由于重心最多有两个，所以给我们的判定时间很宽松。

我在摸爬滚打之后发现了一种符合原教旨主义的树哈希方式，是可以通过的。

随机 $w=1000$ 个奇数作为模数，然后运用四种合并儿子哈希值的方法跑哈希即可。

时间复杂度为 $\mathcal O(nw)$。

等等，有点小丑，$w=10$ 就可以过了，这下 $\text{joker}$ 了。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
//#define fir first
//#define sec second
using namespace std;
//const LL inf;
const LL N=4005;
const LL M=1000;
LL mod[M];

//const LF eps;
LL n,f[N],sz[N],hsh[N][M];
vector<LL>v[N];
void dfs(LL x,LL fa,LL flg,LL way=-1)
{
	sz[x]=1;
	LL cnt[M];
	if(way!=-1)for(int i=0;i<M;i++)hsh[x][i]=0,cnt[i]=1;
	for(LL i:v[x])
	{
		if(i==fa)continue;
		dfs(i,x,flg);
		sz[x]+=sz[i];
		if(flg)f[x]=max(f[x],sz[i]);
		if(way!=-1)
		for(int j=0;j<M;j++)
		{
			if(way==0)cnt[j]=cnt[j]*hsh[i][j]%mod[j];
			if(way==1)cnt[j]=cnt[j]^hsh[i][j];
			if(way==2)cnt[j]=cnt[j]&hsh[i][j];
			if(way==3)cnt[j]=cnt[j]|hsh[i][j];
		}
	}
	if(way!=-1)for(int i=0;i<M;i++)cnt[i]%=mod[i];
	if(flg)f[x]=max(f[x],n-sz[x]);
	if(way!=-1)for(int i=0;i<M;i++)hsh[x][i]=(1331+cnt[i])%mod[i];
	
}
LL ans;
void work(LL x)
{
	LL mx=0,t[M],cnt=0;
	for(int i=0;i<M;i++)t[i]=0;
	for(LL j:v[x])
	{
		cnt++;
		dfs(j,x,0),mx=max(mx,sz[j]);
		
	}
	for(LL j:v[x])if(sz[j]!=mx)return;
	for(int k=0;k<=3;k++)
	{
		
		for(LL j:v[x])
		{
			dfs(j,x,0,k);
			for(int i=0;i<M;i++)t[i]=hsh[j][i];
		}
		for(LL j:v[x])
		{
			for(int i=0;i<M;i++)if(t[i]!=hsh[j][i])return;
		}		
	}
	
	ans=max(ans,cnt);
}
int main()
{
	srand(time(0));
	scanf("%lld",&n);
	for(int i=1;i<=n-1;i++)
	{
		LL x,y;
		scanf("%lld%lld",&x,&y);
		v[x].pb(y),v[y].pb(x);
	}
	for(int i=0;i<M;i++)
	{
		mod[i]=rand()%1000000000+1000000000;
		if(mod[i]%2==0)mod[i]++;
	}
	dfs(1,0,1);
	LL mn=n;
	for(int i=1;i<=n;i++)mn=min(mn,f[i]);
	for(int i=1;i<=n;i++)
	{
		if(mn==f[i])work(i);
	}
	if(ans!=0)printf("%lld",ans);
	else puts("-1");
	return 0;
}
//RP++
```

---

## 作者：_Flame_ (赞：0)

### $\text{solution}$

前置知识：[树哈希判同构](https://www.luogu.com.cn/problem/P5043)。

删去的点是重心是显然的，但这里提供一种完全不用思考老的做法。

直接枚举每一个点，对于删去这个点后的每一棵子树做树哈希判断是否同构。

若都同构，则找到了一个这样的点，统计子树的个数并对答案去较大值即可。

若有不同构的，则枚举下一个点判断即可。

代码是树同构板子。

---

## 作者：紊莫 (赞：0)

树哈希模版。

首先，有一个结论，就是我们选择删去的节点一定是整棵树的重心。

考虑到同构的必要条件是树的大小相同，而非重心节点显然不可能让子树大小相同。

对于每个重心（至多两个），我们枚举以它为根的所有子树，判断这些子树是否同构即可。

对于子树，也是根据重心来算哈希值，若有两个值，统一去取最大或最小即可。

```cpp
// Problem: F. Regular Forestation
// Contest: Codeforces - sxyz_2_4
// URL: https://codeforces.com/gym/502747/problem/F
// Memory Limit: 256 MB
// Time Limit: 1000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define int long long

#define F(i, a, b) for (int i = (a); i <= (b); i++)
#define dF(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;
inline int rd() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = (x << 1) + (x << 3) + (ch ^ 48);
    ch = getchar();
  }
  return x * f;
}

inline int lowbit(int x) { return x & (-x); }
typedef unsigned long long ull;
typedef pair<int, int> Pair;

const int N = 200005, M = (N << 1), inf = 0x3f3f3f3f, mod = 1e9 + 7;
const ull mask = std::chrono::steady_clock::now().time_since_epoch().count();
int n, siz[N], si[N], ans = -1;
vector<int> G[N], root, wc;
void dfs(int now, int fa, int id) {
  siz[now] = 1;
  int flag = 1;
  for (int i : G[now])
    if (i != fa) {
      dfs(i, now, id);
      siz[now] += siz[i];
      if (siz[i] > n / 2) flag = 0;
    }
  if (id && flag && n - siz[now] <= n / 2) root.push_back(now);
}
ull hsh[N];
ull shift(ull x) {
  x ^= mask;
  x ^= x << 13;
  x ^= x >> 7;
  x ^= x << 17;
  x ^= mask;
  return x;
}
void dfs_hash(int now, int fa, int fob) {
  hsh[now] = 1;
  for (int i : G[now])
    if (i != fa && i != fob) {
      dfs_hash(i, now, fob);
      hsh[now] += shift(hsh[i]);
    }
}
void dfs2(int now, int fa, int nn) {
  si[now] = 1;
  int flag = 1;
  for (int i : G[now])
    if (i != fa) {
      dfs2(i, now, nn);
      si[now] += si[i];
      if (si[i] > nn / 2) flag = 0;
    }
  if (flag && nn - si[now] <= nn / 2) wc.push_back(now);
}
int solve(int root) {
  ull hash = 0;
  for (int i : G[root]) {
    wc.clear();
    F(j, 1, n) si[j] = 0;
    dfs2(i, root, siz[i]);//计算这个子树的重心
    ull x = 0;
    for (int j : wc) {
      F(k, 1, n) hsh[k] = 0;
      dfs_hash(j, 0, root);//求解树哈希
      x = max(x, hsh[j]);//此处统一取最大值
    }
    if (hash == 0)
      hash = x;
    else if (x != hash)
      return -1;
  }
  return G[root].size();
}
signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  F(i, 2, n) {
    int u, v;
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  dfs(1, 0, 1);// 首先通过一次 dfs 求出重心
  int ans = -1;
  for (int i : root) {
    F(j, 1, n) siz[j] = 0;
    dfs(i, 0, 0);//对于每个重心，初始化一下以它为根的子树大小
    ans = max(ans, solve(i));//求解问题
  }
  cout << ans << endl;
  return 0;
}

```


---

