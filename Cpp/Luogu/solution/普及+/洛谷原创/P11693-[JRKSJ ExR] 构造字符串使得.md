# [JRKSJ ExR] 构造字符串使得

## 题目描述

给你一张 $n$ 个点 $m$ 条边的无向图。现在有一枚棋子初始在点 $x$。双人博弈，先后手轮流移动棋子，每次可以将棋子移动到图上**任意一个**「与当前棋子所在结点有边直接相连」的结点。**保证每个结点都有至少一条边与之相连**。

有一初值为 $0$ 的变量 $v$，**每次移动过后**，记当前棋子所在结点编号为 $t$，则将 $v$ 赋值为 $\max(v,t)$。也就是说，$v$ 的值是棋子移动到过的结点编号最大值且**棋子的初始位置 $x$ 一开始并不计算在内**。

现在先后手**总共移动 $k$ 次棋子**，先手希望最终 $v$ 尽可能大，后手希望最终 $v$ 尽可能小。

共有 $q$ 次询问，每次询问给出 $x,k$，询问假如从 $x$ 开始一次共 $k$ 步的博弈，若双方均采用最优策略，那么最终 $v$ 的值为多少。

## 说明/提示

### 样例解释

![](https://cdn.luogu.com.cn/upload/image_hosting/as3pdnqp.png)

样例中的图如上。

对于第一个询问，显然先手无法迫使后手移动到 $5$，所以答案 $\le 4$，先手第一步移动到 $4$ 即可达成。

对于第二个询问，先手一步能到达的编号最大的点是 $3$，所以答案是 $3$。

### 数据范围

**本题采用捆绑测试。**

| $\text{Subtask}$ | $n\le$ | $q\le$|特殊性质| 分数 |
|:--:|:--:|:--:|:--:|:--:
| $1$ | $5$ |$5$|  | $7$ |
| $2$ | $80$ | $80$ || $14$ |
| $3$ | $700$ | $700$ || $17$ |
| $4$ | $2\times 10^5$ |$50$|| $20$ |
| $5$ | $2\times 10^5$ | $2\times 10^5$ | $✓$ | $5$ |
| $6$ | $2\times 10^5$ | $2\times 10^5$ | | $37$ |

特殊性质：保证图的形态为一条链。

对于所有数据，保证 $2\le n\le 2\times 10^5$，$1\le m\le 5\times 10^5$，$1\le q\le 2\times 10^5$，$1\le x,k\le n$。

保证给出的图无重边、无自环，保证对于任意点 $u$ 至少存在一个点 $v$ 使得 $u,v$ 之间存在一条边。

## 样例 #1

### 输入

```
5 5 5
1 2
1 4
2 3
2 5
3 4
1 2
4 1
5 3
1 5
2 2```

### 输出

```
4
3
4
4
5```

# 题解

## 作者：Jadonyzx (赞：12)

首先对于初始的点 $u$，先手若采取一种短浅的走法，直接走到最近的最大点，一定是可行的，而后手直接走回 $u$，这种策略在一开始的点值也算上的情况下是正确的，但如果 $u>\forall v \in edge_u$ 这种方法就不一定对了。

考虑另一种情况，不妨设过程为 $u\longrightarrow v\longrightarrow w$。

但是考虑到后手走到 $w$ 后，由于 $w$ 结算过了，那么他只需要反向进行先手的操作即可使答案不再更新，那么游戏一定在 $4$ 步以内结束。

不妨设 $dp_{i,j,k}$ 表示到达 $i$ 号点，还剩 $j$ 步，轮到 $k$ 走的结果，不妨设先手为 $1$，那么答案就是 $dp_{x,\min(k,4),1}$。

转移：$dp_{i,j,1}=\max_{v\in edge_i}\max(dp_{v,j-1,0},v)$，$dp_{i,j,0}=\min_{v\in edge_i}\max(dp_{v,j-1,1},v)$。

预处理即可。

---

## 作者：include13_fAKe (赞：9)

## 前言

考场上调不出来这一题想拼暴力 $63+25+10+5=103$，但显然拼不出来。

## 思路 

### Subtask 1

直接裸暴力即可。

暴搜时记录目前的节点编号、剩余步数、轮到谁走、目前的答案。

时间复杂度 $O(qn^k)$。


```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=114514;
int n,m,q; 
vector<int> g[N];
int dfs(int u,int k,int id,int include13){
//	cout<<u<<' '<<k<<' '<<id<<' '<<include13<<endl; 
	if(k==0)	return max(u,include13);
	if(id==1){
		//希望最大的人先走 
		int max1=include13;
		for(int i=0;i<g[u].size();i++){
			int v=g[u][i];
			max1=max(max1,dfs(v,k-1,2,max(include13,v)));
		} 
		return max1;
	} 
	else{
		//希望最小的人先走 
		int min1=1e9;
		for(int i=0;i<g[u].size();i++){
			int v=g[u][i];
			min1=min(min1,dfs(v,k-1,1,max(include13,v)));
		} 
		return min1;
	}
}
signed main(){
	cin>>n>>m>>q;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	while(q--){
		int a,b;
		cin>>a>>b;
		cout<<dfs(a,b,1,0)<<endl; 
	} 
	cout<<endl;
	return 0;
}
```
### Subtask 2

发现相同的状态被反复搜索到了很多次！考虑**记忆化搜索**（但我的程序把数组命名为 dp）。

时间复杂度 $O(qn^3)$，空间复杂度 $O(n^3)$。
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=114514;
int n,m,q; 
vector<int> g[N];
int dp[87][87][3][87];
int dfs(int u,int k,int id,int include13){
	if(dp[u][k][id][include13])	return dp[u][k][id][include13];
//	cout<<u<<' '<<k<<' '<<id<<' '<<include13<<endl; 
	if(k==0)	return max(u,include13);
	if(id==1){
		//希望最大的人先走 
		int max1=include13;
		for(int i=0;i<g[u].size();i++){
			int v=g[u][i];
			max1=max(max1,dfs(v,k-1,2,max(include13,v)));
		} 
		return dp[u][k][id][include13]=max1;
	} 
	else{
		//希望最小的人先走 
		int min1=1e9;
		for(int i=0;i<g[u].size();i++){
			int v=g[u][i];
			min1=min(min1,dfs(v,k-1,1,max(include13,v)));
		} 
		return dp[u][k][id][include13]=min1;
	}
}
signed main(){
	cin>>n>>m>>q;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	while(q--){
		int a,b;
		cin>>a>>b;
		cout<<dfs(a,b,1,0)<<endl; 
	} 
	cout<<endl;
	return 0;
}
```

### Subtask 3

手玩样例（也可以理论推导）可以发现：棋子最多只会走 $3$ 个点！考虑将剩余步数的大小控制下来（数组相应维度 $\le 5$）。记忆化搜索的数组少掉了一维！


```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=114514;
int n,m,q; 
vector<int> g[N];
int dp[705][12][3][705];
int dfs(int u,int k,int id,int include13){
	if(dp[u][k][id][include13])	return dp[u][k][id][include13];
//	cout<<u<<' '<<k<<' '<<id<<' '<<include13<<endl; 
	if(k==0)	return max(u,include13);
	if(id==1){
		//希望最大的人先走 
		int max1=include13;
		for(int i=0;i<g[u].size();i++){
			int v=g[u][i];
			max1=max(max1,dfs(v,k-1,2,max(include13,v)));
		} 
		return dp[u][k][id][include13]=max1;
	} 
	else{
		//希望最小的人先走 
		int min1=1e9;
		for(int i=0;i<g[u].size();i++){
			int v=g[u][i];
			min1=min(min1,dfs(v,k-1,1,max(include13,v)));
		} 
		return dp[u][k][id][include13]=min1;
	}
}
signed main(){
	cin>>n>>m>>q;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	while(q--){
		int a,b;
		cin>>a>>b;
		b=min(b,3);
		cout<<dfs(a,b,1,0)<<endl; 
	} 
	cout<<endl;
	return 0;
}
```

### Subtask 4 & 5

考虑将以上搜索的模板应用于这两档分中。

一种手段是用 map 代替数组，注意 map 嵌套的方式。

另一种方法是裸暴搜。考虑将这三段代码拼在一起，得 $63$ 分。笔者赛时也就止步于此了。


```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=5*114514;
int n,m,q; 
vector<int> g[N];
int dp[1005][4][3][1005];
map<int,map<int,map<int,map<int,int> > > > dp1;
inline int dfs(int u,int k,int id,int include13){
	if(dp[u][k][id][include13])	return dp[u][k][id][include13];
//	cout<<u<<' '<<k<<' '<<id<<' '<<include13<<endl; 
	if(k==0)	return max(u,include13);
	if(id==1){
		//希望最大的人先走 
		int max1=include13;
		for(int i=0;i<g[u].size();i++){
			int v=g[u][i];
			max1=max(max1,dfs(v,k-1,2,max(include13,v)));
		} 
		dp[u][k][id][include13]=max1;
		return max1;
	} 
	else{
		//希望最小的人先走 
		int min1=1e9;
		for(int i=0;i<g[u].size();i++){
			int v=g[u][i];
			min1=min(min1,dfs(v,k-1,1,max(include13,v)));
		} 
		dp[u][k][id][include13]=min1;
		return min1;
	}
}
inline int dfs1(int u,int k,int id,int include13){
	if(dp1[u][k][id][include13])	return dp1[u][k][id][include13];
//	cout<<u<<' '<<k<<' '<<id<<' '<<include13<<endl; 
	if(k==0)	return max(u,include13);
	if(id==1){
		//希望最大的人先走 
		int max1=include13;
		for(int i=0;i<g[u].size();i++){
			int v=g[u][i];
			max1=max(max1,dfs1(v,k-1,2,max(include13,v)));
		} 
		dp1[u][k][id][include13]=max1;
		return max1;
	} 
	else{
		//希望最小的人先走 
		int min1=1e9;
		for(int i=0;i<g[u].size();i++){
			int v=g[u][i];
			min1=min(min1,dfs1(v,k-1,1,max(include13,v)));
		} 
		dp1[u][k][id][include13]=min1;
		return min1;
	}
}
inline int dfs2(int u,int k,int id,int include13){
//	if(dp1[u][k][id][include13])	return dp1[u][k][id][include13];
//	cout<<u<<' '<<k<<' '<<id<<' '<<include13<<endl; 
	if(k==0)	return max(u,include13);
	if(id==1){
		//希望最大的人先走 
		int max1=include13;
		for(int i=0;i<g[u].size();i++){
			int v=g[u][i];
			max1=max(max1,dfs2(v,k-1,2,max(include13,v)));
		} 
//		dp1[u][k][id][include13]=max1;
		return max1;
	} 
	else{
		//希望最小的人先走 
		int min1=1e9;
		for(int i=0;i<g[u].size();i++){
			int v=g[u][i];
			min1=min(min1,dfs2(v,k-1,1,max(include13,v)));
		} 
//		dp1[u][k][id][include13]=min1;
		return min1;
	}
}
signed main(){
	cin>>n>>m>>q;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	while(q--){
		int a,b;
		cin>>a>>b;
		b=min(b,3);
		if(n<=1000)	cout<<dfs(a,b,1,0)<<endl; 
		else if(q<=50)	cout<<dfs1(a,b,1,0)<<endl;
		else cout<<dfs2(a,b,1,0)<<endl;
	} 
	cout<<endl;
	return 0;
}
```
### 最终解法

考虑去掉目前答案维，正确性也是显然的。

设 $dp_{i,j,k}$ 表示目前在 $i$ 号点，还有 $j$ 轮（$j\le3$），轮到第 $k$ 个人走的最大点号。

时间复杂度 $O(n)$。据说还可以把 $k$ 去掉。


```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2*114514;
int n,q;
int m;
vector<int> g[N];
int dp[N][5][3];	//目前在第 i 个点 还有 j 步 先手/后手  
int dfs(int x,int k,int id){
	if(dp[x][k][id])	return dp[x][k][id];
	if(k==0)	return dp[x][k][id]=x;
	if(id==1){
		int include13=0;//此处是最大值  
		for(int i=0;i<g[x].size();i++){
			int v=g[x][i];
			include13=max(include13,dfs(v,k-1,2));
			include13=max(include13,v);
		}
//		cout<<x<<' '<<k<<' '<<id<<' '<<include13<<endl;
		return dp[x][k][id]=include13;
	}
	else{
		int include13=x;
		int include13_fAKe=1e9;
		for(int i=0;i<g[x].size();i++){
			int v=g[x][i];
			include13_fAKe=min(include13_fAKe,max(dfs(v,k-1,1),v));
//			include13_fAKe=min(include13_fAKe,v);
		}
		include13=max(include13,include13_fAKe);
//		cout<<x<<' '<<k<<' '<<id<<' '<<include13<<endl;
		return dp[x][k][id]=include13;
	}
}
signed main(){
	cin>>n>>m>>q;
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		g[u].push_back(v),g[v].push_back(u);
	}
	while(q--){
		int x,k;
		cin>>x>>k;
		cout<<dfs(x,min(3,k),1)<<endl;
	}
	cout<<endl;
	return 0;
}
```
## 考点总结

$${\LARGE \begin{Vmatrix}
部分分编号  & 分值 & 主要考察的知识点\\
  &  & \\
 \color{Red} 1 & \color{Red}7 & \color{Red}【5】深度优先搜索 \\
  &  & \\
 2 & 14 & \begin{matrix}
【4】动态规划的基本思路\\
【6】 记忆化搜索\\
\end{matrix}\\
  &  & \\
 \color{Red}3 & \color{Red}17 & \begin{matrix}
\color{Red}【4】动态规划的基本思路 \\
\color{Red}【6】搜索的剪枝优化 \\
\color{Red}【6】记忆化搜索
\end{matrix}\\
  &  & \\
 4 & 20 & 【6】搜索的剪枝优化\\
  &  & \\
 \color{Red}5 & \color{Red}5 & \color{Red}【6】搜索的剪枝优化\\
  &  & \\
 6 & 37 & \begin{matrix}
【4】简单一维动态规划 \\
【6】搜索的剪枝优化
\end{matrix}
\end{Vmatrix}} $$

本题具有一定的思维要求，作为本场比赛的 T1 是难得的好题。

---

## 作者：critnos (赞：8)

注意到经过三次操作后，轮到后手操作，他一定会移动回第二步操作之后的点，并且之后每步都这样撤销先手的操作。因为这样不会使答案继续增大了。所以可以直接把 $k\gets \min(k,3)$，然后直接“当前棋子在位置 $i$，还剩 $j$ 步，当前操作的是先手/后手”这样做 dp 即可。

时间复杂度 $O(m+q)$。

---

## 作者：ykzzldz (赞：4)

简单题，不懂为啥评绿，评个黄得了。

令 $S_T$ 表示与集合 $T$ 中的任意一个点相邻的点所构成的集合，$mx_S$ 和 $mn_S$ 分别表示集合 $S$ 中编号的最大值和最小值。先手动模拟一下 $k$ 较小时的答案：

- $k=1$：$mx_{S_{\{x\}}}$
- $k=2$：$mn_{S_{S_{\{x\}}}}$
- $k=3$：$mx_{S_{S_{S_{\{x\}}}}}$

这里，我们似乎找到了一些规律，但是当 $k$ 过大的时候，我们无法快速统计答案。通过模拟博弈的过程，我们可以得到一个显然的结论，在第四次操作时，后手将棋子移向第三部中移来的位置，一定是不劣的。此时，后面的操作都会在两个点中反复横跳。于是，当 $k>3$ 时，答案与 $k=3$ 时相同。而 $k\le 3$ 时的答案，可以记忆化搜索做到线性。下面给出代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,m,q,f[N][5][2];
vector<int>a[N];
int dfs(int x,int k,int op){
	if(!k)return x;
	if(f[x][k][op])return f[x][k][op];
	if(op)f[x][k][op]=n;
	for(int y:a[x]){
		if(op)f[x][k][op]=min(f[x][k][op],max(dfs(y,k-1,op^1),y));
		else f[x][k][op]=max(f[x][k][op],max(dfs(y,k-1,op^1),y));
	}
	return f[x][k][op];
}
int main(){
	cin>>n>>m>>q;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		a[u].push_back(v);
		a[v].push_back(u);
	}
	while(q--){
		int x,k;
		cin>>x>>k;
		cout<<dfs(x,min(k,3),0)<<'\n';
	}
	return 0;
}
```

