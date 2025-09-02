# [POI 2006] PRO-Professor Szu

## 题目描述

某大学校内有一栋主楼，还有 $n$ 栋住宅楼。这些楼之间由一些单向道路连接，但是任意两栋楼之间可能有多条道路，也可能存在起点和终点为同一栋楼的环路。存在住宅楼无法到达主楼的情况，但**保证至少有一间宿舍和主楼之间存在路径**。

现在有一位古怪的教授，他希望每天去主楼上班的路线不同。

一条上班路线中，每栋楼都可以访问任意多次。我们称两条上班路线是**不同的**，当且仅当两条路线中存在一条路是不同的（两栋楼之间的多条道路被视为是不同的道路）。

现在教授希望知道，从哪些住宅楼前往主楼的上班路线数最多。

## 样例 #1

### 输入

```
3 5
1 2
1 3
2 3
3 4
3 4```

### 输出

```
4
1
1```

# 题解

## 作者：Jμdge (赞：9)

				——楼上某篇题解貌似有点问题？


现在我们来解决这个~~作死的老~~教授的问题吧！
--


首先这道题做法就是比较常规的 tarjan 缩点 + topo 传递闭包，要注意的地方就是：

n是教学楼（出发点），是不能算进公寓里面的，而如果教学楼有自环的话，那么按照楼上某位大佬的程序是会输出n的！而且res的答案还会多1


那么多的细节就在代码里面讲好了

# code
------------

```cpp
#include<bits/stdc++.h>
typedef long long LL;
using namespace std;
const int M=1100000;
inline int read()
{
	int x=0; char c=getchar();
	while(!isdigit(c)) c=getchar();
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	return x;
}
int n,m,tim,top,pat;
int part,ans,res;
int has[M],d[M],f[M];
//has--该连通快中的节点数  ；d--该连通快的入度
//f--该连通快到达起点（教学楼）的道路数量；
int dfn[M],low[M],blg[M]; //tarjan重要用的东西
int last[M],head[M]; //last在二次构图的时候用
bool is[M];  //记录该连通块是否是有环的联通块
stack<int> stk;
struct edge { int v,next; }e[M],g[M]; 

void add(int u,int v) { e[pat].next=head[u]; e[pat].v=v; head[u]=pat++; } //一次构图的时候用
void add2(int u,int v) { g[pat].next=last[u]; g[pat].v=v; last[u]=pat++; } //二次构图的时候用
void tarjan(int u)
{
	bool flag=false; //记录是否有自环
	dfn[u]=low[u]=++tim;
	stk.push(u);
	for(int i=head[u];i!=-1;i=e[i].next)
	{
		int v=e[i].v; if(u==v) flag=true; //自环的判断
		if(!dfn[v]) tarjan(v),low[u]=min(low[u] , low[v]);
		else if(!blg[v]) low[u]=min(low[u] , dfn[v]);
	}
	if(dfn[u]==low[u])
	{
		int j=0; ++part;
		if(flag || stk.top()!=u) is[part]=true; //判断是否有环（或者自环），有的话那么出发点到该联通块后就有无数条路好走了
		do{
			j=stk.top();stk.pop();
			blg[j]=part;
			++has[part];
		}while(j!=u);
	}
}

void topo()
{
	queue<int> Q; f[blg[n]]=1;
	for(int i=1;i<=part;++i) if(!d[i]) Q.push(i);
	while(!Q.empty()) //把那些没有入度的点（除了出发点）弹出，事实上不弹也没事儿！
	{
		int now=Q.front(); Q.pop();
		if(now==blg[n]) continue;
		for(int i=last[now];i!=-1;i=g[i].next)
		{ --d[g[i].v]; if(!d[g[i].v]) Q.push(g[i].v); }
	}
	Q.push(blg[n]); //无论如何要把起点塞回去

	while(!Q.empty()) //然后一直拓扑就ok了
	{
		int now=Q.front(); Q.pop();
		if(is[now] && f[now]) f[now]=36501; //有环就给最大值
		for(int i=last[now];i!=-1;i=g[i].next)
		{
			f[g[i].v]=min(f[g[i].v]+f[now] , 36501);//最大为36501
			--d[g[i].v]; if(!d[g[i].v]) Q.push(g[i].v);
		}
	}
}

int main()
{
	memset(head , -1 , sizeof(head));
	memset(last , -1 , sizeof(last));
	n=read(); m=read(); ++n;
	for(int i=0;i<m;++i) //反着加边，等下操作会方便很多
		{ int u=read(),v=read(); add(v,u); } pat=0;
	
	for(int i=1;i<=n;++i)  //tarjan缩点 
		if(!dfn[i]) tarjan(i);
	
	for(int i=1;i<=n;++i)  //重构图 
	for(int j=head[i];j!=-1;j=e[j].next)
		if(blg[i]!=blg[e[j].v]) add2(blg[i] , blg[e[j].v]),++d[blg[e[j].v]];
	topo(); for(int i=1;i<=part;++i) ans=max(ans , f[i]);
    //拓扑一下后找到起点道路数最大的点
	if(ans==36501) printf("zawsze\n");
	else printf("%d\n",ans); //这都是按题目讲的来做了
	if(ans==f[blg[n]]) --res; //挪，这里就是区别，等会儿讲
	for(int i=1;i<=part;++i)
		if(ans==f[i]) res+=has[i];
	printf("%d\n",res);
	for(int i=1;i<n;++i) //这里也是区别滴~~~
		if(ans==f[blg[i]]) printf("%d ",i);
	printf("\n");
	return 0;
}
```



