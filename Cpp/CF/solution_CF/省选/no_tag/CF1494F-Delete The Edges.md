# Delete The Edges

## 题目描述

### 题意

给定一个 $n$ 个顶点和 $m$ 条边组成的无向连通图。你的目标是破坏给定图形的所有边。

可以选择任何顶点作为起始顶点，开始沿边行走。当你走过一条边时，这条边会被破坏，不能走被破坏的边。

最多可以在某顶点执行进行一次模式切换，模式转换后，按以下方式删除经过的边：模式转换后第一条边不被破坏，第二条边被破坏，第三条边不被破坏，第四条边被破坏，依此类推。不能切换回原始模式，可以不执行此操作。

$n,m \le 3000, m\le \dfrac{n(n-1)}{2}$。

## 样例 #1

### 输入

```
3 3
1 2
2 3
3 1```

### 输出

```
4
1 2 3 1```

## 样例 #2

### 输入

```
4 3
1 2
2 3
4 2```

### 输出

```
8
2 -1 1 2 3 2 4 2```

## 样例 #3

### 输入

```
5 5
1 2
2 3
3 1
2 4
2 5```

### 输出

```
9
2 3 1 2 -1 4 2 5 2```

## 样例 #4

### 输入

```
5 5
1 2
2 3
3 1
2 4
4 5```

### 输出

```
8
5 4 2 3 1 -1 2 1```

## 样例 #5

### 输入

```
6 5
1 2
2 3
3 4
4 5
3 6```

### 输出

```
0```

# 题解

## 作者：JasonL (赞：6)

## CF1494F Delete The Edges

