# Balanced Tree

## 题目描述

给定一棵包含 $n$ 个节点的树 $^{\text{∗}}$，每个节点 $i$ 有取值范围 $[l_i, r_i]$。你可以为第 $i$ 个节点选择一个初始值 $a_i$ 满足 $l_i \le a_i \le r_i$。当所有节点值相等时，该树称为平衡树，其值定义为任意节点的值。

每次操作中，你可以选择两个节点 $u$ 和 $v$，在以 $u$ 为根的整棵树结构下，将节点 $v$ 的子树 $^{\text{†}}$ 中所有节点的值增加 $1$。注意 $u$ 可以与 $v$ 相同。

你的目标是通过若干次操作使树变为平衡状态。求操作完成后树的最小可能值（无需最小化操作次数）。

$^{\text{∗}}$ 树是一个无环的连通图。

$^{\text{†}}$ 在以 $u$ 为根时，若从根 $u$ 到节点 $w$ 的所有路径都必须经过节点 $v$，则称 $w$ 属于 $v$ 的子树。

## 说明/提示

第一个测试用例中，可以选择 $a = [6, 6, 0, 5]$。

通过以下操作使所有 $a_i$ 相等：
1. 选择 $u=4$，$v=3$，执行该操作 $5$ 次。
2. 选择 $u=1$，$v=3$，执行该操作 $6$ 次。

完整过程如下（括号内数字为 $a$ 的元素）：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2062D/6f573b8859b260e93c1e13ac9a727b4c669ee51e.png)

可以证明这是最优解。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
6
4
0 11
6 6
0 0
5 5
2 1
3 1
4 3
7
1 1
0 5
0 5
2 2
2 2
2 2
2 2
1 2
1 3
2 4
2 5
3 6
3 7
4
1 1
1 1
1 1
0 0
1 4
2 4
3 4
7
0 20
0 20
0 20
0 20
3 3
4 4
5 5
1 2
1 3
1 4
2 5
3 6
4 7
5
1000000000 1000000000
0 0
1000000000 1000000000
0 0
1000000000 1000000000
3 2
2 1
1 4
4 5
6
21 88
57 81
98 99
61 76
15 50
23 67
2 1
3 2
4 3
5 3
6 4```

### 输出

```
11
3
3
5
3000000000
98```

# 题解

## 作者：LiaoYF (赞：17)

## 题意

给定一颗树，第 $i$ 个节点的点权范围是 $\left[l_i,r_i\right]$，你每次可以选择一个根节点 $u$，再选择一个 $u$ 为根时的子树，将其加 $1$。你需要使得所有节点的点权相等，并且最小。输出最小点权。

## 做法

首先任意选择根不是很好处理，所以我们换一种形式表示这个操作。

我们暂时先只能选择 $1$ 为根时的子树，然后观察操作与原来的区别。换成 $u$ 为根后，选择 $1$ 为根时 $u$ 子树中的节点的操作不会变化，只有 $u$ 的祖先上的操作会变化。观察可以发现，如果我们选择 $u$ 和 $u$ 的祖先 $v$，相当于给原来除了 $v$ 的子树全部加 $1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/ht55hufc.png)

给原来除了 $v$ 的子树全部加 $1$，可以当成是子树减 $1$，并且全局加 $1$。全局加 $1$ 不会改变相对点权，对操作没影响，所以计算答案时再考虑。计算答案我们考虑根节点的权值，即计算出来的权值与子树减 $1$ 的次数之和。子树加 $1$ 的操作对答案是没有贡献的，因为永远不会影响到根节点。

所以我们只需要让每个节点的点权尽可能小即可。使用树上 dp，$f_i$ 表示使得 $i$ 子树中的节点权值相同，不考虑全局加的贡献，$i$ 的最小权值，$ans$ 为子树减次数，答案为 $f_1 + ans$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define i128 __int128
#define ALL(x) x.begin(),x.end()
#define popcount(x) __builtin_popcountll(x)
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif
using namespace std;
const int INF=1e18;
const int N=200005;
const int MOD=1e9+7,MOD2=998244353;
int n,L[N],R[N],f[N],siz[N];
vector<int> G[N];
int ans;
void dfs(int u,int fa){
    siz[u]=1;
    int mx=0,cnt=0;
    for(auto v:G[u]){
        if(v==fa)continue;
        cnt++;
        dfs(v,u);
        siz[u]+=siz[v];
        mx=max(mx,f[v]);
    }
    if(R[u]>=mx){
        f[u]=max(L[u],mx);
    }else{
        for(auto v:G[u]){
            if(v==fa)continue;
            ans+=max(0ll,f[v]-R[u]);
        }
        f[u]=R[u];
    }
}
void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>L[i]>>R[i];
        f[i]=siz[i]=0;
        G[i].clear();
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    ans=0;
    dfs(1,0);
    //debug(ans);
    cout<<ans+f[1]<<"\n";
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int testcase,multitest=1;
    if(multitest)cin>>testcase;
    else testcase=1;
    while(testcase--){
        solve();
    }
    return 0;
}
```

