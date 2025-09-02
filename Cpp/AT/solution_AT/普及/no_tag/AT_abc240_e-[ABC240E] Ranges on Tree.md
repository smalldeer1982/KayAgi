# [ABC240E] Ranges on Tree

## 题目描述

### 题面简述

给出一个有 $N$ 个节点的树和其中的 $N-1$ 条树边（描述无向），其中我们规定节点编号为 $1,2,\cdots,N-1,N$，其中节点 $1$ 为树根。

你需要给予每一个节点 $i$ 一个闭区间 $[L_i,R_i]$，你需要保证一下性质。

- 虽然当 $L_i=R_i$ 的时候不满足闭区间书写规范，但是在本题中允许出现。

- $\forall_i,1\le L_i\le R_i$。

- 如果 $i$ 是 $j$ 的父亲节点，保证 $[L_j,R_j]\subseteq [L_i,R_i]$。

- 如果 $i,j$ 为兄弟节点（拥有相同的父亲节点），那么保证 $[L_i,R_i]\cap[L_j,R_j]=\varnothing$。

你需要保证你构造出的方案的 $\max\limits_{i=1}^{N} R_i$ 最小。

## 样例 #1

### 输入

```
3
2 1
3 1```

### 输出

```
1 2
2 2
1 1```

## 样例 #2

### 输入

```
5
3 4
5 4
1 2
1 4```

### 输出

```
1 3
3 3
2 2
1 2
1 1```

## 样例 #3

### 输入

```
5
4 5
3 2
5 2
3 1```

### 输出

```
1 1
1 1
1 1
1 1
1 1```

# 题解

## 作者：loser_seele (赞：2)

不难想到首先确定答案的下界。

首先设叶子个数为 $ M $，则显然有叶子之间两两不交。所以考虑从分析叶子入手。

于是，问题等价于包含叶子的区间两两不交，因为叶子不可能互相包含。所以答案的下界即为 $ M $。

接下来考虑如何构造一种答案恰好为 $ M $ 的方案。

在 dfs 的时候顺便给叶子分配一个编号，然后取每个点子树中的编号最小值和最大值成为区间端点即可。这样因为叶子数是 $ M $，那么不同的编号也只有 $ M $ 个。那么实际上这些表示的区间即为以其为根节点的子树，而子树显然要么完全包含要么两两不交。

时间复杂度 $ \mathcal{O}(N) $，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
void dfs(int i,int &c,vector<vector<int>> &nodes,vector<bool> &used,vector<vector<int>> &ret) 
{
  if (used[i]) 
  return;
  used[i]=1;
  ret[i][0]=c;
  int n=nodes[i].size();
  for (int j=0;j<n;j++) 
  {
    if (used[nodes[i][j]]) 
    continue;
    dfs(nodes[i][j],c,nodes,used,ret);
    c++;
  }
  if (n>1 || i==0) 
  c--;
  ret[i][1]=c;
}
int main() 
{
  int n;
  cin >> n;
  vector<vector<int>> nodes(n,vector<int>(0));
  for (int i=0;i<n-1;i++) 
  {
    int u,v;
    cin >> u >> v;
    u--;v--;
    nodes[u].push_back(v);
    nodes[v].push_back(u);
  }
  int cur=1;
  vector<bool> used(n,0);
  vector<vector<int>> ret(n,vector<int>(2));
  dfs(0,cur,nodes,used,ret);
  for (int i=0;i<n;i++) 
    cout << ret[i][0] << " " << ret[i][1] << endl;
}
```


---

## 作者：_OccDreamer_ (赞：1)

注意到我们划分的最小无交子问题一定是一个叶子节点，令其为 $k$，那么答案区间显而易见的为 $[1, k]$。

设 $dp_x$ 为点 $x$ 子树中包含的叶子节点个数，则：

$$
dp_x = \sum_{u \in x} dp_u
$$

边界为：$dp_{leaf} = 1$。

dp 序列可以预处理。对于答案的求取，不妨设点 $x$ 当前答案左边界为 $pos$，则答案区间为 $[pos, pos + dp_x]$。递归时顺便传参记录一下即可。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define fi first
#define se second
using namespace std;

const int N = 1e6 + 5;
int n, u, v, ans, dp[N];
vector<int> g[N];
pair<int, int> Ans[N];

inline void dfs(int x, int last, int pos) {
	int now = pos;

	Ans[x] = {now, now + dp[u] - 1};

	for(auto u : g[x])
		if(u != last) {
			dfs(u, x, now);

			now += dp[u];
		}
	
	return ;
}

inline void init(int x, int last) {
	if(x != 1 && g[x].size() == 1) dp[x] = 1;
	
	for(auto u : g[x])
		if(u != last) {
			init(u, x);

			dp[x] += dp[u];
		}
	
	return ;
}

signed main() {
	ios_base :: sync_with_stdio(NULL);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> n;
	for(int i = 1 ; i < n ; ++ i) {
		cin >> u >> v;

		g[u].pb(v), g[v].pb(u);
	}

	init(1, -1);
	dfs(1, -1, 1);

	for(int i = 1 ; i <= n ; ++ i)
		cout << Ans[i].fi << ' ' << Ans[i].se << '\n';

	return 0;
}
```

