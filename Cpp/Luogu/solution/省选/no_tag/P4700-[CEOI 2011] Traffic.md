# [CEOI 2011] Traffic

## 题目描述

在平面直角坐标系上有 $n$ 个点，其中第 $i$ 个点的坐标是 $(x_i,y_i)$ ，所有点在一个以 $(0,0)$ 和 $(A,B)$ 为相对顶点的矩形内。

如果 $x_i=0$ ，那么我们称这个点在西侧。如果 $x_i=A$ ，那么我们称这个点在东侧。

这些点之间有 $m$ 条边，每条边可能是有向边也可能是无向边，保证边在交点以外的任何地方不相交。

现在请你求出，对于每一个西侧的点，能够沿着边到达多少东侧的点。

## 说明/提示

**样例 $2$ 解释**

![0](https://i.loli.net/2018/04/18/5ad725326df6f.png)

**数据范围**

对于 $100\%$ 的数据，有 $1\le n\le 300\ 000;0\le m\le 900\ 000;1\le A,B\le 10^9;0\le x_i\le A;0\le y_i\le B;1\le c_i,d_i\le n;k_i\in \{1,2\}$。保证西侧的点至少有一个，保证每一个无序对 $\{c_i,d_i\}$ 只会出现一次。

## 样例 #1

### 输入

```
5 3 1 3
0 0
0 1
0 2
1 0
1 1
1 4 1
1 5 2
3 5 2```

### 输出

```
2
0
2```

## 样例 #2

### 输入

```
12 13 7 9
0 1
0 3
2 2
5 2
7 1
7 4
7 6
7 7
3 5
0 5
0 9
3 9
1 3 2
3 2 1
3 4 1
4 5 1
5 6 1
9 3 1
9 4 1
9 7 1
9 12 2
10 9 1
11 12 1
12 8 1
12 10 1```

### 输出

```
4
4
0
2```

# 题解

## 作者：糪眾脦颰罷 (赞：7)

## BFS（无需缩点！）
根据题意:

>两条道路是没有相交的

不难得出：
>若一个西海岸的点$x$能连到纵坐标为$y1$和纵坐标为$y2$的东海岸(满足$y1<y2$)，那么对于在东海岸的纵坐标为$[y1,y2]$的点**若有连向西海岸的路**，其都可以到达点$x$。

不懂得看一下图自己再yy一下:
![](https://cdn.luogu.com.cn/upload/pic/64748.png)

#### 算法流程
~~难以口胡，实在看不懂就看代码吧~~
1.广搜一遍求出东海岸到不了的点

2.建反图，将可到达的东海岸的点进行标号

3.进行按y坐标**从小到大**由东海岸向西海岸的广搜，将遇到的点都标记为当前点的标号

4.进行按y坐标**从大到小**由东海岸向西海岸的广搜，将遇到的点都标记为当前点的标号

代码:
```c++
#include<bits/stdc++.h>
#define MAXN 300010
using namespace std;
int n,m,A,B,Head[MAXN],TotEdge,TotWest,TotEast,cnt,L[MAXN],R[MAXN],HeadF[MAXN],TotEdgeF;
struct Edge{
	int ed,last;
}G[MAXN*6],F[MAXN*6];
struct Point{
	int i,y,num;
}West[MAXN],East[MAXN];
queue<int> Q;
bool mark[MAXN];
bool cmp(Point XX,Point YY){
	return XX.y>YY.y;
}
void Rd(int &res){
	res=0;char ch=getchar();
	while('0'>ch||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=(res<<3)+(res<<1)+(ch-'0'),ch=getchar();
}
void Add(int st,int ed){
	TotEdge++,TotEdgeF++;
	G[TotEdge]=(Edge){ed,Head[st]};
	F[TotEdgeF]=(Edge){st,HeadF[ed]};
	Head[st]=TotEdge;
	HeadF[ed]=TotEdgeF;
}
int main(){
	memset(Head,-1,sizeof(Head));
	memset(HeadF,-1,sizeof(HeadF));
	Rd(n),Rd(m),Rd(A),Rd(B);
	for(int i=1;i<=n;i++){
		int x,y;
		Rd(x),Rd(y);
		if(x==0)West[++TotWest]=(Point){i,y};
		else if(x==A)East[++TotEast]=(Point){i,y};
	}
	for(int i=1;i<=m;i++){
		int x,y,k;
		Rd(x),Rd(y),Rd(k);
		if(k==1)Add(x,y);
		else Add(x,y),Add(y,x);
	}
	sort(West+1,West+1+TotWest,cmp);
	sort(East+1,East+1+TotEast,cmp);
	for(int i=1;i<=TotWest;i++){
		if(mark[West[i].i])continue;
		mark[West[i].i]=true;
		Q.push(West[i].i);
		while(!Q.empty()){
			int now=Q.front();
			Q.pop();
			for(int i=Head[now];~i;i=G[i].last){
				int t=G[i].ed;
				if(mark[t])continue;
				mark[t]=true;
				Q.push(t);
			}
		}
	}
	for(int i=1;i<=TotEast;i++){
		if(!mark[East[i].i])continue;
		East[i].num=++cnt;
	}
	while(!Q.empty())Q.pop();
	for(int i=1;i<=TotEast;i++){
		if(!mark[East[i].i])continue;
		if(L[East[i].i])continue;
		Q.push(East[i].i);
		L[East[i].i]=East[i].num;
		while(!Q.empty()){
			int now=Q.front();
			Q.pop();
			for(int j=HeadF[now];~j;j=F[j].last){
				int t=F[j].ed;
				if(L[t])continue;
				L[t]=East[i].num;
				Q.push(t);
			}
		}
	}
	while(!Q.empty())Q.pop();
	for(int i=1;i<=TotEast;i++){
		if(!mark[East[i].i])continue;
	}
	for(int i=TotEast;i>=1;i--){
		if(!mark[East[i].i])continue;
		if(R[East[i].i])continue;
		Q.push(East[i].i);
		R[East[i].i]=East[i].num;
		while(!Q.empty()){
			int now=Q.front();
			Q.pop();
			for(int j=HeadF[now];~j;j=F[j].last){
				int t=F[j].ed;
				if(R[t])continue;
				R[t]=East[i].num;
				Q.push(t);
			}
		}
	}
	for(int i=1;i<=TotWest;i++){
		if(L[West[i].i]==0)puts("0");
		else printf("%d\n",R[West[i].i]-L[West[i].i]+1);
	}
	return 0;
}
```

---

## 作者：ppp204 (赞：5)


> 做法:强联通分量

对于这道题,我们发现了这样一句话

> 保证边在交点以外的任何地方不相交。

那么,这说明了什么呢？

这就说明了下面这幅图

![233](https://i.loli.net/2019/07/20/5d3291501bae713922.png)

因为,如果没有连上的话,那么肯定别的点都连不上,不然就相交了

所以我们不难发现一个性质:**右边的点相当于一段区间,是连续的！**

因此,我们只需要dfs跑出他能经过的最高与最低点即可

如果这个图形成了环怎么办？缩点！

#### Code:

```
#include<bits/stdc++.h>
using namespace std;
const int M=300005,oo=2e9;
struct node{
	int x,y,flag,id;
}A[M],Q[M];
vector<int>Edge[M],G[M];
vector<node>L,R;
int dfn[M],low[M],stk[M],top,cnt,tot,ID[M];
int mx[M],mn[M],n,m,sizx,sizy;
bool instk[M],mark[M];

void Tarjan(int x){
	dfn[x]=low[x]=++tot;
	instk[x]=1; stk[++top]=x;
	if(A[x].flag==1) R.push_back(A[x]);
	for(int i=0,_=Edge[x].size(); i<_; i++){
		int y=Edge[x][i];
		if(!dfn[y]){
			Tarjan(y);
			low[x]=min(low[x],low[y]);
		}else if(instk[y]) low[x]=min(low[x],dfn[y]);
	}
	if(low[x]==dfn[x]){
		int y=-1; cnt++;
		while(x!=y){
			y=stk[top--];
			instk[y]=0;
			ID[y]=cnt;
		}
	}
}

void dfs(int x){
	if(mark[x]) return;
	mark[x]=1;
	for(int i=0,_i=G[x].size(); i<_i; i++){
		int y=G[x][i];
		dfs(y);
		mx[x]=max(mx[x],mx[y]);
		mn[x]=min(mn[x],mn[y]);
	}
}

bool cmp(node x, node y){
	return x.y>y.y;
}

int main(){
	freopen("1.in","r",stdin);
	freopen("myanswer.out","w",stdout);
	scanf("%d %d %d %d",&n,&m,&sizx,&sizy);
	for(int i=1; i<=n; i++){
		scanf("%d %d",&A[i].x,&A[i].y);
		A[i].id=i;
		if(A[i].x==sizx) A[i].flag=1;
		else if(!A[i].x) A[i].flag=-1;
		else A[i].flag=0;
	}
	for(int i=1,u,v,k; i<=m; i++){
		scanf("%d %d %d",&u,&v,&k);
		Edge[u].push_back(v);
		if(k==2) Edge[v].push_back(u);
	}
	for(int i=1; i<=n; i++){
		mn[i]=oo, mx[i]=0;
		if(A[i].flag==-1){
			L.push_back(A[i]);
			if(!dfn[i]) Tarjan(i);
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=0,_j=Edge[i].size(); j<_j; j++){
			int y=Edge[i][j];
			if(ID[i]==ID[y]) continue;
			G[ID[i]].push_back(ID[y]);
		}
	}
	sort(L.begin(),L.end(),cmp);
	sort(R.begin(),R.end(),cmp);
	for(int i=0,szr=R.size(); i<szr; i++){
		int now=ID[R[i].id],res=lower_bound(R.begin(),R.end(),R[i],cmp)-R.begin()+1;
		mn[now]=min(mn[now],res);
		mx[now]=max(mx[now],res);
	}
	for(int i=0,szl=L.size(); i<szl; i++){
		int y=ID[L[i].id];
		dfs(y);
		printf("%d\n",max(mx[y]-mn[y]+1,0));
	}
	return 0;
}
```

---

## 作者：cwfxlh (赞：3)

## [P4700](https://www.luogu.com.cn/problem/P4700)  
提供一种不需要缩点的做法。   

对于任何起点都不能到达的终点，将其删去，那么剩下的点就有一个性质：对于点 $x$，它所能到达的终点在 $y$ 的值上形成一段连续区间。   

用反证证明一下：如果对于起点 $a$，终点 $b$，$c$，$d$，$y_b>y_c>y_d$ 且 $a$ 可以到达 $b$，$d$，不能到达 $c$，则一定有另外一个起点 $e$ 可以到达点 $c$，不妨令 $e$ 在 $a$ 的上方，那么考虑 $e$ 到 $c$ 的路径与 $a$ 到 $b$ 的路径，二者必定有交点（显然），并且根据题目限制，交点一定是一个端点 $f$，那么 $a$ 可以到 $f$，$f$ 又可以到 $c$，那么 $a$ 可以到 $c$，假设不成立，结论得证。    

有了这个结论，我们只需要计算每个点到终点的最大最小 $y$ 值就好了，如果正着做需要缩点（但是我是凸轮废物所以不会），考虑对终点遍历，一遍求最大，一遍求最小就可以了。     


上代码：   
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a,b,x[500003],y[500003],mx[500003],mn[500003],vis[500003];
int k1,k2,k3,k4,k5,k6,k7,k8,k9;
vector<int>r;
vector<int>st;
vector<int>ed;
vector<int>E[500003];
vector<int>F[500003];
vector<pair<int,int> >ans;
void dfs(int now){
	vis[now]=1;
	for(auto i:E[now])if(!vis[i])dfs(i);
	return;
}
bool comp(int XX,int YY){return y[XX]>y[YY];}
int q[2000003],totq;
signed main(){
	scanf("%lld%lld%lld%lld",&n,&m,&a,&b);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&x[i],&y[i]);
		mn[i]=-1;
	}
	for(int i=1;i<=m;i++){
		scanf("%lld%lld%lld",&k1,&k2,&k3);
		E[k1].emplace_back(k2);
		F[k2].emplace_back(k1);
		if(k3==2){
			F[k1].emplace_back(k2);
			E[k2].emplace_back(k1);
		}
	}
	for(int i=1;i<=n;i++)if(vis[i]==0&&x[i]==0)dfs(i);
	for(int i=1;i<=n;i++){
		if(x[i]==0)st.push_back(i);
		if(x[i]==a&&vis[i])ed.push_back(i);
	}
	sort(st.begin(),st.end(),comp);
	sort(ed.begin(),ed.end(),comp);
	for(int i=0;i<ed.size();i++){
		totq=0;
		q[++totq]=ed[i];
		mx[ed[i]]=i;
		for(int j=1;j<=totq;j++){
			for(auto u:F[q[j]]){
				if(mx[u]>0)continue;
				mx[u]=i+1;
				q[++totq]=u;
			}
		}
	}
	for(int i=ed.size()-1;i>=0;i--){
		totq=0;
		q[++totq]=ed[i];
		mx[ed[i]]=i;
		for(int j=1;j<=totq;j++){
			for(auto u:F[q[j]]){
				if(mn[u]>0)continue;
				mn[u]=i+1;
				q[++totq]=u;
			}
		}
	}
	for(auto i:st)printf("%lld\n",max(mn[i]-mx[i]+1,0ll));
	return 0;
}
```


---

## 作者：zhouzihang1 (赞：2)

# [P4700](https://www.luogu.com.cn/problem/P4700) [CEOI2011] Traffic 题解

## 思路

我们称 $x = 0$ 的点为“左点”，$x = A$ 的点为“右点”。

显然，题目没有保证图联通，所以有些右点无法到达，我们可以先使用 bfs 筛掉不可以到达的右点，时间复杂度 $O(n)$。

然后我们发现题目中的一句话：**保证边在交点以外的任何地方不相交**。

由此可以证明，对于任意一个左点，他向右可以到达的右点一定是连续的一段（除去无法到达的）。

假设不连续：

两段连续的右点之间一定存在一个可以从其他左点到达的路径。

换句话说，出现了两条路径相交的情况。

这显然与题意不符，所以假设不成立。

所以原结论成立。

于是，我们可以建反图，把右点的 $y$ 坐标从大到小排序，然后依次 bfs，就可以求出图中点可以到达的最上边的右点的编号（这个编号是右点从小到大排序后的编号）。

同理，可以求出图中可以到达的最下边的右点的编号。

然后就可以求出每一个左点可以到达的右点的数量。

## Code

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=3e5+10,M=9e5+10;
struct point{int x,y;}a[N];
vector<int> W,E,vc[N],inv[N];
//W,E 分别存储左点和右点
//vc 是正图，inv 是反图（邻接表）
int n,m,A,B,ansr[N],ansl[N];
//ansr 即为上文中提到的最上边的右点的编号。
//ansl 即为上文中提到的最下边的右点的编号。
bool cmp1(int p,int q){return a[p].y>a[q].y;}
bool cmp2(int p,int q){return a[p].y<a[q].y;}
//cmp1 按照 y 坐标从大到小排序。
//cmp2 按照 y 坐标从小到大排序。
bool vis[N];
void bfs(int st)
{
	queue<int> q;q.push(st);vis[st]=1;
	while(q.size())
	{
		int u=q.front();q.pop();
		for(int v:vc[u]) if(!vis[v]) vis[v]=1,q.push(v);
	}
}
//bfs 标记处所有从左点出发可达的点。
void solve(int st,bool cas,int num)
{
  //cas = 0 时是从小到大，cas = 1 时与之相反。
	queue<int> q;q.push(st);
	if(cas==1) ansr[st]=num;
	else ansl[st]=num;
	while(q.size())
	{
		int u=q.front();q.pop();
		for(int v:inv[u])
		{
			if(cas==1){if(!ansr[v]) ansr[v]=num,q.push(v);}
			else{if(!ansl[v]) ansl[v]=num,q.push(v);}
		}
	}
}
int main()
{
//	freopen("traffic.in","r",stdin);
//	freopen("traffic.out","w",stdout);
	scanf("%d%d%d%d",&n,&m,&A,&B);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i].x,&a[i].y);
		if(a[i].x==0) W.push_back(i);
		if(a[i].x==A) E.push_back(i);
	}
	sort(W.begin(),W.end(),cmp1);
	for(int i=1,u,v,k;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&k);
		vc[u].push_back(v);inv[v].push_back(u);
		if(k&1^1) vc[v].push_back(u),inv[u].push_back(v);
	}
	for(int i:W) bfs(i);
	int cnt=0;
	sort(E.begin(),E.end(),cmp2);
	for(int i:E)
	{
		if(!vis[i]) continue;
		solve(i,0,++cnt);
	}
	sort(E.begin(),E.end(),cmp1);
	for(int i:E)
	{
		if(!vis[i]) continue;
		solve(i,1,cnt--);
	}
	for(int i:W)
	{
		if(!ansl[i]) puts("0");
		else printf("%d\n",ansr[i]-ansl[i]+1);
	}
	return 0;
}
```

---

## 作者：lalaji2010 (赞：1)

# P4700  [CEOI2011] Traffic

2024.8.31 update：之前的图手滑删了，又重新补上的。

## 题目链接

[洛谷 P4700 [CEOI2011] Traffic](https://www.luogu.com.cn/problem/P4700)

## 分析

首先暴力做法极其容易得到，我们对于每个最西侧的点向东侧进行 BFS，统计其能到达多少个最东侧的点，时间复杂度：$O(n^2)$。

注意到本题数据范围 $1 \leq n \leq 3 \times 10^5$，暴力做法显然不足以通过此题。

那么我们需要考虑一下这道题的特殊性质。注意到题面中有一句话说，本题中的点都是二维平面上的点，点与点之间的连边互不相交。


![](https://cdn.luogu.com.cn/upload/image_hosting/au13anhl.png)

结合图片来看，我们很容易发现一个性质，即我们删去没有最西侧的点能到达的最东侧的点后，对于每一个最西侧的点，其能到达的最东侧的点是按纵坐标排序后的一段连续区间。

证明其实也很容易，我们假设某个最西侧的点到达的最东侧的点不是一段连续区间，我们设它能够到达的纵坐标最大的最东侧的点纵坐标为 $R$，能够到达的纵坐标最小的最东侧的点纵坐标为 $L$，又因为没有最西侧的点到达的最东侧的点已经删去，所以在最东侧纵坐标区间 $(L,R)$ 中一定存在一个点直接或间接地连向另外一个最西侧的点，此时必定有两条路径在平面上相交，与题意矛盾，故结论得证。同理，定义“最西侧的点”为横坐标小于 $A$ 的任意点，此结论恒成立。

所以我们的思路很清晰：设 $U_i$ 为点 $i$ 能够到达的最东侧的点的区间上端点，$D_i$ 则为下端点。首先从每个最西侧的点向东走并标记能够到达的点；然后反向建边按纵坐标由小到大依次由能够到达的最东侧的点向西走，第一次走到点 $i$ 时，令 $D_i$ 等于当前点在**删完点后**的最东边的点纵坐标排序后的位次；再同样反向建边按纵坐标由大到小依次由能够到达的最东侧的点向西走，第一次走到点 $i$ 时，令 $U_i$ 等于当前点在**删完点后**的最东侧的点纵坐标排序后的位次；如果最后两数组对于某个最西侧的点点没有被赋值，则这个最西侧的点到达不了最东侧的点，反之对于最西侧的点 $i$，输出 $U_i-D_i+1$ 即区间长度即可。

## AC CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+7;
int n,m,A,B;
int x[N],y[N],totw,tote;
pair<int,int> we[N],ea[N];
bool book[N],vis[N];
queue<int> q;
vector<int> e[N],E[N];
int D[N],U[N],cnt;
void bfs(int s){
	book[s]=1;
	q.push(s);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=0;i<e[u].size();i++){
			int v=e[u][i];
			if(!book[v]){
				q.push(v);
				book[v]=1;
			}
		}
	}
}
void bfs_D(int s,int id){
	D[s]=id;
	vis[s]=1;
	q.push(s);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=0;i<E[u].size();i++){
			int v=E[u][i];
			if(!vis[v]){
				D[v]=id;
				q.push(v);
				vis[v]=1;
			}
		}
	}
}
void bfs_U(int s,int id){
	U[s]=id;
	vis[s]=1;
	q.push(s);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=0;i<E[u].size();i++){
			int v=E[u][i];
			if(!vis[v]){
				U[v]=id;
				q.push(v);
				vis[v]=1;
			}
		}
	}
}
int main(){
	cin>>n>>m>>A>>B;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
		if(x[i]==0){
			we[++totw]=make_pair(y[i],i);
		}else if(x[i]==A){
			ea[++tote]=make_pair(y[i],i);
		}
	}
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		e[u].push_back(v);
		E[v].push_back(u);
		if(w==2){
			e[v].push_back(u);
			E[u].push_back(v);
		}
	}
	sort(we+1,we+1+totw);
	sort(ea+1,ea+1+tote);
	for(int i=1;i<=totw;i++){
		bfs(we[i].second);
	}
	int cnt=0;//未被标记的点不计入区间，所以不能直接用下标。
	for(int i=1;i<=tote;i++){
		if(!book[ea[i].second]) continue;
		cnt++;
		bfs_D(ea[i].second,cnt);
	}
	memset(vis,0,sizeof vis);
	for(int i=tote;i>=1;i--){
		if(!book[ea[i].second]) continue;
		bfs_U(ea[i].second,cnt);
		cnt--;
	}
	for(int i=totw;i>=1;i--){
		if(U[we[i].second]==0){
			cout<<0<<"\n";
			continue;
		}
		cout<<U[we[i].second]-D[we[i].second]+1<<"\n";
	}
	return 0;
}
```

---

## 作者：Pekac (赞：1)

[P4700](https://www.luogu.com.cn/problem/P4700)

简单的，但是考试的时候没看到是平面图，就只想到了缩点后 DAG 判断能到达哪些点。用 bitset 维护做到 $\mathcal{O}(\frac{nm}{w})$ 的时空复杂度，但是空间会炸。

由于这个图是平面图，稍微推一下就可以知道所有能它最终所能到达的点一定是从西侧出发所能到达的东侧点的点集中按 $y$ 排序后的一段区间。

然后就很简单了，在读入时将 $a_i$ 排序后重编号再进行操作就很方便了，最后直接在 DAG 的反图上 dp。具体地，令 $gl_i$，$gr_i$ 表示缩点后编号为 $i$ 的强连通分量所能到达的 $y$ 最小的点和 $y$ 最大的点，然后对所有连出的点更新一下即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
const int N=3e5+10,inf=1e9;
int n,m,A,B;
int a[N],au[900010],av[900010],aw[900010],ori[N];
vector<int> g[N];
struct node{int x,y,id;} ad[N];
int head[N],cnt_e=1;
struct edge{int v,nxt;} e[1800010];
void adde(int u,int v,int w=2){
	e[++cnt_e]=(edge){v,head[u]};
	head[u]=cnt_e;
	if(w==2)adde(v,u,1);
}
int dfc,dfn[N],low[N],stk[N],tp,vis[N],cs,bel[N],gl[N],gr[N];
void dfs(int u){
	dfn[u]=low[u]=++dfc;vis[stk[++tp]=u]=1;
	for(int i=head[u],v;i;i=e[i].nxt)if(!dfn[v=e[i].v])dfs(v),low[u]=min(low[u],low[v]);else if(vis[v])low[u]=min(low[u],dfn[v]);
	if(low[u]==dfn[u]){
		int v=0;cs++;
		do{bel[v=stk[tp--]]=cs;vis[v]=0;if(a[v]==1)gl[cs]=min(gl[cs],v),gr[cs]=max(gr[cs],v);}while(v!=u);
	}
}
int deg[N],s[N],ac;queue<int> q;
pii ans[N],ne[N];
int main(){
	cin>>n>>m>>A>>B;
	for(int i=1;i<=n;gl[i]=1e9,i++)cin>>ad[i].x>>ad[i].y,ad[i].id=i;
	sort(ad+1,ad+n+1,[](node a,node b){return a.y<b.y;});
	for(int i=1;i<=n;i++)a[i]=(ad[i].x==A?1:(ad[i].x==0?0:2)),ori[ad[i].id]=i;
	for(int i=1;i<=m;i++)cin>>au[i]>>av[i]>>aw[i],adde(au[i]=ori[au[i]],av[i]=ori[av[i]],aw[i]);
	for(int i=1;i<=n;i++)if(!dfn[i]&&!a[i])dfs(i);
	for(int i=1,u,v;i<=m;i++)if(bel[u=au[i]]!=bel[v=av[i]]&&bel[u]&&bel[v])g[bel[v]].push_back(bel[u]),deg[bel[u]]++;
//	for(int i=1;i<=cs;i++)for(int j:g[i])cout<<"Edge: "<<i<<" "<<j<<"\n";
	for(int i=1;i<=cs;i++)if(!deg[i])q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int v:g[u]){
			gl[v]=min(gl[v],gl[u]),gr[v]=max(gr[v],gr[u]);
			if(!--deg[v])q.push(v);
		}
	}
	for(int i=1;i<=n;i++)s[i]=s[i-1]+(a[i]==1&&dfn[i]);
	for(int i=1;i<=n;i++)if(!a[i]){
		int j=bel[i];
//		cout<<i<<" "<<gl[j]<<" "<<gr[j]<<"\n";
		if(gl[j]!=inf)ans[++ac]=pii(ad[i].y,s[gr[j]]-s[gl[j]-1]);else ans[++ac]=pii(ad[i].y,0);
	}
	sort(ans+1,ans+ac+1,greater<pii>());
	for(int i=1;i<=ac;i++)cout<<ans[i].second<<"\n";
	return 0;
}
```

