# 刑務所 (Jail)

## 题目描述

在 JOI 王国，安保最严格的地方就是 IOI 监狱。IOI 监狱中有 $N$ 个房间，以 $1,\dots,N$ 编号。其中有 $N-1$ 条通道。第 $i$ $(1\le i\le N-1)$ 条通道双向地连接房间 $A_i$ 和 $B_i$。任意两个房间都可以相互到达。

IOI 监狱中有 $M$ 个囚犯，以 $1,\dots,M$ 编号。第 $j$ $(1\le j\le M)$ 个囚犯的卧室和工作室分别是房间 $S_j,T_j$。一个囚犯可能在另一个囚犯的卧室工作。然而，每个房间最多成为一个囚犯的卧室，一个囚犯的工作室。

一天早上，这 $M$ 个囚犯需要从他们的卧室移动到他们的工作室。典狱长 APIO 先生需要按如下方式指示囚犯移动：  
**指令**：选择一个囚犯，然后命令他从当前所在的房间移动到一个与该房间有直接连边的房间。为了避免囚犯交流，不允许将囚犯移动到有其他囚犯在的房间。

为了尽早开始工作，APIO 先生想知道，是否存在一种给出任意条指令的方案使得每个囚犯以**最短路径**从卧室到达工作室。

请编写一个程序，在给定如上房间、通道和罪犯的所有信息后判断是否存在满足条件的方案。

# 题解

## 作者：gdf_yhm (赞：0)

