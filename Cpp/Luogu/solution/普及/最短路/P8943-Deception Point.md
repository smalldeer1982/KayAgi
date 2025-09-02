# Deception Point

## 题目背景

“防空火网已启用。”三角洲二号喊道，他坐在“基奥瓦”武装直升机舱门边的武器控制椅里，竖起了大拇指，“火力网
、调制噪声、掩护脉冲全都激活并锁定。”

三角洲一号心领神会，驾驶着飞机猛地向右一个侧弯飞机又驶上了一条前往“戈雅”的直线路径。这一招能躲过“戈雅”的雷达监控。

“锡箔包确定！”三角洲二号喊道。

> 绝对的孤立，

三角洲一号想。

> 他们毫无抵抗力。

他们的目标幸运且狡猾地从米尔恩冰架上逃脱了，但这回他们不会再得逞了。雷切尔 · 塞克斯顿和迈克尔 · 托兰选择弃岸上船，真是糟糕的选择。不过，这将是他们所做的最后一个坏决定了。

## 题目描述

雷切尔与迈克尔被困在了“戈雅”号上，而三角洲二号正在顺着雷达追杀二人。幸运的是，雷切尔也有一副雷达，因此双方都能知道对方的位置。

船舱内部共有 $n$ 个舱室，其中有 $n$ 条走廊连接这些舱室。$n$ 个舱室是互相连通的。由于船上空间拥挤，船舱内不会出现小于等于四条走廊组成的环。每过一分钟，雷切尔与三角洲二号都会同时从一个舱室跑到另一个舱室。

如果雷切尔在舱室内或者过道上碰到了三角洲，那么就意味着大限将至。雷切尔总共有 $q$ 个问题：当她在舱室 $x$，且三角洲二号在舱室 $y$ 时，她是否可以存活下来？

---

#### **【形式化题意】**

给定一张 $n$ 个点 $n$ 条边的无向连通图，图内不存在四元（及以下）环。$q$ 次询问 $x,y$，分别在图上 $x,y$ 点上放上棋子 $\rm A, B$。

每次两人同时操作棋子沿图边移动一步，若两棋子同时走到了同一个点上或者同时走过了相同的边，则 $\rm B$ 胜利。如果在 $10^{10^{9961}}$ 次操作后 $\rm B$ 还未胜利，则 $\rm A$ 胜利。

$\rm A,B$ 都是绝顶聪明的，他们不会做出对自己不利的决策。请你求出每次游戏的游戏结果。若 $\rm A$ 获胜，输出 `Survive`；否则输出 `Deception`。

**若对题意有疑问，请移步样例解释与数据范围部分。**

## 说明/提示

#### 【样例解释】

船舱结构图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/tlsqnsia.png)

在第二组询问中，三角洲可以先走一步到达结点 $2$，此时雷切尔到达结点 $4$。随后可以证明，不存在一种方案使得雷切尔不碰到三角洲。

#### 【数据范围】

**本题开启捆绑测试。**

| $\text{Subtask}$ | 分值 | $n\le$ | $q\le$ | 特殊性质 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $0$ | $5$ | $2\times10^5$ | $1$ | 无 |
| $1$ | $5$ | $10$ | $2\times10^5$ | 无 |
| $2$ | $5$ | $2\times 10^5$ | $2\times10^5$ | $\forall 1\le i\le n, u_i=i,v_i=(i\bmod n) + 1$ |
| $3$ | $15$ | $200$ | $2\times 10^5$ | 无 |
| $4$ | $20$ | $2\times 10^3$ | $2\times 10^5$ | 无 |
| $5$ | $50$ | $2\times 10^5$ | $2\times 10^5$ | 无 |

对于 $100\%$ 的数据，$3\le n\le 2\times10^5$，$1\le q\le2\times10^5$，$u_i\neq v_i$，$x_i\neq y_i$。不存在四（及以下）元环。

## 样例 #1

### 输入

```
8 3
2 1
3 1 
4 2 
5 3
6 2
7 5
8 4
5 6
7 8
8 6
3 6```

### 输出

```
Survive
Deception
Survive
```

# 题解

## 作者：HYdroKomide (赞：14)

### 题意：
首先，$n$ 个结点、$n$ 条边的无向图。

我们充分发挥人类智慧，想到，树有 $n-1$ 条边呀！所以这个图就是一棵树加了一条边，组成了一个环，又称基环树。

### 思路：

我们知道图里必然有且只有一个环，这个环的大小还大于 $4$。所以如果逃离者 $A$ 在监守者 $B$ 堵住路之前到达环上的任意一点，就一定能把监守者绕死。

我们知道图里只有一个环，所以除了环上以外的点都只能通向环上的一个点。我们称 $A$ 第一次踏上环的地点为 $fa_A$。若 $B$ 能够抢先，或者与 $A$ 同时到达 $fa_A$，那么 $A$ 必输。否则，$A$ 必胜。

那么，我们需要知道的，就是 $A$ 与环的距离 $dep_A$、$A$ 踏上环的位置 $fa_A$、$B$ 与环的距离 $dep_B$、$B$ 踏上环的位置 $fa_B$、$A$ 踏上位置与 $B$ 踏上位置的距离 $dist(fa_A,fa_B)$。如果该点在环上，则 $dep$ 值为 $0$。

当 $dep_A \le dist(fa_A,fa_B)+dep_B$，监守者就会堵住门吃掉 $A$。反之 $A$ 可以逃入环中绕杀监守者。

于是，预处理这一堆就行啦！

分解步骤：

1. 分离出图中的环。
2. 对于每个环上的点，遍历其子孙，预处理距离。
3. 预处理环上点互相的距离。

当然，如果 $A$ 已经在环上，肯定有救，可以先特判但没必要。

其实这个方法冗杂比较多，所以代码显得长。具体可参见注释。
### 程序如下：

```cpp
#include<cstdio>
#include<vector>
#include<cmath>
const int N=2e5+1;
using namespace std;
int n,q,fd,f[N],dep[N],cnt,sw[N];
bool vis[N],cir[N];
vector<int>g[N];
void dfs1(int x,int fa){//第一个 dfs，找到所有环上的点并标记
	if(vis[x]==true){//如果回到老地方，说明有环了
		fd=x;
		cir[x]=true;
		sw[x]=++cnt;//给环上的点依次打上标记，方便后面查询环上两点的距离
		return;
	}
	vis[x]=true;
	int u=g[x].size();
	for(int i=0;i<u;i++){
		int v=g[x][i];
		if(v!=fa)dfs1(v,x);
		if(fd!=0){
			if(fd==x)fd=0;
			if(!cir[x]){
				cir[x]=true;//回溯的时候就可以继续打标记
				sw[x]=++cnt;
			}
			break;
		}
	}
	return;
}
void dfs2(int old,int x,int fa){//处理所有非环上点与环的距离（深度）
	f[x]=old;//存踏上环的地点
	dep[x]=dep[fa]+1;
	int u=g[x].size();
	for(int i=0;i<u;i++){
		int v=g[x][i];
		if(!cir[v]&&g[x][i]!=fa)dfs2(old,v,x);
	}
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		g[u].push_back(v);
		g[v].push_back(u);//vector 连边
	}
	dfs1(1,0);
	dep[0]=-1;
	for(int i=1;i<=n;i++)
		if(cir[i])//对于所有环上的点，进行第二个 dfs
			dfs2(i,i,0);
	while(q--){
		int x,y;
		scanf("%d%d",&x,&y);
		int st=f[x],ed=f[y];//踏上环的两地
		int len=abs(sw[st]-sw[ed]);//环上两地之间的距离
		if(len>cnt/2)len=cnt-len;
		if(cir[x]||dep[x]<dep[y]+len)printf("Survive\n");
		else printf("Deception\n");
	}
	return 0;
}
```

