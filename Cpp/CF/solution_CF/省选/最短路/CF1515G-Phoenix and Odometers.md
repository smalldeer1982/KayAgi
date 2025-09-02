# Phoenix and Odometers

## 题目描述

In Fire City, there are $ n $ intersections and $ m $ one-way roads. The $ i $ -th road goes from intersection $ a_i $ to $ b_i $ and has length $ l_i $ miles.

There are $ q $ cars that may only drive along those roads. The $ i $ -th car starts at intersection $ v_i $ and has an odometer that begins at $ s_i $ , increments for each mile driven, and resets to $ 0 $ whenever it reaches $ t_i $ . Phoenix has been tasked to drive cars along some roads (possibly none) and return them to their initial intersection with the odometer showing $ 0 $ .

For each car, please find if this is possible.

A car may visit the same road or intersection an arbitrary number of times. The odometers don't stop counting the distance after resetting, so odometers may also be reset an arbitrary number of times.

## 说明/提示

The illustration for the first example is below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1515G/16d551900219fd749f7184c3ecf1105ab63bdc15.png)In the first query, Phoenix can drive through the following cities: $ 1 $ $ \rightarrow $ $ 2 $ $ \rightarrow $ $ 3 $ $ \rightarrow $ $ 1 $ $ \rightarrow $ $ 2 $ $ \rightarrow $ $ 3 $ $ \rightarrow $ $ 1 $ . The odometer will have reset $ 3 $ times, but it displays $ 0 $ at the end.

In the second query, we can show that there is no way to reset the odometer to $ 0 $ and return to intersection $ 1 $ .

In the third query, the odometer already displays $ 0 $ , so there is no need to drive through any roads.

Below is the illustration for the second example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1515G/e349b4f6bf9a850ce4ba1c7013ad10f004634d45.png)

## 样例 #1

### 输入

```
4 4
1 2 1
2 3 1
3 1 2
1 4 3
3
1 1 3
1 2 4
4 0 1```

### 输出

```
YES
NO
YES```

## 样例 #2

### 输入

```
4 5
1 2 1
2 3 1
3 1 2
1 4 1
4 3 2
2
1 2 4
4 3 5```

### 输出

```
YES
YES```

# 题解

## 作者：ix35 (赞：33)

题意：

给定有向带权图，若干次询问，每次给出 $v,s,t$，问是否存在经过 $v$ 的回路权值 $\equiv t-s\bmod t$。

---

题解：

显然回路上所有点都在 $v$ 所在的强连通分量中，且强连通分量中任何两个点间必有回路，所以每个强连通分量答案是一致的。

对于一个回路，连续走 $t$ 遍就相当于没有走过，但却可以经过这个回路走到路上的另一个点。

考虑求出所有回路的一组“基”，使得所有回路都可以表示成基的线性组合（系数为整数），然后我们可以证明：假设基中所有元素的权值 $\gcd$ 为 $g$，那么任何回路的权值都是 $g$ 的倍数。

这是因为，假设存在回路权值不是 $g$ 倍数，它必然无法被基表示，那么基也就不是基了。

同样，根据裴蜀定理，我们有如下结论：

- 令 $g'=\gcd(g,t)$，对于所有 $i\in [0,t/g')$，都存在一个回路的权值 $x$ 使得 $x\equiv ig'\bmod t$。

证明：首先利用裴蜀定理求 $ug+vt=ig'$，只需构造 $ug$，再次利用裴蜀定理，将 $ug$ 表示为若干回路相加减，而减一个回路相当于走 $k-1$ 次，因为所有点都在一个强连通分量中，所以可以用若干重复走 $k$ 次的回路连起来。

所以我们如果能够对每个强连通分量求出其 $g$，对于询问，首先算 $g'=\gcd(g,t)$，再看 $g'$ 是否是 $\gcd(s,t)$ 的因数，即可确定答案是 YES 还是 NO。

那么如何求所有环的一组基呢？考虑用 DFS 树，对正图和反图都求一个 DFS 树，确定一个根 $r$，令正图上 $r\to x$ 的路径为 $P(x)$，反图上为 $Q(x)$。

注意我们不需要基是最小的，首先我们将 $P(x)+Q(x)$ 加进基中，称为 $x$ 元；然后对于每条边 $(u,v)$ 再将 $P(u)+(u,v)+Q(v)$ 加入基中，称为 $(u,v)$ 元。

如此一来，对于任意一个回路，我们先将环上所有边的 $(u,v)$ 元加起来，再减去所有环上点的 $x$ 元，就实现了用基表示这个回路的方案。

用 Tarjan 算法缩点，并两次 DFS，假设算 $\gcd$ 的时间复杂度为 $O(\log v)$，那么总时间复杂度为 $O(n+(m+q)\log v)$。





