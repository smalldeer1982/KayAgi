# [ABC163F] path pass i

## 题目描述

给定一棵 $n$ 个点的树，给第 $i$ 个点染上颜色 $c_i$，其中，$c_i$ 为 $[1,n]$ 的一个整数。

现在，对于每一种颜色 $k$，你要求出有多少条简单路径满足路径上至少有一个点的颜色为 $k$。

## 说明/提示

### 数据范围
- $1 \le n \le 2 \times 10^5$
- $1 \le c_i \le n$
- $1 \le u_i, v_i \le n$

## 样例 #1

### 输入

```
3
1 2 1
1 2
2 3```

### 输出

```
5
4
0```

## 样例 #2

### 输入

```
1
1```

### 输出

```
1```

## 样例 #3

### 输入

```
2
1 2
1 2```

### 输出

```
2
2```

## 样例 #4

### 输入

```
5
1 2 3 4 5
1 2
2 3
3 4
3 5```

### 输出

```
5
8
10
5
5```

## 样例 #5

### 输入

```
8
2 7 2 5 4 1 7 5
3 1
1 2
2 7
4 5
5 6
6 8
7 8```

### 输出

```
18
15
0
14
23
0
23
0```

# 题解

## 作者：CmsMartin (赞：17)

[更好的阅读体验](http://cmsblog.top/archives/abc163fpathpassi)

## 题目描述

给定一棵 $n$ 个点的树，给第 $i$ 个点染上颜色 $c_i$，其中，$c_i$ 为 $[1,n]$ 的一个整数。

现在，对于每一种颜色 $k$，你要求出有多少条简单路径满足路径上至少有一个点的颜色为 $k$。

（$1 \le k \le n \le 2\times 10^5$）

## 思路

正难则反，考虑所有不包含颜色 $i$ 的路径数量。

如果只求一个，非常简单，删掉所有颜色为 $i$ 的节点，然后树会分为很多很多的联通块。然后设共 $k$ 个联通块，第 $i$ 个联通块的大小为 $s_i$，则答案为：

$$
\sum\frac{s_i(s_i+1)}{2}
$$

然后这样做时间复杂度为 $\Theta(n^2)$ 的，无法接受。

我们设 $sum_i$ 表示我们在树上已经枚举到的过程中，所有颜色为 $i$ 的子树的总大小（如果有包含，记录最大的）。

对于某一节点的每一个子树，找到每一个颜色相同的，之间相隔的点两两可以形成不包含该颜色的路径，用总方案数减去这些方案数即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/9j3aydx2.png)

如图，假设现在在做红色（下面称为颜色 $x$）节点，则答案为 $size_y - k$。

那么 $k$ 怎么算呢？

我们在做 $y$ 之前记一个 $sum_x'$，然后昨晚下面的红色节点后在记一个 $sum_x$，那么 $k = sum_x-sum_x'$。

最后我们要干掉与根相连的边，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/2kg6sz9v.png)

也就是 $n - sum_i$。

具体实现看代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 2e5 + 10;

ll N;
ll Size[MAXN], Color[MAXN], Ans[MAXN], Count[MAXN];
vector<int> G[MAXN];

ll Sum(ll x) {
	return x * (x + 1) / 2ll;
}