---

## 作者：si_kao_zhe (赞：7)

## 题意
给定一颗树，第 $$i$$ 个节点的点权范围是 $$[l_i,r_i ]$$，你每次可以选择一个根节点 $$u$$，再选择一个 $$v$$ 为根时的子树，将其加 $$1$$。你需要使得这个树平衡，即所有节点的点权相等，并且最小。输出最小点权。
## 解法
+ 我们假设 $$1$$ 为根，先假设每个节点初始值   $$a_i$$ 已经确定。我们发现对于一条边上的 $$a_x$$ 和 $$fa[a_x]$$ 如果想要使其相等，只能一个为 $$u$$ ,一个为 $$v$$ ，所以需要 $$|a_x - a[fa_x]|$$ 次操作才能让他们相等，其中对根节点有影响的是 $\max(a_x - a[fa_x],0)$。因此最终答案就是除了根节点外，所有节点对根结点的贡献之和再加上 $$a_1$$。
+ 接下来考虑 $$a_i$$ 。不难发现，父亲节点的 $$a_i$$ 等于子节点的最大值时最优，但要保证在 $$l_i$$ 和 $$r_i$$ 范围内，否则只能取最优合法值。
+ 最终复杂度 $$O(N)$$。
## 代码
``` cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 4 * 1e5 + 10;
int t, n, m, l[N], r[N], e[N], nxt[N], w[N], f[N], a[N], tot = 0;
vector<int> V[N];
void dfs(int x, int fa)
{
  int g = 0;
  for (int i = 0; i < V[x].size(); i++)
  {
    int v = V[x][i];
    if (v != fa)
    {
      f[v] = x;
      dfs(v, x);
      a[x] = max(a[x], a[v]);
      g = 1;
    }
  }
  a[x] = max(l[x], a[x]);
  a[x] = min(a[x], r[x]);
}
signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);//关闭同步流
  cin >> t;
  while (t--)
  {
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
      cin >> l[i] >> r[i];
      V[i].clear();//多次询问，记得清空
    }
    for (int i = 1; i < n; i++)
    {
      int u, v;
      cin >> u >> v;
      V[u].push_back(v);
      V[v].push_back(u);//建树
    }
    long long ans = 0;
    dfs(1, 0);
    for (int i = 2; i <= n; i++)
    {
      ans += max(0, a[i] - a[f[i]]);//遍历除根结点外的节点
    }
    cout << ans + a[1] << '\n';//加根节点
    for (int i = 1; i <= n; i++)
    {
      e[i] = a[i] = f[i] = 0;//不能用memset清空，否则会超时
    }
  }
  return 0;
}
```
##### 蒟蒻排版不好，望各位大佬理解QAQ

---

## 作者：_Kenma_ (赞：2)

## 前言

