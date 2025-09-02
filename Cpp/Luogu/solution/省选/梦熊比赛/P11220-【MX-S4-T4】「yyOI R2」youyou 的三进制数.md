# 【MX-S4-T4】「yyOI R2」youyou 的三进制数

## 题目背景

原题链接：<https://oier.team/problems/S4D>。

## 题目描述

现在有 $0 \sim n$ 共 $n + 1$ 个数。
定义 $(x)_{3}$ 表示十进制数 $x$ 的三进制形式。**如果没有特别强调，那么这些数均为十进制形式。**

youyou 想构造一个序列长度为 $p$（$p \ge 1$）的非负整数序列 $a$。使之满足：

- $a_i \in [0,n]$。
- 不存在 $i,j$（$1 \le i <j \le p$），使得 $a_i = a_j$。
- 对于任意 $1 \le i < n$，$a_i$ 与 $a_{i+1}$ 至少满足以下四个条件中的一个：
  1. $(a_i)_3$ 去掉最后一位，恰好等于 $(a_{i+1})_3$（若只有一位，则去掉后的数字为 $0$）。
  2. 在 $(a_i)_3$ 末尾添上某一位 $t(0 \le t \le 2)$，恰好等于 $(a_{i+1})_3$（若 $a_i = 0$，则添加后舍去前置 $0$）。
  3. $a_i \le w$， $(a_i)_3$ 的末尾不是 $0$，且将末尾的一位数字移到开头与 $(a_{i + 1})_3$ 相等。
  4. 当 $(a_i)_3$ 长度 $\ge 2$，且 $(a_i)_3$ 次高位非零时，将 $(a_i)_3$ 开头的一位数字移到末尾，形成的数的十进制值 $\le w$，且恰好等于 $(a_{i+1})_3$。

这样的序列 $a$ 被称为“完美的”。

youyou 认为，如果十进制三元组 $(x,y,z)$ 是好的，必须满足以下条件：

- $0 \le x,y,z \le n$，$x \neq y$。
- 存在至少一个”完美的“序列 $b$，使得十进制下有 $b_1=x$，$b_s = y$。其中 $s$ 为序列长度。
- 存在至少一个”完美的”序列 $c$，使得十进制下有 $c_1=z$。同时，对于上述**任意的** $b$，均有**恰好**一对 $(i, j)$，满足 $1 \le i \le |b|$，$1 \le j \le |c|$，使得 $b_i = c_j$。

对于每一个 $0 \le z \le n$，求能构成“好的”三元组 $(x,y,z)$ 的有序对 $(x,y)$ 的个数。

## 说明/提示

**【样例解释 #1】**

一共有 $5$ 个数，用三进制表示分别为 $0,1,2,10,11$。

当 $z = 0,1,2,3,4$ 时，全部 $(x,y)(x \neq y)$ 数对均满足题意。

下面给出三元组 $(2,3,1)$ 是“好的”的证明。

当 $x=2,y=3,z=1$ 时，序列 $b$ 可以为 $\{2,0,1,3\}$。

其中 $b_1,b_2$ 满足条件 $1$，$b_2,b_3$ 满足条件 $2$，$b_3,b_4$ 满足条件 $2$。

可以证明只有这一个序列 $b$ 满足题意。因此，存在 $c = \{1\}$，使得 $B \cap C = \{1\}$。所以 $(2,3,1)$ 是“好的”三元组。

**【样例 #2】**

见附件中的 ```ternary/ternary2.in``` 与 ```ternary/ternary2.ans```。

该组样例满足测试点 $4\sim 6$ 的约束条件。

**【样例 #3】**

见附件中的 ```ternary/ternary3.in``` 与 ```ternary/ternary3.ans```。

该组样例满足测试点 $7\sim 10$ 的约束条件。

**【样例 #4】**

见附件中的 ```ternary/ternary4.in``` 与 ```ternary/ternary4.ans```。

该组样例满足测试点 $13\sim 15$ 的约束条件。

**【样例 #5】**

见附件中的 ```ternary/ternary5.in``` 与 ```ternary/ternary5.ans```。

该组样例满足测试点 $20\sim 25$ 的约束条件。

**【数据范围】**

本题共 $25$ 个测试点，每个 $4$ 分。

| 测试点编号 | $n$ | $w$ | 特殊性质
| :-----------: | :-----------: | :-----------: | :-----------: | 
| $1 \sim 3$ | $\le 18$ | $\le 18$ | 无
| $4 \sim 6$ | $\le 242$ | $\le 242$ |  无
| $7 \sim 10$ | $\le 6560$ | $\le6560$ |  无
| $11\sim12$ | $\le 10^5$ | $\le 10^5$ |  无
| $13\sim15$ | $\le 3 \times 10^5$ | $\le 10^5$ | 有 |
| $16\sim 17$ | $\le 3 \times 10^5$ | $=0$ | 无 |
| $18\sim 19$ | $\le 3 \times 10^5$ | $=n$ |  无 |
| $20\sim25$ | $\le 3 \times 10^5$ | $\le 3 \times 10^5$ |  无 |

特殊性质：$w \ge 10^4$。

对于全部数据，保证：$1\le n \le 3 \times 10^5$，$0 \le w \le n$。


## 样例 #1

### 输入

```
4 3```

### 输出

```
20
20
20
20
20```

# 题解

## 作者：_LSA_ (赞：10)

# P11220 【MX-S4-T4】「yyOI R2」youyou 的三进制数 题解
## 前言

给出一种实现起来较为容易的树上差分（换根 dp）的线性做法。

## 正文
首先我们观察题目给的四个性质，容易发现前两个性质是互逆的，后两个性质也是互逆的。

那我们考虑建图，将能够满足题目性质的一对数进行连边，连出来的就是无向边。

直接暴力建图是 $O(n)$ 的。

我们接下来考虑一个三元组 $(x,y,z)$ 什么时候是“好的”。

显然可以观察到的是，对于一个满足条件的 $b$ 序列，它一定对应着图上一条从 $x$ 到 $y$ 的简单路径。而对于 $c$ 序列，它对应着一条从 $z$ 开始的简单路径。

考虑最后一个条件：同时，对于上述**任意的** $b$，均有**恰好**一对 $(i, j)$，满足 $1 \le i \le |b|$，$1 \le j \le |c|$，使得 $b_i = c_j$。

对应到图上，这个条件就相当于需要存在**一条**从 $z$ 开始的简单路径，它根所有从 $x$ 到 $y$ 的简单路径有且仅有一个交点。

引理：对于一条确定的路径 $c$，它所有路径 $b$ 的交点必须是唯一的。

证明：
反证法，假设一条路径 $c$ 根两个不同的 $b$ 存在两个不同的交点 $i$ 和 $j$，不妨假设路径 $c$ 由 $z \to i \to j \to ed$ 构成，$b_1$ 为 $x \to i \to y$，$b_2$ 为 $x \to j \to y$，那么必然存在路径 $b_3$ 为 $x \to i \to j \to y$，它根路径 $c$ 存在两个交点，与题意矛盾，于是假设不成立。

根据引理，所有 $b$ 必须有同一交点，也就是说，这个交点是 $x$ 到 $y$ 的路径上的必经之点。这启示我们建出圆方树，那么这些必经之点就是树上 $x$ 到 $y$ 路径上的所有圆点（包括起点和终点）。接下来我们称这些点为**关键点**。