void DFS(int u, int fa) {
	Size[u] = 1;
	ll tmp = Count[Color[u]];
	ll c = Color[u];
	for (int v : G[u]) {
		if (v == fa) continue;
		int t = Count[c];
		DFS(v, u);
		int Ad = Count[c] - t;
		Size[u] += Size[v];
		Ans[c] -= Sum(Size[v] - Ad);
	}
	Count[c] = tmp + Size[u];
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for (int i = 1; i <= N; i++) cin >> Color[i];
	for (int i = 1; i < N; i++) {
		static int x, y;
		cin >> x >> y;
		G[x].emplace_back(y);
		G[y].emplace_back(x);
	}
	for (int i = 1; i <= N; i++) Ans[i] = Sum(N);
	DFS(1, -1);
	for (int i = 1; i <= N; i++) {
		cout << Ans[i] - Sum(N - Count[i]) << endl;
	}
	return 0;
}
```

---

## 作者：EuphoricStar (赞：14)

感觉我的做法比较奇葩（

容斥，总路径数减去只走点权为 $k$ 的路径。设点权为 $k$ 的点数为 $c_k$，点权**不为 $k$** 的点构成的每个连通块大小为 $s_i$，那么 $ans_k = \frac{n(n-1)}{2} - \sum \frac{s_i (s_i - 1)}{2} + c_k$。

考虑快速计算 $\sum \frac{s_i (s_i - 1)}{2}$，考虑线段树分治，每条边 $(u,v)$ 当 $k \ne a_u \land k \ne a_v$ 是有用的，把它插入对应结点，然后直接上可撤销并查集维护即可。

复杂度 $O(n \log^2 n)$。

[code](https://atcoder.jp/contests/abc163/submissions/41323316)

---

## 作者：_maojun_ (赞：6)

一个比较好想但不一定好写的实现方法。

---

正着应该也可以做，但是分讨挺多的。考虑正难则反。

设一个大小为 $n$ 的联通块中路径的数量为 $f(n)$。**可重复**地选择两个点，所以方案数 $f(n)=\dfrac{n(n+1)}2$。

考虑一个颜色怎么做。把该颜色的点和与之相连的边删除，得到若干个联通块，设这些联通块为 $T$，则不经过这种颜色的路径数就是 $\sum f(T)$，那么经过这个颜色的总路径数为 $f(n)-\sum f(T)$。

这个东西应该不难求。但如果对于每种颜色都跑一边那么就是 $O(n^2)$ 的，发现每种颜色的数量加起来等于 $n$，所以直接上虚树。

对于每种颜色建虚树。维护以某个点为跟向下有多少的点必然经过标记节点（就是所有能**在遇到其他标记节点前遇到的标记节点**的子树大小之和），设为 $sz_u$（$siz_u$ 为原树中的子树大小）；以及一个点如果打上标记且后代都没有打标记的方案数，即 $\sum\limits_{v\in son_u}f(siz_v)$，就是把每个儿子作为联通块的答案，设为 $res_u$。

考虑在虚树上统计不经过该颜色的路径数。

对于一个打标记的点 $u$，首先假设所有儿子都没有标记，即 $sum\gets sum+res_u$。

如果有一个儿子为虚树上的点（不一定有标记），设为 $v$，用倍增找到 $u$ 的儿子 $s$，满足以 $s$ 为根的子树包含 $v$。则先将 $s$ 的贡献剥离出来，再将 $s$ 到 $v$ 这一个联通块的答案加上，即 $sum\gets sum-f(siz_s)+f(siz_s-sz_v)$。注意因为 $v$ 不一定标记，所以不是 $siz_v$。

如果这个点是标记的节点，那么 $sz_u=siz_u$，否则 $sz_u=\sum\limits_{v\in son_u}sz_v$，就是所有儿子的加起来。

最后发现还漏了些什么。如果根节点 $1$ 没有打标记，那么 $1$ 所在的联通块也会产生贡献，而这个联通块的大小就是 $n-sz_1$。

感觉比那种 vector 维护什么东西的好像一点（吧）。

于是就做完了。复杂度 $O(n\log n)$，常数还大，不知道有什么用。

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#define mem(arr,val) memset((arr),(val),sizeof(arr))
using namespace std;

typedef long long ll;
inline ll calc(ll x){return x*(x+1)>>1;}
const int MAXN=2e5+5;
int n,c[MAXN];
int tot=0,head[MAXN];
struct Edge{
	int to,nxt;Edge(){}
	Edge(int to,int nxt):to(to),nxt(nxt){}
}edge[MAXN<<1];
inline void AddEdge(int u,int v){edge[++tot]=Edge(v,head[u]);head[u]=tot;}
inline void Add(int u,int v){AddEdge(u,v);AddEdge(v,u);}

const int MAXK=25;
int dfc=0,lg[MAXN],fa[MAXN][MAXK],dep[MAXN],siz[MAXN],dfn[MAXN];
ll res[MAXN];
void dfs(int u,int fath){					// 倍增
	dfn[u]=++dfc;fa[u][0]=fath;dep[u]=dep[fath]+1;
	for(int k=1;k<=lg[dep[u]];k++)
		fa[u][k]=fa[fa[u][k-1]][k-1];
	siz[u]=1;
	for(int i=head[u];i!=0;i=edge[i].nxt){
		int v=edge[i].to;if(v==fath)continue;
		dfs(v,u);siz[u]+=siz[v];
		res[u]+=calc(siz[v]);
	}
}
inline void init(){
	for(int i=1;i<=n;i++)lg[i]=lg[i>>1]+1;
	dfs(1,0);
}
inline int LCA(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	while(dep[u]>dep[v])u=fa[u][lg[dep[u]-dep[v]]-1];
	if(u==v)return u;
	for(int k=lg[dep[u]];k>=0;k--)
		if(fa[u][k]^fa[v][k])u=fa[u][k],v=fa[v][k];
	return fa[u][0];
}
inline int getson(int u,int v){
	for(int k=lg[dep[v]-dep[u]];k>=0;k--)
		if(fa[v][k]&&dep[fa[v][k]]>dep[u])v=fa[v][k];
	return v;
}
namespace VirtualTree{						// 虚树
	int s,h[MAXN];bool flag[MAXN];
	int top,stk[MAXN];
	inline void build(){
		sort(h+1,h+s+1,[&](int x,int y){return dfn[x]<dfn[y];});
		stk[top=1]=1;
		for(int i=1;i<=s;i++)if(h[i]^1){
			int lca=LCA(h[i],stk[top]);
			if(lca^stk[top]){
				while(dfn[stk[top-1]]>dfn[lca])Add(stk[top],stk[top-1]),top--;
				Add(lca,stk[top--]);
				if(lca^stk[top])stk[++top]=lca;
			}
			stk[++top]=h[i];
		}
		while(top>1)Add(stk[top],stk[top-1]),top--;
		tot=0;
	}
	ll sum;int sz[MAXN];
	void dfs(int u,int fath){
		if(flag[u])sum+=res[u];
		else sz[u]=0;
		for(int i=head[u];i!=0;i=edge[i].nxt){
			int v=edge[i].to;if(v==fath)continue;
			dfs(v,u);
			if(flag[u]){					// 如果是打标记的节点才统计答案.
				int s=getson(u,v);
				sum=sum-calc(siz[s])+calc(siz[s]-sz[v]);
			}else sz[u]+=sz[v];
		}
		if(flag[u])sz[u]=siz[u];
		head[u]=0;
	}
	inline ll solve(){
		build();
		for(int i=1;i<=s;i++)flag[h[i]]=true;
		sum=0;
		dfs(1,0);
		for(int i=1;i<=s;i++)flag[h[i]]=false;
		return calc(n)-sum-calc(n-sz[1]);	// 注意最后算出来的是不包含的，所有包含的要用所有减不包含。
	}
}using namespace VirtualTree;

int id[MAXN];ll ans[MAXN];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&c[i]),id[i]=i;
	sort(id+1,id+n+1,[&](int x,int y){return c[x]<c[y];});
	for(int i=1,u,v;i<n;i++)scanf("%d%d",&u,&v),Add(u,v);
	init();
	tot=0;mem(head,0);
	for(int i=2,lst=1;i<=n+1;i++)if(c[id[i]]^c[id[i-1]]){
		s=0;
		for(int j=lst;j<=i-1;j++)h[++s]=id[j];
		int col=c[id[lst]];
		ans[col]=solve();					// 有些颜色可能没有出现，但是也要输出 0，所有不能直接在这里输出。
		lst=i;
	}
	for(int i=1;i<=n;i++)printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：Rushroom (赞：5)

ABC 好题，写起来也不是很复杂。

[传送门](https://www.luogu.com.cn/problem/AT4820)

## 思路

我们看题面中的这一句话：

>求出有多少条简单路径满足路径上至少有一个点的颜色为 $k$

我们觉得这很难，所以考虑正难则反：

>求出有多少条简单路径满足路径上没有任何一个点的颜色为 $k$

很容易想到，先删去所有颜色为 $k$ 的点，那么剩下的点就会构成若干个连通块，我们设共有 $m$ 个连通块，第 $i$ 个连通块的节点数量为 $siz_i$ ，那么这个连通块对答案的贡献就是 $\sum_{i=1}^n \frac{siz_i\cdot (siz_i+1)}{2}$。

那么，怎么计算连通块的大小呢？

我们看下面这张图。

![](https://cdn.luogu.com.cn/upload/image_hosting/7obg0q05.png)

（红色表示颜色为 $k$ 的点，蓝色表示一个连通块）

显然，我们只需要统计每一个颜色为 $k$ 的点，然后枚举它的每一个儿子节点 $s$，$s$ 所在的连通块大小就是以 $s$ 为根的子树大小减去以颜色为 $k$ 的点为根的子树大小。

（当根的颜色不为 $k$ 时，不要忘了统计根所在连通块的大小）

我们可以先 DFS 一遍，用栈处理出每个节点的最近的和它颜色相同的祖先，这样可以快速找到以 $s$ 为根的子树中颜色为 $k$ 的节点。时间复杂度优化到 $O(n)$。

~~十年 OI 一场空，不开 long long 见祖宗~~

## Code

```cpp
/*
 * @Description: I want to be the weakest vegetable in the world!
 * @Author: CGBoy
 * @Date: 2022-01-29 09:40:10
 */
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define forr(i,a,n) for(int i=a;i<=n;i++)
#define rep(i,n) forr(i,0,n-1)
#define repp(i,n) forr(i,1,n)
#define pb push_back
#define mp make_pair
#define init(a,i) memset(a,i,sizeof(a))
#define fi first
#define se second
#define mod 1000000007
#define MOD 998244353
#define MAXN 0x3f3f3f3f
int T, case_;
int n, c[200005], x, y, dfn[200005], lst[200005], siz[200005], cur = -1;
stack<int>st[200005];
vector<vector<int>>t, v, emp;
ll ans[200005];
ll score(int i) {
    return (ll)i * (ll)(i + 1) / 2ll;
}
void dfs1(int k, int from) {
    if (!st[c[k]].empty())v[st[c[k]].top()].pb(k);
    else emp[c[k]].pb(k);
    st[c[k]].push(k);
    dfn[k] = ++cur;
    siz[k] = 1;
    if (t[k].size())
        rep(i, t[k].size())if (t[k][i] != from) {
        dfs1(t[k][i], k);
        siz[k] += siz[t[k][i]];
    }
    st[c[k]].pop();
    lst[k] = cur;
}
void dfs2(int k, int from) {
    int p = 0;
    if (t[k].size())
        rep(i, t[k].size()) {
        if (t[k][i] == from)continue;
        int u = t[k][i], sum = siz[u];
        while (p < v[k].size() && dfn[v[k][p]] <= lst[u]) {
            sum -= siz[v[k][p]];
            p++;
        }
        ans[c[k]] += score(sum);
    }
    if (t[k].size())rep(i, t[k].size())if (t[k][i] != from)
        dfs2(t[k][i], k);
}
void solve() {
    scanf("%d", &n);
    rep(i, n)scanf("%d", &c[i]), c[i]--;
    t.resize(n), v.resize(n), emp.resize(n);
    rep(i, n - 1) {
        scanf("%d%d", &x, &y);
        x--, y--;
        t[x].pb(y);
        t[y].pb(x);
    }
    dfs1(0, -1);
    dfs2(0, -1);
    rep(i, n) {
        int sum = n;
        if (emp[i].size()) {
            rep(j, emp[i].size()) sum -= siz[emp[i][j]];
        }
        ans[i] += score(sum);
    }
    rep(i, n)printf("%lld\n", score(n) - ans[i]);
}
int main() {
    T = 1;

    for (case_ = 1;case_ <= T;case_++)solve();
    return 0;
}
```

## 特别鸣谢

[Graph Editor](https://csacademy.com/app/graph_editor/) 提供图片支持。

---

## 作者：Tx_Lcy (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc163_f)

简单 $\rm 2400$，我好像又想复杂了，题解区也没有我这种做法。

## 思路

首先对于每种颜色开个数组记一下有哪些点，然后我们考虑**直接计数**方案数。

设当前枚举到颜色 $x$，当前颜色一共有 $y$ 个。

+ 第一种情况：路径至少有一个端点颜色为 	$x$：

	此时路径的数量为 $y \times n-\dfrac{y \times (y-1)}{2}$，这一步是简单的。
    
+ 第二种情况：路径两个端点颜色都不为 $x$：

	我们把颜色 $x$ 的点按照深度从大到小排序。为了防止算重，我们强制钦定不能计数当前点和已枚举的点的子树内点连边，所以我们当前子树的大小要减去它子树内颜色为 $x$ 的点的子树大小，这个可以用树状数组简单维护。
    
    首先计算一个点在子树内，一个点在子树外的方案数，这也是简单的，答案是 $(siz-1) \times (n-siz-p-la)$，解释一下这个柿子的含义：$siz$ 表示当前子树的点数，$siz-1$ 是因为当前点颜色为 $x$，不能连边。$p$ 表示除当前子树内的点所有已经枚举的标记点的子树和，因为我们强制钦定当前点不能计数之前出现过的点，所以要减去。$la$ 是没有枚举到的颜色为 $x$ 的点的个数。
    
    然后我们考虑枚举路径恰好经过当前枚举点 $u$ 的所有节点，枚举点 $u$ 的儿子，设枚举到 $v$，则我们可以直接根据所有 $siz_v$ 算出方案数，由于每条边只会被遍历一次，所以复杂度是对的。
    
    最终时间复杂度：$\mathcal O(n \log n)$。
    
### 代码

```cpp
//A tree without skin will surely die.
//A man without face is invincible.
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define lowbit(x) (x&-x)
int const N=2e5+10;
int n,c[N];
vector<int>a[N],e[N];
struct Tree_Array{
    int c[N];
    void update(int x,int v){while (x<N) c[x]+=v,x+=lowbit(x);}
    int query(int x){int res=0;while (x) res+=c[x],x-=lowbit(x);return res;}
}T,P;
int siz[N],dfn[N],dep[N],Fa[N];
void Dfs(int x,int fa){
    siz[x]=1,dfn[x]=++dfn[0],dep[x]=dep[fa]+1,Fa[x]=fa;
    for (auto v:a[x]) if (v^fa) Dfs(v,x),siz[x]+=siz[v];
}
void sol2(int x){
    int res=0;
    sort(e[x].begin(),e[x].end(),[](int x,int y){
        return dep[x]>dep[y];
    });
    vector< pair<int,int> >g;
    int la=e[x].size();
    for (auto j:e[x]){
        int y=T.query(dfn[j]+siz[j]-1)-T.query(dfn[j]);
        int q=T.query(n)-y;--la;
        y=siz[j]-y-1,res+=y*(n-siz[j]-q-la);//计数子树连向子树外
        int tot=0;
        for (auto v:a[j]){
            if (v==Fa[j]) continue;
            int g=T.query(dfn[v]+siz[v]-1)-T.query(dfn[v]-1);
            g=siz[v]-g,res+=g*tot,tot+=g;//路径恰好经过点 j
        }
        g.push_back({dfn[j],y+1});T.update(dfn[j],y+1);
    }
    res+=e[x].size()*n-e[x].size()*(e[x].size()-1)/2;//计数第一种情况
    for (auto j:g) T.update(j.first,-j.second);
    cout<<res<<'\n';
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for (int i=1;i<=n;++i) cin>>c[i],e[c[i]].push_back(i);
    for (int i=1;i<n;++i){
        int u,v;cin>>u>>v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    Dfs(1,0);
    for (int i=1;i<=n;++i) sol2(i);
    return 0;
}
```

---

## 作者：封禁用户 (赞：3)

## 前言：
竟然有如此水的紫题。

## 题目大意：

根据题目我们可以知道，给定一棵 $n$ 个点的树，给第 $i$ 个点染上颜色 $c_i$，其中 $c_i$ 为 $[1,n]$ 的一个整数。

现在，对于每一种颜色 $k$，我们要求出有多少条简单路径满足路径上至少有一个点的颜色为 $k$。

## 思路：
我们可以假设 $sum_i$ 表示我们在树上已经枚举到的过程中，所有颜色为 $i$ 的子树的总大小（如果有包含，则记录最大的）。

对于某一节点的每一个子树，找到每一个颜色相同的，之间相隔的点两两可以形成不包含该颜色的路径，用总方案数减去这些方案数即可。

当还有一种情况，假设现在我们在做红色（下面称为颜色 $x$）节点，则答案为 $size_y-k$。

我们可以在做 $y$ 之前记一个 $sum_x'$，然后把下面的红色节点后在记一个 $sum_x$，那么就为 $k = sum_x-sum_x'$。

最后我们要干掉与根相连的边，答案也就是 $n - sum_i$。

## AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
long long n,c[N],head[N],Next[N<<1],ver[N<<1],tot=0,sum[N],cnt[N];
ll ans[N];
void insert(long long x,long long y)
{
	ver[++tot]=y,Next[tot]=head[x];
	head[x]=tot;
}
void dfs(long long x,long long fa)
{
	long long t=sum[c[x]];
	cnt[x]=1;
	for(long long i=head[x];i;i=Next[i])
	{
		long long y=ver[i],lst=sum[c[x]];
		if(y!=fa)
		{
			dfs(y,x);
			ll p=cnt[y]-sum[c[x]]+lst;
			ans[c[x]]-=p*(p+1)/2;
			cnt[x]+=cnt[y]; 
		}
	}
	sum[c[x]]=t+cnt[x];
}

int main()
{
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n;
	for(long long i=1;i<=n;++i)
	{
		ans[i]=1ll*n*(n+1)/2;
	}
	for(long long i=1;i<=n;++i)
	{
		cin >> c[i];
	}
	for(long long i=1;i<n;++i)
	{
		long long x,y;
		cin >> x >> y;
		insert(x,y);
		insert(y,x);
	}
	dfs(1,0);
	for(long long i=1;i<=n;++i)
	{
		cout << ans[i]-1ll*(n-sum[i])*(n-sum[i]+1)/2 << endl;
	}
	return 0;
}
``````

---

## 作者：wcyQwQ (赞：2)

很像 CF1681F。我们考虑对于一个颜色 $k$ 怎么计算答案，我们把带有 $k$ 的边全部断掉，然后剩下每个连通块的点数为 $sz_i$，我们用容斥就可以得到最终的答案为 $\frac{n(n - 1)}{2} - \sum\frac{sz_i(sz_i - 1)}{2}$，再算上形如 $(u, u)$ 的路径条数即可，对于这种断边的问题，我们可以用线段树分治解决。时间复杂度 $O(n\log^2n)$。[Code](https://atcoder.jp/contests/abc163/submissions/42791125)

---

## 作者：clamee (赞：2)

题目大意：

给定一棵树,每个节点有颜色。询问经过每一种颜色的简单路径有多少条。节点数量 $1 \le n \le 2\cdot 10^5$。

对于每个点，直接求出有多少对点符合条件且不经过它既可，这可以使用树形 dp 简单的解决，然后容斥掉即可。

```
#include<bits/stdc++.h>
using namespace std;
#define int long long 
struct ss{
	int node,nxt;
}e[600005];
inline int read()
{
	int re=0,k=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')k=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){re=(re<<1)+(re<<3)+ch-48;ch=getchar();}
	return re*k;
}
int u,v,n,col[200005],f[200005],del[200005],s[200005],sz[200005],head[200005],tot,g[200005];
void add(int u,int v)
{
	e[++tot].nxt=head[u];
	e[tot].node=v;
	head[u]=tot;
}
void getsz(int x,int fa)
{
	for(int i=head[x];i;i=e[i].nxt)
	{
		int t=e[i].node;
		if(t==fa)continue;
		getsz(t,x);
		sz[x]+=sz[t];
	}
}
void dfs(int x,int fa)
{
	int lst=s[col[fa]];
	s[col[fa]]=x;
	if(s[col[x]])del[s[col[x]]]+=sz[x];
	else g[col[x]]+=sz[x];
	for(int i=head[x];i;i=e[i].nxt)
	{
		int t=e[i].node;
		if(t==fa)continue;
		dfs(t,x);
	}
	int now=sz[x]-del[x];
	//cerr<<col[fa]<<" "<<now<<" "<<sz[x]<<endl;
	f[col[fa]]+=now*(now+1)>>1;
	s[col[fa]]=lst;
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		col[i]=read();sz[i]=1;
	}
	for(int i=1;i<=n-1;i++)
	{
		u=read();
		v=read();
		add(u,v);
		add(v,u);
	}
	getsz(1,0);
	dfs(1,0);
	for(int i=1;i<=n;i++)
		g[i]=(n-g[i])*(n-g[i]+1)>>1;
	int ans=n*(n+1)>>1;
	for(int i=1;i<=n;i++)
	{
		printf("%lld\n",ans-f[i]-g[i]);
	}
}
```



---

## 作者：tjtdrxxz (赞：1)

在做这道题之前，或做了这道题以后，推荐去看 [P5631](https://www.luogu.com.cn/problem/P5631)。

好，那么我们回归这道题。对于包含节点颜色为 $ k $ 的简单路径的数量是很难直接求出的。

所以我们可以从反方向考虑，我们可以求出不含节点颜色为 $ k $ 的简单路径的数量（后文会用 $ q $ 表示）。然后答案就是总的减去部分的，即 $ n \times (n - 1) / 2 - q + cnt_k $，其中 $ cnt_k $ 表示颜色为 $ k $ 的结点的数量（毕竟可以是从自己到自己的简单路径）。

code：
```cpp
# include <bits/stdc++.h>
# define int long long
using namespace std;
using size_s = unsigned int;
int fa[200011], siz[200011];
int qx[200011], qy[200011];
vector <int> q;
int find (int x)
{
	return fa[x] == x ? x : find (fa[x]);
}
int ans;
int merge (int x, int y)
{
	x = find (x), y = find (y);
	if (x == y) return 0;
	if (siz[x] < siz[y])
	{
		swap (x, y);
	}
	fa[y] = x;
	ans -= siz[x] * (siz[x] - 1) / 2;
	ans -= siz[y] * (siz[y] - 1) / 2;
	siz[x] += siz[y];
	ans += siz[x] * (siz[x] - 1) / 2;
	q.push_back (y);
	return 1;
}
vector <int> col[200011];
int n, a[200011];
int last[200011];
void cut ()
{
	int x = q.back ();
	int y = fa[x];
	q.pop_back ();
	ans -= siz[y] * (siz[y] - 1) / 2;
//	ans += siz[fa[x]] * (siz[fa[x]] - 1) / 2;
	siz[y] -= siz[x];
	fa[x] = x;
	ans += siz[x] * (siz[x] - 1) / 2;
	ans += siz[y] * (siz[y] - 1) / 2;
//	ans -= siz[fa[x]] * (siz[fa[x]] - 1) / 2;
//	ans -= siz[x] * (siz[x] - 1) / 2;
}
int num[200011];
struct SegTree
{
	size_s l, r, mid;
	SegTree *ls, *rs;
	vector <int> stk;
	SegTree (size_s s, size_s t) :
		l { s }, r { t },
		mid { (l + r) >> 1 },
		ls {nullptr},
		rs {nullptr}
	{
		if (s == r)
		{
			return;
		}
		ls = new SegTree (l, mid + 0);
		rs = new SegTree (mid + 1, r);
	}
	void modify (size_s s, size_s t, int x)
	{
		if (s > t) return;
		if (l >= s and r <= t)
		{
			stk.push_back (x);
			return;
		}
		if (mid >= s) ls -> modify (s, t, x);
		if (mid <  t) rs -> modify (s, t, x);
	}
	void solve ()
	{
		int cnt = 0;
		for (auto it : stk)
		{
			int u = qx[it];
			int v = qy[it];
			cnt += merge (u, v);
		}
		if (l == r)
		{
//			cout << ans << endl;
			cout << n * (n - 1) / 2 - ans + num[l] << endl;
		}
		else
		{
			ls -> solve ();
			rs -> solve ();
		}
		while (cnt --)
		{
			cut ();
		}
	}
};
signed main ()
{
	ios :: sync_with_stdio (NULL);
	cin.tie (0x0), cout.tie (0x0);
	cin >> n;
//	ans = n * (n - 1) / 2;
	for (int i = 1; i <= n; i ++) fa[i] = i, siz[i] = 1;
	for (int i = 1; i <= n; i ++)
	{
		cin >> a[i];
		last[i] = 1;
		num[a[i]] ++;
	}
	SegTree tr (1, n);
	for (int i = 1; i < n; i ++)
	{
		cin >> qx[i] >> qy[i];
		if (a[qx[i]] != a[qy[i]])
		{
			int l = min (a[qx[i]], a[qy[i]]);
			int r = max (a[qx[i]], a[qy[i]]);
			tr.modify (1, l - 1, i);
			tr.modify (r + 1, n, i);
			tr.modify (l + 1, r - 1, i);
//			col[a[qx[i]]].push_back (i);
//			col[a[qy[i]]].push_back (i);
		}
		else
		{
			int x = a[qx[i]];
			tr.modify (1, x - 1, i);
			tr.modify (x + 1, n, i);
//			col[a[qy[i]]].push_back (i);
		}
	}
//	for (int i = 1; i <= n; i ++)
//	{
//		for (auto it : col[i])
//		{
//			cout << "num : " << last[it] << ' ' << i - 1 << ' ' << it << endl;
//			tr.modify (last[it], i - 1, it);
//			last[it] = i + 1;
//		}
//	}
//	for (int i = 1; i < n; i ++)
//	{
//		cout << "num : " << last[i] << ' ' << n << ' ' << i << endl;
//		tr.modify (last[i], n, i);
//	}
	tr.solve ();
	return 0;
}