[题目传送门](https://www.luogu.com.cn/problem/CF1494F)

#### 题目解析

这里补叙关于欧拉路的相关信息。

**欧拉路**，指从其中一点出发，不重复地经过图上所有边的一条路径。如果起点和终点相同，则称之为**欧拉回路**。

**无向图**中存在欧拉路当且仅当图上度数为奇数的点数量不超过 2 ，存在欧拉回路当且仅当图上任意点的度数均为偶数。

**有向图**中存在欧拉路当且仅当图上入度与出度不等的点数量不超过 2 ，存在欧拉回路当且仅当图上任意点的入度与出度均相等。

如果不存在 shift 操作，那么只要存在欧拉路即可。

观察如果使用 shift 操作时图的性质。如果我们将删除倒过来改为插入，那么从我们删除的最后一条边开始。假定我们删除完后停留在 $u$ 点，那么我们删除时沿 $v\rightarrow u$ ，而前一步我们只能走 $ u\rightarrow v$ 。以此类推，我们发现还原后得到的是一张菊花图。

我们假定切换操作前经过的边构成的图为 $G_1$ ，操作后经过的边构成的图为 $G_2$ 。由上面的分析可知 $G_1$ 一定存在一条欧拉路，而且最后停留在菊花图 $G_2$ 的中心点。那么我们只需要考虑是否存在一种分割方式满足上述条件即可。

对于 $G_2$ ，我们枚举每一个点作为中心点。为了保证 $G_1$ 满足条件，我们先将中心点与当前度数为奇数的点连成的边全部加入 $G_2$ ，图上剩余的边加入 $G_1$ ，使得度数为奇数的点尽可能小。检查当前是否合法，如果不合法则对原图上与中心点相连的边进行“翻转”，即如果原来该边在 $G_1$ ，则将其加到 $G_2$ ；反之亦然。发现如果进行翻转的次数恰为 2 , $G_1$ 中会有大于 2 个度数为奇数的点，或者有 2 个度数为奇数的点且中心点度数为偶数，此时不符合条件。故我们只需要枚举每一条边进行“翻转”后检查是否合法即可。

如何检查是否合法？首先我们可以按照上面判断存在欧拉路的方式进行第一步的判断。由于此时的图可能不连通，我们求一遍欧拉路，然后检查欧拉路上的边数与 $G_2$ 中的边数之和是否为 $m$ 即可。

这样枚举点的复杂度为 $O(n+m)$ 。加上判断的 $O(n+m)$ ，时间复杂度为 $O((n+m)^2)$ 。

```cpp
#include<iostream>
#include<cstdio>
#include<set>
using namespace std;
const int maxn=3010;
int n,m;
set<int> e[maxn],e2[maxn],del,ep;
set<int>::iterator it;
int route[maxn],tnt;
inline int read(){
	int res=0;
	char ch=getchar(),ch1=ch;
	while(!isdigit(ch))ch1=ch,ch=getchar();
	while(isdigit(ch))res=(res<<3)+(res<<1)+ch-'0',ch=getchar();
	return ch1=='-'?-res:res;
}
void euler(int x){
	while(e2[x].size()){
		int y=*e2[x].begin();
		e2[x].erase(y);
		e2[y].erase(x);
		euler(y);
	}
	route[++tnt]=x;
}
bool check(int x){
	if(!e[x].size())return false;
	int cnt=0;
	for(int i=1;i<=n;++i)
		if(e[i].size()&1)++cnt;
	if(cnt==0||(cnt==2&&e[x].size()&1));
	else return false;
	for(int i=1;i<=n;++i)e2[i]=e[i];
	tnt=0;
	euler(x);
	return tnt-1+del.size()==m;
}
void output(int x){
	if(del.size())printf("%d\n",tnt+1+del.size()*2);
	else printf("%d\n",tnt);
	for(int i=1;i<=tnt;++i)
		printf("%d ",route[i]);
	if(del.size()){
		printf("-1");
		while(del.size()){
			int y=*del.begin();
			printf(" %d %d",y,x);
			del.erase(y);
		}
	}
}
int main(){
	n=read();m=read();
	for(int i=1,x,y;i<=m;++i){
		x=read();y=read();
		e[x].insert(y);
		e[y].insert(x);
	}
	for(int i=1;i<=n;++i){
		ep=e[i];
		for(it=ep.begin();it!=ep.end();++it){
			if(e[*it].size()&1){
				del.insert(*it);
				e[*it].erase(i);
				e[i].erase(*it);
			}
		}
		if(check(i)){
			output(i);return 0;
		}
		for(it=ep.begin();it!=ep.end();++it){
			int x=*it;
			if(e[i].count(x)){
				del.insert(x);
				e[x].erase(i);
				e[i].erase(x);
			}
			else{
				del.erase(x);
				e[x].insert(i);
				e[i].insert(x);
			}
			if(check(i)){
				output(i);return 0;
			}
			if(e[i].count(x)){
				del.insert(x);
				e[x].erase(i);
				e[i].erase(x);
			}
			else{
				del.erase(x);
				e[x].insert(i);
				e[i].insert(x);
			}
		}
		for(it=ep.begin();it!=ep.end();++it){
			int x=*it;
			if(!e[i].count(x)){
				del.erase(x);
				e[x].insert(i);
				e[i].insert(x);
			}
		}
	}
	puts("0");
	return 0;
}
```

---

## 作者：Larryyu (赞：3)

## _Description_

给定一张 $n$ 个点、$m$ 条边的图，你可以从图上任意一点出发，目标是删去所有的边，当一条边被删去后你不能再走此边。

初始模式下，一条边在你走过后会立即被删去。

你可以在任意一点切换模式（或全程不换），换完模式后走过的第偶数条便会被删去，且不可重新换回初始模式。

求一组方案。

## _Solution_

观察样例可得切换模式后走的图为一个菊花图，下面浅浅分析一下。

假设只有一条边，则折返走一遍便能删完。

若为两条边 $(i,j),(j,k)$，发现只能 $j\rightarrow i\rightarrow j\rightarrow k\rightarrow j$ 将其删完。

依此类推，删边必须像 $i\rightarrow j\rightarrow i$ 折返地删。

所以我们可以枚举菊花图的中心，构造出走一条终点为菊花图中心的欧拉路径，然后切换模式的方案。

关键在于如何求出这条欧拉路径。

首先将所有和中心相连的奇点（度数为奇）和中心连的这条边删去，这样这个点就会变为偶点（度数为偶），方便后续操作。

然后得出当前图中奇点个数 $cnt$，和中心度数是否为 $0$，记为 $f$。

若 $f=true$：

- $cnt>2$，无法构出欧拉路径，非法。

- $cnt=2$ 且中心不为奇点，终点不为中心，非法。
- $cnt=2$ 且外围图不连通（除去度数为 $0$ 的点，这些点虽然不连通，但切换模式后都会连通），非法。
- $cnt=2$ 且外围连通，即我们已经构造出了合法方案。

若 $f=false$：

- $cnt\ge2$，还要连一条边到中心，然而再加边就不是欧拉路径了，非法。

剩下还剩当前路径有中心但外围不连通、当前路径不含中心两种情况，发现 $cnt=0$ 使得我们可以在加一条删去的边到欧拉路径上，那我们就枚举这条边。

首先当前外围图（此时是除去度数为 $0$ 的点但此点不为中心）连通块个数要小于等于 $2$，因为加一条边只能让两个连通块连通。

然后分别将这两连通块染色，遍历删去的边，若边的两顶点颜色不同，则加上这条边，发现这种合法方案的起点就是这两顶点中不是中心的那个点。

发现一定存在这条先前被删去的边，即我们一定能找到合法方案。

然后我们按输出要求输出方案即可，首先遍历欧拉路径，再切换模式，然后折返删菊花图。

代码细节很多，理清思路再写。

时间复杂度 $O(n(n+m))$

## _Code_

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int tot,head[3030];
int in[3030],du[3030],col[3030];
bool vis[3030],viss[3030],pit[3030];
vector<int> path;
struct edge{
	int to,next,id;
}e[6060];
void add(int x,int y,int z){
	e[++tot]=edge{y,head[x],z};
	head[x]=tot;
}
void dfs(int x,int v=0){
	viss[x]=1;
	col[x]=v;
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].to,w=e[i].id;
		if(viss[y]||vis[w]) continue;
		dfs(y,v);
	}
}
void get(int x){
	bool f=0;
	int ss,ww;
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].to,w=e[i].id;
		if(!vis[w]){
			vis[w]=1;
			get(y);
			path.push_back(x);
		}
	}
}
bool solve(int st){
	for(int i=1;i<=n;i++) du[i]=in[i],viss[i]=0,pit[i]=0,col[i]=0;
	for(int i=1;i<=m;i++) vis[i]=0;
	bool f=0;
	int ts=0,ttot=0;  //ts为方案起点、ttot为切换模式后删的边数
	for(int i=head[st];i;i=e[i].next){
		int y=e[i].to,w=e[i].id;
		if(du[y]%2){  //删去中心与偶点相连的边
			pit[y]=1,du[y]--,du[st]--,vis[w]=1,ttot++;
		}else f=1;  //中心是否在当前欧拉路径上
	}
	int cnt=0,fl=0;
	for(int i=1;i<=n;i++){
		if(du[i]%2) cnt++;  //奇点数量
		if(du[i]%2&&i!=st) fl=i;  //得出合法欧拉路径的起点
	}
	if(f){
		if(fl==0) fl=st;  //欧拉回路则任选起点
		if(cnt>2) return 0;
		if(cnt==2&&du[st]%2==0) return 0;
		if(cnt==2){
			dfs(st);
			for(int i=1;i<=n;i++){  //判断外围连通性
				if(du[i]==0) continue;
				if(!viss[i]) return 0;
			}
			ts=fl;
		}
		
	}else{
		if(cnt>=2) return 0;
	}
	if(cnt==0){
		dfs(st);  //染第一个连通块
		bool ff=0;
		for(int i=1;i<=n;i++){
			if(du[i]==0) continue;
			if(!viss[i]){
				if(ff) return 0;  //有至少三个连通块
				dfs(i,1);
				ff=1;
			}
		}
		if(ff){
			for(int i=head[st];i;i=e[i].next){
				int y=e[i].to,w=e[i].id;
				if(pit[y]&&col[y]){  //是之前删去的奇点且与中心不在同一连通块上
					pit[y]=0,vis[w]=0,ttot--;
					ts=y,du[y]++,du[st]++;
					break;
				}
			}
		}else{  //只有一个连通块即为欧拉回路
			ts=st;
		}
	}
	cout<<m+ttot+2<<'\n';  //m条边要删完则有m次操作，ttot条边被操作2次，加上起点和切换模式的2次操作
	get(ts);  //遍历欧拉路径
	for(int i=path.size()-1;i>=0;i--) cout<<path[i]<<" ";
	cout<<st<<" ";
	cout<<-1<<" ";
	for(int i=head[st];i;i=e[i].next){
		int y=e[i].to,w=e[i].id;
		if(pit[y]){
			cout<<y<<" "<<st<<" ";  //折返删菊花图
		}
	}
	return 1;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		in[x]++,in[y]++;
		add(x,y,i),add(y,x,i);
	}
	for(int i=1;i<=n;i++){
		if(solve(i)){
			return 0;
		}
	}
	cout<<"0"<<'\n';  //无解
	return 0;
}
```

---

## 作者：int08 (赞：3)

## 前言
模拟赛 T4，由于不会写欧拉路（写挂了）遗憾离场，错失场切 *$2900$ 的机会。

# Solution

题意还是比较简洁的。

容易发现如果没有第二种模式那么原问题就是找一条欧拉路，所以猜测做法跟欧拉路有关。

所以我们需要找一下第二种模式的性质。

这个时候观察一些样例，手玩一下，发现一个重要性质：

我们**倒着**考虑模式二的过程，最后一次一定是走了一条边，假设是 $(v,u)$，那么走完倒数第二次的时候在 $v$ 点，只存在一条边可以走，只能是 $(u,v)$，倒数第三次假设删去了 $(v_2,u)$，那么走完倒数第四次的时候应该位于 $v_2$，此时同样只有 $u$ 能到达 $v_2$，倒数第四次走的只能是 $(u,v_2)$……观察到，由于**没有重边和自环**，模式二只能清空一个**菊花图**，并需要从根开始走。

那么现在题目就简单了：将图分为两部分 $S_1,S_2$（可以为空），并使得 $S_1$ 有欧拉路，$S_2$ 是菊花图，并且欧拉路的终点是菊花图的根。

你说：“好了剩下的我会了，找一下奇点（度数为奇数的点），枚举菊花的根就行了……等一下为啥 $n,m\le 3000$？这不是可以开到 $10^5$ 吗？”

没那么简单。
### 做法（雏形）

很显然，我们来枚举一下菊花的根，现在，剥出一朵菊花也就是删掉一些和根连通的边并使得剩下一个欧拉路。

显然，删去奇点和根连通的边就能消掉一个奇点，外面最多只能有一个奇点和根不连通。

我们特判掉直接有欧拉路的情况，现在至少有 $4$ 个奇点。

如果根与所有奇点相连，全部删掉之后可能会导致根和外界不连通了，所以我们可以随意留一条连向奇点的边。

否则，直接删去所有根与奇点相连的边。

现在外面只剩下了一个奇点，加上根（奇点数量必为偶数），正好满足条件。

### 做法（修正）

这题并没有结束，考虑这个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/5d06wqxc.png)

看似蓝点和所有奇点相连，删去之后就没有奇点了，但是要是删除了，剩下的点都不连通了，显然没有欧拉路！

咋办呢？别忘了毕竟这题 $n,m\le 3000$，弄一些比较暴力的方案：

对于某个点，如果它已经和某个奇点不连通了，那么它和剩下的奇点的连边都需要删，检测剩下的图是否连通即可。

如果它和所有奇点连通，我们可以选择保留一条连向奇点的边，那么看保留了哪一条能使剩下的图联通即可。

使用并查集维护就行了，复杂度 $O((n+m)^2\log n)$。

### 其余细节

~~好的所以到底咋写欧拉回路？~~ 欧拉回路的实现参考了另一篇题解，使用 `set` 维护，十分方便，不需要链式前向星了。

注意，某个度数为 $1$（也就是只和根连通的奇点）虽然删去了边之后和其它点不连通了，但是这个并不影响答案，检查的时候忽略掉这一部分。

## AC Code
~~我就是传说中的 `goto` 享受者。~~
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 3055
int task,n,m,i,u[N],v[N],deg[N],jd,cj[N],id[N][N],ava[N],req,s,t,vis[N];
vector<int> e[N],ans;
set<int> ed[N];
int fa[N];
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
bool dfs(int u)
{
	while(ed[u].size())
	{
		int v=*ed[u].begin();
		ed[u].erase(v);
		ed[v].erase(u);
		dfs(v);
	}
	ans.push_back(u);
}
int main()
{
	cin>>n>>m;
	for(i=1;i<=n;i++) fa[i]=i;
	for(i=1;i<=m;i++) cin>>u[i]>>v[i],deg[u[i]]++,deg[v[i]]++,id[u[i]][v[i]]=id[v[i]][u[i]]=i,e[u[i]].push_back(v[i]),e[v[i]].push_back(u[i]),fa[find(u[i])]=find(v[i]);
	for(i=1;i<=n;i++) if(deg[i]%2) jd++;
	for(i=1;i<=n;i++) if(find(i)!=find(1))
	{
		cout<<0;return 0;
	}
	memset(ava,1,sizeof(ava));req=m;
	if(!jd)
	{
		cout<<m+1<<"\n";
		for(i=1;i<=n;i++)
			for(auto v:e[i]) ed[i].insert(v);
		dfs(1);
		for(auto x:ans) cout<<x<<" ";
		return 0;
	}
	int ii=0,tg=1,len;
	here:
	here2:
	memset(ava,1,sizeof(ava));req=m;
	for(ii++;ii<=n;ii++)
	{
		if(deg[ii]%2) cj[ii]++;
		for(auto v:e[ii]) if(deg[v]%2) cj[ii]++;
		if(cj[ii]>=jd-1) {t=ii;break;}
	}
	if(ii>n)
	{
		cout<<0;
		return 0;
	}
	s=0;
	for(int x=1;x<=n;x++) if(!id[t][x]&&deg[x]%2&&x!=t) s=x;
	for(auto v:e[t]) if(deg[v]%2&&v!=s) req--,ava[id[t][v]]=0;
	if(s)
	{
		for(i=1;i<=n;i++) fa[i]=i;
		for(i=1;i<=m;i++) if(ava[i]) fa[find(u[i])]=find(v[i]);
		tg=1;
		for(i=1;i<=n;i++) if(find(i)!=find(t)&&!(deg[i]%2==1&&e[i].size()==1&&i!=t)) tg=0;
		if(!tg) goto here;
	}
	else
	{
		for(i=1;i<=n;i++) fa[i]=i;
		for(i=1;i<=m;i++) if(ava[i]) fa[find(u[i])]=find(v[i]);
		set<int> se;
		for(i=1;i<=n;i++) if(!(deg[i]%2==1&&e[i].size()==1&&i!=t)) se.insert(find(i));
		if(se.size()==1)
			for(auto v:e[t]) if(deg[v]%2) {s=v,ava[id[s][t]]=1,req++;break;}
		if(se.size()==2)
			for(auto v:e[t]) if(deg[v]%2&&find(v)!=find(t)&&se.find(find(v))!=se.end()&&se.find(find(t))!=se.end()) {s=v,ava[id[s][t]]=1,req++;break;}
		if(!s) goto here2;
	}
	for(i=1;i<=n;i++)
		for(auto v:e[i]) if(ava[id[i][v]]) ed[i].insert(v);
	dfs(s);
	reverse(ans.begin(),ans.end());
	cout<<ans.size()+1+2*(m-req)<<"\n";
	for(auto x:ans) cout<<x<<" ";
	cout<<-1<<" ";
	for(auto v:e[t]) if(deg[v]%2&&v!=s) cout<<v<<" "<<t<<" ";
	return 0;
 } 
```
# The End.

