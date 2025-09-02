# Doe Graphs

## 题目描述

John Doe decided that some mathematical object must be named after him. So he invented the Doe graphs. The Doe graphs are a family of undirected graphs, each of them is characterized by a single non-negative number — its order.

We'll denote a graph of order $ k $ as $ D(k) $ , and we'll denote the number of vertices in the graph $ D(k) $ as $ |D(k)| $ . Then let's define the Doe graphs as follows:

- $ D(0) $ consists of a single vertex, that has number $ 1 $ .
- $ D(1) $ consists of two vertices with numbers $ 1 $ and $ 2 $ , connected by an edge.
- $ D(n) $ for $ n>=2 $ is obtained from graphs $ D(n-1) $ and $ D(n-2) $ . $ D(n-1) $ and $ D(n-2) $ are joined in one graph, at that numbers of all vertices of graph $ D(n-2) $ increase by $ |D(n-1)| $ (for example, vertex number $ 1 $ of graph $ D(n-2) $ becomes vertex number $ 1+|D(n-1)| $ ). After that two edges are added to the graph: the first one goes between vertices with numbers $ |D(n-1)| $ and $ |D(n-1)|+1 $ , the second one goes between vertices with numbers $ |D(n-1)|+1 $ and $ 1 $ . Note that the definition of graph $ D(n) $ implies, that $ D(n) $ is a connected graph, its vertices are numbered from $ 1 $ to $ |D(n)| $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF232C/ef320fe60e1714744a7b026fb199d2799a6e48f5.png)The picture shows the Doe graphs of order 1, 2, 3 and 4, from left to right.John thinks that Doe graphs are that great because for them exists a polynomial algorithm for the search of Hamiltonian path. However, your task is to answer queries of finding the shortest-length path between the vertices $ a_{i} $ and $ b_{i} $ in the graph $ D(n) $ .

A path between a pair of vertices $ u $ and $ v $ in the graph is a sequence of vertices $ x_{1} $ , $ x_{2} $ , $ ... $ , $ x_{k} $ $ (k&gt;1) $ such, that $ x_{1}=u $ , $ x_{k}=v $ , and for any $ i $ $ (i&lt;k) $ vertices $ x_{i} $ and $ x_{i+1} $ are connected by a graph edge. The length of path $ x_{1} $ , $ x_{2} $ , $ ... $ , $ x_{k} $ is number $ (k-1) $ .

## 样例 #1

### 输入

```
10 5
1 2
1 3
1 4
1 5
2 3
2 4
2 5
3 4
3 5
4 5
```

### 输出

```
1
1
1
2
1
2
3
1
2
1
```

# 题解

## 作者：George1123 (赞：6)