```

---

## 作者：Fesdrer (赞：1)

对于每一个颜色 $c$，我们求出路径中不包含颜色 $c$ 的路径数量即可，因为答案即为将总方案数减去这一数量。

考虑如何求出路径中不包含颜色 $c$ 的路径数量。为了方便，我们新建一个颜色为 $c$ 的节点作为新的根节点并将其连接向 $1$ 号点。令 $g(x)$ 表示一个大小为 $x$ 的连通块所包含的路径个数，通过枚举端点得出 $g(x)=\frac 12x(x-1)+x$。那么不包含颜色 $c$ 的路径数量就是所有极大的不含颜色 $c$ 的连通块 $S$ 的 $g(|S|)$ 之和，其中 $|S|$ 表示 $S$ 的大小。因此只需要枚举所有极大的不含颜色 $c$ 的连通块即可。

容易发现，对于每一个颜色为 $c$ 的点的儿子 $y$，如果 $y$ 的颜色不为 $c$，那么 $y$ 就包含于一个极大的不含颜色 $c$ 的连通块。具体的，这个连通块的大小就是 $\operatorname{siz}(y)$ 减去 $y$ 的子树中所有颜色为 $c$ 的节点的子树大小，并且这些节点还需满足其到 $y$ 的路径上没有其他颜色为 $c$ 的点，否则就会算重。

因此我们对每个颜色 $c$ 建出虚树，然后遍历虚树计算即可。因为虚树的总大小为 $\mathcal O(n)$，因此在虚树的每个节点枚举其儿子的复杂度也是 $\mathcal O(n)$。所以复杂度为 $\mathcal O(n\log n)$。

```c++
#include<bits/stdc++.h>
using namespace std;
using i64=long long;
const int N=2e5+5;
int n,c[N],fa[30][N],dep[N],siz[N],dfn[N],tod;
vector<int> e[N],color[N],ne[N];
inline void add(int x,int y){
	e[x].push_back(y),e[y].push_back(x);
}
void dfs(int x,int fas){
	fa[0][x]=fas,dep[x]=dep[fas]+1,siz[x]=1,dfn[x]=++tod;
	for(int y:e[x])	if(y!=fas)	dfs(y,x),siz[x]+=siz[y];
}
void init(){
	for(int bit=1;(1<<bit)<=n;bit++)	for(int i=1;i<=n+1;i++)
		fa[bit][i]=fa[bit-1][fa[bit-1][i]];
}
int lca(int x,int y){
	if(dep[x]>dep[y])	swap(x,y);
	for(int bit=20;bit>=0;bit--)	if(dep[x]+(1<<bit)<=dep[y])	y=fa[bit][y];
	if(x==y)	return x;
	for(int bit=20;bit>=0;bit--)	if(fa[bit][x]!=fa[bit][y])	x=fa[bit][x],y=fa[bit][y];
	return fa[0][x];
}
void build(vector<int> tmp){
	sort(tmp.begin(),tmp.end(),[&](int x,int y){return dfn[x]<dfn[y];});
	for(int i=int(tmp.size())-1;i>=1;i--)	tmp.push_back(lca(tmp[i],tmp[i-1]));
	sort(tmp.begin(),tmp.end(),[&](int x,int y){return dfn[x]<dfn[y];});
	tmp.erase(unique(tmp.begin(),tmp.end()),tmp.end());
	auto add_edge=[&](int x,int y){ne[x].push_back(y),ne[y].push_back(x);};
	for(int i=1;i<int(tmp.size());i++)	add_edge(lca(tmp[i-1],tmp[i]),tmp[i]);
}
int dfs2(int x,int fas,int color,i64 &ans){
	if(x!=n+1&&c[x]!=color){
		int ret=0;
		for(int y:ne[x])	if(y!=fas)	ret+=dfs2(y,x,color,ans);
		return ret;
	}
	sort(e[x].begin(),e[x].end(),[&](int x,int y){return dfn[x]<dfn[y];});
	sort(ne[x].begin(),ne[x].end(),[&](int x,int y){return dfn[x]<dfn[y];});
	for(int i=0,j=-1;i<int(e[x].size());i++)	if(dfn[e[x][i]]>=dfn[x]){
		int y=e[x][i],nowsiz=siz[y];
		if(j<int(ne[x].size())-1){
			if(ne[x][j+1]==fas)	j++;
			if(dfn[ne[x][j+1]]>=dfn[y]&&dfn[ne[x][j+1]]<dfn[y]+siz[y])
				nowsiz-=dfs2(ne[x][++j],x,color,ans);
		}
		ans+=1ll*nowsiz*(nowsiz-1ll)/2+1ll*nowsiz;
	}
	return siz[x];
}
void erase(int x,int fas){
	for(int y:ne[x])	if(y!=fas)	erase(y,x);
	ne[x].clear();
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>c[i],color[c[i]].push_back(i);
	for(int i=1,x,y;i<n;i++)	cin>>x>>y,add(x,y);
	add(n+1,1),dfs(n+1,0),init();
	for(int i=1;i<=n;i++)	color[i].push_back(n+1);
	for(int i=1;i<=n;i++){
		build(color[i]);
		i64 ans=0;
		dfs2(n+1,0,i,ans);
		erase(n+1,0);
		cout<<1ll*n*(n-1)/2+n-ans<<endl;
	}
	return 0;
}
```

---

## 作者：chenxia25 (赞：1)

~~爬爬爬~~

这其实算是ABC的F们中比较难的一个

>### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/AT4820) & [AtCoder题目页面传送门](https://atcoder.jp/contests/abc163/tasks/abc163_f)

>有一棵树$T=(V,E),|V|=n,|E|=n-1$，节点$i$的颜色为$a_i\in[1,n]$。求$\forall i\in[1,n]$，经过至少$1$个颜色为$i$的节点的路径个数。

>$n\in\left[1,2\times10^5\right]$。

先考虑对于某个$i$，该如何求答案。注意到，若正面求答案，那么需要容斥一大堆，或者点分治（我还不会），比较麻烦。考虑反面求答案，求不经过任何颜色为$i$的节点的路径个数，最后用总路径数$\dfrac{n(n+1)}2$减去它即可。考虑“不经过任何颜色为$i$的节点的路径个数”怎么算，显然，若将所有颜色为$i$的节点删除，会分离成若干CC，设它们的大小分别为$s_1,s_2,\cdots,s_m$，那么答案就是$\sum\limits_{j=1}^m\dfrac{s_j(s_j+1)}2$，因为一条路径不经过任何颜色为$i$的节点当且仅当它的两端点属于同一个CC。

如果只对于一个$i$求答案，那么显然可以直接删除所有该删的点，然后随便DFS一下就$\mathrm O(n)$出答案了。但现在需要在较短时间内求出对于所有$i$的答案，就有那么一丝丝难度了。不难发现，$\forall i$，任意一个CC的深度最小的点要么没有父亲（等于根，令$1$为根），要么父亲颜色为$i$（反证法，如果不成立，那么显然CC可以再往上扩展）。于是我们可以用这个唯一的（唯一性可以反证，如果不唯一，也就是$2$个同辈人没有长辈连接，一定不连通）深度最小的点作为整个CC的代表。

又不难发现，任意一个非$1$节点，都只能作为一个$i$剖出来的CC的代表，因为它们都有一个固定的父亲，也就有一个固定的父亲的颜色，而节点$1$却可以作为任意一个$i$剖出来的CC的代表，需要特殊开数组处理。所以总CC数为$\mathrm O(n)$。考虑一遍DFS求出所有CC的大小。考虑如何算一个CC的大小。先假设整个以$x$为根的子树全属于此CC，然后看有多少是被删了的或属于其他CC的，减去即可。显然，在子树内的所有CC代表要么一个为祖先一个为晚辈，此时以它们为根的子树一个包含另一个，要么无关，此时以它们为根的子树不相交，CC代表们的父亲（颜色为$i$）亦然。又显然，所有子树内的以颜色为$i$的节点为根的子树内的节点都不属于此CC，于是我们只需要将此CC的大小减去所有不为其他颜色为$i$的节点的晚辈的颜色为$i$的节点的子树大小即可。考虑从下往上贡献，即DFS过程中时刻维护递归栈，每到一个节点就将最深的一个颜色相同的节点（这个可以时刻维护每种颜色的递归栈$\mathrm O(1)$做到）在栈中的下一个节点的CC大小减去它的子树大小（正确性显然）。对于根代表多CC的情况，特判一下即可。

时间复杂度$\mathrm O(n)$。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ppb pop_back
typedef long long ll;
const int N=200000;
int n;//节点个数 
int a[N+1];//颜色 
vector<int> nei[N+1];//邻接表 
int sz[N+1]/*子树大小*/,cc_sz[N+1]/*CC大小（非根）*/,cc_sz1[N+1]/*CC大小（根，下标为颜色）*/;
int fa[N+1];//父亲 
vector<int> stk/*总递归栈*/,stk_c[N+1]/*颜色们的递归栈*/;
void dfs(int x=1){//求CC们的大小 
//	cout<<x<<"\n";
	sz[x]=1;
	stk_c[a[x]].pb(stk.size());
	stk.pb(x);//压栈 
	for(int i=0;i<nei[x].size();i++){
		int y=nei[x][i];
		if(y==fa[x])continue;
		fa[y]=x;
		dfs(y);
		sz[x]+=sz[y];
	}
	stk.ppb();
	stk_c[a[x]].ppb();//准备回溯，弹出 
	if(stk_c[a[x]].size()>1)cc_sz[stk[stk_c[a[x]].back()+1]]-=sz[x];//贡献（非根） 
	else/*特判*/ cc_sz1[a[x]]-=sz[x];//贡献（根） 
}
ll ans[N+1];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		nei[x].pb(y);nei[y].pb(x);
	}
	stk.pb(0);
	for(int i=1;i<=n;i++)stk_c[i].pb(0);
	dfs();
	for(int i=1;i<=n;i++)cc_sz[i]+=sz[i],cc_sz1[i]+=n;
//	for(int i=1;i<=n;i++)cout<<cc_sz[i]<<" ";puts("");
//	for(int i=1;i<=n;i++)cout<<cc_sz1[i]<<" ";puts("");
	for(int i=1;i<=n;i++)ans[i]=1ll*n*(n+1)/2;
	for(int i=2;i<=n;i++)ans[a[fa[i]]]-=1ll*cc_sz[i]*(cc_sz[i]+1)/2;
	for(int i=1;i<=n;i++)ans[i]-=1ll*cc_sz1[i]*(cc_sz1[i]+1)/2;//减去反面答案 
	for(int i=1;i<=n;i++)cout<<ans[i]<<"\n";
	return 0;
}
```