---

## 作者：CQ_Bab (赞：4)

# 前言
没脑子题，赛时以为是用暴力找最优方案结果找半天没看出来方案，倒是 1 个多小时才切，~~菜死了~~，给一种不用 dp 的方法。
# 思路
首先分类讨论。

- 如果 $x<val_x$，其中 $val_x$ 表示与 $x$ 相连的点的最大值，那么你会发现如果先手从 $x$ 走到 $val_x$ 那么后周就会一直重新走回 $x$。
- 否则还需要分类讨论。
- 首先如果 $k=2$ 那么你会发现第一步会走到与 $x$ 相连且与自己相连的最小值最大的地方（因为第二布会走最小的那个）。
- 否则我们假设第一布走到 $to$ 第二布走到 $to1$ 第三步走到 $to2$，那么我们发现因为第三步会是先手操作所以 $to2$ 为与 $to1$ 相连的最大值，又因为 $to1$ 那步为后手所以 $to1$ 为能使得 $to2$ 最小的那个点，而 $to1$ 自然是使得 $\max(to1,to2)$ 最大的那个。

这些东西都可以预处理，时间复杂度 $O(m)$。
# 代码
暴力大概长这样。
```cpp
void solve() {
	in(n),in(m),in(q);
	rep(i,1,m) {
		int x,y;
		in(x),in(y);
		v[x].pb(y);
		v[y].pb(x);
	}
	rep(i,1,n) for(auto to:v[i]) val[i]=max(val[i],to);
	while(q--) {
		int x,k;
		in(x),in(k);
		int res=0;
		for(auto to:v[x]) {
			res=max(res,to);
		}
		if(res>=x||k==1) cout<<res<<endl;
		else {
			k--;
			if(k==1) {
				for(auto to:v[x]) {
					int res1=n;
					for(auto to1:v[to]) {
						res1=min(res1,to1);
					}
					res=max(res,max(res1,to));
				}
			}else {
				for(auto nxt:v[x]) {
					int rr=n;
					for(auto to:v[nxt]) {
						rr=min(rr,max(to,val[to]));
					}
					res=max(res,rr);
				}
			}cout<<min(res,x)<<endl;
		}
	}
}
```
而正解反而更短。
```cpp
void solve() {
	in(n),in(m),in(q);
	rep(i,1,m) {
		int x,y;
		in(x),in(y);
		v[x].pb(y);
		v[y].pb(x);
	}
	rep(i,1,n) vv[i]=n,vv1[i]=n;
	rep(i,1,n) for(auto to:v[i]) val[i]=max(val[i],to);
	rep(i,1,n) for(auto to:v[i]) vv[i]=min(vv[i],max(to,val[to]));
	rep(i,1,n) for(auto to:v[i]) vv1[i]=min(vv1[i],to);
	rep(i,1,n) for(auto to:v[i]) vv2[i]=max({vv1[to],to,vv2[i]});
	rep(i,1,n) for(auto to:v[i]) vv3[i]=max(vv3[i],vv[to]);
	while(q--) {
		int x,k;
		in(x),in(k);
		int res=val[x];
		if(res>=x||k==1) printf("%d\n",res);
		else {
			k--;
			if(k==1) res=max(res,vv2[x]);
			else res=max(res,vv3[x]);
			printf("%d\n",min(res,x));
		}
	}
}
```

