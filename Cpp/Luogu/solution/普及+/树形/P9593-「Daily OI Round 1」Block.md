# 「Daily OI Round 1」Block

## 题目描述

给定一棵树，节点有颜色，在树上距离为 $2$ 的点连边（仍保留原来的边），求新图中颜色相同且连通的非空点集数量。由于答案可能非常大，您只需输出答案对 $10^9+7$ 取模的值。

点集连通的定义：对于图 $G(V,E)$，$V$ 的一个子集 $V'$ 是连通点集，当且仅当 $G(V',E')$ 是一个连通图，其中边集 $E'=\{(u,v)|(u,v)\in E\land u \in V'\land v\in V'\}$。

## 说明/提示

样例 1 中，原树如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/zmgrnwkh.png)

树上距离为 $2$ 的点连边后，新图如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/id3xc54a.png)

则 $8$ 个颜色相同且连通的非空点集分别是：$\{1\},\{2\},\{3\},\{4\},\{1,3\},\{1,4\},\{3,4\},\{1,3,4\}$。

**本题开启捆绑测试。**



|$\text{Subtask}$|分值|$n \le$| 特殊性质 | 子任务依赖 |
| :-----------: | :-------------:|:-----------: |:-----------: |:-----------: |
|$0$|$5$|$10^5$| A | 无 |
|$1$|$5$|$16$| 无 | 无 |
|$2$|$5$|$10^5$| B | 无 |
|$3$|$15$|$10^5$| C | 无 |
|$4$|$20$|$10^5$| D | 无 |
|$5$|$50$|$10^5$| 无 | $0\sim4$ |

- 特殊性质 A：所有节点的颜色不相同。
- 特殊性质 B：给出的树是菊花，具体地，第 $i$ 条边连接节点 $1$ 和节点 $i+1$。
- 特殊性质 C：给出的树是链，具体地，第 $i$ 条边连接节点 $i$ 和节点 $i+1$。
- 特殊性质 D：所有节点的颜色相同。


对于全部数据，满足 $2\leq n\leq 10^5$，$1\leq c_i\leq n$。

## 样例 #1

### 输入

```
4
1 2 1 1
1 2
2 3
2 4
```

### 输出

```
8```

## 样例 #2

### 输入

```
6
1 2 2 2 1 2
5 3
2 1
4 5
6 3
3 1
```

### 输出

```
14```

## 样例 #3

### 输入

```
16
1 1 2 1 1 2 2 2 1 1 2 1 1 1 2 1
12 8
14 9
10 8
1 16
7 12
6 1
14 8
3 1
12 5
1 13
12 2
1 12
15 8
11 5
4 12
```

### 输出

```
442```

## 样例 #4

### 输入

```
16
11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11
4 14
4 15
12 13
2 5
7 15
10 2
15 8
15 13
9 11
13 11
3 15
8 16
6 13
1 4
10 4```

### 输出

```
27454```

## 样例 #5

### 输入

```
9
3 3 2 3 2 4 2 3 3
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9```

### 输出

```
16```

# 题解

## 作者：teylnol_evteyl (赞：7)

设 $c_u$ 表示节点 $u$ 的颜色，$f_u$ 表示只考虑原树中 $u$ 的子树中的点、选择点 $u$ 的方案数。对于儿子 $v$，可以选择同色儿子节点，也可以跳过这个儿子节点，选择 $v$ 的与 $u$ 同色的儿子节点 $w$，故状态转移方程为：

$$f_u=\prod[c_u=c_v]f_v+\left(\prod[c_u=c_w]f_w+1\right)$$

其中 $v$ 是 $u$ 的儿子，$w$ 是 $v$ 的儿子。

统计答案时，除了考虑选择的点的最近公共祖先被选择的情况（即 $\sum f_u$），还有最近公共祖先没有被选择的情况，也就是说一个节点 $u$ 的几个儿子节点颜色相同，则可以分别在它们的子树中选择，而不选 $u$。设 $g_{u,c}$ 表示考虑 $u$ 的子树，不选择 $u$，选择**至少两个**颜色为 $c$ 的儿子节点的方案数，因为要分别减去选择 $0$ 或 $1$ 个儿子的情况，所以：