---

## 作者：hinin (赞：0)

树上统计的一题

这个问题要求我们在一棵树上计算每种颜色的路径数量，路径上至少有一个点的颜色为特定颜色。我们可以使用深度优先搜索（DFS）来解决这个问题。

#### 解题思路

1.  **树的性质**：
    
    *   树是一个无环连通图，任意两个节点之间有且仅有一条简单路径。
    *   对于每种颜色 $k$，我们需要计算所有经过至少一个颜色为 $k$ 的节点的路径数量。
2.  **路径数量的计算**：
    
    *   对于每个节点 $u$，我们可以通过 DFS 遍历其所有子节点 $v$ 来计算路径数量。
    *   假设 $sz_v$ 是子树 $v$ 的大小（包括 $v$ 本身），那么从 $u$ 到 $v$ 的路径数量是 $sz_v$。
    *   如果我们在处理节点 $u$ 时，已经知道了其子树的大小，我们可以通过维护一个计数器 $sum$ 来记录当前颜色的节点数量。
3.  **DFS 过程**：
    
    *   在 DFS 中，我们会维护一个 $sum$ 数组，记录每种颜色在当前路径中的出现次数。
    *   当我们访问一个节点时，我们会更新其颜色的计数，并在返回时更新路径数量。
4.  **最终结果**：
    
    *   在 DFS 完成后，我们可以计算每种颜色的路径数量，并输出结果。
      