---

## 作者：gghack_Nythix (赞：4)

## 前言：

考场上注意到了所有性质，然后脑子一抽就并没有用到发现的性质，最终结果是第一题都没过。

## 分析：

首先可以想到一些贪心一类的做法。

但是发现对于一条边 $(u,v)$ 并不存在一些比较有规律的偏序关系，而且这是一张图，用贪心的考虑情况很复杂（主要是我写了一发获得 0 pts），所以直接贪心应该不是正解。

那么我们先尝试打个暴力，具体而言，你枚举当前 $u$ 这个点是先手还是后手，然后将每个出边都搜索得到最优解，最后合并答案。记忆化一下就有 21pts。

```cpp
# include <bits/stdc++.h>
# define pb push_back
using namespace std;
const int N = 1e6 + 5 , INF = 1e9;
int n , m , q , maxx[N] , cur;
int dp[2000][2][2000];
vector <int> g[N];
int dfs (int now , int k , int op) {
    if (k == 0) return now;
    if (dp[now][op][k]) return max (dp[now][op][k] , now);
    if (op == 1) {
        int minn = INF , pos = 0 , maxx = INF;
        for (auto x : g[now]) maxx = min ( maxx , max (dfs (x , k - 1 , op ^ 1) , x) );
        return dp[now][op][k] = maxx;
    }
    else {
        int minn = 0 , pos = 0 , maxx = 0;
        for (auto x : g[now]) maxx = max ( maxx , max (dfs (x , k - 1 , op ^ 1) , x) );
        return dp[now][op][k] = maxx;
    }
}
void solve () {
    int u , k , ans = 0 , maxx2 = 0 , minn2 = INF , tmp = 0;
    cin >> u >> k , tmp = u , ++cur;
    for (int i = 1;i <= n;++i) for (int j = 0;j < 2;++j) for (int kk = 0;kk <= n;++kk) dp[i][j][kk] = 0;
    return cout << dfs (u , k , 0) << "\n" ,  void ();
}
signed main () {
    ios::sync_with_stdio (false) , cin.tie(0) , cout.tie(0);
    cin >> n >> m >> q;
    for (int i = 1;i <= m;++i) {
        int u , v;
        cin >> u >> v , g[u].pb (v) , g[v].pb (u);
    }
    for (int i = 1;i <= n;++i) if (g[i].size()) sort (g[i].begin() , g[i].end() , greater<int>()) , maxx[i] = g[i][0];
    while ( q-- ) solve ();
    return 0;
}
```