### THE END

---

## 作者：bloodstalk (赞：4)

## Description
题目给的很详细了。
## Solution
首先 $n$ 个点 $n$ 条边，我们很容易就想到基环树(比正常的树多了一条边，形成了一个环)，不会也没关系，这题跟基环树其实关系不大。

首先，我们可以发现题目中说明了这个环不是一个四元及以下的环，这代表着如果 $A$ 提前进入了这个环，那么他就可以和 $B$ 周旋，这样 $B$ 就永远都抓不到 $A$ ；相反的，如果 $B$ 赶在 $A$ 之前就把 $A$ 通往环内的那个点就封死了，那么 $A$ 就只能静待被抓了。

想到这里其实思路就很明了了，我们需要预处理出这些东西：

- 求出这个环；

- 求出每个不在环上的点到环的距离以及最初到环上的哪个点；

- 求出环内点与点之间的距离。

由于赛前几天一直在学习边双，降智了，所以找环我用的边双做的(，其实也可以用拓扑等方法来解决；

对于第二个问题，我们 $O(n)$ 枚举每一条边，如果出现了点 $x$ 在环内点 $y$ 不在环内的情况，我们从 $y$ 开始进行广搜给 $y$ 延伸出来的子树打上标记。

对于第三个问题，我们随便断掉环上的一条边，这样形成的就是一条链，我们在链上以断的那条边的其中一个端点为起点再进行一次广搜，处理出环上每个点到这个端点的距离，那么最后环上两个点 $x,y$ 的最短距离就是 $\min(\lvert len_x-len_y \rvert,size- \lvert len_x-len_y \rvert)$，其中 $size$ 表示的是这个环的大小。

由此可知，总复杂度是一个线性的，可以通过。

## Code
```cpp
#include<bits/stdc++.h>
//define int long long
#define ll long long
#define next nxt
#define re register
#define il inline
const int N = 4e5 + 5;
using namespace std;
int max(int x,int y){return x > y ? x : y;}
int min(int x,int y){return x < y ? x : y;}

int n,q,u,v,cnt,tot,idx,ans,k,cutx,cuty;
int low[N],dfn[N],stk[N],belong[N],len[N];
struct Node{
	int tp,dep;//tp表示这个不在环上的点通过哪个点进入环，以及到环的距离
}f[N];
vector <int> vec[N];
struct node{
	int u,v,next;
}edge[N<<1]; int head[N],num_edge;

il int read()
{
	int f=0,s=0;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f |= (ch=='-');
	for(; isdigit(ch);ch=getchar()) s = (s<<1) + (s<<3) + (ch^48);
	return f ? -s : s;
}

il void add(int from,int to)
{
	edge[++num_edge] = (node){from,to,head[from]};
	head[from] = num_edge;
}

il void tarjan(int x,int in_edge)//边双缩点
{
	dfn[x] = low[x] = ++tot;
	stk[++idx] = x;
	for(re int i=head[x];i;i=edge[i].next)
	{
		int y = edge[i].v;
		if(!dfn[y])
		{
			tarjan(y,i);
			low[x] = min(low[x],low[y]);
		}
		else if(i != (in_edge^1)) low[x] = min(low[x],dfn[y]);
	}
	if(dfn[x] == low[x])
	{
		++cnt;
		while(x != stk[idx+1])
		{
			vec[cnt].push_back(stk[idx]);
			belong[stk[idx]] = cnt;
			idx--;
		}
	}
}

il void bfs(int tp,int x,int dep)//求不在环上的点从哪个点入环，路径长度是多少
{
	f[x] = (Node){tp,dep};
	queue <int> q;
	q.push(x);
	while(!q.empty())
	{
		u = q.front(); q.pop();
		for(re int i=head[u];i;i=edge[i].next)
		{
			v = edge[i].v;
			if(v == tp) continue;
			if(!f[v].dep)
			{
				f[v].dep = f[u].dep + 1 , f[v].tp = tp;
				q.push(v);
			}
		}
	}
}

il void circle()//求断边后链上路径长
{
	memset(len , -1 , sizeof len);
	len[cutx] = 0;
	queue <int> q;
	q.push(cutx);
	while(!q.empty())
	{
		u = q.front(); q.pop();
		for(re int i=head[u];i;i=edge[i].next)
		{
			v = edge[i].v;
			if((u == cutx && v == cuty) || (v == cutx && u == cuty)) continue;
			if(belong[v] != k) continue;
			if(len[v] == -1)
			{
				len[v] = len[u] + 1;
				q.push(v);
			}
		}
	}
}

signed main()
{
	n = read() , q = read();
	num_edge = 1;
	for(re int i=1;i<=n;i++)
	{
		u = read() , v = read();
		add(u,v) , add(v,u);
	}
	tarjan(1,1);//边双缩点找环
	for(re int i=1;i<=cnt;i++) if(vec[i].size() > 1) { k = i; break; }//找哪个是环,步骤一
	for(re int i=2;i<=num_edge;i++)
	{
		u = edge[i].u , v = edge[i].v;
		if(belong[u] == belong[v]) { cutx = u , cuty = v ; continue; }//随便找一条在环上的边
		if(belong[u] == k && belong[v] != k) bfs(u,v,1);//一个在环上一个不在环上,进行步骤二
	}
	circle();//步骤三
	int siz = vec[k].size() , disu , disv;
	while(q--)
	{
		u = read() , v = read();
		if(belong[u] == k) { cout << "Survive" << "\n"; continue; }//原本就在环里那直接跑了
		disu = f[u].dep;//计算路径长度
		if(belong[v] == k) disv = min(abs(len[f[u].tp]-len[v]),siz-abs(len[f[u].tp]-len[v]));//B要拦截的距离就是B到环的距离B的tp和A的tp之间的距离
		else disv = f[v].dep + min(abs(len[f[u].tp]-len[f[v].tp]),siz-abs(len[f[u].tp]-len[f[v].tp]));
		if(disu < disv) cout << "Survive" << "\n";
		else cout << "Deception" << "\n";
	}
	return 0;
}
```


---

## 作者：LHQing (赞：2)

#### 思路分析

$n$ 个点 $n$ 条边的连通图叫做基环树，可以认为其是在普通的树上加了一条边，形成了若干棵树，彼此的根又被联通为一个环。

如果两个人都走到环上，那么一定可以一直在环上绕圈，即 $\rm A$ 胜利。可以推出，若 $\rm A$ 在走到环之前就被 $\rm B$ 堵住，那么 $\rm B$ 获胜。

除了环上，每个点走到环上的路径都是唯一的。我们可以先拓扑排序找出环上所有结点，然后计算出环上两两结点的距离，最后算出每个点到环的距离。

如果 $\rm A$ 和 $\rm B$ 都不在环上，有两种情况：

- $\rm A$ 与 $\rm B$ 进入环的路径重合。即，若断开所有环边，两者在同一个连通块上。

  这种情况很好判断：即距离环较近者获胜。
  
- $\rm A$ 与 $\rm B$ 进入环的路径不重合。即，若断开所有环边，两者不在同一个连通块上。

  若 $\rm B$ 要成功堵住 $\rm A$，则一定要走到 $\rm A$ 进入环的那一点。距离即为两者进入环的点的距离加上 $\rm B$ 到环上的距离。
  
  然后与 $\rm A$ 走到环上的距离比较即可。
  
如何线性求环上点距呢？对于任意两点，仅存在两种路线可以到达。因此我们对环深度优先搜索，对每个点打上时间戳，就可以做到 $\Theta(n+q)$ 求环上两点距离了。

总复杂度 $\Theta(n+q)$。

#### 题解代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define maxn 1000010

using namespace std;

struct ed
{
    int v, nxt;
};

int n, q, head[maxn];
ed e[maxn << 1];
int cnt, deg[maxn], bk[maxn], seq[maxn], idx;
queue<int> que;
int branch[maxn], dep[maxn], dis[maxn];

void add_edge(int u, int v)
{
    e[++cnt].v = v, e[cnt].nxt = head[u];
    head[u] = cnt;
}

void get_ring()
{
    for (int i = 1; i <= n; i++)
    {
        if (deg[i] == 1)
        {
            que.push(i);
            deg[i]--;
        }
    }
    while (!que.empty())
    {
        int u = que.front();
        que.pop();
        for (int i = head[u]; i; i = e[i].nxt)
        {
            int v = e[i].v;
            if (deg[v] >= 1)
                deg[v]--;
            if (deg[v] == 1)
                que.push(v);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (deg[i] >= 2)
            bk[i] = true, seq[++idx] = i;
    }
}

void dfs1(int u, int fa, int s, int d)
{
    branch[u] = s;
    dep[u] = d;
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].v;
        if (v == fa || bk[v])
            continue;
        dfs1(v, u, s, d + 1);
    }
}

