# [COCI 2009 Final Exam#1] PODJELA

## 题目描述

有 $n$ 个农民，他们住在 $n$ 个不同的村子里，这 $n$ 个村子形成一棵树，每个农民初始时有 $x$ 元钱。  
每一次操作，一个农民可以从它自己的钱中，取出任意数量的钱，交给某个相邻村子的农民。   
对于每个农民给定一个值 $v_i$，求最少需要多少次操作，使得每个农民最终拿到的钱 $\geq$ 给定的值。  

## 说明/提示

对于 $100\%$ 的数据，$1 \leq n \leq 2000,~0 \leq x \leq 10000,~\sum\limits_{i=1}^{n}v_i \leq n\times x$

## 样例 #1

### 输入

```
6
15
10 20 18 16 6 16
1 4
4 5
4 6
6 2
5 3
```

### 输出

```
5
```

# 题解

## 作者：Mr_Eight (赞：22)

# 很典型的一道树形DP
首先简化一下题目：每个人有 $x-$ $v_{i}$块钱（可为负）。要求出使所有人的钱数都 $≥0$。
### $DP$状态确立
设 $dp_{i,j}$ 为在节点为 $i$ 的子树内进行 $j$ 次操作，使除 $i$ 号节点外，$i$ 的所有子节点的钱数都 $≥0$ 时（符合要求），$i$ 号节点最多能有的钱数（若为负数，则意为还需要父节点给自己的钱数）。
### $DP$转移式
对于每一个节点，每添加一颗子树时，

$(1)$将子节点的钱向上运：
```cpp
next[pos][j+k+1]=max(next[pos][j+k+1],dp[pos][j]+dp[c[pos][i]][k])
```
其中 $pos$ 是该节点， $c[pos][i]$ 表示正在添加的子树。

$(2)$当 $dp[c[pos][i]][k]$ $≥0$ 时，可以不将子节点的钱向上运：
```cpp
if(dp[c[pos][i]][k]>=0){
	next[pos][k+j]=max(next[pos][k+j],dp[pos][j]);
}
```
### 附上丑陋的代码（仅删去头文件部分）
```cpp
#define F(i,a,b) for(register int i=a,i##end=b;i<=i##end;++i)
using namespace std;
int read() {
	int x=0;
	bool fu=0;
	char ch=0;
	while(ch>'9'||ch<'0') {
		ch=getchar();
		if(ch=='-')fu=1;
	}
	while(ch<='9'&&ch>='0') x=(x*10+ch-48),ch=getchar();
	return fu?-x:x;
}
int n,t1,t2,x,v[2002],f[2002],dp[2002][2002],size[2002],next[2002][2002];
bool vis[2002];
vector<int>g[2002],c[2002];
void make_tree(int pos) {
	vis[pos]=1;
	if(g[pos].size()<=1 && pos!=1) {
		size[pos]=1;
		return;
	}
	size[pos]=1;
	F(i,0,g[pos].size()-1) {
		if(!vis[g[pos][i]]) {
			c[pos].push_back(g[pos][i]);
			f[g[pos][i]]=pos;
			make_tree(g[pos][i]);
			size[pos]+=size[g[pos][i]];
		}
	}
}
void DP(int pos) {
	int ssize=0;
	F(i,0,c[pos].size()-1) {
		DP(c[pos][i]);
	}
	F(i,0,c[pos].size()-1) {
		F(j,0,2001) {
			next[pos][j]=(-INT_MAX)/3;
		}
		F(j,0,ssize) {
			F(k,0,size[c[pos][i]]-1) {
				next[pos][j+k+1]=max(next[pos][j+k+1],dp[pos][j]+dp[c[pos][i]][k]);
				if(dp[c[pos][i]][k]>=0) {
					next[pos][k+j]=max(next[pos][k+j],dp[pos][j]);
				}
			}
		}
		F(j,0,2000) {
			dp[pos][j]=next[pos][j];
		}
		ssize+=size[c[pos][i]];
	}
}
int main() {
	memset(dp,-0x1f,sizeof(dp));
	cin>>n>>x;
	F(i,1,n) {
		v[i]=x-read();
		dp[i][0]=v[i];
	}
	F(i,2,n) {
		t1=read(),t2=read();
		g[t1].push_back(t2);
		g[t2].push_back(t1);
	}
	make_tree(1);//建树
	DP(1);//DP
	F(i,0,2000) {//输出答案
		if(dp[1][i]>=0) {
			cout<<i;
			return 0;
		}
	}
	return 0;
}
```
~~记得双击，么么哒（~~