---

## 作者：Leasier (赞：1)

前置芝士：[平面图](https://oi-wiki.org/graph/planar/)、[SCC](https://oi-wiki.org/graph/scc/)、[拓扑排序](https://oi-wiki.org/graph/topo/)

首先可以把这张混合图缩点变成一个 DAG。若对于每个 SCC 中挑选一个在其中的点作为其坐标，感性地，可以认为缩点对原图性质无影响。

注意到原图的性质相当于给出这是一张**平面图**，那这张平面图有什么性质呢？

抛开那些没有任何一个西侧点可以到达的东侧点，我们会发现：**若将剩下的东侧点按 $y$ 坐标升序重编号，每个西侧点可以到达的东侧点构成一个区间**。

上述结论不难感性理解。

于是我们 Tarjan 缩点，对缩点后的反图拓扑排序，每次更新当前区间的左右端点即可。时间复杂度为 $O(n + m)$。

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <cstdio>

using namespace std;

typedef struct {
	int nxt;
	int start;
	int end;
} Edge;

typedef struct {
	int cnt = 0;
	int head[300007];
	Edge edge[1800007];
	
	inline void add_edge(int start, int end){
		cnt++;
		edge[cnt].nxt = head[start];
		head[start] = cnt;
		edge[cnt].start = start;
		edge[cnt].end = end;
	}
} Graph;

Graph G1, G2;
int x[300007], y[300007], label[300007], p[300007], dfn[300007], low[300007], belong[300007], l[300007], r[300007], deg[300007], ans[300007];
bool vis1[300007], vis2[300007], vis3[300007], vis4[300007];
stack<int> s;
queue<int> q;

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

bool cmp(const int a, const int b){
	return y[a] > y[b];
}

void dfs(int u){
	if (vis1[u]) return;
	vis1[u] = true;
	for (register int i = G1.head[u]; i != 0; i = G1.edge[i].nxt){
		dfs(G1.edge[i].end);
	}
}

void tarjan(int u, int &id, int &scc_cnt, int a){
	dfn[u] = low[u] = ++id;
	vis2[u] = vis3[u] = true;
	s.push(u);
	for (register int i = G1.head[u]; i != 0; i = G1.edge[i].nxt){
		int x = G1.edge[i].end;
		if (!vis2[x]){
			tarjan(x, id, scc_cnt, a);
			low[u] = min(low[u], low[x]);
		} else if (vis3[x]){
			low[u] = min(low[u], dfn[x]);
		}
	}
	if (dfn[u] == low[u]){
		int cur;
		scc_cnt++;
		l[scc_cnt] = 0x7fffffff;
		r[scc_cnt] = 0;
		vis4[scc_cnt] = true;
		do {
			cur = s.top();
			s.pop();
			vis3[cur] = false;
			belong[cur] = scc_cnt;
			vis4[scc_cnt] &= vis1[cur];
			if (x[cur] == a){
				l[scc_cnt] = min(l[scc_cnt], label[cur]);
				r[scc_cnt] = max(r[scc_cnt], label[cur]);
			}
		} while (cur != u);
	}
}

int main(){
	int n = read(), m = read(), a = read(), b = read(), label_id = 0, awa = 0, dfn_id = 0, scc_cnt = 0;
	for (register int i = 1; i <= n; i++){
		x[i] = read();
		y[i] = read();
		if (x[i] == a) label[i] = ++label_id;
	}
	for (register int i = 1; i <= m; i++){
		int c = read(), d = read(), k = read();
		G1.add_edge(c, d);
		if (k == 2) G1.add_edge(d, c);
	}
	for (register int i = 1; i <= n; i++){
		if (x[i] == 0) dfs(i);
	}
	for (register int i = 1; i <= n; i++){
		p[i] = i;
	}
	label_id = 0;
	sort(p + 1, p + n + 1, cmp);
	for (register int i = 1; i <= n; i++){
		if (x[p[i]] == a && vis1[p[i]]) label[p[i]] = ++label_id;
	}
	for (register int i = 1; i <= n; i++){
		if (!vis2[i]) tarjan(i, dfn_id, scc_cnt, a);
	}
	for (register int i = 1; i <= G1.cnt; i++){
		int u = G1.edge[i].start, v = G1.edge[i].end;
		if (belong[u] != belong[v] && vis4[belong[u]] && vis4[belong[v]]){
			deg[belong[u]]++;
			G2.add_edge(belong[v], belong[u]);
		}
	}
	for (register int i = 1; i <= scc_cnt; i++){
		if (vis4[i] && deg[i] == 0) q.push(i);
	}
	while (!q.empty()){
		int cur = q.front();
		q.pop();
		ans[cur] = l[cur] == 0x7fffffff && r[cur] == 0 ? 0 : r[cur] - l[cur] + 1;
		for (register int i = G2.head[cur]; i != 0; i = G2.edge[i].nxt){
			int x = G2.edge[i].end;
			l[x] = min(l[x], l[cur]);
			r[x] = max(r[x], r[cur]);
			if (--deg[x] == 0) q.push(x);
		}
	}
	for (register int i = 1; i <= n; i++){
		p[i] = i;
	}
	sort(p + 1, p + n + 1, cmp);
	for (register int i = 1; i <= n; i++){
		if (x[p[i]] == 0) cout << ans[belong[p[i]]] << endl;
	}
	return 0;
}
```

---

## 作者：qwer6 (赞：0)

## 1. Description

一个左下角为 $(0,0)$，右上角为 $(A,B)$ 的矩形中 $n$ 个不相同的点 $(x_i,y_i)$，我们称 $x_i=0$ 的点为西侧点，$x_i=A$ 的点为东侧点。这些点之间有一些边，满足边只在顶点相交，询问每一个西侧点可以通过这些边到达多少个东侧点。

## 2. Solution

这种可达性问题，我们首先肯定是先强联通分量缩点，使图成为一张 DAG 之后用拓扑排序处理。

容易得到一个 $O(\frac{n^2}{w})$ 的暴力，对于每一个强联通分量维护一个 bitset 表示这个强联通分量可以到达哪些东侧点，在拓扑排序时维护即可。

但是这种做法显然没有利用边只在顶点处相交这一性质，所以我们考虑这个性质会导出什么结论。

很容易想到：去除所有西侧点都无法到达的东侧点，将所有剩下的东侧点按照 $y$ 坐标排序并重新标号后，每一个可以到达的点一定是一个连续的区间。

考虑证明这个结论，下文所述的东侧点编号均为重标号后的。~~显然正确，无需证明。~~

不妨假定一个点 $u$ 可以到达 $L$ 和 $R$，而无法到达 $x$，其中 $L< x< R$，因而存在 $u\rightarrow L$ 和 $u\rightarrow R$ 的路径，那么这两条路径和直线 $x=A$ 构成一个封闭的三角形，由于我们已经将所有西侧点都无法到达的东侧点除去了，那么 $x$ 一定可以被一个点 $v$ 到达，也就是存在一条 $v\rightarrow x$ 的路径，这条路径一定处于矩形之中（废话，因为所有点都在矩形内），那么这条路径一定与 $u\rightarrow L$ 或者 $u\rightarrow R$ 存在交点，这里不妨假设 $v\rightarrow x$ 与 $u\rightarrow L$ 有交点，另一种情况同理。

那么交点的位置可以分为两类：

1. 交点在两条边上，显然和边只在顶点相交矛盾。
2. 交点处于一个顶点处，设这个顶点为 $y$，那么一定存在一条 $y\rightarrow x$ 的路径，而又存在 $u\rightarrow y$ 的路径，因而一定存在 $u\rightarrow x$ 的路径，和 $u$ 无法到达 $x$ 矛盾。

从而，命题得证。

那么就简单了，只需要记录每一个点可以到达的东侧点编号最小值和最大值，拓扑排序求解即可。

## 3. Code

```c++
/*by qwer6*/
/*略去缺省源与快读快写*/
const int N=3e5+5;
int n,m,A,B,cnt_scc,cnt_dfn,top,tot;
int x[N],y[N],st[N],dfn[N],low[N],id[N],L[N],R[N],d[N],east[N];
bool vis[N],flag[N];
pii ans[N];
vector<int>e[N],E[N];
void bfs(){
	queue<int>q;
	for(int i=1;i<=n;i++){
		if(x[i]==0){
			q.push(i);
			vis[i]=1;
		}
	}
	while(!q.empty()){
		int u=q.front();
		q.pop();
		if(x[u]==A)east[++tot]=y[u];
		for(int v:e[u]){
			if(vis[v])continue;
			q.push(v);
			vis[v]=1;
		}
	}
}
void Tarjan(int u){
	vis[u]=1;
	st[++top]=u;
	flag[u]=1;
	dfn[u]=low[u]=++cnt_dfn;
	for(int v:e[u]){
		if(!vis[v]){
			Tarjan(v);
			tomin(low[u],low[v]);
		}else if(flag[v])tomin(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		cnt_scc++;
		L[cnt_scc]=0x3f3f3f3f;
		R[cnt_scc]=-0x3f3f3f3f;
		do{
			flag[st[top]]=0;
			id[st[top]]=cnt_scc;
			if(x[st[top]]==A){
				int p=lower_bound(east+1,east+tot+1,y[st[top]])-east;
				tomin(L[cnt_scc],p);
				tomax(R[cnt_scc],p);
			}
		}while(st[top--]!=u);
	}
	
}
void topo(){
	queue<int>q;
	for(int i=1;i<=cnt_scc;i++)
		if(d[i]==0)q.push(i);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int v:E[u]){
			d[v]--;
			tomin(L[v],L[u]);
			tomax(R[v],R[u]);
			if(!d[v])q.push(v);
		}
	}
}
signed main(){
	raed(n),read(m),read(A),read(B);
	for(int i=1;i<=n;i++)
		read(x[i]),read(y[i]);
	for(int i=1,u,v,k;i<=m;i++){
		read(u),read(v),read(k);
		e[u].push_back(v);
		if(k==2)e[v].push_back(u);
	}
	bfs();
	sort(east+1,east+tot+1);
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++){
		if(vis[i])continue;
		Tarjan(i);
	}
	for(int u=1;u<=n;u++){
		for(int v:e[u]){
			if(id[u]==id[v])continue;
			E[id[v]].push_back(id[u]);
			d[id[u]]++; 
		}
	}
	topo();
	int now=0;
	for(int i=1;i<=n;i++){
		if(x[i]!=0)continue;
		ans[++now]={y[i],max(0,R[id[i]]-L[id[i]]+1)};
	}
	sort(ans+1,ans+now+1);
	for(int i=now;i>=1;i--)write(ans[i].second),Nxt;
}
```

---

## 作者：rainbow_cat (赞：0)

印象很深，在某校内 OJ 上大力卡常、卡空间，故写一篇题解纪念。    
由图的特性切入，注意到图是平面图，得到一个重要的性质：在去除掉东侧无法到达的点后，对于每一个西侧的点到达的都是连续的一段点。   
性质想通了就比较简单了，先跑一遍缩点，对于西侧每个点跑 DFS，计算可以到达的东侧的点段的最高与最低处，为保证复杂度记忆化即可。   
个人认为细节很多，详见代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
#ifdef ONLINE_JUDGE
char buf[1 << 17] , * p1 = buf , * p2 = buf , obuf[1 << 17] , * O = obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<17,stdin),p1==p2)?EOF:*p1++)
#endif
inline int read() {
	int x = 0 , f = 1;char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1;ch = getchar(); }
	while (isdigit(ch)) x = x * 10 + (ch ^ 48) , ch = getchar();
	return x * f;
}
int n,m,k,l,x,y,z,idx,scc,dfn[300010],low[300010],scv[300010],sum[300010];
bool vis[300010],flag[300010],vis1[300010];
struct node{int x,y,idx;}a[300010];
vector<int>e[300010],ne[300010];
int mp[300010];
stack<int>s;
bool cmp(node x,node y)
{
	if(x.x==y.x)return x.y>y.y;
	return x.x<y.x;
}
void dfs(int u)
{
	vis[u]=1;
	for(auto i:e[u])if(!vis[i])dfs(i);
}
void dfs1(int u)
{
	if(vis1[u])return;
	vis1[u]=1;
	for(auto i:ne[u])
	{
		dfs1(i);
		low[u]=max(low[u],low[i]);
		dfn[u]=min(dfn[u],dfn[i]);
	}
}
void tarjan(int u)
{
	dfn[u]=low[u]=++idx,s.push(u),flag[u]=1;
	for(auto i:e[u])
	{
		if(!dfn[i])tarjan(i),low[u]=min(low[u],low[i]);
		else if(flag[i])low[u]=min(low[u],dfn[i]);
	}
	int las=0;
	if(low[u]==dfn[u])
	{
		scc++;
		do flag[s.top()]=0,las=s.top(),scv[s.top()]=scc,s.pop();
		while(las!=u);
	}
}
int main()
{
	ios::sync_with_stdio(0);
	n=read(),m=read(),k=read(),l=read();
	for(int i=1;i<=n;i++)a[i].x=read(),a[i].y=read(),a[i].idx=i;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)mp[a[i].idx]=i;
	for(int i=1;i<=m;i++)
	{
		x=read(),y=read(),z=read();
		e[mp[x]].push_back(mp[y]);
		if(z==2)e[mp[y]].push_back(mp[x]);
	}
	for(int i=1;i<=n;i++)if(a[i].x==0)dfs(i);
	for(int i=1;i<=n;i++)
	{
		sum[i]=sum[i-1];
		if((a[i].x==k)&&vis[i])sum[i]++;
	}
	for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i);
	memset(dfn,0x3f,sizeof dfn),memset(low,0,sizeof low);
	for(int i=1;i<=n;i++)
	{
		if(a[i].x==k&&vis[i])dfn[scv[i]]=min(dfn[scv[i]],i),low[scv[i]]=max(low[scv[i]],i);
		if(a[i].x==0)flag[scv[i]]=1;
	}
	for(int i=1;i<=n;i++)
		for(auto j:e[i])
			if(scv[i]!=scv[j])
				ne[scv[i]].push_back(scv[j]);
	for(int i=1;i<=scc;i++)if(flag[i])dfs1(i);
	for(int i=1;i<=n;i++)
	{
		if(a[i].x)continue;
		if(dfn[scv[i]]==0x3f3f3f3f)cout<<0<<'\n';
		else cout<<sum[low[scv[i]]]-sum[dfn[scv[i]]-1]<<'\n';
	}
	return 0;
}
```