void dfs2(int u, int fa, int d)
{
    dis[u] = d;
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].v;
        if (v == fa || dis[v] || !bk[v])
            continue;
        dfs2(v, u, d + 1);
    }
}

int dist(int u, int v)
{
    if (dis[u] - dis[v] >= 0)
        swap(u, v);
    return min(abs(dis[u] - dis[v] + idx), abs(dis[u] - dis[v]));
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> q;
    for (int i = 1, u, v; i <= n; i++)
    {
        cin >> u >> v;
        add_edge(u, v), add_edge(v, u);
        deg[u]++, deg[v]++;
    }
    get_ring();
    for (int i = 1; i <= idx; i++)
        dfs1(seq[i], 0, i, 0);
    dfs2(seq[1], 0, 1);
    while (q--)
    {
        int v, u;
        cin >> u >> v;
        puts(dep[v] + dist(seq[branch[v]], seq[branch[u]]) <= dep[u] ? "Deception" : "Survive");
    }
    return 0;
}
```

---

## 作者：Register_int (赞：2)

可以做到线性。

首先图是个基环树。对于雷切尔，能存活的条件就是要跑到环上，而三角洲则需要围堵雷切尔所在“子树”的入环点。

将环上的点找出，将环边删除分为多个树，设点 $x$ 所在的树根为 $rt_x$，则 $u$ 到 $v$ 的最短距离为 $dep_u+dis(rt_u,rt_v)+dep_v$。环上的距离可以记录每个点的位置，判断正向和反向的距离，之后就能 $O(1)$ 查询了。

最后判断两者到雷切尔入环点的距离，比较大小输出即可。

# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

struct edge {
	int v, nxt;
} e[MAXN];

int head[MAXN], tot;

inline 
void add(int u, int v) {
	e[++tot] = { v, head[u] }, head[u] = tot;
}

int a[MAXN], pos[MAXN], fa[MAXN], cnt;

bool vis[MAXN], col[MAXN];

void dfs(int u, int f) {
	if (col[u]) {
		if (cnt) return ;
		for (int p = f; p != u; p = fa[p]) a[pos[p] = ++cnt] = p;
		return a[pos[u] = ++cnt] = u, void();
	}
	fa[u] = f, col[u] = vis[u] = 1;
	for (int i = head[u]; i; i = e[i].nxt) {
		if (e[i].v != f) dfs(e[i].v, u);
	}
	col[u] = 0;
}

int dep[MAXN], rt[MAXN];

void init(int u, int f, int p) {
	dep[u] = dep[f] + 1, rt[u] = p;
	for (int i = head[u]; i; i = e[i].nxt) {
		if (!col[e[i].v] && e[i].v != f) init(e[i].v, u, p);
	}
}

int n, q;

int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1, u, v; i <= n; i++) scanf("%d%d", &u, &v), add(u, v), add(v, u);
	dfs(1, 0);
	for (int i = 1; i <= cnt; i++) col[a[i]] = 1;
	for (int i = 1; i <= cnt; i++) init(a[i], 0, a[i]);
	for (int x, y, d; q--;) {
		scanf("%d%d", &x, &y), d = (pos[rt[x]] - pos[rt[y]] + cnt) % cnt, d = min(d, cnt - d);
		puts(dep[x] >= dep[y] + d ? "Deception" : "Survive");
	}
}
```

---

## 作者：allqpsi (赞：1)

### 图论题一个。

看题目数据，有 $n$ 个点 $n$ 条边，很明显就是树加一个边。所以只会有一个环。我们只需要判断 $A$ 是否能在 $B$ 
之前到达环就可以了。主要分为三步：

1. 找出图中的环上的点。
2. 找出每个点离的最近的在环上的点，以及到环上的点的最短距离。
3. 判断 $A$ 和 $B$ 谁赢。

第一步，我们可以用列表记录每个点是否到过。然后返回，找到这个点，把途中的点记录下来。

第二步，我们把在环上的点 dfs 一遍。如果比其他环上的点更早到一个点，就把它记录上去。

第三步，我们算是否 $A$ 到环上的速度是否小于 $B$ 到  $A$ 到环上的位置就行了。

#### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
bool vis[200005],huan[200005];
int n,q,a,b,l,huanx[200005],f,chuan[200005],huanf[200005],c1,c2,len;
vector<int>vi[200005];
void dfs1(int x,int fat){
	if(vis[x]){
		f=x;
		huan[x]=true;
		huanx[x]=++l;
		return;
	}
	vis[x]=true;
	for(int i=0;i<vi[x].size();i++){
		int y=vi[x][i];
		if(y!=fat){
			dfs1(y,x);
		}
		if(f){
			if(f==x){
				f=0;
			}
			if(!huan[x]){
				huan[x]=true;
				huanx[x]=++l;
			}
			break;
		}
	}
}
void dfs2(int x,int fat,int k){
	chuan[x]=k;
	huanf[x]=huanf[fat]+1;
	for(int i=0;i<vi[x].size();i++){
		int v=vi[x][i];
		if(!huan[v]&&vi[x][i]!=fat){
			dfs2(v,x,k);
		}
	}
}
int main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a>>b;
		vi[a].push_back(b);
		vi[b].push_back(a);
	}
	dfs1(1,-1);
	memset(huanf,127,sizeof(huanf));
	for(int i=1;i<=n;i++){
		if(huan[i]){
			dfs2(i,0,i);
		}
	}
	for(int i=1;i<=q;i++){
		cin>>a>>b;
		c1=chuan[a];
		c2=chuan[b];
		len=abs(huanx[c1]-huanx[c2]);
		if(len>l/2){
			len=l-len;
		}
		if(huanf[a]<huanf[b]+len){
			cout<<"Survive"<<endl;
		}
		else{
			cout<<"Deception"<<endl;
		}
	}
}
```


---

## 作者：TernaryTree (赞：1)

![](https://cdn.luogu.com.cn/upload/image_hosting/zxc9uiax.png)（x

***

出题人题解。

首先我们来考虑，$n$ 个点 $n$ 条边的连通图长啥样。我们知道，$n$ 个点 $n-1$ 条边的连通图是一棵树。那么加上一条边以后仍然连通，就形成了一个叫做“基环树”的东西，也就是只有一个简单环的图，~~漂亮滴很呐~~。

那么我们如何处理基环树上的信息呢？提供一种简单的思路：把每条环边断掉，我们就得到了一个森林。你会发现森林中每棵树的根都是环上的一个点。换句话说，环上的每个点都是一棵树的根。于是有一个显然的结论是，基环树上每个点都有唯一的一条通向环的路径。记 $\text{rng}_i$ 为点 $i$ 进入环的那一点，也就是森林中这个点所在树的树根；记 $\text{dep}_i$ 为点 $i$ 到环的距离，也就是其所在树的深度。

如何找环呢？较简单的做法是使用拓扑排序。每次找度数为 $1$ 的结点删掉，最后剩下的就是环。例题：[P8655](https://www.luogu.com.cn/problem/P8655)。

然后我们来考虑两人的决策问题。假设 $\rm B$ 在 $\rm A$ 进入环之前就到达了 $\text{rng}_\textrm{A}$，那么这个时候 $\rm A$ 出逃的路径就被堵死了。反之，若 $\rm A$ 在 $\rm B$ 把我们堵死之前就跑到了 $\rm rng_A$，我们想想秦始皇怎么死的？因为环大小 $>4$，所以我们采用“秦王绕柱”的策略，优先走离 $\rm B$ 距离更远的一边，一定不会被抓到。

那么我们如何算 $\text {rng}_i$ 之间的距离呢？普通的 bfs 最短路方法是 $\Theta(n^2)$ 的，无法通过。考虑到这是一个环，环内两点只有顺时针和逆时针两条路径。于是随便选择一条路径 dfs 然后标号，然后两条路径的长度都可以用标号表示，取 $\min$ 即可。

预处理是 $\Theta(n)$ 的，每次询问 $\Theta(1)$。总时间复杂度 $\Theta(n+q)$。

---

## 作者：eastcloud (赞：1)

## 简要题意

给定一棵基环树，A，B 两人都在节点上，互相能知道对方的位置且速度相同，每次询问给定两人位置，问 B 能否抓到 A。

## 题目分析

考虑如果题目给的是一棵树，可以发现 A 肯定逃不掉，B 只要走到根节点之后往 A 的子树走即可。

那么对于基环树，可以先把整个环作为根节点来思考，由于环只有可能是五元环或节点更多，那么只要 A 走到环上，一直与 B 绕圈就赢了（可以想象一下有两个人在绕着一个物体抓人，只要物体足够大，A 就可以牵制住 B）。

于是 B 的获胜策略即为在 A 走到环上之前抓住他，因此只要将它到 A 入环点的最短路径长度与 A 到入环点的最短路径长度进行比较即可，若 A 能更快到达则 A 赢，否则 B 赢。时间复杂度 $O(n+q)$。

## 代码

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector> 
#define ll long long
using namespace std;
vector<int> l[1000001];
int f[1000001],vis[1000001];
int g[1000001],dep[1000001];
int a[1000001];
int tot,all;
void dfs(int x,int fa){
	f[x]=fa;
	vis[x]=++tot;
	for(int i=0;i<l[x].size();i++){
		int v=l[x][i];
		if(v==fa) continue;
		if(!vis[v])dfs(v,x);
		else if(vis[v]>=vis[x]){
			while(v!=x){
				g[++all]=v;
				v=f[v];
			}
			g[++all]=x;
		}
	}
}
void dfs2(int x,int fa,int anc){
	dep[x]=dep[fa]+1;
	a[x]=anc;
	for(int i=0;i<l[x].size();i++){
		int v=l[x][i];
		if(v==fa || vis[v]) continue;
		dfs2(v,x,anc);
	}
}
int main(){
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		int u,v;
		cin>>u>>v;
		l[u].push_back(v);
		l[v].push_back(u);
	}
	dfs(1,0);
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=all;i++) vis[g[i]]=1;
	for(int i=1;i<=all;i++){
		dfs2(g[i],0,g[i]);
		dep[g[i]]=i;
	}
	for(int i=1;i<=q;i++){
		int x,y;
		cin>>x>>y;
		if(all==0) cout<<"Deception"<<endl;
		else if(vis[x]) cout<<"Survive"<<endl;
		else{
			int dis=dep[x]-1,dis2=min(abs(dep[a[y]]-dep[a[x]]),all-abs(dep[a[y]]-dep[a[x]]));
			if(!vis[y]) dis2+=dep[y]-1;
			if(dis2<=dis) cout<<"Deception"<<endl;
			else cout<<"Survive"<<endl;
		}
	}
}

```


---

## 作者：splendore (赞：0)

### 题意
给定一棵不存在四元（及以下）环的基环树，$q$ 次询问 $x,y$，在图上 $x,y$ 点上分别有棋子 $\text{A,B}$。

每次棋子同时沿边移动一步，若 $\text{A}$ 永不与 $\text{B}$ 相遇则 $\text{A}$ 胜利，否则 $\text{B}$ 胜利。

保证 $\text{A,B}$ 不会做出对自己不利的决策。

