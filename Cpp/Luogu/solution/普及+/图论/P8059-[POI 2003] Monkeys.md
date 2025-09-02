# [POI 2003] Monkeys

## 题目描述

一棵树上有 $n$ 只猴子。他们从 $1 \sim n$ 编号。编号为 $1$ 的猴子用它的尾巴盘住了一个树枝，剩下的猴子要么被其他的猴子钩住要么就是自己用手钩住其他的猴子。每只猴子都可以用两只手去钩其他的猴子，每只手最多只能钩一只。

从 $0$ 时刻开始，每一秒都有一只猴子松开它的一只手。这也许会造成一些猴子掉落到地上，我们想要知道它们掉落地上的时间（猴子掉落的速度都非常的快，可以忽略掉落的时间）。

## 说明/提示

对于所有数据，$1 \le n \le 2 \times 10^5$，$1 \le m \le 4 \times 10^5$。

## 样例 #1

### 输入

```
3 2
-1 3
3 -1
1 2
1 2
3 1```

### 输出

```
-1
1
1```

# 题解

## 作者：Alex_Wei (赞：14)

> [*P8059 [POI2003] Monkeys*](https://www.luogu.com.cn/problem/P8059)
>
> [POI 合集](https://www.cnblogs.com/alex-wei/p/POI.html)。

连通性相关删边题目考虑时光倒流，求出每个猴子第一次与 $1$ 连通的时间。直接 dfs 打标记即可。时间复杂度线性，细节见代码。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 4e5 + 5;
int n, m, ls[N], rs[N], ban[N][2];
int id[N], dir[N], ans[N], vis[N];
vector <pair <int, int>> e[N];
void dfs(int id, int as) {
	if(id == -1 || vis[id]) return; // vis[id] = 1 表示 id 与 1 连通
	vis[id] = 1, ans[id] = as; // ans[id] 表示 id 的答案
	if(!ban[id][0]) dfs(ls[id], as);
	if(!ban[id][1]) dfs(rs[id], as);
	for(auto it : e[id]) if(!ban[it.first][it.second]) dfs(it.first, as);
}
int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		cin >> ls[i] >> rs[i];
		if(ls[i] != -1) e[ls[i]].push_back({i, 0}); // 连双向边，记录是哪只手
		if(rs[i] != -1) e[rs[i]].push_back({i, 1});
	} for(int i = 0; i < m; i++) cin >> id[i] >> dir[i], ban[id[i]][--dir[i]] = 1;
	dfs(1, -1);
	for(int i = m - 1; ~i; i--) {
		ban[id[i]][dir[i]] = 0;
		if(vis[id[i]]) dfs(dir[i] ? rs[id[i]] : ls[id[i]], i);
		if(vis[dir[i] ? rs[id[i]] : ls[id[i]]]) dfs(id[i], i);
	} for(int i = 1; i <= n; i++) cout << ans[i] << "\n";
	return 0;
}
```

---

## 作者：wzy2021 (赞：12)

这道题思路比较巧妙也比较常见：正难则反。

考虑正推，仿佛要带撤销并查集，反正很难，

面对这种删边问题，一般都是通过倒推的方法变为加边问题，往往会好做。

所以考虑倒推，问题转换为：通过不断加边，则每个点的掉落时间为它第一次与 $1$ 号节点联通的时间，可用并查集维护。

但是，一个问题来了：在一块连通块 $B$ 与 $1$ 号节点所在的连通块相连时，怎么更新 $B$ 内的节点？

可用链表维护，记录一个 $nxt_i$ 维护链表操作，

而且每个并查集维护三个信息：

1. $f_i$，记录 $i$ 节点的父亲，初始值：$f_i=i$；

2. $head_i$ 记录 $i$ 节点的连通块的节点中，编号最小的点；

3. $tail_i$ 记录 $i$ 节点的连通块的节点中，编号最大的点；

其中 $head_i$ 与 $tail_i$ 的 $i$ 是连通块的根，即“老大”。

若要与 $1$ 合并，还要先更新答案，

而且每次合并时都是由大合并到小的，要保证 $1$ 节点一直为根。

~~~cpp
#include <cstdio>
#include <iostream>
using namespace std;

const int N = 4e5 + 10;

int a[N][3]; 
int ans[N], nxt[N];
int p[N], w[N], vis[N][3];
int fa[N], head[N], tail[N];

int find(int x){
	if (fa[x] == x)return x;
	return fa[x] = find(fa[x]);
}

void merge (int u, int v, int p) {
	int fu = find(u), fv = find(v);
	if (fu == fv) return ;
	if (fu > fv) swap (fu, fv);
	if (fu == 1 && p != -1) { // 更新答案。其中 p = -1 代表是没有删过的边将它加上，所以不更新答案。
		for (int use = head[fv]; use; use = nxt[use]) ans[use] = p;
	}
	fa[fv] = fu; nxt[tail[fu]] = head[fv]; tail[fu] = tail[fv];
} 

int main() {
	int n, m; scanf ("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf ("%d%d", &a[i][1], &a[i][2]); ans[i] = -1;
	}
	for (int i = 0; i < m; ++i) {
		scanf ("%d%d", &p[i], &w[i]);
		vis[p[i]][w[i]] = 1; // 记录此条边会被删掉。
	}
	for (int i = 1; i <= n; ++i) fa[i] = head[i] = tail[i] = i, nxt[i] = 0;
	for (int i = 1; i <= n; ++i) { // 若从来没有删过的边，一开始就要加上。
		if (!vis[i][1] && a[i][1] != -1) merge (i, a[i][1], -1);
		if (!vis[i][2] && a[i][2] != -1) merge (i, a[i][2], -1);
	}
	for (int i = m - 1; i >= 0; --i) {
		int u = p[i], v = a[p[i]][w[i]];
		merge (u, v, i);
	}
	for (int i = 1; i <= n; ++i) printf("%d\n",ans[i]);
	return 0;
} 
~~~

---

## 作者：xiaozeyu (赞：4)

[P8059 [POI2003] Monkeys](https://www.luogu.com.cn/problem/P8059)

与他人写法略有不同的并查集做法。

这其中其实也用了一点倒序连边的思想。

正着连边难做，那就倒着连边。

那么，问题就变成了：一个无向图，初始有一些边，每次加一条边，问每个点何时与点 $1$ 联通。

这样就很简单了。

每次加边的时候，假如这条边一端和 $1$ 联通而另一端没有，那么我们可以对未联通的那端 dfs 一遍，标记它们都被联通了，并记录联通的时间。

这里的 dfs 其实只是一个前向星而已。不太算得上 dfs 吧。

代码如下。

---

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 200010
#define maxe 400010
int L[maxn],R[maxn],f[maxn],Next[maxn],ans[maxn],Hand[maxe],id[maxe],n,m,flag[maxn][3];
inline int read()
{
	int s=0;char c=getchar();bool f=0;
	for(;!isdigit(c);c=getchar()) f^=!(c^45);
	for(;isdigit(c);c=getchar()) s=(s<<3)+(s<<1)+(c^48);
	if(f) s=-s;return s;
}
inline void write(int x)
{
	if(x>=10) write(x/10);
	putchar('0'+x%10);
}
inline int getf(int x)
{
	if(x==f[x]) return x;
	else return f[x]=getf(f[x]);
}
int dfs(int x)
{
	if(ans[x]) return ans[x];
	else return dfs(Next[x]);
}
int main()
{
	n=read(),m=read();
	memset(flag,true,sizeof flag);
	memset(ans,0,sizeof ans);
	for(int i=1;i<=n;i++) L[i]=read(),R[i]=read(),f[i]=i;
	for(int i=1;i<=m;i++) Hand[i]=read(),id[i]=read(),flag[Hand[i]][id[i]]=false;;
	for(int i=1;i<=n;i++)
		{
			if(L[i]!=-1&&flag[i][1])
			{
				int v=getf(L[i]),u=getf(i);
				{
					if(u!=v)
					{
						if(u==1) swap(u,v);
						f[u]=v;Next[u]=v;
					}
				}
			}
			if(R[i]!=-1&&flag[i][2])
			{
				int v=getf(R[i]),u=getf(i);
				if(u!=v)
				{
					if(u==1) swap(u,v);
					f[u]=v;Next[u]=v;
				}
			}
		}
	//for(int i=1;i<=n;i++) cout<<"i="<<i<<" "<<f[i]<<endl;
	for(int i=m;i>0;i--)
	{
		if(id[i]==1)
		{
			int u=getf(Hand[i]),v=getf(L[Hand[i]]);
			if(u!=v)
			{
				if(u==1) swap(u,v);
				f[u]=v;
				if(v==1) ans[u]=i;
				else Next[u]=v;
			}
		}
		if(id[i]==2)
		{
			int u=getf(Hand[i]),v=getf(R[Hand[i]]);
			if(u!=v)
			{
				if(u==1) swap(u,v);
				if(v==1) ans[u]=i;
				else Next[u]=v;
				f[u]=v;
			}
		}
	}
	ans[1]=-1;cout<<-1<<endl;
	
	for(int i=2;i<=n;i++)
	{
		ans[i]=dfs(i);
		if(ans[i]==-1) puts("-1");
		else {write(ans[i]-1);puts("");}
	}
	return 0;
}


```