注意到 $v$ 是单调不降的，所以最后先后手应该会在某个地方反复横跳，后手每次都是为了撤销先手的最新的操作。

这条性质看起来挺没用的对吧，但是再仔细思考你就会发现，当先后手全部执行完一次操作之后，此时如果先手再动一步，后手一定会尝试撤销，否则由于前文提及 $v$ 是单调不降的，后手不选择撤销一定不会优于当前状态。换句话讲，$k\leq 3$ 的操作才是有用的。

所以你手动限制一下 $k$ 的范围就做完了。

```cpp
# include <bits/stdc++.h>
# define pb push_back
using namespace std;
const int N = 2e5 + 5 , INF = 1e9;
int n , m , q , maxx[N] , cur;
pair <int , int> dp[N][4];
int ans[N][4];
vector <int> g[N];
int dfs (int now , int k , int op) {
    if (k == 0) return now;
    if (dp[now][k].second == cur) return max (dp[now][k].first , now);
    if (op == 1) {
        int minn = INF , pos = 0 , maxx = INF;
        for (auto x : g[now]) maxx = min ( maxx , max (dfs (x , k - 1 , op ^ 1) , x) );
        return dp[now][k] = {maxx , cur} , maxx;
    }
    else {
        int minn = 0 , pos = 0 , maxx = 0;
        for (auto x : g[now]) maxx = max ( maxx , max (dfs (x , k - 1 , op ^ 1) , x) );
        return dp[now][k] = {maxx , cur} , maxx;
    }
}
void solve () {
    int u , k ;
    cin >> u >> k , ++cur , k = min (k , 3);
    return cout << (ans[u][k] ? ans[u][k] : ans[u][k] = dfs (u , k , 0)) << "\n" ,  void ();
}
signed main () {
    ios::sync_with_stdio (false) , cin.tie(0) , cout.tie(0);
    cin >> n >> m >> q;
    for (int i = 1;i <= m;++i) {
        int u , v;
        cin >> u >> v , g[u].pb (v) , g[v].pb (u);
    }
    while ( q-- ) solve ();
    return 0;
}
```

---

## 作者：fish_love_cat (赞：3)

当 $k=1$ 时，答案显然。

注意到当后手操作时若有邻点已经被计录答案过，返回一定不劣。此时情况称作反复横跳。