### 思路
$\text{A}$ 只有进入环中才可能胜利，所以只有在满足：

$\text{A}$ 到环的距离 $>$ $\text{B}$ 到环的距离 $+$ $\text{A}$ 入环点与 $\text{B}$ 入环点的距离时，

有 $\text{A}$ 胜利，否则 $\text{B}$ 胜利。

代码如下：
```
#include<cstdio>
#include<algorithm>
using namespace std;
constexpr int N=200005;
struct edge{int y,pre;}a[N<<1];int alen,last[N];
inline void ins(int x,int y){a[++alen]={y,last[x]};last[x]=alen;}
int n,A,B,d1[N],d2[N];
bool v[N];
int dfn[N],dep[N],f[N],p[N],c[N],id,cl;
void dfs(int x,int fa){
	dfn[x]=++id;f[x]=fa;
	for(int k=last[x];k;k=a[k].pre){
		int y=a[k].y;
		if(y==fa)continue;
		if(!dfn[y])dfs(y,x);
		else if(dfn[y]>=dfn[x])
			while(y!=f[x])
				v[c[++cl]=y]=1,y=f[y];
	}
}
void dfs2(int x,int fa,int t){
	dep[x]=dep[fa]+1;p[x]=t;
	for(int k=last[x];k;k=a[k].pre){
		int y=a[k].y;
		if(y==fa||v[y])continue;
		dfs2(y,x,t);
	}
}
int main(){
	int q;scanf("%d%d",&n,&q);
	for(int i=1,x,y;i<=n;++i){
		scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	dfs(1,0);
	for(int i=1;i<=cl;++i)dfs2(c[i],0,c[i]),dep[c[i]]=i;
	for(int i=1,A,B;i<=q;++i){
		scanf("%d%d",&A,&B);
		if(v[A]){puts("Survive");continue;}
		int t=abs(dep[p[B]]-dep[p[A]]);
		int d1=dep[A]-1,d2=min(t,cl-t)+(v[B]?0:dep[B]-1);
		puts(d1<d2?"Survive":"Deception");
	}
	return 0;
}
```

---

## 作者：未来姚班zyl (赞：0)

## 题目大意

像某音里看见过的一种小游戏一样，一个人在一颗基环树上追逐另一个人，方法是双方交替走一条边。问能否在有限次数内抓到那个人。

## 题目分析

首先如果在树上，则一定是能抓到的，方法是追逐方每次向被追逐方的子树方向走。

所以，环是被追逐方唯一的出路。不难证明，如果双方在五（以及以上）圆环上，被追逐方总可以找到一种周旋的方案，方法是每次往离追逐方较远的地方走。

所以，在环存在的情况下，追逐方能够胜利的唯一方法就是在被追逐方达到环上前就堵住那个环上对应的点。

这个就只需要求距离就好了，复杂度 $O(n+q)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define L x<<1
#define R x<<1|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK l>=Ll&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define pb push_back
#define ull unsigned long long
#define e(x) for(int i=h[x];i;i=nxt[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned int 
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =2e5+5,M=4e6+5,inf=2147000000;
const ll mod=998244353;
using namespace std;
int h[N],to[N*2],nxt[N*2],cnt,n,m;
inline void add(int a,int b){
	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt;
}
bool vis[N],inc[N],ff;
int sizc,fr[N],idc[N],Id[N],bel[N],dep[N],tot;
inline void dfsc(int x,int fa){
	if(ff)return;
	fr[x]=fa,vis[x]=1;
	e(x){
		if(ff)return;
		int y=to[i];
		if(vis[y]&&(y!=fa)){
			int now=x;
			ff=1;
			while(1){
				inc[now]=1,idc[now]=++sizc,Id[sizc]=now;
				if(now==y)return;
				now=fr[now];
			}
		}
		else if(y^fa)dfsc(y,x);
	}
}
inline void dfs(int x,int fa,int root){
	bel[x]=root,dep[x]=dep[fa]+1;
	e(x){
		int y=to[i];
		if((y^fa)&&(!inc[y]))dfs(y,x,root);
	}
}
inline int dist(int x,int y){
	int a=idc[x],b=idc[y];
	return min(abs(a-b),sizc-abs(a-b));
}
int main(){
	n=read(),m=read();
	for(int i=1,x,y;i<=n;i++)x=read(),y=read(),add(x,y),add(y,x);
	dfsc(1,0);
	dep[0]=-1;
	rep(i,1,sizc)dfs(Id[i],0,Id[i]);
	for(int i=1,x,y;i<=m;i++){
		x=read(),y=read();
		if(inc[x]){
			printf("Survive\n");
			continue;
		}
		int dis=dep[y]+dist(bel[x],bel[y]);
		if(dis<=dep[x])printf("Deception\n");
		else printf("Survive\n");
	}
	return 0;
}
```


---

## 作者：_shy (赞：0)

## [P8943 Deception Point](https://www.luogu.com.cn/problem/P8943)
### 思路 $1$ $\mathcal O(n\log n)$ 赛时思路
1. 考虑这个图的构造，发现可以看作是**一个环与其的多颗子树**。易得，若 A 和 B 同时在环上的不同点，则答案便是 "Survive"。于是，问题即求在 A 上环前或恰恰上环时，B 能否赶到 A 的上环点。于是我们需要统计**环上各点之间的距离以及子树上的点到其上环点的距离**。
2. 考虑如何找到环。发现这个图的构造也可以看作是**一棵树上的非父子关系的两点之间多连了一条边**。于是，可以用**并查集**先求出其生成树以找到这条多的边。然后，对这条边的两个端点找其在生成树上的**最近公共最先**，但**不倍增**，就找出来了环。
3. 考虑如何寻找并记录两点之间的距离。发现 $n \le 2\times10^5$，故两点之间距离可以用 map 存。对于子树上的点到其上环点的距离，暴力搜索即可。对于环上两点间的距离，可以用**相对**的思想，即用 $dis_u$ 表示环上一点 $u$  到环上另一固定点 startpoint 的距离，那么环上两点 $u$、$v$ 间的距离便是 $\min (|dis_u-dis_v|,tot-|dis_u-dis_v|)$，$tot$ 为环上的点的总个数。
4. 时间复杂度为 $\mathcal O((n+q)\log n)$。

### 代码 $1$
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 100;
int n, q;
int head[maxn], cnt, cnti, cntii, headii[maxn];
struct edgei 
{
	int u, v;
} ei[maxn << 1];
struct edge 
{
	int v, next;
} e[maxn << 1], eii[maxn << 1];
void add (int tp, int u, int v) 
{
	if (tp == 1) 
		ei[++ cnti] = (edgei) {u, v};
	else if (tp == 0)
		e[++ cnt] = (edge) {v, head[u]},
		head[u] = cnt;
	else 
	{
		eii[++ cntii] = (edge) {v, headii[u]},
		headii[u] = cntii;
	}
}
map <pair <int, int>, int> dis;
void addi (int x, int y, int w) 
{
	dis.insert (make_pair (make_pair (x, y), w));
}
int fquery (int x, int y) 
{
	return (dis.find (make_pair (x, y)) -> second);
}
int f[maxn], vis[maxn], depth[maxn], fi[maxn];
int find (int x) 
{
	while (x != f[x]) x = f[x] = f[f[x]];
	return x;
}
void dfs (int u, int fa, int d) 
{
	depth[u] = d, fi[u] = fa;
	for (int i = head[u]; i; i = e[i].next) 
	{
		int v = e[i].v;
		if (v == fa) continue;
		dfs (v, u, d + 1);
	}
}
int zl[maxn], zp, rl[maxn], rp;
void find_circle (int x, int y) 
{
	if (depth[x] < depth[y]) swap (x, y);
	while (depth[x] > depth[y]) 
	{
		zl[++ zp] = x;
		x = fi[x];
	}
	if (x == y) 
	{
		zl[++ zp] = x;
		return;
	}
	while (fi[x] != fi[y]) 
	{
		zl[++ zp] = x, rl[++ rp] = y;
		x = fi[x], y = fi[y];
	} 
	zl[++ zp] = x, rl[++ rp] = y;
	zl[++ zp] = fi[x];
	return;
}
int wl[maxn], visi[maxn], p;
void Kruskal () 
{
	for (int i = 1; i <= n; i++)
		f[i] = i;
	for (int i = 1; i <= n; i++) 
	{
		int fx = find (ei[i].u), 
			fy = find (ei[i].v);
		if (fx == fy) continue;
		f[fy] = fx, vis[i] = 1;
		add (0, ei[i].u, ei[i].v);
		add (0, ei[i].v, ei[i].u);
	}
	dfs (1, 0, 1);
	for (int i = 1; i <= n; i++)
	{
		if (!vis[i]) 
		{
			find_circle (ei[i].u, ei[i].v);
			for (int j = 1; j <= zp; j++) 
			{
				wl[++ p] = zl[j];
				visi[zl[j]] = 1;
				addi (wl[p], wl[1], p - 1);
			}
			for (int j = rp; j >= 1; j--) 
			{
				wl[++ p] = rl[j];
				visi[rl[j]] = 1;
				addi (wl[p], wl[1], p - 1);
			}
			break;
		}
	}
}
int fii[maxn];
void dfsi (int u, int fa, int fai, int d)
{
	fii[u] = fai;
	addi (u, fai, d);
	for (int i = headii[u]; i; i = eii[i].next) 
	{
		int v = eii[i].v;
		if (v == fa || visi[v]) continue;
		dfsi (v, u, fai, d + 1);
	}
}
int main ()
{
	scanf ("%d %d", &n, &q);
	for (int i = 1; i <= n; i++)
	{
		int u, v;
		scanf ("%d %d", &u, &v);
		add (1, u, v);
		add (2, u, v), add (2, v, u);
	}
	Kruskal ();
	for (int i = 1; i <= n; i++) 
		if (visi[i]) dfsi (i, i, i, 0);
	while (q --) 
	{
		int a, b;
		scanf ("%d %d", &a, &b);
		int di = fquery (b, fii[b]),
			dii = fquery (a, fii[a]),
			diii = fquery (fii[a], wl[1]),
			div = fquery (fii[b], wl[1]);
		int dv = min (abs (diii - div), p - abs (diii - div));
		if (di + dv > dii) printf ("Survive\n");
		else printf ("Deception\n"); 
	}
	return 0;
}
```
### 思路 $2$ $\mathcal O(n)$ 正解
1. 赛后知道了这种图叫做**基环树（$n$ 个点，$n$ 条边的联通图）**，可以实现 $\mathcal O(n)$ 找环。
2. 发现不用 map 便可以存储距离。我们可以用 $dis_i$ 表示某一子树上的 $i$ 到其上环点的距离，用 $fi_i$ 表示 $i$ 的上环点，用 $disi_i$ 表示环上的一点 $i$ 到环上另一固定点 startpoint 的距离，便实现了 $\mathcal O(1)$ 查询。
3. 时间复杂度为 $\mathcal O(n+q)$。

