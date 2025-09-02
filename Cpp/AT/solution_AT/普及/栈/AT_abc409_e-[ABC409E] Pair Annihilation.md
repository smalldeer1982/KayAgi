# [ABC409E] Pair Annihilation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc409/tasks/abc409_e

给定一棵包含 $N$ 个顶点的树。顶点编号为 $1,2,\dots,N$，边编号为 $1,2,\dots,N-1$。边 $j$ 双向连接顶点 $u_j$ 和 $v_j$，其权重为 $w_j$。此外，顶点 $i$ 上有一个整数 $x_i$：若 $x_i > 0$，表示该顶点有 $x_i$ 个正电子；若 $x_i < 0$，表示有 $-x_i$ 个电子；若 $x_i = 0$，则该顶点没有粒子。题目保证 $\sum_{i=1}^N x_i = 0$。

每次可以沿边 $j$ 移动 1 个正电子或电子，消耗能量 $w_j$。当正电子和电子位于同一顶点时，它们会相互抵消（数量相等时完全消失）。

求使所有正电子和电子完全消失所需的最小总能量。

## 说明/提示

### 约束条件

- $2 \leq N \leq 10^5$
- $|x_i| \leq 10^4$
- $\sum_{i=1}^N x_i = 0$
- $1 \leq u_j < v_j \leq N$
- $0 \leq w_j \leq 10^4$
- 给定的图是一棵树
- 输入均为整数

### 样例解释 1

初始状态 $x=(-3,+2,+2,-1)$。通过以下操作可以用最小能量 $9$ 使所有粒子消失：
1. 将顶点 $1$ 的 1 个电子移动到顶点 $2$，消耗能量 $2$，$x=(-2,+1,+2,-1)$；
2. 将顶点 $2$ 的 1 个正电子移动到顶点 $1$，消耗能量 $2$，$x=(-1,0,+2,-1)$；
3. 将顶点 $4$ 的 1 个电子移动到顶点 $1$，消耗能量 $3$，$x=(-2,0,+2,0)$；
4. 将顶点 $1$ 的 1 个电子移动到顶点 $3$，消耗能量 $1$，$x=(-1,0,+1,0)$；
5. 将顶点 $1$ 的 1 个电子移动到顶点 $3$，消耗能量 $1$，$x=(0,0,0,0)$。

无法用 $8$ 或更少能量完成目标，因此答案为 $9$。

### 样例解释 2

初始状态已满足条件时，输出 $0$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
-3 2 2 -1
1 2 2
1 3 1
1 4 3```

### 输出

```
9```

## 样例 #2

### 输入

```
2
0 0
1 2 1```

### 输出

```
0```

## 样例 #3

### 输入

```
5
-2 -8 10 -2 2
3 5 1
1 3 5
2 5 0
3 4 6```

### 输出

```
28```

# 题解

## 作者：dongzirui0817 (赞：1)

首先，将能量全部合并在一个点上，不会使答案变劣。

因为假设一种情况可以合并在多个点，且使 $x_i$ 全为 $0$，那么将这些点再合并至一个点的代价为 $0$，不会变劣。

那么得出了 $O(n^2)$ 做法：枚举合并点，再将其他能量全部合并的代价，最后取最小值即可。合并只需树形 dp。

然而手玩一下数据，你会发现，**无论选哪个点合并，代价都一样**。

因为在最后合并时，一定有两个点之间有边，且其他点对应的 $x_i$ 都为 $0$。此时设这两个点分别为 $i$ 和 $j$ 号点，边的权值为 $w$。  
那么合并到 $j$ 的代价为 $w \times |x_j|$，合并到 $i$ 的代价为 $w \times |x_i|$。而 $x_i + x_j$ 应为 $0$，所以 $|x_i| = |x_j|$，这次的合并代价相同。  
并且在之前的合并顺序相同，代价也相同，所以无论合并到 $i$ 号点还是 $j$ 号点，代价都相同。既而推广到结论。

于是只要选 $1$ 号点合并，算代价即可。

[Submission](https://atcoder.jp/contests/abc409/submissions/66561658)

---

## 作者：fish_love_cat (赞：1)

简单树形 dp。

---

显然每一个节点的子树内所有的电子都可以在该点进行处理。

于是对于每一个点，先把每一个子节点湮灭剩下的提上来，然后在该点继续湮灭，湮灭不干净的再扔给父亲。

这样操作可以做到能湮灭就湮灭，是最优的。

我们上个树形 dp，只需要开两个数组维护电子类型数量和答案就可以了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[100005];
vector<pair<int,int> >ve[100005];
int dp[100005],sum[100005];
void dfs(int x,int fa){
    sum[x]=a[x];
    for(int i=0;i<ve[x].size();i++){
        if(ve[x][i].first==fa)continue;
        dfs(ve[x][i].first,x);
        sum[x]+=sum[ve[x][i].first];
        dp[x]+=dp[ve[x][i].first];
        if(sum[ve[x][i].first])
        dp[x]+=ve[x][i].second*abs(sum[ve[x][i].first]);
    }
}
void solve(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        ve[u].push_back(make_pair(v,w));
        ve[v].push_back(make_pair(u,w));
    }
    dfs(1,0);
    cout<<dp[1];
}
signed main(){
    int t=1;
    // cin>>t;
    while(t--)solve();
    return 0;
}
```