---

## 作者：翼德天尊 (赞：4)

首先有一个貌似没什么用的结论是，最少需要的操作次数最多为 $n-1$。

道理很显然，对于一条边，显然不会出现 $u$ 给 $v$ 一些钱的同时 $v$ 再给 $u$ 一些钱的情况，这显然是不够优的。

那么现在就相当于是让我们给每条边定向或者删掉，使得钱沿着有向边流动之后每个节点都可以达到目标要求，并且需要满足删掉的边最少。

但是由于这是有向边，且删掉一些边之后就使得原树变成了森林——我们好像把原问题变得更复杂了。

别急，没有。注意到 $u$ 向 $v$ 流动正数的钱数，其实就相当于 $v$ 向 $u$ 流动负数的钱数。所以我们仍然可以指定一个结点为根后，从叶子节点开始向根节点流动金钱，只不过我们有两个决策：流动和不流动。

于是就要采取树形 dp 啦。我们在转移过程中都关注哪些东西呢？当前所在节点当然不必说，操作次数当然也要关注，以及还有流动到当前节点所堆积的钱数。前两者数据范围较小，我们就把它们设进状态里，让钱数作为答案维，而我们又显然是需要在当前节点当前操作次数下让钱数尽可能地大，于是就推出来状态了——设 $dp_{i,j}$ 表示在以 $i$ 为根的子树中，操作次数为 $k$ 时的最大堆积钱数。

转移时就考虑两种决策，当子节点堆积钱数为负时不能不流动。

注意我们的转移是【必须转移】而不是【可转移可不转移】，所以我们不能直接用滚动数组 $dp_{i,j}$ 来进行转移，因为这样会使得负数贡献状态无法向上转移。所以我们在转移过程中还需要设置一个临时数组，转移完成后将临时数组的值赋回 $dp$ 数组即可。

时间复杂度 $O(n^2)$.

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2005;
int n,x,v[N],size[N],dp[N][N],f[N];
struct node{
	int to[N<<1],next[N<<1],tot,head[N];
	void adde(int u,int v){
		to[++tot]=v,next[tot]=head[u],head[u]=tot;
	}
}S;
int read(){
	int w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}