---

## 作者：piggy123 (赞：10)

感觉题解都比较厉害，但是感觉不如随机化。

容易将题目转化为求每个强连通分量内的环长的 $\gcd$。我们考虑求出一棵 DFS 树，仅考虑返祖边即可得到若干个简单环。但是这样过不去，因为返祖边与后向边、横插边可能会形成新的环，影响 $\gcd$ 结果。

所以我们考虑随机取强连通分量内的 $10$ 个点作为根进行 DFS，这样取到所有单位环的概率很大，即可通过。

[提交记录](https://www.luogu.com.cn/record/163893784)。

---

## 作者：900102bj (赞：8)

### [CF1515G Phoenix and Odometers](https://www.luogu.com.cn/problem/CF1515G "CF1515G Phoenix and Odometers")
首先进行缩点，对于一个点，与它不在同一连通分量的点无法形成回路，所以对每个连通分量分别计算。

假设一个点 $u$，有两个长度为 $a$ 和 $b$ 的环，那么就相当于找两个非负整数 $x$ 和 $y$，使得 $ax+by=w$，其中 $w$ 为题中的路径长，根据裴蜀定理得到上述方程成立当且仅当 $\gcd(a,b)\mid w$。

考虑如何求出 $\gcd(a,b)$，即点 $u$ 所有环长的 gcd。

首先在强连通分量中存在四种边：树边、横叉边、返祖边、前向边。

举个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/k1pq3cyw.png)


假设根节点为 $1$，根节点通过树边到节点 $u$ 的路径长度为 $dis_{u}$。

以横叉边 $5\to 3$ 这条边为例，设它的边权为 $w$。因为这些点在同一连通分量且它是横叉边，说明 $3$ 这边已经可以形成回到 $1$ 的一条回路了。

所以其中一条回路为 $1$ 通过树边连向 $3$，$3$ 再通过一些非树边连回 $1$，大体路径为 $1\to 3\to 1$，长度可以表示为 $dis_{3}+val(3,1)$。

又因为当前的横叉边 $5\to 3$，产生了一条新的回路。

$1$ 通过树边连向 $5$，$5$ 通过横叉边连向 $3$，$3$ 通过一些非树边连回 $1$，大体路径为 $1\to 5\to 3\to 1$，长度为 $dis_{5}+w+val(3,1)$。

这两条回路的 gcd，可以使用辗转相减进行化简，将公共路径部分减掉，则 gcd 为 $\gcd(dis_{3}+val(3,1),dis_{5}+w-dis_{3})$。

这样对于一条横叉边 $u\to v$，对 gcd 产生的贡献为 $dis_{u}+w-dis_{v}$。

然后通过分析发现，返祖边和前向边对 gcd 的贡献也是 $dis_{u}+w-dis_{v}$，即所有的非树边，对答案的贡献是相同的。