容易想到 $k$ 很大时两人反复横跳，答案不会再改变。那么我们是可以将 $k$ 等价缩小的。

惊讶的发现 $n,q$ 大的惊人，所以考虑预处理出所有答案。而 $k$ 可以缩小这无疑是一个很适于预处理的性质。

但不管怎么说先把每个点 $k=1$ 时的答案存下来。

---

然后我没有注意到：

> 棋子的初始位置 $x$ 一开始并不计算在内。

所以我认定当 $k>1$ 时就开始反复横跳了，后手无脑回 $x$ 即可。

于是挂了。

---

仔细审查题面后我们又该如何做呢？

经过思考，发现 $k>2$ 时会反复横跳。手动模拟可知这是一定的。

先分析一下反复横跳时应该怎么做。

当以某一个点为基础开始反复横跳时，答案显然是该点与其相邻所有点取最大值。

这个可以先预处理。

容易发现后手会选择一个反复横跳答案最小的点反复横跳。此时反复横跳点的答案就是最终的答案。

我们对一个点求出其周边一圈点反复横跳答案的最小值。这个是后手走后会得到的最优答案。一样预处理掉。

那么先手选点时，必定会走到一个后手走后答案最大的点。由于预处理了每个点后手处理后的结果，我们可以轻松的预处理出来。

那么做完了。

---

继续分析 $k=2$ 时的做法。~~你怎么知道这个我写挂调了一个世纪（~~

首先思考后手会怎么走。

显然此时没有反复横跳答案变大的顾忌，后手一定会走到相邻答案最小的点。这个可以预处理。

然后先手走到每个点的答案也就可以预处理了。

最后该点的答案即走到周围一圈点答案的最大值。

那么做完了。

---

彻底做完了。但是你如果直接像我这样写大分讨会写的很史山。听说有神秘 dp 做法，但我不会。