推销博客：[here.](https://www.cnblogs.com/Kenma/p/18697012)

## 正文

草感觉比 E 困难啊。

为了方便，我们强制每次操作的 $(u,v)$ 相连。 

首先钦定 $1$ 为根，假设 $a$ 是已知的，不难发现对于每次操作 $(u,v)$，它们是相互独立的，只影响 $(u,v)$ 两点的相对点权。

想要最小化点权，那么对于每个点，应该这样操作：

- 如果 $a_x < a_{fa}$，那么令 $u=fa,v=x$，使得 $a_x \to a_{fa}$；

- 如果 $a_x > a_{fa}$，那么令 $u=x,v=fa$，使得 $a_{fa} \to x$。

不难发现，这样操作后，点权为 $\sum_x \max(0,a_x-a_{fa})$。此处认为 $1$ 的父亲是 $0$。

所以，我们的问题转化为最小化 $\sum_x \max(0,a_x-a_{fa})$。

不难发现，在没有区间限制的前提下，令 $a_x \to \max_{y\in son_x}(a_y)$ 是最优的。

加上区间限制之后，结论依然成立。

注意对于叶子节点来说，令 $a_x \to l_x$ 是最优的。

按题意模拟贪心策略，总体复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,maxn,l[200005],r[200005],x,y;
int head[200005],nxt[400005],target[400005],tot;
void add(int x,int y){
	tot++;
	nxt[tot]=head[x];
	head[x]=tot;
	target[tot]=y;
}
int f[200005],a[200005];
void dfs(int x,int fa){
	f[x]=fa;
	bool flag=true;
	for(int i=head[x];i;i=nxt[i]){
		int y=target[i];
		if(y==fa) continue;
		dfs(y,x);
		a[x]=max(a[x],max(l[x],a[y]));
		flag=false;
	}
	if(flag) a[x]=l[x];
	a[x]=min(a[x],r[x]);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>l[i]>>r[i];
		}
		for(int i=1;i<n;i++){
			cin>>x>>y;
			add(x,y);
			add(y,x);
		}
		dfs(1,0);
		for(int i=1;i<=n;i++){
			maxn+=max(0ll,a[i]-a[f[i]]);
		}
		cout<<maxn<<'\n';
		for(int i=1;i<=n;i++){
			head[i]=0;
			a[i]=0;
			f[i]=0;
        }
    }
}
```

---

## 作者：_fairytale_ (赞：2)

-87，哈哈。

我们随便定一个根，然后把操作改写成子树 $+1$，或者全局 $+1$，子树 $-1$。

有一个性质是，在每个点的 $a$ 确定的时候，我们自底向上考虑每棵子树，对于点 $u$，如果我们忽略掉全局加，那么它子树中的值都会变成 $a_u$。

回到原题，一个贪心的想法是直接令 $a_i=l_i$。我们发现在叶子上这么做完全没有问题，问题出现在一个点小于它子树的时候，这个时候会带来一个全局加，但是全局加不优于子树加，于是记录一下儿子的 $\max$，取 $a_i$ 为尽可能接近儿子 $\max$ 的值即可。

```cpp
void Solve_(){
	int n;
	cin>>n;
	vector<int>l(n+1),r(n+1);
	rep(i,1,n)cin>>l[i]>>r[i];
	vector<vector<int>>g(n+1);
	for(int i=2,u,v;i<=n;++i){
		cin>>u>>v;
		g[u].ep(v),g[v].ep(u);
	} 
	vector<ll>f(n+1);
	vector<int>a(n+1);
	auto dfs=[&](auto &self,int u,int fa)->void{
		for(int v:g[u])if(v!=fa){
			self(self,v,u);
			ckmax(a[u],a[v]);
			f[u]+=f[v];
		}
		if(a[u]<l[u])a[u]=l[u];
		else if(a[u]>r[u])a[u]=r[u];
		for(int v:g[u])if(v!=fa)if(a[u]<a[v])f[u]+=a[v]-a[u];
	};
	dfs(dfs,1,0);
	cout<<a[1]+f[1]<<'\n';
}
```

---

## 作者：dayz_break404 (赞：1)

感觉 D 远大于 E1，卡了好久才做出来 qwq。

先考虑怎么根据区间给点赋初值更优，由于每次子树内加相当于是两个值不同的块合并的过程，合并是必定的，所以我们应当使每次加尽可能地少加一些不必要的点。因此每个叶子节点应当取最小值，记 $a_v$ 为 $v$ 这个点的值，对于一个点 $u$，定义 $k=\max_{v\in son(u)} a_v$，则 $a_u$ 的取值为：

$$a_u=\begin{cases}\max(k,l_u),r_u\ge k \\ r_u,r_u<k\end{cases}$$

现在考虑将所有点的值变成一样的过程，应该是自底向上变成一样的。对于 $u$ 为 $v$ 的父亲，如果有 $a_u\ge a_v$，那么可以通过一直加 $v$ 的子树变成相同的。否则就应当把 $v$ 作为根，将 $u$ 的子树一直加，直到 $a_u=a_v$。

现在考虑怎么维护这样的过程，加的过程相当于是将除了某一个子树整体加，最后统计单点的值，可以用 dfn 序加差分维护。

官方题解比我赛时写的更简单，因为最后每个点都是一样的值，所以只需要关注根节点的值，那么就变成当 $a_v>a_u$ 的时候，将根节点加上 $a_v-a_u$ 了。

代码很丑，但还是放着：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*f;
}
const int maxn=2e5+20;
#define ll long long
ll t,n,val[maxn],b[maxn],cf[maxn],dfn[maxn],tot,siz[maxn],ans,f[maxn],rev[maxn];
vector<ll> e[maxn];
struct range{
	ll l,r;
}a[maxn];
void dfs(int u,int fa){
	ll flag=0,mx=0;
	dfn[u]=++tot,siz[u]=1,f[u]=fa,rev[tot]=u;
	for(int v:e[u]){
		if(v==fa) continue;
		flag=1,dfs(v,u);
		mx=max(mx,val[v]),siz[u]+=siz[v];
	}
	if(!flag) val[u]=a[u].l;
	else{
		if(mx<=a[u].r) val[u]=max(mx,a[u].l);
		else val[u]=a[u].r;
	}
}
inline void solve(){
	n=read(),tot=ans=0;
	for(int i=0;i<=n;i++) e[i].clear(),b[i]=cf[i]=0;
	int u,v;
	for(int i=1;i<=n;i++) a[i]={read(),read()};
	for(int i=1;i<n;i++) u=read(),v=read(),e[u].push_back(v),e[v].push_back(u);
	dfs(1,0);
	for(int i=1;i<=n;i++) if(f[i]&&val[i]>val[f[i]]) b[i]=val[i]-val[f[i]];
	for(int i=1;i<=n;i++) cf[0]+=b[i],cf[dfn[i]]-=b[i],cf[dfn[i]+siz[i]]+=b[i];
	for(int i=1;i<=n;i++) cf[i]+=cf[i-1],ans=max(ans,cf[i]+val[rev[i]]);
	printf("%lld\n",ans);
}
int main(){
	t=read();
	while(t--) solve();
	return 0;
}
```

