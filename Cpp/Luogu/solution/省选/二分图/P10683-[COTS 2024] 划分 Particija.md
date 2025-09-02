# [COTS 2024] 划分 Particija

## 题目背景

译自 [Izborne Pripreme 2024 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2024/) D2T1。$\texttt{1s,512M}$。

## 题目描述



给定正整数 $ N $。

集合 $ \{1, 2, \ldots, N\} $ 的**划分**为由非空集合组成的集族，满足：
- $\forall 1\le i\le N$，$i$ 出现在**恰好一个**集合中。

例如，$\{\{1,3\},\{2,4\},\{5\}\}$ 是集合 $ \{1, 2, 3, 4, 5\} $ 的一个划分。

可以用数列 $ [x_1, x_2, \ldots, x_N ]$ 来表示划分。当且仅当 $ x_i = x_j $ 时，$ i $ 和 $ j $ 在同一个集合中。上面提到的划分 $\{\{1,3\},\{2,4\},\{5\}\}$ 可以由数列 $[1, 2, 1, 2, 3]$ 或者 $[5, 1, 5, 1, 4]$ 表示。

Patricija 拥有两个划分：第一个划分用数列 $ [a_1, a_2, \ldots, a_N] $ 表示，第二个划分用数列 $ [b_1, b_2, \ldots, b_N] $ 表示。

Patricija 想知道以下问题的答案：如果她使用这两个划分中的集合，来构造集合 $ \{1, 2, \ldots, N\} $ 的划分，至少需要多少个集合。


给定参数 $k\in \{0,1,2\}$，

- 当 $k=0$ 时，你需要回答原问题的答案。
- 当 $k=1$ 时，允许更改 $2N$ 个数字（$a_1,\cdots,a_N,b_1,\cdots,b_N$）中**至多**一个，**最小化**构造划分需要的最少集合数。
- 当 $k=2$ 时，允许更改 $2N$ 个数字（$a_1,\cdots,a_N,b_1,\cdots,b_N$）中**至多**一个，**最大化**构造划分需要的最少集合数。

请注意，你需要保证在你修改后，$\forall 1\le i\le N$，$1\le a_i,b_i\le N$。

## 说明/提示


#### 样例解释

样例 $1$ 解释：

对于第一组数据，第一个划分为 $\{\{1,2\},\{3\},\{4\}\}$，第二个划分为 $\{\{1\},\{2\},\{3,4\}\}$。选取 $\{1,2\},\{3,4\}$ 即可。

对于第二组数据，第一个划分为 $\{\{1,2,3,4\},\{5\},\{6\},\{7\}\}$，第二个划分为 $\{\{1\},\{2\},\{3\},\{4,5,6,7\}\}$。选取第一个划分或第二个划分即可。

#### 数据范围

对于 $100\%$ 的数据，保证：

- $1\le T\le 200\, 000$，$k\in \{0,1,2\}$；
- $1\le a_i,b_i\le N$；
- $1\le N,\sum N\le 200\, 000$。

| 子任务编号 | 分值 | 约束  |
|:-----:|:------:|:-------:|
| $1$  | $7$  | $k=0,N\le 8,\sum 2^N\le 10^5$   |
| $2$  | $23$  | $k=0$  |
| $3$  | $15$  | $k=1,N\le 1\, 000,\sum N^2\le 10^6$ |
| $4$  | $16$  | $k=1$ |
| $5$  | $19$  | $k=2,N\le 1\, 000,\sum N^2\le 10^6$ |
| $6$  | $20$  | $k=2$ |



## 样例 #1

### 输入

```
2 0
4 
1 1 2 3
1 2 3 3
7
1 1 1 1 2 3 4
1 2 3 4 4 4 4```

### 输出

```
2
4```

## 样例 #2

### 输入

```
3 1
4
1 1 2 3
1 2 3 3
4
1 1 1 1
1 2 3 3
7
1 1 1 1 2 3 4
1 2 3 4 4 4 4```

### 输出

```
2
1
2```

## 样例 #3

### 输入

```
3 2
4 
1 1 2 3
1 2 3 3
4
1 1 1 3
1 2 3 3
7
1 1 1 2 3 4 5
1 2 3 4 4 4 4```

### 输出

```
3
3
4```

# 题解

## 作者：Nephren_Sakura (赞：10)

