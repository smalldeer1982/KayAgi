# [ABC350G] Mediator

## 题目描述

**请注意特殊的输入格式。同时，请注意内存限制比通常更小。**

有一个包含 $N$ 个顶点 $1,2,\dots,N$ 的无向图，初始时没有任何边。  
请对该图处理以下 $Q$ 个查询。

> 1 $u$ $v$

类型 $1$：在顶点 $u$ 和顶点 $v$ 之间添加一条边。  
在添加边之前，$u$ 和 $v$ 属于不同的连通分量（也就是说，图始终是一片森林）。

> 2 $u$ $v$

类型 $2$：如果存在同时与顶点 $u$ 和顶点 $v$ 相邻的顶点，则输出其编号，否则输出 $0$。  
由于图始终是一片森林，可以证明对于该查询的答案是唯一的。

但是，上述查询是经过加密后给出的。  
原始查询由 $3$ 个整数 $A,B,C$ 定义，基于此给出加密后的查询 $a,b,c$。  
对于类型 $2$ 的查询，第 $k$ 个（从前往后数）查询的答案记为 $X_k$。此外，定义 $k=0$ 时 $X_k=0$。  
请根据给定的 $a,b,c$ 按如下方式解密得到 $A,B,C$：

- 设在该查询之前已经给出的类型 $2$ 查询的个数为 $l$（不包括当前查询）。此时，按如下方式解密：
  - $A = 1 + (((a \times (1+X_l)) \bmod 998244353) \bmod 2)$
  - $B = 1 + (((b \times (1+X_l)) \bmod 998244353) \bmod N)$
  - $C = 1 + (((c \times (1+X_l)) \bmod 998244353) \bmod N)$

## 说明/提示

### 限制

- 所有输入均为整数。
- $2 \leq N \leq 10^5$
- $1 \leq Q \leq 10^5$
- $1 \leq u < v \leq N$
- $0 \leq a,b,c < 998244353$

### 样例解释 1

将所有查询解密后，输入如下：  
```
6 12
2 1 3
1 2 6
1 2 4
1 1 3
2 4 6
2 1 4
1 5 6
1 1 2
2 1 4
2 2 5
2 3 4
2 2 3
```
对于该输入，图有 $6$ 个顶点，包含 $12$ 个查询。
- 第 $1$ 个查询为 `2 1 3`。  
  顶点 $1$ 和顶点 $3$ 没有共同相邻的顶点，输出 $0$。
- 第 $2$ 个查询为 `1 2 6`。  
  在顶点 $2$ 和顶点 $6$ 之间添加一条边。
- 第 $3$ 个查询为 `1 2 4`。  
  在顶点 $2$ 和顶点 $4$ 之间添加一条边。
- 第 $4$ 个查询为 `1 1 3`。  
  在顶点 $1$ 和顶点 $3$ 之间添加一条边。
- 第 $5$ 个查询为 `2 4 6`。  
  顶点 $4$ 和顶点 $6$ 的共同相邻顶点为顶点 $2$。
- 第 $6$ 个查询为 `2 1 4`。  
  顶点 $1$ 和顶点 $4$ 没有共同相邻顶点，输出 $0$。
- 第 $7$ 个查询为 `1 5 6`。  
  在顶点 $5$ 和顶点 $6$ 之间添加一条边。
- 第 $8$ 个查询为 `1 1 2`。  
  在顶点 $1$ 和顶点 $2$ 之间添加一条边。
- 第 $9$ 个查询为 `2 1 4`。  
  顶点 $1$ 和顶点 $4$ 的共同相邻顶点为顶点 $2$。
- 第 $10$ 个查询为 `2 2 5`。  
  顶点 $2$ 和顶点 $5$ 的共同相邻顶点为顶点 $6$。
- 第 $11$ 个查询为 `2 3 4`。  
  顶点 $3$ 和顶点 $4$ 没有共同相邻顶点，输出 $0$。
- 第 $12$ 个查询为 `2 2 3`。  
  顶点 $2$ 和顶点 $3$ 的共同相邻顶点为顶点 $1$。

### 样例解释 2

也可能出现输出为空的情况。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6 12
143209915 123840720 97293110
89822758 207184717 689046893
67757230 270920641 26993265
952858464 221010240 871605818
730183361 147726243 445163345
963432357 295317852 195433903
120904472 106195318 615645575
817920568 27584394 770578609
38727673 250957656 506822697
139174867 566158852 412971999
205467538 606353836 855642999
159292205 319166257 51234344```

### 输出

```
0
2
0
2
6
0
1```

## 样例 #2

### 输入

```
2 1
377373366 41280240 33617925```

### 输出

```
```

# 题解

## 作者：NATO (赞：11)

AT 官方写的都是什么 shaber 玩意，无所谓，优雅的、正确的暴力会出手！

~~要为暴力而斗争！~~

### 思路浅析：

我们很容易就可以有一个暴力做法。

即：对于查询的点对，我们先判断它们是否在一个连通块内，在则再枚举与其中一个点相连的点，再判断枚举的点是否与另一个点相邻即可。

这样做是 $O(n^2)$ 的，~~虽然可以过~~。

但是，暴力真的，就这样了吗？

下面我们将证明记忆化、钦定枚举相邻点数较小的点的相邻点的暴力的复杂度是 $O(n\sqrt n)$ 的。

显然，如果两个点不在一个连通块内，使用并查集判断的单次复杂度是 $O(\alpha(n))$ 的，这是极小的。

否则，若在一个连通块内，显然对于两个点答案必然是固定的，可以记忆化，这样我们分析复杂度时只需要考虑不同点对的影响。设当前询问的两个点相邻点数分别是 $sz_u,sz_v$，因为我们钦定枚举相邻点数较小的点，所以复杂度最差的情况就是每次询问时 $sz_u=sz_v$。因为如果不等，在单次询问复杂度相同的情况下我们可能的最大询问数必然是不超过相等的情况的。而复杂度最差就要求在 $sz_u=sz_v$ 的同时又要尽可能挂满不同点对的询问数，那么这些询问用到的节点的度数全部相同就是我们复杂度最差的情况，因此我们只需要证明这种情况的复杂度是 $O(n\sqrt n)$ 即可。

那么设询问用到的节点的度数均是 $r$，那么我们最多可以有 $\lfloor\frac{n}{r}\rfloor$ 个这样的点，那么最多可以有 $\min(q,\lfloor\frac{n}{r}\rfloor^2)$ 次询问，而单次询问的复杂度可以做到 $O(r)$（考虑用哈希表存边，枚举相邻点数较小的点的相邻点，每个相邻点可以均摊 $O(1)$ 地判断是否为另一个点的相邻点，单次就是 $O(r)$ 的），那么总复杂度就是 $O(\min(q,\lfloor\frac{n}{r}\rfloor^2)r)$。

1. 当 $\min(q,\lfloor\frac{n}{r}\rfloor^2)=q$ 时。

   那么现在复杂度即为 $O(qr)$，而由 $\min(q,\lfloor\frac{n}{r}\rfloor^2)=q$ 可知 $\lfloor\frac{n}{r}\rfloor^2\ge q$，即 $\lfloor\frac{n}{r}\rfloor\ge\sqrt q$，即 $r\le\sqrt q$，又考虑到 $n,q$ 同阶，那么复杂度即为 $O(n\sqrt n)$。

2. 当 $\min(q,\lfloor\frac{n}{r}\rfloor^2)=\lfloor\frac{n}{r}\rfloor^2$ 时。

   与第一点同理，我们可以知道，$r\ge\sqrt q$，而此时的复杂度是 $O(\lfloor\frac{n}{r}\rfloor^2r)$，即为 $O(n\sqrt n)$。

综上所述，我们经过小改进的暴力是 $O(n\sqrt n)$ 的，可以通过本题。

#### 参考代码：

```cpp
#include<bits/stdc++.h>
#define ll int 
using namespace std;
ll n,q;
ll a,b,c;
ll lans;
unordered_map<ll,ll>s[100005];
unordered_map<ll,ll>ans[100005];
unordered_map<ll,ll>vis[100005];
ll f[100005];
ll find(ll x)
{
	return (f[x]==x)?x:(f[x]=find(f[x]));
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>q;
	for(ll i=1;i<=n;++i)f[i]=i;
	while(q--)
	{
		cin>>a>>b>>c;
		a=1+((long long)(a*1ll*(1+lans))%998244353ll%2);
		b=1+((long long)(b*1ll*(1+lans))%998244353ll%n);
		c=1+((long long)(c*1ll*(1+lans))%998244353ll%n);
		if(a==1)
			s[b][c]=s[c][b]=1,f[find(b)]=find(c);
		else
		{
			if(vis[b][c])
				cout<<(lans=ans[b][c])<<'\n';
			else
			{
				if(find(b)!=find(c))
				{
					cout<<(lans=0)<<'\n';continue;
				}
				if(s[b].size()>s[c].size())swap(b,c);
				for(auto it:s[b])
				if(s[c].count(it.first))
				{
					ans[b][c]=ans[c][b]=it.first;break;
				}
				vis[b][c]=vis[c][b]=1;
				cout<<(lans=ans[b][c])<<'\n';
			}
		}
	}
 } 