[[JOISC2022] 监狱](https://www.luogu.com.cn/problem/AT_joisc2022_a)

### 思路

因为是一棵树，最短路径唯一，所以每次都让一个人走到底。当走 $s->t$，$s->t$ 中此时没有点，意味着起点这条路径上的人一定先于这个人走，终点在这条路径上的人一定后于这个人走。对于他们的相对顺序的限制，先走向后走连边，连边跑拓扑排序看有没有环。复杂度 $O(n^2)$。

优化建图，形如一个点向一条路径连边，一条路径向一个点连边。把一个点拆成两个，一个记录进入，一个出去。

线段树 $O(n\log^2 n)$，但可以倍增优化 $O(n\log n)$。记 $in_{u,i}$ 和 $out_{u,i}$ 表示 $u$ 到 $u$ 的 $2^i$ 级祖先这段区间。然后跟线段树优化一样向下一级区间连边。点向路径连边则在跳路径的 lca 是连边。

倍增常数过大甚至有时不如线段树。

```cpp
int n,m;
int head[maxn<<6],tot;
struct nd{
	int nxt,to;
}e[maxn<<7];
int d[maxn<<6];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;d[v]++;}
int to[maxn][17],dep[maxn];
int in[maxn][17],out[maxn][17],idx;
void dfs(int u,int fa){
	to[u][0]=fa;dep[u]=dep[fa]+1;
	for(int i=1;i<=16;i++)to[u][i]=to[to[u][i-1]][i-1];
	for(int i=0;i<=16;i++)if(to[u][i])in[u][i]=++idx,out[u][i]=++idx,d[idx-1]=d[idx]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);
	}
}
int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	for(int i=16;~i;i--)if(dep[to[u][i]]>=dep[v])u=to[u][i];
	if(u==v)return u;
	for(int i=16;~i;i--)if(to[u][i]!=to[v][i])u=to[u][i],v=to[v][i];
	return to[u][0];
}
int kth(int u,int k){
	for(int i=16;~i;i--)if((k>>i)&1)u=to[u][i];
	return u;
}
void updin(int u,int v,int w){
	if(u==v){
		add(w,u);
		return ;
	}
	if(dep[u]<dep[v])swap(u,v);
	for(int i=16;~i;i--)if(dep[to[u][i]]>=dep[v]){
		add(w,in[u][i]);
		u=to[u][i];
	}
	if(u==v)return ;
	for(int i=16;~i;i--)if(to[u][i]!=to[v][i]){
		add(w,in[u][i]),add(w,in[v][i]);
		u=to[u][i],v=to[v][i];
	}
	add(w,to[u][0]);
	add(w,u),add(w,v);
}
void updout(int u,int v,int w){
	if(u==v){
		add(u+n,w);
		return ;
	}
	if(dep[u]<dep[v])swap(u,v);
	for(int i=16;~i;i--)if(dep[to[u][i]]>=dep[v]){
		add(out[u][i],w);
		u=to[u][i];
	}
	// cout<<u<<" "<<v<<" "<<w<<" out\n";
	if(u==v)return ;
	for(int i=16;~i;i--)if(to[u][i]!=to[v][i]){
		add(out[u][i],w),add(out[v][i],w);
		u=to[u][i],v=to[v][i];
	}
	add(to[u][0]+n,w);
	add(u+n,w),add(v+n,w);
}
queue<int> q;
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	m=read();idx=2*n+m;
	dfs(1,0);
	for(int i=1;i<=n;i++)head[i]=0;tot=0;
	for(int i=1;i<=idx;i++)d[i]=0;
	for(int u=1;u<=n;u++){
		for(int i=1;i<=16;i++)if(to[u][i]){
			add(in[u][i],in[u][i-1]),add(in[u][i],in[to[u][i-1]][i-1]);
			add(out[u][i-1],out[u][i]),add(out[to[u][i-1]][i-1],out[u][i]);
		}
		if(to[u][0]){
			add(in[u][0],u),add(in[u][0],to[u][0]);
			add(u+n,out[u][0]),add(to[u][0]+n,out[u][0]);
		}
	}
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(i+2*n,u+n),add(v,i+2*n);
		// cout<<i+2*n<<" "<<u+n<<" "<<v<<"\n";
		int tp=lca(u,v),uu,vv;
		if(tp==u)uu=kth(v,dep[v]-dep[tp]-1);
		else uu=to[u][0];
		if(tp==v)vv=kth(u,dep[u]-dep[tp]-1);
		else vv=to[v][0];
		// cout<<uu<<" "<<vv<<" q\n";
		updin(u,vv,i+2*n);updout(uu,v,i+2*n);
	}
	// for(int u=1;u<=idx;u++){
		// for(int i=head[u];i;i=e[i].nxt){
			// int v=e[i].to;
			// cout<<u<<" "<<v<<"\n";
		// }
	// }
	for(int i=1;i<=idx;i++)if(!d[i])q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();
		// if(u>2*n&&u<=2*n+m)cout<<u-2*n<<" t\n";
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(d[v]){
				d[v]--;
				if(!d[v])q.push(v);
			}
		}
	}
	for(int i=1;i<=idx;i++)head[i]=0;tot=0;
	// for(int i=1;i<=idx;i++)if(d[i])cout<<i<<" "<<d[i]<<" d\n";
	for(int i=2*n+1;i<=2*n+m;i++)if(d[i]){printf("No\n");return ;}
	printf("Yes\n");
}
```

---

## 作者：EuphoricStar (赞：0)

观察可得，若存在合法解，则一定存在一种解，使得每个人都不停顿地从起点走到终点。

因为如果一个人走到一半要停下来等另一个人走，显然这个人也可以选择先走或者等另一个人走完自己再走。

继续观察可得，当且仅当第 $i, j$ 个人满足以下条件，它们之间的走的先后顺序能被确定：

- $s_i$ 在 $\text{path}(s_j, t_j)$ 上，则 $i$ 比 $j$ 先走；
- $t_i$ 在 $\text{path}(s_j, t_j)$ 上，则 $i$ 比 $j$ 后走。

建图跑拓扑排序即可。但是朴素建图边数太多了。

考虑把 $u, v$ 之间的边通过树上的点中转。对于每个点再复制一份，形成 $x_i, x'_i$。考虑建图如下：对于第 $i$ 个人，设 $s_i \to t_i$ 的路径中，除 $s_i$ 外走到的第一个点是 $p$，除 $t_i$ 外走到的第一个点是 $q$。

- 对于 $u \in \text{path}(s_i, q)$，连边 $i \to u$；
- 对于 $u \in \text{path}(p, t_i)$，连边 $u' \to i$；
- 连边 $t_i \to i, i \to s_i'$。

这样，若 $s_i$ 在 $\text{path}(s_j, t_j)$ 上，可以通过 $i \to s_i' \to j$ 从 $i$ 到达 $j$；若 $t_i$ 在 $\text{path}(s_j, t_j)$ 上，可以通过 $j \to t_i \to i$ 从 $j$ 到达 $i$。并且这样建图不会造成多余的影响。

那我们还剩下的问题是，一个点向树上的一条路径上的所有点连边。

考虑树剖后线段树优化建图，边数是 $O(n \log^2 n)$，就可以通过了。

[code](https://loj.ac/s/1881768)

鲜花：

![](https://s1.ax1x.com/2023/09/08/pP63Ruq.png)

调了一下午。

---

## 作者：5k_sync_closer (赞：0)

若 $u$ 路径的起点在 $v$ 路径上，则 $u$ 必须比 $v$ 先走，

若 $u$ 路径的终点在 $v$ 路径上，则 $v$ 必须比 $u$ 先走。

考虑建图，边 $u\to v$ 存在当且仅当 $u$ 必须比 $v$ 先走，

若建出的图有拓扑序，则按拓扑序操作即可，否则无解。

建图的复杂度太高，于是考虑线段树优化建图，分别考虑两个要求：

> 若 $u$ 路径的起点在 $v$ 路径上，则 $u$ 必须比 $v$ 先走

把每条路径向其起点连边，然后把每条路径除起点外的点向这条路径连边，

此时 $u$ 连向 $u$ 的起点，而 $u$ 路径的起点在 $v$ 路径上，所以 $u$ 的起点连向 $v$。

> 若 $u$ 路径的终点在 $v$ 路径上，则 $v$ 必须比 $u$ 先走

把每个终点向其路径连边，然后把每条路径向这条路径除终点外的点连边，

此时 $u$ 路径的终点在 $v$ 路径上，所以 $v$ 连向 $u$ 的终点，而 $u$ 的终点连向 $u$。

```cpp
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#define L(p) (p << 1)
#define R(p) (p << 1 | 1)
using namespace std;
struct E
{
    int v, t;
} e[10000050];
queue<int> q;
int O, n, m, c, z, a[200050], d[2000050], h[2000050];
void A(int u, int v)
{
    ++d[v];
    e[++c] = {v, h[u]};
    h[u] = c;
}
void B(int s, int t, int p)
{
    if (s == t)
    {
        a[s] = p;
        return;
    }
    A(p, L(p));
    A(p, R(p));
    A(L(p) + (n << 2), p + (n << 2));
    A(R(p) + (n << 2), p + (n << 2));
    int m = s + t >> 1;
    B(s, m, L(p));
    B(m + 1, t, R(p));
}
void C(int l, int r, int v, int o, int s, int t, int p)
{
    if (l <= s && t <= r)
    {
        if (o)
            A(v, p);
        else
            A(p + (n << 2), v);
        return;
    }
    int m = s + t >> 1;
    if (l <= m)
        C(l, r, v, o, s, m, L(p));
    if (r > m)
        C(l, r, v, o, m + 1, t, R(p));
}
struct T
{
    struct E
    {
        int v, t;
    } e[400050];
    int c, p, z[400050], d[400050], f[400050], s[400050], t[400050], b[400050], k[400050], h[400050];
    void A(int u, int v)
    {
        e[++c] = {v, h[u]};
        h[u] = c;
    }
    void X(int u)
    {
        s[u] = 1;
        for (int i = h[u], v; i; i = e[i].t)
            if (!d[v = e[i].v])
            {
                d[v] = d[f[v] = u] + 1;
                X(v);
                s[u] += s[v];
                if (s[v] > s[z[u]])
                    z[u] = v;
            }
    }
    void Y(int u, int g)
    {
        t[k[b[u] = ++p] = u] = g;
        if (z[u])
            Y(z[u], g);
        for (int i = h[u], v; i; i = e[i].t)
            if ((v = e[i].v) != f[u] && v != z[u])
                Y(v, v);
    }
    void M(int x, int y, int z, int k, int o)
    {
        while (t[x] != t[y])
        {
            if (d[t[x]] < d[t[y]])
                swap(x, y);
            C(b[t[x]], b[x] - (x == z), k, o, 1, n, 1);
            x = f[t[x]];
        }
        if (d[x] > d[y])
            swap(x, y);
        C(b[x] + (x == z), b[y] - (y == z), k, o, 1, n, 1);
    }
} T;
int main()
{
    scanf("%d", &O);
    while (O--)
    {
        scanf("%d", &n);
        B(1, n, 1);
        for (int i = 1, u, v; i < n; ++i)
            scanf("%d%d", &u, &v), T.A(u, v), T.A(v, u);
        T.X(T.d[1] = 1);
        T.Y(1, 1);
        scanf("%d", &m);
        for (int i = 1, x, y; i <= m; ++i)
        {
            scanf("%d%d", &x, &y);
            A(i + (n << 3), a[T.b[x]] + (n << 2));
            A(a[T.b[y]], i + (n << 3));
            T.M(x, y, x, i + (n << 3), 0);
            T.M(x, y, y, i + (n << 3), 1);
        }
        for (int i = 1; i <= (n << 3) + m; ++i)
            if (!d[i])
                q.push(i);
        while (!q.empty())
        {
            ++z;
            int u = q.front();
            q.pop();
            for (int i = h[u], v; i; i = e[i].t)
                if (!--d[v = e[i].v])
                    q.push(v);
        }
        puts(z == (n << 3) + m ? "Yes" : "No");
        c = z = T.c = T.p = 0;
        for (int i = 1; i <= (n << 3) + m; ++i)
            d[i] = h[i] = 0;
        for (int i = 1; i <= n; ++i)
            T.z[i] = T.d[i] = T.f[i] = T.s[i] = T.t[i] = T.b[i] = T.k[i] = T.h[i] = 0;
    }
    return 0;
}
```


---