void dfs(int u,int fa){
	dp[u][0]=v[u],size[u]=1;
	for (int i=S.head[u];i;i=S.next[i]){
		int v=S.to[i];
		if (v!=fa){
			dfs(v,u);
			for (int j=size[u]-1;j>=0;j--){
				for (int k=size[v];k>=0;k--){
					f[j+k+1]=max(f[j+k+1],dp[v][k]+dp[u][j]);
					if (dp[v][k]>=0) f[j+k]=max(f[j+k],dp[u][j]);
				}
			}
			size[u]+=size[v];
			for (int j=0;j<=size[u];j++)
				dp[u][j]=f[j],f[j]=-1e9;
		}
	}
}
signed main(){
	n=read(),x=read();
	for (int i=0;i<=n+2;i++)
		for (int j=0;j<=n+2;j++)
			dp[i][j]=-1e9;
	for (int i=0;i<=n+2;i++) f[i]=-1e9;
	for (int i=1;i<=n;i++) v[i]=x-read();
	for (int i=1;i<n;i++){
		int u=read(),v=read();
		S.adde(u,v),S.adde(v,u);
	}
	dfs(1,0);
	for (int i=0;i<=n;i++)
		if (dp[1][i]>=0){
			cout<<i<<'\n';
			return 0;
		}
	return 0;
} 
```

---

## 作者：IkunTeddy (赞：2)

这个题很明显所使用的是树形 DP 。

接下来就是设计状态了。

我们设 $dp_{i,j}$ 是以 $i$ 为根的子树操作 $j$ 次后满足所需能剩下的最多金币。

现在状态设计完毕接下来就开始推导转移方程。

如果 $dp_{i,j}<0$ 就说明当前必须要接受子树剩余的金币，枚举 $j$ 为当前点的操作步数，再枚举 $k$ 为子树的操作步数，那么得到方程：

$dp_{i,j} = \max(dp_{i,j},dp_{v,k}+dp_{i,j-k-1})$

如果 $dp_{i,j}\ge0$ 那么当前点就可以接受子树的金币也可以不接受，那么得到另一个方程方程：

$dp_{i,j}=\max(dp_{i,j},\max(dp_{i,j-k},dp_{v,k}+dp_{i,j-k-1}))$

最后就是数组初始值，每个点如果操作 $0$ 次，那它剩余的金币数量就是金币的初始值 $-$ 当前点所需的值。

再取所有大于等于 $0$ 的 $dp_{1,j}$ 中 $j$ 的最小值整个题就完毕了

# Code
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
const int maxn=2000+10;
int n,x;
vector<int> vt[maxn];
int a[maxn];
int dp[maxn][maxn];
int size[maxn];
int f[maxn];
void dfs(int u,int fa){
	int l=vt[u].size();
	//for(int i=0;i<n;i++) dp[u][i]=x-a[u];
	dp[u][0]=x-a[u];
	size[u]=1;
	for(int i=0;i<l;i++){
		int v=vt[u][i];
		if(v==fa) continue;
		dfs(v,u);
		size[u]+=size[v];
		memset(f,-0x3f,sizeof(f));
		for(int j=size[u]-1;j>=0;j--){
			for(int k=size[v]-1;k>=0;k--){
				if(j-k-1>=0) f[j]=max(f[j],dp[v][k]+dp[u][j-k-1]);
				if(dp[v][k]>=0&&j-k>=0) f[j]=max(f[j],dp[u][j-k]);
			}
		}
		for(int j=size[u];j>=0;j--) dp[u][j]=f[j];
	}
}
int main(){
	
	cin>>n>>x;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<n;i++){
		int a,b;
		cin>>a>>b;
		vt[a].push_back(b);
		vt[b].push_back(a);
	}
	memset(dp,-0x3f,sizeof(dp));
	dfs(1,0);
	int ans=0x3f3f3f3f;
	for(int i=0;i<n;i++){
		if(dp[1][i]>=0){
			cout<<i;
			return 0;
		}
	}

	return 0;
}



```


---

## 作者：Melo_qwq (赞：1)

很抽象也很巧妙的好题啊，记录一下，感觉其他大佬讲的没有太看懂（。

考虑转化问题，我们的原问题等价于每个点的权值是 $x-v_i$，最终的目标是让所有点的权值都非负，同时给一个点一些钱相当于把那个点缺少的钱数扣到这个点上来，请注意，这是解决问题的决定性因素。

发现一件事情，就是一棵合法的 $n$ 个结点的树所需要的最小传递次数最大是 $n-1$，比较容易看出，~~但是很抱歉我也不会证~~。这同样很重要，因为这决定了我们接下来数组能不能开下。

经过上述思考之后，我们设 $dp_{i,j}$ 表示以 $i$ 为根的子树内部经过 $j$ 次转移之后，内部所有的点都合法时点 $i$ 的权值最大是多少。

这是本题最为抽象的点，接下来我尽量尝试讲地详细一点。

考虑合并子树的过程，假如我们让点 $u$ 的 dp 值加上其儿子结点 $v$ 的 dp 值（当然这个时候 $v$ 还没有被算过），其意义是什么呢？

假如点 $v$ 的 dp 值是负的，我们用 $u$ 的 dp 值加上它的 dp 值之后显然 $u$ 的 dp 值会变小，那么我们可以看做是**把 $v$ 点上负的那部分转递到了 $u$ 上**，注意到此时除了他俩之外其他的点全部合法，那么我们把 $v$ 的负数部分加到 $u$ 上之后，这个子树中除了 $u$ 之外的点全部合法，满足 dp 性质。

$dp_v>0$ 的时候同理，贪心地考虑，当前子树外的点如果想获得或者或者给出一些钱，肯定是给根节点 $u$ 代价最小，所以我们应当把它的子树中多的部分尽可能地转移到它上面来，若 $dp_v$ 大于 $0$，进行加法可以看做是给了 $u$ 一些钱，满足最优性。

有了这个思想基础，转移方程便呼之欲出了：

