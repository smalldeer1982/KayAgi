# [ARC153F] Tri-Colored Paths

## 题目描述

给定一个包含 $N$ 个顶点和 $M$ 条边的连通且简单的无向图 $G$。顶点编号为 $1$ 到 $N$，第 $i$ 条边连接顶点 $A_i$ 和 $B_i$。

请计算将 $G$ 的每条边染成颜色 $1$、$2$ 或 $3$ 的方案数，要求满足以下条件，并将答案对 $998244353$ 取模：

- 存在一条 $G$ 的简单路径，且该路径上同时包含颜色 $1$、颜色 $2$、颜色 $3$ 的边。

简单路径指的是由顶点序列 $(v_1, \ldots, v_{k+1})$ 和边序列 $(e_1, \ldots, e_k)$ 组成的路径，满足以下条件：
- $i \neq j \implies v_i \neq v_j$。
- 边 $e_i$ 连接顶点 $v_i$ 和 $v_{i+1}$。

## 说明/提示

## 限制条件

- $3 \leq N \leq 2 \times 10^5$
- $3 \leq M \leq 2 \times 10^5$
- $1 \leq A_i, B_i \leq N$
- 给定的图是连通且简单的

## 样例解释 1

$G$ 的所有简单路径都只包含至多 $2$ 条边，因此不存在满足条件的染色方案。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 3
1 2
1 3
3 2```

### 输出

```
0```

## 样例 #2

### 输入

```
4 6
1 2
1 3
1 4
2 3
2 4
3 4```

### 输出

```
534```

## 样例 #3

### 输入

```
6 5
1 3
4 3
5 4
4 2
1 6```

### 输出

```
144```

## 样例 #4

### 输入

```
6 7
1 2
2 3
3 1
4 5
5 6
6 4
1 6```

### 输出

```
1794```

# 题解

## 作者：ღꦿ࿐ (赞：18)

[更好的阅读体验](https://www.cnblogs.com/Dreamerkk/p/17949720) 

很有意义很有思维量的图论题。（摸了好久做出来了，很有感觉）

本文的「环」均指简单环，「路径」均指简单路径。



## 初步

考虑这个「存在一条三种颜色的路径」这个限制其实是很弱的，首先的感觉就是我们随便画出一些连通图，随便选择三条边，基本都能找到一条经过这三条边的路径。

于是我们考虑将难以描述的弱限制单步容斥成相反的强性质：考虑**存在三种颜色**但不存在一条三色路径的染色计数。这显然一个限制更加明确的问题。



## 特殊情况

让我们先来考虑从特例分析：树。

如果存在三种颜色的边且无法在树上被一条简单路径所连接，考虑任意两条颜色不同的边：

![](https://cdn.luogu.com.cn/upload/image_hosting/pk8vd340.png)

其路径上不可能存在第三种颜色的边，且如果某个位置要存在第三种颜色的边，则这条边到到这条路径上的那个点两侧必须全是不同的颜色，否则从第三种颜色的边走到该路径，然后经过其它两种颜色的点。而且第三种颜色的边到该路径上仅能存在该颜色，否则到了直接选择没有的那侧就有三种颜色了。

![](https://cdn.luogu.com.cn/upload/image_hosting/7knwir40.png)

所以我们得到，树的染色方案的形态一定如下图，即存在一个点使得其每个子树内颜色全相同（其实我觉得这个很显然不需要分析啊）。



于是枚举这个点，方案数即将子树染色且每种颜色都出现的方案数 $\sum f(deg_i)$，简单容斥可以得到 $f(x)=3^x-3(2^x)+3$。

![](https://cdn.luogu.com.cn/upload/image_hosting/88v3yk3n.png)



## 泛化

树上的问题向图上的问题拓展的一步就是考虑环，首先我们来考虑一个特定的环的情况，环上可能有一种/两种/三种颜色。

首先如果一个长度大于 $4$ 的环上有三种颜色，那么至少一种颜色出现了两次，考虑指定一条该颜色边不用然后选择其他边即存在了三色路径，所以不存在长度 $\geq 4$ 的有三种颜色的环。

考虑存在一个三色的三元环，如果一个点 $\text{P}$ 上有向外连的边，则这些边只能和点在环上相对的边是同色的，如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/i879jx8z.png)

因为如果连接了颜色和邻边相同的边 $\text{E}$，则可以选择一条路径 $\text{E} \to \text{P 和 E 颜色不同的邻边}\to \text{P 的对边}$ 同时拥有三种颜色，所以一个点上只能连出和对边颜色相同的边。

如果这个三元环上有两个点同时向外连向了外界**不同**的两个点，那么一定也会出现三色路径（显然从这某个点进入然后走环上这条边进入其它点离开就是一条三色路径），下面这种情况是不能出现的。

![](https://cdn.luogu.com.cn/upload/image_hosting/dl87cjof.png)

所以说，三色三元环出现有且仅有以下两种情况：

- 有至多一个点向外连边，且外面的所有边颜色都和三元环上的对边相同。
- 有且仅有两/三个向外的**同一个点**连了边。

第一种情况是好处理的，直接枚举这种 $O(n)$ 条两端点度数均为 $2$ 的点并判断是否为这种三元环，如果是则会增加 $3!=6$ 种颜色方案（确定完环上的边外面的边也确定了），然后直接做就完了。

让我们继续考虑第二种情况，并继续考虑这个环外的 $\text{T}$ 连边情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/8ctznmrq.png)

这个点 $\text{T}$ 已经有了 $\text{P}\to\text{Q}\to \text{T}$，$\text{Q}\to\text{P}\to \text{T}$，$\text{R}\to\text{P}\to \text{T}$，这三条路径，分别限制该点不能再向外连边了。所以这个点不可能再向外连接任何其他边，环上其它点也不可以向任何其它点连边（如果练了就同时向外连向了外界不同的两个点），所以不可以再有其它点了，所以这种情况的出现仅当 $n\leq 4$，当 $n\leq 4$ 时可以选择手动判掉或者枚举颜色。

所以我们处理完了**存在三色环**的情况，所以我们接下来可以把限制加强到「环上不存在三种颜色」的问题并继续考虑下去。



## 加强限制

考虑环上存在两种颜色的情况：

考虑第三种颜色的边连接的点  $\text{P}$，我们只需要找到一条以 $\text{P}$ 为终点且同时拥有两种颜色的路径即可走到 $\text{P}$ 并走到第三种颜色了。

考虑 $\text{P}$ 两侧的边，因为环的大小 $\geq 3$，这时候一定有一种颜色在环上出现了至少两次，考虑选择该颜色的一条与  $\text{P}$ 相邻的边不选，环上剩余的边构成了一条以 $P$ 为端点的有两种颜色的路径，所以一定存在三色路径。

![](https://cdn.luogu.com.cn/upload/image_hosting/i01d4lmb.png)

所以得到环上不能存在两种颜色，于是我们现在就得到了一个很强的限制「一个环上的边必须是同一种颜色」，这也意味着一个点双连通分量内的所有边的颜色都相同。



## 最终问题

问题到现在已经有了「一个点双连通分量内的边颜色全相同」这样的强限制，考虑建出圆方树，接下来问题变成了「将方点染色，不存在一条简单路径使得经过三种颜色的方点」，几乎和树上问题一模一样，我们同样可以和树上问题相同地得出结论：最终染色方案的形态一定存在一个圆点，使得其每个子树内方点颜色全相同，答案即 $\sum f(deg_i)$，其中 $deg_i$ 表示圆点 $i$ 在圆方树上的度数。

问题至此已经解决，每部分的时间复杂度都是 $O(n+m)$。

## 总结

回顾整个过程，我们首先将若限制转化为对称的强限制，很多「大多数情况都存在」类的问题都可以通过容斥或单步容斥变成「不存在」，会方便很多，接下来逐步将一个限制通过分析某种较弱的特殊情况，并单独考虑这种情况，解决这种问题后将「不存在这样的结构」当作限制解决接下来的问题。

---

## 作者：DaiRuiChen007 (赞：4)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc153_f)

**题目大意**

> 给定一张 $n$ 个点 $m$ 条边的无向简单连通图，求有多少种给边染色 $\{1,2,3\}$ 的方法，使得至少存在一条简单路径上有三种颜色。
>
> 数据范围：$n,m\le 2\times 10^5$。

**思路分析**

注意到限制比较松，我们可以考虑染了三种颜色但没有这样路径的方案数。

先考虑树的情况，取某条极长路径 $u\to v$，显然路径上只有两种颜色，不妨假设第三种颜色在树上某个点 $w$ 子树内。

那么 $u\to w$ 整个部分不能包括两种颜色，同理 $w\to v$ 部分也只能有一种颜色。

因此我们还能证明这样的 $w$ 至多一个。

方案数就是 $\sum f(deg_u)$，其中 $f(x)=3^x-2^x+3$。

因此对于一棵树，合法的染色方案一定存在恰好一个节点，使得该节点每个子树内都染相同颜色。

然后考虑一般情况，先缩点，对每个点双联通分量内部讨论：

- 存在一个长度 $\ge 4$ 的环，此时整个点双联通分量只能染同一颜色，否则必然存在一条路径从任意一个点出发经过两种颜色，此时这个点往外连第三种颜色即可（手玩可以得出结论）。
- 否则该点双连通分量中只有三元环，先假设每条边颜色各不相同：
  - 手玩发现如果环上存在两个点 $u,v$ ，以及环外两点 $x,y$ 使得 $x\to u,y\to v$ 存在（$x\ne y$）那么这个环不能染 $> 1$ 种颜色。
  - 否则分类讨论：如果 $u,v,w$ 都只和 $\le 1$ 个环外点相连，那么此时三元环可以染三种颜色，然后环外边染该点在环上对边的颜色，恰有 $6$ 种方案，这种情况只在 $n=4,m\ge 5$ 时出现。
  - 否则这个点双一定恰为三元环，且恰有一个点 $u$ 向外连边（假设 $n>3$），手玩发现三元环必须染三种不同颜色，且环外所有边必须都染 $u$ 对边颜色，也只有 $6$ 种方案。

否则所有点双都同色，类似树的结论，可以在圆方树上恰取出一个圆点使得其每个子树染相同颜色。

答案还是 $\sum f(deg_u)$，但 $u$ 是圆方树上所有圆点。

时间复杂度 $\mathcal O(n+m)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2e5+5,MOD=998244353;
vector <int> G[MAXN],C[MAXN];
int n,m,stk[MAXN],tp,dcnt,sc,dfn[MAXN],low[MAXN],d[MAXN];
ll ksm(ll a,ll b,ll p=MOD) {
	ll ret=1;
	for(;b;a=a*a%p,b>>=1) if(b&1) ret=ret*a%p;
	return ret;
}
void tarjan(int u,int fz) {
	dfn[u]=low[u]=++dcnt,stk[++tp]=u;
	for(int v:G[u]) if(v^fz) {
		if(!dfn[v]) {
			tarjan(v,u),low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u]) {
				int k;
				C[++sc].push_back(u),++d[u];
				do k=stk[tp--],C[sc].push_back(k),++d[k];
				while(k!=v);
			}
		} else low[u]=min(low[u],dfn[v]);
	}
}
signed main() {
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;++i) {
		scanf("%d%d",&u,&v);
		G[u].push_back(v),G[v].push_back(u);
	}
	tarjan(1,0);
	ll ans=0;
	if(n==4&&m>=5&&sc==1) ans+=6;
	for(int i=1;i<=n;++i) if(d[i]>=3) ans+=ksm(3,d[i])-3*ksm(2,d[i])+3;
	for(int i=1;i<=sc;++i) if(C[i].size()==3) {
		if((d[C[i][0]]>1)+(d[C[i][1]]>1)+(d[C[i][2]]>1)<=1) ans+=6;
	}
	printf("%lld\n",((ksm(3,m)-ans-3*ksm(2,m)+3)%MOD+MOD)%MOD);
	return 0;
}
```