$$g_{u,c}=\left(\prod[c_v=c]f_v+1\right)-\left(\sum[c_v=c]f_v\right)-1$$

其中 $v$ 是 $u$ 的儿子。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 1e5 + 5, P = 1e9 + 7;

int n, c[N];
int la[N], ne[N * 2], en[N * 2], idx;
LL f[N], g[N], res;

void add(int a, int b)
{
	ne[ ++ idx] = la[a];
	la[a] = idx;
	en[idx] = b;
}
void dp(int u, int fa)
{
	f[u] = 1;
	for(int i = la[u]; i; i = ne[i])
	{
		int v = en[i];
		if(v == fa) continue ;
		dp(v, u);
		
		LL t = 1;
		for(int j = la[v]; j; j = ne[j])
		{
			int w = en[j];
			if(w == u) continue ;
			if(c[w] == c[u]) t = t * (f[w] + 1) % P;
		}
		if(c[v] == c[u]) t = (t + f[v]) % P;
		f[u] = f[u] * t % P;
	}
	for(int i = la[u]; i; i = ne[i])
	{
		int v = en[i];
		if(v == fa) continue ;
		g[c[v]] = g[c[v]] * (f[v] + 1) % P;
	}
	for(int i = la[u]; i; i = ne[i])
	{
		int v = en[i];
		if(v == fa) continue ;
		res = (res + g[c[v]] - 1) % P;
		g[c[v]] = 1;
	}
}

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++ ) scanf("%d", &c[i]);
	for(int i = 1; i < n; i ++ )
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add(a, b), add(b, a);
	}
	add(0, 1);
	for(int i = 1; i <= n; i ++ ) g[i] = 1;
	dp(0, 0);
	printf("%lld\n", res);
	return 0;
}
```

---

## 作者：by_chance (赞：5)

[Link](https://www.luogu.com.cn/problem/P9593)

考虑树形 DP，定义 $dp_u$ 为在 $u$ 子树内，包含 $u$ 的合法点集数目。转移方程需要考虑 $u$ 的每个儿子的子树内的情况数。对于 $u$ 的儿子 $v$，分为两种情况：

- $v$ 的子树中所取的点包含 $v$。方案数为 $dp_v$，要求 $c_v=c_u$。这里 $c_i$ 表示点 $i$ 的颜色，下同。
- $v$ 的子树中所取的点不包含 $v$。那么要在 $v$ 的某些儿子的子树中取一些点，并且此时有点的子树的根一定取到，这样才能满足距离不超过 $2$。方案数就是

$$\prod_{w\text{是}v\text{的儿子},c_u=c_v}(dp_w+1)$$

下面统计答案。对于点 $u$，考虑 $u$ 子树内不包含 $u$ 的点集，按颜色分类，假设是颜色 $col$，则方案数为

$$\prod_{v\text{是}u\text{的儿子},c_v=col}(dp_v+1)-1$$

减掉的 $1$ 表示空集。

剩下还没有统计的是包含根结点的集合数目，也就是 $dp_1$。求和即得答案。

实现时只需要一次 dfs，递归完一个点的所有儿子就可以统计答案，然后记下和父亲颜色相同的方案数。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,P=1e9+7;
int n,c[N],dp[N],f[N],g[N],ans;
vector<int> G[N];
void dfs(int u,int fa){
    for(int v:G[u])if(v!=fa)dfs(v,u);
    dp[u]=1;
    for(int v:G[u])if(v!=fa)
        g[c[v]]=1ll*g[c[v]]*(dp[v]+1)%P;
    f[u]=g[c[fa]];
    for(int v:G[u])if(v!=fa)
        dp[u]=1ll*dp[u]*(f[v]+dp[v]*(c[v]==c[u]))%P;
    for(int v:G[u])if(v!=fa)
        ans=(ans+g[c[v]]-1)%P,g[c[v]]=1;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",c+i),g[i]=1;
    for(int i=1,u,v;i<n;i++){
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1,0);
    printf("%d\n",(ans+dp[1])%P);
    return 0;
}
```

---

## 作者：一只绝帆 (赞：3)