```

---

## 作者：small_john (赞：10)

## 思路

G 题最简单的一集~~因为暴力可过~~，但是看到官解是根号做法我惊了。

首先发现结构是个森林，则记点 $x$ 的父亲为 $f_x$，那么存在一个顶点同时与点 $u,v$ 相邻有三种情况：

1. $f_u=f_v$，那么这个点就是 $f_u$；
2. $f_{f_u}=v$，那么这个点就是 $f_u$；
3. $f_{f_v}=u$，那么这个点就是 $f_v$。

发现只要能维护出每个节点的父亲即可解决这道题，考虑启发式合并。

在顶点 $u$ 和 $v$ 之间连边之前我们先保证 $u$ 所在的联通块大小不超过 $v$ 所在的联通块大小（这部分可以用并查集维护）。把 $u$ 所在的联通块的根节点变为 $u$，暴力修改联通快内点的父亲，然后 $u,v$ 连边，将 $f_u$ 赋值为 $v$。时间复杂度 $O(n\log n)$。

那为什么是这个时间复杂度呢？

发现每次把小的块合并进大的块时，小的块的大小至少扩大一倍。而总共只有 $n$ 个点，则最多扩大 $\log n$ 次，即每个点的父亲只会变化 $\log n$ 次，所以复杂度为 $O(n\log n)$。

## 代码

注意处理询问时需要判断两个点是否都为联通块的根。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

template<typename T> inline void read(T &x)
{
	x = 0;
	T f = 1;char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f = -1,ch = getchar();
			break;
		}
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
		x = (x<<3)+(x<<1)+ch-48,ch = getchar();
	x*=f;
}
template<typename T> inline T read()
{
	T x;read(x);return x;
}
template<typename T> void write(T x)
{
    if(x<0) x = -x,putchar('-');
    if(x>9) write(x/10);
    putchar(x%10+48);
}
template<typename T> inline void writen(T x)
{
    write(x);
    putchar(10);
}
const int N = 1e5+5,mod = 998244353;
int n,q,f[N],sz[N],ff[N];
vector<int> g[N];
void dfs(int u,int fa)
{
	f[u] = fa;
	for(auto v:g[u])
	{
		if(v==fa) continue;
		dfs(v,u);
	}
}
int find(int x)
{
	if(x==ff[x]) return x;
	return ff[x] = find(ff[x]);
}
inline void merge(int x,int y)
{
	int fx = find(x),fy = find(y);
	if(sz[fx]>sz[fy]) swap(x,y),swap(fx,fy);
	dfs(x,y);
	sz[fy]+=sz[fx],ff[fx] = fy;
	g[x].push_back(y),g[y].push_back(x);
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n),read(q);
	for(int i = 1;i<=n;i++)
		sz[i] = 1,ff[i] = i;
	int las = 0;
	while(q--)
	{
		int op,u,v;
		read(op),read(u),read(v);
		op = (op*(1+las))%mod%2+1,u = (u*(1+las))%mod%n+1,v = (v*(1+las))%mod%n+1;
		if(op==1) merge(u,v);
		else
		{
			las = 0;
			if(f[u]==f[v]&&f[u]!=0) las = f[u];
			else if(f[f[u]]==v) las = f[u];
			else if(f[f[v]]==u) las = f[v];
			writen(las);
		}
	}
	return 0;
}
```

---

## 作者：MicroSun (赞：5)

你说的对但是这题暴力可过。

为什么呢？

操作分为两种，一种加边，一种查询，而用暴力解题时，明显加边 $\Omicron(1)$，查询 $\Omicron(n)$。

明显查询数越多，程序用时越长。注意到查询数量不大于 $10^5$，所以极限情况差不多是先 $5\times10^4$ 次加边，再 $5\times10^4$ 次查询。

但即使处于这种较为极限的情况，最大计算次数约为 $2.5\times10^9$。

注意到时限 $3$ 秒，机子是 AT 的……