```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define pii pair<int, int>

using namespace std;

const int N = 2e5 + 5;

int n, c[N], cnt[N], sz[N], sum[N];
vector <int> g[N];
ll ans[N];

ll f(int x) { return 1ll * x * (x + 1) / 2; }

void dfs(int u, int fa) {
    sz[u] = 1;
    int t = sum[c[u]];
    for (auto v : g[u]) if (v != fa) {
        sum[c[u]] = 0;
        dfs(v, u);
        sz[u] += sz[v];
        ans[c[u]] -= f(sz[v] - sum[c[u]]);
    }
    sum[c[u]] = t + sz[u];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(20);
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        ++cnt[c[i]];
    }
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);

    for(int i = 1; i <= n; i++) { ans[i] += f(n) - f(n - sum[i]); }
    for (int i = 1; i <= n; i++) { cout << ans[i] << '\n'; }
    return 0;
}
```

---

## 作者：Union_Find (赞：0)

# 题目描述

有一颗有 $n$ 个节点的树，第 $i$ 的颜色为 $c_i$，求对于每一种颜色 $k$，有多少条路径经过颜色 $k$。

# 思路

正着想比较难，我们反着想。我们去计算有多少条路径不经过颜色 $k$。我们设 $cnt_i$ 表示第 $i$ 个连通块的大小，那么不经过颜色 $k$ 的路径数就是 $\frac{cnt_i(cnt_i - 1)}{2}$。但是这样做我们要枚举每一个颜色，时间复杂度是 $O(n^2)$，T 飞了。