---

## 作者：2020luke (赞：1)

# [[ABC240E] Ranges on Tree](https://www.luogu.com.cn/problem/AT_abc240_e) 题解

## 思路解析

由题意可知，只要一个点的所有儿子节点都被确定了，那么当前节点也就被确定了。也就是说，只要确定了所有叶子节点，也就能一层层地确定所有节点，而叶子节点没有儿子节点不受此条件的约束，同时我们希望 $\max\limits^N_{i=1}R_i$ 最小，所以我们把所有叶子节点的区间长度都置为 $1$ 即可。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, fa[N], son[N], cnt = 0, l[N], r[N];
vector<int> g[N];
void dfs(int u, int f) {
	fa[u] = f;
	for(auto it : g[u]) if(it != f) son[u]++;
	if(son[u] == 0) l[u] = r[u] = ++cnt;
	else l[u] = 2e9, r[u] = 0;
	for(auto it : g[u]) {
		if(it != f) dfs(it, u), l[u] = min(l[u], l[it]), r[u] = max(r[u], r[it]);
	}
}
int main() {
	cin >> n;
	for(int i = 1, u, v; i < n; i++) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1, 0);
	for(int i = 1; i <= n; i++) {
		cout << l[i] << ' ' << r[i] << '\n';
	}
	return 0;
}
```

---

## 作者：_qingshu_ (赞：1)

# 题意：

[这里](https://www.luogu.com.cn/paste/szubtpuv)。

# 思路：

对于每一个点 $x$ 来说，假设 $l,r$ 分别为它的左右儿子（如果不存在某一个则该点集合视为空集），那么肯定是当 $[L_l,R_l]\cup[L_r,R_r]=[L_x,R_x]$ 的时候保证最优。而当其不存在儿子的时候，其区间一定是 $L_x=R_x$。以上结论是好证的，可以手摸反证一下，在此就不过多赘述了。

既然不存在儿子的时候就相当于访问的是叶子节点，而又需要叶子之间两两不交，我们可以尝试给予叶子节点单独的编号，每一个点的集合就是以该点为根的子数内所包含单独编号最大、最小的叶子节点，这下就好求了。

考虑搜索树时如果遇到叶子节点就给予单独编号，$L_i,R_i$ 都是这个叶子的编号，其余节点回溯时尝试更新，分别取最大取最小，在最后独立输出就好了。

# Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,tot,lef[5200010],rig[5200010];
vector<int>e[5200010];
inline void dfs(int id,int fa){
    if(e[id].size()==1&&e[id][0]==fa){
        rig[id]=lef[id]=++tot;
        return;
    }
    for(int v : e[id]){
        if(v!=fa){
            dfs(v,id);
            rig[id]=max(rig[id],rig[v]);
            lef[id]=min(lef[id],lef[v]);
        }
    }
}
int main(){
    memset(lef,0x3f,sizeof lef);
    cin>>n;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++)cout<<lef[i]<<" "<<rig[i]<<endl;
}
```