首先暴力枚举 $u$ 和 $v$ 的子树中各自转移几次，假设是 $dp_{u,j}$ 和 $dp_{v,k}$。那么：

  - 如果 $dp_{v,k} < 0$，必须把负的部分给 $u$，强制转移 $g_{j+k+1}=\max(g_{j+k+1},dp_{u,j}+dp_{v,k})$（注意还要加上传递的那一个 $1$）。
  - 否则既可以像上面那样转移，也可以不给 $u$，即 $g_{j+k}=\max(g_{j+k},dp_{u,j})$。

其中 $g$ 是为了防止因为奇怪转移顺序产生问题的副本数组。 

代码：


```cpp
#include <bits/stdc++.h>
#define f(i ,m ,n ,x) for (int i = (m) ;i <= (n) ;i += (x))
using std :: cout ;
using std :: max ;
template < typename T > inline void read ( T &x ) {
	x = 0 ;
	bool flag (0) ;
	register char ch = getchar () ;
	while (! isdigit (ch)) {
		flag = ch == '-' ;
		ch = getchar () ;
	}
	while (isdigit (ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48) ;
		ch = getchar () ;
	}
	flag ? x = - x : 0 ;
}
template < typename T ,typename ...Args >
inline void read ( T &x ,Args &...tmp ) {
	read (x) ,read (tmp...) ;
}
const int N = 2e3 + 7 ,inf = - 0x3f3f3f3f ;
int n ,x ,head[N << 1] ,tot ,dp[N][N] ,g[N] ,siz[N] ,kk[N] ;
struct edge { 
	int to ,nxt ;
} e[N << 1] ;
namespace melo {
	inline void add (int u ,int v) {
		e[++ tot] = (edge) {v ,head[u]} ;
		head[u] = tot ;
	}
	inline void pre (int cur ,int fa) {
		for (int i = head[cur] ;i ;i = e[i].nxt) {
			int nex = e[i].to ;
			if (! (nex ^ fa)) continue ;
			pre (nex ,cur) ;
			dp[cur][0] += dp[nex][0] ;
 		}
	} // 预处理要是一下都不转移当前点会为它的子树背上多少负债
	inline void dfs (int cur ,int fa) {
		siz[cur] = 1 ;
		f (i ,0 ,N - 1 ,1) g[i] = inf ;
		for (int i = head[cur] ;i ;i = e[i].nxt) {
			int nex = e[i].to ;
			if (! (nex ^ fa)) continue ;
			dfs (nex ,cur) ;
			for (int j = 0 ;j < siz[cur] ;j ++) {
				for (int k = 0 ;k < siz[nex] ;k ++) {
					if (dp[nex][k] >= 0) 
						g[j + k] = max (g[j + k] ,dp[cur][j]) ;
					g[j + k + 1] = max (g[j + k + 1] ,dp[cur][j] + dp[nex][k]) ;
				}
			}
			siz[cur] += siz[nex] ; 
			f (j ,0 ,siz[cur] ,1) {
				dp[cur][j] = g[j] ;
				g[j] = inf ; 
			}
		}
	}
}
using melo :: add ;
using melo :: dfs ;
using melo :: pre ;
int main () {
	read (n ,x) ;
	memset (dp ,- 0x3f ,sizeof dp) ;
	memset (g ,- 0x3f ,sizeof g) ;
	f (i ,1 ,n ,1) {
		int k ;
		read (k) ;
		dp[i][0] = x - k ;
	}
	pre (1 ,0) ;
	f (i ,1 ,n - 1 ,1) {
		int u ,v ;
		read (u ,v) ;
		add (u ,v) ,add (v ,u) ;
	}
	dfs (1 ,0) ;
	//cout << siz[1] << '\n' ;
	f (i ,0 ,siz[1] ,1) {
		if (dp[1][i] >= 0) 
			return cout << i << '\n' ,0 ;
	} // 能够使根节点大于 0 的最小的 i 就是答案
	return 0 ;
} 
```

---

## 作者：ZBH_123 (赞：1)

## 使用的算法：树上 DP
这是一道非常典型的树上 DP。要想写出动态规划的程序，第一步是设计状态。状态设计的好，状态转移方程推导起来就会更加容易。那么，如何设计状态呢？由于每个村民最后要得到的钱并不完全相同，所以我们设 $dp_{i,j}$ 为以 $i$ 为根的子树，每个村民至少得到 $j$ 元钱的最少操作次数时，状态转移方程会比较难推。我比较推荐的一种状态设计是这样的：设 $dp_{i,j}$ 为以 $i$ 为根的子树操作 $j$ 步后，所有村民钱数总比与给定的需求量总和最多多多少。