----


---

## 作者：Alex_Wei (赞：8)

> [P3436 [POI2006]PRO-Professor Szu](https://www.luogu.com.cn/problem/P3436)

首先，容易发现若一个大小大于 $1$ 的 SCC 或自环（下称为不合法结构）能够到达教学楼，则该不合法结构内部每个点到教学楼的路径数量都是无穷大。因此 SCC 缩点 + **建反图** 拓扑排序，不合法结构不能入队。拓扑排序同时记录路径数 $f_i$ 表示从 $i$ 到 $n+1$ 的路径数量。因为不能取模，所以要对 $36501$ 取 $\min$。

但题目没有保证每个点都能到教学楼（题面有误），所以需要先将反图上入度为 $0$ 的非教学楼点入队跑一遍拓扑排序。注意此时不合法结构可以入队，因为它们没有到达教学楼的路径。

最后，若出现没有入队的点，说明这个点能够到达一个不合法结构，因此路径数同样为无穷大。此外，若 $f_i>36500$ 也不符合题意。时间复杂度线性。

- 如果 $n + 1$ 所在 SCC 是不合法结构，那么不能入队。
- 使用 `vector` 存图会 MLE，原题空间限制 64MB。

```cpp
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int n, m, ed, ban[N], deg[N], f[N];
int dn, dfn[N], low[N], cn, col[N], top, stc[N], vis[N];
struct linklist {
  int cnt, hd[N], nxt[N], to[N];
  void add(int u, int v) {nxt[++cnt] = hd[u], hd[u] = cnt, to[cnt] = v;}
} e, g;
void tarjan(int id) {
  dfn[id] = low[id] = ++dn, stc[++top] = id, vis[id] = 1; // 0 -> 1
  for(int _ = e.hd[id]; _; _ = e.nxt[_]) {
    int it = e.to[_];
    if(!dfn[it]) tarjan(it), low[id] = min(low[id], low[it]);
    else if(vis[it]) low[id] = min(low[id], dfn[it]);
  }
  if(low[id] == dfn[id]) {
    col[id] = ++cn, ban[cn] = stc[top] != id;
    while(stc[top] != id) col[stc[top]] = cn, vis[stc[top--]] = 0; // id -> cn
    vis[id] = 0, top--;
  }
}
int main() {
#ifdef ALEX_WEI
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
#endif
  cin >> n >> m;
  for(int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    e.add(u, v);
  }
  for(int i = 1; i <= n + 1; i++) if(!dfn[i]) tarjan(i);
  for(int i = 1; i <= n + 1; i++)
    for(int _ = e.hd[i]; _; _ = e.nxt[_]) {
      int it = e.to[_];
      if(i == it) ban[col[i]] = 1;
      else if(col[i] != col[it]) g.add(col[it], col[i]), deg[col[i]]++;
    }
  ed = col[n + 1];
  queue<int> q;
  for(int i = 1; i <= cn; i++) if(i != ed && !deg[i]) q.push(i);
  memset(vis, 0, sizeof(vis));
  while(!q.empty()) {
    int t = q.front();
    q.pop(), vis[t] = 1;
    for(int _ = g.hd[t]; _; _ = g.nxt[_]) {
      int it = g.to[_];
      if(!--deg[it] && it != ed) q.push(it);
    }
  }
  if(!ban[ed]) assert(!deg[ed]), q.push(ed), f[ed] = 1;
  while(!q.empty()) {
    int t = q.front();
    q.pop(), vis[t] = 1;
    for(int _ = g.hd[t]; _; _ = g.nxt[_]) {
      int it = g.to[_];
      if(ban[it]) continue;
      f[it] = min(36501, f[it] + f[t]);
      if(!--deg[it]) q.push(it);
    }
  }
  vector<int> ans;
  for(int i = 1; i <= n; i++)
    if(!vis[col[i]] || f[col[i]] == 36501)
      ans.push_back(i);
  if(!ans.empty()) puts("zawsze");
  else {
    int mx = 0;
    for(int i = 1; i <= n; i++) {
      if(f[col[i]] > mx) mx = f[col[i]], ans.clear();
      if(f[col[i]] == mx) ans.push_back(i);
    }
    cout << mx << "\n";
  }
  cout << ans.size() << "\n";
  for(int it : ans) cout << it << " ";
  return cerr << "Time: " << clock() << endl, 0;
}
/*
2022/5/25
start coding at 8:35
finish debugging at 9:11
*/
```

---

## 作者：oscar (赞：6)

【POI补全计划#20 POI2006 PRO】

首先为了方便，把“从别墅走到主建筑楼”视为“从主建筑楼走到别墅”，然后把所有边反向（为了方便dfs），这样对题目答案没有影响

接下来记录主建筑能走到那些建筑，把走不到的建筑（和它们的出边）从图中去掉

然后在能走到的建筑中记录每个点的入度（不包含从“走不到的建筑”连向“能走道的建筑”的边），进行拓扑排序

在拓扑排序的过程中记录方案数，如果排到一半发现没有待处理的，入度为0的点时说明剩下的点中存在环，可以有无限种方案走向剩余的点

在记录方案的过程中如果遇到方案数>36500的点则设为一个固定的，略大于36500的数，防止爆int

最后输出一下方案就好了，注意无限种方案和方案数>36500的点都需要输出

贴代码：

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN=1000010;
struct edge
{
    int v;
    edge *next;
}*h[MAXN],pool[MAXN];
int deg[MAXN],top,cnt;
inline void addedge(int v,int u)
{
    edge *tmp=&pool[++top];tmp->v=v;tmp->next=h[u];h[u]=tmp;deg[v]++;
}
int dp[MAXN],vis[MAXN];
vector<int> ans;
void dfs(int u)
{
    vis[u]=1;cnt++;
    for(edge *tmp=h[u];tmp;tmp=tmp->next)
    {
        if(!vis[tmp->v])dfs(tmp->v);
    }
}
queue<int> q;
int main()
{
    int n,m,a,b;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&a,&b);
        addedge(a,b);
    }
    dfs(n+1);
    for(int i=1;i<=n;i++)
    {
        if(!vis[i])
        {
            for(edge *tmp=h[i];tmp;tmp=tmp->next)
            {
                deg[tmp->v]--;
            }
        }
    }
    q.push(n+1);
    dp[n+1]=1;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        cnt--;vis[u]=0;
        for(edge *tmp=h[u];tmp;tmp=tmp->next)
        {
            dp[tmp->v]+=dp[u];
            deg[tmp->v]--;
            if(deg[tmp->v]==0)
            {
                if(dp[tmp->v]>36500)
                {
                    dp[tmp->v]=36501;
                    ans.push_back(tmp->v);
                    cnt++;
                }
                q.push(tmp->v);
            }
        }
    }
    if(cnt==0)
    {
        int maxx=0;
        for(int i=1;i<=n;i++)
        {
            if(dp[i]>maxx)
            {
                maxx=dp[i];
                ans.clear();
                ans.push_back(i);
            }
            else if(dp[i]==maxx)ans.push_back(i);
        }
        sort(ans.begin(),ans.end());
        printf("%d\n%d\n",maxx,ans.size());
        for(auto x:ans)printf("%d ",x);
        return 0;
    }
    for(int i=1;i<=n;i++)if(vis[i])ans.push_back(i);
    sort(ans.begin(),ans.end());
    printf("zawsze\n%d\n",ans.size());
    for(auto x:ans)printf("%d ",x);
    return 0;
}
```

---

## 作者：RiverFun (赞：6)

推广一波 [$\texttt{BLOG}$](https://stevebraveman.github.io/)

进入正题：

# 拓扑排序 + Tarjan缩点 + DP

为了统计答案，我们可以反向建图，然后跑一遍Tarjan进行缩点，如果一个强连通分量的大小大于1，那么这个强连通分量里的点肯定都有无穷多种方案，并且，我们把自环也当做是一种大小大于1的强连通分量。

然后跑拓扑排序就可以了，但是要记住，**不能被起点到达的点不能统计**。

状态转移方程也很简单：$\texttt{dp[to] = dp[to] + dp[u]}$。

$\texttt{Code}$：

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#define MAXN 1000100
#define LIM 36500
struct Edge {
	int v, nx;
}e[MAXN << 2];
int min(int a, int b) {
	if (a < b) return a;
	else return b;
}
int max(int a, int b) {
	if (a > b) return a;
	else return b;
}
int head[MAXN], ecnt, n, m, x[MAXN], y[MAXN], tim, dfn[MAXN], low[MAXN], dp[MAXN];
int f[MAXN], num, top, st[MAXN], in[MAXN], siz[MAXN], ent[MAXN], ans, tot;
bool vis[MAXN];
void add(int f, int t) {
	e[++ecnt] = (Edge) {t, head[f]};
	head[f] = ecnt;
}
void tarjan(int u) {
	dfn[u] = low[u] = ++tim;
	st[++top] = u;
	vis[u] = 1;
	for (int i = head[u]; i; i = e[i].nx) {
		int v = e[i].v;
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if (vis[v]) low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		int v;
		num++;
		do {
			v = st[top--];
			vis[v] = 0;
			in[v] = num;
			siz[num]++;
		} while (v != u);
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &y[i], &x[i]);
		add(x[i], y[i]);
	}
	for (int i = 1; i <= n + 1; i++) {
		if (!dfn[i]) tarjan(i);
	}
	memset(e, 0, sizeof(e));
	memset(head, 0, sizeof(head));
	ecnt = 0;
	for (int i = 1; i <= m; i++) {
		if (x[i] == y[i]) {
			siz[in[x[i]]]++;
		}
	}
	for (int i = 1; i <= m; i++) {
		if (in[x[i]] != in[y[i]]) {
			add(in[x[i]], in[y[i]]);
			ent[in[y[i]]]++;
		}
	}
	std::queue <int> q;
	for (int i = 1; i <= num; i++) {
		if (!ent[i]) q.push(i);
	}
	dp[in[n + 1]] = 1;
	memset(vis, 0, sizeof(vis));
	vis[in[n + 1]] = 1;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = head[u]; i; i = e[i].nx) {
			int to = e[i].v;
			ent[to]--;
			if (!ent[to]) {
				q.push(to);
			}
			if (vis[u]) vis[to] = 1;
			dp[to] += dp[u];
			if (siz[to] > 1 && vis[to]) dp[to] = LIM;
			if (dp[to] > LIM) {
				dp[to] = LIM;
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		if (vis[in[i]]) {
			f[i] = dp[in[i]];
			ans = max(ans, f[i]);
		}
	}
	for (int i = 1; i <= n; i++) {
		if (vis[in[i]]) {
			if (f[i] == ans) tot++;
		}
	}
	if (ans == LIM) {
		puts("zawsze");
	}
	else {
		printf("%d\n", ans);
	}
	printf("%d\n", tot);
	for (int i = 1; i <= n; i++) {
		if (vis[in[i]]) {
			if (f[i] == ans) {
				printf("%d ", i);
			}
		}
	}
}
```