---

## 作者：littlebug (赞：1)

## Solution

注意点叶子结点 $i$ 上的电子若想湮灭，无论是往其父亲转移还是父亲往它转移，总会有 $x_i$ 个电子走边 $(i,fa_i)$ 了。

所以不妨直接往父亲转移，这样显然不会更劣。

转移完成之后，叶子结点 $i$ 上的电子数就变成 $0$ 了，所以以后就不可能有电子走边 $(i,fa_i)$ 了，因为走了显然不会更优。

那么叶子结点就没用了，直接删掉。

然后会发现又得到了一些新的叶子节点，可以继续重复上面的操作，直到只剩一个点。

## Code

可能是我的写法问题，最后剩下的是一条边而不是一个点，不过特判一下就好了。

```cpp
int n,a[N],deg[N];
vector <pii> p[N];
bitset <N> del;

il int topo()
{
    queue <int> q;
    rep(i,1,n) deg[i]==1 && (q.emplace(i),del[i]=1);
    
    int u,ans=0;
    while(!q.empty())
    {
        u=q.front(),q.pop();
        for(auto [v,w]:p[u]) if(!del[v])
        {
            ans+=abs(a[u])*w,a[v]+=a[u],a[u]=0;
            --deg[v];
            deg[v]==1 && (q.emplace(v),del[v]=1);
        }
    }
    
    rep(u,1,n) if(a[u]) for(auto [v,w]:p[u]) if(a[v]) return ans+abs(a[u])*w;
    return ans;
}

il void solve()
{
    read(n),_::r(a,n); {int u,v,w; rep(i,1,n-1) read(u,v,w),p[u].pb(v,w),p[v].pb(u,w),++deg[u],++deg[v];}
    
    write(topo());
}
```

---

华风夏韵，洛水天依！

---

## 作者：__KevinMZ__ (赞：1)

# [AT\_abc409\_e 题解](https://www.luogu.com.cn/problemnew/show/AT_abc409_e)

## 感受

这次 e 好水。比之前的水多了。第一次过 e 祭而有了这篇 tj。赛时 20min 场切。

## 思路

发现度为 1 的节点只能向它的父亲（儿子）“传输” 电子（离子）。\
每次对度为 1 的节点操作，然后删了它。

### 实现思路

存 `priority_queue<pair<int/*节点度数*/,int/*节点编号*/>,vector<pair<int,int>>,greater<pair<int,int>>>`。但是有个问题：`priority_queue` 不支持在容器内部更改（删除再添加）元素（更改节点度数），改用 `set<pair<int/*节点度数*/,int/*节点编号*/>>`。

### 然后就是代码了