---

## 作者：iPhoneSX (赞：0)

# 题解
先发现一条重要性质：因为道路不能相交，所以把东侧的点按照纵坐标排序后，若纵坐标为 $y_1$ 和 $y_2$ 的两个东侧点能够到达西侧的点 $a$，那么纵坐标在 $[y_1,y_2]$ 之间的所有东侧点如果能到达西侧，一定到达 $a$。

证明：设东侧纵坐标在 $[y_1,y_2]$ 之间有一点 $b$ 可以到达西侧点 $c$ 且 $c \ne a$，那么路径 $c-d$ 肯定和路径 $a-y_1$ 或 $a-y_2$ 有交点。如果交点不是一个节点，那么不符合题目要求。如果交点是节点 $d$，那么存在路径 $a-d-b$。故这样的 $b$ 不存在。

所以对于每个西侧点，我们可以只需要求出来它能到达的东侧点中纵坐标最大的和最小的即可。

操作：先把东西两侧的点分别记录下来，按照纵坐标排序。从西边开始，一遍 $O(n)$ 搜索，标记掉谁都不能到达的东侧点并对剩下的东侧点依次标号。再建反图，由东侧向西侧做两遍 $O(n)$ 的搜索，一遍按照东侧点纵坐标从小到大，一遍从大到小，两遍搜索分别拿一个数组，将遇到的所有点都赋值为当前东侧点的编号。最后每个西侧点的答案就是两个数组的值之差再加一。