第一次写这么长的题解。

首先我们考虑 $k=0$ 时如何计算答案。

转化一下限制条件，也就是说对于任意一个 $i$，$a_i$ 和 $b_i$ 必须有恰好一个被选择。于是我们选择图论建模。左部点为 $i$，右部点为 $i+n$，连边方式是 $a_i$ 与 $b_i+n$ 连边。

然后限制就被转化成了每条边恰好一个端点被选择，要求选择最少的点。

又因为这是一个二分图，当你选择某个连通块的左部点时，你就必须把整个连通块的左部点选上，和二分图染色一个意思，这点可以手动模拟一下。

于是 $k=0$ 时最后的答案就是所有连通块左部点和右部点数量较小值之和。

然后考虑修改一个数，相当于可以把一条 $(a_i,b_i+n)$ 修改为 $(a_i,x+n)$ 或者 $(x,b_i+n)$，其中 $x$ 为 $1$ 到 $n$ 中的任意点。

现在有一个十分有意思的性质，对于任意四个数 $a,b,c,d$，都有 $\min(a,b)+\min(c,d) \le \min(a+c,b+d)$。

证明是显然的，因为前式相当于 $\min(a+c,a+d,b+c,b+d)$。

也就是说只有当我们**合并**两个连通块时，答案才可能变得更**大**。只有当我们将一个连通块**分割**成两个时，答案才可能变得更**小**。

那么就可以做 $k=1$ 了。考虑将修改转化为一次删除和一次加入，如果我们删除的这条边没有将一个连通块分成两个，那么答案一定不会变得更小。因为下一步操作加边只可能合并让答案变大。也就是说我们修改的边只有可能是**割边**。

而且我们还要考虑加边对答案的影响，但我们发现其实可以做到没有影响。如果你修改的边的端点 $x,y$ 有至少一个在删除这条边后不为孤点，那么你可以把这条边塞到**那个连通块里面**去。否则只要 $n$ 不为 $1$，你必然能找到一个连通块的**左部点数量不超过右部点**，塞进去即可。

对这个值的计算，我们可以预处理出一条边是否是割边以及每个连通块的大小。

然后枚举每个点，如果一个点没去过就以它为根搜一遍 dfs 生成树，同时统计子树内的左部点数量和右部点数量。

如果一条边是割边，它必然会在往下搜的时候被找到，这个时候下面传上来的数量就是割开**这条割边**之后一个连通块的左右部点大小，另一个用总数减去即可。最后求个最小值就做完了

现在我们再来考虑 $k=2$ 的情况。那么只有合并会有正收益。我们贪心的想，如果你现在有一个连通块**左部点超过右部点**，是不是你肯定会连接上一个**右部点超过左部点**的连通块，让这两个连通块**被浪费**的左部点和右部点相互匹配。

因为你还需要删除一条边，所以你需要分成**割边**和**非割边**考虑。

处理出左部点与右部点差值**最大**和**最小**的连通块差值（注意这里的差值不取绝对值）。定义一个连通块**对应的连通块**指：如果左部点大于右部点就取差值最小的，否则就是最大的。

对于一个连通块的**割边**，将其连接的两个连通块分别连接其对应的连通块计算。如果某个连通块里有**非割边**，就直接连接这个连通块和对应的连通块。然后取最大值计算即可。