求出所有环长的 gcd，设为 $g$，然后根据题意得出 $a\times g+s=b\times t$，再一次使用裴蜀定理得到 $\gcd(g,t)\mid s$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,q;
const int maxn=2e5+10;
struct node{
    int to,nxt,w;
};
node e[maxn];
int head[maxn],tot;
void add(int u,int v,int w){
    ++tot;
    e[tot].to=v;
    e[tot].nxt=head[u];
    e[tot].w=w;
    head[u]=tot;
}
int dfn[maxn],low[maxn],st[maxn];
bool vis[maxn];
int scc[maxn];
int res,tp,cnt;
void tarjan(int u){
    dfn[u]=low[u]=++res;
    st[++tp]=u;
    vis[u]=1;
    for(int i=head[u];i!=0;i=e[i].nxt){
        int v=e[i].to;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(vis[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(dfn[u]==low[u]){
        ++cnt;
        while(st[tp]!=u){
            scc[st[tp]]=cnt;
            vis[st[tp]]=0;
            --tp;
        }
        scc[st[tp]]=cnt;
        vis[st[tp]]=0;
        --tp;
    }
}
int dis[maxn],g[maxn];
bool tag[maxn];
void dfs(int u,int cur){
    tag[u]=1;
    for(int i=head[u];i!=0;i=e[i].nxt){
        int v=e[i].to;
        int w=e[i].w;
        if(scc[v]!=cur){
            continue;
        }
        if(tag[v]){
            g[cur]=__gcd(g[cur],dis[u]-dis[v]+w);
            continue;
        }
        dis[v]=dis[u]+w;
        dfs(v,cur);
    }
}
signed main(){
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v,w;
        scanf("%lld%lld%lld",&u,&v,&w);
        add(u,v,w);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=n;i++){
        if(!tag[i]){
            dfs(i,scc[i]);
        }
    }
    scanf("%lld",&q);
    while(q--){
        int u,s,t;
        scanf("%lld%lld%lld",&u,&s,&t);
        if(s%__gcd(g[scc[u]],t)==0){
            printf("YES\n");
        }
        else{
            printf("NO\n");
        }
    }
    return 0;
}
```

---

## 作者：lsj2009 (赞：6)

### Solution

好题！

感觉其他题解都没有讲清楚结论的证明/讲得过于抽象、复杂，所以特在此写一篇讲得清楚一些的题解。

首先容易发现的是我们经过的边必须在 $u$ 所在的强连通分量内，否则出去了就回不来了，然后我们可以在该强连通分量内乱走，假设里面一共有 $k$ 个环，长度分别为 $c_1,c_2,\cdots,c_k$，那么显然我们走过的长度可以表示为 $c_1\cdot x_1+c_2\cdot x_2+\cdots c_k\cdot x_k$，其中 $x_i$ 是任意非负整数，也就是我们可以绕每个环多次，其中将两个环衔接起来的时候，我们可以这么走：

![](https://z1.ax1x.com/2023/11/27/pi0bGWR.png)

其中两个环的交集部分 $\textbf{C}$ 必然也是一个环/点，否则必然无法衔接环 $\textbf{A,B}$，如果是一个环，不妨先衔接 $\textbf{A,C}$，再衔接 $\textbf{C,B}$。

根据裴蜀定理（这里不多具体介绍），显然我们可以走出的路径长度可以表示成 $p\gcd(c_1,c_2,\cdots,c_k)$，其中 $p$ 是任意非负整数。

那么也就是说，我们统计出所有环的环长 $\gcd$ 即可。

但是这是一个非常困难的事情，因为环的数量可能会非常多，比如我们两条边 $u\to v$ 和 $v\to u$ 就构成了一个环，而当两个大环 $\textbf{A,B}$ 合并时，如果分别包含 $f_A$ 和 $f_B$ 个小环，则新环 $\textbf{C}$ 一共有 $f_C=f_A\times f_B$ 个环，可能会非常大。

但是我们会猜结论：

- 找出原图的 dfs 生成树，考虑只包含一条非树边的环的 $\gcd$ 可以得到所有环的 $\gcd$。

需要注意的是，该结论只在有向图成立（如果说你认为无向图图上一条边 $(u,v)$ 不算一个环的话），在无向图上，好像只需要考虑只包含两条非树边的环（？，这里不多赘述。

- 证明：还是掏出刚才那张图

![](https://z1.ax1x.com/2023/11/27/pi0bYS1.png)

不妨假设其交集 $\textbf{C}$ 是一个点（如果是一个环就先合并 $\textbf{A,C}$ 再合并 $\textbf{B,C}$），则一个新环的长度为 $A+B$，而有结论 $\gcd(A,B,A+B)=\gcd(A,B)$，证明是简单的：

- 证明：
  1. 设 $\gcd(A,B)=d$，设 $A=nd,B=md$，那么 $A+B=(n+m)d$，则显然 $d\mid A+B$，得到 $\gcd(A,B,A+B)\ge \gcd(A,B)$。
  2. 又由于 $A,B,A+B$ 的公共因子显然比 $A,B$ 的公共因子要少，所以 $\gcd(A,B,A+B)\le \gcd(A,B)$。
  3. 所以 $\gcd(A,B,A+B)=\gcd(A,B)$。

将两个环的情况拓展到 $k$ 个环的情况归纳法易证。

故证毕。

考虑到计算 $\gcd$ 的时间复杂度为 $\log{V}$，所以最终复杂度为 $\Theta((n+m)\log{V})$。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=2e5+5;
int head[N],len;
struct node {
	int to,w,nxt;
}; node edge[N<<1];
void add_edge(int u,int v,int w) {
	edge[++len]={v,w,head[u]}; head[u]=len;
}
int dfn[N],low[N],color[N],cnt,p;
bool ins[N];
stack<int> s;
void tarjan(int u) {
	dfn[u]=low[u]=++p;
	s.push(u);
	ins[u]=true;
	for(int i=head[u];i;i=edge[i].nxt) {
		int v=edge[i].to;
		if(!dfn[v]) {
			tarjan(v);
			chkmin(low[u],low[v]);
		} else if(ins[v])
			chkmin(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]) {
		int x=-1; ++cnt;
		while(x!=u) {
			x=s.top(); s.pop();
			color[x]=cnt;
			ins[x]=false;
		}
	}
}
int d[N],g[N];
bool used[N];
void dfs(int u,int c) {
	used[u]=true;
	for(int i=head[u];i;i=edge[i].nxt) {
		int v=edge[i].to,w=edge[i].w;
		if(color[v]==c) {
			if(!used[v]) {
				d[v]=d[u]+w;
				dfs(v,c);				
			} else 
				g[c]=__gcd(g[c],abs(d[u]+w-d[v]));
		}
	}
}
signed main() {
	int n,m;
	scanf("%lld%lld",&n,&m);
	while(m--) {
		int u,v,w;
		scanf("%lld%lld%lld",&u,&v,&w);
		add_edge(u,v,w);
	}
	rep(i,1,n) {
		if(!dfn[i])
			tarjan(i);
	}
	rep(i,1,n) {
		if(!used[i])
			dfs(i,color[i]);
	}
	int q;
	scanf("%lld",&q);
	while(q--) {
		int u,a,b;
		scanf("%lld%lld%lld",&u,&a,&b);
		puts(a%__gcd(b,g[color[u]])==0? "YES":"NO");
	}
    return 0;
}
```

---

## 作者：7KByte (赞：4)

赛时没想出来自闭了。

第一个条件从 $v$ 出发回到 $v$ ，那么我们只用考虑 $v$ 所在的强连通分量。

现在整张图是一个强连通分量。

对于任意一条路径 $a\to b$ ，长度为 $w$，则等价于 $b\to a$ 长度为$-w$，且对任意模数 $P$ 成立。

我们假设 $b\to a$ 的路径长度为 $k$ ，依次走 $P$ 次 $b\to a$ 和 $P-1$ 次 $a\to b$ 等价于从 $b \to a$，且长度恰好为 $(P-1)w\equiv -w$ 。

那么整个图中所有的环是共享的，例如当前点 $x$ ，先花费 $w$ 代价走到环上一个点，在环上绕任意圈后再花费 $-w$ 的代价回到 $x$ 点。

所以对于出发点 $v$，我们可以选择图中若干个环，每个环可以走任意次。

如果只有两个环，长度分别为 $x,y$，那么 $ax+by$ 可以表示所有 $\gcd(x,y)$ 的倍数。

归纳一下，有若干个环，则可以表示的一定是所有环长度的 $\gcd$ 的倍数。

令这些环的 $\gcd =g$ ，有解的条件为 $S=ag-bT$，等价于 $\gcd(g,T)|S$ 。

如何找到所有环？猜个结论 $\rm DFS$ 树上仅包含一条非树边的所有环可以表示出所有环。

证明：我们找出的环长度都是形如 $d_x-d_y+val_{x\to y}$ ，对于任意一个环，长度可以写为 

$$Len = \sum val_{x_i\to x_{i+1}}=\sum d_{x_i}-d_{x_{i+1}}+val_{x_i\to x_{i+1}}$$

如果是树边，则 $d_{x_i}-d_{x_{i+1}}+val_{x_i\to x_{i+1}}=0$，否则一定可以表示为若干仅包含一条非树边的环的长度之和。

同时有 $\gcd(a_1,a_2,\cdots,a_n,\sum a_i)=\gcd(a_1,a_2,\cdots,a_n)$，所以仅包含一条非树边的环可以表示出所有环。

时间复杂度$\rm O(N+M)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 200005
#define int long long 
using namespace std;
int idx,n,m,c[N],col,h[N],tot,v[N],low[N],dfn[N],top,sta[N],g[N],d[N];
struct edge{int to,nxt,val;}e[N];
void add(int x,int y,int z){e[++tot].nxt=h[x];h[x]=tot;e[tot].to=y;e[tot].val=z;}
void dfs(int x){
	low[x]=dfn[x]=++idx;v[sta[++top]=x]=1;
	for(int i=h[x];i;i=e[i].nxt){
		if(!dfn[e[i].to])dfs(e[i].to),low[x]=min(low[x],low[e[i].to]);
		else if(v[e[i].to])low[x]=min(low[x],dfn[e[i].to]);
	}
	if(low[x]==dfn[x]){
		++col;
		while(true){
			int y=sta[top--];
			v[y]=0;c[y]=col;
			if(x==y)break;
		}
	}
}
int gcd(int x,int y){return y?gcd(y,x%y):x;}
void calc(int x,int w){
	v[x]=1;
	for(int i=h[x];i;i=e[i].nxt)if(c[e[i].to]==w){
		if(!v[e[i].to])d[e[i].to]=d[x]+e[i].val,calc(e[i].to,w);
		else {
			int cur=abs(d[x]+e[i].val-d[e[i].to]);
			//cout<<"ss "<<x<<" "<<d[x]<<" "<<d[e[i].to]<<" "<<e[i].val<<" "<<cur<<endl;
			if(!g[w])g[w]=cur;
			else if(cur)g[w]=gcd(g[w],cur);
		}
	}
}
signed main(){
	scanf("%lld%lld",&n,&m);
	rep(i,1,m){
		int x,y,z;scanf("%lld%lld%lld",&x,&y,&z);
		add(x,y,z);
	}
	rep(i,1,n)if(!dfn[i])dfs(i);
	rep(i,1,n)if(!v[i])calc(i,c[i]);
	int T;scanf("%lld",&T);
	while(T--){
		int x,s,t;scanf("%lld%lld%lld",&x,&s,&t);
		if(!g[c[x]]){
			if(!s)puts("YES");
			else puts("NO");
		}
		else{
			if(s%gcd(g[c[x]],t)==0)puts("YES");
			else puts("NO");
		}
	}
	return 0;
}
```

---

## 作者：do_it_tomorrow (赞：3)

修了一下计算 $\gcd$ 的坑。

在一个有向图中，因为要从 $p$ 出发然后再回到 $p$，所以路程只能在包含 $p$ 的强连通分量里面。

那么容易想到先用 tarjan 跑出强连通分量，然后对于每一个强连通分量分开求解，下面的所有讨论都在一个强两连通分量之内。

另外因为这个题目要求对 $t$ 取模，所以一下所有的操作都是在模意义之下的。

首先有两个个性质：

如果存在一条路径 $a\to b$，而且边权为 $w$，那么就可以构造出 $b\to a$ 而且边权为 $-w$ 的路径。

> 证明：
> 
> 因为 $a,b$ 在同一个强连通分量内，所以它们必然在一个环中，假设这个环的边权和为 $s$。那么从 $b$ 出发绕着环走 $t$ 圈，这样的贡献就是 $s\times t$ 也就是 $0$。
> 
> 所以只要在最后一圈的时候直接停在 $a$ 那么就相当于构造出了一条 $b\to a$ 的边权为 $-w$ 的路径。

另外有一个性质，如果强连通分量上有一个环，那么所有的点都可以看作在这个环上。

> 证明：
>
> 假设 $a$ 在长度为 $x$ 的环上，而 $b$ 不在。
> 
> 假设 $a\to b$ 的路径长度为 $w$，那么根据上面的性质，显然 $b\to a$ 的长度就是 $w$。
>
> 那么就可以构造 $b\to a\to  b$ 的路径，在到达 $a$ 之后可以随意的在环上行走，而结束后又可以原路返回。容易理解，这样路径的长度为 $w+x+(-w)=x$。


那么我们假设这个强连通分量中，所有的环的大小为 $x_1,x_2,\cdots,x_{ct}$，那么如果需要有解显然需要满足：

$${\sum\limits_{i=1}^{ct} k_i\times x_i}\equiv s\pmod{t}$$

其中 $k$ 满足：

$$\forall i\in[1,ct]\cap \mathbb{Z}\mid k_i\in\mathbb{Z}$$

那么根据裴蜀定理，有：

$$\gcd\limits_{i=1}^{ct} x_i\mid s$$

所以现在的问题就转化成为了统计一个强连通分量内所有的环的长度的 $\gcd$。

显然，直接求出所有的环显得并不现实，因为原本环的个数时无限的，所以考虑只求解出一些环但是其 $\gcd$ 却与原本一样。

容易发现只有简单环对答案有贡献，因为不是简单环的一定都是几个简单环的和，而 $\gcd$ 有性质 $\gcd(a,b)=\gcd(a,b,a+b)$，所以注定时不影响答案的。

为了以防有人不会证，这里说一下：

> 设 $\gcd(a,b)=g$，那么 $a=\dfrac{a}{g}\times g$，$b=\dfrac{b}{g}\times g$，所以就有 $a+b=g\times ({\dfrac{a}{g}+\dfrac{b}{g}})$。

对于统计环的情况，在这个强连通块中构建出一个 dfs 树，显然环有两种情况：一条非树边和一些树边组成，多条树边和一些树边组成。

显然对第二种情况，这些环的长度都可以通过第一种环通过加减得到，所以显然不会对 $\gcd$ 产生影响。

假设 $x\to y$ 存在一条非树边，那么计算方法为 $\lvert \text{dep}_{x}-\text{dep}_y+1\rvert$。

显然对于返祖边，这样是正确的，考虑证明对于横叉边的正确性。

> 假设有横叉边 $x\to y$，那么环的长度就应该为 $\text{dis}(rt,x)+\text{dis}(y,rt)+1$。
> 
> 通过上面的性质，因为 $\text{dis}(rt,y)\equiv -\text{dis}(y,rt)\pmod{d}$，所以得到 $\text{dis}(rt,x)+\text{dis}(y,rt)+1\equiv \text{dis}(rt,x)-\text{dis}(rt,y)+1\equiv\text{dep}_x-\text{dep}_y+1\pmod{d}$。

时间复杂度为 $O(n\log V)$。

---

## 作者：XiaoQuQu (赞：2)

### 题意

给定一个 $n$ 个点 $m$ 条边的带权有向图，多次询问给定 $p,s,t$，求是否存在一条从 $p$ 出发回到 $p$ 的路径使得路径的边权和 $w$ 满足 $(w+s)\bmod t=0$

### 题解

首先由于你要从 $p$ 出发并且回到 $p$，所以你经过的所有点一定是和 $p$ 处于一个强连通分量里（否则你走出强联通之后无法回到 $p$）。所以我们可以对每个强连通分量分别考虑。

对于任意模数 $t$（即使我们还不知道 $t$ 具体是什么），我们都有（注意下方的讨论如无标注均在模意义下进行）：

1. 如果存在一条 $a\to b$ 的路径长度为 $w$，那么存在一条 $b\to a$ 的路径长度为 $-w$。证明：假设 $b\to a$ 的路径长度为 $w'$，那么我们可以从 $b$ 经过 $a$ 绕回 $b$ 走 $t$ 次，再从 $b$ 走到 $a$，最终的长度为 $tw'+(t-1)w\equiv -w\pmod t$。
2. 如果 $a$ 在一个大小为 $x$ 的环内，那么对于该强连通分量里的任意一个点 $b$，$b$ 也在大小为 $x$ 的环内。证明：设 $b\to a$ 路径长度为 $w$，则构造形如 $b\to a\to a \to b$ 的路径，长度为 $w+x+(-w)=x$。

由于我们要求是否存在一个边权和为 $w$ 使得 $(w+s)\bmod t=0$，一个非常朴素的想法是我们求出一个强连通分量里的所有的环，设所有环的大小为 $x_1,x_2,\cdots x_n$，对于一组询问，我们其实想知道是否存在 $n$ 个整数 $k_1,k_2,\cdots,k_n$ 满足 $(k_1x_1+k_2x_2+\cdots+k_nx_n)+s\equiv 0\pmod t$。通过裴蜀定理可知，存在 $k_1,k_2,\cdots,k_n$ 的充要条件是 $s$ 为 $\gcd(x_1,x_2,\cdots,x_n)$ 的倍数。

但是求出每一个环显然是不太现实的。注意到有些 $x$ 显然是不必要的（比如一个 $x_i$ 是另一个 $x_j$ 的倍数），于是我们考虑是否可以「精简」一下我们的 $x_1,x_2,\cdots x_n$，选出其中的一个子集，使得原先可以表示出的任意一个环在子集中也可以表出。

我们求出一个强连通分量的 DFS 生成树，设根节点为 $r$，对于任意节点 $x$ 记从 $r$ 到 $x$ 的路径边权和为 $dep_x$。我们发现，对于两个点 $x,y$，设他们之间的路径长度为 $w$，$x\to y\to x$ 的这个环可以表示为 $dep_x+w-dep_y$，通过归纳法可以证明：对于任意一个环，均可以被若干个「形如 $r\to x\to y\to r$ 的环」表出，其中 $x,y$ 之间有连边。

所以我们就可知，要想求处所有环的 $\gcd$，只需要求出「形如 $r\to x\to y\to r$ 的环」即可。

最终对于每次询问 $p,s,t$，设我们要找的环长度为 $w$，即 $w=(k_1x_1+k_2x_2+\cdots+k_nx_n)=k\gcd(x_1,x_2,\cdots,x_n),k\in \mathbb{Z}$，我们有 $s=bt-aw$，其中 $a,b\in \mathbb{Z}+$，由裴蜀定理可知存在 $a,b$ 使得该式成立的充要条件为 $\gcd(t, w)|s$，也即 $\gcd(t,\gcd(x_1,x_2,\cdots,x_n))|s$。

最终时间复杂度为 $O(n\log V)$，视 $n,m,q$ 同阶。

```cpp
int n, m, q, st[MAXN], top, dfn[MAXN], g[MAXN], low[MAXN], dep[MAXN], col[MAXN], tot, scc;
struct _node {
	int v, w;
};
struct _edge {
	int u, v, w;
} e[MAXN];
vector<_node> G[MAXN], T[MAXN];
bool vis[MAXN], inst[MAXN];

void tarjan(int x) {
	dfn[x] = low[x] = ++tot;
	st[++top] = x;
	inst[x] = true;
	for (auto [u, w]:G[x]) {
		if (inst[u]) low[x] = min(low[x], dfn[u]);
		else if (!dfn[u]) {
			tarjan(u);
			low[x] = min(low[x], low[u]);
		}
	}
	if (low[x] == dfn[x]) {
		col[x] = ++scc;
		inst[x] = 0;
		while (st[top] != x) {
			col[st[top]] = col[x];
			inst[st[top]] = 0;
			top--;
		}
		top--;
	}
}

void dfs(int x) {
	vis[x] = true;
	for (auto [u, w]:G[x]) {
		if (vis[u] || col[u] != col[x]) continue;
		dep[u] = dep[x] + w;
		dfs(u);
	}
}

void work() {
	cin >> n >> m;
	for (int u, v, w, i = 1; i <= m; ++i) {
		cin >> u >> v >> w;
		G[u].push_back({v, w});
		e[i] = {u, v, w};
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= n; ++i)
		if (!vis[i]) dfs(i);
	for (int i = 1; i <= m; ++i) {
		auto u = e[i].u, v = e[i].v, w = e[i].w;
		if (col[u] != col[v]) continue;
		if (!g[col[u]]) g[col[u]] = dep[u] + w - dep[v];
		else g[col[u]] = __gcd(g[col[u]], dep[u] + w - dep[v]);
	}
	cin >> q;
	while (q--) {
		int p, s, t;
		cin >> p >> s >> t;
		if (s % t != 0 && !g[col[p]]) cout << "NO" << endl;
		else if (s % __gcd(t, g[col[p]]) == 0) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
}
```



---

## 作者：Mirasycle (赞：1)

很牛的一道数论和图论相结合的题目。

注意到由于要求走出一条回路，所以我们必须在 $u$ 所在强连通分量中走，而且还必须是若干个环的组合，否则无法回到起点。由于是若干个环的线性组合，所以也可以看出一个强连通分量中作为起点的答案是相同的。

于是设强连通分量中有 $m$ 个环，环长为 $l_i$。

那么就是要求 $\sum l_ix_i\equiv t-s \pmod t$。

根据裴蜀定理，一个强连通分量内的环可以表示出来的数必须满足是 $\gcd(l_1,l_2,\dots, l_n,t)$ 的倍数。

对于一个强连通分量中可能有很多很多环的存在（存在一堆环合并的情况），但是我们其实只要求出简单环即可，也就是 dfs 树上一条非树边连出的环即可。因为就是有多个环合并成大环，最后的本质也都是小环的线性组合，肯定满足 $\gcd(l_1,l_2,\dots,l_z)=\gcd(l_1,l_2,\dots,l_z,\sum x_il_i)$。

于是对于每个强连通分量求出 $\gcd$ 即可。

时间复杂度 $O((n+q)\log V)$。


```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
const int maxn=2e5+10;
void cmax(int &x,int y){ x=x>y?x:y; }
void cmin(int &x,int y){ x=x<y?x:y; }
int low[maxn],dfn[maxn],sz[maxn],ins[maxn],n,m,q,tot=0;
int st[maxn],col[maxn],rt[maxn],vis[maxn],scc,C,top=0;
ll dis[maxn],g[maxn]; vector<pair<int,int> > G[maxn];
bool chk(int u,int v){ return dfn[u]<dfn[v]&&dfn[v]<dfn[u]+sz[u]; }
void tarjan(int u){
	dfn[u]=low[u]=++tot; sz[u]=1;
	ins[u]=1; st[++top]=u;
	for(auto z:G[u]){
		int v=z.fi,w=z.se;
		if(!dfn[v]){
			dis[v]=dis[u]+w; tarjan(v);
			sz[u]+=sz[v]; cmin(low[u],low[v]);
		}else if(ins[v]) cmin(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		int y; rt[++scc]=u;
		do{ y=st[top--]; col[y]=scc; ins[y]=0; }while(y!=u);
	}
}
void dfs(int u){
	vis[u]=1;
	for(auto z:G[u]){
		int v=z.fi,w=z.se;
		if(col[v]!=C) continue;
		if(!vis[v]) dfs(v);
		else g[col[u]]=__gcd(g[col[u]],abs(dis[u]-dis[v]+w));
	}
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v,w; cin>>u>>v>>w;
		G[u].pb(v,w);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i]) tarjan(i);
	for(int i=1;i<=scc;i++) g[C=i]=0,dfs(rt[i]);
	cin>>q;
	for(int i=1;i<=q;i++){
		int u,s,t; cin>>u>>s>>t;
		if(s%__gcd(g[col[u]],(ll)t)==0) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：1)

首先，一个点想要回到自己，必须在他所在的强连通分量里走。

考虑对于强连通分量里的所有环长度求 $\gcd$，容易证明所有路径长度一定是 $r=\gcd$ 的倍数，最终每个询问仪表盘能显示某个数等价于他是 $\gcd(r,t)$ 的倍数。

简要证明：把所有环拎出来，由裴蜀定理可得有一种走环次数的方案使得其长度 $\bmod\ t$ 恰好为 $\gcd(r,t)$。考虑给每个环一个初始的走 $t$ 次，接着由欧拉回路的结论可以得到存在一条回路。最后，是 $\gcd(r,t)$ 倍数的情况只需要将每个环初始 $t$ 次以上的部分对应若干倍即可。

问题变成了求环长的 $\gcd$。

考虑求出 dfs 树。对于任意一条横叉边或返祖边，将两边距离的差其计入 $\gcd$ 中。这样，所有的环都至少与另一个环进行了求差后求 $\gcd$，等于原来的 $\gcd$。

总复杂度 $O(n\log V)$，可以通过。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define lowbit(i) (i&(-i))
using namespace std;
vector<pair<int,int>> vc[200005];
int dfn[200005],low[200005],cnt,ins[200005],stk[200005],top,bel[200005],tot;
int siz[200005],vis[200005],len[200005];
int gcdv[200005];
void dfs1(int now){
	dfn[now]=low[now]=++cnt;
	stk[++top]=now;
	ins[now]=1;
	for(auto v:vc[now]){
		if(!dfn[v.first]){
			dfs1(v.first);
			low[now]=min(low[now],low[v.first]);
		}
		else if(ins[v.first]){
			low[now]=min(low[now],low[v.first]);
		}
	}
	if(low[now]==dfn[now]){
		tot++;
		while(stk[top]!=now){
			ins[stk[top]]=0;
			bel[stk[top]]=tot;
			siz[tot]++;
			top--;
		}
		ins[stk[top]]=0;
		bel[stk[top]]=tot;
		siz[tot]++;
		top--;
	}
}
void dfs2(int now){
	vis[now]=1;
	for(auto v:vc[now]){
		if(bel[v.first]!=bel[now]) continue;
		if(!vis[v.first]){
			len[v.first]=len[now]+v.second;
			dfs2(v.first);
		}
		else{
			gcdv[bel[now]]=__gcd(gcdv[bel[now]],llabs(len[now]+v.second-len[v.first]));
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,m; cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v,w; cin>>u>>v>>w;
		vc[u].push_back(make_pair(v,w));
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) dfs1(i);
	for(int i=1;i<=n;i++) if(!vis[i]) dfs2(i);
	int q; cin>>q;
	while(q--){
		int v,s,t; cin>>v>>s>>t;
		if(s==0){
			cout<<"YES\n";
			continue;
		}
		if(siz[bel[v]]==1){
			cout<<"NO\n";
			continue;
		}
		int p=__gcd(gcdv[bel[v]],t);
		if(s%p!=0) cout<<"NO\n";
		else cout<<"YES\n";
	}
	return 0;
}
```

---

## 作者：Mashu77 (赞：0)

首先每个强连通分量可以隔离。接着可以通过强连通发掘一些性质。

若 
$(
x
,
y
,
z
)$，一定有 
$(
y
,
x
,
−
z
)$。在模任意数下都成立。因为强连通，$x
,
y$
 一定可以在同一个环上。从 
$y$
 开始，走 
$t$
 圈，此时为 
$0$。最后一步不走，就是 
$−
z$。

进而得出下面的性质：

同一个强连通分量中答案都一样。任意一个环都可以通过简单环的加减运算得到。设所有简单环长为 
$l_
1
,
l_
2
,
\cdots
,
l_k$，那么由裴蜀定理，可以得到所有 
$\gcd
(
l_
1
,
l_
2
,
\cdots,l_k)$
 倍数的长度。于是只需求所有简单环，就可以 
$O
(
1
)$
 查询。

寻找简单环，不难想到 
dfs
 树。这又分为只有一条非树边和有多条非树边的简单环。又发现，第二种一定可以由第一种加减而成。于是就解决了。

---

## 作者：_lbw_ (赞：0)

题意翻译的很清楚了。

首先题意等价于 $dis$ 同余于某个数。

然后起点终点均为 $v$，必须在同一个强连通分量里走，不然走不回来了。

问题转化为给定一个图，给定一个点和一个 $val$，在同余意义下求是否有环包含这个点且权值和等于 $val$。

接下来想到 P4151 的结论，把 DFS 树上的树边加一条返祖边这样的环抠出来，用他们就可以组合出任意的环了，接下来裴蜀定理即可。

---