那么，第一步解决了，接下来就来到了第二步——推导状态转移方程。$dp_{i,j}$ 如何转移呢？我们这样思考一下：对于以 $i$ 的子结点 $k$ 为根的子树，我们可以选择把它的 $dp_{k,l}$ 的最大值传上去（$l$ 为以 $k$ 为根的子树的操作次数），然后在对以 $i$ 为根的子树进行 $j-l-1$ 次操作。为什么不是 $j-l$ 次操作呢？因为把子结点的 $dp_{k,l}$ 传上去后，还需要再进行一次操作。这样，我们就能推出状态转移方程的一部分了：
$$dp_{i,j}=\max(dp_{i,j},dp_{k,l}+dp_{i,j-l-1})$$
这还没完，由于 $dp_{k,l}$ 有可能 $\ge 0$，而当 $dp_{k,l} \ge 0$ 的时候，就意味着 $dp_{k,l}$ 不必传上去。所以，当 $dp_{k,l} \ge 0$ 的时候，我们要在原来的状态转移方程上稍微改动一下：
$$dp_{i,j}=\max(dp_{i,j},\max(dp_{k,l}+dp_{i,j-l-1},dp_{i,j-l}))$$
状态转移方程也解决了，接下来就是解决初始化和动态规划的程序的问题了。首先是初始化，对于每一个 $dp_{i,0}$，我们知道它的初始值必定是原有的钱数减去 $i$ 号结点的钱数需求量，其他的 $dp_{i,j}$ 暂时不知道，所以就初始化成极小值。接着是动态规划程序的实现。由于在树上 DP 的过程中，一个子结点的 $dp_{i,j}$ 改变了，那么这个结点的 $dp_{i,j}$ 也要改变。所以我们不能直接在 $dp$ 数组上进行操作，而是要重新开一个辅助数组，每找完一个子结点就更新一次 $dp$ 数组。

最后，在根结点的 $dp_{i,j}$ 中找到第一个多出来的钱数 $\ge 0$ 的 $j$，输出它就行了。

就这样，一道蓝题就被我们解决啦！

附上代码：
```cpp
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
int n,m,a[2001],dp[2001][2001],f[2001],x,y,ans,Size[2001];//Size[i] 为以 i 为根的子树的结点个数
bool vis[2001];
vector<int>node[2001];
void dfs(int x){
	dp[x][0]=m-a[x],Size[x]=1;
	for(int i=0;i<node[x].size();i++){
		if(!vis[node[x][i]]){
			vis[node[x][i]]=1;
			dfs(node[x][i]);
			vis[node[x][i]]=0;
			Size[x]+=Size[node[x][i]];
			memset(f,-0x3f,sizeof(f));
			for(int j=Size[x]-1;j>=0;j--){//为什么是从 Size[x]-1 开始呢？因为对于以 x 为根的子树，最多操作总结点数量-1次
				for(int k=0;k<=min(j,Size[node[x][i]]-1);k++){
					if(dp[node[x][i]][k]>=0){
						f[j]=max(f[j],dp[x][j-k]);
						if(j-k-1>=0)
							f[j]=max(f[j],dp[x][j-k-1]+dp[node[x][i]][k]);
					}
					else if(j-k-1>=0)
						f[j]=max(f[j],dp[x][j-k-1]+dp[node[x][i]][k]);
				}
			}	
			for(int j=0;j<Size[x];j++)
				dp[x][j]=f[j];
		}	
	
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<n;i++){
		cin>>x>>y;
		node[x].push_back(y);
		node[y].push_back(x);
	}
	memset(dp,-0x3f,sizeof(dp));//答案可能会有负数，所以初始化成极小值
	vis[1]=1;
	dfs(1);
	for(int i=0;i<=Size[1];i++){
		if(dp[1][i]>=0){//找到第一个钱数总和大于等于总需求量的步数
			ans=i;
			break;
		}
	}
	cout<<ans;
	return 0;
}

---

## 作者：Eric998 (赞：0)

简单题。

记 $dp_{i,j}$ 为 $i$ 的子树（除 $i$）外均已经补满，总共进行最多 $j$ 次操作，$i$ 上的最大钱数。

转移显然有如下两类：

- 一个儿子的 $dp$ 值为负。此时**需要**父亲向其运输一部分钱。

- 一个儿子的 $dp$ 值非负。此时父亲**可以**向其索取一部分钱。

树上背包即可。注意对于此题，记 $sn_i$ 为 $i$ 的儿子，集合，由于 $dp_{i,j}$ 在 $j\le |sn_i|$ 时才可能为正，所以复杂度上界为 $\displaystyle\sum_i|sn_i|\sum^j_{j\in sn_i}|sn_j|\le n\sum^j_{j\in sn_i}|sn_j|=O(n^2)$。

code:

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2005;
vector<int> E[N];
int a[N], dp[N][N], sz[N], tmp[N], n, x, ans;

void dfs(int u, int fa) {
	dp[u][0] = x - a[u], sz[u] = 1;
	for (int v : E[u]) {
		if (v == fa)
			continue;
		dfs(v, u), sz[u] += sz[v];
		memset(tmp, 0xc0, sizeof(tmp));
		for (int j = sz[u] - 1; ~j; j--)
			for (int k = sz[v] - 1; ~k; k--) {
				if (dp[v][k] >= 0 && j >= k)
					tmp[j] = max(tmp[j], dp[u][j - k]);
				if (j > k)
					tmp[j] = max(tmp[j], dp[v][k] + dp[u][j - k - 1]);
			}
		for (int j = sz[u]; ~j; j--) {
			dp[u][j] = tmp[j];
			if (u == 1 && dp[1][j] >= 0)
				ans = j;
		}
	}
}

int main() {
	cin >> n >> x;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1, l, r; i < n; i++)
		cin >> l >> r, E[l].push_back(r), E[r].push_back(l);
	memset(dp, 0xc0, sizeof(dp));
	dfs(1, 0);
	cout << ans;
}
```