---

## 作者：AmaoFox (赞：1)

题意：

- 有一棵有 $N$ 个节点的树，每个点的初始点权可以是 $l_i\sim r_i$ 中的任何一个整数。
- 我们可以选定一条边，然后把该边某一侧的所有点点权增加 $1$。
- 目标是把所有点的点权调整成同一个数。求这个数最小是多少。

~~致敬场上想不出来打了十分钟钢四突然想出来了的 Amao_Fox。~~

我们发现，如果树上所有点的点权都相等，那么每一条边两侧的点权也是相等的。

我们又发现，一条边不可能往两个方向都进行过操作，否则等于给整个树平白无故加了 $1$，这当然是可以节约的。

所以我们得出一个结论：如果树上所有点的点权都已经确定了，那么对于每一条边，把点权小的那一侧所有节点点权 $+1$。因为除了这一条边以外的其它边两侧不是整体增加，就是整体不动，边之间并不会互相干扰。

接下来考虑怎么运用这个性质。首先会发现边的决策只和两侧的节点有关，所以我们不妨设立一个根。

对于一个父亲，如果它的点权比所有儿子都大，操作完以后点权还是原来的样子，因为所有的增加操作都是向下的。否则，父亲的点权为了变成最大的儿子，会向上传播增加操作。我们的目的便是要最小化向上的增加。（因为向下的增加是无可避免的）