打狗 $\to$ [`George1123`](https://www.cnblogs.com/George1123/p/14231560.html)

---

## 题面

> [CF232C Doe Graphs](https://www.luogu.com.cn/problem/CF232C)

> $0$ 级 `Doe` 图是一个点，$1$ 级 `Doe` 图是两个点加一条边，$k$ 级 `Doe` 图是一个 $k-1$ 级 `Doe` 图加上一个编号全加了 $k-1$ 级 `Doe` 图大小的 $k-2$ 级 `Doe` 图。给一个 $n$ 级 `Doe` 图，$m$ 次询问，每次查询 $a$ 和 $b$ 两点间的最短路。

> 数据范围：$1\le n\le 10^3$，$1\le m\le 10^5$，$1\le a,b\le 10^{16}$。

---

## 题解

肝了一个下午最终贺题了。既然狗做不动题，就多写点题解吧。

注意到 $a,b$ 比 $fib_n$ 小很多，发现 $n$（$fib_{79}$ 就 $>10^{16}$） 可以和 $80$ 取最小值。

考虑一个 $k$ 级图，把 $k-1$ 级部分叫做 $A$，把 $k-2$ 级部分叫做 $B$。

有四个点：$S=1$，$T_A=fib_{k-1}$，$S_B=T_A+1$，$T=fib_{k}$。

有两条边在这里：$(S,S_B)$，$(T_A,S_B)$。

---

容易想到计算出每个点到 $S$ 的距离和到 $T$ 的距离，然后任意两点间的询问，貌似可以通过这两个距离搞出来。

这样便缩小了查询的一维。但是还是不能直接求。

由于 $a,b$ 是固定的，所以它们在每级图中的地位也是固定的，所以可以考虑只算对于一个查询的点 $u$，计算它在每层图中和 $S,T$ 的距离，这东西是可以递推的。

如果设 $f(k,0/1)$ 表示 $k$ 级图下 $u$ 到 $S/T$ 的距离，便可以非常睿智地玩出一个递推方程，但它是错的。

玩的时候，会发现一个 $k$ 级图外的边也是对内部的距离有影响的。

最好的例子就是对于 $S$ 和 $T_A$，它们都连向 $S_B$，而它们的内部距离可能 $>2$。

然后狗就是很 `naive` 以为只要对这种情况特殊处理掉就 `OK` 了，没想到有以下情况：

有以下边：$(S,T)$，$(T_A,S_B)$，$(S,S_B)$，然后查询 $S_B$ 到 $T$ 的距离。

这种时其实是有个性质的：所有的外部边的影响可以改为在 $S,T$ 之间加一条带权边。

可以把 `dp` 转成搜索，$dp(u,k,d)$ 表示 $k$ 级图，$S,T$ 上有一条长度 $k$ 的边，返回值是个 `pair`，即 $u$ 到 $S,T$ 的距离。

然后就很好递推了。

---

再考虑接下来如何求 $a,b$ 之间的距离，不妨设 $a<b$。

发现也不能直接把 $n$ 替换成最小的 $k$ 使得 $b\le fib_k$，原理同上：有外部影响。

> 但是推推可以发现：虽然整个图对答案有影响，但因为如果对于最小 $k$ 满足 $b\le fib_{k-1}$，$a,b$ 必然都在它大的部分子图内，所以这里的 $d$ 肯定是 $2$，所以 $n$ 和 $80$ 取 `min` 依然是可以的 `/cy`。

所以同样可以搜索，设 $solve(u,v,k,d)$ 表示 $k$ 级图，$S,T$ 上有一条长度 $k$ 的边，返回它们间的距离。

---

至于 $d$ 怎么递推，`dp` 怎么递推（包括上面）留给读者自行思考了。

**时间复杂度 $\Theta(80m)$。**

---

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
#define x first
#define y second
#define bg begin()
#define ed end()
#define pb push_back
#define mp make_pair
#define sz(u) int((u).size())
#define R(i,n) for(int i(0);i<(n);++i)
#define L(i,n) for(int i((n)-1);i>=0;--i)
const int iinf=0x3f3f3f3f;
const ll linf=0x3f3f3f3f3f3f3f3f;

//Data
const int N=80;
int n;

//Math
ll fib[N];
void math_init(){
    fib[0]=fib[1]=1;
    for(int i=2;i<N;++i)    
        fib[i]=fib[i-1]+fib[i-2];
}

//Function
#define mi fib[k-1]
pair<int,int> dp(ll u,int k,int d=iinf){
    if(k<=1) return mp(0,0);
    if(u<mi){
        auto p=dp(u,k-1,2);
        return mp(p.x,min(min(p.x,p.y)+1+(k-2)/2,p.x+d));
    } else {
        auto p=dp(u-mi,k-2,d+1);
        return mp(min(p.x+1,p.y+d),p.y);
    }
}
int solve(ll u,ll v,int k,int d=iinf){
    if(u==0&&v==fib[k]-1) return min(d,k/2);
    if(v<mi) return solve(u,v,k-1,2);
    if(u>=mi) return solve(u-mi,v-mi,k-2,d+1);
    auto ud=dp(u,k-1,2),vd=dp(v-mi,k-2,d+1);
    return min(min(ud.x,ud.y)+1+vd.x,ud.x+d+vd.y);
}

//Main
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    math_init();
    int m; cin>>m>>n,n=min(n+1,N-1);
    while(m--){
        ll u,v; cin>>u>>v,--u,--v;
        if(u>v) swap(u,v);
        cout<<solve(u,v,n)<<'\n';
    }
    return 0;
}

```

---

**祝大家学习愉快！**

---

## 作者：姬小路秋子 (赞：2)

我们预处理出 $a,b$ 在每一层中的编号，然后从$n$层开始递归

分三种情况：

$a$ 在 $n-1$ 层，$b$ 在 $n-2$ 层：那么这个时候两点必经过连接n-1层和n-2的边。所以我们递归下去，使得a强制走到n-1的开头，b走到n-2的开头或结尾（因为首尾都有边）。

$.........................................................................................................$

其他两种情况也类似。。这里就不提了

放个代码（不难，看着代码就能轻松想出来了QAQ）：

```c
int work(int a,int b,int n){
	if (n==-1||p[n][a]==p[n][b]) return 0;
	if (g[n][a][b]) return g[n][a][b];
	int ans;
	if (p[n][a]>f[n-1]) ans=work(a,b,n-2);//都在n-2层
	else if (p[n][a]<=f[n-1]&&p[n][b]>f[n-1])//在不同层
		ans=min(work(0,a,n-1),work(a,3,n-1))+1+work(0,b,n-2);
	else ans=min(work(a,b,n-1),min(work(0,a,n-1)+work(b,3,n-1),work(0,b,n-1)+work(a,3,n-1))+2);
	return g[n][a][b]=ans;
}
//0表示走到开头，3表示走到结尾
int main(){
	scanf("%d%d",&T,&nn);
	f[0]=1; f[1]=2;
	for (n=2;;++n){
		f[n]=f[n-1]+f[n-2];
		if (f[n]>1e16) break;
	}
	n=min(n,nn);
	while (T--){
		ll x,y;
		scanf("%lld%lld",&x,&y);
		if (x>y) swap(x,y);
		Rep(j,n,0){
			p[j][0]=1; p[j][3]=f[j];
			p[j][1]=x; p[j][2]=y;
			if (j&&x>f[j-1]) x-=f[j-1];
			if (j&&y>f[j-1]) y-=f[j-1];
			For(k,0,2) For(l,1,3) g[j][k][l]=0;
			g[j][0][3]=(j+1)/2;
		}
		printf("%d\n",work(1,2,n));
	}
}
```

---

## 作者：tzc_wk (赞：1)

摘自我的 [贪心 & 构造 & DP 杂题选做 Ⅱ](https://www.cnblogs.com/ET2006/p/greedy-construction-dp2.html) 第 $35$ 题。

~~代码 10 分钟，debug 两小时~~

~~又是精神崩溃的一天/dk~~

首先这个 Doe 图是递归构造的，因此我们也可以尝试考虑**递归地求解某些量，进而计算出答案**，可以发现，在一个 $n$ 阶 Doe 图中，有两个点是非常特殊的：$1$ 和 $|D_n|$，因为只有经过它们才能进入其他 Doe 图，因此我们考虑设 $F(n,x)$ 表示在一个 $n$ 阶 Doe 图中，$x$ 到 $1$ 的最短距离，再设 $G(n,x)$ 表示在一个 $n$ 阶 Doe 图中，$x$ 到 $|D_n|$ 的最短距离，考虑如何递归地求解 $F,G$：

- 如果 $x\le\text{fib}_{n-1}$，则意味着 $x$ 在左半边的 $D_{n-1}$ 子图中，那么 $x$ 到 $1$ 有两种可能，要么直接在左半边的子图内走到 $1$，要么先走到 $|D_{n-1}|$，再走到 $|D_{n-1}|+1$，最后再走到 $1$，注意，后面那种情况很容易忽略，我因为忽略了后者而疯狂 WA 14。$x$ 到 $|D_{n}|$ 则只能要么先走到 $1$，要么先走到 $|D_{n-1}|$，再走到 $|D_{n-1}|+1$，再在右边的子图内走到 $D_{n}$，而打个表可以发现，在 $D_n$ 中，$1$ 与 $|D_n|$ 的最短距离为 $\lceil\dfrac{n}{2}\rceil$，因此在右边子图中经过的最短距离就是 $\lceil\dfrac{n-2}{2}\rceil$。
- 如果 $x>\text{fib}_{n-1}$，那么 $x$ 到 $1$ 肯定会先在右边子图内走到 $|D_{n-1}|+1$，再一步走到 $1$，而 $x$ 到 $|D_n|$ 则只能在右半部分走，到左半部分肯定是不优的，这个同样可以递归求出。

这样单次求解 $F/G$ 的复杂度就降到了 $\Theta(\log n)$，接下来考虑如何求解答案，我们设 $H(n,a,b,len)$ 表示在 $n$ 阶 Doe 图中，$1$ 与 $D_n$ 之间连了一条长度为 $len$ 的链（注意，这种情况同样也很容易忽略，事实上，如果你点开 test 6 的数据，你发现在 $D_{1000}$ 中，$1$ 和 $13$ 的距离不是 $D_5$ 中 $1$ 和 $13$ 的距离 $3$，而是 $2$，因为可以 $1\to 14\to 13$，这时候 $1$ 和 $13$ 之间就可以视作连上了一条长度为 $2$ 的链），$a$ 与 $b$ 之间的最短距离。还是分三种情况考虑：

- 如果 $a,b$ 都在左子图内，直接递归左子图内，即 $H(n-1,a,b,2)$

- 如果 $a,b$ 都在右子图内，到右子图内递归，$H(n-2,a-\text{fib}_{n-1},b-\text{fib}_{n-1},len+1)$

- 如果 $a,b$ 一个在左子图内，一个在右子图内，那么我们计算答案，分三种情况：

  - $a\to 1\to |D_{n-1}|+1\to b$
  - $a\to |D_{n-1}|\to|D_{n-1}|+1\to b$
  - $a\to 1\to |D_n|\to b$

  分别讨论一下即可。三种情况的答案均可通过调用 $F/G$ 函数算出。

总复杂度 $\Theta(q\log n)$。

```cpp
using namespace fastio;
const int MAXD=82;
const int INF=0x3f3f3f3f;
int n;ll fib[MAXD+5];
pii FG(int id,ll x){
//the minimum distance between x and 1 in graph id
//and the minimum distance between x and fib[id] in graph id
	if(x==fib[id]) return mp(id+1>>1,0);
	if(x==1) return mp(0,id+1>>1);
	if(x<=fib[id-1]){
		pii nt=FG(id-1,x);
		return mp(min(nt.fi,nt.se+2),min(nt.fi,nt.se)+1+FG(id-2,1).se);
	} else {
		pii nt=FG(id-2,x-fib[id-1]);
		return mp(nt.fi+1,nt.se);
	}
}
int query(ll a,ll b,int x,int len){
	if(x==1) return 1;
//	printf("%lld %lld %d %d\n",a,b,x,len);
	if(b<=fib[x-1]) return query(a,b,x-1,2);
	else if(a<=fib[x-1]){
		pii p1=FG(x-2,b-fib[x-1]),p2=FG(x-1,a);
		pii p3=FG(x,a),p4=FG(x,b);
		int res=p1.fi+1+min(p2.fi,p2.se);
		chkmin(res,p3.fi+p4.se+len);
		chkmin(res,p3.se+p4.fi+len);
		return res;
	} else return query(a-fib[x-1],b-fib[x-1],x-2,len+1);
}
int main(){
	fib[0]=1;fib[1]=2;
	for(int i=2;i<=MAXD;i++) fib[i]=fib[i-1]+fib[i-2];
	int qu;scanf("%d%d",&qu,&n);
	while(qu--){
		ll a,b;read(a);read(b);
		if(a>b) swap(a,b);
		if(a==b){print(0,'\n');continue;}
		int x=0;while(b>fib[x]) ++x;
		print(query(a,b,x,(x==n)?INF:2),'\n');
	} print_final();
	return 0;
}
/*
1 1000
89 55
*/
```

---

## 作者：I_am_Accepted (赞：0)

$|D_i|$ 的大小是斐波那契数列，指数增长，所以 $n$ 可以向 $80$ 取 $\min$。

考虑在 $D_i$ 中同构于 $D_{i-1}$ 和 $D_{i-2}$ 子图内部的最短路状态，发现外界对其影响至多为增加了一条编号最小和最大的点之间（以下称为头和尾）的路径。

在 $D_n$ 中不断 zoom in 找到同时包含 $a,b$ 两点的最小 Doe 图，此过程同时维护外界对其影响的路径长度（在 zoom in 时按进入 $D_{i-1}$ 还是 $D_{i-2}$ 分类维护长度）。

设该子图为 $D_{m}$，头尾之间外界路径长度为 $len$（没有则设为 $\infty$），不妨设 $a$ 属于其 $D_{m-1}$ 部分，$b$ 则属于 $D_{m-2}$，分别维护出 $a/b$ 在 $D_{m-1}/D_{m-2}$ 中到头和尾的最短路 $a_0,a_1,b_0,b_1$（此过程可递归求解）。

最后答案即为 $\min(a_0+b_0+1,a_1+b_0+1,a_0+b_1+len,a_1+b_1+2+len)$。

代码很短，但是要考虑的细节不少。

---