---

## 作者：KEBrantily (赞：3)

直接说解法。

首先可以发现，如果图中出现环，就会出现无数条路径，因为我们可以在环里走无数圈来增加路径数量。

所以我们可以缩点处理环，顺便处理环上点的个数。

然后对于非环上的点，可以在重建图后用拓扑排序简单 DP 来统计每个点到终点的路径总数。特别的，为了方便统计，我们可以把路径总数超出范围的点（包括环上的点）直接赋值为 $36500$。

然后统计输出，就做完了。

```cpp
void add(int fr,int to){
  e[++tot]=(edge){fr,to,head[fr]};
  head[fr]=tot;
}

void Add(int fr,int to){
  E[++TOT]=(edge){fr,to,Head[fr]};
  Head[fr]=TOT;  
}

void tarjan(int u){
  dfn[u]=low[u]=++cnt;
  vis[u]=1;zhan[++top]=u;
  for(int i=head[u];i;i=e[i].nxt){
    int to=e[i].to;
    if(!dfn[to]) tarjan(to),low[u]=min(low[u],low[to]);
    else if(vis[to]) low[u]=min(low[u],dfn[to]);
  }
  if(dfn[u]==low[u]){
    ++siz[++t];
    int pre=zhan[top--];
    num[pre]=t;vis[pre]=0;
    while(pre!=u){
      ++siz[t];
      pre=zhan[top--];
      num[pre]=t;vis[pre]=0;
    }
  }
}

void topsort(){
  queue<int> q;
  for(int i=1;i<=t;i++)
    if(!du[i]) q.push(i);
  while(!q.empty()){
    int u=q.front();q.pop();
    for(int i=Head[u];i;i=E[i].nxt){
      int to=E[i].to;
      if(--du[to]==0) q.push(to); 
      if(flag[u]) flag[to]=1;dp[to]+=dp[u];
      if(siz[to]>1&&flag[to]) dp[to]=UP;
      if(dp[to]>UP) dp[to]=UP;
    }
  }
}

signed main(){
  n=read();m=read();
  for(int i=1;i<=m;i++){
    fr[i]=read(),to[i]=read();
    add(to[i],fr[i]);
  }
  for(int i=1;i<=n+1;i++) if(!dfn[i]) tarjan(i);
  
  for(int i=1;i<=m;i++){
    if(fr[i]==to[i]) ++siz[num[fr[i]]];
    else if(num[fr[i]]!=num[to[i]]) 
      Add(num[to[i]],num[fr[i]]),du[num[fr[i]]]++;
  }
  
  flag[num[n+1]]=1;
  dp[num[n+1]]=1;topsort();
  for(int i=1;i<=n;i++){
    if(!flag[num[i]]) continue;
    ans=max(ans,dp[num[i]]);
  }
  for(int i=1;i<=n;i++){
    if(!flag[num[i]]) continue;
    all+=(dp[num[i]]==ans);
  }
  if(ans==UP) puts("zawsze");
  else printf("%d\n",ans);printf("%d\n",all);
  for(int i=1;i<=n;i++){
    if(!flag[num[i]]) continue;
    if(dp[num[i]]==ans) printf("%d ",i);
  }
  return 0;
}
```

