# Longest Path

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dp/tasks/dp_g

$ N $ 頂点 $ M $ 辺の有向グラフ $ G $ があります。 頂点には $ 1,\ 2,\ \ldots,\ N $ と番号が振られています。 各 $ i $ ($ 1\ \leq\ i\ \leq\ M $) について、$ i $ 番目の有向辺は頂点 $ x_i $ から $ y_i $ へ張られています。 $ G $ は**有向閉路を含みません**。

$ G $ の有向パスのうち、最長のものの長さを求めてください。 ただし、有向パスの長さとは、有向パスに含まれる辺の本数のことです。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 10^5 $
- $ 1\ \leq\ x_i,\ y_i\ \leq\ N $
- ペア $ (x_i,\ y_i) $ はすべて相異なる。
- $ G $ は**有向閉路を含まない**。

### Sample Explanation 1

次図の赤い有向パスが最長です。 ![](https://img.atcoder.jp/dp/longest_0_muffet.png)

### Sample Explanation 2

次図の赤い有向パスが最長です。 ![](https://img.atcoder.jp/dp/longest_1_muffet.png)

### Sample Explanation 3

例えば、次図の赤い有向パスが最長です。 ![](https://img.atcoder.jp/dp/longest_2_muffet.png)

## 样例 #1

### 输入

```
4 5
1 2
1 3
3 2
2 4
3 4```

### 输出

```
3```

## 样例 #2

### 输入

```
6 3
2 3
4 5
5 6```

### 输出

```
2```

## 样例 #3

### 输入

```
5 8
5 3
2 3
2 4
5 2
5 1
1 4
4 3
1 3```

### 输出

```
3```

# 题解

## 作者：lottle1212 (赞：17)

# [原题传送门](https://www.luogu.com.cn/problem/AT_dp_g)
## Part0：
题目大意：

- 给出一棵 $N$ 个顶点 $M$ 条边的**有向无环图**。
- 求该图最长路长度，即最长路径的**边数**。
- $2 \leq N \leq 10^{5}$，$1 \leq M \leq 10^{5}$。

样例输入：
```
4 5
1 2
1 3
3 2
2 4
3 4
```
样例输出：
```
3
```
![](https://stream.lexar.com/downloadService/download/graph1.png?dKey=9d9439fc3e0ac400a5e5068fcd542682&type=2)

如图，最长路径为 $\{1,3,2,4\}$，该路径边的数量为 $3$。
## Part1：
首先，由于 $N \leq 10^{5}$ ，我们可以知道该题时间复杂度为 $O(n)$。也就是说，将每一个点都遍历一遍。

由于该题为**有向无环图**，因此我们可以按序去搜索遍历每一个点。若该点未被访问过，则对其进行搜索；否则，就可以直接对该点保存的答案进行求最大。

**AC Code：**
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans,dp[100010],n,m,x,y,i,cnt,head[100010];
struct Edge{int next,to;}e[100010];//邻接表
void add(int x,int y){e[++cnt]={head[x],y};head[x]=cnt;}//邻接表建边
void dfs(int u){
	if(dp[u]) return ;//已经访问过，无需再次搜索
	int i,v;dp[u]=-1;
	for(i=head[u];i;i=e[i].next){
		v=e[i].to;
		dfs(v);
		dp[u]=max(dp[u],dp[v]);//在儿子的边数中求最大
	}
	++dp[u];//加上自己与儿子的这条边
	ans=max(ans,dp[u]);
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	while(m--) cin>>x>>y,add(x,y);//建边
	for(i=1;i<=n;i++) dfs(i);//搜索
	cout<<ans;
	return 0;
}
```


---

## 作者：Phartial (赞：7)

由于题目是要让我们求 **有向无环图** 上的最长路，不难想到对图进行分层，这样就只能从前面一层走到后面一层，如果想要让路径最长，显然只能从最顶层一层一层走到最底层，即答案为层数 $-1$。

至于层数的求法可以使用拓扑排序，维护一下当前层数就行。

```cpp
#include <iostream>
#include <vector>

using namespace std;

const int kN = 1e5 + 1;

int n, m, c[kN], d[kN], q[kN], h = 1, t;
vector<int> e[kN];

int main() {
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; ++i) {
    cin >> x >> y;
    e[x].push_back(y), ++c[y];  // 建图，计算入度
  }
  for (int i = 1; i <= n; ++i) {
    if (!c[i]) {             // 若入度为0
      q[++t] = i, d[i] = 1;  // 则加入队列并更新层数
    }
  }
  for (; h <= t; ++h) {                  // 拓扑排序
    for (int i : e[q[h]]) {              // 遍历出边
      if (!--c[i]) {                     // 若更新后的入度为0
        q[++t] = i, d[i] = d[q[h]] + 1;  // 则加入队列并更新层数
      }
    }
  }
  cout << d[q[t]] - 1;  // 结果为层数-1
  return 0;
}
```


---

## 作者：syzxzqy (赞：6)

# [原题传送门](https://www.luogu.com.cn/problem/AT_dp_g)  
此题题目意思就是在一个**有向无环图**中找到最长路径。  
因此我们可以用邻接表存边，枚举每个点，Dfs 搜索最长路径。  
时间复杂度：$O(n^2)$。  
因为每个点开始的最长路径是不变的，所以可以加上记忆化。  
时间复杂度：$O(n)$。  
#### 代码:
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int i,n,m,f[100100],x,y,ans,head[200100],tot;//定义 
struct no{
	int zd,next;
}e[1000100];
void add(int x,int y){
	e[++tot]=(no){y,head[x]};head[x]=tot;//邻接表存边 
}
int dfs(int u){//u 父亲 
	if(f[u]!=0) return f[u];//记忆化 
	for(int v,i=head[u];i;i=e[i].next){//枚举每个儿子
		v=e[i].zd;//v 儿子 
		f[u]=max(f[u],dfs(v)+1);//父亲的最长路径就是儿子的最长路径+1 
	}
	return f[u];
}
signed main(){
	cin>>n>>m;
	for(i=1;i<=m;i++)
		cin>>x>>y,add(x,y);//输入
	for(i=1;i<=n;i++)//枚举每个点 
		ans=max(ans,dfs(i));//求最大
	cout<<ans;
}
```


---

## 作者：DengDuck (赞：5)

本题让我们求最长路的长度。

本题的图是一个有向无环图，动态规划是解决这一类问题的常用方法。

我们设 $f_i$ 表示从点 $i$ 开始走，能走的最远距离。

那么，最长路一定是最大的 $f_i$，为什么？因为最长路也有一个起点啊，从那个起点，尽可能走最远，不就是最长路了吗？

转移方程：

$$
f_i=\max(0,\max_{(i,j)\in E}(f_j+1))
$$

因为这是无环图，不存在从一点走着走着回到自己的情况，所以不可能在求解 $f_i$ 时要求出 $f_i$，这也就满足了动态规划的后无效性。

那正常来说，我们要找出度为零的点，然后倒退求解，整体使用拓扑排序，有些小麻烦。

如果用记忆化搜索，就方便多了，而且每个店，每个边，最多访问一次，所以时间复杂度为 $O(n+m)$。

代码如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,x,y,f[100005],ans;
vector<long long>v[100005];
long long dfs(long long x)
{
	if(f[x]==0)//如果没求过就求出来
	{
		for(auto i:v[x])//新版本的遍历方法，相当于遍历v[x]的所有元素，值存储在i
		{
			f[x]=max(dfs(i)+1,f[x]);
		}
	}
	return f[x];
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y;
		v[x].push_back(y);//加边
	}
	for(int i=1;i<=n;i++)
	{
		ans=max(dfs(i),ans);//求fi中的最大值，没求过的求出来，求过的直接返回值，效率高
	}
	cout<<ans<<endl; 
} 
```

---

## 作者：Obviathy (赞：3)

拓扑排序模板题。

拓扑排序的基本思想就是从入度为 $0$ 的点开始遍历，更新它能到达的点的答案，同时删掉这个点，即它去的这些点入度减一。

显然，最长路一定是从入度为 $0$ 的点开始，出度为 $0$ 的点结束，可自行反证一下。

这个题我们开一个 $dis$ 数组存到入度为 $0$ 的起点的长度。用队列或向量存一下入度为 $0$ 的点，那么刷表去跑就行了。

### AC code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+10;
int n,m;
int du[N],h[N],tot,dis[N],vis[N];
struct edge{
	int u,v,nxt;
}e[N];
queue<int>q;
inline void add(int u,int v){
	e[++tot].u = u;
	e[tot].v = v;
	e[tot].nxt = h[u];
	h[u] = tot;
	du[v] ++; 
}
inline void dfs(int u){
	if(q.empty())return;
	q.pop();
	//cout << u << endl;
	for(int i = h[u];i;i = e[i].nxt){
		int v = e[i].v;
		dis[v] = max(dis[v],dis[u] + 1);
		du[v] --;
		if(du[v] == 0)q.push(v);
	}
	dfs(q.front());
}
int main(){
	cin >> n >> m;
	for(int i = 1;i <= m;i ++){
		int u,v;
		cin >> u >> v;
		add(u,v);
	}
	int ans = 0;
	for(int i = 1;i <= n;i ++)if(du[i] == 0)q.push(i);
	dfs(q.front());
	for(int i = 1;i <= n;i ++)ans = max(ans,dis[i]);
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Haphyxlos (赞：1)

# AT4528 Longest Path
[题目传送门](https://www.luogu.com.cn/problem/AT4528)

这题的转移方程比较显然，即 $dp[i]$ 表示以节点 $i$ 为终点的路径中最长的长度。 

若存在边 $j \to i$，则转移方程为： $f[i]=\max (f[i],f[j]+1) $

有向无环图最重要的性质就是没有环，这使得我们可以对节点进行拓扑排序， 并按照拓扑序的顺序计算dp状态的值。相信你对于宽度优先搜索（BFS）没有什么问题，以下我给出一种用深度优先搜索（DFS）的做法，又称记忆化搜索。

本题参考程序如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
const double eps=1e-8;
const int INF=0x3f3f3f3f;
const int maxn=1e5+5;
const int maxm=1e6+5;
struct node{
	int to,nxt;
}e[maxn];
int n,m,ans,pos,head[maxn],f[maxn];
bool vis[maxn];
inline void add(int u,int v){
	e[++pos]=(node){v,head[u]},head[u]=pos;
}
inline void dfs(int u){
	if(vis[u])return;
	vis[u]=true;
	for(int i=head[u],v;i;i=e[i].nxt){
		v=e[i].to;
		dfs(v);
		f[u]=max(f[u],f[v]+1);
	}
	ans=max(ans,f[u]);
}
int main(int argc,char const *argv[]){
	std::ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1,u,v;i<=m;++i){
		cin>>u>>v;
		add(u,v);
	}
	for(int i=1;i<=n;++i){
		dfs(i);
	}
	cout<<ans;
	return 0;
}
```

本篇题解就到此结束了，如果喜欢，还请点个赞吧。

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_dp_g)        
这里淼一发记忆化搜索题解。       
一眼 dfs。       
我们设一个点为起始点，从它开始进行遍历，我们设 $f(i)$ 为这个点的最长路边数，则有 $f(i)=1+\max{v_i}$，$v_i$ 表示和这个点有边连接的点。      
这么样太慢了，我们可以用 $dp_i$ 表示 $f(i)$ 的值。         
这样，时间变为了 $O(n)$。      
注意图不一定连通，所以结果为 $\max\limits^n_{i=1}f(i)$。      
[CODE](https://www.luogu.com.cn/paste/awjb8ayg)

---

## 作者：CQ_Bab (赞：0)

# 思路
这道题我们发现可以用一个记忆化搜索来解觉，我们只需要将 $x$ 和 $y$ 建边然后去用记忆化搜索搜索出每一个点的深度（即题目中的长度），我们在函数中只需要将 $x$ 的儿子的长度加一并且与本身的值去一个最大值，然后返回。

再在主函数中对每一个点进行搜索，并输出他们中的最大值即可。
# 代码
```cpp
#include <bits/stdc++.h>
#define rep(x,i,j) for(int x=i;x<=j;x++)
#define IOS std::ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define pb push_back
#define int long long
using namespace std;
int n,m,f[100100],x,y,res,head[200100],tot;
struct node{
	int x,y;
}edg[1000100];
void add(int x,int y) { //建边
	edg[++tot].x=y;
	edg[tot].y=head[x];
	head[x]=tot;
}
int dfs(int x) {
	if(f[x]) return f[x];
	for(int i=head[x];i;i=edg[i].y) { //拿出他的儿子
		int u=edg[i].x;
		f[x]=max(f[x],dfs(u)+1); //更新答案
	}
	return f[x];
}
signed main() {
	IOS;
	cin>>n>>m;
	rep(i,1,m) {
		cin>>x>>y;
		add(x,y);
	}
	rep(i,1,n) res=max(res,dfs(i));
	cout<<res<<endl; //输出
	return false;//好习惯
}
/*
4 5
1 2
1 3
3 2
2 4
3 4
*/
```


---

## 作者：Lyu_echo (赞：0)

## 序:
双倍经验题 [P1807 最长路](https://www.luogu.com.cn/problem/P1807)

## 解题思路:

以下提供三种不同解题方法。

### 方法1：BFS

枚举每一个点，用BFS求出其最长路径。取最大值。

预计得分：30pts

实际得分：20pts

考虑优化：边权值均为1，所以尽可能地多走一些边。那么，对于任意的入度非0的起点，必然在这个点之前还有边，不构成最长路。我们需要找到所有入度为0的节点并对它进行BFS求得最长路。

预计得分：70-80pts

实际得分：28pts

### 方法2：最短路算法求最长路

#### Floyd求最长路

状态转移方程 $f_{i,j} = (f_{i,j},f_{i,k}+f_{k,j})_{max}$，时间复杂度 $O(n^3)$。

预计得分：30pts

实际得分：24pts

#### Bellman-Ford/SPAF求最长路

将原算法中松弛操作取小值改为取大值即可。时间复杂度 $O(nm)$。

预计得分：30-40pts

### 方法3：DAG图求关键路径

在拓扑排序的过程中求得关键路径即可。详见代码。

预计得分：100pts

实际得分：100pts

## 代码：

```cpp
//方法1：BFS
//暴力方案
/*
预计得分：30pts
实际得分：20pts
*/
#include<bits/stdc++.h>
using namespace std;
struct Edge{
	int v,nxt;
}edge[100010];
queue<int>q;
int n,m,ans;
int edge_cnt;
int dis[100010];
int head[100010];
void add(int u,int v){
	edge[++edge_cnt].v=v;
	edge[edge_cnt].nxt=head[u];
	head[u]=edge_cnt;
}
void bfs(int x){
	memset(dis,0,sizeof dis);
	q.push(x);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=edge[i].nxt){
			q.push(edge[i].v);
			dis[edge[i].v]=max(dis[edge[i].v],dis[u]+1);
		}
	}
	ans=max(ans,*max_element(dis+1,dis+n+1));
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
	}
	for(int i=1;i<=n;i++) bfs(i);
	cout<<ans;

	return 0;
}
```

```cpp
//方法1：BFS
//优化方案
/*
预计得分：70-80pts
实际得分：28pts
*/
#include<bits/stdc++.h>
using namespace std;
struct Edge{
	int v,nxt;
}edge[100010];
queue<int>q;
int n,m,ans;
int edge_cnt;
int dis[100010],indegree[100010];
int head[100010];
void add(int u,int v){
	edge[++edge_cnt].v=v;
	edge[edge_cnt].nxt=head[u];
	head[u]=edge_cnt;
}
void bfs(int x){
	memset(dis,0,sizeof dis);
	q.push(x);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=edge[i].nxt){
			q.push(edge[i].v);
			dis[edge[i].v]=max(dis[edge[i].v],dis[u]+1);
		}
	}
	ans=max(ans,*max_element(dis+1,dis+n+1));
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		indegree[v]++;
	}
	for(int i=1;i<=n;i++) if(indegree[i]==0) bfs(i);
	cout<<ans;

	return 0;
}
```

```cpp
//方法二：最短路算法求最长路
//Floyd求最长路
#include<bits/stdc++.h>
#define inf 0x7fffffff
using namespace std;
int n,m,ans;
int dis[1000][1000]; //O(n^3)只能过几百的数据，所以数组只开这么点
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) dis[i][j]=(i==j?0:inf);
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		dis[u][v]=-1;
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(dis[i][k]!=inf && dis[k][j]!=inf)
					dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			ans=max(ans,-dis[i][j]);
	cout<<ans;

	return 0;
}

```

```cpp
//Bellman-Ford/SPFA就不写了，实际得分跟BFS/BFS优化因该差不了多少(逃
```

```cpp

//方法三：DAG求关键路径
//拓扑排序+关键路径
/*
预计得分：100pts
实际得分：100pts
*/
#include<bits/stdc++.h>
using namespace std;
struct Edge{
	int v,nxt;
}edge[100010];
queue<int>q;
int n,m;
int edge_cnt;
int indegree[100010],dis[100010];
int head[100010];
void add(int u,int v){
	edge[++edge_cnt].v=v;
	edge[edge_cnt].nxt=head[u];
	head[u]=edge_cnt;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		indegree[v]++;
	}
	for(int i=1;i<=n;i++) if(indegree[i]==0) q.push(i);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=edge[i].nxt){
			int v=edge[i].v;
			indegree[v]--;
			dis[v]=max(dis[v],dis[u]+1);
			if(indegree[v]==0) q.push(v);
		}
	}
	cout<<*(max_element(dis+1,dis+n+1));

	return 0;
}
```

注：以上所有非AC代码测评时均已开启O2

---

## 作者：Daniel_yao (赞：0)

# 题目大意

给定一个 **有向无环图** ，求最长路长度。

## 思路

1. 暴搜：枚举每一个点，通过搜索求出已该点为起点的最长路长度。再把每一个点的最长路长度取个最大值。则可得整个图的最长路长度。

2. 记搜（记忆化搜索）：由题可推出边 $u\to v$ 的最长路的状态转移，即 $f[i]=max(f[i],f[j]+1)$ 通过记搜完成转移。

## AC code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, m, ans, dp[N];
vector <int> e[N];
bool v[N]; 

void dfs(int x){
	if(v[x]) return ;//记搜 
	v[x] = 1;//标记为出现过 
	for(int i = 0;i < e[x].size();i++){
		dfs(e[x][i]);//遍历每一条边 
		dp[x] = max(dp[x], dp[e[x][i]] + 1);//转移 
	}
	ans = max(ans, dp[x]);//取最长路最大值 
}

int main(){
	cin >> n >> m;
	for(int i = 1;i <= m;i++){
		int a, b;
		cin >> a >> b;
		e[a].push_back(b);//连边 
	}
	dp[0] = 0;
	for(int i = 1;i <= n;i++){//枚举每一条边 
		dfs(i);
	}
	cout << ans << '\n';
	return 0;//完结撒花！ 
}
//防伪标记
```

~~[安利](https://yzy001633.blog.luogu.org/)，逃！~~。

---

## 作者：JerryMao (赞：0)

本蒟蒻的第一篇题解。

其实就是先拓扑排序，$dp[i]$ 表示从每个点开始的长度，然后扫一遍统计 $max$ 计入答案就行了。
拓扑排序可以 dfs 看结束时间，也可以手动删除端点。~~就是有点麻烦~~
```cpp
void dfs(int x){
	used[x]=true;
	for(int i=0;i<v[x].size();i++){
		if(!used[v[x][i]]) dfs(v[x][i]);
	}
	topo.push_back(x);
}
 


```


最~~暴力~~简单的就是枚举每个点，然后 bfs 找到最远的，但是会 TLE。

完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(i=0;i<n;i++)
#define Rep(i,x,n) for(i=x;i<=n;i++)
#define all(v) v.begin(),v.end()
#define foreach(c,itr) for(__typeof(c.begin()) itr=c.begin();itr!=c.end();itr++)
#define p_b push_back
#define pii pair<int,int>
#define fr first
#define sc second
#define m_p make_pair
#define zero(a) memset(a,0,sizeof(a))
#define setp setprecision
typedef long long ll;
typedef long double ld;
const ll INF=0x3f3f3f3f;
const ll mod=1000000007;
const ld eps=1e-14;
int i,j;

int n,m;
int dp[100005];
vector<int> v[100005];
vector<int> topo;
bool used[100005]={false};
 
void dfs(int x){
	used[x]=true;
	for(int i=0;i<v[x].size();i++){
		if(!used[v[x][i]]) dfs(v[x][i]);
	}
	topo.push_back(x);
}
 
int main(){
	ios::sync_with_stdio(false);
    cin.tie();
 
    cin>>n>>m;
    while(m--){
    	int a,b;
    	cin>>a>>b;
    	v[a].push_back(b);
    	//v[b].push_back(a);
	}
	for(i=1;i<=n;i++) if(!used[i]) dfs(i);
	reverse(all(topo));
	for(i=0;i<=topo.size();i++){
    	int maxn=0;
    	for(j=0;j<v[topo[i]].size();j++){	
    		dp[v[topo[i]][j]]=max(dp[v[topo[i]][j]],dp[topo[i]]+1);
		}
	}	
	
	int ans=-1;
	for(i=1;i<=n;i++){
		if(dp[i]>ans) ans=dp[i];
	}
	cout<<ans<<endl;
	return 0;
}

```



---

## 作者：Lates (赞：0)

在 DAG 上 dp。

首先做一遍拓扑排序。

设 $f[x]$ 表示到点 $x$ 的最长路，若有一条边 $u\to v$，那么 $f[v]=f[u]+1$。最后在所有 $f[x]$ 里取个最大值即可。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
inline int read(){
	register int x=0,v=1,ch=getchar();
	while(!isdigit(ch)){if(ch=='-')v=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^'0');ch=getchar();}
	return x*v;
}
const int MAX=1e5+5;
queue<int>q;
int n,m;
struct E{int e,next;}e[MAX];int cnt=1,head[MAX];
inline void add(int u,int v){e[cnt]=(E){v,head[u]};head[u]=cnt++;}
int deg[MAX],top[MAX],x;
inline void topsort(){
	for(register int i=1;i<=n;++i)if(!deg[i])q.push(i);
	while(!q.empty()){
		x=q.front();q.pop();
		top[++top[0]]=x;
		for(register int i=head[x];i;i=e[i].next){
			--deg[e[i].e];if(!deg[e[i].e])q.push(e[i].e);
		}
	}
}
int f[MAX],ans;
signed main(){
	n=read(),m=read();
	for(register int i=1,u,v;i<=m;++i)u=read(),v=read(),add(u,v),++deg[v];
	topsort();
	for(register int j=1;j<=n;++j){
		x=top[j];
		for(register int i=head[x];i;i=e[i].next){
			f[e[i].e]=max(f[e[i].e],f[x]+1);
		}
	}
	for(register int i=1;i<=n;++i)ans=max(ans,f[i]);
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：chenxia25 (赞：0)

>### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/AT4528) & [AtCoder题目页面传送门](https://atcoder.jp/contests/dp/tasks/dp_g)

>给定一个无边权DAG$G=(V,E),|V|=n,|E|=m$，求最长链长度。

>$n\in\left[2,10^5\right],m\in\left[1,10^5\right]$。

DAG上DP。

设$dp_i$表示从节点$i$开始的最长链长度。目标是$\max\limits_{i=1}^n\{dp_i\}$，状态转移方程是$dp_i=\max\!\left(0,\max\limits_{(i,j)\in E}\{dp_j+1\}\right)$。

DP顺序自然是拓扑逆序。但是为了更方便，不用写拓扑排序，可以直接记忆化搜索。时间复杂度$\mathrm O(n+m)$。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
const int N=100000;
int n,m;
vector<int> nei[N+1];
int dp[N+1];
bool vis[N+1];//是否访问过 
int ans;
void dfs(int x){//记忆花搜索 
	if(vis[x])return;
	vis[x]=true; 
	for(int i=0;i<nei[x].size();i++)dfs(nei[x][i]),dp[x]=max(dp[x],dp[nei[x][i]]+1);//转移 
	ans=max(ans,dp[x]);//目标 
}
int main(){
	cin>>n>>m;
	while(m--){
		int x,y;
		cin>>x>>y;
		nei[x].pb(y);
	}
	for(int i=1;i<=n;i++)dfs(i);
	cout<<ans;
	return 0;
}
```

---