### 代码 $2$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 100;
int head[maxn], cnt;
struct edge 
{
	int v, next;
} e[maxn << 1];
void add (int u, int v) 
{
	e[++ cnt] = (edge) {v, head[u]};
	head[u] = cnt;
} 
int n, q;
int dfn[maxn], vis[maxn], p, f[maxn], tot;
// 找环。
void getloop (int u, int fa) 
{
	dfn[u] = ++ p;
	for (int i = head[u]; i; i = e[i].next) 
	{
		int v = e[i].v;
		if (v == fa) continue;
		if (dfn[v]) 
		{
			if (dfn[v] < dfn[u]) continue;
			for (int x = v; x != f[u]; x = f[x])
				vis[x] = 1, tot ++;
		}
		else f[v] = u, getloop (v, u);
	}
}
// 得环上一点到固定点的距离。
int dis[maxn], start_point, disi[maxn];
void dfs (int u, int fa, int d) 
{
	disi[u] = d;
	for (int i = head[u]; i; i = e[i].next) 
	{
		int v = e[i].v;
		if (v == fa || !vis[v] || v == start_point) continue;
		dfs (v, u, d + 1);
		if (u == start_point) return; // 避免在把环倒着搜一遍。
	}
}
// 找子树上的点的上环点和到上换点的距离。
int fi[maxn]; 
void dfsi (int u, int fa, int fai, int d) 
{
	fi[u] = fai, dis[u] = d;
	for (int i = head[u]; i; i = e[i].next) 
	{
		int v = e[i].v;
		if (v == fa || vis[v]) continue;
		dfsi (v, u, fai, d + 1); 
	}
}
int main ()
{
	scanf ("%d %d", &n, &q);
	for (int i = 1; i <= n; i++) 
	{
		int u, v;
		scanf ("%d %d", &u, &v);
		add (u, v), add (v, u); 
	}
	getloop (1, 0);
	for (int i = 1; i <= n; i++) 
	{ 
		if (!vis[i]) continue;
		if (!start_point)start_point = i, dfs (i, f[i], 0);	
		dfsi (i, i, i, 0); 
	}
	while (q --) 
	{
		int a, b;
		scanf ("%d %d", &a, &b);
		int di, dii, diii;
		di = dis[b], dii = dis[a];
		// 相对得环上两点之间得距离。
		diii = abs (disi[fi[a]] - disi[fi[b]]);
		diii = min (diii, tot - diii);
		// 赶不到则是 A 胜利。
		if (di + diii > dii) printf ("Survive\n");
		else printf ("Deception\n");
	}
	return 0;
}
```

---

## 作者：Forever1507 (赞：0)

线性复杂度。

首先，$n$ 个点 $n$ 条边，连通图，好！基环树！

然后你发现只要 $A$ 跑进了环里，$B$ 就追不上它了，因为互相知道位置可以转圈圈。

那如果我是 $B$，我一定会取把 $A$ 堵在它所在的以环中离 $A$ 最近的点为根节点的子树里。

那么，设这个点为 $X$，如果 $dis(A,X)<dis(B,X)$，$A$ 就赢了。

用割边找到这个环，对于环上每个点向下搜就可以找到每个点的入环点以及和这个点的距离！然后我完全可以求出环中任意两个点的距离，标个号就行了！

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,u[200005],v[200005];
vector<pair<int,int> >nbr[200005];
int dfn[200005],low[200005],cnt,root;
bool cut[200005];
void tarjan(int cur,int edge){
	low[cur]=dfn[cur]=++cnt;
	int num=0;
	for(auto j:nbr[cur]){
		int to=j.first;
		if(j.second==edge)continue;
		if(!dfn[to]){
			tarjan(to,j.second);
			low[cur]=min(low[cur],low[to]);	
			if(low[to]>dfn[cur])cut[j.second]=1;
		}
		else low[cur]=min(low[cur],dfn[to]);
	}
}//tarjan算法求割边
bool vis[200005];
int dis[200005],t[200005];
void dfs(int cur,int fa,int from){//找入环点
	t[cur]=from;
	for(auto j:nbr[cur]){
		int to=j.first;
		if(to==fa||vis[to])continue;
		dis[to]=dis[cur]+1;
		dfs(to,cur,from);
	}
	return;
}
int id[200005],tott,siz;
bool _[200005];
void dfs2(int cur,int fa,int faa){//环内点打标号，算距离。
	id[cur]=++tott;
	_[cur]=1;
	for(auto j:nbr[cur]){
		int to=j.first;
		if(!vis[to]||to==faa||_[to])continue;
		if(to==fa)return;
		dfs2(to,fa,cur);
	}
	return;
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		cin>>u[i]>>v[i];
		nbr[u[i]].push_back(make_pair(v[i],i));
		nbr[v[i]].push_back(make_pair(u[i],i));
	}
	for(int i=1;i<=n;++i)if(!dfn[i])tarjan(i,0);
	queue<int>q;
	for(int i=1;i<=n;++i){
		if(cut[i])continue;
		if(!vis[u[i]])q.push(u[i]),vis[u[i]]=1;
		if(!vis[v[i]])q.push(v[i]),vis[v[i]]=1;
	}
	dfs2(q.front(),q.front(),0);
	siz=q.size();
	while(!q.empty()){
		int cur=q.front();
		dfs(cur,0,cur);
		q.pop();
	}
	for(int i=1;i<=m;++i){
		int x,y;
		cin>>x>>y;
		if(dis[x]<dis[y]+min((id[t[x]]-id[t[y]]+siz)%siz,(id[t[y]]-id[t[x]]+siz)%siz)){
			cout<<"Survive\n";
		}
		else cout<<"Deception\n";
	}
	return 0;
}
```