为了方便，我们定义一个点是**路径上的点**当且仅当存在一条从 $x$ 到 $y$ 的路径经过这个点。

那么对于一对 $(x,y)$，能对 $z$ 产生贡献当且仅当：

1. $z$ 是关键点；
2. $z$ 不是路径上的点，存在一条从 $z$ 开始的简单路径能在不经过任何其他路径上的点的情况下到达任意一个关键点。

对应到圆方树上，$z$ 要么是 $x$ 到 $y$ 路径上的圆点，要么是以其中任一圆点为根，这个圆点上的不包括 $x$ 和 $y$ 所在的子树的任意一个点。

画个图直观感受一下（比较粗糙，见谅）。

![](https://cdn.luogu.com.cn/upload/image_hosting/8g7x5zcc.png)

对于一对 $(x,y)$，图中用三角形框起来的子树（包括树根的圆点）都能得到贡献。

我们不妨以 $0$ 号节点为根，进行 dfs。

显然在方点上没有贡献，我们只需要考虑圆点。

令 $siz_x$ 表示圆方树上以 $x$ 为根子树的圆点数量。比如我们当前 dfs 到子树 $t$，我们类似换根 dp 的思路，把 $t$ 当作根，那么对于节点 $t$ 的两棵子树 $x$ 和 $y$，它会对其他所有除了这两棵子树内的点造成 $2\times siz_x\times siz_y$ 的贡献（包括 $t$ 子树外的点）。也就是对整棵树加上这个贡献，再对这两棵子树减去这个贡献，这个可以树上差分。


具体对于子树外的点的情况，由于对整棵树加贡献再对子树外的所有点减贡献等价于直接对整棵子树加贡献，所以这个树上差分是容易实现的。

于是这题便做完了，总时间复杂度 $O(n)$。

## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll read(){
	ll X = 0,r = 1;
	char ch = getchar();
	while(!isdigit(ch) && ch != '-') ch = getchar();
	if(ch == '-') r = -1,ch = getchar();
	while(isdigit(ch)) X = X*10+ch-'0',ch = getchar();
	return X*r;
}
const int N = 6e5+10;
int n,w,cnt;
vector<int> G[N],E[N];
int bas[N];
int dfn[N],low[N],stk[N],top,num;
void tarjan(int x,int ft){
	stk[++top] = x;
	low[x] = dfn[x] = ++num;
	for(int y : G[x]){
		if(y == ft) continue;
		if(!dfn[y]){
			tarjan(y,x);
			low[x] = min(low[x],low[y]);
			if(low[y] >= dfn[x]){
				cnt++;
				int z;
				do{
					z = stk[top--];
					E[cnt].push_back(z);
					E[z].push_back(cnt);
				}while(z != y);
				E[cnt].push_back(x);
				E[x].push_back(cnt);
			}
		}else low[x] = min(low[x],dfn[y]);
	}
}
ll siz[N],f[N];
void dfs(int x,int ft){
	siz[x] = x <= n;
	ll sum = 0;
	for(int y : E[x]){
		if(y == ft) continue;
		dfs(y,x);
		sum += siz[y]*siz[x];
		siz[x] += siz[y];
	}
	if(x <= n){
		for(int y : E[x]){
			if(y == ft) continue;
			f[y] -= (n+1-siz[y])*siz[y];
		}
		f[0] += sum;
		f[x] += siz[x]*(n+1-siz[x]);
	}
}
void dfs0(int x,int ft){
	for(int y : E[x]){
		if(y == ft) continue;
		f[y] += f[x];
		dfs0(y,x);
	}
}
int main(){
	n = read(); w = read();
	auto add_edge = [&](int x,int y){
		G[x].push_back(y);
		G[y].push_back(x);
	};
	for(int i=1;i<=n;i++) add_edge(i/3,i);
	bas[0] = 1;
	for(int i=1;i<=n;i++) bas[i] = bas[i/3]*3;
	for(int i=1;i<=w;i++){
		if(i % 3 == 0) continue;
		int x = i/3,y = i%3;
		x = bas[x]*y+x;
		if(x <= n) add_edge(x,i);
	}
	cnt = n;
	tarjan(0,0);
	dfs(0,0); dfs0(0,0);
	for(int i=0;i<=n;i++) cout << f[i]*2 << "\n";
    return 0;
}


```

---

## 作者：yukimianyan (赞：7)

## 题目描述
题目描述
## solution

发现题目中的四个条件，第一条和第二条是对称的，第三条和第四条仔细看也是对称的。结合下文需要固定序列的首项和末项，我们不难想到：构造一个 $n+1$ 个点的无向图，标号 $0\sim n$，其中点 $i$ 与 $3i, 3i+1, 3i+2$ 有边，$i\leq w$ 时还和“将 $i$ 末尾的一位数字移到开头”形成的数之间有边，注意以上点的标号如果超过 $n$ 则不用连。

则需要计数的对象可以转写为：对于 $(x, y, z)$，需要满足 $x, y$ 之间有一条简单路径（可以发现图是连通的，这样的路径必然存在），且存在一条从 $z$ 出发的路径，使得 $x, y$ 之间的任意简单路径都与这条路径有交，也就是说：存在一条从 $z$ 出发的路径，其上恰有一个点是任何 $x$ 到 $y$ 的简单路径的必经点，其余点都不能出现在任何 $x$ 到 $y$ 的简单路径上（容易发现这是充要的）。

不妨提取每个点双连通分量为一个方点带一堆圆点，建立圆方树。则又可以将计数对象转写为：**$x, y$ 在圆方树上的路径上离 $z$ 最近的点必须是一个圆点**。

由此可以尝试计算答案。记 $x, y$ 在圆方树上的路径上离 $z$ 最近的点为 $u$，在为圆点的 $u$ 上统计答案。枚举每条出边，计算删去这条出边指出的子树后有多少条路径经过 $u$，这些路径都能贡献到这棵子树中的所有点。可以求出 dfn 序，在 dfn 序上进行区间加，使用差分维护。计算路径条数则可以先计算全局有多少路径经过 $u$，枚举出边后再删去对应多算的路径。

至此本题可以在 $O(n\log n)$ 的时间复杂度内完成，瓶颈在建图（迫真）。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define link b426058e
#ifdef LOCAL
#define debug(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define endl "\n"
#define debug(...) void(0)
#endif
using LL = long long;
int n, w, tot, siz[600010], sz[600010];
basic_string<int> g[300010], t[600010];
void link(int u, int v) {
  if (++u != ++v) g[u] += v, g[v] += u, debug("%d %d\n", u, v);
}
int dfn[600010], low[300010], stk[300010], top, cnt;
void tarjan(int u) {// {{{
  dfn[u] = low[u] = ++cnt, stk[++top] = u;
  for (int v : g[u]) {
    if (dfn[v]) low[u] = min(low[u], dfn[v]);
    else {
      tarjan(v);
      low[u] = min(low[u], low[v]);
      if (low[v] >= dfn[u]) {
        int p = ++tot;
        t[p] += u, t[u] += p, debug("%d %d\n", u, p);
        do t[p] += stk[top], t[stk[top]] += p, debug("%d %d\n", p, stk[top]); while (stk[top--] != v); 
      }
    }
  }
}// }}}
LL c[600010];
void dfs(int u, int fa) {
  siz[u] = u <= n, dfn[u] = ++cnt, sz[u] = 1;
  for (int v : t[u]) if (v != fa) dfs(v, u), siz[u] += siz[v], sz[u] += sz[v];
  if (u <= n) {
    LL num = n;
    for (int v : t[u]) if (v != fa) num += 1ll * siz[v] * (n - siz[v]);
    int fsiz = n - siz[u];
    num += 1ll * fsiz * (n - fsiz);
    c[dfn[u]] += num, c[dfn[u] + 1] -= num;
    debug("ans[%d] += %lld\n", u, num);
    for (int v : t[u]) if (v != fa) {
      LL val = num - 2ll * siz[v] * (n - siz[v]);
      c[dfn[v]] += val, c[dfn[v] + sz[v]] -= val;
      debug("ans[subtree(%d)] += %lld\n", v, val);
    }
    LL fval = num - 2ll * fsiz * (n - fsiz);
    c[1] += fval, c[dfn[u]] -= fval, c[dfn[u] + sz[u]] += fval;
    debug("ans[!subtree(%d)] += %lld\n", u, fval);
  }
}
int main() {
#ifndef LOCAL
#ifdef NF
  freopen("ternary.in", "r", stdin);
  freopen("ternary.out", "w", stdout);
#endif
  cin.tie(nullptr)->sync_with_stdio(false);
#endif
  cin >> n >> w;
  for (int i = 0; i <= n; i++) {
    link(i, i / 3);
    if (i % 3 && i <= w) {
      vector<int> dit;
      for (int x = i; x; x /= 3) dit.push_back(x % 3);
      int x = 0;
      x = x * 3 + dit[0];
      for (int i = (int)dit.size() - 1; i >= 1; i--) x = x * 3 + dit[i];
      if (x <= n) link(i, x);
    }
  }
  debug("===\n");
  tot = ++n, tarjan(1), cnt = 0, dfs(1, 0);
  for (int i = 1; i <= cnt; i++) c[i] += c[i - 1];
  for (int i = 1; i <= n; i++) cout << c[dfn[i]] - n << endl;
  return 0;
}
```