---

## 作者：include13_fAKe (赞：2)

学圆方树的作业题。也是蒟蒻的第一个 ARC F 题！

感谢 @[DaiRuiChen007](https://www.luogu.com.cn/user/539618) 的贡献！



---

正难则反，考虑不存在路径但有 $3$ 种颜色的情况。

从树的角度开始思考，**只考虑三种颜色都出现的情况**。

- 结论：必然存在一个点，以其为根的树上它的所有大小小于它自身的子树都**只含一种颜色**。正确性显然。

一般情况考虑**点双**。其实这对于我而言比较突兀，因为是给边涂色。

- 如果整个图只有一个 vDCC，考虑它是否满足 $n=4$、$m\ge 5$，若满足，就有 $6$ 种染色方案，具体如下图：（边上的字母代表颜色的编号，全文余同）

![](https://cdn.luogu.com.cn/upload/image_hosting/yd3gy3yt.png)

其中 $1\leftrightarrow3$、$2\leftrightarrow4$ 的边至少有 $1$ 条，所以是 $m\ge5$。但两条边同时没有的情况是不计算的。

否则点双内只有三元环，令三个点分别为 $x,y,z$。先假设每条边颜色若不相同：

- 存在两个环外节点能够分别走到 $x,y,z$ 的两个不同节点上，则环上颜色全部相同。下面考虑相同节点的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/dja3c9pz.png)

把任何一个 $\texttt{A}$ 改成 $\texttt B$ 都可以通过将未设色的边设为 $\texttt C$ 达成目的。但我们不由得想到以下情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/kf62ei2l.png)