---

## 作者：masonpop (赞：0)

可以做到复杂度 $O(n+q).$
* 首先转化题意，由于边数 $=$ 点数，因此，这就是一个**基环树**。
* 我们可以拿样例分析一下。(这里已经转化为一个环和若干个分支树的结构）
![](https://cdn.luogu.com.cn/upload/image_hosting/miivjj4t.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)
* 开始时雷切尔在 $8,$ 三角洲在 $6.$
* 我们发现，三角洲第一步到达了 $2,$ 也就是雷切尔的根节点。而雷切尔还没有到达环，因此就失败了。
* 从模拟中，我们可以初步确定两个人会采取的策略，也就是: **雷切尔尽量往环走，三角洲尽量往雷切尔的根结点走。**
* 可以简单说明一下。如果雷切尔刚开始在环上，那它肯定胜利了，不可能被抓到。否则，如果在三角洲到达它的根节点时它还没有到达环，那它就失败了，一定会被一步步逼到一个点。对于三角洲的策略同理。
* 我们设 $dis(x,y)$ 表示 $x$ 和 $y$ 点的最短距离。设雷切尔在 $a_1,$ 根节点为 $b_1,$ 三角洲在 $a_2,$ 根节点为 $b_2.$ 显然，雷切尔到环的距离应当小于雷切尔到它的根的距离，也就是

$dis(a_1,b_1)\leq dis(a_2,b_2)+dis(b_2,b_1).$

* 其中，$a_1$ 到 $b_1,$ $a_2$ 到 $b_2$ 的路径都是唯一的。而 $dis(b_1,b_2)$ 可以通过获取环长和这两个点在环中顺时针的序号得知。
* 这些信息都是可以通过预处理获得的。我的代码可能比较冗长，因为我是分开处理的。
* 具体的，第一遍深搜从任意一个节点开始，开栈记录 $dfs$ 序，实现找环。第二遍从环中的每一个点开始，向以这个点为根的树深搜，获取每个点到它的根的距离 $dis$ 和它对应的根节点 $from$。第三遍从环中一个点开始顺时针遍历环，记录环长和每个点的顺时针编号。之后每次询问 $O(1)$ 查询即可。
* 时间复杂度确实是线性的。
* 代码:
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,q;
const int maxn=4e5+10;
int head[maxn],nxt[maxn],to[maxn],ring[maxn],deg[maxn],tot;
inline void add(int x,int y)
{
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
	deg[x]++;deg[y]++;
}
stack<int> s;
int vis[maxn],stk[maxn];//到环的距离 
int dis[maxn],from[maxn],idx[maxn],now,sum;//from:去向的环上的点
inline void dfs2(int x,int fr)
{
	from[x]=fr;
	for(int i=head[x];i;i=nxt[i])
	{
		int y=to[i];
		if(ring[y] || vis[y])continue;
		vis[y]=1;
		dis[y]=dis[x]+1;
		dfs2(y,fr);
	}
}
inline void dfs3(int x)
{
	++sum;
	idx[x]=++now;
	vis[x]=1;
	for(int i=head[x];i;i=nxt[i])
	{
		int y=to[i];
		if(vis[y] || !ring[y])continue;
		dfs3(y);
	}
}
inline bool dfs(int x,int fa)
{
	if(stk[x])
	{
		ring[x]=1;
		while(s.top()!=x)
		{
			ring[s.top()]=1;
			s.pop();
		}
		s.pop();
		return 1;
	}
	if(vis[x])return 0;
	vis[x]=1;
	s.push(x);
	stk[x]=1;
	for(int i=head[x];i;i=nxt[i])
	{
		int y=to[i];
		if(y==fa)continue;
		if(dfs(y,x))return 1;
	}
	s.pop();
	stk[x]=0;
	return 0;
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	dfs(1,0);
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)if(ring[i])dfs2(i,i);
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)
	{
		if(ring[i])
		{
			dfs3(i);
			break;
		}
	}
	while(q--)
	{
		int x,y;
		scanf("%d%d",&x,&y);//x躲，y抓
		if(ring[x])printf("Survive\n");
		else
		{
			int xneed=dis[x];
			int yneed=dis[y];
			int toring=abs(idx[from[x]]-idx[from[y]]);
			yneed+=min(toring,sum-toring);
			if(xneed<yneed)printf("Survive\n");
			else printf("Deception\n");
		} 
	}
	return 0;
}
```
* 注意：我的代码里面三个搜索由于码风原因不是顺着排布的。但搜索顺序和搜索函数名一致。

---

## 作者：__ex (赞：0)

~~样例的图有点小乱，用这张看吧。~~

![](https://cdn.luogu.com.cn/upload/image_hosting/1xdazrfc.png)

首先，因为它有 $n$ 个点 $n$ 条无向边而且是个连通图，所以环有且只有一个。然后就考虑 dfs 标记环上的点。

~~我赛时用缩点的方法找环出了点小问题，因为这是无向图。我太菜了就没继续往这边想。~~

观察样例发现，$A$ （就是求生者）只要活着进环就赢了，$B$ 只要在 $A$ 进环之前走到 $A$ 的进环入口就赢了，且 $A$ 和 $B$ 同时到达入口是 $B$ 赢了，所以用点 $C$ 表示 $A$ 的入环口，则 $A$ 到 $C$ 的距离小于 $B$ 到 $C$ 的距离就是 $A$ 赢，反之则 $B$ 赢。

则我们需要把每一个点距离**环上的最近的点**先求出来，用 $bel$ 表示，并求出每个点距离**环上最近的点**的距离，用 $dis$ 表示（对于环上每个点跑 dfs 把每个点对应的子树标记起来就好了），然后对环上的点重新编号（相邻的点相差 $1$ ，$1$ 和 $cnt$ 除外），用 $num$ 表示。

则，$A$ 获胜的充要条件是 $dis_u < dis_v + \min\{(num_{bel_u} - num_{bel_v} + cnt)\bmod cnt , cnt - (num_{bel_u} - num_{bel_v} + cnt)\bmod cnt\}$

### CODE

```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T>inline T read(){
    T a=0;bool s=0;
    char ch=getchar();
    while(ch>'9' || ch<'0'){
        if(ch=='-')s^=1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9'){
        a=(a<<3)+(a<<1)+(ch^48);
        ch=getchar();
    }
    return s?-a:a;
}
const int mn=2e5+10;
struct Eg{
    int ver,nex;
}e[mn<<1];
int head[mn],tot;
inline void add_edge(int sta,int end){
    e[++tot].ver=end;
    e[tot].nex=head[sta];
    head[sta]=tot;
}
int dfn[mn],tim;
int bel[mn],dis[mn],cnt,pre[mn],num[mn];
bool o[mn];
void predfs(int now){
	dfn[now]=++tim;
	for(int i=head[now];i;i=e[i].nex){
		int sub=e[i].ver;
		if(sub==pre[sub])continue;
		if(dfn[sub]){
			if(dfn[sub]<dfn[now])continue;//sub已经访问过，直接continue
			o[sub]=1;num[sub]=++cnt;
			while(sub!=now){
                o[pre[sub]]=1;
                num[pre[sub]]=++cnt;
                sub=pre[sub];
            }
		}
		else pre[sub]=now,predfs(sub);
	}
}
void dfs(int now,int fa){
    dis[now]=dis[fa]+1;
    bel[now]=bel[fa];
    for(int i=head[now];i;i=e[i].nex){
        int sub=e[i].ver;
        if(sub==fa || o[sub])continue;
        dfs(sub,now);
    }
}
int main(){
    int n=read<int>(),q=read<int>();
    for(int i=1;i<=n;i++){
        int u=read<int>(),v=read<int>();
        add_edge(u,v);add_edge(v,u);
    }
    dis[0]=-1;
    predfs(1);
    for(int i=1;i<=n;i++)
        if(o[i])bel[i]=i;
    for(int i=1;i<=n;i++)
        if(o[i])dfs(i,bel[i]);
    for(int i=1;i<=q;i++){
        int u=read<int>(),v=read<int>();
        if(dis[u]<dis[v]+min((num[bel[u]]-num[bel[v]]+cnt)%cnt,cnt-(num[bel[u]]-num[bel[v]]+cnt)%cnt))
            puts("Survive");
        else puts("Deception");
    }
    // while(1)getchar();
    return 0;
}
```



---

## 作者：JackMerryYoung (赞：0)

# 前言

简单图论。

# 正文

发现题目里的图给的是基环树，那就是一眼题了。

回想一下 IOI 2008 Island, 这道题求的是差不多的东西。

首先这题询问数比较多，考虑预处理。那么很显然处理两者到环上的距离和环上各个点之间距离。

那么只要判断三角洲一号是否有足够时间到雷切尔去往环的路径上第一个环上的点前面等着就行。

由于不存在四元及以下的环，所以只要雷切尔跑到环上她就能活下来。

复杂度 $\mathcal{O}(N + Q)$，显然可以通过。

# 代码

``` cpp
#include <bits/stdc++.h>
using namespace std;

