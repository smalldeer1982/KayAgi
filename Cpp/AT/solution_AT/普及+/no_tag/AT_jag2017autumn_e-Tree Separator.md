# Tree Separator

## 题目描述

给定一棵无根树 $T$ 与一个整数 $K$，你需要找到两个不同的节点 $u,v$，使得将在 $u,v$ 简单路径上的点及其所连接的边全部删去后剩余的连通块中大小至少为 $K$ 的连通块数量最多。

# 题解

## 作者：happy_dengziyue (赞：0)

### 1 思路

看到路径分割连通块，考虑点分治。

设当前分治中心为 $x$，对于经过 $x$ 但端点不在 $x$ 的路径 $(u,v)$，考虑如何计算贡献。

以下认为“子树 $p$”为以分治中心 $x$ 为根时以 $p$ 为根的子树，记这个子树的大小是 $si_p$，则它的贡献是 $[si_p\ge k]$。

设路径 $(x,u)$ 中，点 $a$ 是 $x$ 的下一个点；同理路径 $(x,v)$ 中，点 $b$ 是 $x$ 的下一个点。与路径 $(a,u)$ 或 $(b,v)$ 相连的子树的贡献都是好求的，而 $x$ 产生的贡献则是所有与 $x$ 相连的子树（包括子树 $a$ 和 $b$）的贡献减去子树 $a$ 和 $b$ 的贡献。

我们发现，所有与 $x$ 相连的子树的贡献是无关乎 $u$ 和 $v$ 的，然后再对于每个 $a$ 求出最优的 $u$，选出最优的 $(a,b)$ 即可。

对于端点在 $x$ 的路径同理。

### 2 代码与记录