所以放史山代码供各位一乐。

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int>ve[200005];
int maxx[200005];
int maxx2[200005];
int mini[200005];
int mini2[200005];
int mini3[200005];
int mini4[200005];
int ans[200005];
bool vis[200005];
void dfs(int x){
    vis[x]=1;
    for(int i=0;i<ve[x].size();i++){
        if(!vis[ve[x][i]])dfs(ve[x][i]);
        mini[x]=min(mini[x],maxx2[ve[x][i]]),
        mini4[x]=max(mini4[x],mini3[ve[x][i]]);
    }
}
void dfs1(int x){
    vis[x]=1;
    for(int i=0;i<ve[x].size();i++){
        if(!vis[ve[x][i]])dfs1(ve[x][i]);
        ans[x]=max(ans[x],mini[ve[x][i]]);
    }
}
int main(){
    memset(mini,0x3f,sizeof mini);
    memset(mini2,0x3f,sizeof mini2);
    int n,m,q;
    cin>>n>>m>>q;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        ve[u].push_back(v);
        ve[v].push_back(u);
        maxx[u]=max(maxx[u],v);
        maxx[v]=max(maxx[v],u);
        mini2[u]=min(mini2[u],v);
        mini2[v]=min(mini2[v],u);
    }
    for(int i=1;i<=n;i++)
    maxx2[i]=max(maxx[i],i),
    mini3[i]=max(mini2[i],i);
    for(int i=1;i<=n;i++)
    if(!vis[i])dfs(i);
    memset(vis,0,sizeof vis);
    for(int i=1;i<=n;i++)
    if(!vis[i])dfs1(i);
    while(q--){
        int x,y;
        cin>>x>>y;
        if(y==1)cout<<maxx[x]<<'\n';
        else if(y==2)cout<<mini4[x]<<'\n';
        else cout<<ans[x]<<'\n';
    }
    return 0;
}
```

这数组干什么用的我也忘了。大家看个乐呵就行了。

---

## 作者：Eterna (赞：3)

设第 $i$ 次移动前，棋子在节点 $d_i$，与 $i$ 相连的所有节点构成的集合为 $S_i$

容易发现 $v$ 随棋子移动单调不减，而走到走过的棋子 $v$ 一定不增。所以第 $4$ 步时，我们可以直接将棋子走到 $d_3$。此后，不管先手走哪里，我们都可以直接将棋子走到 $d_3$。

所以我们得到结论：$k>3$ 的情况与 $k=3$ 等价。

于是我们分别讨论 $k\in\{ 1,2,3 \}$ 的所有情况即可。

> 当 $k=1$ 时，显然答案为 $\max_{i \in S_x} i$。

> 当 $k=2$ 时，第二步显然会走向 $\min_{i \in S_{v_2}} i$，计算第二步答案为 $g_{v_2,1}=\max\{\min_{i \in S_{v_2}} i,v_2\}$。总的答案则为 $\max_{i \in S_x} g_{i,1}$。

> 当 $k=3$ 时，第三步会走向 $\max_{i \in S_{v_3}} i$，计算第三步答案为 $g_{v_3,2}=\max\{\max_{i \in S_{v_2}} i,v_2\}$。第二步希望 $g_{v_3,2}$ 尽可能小，则第二步答案为 $g_{v_2,3}=\max\{ \min_{i \in S_{v_2}} g_{i,2},v_2\}$。第一步希望答案尽可能大，那答案即为 $\max_{i \in S_{x}}g_{i,3}$。

预处理即可，时间复杂度 $O(m+q)$。

---

## 作者：Getaway_Car_follower (赞：3)

简单题，建议黄。

**结论**：总共最多走到 $3$ 个有效节点。

证明简单，很显然后手在第 $4$ 步时会走回先手第 $3$ 步的点，接下来，每次先手走完后手一定走回去。

那么我们设 $a_i$ 为 $i$ 邻域的最大编号，很显然当 $k=1$ 时先手一开始会走向 $a_i$。

$k=2$ 时，我们设 $b_i$ 为 $i$ 邻域的最小编号，$c_i=\max_{\{i,j\}\in G} \max\{j,b_j\}$，其中 $G$ 为边集，很显然答案为 $c_x$。

$k=3$ 时，我们用类似的方法，设 $d_i=\max\{(\min_{\{i,j\}\in G}(\max\{a_j,j\})),i\}$，$e_i=\max_{\{i,j\}\in G}d_j$，那么答案为 $e_x$。

我们发现上面那一大堆东西可以在 $O(m)$ 的时间复杂度内求出，那么这题就做完了。

---

## 作者：entelecheia_with_3 (赞：2)

## 前言：

赛时没能做出来，赛后看题解理解不了怎么推出 $k>3$ 无意义，经过思考，恍然大悟，决定写篇题解。

## 正文：

题意还是很好理解的，两人轮流操作，先手希望 $v$ 尽量大，后手希望 $v$ 尽量小。一开始想到后手应该怎么走，如果当前点有机会走到一个更大的点，那么对于后手来说，为了避免 $v$ 变大，退回上一个点是更好的。注意到一点，对于起点，并不会对答案有贡献。那么问题转化为找到拉扯开始的时机。

下面模拟一下：

- 第一步：先手走。
- 第二步：后手走，不能无脑退回，因为起点并未对答案做出贡献，直接退回可能使 $v$ 变大。
- 第三步：先手走。
- 第四步：由于上一次走到的点（其实是第二步走到的点）已经对答案做出了贡献，所以直接退回，并不会令 $v$ 更大，这时候无脑退回即可。
- 第五步重复第三步。
- 第六步重复第四步。

到这里不难发现，只有前三步的操作才会对 $v$ 产生贡献。

## 实现：

用记搜实现即可，代码如下。

```cpp
#include<bits/stdc++.h>
#define rise(i,l,r) for(int i=l;i<=r;i++)
#define fall(i,r,l) for(int i=r;i>=l;i--)
#define pii pair<int,int>
#define div cout<<"____________________\n";
#define db cout<<"work\n";
using namespace std;
const int maxn=1e6+10;
int n,m,q,p,k;
int head[maxn],to[maxn],ne[maxn],idx;
int re[maxn][4][2];
void add(int a,int b){
	to[++idx]=b;
	ne[idx]=head[a];
	head[a]=idx;
}
void in(){
	int u,v;
	cin>>n>>m>>q;
	rise(i,1,m){
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
}
int dfs(int x,int k,int r){
	if(re[x][k][r])return re[x][k][r];
	re[x][k][r]=r?INT_MIN:INT_MAX;
	for(int i=head[x];~i;i=ne[i]){
		int v=to[i];
		if(r)re[x][k][r]=max(re[x][k][r],max(dfs(v,k-1,r^1),v)); 
		else re[x][k][r]=min(re[x][k][r],max(dfs(v,k-1,r^1),v));
	}
	return re[x][k][r];
}
int main(){
	ios::sync_with_stdio(false);
	memset(head,-1,sizeof head);
	in();
	rise(i,1,n)
		re[i][0][0]=re[i][0][1]=i;
	rise(i,1,q){
		cin>>p>>k;
		k=min(k,3);
		cout<<dfs(p,k,1)<<endl;
	}
	return 0;
}
```

---

## 作者：pies_0x (赞：2)

# P11693 \[JRKSJ ExR] 构造字符串使得 题解

本题可以通过 dp 计算特殊情况再多次 dp 反推一般情况。

如果本题起点算的话，那肯定是先手走一步，后手再走回去。

我们可以先计算起点算，先手先的答案 $dp1$。

通过枚举下一步要走到哪里取最优答案，反推起点算，后手先的答案 $dp2$。

即 $dp2_i = \max(i, \min\limits_{j\in V_i} dp1_j)$。

再通过相同方法反推起点不算，先手先的答案 $dp3$。此时已是一般情况。

见下：

```cpp
#include<cstdio>
#include<vector>
using namespace std;

#define N 200005

int n,m;
int dp1[N],dp2[N],dp3[N];
vector<int> map[N];
/*
dp1: 起点计，先手先
dp2: 起点计，后手先
dp3: 起点不计，先手先
*/

signed main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		dp1[i]=i;
	for(int i=1;i<=m;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		dp1[u]=max(dp1[u],v);
		dp1[v]=max(dp1[v],u);
		map[u].push_back(v);
		map[v].push_back(u);
	}
	for(int i=1;i<=n;++i)
	{
		dp2[i]=2e9;
		for(int j:map[i])
			dp2[i]=min(dp2[i],dp1[j]);
		dp2[i]=max(dp2[i],i); // 此处之所以不直接开头直接赋值为 i ，是因为 dp2[i] 可能会被 dp1[j] 更新为更小，但因为 i 要计算，故放到最后计算
	}
	for(int i=1;i<=n;++i)
		for(int j:map[i])
			dp3[i]=max(dp3[i],dp2[j]);
	return 0;
}
```

$dp3$ 是刚开始先手遇到的情况，$dp2$ 是后手遇到的情况，$dp1$ 是**第一步后**先手遇到的情况。注意到 $dp3$ 是考虑了 $dp1$ 的情况的，**故如果步数不够，不会有 $dp1$ 的情况，$dp3$ 有误。**

所以，共 $2$ 步和共 $1$ 步应特殊计算。

同样的道理，我们再次使用反推法。

第 $2$ 步是后手执棋，不考虑第 $1$ 步，由于是特殊情况下，没有第 $3$ 步的情况，所以此时后手面对的情况是：起点计算，只有一步。

明显枚举一步可到的结点取最小值即可，既然只有一步，无需再考虑先手。

反推回第一步同 $dp3$ 的计算方法。

见下：

```cpp
#include<cstdio>
#include<vector>
using namespace std;

#define N 200005

int n,m;
vector<int> map[N];
int dp4[N],dp5[N];
/*
dp4: 第二步(起点计，后手先，共一步)
dp5: 第一步(起点不计，先手先，共两步)
*/

signed main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		dp4[i]=2e9;
	for(int i=1;i<=m;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		dp4[u]=min(dp4[u],v);
		dp4[v]=min(dp4[v],u);
		map[u].push_back(v);
		map[v].push_back(u);
	}
	for(int i=1;i<=n;++i)
		dp4[i]=max(dp4[i],i); // 这里也同理
	for(int i=1;i<=n;++i)
		for(int j:map[i])
			dp5[i]=max(dp5[i],dp4[j]);
	return 0;
}
```

对了，一步的情况也要单独再算哦！枚举一步可到的结点取最大值即可。

## Code

两个代码拼起来不会都不会吧？

```cpp
#include<cstdio>
#include<vector>
using namespace std;