```cpp
#include<bits/stdc++.h>
#define int __int128//见我主页缺省源
#define ONLINE_JUDGE
using namespace std;
inline istream&operator>>(istream&is,int&k){
	int f=1;
	k=0;
	char ch=getchar();
	while(!isdigit(ch))(ch=='-'?f*=-1:f*=1),ch=getchar();
	while(isdigit(ch))k=(k<<3)+(k<<1),k+=ch-'0',ch=getchar();
	k*=f;
	return is;
}
inline ostream&operator<<(ostream&os,int k){
	if(k<0)putchar('-'),k*=-1;
	if(k>=10)os<<(k/10);
	putchar(k%10+'0');
	return os;
}
inline int qpow(int x,int y,const int mod=-1){int ans=1;while(y){if(y&1)ans*=x;x*=x;if(mod!=-1)ans%=mod,x%=mod;y>>=1;}return ans;}
const int maxn=1e5+5;
int n,x[maxn],du[maxn]/*存度*/,ans;
set<int>G[maxn];//存树
map<pair<int,int>,int>mp;//存边
set<pair<int/*节点度数*/,int/*节点编号*/>>pq;
signed main(){
#ifndef ONLINE_JUDGE
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif
	cin>>n;
	for(int i=1;i<=n;i++)cin>>x[i];
	for(int i=1,u,v,z;i<n;i++)cin>>u>>v>>z,G[u].insert(v),G[v].insert(u),mp[{u,v}]=mp[{v,u}]=z,du[u]++,du[v]++;
	for(int i=1;i<=n;i++)pq.insert({du[i],i});
	while(pq.size()>1){//模拟即可。pq.size()==1时里面的元素度为0
		int k=pq.begin()->second;
		pq.erase(pq.begin());
		int y=*G[k].begin();
		G[y].erase(k);
		ans+=mp[{k,y}]*abs((long long)x[k]);
		x[y]+=x[k];
		pq.erase({du[y],y});
		du[y]--;
		pq.insert({du[y],y});
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：jojo222 (赞：1)

翻译（仅供参考）：

给定一个有 $N$ 个顶点的树。顶点的编号为  $ 1,2,\dots,N$，边的编号为  $1,2,\dots,N-1$。边 $j$ 双向连接顶点 $u_j$ 和$ v_j$，并具有权重 $w_j$。此外，顶点 $i$ 被赋予整数 $x_i$，如果 $x_i>0$ 则有 $x_i$ 个正电子，如果 $x_i<0$ 则有 $-x_i$ 个电子，如果 $x_i=0$ 则顶点 $i$ 上没有任何东西。这里保证 $\sum_{i=1}^Nx_i=0$。

沿着边 $j$ 移动一个正电子或电子将消耗能量 $w_j$。当正电子和电子位于同一顶点时，它们会以相同的数量相互抵消并消失。

请计算消灭所有正电子和电子所需的最小能量值。

题解：

我们可以假设 $1$ 是根节点，从叶子结点往上移动正电子或电子，在中途就被消灭的正电子和电子就不再移动。

[代码](https://atcoder.jp/contests/abc409/submissions/66565351)。

---

## 作者：xiaoyin2011 (赞：1)

## AT_abc409_e [ABC409E] 成对湮灭 题解

[题目链接](https://www.luogu.com.cn/problem/AT_abc409_e)

### 题目大意

有一棵 $N$ 个节点的树，每条边连接 $u_i$、$v_i$ 权重 $w_i$。现在每个节点上带了 $x_i$ 的电荷。$x_i > 0$ 就是 $x_i$ 个正电子，$x_i < 0$ 就是 $-x_i$ 个电子，否则没有粒子。在一个节点上的电子和正电子会成对湮灭。驱动 $x$ 个粒子经过某条权重 $w$ 的边一次花费 $x \times w$。问湮灭所有粒子的最小花费。

### 思路及实现

电子和正电子花费相同，所以只考虑通过一条边的实质粒子数即可。因为这是个树，所以一条边一定把这个树分为外围和一个子树。子树内部和外围内部的粒子在最优情况均不通过这条边。

通过这条边的是子树和外围内部自我湮灭完成后的粒子数量差。因为成对，所以只需要统计子树内部电荷和的绝对值即可。

使用 DFS 可以一次解决本问题，复杂度 $O(N)$。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N, x[100005], u, v, w;
struct edge
{
	ll v, w;
};
vector<edge> e[100005];
ll sum[100005], ans = 0;
void dfs(ll u, ll fa)
{
	sum[u] = x[u];
	for (int i = 0; i < e[u].size(); i++)
	{
		if (e[u][i].v == fa) continue;
		dfs(e[u][i].v, u);
		sum[u] += sum[e[u][i].v];
		ll mov = abs(sum[e[u][i].v]);
		ans += mov * e[u][i].w;
	}
} 
int main()
{
	scanf("%lld", &N);
	for (int i = 1; i <= N; i++)
		scanf("%lld", &x[i]);
	for (int i = 1; i <= N - 1; i++)
	{
		scanf("%lld%lld%lld", &u, &v, &w);
		e[u].push_back({v, w});
		e[v].push_back({u, w});
	}
	dfs(1, 0);
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：FXLIR (赞：0)

第一次写 E 的题解呢。
### 思路
定义 $s_i$ 为以 $i$ 为根的子树中，完成操作后剩下的粒子数量。若 $s_i > 0$，说明剩下 $s_i$ 个正粒子；若 $s_i < 0$，说明剩下 $-s_i$ 个负粒子；若 $s_i = 0$，说明粒子全部湮灭。

考虑以 $1$ 为根进行 dfs，途中从叶节点开始统计每个 $s_i$。对于一个不为 $0$ 的 $s_i$，需要从它的父结点中拿 $|s_i|$ 个粒子，此时需要 $w \times |s_i|$ 的能量（其中 $w$ 为 $i$ 与其父节点之间的边的边权）。

之所以从父节点中拿粒子，是因为所有的 $w$ 都是非负整数，从除父节点以外的其它节点拿粒子一定不会更优。

最后将所有所需的能量加起来，输出即可。

具体实现见代码。
### 代码
```
#include<cmath>
#include<vector>
#include<iostream>
#define int long long
using namespace std;
const int N=2e5+5,INF=1e9;
struct node{
	int u,w;
};
vector<node> to[N];
int n,a[N],u,v,w,s[N],ans;
void dfs(int x,int fa){
	s[x]=a[x];
	for(auto v:to[x]){
		if(v.u!=fa){
			dfs(v.u,x);
			s[x]+=s[v.u],ans+=v.w*abs(s[v.u]);
		}
	}
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<n;i++){
		cin>>u>>v>>w;
		to[u].push_back({v,w});
		to[v].push_back({u,w});
	}
	dfs(1,0);
	cout<<ans;
	return 0;
}
```

---

## 作者：ljy05 (赞：0)

注意到，如果将某一条边断开，消除剩下两棵树的电子，一定会剩下一些消不完的电子，这些剩下的电子一定需要通过这条边才能消除，这条边上通过的电子一定不会更少了。

如何达到这个最小值？对于每个点，我们将它的子树中的所有电子全都移动到它这里，并将消不完的电子移动到他的父亲。

计算答案时，使用一个 dfs 统计子树内剩余的电子，这样就做完了。

AC 记录：https://atcoder.jp/contests/abc409/submissions/66558551

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int hea[100010],nex[200010],to[200010],wei[200010];
int e[100010],fa[100010];
ll sum[100010];//不开long long见祖宗
int u,v,w;
ll ans;
int n;
int p;
void ae(int x,int y,int z){//加边
	nex[++p]=hea[x];
	hea[x]=p;
	to[p]=y;
	wei[p]=z;
}
void dfs(int x){
	for(int i=hea[x];i!=0;i=nex[i]){
		if(to[i]!=fa[x]){//枚举出边
			fa[to[i]]=x;
			dfs(to[i]);
			ans+=abs(sum[to[i]])*wei[i];
			sum[x]+=sum[to[i]];
		}
	}
	sum[x]+=e[x];
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&e[i]);
	for(int i=1;i<n;i++){
		scanf("%d%d%d",&u,&v,&w);
		ae(u,v,w);
		ae(v,u,w);
	}
	dfs(1);
	printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Ivan422 (赞：0)

你说的对但是这题比较容易吗？个人认为思路比 F 难怎么办没救了。

### 题意

给你一颗树。每个点有权值 $a_i$。其中 $a_i>0$，就有 $a_i$ 个正电子，当 $a_i<0$ 就有 $-a_i$ 个负电子。你可以让电子移动，代价是移动的边权。当正电子与负电子相遇就会湮灭。问**全部**湮灭最小代价是多少。保证 $\sum a_i=0$，即肯定可以全部湮灭。

### 思路

从树叶到根考虑更简单。首先是树叶，肯定走到父节点，代价是边权 $w$。之后我们可以看看树叶的父节点这颗**子树**怎么处理。首先我们设每个点都有电子，没有的话其实不影响。那么把所有电子集中在这个**子树根**上显然更优。

证明：当一组正电子 $a_i$ 个，到子树根距离为 $w_i$。负电子 $-a_i$ 个，到子树根距离为 $w_j$。他们想要抵消，那么就需要**其中一方**一起走 $w_i+w_j$ 的距离，消耗是 $a_i(w_i+w_j)$。因为两端本质电子数相同，所以同时走到根的代价是 $a_iw_i+a_iw_j$，你发现这是一样的。所以综上，全部聚集在子树根销毁最优。

接着我们发现走完统计了代价，这个点的儿子节点其实已经**无用**了。所以可以当做这个点**没有儿子节点了**，那么我们惊奇地发现这个原先的点变成了叶子！然后就可以通过一层一层萎缩成叶子的方法求解了，复杂度 $\mathcal O(n)$。

具体的，我们考虑从根搜索。每次搜完一颗子树，就把子树的 $a_i$ 之和 $suz$（注意不用取绝对值）加上，即这颗子树已经变成叶子了，里面的电子已经集中湮灭，剩下的是没有销毁的电子，是 $suz$，注意这个东西也有正负之分。然后我们统计一下这颗子树的贡献，即这颗子树剩余电子（注意**取绝对值**）个数 $|suz|$ 乘上边权 $w$。我们注意到每次统计贡献 $w|suz|$ 其实是**针对单个电子的**，也就是说每一个节点都会有距离的贡献。说白了，我们要求所有的 $w|suz|$ 之和，这样**才能覆盖所有**电子。

### 代码

好的，我们做完了。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+10;
int n,val[N],suz[N],ans,f[N];
vector<pair<int,int>>e[N];
void dfs1(int p,int fa){
	suz[p]=val[p];
	for(auto v:e[p])if(v.first!=fa){
		dfs1(v.first,p);
		suz[p]+=suz[v.first];
		ans+=abs(suz[v.first])*v.second;
	}
	return;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>val[i];
	for(int i=1;i<n;i++){
		int u,v,w;
		cin>>u>>v>>w;
		e[u].push_back({v,w});
		e[v].push_back({u,w});
	}
	dfs1(1,0);
	cout<<ans;
	return 0;
}
```

---