氰危卡卡常。[Code](https://atcoder.jp/contests/abc350/submissions/52634427)

---

## 作者：沉石鱼惊旋 (赞：4)

# 题目翻译

$n$ 个点的图，$q$ 次操作。

`1 u v` 操作 $1$ 是 $u$ 和 $v$ 连边。

`2 u v` 查询**哪个点**同时和 $u,v$ 有连边。保证 $u,v$  同时只会和不超过 $1$ 个点连边。如果没有同时连边的点，答案就是 $0$。

$1\leq n,q\leq 10^5$。强制在线。

注意特殊的空间限制是 $\color{red}{256\ \tt{MB}}$。

# 题目思路

首先看完就秒一个 $\mathcal O(\frac{nq}{\omega})$ 的做法。直接用 bitset 优化暴力。

然后交一发发现 MLE 了，空间限制过不去。

然后再想到一个朴素一点的 $\mathcal O(qn\log n)$ 的做法，直接维护邻接表，然后遍历与 $u$ 连接的点，判断是否与 $v$ 连接。

~~然后做完了。~~

这个时候你发现一个很优美的很经典的性质，$\sum deg_u=\mathcal O(n)$。

也就是说，点度数越大，那么点数越少。

这就是很经典的根号分治。

具体的，我们定义 $deg_u\geq B$ 的点为大点，反之为小点。

容易发现大点个数 $\leq \frac{n}{B}$。

也就是说，如果我们查询两个大点，直接用 $\mathcal O(\frac{nq}{\omega})$ 的做法。如果查询包含小点，直接用  $\mathcal O(qn\log n)$ 的做法。

考虑到第一个做法瓶颈在空间上，第二个做法瓶颈在时间上，这么缝合就能保证第一个做法只会对 $\frac{n}{B}$ 个点维护 bitset，第二个做法遍历的邻接表大小一定是 $\leq B$ 的。

然后时空限制就都很对了。

注意一下大点只有 $\frac{n}{B}$ 个。编号离散化一下。

~~你怎么知道我没离散化干净吃了 3 发 RE。~~

# 完整代码

[https://atcoder.jp/contests/abc350/submissions/52578330](https://atcoder.jp/contests/abc350/submissions/52578330)

```cpp
#include <bits/stdc++.h>
using namespace std;
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++
char buf[1000000], *p1 = buf, *p2 = buf;
template <typename T>
void read(T &x)
{
    x = 0;
    int f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -f;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    x *= f;
}
template <typename T, typename... Args>
void read(T &x, Args &...y)
{
    read(x);
    read(y...);
}
const int p = 998244353;
const int B = 320;
int n, q;
int id[100020];
int tot;
bitset<100020> f[720];
bitset<100020> g;
bitset<100020> big;
set<int> a[100020];
int ans;
int decode(int x, int q) { return 1 + (1LL * x * (ans + 1) % p) % q; }
void add(int u, int v)
{
    if (big[u])
        return f[id[u]][v] = 1, void();
    a[u].insert(v);
    if (a[u].size() == B)
    {
        id[u] = ++tot;
        for (int j : a[u])
            f[tot][j] = 1;
        big[u] = 1;
    }
}
int main()
{
    read(n, q);
    while (q--)
    {
        int op, u, v;
        read(op, u, v);
        op = decode(op, 2);
        u = decode(u, n);
        v = decode(v, n);
        if (op & 1)
        {
            add(u, v);
            add(v, u);
        }
        else
        {
            if (big[u] && big[v])
            {
                g = f[id[u]] & f[id[v]];
                if (g.none())
                    cout << (ans = 0) << '\n';
                else
                    cout << (ans = g._Find_first()) << '\n';
                continue;
            }
            if (big[u])
                swap(u, v);
            ans = 0;
            for (int j : a[u])
            {
                if (big[v] ? f[id[v]][j] : a[v].count(j))
                {
                    ans = j;
                    break;
                }
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
```

---

## 作者：_qingshu_ (赞：4)

感觉下位蓝或者上位绿吧，挺简单的启发式合并裸题。

# 题意：

给定 $N$ 个点，$M$ 次操作，操作强制在线，操作分为：

- 将点 $u,v$ 之间连一条边。

- 询问同时与 $u,v$ 直接相连的一个点，如果没有输出 $0$。

然后数据保证无重边无自环，任意时刻图为一个森林，所以操作二答案唯一。

# 思路：

一眼启发式合并，如果操作可能有答案那么这两个点一定在同一颗树内且距离为 $2$，考虑在随意钦定根的情况下答案的分类讨论，容易发现如果记录 $fa_{i}$ 为点 $i$ 的父亲节点，当 $fa_{i}=i$ 时点 $i$ 为根，那么答案有且仅有五种情况：

1) $fa_u=v\lor fa_v=u$，这个是防止当 $u,v$ 任意一点为根时后续判断出错的，此时答案为 $0$。

2) $fa_u=fa_v$，答案为 $fa_u$还是 $fa_v$ 是一样的。

3) $fa_{fa_u}=v$，答案是 $fa_u$。

4) $fa_{fa_v}=u$，答案是 $fa_v$。

5) 如果以上均不满足，那么答案不存在，答案是 $0$。

解决了询问，我们来考虑连边，发现如果要保证是森林的话一次连边等价于合并两颗树，但是我们要保证合并后的大树的根唯一，那么也就是说被合并的树一定是以 $v$ 为根节点的，所以我们考虑怎么将一棵树的根节点变成 $v$。

我们可以想一想对于原树与新树需要更改的 $fa_{i}$，你会发现把所有的需要被更改的点连起来就是一条从 $v$ 到原树根的链，下面是口胡证明（并不严谨，但是是对的，感性理解qwq）：

我们把原树所有的点分为 $4$ 类：

- 以 $v$ 为根节点的子树内的所有节点，对于原树和新树来说，它们都是满足到根路径经过点 $v$ 的，所以不需要更改，在 $fa_{v}$ 的更改后自然指向大树的根。

- 从点 $v$ 到原根的路径上的点，这些点均为指向有误，是需要更改方向变为从原根指向 $v$。

- 以点 $i$ 为根节点且满足 $fa_{i}$ 在从 $v$ 到根的链上的子树，它们在第二类的点更改后自然随之指向大树的根。

- 以点 $i$ 为根且满足 $fa_{i}$ 为原根的子树，这些点在原根指向更改后随之指向大树的根。

综上，我们换根的过程仅需要跑一边从 $v$ 到原根的路径就可以保证换根后所有的点父亲指向均正确。

然后这个复杂度是 $\mathcal{O}(N^2)$ 的，但是我们可以启发式合并优化到 $\mathcal{O}(N\log(N))$，树的大小可以用并查集维护。

# Code：