---

## 作者：appear_hope (赞：1)

给叶子节点编号，那么当前点 $i$ 的区间是 $\min l_j \sim \max r_j$，其中 $j$ 是以 $i$ 为根的子树的叶子。

代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 1145141919810;

vector<int> g[N];
int n, id, l[N], r[N];

void dfs(int x, int fa){
  int flag = 1;
  for(int v : g[x]){
    if(v != fa){
      flag = 0;
      dfs(v, x);
      l[x] = min(l[x], l[v]);
      r[x] = max(r[x], r[v]);
    }
  }
  if(flag){
    l[x] = r[x] = ++id;
  }
}

int main(){
  cin >> n;
  for(int i = 1, u, v; i < n; i++){
    cin >> u >> v;
    g[u].push_back(v), g[v].push_back(u);
  }
  fill(l + 1, l + n + 1, n + 1);
  dfs(1, 0);
  for(int i = 1; i <= n; i++){
    cout << l[i] << ' ' << r[i] << '\n';
  }
  return 0;
}

```

---

## 作者：OrzSceamyn (赞：0)

## AT_abc240_e [ABC240E] Ranges on Tree

### 思路
~~看到这题，想到了线段树的建树。~~

但是根本不用这么麻烦。

从叶子节点开始考虑，如果该节点为叶子节点，那么该节点对应的区间一定满足 $l$ 与 $r$ 相等。dfs 的时候特判一下即可。

对于非叶子节点，直接取儿子节点的并集，也就是取叶子节点 $l$ 的最小值和叶子节点 $r$ 的最大值即可。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T=1;
const int maxn=2e5+7;
int son[maxn],ansl[maxn],ansr[maxn];
vector<int> g[maxn];
int n;
int ans=0;
void dfs(int u,int fa){
	for(int v:g[u]){
		if(v!=fa){
			son[u]++;
		}
	} 
	if(son[u]==0){
	 	ansl[u]=ansr[u]=++ans;
	}
	else{
		ansl[u]=1e18;
		ansr[u]=-1;
		for(int v:g[u]){
			if(v==fa) continue;
			dfs(v,u);
			ansl[u]=min(ansl[u],ansl[v]);
			ansr[u]=max(ansr[u],ansr[v]);
		}
	}
}
void solve(){
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++){
		cout<<ansl[i]<<' '<<ansr[i]<<'\n';
	}
	
}
int32_t main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	while(T--){
		solve();
	}
	return 0;
}

```

---

## 作者：kczw (赞：0)

# 题意
给定一棵有 $N$ 个点且以节点 $1$ 为根的树，对于树上的点 $i(1\le i\le N)$ 要求你对其定一个区间 $[L_i,R_i]$，保证所有兄弟节点两两间交集为空集，以及父节点区间包含子节点区间。

求 $R_1$ 最小时的 $L_i,R_i(1\le i\le N)$。
# 思路
首先分类讨论一下：
- 对于一个叶节点 $u$，易知为了使 $R_1$ 最小，有 $L_u=R_u$。
- 对于一个非叶节点 $u$，易知为了使 $R_1$ 最小，其区间须取其所有子节点区间并集。

最后跑一遍深搜，按照叶节点遍历顺序的先后赋值其区间左右端点值，同时对于非叶节点合并其子节点区间，最后输出 $L_i,R_i(1\le i\le N)$ 即可。
# 实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
vector<int> r[N];
int n,L[N],R[N],id;
inline void dfs(int u,int fa){
    for(auto v:r[u])
        if(v!=fa){
            dfs(v,u);
            if(!L[u])L[u]=L[v];
            R[u]=R[v];
    }
    if(r[u].size()==1&&u!=1)
        L[u]=R[u]=++id;
}
int main(){
    scanf("%d",&n);
    for(int i=1,u,v;i<n;i++){
        scanf("%d%d",&u,&v);
        r[u].emplace_back(v);
        r[v].emplace_back(u);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++)
        printf("%d %d\n",L[i],R[i]);
    return 0;
}
```

---