感谢管理员的审核。

---

## 作者：NightTide (赞：4)

## PART 0：说些闲话
写这题之前或之后不妨去写一写[P1197 [JSOI2008]星球大战](https://www.luogu.com.cn/problem/P1197)，这两题的思路都差不多，还有[P1653 猴子](https://www.luogu.com.cn/problem/P1653)，应该说这题三倍经验？
## PART 1：思路简析
正题开始，按照题目的意思，我们需要对一个无向图进行删边，问每个点什么时候与 $1$ 号点不连通。但是在编程中，删边是很难的，加边是很容易的，于是我们换一个思路，考虑离线处理，先把所有要删的边先删掉，之后我们进行一次时光倒流，把每一条边加回去，这样问题就变成了，一个无向图，加入 $m$ 条边，问每个节点什么时候与 $1$ 号点相连。

这样问题就简单了，我们一条一条的把边加回去，对这条边未与 $1$ 号点相连的那一段进行 `DFS`，并记录答案
## PART 2：时间复杂度
关于这个，本蒟蒻其实不太会证，但是照虎画猫，学着大佬的样子证一下，欢迎纠错。

由于每一个点只会经过一次 `DFS` 后就被标记掉，每一条边也只会遍历一次，所以时间复杂度应该是线性的，也就是 $O(n)$ 的，完全足以 A 掉这一题
## PART 3：AC CODE
新鲜出炉的难看代码

```cpp
#include<bits/stdc++.h>
#define MAXN 200010
#define MAXM 400010
using namespace std;
struct node{
	int l_son,r_son;
};
struct edge{
	int pre,to;
};
struct opearte{
	int id,hand;
};

int n,m,cnt,now_time=-1;
edge e[MAXN*4];
node monkey[MAXN];
opearte del[MAXM];
int ans[MAXN],head[MAXN];
bool is_alive[MAXN][2],vis[MAXN];

void add_edge(int u,int v){
	e[++cnt].pre=head[u];
	e[cnt].to=v; head[u]=cnt;
}
void dfs(int now){
	ans[now]=now_time;
	vis[now]=true;
	for(int i=head[now];i;i=e[i].pre){
		if(!vis[e[i].to]){
			dfs(e[i].to);
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&monkey[i].l_son,&monkey[i].r_son);
		if(monkey[i].l_son!=-1) is_alive[i][0]=true;
        if(monkey[i].r_son!=-1) is_alive[i][1]=true;
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d",&del[i].id,&del[i].hand);
        is_alive[del[i].id][del[i].hand-1]=false;
	}
	for(int i=1;i<=n;i++){
		if(is_alive[i][0]) add_edge(i,monkey[i].l_son),add_edge(monkey[i].l_son,i);
		if(is_alive[i][1]) add_edge(i,monkey[i].r_son),add_edge(monkey[i].r_son,i);
	}
	dfs(1);
	for(int i=m;i>=1;i--){
		now_time=i-1;
		int u,v;
		if(del[i].hand==1) u=del[i].id,v=monkey[del[i].id].l_son;
		else u=del[i].id,v=monkey[del[i].id].r_son;
		add_edge(u,v); add_edge(v,u);
		if(vis[u]&&!vis[v]) dfs(v);
		else if(vis[v]&&!vis[u]) dfs(u);
	}
	for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：ningago (赞：3)

首先想到的是并查集，于是并查集调炸了，无意中发现了另一种不用并查集的小清新做法。

对于每个点，维护一个 $val_i$ 表示 $i$ 所在的连通块里有没有包含 $1$。

删边对于邻接表建图不友好，考虑把时光倒流，删边就变成了加边。

加边时，每次如果是将一个包含 $1$ 的连通块与一个不包含的连通块合并时，就dfs更新答案。由于每个点只会被更新答案一次，dfs时间复杂度 $O(n)$。

总时间复杂度 $O(n+m)$。

Code：

```cpp
#include <cstdio>
#include <cstring>

#define N 200005

int n,m;
int l[N],r[N];
bool lf[N],rf[N];
int u[N << 1];
bool v[N << 1];
bool val[N];
int ans[N];

int h[N],e[N << 2],ne[N << 2],idx;

void add_edge(int x,int y)
{
	ne[++idx] = h[x];
	h[x] = idx;
	e[idx] = y;
}

void dfs(int k,int id)
{
	if(~ans[k])
		return;
	ans[k] = id;
	val[k] = 1;
	//printf("ans[%d] = %d\n",k,id);
	for(int i = h[k];~i;i = ne[i])
	{
		int nx = e[i];
		dfs(nx,id);
	}
}

void add(int x,int y,int id)
{
	//printf("add(%d,%d,%d)\n",x,y,id);
	if(val[x] > val[y])
		x ^= y ^= x ^= y;
	if(val[x] == 0 && val[y] == 1)
	{
		dfs(x,id);
	}
	add_edge(x,y);
	add_edge(y,x);
	if(val[y])
		val[x] = 1;
}

int main()
{
	//freopen("monkey.in","r",stdin);
	//freopen("monkey.out","w",stdout);
	memset(ans,-1,sizeof(ans));
	memset(h,-1,sizeof(h));
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++)
	{
		scanf("%d%d",&l[i],&r[i]);
		val[i] = (i == 1);
	}
	for(int i = 0,x;i < m;i++)
	{
		scanf("%d%d",&u[i],&x);
		x--;
		v[i] = x;
		if(v[i] == 0)
			lf[u[i]] = 1;
		else
			rf[u[i]] = 1;
	}
	//printf("A\n");
	for(int i = 1;i <= n;i++)
	{
		if(~l[i] && !lf[i])
			add(i,l[i],m);
		if(~r[i] && !rf[i])
			add(i,r[i],m);
	}
	//printf("B\n");
	for(int i = m - 1;i >= 0;i--)
	{
		if(v[i] == 0)
			add(u[i],l[u[i]],i);
		else
			add(u[i],r[u[i]],i);
	}
	printf("-1\n");
	for(int i = 2;i <= n;i++)
		printf("%d\n",ans[i] == m ? -1 : ans[i]);
	return 0;
}
```

---