```cpp
#include<bits/stdc++.h>
#define mod 998244353
using namespace std;
int ans,a,b,c,n,q,lastans,fa[100010],root[100010],siz[100010],fab,fac;
inline int findfa(int x){
	if(root[x]!=x)root[x]=findfa(root[x]);
	return root[x];
}
inline void cg(int x){
	if(fa[x]==x)return;
	cg(fa[x]),fa[fa[x]]=x;
}
inline void solve(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		fa[i]=root[i]=i;siz[i]=1;
	}
	while(q--){
		cin>>a>>b>>c;
		a=1+((1ll*a*(1+lastans))%mod)%2;
		b=1+((1ll*b*(1+lastans))%mod)%n;
		c=1+((1ll*c*(1+lastans))%mod)%n;
		if(a==1){
			fab=findfa(b);fac=findfa(c);
			if(siz[fac]>siz[fab])swap(b,c),swap(fab,fac);
			siz[fab]+=siz[fac];
			cg(c);fa[c]=b;root[fac]=fab;
		}
		else{
			lastans=0;
			if(fa[c]==b||fa[b]==c);
			else if(fa[c]==fa[b]||fa[fa[c]]==b)lastans=fa[c];
			else if(fa[fa[b]]==c)lastans=fa[b];
			cout<<lastans<<"\n";
		}
	}
}
int main(){
	int T=1;//cin>>T;
	while(T--)solve();
}
```

加上快读可以跑进 $10ms$，目前 $2024.4.21$ 的最优解。

---

## 作者：_Ch1F4N_ (赞：3)

考虑根号重构。

每 $\sqrt n$ 次操作就把已经给出的边建出树，那么假若询问的两个点在同一个联通块中枚举相邻那个点是共同父亲还是儿子与祖先中的父亲。

假若不在同一个连通块上，那么这个相邻的点一定是没有建出的边上，由于只有 $\sqrt n$ 条便可以直接枚举，当然需要对于每个点开个哈希表记录下一个点与其他点是否有边相连。