节点 $2$ 和外节点 $2$（外节点指节点编号加了“外”字的节点，全文余同）的边必须染成 $\texttt C$，外节点 $1$ 和节点 $1$ 得便必须染成 $\texttt B$，但是**外节点 $1\leftrightarrow1\leftrightarrow2\leftrightarrow$ 外节点 $2$** 就兼具三种颜色，所以只允许一个节点有往外的出边。此时随机颜色可以有 $3!=6$ 种可能性。

更朴素的情况是：建出圆方树，对原点找树的答案即可。

最后在计算答案时要注意**是否同时出现了三种颜色**。

时间复杂度 $O(n\log n+m)$，也可以通过提前处理 $2$ 和 $3$ 的次幂实现 $O(n+m)$ 的时间复杂度。

代码是在 vDCC 板子的基础上改动得到的。我咋写了 3KB 多？建议直接去看 drc 的实现。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

inline int read(){
	int a=0,b=1;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	b=-1;
		c=getchar();
	}
	while(isdigit(c)){
		a=(a<<1)+(a<<3)+(c-48);
		c=getchar(); 
	} 
	return a*b;
}
inline void write(int x){
	if(x<0)	putchar('-'),x=-x;
	if(x>=10)	write(x/10);
	putchar(x%10+48);
}
inline void write1(int x){
	write(x),putchar(' ');
}
inline void write2(int x){
	write(x),putchar('\n'); 
}
const int N=5*114514;	//开 2 倍以上  
const int mod=998244353;
int n,m;
vector<int> g[N],h[N];//g 是原图 h 是圆方树  
int dfn[N],low[N],idx;
int stk[N],idx2;
int dcc_id;
vector<int> dcc[N];
int root=0;
void dfs(int u){
	dfn[u]=low[u]=++idx;
	stk[++idx2]=u;
	if(u==root&&g[u].size()==0){
		dcc_id++;
		dcc[dcc_id].push_back(u);
//		cout<<dcc_id<<' '<<u<<endl;
//		cout<<endl;
		return;
	}
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
//		if(fa==v)	continue;
		if(!dfn[v]){
			dfs(v);
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u]){
//				cout<<'*'<<v<<endl; 
				//这时 u 是割点 
				int now=stk[idx2];
				dcc_id++;
//				while(now!=v){
//					instk[now]=0;
//					dcc[dcc_id].push_back(now);
//					cout<<dcc_id<<' '<<now<<endl;
//					idx2--;
//					now=stk[idx2];
//				} 
				do{
					dcc[dcc_id].push_back(now);
//					cout<<dcc_id<<' '<<now<<endl;
					idx2--;
					now=stk[idx2];
				}while(stk[idx2+1]!=v);
				dcc[dcc_id].push_back(u);
//				cout<<dcc_id<<' '<<now<<endl<<endl;
			}
		}
		else	low[u]=min(low[u],dfn[v]);
	} 
}
int qpow(int x,int y){
	if(y==0)	return 1;
	if(y==1)	return x;
	int ret=qpow(x,y/2);
	ret=ret*ret%mod;
	if(y&1)	ret=ret*x%mod;
	return ret;
}
int deg[N];
int include13=0;
int include13_fAKe=0;
signed main(){
	n=read(),m=read();
	dcc_id=n;	//dcc 从 n+1 开始标号  
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		if(u!=v)	g[u].push_back(v),g[v].push_back(u);
	} 