---

## 作者：xieziheng (赞：6)

被诈骗的彻头彻尾。。。

赛时被 T1T2T3 的表象大大的诈骗了，以为这题也是观察性质。于是什么都没注意到。真给我唐完了。

发现条件就是一坨屎。如果你去分析条件的性质，就真的输了。

考虑转化，注意到条件是对称的，所以建图出来是个无向图。序列就是选一条简单路径。

等价于对每个点 $z$，算多少个点对 $x,y$ 满足任意经过 $x,y$ 的路径都与某一条固定的以 $z$ 为端点的简单路径交为 $1$。

这显然很圆方树。

然后开始陶。继续刻画充要条件。以下都在圆方树上讨论。

1. 如果 $z$ 是 $x,y$ 路径上的圆点。显然可以。

2. 如果 $z$ 在 $x,y$ 路径上的某个点双上，也就是挂在 $x,y$ 路径上的一个方点上，不可以。

3. 根据 $2$，进一步发现，对于任意的 $z$，使得 $z$ 到路径 $x,y$ 的路径上的最后一个点（在 $x,y$ 路径上，下文称之为关键点）如果是方点，就一定不行，因为不能保证交唯一。

4. 同理得到，如果关键点是圆点，就一定可以。

考虑如何计算答案，先把有序变无序，最后乘个二。

然后考虑对关键点算其对别点的贡献。算出每个点各个子树内的圆点数量。

不妨 $x,y,z$ 互不相同，相同的话答案加 $n$ 即可。

对于关键点 $u$，我们有 $x,y,z$ 一定不在其同一个子树中。所以算一下其他子树（$u$ 子树外的也是）的形如 $\sum_{x} \sum_{y\neq x} s_xs_y$ 的贡献即可，$x,y$ 指 $u$ 的儿子（$u$ 的父亲也算），$s_x$ 表示 $x$ 子树内圆点个数。就做完了，复杂度 $\mathcal{O}(n)$。

不知道官方题解说的什么换根 dp 是啥意思。。。这不是很好写吗。

```cpp
#include <bits/stdc++.h>
#define il inline
using namespace std;
typedef long long ll;
const int N=3e5+5;
int n,m,lg[N],pw[20];
int sum[N<<1],df[N<<1],tot,id[N<<1],siz[N<<1],fa[N<<1];ll ans[N],s[N<<1];
il int to(int x){
    if(!(x%3) || x>m) return -1;
    return (x/3)+(x%3)*pw[lg[x]];
}
int dfn[N],low[N],cnt,st[N],top,bel[N],idx;
vector<int> e[N],g[N<<1];
il void adde(int x,int y,vector<int> e[]){e[x].push_back(y),e[y].push_back(x);}
void tarjan(int x,int fath){
    int y,z;dfn[x]=low[x]=++cnt,st[++top]=x;
    for(int y:e[x]){
        if(y==fath) continue;
        if(!dfn[y]){
            tarjan(y,x),low[x]=min(low[x],low[y]);
            if(low[y]>=dfn[x]){
                ++idx,adde(idx+n,x,g);
                do{
                    z=st[top--],bel[z]=idx,adde(idx+n,z,g);
                }while(z!=y);
            }
        }
        else low[x]=min(low[x],dfn[y]);
    }
}
il void add(int x,ll w){s[df[x]]+=w,s[df[x]+siz[x]]-=w;}
void dfs0(int x,int fath){
    int y,z;fa[x]=fath,df[x]=++tot,id[tot]=x,sum[x]=(x<=n),siz[x]=1;
    for(int y:g[x]) if(y!=fath) dfs0(y,x),sum[x]+=sum[y],siz[x]+=siz[y];
}
void dfs(int x,int fath){
    int y,z;ll u,v,w,s1=0,s2=0;
    for(int y:g[x]) if(y!=fath) dfs(y,x);
    if(x>n) return ;
    s1=0;for(int y:g[x]) if(y!=fath) s1+=1ll*sum[y],s2+=1ll*sum[y]*sum[y];
    w=(s1+1ll)*(s1+1ll)-(s2+1ll),w>>=1;
    s[1]+=w,s[df[x]]-=w,s[df[x]+siz[x]]+=w;
    s2+=1ll*(n-s1)*(n-s1),++s2;ans[x]+=((n+1ll)*(n+1ll)-s2)/2;
    for(int y:g[x]) if(y!=fath) w=(n+1ll-sum[y])*(n+1ll-sum[y])-(s2-1ll*sum[y]*sum[y]),w>>=1,add(y,w);

}
int x,y,z;ll u,v,w;
int main(){
    scanf("%d%d",&n,&m);
    pw[0]=1;for(int i=1;i<=12;++i) pw[i]=pw[i-1]*3;
    for(int i=3;i<=n;++i) lg[i]=lg[i/3]+1;
    for(int i=1;i<=n;++i){
        adde(i,i/3,e),x=to(i);
        if(x>0 && i!=x && x<=n) adde(i,x,e);
    }
    tarjan(0,-1);
    dfs0(0,-1),dfs(0,-1);
    for(int i=1;i<=tot;++i) s[i]+=s[i-1];
    for(int i=1;i<=tot;++i){
        x=id[i];if(x<=n) ans[x]+=s[i];
    }
    for(int i=0;i<=n;++i) printf("%lld\n",ans[i]*2ll);
    return 0;
}

```