时间复杂度 $O(n \sqrt n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5+114;
const int mod = 998244353;
const int B = 400;
int fa[maxn],dep[maxn],col[maxn];
vector<int> E[maxn];
unordered_map<int,int> hood[maxn];//1 级邻域
vector<int> e[maxn];//临时边
int n,q;
void dfs(int u,int father,int rt){
    col[u]=rt;
    fa[u]=father;
    dep[u]=dep[father]+1;
    for(int v:E[u]){
        if(v!=fa[u]) dfs(v,u,rt);
    }
}
int ask(int u,int v){
    if(col[u]==col[v]){
        if(dep[u]<dep[v]) swap(u,v);
        if(v==fa[fa[u]]) return fa[u];
        else if(fa[u]==fa[v]) return fa[u];
        else return 0;
    }else{
        for(int x:e[u]){
            if(hood[x][v]==1) return x;
        }
        for(int x:e[v]){
            if(hood[x][u]==1) return x;
        }
        return 0;
    }
}
void build(){
    for(int i=1;i<=n;i++){
        for(int u:e[i]) E[i].push_back(u);
        e[i].clear();
        col[i]=0;
    }
    for(int i=1;i<=n;i++){
        if(col[i]==0) dfs(i,0,i);
    }
}
int lstans;
signed main(){
    cin>>n>>q;
    build();
    for(int i=1;i<=q;i++){
        int a,b,c;
        cin>>a>>b>>c;
        a=1+(a*(1+lstans)%mod)%2;
        b=1+(b*(1+lstans)%mod)%n;
        c=1+(c*(1+lstans)%mod)%n;
        if(a==1){
            e[b].push_back(c);
            e[c].push_back(b);
            hood[b][c]=hood[c][b]=1;
        }else{
            cout<<(lstans=ask(b,c))<<'\n';
        }
        if(i%B==0) build();
    }
    return 0;
}

```

---

## 作者：_determination_ (赞：3)

这里是启发式合并做法。

注意到如果我们知道了每个节点的父亲，那么就很好判断他们是不是符合条件。但是父亲这个东西显然不能像并查集那样随便维护，连一条边后我们就需要用一次 `dfs` 来重新确定父亲关系。

但是我们发现不用遍历整个新树。根原来所处的部分不用遍历。考虑启发式合并，遍历大小小的那棵树。

复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
int n,q;
int lastans;
const int mod=998244353;
int fa[100010];
vector<int>e[100010];
int siz[100010];
int root[100010];
void dfs(int x,int f,int rt)
{
    fa[x]=f;
    root[x]=rt;
    for ( int i = 0 ; i < e[x].size() ; i++ )
    {
        int v=e[x][i];
        if(v==f)continue;
        dfs(v,x,rt);
    }
}
void merge(int x,int y)
{
    if(siz[root[x]]>siz[root[y]])swap(x,y);
    siz[root[y]]+=siz[root[x]];
    dfs(x,y,root[y]);
    e[x].push_back(y);
    e[y].push_back(x);
}
signed main()
{
    ios::sync_with_stdio(false);
    cin >> n >> q;
    for ( int i = 1 ; i <= n ; i++ )
    {
        siz[i]=1;
        root[i]=i;
    }
    while(q--)
    {
        int op,x,y;
        cin >> op >> x  >> y;
		op=(op*(1+lastans)%998244353)%2+1;
		x=(x*(1+lastans)%998244353)%n+1;
		y=(y*(1+lastans)%998244353)%n+1;
        // cout << op << " " << x << " " << y << endl;
        if(op==1)
        {
            merge(x,y);
        }else{
            if(fa[x]==fa[y])
            {
                lastans=fa[x];
            }else if(fa[fa[x]]==y)
            {
                lastans=fa[x];
            }else if(fa[fa[y]]==x)
            {
                lastans=fa[y];
            }else{
                lastans=0;
            }
            cout << lastans << endl;
        }
    }
    return 0;
}
```

---

## 作者：fydj (赞：3)

# [ABC350G] Mediator

### 题目大意

给你 $n$ 个点，要完成 $q$ 种操作，操作有两种：

* ```1 x y``` 从 $x$ 向 $y$ 连一条无向边
* ```2 x y``` 如果有一个点同时被 $x$ 和 $y$ 连接，那么回答这个点的编号，否则回答 $0$。

保证每一次操作 $1$ 后这个图是一个森林。

强制在线，操作解密方法见原题面。

### 思路

```LCT``` 模板题。

用 ```LCT``` 维护操作 $1$ 的连边。

对于操作 $2$，先 ```makeroot x```，再 ```access y```，最后 ```splay x```，有两种情况：

##### 情况 1

![](https://cdn.luogu.com.cn/upload/image_hosting/k10c4sdk.png)

##### 情况 2

![](https://cdn.luogu.com.cn/upload/image_hosting/oph46e6y.png)

暴力判断位置关系以及一些关键位置是不是空就可以了。

或者取中序遍历的前 $3$ 位，看一下是不是 ```x y z```。

### [代码](https://atcoder.jp/contests/abc350/submissions/52613484)

### 建议评紫

因为 [模板题](https://www.luogu.com.cn/problem/P3690) 是紫的。

---

## 作者：CarroT1212 (赞：3)

用 [LCT](https://www.luogu.com.cn/problem/P3690) 大炮打蚊子也是可以的呢。

操作 $1$ 是 `link`，操作 $2$ 就是把 $b\to c$ 的路径 `split` 出来，然后看一看这条链的长度是不是 $3$，是的话答案就是中间那个点。

注意不能上来直接找 LCT 里每个点的父亲判出各种情况输出，因为同一条实链上的父子关系是 `splay` 过的，跟原树不一样，需要 `split` 过后才是。

那我场上为什么没过呢？

因为联想一下 `split` 的操作，查询路径答案的时候两个端点不在同一个连通块会出不小的问题。所以在 `split` 之前记得看一下两个点的 `findroot` 结果是否相同。场上这玩意在强制在线的力量下显示了 `RE` 让我以为是板子写挂了……

```cpp
ll n,q;
struct lct {
	ll w[N],sz[N],s[N][2],fa[N],tg[N],st[N],tp;
	ll gsn(ll p) { return s[fa[p]][1]==p; }
	void pdn(ll p) {
		if (tg[p]) swap(s[p][0],s[p][1]),tg[s[p][0]]^=1,tg[s[p][1]]^=1,tg[p]=0;
	}
	void upd(ll p) { w[p]=w[s[p][0]]+w[s[p][1]]+p,sz[p]=sz[s[p][0]]+sz[s[p][1]]+1; }
	bool isr(ll p) { return s[fa[p]][0]!=p&&s[fa[p]][1]!=p; }
	void tur(ll p) {
		ll f=fa[p],ff=fa[f],c=gsn(p);
		if (!isr(f)) s[ff][gsn(f)]=p;
		s[f][c]=s[p][!c],fa[s[p][!c]]=f,s[p][!c]=f,fa[f]=p,fa[p]=ff,upd(f),upd(p);
	}
	void lif(ll p) {
		st[tp=1]=p;
		for (ll i=p;!isr(i);i=fa[i]) st[++tp]=fa[i];
		for (;tp;tp--) pdn(st[tp]);
		for (;!isr(p);) {
			ll f=fa[p];
			if (!isr(f)) tur(gsn(p)^gsn(f)?p:f);
			tur(p);
		}
	}
	void acc(ll p) { for (ll c=0;p;c=p,p=fa[p]) lif(p),s[p][1]=c,upd(p); }
	void mrt(ll p) { acc(p),lif(p),tg[p]^=1; }
	ll grt(ll p) {
		acc(p),lif(p);
		for (;s[p][0];) p=s[p][0];
		return p;
	}
	void spl(ll x,ll y) { mrt(x),acc(y),lif(y); }
	void lnk(ll x,ll y) { mrt(x),fa[x]=y; }
	ll que(ll x,ll y) {
		if (grt(x)!=grt(y)) return 0;
		spl(x,y);
		if (sz[y]!=3) return 0;
		else return w[y]-x-y;
	}
} T;
void mian() {
	scanf("%lld%lld",&n,&q);
	for (ll i=1;i<=n;i++) T.w[i]=i,T.sz[i]=1;
	for (ll i=1,x,y,z,last=0;i<=q;i++) {
		scanf("%lld%lld%lld",&x,&y,&z);
		x=1ll+x*(1ll+last)%P%2,y=1ll+y*(1ll+last)%P%n,z=1ll+z*(1ll+last)%P%n;
		if (x==1) T.lnk(y,z);
		else cout<<(last=T.que(y,z))<<"\n";
	}
}
```

---

## 作者：FFTotoro (赞：2)

有人问 G 的根号做法。那就随便写点。

简单地将点按照度数是否超过 $\sqrt{n}$ 进行分类，$\deg_u>\sqrt{n}$ 的 $u$ 称为大点，反之称为小点。容易得知大点数量 $\le\sqrt{n}$。所以对于大点提前处理出所有答案，用 `std::map` 存储，询问时直接查询已经求得的答案；对于小点遍历所有出边直接暴力查，存边使用 `std::set`。

每次合并时简单判断一个点是否成为大点即可。如果是这个点第一次成为大点就直接进行搜索，否则就更新新加进来的点即可。

时间复杂度 $O(n\sqrt{n}\log n)$，但是实际上跑起来常数很小，$10^5$ 稳稳跑进 400ms。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int P=998244353;
main(){
  ios::sync_with_stdio(false);
  int n,q,l=0,sq; cin>>n>>q,sq=sqrt(n);
  vector<int> d(n);
  vector<set<int> > g(n);
  map<pair<int,int>,int> t;
  auto I=[&](int u,int v,int w){
    t[make_pair(min(u,v),max(u,v))]=w;
  }; // 大点提前预处理答案
  auto Q=[&](int u,int v)->int{
    if(u>v)swap(u,v);
    if(t.find(make_pair(u,v))==t.end())return -1;
    return t[make_pair(u,v)];
  }; // 查询大点的答案
  while(q--){
    int a,b,c; cin>>a>>b>>c;
    a=((l+1)*a%P&1)+1,b=(l+1)*b%P%n,c=(l+1)*c%P%n;
    if(a==1){
      d[b]++,d[c]++,g[b].emplace(c),g[c].emplace(b);
      if(d[b]==sq) // 第一次成为大点
        for(int i:g[b])
          for(int j:g[i])I(b,j,i);
      else if(d[b]>sq) // 不是第一次，只加新的
        for(int j:g[c])I(b,j,c);
      if(d[c]==sq)
        for(int i:g[c])
          for(int j:g[i])I(c,j,i);
      else if(d[c]>sq)
        for(int j:g[b])I(c,j,b);
    }
    else{
      if(d[b]>d[c])swap(b,c);
      if(d[b]<=sq){ // 小点直接暴力
        bool f=false;
        for(int i:g[b])
          if(g[c].find(i)!=g[c].end()){
            cout<<(l=i+1)<<'\n',f=true; break;
          }
        if(!f)cout<<(l=0)<<'\n';
      }
      else cout<<(l=Q(b,c)+1)<<'\n';
    }
  }
  return 0;
}
```

---

## 作者：WaterSun (赞：1)

[更好的阅读体验](https://watersun.top/%5B%E9%A2%98%E8%A7%A3%5DAT_abc350_g%20[ABC350G]%20Mediator)

# 思路

有加边操作，一眼 LCT。问题在于处理询问操作。

首先，判断联通。如果 $x,y$ 不在同一个联通块内，则一定没有答案。

其次，求出 $x,y$ 之间节点的数量 $num$（包括 $x,y$）。如果 $num = 3$ 说明 $x,y$ 之间有一个共同的节点；如果 $num = 2$ 说明 $x,y$ 直接连接；如果 $num > 3$ 说明 $x,y$ 之间有不止一个节点。

当 $num = 3$ 时，考虑如何计算该节点的编号。维护节点的编和，查询 $x,y$ 之间的编号和 $sum$，答案显然就是 $sum - x - y$。

全都是 LCT 基本操作，难点在于会不会 LCT。

# Code

```cpp
#include <bits/stdc++.h>
#define fst first
#define snd second
#define re register
#define int long long

using namespace std;

typedef pair<int,int> pii;
const int N = 1e5 + 10,mod = 998244353;
int n,q,lst,f[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

struct LCT{
    #define fp(u) (tr[u].fa)
    #define son(u,k) (tr[u].ch[k])
    #define getch(u) (u == son(fp(u),1))
    #define isroot(u) (u != son(fp(u),getch(u)))

    struct node{
        int fa,ch[2];
        pii val,sum;
        int tag;
    }tr[N];

    inline void calc(int u){
        if (!u) return;
        tr[u].tag ^= 1;
        swap(son(u,0),son(u,1));
    }

    inline void maintain(int u,int fa,int k,bool falg){
        if (!falg || !isroot(fp(u))) son(fa,k) = u;
        fp(u) = fa;
    }

    inline void pushup(int u){
        tr[u].sum.fst = tr[son(u,0)].sum.fst + tr[son(u,1)].sum.fst + tr[u].val.fst;
        tr[u].sum.snd = tr[son(u,0)].sum.snd + tr[son(u,1)].sum.snd + tr[u].val.snd;
    }

    inline void pushdown(int u){
        if (tr[u].tag){
            calc(son(u,0)); calc(son(u,1));
            tr[u].tag = 0;
        }
    }

    inline void update(int u){
        if (!isroot(u)) update(fp(u));
        pushdown(u);
    }

    inline void rotate(int u){
        int fa = fp(u);
        int ffa = fp(fa);
        int k = getch(u);
        maintain(son(u,k ^ 1),fa,k,false);
        maintain(u,ffa,getch(fa),true);
        maintain(fa,u,k ^ 1,false);
        pushup(fa);
    }

    inline void splay(int u){
        update(u);
        while (!isroot(u)){
            int fa = fp(u);
            if (!isroot(fa)){
                if (getch(u) != getch(fa)) rotate(u);
                else rotate(fa);
            }
            rotate(u);
        }
        pushup(u);
    }

    inline void access(int u){
        int p = 0;
        while (u){
            splay(u);
            son(u,1) = p; pushup(u);
            p = u; u = fp(u);
        }
    }

    inline void makeroot(int u){
        access(u); splay(u);
        calc(u);
    }

    inline int split(int x,int y){
        makeroot(x);
        access(y); splay(y);
        return y;
    }

    inline int find(int u){
        access(u); splay(u);
        pushdown(u);
        while (son(u,0)) pushdown(u = son(u,0));
        splay(u);
        return u;
    }

    inline void link(int x,int y){
        makeroot(x);
        if (find(y) != x) fp(x) = y;
    }

    #undef fp
    #undef son
    #undef getch
    #undef isroot
}T;

inline int find(int x){
    if (f[x] != x) return f[x] = find(f[x]);
    return f[x];
}

inline void merge(int a,int b){
    int x = find(a),y = find(b);
    if (x == y) return;
    f[x] = y;
}

signed main(){
    n = read(),q = read();
    for (re int i = 1;i <= n;i++){
        T.tr[i].val = {i,1};
        f[i] = i;
    }
    while (q--){
        int op,x,y;
        op = (read() * (1 + lst) % mod) % 2 + 1;
        x = (read() * (1 + lst) % mod) % n + 1;
        y = (read() * (1 + lst) % mod) % n + 1;
        if (op == 1){
            T.link(x,y); merge(x,y);
        }
        else{
            if (find(x) != find(y)) printf("%lld\n",lst = 0);
            else{
                pii ans = T.tr[T.split(x,y)].sum;
                if (ans.snd != 3) printf("%lld\n",lst = 0);
                else printf("%lld\n",lst = (ans.fst - x - y));
            }
        }
    }
    return 0;
}
```

---

## 作者：破壁人罗辑 (赞：0)

题目传送门：[AtCoder](https://atcoder.jp/contests/abc350/tasks/abc350_g)

## 题意简述

有一个 $n$ 个节点的无向图，初始情况下没有边，给出 $q$ 个操作，在节点 $u,v$ 之间建立一条无向边或者查询连接 $u,v$ 的节点，强制在线。

Time Limit: 3 sec / Memory Limit: 256 MB

## 解题思路

直接暴力最高复杂度是 $O(nq)$，最高到 $10^{10}$，使用位运算优化后可以达到 $\frac{10^{10}}{32}$ 或 $\frac{10^{10}}{64}$，不需要使用 `bitset` 就可以通过。注意空间限制较小，需要使用 `unordered_map`。

## AC 代码
```cpp
#include<bits/stdc++.h>
#define MOD 998244353
using namespace std;
unordered_map<int,unsigned int> st[100000];
int main(){
	int n,q,x=0,a,b,c;scanf("%d%d",&n,&q);
	while(q--){
		scanf("%d%d%d",&a,&b,&c);
		b=(b*(1ll+x)%MOD)%n;c=(c*(1ll+x)%MOD)%n;
		if((a*(1ll+x)%MOD)&1){
			if(st[b].find(c>>5)!=st[b].end()&&st[b][c>>5]&(1<<(c&31))){
				puts("0");x=0;
			}
			else{
				bool h=1;
				for(int i=0;i<(n+63)>>5;i++)
				if(st[b].find(i)!=st[b].end()&&st[c].find(i)!=st[c].end()&&st[b][i]&st[c][i]){
					for(int j=0;j<32;j++)
					if(st[b][i]&st[c][i]&(1<<j)){
						x=(i<<5)+j+1;printf("%d\n",x);break;
					}
					h=0;break;
				}
				if(h){puts("0");x=0;}
			}
		}
		else{
			st[b][c>>5]|=1<<(c&31);
			st[c][b>>5]|=1<<(b&31);
		}
	}
	return 0;
}
```

---

## 作者：Judgelight (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc350_g)

---

给个不动脑子的 LCT 做法。。。

考虑连接操作可以直接做，询问的话先判断 $x$ 和 $y$ 是否在同一个连通块，然后考虑把 $x$ 当作根，再把 $x$ 和 $y$ 拉到同一棵 Splay 上。由于 Splay 的中序遍历就是原树重链由浅到深的排列，判断 $y$ 的前驱是否是 $x$ 的后继即可，答案就是 $y$ 的前驱。

```cpp
#include<bits/stdc++.h>
#define N 100009
#define eb emplace_back
#define mk make_pair
#define ll long long
using namespace std;
const int mod=998244353;
struct Node{int l,r,s[2],v;bool rev;}tr[N];int fa[N],a[N];
inline void pushup(int u){tr[u].v=tr[tr[u].s[0]].v^tr[tr[u].s[1]].v^a[u];}
inline void pushdown(int u){if(tr[u].rev)swap(tr[u].s[0],tr[u].s[1]),tr[tr[u].s[0]].rev^=1,tr[tr[u].s[1]].rev^=1,tr[u].rev=0;}
inline bool isrt(int u){return tr[fa[u]].s[0]!=u&&tr[fa[u]].s[1]!=u;}
void rotate(int x){
	pushdown(x);
	int y=fa[x],z=fa[y],k=(tr[y].s[0]==x);
	if(!isrt(y))tr[z].s[tr[z].s[1]==y]=x;
	fa[x]=z,fa[tr[x].s[k]]=y,tr[y].s[k^1]=tr[x].s[k],fa[y]=x,tr[x].s[k]=y;
	pushup(y),pushup(x);
}
int stk[N],top;
void splay(int x){
	for(int i=x;;i=fa[i]){stk[++top]=i;if(isrt(i))break;}
	while(top)pushdown(stk[top--]);
	while(!isrt(x)){
		int y=fa[x],z=fa[y];
		if(!isrt(y)){if((tr[z].s[1]==y)^(tr[y].s[1]==x))rotate(x);else rotate(y);}
		rotate(x);
	}
}
inline void access(int x){for(int y=0;x;x=fa[y=x])splay(x),tr[x].s[1]=y,pushup(x);}
inline void mkrt(int x){access(x);splay(x);tr[x].rev^=1;pushdown(x);}
inline int fdrt(int x){access(x);splay(x);pushdown(x);while(tr[x].s[0])pushdown(x=tr[x].s[0]);return x;}
inline void split(int x,int y){mkrt(x);access(y);splay(y);}
inline void link(int x,int y){mkrt(x);if(fdrt(y)!=x)fa[x]=y;}
inline void cut(int x,int y){split(x,y);if(fdrt(y)==x&&fa[x]==y&&tr[y].s[0]==x&&!tr[x].s[1])fa[x]=tr[y].s[0]=0,pushup(y);}
int n,m;
int pre(int x){
	if(!x)return 0;
	if(tr[x].s[0]){
		x=tr[x].s[0];
		while(tr[x].s[1])x=tr[x].s[1];
	}
	else{
		while(x){if(tr[fa[x]].s[1]==x)return fa[x];x=fa[x];}
	}
	return x;
}
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1,lst,op,x,y;i<=m;i++){
		scanf("%d%d%d",&op,&x,&y),op=1ll*op*(lst+1)%mod%2+1,x=1ll*x*(lst+1)%mod%n+1,y=1ll*y*(lst+1)%mod%n+1;
		if(op==1)link(x,y);
		else{
			if(fdrt(x)!=fdrt(y)){printf("%d\n",lst=0);continue;}
			mkrt(x);access(y);splay(y);fa[y]=0;
			int ans=pre(y);
			if(pre(ans)==x)printf("%d\n",lst=ans);
			else printf("%d\n",lst=0);
		}
	}
	return 0;
}
```

---

## 作者：CuteGirlGC (赞：0)

~~G 比 EF 简单（~~
## Solution

如果遇到查询 `1`，那么就加一条无向边。

如果遇到查询 `2`，那么让 $t_i$ 记录 $i$ 在 $b$ 中有没有出现过，然后遍历 $c$，如果同时出现了一个数，那么记录下来并直接退出循环。

对于加密的问题直接计算即可。

## Code
```cpp
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

const int kMaxN = 1e5 + 1;

int n, q;
ll a, b, c, x;
vector<int> g[kMaxN];

int main() {
  cin >> n >> q;
  for (q; q; q--) {
    cin >> a >> b >> c;
    int op = 1 + (a * (1 + x) % 998244353) % 2, u = 1 + (b * (1 + x) % 998244353) % n, v = 1 + (c * (1 + x) % 998244353) % n;
    if (op == 1) {
      g[u].push_back(v);
      g[v].push_back(u);
    } else {
      bool t[kMaxN] = {};
      int ans = 0;
      for (int i : g[u]) {
        t[i] = 1;
      }
      for (int i : g[v]) {
        if (t[i]) {
          ans = i;
          break;
        }
      }
      cout << ans << '\n';
      x = ans;
    }
  }
  return 0;
}
```

---

## 作者：Phartial (赞：0)

考虑用一个 LCT 维护这个森林结构，1 操作直接连边，2 操作先判连通块，再把路径 split 出来看点数是否为 $3$，最后维护一个异或和之类的东西就可以把中间的那个点求出来了。

$\mathcal{O}(n\log n)$。薄纱根号分治。

```cpp
#include <iostream>

using namespace std;

const int kN = 1e5 + 1;

struct LCT {
  struct E {
    int f, c[2];
    int s, x;
    bool tr;
  } e[kN];

  int W(int x) { return e[e[x].f].c[1] == x; }
  bool nR(int x) { return e[e[x].f].c[W(x)] == x; }
  void Pu(int x) {
    e[x].s = e[e[x].c[0]].s + e[e[x].c[1]].s + 1;
    e[x].x = (e[e[x].c[0]].x ^ e[e[x].c[1]].x ^ x);
  }
  void Pr(int x) { swap(e[x].c[0], e[x].c[1]), e[x].tr ^= 1; }
  void Pd(int x) { e[x].tr && (Pr(e[x].c[0]), Pr(e[x].c[1]), e[x].tr = 0); }
  void R(int x) {
    int y = e[x].f, z = e[y].f, w = W(x), k = e[x].c[w ^ 1];
    if (nR(y)) {
      e[z].c[W(y)] = x;
    }
    e[x].c[w ^ 1] = y, e[y].c[w] = k;
    if (k) {
      e[k].f = y;
    }
    e[y].f = x, e[x].f = z, Pu(y), Pu(x);
  }
  void S(int x) {
    static int s[kN];
    int t = 0, y = x;
    for (; nR(y); s[++t] = y, y = e[y].f) {
    }
    for (Pd(y); t; Pd(s[t--])) {
    }
    for (; nR(x); R(x)) {
      int y = e[x].f;
      if (nR(y)) {
        R(W(x) == W(y) ? y : x);
      }
    }
  }
  void A(int x) {
    for (int y = 0; x; y = x, x = e[x].f) {
      S(x), e[x].c[1] = y, Pu(x);
    }
  }
  void M(int x) { A(x), S(x), Pr(x); }
  void S(int x, int y) { M(x), A(y), S(y); }
  int F(int x) {
    for (A(x), S(x); e[x].c[0]; Pd(x), x = e[x].c[0]) {
    }
    S(x);
    return x;
  }
  void L(int x, int y) {
    M(x);
    if (F(y) == x) {
      return;
    }
    e[x].f = y;
  }
} t;
int n, q;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> q;
  for (int _a, _b, _c, _x = 0; q--;) {
    cin >> _a >> _b >> _c;
    int o = 1 + _a * (1LL + _x) % 998244353 % 2;
    int x = 1 + _b * (1LL + _x) % 998244353 % n;
    int y = 1 + _c * (1LL + _x) % 998244353 % n;
    if (o == 1) {
      t.L(x, y);
    } else {
      if (t.F(x) != t.F(y)) {
        cout << (_x = 0) << '\n';
      } else {
        t.S(x, y);
        if (t.e[y].s != 3) {
          cout << (_x = 0) << '\n';
        } else {
          cout << (_x = (t.e[y].x ^ x ^ y)) << '\n';
        }
      }
    }
  }
  return 0;
}
```

---

## 作者：N_Position (赞：0)

### AT_abc350_g
## 闲话
第一次 `solve F` 祭，差一点 `AK` 祭，第一次被卡空间祭，青名祭，`ABC` 最高 `rank` 祭，`ABC` 最高 `perf` 祭。
## 分析
我们首先忽略空间限制和时间限制去考虑。

若空间限制为 `1 GB`，显然可以用 `bitset` 实现，[代码实现](https://atcoder.jp/contests/abc350/submissions/52614416)。然后我们收获了 `MLE` 的好成绩。

若数据范围从 $1\times10^5$ 改为 $1\times10^3$ 显然用 `set` 可以 $O(QN\log n)$ 的时间复杂度通过。

我们发现第一种方法空间太大但时间很快，第二种方法在遇到度数很大的点时时间太慢，但遇到度数较小的点时的时间较快且空间较小。

考虑将点分为两种：度数大于 $\sqrt N$ 的点和度数小于 $\sqrt N$ 的点。

对于两个大的点，我们可以用 `bitset` 优化实现，否则单次暴力的时间复杂度仅为 $O(\sqrt N\log(\sqrt N))$。

较大的点最多只有 $\sqrt N$ 个，空间复杂度为 $O(N\sqrt N)$。

## 代码实现

空间复杂度为 $O(N\sqrt N)$，时间复杂度上界为 $O(Q\sqrt N\log(\sqrt N))$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
const int sqrtN = 400;
const int MOD = 998244353;
int n,q,last = 0;
bitset<N> e[sqrtN];
set<int> s[N];
int belong[N],cnt = 0,sqrtn;
void add(int u,int v){
	s[u].insert(v);
	s[v].insert(u);
	
	if(s[u].size() > sqrtn){
		if(belong[u] == 0){
			belong[u] = ++cnt;
			for(auto i=s[u].begin();i!=s[u].end();i++){
				e[belong[u]][*i] = 1;
			}
		}else{
			e[belong[u]][v] = 1;
		}
	}
	if(s[v].size() > sqrtn){
		if(belong[v] == 0){
			belong[v] = ++cnt;
			for(auto i=s[v].begin();i!=s[v].end();i++){
				e[belong[v]][*i] = 1;
			}
		}else{
			e[belong[v]][u] = 1;
		}
	}
}
int main(){
	scanf("%d%d",&n,&q);
	sqrtn = sqrt(n);
	for(int i=1;i<=q;i++){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		a = 1+((1ll*a*(1+last))%MOD)%2;
		b = 1+((1ll*b*(1+last))%MOD)%n;
		c = 1+((1ll*c*(1+last))%MOD)%n;
		if(a == 1){
			add(b,c);
		}else if(belong[b] && belong[c]){
			b = belong[b],c = belong[c];
			bitset<N> it = e[b] & e[c];
			if(it.count()){
				last = it._Find_first();
				printf("%d\n",last);
			}else{
				last = 0;
				puts("0");
			}
		}else{
			last = 0;
			if(s[c].size() < s[b].size()){
				swap(c,b);
			}
			for(auto i=s[b].begin();i!=s[b].end();i++){
				if(s[c].find(*i) != s[c].end()){
					last = *i;
					break;
				}
			}
			printf("%d\n",last);
		}
	}
}
```

---

## 作者：Starrykiller (赞：0)

钦定某个连通块以某个节点为根。设 $dep_u\ge dep_v$，我们发现询问答案为：

- 若 $u,v$ 不在一个连通块内，无解。
- 若 $dep_u=dep_v$ 且 $fa_u=fa_v$，则答案为 $fa_u$。
- 若 $dep_u=dep_v+2$ 且 $fa_{fa_u}=v$，则答案为 $fa_u$。
- 否则，无解。

第一种情况可以用并查集维护。

对于维护 $\texttt{father}$ 和 $\texttt{depth}$ 信息，受到 [P3302 [SDOI2013] 森林 ](https://www.luogu.com.cn/problem/P3302) 的启发，我们套路地考虑启发式合并。

具体地，合并 $(u,v)$ 时，我们不妨设 $siz_u\ge siz_v$，然后把 $v$ 作为树根接到 $u$ 上，dfs 子树 $v$ 来维护 $\texttt{father}$ 和 $\texttt{depth}$ 信息。

然后就做完了。时间复杂度 $\Theta(n\log n)$。

[My implementation](https://atcoder.jp/contests/abc350/submissions/52601311).

---

## 作者：Shadow_T (赞：0)

### 题目分析

$opt$，$u$，$v$ 是由题目给出的种子和上一次答案生成的，所以我们发现数据基本随机。

然后考虑暴力，我们用 vector 建图：

- 对于 $opt=1$：直接对 $u$ 和 $v$ 双向建图。

```cpp
g[u].push_back(v);
g[v].push_back(u);
```

- 对于 $opt=2$：我们暴力检索，先把 $u$ 连接的点在 bool 数组里标记一下，然后检索 $v$ 连接的点，如果在 bool 数组里标记过就输出。没有找到答案就是 $0$，注意记录答案，为后面生成答案做准备。

然后就这样过了（

### 代码

```cpp
// LUOGU_RID: 156573677
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
const int maxn=1e5+10;
vector<int> g[maxn];
bool mp[maxn];
signed main()
{
	int n,t;
	cin>>n>>t;
	int answer=0;
	while(t--)
	{
		long long a,b,c;
		scanf("%lld%lld%lld",&a,&b,&c);
		int opt=1ll+(((a*(1ll+answer))%mod)%2);
		int u=1ll+(((b*(1ll+answer))%mod)%n);
		int v=1ll+(((c*(1ll+answer))%mod)%n);
		if(opt==1)
		{
			g[u].push_back(v);
			g[v].push_back(u);
		}
		else
		{
			bool p=true;
			for(int i=0;i<g[u].size();i++)
			mp[g[u][i]]=true;
			for(int i=0;i<g[v].size();i++)
			if(mp[g[v][i]])
			{
				cout<<g[v][i]<<"\n";
				answer=g[v][i];
				p=false;
				break;
			}
			for(int i=0;i<g[u].size();i++)
			mp[g[u][i]]=false;
			if(p) answer=0,puts("0");
		}
	}
}
```

[洛谷通过记录](https://www.luogu.com.cn/record/156573677) | [Atcoder 通过记录](https://atcoder.jp/contests/abc350/submissions/52635331)。

---