感觉官方题解有点东西没说清/kk。

树形 dp 的状态很关键：本题设 $f_x$ 表示只考虑 $x$ 子树内**且必须选** $x$ 的方案数，$g_{x}$ 表示 $x$ 选了至少两个同颜色的儿子，**且不选** $x$ 的方案数。

转移方程：

$$f_x\gets \prod_{v\text{ is son of }x}\left([c_x=c_v]f_v+\prod_{w\text{ is son of }v,c_x=c_w}(f_w+1)\right)$$

最终肯定是若干子树的某一权值乘起来，而这个值有两部分：$[c_x=c_v]f_v$ 表示选 $v$（以及 $v$ 的子树的所有情况）。

而 $\prod_{w\text{ is son of }v,c_x=c_w}(f_w+1)$ 表示跳过 $v$ 选 $w$，注意这一部分并不能写成 $\prod_{w\text{ is son of }v}[c_x=c_w](f_w+1)$，显而易见地会乘 $0$。

只选 $x$ 一个点的方案包括在后一项中。

还有 $g_{x}$：

$$g_{x}\gets\sum_{c=1}^n\left(\prod_{v\text{ is son of }x,c_v=c}(f_{v}+1)-\left(\sum_{v\text{ is son of }x,c_v=c}f_v\right)-1\right)$$

第一部分是每棵子树选/不选乘起来，就是所有子树选/不选的全部情况，减去选一个子树的所有情况 $\sum_{v\text{ is son of }x,c_v=c}f_v$，再减去啥也不选的 $1$，就是至少两棵子树的情况。

这个 $g_x$ 也没什么用，直接加到 $ans$ 里就好。

看着 $g_x$ 的转移好像是 $O(n)$ 的，实际上只需要枚举有用的颜色即可。

Code：
```cpp
#include<bits/stdc++.h>
#define F(i,a,b) for(int i(a),i##end(b);i<=i##end;i++)
#define gc getchar
#define G(i,x) for(int i(start[x]);i;i=Next[i])
using namespace std;
int read() {
	int s=0;char c=gc(),w=0;
	while(c<'0'||c>'9') w|=c=='-',c=gc();
	while(c>='0'&&c<='9') s=s*10+(c^48),c=gc();
	return w?-s:s;
} const int N=2e5+5,M=N<<1,p=1e9+7;typedef long long ll;
int cnt,v[M],Next[M],start[N],n,c[N];ll p1[N],s1[N],ans,f[N];
void add(int x,int y) {v[++cnt]=y;Next[cnt]=start[x];start[x]=cnt;}
void Add(int x,int y) {add(x,y);add(y,x);}
void d(int x,int fa) {
	f[x]=1;G(i,x) if(v[i]^fa) {
		d(v[i],x);
		ll t1=(c[x]==c[v[i]])?f[v[i]]:0,t2=1;
		G(j,v[i]) if(v[j]^x) {
			if(c[x]==c[v[j]]) t2=t2*(f[v[j]]+1)%p;
		} f[x]=f[x]*(t1+t2)%p;
	} ans=(ans+f[x])%p;
	G(i,x) if(v[i]^fa) {
		int co=c[v[i]];
		if(!p1[co]) p1[co]=1;
		p1[co]=p1[co]*(f[v[i]]+1)%p;
		s1[co]=(s1[co]+f[v[i]])%p;
	} 
	G(i,x) if(v[i]^fa) {
		int co=c[v[i]];
		if(p1[co]) ans=(ans+p1[co]-s1[co]-1+p)%p,p1[co]=s1[co]=0;
	}
}
int main() {
	F(i,1,n=read()) c[i]=read();
	F(i,1,n-1) Add(read(),read());
	d(1,0);cout<<ans<<endl;
	return 0;
} 
```

---

## 作者：MrPython (赞：1)

在树上考虑 dp。

对于每个节点，dp 数组保存两个信息。设当前位于点 $p$，$f_{p,0}$ 表示**必须选择** $p$ 的方案数，$f_{p,1}$ 表示**必须不选当前点**且**至少选了一点**的方案数。

然后是转移。