int N, Q;

int head[200005], cnt;
struct Edge {
    int to, nxt;
} edge[400005];

void add(int u, int v)
{
    ++ cnt;
    edge[cnt].to = v;
    edge[cnt].nxt = head[u];
    head[u] = cnt;
}

vector<int> circle;
int idx, circnt, dfn[200005], pre[200005], cnum[200005];

void dfs(int u)
{
    dfn[u] = ++ idx;
    for(int i = head[u]; i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if(v != pre[u])
        {
            if(dfn[v])
            {
                if(dfn[u] > dfn[v])
                    continue;
                
                circle.push_back(v);
                for(; v != u; v = pre[v]) circle.push_back(pre[v]);
            }
            else
                pre[v] = u, dfs(v);
        }
    }
}

int color[200005], mindis[200005];
bool doc[200005];

void paint(int u, int fa, int clr)
{
    color[u] = clr;
    for(int i = head[u]; i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if(v != fa && !doc[v])
        {
            mindis[v] = mindis[u] + 1;
            paint(v, u, clr);
        }
    }
}

int getdis(int x, int y)
{
    return min(abs(cnum[x] - cnum[y]), circnt - abs(cnum[x] - cnum[y]));
}

int main()
{
    cin >> N >> Q;
    for(int i = 1; i <= N; ++ i)
    {
        int u, v;
        cin >> u >> v;
        add(u, v);
        add(v, u);
        pre[i] = i;
    }

    
    dfs(1);
    for(auto i : circle) // Cut the circle
        doc[i] = true;

    for(auto i : circle) // Paint the circle-based tree
        paint(i, 0, i);

    for(auto i : circle)
        cnum[i] = ++ circnt;

    for(int i = 1; i <= Q; ++ i)
    {
        int x, y;
        cin >> x >> y;
        if(mindis[x] < mindis[y] + getdis(color[x], color[y]) || doc[x])
            puts("Survive");
        else 
            puts("Deception");
    }
    
    return 0;
}
```

# 后言

这题并不难，但是我竟然写挂了。

---

