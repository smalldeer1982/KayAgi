# [BalticOI 2008] 阀门

## 题目描述

成为码农多年的你，已经厌倦了码农生活。你决定跳槽，去做一些不一样的事情。

正在寻找下一份工作的你，被一份水产养殖的工作吸引住了。“太酷了！”并且，鱼是很好的生物 嗯切绘也是这么想的 。所以你毫不犹豫地去应聘了。幸运的是，你成功拿到了 Offer。今天是你工作的第一天。

你的老板已经给你分配了任务：分隔两个蓄水池。你手上的操作指南告诉了你如下信息：

这两个蓄水池之间有一些管道连通，每个管道有两个阀门。当两个阀门同时开启时，这个管道就处于开启状态，反之处于关闭状态。阀门用开关控制。同一个开关会控制一些阀门，但是每一个阀门都只被一个开关控制。有可能一个管道上的两个阀门被同一个开关控制，也可能有开关不控制任何阀门。 

![0](https://i.loli.net/2018/02/19/5a8ac86221c4b.png)

开关以以下两种方式控制阀门：

-    当开关闭合时阀门打开，当开关断开时阀门关闭
-    当开关闭合时阀门关闭，当开关断开时阀门打开

玩了一会儿开关之后你突然意识到你的编程经历会十分有用。给出每个阀门被哪个开关所控制，判断是否可能关闭所有管道，如果可以，找出这种合法配置下每一个开关的状态。 

## 说明/提示

**数据范围**

对于 $30\%$ 的数据，$n\le 40, m\le 20$。

对于所有数据，$1\le n\le 2.5\times 10^5, 1\le m\le 5\times 10^5$​​。 

## 样例 #1

### 输入

```
3 2
1 0 2 1
1 0 2 0
1 1 2 1```

### 输出

```
0
1```

## 样例 #2

### 输入

```
2 1
1 0 1 0
1 1 1 1```

### 输出

```
IMPOSSIBLE```

# 题解

## 作者：0nullptr (赞：5)

[题目传送门：P4659 BalticOI 2008阀门](https://www.luogu.org/problem/P4659)

这道题要求我们找到一种排列方式，使得两个水池不相互连通。其中每个阀门有开关两种状态。

很容易想到直接暴力枚举每个开关的开闭状态，判断每种状态是否可行，但这样只能过30%的数据。

考虑将每个开关的开闭关系抽象成一个点，并以水管的开放与否作为边的连接条件，那么我们可以推断出这样一个结论：对于一个开关，如果在图中的一个强联通分量中出现它既开又关的情况 ~~（薛定谔：不是我干的）~~ ，那么一定是无解情况，而且当且仅当出现这种情况时无解。

根据以上结论，可以找到这种建图方式：
- 将每个开关$\text{i}$拆成两个点，正点$\text{i << 1}$和反点$\text{i << 1 | 1}$，分别表示开关在开\闭情况下这个管道的开放情况。
- 对于每行输入给定的两个点，我们从一个点向另一个点的反点建立单向边，表示当一个开关开\闭时，另一个开关的状态

在如上建图并求出图的强连通分量之后，就只需要找出一种使不同强连通分量之间的点不互相影响的做法。有一种简单的方法是判断一个开关的正反点所处的强连通分量编号值，正点大的为断开，反点大的为闭合。

附上完整代码

```cpp
vector<int> G[MAXN];
int pre[MAXN], lowlink[MAXN], sccno[MAXN];
stack<int> S;
int dfs_clock, scc_cnt;//强连通分量系变量声明

//朴素的强连通分量板子
void dfs(int u) {
	pre[u] = lowlink[u] = ++dfs_clock;
	S.push(u);
	for (unsigned i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (!pre[v]) {
			dfs(v);
			lowlink[u] = min(lowlink[u], lowlink[v]);
		} else if (!sccno[v]) {
			lowlink[u] = min(lowlink[u], pre[v]);
		}
	}
	if (lowlink[u] == pre[u]) {
		scc_cnt++;
		while(1) {
			int x = S.top();
			S.pop();
			sccno[x] = scc_cnt;
			if(x == u) break;
		}
	}
}

void find_scc(int n) {
	for (int i = 2 ; i <= n; i++)
		if(!pre[i]) dfs(i);
}

int main() {
	int n, m;
	cin>>n>>m;
	for (int i = 1; i <= n; i++) {
		int u, tu, v, tv;
		cin>>u>>tu>>v>>tv;
		int x = 2 * u + tu, y = 2 * v + tv;
		G[x].push_back(y ^ 1);
		G[y].push_back(x ^ 1);
	}//存图
	find_scc(m * 2 + 1);
	queue<int> ans;//用于记录答案
	for (int i = 1; i <= m; i++) {
		if (sccno[i << 1] > sccno[i << 1 | 1])
			ans.push(0);
		else if (sccno[i << 1] == sccno[i << 1 | 1]) {
			puts("IMPOSSIBLE");
			return 0;//判断无解情况，及时退出
		} else ans.push(1);
	}
	while (!ans.empty()) cout<<ans.front()<<endl, ans.pop();//输出答案
	return 0;
}
```

---

## 作者：2018ty43 (赞：3)

此题解为个人对 @0nullptr 的题解内容补充。

## 题意
有 $n$ 管道 $2n$ 个阀门，每个阀门状态由指定开关决定，要使每个管道有一个阀门关闭。

## 思路
先想到网络流，但发现难以控制每个开关的开关节点只有一个有流，也因可能两个阀门都关闭难以确定最大流。

此时反向思考，一个阀门打开意味着另一个阀门必定关闭。因此可以对开关拆点，由使阀门打开的节点向使另一个阀门关闭的节点连有向边，表示对其的依赖。

记开关 $i$ 的断开闭合为 $i$ 与 $i'$ ,则若 $i$ 可达 $i'$，$i'$ 又可达 $i$ ，即 $i$ 开关的闭合依赖于断开，断开又依赖于闭合，无解。  
否则若 $i$ 可达 $i'$，则只能选 $i'$，反之亦然。  
若 $i$ 与 $i'$ 互不可达，则选满足其依赖的节点都被选的。因为若 $i$ 向 $j$ 有连边，则 $j'$ 向 $i'$ 有连边，所以一个点的依赖节点对应的反点都依赖这个点的反点，一个点被选了说明依赖其反点的开关都有点被选了。

此时发现可以选择两点中所属强连通分量编号最小的（使用 tarjan 算法）。  
若 $i$ 可达 $i'$ 则 $i'$ 的强连通分量编号必定比 $i$ 小。  
否则假设 $i$ 所属强联通分量编号小于 $i'$ 所属编号，不合法时则 $i$ 的依赖点强连通分量编号小于依赖 $i'$ 的点的强连通分量编号。  
分类讨论，若 $i$ 所属强联通分量编号小于依赖 $i'$ 的点的强连通分量编号，则 “$i$ 的依赖点强连通分量编号小于依赖 $i'$ 的点的强连通分量编号”不成立，因为 $i$ 的依赖点会先被遍历。反之则“$i$ 所属强联通分量编号小于 $i'$ 所属编号”不成立，因为 $i'$ 会先被遍历。
因此用此方法选择是正确的。

---

## 作者：ottora (赞：2)

### 分析

一道 [2-SAT](https://www.luogu.com.cn/problem/P4782) 模板题，但是很不明白为什么其他题解没有点明 2-SAT。

设第 $i$ 个开关状态为 $x_i\left(x_i\in\left\{0,1\right\}\right)$，首先发现答案必须满足对于每一条管道，都有 $x_a=s_a$ 或 $x_b=s_b$。所以本题是有 $m$ 个未知量和 $n$ 个约束的 2-SAT，直接套板子即可。

### 代码

```cpp
#include<bits/stdc++.h>
const int maxn=2000005;
const int maxe=2000005;
using namespace std;
int N,M,tot,lnk[maxn],nxt[maxe],son[maxe];
int tim,dfn[maxn],low[maxn],fa[maxn],top,stk[maxn],scn,scc[maxn];
void add_e(int x,int y){son[++tot]=y,nxt[tot]=lnk[x],lnk[x]=tot;}
void Tarjan(int id){
	dfn[stk[++top]=id]=low[id]=++tim;
	for(int j=lnk[id];j;j=nxt[j])
		if(!dfn[son[j]]) Tarjan(son[j]),low[id]=min(low[id],low[son[j]]);else
		if(!fa [son[j]])                low[id]=min(low[id],dfn[son[j]]);
	if(dfn[id]==low[id]) for(scn++;true;)
		if(fa[stk[top]]=id,scc[stk[top]]=scn,stk[top--]==id) return;
}
int read(){
	int f=1,ret=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f; ch=getchar();}
	while( isdigit(ch)) ret=(ret<<3)+(ret<<1)+(ch&15),ch=getchar();
	return f*ret;
}
int main(){
	M=read(),N=read();
	for(int i=1;i<=M;i++){
		int x=read(),a=read(),y=read(),b=read();
		add_e(x+N*(a^1),y+N*b);
		add_e(y+N*(b^1),x+N*a);
	}
	for(int i=1;i<=N;i++) if(!dfn[  i]) Tarjan(  i);
	for(int i=1;i<=N;i++) if(!dfn[N+i]) Tarjan(N+i);
	for(int i=1;i<=N;i++) if(fa[i]==fa[N+i]){printf("IMPOSSIBLE\n");return 0;}
	for(int i=1;i<=N;i++) printf("%d\n",scc[i]>scc[N+i]);
	return 0;
}
```

---

## 作者：WuMin4 (赞：0)

## [[BalticOI 2008] 阀门](https://www.luogu.com.cn/problem/P4659)

## 思路

为什么评紫？2-SAT 模板直接搬过来都能 A。

设每个开关的状态为 $x_i$，观察到对于每个限制都要满足「$x_i$ 为 `true` / `false` 或 $x_j$ 为 `true` / `false`」，因为对于每条水管至少要有一个阀门关闭才能保证水管关闭。

显然该问题满足 2-SAT 的形式，具体可见[【模板】2-SAT](https://www.luogu.com.cn/problem/P4782)，直接套用模板即可。

注意本题内存限制比较小，对于某些写法可能需要优化空间复杂度。

## 代码

```cpp
#include <bits/stdc++.h>
#define to(x) (x<=n?x+n:x-n)
using namespace std;
struct node{
	int x;
	bool y;
};
int n,m,col[1000005],nc;
vector<node> t[1000005];
vector<int> id;
bitset<1000005> vis;
void add(int x,int y){
	t[x].push_back({y,0});
	t[y].push_back({x,1});
}
void dfs(int x){
	vis[x]=true;
	for(node &v:t[x])
		if(!v.y&&!vis[v.x]) dfs(v.x);
	id.push_back(x);
}
void dfs2(int x){
	col[x]=nc;
	for(node v:t[x])
		if(v.y&&!col[v.x]) dfs2(v.x);
}
void kosaraju(){
	for(int i=1;i<=n;i++)
		if(!vis[i]) dfs(i);
	for(int i=id.size()-1;i>=0;i--){
		if(col[id[i]]) continue;
		nc++,dfs2(id[i]);
	}
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>m>>n;
	for(int x,xx,y,yy,i=1;i<=m;i++){
		cin>>x>>xx>>y>>yy;
		if(xx) x+=n;
		if(yy) y+=n;
		add(to(y),x);
		add(to(x),y);
	}
	n*=2;
	kosaraju();
	for(int i=1;i<=n/2;i++){
		if(col[i]==col[i+n/2]){
			cout<<"IMPOSSIBLE";
			return 0;
		}
	}
	for(int i=1;i<=n/2;i++){
		if(col[i]>col[i+n/2])
			cout<<0<<endl;
		else
			cout<<1<<endl;
	}
	return 0;
}
```

[记录](https://www.luogu.com.cn/record/211287515)

---