---

## 作者：WRuperD (赞：3)

这是一篇比较低质量的题解，但是由于场上好像切了，所以还是来写写。

首先考虑不进行模式切换是什么样的。这相当于跑一个欧拉路径。直接做就好了。

考虑切换后的模式可以怎么样删边，或者说比较擅长删什么样子的图。手玩一下发现貌似第二种模式对比切换前的模式优势在于它可以删掉一个菊花（从菊花中心到叶子来回走即可）。所以我们考虑就单纯的切换模式删菊花就好了。这样子做的正确性可以感性理解。~~我不会证明。~~

于是我们可以考虑枚举最后菊花的中心位置在哪里，然后贪心的去把所以与之连边的度数为奇数的节点的边删去。注意删完之后所有度数大于零的点要联通。然后判断一下能不能构成一个欧拉路径，输出方案即可。

细节有点小多，我的实现非常劣，代码就不放了。

---

## 作者：sqrtqwq (赞：0)

> Lemma：切换后一定走的是菊花图。

> Proof：为了删掉倒数第二条边，我们必须在最后一步走回头路。类似的，为了删掉倒数第四条边，我们必须在下一步走回头路。以此类推我们走到最后一定走的是一个菊花图。

这样子我们就可以枚举菊花中心点 $u$。接下来考虑如何构造答案。

删去 $u$ 的若干条相邻的边后，要求只有 $u$ 和另外一个点的度数为奇数或者所有点的度数并且除了孤点，图联通。

假如有和 $u$ 不相邻的点的度数为奇数，则需要将所有与 $u$ 相联的奇数度电之间的连边删除。然后就可以构造啦！

由于 $n,m$ 比较小，可以直接暴力 $\mathrm O(n(n + m))$ 做。

---