我个人在 $k=2$ 时的代码实现可能有点神秘，我在统计割边时是直接把**割出来的连通块**的对应连通块当成了整个连通块的对应连通块计算。但这样做因为你取得是最大值所以也能过，应该是对的但我不会证。卡掉了麻烦私信或直接评论一下。$k=2$ 时的代码请谨慎食用。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define F first
#define S second
int T,k,n,a[1000005],b[1000005],siz1,siz2,id[1000005],dfn[1000005],low[1000005],cnt;
vector<pair<int,int> > v[1000005];
vector<pair<int,int> > V;
bool vis[1000005],VIS[1000005];
void pre(int cur){
	if(vis[cur]) return;
	vis[cur]=true,id[cur]=V.size(),siz1+=(cur<=n),siz2+=(cur>n);
	for(auto i:v[cur]) pre(i.F);
	return;
}
void tarjan(int cur,int id){
	dfn[cur]=low[cur]=++cnt;
	for(auto i:v[cur]){
		int nxt=i.F,w=i.S;
		if(id==w) continue;
		if(!dfn[nxt]){
			tarjan(nxt,w);
			low[cur]=min(low[cur],low[nxt]);
			if(low[nxt]>dfn[cur]) VIS[w]=true;
		}
		else low[cur]=min(low[cur],dfn[nxt]);
	}
	return;
}
int mini;
int val[1000005];
pair<int,int> dfs(int cur){
	// cout<<cur<<'\n'
	if(vis[cur]) return {0,0};
	vis[cur]=true;
	int siz1=(cur<=n),siz2=(cur>n);
	for(auto i:v[cur]){
		int nxt=i.F,w=i.S;
		if(vis[nxt]) continue;
		pair<int,int> p=dfs(nxt);
		siz1+=p.F,siz2+=p.S;
		if(VIS[w]) mini=min(mini,-min(V[id[cur]].F,V[id[cur]].S)+min(p.F,p.S)+min(V[id[cur]].F-p.F,V[id[cur]].S-p.S));
	}
	return {siz1,siz2};
}
pair<int,int> DFS(int cur,int fa){
	if(vis[cur]){mini=max(mini,min(abs(V[id[cur]].F-V[id[cur]].S),abs(val[id[cur]])));return {0,0};}
	vis[cur]=true;
	int siz1=(cur<=n),siz2=(cur>n);
	for(auto i:v[cur]){
		int nxt=i.F,w=i.S;
		if(nxt==fa) continue;
		pair<int,int> p=DFS(nxt,cur),P=V[id[cur]];
		siz1+=p.F,siz2+=p.S;
		if(VIS[w]) mini=max(mini,-min(P.F,P.S)+min(p.F,p.S)+min(P.F-p.F,P.S-p.S)+min(abs(val[id[cur]]),max(abs(p.F-p.S),abs((P.F-p.F)-(P.S-p.S)))));
	}
	return {siz1,siz2};
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T>>k;
	while(T--){
		cin>>n;
		V.clear();
		for(int i=1; i<=n; i++) v[i].clear(),v[i+n].clear(),vis[i]=vis[i+n]=false;
		for(int i=1; i<=n; i++) cin>>a[i];for(int i=1; i<=n; i++) cin>>b[i],v[a[i]].push_back({b[i]+n,i}),v[b[i]+n].push_back({a[i],i});
		siz1=siz2=0;
		for(int i=1; i<=n; i++) if(!vis[i]) siz1=siz2=0,pre(i),V.push_back({siz1,siz2});
		if(!k){
			int ans=0;
			for(auto p:V) ans+=min(p.F,p.S);
			cout<<ans<<'\n';
		}
		else if(k==1){
			if(n==1){cout<<"1\n";continue;}
			for(int i=1; i<=n; i++) dfn[i]=low[i]=dfn[i+n]=low[i+n]=VIS[i]=0;
			cnt=0;
			for(int i=1; i<=n; i++) if(!dfn[i]) tarjan(i,0);
			int ans=0;mini=0;
			for(auto p:V) ans+=min(p.F,p.S);
			for(int i=1; i<=n; i++) vis[i]=vis[i+n]=false;
			for(int i=1; i<=n; i++) if(!vis[i]) dfs(i);
			cout<<ans+mini<<'\n';
 		}
		else{
			for(int i=1; i<=n; i++) dfn[i]=low[i]=dfn[i+n]=low[i+n]=VIS[i]=0;
			cnt=0;
			for(int i=1; i<=n; i++) if(!dfn[i]) tarjan(i,0);
			int ans=0;mini=0;
			for(auto p:V) ans+=min(p.F,p.S);
			for(int i=1; i<=n; i++) vis[i]=vis[i+n]=false;
			bool f1=false,f2=false;
			sort(a+1,a+n+1),sort(b+1,b+n+1);
			for(int i=1; i<=n; i++) if(a[i]==a[i-1]) f1=true;
			for(int i=1; i<=n; i++) if(b[i]==b[i-1]) f2=true;
			for(int i=0; i<V.size(); i++) if(V[i].F>V[i].S) val[i]=-f2;else val[i]=f1;
			int mn=0,mx=0;
			for(int i=0; i<V.size(); i++) mn=min(mn,V[i].F-V[i].S),mx=max(mx,V[i].F-V[i].S);
			for(int i=0; i<V.size(); i++) if(V[i].F-V[i].S>0) val[i]=min(val[i],mn);else val[i]=max(val[i],mx);
			for(int i=1; i<=n; i++) if(!vis[i]) DFS(i,0);
			cout<<ans+mini<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：oMin0 (赞：5)

某怪兽老师模拟赛的签到题。

## 分析

首先考虑 $k=0$ 怎么算答案。对每个 $i$ 来说，唯一的要求是 $a_i$ 与 $b_i$ 必须恰有一个被选择。那么套路地想到把 $(a_i,b_i+n)$ 连边建二分图（记编号 $\leq n$ 的为左部点，$>n$ 的为右部点），则每个连通块对答案的贡献是左右部点数量的 $\min$，进行 $O(n)$ 的二分图染色即可解决。

再考虑修改。修改一个数相当于修改一条边（可以把 $(x,y)$ 修改成 $(x,i)$ 或 $(i,y)$），那么考虑枚举这条边做分讨。

当 $k=1$ 时，你希望断开一个连通块（因为 $\min(x_1,y_1)+\min(x_2,y_2)<\min(x_1+x_2,y_1+y_2)$），那么显然你需要断开割边并将其连到小连通块内部，其贡献可以在边双缩点后简单维护。注意有特殊情况，当连通块只有两个点 $u,v(u<v)$ 时无法连到内部，但当 $n>1$ 时一定另有一个连通块的左部点数量不多于右部点数量，断开割边后将 $v$ 与该连通块连接有相同的作用。因此只需特判 $n=1$ 时答案为 $1$。

当 $k=2$ 时，你希望连接两个连通块，枚举要断开的边和其两个端点，不妨设该端点所在连通块的左部点数量小于右部点数量，则将其与 右部点数量-左部点数量 最大的连通块连接起来一定最优，那么这也可以简单维护。

## 代码

综上所述，做完了。放上赛时代码。

```cpp
/*
  author: honglan0301
  Sexy_goodier _ xiaoqing
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cctype>
#include <queue>
#include <map>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <bitset>
#include <assert.h>
using namespace std;
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define int long long
#define ll long long
#define ull unsigned long long
#define mod 998244353
#define G 3
#define Gi 332748118
mt19937 rnd(time(0));
mt19937_64 rndl(time(0));
#define endl "\n"

int T,k,n,a[200005],b[200005],csans,tans;
int cntlt,cnt1[400005],cnt2[400005],flaglt[400005];
int dfn[400005],low[400005],cntd,stk[400005],top,vis[400005],cntb,flagltb[400005],flag[400005],val1[400005],val2[400005];
vector <pair<int,int>> e[400005];

void dfs(int x,int frm)
{
	cnt1[cntlt]+=(x<=n); cnt2[cntlt]+=(x>n); flaglt[x]=cntlt;
	dfn[x]=low[x]=++cntd; stk[++top]=x; vis[x]=1;
	for(auto i:e[x])
	{
		if(i.se==frm) continue;
		if(!dfn[i.fi]) dfs(i.fi,i.se),low[x]=min(low[x],low[i.fi]);
		else if(vis[i.fi]) low[x]=min(low[x],dfn[i.fi]);
	}
	if(dfn[x]==low[x])
	{
		cntb++; while(1) {int nr=stk[top--]; vis[nr]=0; flag[nr]=cntb; flagltb[cntb]=cntlt; val1[cntb]+=(nr<=n); val2[cntb]+=(nr>n); if(nr==x) break;}
	}
}

vector <int> g[400005];

void solve0()
{
	for(int i=1;i<=2*n;i++) e[i].clear();
	for(int i=1;i<=n;i++) e[a[i]].pb(mp(b[i]+n,i)),e[b[i]+n].pb(mp(a[i],i));
	for(int i=1;i<=2*n;i++) dfn[i]=low[i]=stk[i]=vis[i]=flag[i]=val1[i]=val2[i]=flaglt[i]=0; top=0; csans=0; cntlt=0; cntb=0;
	for(int i=1;i<=2*n;i++)
	{
		if(!dfn[i]&&e[i].size()!=0)
		{
			cntlt++; cnt1[cntlt]=cnt2[cntlt]=0; 
			dfs(i,-1); csans+=min(cnt1[cntlt],cnt2[cntlt]);
		}
	}
	for(int i=1;i<=cntb;i++) g[i].clear();
	for(int i=1;i<=2*n;i++) for(auto j:e[i]) if(flag[i]!=flag[j.fi]) g[flag[i]].pb(flag[j.fi]); 
}
void solve1()
{
	cout<<csans<<endl;
}

void dfs2(int x,int fat)
{
	vis[x]=1;
	for(auto i:g[x])
	{
		if(i==fat) continue; dfs2(i,x);
		tans=min(tans,csans-min(cnt1[flagltb[x]],cnt2[flagltb[x]])+min(val1[i],val2[i])+min(cnt1[flagltb[x]]-val1[i],cnt2[flagltb[x]]-val2[i]));
		val1[x]+=val1[i]; val2[x]+=val2[i];
	}
}
void solve2()
{
	tans=csans;
	for(int i=1;i<=cntb;i++) vis[i]=0;
	for(int i=1;i<=cntb;i++) if(!vis[i]) dfs2(i,i);
	cout<<max(tans,1ll)<<endl;
}

multiset <int> ss;

void ck(int k,int p)
{
	if(!ss.size()) return;
	if(p>0)
	{
		int nr=(*ss.begin());
		if(nr<0) tans=max(tans,csans+k+min(p,-nr));
	}
	else
	{
		int nr=(*--ss.end());
		if(nr>0) tans=max(tans,csans+k+min(nr,-p));
	}
}
void dfs3(int x,int fat)
{
	vis[x]=1; if(val1[x]+val2[x]>1) ck(0,cnt2[flagltb[x]]-cnt1[flagltb[x]]);
	for(auto i:g[x])
	{
		if(i==fat) continue; dfs3(i,x);
		ck(-min(cnt1[flagltb[x]],cnt2[flagltb[x]])+min(val1[i],val2[i])+min(cnt1[flagltb[x]]-val1[i],cnt2[flagltb[x]]-val2[i]),val2[i]-val1[i]);
		ck(-min(cnt1[flagltb[x]],cnt2[flagltb[x]])+min(val1[i],val2[i])+min(cnt1[flagltb[x]]-val1[i],cnt2[flagltb[x]]-val2[i]),(cnt2[flagltb[x]]-val2[i])-(cnt1[flagltb[x]]-val1[i]));
		val1[x]+=val1[i]; val2[x]+=val2[i];
	}
}
void solve3()
{
	tans=csans;
	for(int i=1;i<=cntb;i++) vis[i]=0; ss.clear();
	for(int i=1;i<=cntlt;i++) ss.insert(cnt2[i]-cnt1[i]);
	for(int i=1;i<=n;i++) if(!dfn[i]) ss.insert(-1);
	for(int i=n+1;i<=2*n;i++) if(!dfn[i]) ss.insert(1); 
	for(int i=1;i<=cntb;i++) if(!vis[i]) {ss.erase(ss.lower_bound(cnt2[flagltb[i]]-cnt1[flagltb[i]])); dfs3(i,i); ss.insert(cnt2[flagltb[i]]-cnt1[flagltb[i]]);}
	cout<<tans<<endl;
}

signed main()
{
//	freopen("div.in","r",stdin);
//	freopen("div.out","w",stdout);
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(0);
	cin>>T>>k;
	while(T--)
	{
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++) cin>>b[i]; solve0();
		if(k==0) solve1(); else if(k==1) solve2(); else if(k==2) solve3(); 
	}
}

/*

1 1
7
7 7 7 7 7 7 7
5 5 1 7 4 3 1

*/
```

---

## 作者：modfish_ (赞：0)

## 思路
考虑建一张二分图，它的左部点和右部点被强制钦定（即一个点的左右是确定的）。其有 $n$ 个编号为 $1$ 到 $n$ 的左部点和 $n$ 个编号为 $1$ 到 $n$ 的右部点。对于每一个 $i$，连一条边 $(a_i,b_i)$，表示将左部 $a_i$ 和右部 $b_i$ 连接。

### $k=0$
这样必定会得到一个由若干二分图连通块组成的图。每个点表示一个划分的子集，每条边表示一个元素。

我们希望对于每一条边，它的端点中有且仅有一个被选择，要求选择的点数最少。

容易发现，对于一个连通块，要么选择它的所有左部点，要么选择它的所有右部点。

#### 证明
如果我们钦定某个点要选，那么所有和它距离为 $1$ 的点都不能选。相应的，所有与它距离为 $2$ 的都要选（若不选，则存在一条边，它的两个端点都没被选），所有与它距离为 $3$ 的点都要选。以此类推，所有与它相距为奇数的点都不能选，所有与它相距为偶数的都必须选，所以所有和他同侧的都要选，不同侧的都不选。

若钦定某个点不选也同理。

那么，我们处理出每个连通块的左部点个数和右部点个数，取 $\min$ 再求和即可。

### $k=1$
现在，我们可以更改某条边的一个端点。

发现如果将两个连通块连起来一定不优。

#### 证明
设第一个连通块左、右部点分别有 $a,b$ 个，第二个分别有 $c,d$ 个。

连接前，这两个连通块的贡献为 $\min(a,b)+\min(c,d)$。连接后，其贡献为 $\min(a+c,b+d)$。

因为：

$$\min(a,b)+\min(c,d)=\min(a+c,b+d,a+d,b+c)$$

又有：

$$\min(a+c,b+d,a+d,b+c)=\min(\min(a+c,b+d),a+d,b+c)\le \min(a+c,b+d)$$

所以不会更优。

相应的，将一个连通块断成两个一定不会更劣，考虑枚举每条边，考虑断开它会不会使答案变优。

可以跑 Tarjan 求割边，然后挨个断开试试。

但是这种方法必须要判掉 $n=1$ 的情况，因为这时无法断开一条边。

### $k=2$
与 $k=1$ 类似，我们要尝试将某两个连通块连起来。仍然枚举每条边，考虑将其断开再连上后，可能使答案变得多大。

容易发现，问题转换为以下这个问题：

给定 $m$ 二元组 $(l_i,r_i)$，每次给定一个二元组 $(L,R)$，求出：

$$\max_{i=1}^m(\min(L+l_i,R+r_i) - \min(l_i,r_i))$$

我们本质上就是要求出最大的 $k$，使得存在某个 $x$，满足：

$$\min(L+l_x,R+r_x)-\min(l_x,r_x)\ge k$$

也即：

$$l_x-\min(l_x,r_x)\ge k-L$$

$$r_x-\min(l_x,r_x)\ge k-R$$

考虑二分 $k$，用主席树 check，然后就可以了。

复杂度：

$k=0,1$ 时 $O(n\alpha(n))$，$k=2$ 时 $O(n\log^2 n)$。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 5;

int n;
int a[maxn], b[maxn], fa[maxn << 1], sizl[maxn << 1], sizr[maxn << 1], tag[maxn << 1];
int head[maxn << 1], nxt[maxn << 1], to[maxn << 1], cnt = 1, dfn[maxn << 1], dnt = 0, low[maxn << 1], sl[maxn << 1], sr[maxn << 1];

struct node{
	int l, r;
}bs[maxn];
int rt[maxn << 1], m;
bool cmp(node x, node y){
	return x.l < y.l;
}

namespace seg{
int lc[maxn * 80], rc[maxn * 80], siz[maxn * 80], tot = 0;
void update(int &x, int pr, int l, int r, int id){
	x = ++ tot, lc[x] = lc[pr], rc[x] = rc[pr], siz[x] = siz[pr] + 1;
	if(l == r) return;
	int mid = l + r >> 1;
	if(id <= mid) update(lc[x], lc[pr], l, mid, id);
	else update(rc[x], rc[pr], mid + 1, r, id);
}
int query(int xl, int xr, int l1, int r1, int l, int r, int ql, int qr, int cutl, int cutr){
	if(ql <= l && r <= qr){
		if(l1 <= cutl && cutl <= r1 && l <= cutr && cutr <= r) return siz[xr] - siz[xl] - 1;
		else return siz[xr] - siz[xl];
	}
	int mid = l + r >> 1, res = 0;
	if(ql <= mid) res += query(lc[xl], lc[xr], l1, r1, l, mid, ql, qr, cutl, cutr);
	if(qr > mid) res += query(rc[xl], rc[xr], l1, r1, mid + 1, r, ql, qr, cutl, cutr);
	return res;
}}
int find(int x){
	if(x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}
void merge(int u, int v){
	nxt[++ cnt] = head[u], to[cnt] = v, head[u] = cnt;
}
void Tarjan(int x, int pi, int ans, int &rans, int k){
	dfn[x] = low[x] = ++ dnt;
	if(x <= n) sl[x] = 1, sr[x] = 0;
	else sr[x] = 1, sl[x] = 0;
	for(int i = head[x]; i; i = nxt[i]){
		int j = to[i];
		if(dfn[j]){
			if((i ^ pi) != 1) low[x] = min(low[x], dfn[j]);
		}else{
			Tarjan(j, i, ans, rans, k);
			low[x] = min(low[x], low[j]);
			sl[x] += sl[j], sr[x] += sr[j];
		}
	}
	if(!pi) return;
	int fi = find(x);
	if(dfn[x] == low[x]){
		if(k == 1) rans = min(rans, ans - min(sizl[fi], sizr[fi]) + min(sl[x], sr[x]) + min(sizl[fi] - sl[x], sizr[fi] - sr[x]));
		else{
			int l = 0, r = n << 1, res = 0;
			while(l <= r){
				int mid = l + r >> 1;
				int mxl = max(mid - sl[x], 0), mxr = max(mid - sr[x], 0);
				if(seg::query(mxl ? rt[mxl - 1] : 0, rt[n << 1], mxl, n << 1, 0, n << 1, mxr, n << 1, sizl[fi] - min(sizl[fi], sizr[fi]), sizr[fi] - min(sizl[fi], sizr[fi]))) l = mid + 1, res = mid;
				else r = mid - 1;
			}
			rans = max(rans, ans - min(sizl[fi], sizr[fi]) + res + min(sizl[fi] - sl[x], sizr[fi] - sr[x]));
			l = 0, r = n << 1, res = 0;
			while(l <= r){
				int mid = l + r >> 1;
				int mxl = max(mid - (sizl[fi] - sl[x]), 0), mxr = max(mid - (sizr[fi] - sr[x]), 0);
				if(seg::query(mxl ? rt[mxl - 1] : 0, rt[n << 1], mxl, n << 1, 0, n << 1, mxr, n << 1, sizl[fi] - min(sizl[fi], sizr[fi]), sizr[fi] - min(sizl[fi], sizr[fi]))) l = mid + 1, res = mid;
				else r = mid - 1;
			}
			rans = max(rans, ans - min(sizl[fi], sizr[fi]) + res + min(sl[x], sr[x]));
		}
	}else if(k == 2){
		int l = 0, r = n << 1, res = 0;
		while(l <= r){
			int mid = l + r >> 1;
			int mxl = max(mid - sizl[fi], 0), mxr = max(mid - sizr[fi], 0);
			if(seg::query(mxl ? rt[mxl - 1] : 0, rt[n << 1], mxl, n << 1, 0, n << 1, mxr, n << 1, sizl[fi] - min(sizl[fi], sizr[fi]), sizr[fi] - min(sizl[fi], sizr[fi]))) l = mid + 1, res = mid;
			else r = mid - 1;
		}
		rans = max(rans, ans - min(sizl[fi], sizr[fi]) + res);
	}
}

int main(){
	int T, k;
	scanf("%d %d", &T, &k);
	while(T --){
		scanf("%d", &n);
		for(int i = 1; i <= n * 2; i ++) fa[i] = i;
		for(int i = 1; i <= n; i ++) scanf("%d", &a[i]), sizl[i] = 1, sizr[i + n] = 1;
		for(int i = 1; i <= n; i ++) scanf("%d", &b[i]), b[i] += n;
		if(n == 1){
		    printf("1\n");
    		for(int i = 1; i <= n * 2; i ++) fa[i] = sizl[i] = sizr[i] = tag[i] = head[i] = dfn[i] = low[i] = sl[i] = sr[i] = 0;
    		for(int i = 1; i <= cnt; i ++) nxt[i] = to[i] = 0;
			dnt = 0, cnt = 1;
    		continue;
		}
		for(int i = 1; i <= n; i ++){
			if(find(a[i]) != find(b[i])) sizl[find(b[i])] += sizl[find(a[i])], sizr[find(b[i])] += sizr[find(a[i])], fa[find(a[i])] = find(b[i]);
			merge(a[i], b[i]), merge(b[i], a[i]);
		}
		int ans = 0;
		for(int i = 1; i <= n; i ++){
			if(!tag[find(a[i])]){
				ans += min(sizl[find(a[i])], sizr[find(a[i])]), tag[find(a[i])] = 1;
				bs[++ m] = (node){sizl[find(a[i])] - min(sizl[find(a[i])], sizr[find(a[i])]), sizr[find(a[i])] - min(sizl[find(a[i])], sizr[find(a[i])])};
			}
		}
		bs[++ m] = (node){0, 1}, bs[++ m] = (node){1, 0};
		for(int i = 1; i <= n * 2; i ++) tag[i] = 0;
		if(k == 0){
			printf("%d\n", ans);
		}else if(k == 1){
			int rans = ans;
			for(int i = 1; i <= n; i ++){
				if(!tag[find(a[i])]){
					Tarjan(a[i], 0, ans, rans, k);
					tag[find(a[i])] = 1;
				}
			}
			printf("%d\n", rans);
		}else if(k == 2){
			sort(bs + 1, bs + m + 1, cmp);
			int s = 1;
			rt[0] = 0;
			for(int i = 0; i <= n << 1; i ++){
				if(i) rt[i] = rt[i - 1];
				while(s <= m && bs[s].l == i) seg::update(rt[i], rt[i], 0, n << 1, bs[s].r), s ++;
			}
			int rans = ans;
			for(int i = 1; i <= n; i ++){
				if(!tag[find(a[i])]){
					Tarjan(a[i], 0, ans, rans, k);
					tag[find(a[i])] = 1;
				}
			}
			printf("%d\n", rans);
		}
		for(int i = 1; i <= n * 2; i ++) fa[i] = sizl[i] = sizr[i] = tag[i] = head[i] = dfn[i] = low[i] = sl[i] = sr[i] = 0;
		for(int i = 1; i <= cnt; i ++) nxt[i] = to[i] = 0;
		dnt = 0, cnt = 1, seg::tot = 0, m = 0;
	}
	return 0;
}
```
不得不承认这个 $k=2$ 处理得过于复杂了。

但我真没想到贪心。

---

## 作者：xiaoliebao1115 (赞：0)

## solve
### $k=0$
对于每一个 $i$ 来讲 $a_i$ 和 $b_i$ 只能选择其中一个点，并且 $a_i$ 不会影响到 $a$ 中不同于 $a_i$ 的其他元素，对于 $a_i$ 或者说 $b_i$ 相同的 $i$ 应当被视作同一个点。显然我们应该按照 $a_i$ 和 $b_i$ 建立二分图，但是因为 $a_i$ 和 $b_i$ 有重复的标号，所以将 $b_i+N$ 和 $a_i$ 连边。

这样建立出来的二分图会形成若干个连通块，对于每一个连通块，问题就转化成了要选出尽可能少的点，使得每条边都和一个选中的点相连，其实就是满足题目中的所有条件。那么这个连通块的答案就是**左右部点中点数较小的那个**。因为不可能存在先选一个左部点再选一个右部点的情况，可以自行画图验证，如果有这样的情况出现，那么一定还有边并未被覆盖。

把所有答案加起来即可。

### $k=1$
首先有一个结论就是你把两个连通块合并成一个，答案一定是增加的，否则断开是减少的，不一定严格。

我们现在需要断开一个连通块，使其最小化，那么一定要断开的是割边，并且添加到割出来的两部分的内部，这个东西边双缩点之后还是很好维护的。

#### 特殊情况
但是当这个连通块只有两个点的时候不能这么干，所以去找一个左端点数量小于等于右端点的，把这条割边加到右端点那里，最小值不变，且对于当前连通块答案减去 $1$。在 $n>1$ 时，一定是除了当前连通块能够找到一个左端点数量小于等于右端点的其他块，因为剩下点的数量一定相同，且不止有当前这样一个连通块。
### $k=2$
我们需要连接两个连通块，使其最大化。但是注意在连接的同时，我们必须要先断开一条边才能连。那么我们枚举断边，如果断边所在连通块右数量大于左数量，那么我们找到左数量减去右数量最大的连起来一定最优，反之，亦然。因为我们要让左右点数量尽可能均匀。

默默撒花。

---