---

## 作者：NBest (赞：0)

一道不错的树上背包题。

为了方便，我们先让拿到的钱减去给定值。那么此时因为要使所有农民的值 $\ge 0$ 而每个节点只能通过它的祖先和其他的而非其子树节点沟通，所以我们先对于每个子树，让其所有非根值 $\ge 0$ 求最小次数。这样参数还不够，那我们便在对应限制次数的基础上贪心地让根的值最大。设 $dp_{i,u}$ 表示操作 $i$ 次使得 $u$ 的子树全达标，$u$ 的最大值，那么对于此时我们加入的子节点 $v$，假设它的限制此数为 $j$，那么：  
当 $dp_{v,j}<0$ 时，我们一定要花一次使得其大于 $0$，那么有：  
$$g_{i+j+1}=\max\{g_{i+j+1},dp_{v,j}+dp_{u,i}\}$$  
（$g[]$ 是临时数组）
否则，我们可以选择是否与 $v$ 对应子树合并，有：  
$$g_{i+j+1}=\max\{g_{i+j+1},dp_{v,j}+dp_{u,i}\}\\ g_{i+j}=\max\{g_{i+j},dp_{u,i}\}$$  
然后注意一下代码细节即可。（用临时数组是因为我经常搞错转移顺序，而且有些背包题不能直接转移必须要临时数组，所以这里就直接用了）
## $Code$
```cpp
int n,f[N][N],siz[N],g[N];
vector<int>F[N];
void dfs(int x,int fa){
    for(int y:F[x])if(y^fa){
        dfs(y,x);
        for(int i=0;i<=siz[x]+siz[y];i++)g[i]=-1e9;//赋初值
        for(int i=0;i<siz[x];i++)
            for(int j=0;j<siz[y];j++){
                if(f[j][y]>=0)//可以不合并
                    g[i+j]=max(g[i+j],f[i][x]);
                g[i+j+1]=max(g[i+j+1],f[i][x]+f[j][y]);//合并
            }
        for(int i=(siz[x]+=siz[y]);~i;--i)//赋值回去
            f[i][x]=g[i];
    }
}
int main(){
    n=read();
    memset(f,-0x3f,sizeof(f));//赋初值
    for(int i=1,V=read();i<=n;i++)
        f[0][i]=V-read(),siz[i]=1;
    for(int i=1,u,v;i<n;i++)
        F[u=read()].push_back(v=read()),F[v].push_back(u);
    dfs(1,0);
    for(int i=0;i<=n;i++)
        if(f[i][1]>=0)
            return printf("%d",i),0;
}
```

---