所以我们要优化一下，让它在一次 dfs 中求出所有的 $cnt_i$。我们定义一个 $sum_i$，表示当前情况下颜色为 $i$ 的点的子树大小的和。确实很抽象，我们来看一张图。

![](https://cdn.luogu.com.cn/upload/image_hosting/qnbi3fsd.png)

假设在处理红色（颜色 $x$），那么 $v$（当前点的儿子） 所在连通块大小就是 $size_v - k$，$k$ 就是 $v$ 的子树中 所有颜色为 $x$ 的点的 $\sum size_i$。但是怎么求 $k$ 呢？我们可以存一下原本的 $sum_u$，然后向下 dfs 之后，算增加值 $add$，就是上式中的 $k$。

综上，我们就成功用 $O(n)$ 通过了这题。

注意：要额外处理根节点所在的连通块，就是 $n - sum_i$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 200005
ll n, ans[N], col[N], sz[N], cnt[N], u, v;
ll head[N], nxt[N << 2], to[N << 2], en;
il void add_edge(ll u, ll v){
	nxt[++en] = head[u];
	head[u] = en;
	to[en] = v;
}
il ll ask(ll x){return x * (x + 1) / 2;}
void dfs(ll u, ll fa){
	sz[u] = 1;
	ll kkk = cnt[col[u]];
	for (int i = head[u]; i; i = nxt[i]){
		ll v = to[i];
		if (v == fa) continue;
		ll cnt1 = cnt[col[u]];
		dfs(v, u);
		sz[u] += sz[v];
		ans[col[u]] -= ask(sz[v] - cnt[col[u]] + cnt1);
	}
	cnt[col[u]] = kkk + sz[u];
}
int main(){
	scanf ("%lld", &n);
	for (int i = 1; i <= n; i++)
		scanf ("%lld", &col[i]), ans[i] = ask(n);
	for (int i = 1; i < n; i++){
		scanf ("%lld %lld", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; i++)
		printf ("%lld\n", ans[i] - ask(n - cnt[i]));
	return 0;
}
```

---