```cpp
#include<bits/stdc++.h>
using namespace std;
#define max_n 100000
int tid;
int n;
int k;
vector<int>g[max_n+2];
int fa[max_n+2];
int dfn[max_n+2],tim=0;
int edfn[max_n+2];
int sp[max_n+2];
bool vis[max_n+2];
int si[max_n+2],ssi=0;
int masi[max_n+2];
int dis[max_n+2];
int rt=0;
int ans=0;
void dfs1(int u,int f){
	fa[u]=f; dfn[u]=++tim;
	for(auto v:g[u]){
		if(v!=f)dfs1(v,u);
	}
	edfn[u]=tim;
}
inline int calcsi(int u,int v){
	if(dfn[u]<=dfn[v])return edfn[v]-dfn[v]+1;
	return n-(edfn[u]-dfn[u]+1);
}
void asksi(int u,int f){
	si[u]=1;
	for(auto v:g[u]){
		if(v==f||vis[v])continue;
		asksi(v,u); si[u]+=si[v];
	}
}
void askrt(int u,int f){
	masi[u]=0;
	for(auto v:g[u]){
		if(v==f||vis[v])continue;
		askrt(v,u); masi[u]=max(masi[u],si[v]);
	}
	masi[u]=max(masi[u],ssi-si[u]);
	if(masi[u]<=masi[rt])rt=u;
}
inline void askdis(int x,int u,int f,int sum){
	int w=sum+sp[u];
	if(calcsi(u,f)>=k)--w;
	dis[x]=max(dis[x],w);
	for(auto v:g[u]){
		if(v==f||vis[v])continue;
		if(calcsi(u,v)>=k)askdis(x,v,u,w-1);//否则往下也没意义了 
	}
}
void askans(int u){
//	printf("askans u=%d\n",u);
	vis[u]=true;
	vector<int>son;
	for(auto v:g[u]){
		if(!vis[v])son.push_back(v);
	}
	if(son.empty())return;
	int soni=son.size(),tot=0;
	for(auto v:g[u]){
		if(calcsi(u,v)>=k)++tot;
	}
	for(int i=0;i<soni;++i)dis[i]=0;
	for(int i=0;i<soni;++i){
		askdis(i,son[i],u,0);
		if(calcsi(u,son[i])>=k)--dis[i];
	}
	sort(dis,dis+soni,[](int x,int y){return x>y;});
	ans=max(ans,tot+dis[0]);
	if(soni>=2)ans=max(ans,tot+dis[0]+dis[1]);
	for(auto v:son){
		asksi(v,u); ssi=masi[rt=0]=si[v];
		askrt(v,u); askans(rt);
	}
}
int main(){
    tid=1;
	for(int ca=1;ca<=tid;++ca){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;++i)g[i].clear();
		for(int i=1,u,v;i<n;++i){
			scanf("%d%d",&u,&v);
			g[u].push_back(v); g[v].push_back(u);
		}
		/*printf("n=%d k=%d\n",n,k);
		for(int u=1;u<=n;++u){
			for(auto v:g[u]){
				if(u<v)printf("%d %d\n",u,v);
			}
		}*/
		tim=0;
		dfs1(1,0);
		for(int i=1;i<=n;++i)sp[i]=0;
		for(int u=1;u<=n;++u){
			for(auto v:g[u]){
				if(calcsi(u,v)>=k)++sp[u];
			}
		}
		for(int i=1;i<=n;++i)vis[i]=false;
		ans=0;
		asksi(1,0); ssi=masi[rt=0]=si[1];
		askrt(1,0); askans(rt);
		printf("%d\n",ans);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/181383423)

By **dengziyue**

---

## 作者：__Floze3__ (赞：0)

## 思路简述

具体而言，对于树上的每个点，我们可以分为两个部分来考虑：这个点是选择的两个端点中离根节点更近的那个，或是不同于选择的两个端点的 LCA。我们考虑通过树形 dp 来找出答案。我们设 $f_{i, 0/1}$ 表示对于每个点，它是上面两种情况之一时整个子树的答案。我们发现为了得出每个 dp 值，我们需要预先处理出子树的大小，记为 $siz_u$；和删除每个点能创造出的大小不小于于 $k$ 的连通块个数，记这个值为 $del_u$。那么对于第一个情况，我们不难写出这样的转移方程：

$$
f_{u, 0} = \max_{v \in son(u)} \lbrace del_u + \max(del_v, f_{v, 0}) - [siz_v \ge k] \rbrace
$$

对于第二种情况，我们需要从当前节点的儿子节点中选出两个作为两个被删除的链的顶端，我们可以得出选择一个儿子节点的贡献为：

$$
\max(del_v, f_{v, 0} - [siz_v \ge k])
$$

我们记最大的两个贡献值为 $m1$，$m2$，可以得出：

$$
f_{u, 1} = del_u + m1 + m2
$$

那么最终答案即为

$$
\max_{u \notin leaf} \lbrace \max(f_{u, 0}, f_{u, 1}) + [n - siz_u \ge k] \rbrace
$$

直接计算即可。

## 代码

```cpp
#include <bits/stdc++.h>

using i64 = long long;
using vi = std::vector<int>;

constexpr int N = 1e5 + 5;
constexpr int inf = 0x3f3f3f3f;

int n, k, f[N][2], siz[N], del[N], ans;

vi g[N];

void pre(int u, int fa) {
  siz[u] = 1;
  for (int v : g[u]) {
    if (v == fa) continue;
    pre(v, u);
    siz[u] += siz[v];
    if (siz[v] >= k) ++del[u];
  }
  return ;
}

void dp(int u, int fa) {
  int m1 = -inf, m2 = -inf;
  for (int v : g[u]) {
    if (v == fa) continue;
    dp(v, u);
    int res = del[u] + std::max(del[v], f[v][0]) - (siz[v] >= k);
    f[u][0] = std::max(f[u][0], res);
    res -= del[u];
    if (res > m1) m2 = m1, m1 = res;
    else if (res > m2) m2 = res;
  }
  f[u][1] = del[u] + m1 + m2;
  // 注意叶子节点不能更新答案
  if(g[u].size() > 1) ans = std::max(ans, std::max(f[u][0], f[u][1]) + (n - siz[u] >= k));
  return ;
}

signed main() {
  std::cin.tie(nullptr) -> sync_with_stdio(false);
  std::cin >> n >> k;
  for (int i = 1; i < n; ++i) {
    int u, v;
    std::cin >> u >> v;
    g[u].emplace_back(v), g[v].emplace_back(u);
  }
  pre(1, 0), dp(1, 0);
  std::cout << ans << '\n';
  return 0;
}
```

---

