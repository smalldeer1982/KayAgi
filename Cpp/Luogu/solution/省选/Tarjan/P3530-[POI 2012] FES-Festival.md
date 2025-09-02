# [POI 2012] FES-Festival

## 题目背景

在 Byteburg 举办了一场慈善活动，你是其中一个筹款人。不幸的是，你错过了一些有趣的活动，包括一场越野赛。

谜题爱好者 Byteasar 承诺：如果你能解开他的谜题，他会捐一大笔钱。

## 题目描述

你不知道越野赛的结果，但 Byteasar 会告诉你部分信息。现在，他要你答出：所有参赛者最多能达到多少种不同的成绩，而不违背他给的条件。（他们中的一些人可能平局，也就是同时到达终点，这种情况只算有一种成绩）。

Byteasar 告诉你，所有参赛者的成绩都是整数秒。他还会为你提供了一些参赛者成绩的关系。具体是：他会给你一些数对 $(A, B)$，表示 $A$ 的成绩正好比 $B$ 快 $1$ 秒；他还会给你一些数对 $(C, D)$，表示 $C$ 的成绩不比 $D$ 慢。而你要回答的是：所有参赛者最多能达到多少种不同的成绩，而不违背他给的条件。

请你编程解决这个谜题。

## 说明/提示

答案为 $3$，情况为：$t_3=1, t_1=t_4=2, t_2=3$。  
（$t_i$ 表示参赛者 $i$ 花的时间）

**【数据范围】**

对于 $15\%$ 的数据，$n \le 10$。  
对于 $100\%$ 的数据，$2 \le n \le 600$，$1 \le m_{1} + m_{2} \le {10}^5$。

## 样例 #1

### 输入

```
4 2 2
1 2
3 4
1 4
3 1
```

### 输出

```
3
```

# 题解

## 作者：cminus (赞：29)

感觉部分题解表述有一点点难以理解，所以蒟蒻第一次尝试自己写题解。

### 题目分析
---

仔细考虑这道题，从不等式上来看显然是要差分约束建图的，每个点之间的关系错综复杂，但是我们来看两个点，如果它们之间能互相到达，说明它们t值的差有确定的一个上界和下界，这时候这两个点之间的关系是互相确定的，他们之间的差才有意义，如果只是单向的关系，他们之间并不能确定差值关系。

基于此，如果有一个集合里面包含的所有的点，这些点都可以互相到达（就是一个强连通分量），那这个集合中任意两个点的差值关系都是确定的，此时这个集合中所有点之间最短路的最大值加一的就是这一个集合的答案。

#### 为什么是所有点之间最短路的最大值 + 1 ？

这是这道题的特殊之处，因为题目限制只有两种，一种是相差 1，另一种是 $t(a)<t(b)$ 的限制，此时我们使用差分约束的原理建出来的边权值只有 $1，0，-1$ 这三种，最终算出的**正**差值虽然是权值之差，却恰好可以反映出它们之间应该有多少个不同值的数量 $-1$。

举例而言：

+ 存在边 $dis(1, 2) = 1, dis(2, 3) = 1, dis(2, 4) = 1$，那么$dis(1, 4)=3$，这个3既是1和4之间的差值上界（即 $dis(4)-dis(1)$ ），又能表示 $1$ 和 $4$ 中间（包括 $1，4$ )有 $3+1$ 个数字个数字，因此 $dis(1, 4)$ 反应的就是不同取值的数量 $-1$。

+ 但是如果题目不一定是相差 $1$，例如 $1$ 和 $2$ 相差 $5$，还用上面的方法就会算出 $6$ 的奇怪数字，因为我们上面的前提就不存在了。

然后对于不同连通块，显然，他们之间要么没有边，要么是单向边，是没有影响可以做到互不重叠的。

**总结一下**
+ 根据差分约束的规则建图，先用 Tarjan 找到所有强连通分量，对图中每个强连通分量内使用 Floyd 跑最短路，把每一个连通块中最短路最大值 $+1$ 加起来就是我们的答案。
+ 如果 $dis(x, x) < 0$ ，说明无解。

有了上面这些理论，剩下的就是平平无奇的建图。

#### 建图方式：

例如：
$$
t(B) <= t(A) + 1
$$
在最短路中，对于某条边，dis数组满足如下条件：
$$
dis(to) <= dis(from) + w
$$
故我们以dis作为我们相求的答案，加一条边 ```Add(A, B, 1)``` 就可以保证 dis 数组满足我们的要求。

#### 无解的情况：

结合定义，$dis(x, y)$ 表示的是 $dis(y) - dis(x)$，就是 y 比 x 最多大了的值，考虑对这道题而言无解的情况，显然，$dis(x, x)$ 表示的是 x 比 x 最多大的值，即 $dis(x)-dis(x)$ 的最大值，这个数字肯定不能小于0。