---

## 作者：YANG_XIAO (赞：3)

 _~~Szu教授怕不是教书教傻了233~~_ 

首先考虑 **tarjan** 缩点，找出所有的强联通分量(scc)，显然当一个scc中的点超过1个时，那么到这个scc中的点的方案就有无数种（因为这个教授可以绕着圈一直走），然后将重构后的图进行拓扑排序（**Topological_Sort**），算出方案数即可。

PS：重复使用数组d和moo，还有中途删除数组都是因为BZOJ卡空间的缘故。。。就当普通数组看就好了QAQ。

附代码：
```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
#include<string>
#include<cstring>
using namespace std;

#define MAXN 1000000+10
#define INF 36500

int n,m,DFNT,cnt;
int *DFN,*LOW,Belong[MAXN],d[MAXN],f[MAXN];
vector<int> *G,*H;
bool moo[MAXN];
stack<int> s;

int read()
{
	int x=0,f=1;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-')
			f=-1;
		ch=getchar();
	}
	while (isdigit(ch))
		x=x*10+ch-'0',ch=getchar();
	return x*f;
}

void tarjan(int u)
{
	DFN[u]=LOW[u]=++DFNT;
	s.push(u);
	moo[u]=true;
	for (int i=0;i<G[u].size();i++)
	{
		int v=G[u][i];
		if (!DFN[v])
			tarjan(v),LOW[u]=min(LOW[u],LOW[v]);
		else if (moo[v])
			LOW[u]=min(LOW[u],DFN[v]);
	}
	int tmp=0;
	if (DFN[u]==LOW[u])
	{
		cnt++;
		do
		{
			tmp=s.top();
			s.pop();
			moo[tmp]=false;
			Belong[tmp]=cnt;
		}
		while (tmp!=u);
	}
}

void Rebuild()
{
	for (int i=1;i<=n;i++)
		for (int j=0;j<G[i].size();j++)
			if (Belong[i]!=Belong[G[i][j]])
				H[Belong[i]].push_back(Belong[G[i][j]]),d[Belong[G[i][j]]]++;
			else
				moo[Belong[i]]=true;
}

void Topological_Sort(int t)
{
	queue<int> q;
	for (int i=1;i<=cnt;i++)
		if (!d[i])
			q.push(i);
	f[Belong[t]]=1;
	if (moo[Belong[t]])
		f[Belong[t]]+=INF;
	while (!q.empty())
	{
		int tmp=q.front();
		q.pop();
		for (int i=0;i<H[tmp].size();i++)
		{
			int to=H[tmp][i];
			f[to]+=f[tmp];
			if (f[to]>INF)
				f[to]=INF+1;
			d[to]--;
			if (!d[to])
			{
				if (moo[to]&&f[to])
					f[to]=INF+1;
				q.push(to);
			}
		}
	}
}

int main()
{
	n=read()+1,m=read();
	G=new vector<int>[n+1];
	LOW=new int[n+100];
	DFN=new int[n+100];
	memset(LOW,0,n+100);
	memset(DFN,0,n+100);
	while (m--)
	{
		int u=read(),v=read();
		G[v].push_back(u);
	}
	for (int i=1;i<=n;i++)
		if (!DFN[i])
			tarjan(i);
	memset(moo,false,sizeof(moo));
	delete []LOW;
	delete []DFN;
	H=new vector<int>[cnt+1];
	Rebuild();
	Topological_Sort(n);
	delete []G;
	delete []H;
	int ans=0,res=0;
	for (int i=1;i<n;i++)
		ans=max(ans,f[Belong[i]]);
	for (int i=1;i<n;i++)
		if (ans==f[Belong[i]])
			d[++res]=i;
	printf(ans>INF ? "zawsze":"%d",ans);
	printf("\n%d\n",res);
	for (int i=1;i<=res;i++)
		printf("%d ",d[i]);
	return 0;
}
```