如果不选择第 $p$ 个点，分两种情况：
- 选择了若干个相同颜色的子节点。对于若干个颜色相同的节点，每个节点都可以选择选择该点的任意一种方案或不选。设当前子树为 $i$，则该点的贡献为 $f_{i,0}+1$。拿个 map 玩一下，将每种颜色的所有贡献相乘，记 $s_c=\prod_{i\in son(p) \wedge color(i)=c}f_{i,0}+1$。最后，可以选择任意一种颜色，将他们的贡献相加。不过，每种颜色都有全不选的情况，应当减去这一种，即 $f_{p,1,0}=\sum_{c} s_c-1$。
- 其他情况。所有选择子节点的情况都已经在上一种情况中考虑过了，我们在此考虑所有不选择子节点的情况。如果不选择某个子节点 $i$ 且不选择当前节点 $p$，则 $i$ 的子树中不为 $i$ 的任意一点都不可能与 $p$ 的其他儿子[^1]相连。而 $i$ 的子树中不选 $i$ 的方案数正好为 $f_{i,1}$，因此 $f_{p,1,1}=\sum_{i\in son_(p)} f_{i,1}$。

最后的答案即 $f_{p,1}=f_{p,1,0}+f_{p,1,1}$。

如果选择第 $p$ 个点，该点与其所有儿子与孙子[^2]相连。此时，我可以任意选择所有颜色与 $p$ 相同的儿子或孙子。不过，选择儿子 $i$ 的方案数 $f_{i,0}$ 已经包括了所有选择 $i$ 的儿子的可能方案，所以对于某个儿子 $i$，其贡献应为选了 $i$ 的方案与未选 $i$ 的方案相加。选了 $i$ 时的方案数，当 $i$ 的颜色与 $p$ 相同时为 $f_i$，否则不可能选择，为 $0$。未选 $i$ 时，$i$ 的所有颜色与 $p$ 相同的儿子都可以任意选择一种或不选择。因此，考虑子树 $i$ 总方案数为 $t_{i}=\left[color(i)=color(p)\right]\times f_{i,0}+\prod_{j\in son(i)\wedge color(j)=color(p)}f_{j,0}$。最后，任意两颗子树之间没有相互影响，$f_{p,0}=\sum_{i\in son(p)}t_i$。

[^1]: 指以该节点为根的子树中与根距离为 $1$ 的节点。
[^2]: 指以该节点为根的子树中与根距离为 $2$ 的节点。

```cpp
// include https://raw.githubusercontent.com/atcoder/ac-library/master/atcoder/modint
#include <bits/extc++.h>
using namespace std;
namespace pbds = __gnu_pbds;
istream &fin = cin;
ostream &fout = cout;
using ui = unsigned int;
using uli = unsigned long long int;
using li = long long int;
using mi = atcoder::modint1000000007;
struct Node {
  size_t color;
  vector<Node *> nxt;
  pair<mi, mi> dp;
  size_t id;
  pair<mi, mi> f(Node *fa = nullptr) {
    unordered_map<size_t, mi> s;
    dp.first = 1;
    for (Node *son : nxt)
      if (son != fa) {
        son->f(this);
        s.emplace(son->color, 1).first->second *= son->dp.first + 1;
        dp.second += son->dp.second;
        mi r = 1;
        for (Node *son2 : son->nxt)
          if (son2 != this && son2->color == color) r *= (son2->dp.first + 1);
        dp.first *= (son->color == color ? son->dp.first : 0) + r;
      }
    for (auto const &i : s) dp.second += i.second - 1;
    return dp;
  }
};
int main(void) {
  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  size_t n;
  fin >> n;
  vector<Node> nodes(n);
  for (size_t i = 0; i < n; ++i)
    fin >> nodes[i].color, --nodes[i].color, nodes[i].id = i;
  for (size_t i = 1; i < n; ++i) {
    size_t x, y;
    fin >> x >> y;
    --x, --y;
    nodes[x].nxt.emplace_back(&nodes[y]);
    nodes[y].nxt.emplace_back(&nodes[x]);
  }
  nodes[0].f();
  mi ans = nodes[0].dp.first + nodes[0].dp.second;
  fout << ans.val();
  return 0;
}
```

---