所以判断有没有 $dis(x, x)$ 小于0就知道有没有无解了。

#### 最后的一点思考：

有一些题解说这道题根据差分约束的条件建边，然后直接 Floyd 跑最短路找最长路就可以，但是因为会T所以才需要缩点，刚看到的时候疑惑了整整一天没想明白，例如：

给出一个 $1$ 的时间小于 $2$ 时间的限制条件，此时最长路为 $0$，最长路 $+1$ 也是 $1$，但是显然它们可以最多取两种时间。

当我做完这道题再回头去看刚开始的想法，其实发现了一些有趣的事情，就是如果不管每个点属不属于同一个强连通分量，直接建完图就去跑 Floyd 的话，对于在同一个强连通分量里的点之间的最短路是没有影响的。

就是说如果不会 TLE 的话，刚开始直接建图跑最短路，然后找到所有强连通分量，把所有连通块最短路最大值 $+1$ 加起来我们的答案了。

因为如果某个在强连通外的点能更新这个强连通分量内某两个点的距离，那它一定也属于这个强连通分量，矛盾了，所以整个一起算和单独算每个强连通分量是等价的。

以上。

### 代码
---

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 610;
int dis[N][N], low[N], dfn[N], num[N], t, n, ans[N];
bool vis[N];
stack < int > s;
void Tarjan(int u) {
	low[u] = dfn[u] = ++t;
	s.push(u); vis[u] = true;
	for (int i = 1; i <= n; i++)
		if (dis[u][i] <= 1) {
			if (!dfn[i]) {
				Tarjan(i);
				low[u] = min(low[i], low[u]);
			}
			else if (vis[i])
				low[u] = min(low[u], dfn[i]); 
		}
	if (dfn[u] == low[u]) {
		int v = s.top(); s.pop();
		while (u != v) {
			num[v] = u;
			vis[v] = false;
			v = s.top(); s.pop();
		}
		num[v] = u;
		vis[v] = false;
	}
}
int main() {
	int m1, m2;
	scanf("%d%d%d", &n, &m1, &m2);
	memset(dis, 0x3f, sizeof(dis));
	for (int i = 1; i <= m1; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		dis[a][b] = min(1, dis[a][b]); 
		dis[b][a] = min(-1, dis[b][a]); 
	}
	for (int i = 1; i <= m2; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		dis[b][a] = min(dis[b][a], 0);
	}
	for (int i = 1; i <= n; i++) {
		dis[i][i] = 0;
		if (!dfn[i])	Tarjan(i);
	}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			if (num[i] == num[k] && dis[i][k] != 0x3f3f3f3f)
				for (int j = 1; j <= n; j++)
					if (num[i] == num[j])
						dis[i][j] = min(dis[i][k] + dis[k][j], dis[i][j]);
	bool flag = true;
	for (int i = 1; i <= n; i++) {
		if (dis[i][i] < 0) {
			flag = false;
			break;
		}
		for (int j = 1; j <= n; j++) 
			if (num[i] == num[j])
				ans[num[i]] = max(ans[num[i]], dis[i][j] + 1);
	}
	if (!flag)	puts("NIE");
	else {
		int tot = 0;
		for (int i = 1; i <= n; i++)
			tot += ans[i];
		printf("%d\n", tot);
	}	
	return 0;
}
```



---

## 作者：chenxia25 (赞：23)

啥？pigeon ycx 又回来补差分约束了？有生之年。

---

**[Portal]( https://www.luogu.com.cn/problem/P3530 )**

这是一个挺厉害的差分约束。

首先建出差分约束系统。然后它要你求的是不同成绩的最大数量，而差分约束只擅长做「两个变量的差的最大 / 小值」这种问题，如何转化过去呢？

注意到对于**任意**差分约束系统，这个点与点的连通性是非常混乱的，无法判断点和点和点和点之间到底能不能拉开，还是必须重叠的什么情况。我们考虑一个强连通图，这里面每个点到每个点都可以互相到达，也就是说任意两个变量的差都有有限的上下限。那就很好了呀，我们至少知道了它的不同成绩的数量的一个上限：我们总要选两个点当作值域的两端对不对，而每两个点的差都是有有限上限的，于是取那个最大的距离（也就是最大的一对点之间的最短路）就是上限了。接下来考虑上限能不能达到，很容易证明可以，因为在那条最大的最短路上，一路走的过程中每次加一，都一定是第一种限制做的功劳，而第一种限制是定量限制，限制死了的，所以一旦把值域的两端确定下来，中间都填的满满的。

至此我们已经知道一个强连通图的求法了。考虑将原图强连通分解，然后每个 SCC 求出来答案，再缩点发现是个 DAG。DAG 也是个连通性特殊的有向图，它也好办了呀，没有任意两个 SCC 间有相互的限制，也就是说我们可以沿着边的方向将两个 SCC 之间的距离无限拉大，这样每个 SCC 就是独立的了，把所有 SCC 答案加起来也就达到了上限。

然后考虑实现？强连通分解用 Tarjan，然后最短路的话因为 $n$ 只有 $600$ 可以 Floyd 三行搞定（包括判负环）（不过要开 O2）。

**_[code]( https://www.luogu.com.cn/paste/v26j2ux9 )_**

---

## 作者：Llf0703 (赞：12)

[更好的阅读体验](https://llf0703.com/p/luogu-3530.html)

## 题意

有 $N$ 个数和 $M_1+M_2$ 种关系。前 $M_1$ 种关系 $(x,y)$ 表示 $S_x+1=S_y$ ，后 $M_2$ 种关系表示 $S_x\le S_y$ 。求最多有多少个数字值。如果无解输出 `NIE` 。

$N\le 600 , M_1+M_2\le 100000$ 。

## 题解

不等式关系可以先差分约束建图。边 $(x,y)$ 的权值表示 $S_x-S_y$ 的最大值，对于 $M_1$ 就连边 $(x,y,-1)$ 和 $(y,x,1)$ ，对于 $M_2$ 就连 $(x,y,0)$ 。显然最长路径 $+1$ 就是答案。

容易想到用 $\text{Floyd}$ 来实现，但 $N^3\approx 2\times 10^8$ ，会爆。

不过可以发现强连通分量之间是没有关系的，所以可以对每个强连通分量跑最长路径。因为数值的个数都要 $+1$ ，所以最后的答案为 最长路径和 $+$ 强连通分量个数。

但如果存在非 $0$ 环就可能无解，所以需要判环。**其它题解说正环也不合法，我感觉是错误的。**如下例：

```
4 3 1
2 1
3 2
1 4
3 4
```

建边的方法为（因为Graph Editor画出来两条边会重在一起所以就不放图了自己画一下吧）

```
1 2 1
2 1 -1
2 3 1
3 2 -1
4 1 1
1 4 -1
3 4 0
```

这个图里是有正环的，但仍然有解，答案显然为 $4$ 。

继续分析可以发现，正环无解的情况仅有环上**全为 $1$**这一种，否则就可以把权值为 $0$ 的边拆开使其满足条件。

不过全为 $1$ 的情况下反过来走就是个负环，所以**可以只判负环**。跑完 $\text{Floyd}$ 后如果存在 $dis[i][i] < 0$ ，就说明有负环。

最后对每个强连通分量记录最长路径，加起来统计答案即可。

注意：对于读入，如果有多组限定关系应该选择较小的那个，所以需要取最小值。

```cpp
#include<bits/stdc++.h>