---

## 作者：koukilee (赞：1)

一道比较板子的题目但是调了我很久（。

Tarjan + 拓扑排序。

先考虑无环的情况，建出逆拓扑序，并直接 dp 转移路径方案数，这一部分是简单的。

发现如果有一个环可以到达主楼，那么一定存在无数种方案，因为可以反复在这个环上绕。

同理，可以经过某个环到达主楼的所有点也是应该有无限种方案的。

那么考虑缩点即可，把环缩起来。然后再按照上面的逆拓扑序 dp 即可，顺便转移一下环能到达的点。

最后输出的时候，如果可以到达环的所有点和路线数超过了 $36500$ 的点都要输出。

[代码](https://www.luogu.com.cn/article/umn9z0zs)就写得有点难看了。

---

## 作者：zhhgdm (赞：1)

# 题目大意
求有向图中可到达 $n+1$ 号节点的方案数。

# step 1
如果图中没环怎么做？

有向无环图不难想到拓扑排序。当然了，“到达某一节点”自然得反向建图，如果在反向图中 $u$ 可以到达 $v$，原图中 $v$ 便可以到达 $u$。然后就是一个简单的图上计数 DP 了。转移方程如下:
$$
f_u=\sum f_v
$$
其中，$u$ 是当前节点，$v$ 是所有可以到达 $u$ 的节点。

# step 2
如果图中有环怎么办？

容易想到 Tarjan 缩点。然后就可以按照 step 1 来做了。但是，一个节点个数大于 $1$ 的强连通分量若可以到达 $n+1$ 号节点，那么它们中的任意一个都有无数个路径可以到达 $n+1$ 号节点，那么 $f_u$（$u$ 即为任意一个节点） 就等于无穷大，在本题中，使用 $36501$ 即可（大于 $36500$）。

# 代码
需要注意的是，并不只有 $n+1$ 号节点所在的强连通分量入度为 $0$（既不充分也不必要），任何一个入度为 $0$ 的强连通分量都需要入队，但考虑到它们不对答案产生贡献，所以 $f_u$ 为 $0$，可以维护一个 `exist` 数组来判断是否对答案产生贡献。

``` cpp
#include <bits/stdc++.h>
using namespace std;

const int inf = 36501;

struct graph {
  struct edge {
    int nxt, to;
  } mp[2000005];
  int cnt, head[1000005];
  void add(int x, int y) {
    mp[++cnt] = {head[x], y};
    head[x] = cnt;
  }
} a, b;
// a 为原图，b 为缩点后的图的反图

vector<int> v;
// 记录自环

int dfn[1000005], low[1000005], col[1000005], now, num;
stack<int> s;
bool instack[1000005];
vector<vector<int>> scc;

bool flag[1000005];   // 记录是否是节点个数大于 1 的强连通分量
int in[1000005];     // 记录 b 的入度
int f[1000005];      // 记录到达 n+1 点的方案数
bool exist[1000005]; // 记录是否存在到达 n+1 点的路径

// tarjan 算法求强连通分量
void tarjan(int x, int fa) {
  dfn[x] = low[x] = ++now;
  s.push(x);
  instack[x] = true;
  for (int i = a.head[x]; i; i = a.mp[i].nxt) {
    if (!dfn[a.mp[i].to]) {
      tarjan(a.mp[i].to, x);
      low[x] = min(low[x], low[a.mp[i].to]);
    } else if (instack[a.mp[i].to]) {
      low[x] = min(low[x], dfn[a.mp[i].to]);
    }
  }
  if (dfn[x] == low[x]) {
    num++;
    scc.push_back(vector<int>());
    int t;
    do {
      t = s.top();
      if (t != x)
        flag[num] = true;
      s.pop();
      instack[t] = 0;
      col[t] = num;
      scc.back().push_back(t);
    } while (t != x);
  }
}
int main() {
  // 加速输入输出
  ios::sync_with_stdio(0);
  cin.tie(0);

  // 输入
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int x, y;
    cin >> x >> y;
    if (x == y) {
      v.push_back(x);
      continue;
    }
    a.add(x, y);
  }

  // 调用 tarjan
  for (int i = 1; i <= n + 1; i++) {
    if (!dfn[i])
      tarjan(i, 0);
  }

  // 处理自环
  for (int i : v)
    flag[col[i]] = true;

  // 构建 b
  for (int i = 1; i <= n; i++) {
    for (int j = a.head[i]; j; j = a.mp[j].nxt) {
      if (col[i] != col[a.mp[j].to]) {
        b.add(col[a.mp[j].to], col[i]);
      }
    }
  }

  // 记录 b 的入度
  for (int i = 1; i <= num; i++) {
    for (int j = b.head[i]; j; j = b.mp[j].nxt) {
      in[b.mp[j].to]++;
    }
  }

  // 拓扑排序
  exist[col[n + 1]] = 1;
  if (flag[col[n + 1]])
    f[col[n + 1]] = inf;
  else
    f[col[n + 1]] = 1;
  queue<int> q;
  for (int i = 1; i <= num; i++) {
    if (!in[i])
      q.push(i);
  }
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    if (exist[x] && flag[x])
      f[x] = inf;
    for (int i = b.head[x]; i; i = b.mp[i].nxt) {
      in[b.mp[i].to]--;
      if (exist[x]) {
        exist[b.mp[i].to] = 1;
        f[b.mp[i].to] += f[x];
        if (f[b.mp[i].to] > inf)
          f[b.mp[i].to] = inf; // 要和 inf 取 min
      }
      if (!in[b.mp[i].to])
        q.push(b.mp[i].to);
    }
  }

  // 输出
  vector<int> ans;
  for (int i = 1; i <= num; i++) {
    if (exist[i] && (ans.empty() || f[i] > f[ans[0]])) {
      ans.clear();
      ans.push_back(i);
    } else if (exist[i] && f[i] == f[ans[0]]) {
      ans.push_back(i);
    }
  }
  if (f[ans[0]] == inf)
    cout << "zawsze" << endl;
  else
    cout << f[ans[0]] << endl;
  set<int> s;
  for (int i : ans) {
    for (int j : scc[i - 1])
      s.insert(j);
  }
  if (s.count(n + 1))
    s.erase(n + 1); // 特判
  cout << s.size() << endl;
  for (int i : s)
    cout << i << ' ';
  return 0;
}
```

---

## 作者：Coros_Trusds (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/16449003.html)

# 题目大意

某大学校内有一栋主楼，还有 $n$ 栋住宅楼。这些楼之间由一些单向道路连接，但是任意两栋楼之间可能有多条道路，也可能存在起点和终点为同一栋楼的环路。已知任意一栋住宅楼都存在至少一条前往主楼的路线。

现在有一位古怪的教授，他希望每天去主楼上班的路线不同。

一条上班路线中，每栋楼都可以访问任意多次。我们称两条上班路线是**不同的**，当且仅当两条路线中存在一条路是不同的（两栋楼之间的多条道路被视为是不同的道路）。

现在教授希望知道，从哪些住宅楼前往主楼的上班路线数最多。

# 题目分析

为了方便，不妨反着建图，这样题目就转化为从主楼前往哪些住宅楼的上班路线数最多，多点转换为了单点，可以 $\verb!tarjan!$ 缩点后直接套路上拓扑排序即可。

这道题思路不难，重要的是如下的几项难点：

+ 可能存在 $(u,v),u=v$ 的数据（即自环），此时我们把它也当成连通块大小大于 $1$ 的连通块。

+ 拓扑排序时，若当前节点可以被访问到，那么下一个节点也能被访问到，如果下一个节点能被访问到，则有 $dp_v\gets dp_v+dp_u$，$dp$ 表示方案数。

+ 特殊地，因为所有路径和点可以无限次经过，所以一个连通块内所有点都有无数种方案数，而之前我们提到此处视自环的大小大于 $1$ 且属于连通块，所以解决了自环的问题。如果方案数超过了 $36500$，则强制改为 $36500$。

# 代码

```cpp
#include <bits/stdc++.h>
#define enter putchar(10)
#define debug(c,que) std::cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) std::cout << arr[i] << w;
#define speed_up() std::ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if(x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
#ifndef ONLINE_JUDGE
#define getc getchar
#endif
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline double double_read() {
		long long ret = 0,w = 1,aft = 0,dot = 0,num = 0;
		char ch = getc();
		while (!isdigit(ch)) {
			if (ch == '-') w = -1;
			ch = getc();
		}
		while (isdigit(ch) || ch == '.') {
			if (ch == '.') {
				dot = 1;
			} else if (dot == 0) {
				ret = (ret << 3) + (ret << 1) + ch - 48;
			} else {
				aft = (aft << 3) + (aft << 1) + ch - '0';
				num ++;
			}
			ch = getc();
		}
		return (pow(0.1,num) * aft + ret) * w;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;

const int N = 1e6 + 5;
struct Graph {
	struct Node {
		int u,v,nxt;
	} gra[N];
	int head[N];
	int idx;
	inline void add(int u,int v) {
		gra[++ idx] = (Node){u,v,head[u]},head[u] = idx;
	}
} g1,g2;
int in[N],id[N],dfn[N],low[N],dp[N],g[N],siz[N];
bool in_stack[N],vis[N];
std::stack <int> st;
int n,m,dfntim,cnt;

inline void tarjan(int now) {
	dfn[now] = low[now] = ++ dfntim,in_stack[now] = true;
	st.push(now);
	for (register int i = g1.head[now];i;i = g1.gra[i].nxt) {
		int v = g1.gra[i].v;
		if (!dfn[v]) {
			tarjan(v);
			low[now] = std::min(low[now],low[v]);
		} else if (in_stack[v]) {
			low[now] = std::min(low[now],dfn[v]);
		}
	}
	if (dfn[now] == low[now]) {
		cnt ++;
		int u;
		do {
			u = st.top();st.pop();
			in_stack[u] = false,id[u] = cnt,siz[cnt] ++;
		} while (u != now);
	}
}
inline void topo() {
	std::queue <int> q;
	for (register int i = 1;i <= cnt; ++ i) {
		if (!in[i]) q.push(i);
	}
	vis[id[n]] = true,dp[id[n]] = 1;
	while (!q.empty()) {
		int u = q.front();q.pop();
		for (register int i = g2.head[u];i;i = g2.gra[i].nxt) {
			int v = g2.gra[i].v;
			in[v] --;
			if (!in[v]) q.push(v);
			if (vis[u]) vis[v] = true;
			dp[v] += dp[u];
			if (siz[v] > 1 && vis[v]) dp[v] = 36500;
			if (dp[v] > 36500) dp[v] = 36500;
		}
	}
}
int main(void) {
	n = read() + 1,m = read();
	for (register int i = 1;i <= m; ++ i) {
		int u = read(),v = read();
		g1.add(v,u);
	}
	for (register int i = 1;i <= n; ++ i) {
		if (!dfn[i]) tarjan(i);
	}
	for (register int i = 1;i <= g1.idx; ++ i) {
		if (g1.gra[i].u == g1.gra[i].v) siz[id[g1.gra[i].u]] ++;
	}
	for (register int i = 1;i <= n; ++ i) {
		for (register int j = g1.head[i];j;j = g1.gra[j].nxt) {
			int v = g1.gra[j].v;
			if (id[i] != id[v]) {
				g2.add(id[i],id[v]);
				in[id[v]] ++;
			}
		}
	}
	topo();
	int ans = 0,num = 0;
	for (register int i = 1;i <= n; ++ i) {
		if (vis[id[i]]) {
			g[i] = dp[id[i]];
			ans = std::max(ans,g[i]);
		}
	}
	for (register int i = 1;i <= n; ++ i) {
		if (vis[id[i]] && g[i] == ans) num ++;
	}
	if (ans == 36500) {
		puts("zawsze");
	} else {
		printf("%d\n",ans);
	}
	printf("%d\n",num);
	for (register int i = 1;i <= n; ++ i) {
		if (vis[id[i]] && g[i] == ans) {
			printf("%d ",i);
		}
	}

	return 0;
}
```

---