#define N 200005

int n,m,q;
vector<int> map[N];
int dp1[N],dp2[N],dp3[N];
int dp4[N],dp5[N];
int dp6[N];
/*
dp1: 起点计，先手先
dp2: 起点计，后手先
dp3: 起点不计，先手先
dp4: 第二步(起点计，后手先，共一步)
dp5: 第一步(起点不计，先手先，共两步)
dp6: 起点不计，先手先，仅一步
*/

signed main()
{
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;++i)
		dp1[i]=i;
	for(int i=1;i<=n;++i)
		dp4[i]=2e9;
	for(int i=1;i<=m;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		dp1[u]=max(dp1[u],v);
		dp1[v]=max(dp1[v],u);
		dp4[u]=min(dp4[u],v);
		dp4[v]=min(dp4[v],u);
		dp6[u]=max(dp6[u],v);
		dp6[v]=max(dp6[v],u);
		map[u].push_back(v);
		map[v].push_back(u);
	}
	for(int i=1;i<=n;++i)
		dp4[i]=max(dp4[i],i);
	for(int i=1;i<=n;++i)
	{
		dp2[i]=2e9;
		for(int j:map[i])
			dp2[i]=min(dp2[i],dp1[j]);
		dp2[i]=max(dp2[i],i); // 此处之所以不直接开头直接赋值为 i ，是因为 dp2[i] 可能会被 dp1[j] 更新为更小，但因为 i 要计算，故放到最后计算
	}
	for(int i=1;i<=n;++i)
		for(int j:map[i])
			dp3[i]=max(dp3[i],dp2[j]);
	for(int i=1;i<=n;++i)
		for(int j:map[i])
			dp5[i]=max(dp5[i],dp4[j]);
	while(q--)
	{
		int st,k;
		scanf("%d%d",&st,&k);
		if(k==1)
			printf("%d\n",dp6[st]);
		else if(k==2)
			printf("%d\n",dp5[st]);
		else
			printf("%d\n",dp3[st]);
	}
	return 0;
}
```

---

## 作者：ztd___ (赞：1)

希望你可以看到结尾。

注意：**本题解致力于将问题复杂化，所以不采用 DP 解决，而是使用预处理套预处理。**  
真是非常独特的方法呢。  
~~据说评绿的原因是图上 DP，那不用 DP 是不是就降黄了。~~

## 分析
首先，最大值是没有后效性的一种运算，一旦遇到了真正的答案，后面的一切操作都没有用了。

那么容易想到，先手为了想办法扩张答案，必然会到处乱跑来凑答案，因为一旦凑到了一个很大的，那么后手就无能为力了。

所以对于后手而言，肯定要防止先手到处乱跑。一个很无脑的想法就是：把棋子给送回去。看上去非常令人吃惊，但是他是对的。这样的话，先手每想要扩张，后手就会送他回去，取消扩张。等于说是约束了一个扩张的范围。

然后因为这个方法的主动权在后手，所以先手的第一步是必须要走的。然后又因为我们要模拟出这个扩张的过程，所以第二步和第三步（即一次来回）也是需要走的。

所以如果 $k > 3$ 的话，只要走 $3$ 步就能得出答案了。即 $k \gets \min(k, 3)$。

唉听着怎么这么简单啊？

## 实现
出题人和绝大多数其他人的题解是采用 DP 解决的，每次询问直接调用 DP 数组即可。**但是本题解致力于将问题复杂化，所以不采用 DP 解决。**

多次询问，考虑预处理。
既然我们将题意进行转化之后，$k$ 最大只有 $3$，那么我们就分别预处理 $k = 1, 2, 3$ 的答案。  
具体的，定义数组 $ans$，预处理 $ans_{x, k}$ 为『从 $x$ 开始，走 $k$ 步后可以得到的答案』。~~其实就是 DP 数组？~~

### k = 1
只能走一次，那么必然就是相邻点里面的最大值（因为是先手走）。代码极简。

为了方便后面的恶臭分讨，我们定义两个函数 $\operatorname{mx}(x)$ 和 $\operatorname{mn}(x)$，分别表示相邻点中的最大或最小值。

可以预先对每个点的相邻点进行排序，然后函数直接 $O(1)$ 调用即可。这里用的是 `vector` 存图。
```cpp
vector<int> to[N];
inline int mx(int x) { return to[x][to[x].size() - 1]; }
inline int mn(int x) { return to[x][0]; }
```
然后 $k = 1$ 的预处理就是这样。
```cpp
for (int i = 1;i <= n;i++) {
	sort(to[i].begin(), to[i].end());
	ans[i][1] = mx(i);
}
```
这里的复杂度不会很高，因为边数为 $m$，而一个点的相邻点数就是它连接的边数，所以复杂度**大概**是单 $\log$ 级别。轻松解决。

### k = 2
因为本题中的运算是取 $\max$，所以一步能够到的答案，两步肯定也可以够到。人话：我们需要顺便统计所有相邻点，即把 $k = 1$ 的部分也算上。

然后统计专属于第二步的部分。显然，这个专属于第二步的点必然是出发点的相邻点的相邻点（包括自己）。

容易想到的是，不管先手决定走到哪个相邻点，后手为了使答案尽可能小，会尽可能地选择这个相邻点的**最小相邻点**。而先手为了使答案最大，必然会选择**最小相邻点最大**的相邻点。

那么，对每个点 $u$，我们遍历每一个与其相邻的点 $v$，然后 $ans_{u, 2}$ 就是 $\max \lbrace \operatorname{mn}(v) \rbrace$。

做起来极其简单，比起 DP 而言就是极其的绕。代码待会给，因为 $k = 3$ 的时候要用。

### k = 3
同理，此时也要计算 $k = 1$ 时的答案。

然后第三步是先手动手，所以后手在走第二步的时候，就会尽可能地让先手没有办法走到很大的点上。

此时，在后手走第二步之前，棋子的位置应该在原点的相邻点上，设这个相邻点为 $u$。  
则此时后手就可以走到任意一个与 $u$ 有连边的点。设能走到的这个点为 $v$。

显然，如果后手选择了 $v$ 这个点，那么答案会与 $v$ 取一个 $\max$。然后接下来的第三步又是先手走，先手会尽量走大的点，所以必然会走到 $\operatorname{mx}(v)$ 上。所以答案又会对 $\operatorname{mx}(v)$ 取一个 $\max$。综合一下，就是答案会与 $\max(v, \operatorname{mx}(v))$ 之间去最大值。

而后手为了使答案最小，一定会使 $\max(v, \operatorname{mx}(v))$ 尽可能小。

那么就显然了，取一个 $\min \lbrace \max(v, \operatorname{mx}(v)) \rbrace$ 就好了。可以和 $k = 2$ 一起处理。

共同处理的代码。
```cpp
for (int i = 1;i <= n;i++) {
	int siz = to[i].size(), maxx = 0, maxa = 0;
	for (int j = 0;j < siz;j++) {
		int u = to[i][j];
		ans[i][2] = max(ans[i][2], u);
		ans[i][3] = max(ans[i][3], u);
		maxx = max(maxx, mn(u));
		int len = to[u].size(), minx = 1e18;
		for (int t = 0;t < len;t++) {
			int v = to[u][t];
			minx = min(minx, max(v, mx(v)));
		}
		maxa = max(maxa, minx);
	}
	ans[i][2] = max(ans[i][2], maxx);
	ans[i][3] = max(ans[i][3], maxa);
}
```

唉等等，我们是不是做完了啊！！！

唉唉，怎么[万绿丛中一点黑](https://www.luogu.com.cn/record/202449893)啊。

不难发现，这个代码的复杂度不太有保障，他的复杂度大概是等于每个点的相邻点的相邻点的个数和，可以被一朵菊花卡到平方级别。

唉唉唉，那怎么办啊！！！

看这一段。
```cpp
int len = to[u].size(), minx = 1e18;
for (int t = 0;t < len;t++) {
	int v = to[u][t];
	minx = min(minx, max(v, mx(v)));
}
maxa = max(maxa, minx);
```

你会发现这段代码好像和我们枚举的原点 $i$ 并没有关系。

说明这段代码被重复计算了很多次！！！

唉等等，重复计算，是不是可以相当于多次查询啊。多次查询……预处理！

于是我们有了一个**预处理套预处理**的做法。真是问题复杂化的模范呢。

对于每一个点 $i$，预处理上面这段代码运行出来的答案，记为 $pre_i$，使用的时候直接调用即可。注意 $pre_i$ 在一开始的时候要赋一个极大值。

这部分的代码。
```cpp
for (int i = 1;i <= n;i++) {
	int siz = to[i].size();
	for (int j = 0;j < siz;j++) {
		int v = to[i][j];
		pre[i] = min(pre[i], max(v, mx(v)));
	}
}
for (int i = 1;i <= n;i++) {
	int siz = to[i].size(), maxx = 0, maxa = 0;
	for (int j = 0;j < siz;j++) {
		int u = to[i][j];
		ans[i][2] = max(ans[i][2], u);
		ans[i][3] = max(ans[i][3], u);
		maxx = max(maxx, mn(u));
		maxa = max(maxa, pre[u]);
	}
	ans[i][2] = max(ans[i][2], maxx);
	ans[i][3] = max(ans[i][3], maxa);
}
```

## AC Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 55;
int n, m, q, x, k, pre[N], ans[N][5];
vector<int> to[N];
inline int mx(int x) { return to[x][to[x].size() - 1]; }
inline int mn(int x) { return to[x][0]; }
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m >> q;
	for (int i = 1, u, v;i <= m;i++) {
		cin >> u >> v;
		to[u].push_back(v);
		to[v].push_back(u);
	}
	for (int i = 1;i <= n;i++) {
		sort(to[i].begin(), to[i].end());
		ans[i][1] = mx(i), pre[i] = 1e18;
	}
	for (int i = 1;i <= n;i++) {
		int siz = to[i].size();
		for (int j = 0;j < siz;j++) {
			int v = to[i][j];
			pre[i] = min(pre[i], max(v, mx(v)));
		}
	}
	for (int i = 1;i <= n;i++) {
		int siz = to[i].size(), maxx = 0, maxa = 0;
		for (int j = 0;j < siz;j++) {
			int u = to[i][j];
			ans[i][2] = max(ans[i][2], u);
			ans[i][3] = max(ans[i][3], u);
			maxx = max(maxx, mn(u));
			maxa = max(maxa, pre[u]);
		}
		ans[i][2] = max(ans[i][2], maxx);
		ans[i][3] = max(ans[i][3], maxa);
	}
	while (q--) {
		cin >> x >> k;
		k = (k > 3 ? 3 : k);
		cout << ans[x][k] << "\n";
	}
	return 0;
}
```