//	cout<<endl;
	for(int i=1;i<=n;i++){
		if(!dfn[i])	root=i,dfs(i);
	}
//	for(int i=1;i<=n;i++){
//		cout<<'#'<<i<<' '<<dfn[i]<<' '<<low[i]<<endl;
//	}
//	dfs(1,0);	//这里不需要跑多根 dfs  
//	cout<<dcc_id-n<<endl;
//	write2(dcc_id-n);
//	for(int i=n+1;i<=dcc_id;i++){
////		cout<<dcc[i].size()<<' '
//		write1(dcc[i].size());
//		for(int j=0;j<dcc[i].size();j++){
//			write1(dcc[i][j]);
//		}
//		putchar('\n');
//	}
//	putchar('\n');
	for(int i=n+1;i<=dcc_id;i++){
		for(int j=0;j<dcc[i].size();j++){
			int u=i,v=dcc[i][j];
			h[u].push_back(v),h[v].push_back(u); 
			deg[u]++,deg[v]++;
		}
	}
	int dcc_=dcc_id-n;
	if(n==4&&m>=5&&dcc_==1)	include13+=6;//cout<<"谭总的世界-019"<<endl; 
	for(int i=1;i<=n;i++){
		//这里的计数主要考虑 deg>=3 的情况 
		if(deg[i]>=3)	include13+=(qpow(3,deg[i])-3*qpow(2,deg[i])+3); 
		include13%=mod;
	} 
	for(int i=n+1;i<=dcc_id;i++){
		if(dcc[i].size()==3){
			int x=dcc[i][0],y=dcc[i][1],z=dcc[i][2];
			if((deg[x]>1)+(deg[y]>1)+(deg[z]>1)<=1)	include13+=6;
		}
	} 
	include13%=mod;
	include13_fAKe=((qpow(3,m)-include13-3*qpow(2,m)%mod+3)%mod+mod)%mod;
	write2(include13_fAKe);
	return 0;
} //LYY 0+100+234+168=502 rank 19 
```

---

## 作者：Purslane (赞：1)

# Solution

来一些点双推结论。下面所有的讨论都是简单图。

性质 $1$：对于一个 $\ge 3$ 的点双连通分量，以及其中任意三个点 $x$、$y$ 和 $z$，一定能找到一条依次经过 $x$、$y$ 和 $z$ 的简单路径。

> **点双的等价定义**：对于任何 $x$ 和 $y$，都存在经过 $x$ 和 $y$ 的简单回路（不经过重复点）。（注：边双的等价定义是，存在经过 $x$ 和 $y$ 的不经过重复边的回路。）
>
> 考虑找到一个包含 $x$ 和 $y$ 的回路 $S$。
>
>删掉 $x$ 之后，一定存在一条 $y \to z$ 的路径。取这条路径上最后一个在 $S$ 中的点 $q$，则 $x \to y \to q \to z$ 的简单路径一定存在。

推论 $1$：如果一个点双只含有三元简单环，那么它的大小一定为 $3$。

> 考虑先找到一个三元环 $(x,y,z)$。假设有第四个点，设为 $w$，且和 $x$ 有连边。根据推论，一定存在一个 $x \to w \to y$ 的简单路径，那么存在一个包含 $(x,y,w)$ 的简单环。则 $y$ 和 $w$ 有连边，同理 $z$ 和 $w$ 有连边。那么找到了一个四元简单环 $x \to w \to y \to z \to x$，矛盾。

**上面叙述的两条性质是普适性的，和本题的限制无关。**

性质 $2$：如果点双的边被染成了两种颜色，那么对于其中任何一个点，一定能找到一条由它出发的含有这两种颜色的简单路径。

> 设这个点为 $s$。如果 $s$ 的所有连边同色，那么一定能找到一条 $e=(u,v)$ 是另一种颜色。根据性质 $1$，存在 $u \to s \to v$ 的简单路径。将 $s \to u$ 最靠近 $s$ 的边断掉，连上 $v \to u$，则找到了一条 $s \to v \to u$ 的路径。显然它包含两种颜色。

性质 $3$：如果点双的边被染成了三种颜色。那么其内部不存在含有三种颜色的路径，当且仅当它是一个三元环，或者某种四个点、至少五条边的点双。

> 如果一个长度 $\ge 4$ 的环上有三种颜色，那么必有一种颜色出现了至少 $2$ 次。将其中一次删掉，就得到了一个合法路径。
>
> 否则，任何一个 $\ge 4$ 的环上都只有 $2$ 种颜色。如果点双大小至少为 $4$，那么存在大小至少为 $4$ 的环，设上面有颜色 $1$ 和 $2$。
> 
> 如果有一条颜色为 $3$ 的边，其两个点不全在环上。我们一定能通过简单路径把这条边的一个短点引到环上。而考虑环上相邻两条边，一定有至少一条出现了至少 $2$ 次，将其断掉即可。
>
> 否则，所有颜色为 $3$ 的边两端点一定都在环上。设为 $u$ 和 $v$。考虑 $u$ 和 $v$ 在环上的邻居，发现只有 $0 \to u \to 1 \to \cdots \to 0 \to v \to 1$ 这种情形才会不能找到长度恰为 $3$ 的合法路径。
>
> 如果环大小大于等于 $5$，那么显然存在（哎我实在不想打字了，这个画图难度比其他几篇题解简单多了）。否则，环大小为 $4$。如果这个图上面有任何其他的边（往这个四元环外，因为我们从任何一个点出发都可以任何两种颜色的集合），都能对。唯一不合法的情形如下图所示（后来发现搞错了，如果中间横一个红色边也不合法）：

![](https://img.picui.cn/free/2025/05/23/683029ba069c3.png)

其实你可能会猜，点双内部不能有三色边。其实差不多如此，但是需要修正。

-----

这道题能做了。

首先要解决一个问题，你为什么要点双缩点。哎这个就是说，边双缩了之后还是有边，而且边双和简单路径关系并不大（如果研究简单路径，点双是一个非常有力的武器）。

我们希望处理至少有 $3$ 种颜色且没有合法路径的图。

先用圆方树缩点。特判掉上面那张图的特殊情况。

显然不可能有大小 $\ge 4$ 的点双染了至少 $2$ 种颜色。如果是 $3$ 种显然不行，而如果是 $2$ 种，那么在外面随便找一种第三颜色即可。

考虑三元环：

1. 如果存在染了 $2$ 种颜色的三元环：那么显然整个图只能有 $2$ 种颜色。这并不符合规定。
2. 如果存在染了 $3$ 种颜色的三元环，设三元环为 $u$、$v$、$w$。三元环是点双，所以把三元环边断开之后，会分为三个分别包含 $uvw$ 的集合 $PQR$。$P$ 内部的颜色必须和 $(v,w)$ 相同，证明显然。而如果至少有两个集合有内部连边，显然又不合法了。所以这种情况只会出现在 $(u,v,w)$ 中至少有 $2$ 个割点。

那假装三元环都是同色的，所有点双都是同色的。

考虑随便两个连通块 $u$ 和 $v$ 异色，设颜色分别是 $1$ 和 $2$。稍微讨论一下，发现只能是这种结构：

![](https://img.picui.cn/free/2025/05/23/68302c55513a0.png)

这样中间那个点，考虑它在圆方树上连了 $k$ 个点双。给这 $k$ 个点双分配上 $3$ 种不同的颜色就行。

复杂度 $O(n+m)$。

-----

总结一下，这道题是典型的点双推性质。想做出来这种题，你得会记住双连通分量的一些基础结论（本质上就是两个等价定义，它们非常重要）。然后是对着题目特有的性质做分析。由于题是能做的，所以相信它一定不会太复杂，往往是一个非常优美的结论。

还有一个有趣的事情：如果之后你遇到了点双钦定经过边的结论，可以钦定在点双中删掉一个点。对于**大多数情况**，可以保证双连通性不变（因为你会把割边当做点双，这样会改变双连通性）。然后再套用我们上面两个普适性结论即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=4e5+10,MOD=998244353;
int n,m,p2[MAXN],p3[MAXN];
vector<int> G[MAXN],T[MAXN];

int dt,tot,dfn[MAXN],low[MAXN],vis[MAXN];
stack<int> st;
void tarjan(int u) {
	dfn[u]=low[u]=++dt,vis[u]=1,st.push(u);
	for(auto v:G[u]) {
		if(vis[v]) low[u]=min(low[u],dfn[v]);
		else {
			tarjan(v),low[u]=min(low[u],low[v]);
			if(low[v]==dfn[u]) {
				++tot;
				T[u].push_back(tot),T[tot].push_back(u);
				while(1) {
					int w=st.top();
					st.pop();
					T[tot].push_back(w),T[w].push_back(tot);
					if(w==v) break ;
				}
			}
		}
	}
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,m) {
		int u,v;
		cin>>u>>v,G[u].push_back(v),G[v].push_back(u);	
	}
	p2[0]=p3[0]=1;
	ffor(i,1,m) p2[i]=p2[i-1]*2%MOD,p3[i]=p3[i-1]*3%MOD;
	tot=n,tarjan(1);
	
	int ans=0;
	if(n==4&&m>=5&&tot==n+1) ans+=6;
	ffor(i,n+1,tot) if(T[i].size()==3) {
		int cnt=0;
		for(auto v:T[i]) cnt+=(T[v].size()==1);
		if(cnt>=2) ans+=6;
	}
	ffor(i,1,n) if(T[i].size()>=3) {
		int x=T[i].size();
		ans=(ans+p3[x]-3*p2[x]+3)%MOD;
	}
	cout<<((p3[m]-3*p2[m]+3-ans)%MOD+MOD)%MOD;
	return 0;
}
```