using namespace std;

inline int read()
{
    char ch=getchar();
    int f=1,x=0;
    while (ch<'0' || ch>'9')
    {
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return f*x;
}

struct Edge {
    int next,to,w;
} edge[200005];
stack <int> s;
int scnt,dfsord,id[605],low[605],scc[605];
int cnt,head[605],n,m1,m2,a,b,dis[605][605],mx[605],ans;

inline void add(int u,int v,int w)
{
    edge[++cnt].to=v;
    edge[cnt].next=head[u];
    edge[cnt].w=w;
    head[u]=cnt;
}

void dfs(int x) //Tarjan
{
    s.emplace(x);
    id[x]=low[x]=++dfsord;
    for (int i=head[x];i;i=edge[i].next)
    {
        int y=edge[i].to;
        if (!id[y])
        {
            dfs(y);
            low[x]=min(low[x],low[y]);
        }
        else if (!scc[y]) low[x]=min(low[x],id[y]);
    }
    if (id[x]==low[x])
    {
        scnt++;
        while (!s.empty())
        {
            int t=s.top(); s.pop();
            scc[t]=scnt;
            if (t==x) break;
        }
    }
}

signed main()
{
    n=read(); m1=read(); m2=read();
    memset(dis,0x3f,sizeof(dis));
    for (int i=1;i<=n;i++) dis[i][i]=0;
    for (int i=1;i<=m1;i++)
    {
        a=read(); b=read();
        add(a,b,-1); add(b,a,1);
        dis[a][b]=min(dis[a][b],-1); dis[b][a]=min(dis[b][a],1); //取
    }
    for (int i=1;i<=m2;i++)
    {
        a=read(); b=read();
        add(a,b,0);
        dis[a][b]=min(dis[a][b],0);
    }
    for (int i=1;i<=n;i++)
    {
        if (id[i]) continue;
        dfs(i);
    }
    for (int k=1;k<=n;k++)
    {
        for (int i=1;i<=n;i++)
        {
            if (scc[i]!=scc[k]) continue;
            for (int j=1;j<=n;j++)
            {
                if (scc[j]!=scc[i]) continue;
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]); //对每个强连通分量求出最短路
            }
        }
    }
    for (int i=1;i<=n;i++) if (dis[i][i]) return 0&puts("NIE"); //判负环
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=n;j++)
        {
            if (scc[i]!=scc[j]) continue;
            mx[scc[i]]=max(mx[scc[i]],dis[i][j]); //强连通分量
        }
    }
    for (int i=1;i<=scnt;i++) ans+=mx[i];
    return !printf("%d",ans+scnt);
}
```

---

## 作者：LONV_HY (赞：8)

# **题解**

（写这道题的时候又忘记该怎么写差分约束模板了，然后跑回原题，又忘记了一些东西，在@big_turkey 博客终于复习完了。

首先依据题意我们可以确定 $\text{m1}$ 是已经明确量之间的关系，那么根据模板，我们可以建边 $\text{add(x,y,-1)}$  ， $\text{add(y,x,1)}$。（$x=y+1$ 等价于 $x≤y+1\  \ \text{并且} \ \ y≤x-1$）

对于 $\text{m2} $ 我们建边 $\text{(x,y,0)}$。（$x\le y$）

那么答案便是最长路 $+1$。

可以用 $\text{Floyd}$ 实现，不过会爆。

不过，我们可以发现在一个强连通中，他们的关系是可以确定的，那什么时候他们的关系是矛盾的？

分情况讨论：

1. 负环：显然当一个环是负环它是不合法的。

2. 正环：那么是正环呢，稍微思考可以发现，当环上的都为 $1$ 是，它是矛盾的。 当它带有一条边权为 $0$ 的边，它与边权为 $1$的区别是没有限制 $y$ 比 $x$ 大多少，故带有 $0$ 权的正环可行。

3. 零环：显然他们可以相等，可行。

终上，我们只需要处理是负环和边权都为 $1$ 的环。对于负环容易判断，对于边权都为 $1$ 的环，我们看到属于 $\text{m1}$ 的我们建了两条，一正一反，所以我们仍然可以通过判断负环来判断掉边权都为 $1$ 的正环。

那么多个强连通分量的贡献是什么？

我们可以发现连接强连通之间的边必定是属于 $\text{m2}$ 的边，那么我们可以不必在乎强连通之间究竟大多少，我们可以知道各个强连通皆可以对答案产生贡献。

那么最后答案就为：各个强连通内的最长路 $+$ 连通分量的个数。

代码：

```c
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,m1,m2;
int dis[666][666];
int head[666],cnt;
int vis[666];
struct node{
	int to,nex,z;
}a[200005];
void add(int x,int y,int z){
	a[++cnt].to=y;
	a[cnt].nex=head[x];
	a[cnt].z=z;
	head[x]=cnt;
}
int low[666],dfn[666],xu;
int z[666],tot;
int ccnt;
int pan[666];
void tarjan(int x){
	low[x]=dfn[x]=++xu;
	vis[x]=1;
	z[++tot]=x;
	for(int i=head[x];i;i=a[i].nex){
		int y=a[i].to;
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(vis[y]){
			low[x]=min(low[x],dfn[y]);
		}
	}
	if(dfn[x]==low[x]){
		ccnt++;
		while(true){
			pan[z[tot]]=ccnt;
			vis[z[tot]]=0;
			tot--;
			if(z[tot+1]==x) break;
		}
	}
}
int v[666];
int ans;
int main(){
	memset(dis,0x3f,sizeof(dis));
	scanf("%d%d%d",&n,&m1,&m2);
	for(int i=1;i<=n;i++){
		dis[i][i]=0;
	}
	while(m1--){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y,-1);
		add(y,x,1);
		dis[x][y]=-1;
		dis[y][x]=1;
	}
	while(m2--){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y,0);
		if(dis[x][y]==0x3f3f3f3f) dis[x][y]=0;//当x与y没有定量关系是才设为定性关系 
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]){
			tarjan(i);
		}
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			if(pan[i]!=pan[k]||dis[i][k]==0x3f3f3f3f) continue;//！！！||后半部分是来剪枝的，这样可以过第八个点。 
			for(int j=1;j<=n;j++){
				if(pan[j]!=pan[i]||dis[k][j]==0x3f3f3f3f) continue;//！！！ 
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
			}
		}
	}
	for(int i=1;i<=n;i++) if(dis[i][i]){printf("NIE\n");return 0;};//判负环 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(pan[i]!=pan[j]) continue;
			v[pan[i]]=max(v[pan[i]],dis[i][j]);
		}
	}
	for(int i=1;i<=ccnt;i++){
		ans+=v[i];
	}
	printf("%d",ans+ccnt);
	return 0;
}
```


---

## 作者：ysner (赞：6)

看到不等式就可以想到差分约束。

根据一些差分约束小常识，可以设$dis[x][y]$表示$a_x$**最多**能比$a_y$大多少。

于是对第一类，$dis[x][y]=1,dis[y][x]=-1$。（双向边适用于定量比较）

第二类，由于是$a_y\geq a_x$,$dis[y][x]=0$。（单向边适用于定性比较）

一般来说，图中只要有非$0$环就是不合法的。

观察一下建边，可以发现如果有正环，它的反边就会构成负环。

于是只要判负环就可以了。

如何判负环？

$SPFA$判负环、$floyd$判断$dis[i][i]<0$都可以。

然而这题用前者会出现点小坑。

因为我们一般出发都会以$1$为起点，而这一个图中$1$不一定与负环联通。
怎么办？

跑$tarjan$找出联通块。虚构一个结点，与各个联通块建边权为$0$的边（主要注意防止因该结点的建立而产生新的负环），然后从虚构点出发$SPFA$即可。

缩完点后，图中只剩边权为$0$的边连接各联通块（第一类自己就能构成一个块）。由于“大于等于”这个关系不限制绝对大小，因而对答案没有影响（因可以无限扩大各联通块的值），可以忽略这些边。

于是各联通块内$maxdis+1$之和即为答案。
（话说**只在联通块内跑$floyd$**的效率真是恐怖，$SPFA$判负环成了复杂度瓶颈）

完了？然而还要注意限制条件可以叠加，所以$dis$的赋值要取$\min$。
```
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#define re register
#define il inline
#define ll long long
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define fp(i,a,b) for(re int i=a;i<=b;i++)
#define fq(i,a,b) for(re int i=a;i>=b;i--)
using namespace std;
const int mod=1e9+7,N=605;
struct Edge{int to,nxt,w;}e[N*400];
int n,m1,m2,h[N],cnt,dis[N],dfn[N],low[N],tim,sta[N],top,scc,bl[N],sz[N],num[N],d[N][N];
bool vis[N];
ll ans;
queue<int>Q;
il void add(re int u,re int v,re int w){e[++cnt]=(Edge){v,h[u],w};h[u]=cnt;}
il ll gi()
{
   re ll x=0,t=1;
   re char ch=getchar();
   while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
   if(ch=='-') t=-1,ch=getchar();
   while(ch>='0'&&ch<='9') x=x*10+ch-48,ch=getchar();
   return x*t;
}
il void tarjan(re int u)
{
  dfn[u]=low[u]=++tim;vis[u]=1;sta[++top]=u;
  re int v;
  for(re int i=h[u];i+1;i=e[i].nxt)
    {
      re int v=e[i].to;
      if(!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
      else if(vis[v]) low[u]=min(low[u],dfn[v]);
    }
  if(dfn[u]==low[u])
    {
      ++scc;
      do{v=sta[top];bl[v]=scc;vis[v]=0;++sz[scc];top--;}while(u^v);
    }
}
il int fSPFA(re int st)
{
  memset(dis,63,sizeof(dis));memset(vis,0,sizeof(vis));memset(num,0,sizeof(num));
  while(!Q.empty()) Q.pop();
  dis[st]=0;num[st]=1;Q.push(st);vis[st]=1;
  while(!Q.empty())
    {
      re int u=Q.front();Q.pop();
      for(re int i=h[u];i+1;i=e[i].nxt)
    {
      re int v=e[i].to;
      if(dis[v]>dis[u]+e[i].w)
        {
      if((++num[v])>n) return 0;
          dis[v]=dis[u]+e[i].w;
          if(!vis[v]) vis[v]=1,Q.push(v);
        }
    }
      vis[u]=0;
    }
  return 1;
}
int main()
{
  memset(h,-1,sizeof(h));memset(d,63,sizeof(d));
  re int u,v;
  n=gi();m1=gi();m2=gi();
  fp(i,1,m1) u=gi(),v=gi(),add(u,v,1),add(v,u,-1),d[u][v]=min(d[u][v],1),d[v][u]=min(d[v][u],-1);
  fp(i,1,m2) u=gi(),v=gi(),add(v,u,0),d[v][u]=min(d[v][u],0);
  fp(i,1,n) d[i][i]=min(d[i][i],0);
  fp(i,1,n) if(!dfn[i]) tarjan(i);
  memset(vis,0,sizeof(vis));
  fp(i,2,n)
    if(!vis[bl[i]])
      add(0,i,0),vis[bl[i]]=1;
  memset(vis,0,sizeof(vis));
  //if(!fSPFA(0)) {puts("NIE");return 0;}
  fp(o,1,scc)
  {
    re ll mx=0;
    fp(k,1,n)
    {
      if(bl[k]!=o) continue;
      fp(i,1,n)
      {
    if(bl[i]!=o||d[i][k]==d[0][0]) continue;
        fp(j,1,n)
      {
        if(bl[j]!=o||d[k][j]==d[0][0]) continue;
        d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
      }
      }
    }
    fp(i,1,n)
      {
    if(bl[i]!=o) continue;
    fp(j,1,n)
      {
        if(bl[j]!=o) continue;
        mx=max(mx,d[i][j]);
      }
      }
    ans+=mx+1;
  }
  fp(i,1,n) if(d[i][i]<0) {puts("NIE");return 0;}
  printf("%lld\n",ans);
  return 0;
}
```

---

## 作者：破壁人 (赞：5)

看到题目的约束条件很容易就可以想到差分约束建图。

先判断一下有没有非零环，有的话无解。

由于有零环的存在，所以图中每个强连通块之间没有任何关系。

所以我们先缩点，由于缩点后成了所有边权都为零的dag(有向无环图)

所以对于每个强连通分量分别求解，累加即可。

当然n只有600，floyed即可，但直接floyed会被T飞。

我们在floyed的时候如果两个点不在同一个强连通分量中就可以剪掉。

当然这样并不是最保险的，虽然可以过大部分数据，但还是可以卡掉的。

所以最保险的是对每个点都求一遍spfa或迪杰斯特拉堆优化，这里写的是floyed。






```cpp
#include<cstdio>
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
vector<int> a[601];
int low[601],dfn[601],cnt=0,dis[601][601],position[601],ma[601],stack[601],h=0,z=0;
bool v[601],f[601];
void tarjan(int o)
{
    h++;
    stack[h]=o;
    f[o]=true;
    z++;
    low[o]=dfn[o]=z;
    for(int i=0;i<a[o].size();i++)
        if(!v[a[o][i]])
        {
            v[a[o][i]]=true;
            tarjan(a[o][i]);
            low[o]=min(low[o],low[a[o][i]]);
        }else
        if(f[a[o][i]])
            low[o]=min(low[o],dfn[a[o][i]]);
    if(low[o]==dfn[o])
    {
        cnt++;
        while(stack[h]!=o)
        {
            position[stack[h]]=cnt;
            f[stack[h]]=false;
            h--;
        }
        position[stack[h]]=cnt;
        f[stack[h]]=false;
        h--;
    }
}
int main()
{
    int n,k1,k2;
    cin>>n>>k1>>k2;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            dis[i][j]=1000000000;
    for(int i=1;i<=n;i++) dis[i][i]=0;
    for(int i=1;i<=k1;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
        dis[x][y]=min(dis[x][y],1);
        dis[y][x]=min(dis[y][x],-1);
    }
    for(int i=1;i<=k2;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[y].push_back(x);
        dis[y][x]=min(dis[y][x],0);
    }
    memset(v,0,sizeof(v));
    memset(f,0,sizeof(f));
    memset(low,0,sizeof(low));
    memset(dfn,0,sizeof(dfn));
    for(int i=1;i<=n;i++)
        if(!v[i])
        {
            v[i]=true;
            tarjan(i);
        }
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            if(position[k]==position[i])
                for(int j=1;j<=n;j++)
                    if(position[i]==position[j])
                        dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
    for(int i=1;i<=n;i++)
        if(dis[i][i]!=0){cout<<"NIE"<<endl;return 0;}
    for(int i=1;i<=n;i++) ma[i]=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(position[i]==position[j])
                ma[position[i]]=max(ma[position[i]],dis[i][j]);
    int ans=0;
    for(int i=1;i<=cnt;i++) ans+=ma[i];
    cout<<ans+cnt<<endl;
    return 0;
}
```

---

## 作者：神眷之樱花 (赞：3)

# 题面
[P3530 [POI2012]FES-Festival](https://www.luogu.com.cn/problem/P3530)
# 题意
在满足给定的条件下，求出赛车手的成绩可能的取值有多少种。
# 解析
### 差分约束
不等式关系自然联想到差分约束。
* 对于第一种不等式
因为给定了相差的值，所以建双向边：
$$dis[i] \leq dis[j] - 1$$
$$dis[j] \leq dis[i] + 1$$
通过两个不等式，锁定 $i,j$ 之间的差值为 $1$。
* 对于第二种不等式
建单向边：
$$dis[i] \leq dis[j] + 0$$
### Floyd
容易发现求赛车手的成绩可能的取值有多少种，其实就是赛车手正整数值域大小的最大值，因为这道题的数据卡了SPFA，所以我们只好用Floyd，但是因为直接跑，$n^3=216000000$，显然会炸，所以我们就想到了缩点。
### 缩点
容易发现，强联通分量之间是不会相互影响的，所以我们可以在强联通分量内进行Floyd，跑最短路后，找出最长路径，也就是最大的值域，而这个值域的大小 = R - L + 1；
### 缩点后的Floyd
设 $dis[i][j]$ 表示从$i$ 到 $j$ 的最长距离。
在每个阶段开始时，判断进行状态转移的三个点是否在同一个连通块内。
* 对于合法的答案：
求出 $dis$ 后，找出每个连通块内的最长路径 $max_{i}$，根据上面的分析，每个连通块对答案的贡献为 $max_{i} + 1$。
所以最终的答案就是：
$$\sum_{i = 1} ^{cnt}max_{i} + 1$$
* 对于不合法的答案：
 如果存在负环，则无解。Floyd判负环先初始化 $dis[i][i] = 0$，如果存在负环，那么 $dis[i][i]$ 的值就会被修改，只需要判断 $dis[i][i]$ 的值是否为 $0$就行了。
# 代码
如果想不吸氧过的话，可以加 $register$。
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
const int N = 605;
struct edge {
	int next,to;
}a[N * 100];
int head[N],dis[N][N],maxn[N],n,m1,m2,a_size = 1,ans = 0;
inline void add(int u,int v) {
	a[++a_size] = (edge){head[u],v};
	head[u] = a_size;
}
int dfn[N],low[N],sta[N],c[N],top = 0,cnt = 0,num = 0;
bool ins[N];
void tarjan(int x) {
	dfn[x] = low[x] = ++num;
	sta[++top] = x,ins[x] = true;
	for(int i = head[x]; i; i = a[i].next) {
		int y = a[i].to;
		if(!dfn[y]) {
			tarjan(y);
			low[x] = min(low[x],low[y]);
		}
		else if(ins[y])
			low[x] = min(low[x],dfn[y]);
	}
	if(dfn[x] == low[x]) {
		cnt++; int y; do {
			y = sta[top--]; ins[y] = false;
			c[y] = cnt;
		}while(y != x);
	}
}
inline int read() {
	int x = 0,flag = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')flag = -1;ch = getchar();}
	while(ch >='0' && ch <='9'){x = (x << 3) + (x << 1) + ch - 48;ch = getchar();}
	return x * flag;
}
int main() {
	memset(dis,0x3f,sizeof(dis));
	n = read(),m1 = read(),m2 = read();
	for(int i = 1; i <= n; i++) dis[i][i] = 0;
	for(int i = 1; i <= m1; i++) {
		int u = read(),v = read();
		add(u,v); add(v,u);
		dis[u][v] = min(dis[u][v],-1);
		dis[v][u] = min(dis[v][u],1);
	}
	for(int i = 1; i <= m2; i++) {
		int u = read(),v = read();
		add(u,v);
		dis[u][v] = min(dis[u][v],0);
	}
	for(int i = 1; i <= n; i++)
		if(!dfn[i]) tarjan(i);
	for(int k = 1; k <= n; k++) {
		for(int i = 1; i <= n; i++) {
			if(c[i] != c[k]) continue;
			for(int j = 1; j <= n; j++) {
				if(c[j] != c[i]) continue;
				dis[i][j] = min(dis[i][j],dis[i][k] + dis[k][j]);
			}
		}
	}
	for(int i = 1; i <= n; i++)
		if(dis[i][i]) {
			puts("NIE");
			return 0;
		}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			if(c[j] != c[i]) continue;
			maxn[c[i]] = max(maxn[c[i]],dis[i][j]);
		}
	}
	for(int i = 1; i <= cnt; i++) ans += maxn[i] + 1;
	printf("%d",ans);
	return 0;
}
```




---

## 作者：fengyaun (赞：0)

## [P3530 FES-Festival](https://www.luogu.com.cn/problem/P3530)

### 前言

一道差分约束好题，是典型的差分约束思想题，与一般的差分约束实现方式不大相同，值得一做。

### 分析

注意到，如果有多种不同的情况当且仅当其约束关系形成一条环，换言之即在一个强连通分量中时。因为如果不在一个强连通分量之中，那么其赋值仅存在一个约束条件，赋值是由上一个决定的。

我们对于某一个强连通分量的可能的权即是其中互相的最短路的最大值 $+1$，因为我们不难发现其最短路即是其差值的可能数目，也就是未知量取值的值域的两端。那么同一个强连通分量的相互的最短路的最大值也就是可能的解的最大值。

考虑什么时候无解，比较显然的是，如果一个点取不了任意一值即无解，也就是其到自己的最短路小于 $0$。

实现就是用 Floyd 和 Tarjan 就行了。

### 代码

```c++
#include<bits/stdc++.h>
using namespace std;

const int N = 6e2 + 10;

struct node
{
    int v, w;
};

int n, m1, m2;

int answer;

int stamp;

int timestamp;

int dfn[N], low[N], vis[N];

int scc[N];

int ans[N];

stack<int> now;

int dis[N][N];

void tarjan(int u)
{
    dfn[u] = low[u] = ++timestamp;
    vis[u] = true;
    now.push(u);
    for (int v = 1; v <= n; v++)
    {
        if (dis[u][v] > 1) continue;
        if (!dfn[v]) 
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        if (vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        ++stamp;
        int cur;
        do
        {
            cur = now.top();
            now.pop();
            vis[cur] = 0;
            scc[cur] = stamp;
        }
        while(cur != u);
    }
}

int main()
{
    memset(dis, 0x3f, sizeof(dis));
    cin >> n >> m1 >> m2;
    for (int i = 1, u, v; i <= m1; i++)
    {
        cin >> u >> v;
        dis[u][v] = min(dis[u][v], 1);
        dis[v][u] = min(dis[v][u], -1);
    }
    for (int i = 1, u, v; i <= m2; i++)
    {
        cin >> u >> v;
        dis[v][u] = min(dis[v][u], 0);
    }
    for (int i = 1; i <= n; i++) dis[i][i] = 0;
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i);
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            if (scc[i] == scc[k] && dis[i][k] != 0x3f3f3f3f)
            for (int j = 1; j <= n; j++) if (scc[i] == scc[j])
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    for (int i = 1; i <= n; i++)
    {
        if (dis[i][i] < 0)
        {
            cout << "NIE";
            return 0;
        }
        for (int j = 1; j <= n; j++)
            if (scc[i] == scc[j]) ans[scc[i]] = max(ans[scc[i]], dis[i][j] + 1);
    }
    for (int i = 1; i <= n; i++) answer += ans[i];
    cout << answer;
    return 0;
}
```

---

## 作者：Jμdge (赞：0)

思路与楼下大佬相仿，但是这里用的求最短路的方式是SPFA（而且是深搜的那个版本，入门的童鞋们可以涨涨姿势），然后判断负环的方式也算是挺有意思的（不知道为什么用普通的SPFA模板过不了，一直wa了一个点，而且wa的就是Floyd算法会T的那个点，不T就WA是么？），恩，数据还算友好就这样过了（在bzoj上其实Floyd也能过，大概是AC标准不一样，但是用这个SPFA能砍掉2/3的 时间，时间上还是很可观的）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=700;
inline int read(){
	int x=0; char c=getchar();
	while(!isdigit(c)) c=getchar();
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	return x; 
}
int n,m1,m2,ans,top,num,pat,cnt;
int dfn[M],low[M],blg[M],dis[M][M];
int stk[M],head[M],last[M],tim[M];
bool in[M],vis[M];
struct Edge{
	int to,val,next;
}e[210000];
inline void add(int u,int v,int c){
	++pat; e[pat].to=v; e[pat].val=c;
	e[pat].next=head[u]; head[u]=pat;
}
inline void tarjan(int u){  //这些东西我都不介绍了
	dfn[u]=low[u]=++num;
	stk[++top]=u; in[u]=true;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(!dfn[v]) tarjan(v), low[u]=min(low[u] , low[v]);
		else if(in[v]) low[u]=min(low[u] , dfn[v]);
	}
	if(dfn[u]==low[u]){
		int j; ++cnt;
		do{
			j=stk[top--];
			in[j]=false; blg[j]=cnt;
		}while(j!=u);
	}
}
bool SPFA(int s,int u){
//之前用的标准版SPFA就不给过，不知道是不是判负环的方法（某点入队次数超过n）被卡了还是怎么滴了反正这个版本的SPFA过了（深搜）
	vis[u]=true;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to,c=e[i].val;
		if(blg[u]!=blg[v]) continue;
		if(dis[s][u]+c<dis[s][v]){
			dis[s][v]=dis[s][u]+c;
			if(vis[v]) return false; //该点在深搜过程中访问过了就return false
			else if(!SPFA(s , v)) return false; //深搜失败返回false
		}
	}
	vis[u]=false;
	return true;
}

int main(){ //主函数其实和楼下大佬基本差不了多少
	n=read(); m1=read(); m2=read();
	memset(dis , 0x3f , sizeof(dis));
	for(int i=1;i<=n;++i) dis[i][i]=0;
	for(int i=1;i<=m1;++i){
		int u=read(),v=read();
		add(u , v , 1); add(v , u , -1);
	}
	for(int i=1;i<=m2;++i){
		int u=read(),v=read();
		add(v , u , 0);
	}
	for(int i=1;i<=n;++i){
		if(!dfn[i]) tarjan(i);
		dis[i][i]=0;
	}
	for(int i=1;i<=n;++i)
	if(!SPFA(i , i)){  //有负环直接输出+return
		printf("NIE\n"); return 0;
	}
	for(int k=1;k<=cnt;++k){ //这里也差不了多少
		int mn=0;
		for(int i=1;i<=n;++i) for(int j=1;j<=n;++j)
		if(blg[i]==k && blg[j]==k) mn=max(mn , dis[i][j]);
		ans+=mn+1;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