所以我们设立一个贪心策略：父亲的点权正好是最大的儿子点权。否则尽可能大的设立（即设到 $r_i$）。不过，如果是叶子，为了这个贪心策略肯定要设到 $l_i$，这样可以尽可能避免向上的操作。

最终时间复杂度 $O(n)$。

代码：
```
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 200005;

int l[N], r[N], a[N];
vector<int> g[N];
int fat[N][20], dep[N];

void dfs(int u, int fa) {
  bool leaf = 1;
  int maxv = 0;
  for(auto v : g[u]) {
    if(v != fa) {
      dfs(v, u);
      maxv = max(maxv, a[v]);
      leaf = 0;
    }
  }
  if(leaf) {
    a[u] = l[u];
    return;
  }
  a[u] = max(min(maxv, r[u]), l[u]);
}

int calc(int u, int fa) {
  int ans = 0;
  for(int v : g[u]) {
    if(v != fa) {
      ans += max(a[v] - a[u], 0ll) + calc(v, u);
    }
  }
  return ans;
}

void solve() {
  int n;
  cin >> n;
  for(int i = 1; i <= n; i++) {
    cin >> l[i] >> r[i];
    g[i].clear();
  }
  for(int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(1, 1);
  // for(int i = 1; i <= n; i++) {
  //   cout << a[i] << ' ';
  // }
  // cout << '\n';
  cout << a[1] + calc(1, 1) << '\n';
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
}
```

---

## 作者：lfxxx (赞：0)

神秘调整法。

首先如果 $l_i=r_i$，考虑这么计算答案：对于每条边两端的节点，让端点权值小的一侧整体加上差值。

这么做是因为整体加上差值只会改变这一条边两端端点的差值，所以这么做是必须的，那么只进行这些操作也就是最优的了。

考虑 $l_i \not = r_i$ 的情形。

首先我们要给上面的处理方法找到一个比较好的刻画答案的方式，由于最终所有点权值均一样，不妨以 $1$ 为根，那么所以向上面那一侧的修改总和加上 $1$ 的权值就是答案。

考虑给每个点的实际点权 $a_i$ 会有的性质。

如果 $a_i < \max_{j \in son_i} a_j$ 并且 $a_i < r_i$，那么调大 $a_i$ 是不劣的。这一点容易通过分析 $j,i$ 之间的代价说明。

也就是说，在 $a_i \leq \max_{j \in son_i} a_j$ 的前提下我们希望尽量调大 $a_i$ 的值，而在已经有 $l_i \geq \max_{j \in son_i} a_j$ 的前提下很显然就直接让 $a_i=l_i$ 是最优的。

所以我们考虑从下往上按照这个方法直接确定所有的 $a_i$ 即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5+114;
int l[maxn],r[maxn],a[maxn];
vector<int> E[maxn];
int ans;
int n;
void dfs(int u,int fa){
    a[u]=l[u];
    for(int v:E[u]){
        if(v!=fa){
            dfs(v,u);
            a[u]=max(a[u],a[v]);
        }
    }
    a[u]=min(a[u],r[u]);
    for(int v:E[u]){
        if(v!=fa) ans+=max(0*1ll,a[v]-a[u]);
    }
}
void work(){
    cin>>n;
    ans=0;
    for(int i=1;i<=n;i++) cin>>l[i]>>r[i];
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    dfs(1,0);
    cout<<ans+a[1]<<"\n";
    for(int i=1;i<=n;i++) E[i].clear();
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}
```

---