通过这题，我们相信各位一定将**预处理套预处理**这一将问题复杂化的神奇 trick 了然于心。  
希望大家在算法竞赛里多多运用这种厉害的 trick，打出题人一个出其不意，也可以打朋友一个攻其不备，更可以浪费自己的时光，锻炼自己的脑力，享受不断复杂化问题并不断解决的乐趣。

---

## 作者：lw393 (赞：0)

~~赛时成功地猜对结论，然后光明地写错，成为 0pts 的一员！！~~

发现答案关于 $k$ 单调不降。而又可以走重复的节点，所以可以知道答案一定会在某个 $k$ 处不增。

由于初始点不做计算，所以可以延申出去三个单位长度，因为第四步是后手，可以回到第二步时到达的点。

当然打表也可以明白这一点。于是考虑 dp。

$dp_{i,j,k}$ 表示在节点 $i$，剩下 $j$ 步，由 $k$ 走， $k=1$ 为先手，$k=0$ 为后手。

由题意列出转移方程。

$$dp_{u,j,1} = \max_{u,v有边} \max(v, dp_{v, j-1, 0}), dp_{u,j,0}=\min_{u,v有边} \max(v, dp_{v,j-1,1})$$。

答案即为 $dp_{x,\min(k,3),1}$。

时间复杂度：$O(m+q)$。

---