---

## 作者：Heptagon18 (赞：3)

## Description
[原题链接](https://www.luogu.com.cn/problem/P11220)。

[更好的浏览体验](https://www.luogu.com.cn/article/fukmqcf0)。

-----

## Solution

题目给出了“$n$ 最大为 $3\times10^5$”这个重要信息。

发现 $3\times10^5$ 的三进制表示只有 $12$ 位，考虑如何运用这个信息。

考虑建图。

发现题目所述与圆方树的性质很像，用 tarjan 跑出圆方树。

思考需要在圆方树上维护什么信息。

对于每个点，我们维护以下三个信息：

- $sum_t$ 表示若有一条以节点 $t$ 为结尾的序列 $c$，它的总贡献。

- $ssum_t$ 表示对于以节点 $t$ 为根的**整棵子树的总贡献**。

- $sumson_t$ 表示对于节点 $t$ 的所有儿子，它们的 $ssum$ 之和。

维护 $sumson$ 数组是容易的，考虑如何维护 $sum$ 数组和 $ssum$ 数组。

对 $sum_t$ 有贡献的情况可以分为两种：

- 有一条以 $t$ 为端点的路径，贡献为 $size_t\times2$。
- 有一条以 $t$ 为 $lca$ 的路径，贡献为 $\sum_{i=1}^d (size_t-size_{son_i}-1)\times size_i$，其中 $d$ 为 $t$ 儿子的数量。

考虑计算 $ssum_t$：

- 如果 $t$ 为圆点，那么 $t$ 点的所有儿子对其都有贡献，$ssum_t=(\sum_{i=1}^d ssum_{son_i})+sum_t$。

- 如果 $t$ 为方点，那么位于同一个点双内的点均无贡献，$ssum_t=(\sum_{i=1}^d sumson_{son_i})+sum_t$。

预处理是 $O(n)$ 的，考虑计算答案。

由于这棵树的高度较低（本题中不会超过 $23$），考虑对每一个圆点暴力往上跳，计算答案。

对于当前跳到的点，我们考虑两部分的贡献：

- 当前点的贡献。
- 兄弟节点的贡献。

有了预处理好的数组，这部分的计算是容易的。

总时间复杂度 $O(n\log_3n)$，可以通过本题。

这个做法的常数较小，还有一个 $O(n)$ 的换根 dp 做法，实现起来较为复杂，常数较大。

std 是 $O(n\log_3 n)$ 的。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

namespace fastio {
const int MAXBUF = 1 << 23;
char buf[MAXBUF], *p1 = buf, *p2 = buf;
char pbuf[MAXBUF], *pp = pbuf;
inline char getc() { return (p1 == p2) && (p2 = (p1 = buf) + fread(buf, 1, MAXBUF, stdin)), p1 == p2 ? EOF : *p1++; }
inline void putc(char c) { (pp == pbuf + MAXBUF) && (fwrite(pbuf, 1, MAXBUF, stdout), pp = pbuf), *pp++ = c; }
inline void print_final() { fwrite(pbuf, 1, pp - pbuf, stdout), pp = pbuf; }
} // namespace fastio
using fastio::getc; using fastio::putc; using fastio::print_final;
template <class _Tp>
inline _Tp& read(_Tp& x) {
  bool sign = 0;
  char ch = getc();
  for (; !isdigit(ch); ch = getc()) sign |= (ch == '-');
  for (x = 0; isdigit(ch); ch = getc()) x = x * 10 + (ch ^ 48);
  return sign ? (x = -x) : x;
}
template <class _Tp>
inline void write(_Tp x) {
  if (x > 9) write(x / 10);
  putc((x % 10) ^ 48);
}

int n,w,cnt;
vector<int> G[300005],T[600005];
int dfn[600005],low[600005],dfc;
int stk[600005],tp;

void tarjan(int u)
{
    low[u]=dfn[u]=++dfc;               
    stk[++tp]=u;                         
    for(int v:G[u])
    {                   
        if(!dfn[v])
        {                      
            tarjan(v);                       
            low[u]=min(low[u],low[v]); 
            if (low[v]==dfn[u])
            {  
                ++cnt;     
                for(int x=0;x!=v;--tp)
                {
                    x=stk[tp];
                    T[cnt].push_back(x);
                    T[x].push_back(cnt);
                }
                T[cnt].push_back(u);
                T[u].push_back(cnt);
            }
        }
        else low[u]=min(low[u],dfn[v]); 
    }
}

int siz[600005];
int fa[600005];
int sum[600005];
int ssum[600005];
int sumson[600005];
int dep[600005];

void dfs(int t,int pr)
{
    if(t>n) siz[t]=0;
    else siz[t]=1;
    dep[t]=dep[pr]+1;
    fa[t]=pr;
    for(int to:T[t])
    {
        if(to==pr) continue;
        dfs(to,t);
        siz[t]+=siz[to];
    }
}

void dfs2(int t,int pr)
{
    int d=siz[t];
    if(t<=n)
    {
        sum[t]+=(siz[t]-1)*2;
        d--;
    }
    for(int to:T[t])
    {
        if(to==pr) continue;
        sum[t]+=(d-siz[to])*siz[to];
        dfs2(to,t);
        if(to<=n) ssum[t]+=ssum[to];
        else ssum[t]+=sumson[to];
        sumson[t]+=ssum[to];
    }
    ssum[t]+=sum[t];
}

int Len(int t)
{
    int cnt=0;
    while(t)
    {
        cnt++;
        t/=3;
    }
    return cnt;
}

void work(int t)
{
    int u=n+1-siz[t];
    int p=siz[t]-1;
    int ans=u*p*2+u*2;
    ans+=ssum[t];
    int pr=t;
    int nw=fa[t];
    while(pr!=nw)
    {
        int d1=n+1-siz[nw];
        int d2=siz[nw]-(nw<=n)-siz[pr];
        if(nw<=n) ans+=d1*d2*2;
        if(nw<=n) ans+=d1*2;
        ans+=sumson[nw]-ssum[pr];
        if(nw<=n) ans+=sum[nw]-(siz[nw]-1)*2-(siz[pr]*(siz[nw]-siz[pr]-1))*2;
        if(nw<=n) ans+=(siz[nw]-siz[pr]-1)*2;
        pr=nw;
        nw=fa[nw];
    }
    write(ans);
    putc('\n');
}

signed main()
{
    read(n);
    read(w);
    cnt=n;
    int pre=1;
    for(int i=1;i<=n;i++)
    {
        G[i].push_back(i/3);
        G[i/3].push_back(i);
        if(i<=w)
        {
            int u=i%3;
            int d=i/3;
            int op=Len(i);
            int kl=pow(3,op-1)*u+d;
            if(kl>n) continue;
            if(kl/3==i||i/3==kl) continue;
            if(kl==i) continue;
            G[i].push_back(kl);
            G[kl].push_back(i);
        }
    }
    int opu=0;
    tarjan(opu);
    dfs(opu,opu);
    dfs2(opu,opu);
    for(int i=0;i<=n;i++)
    {
        work(i);
    }
    print_final();
    return 0;
}
```

---

## 作者：729hao (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P11220)

CSP 考前三天写篇题解攒攒 rp。

---
以下的“路径”均指简单路径。
## 铺垫
这段内容为我如何想到用圆方树的，想到圆方树的可以跳过。

读题，发现操作 $1$ $2$、$3$ $4$ 互逆，所以整道题可视作一个有 $n+1$ 个无向连通图。（操作 $1$ $2$ 所连的边构成了一颗树）

那么原题中“完美的”序列就是图上的一条简单路径。

对于题目中这一条：
> 存在至少一个”完美的”序列 $c$，使得十进制下有 $c_1=z$。同时，对于上述**任意的** $b$，均有**恰好**一对 $(i, j)$，满足 $1 \le i \le |b|$，$1 \le j \le |c|$，使得 $b_i = c_j$。

不妨钦定 $j=|c|$，即这个相同的数就是 $c$ 最后一个数。可以证明这样统计师不重不漏的。

于是问题就转化成了：
> 对于图上的每个点 $i$，满足以下条件的三元组 $(x,y,z)$ 的个数：
>> $x\ne y$，且对于所有 $x$ $y$ 之间经过 $z$ 的路径，不存在 $i$ $z$ 之间的路径，与这条路径有除了 $z$ 以外的公共点。

于是考虑圆方树。

## 思路
将图转成圆方树之后，问题变为：
> 对于树上的每个圆点 $i$，满足以下条件的三元组 $(x,y,z)$ 的个数：
>> $x\ne y$，$x$ $y$ 之间的路径经过 $z$，且这条路径与 $i$ $z$ 之间的路径不存在除了 $z$ 以外的公共点。

那么对于每个 $i(i\in [0,n])$，在求解其答案时，先将其置为根，枚举 $z$ ，可以发现此时满足情况的 $(x,y)$ 的充要条件是 $x$、$y$ 分别位于 $z$ 的不同子树或者其中有一个点就是 $z$。

求 $(x,y)$ 的数量可以在遍历时顺带求出，于是我们有了 $O(N^2)$ 做法。

降低复杂度的话，因为对于每个 $z$，如果其子树的形态不变的话，它的贡献是不变的，所以可以换根。

## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace cs{
	#define LL long long
	const int N=3e5;
	int n,w;
	vector<int>v[N+5],bf[2*N+5];
	int dfn[N+5],low[N+5],cnt,bcc;
	stack<int>st;
	void tarjan(int rt,int prt){
		int y;
		dfn[rt]=low[rt]=++cnt;
		st.push(rt);
		for(auto u:v[rt]){
			if(!dfn[u]){
				tarjan(u,rt);
				if(low[u]>=dfn[rt]){
					bcc++;
					do{
						y=st.top();
						st.pop();
						bf[y].push_back(bcc+n);
						bf[bcc+n].push_back(y);
					}while(y!=u);
					bf[rt].push_back(bcc+n);
					bf[bcc+n].push_back(rt);
				}
				else low[rt]=min(low[rt],low[u]);
			}
			else if(u!=prt)low[rt]=min(low[rt],dfn[u]);
		}
	}
	LL ans[2*N+5],real_ans[2*N+5],nowans;
	int siz[2*N+5];
	void dfs(int rt,int prt){
		if(rt<=n)siz[rt]=1;
		else siz[rt]=0;
		for(auto u:bf[rt]){
			if(u==prt)continue;
			dfs(u,rt);
			ans[rt]+=siz[rt]*1ll*siz[u];
			siz[rt]+=siz[u];
		}
		if(rt<=n)nowans+=ans[rt];
	}
	void DP(int rt,int prt){
		real_ans[rt]=nowans;
		int osiz=siz[rt],uosiz;
		LL oans=ans[rt],uoans;
		if(rt<=n)nowans-=oans;
		for(auto u:bf[rt]){
			if(u==prt)continue;
			uosiz=siz[u];
			uoans=ans[u];
			if(u<=n)nowans-=uoans;
			siz[rt]=n+1-siz[u];
			ans[rt]=oans-siz[rt]*1ll*siz[u];
			ans[u]+=siz[u]*1ll*(n+1-siz[u]);
			siz[u]=n+1;
			if(rt<=n)nowans+=ans[rt];
			else nowans+=ans[u];
			DP(u,rt);
			if(rt<=n)nowans-=ans[rt];
			else nowans-=ans[u];
			siz[u]=uosiz;
			ans[u]=uoans;
			if(u<=n)nowans+=uoans;
		}
		if(rt<=n)nowans+=oans;
		siz[rt]=osiz;ans[rt]=oans;
	}
	int main(){
		ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
		cin>>n>>w;
		int x,y,f;
		for(int i=0;i<=w;i++){
			v[i].push_back(i/3);
			v[i/3].push_back(i);
			x=i%3;
			if(x!=0){
				f=1;
				y=i/3;
				while(y){
					y/=3;
					f*=3;
				}
				y=i/3+x*f;
				if(y<=n){
					v[i].push_back(y);
					v[y].push_back(i);
				}
			}
		}
		for(int i=w+1;i<=n;i++){
			v[i].push_back(i/3);
			v[i/3].push_back(i);
		}
		tarjan(0,-1);
		dfs(0,-1);
		DP(0,-1);
		for(int i=0;i<=n;i++){
			cout<<real_ans[i]*2<<"\n";
		}
		return 0;
	}
}
int main(){
	cs::main();
	return 0;
}
```

---

## 作者：Sky_Maths (赞：1)

本文证明可能较为冗长，当做抛砖引玉，希望有更简单的证法。

考虑有 4 种操作，发现 1 和 2，3 和 4 互为相反操作。

想到转换成图上问题，就可以解决这道题。

建图方式：若 $x$ 和 $y$ 可以相互转化，则在 $x, y$ 之间连边。

**发现完美序列和得到的图上的一条不经过重复点的路径（简单路径）等价。** 

那么对于 $(x, y)$，任意连接 $x, y$ 的简单路径都是一个完美序列 $b$。

令所有 $b$ 都要经过的点为“关键点”，可能经过的点为“可能点”。有一个点双圆方树的基础结论，若建出点双圆方树，则关键点就是 $x, y$ 上的圆点，而“可能点”就是与 $(x, y)$ 上的方点相邻的非圆点。

对于一个 $z$，$(x, y, z)$ 是一个“好的”三元组（即存在 $c$）等价于在图上存在一条以 $z$ 为起点的简单路径 $c = z,\dots, t$，使 $t$ 是 $c$ 中唯一关键点且不经过“可能点”。

证明：
1. 若没有关键点和可能点，显然不行。
2. 若只有一个可能点，可以不经过。
3. 同时存在一个关键点和可能点，或两个处于不同点双内的可能点，则一定存在一个 $b$ 同时经过这两个点，多余的只要选两个即可
4. 若有两个可能点，且不能选出一条路径不经过任何被选的点，则选取两条除关键点外不相交的路径，设为 $p_1,p_2$，经过的可能点为 $u_1, u_2$，因为 $u_1\to u_2$ 中有一条完全由可能点构成的路径（$c$ 走过的），那么可以从 $x$ 沿 $p_1$ 走到 $u_1$，从 $u_1$ 沿 $c$ 走到 $u_2$，再从 $u_2$ 沿 $p_2$ 走到 $y$，这是一条经过了至少两个可能点的简单路径。

那么在圆方树上考虑对于一对 $(x, y)$ 不会对哪些 $z$ 产生贡献，即和 $(x, y)$ 的最近公共点在方点上的。

可以想到对于每个方点，对于其每个 $subtree(v)$，整体减去其作为最近相同点的方案数（即在其余的子树中任选两个属于不同子树的点作为 $(x, y)$ 的方案数），可以简单算，具体就是在除 $v$ 子树外任选两个的方案减去选到同一个子树的方案。

时间复杂度 $\mathcal O(n\log n)$，瓶颈在建边，应该可以做到 $\mathcal O(n)$。

## 代码
```cpp
const int N = 3e5 + 9;

int n, w, tp, dfc, scc;
int dfn[N], low[N], sta[N], sz[N * 2], fa[N * 2];
LL sum[N * 2], ans[N * 2];
vector <int> G[N], T[N * 2];

void adde(int u, int v) { G[u].EB(v), G[v].EB(u);}

void tarjan(int u) {
    low[u] = dfn[u] = ++dfc;
    sta[++tp] = u;
    for (int v : G[u]) {
        if (!dfn[v]) {
            tarjan(v);
            cmin(low[u], low[v]);
            if (low[v] == dfn[u]) {
                ++scc;
                for (int x = 0; x != v; --tp) {
                    x = sta[tp];
                    T[scc].EB(x);
                    T[x].EB(scc);
                }
                T[scc].EB(u), T[u].EB(scc);
            }
        } else {
            cmin(low[u], dfn[v]);
        }
    }
}

void add(int u, int v, LL var) {
    // u->v 的 v 子树加
    // printf("    u = %d, v = %d, var = %lld\n", u, v, var);

    if (fa[u] == v) sum[0] += var, sum[u] -= var;
    else sum[v] += var;
}

void dfs1(int u, int lst = -1) {
    fa[u] = lst;
    for (int v : T[u]) if (v != lst) {
        // printf("    %d -> %d\n", u, v);

        dfs1(v, u);
        sz[u] += sz[v];
    }
}

vector <int> vec;

void dfs2(int u, int lst = -1) {
    for (int v : T[u]) if (v != lst) {
        dfs2(v, u);
    }

    if (u <= n) return ;

    vector <int> ().swap(vec);
    for (int v : T[u]) if (v != lst) {
        vec.EB(sz[v]);
    }
    vec.EB(n + 1 - sz[u]);

    // printf("    u = %d, sz = ", u); for (int v : vec) printf("%d, ", v); printf("\n");

    LL sum = 0;
    for (int s : vec) sum = sum + 1ll * s * (s - 1);

    for (int v : T[u]) if (v != lst) {
        add(u, v, 1ll * (n + 1 - sz[v]) * (n + 1 - sz[v] - 1) - sum + 1ll * sz[v] * (sz[v] - 1));
    }
    add(u, lst, 1ll * sz[u] * (sz[u] - 1) - sum + 1ll * (n + 1 - sz[u]) * (n + 1 - sz[u] - 1));
}

void dfs3(int u, int lst = -1) {
    for (int v : T[u]) if (v != lst) {
        sum[v] += sum[u];
        dfs3(v, u);
    }
}

void skymaths() {
    read(n, w);
    rep (i, 1, n) {
        adde(i / 3, i);
    }
    rep (x, 0, w) {
        if (x % 3 == 0) continue;
        int _ = x % 3; int ret = x / 3;
        // while (_ <= ret) _ *= 3;
        // 注意不能这么写，因为这样有可能 ret 最高位为 1 但是 _ = 2/lh
        while (ret) ret /= 3, _ *= 3;
        int y = x / 3 + _;
        if (y <= n) {
            adde(x, y);
        }
    }

    dfc = 0, scc = n;
    tarjan(0);

    rep (i, 0, n) sz[i] = 1;
    dfs1(0);
    dfs2(0);
    dfs3(0);

    rep (z, 0, n) {
        ans[z] = 1ll * (n + 1) * n - sum[z];
    }

    rep (z, 0, n) {
        write(ans[z]);
    }
}
```

---

## 作者：dream10 (赞：0)

### 题意简述

简单讲讲我是怎么看错题的 


- $0 \le x,y,z \le n$，$x \neq y$。
- 存在至少一个”完美的“序列 $b$，使得十进制下有 $b_1=x$，$b_s = y$。其中 $s$ 为序列长度。
- 存在至少一个”完美的”序列 $c$，使得十进制下有 $c_1=z$。同时，对于上述**任意的** $b$，均有**恰好**一对 $(i, j)$，满足 $1 \le i \le |b|$，$1 \le j \le |c|$，使得 $b_i = c_j$。

我看成对于任何一个 $b$ 序列，都有这么一个 $c$ 序列存在。实际上，应该是存在一个 $c$ 序列，对于任何一个 $b$ 成立。 

$\forall b \ \exist c \neq \exist c \ \forall b$。

题意请看[链接](https://www.luogu.com.cn/problem/P11220)。

### 题意转换

对于这四种操作，$1,2$ 互为逆操作，$3,4$ 互为逆操作，出现的数又是 $O(n)$ 的级别，想到建图，点数为 $n+1$，边数 $O(n)$。这时候一个完美的序列，就是图上的一条简单路径（点不重复）。对于每个 $z$ ，要求有一条从它开始的路径 $c$，有多少个有序 $(x,y)$ 使得 $x$ 到 $y$ 的任何一条路径 $b$ 都和路径 $c$ 有恰好一个交点。

### 解决问题

思考固定 $x,y$ 的情形，由于是点的联通性问题，所以先点双缩点，建立一颗圆方树。然后发现有一些必经的原点和方点。一个点双里不是割点的点总是可以有一条路径不经过的。如果 $z$ 是这个路径上的圆点，那么只有 $z$ 的序列条件就满足；如果是 $z$ 在经过方点连出去的某个圆点上，那么如果 $z$ 在这个点双里的路径 $c$ 长度大于 $1$ 则显然存在序列 $b$ 可以与其完全重合。然而长度为 $1$ 时又可以绕开，所以不可能。另外的情况就是 $z$ 不在这个路径周围，但是可以延伸出来一个路径到这个 $b$ 路径上的一个必经圆点。

然后将思维反向，因为题目让我们固定 $z$。把 $z$ 放到圆方树上，这时候应该是分类讨论：

- z 是 $b$ 路径的端点，贡献 $2n$。
- z 是 $b$ 路径上的必经点，这时候需要利用和的平方公式计算，略。
- z 延伸出去是 $b$ 路径的端点，那么可以对这个进行换根处理。
- z 延伸出去是 $b$ 路径的一个必经圆点，那么既需要用换根，也要用和的平方公式。

$(x_1+x_2+ \dots +x_n)^2-x_1^2-x_2^2-...x_n^2=2\sum_{1\leq i < j 
\leq n}x_ix_j$

代码应该蛮清晰的，见后，有注释。

### 总结

此题最新颖的在于图论模型的隐藏，这启发我们要善于建立模型，理解图的本质。然后就是发现性质，关注联通性，使用控制变量法。直播讲解的时候讲了一个 $O(n \log_3 n)$ 的做法，这里就是 $Bonus$ 的换根 $O(n)$。我认为换根非常考验能力，反正我调了很久，所以附上标程。


```cpp
#include<bits/stdc++.h>
using namespace std;

int n,W;
const int MAXN=300010;
int h[MAXN];
struct Edge{
    int ne,to;
}e[MAXN*5];int eid;
void add(int x,int y){
    if(x==y)return;
    // printf("%d %d\n",x,y);
    e[eid].ne=h[x],e[eid].to=y,h[x]=eid++;
}
int a[30];int len;
int pw3[30];
int dfn[MAXN],low[MAXN],dfc,stk[MAXN],tp;
vector<int> c[MAXN];//一个点所属于的点双
int num;//点双编号
int w[MAXN<<1];
void tarjan(int x){
    dfn[x]=low[x]=++dfc;
    stk[++tp]=x;
    for(int i=h[x];~i;i=e[i].ne){
        int y=e[i].to;
        if(!dfn[y]){
            // if(x==0){
            //     printf("yy %d\n",y);
            // }
            tarjan(y);
            low[x]=min(low[x],low[y]);
            if(low[y]==dfn[x]){
                ++num;
                do{
                    w[num]++;
                    c[stk[tp]].emplace_back(num);
                    tp--;
                }while(stk[tp+1]!=y);
                c[x].emplace_back(num);
            }
        }
        else low[x]=min(low[x],dfn[y]);
    }
}
vector<int> G[MAXN<<1];
/*
siz 子树内圆点个数
f 子树内每个圆点的 siz-1 之和
g 换根之下的 f
p 选子树的两个不同圆点，在不同的儿子子树的方案
q 子树圆点的 p 之和
q2 换根之下的 q 
*/
typedef long long ll;
ll ans[MAXN<<1],siz[MAXN<<1];
ll f[MAXN<<1],g[MAXN<<1],p[MAXN<<1],q[MAXN<<1],q2[MAXN<<1];
void dfs1(int x,int Fa){
    f[x]=g[x]=p[x]=q[x]=q2[x]=0;
    siz[x]=x<=n;
    for(auto y:G[x]){
        if(y==Fa)continue;
        dfs1(y,x);
        siz[x]+=siz[y];
        f[x]+=f[y];
        q[x]+=q[y];
        if(x<=n)p[x]-=(ll)(siz[y])*(siz[y]);
    }
    if(x<=n){
        p[x]+=(ll)(siz[x]-1)*(siz[x]-1);
        q[x]+=p[x];
        f[x]+=siz[x]-1;
    }
}
void dfs2(int x,int Fa){
    ll sum=0,sum2=0;
    for(auto y:G[x]){
        if(y==Fa)continue;
        sum+=f[y];
        sum2+=q[y];
    }
    for(auto y:G[x]){
        if(y==Fa)continue;
        if(x<=n){
            g[y]=g[x]+sum-f[y]+n+1-siz[y]-1;
            q2[y]=q2[x]+sum2-q[y]
                +p[x]-(ll)(siz[x]-1)*(siz[x]-1)+(ll)(n+1-siz[y]-1)*(n+1-siz[y]-1)+(ll)siz[y]*siz[y]-(ll)(n+1-siz[x])*(n+1-siz[x]);
        }else{
            g[y]=g[x]+sum-f[y];
            q2[y]=q2[x]+sum2-q[y];
        }
        dfs2(y,x);
    }
}
void dfs3(int x,int Fa){
    ans[x]=2*(n+1-1);
    ans[x]+=(ll)(n+1-1)*(n+1-1);
    for(auto y:G[x]){
        if(y==Fa)continue;
        dfs3(y,x);
        ans[x]-=(ll)siz[y]*siz[y];
        ans[x]+=f[y]*2;
        ans[x]+=q[y];
    }
    ans[x]-=(ll)(n+1-siz[x])*(n+1-siz[x]);
    ans[x]+=g[x]*2;
    ans[x]+=q2[x];
}
signed main(){
    // freopen("ternary4.in","r",stdin);
    // freopen("ternary.out","w",stdout);
    cin>>n>>W;
    memset(h,-1,sizeof h);
    pw3[0]=1;for(int i=1;i<=20;++i)pw3[i]=pw3[i-1]*3;
    for(int i=0;i<=n;++i){
        if(i*3+0<=n)add(i,i*3+0);
        if(i*3+1<=n)add(i,i*3+1);
        if(i*3+2<=n)add(i,i*3+2);
        add(i,i/3);
        int j=i;len=0;
        while(j){a[++len]=j%3;j/=3;}
        if(i<=W&&a[1]>0){
            int y=i/3+a[1]*pw3[len-1];
            if(y<=n)add(i,i/3+a[1]*pw3[len-1]);
        }
        if(len>=2&&a[len-1]>0){
            int y=(i-a[len]*pw3[len-1])*3+a[len];
            if(y<=W)add(i,y);
        }
    }
    num=n;
    for(int i=0;i<=n;++i)
        if(!dfn[i])tp=0,tarjan(i);
    for(int i=0;i<=n;++i)
        if(c[i].size()>0)
            for(auto j:c[i]){
                G[i].emplace_back(j);
                G[j].emplace_back(i);
            }
    dfs1(0,-1);
    dfs2(0,-1);
    dfs3(0,-1);
    for(int i=0;i<=n;++i)printf("%lld\n",ans[i]);
    return 0;
}

```


### 结语

本人能力有限，如果题解有纰漏，错误或者不足之处，欢迎私信我指正。祝各位 CSP rp++，望审核通过。

---

## 作者：Corzica (赞：0)

“完美”序列实际上描述了由 4 种变换组成的变换序列。我们把每一种可能的变换都连上边，这样的边总共有 $O(n)$ 条。

如果您像我一样想考虑把数字滚动的这种变换的性质就错了，本题实际上可以任意给若干条边。

正确的做法是把这个图直接建圆方树，我们在圆方树上考虑对于一个点的答案。

我们发现：一个三元组 $(a,b,c)$ 合法，当且仅当以 $c$ 为根时，$\operatorname{lca}(a,b)$ 是一个圆点。也就是 $c$ 到 $a,b$ 组成的路径上的第一个点是圆点。

考虑证明该结论，充分性显然。考虑必要性，如果我们进入了一个方点，我们取出 $a,b$ 在这个点双内的两条不交的路径。如果我们想让这两条路径都有恰好一个点被经过，那么就会使得这两个被经过的点中间存在一条路径，只需要改走中间那一个路径就能存在 $2$ 个交点，不满足题意。

知道这个结论之后，我们可以对每一个圆点维护以当前点为 lca 的点对个数。当询问一个点的时候，其子树内的答案不变，仅有以其祖先为 lca 的答案改变。

注意到以 $0$ 为根的时候所有点深度小于等于 $\log_3n$，直接在每个点向上跳即可。

时间复杂度 $O(n\log_3n)$。

代码:

```cpp
#include <bits/stdc++.h>
using namespace std;
int  cnt, ccnt, dfn[600005], low[600005],  fa[600005];
vector<int> to[600005], son[600005];
long long sum[600005], ssum[600005], sums[600005];
int n, m;
stack<int> s;
inline int zhuan(int p) {
	int cnt = 1;
	while (cnt <= p) cnt *= 3;
	cnt /= 3;
	return cnt * (p % 3) + p / 3;
}
inline void tarjan(int p) {
	dfn[p] = low[p] = ++cnt;
	s.push(p);
	for (int i : to[p]) {
		if (!dfn[i]) {
			tarjan(i);
			low[p] = min(low[p], low[i]);
			++ccnt;
			if (low[i] == dfn[p]) {
				int op;
				s.push(-1);
				while (s.top() != p) {
					s.pop();
					op = s.top();
					son[ccnt].push_back(op), son[op].push_back(ccnt);
				}
			}
		} else {
			low[p] = min(low[p], dfn[i]);
		}
	}
}
struct node {
	long long sum, cnt;
	inline node() {
		sum = cnt = 0;
	}
	inline void add(int siz) {
		cnt = cnt + sum * siz;
		sum += siz;
	}
	inline void del(int siz) {
		sum -= siz;
		cnt = cnt - sum * siz;
	}
} f[600005];
inline void dfs(int p, int q) {
	fa[p] = q;
	f[p].add((p <= n));
	for (int i : son[p]) {
		if (i != q) {
			dfs(i, p);
			f[p].add(f[i].sum);
			ssum[p] += ssum[i];
			sums[p] += ssum[i];
		}
	}
	if (p <= n) ssum[p] += f[p].cnt;
}
inline long long getans(int p, int flg, long long w) {
	if (p == -1) return 0;
	if (!flg) {
		return ssum[p] + getans(fa[p], 1, p) + f[p].sum * (n + 1 - f[p].sum);
	} else {
		node ops = f[p];
		ops.add(n + 1 - f[p].sum);
		ops.del(f[w].sum);
		long long cnt = 0;
		if (p <= n) cnt = ops.cnt;
		return getans(fa[p], 1, p) + cnt + sums[p] - ssum[w];
	}
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i <= n; i++) {
		if (i != 0 && i * 3 <= n) {
			to[i].push_back(i * 3), to[i * 3].push_back(i);
		}
		if (i * 3 + 1 <= n) {
			to[i].push_back(i * 3 + 1), to[i * 3 + 1].push_back(i);
		}
		if (i * 3 + 2 <= n) {
			to[i].push_back(i * 3 + 2), to[i * 3 + 2].push_back(i);
		}
		if (i % 3 != 0) {
			int op = zhuan(i);
			if (op <= n && op != i) {
				if (zhuan(op) == i) {
					if (i < op) {
						to[i].push_back(op), to[op].push_back(i);
					}
				} else {
					to[i].push_back(op), to[op].push_back(i);
				}
			}
		}
	}
	cnt = 0;
	ccnt = n;
	for (int i = 0; i <= n; i++) {
		if (!dfn[i]) {
			tarjan(i);
			s.pop();
		}
	}
	dfs(0, -1);
	for (int i = 0; i <= cnt; i++) {
		cout << getans(i, 0, 0) * 2 << '\n';
	}
}
```

---

## 作者：happybob (赞：0)

这么连边真有啥意义吗。

对于所有可以相邻的数连边，事实上可以发现所有边都是双向的。连出后可以发现图一定连通。

完美的序列事实上就是一条简单路径，好的三元组 $(x,y,z)$ 其实就是存在一条从 $z$ 出发的简单路径，使得 $x$ 到 $y$ 的所有简单路径都和这条路径有恰好一个交点。

那么对于固定的 $z$，哪些 $(x,y,z)$ 是好的呢？我们声称若 $x$ 到 $y$ 的路径有必经点，且存在一条 $z$ 出发的路径经过此必经点，且这条路径不与任意一条 $x$ 到 $y$ 路径在必经点外重合。证明是比较显然的，如果 $x$ 到 $y$ 的所有简单路径与 $z$ 开始的简单路径相交于至少两个点，则必然存在某条简单路径也经过至少两个点。

对图建立圆方树，则判定条件变为 $x$ 到 $y$ 路径上离 $z$ 最近的点为圆点。枚举这个最近点，然后枚举 $z$ 所在子树，做子树加，最后进行查询，直接差分维护 DFN 序即可。复杂度线性。建图若实现不精细则是 $O(n \log n)$ 的。

代码：


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
#include <stack>
#include <array>
#include <set>
#include <vector>
using namespace std;

using ll = long long;

constexpr int N = 6e5 + 5;

array<vector<int>, N> G, NG;
int n, w, nc;
array<int, N> dfn, low, ra;
int idx;
stack<int, vector<int>> st;
array<bool, N> vis;
array<int, N> sz, sum;
array<ll, N> cfs;
int dfnid;

inline void rangeadd(int l, int r, ll v)
{
	if (l > r) return;
	cfs[l] += v, cfs[r + 1] -= v;
}

inline void addedge(int u, int v)
{
	if (u < 0 || v < 0 || u > n || v > n) return;
	if (u ^ v)
	{
		G[u].emplace_back(v), G[v].emplace_back(u);
	}
}

void Init()
{
	for (int i = 0; i <= n; i++)
	{
		addedge(i, i / 3);
		if (i <= w && i % 3 != 0)
		{
			int x = i % 3;
			int len = ceil(log(i) / log(3));
			int ni = i / 3 + (int)pow(3, len - 1) * x;
			addedge(i, ni);
		}
	}
}

inline void tarjan(int u)
{
	dfn[u] = low[u] = ++idx;
	st.emplace(u);
	for (auto& j : G[u])
	{
		if (!dfn[j])
		{
			tarjan(j);
			low[u] = min(low[u], low[j]);
			if (low[j] == dfn[u])
			{
				nc++;
				for (int y = 0; y ^ j;)
				{
					y = st.top();
					st.pop();
					NG[nc].emplace_back(y), NG[y].emplace_back(nc);
				}
				NG[nc].emplace_back(u), NG[u].emplace_back(nc);
			}
		}
		else
		{
			low[u] = min(low[u], dfn[j]);
		}
	}
}

void dfs(int u, int fa)
{
	dfn[u] = dfnid++;
	ra[dfnid] = u;
	sz[u] = 1;
	sum[u] = (u <= n);
	for (auto& j : NG[u])
	{
		if (j == fa) continue;
		dfs(j, u);
		sz[u] += sz[j], sum[u] += sum[j];
	}
}

void dfs2(int u, int fa)
{
	ll totc = 2ll * (n + 1 - sum[u]) * sum[u];
	ll sp = 0ll;
	for (auto& j : NG[u])
	{
		if (j == fa) continue;
		dfs2(j, u);
		sp += sum[j];
	}
	if (u > n) return;
	for (auto& j : NG[u])
	{
		if (j == fa) continue;
		totc += 1ll * sum[j] * (sp - sum[j]);
	}
	totc += 2ll * (sum[u] - 1);
	rangeadd(dfn[u], dfn[u], totc);
	for (auto& j : NG[u])
	{
		if (j == fa) continue;
		ll npc = totc - 2ll * sum[j] * (n + 1 - sum[j]);
		rangeadd(dfn[j], dfn[j] + sz[j] - 1, npc);
	}
	totc -= 2ll * (n + 1 - sum[u]) * sum[u];
	rangeadd(0, dfn[u] - 1, totc);
	rangeadd(dfn[u] + sz[u], nc, totc);
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> w;
	Init();
	nc = n;
	tarjan(0);
	dfs(0, -1);
	dfs2(0, -1);
	for (int i = 1; i <= nc; i++)
	{
		cfs[i] += cfs[i - 1];
	}
	for (int i = 0; i <= n; i++)
	{
		cout << cfs[dfn[i]] << "\n";
	}
	return 0;
}
```

---