---

## 作者：ningago (赞：1)

在点双上考虑问题。不妨计数 $3^m-$ 不满足条件的方案数。

如果整张图颜色数 $\leq 2$，显然不合法，贡献为 $3\times 2^m -3$。

接下来考虑整张图颜色数 $= 3$ 的情况。

一个**错误的**结论：一个点双内不能同时出现 $3$ 种颜色。

错误的原因是 "simple path" 不能多次经过同一个点，因此环是不影响答案的。仔细分析一下：如果一个环长度 $>3$，那么一定可以断开一条（重复颜色的）边变成一条链，所以只需要考虑三元环的影响。

- 如果某个点双点数 $=3$，即三元环

![](https://cdn.luogu.com.cn/upload/image_hosting/r3bev9b1.png)

1：三个点 $x,y,z$，分别含有（圆方树上）的三个子树（可能为空）。

2：考虑 $x$ 子树区域的边，其只能与对边 $(y,z)$ 同色。

3：如果存在两个子树均非空，那么也会产生矛盾。

4：也就是说，一个由三元环构成的点双，合法当且仅当其是圆方树上的叶子，造成 $3!$ 的贡献。

- 如果某个点双点数 $=4$

分讨一下可能的情况（此时的三元环的邻边需要满足刚才分析的限制）：

![](https://cdn.luogu.com.cn/upload/image_hosting/ofw1c64p.png)

$m=4$：不存在三元环。

$m=5/6$：另外几条边的颜色都随三元环而确定，**并且该点双必须不存在邻边，否则会存在不合法路径**（也就是整张图 $n=4$ 且只有一个点双）。造成 $3!$ 的贡献。

- 如果某点双点数 $\geq 5$（并且存在三元环）

![](https://cdn.luogu.com.cn/upload/image_hosting/l86cvza4.png)

考虑任意两个邻点，根据刚才的分析它们的颜色是固定的，并且根据点双的性质，它们一定会直接或间接地联通。不论它们之间的边含有什么颜色，都会产生矛盾。

---

于是某个点双同时出现 $3$ 种颜色的情况就分析完了。

![](https://cdn.luogu.com.cn/upload/image_hosting/nzz1zqdr.png)

1：此时如果某个点双内只有两种颜色，那么一定存在另一个点双，其含有另外的颜色，并且一定存在这两个点双之间的一条不合法路径。

2：每个点双内部的颜色是相同的。这就简单了，枚举一个分界点，设它在圆方树上包含 $d$ 个子树，则每个子树内部的颜色都应该相同（否则会存在不合法路径）。贡献为 $3^d-3\times 2^d+3$。

---

于是这题就解决了，复杂度 $O(n+m)$。

```cpp
#define N 200010
#define M 400010
int n, m;
int h[N], e[N << 1], ne[N << 1], idx = -1, du[N];
void add_edge(int x, int y) { ne[++idx] = h[x], h[x] = idx, e[idx] = y; }
void add(int x, int y) { add_edge(x, y), add_edge(y, x); }
std::vector <int> vec[N];
int dfn[N], low[N], sc, ecnt[N];
void Add(int y) { vec[sc].push_back(y); du[y]++; }
int sta[M], top; bool vis[N];

void tarjan(int k, int in_edge)
{
	dfn[k] = low[k] = ++dfn[0];
	for(int i = h[k]; ~i; i = ne[i])
	{
		int nx = e[i]; if(i == in_edge) continue;
		if(!dfn[nx])
		{
			sta[++top] = i;
			tarjan(nx, i ^ 1);
			ckmin(low[k], low[nx]);
			if(low[nx] > dfn[k]) { top--; ecnt[++sc] = 1; Add(k); Add(nx); }
			else if(low[nx] == dfn[k])
			{
				++sc;
				for(;;)
				{
					ecnt[sc]++;
					int t = sta[top--];
					if(!vis[e[t]]) vis[e[t]] = 1, Add(e[t]);
					if(t == i) break;
				}
				for(int t : vec[sc]) vis[t] = 0;
			}
		}
		else if(dfn[nx] < dfn[k]) sta[++top] = i, ckmin(low[k], dfn[nx]);
	}
}

void solve()
{
	memset(h, idx = -1, sizeof(h));
	n = read(), m = read();
	for(int i = 1, x, y; i <= m; i++) x = read(), y = read(), add(x, y);
	tarjan(1, -1);
	int ans = 0;
	if(n == 4 && sc == 1 && m >= 5) { ans = 6; }
	plus_(ans, 3ll * ksm(2, m) % mod);
	plus_(ans, mod - 3);
	for(int i = 1; i <= sc; i++)
	{
		if(vec[i].size() == 3) 
		{
			int x = vec[i][0], y = vec[i][1], z = vec[i][2];
			if((du[x] > 1) + (du[y] > 1) + (du[z] > 1) >= 2) continue; 
			plus_(ans, 6ll);
		}
	}
	for(int i = 1; i <= n; i++)
	{
		if(du[i] <= 2) continue;
		plus_(ans, ksm(3, du[i]));
		plus_(ans, mod - 3ll * ksm(2, du[i]) % mod);
		plus_(ans, 3ll);
	}
	ans = sm(ksm(3, m) + mod - ans);
	print(ans, '\n');
}
```

---

## 作者：Francais_Drake (赞：0)

考虑将“用三种颜色染色”的方案数减去“用了三种颜色，然而不存在任何一条有三种颜色的路径”的方案数以得出答案。

1. 考虑某个环有三种颜色的情况：

	1. 环的大小 $\ge 4$。此时一定可以找出一条至少出现了两次的边，剩下的边可以组成一条路径且包含了三种颜色。
	
	1. 该环为三元环（令这三个点为 $u,v,w$）。考虑其向其他点连的边的情况。
	
		1. 如果环上存在两个点 $u,v$ 均向其他点连边。如果 $u$ 和 $v$ 均连向了同一个点 $x$；则由路径 $x-u-w-v$ 和 $x-u-v-w$ 存在可得 $x-u$ 边颜色一定和 $v-w$ 相同，同理 $x-v$ 边的颜色一定和 $u-w$ 相同；此时 $x$ 不能向环外第二个点连边，$n=4$ 可以爆搜解决（同理可以爆搜 $n$ 更小的情况，方便之后的处理）。如果 $u$ 连向了 $x$，$v$ 连向了 $y$；则由于 $x-u-v-y$ 和 $x-u-w-v-y$ 可得 $x-u,v-y$ 选择任意一种颜色都会不合法。
		
		1. 否则环上只有一个点 $u$ 能和环外连边，此时环外面的边只能都和 $v-w$ 边同色。枚举 $v-w$ 边以找出所有这样的环的数量 $c$ 之后，其对方案数的贡献为 $6c$。
		
1. 考虑某个环有两种颜色的情况（此时环上有三种颜色的方案可以直接视为非法）。此时一定存在第三种颜色的边 $u-v$，令 $u$ 可以不通过 $u-v$ 连向环上的某个点 $w$，$w$ 在环上相邻的点为 $x,y$；则 $w-x,w-y$ 中一定有一种颜色在环上出现了两次，去掉一条出现了两次的颜色的边之后一定会形成一条有三种颜色的路径。

综上，每个环只能有一种颜色，从而每个点双内部的边只能有一种颜色。考虑建出圆方树，则所有方点一定需要凑齐三种颜色，则一定存在某个圆点满足每个儿子的子树内的方点只有一种颜色，计算每个圆点的出边数量即可。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=200010;
const int md=998244353;
int n,m,i,j,u,v,w,a,t=1,tim,top;
int h[maxn],f[maxn],d[maxn],T[3];
int dfn[maxn],low[maxn],stk[maxn];
int p2[maxn],p3[maxn]; bool vis[maxn];
struct edge{int to,nxt;}E[maxn<<1];
bool dfs(int p){
	vis[p]=1; int lp,to;
	for(lp=h[p];lp;lp=E[lp].nxt){
		if(vis[to=E[lp].to]) continue;
		w+=(!(T[f[lp>>1]]++));
		if(w==3||dfs(to)) return 1;
		w-=(!(--T[f[lp>>1]]));
	}
	return vis[p]=0;
}
void color(int p){
	if(p>m){
		for(i=1,w=0;i<=n;++i){
			if(dfs(i)){
				memset(T,0,12);
				memset(vis+1,0,n);
				++a; break;
			}
		}
		return;
	}
	f[p]=0; color(p+1);
	f[p]=1; color(p+1);
	f[p]=2; color(p+1);
}
inline void Add(int &x,int y){x-=((x+=y)>=md)*md;}
void tarjan(int p){
	dfn[p]=low[p]=++tim;
	stk[++top]=p; int lp,to;
	for(lp=h[p];lp;lp=E[lp].nxt){
		to=E[lp].to;
		if(!dfn[to]){
			tarjan(to);
			if(low[to]==dfn[p]){
				for(u=0;u!=p;++f[u=stk[top--]]);
				stk[++top]=p;
			}
			else low[p]=min(low[p],low[to]);
		}
		else low[p]=min(low[p],dfn[to]);
	}
}
int main(){
	p2[0]=p3[0]=1;
	for(i=1;i<maxn;++i){
		Add(p2[i]=p2[i-1],p2[i-1]);
		p3[i]=(3LL*p3[i-1])%md;
	}
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;++i){
		scanf("%d%d",&u,&v); 
		++d[u]; ++d[v];
		E[++t]={v,h[u]}; h[u]=t;
		E[++t]={u,h[v]}; h[v]=t;
	}
	if(n<=4){
		color(1);
		printf("%d\n",a);
		return 0;
	}
	a=((p3[m]+3-3LL*p2[m])%md+md)%md;
	for(i=2;i<=t;i+=2){
		u=E[i].to; v=E[i|1].to;
		if(d[u]==2&&d[v]==2){
			if(E[j=h[u]].to==v) j=E[j].nxt; w=E[j].to; 
			if(E[j=h[v]].to==u) j=E[j].nxt; if(w==E[j].to) Add(a,md-6);
		}
	} 
	tarjan(1);
	for(i=1;i<=n;++i)
		Add(a,((3LL*p2[f[i]]-p3[f[i]]-3)%md+md)%md);
	printf("%d\n",a);
	return 0;
}
```

---