我写的深搜，代码还是比较简单的:
```cpp
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<iomanip>
#include<iostream>
#include<list>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<vector>
#define ll long long
#define DBG(x) cout << #x << "=" << x << endl
#define inf 0x3f3f3f3f
#define mod 1000000007
#define N 300005
using namespace std;
template <typename T>
void read(T& x) {
    x = 0;
    ll t = 1;
    char ch;
    ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') {
            t = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    x *= t;
}
template <typename T, typename... Args>
void read(T& first, Args&... args) {
    read(first);
    read(args...);
}
template <typename T>
void write(T y) {
    T x = y;
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) {
        write(x / 10);
    }
    putchar(x % 10 + '0');
}
template <typename T, typename... Ts>
void write(T arg, Ts... args) {
    write(arg);
    if (sizeof...(args) != 0) {
        putchar(' ');
        write(args...);
    }
}
int n,m,a,b,c,d,k,tot1,tot2,vis[N],cnt,up[N],down[N];
struct node{
	int x,y,id,cnt;
}l[N],r[N]; 
vector<int> ve[N],we[N];
bool cmp(node X,node Y){//要按照纵坐标从大到小输出答案
	return X.y>Y.y;
}
void dfs(int u){
	vis[u]=1;
	for(int i=0;i<ve[u].size();i++){
		int v=ve[u][i];
		if(vis[v]==1){
			continue;
		}
		dfs(v);
	}
}
void dfs2(int a[],int u,int k){
	a[u]=k;
	for(int i=0;i<we[u].size();i++){
		int v=we[u][i];
		if(a[v]!=0){
			continue;
		}
		dfs2(a,v,k);
	}
}
int main(){
	read(n,m,a,b);
	for(int i=1;i<=n;i++){
		read(c,d);
		if(c==0){
			l[++tot1].x=c;
			l[tot1].y=d;
			l[tot1].id=i;
		}
		if(c==a){
			r[++tot2].x=c;
			r[tot2].y=d;
			r[tot2].id=i;
		}
	}
	sort(l+1,l+1+tot1,cmp);
	sort(r+1,r+1+tot2,cmp);
	for(int i=1;i<=m;i++){
		read(c,d,k);
		if(k==2){
			ve[d].push_back(c);
			we[c].push_back(d);
		}
		ve[c].push_back(d);
		we[d].push_back(c);
	}
	for(int i=1;i<=tot1;i++){
		if(vis[l[i].id]==0){
			dfs(l[i].id);
		}
	}
	for(int i=1;i<=tot2;i++){
		if(vis[r[i].id]==1){
			r[i].cnt=++cnt;
		}
	}
	for(int i=1;i<=tot2;i++){
		if(vis[r[i].id]==0||down[r[i].id]!=0){
			continue;
		}
		dfs2(down,r[i].id,r[i].cnt);
	}
	for(int i=tot2;i>=1;i--){
		if(vis[r[i].id]==0||up[r[i].id]!=0){
			continue;
		}
		dfs2(up,r[i].id,r[i].cnt);
	}
	for(int i=1;i<=tot1;i++){
		if(up[l[i].id]==0||down[l[i].id]==0){//别忘了特判一下
			putchar('0');
			putchar('\n');
			continue;
		}
		write(up[l[i].id]-down[l[i].id]+1);
		putchar('\n');
	}
    return 0;
}
``````

---

## 作者：Imken (赞：0)

暴力做，直接 $O(n^2)$ 一个深搜。

如果我们需要一个线性的做法的话，那么肯定是不能考虑从西向东深搜的。如果要优化的话，咱可以观察到一个性质，对于所有可以到达点 $v$ 的点，这些点都可以到达点 $v$ 可以到达的点。

这个时候想到什么，拓扑。我们只需要从东侧点（出口）进行拓扑排序就行了啊！环的话，跑一遍 Tarjan 缩个点就可以啦。

很容易想到拿 bitset 维护点集，但是实现不好的话无疑会 RTE/TLE/MLE。怎么办呢？

题目不是一个矩形嘛，里面的边**都不相交**。感性思考一下，你可以发现，如果抛去无法被任何西点到达的东点，那么对于每一个西点，它可以到达的东点必然是一个连续的区间（按照坐标排序）。

那么这个时候只用维护可以到达的区间的东点区间端点，这道题就做完了。

```cpp
inline void cond()
{
	for (int i = 1; i <= n; i++)
		if (!dfn[i] && west_flag[i])
			tarjan(i);
	for (int u = 1; u <= n; u++) {
		for (int v : G[u]) {
			if (sccid[u] != sccid[v]) {
				ng[sccid[v]].push_back(sccid[u]);
				indeg[sccid[u]]++;
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		if (nodes[i].x == a && sccid[i])
			east.push_back(nodes[i]);
	}
	sort(east.begin(), east.end(), [&](const Node& lhs, const Node& rhs) { return lhs.y < rhs.y; });
	for (int i = 0; i < east.size(); i++) {
		east_min[sccid[east[i].id]] = min(i + 1, east_min[sccid[east[i].id]]);
		east_max[sccid[east[i].id]] = i + 1;
	}
}

inline void topo()
{
	queue<int> q;
	for (int i = 1; i <= scccnt; i++)
		if (!indeg[i])
			q.push(i);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (const int v : ng[u]) {
            // 更新端点
			east_min[v] = min(east_min[v], east_min[u]);
			east_max[v] = max(east_max[v], east_max[u]);
			if (!--indeg[v])
				q.push(v);
		}
	}
}

int main()
{
	cin >> n >> m >> a >> b;
	for (int i = 1; i <= n; i++) {
		nodes[i].id = i;
		cin >> nodes[i].x >> nodes[i].y;
		if (nodes[i].x == 0) {
			west.push_back(nodes[i]);
			west_flag[i] = 1;
		} else if (nodes[i].x == a) {
			east_flag[i] = 1;
		}
	}
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> k;
		G[u].push_back(v);
		if (k == 2)
			G[v].push_back(u);
	}
	memset(east_min, 0x3f, sizeof east_min);
	cond();
	topo();

	sort(west.begin(), west.end(), [&](const Node& lhs, const Node& rhs) { return lhs.y > rhs.y; });
	for (const Node x : west) {
		if (east_min[sccid[x.id]] > n)
			cout << 0 << '\n';
		else
			cout << east_max[sccid[x.id]] - east_min[sccid[x.id]] + 1 << '\n';
	}
}
```


---

## 作者：teylnol_evteyl (赞：0)

介绍一种最无脑方法。

首先对进行一次强连通分量缩点，得到一个拓扑图，然后对每一个节点建立一个 bitset，表示可以到达的东边的点，接下来在反图上跑一个拓扑排序就可以了。

但这样直接实现空间会爆炸，考虑优化。把东边的点分成几组，每一组跑一次拓扑排序，用时间换空间。当设置每 $k$ 个点分为一组跑，时间复杂度为 $O\left(\frac{n^2m}{k}\right)$，但因为 bitset 的常数优化勉强能过。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5, M = 4e6 + 5, T = 1024;

int n, m, A, y[N];
int ep[N], wp[N], ec, wc;
int la[N], h[N], ne[M], en[M], idx;
int dfn[N], low[N], dfst;
int sta[N], tt;
bool insta[N];
int scc, bel[N];
bitset<T> f[N];
int res[N];

bool cmp(int i, int j) {return y[i] > y[j];}

void add(int la[], int a, int b)
{
	ne[ ++ idx] = la[a];
	la[a] = idx;
	en[idx] = b;
}
void tarjan(int u)
{
	dfn[u] = low[u] = ++ dfst;
	insta[sta[ ++ tt] = u] = true;
	for(int i = la[u]; i; i = ne[i])
	{
		int v = en[i];
		if(!dfn[v])
		{
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if(insta[v]) low[u] = min(low[u], dfn[v]);
	}
	if(low[u] == dfn[u])
	{
		scc ++ ;
		int v;
		do{
			insta[v = sta[tt -- ]] = false;
			bel[v] = scc;
		}while(v != u);
	}
}

int main()
{
	scanf("%d%d%d%*d", &n, &m, &A);
	for(int i = 1; i <= n; i ++ )
	{
		int x;
		scanf("%d%d", &x, &y[i]);
		if(x == 0) wp[wc ++ ] = i;
		if(x == A) ep[ec ++ ] = i;
	}
	sort(wp, wp + wc, cmp);
	for(int i = 1; i <= m; i ++ )
	{
		int a, b, t;
		scanf("%d%d%d", &a, &b, &t);
		if(t == 1) add(la, a, b);
		else add(la, a, b), add(la, b, a);
	}
	
	for(int i = 1; i <= n; i ++ )
		if(!dfn[i])
			tarjan(i);
	
	for(int i = 1; i <= n; i ++ )
		for(int j = la[i]; j; j = ne[j])
		{
			int u = bel[i], v = bel[en[j]];
			if(u != v) add(h, v, u);
		}
	
	for(int i = 0; i < ec; i += T)
	{
		memset(f, 0, sizeof f);
		for(int j = 0; j < min(ec - i, T); j ++ ) f[bel[ep[i + j]]].set(j);
		for(int j = 1; j <= scc; j ++ )
			for(int k = h[j]; k; k = ne[k])
				f[en[k]] |= f[j];
		for(int j = 0; j < wc; j ++ ) res[j] += f[bel[wp[j]]].count();
	}
	
	for(int i = 0; i < wc; i ++ ) printf("%d\n", res[i]);
	
	return 0;
}
```

数据加强了请联系我撤下题解。

---

