# Quantifier Question

## 题目描述

Logical quantifiers are very useful tools for expressing claims about a set. For this problem, let's focus on the set of real numbers specifically. The set of real numbers includes zero and negatives. There are two kinds of quantifiers: universal ( $ \forall $ ) and existential ( $ \exists $ ). You can read more about them <a>here</a>.

The universal quantifier is used to make a claim that a statement holds for all real numbers. For example:

- $ \forall x,x<100 $ is read as: for all real numbers $ x $ , $ x $ is less than $ 100 $ . This statement is false.
- $ \forall x,x>x-1 $ is read as: for all real numbers $ x $ , $ x $ is greater than $ x-1 $ . This statement is true.

The existential quantifier is used to make a claim that there exists some real number for which the statement holds. For example:

- $ \exists x,x<100 $ is read as: there exists a real number $ x $ such that $ x $ is less than $ 100 $ . This statement is true.
- $ \exists x,x>x-1 $ is read as: there exists a real number $ x $ such that $ x $ is greater than $ x-1 $ . This statement is true.

Moreover, these quantifiers can be nested. For example:

- $ \forall x,\exists y,x<y $ is read as: for all real numbers $ x $ , there exists a real number $ y $ such that $ x $ is less than $ y $ . This statement is true since for every $ x $ , there exists $ y=x+1 $ .
- $ \exists y,\forall x,x<y $ is read as: there exists a real number $ y $ such that for all real numbers $ x $ , $ x $ is less than $ y $ . This statement is false because it claims that there is a maximum real number: a number $ y $ larger than every $ x $ .

 Note that the order of variables and quantifiers is important for the meaning and veracity of a statement.

There are $ n $ variables $ x_1,x_2,\ldots,x_n $ , and you are given some formula of the form $        f(x_1,\dots,x_n):=(x_{j_1}<x_{k_1})\land       (x_{j_2}<x_{k_2})\land \cdots\land (x_{j_m}<x_{k_m}),  $  

where  $ \land $  denotes logical AND. That is,  $ f(x_1,\ldots, x_n) $  is true if every inequality  $ x_{j_i}<x_{k_i} $        holds. Otherwise, if at least one inequality does not hold, then        $ f(x_1,\ldots,x_n) $  is false.

Your task is to assign quantifiers  $ Q_1,\ldots,Q_n $  to either  universal ( $ \forall $ ) or existential ( $ \exists $ ) so that the statement  $  Q_1 x_1, Q_2 x_2, \ldots, Q_n x_n,       f(x_1,\ldots, x_n)  $ 

is true, and <span class="tex-font-style-bf">the number of         universal quantifiers is maximized</span>, or determine that the       statement is false for every possible assignment of quantifiers.

**Note that the order the variables         appear in the statement is fixed.** 

For example, if        $ f(x_1,x_2):=(x_1<x_2) $  then you are not allowed to make        $ x_2 $  appear first and use the statement  $ \forall x_2,\exists x_1, x_1<x_2 $ . If you assign  $ Q_1=\exists $        and  $ Q_2=\forall $ , it will only be interpreted as  $ \exists x_1,\forall x_2,x_1<x_2$.

## 说明/提示

For the first test, the statement $ \forall x_1, \exists x_2,       x_1<x_2 $ is true. Answers of "EA" and "AA" give false statements. The answer "EE" gives a true statement, but the number of universal quantifiers in this string is less than in our answer.

For the second test, we can show that no assignment of quantifiers, for which the statement is true exists.

For the third test, the statement $ \forall x_1, \forall x_2,       \exists x_3, (x_1<x_3)\land (x_2<x_3) $ is true: We can set $ x_3=\max\{x_1,x_2\}+1 $ .

## 样例 #1

### 输入

```
2 1
1 2```

### 输出

```
1
AE```

## 样例 #2

### 输入

```
4 3
1 2
2 3
3 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
3 2
1 3
2 3```

### 输出

```
2
AAE```

# 题解

## 作者：George1123 (赞：12)

[$\Huge\texttt{In Cnblogs}$](https://www.cnblogs.com/Wendigo/p/12845268.html)

---
> [Quantifier Question](https://www.luogu.com.cn/problem/CF1344C)

> 有长度为 $n$ 的序列 $x\{n\}$，有 $m$ 个条件 $(j_i,k_i)$。有 $n$ 个待定的条件符 $Q_i\in\{\forall,\exists\}$，使
> $$Q_1x_1,Q_2x_2,...,Q_nx_n,(x_{j_1}<x_{k_1})∧(x_{j_2}<x_{k_2})∧\cdots∧(x_{j_m}<x_{k_m})$$
> 求 $\forall$ 最多的方案。如果没有满足方案，输出 $-1$。否则输出 $\forall$ 的数量及整个条件符串。

> 数据范围：$2\le n\le 2\cdot 10^5$，$1\le m\le 2\cdot 10^5$，$1\le j_i,k_i\le n,j_i\not=k_i$。

---
**一句话题解：拓扑排序，有环输出 $-1$，否则将每个不被前后节点影响的节点置为 $\forall$。**

---
首先理解一下，不同序号的 $Q_i$ 是**有顺序的**，不是**平等的**。如 **$x_1<x_2$，$x_1<x_3$，令 $Q_1=\exists,Q_2=\forall,Q_3=\forall$ 是不可以的（如选定 $x_1$ 后取 $x_2=x_1-1$ 就爆了）；但是如果 $x_3<x_1,x_3<x_2$，令 $Q_1=\exists,Q_2=\forall,Q_3=\forall$ 是可以的**。

先用**差分约束**的思想，把条件转化为边，即连 $j_i\to k_i$。然后**拓扑排序**。如果拓扑排序序列长度 $<n$，说明**有环**，无解，输出 $-1$。否则存下这个拓扑序列。

设 $u<v$，因为先发挥 $u$ 的条件符再发挥 $v$ 的条件符。所以如果 $u$ 可以走到 $v$ 或者 $v$ 可以走到 $u$，那么 $v$ 点就不能选 $\forall$ 了；反之，如果对于 $v$，不存在 $u<v$ 可以走到它或被它走到，这样的节点条件符选 $\forall$ 是最优且没有后效性的。

然后用类似 $\texttt{dp}$ 的方法，求出每个节点的最小前驱（可以走到它）和最小后继（它可以走到），然后如果**最小前驱和最小后继都不小于该节点编号**，那么该节点的条件符选 $\forall$。

---
**时间复杂度 $\Theta(n+m)$。**

---
**代码：**

```cpp
#include <bits/stdc++.h>
using namespace std;

//Start
typedef long long ll;
typedef double db;
#define mp(a,b) make_pair(a,b)
#define x(a) a.first
#define y(a) a.second
#define b(a) a.begin()
#define e(a) a.end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)
const int inf=0x3f3f3f3f;
const ll INF=0x3f3f3f3f3f3f3f3f;

//Data
const int N=2e5;
int n,m,d[N+7],f[N+7],b[N+7],sm,ans[N+7];
vector<int> e[N+7],g[N+7];

//Bfs
int Bfs(vector<int>&q){ //就是拓扑排序
	//将图的拓扑序存入q，如果形成了环就返回0。
	q.clear();
	for(int i=1;i<=n;i++)if(!d[i]) q.pb(i);
	for(int i=0;i<sz(q);i++)
		for(int to:e[q[i]])if(!--d[to]) q.pb(to);
	return sz(q)==n;
}

//Main
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v),e[u].pb(v),g[v].pb(u);
	for(int i=1;i<=n;i++) d[i]=sz(g[i]); //d为入度
	vector<int> tp;
	if(!Bfs(tp)) return puts("-1"),0;
	iota(f+1,f+n+1,1),iota(b+1,b+n+1,1); //将fi:=i,bi:=i。
	for(int i=0;i<=sz(tp)-1;i++)
		for(int to:g[tp[i]]) f[tp[i]]=min(f[tp[i]],f[to]); //最小前驱
	for(int i=sz(tp)-1;i>=0;i--)
		for(int to:e[tp[i]]) b[tp[i]]=min(b[tp[i]],b[to]); //最小后继
	for(int i=1;i<=n;i++)if(min(f[i],b[i])==i) sm++,ans[i]=1; //讲解中说了
	printf("%d\n",sm);
	for(int i=1;i<=n;i++) putchar("EA"[ans[i]]);puts("");
	return 0;
}
```
---
**祝大家学习愉快！**

---

## 作者：Soulist (赞：6)

本题的难点在于看懂题意。

题意搞懂之后，会自然的想到连边，有环则非法，否则问题即给定一张 $\rm DAG$，然后问题等价于按照顺序从 $1\to n$ 加点，然后每次加点之后如果这个点没有被访问过则标记其，然后将能够访问到它的点以及能被它访问的点删除。

在正向 DAG 和反向 DAG 分别 dp 出这个点能够到达的点中编号最小值即可，若为本身则意味着这个点无法被删除。

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( register int i = (s); i <= (t); ++ i )
#define drep( i, s, t ) for( register int i = (t); i >= (s); -- i )
#define re register
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N = 2e5 + 5 ; 
int n, m, dp[N], dp2[N], deg[N], vis[N] ; 
vector<int> G[N], e[N] ; 
void add( int x, int y ) {
	G[x].push_back(y), e[y].push_back(x) ; 
}
queue<int> q ; 
signed main()
{
	n = gi(), m = gi() ; int x, y ; 
	rep( i, 1, m ) x = gi(), y = gi(), add( y, x ) ; 
	rep( i, 1, n ) {
		for( int j : G[i] ) ++ deg[i] ;
		if( !deg[i] ) q.push(i) ; 
	}
	rep( i, 1, n ) dp[i] = i ;
	while( !q.empty() ) {
		int u = q.front() ; q.pop(), vis[u] = 1 ;  
		for( int j : e[u] ) {
			dp[j] = min( dp[j], dp[u] ), -- deg[j] ;
			if( !deg[j] ) q.push(j) ; 
		}
	}
	int flag = 0 ; 
	rep( i, 1, n ) if( !vis[i] ) flag = 1 ;
	if( flag ) {
		puts("-1") ; exit(0) ; 
	}
	rep( i, 1, n ) {
		for( int j : e[i] ) ++ deg[i] ;
		if( !deg[i] ) q.push(i) ;
	} 
	rep( i, 1, n ) dp2[i] = i ;
	while( !q.empty() ) {
		int u = q.front() ; q.pop() ;
		for( int j : G[u] ) {
			dp2[j] = min( dp2[j], dp2[u] ), -- deg[j] ;
			if( !deg[j] ) q.push(j) ;
		}
	}
	flag = 0 ;
	rep( i, 1, n ) {
		if( min( dp[i], dp2[i] ) == i ) ++ flag ; 
	}
	cout << flag << endl ; 
	rep( i, 1, n ) 
	if( min( dp[i], dp2[i] ) == i ) printf("A") ;
	else printf("E") ; 
	return 0 ;
}
```

---

## 作者：pzc2004 (赞：5)

# 题目分析
建图+拓扑排序+dfs  
先考虑-1的情况，如果存在一个环，那么一定不可以，否则就一定可以，判环可以用拓扑排序。  
可以发现，如果 $X_i>X_j$ 或 $X_i<X_j(i<j)$ 那么 $Q_j$ 一定是E。  
所以我们建两个图，一个图存正边，一个图存反边。然后从1扫到 $n$，对于当前的点 $i$，我们在正反图上都进行一次dfs，把遍历到的点都标记掉。如果点 $i$ 没有被标记，那么 $Q_i$ 就可以是A。  
最后输出即可，复杂度 $O(N)$。
``` cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200005
int n,m,ans,head1[N],head2[N],cnt1,cnt2,rd1[N],q[N],l=1,r,s,mi[N],ma[N];
int c[N],vis1[N],vis2[N];
struct sb//链式前向星存图
{
	int a,b;
}e1[N],e2[N];
inline void add1(int a,int b)
{
	e1[++cnt1].a=head1[a],e1[cnt1].b=b,head1[a]=cnt1;
}
inline void add2(int a,int b)
{
	e2[++cnt2].a=head2[a],e2[cnt2].b=b,head2[a]=cnt2;
}
inline void dfs1(int x)//正图上dfs
{
	vis1[x]=1;
	for(int i=head1[x];i;i=e1[i].a)
	{
		if(vis1[e1[i].b])continue;
		dfs1(e1[i].b);
	}
}
inline void dfs2(int x)//反图上dfs
{
	vis2[x]=1;
	for(int i=head2[x];i;i=e2[i].a)
	{
		if(vis2[e2[i].b])continue;
		dfs2(e2[i].b);
	}
}
signed main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,a,b;i<=m;i++)scanf("%d%d",&a,&b),add1(a,b),add2(b,a),++rd1[b];//建正反图
	for(int i=1;i<=n;i++)//拓扑排序
	{
		ma[i]=i;
		if(rd1[i])continue;
		q[++r]=i;
	}
	while(l<=r)
	{
		++s;
		int x=q[l++];
		for(int i=head1[x];i;i=e1[i].a)
		{
			ma[e1[i].b]=min(ma[e1[i].b],ma[x]);
			--rd1[e1[i].b];
			if(rd1[e1[i].b]==0)q[++r]=e1[i].b;
		}
	}
	if(s!=n){printf("-1");return 0;}//-1的情况
	for(int i=1;i<=n;i++)//从1扫到n
	{
		if(!vis1[i] && !vis2[i])++ans,c[i]=1;//统计答案
		dfs1(i),dfs2(i);//遍历
	}
	printf("%d\n",ans);
	for(int i=1;i<=n;i++)if(c[i])printf("A");else printf("E");
	return 0;
}
```

---

## 作者：yu_666 (赞：4)

### 题目解释
题目要求我们对一组不等式分配逻辑量词（全称量词 $\forall$ 或存在量词 $\exists$），以使整个逻辑公式为真，并且全称量词的数量最大化。我们需要处理的不等式集合可以表示为：
$f(x_1, x_2, \dots , x_n) = (x_{j_1} < x_{k_1}) \land (x_{j_2} < x_{k_2}) \land \cdots \land (x_{j_m} < x_{k_m})$

其中每个 $j_i$ 和 $k_i$ 都是给定的整数，满足 $1 \leq j_i,k_i \leq n $ 且 $j_i \neq k_i$。

我们的任务是找到一个量词分配方案，使得：

$Q_1 x_1,Q_2 x_2, \dots,Q_n x_n,f(x_1,x_2, \dots ,x_n) $
在这个方案中，$Q_i$ 可以是 $\forall$ 或 $\exists$，并且我们要最大化全称量词 $\forall$ 的数量。
如果不存在这样的量词分配方案，使得上述公式为真，则应输出 $-1$。
输出格式要求，如果存在符合条件的量词分配方案，首先输出一个整数，表示最大可能的全称量词 $\forall$ 的数量。然后在下一行输出一个长度为 $n$ 的字符串，其中第 $i$ 个字符是 "$\forall$" 如果 $Q_i$ 应该是全称量词 $\forall$ ，或 "$\exists$" 如果 $Q_i$ 应该是存在量词 $\exists$ 。所有字母都应该是大写的。如果有多种解决方案，可以选择任意一种输出。
### 实现过程
- 把条件转化为边，对于一个限制条件 $\left(j_i ,k_i\right)$，连 $j_i\rightarrow k_i$，建图。     

- 发现有环肯定无解，输出 $−1$ 即可。

- 然后拓扑排序，存下这个拓扑序列。 

- 可以发现对于一个点能取到 $\forall$ 的条件是它是能走到的点和能到它的点中编号最小的。  

- 那么直接求出每个节点的最小前驱和最小后继，如果最小前驱和最小后继的编号都大于该节点编号，那么该节点的条件符选 $\forall$，否则取 $\exists$。

- 可以证明以上这个“东西”是有唯一解的。

- 时间复杂度 $\Theta (n+m)$。

---

## 作者：Piwry (赞：4)

我来发个完整的做题思路吧QWQ

首先看到不等式可以想到它是有**传递性**的，因此就可以用有向边描述这种关系（而非枚举）。

但为什么要用有向边，或者连边的方向如何判断呢？考虑 $a<b>c$，我们能确定 $a, b; a, c$ 的关系 $a<b, c<b$，但我们不能确定 $a, c$ 的关系，因此是不能用无向边的；而由于不等式的对称性，实际上正反连边都是可行的，但因为遍历时需要**按同一个不等号遍历**（避免出现上述情况），所以连边时不论正反，所有边的 "不等式方向" 必须统一（均是按 $a<b$ : $a$ -> $b$ 或 $a>b$ : $a$ -> $b$ 连）。

考虑如何有解，可以发现只要构造全部元素（$\exists$）就可以使一个不等式成立，但唯一例外是类似 $a<b<a$，从它可以得到 $a<a$，这是显然不成立的；对应到有向图中，这段路径实际上就是一个环，**因此只要在找到环时判 `"-1"` 即可**。

接着考虑如何放进更多的 `"A"`。有一个需要说明的事是：（从题意可得）**这几个元素的确定是有顺序的**。

（下面会默认用 $a<b$ : $a$ -> $b$ 的方式连边）

1. 设 $x_k<x_{k'}, k'>k$，由于 $x_k$ 先确定，这时候显然 $x_{k'}$ 只可取 `"E"`。

2. 设 $x_{k'}<x_k, k'>k$，由于 $x_k$ 先确定，这时候 $x_{k'}$ 也只可取 `"E"`。

再结合**不等式的传递性**，显然若一个点在图中的**所有可以到达这个点的点**以及**所有可以到达的点**的编号均大于它，这个点就可以不取 `"E"`，也就是说它可以取 `"A"`。

由于同时需要 "前驱" 和 "后继"（~~不太标准但这样写比较短...~~）满足条件，连边的方向实际上对结果没有影响，因此应该可以发现方案是唯一的。

实现的话遍历判一次环，再遍历拓补排序得到的序列类似dp地求一下（正着遍历一次反着遍历一次） "前驱"、"后继" 的最小编号答案就出来了。

# CODE

```cpp
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#define IT vector<int>::iterator
using std::vector;
using std::queue;
using std::min;

const int MAXN =2e5+50;

int n, m;
int in[MAXN], minpre[MAXN], minpost[MAXN];
vector<int> to[MAXN], from[MAXN];

inline int read(){
	int x =0; char c =getchar();
	while(c < '0' || c > '9') c =getchar();
	while(c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (48^c), c =getchar();
	return x;
}

bool vis[MAXN], isA[MAXN]/*这个数组其实可以不要*/;
vector<int> Sort;

inline void topo(){
	queue<int> q, ss;
	for(int i =1; i <= n; ++i) if(!in[i]) q.push(i);
	while(!q.empty()){
		int nw =q.front();
		q.pop();
		if(vis[nw]) continue;
		vis[nw] =1;
		/*话说 c++11可以写:for(int i:to[nw])遍历 vector元素引用*/
		for(IT it =to[nw].begin(); it != to[nw].end(); ++it)
			if(--in[*it] == 0) q.push(*it);
		Sort.push_back(nw);
	}
	if((int)Sort.size() < n) printf("-1"), exit(0);/*拓补判环*/
}

int main(){
	n =read(), m =read();
	for(int i =0; i < m; ++i){
		int x =read(), y =read();
		to[x].push_back(y);
		from[y].push_back(x);
		++in[y];
	}
	topo();
	for(int i =1; i <= n; ++i) minpre[i] =minpost[i] =i;
	for(IT it =Sort.begin(); it != Sort.end(); ++it) for(IT it2 =from[*it].begin(); it2 != from[*it].end(); ++it2)
		minpre[*it] =min(minpre[*it], minpre[*it2]);
	for(IT it =Sort.end(); it != Sort.begin(); --it){
		IT it3 =it; --it3;/*笨拙的遍历方法*/
		for(IT it2 =to[*it3].begin(); it2 != to[*it3].end(); ++it2)
			minpost[*it3] =min(minpost[*it3], minpost[*it2]);
	}
	int ans =0;
	for(int i =1; i <= n; ++i) if(min(minpre[i], minpost[i]) ==/*>=*/ i) isA[i] =1, ++ans;
	printf("%d\n", ans);
	for(int i =1; i <= n; ++i) if(isA[i]) putchar('A'); else putchar('E');
}
```


---

## 作者：duyi (赞：2)

# 太棒了↓

[超超超超超超超超超爽的阅读体验](https://www.cnblogs.com/dysyn1314/p/13388056.html)

首先，因为小于的关系是**可传递**的，所以对于一组限制$(j_i,k_i)$，我们考虑连一条有向边$j_i\to k_i$。这样能建出一个图。显然。如果图上有环，肯定无解，答案是$-1$。而只要图上没有环，那么一定有解，因为至少全填$\exist$的时候是成立的。所以以下只考虑一个DAG的情况。

接下来，要让$\forall$尽可能多。这就需要你细细地品这个关系了。

你会发现，每个$Q_i$，不是平等的。例如，如果是$x_1<x_2,x_3<x_2$，答案就是$Q_1=\forall,Q_2=\exist,Q_3=\exist$。但如果是$x_1<x_3,x_2<x_3$，答案就可以变成$Q_1=\forall,Q_2=\forall,Q_3=\exist$。（备注：这个例子其实就是样例3）。你可以看出，在两个一模一样的结构里，仅仅是编号不同（$2$和$3$交换了），就可以改变$\forall$的数量，所以从前往后每个编号是有区别的、**不平等**的。

进而发现，对于$i<j$，只要$i$能到达$j$或$j$能到达$i$，那么$Q_j$一定等于$\exist$，不论$Q_i$等于什么。那既然不论我填$\forall$还是$\exist$，影响是一样的，我当然尽可能多填$\forall$。也就是用这样一种贪心的思想：能填$\forall$就绝不填$\exist$。

于是问题转化为，按编号从小到大，依次标记每个节点。对当前节点$i$，如果所有【$i$能到达的】和【能到达$i$的】节点都未被标记，则$Q_i=\forall$，否则$Q_i=\exist$。

当然，你会发现，对所有【$i$能到达的】和【能到达$i$的】节点进行查询，非常困难。转化一下，变成修改操作，也同样困难！如果你这么想这个问题，那你就是用了“数据结构”的思维，总想在**过程进行中**，大力维护一些什么。但其实，还有另一种思维，也就是“DP”的思维。不在过程中维护，而是预处理出来：用递推的方式预处理出来，不断从已知的，推出未知的。

具体来说，可以现在DAG上正着跑一遍拓扑排序，就能递推出【能到达每个点的】最小编号。再在反图上跑一遍拓扑排序，就能递推出【每个点能到达的】最小编号。

时间复杂度$O(n+m)$。

参考代码：

```cpp
//problem:
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

template<typename T>inline void ckmax(T& x,T y){x=(y>x?y:x);}
template<typename T>inline void ckmin(T& x,T y){x=(y<x?y:x);}

const int MAXN=2e5;
int n,m,ind[MAXN+5],ind_rev[MAXN+5];
int dp[MAXN+5],dp_rev[MAXN+5];
vector<int>G[MAXN+5],RG[MAXN+5];

char ans[MAXN+5];
int maxnum;
int main() {
	cin>>n>>m;
	for(int i=1;i<=m;++i){
		int u,v; cin>>u>>v;
		G[u].pb(v); RG[v].pb(u);
		ind[v]++; ind_rev[u]++;
	}
	queue<int>q;
	for(int i=1;i<=n;++i){
		dp[i]=i;
		if(!ind[i]){
			q.push(i);
		}
	}
	while(!q.empty()){
		int u=q.front(); q.pop();
		for(int i=0;i<SZ(G[u]);++i){
			int v=G[u][i];
			ind[v]--;
			ckmin(dp[v],dp[u]);
			if(!ind[v]){
				q.push(v);
			}
		}
	}
	for(int i=1;i<=n;++i)
		if(ind[i]){
			cout<<"-1"<<endl;
			return 0;
		}
	for(int i=1;i<=n;++i){
		dp_rev[i]=i;
		if(!ind_rev[i]){
			q.push(i);
		}
	}
	while(!q.empty()){
		int u=q.front(); q.pop();
		for(int i=0;i<SZ(RG[u]);++i){
			int v=RG[u][i];
			ind_rev[v]--;
			ckmin(dp_rev[v],dp_rev[u]);
			if(!ind_rev[v]){
				q.push(v);
			}
		}
	}
	for(int i=1;i<=n;++i){
		if(dp[i]<i || dp_rev[i]<i){
			ans[i]='E';
		}
		else{
			ans[i]='A';
			maxnum++;
		}
	}
	cout<<maxnum<<endl;
	for(int i=1;i<=n;++i)
		cout<<ans[i];
	cout<<endl;
	return 0;
}
```







---

## 作者：Purslane (赞：1)

# Solution

如果限制中有 $x_a > x_b$，连边 $a \to b$。

显然这种偏序关系必须形成一个 DAG，有环肯定无解。

在一条链上，不能选择两个元素都是 $\forall$，显然后者可以自行调整大小破坏等式条件。

同样，如果有一个元素被确定了 $\forall$，他在 DAG 上有关的点（它能到达或能到达它）编号比他小，我们可以随意调节这个元素破坏等式条件。

因此，我们只能选择 DAG 上所有相关点编号都比他大的点。很显然它们之间构成了一组反链，就是答案。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,m,mn[MAXN],deg[MAXN],vis[MAXN],tval[MAXN];
vector<int> G[MAXN],g[MAXN];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,m) {int u,v;cin>>u>>v,G[u].push_back(v),g[v].push_back(u);}
	ffor(i,1,n) mn[i]=i,tval[i]=i,deg[i]=g[i].size();
	queue<int> q;
	ffor(i,1,n) if(!deg[i]) q.push(i);
	while(!q.empty()) {
		int u=q.front();
		q.pop(),vis[u]=1,mn[u]=min(mn[u],tval[u]);
		for(auto v:G[u]) {
			tval[v]=min(tval[v],tval[u]),deg[v]--;
			if(!deg[v]) q.push(v);
		}
	}
	ffor(i,1,n) if(!vis[i]) return cout<<-1,0;
	ffor(i,1,n) tval[i]=i,deg[i]=G[i].size();
	ffor(i,1,n) if(!deg[i]) q.push(i);
	while(!q.empty()) {
		int u=q.front();
		q.pop(),mn[u]=min(mn[u],tval[u]);
		for(auto v:g[u]) {
			tval[v]=min(tval[v],tval[u]),deg[v]--;
			if(!deg[v]) q.push(v);
		}
	}
//	ffor(i,1,n) cout<<mn[i]<<'\n';
	int cnt=0; string ans;
	ffor(i,1,n) {
//		cout<<mn[i]<<' '<<i<<'\n';
		if(mn[i]==i) cnt++,ans+='A';
		else ans+='E';
	}
	cout<<cnt<<'\n'<<ans;
	return 0;
}
```

---

## 作者：QwQcOrZ (赞：1)

首先无解显然是输入中存在环的情况，这个可以用拓扑排序解决

考虑一对限制 $x_j<x_k$ 且 $j<k$，如何填才能合法

- $\forall x_j,\forall x_k$ 不合法

- $\exists x_j,\forall x_k$ 不合法

- $\forall x_j,\exists x_k$ 合法

- $\exists x_j,\exists x_k$ 合法

由此推导我们可以得到：对于一个 $x_i$，如果存在一个 $j$，$1\leq j<i$，有限制 $x_j<x_i$，那么这个 $x_i$ 前不能就不能填 $\forall$ 因为不存在一个实数 $x$，使得对于任意实数都大于它

如果限制是大于也是同理的

那么可以对于每个点找到确定了与它关系是小于和大于的所有点中编号最小的点，如果这个点编号比当前点小，那么这个点就不能填 $\forall$，否则可以

具体过程可以按照所有 $j,k$ 的限制建两个图，然后问题就转化为了对于每个点求与此点确定大小关系的点中最小编号

这个东西可以用一个类似 $dp$ 的做法解决，设 $Min1_i$ 表示有比 $i$ 小的限制的点中编号最小的点， $Min2_i$ 表示有比 $i$ 大的限制的点中编号最小的点，然后它们显然都可以从与它有连边的点中转移过来。那么将所有点的入边和出边分别存下来，然后按照拓扑序转移即可

时间复杂度 $\mathcal{O(n+m)}$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;

int read()
{
	int s=0;
	char c=getchar(),lc='+';
	while (c<'0'||'9'<c) lc=c,c=getchar();
	while ('0'<=c&&c<='9') s=s*10+c-'0',c=getchar();
	return lc=='-'?-s:s;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x<10) putchar(x+'0');
	else
	{
		write(x/10);
		putchar(x%10+'0');
	}
}
void print(int x,char c='\n')
{
	write(x);
	putchar(c);
}
struct edge
{
	int to,nxt;
}e[N];
int head[N],cnt=0;
void add(int u,int v)
{
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
int siz[N],Min1[N],Min2[N];
bool vis[N];
int q[N],h=1,t=0;
bool check(int n)
{
	for (int i=1;i<=n;i++)
	if (siz[i]==0)
	q[++t]=i;
	while (h<=t)
	{
		int now=q[h];
		for (int i=head[now];i;i=e[i].nxt)
		{
			int to=e[i].to;
			siz[to]--;
			if (!siz[to]) q[++t]=to;
		}
		h++;
	}
	return t!=n;
}
vector<int>in[N],out[N];

signed main()
{
	memset(vis,0,sizeof(vis));
	memset(siz,0,sizeof(siz));
	int n=read(),m=read(),ans=0;
	for (int i=1;i<=m;i++)
	{
		int u=read(),v=read();
		add(u,v);
		siz[v]++;
		vis[max(u,v)]=1;
		in[v].push_back(u);
		out[u].push_back(v);
	}
	if (check(n)) return puts("-1"),0;
	for (int i=1;i<=n;i++) Min1[i]=Min2[i]=i;
	for (int i=1;i<=n;i++)
	{
		int now=q[i];
		for (int j=0;j<in[now].size();j++)
		Min1[now]=min(Min1[now],Min1[in[now][j]]);
	}
	for (int i=n;i>=1;i--)
	{
		int now=q[i];
		for (int j=0;j<out[now].size();j++)
		Min2[now]=min(Min2[now],Min2[out[now][j]]);
	}
	for (int i=1;i<=n;i++) vis[i]=Min1[i]>=i&&Min2[i]>=i;
	for (int i=1;i<=n;i++) ans+=vis[i];
	print(ans);
	for (int i=1;i<=n;i++) putchar(vis[i]?'A':'E');

	return 0;
}
```

---

## 作者：CCCCOrz (赞：1)

# 分析

首先，我们发现这个题提供了很多大小关系，这启发我们以大小关系为边建图（ $ x_1<x_2 $ 时都从 $ x_1 $ 向 $ x_2 $ 连边）。这样我们就会很容易地发现只要图中有环，我们就应该输出 $ -1 $ ，可以用拓补排序判断是否有解。

其次我们要注意到这样一件事：每个位置是不平等的，也就是说 $ ∀x_1,∃x_2 $ 和 $ ∃x_1,∀x_2 $ 是不同的表达（原英文题面中解释了这一点，但翻译中没有解释原因）

举个例子：

对于输入

	7 6
    1 2
    3 4
    5 2
    3 6
    2 7
    7 3
    
可以得到

![](https://cdn.luogu.com.cn/upload/image_hosting/wicqe7fo.png)

此时只有 $ Q_1 $ 可以是 $ ∀ $ ，其它都只能是 $ ∃ $

但如果输入为

	7 6
    1 5
    3 4
    5 7
    3 6
    2 5
    7 3
    
则图变为

![](https://cdn.luogu.com.cn/upload/image_hosting/7u6zsd2t.png)

此时 $ Q_1，Q_2 $ 都可以是 $ ∀ $ ，其它都只能是 $ ∃ $ 。

（这也是hack掉我曾经的一个错误做法的数据）

这时我们可以发现，（有解的情况下）对于任何一个 $ x_i $ ，如果我们想让 $ Q_i $ 取 $ ∀ $ ，则一切可以确定比 $ x_i $ 小的数和确定比 $ x_i $ 大的数编号都必须比 $ i $ **大**且只能取 $ ∃ $ 。

所以对于每一个点，我们可以查找所有**它能到达**的点（即比它大的数）编号的**最小值**和所有**能到达它**的点（即比它小的数）编号的**最小值**，若两者的编号都比此点大，则该点可以取 $ ∀ $ ，否则只能取 $ ∃ $ 。

通过记忆化搜索实现，复杂度 $ \operatorname{O}(n+m) $ 。

代码：

```cpp
#include <iostream>
#include <queue>
using namespace std;
int n,m,in[200001],ans,sum;
bool aa[200001];
struct edge{
	int to,next;
};
inline int mmin(const int &x,const int &y){
	return x<y?x:y;
}
namespace s1{
	edge e[200001];
	int h[200001],ans[200001],tot;
	//ans[i]表示“i号点能到达的点”的最小编号
	inline void add(int u,int v){
		e[++tot]=(edge){v,h[u]};
		h[u]=tot;
	}
	inline void dfs(int k){
		ans[k]=k;
		for(int i=h[k];i;i=e[i].next){
			if(!ans[e[i].to])dfs(e[i].to);
			ans[k]=mmin(ans[k],ans[e[i].to]);
		}
	}
	//查询“该点能到达的点”的最小编号
}
namespace s2{
	edge e[200001];
	int h[200001],ans[200001],tot;
	//ans[i]表示“能到达i号点的点”的最小编号
	inline void add(int u,int v){
		e[++tot]=(edge){v,h[u]};
		h[u]=tot;
	}
	inline void dfs(int k){
		ans[k]=k;
		for(int i=h[k];i;i=e[i].next){
			if(!ans[e[i].to])dfs(e[i].to);
			ans[k]=mmin(ans[k],ans[e[i].to]);
		}
	}
	//查询“能到达该点的点”的最小编号
}
//大家会发现两个namespace是完全相同的，这也是namespace的好处之一
queue<int> q;
int main(){
	cin>>n>>m;
	int x,y;
	do{
		cin>>x>>y;
		s1::add(x,y);//由小到大建边
		s2::add(y,x);//由大到小建边
		++in[y];
	}while(--m);
	//拓补排序判断是否有解
	for(int i=1;i<=n;++i)
		if(!in[i])q.push(i);
	while(!q.empty()){
		using namespace s1;
		int u=q.front();
		++sum;
		q.pop();
		for(int i=h[u];i;i=e[i].next){
			int v=e[i].to;
			if(!(--in[v]))q.push(v);
		}
	}
	if(sum<n){
		cout<<"-1\n";
		return 0;
	}
	//运行到这里就一定有解
	for(int i=1;i<=n;++i){
		if(!(s1::ans[i] || s2::ans[i])){
			s1::dfs(i);//求出“i号点能到达的点”的最小编号
			s2::dfs(i);//求出“能到达i号点的点”的最小编号
		}
		if(s1::ans[i]>=i && s2::ans[i]>=i){
			//可以取∀
			++ans;
			aa[i]=1;
		}
	}
	cout<<ans<<endl;
	for(int i=1;i<=n;++i)
		cout<<(aa[i]?'A':'E');
	cout<<endl;
	return 0;
}
```
谢谢大家

[图片来源：https://csacademy.com/app/graph_editor/](https://csacademy.com/app/graph_editor/)

---

## 作者：AzusidNya (赞：0)

阅读理解题，难点在读懂题。

看见一堆偏序关系，想到把图建出来，如果 $x_i < x_j$ 就连 $i \rightarrow j$。

然后如果有环就无解，这个可以用拓扑排序判定。没有环的时候必然存在解，可以每个点都填 $\exist$。然后就得到了一张 DAG。

手玩一下，考虑一对 $(i, j)$ 满足 $1 \le i < j \le n$。

如果有 $x_i < x_j$，那么满足条件的情况只有 $\forall x_i, \exist x_j, x_i < x_j$ 和 $\exist x_i , \exist x_j, x_i < x_j$。

如果 $x_i > x_j$，那么满足条件的情况也是一样的。

也就是说，一组方案合法的充要条件是对于任意满足 $1 \le i < j \le n$ 的 $(i, j)$，若 $x_i$ 和 $x_j$ 存在大小关系，则 $j$ 一定是 $\exist$。下面称令 $i$ 为 $\forall$ 或者 $\exist$ 为染成 $\forall$ 或染成 $\exist$。

那么有种暴力的做法。从前往后枚举 $i$，如果 $i$ 没被染色，那么就将 $i$ 染成 $\forall$。然后从 $i$ 开始在 DAG 及它的反图上遍历，如果遍历到没染色的点，就将它染成 $\exist$。这个做法是 $O(n ^ 2)$ 的。

考虑优化。对于原图和反图分别而言，如果 $i$ 被染色了，那么它能走到的点也必然被染色了。所以在遍历的时候如果遇到了一个被染过色的点就直接结束遍历即可。每个点只会被染色一次，时间复杂度是 $O(n)$ 的。

```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<queue>
#define int long long
#define eb emplace_back
#define mp make_pair
#define DEBUG
using namespace std;
const int P = 998244353, inf = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;
using piii = pair<int, pii>;
using piiii = pair<pii, pii>;
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned int;
namespace azus{
	int n, m;
	vector<int> edge[200005];
	vector<int> iedge[200005];
	int col[200005];
	int icol[200005];
	int C[200005];
	int topo[200005], ind[200005], tot;
	int dfs(int u){
		if(col[u]) return 0;
		col[u] = 2;
		C[u] = 2;
		for(int v : edge[u])
			dfs(v);
		return 0;
	} int idfs(int u){
		if(icol[u]) return 0;
		icol[u] = 2;
		C[u] = 2;
		for(int v : iedge[u])
			idfs(v);
		return 0;
	}
	int main(){
		cin >> n >> m;
		for(int i = 1, u, v; i <= m; i ++){
			cin >> u >> v;
			edge[u].eb(v), iedge[v].eb(u);
			ind[v] ++;
		}
		queue<int> q;
		for(int i = 1; i <= n; i ++)
			if(!ind[i]) q.emplace(i);
		while(!q.empty()){
			int u = q.front(); q.pop();
			topo[++ tot] = u;
			for(int v : edge[u]){
				-- ind[v]; if(ind[v] == 0) q.emplace(v);
			}
		}
		if(tot != n) return cout << "-1\n", 0;
		int cnt = 0;
		for(int u = 1; u <= n; u ++){
			int x = C[u];
			dfs(u), idfs(u);
			if(x == 0) C[u] = 1, col[u] = 1, icol[u] = 1;
			else C[u] = x; 
			if(C[u] == 1) cnt ++; 
		}
		cout << cnt << "\n";
		for(int i = 1; i <= n; i ++)
			if(C[i] == 1) cout << "A"; else cout << "E";
		cout << "\n";
		return 0;
	}
}
signed main(){
#ifndef DEBUG
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
#endif
	int T = 1;
	while(T --)
		azus::main();
	return 0;
}
```

---

## 作者：lcfollower (赞：0)

这题是我们模拟赛的题目，题意在模拟赛时没有理解，所以没有过，但是理解了还是很好理解的。

题目大意
------------
给定 $m$ 个约束条件 $\left(j_i ,k_i\right)$（$1\le j_i ,k_i\le n$），表示 $x_{j_i} < x_{k_i}$。又给定两种符号「任意」$\forall$ 以及「存在」$\exists$。请你分配 $n$ 种符号 $Q_i \in\{\forall ,\exists\}$，使得添加符号后的 $x_i$（$1\le i\le n$）满足 $m$ 个约束条件 $x_{j_i} < x_{k_i}$ 成立，程序给出的方案需要满足 $\forall$ 符号数量尽量多，若无解输出 $-1$。

题目分析
------------
明显这是一道拓扑排序题。

首先正向建图，即 $j_i\rightarrow k_i$。若出现环，则必然无解。

比如图为 $1\rightarrow 2\rightarrow 3\rightarrow 1$，约束条件为 $a_1 < a_2$，$a_2 < a_3$，$a_3 < a_1$，明显不成立。

我们可以尝试列表，分别列出符号，保证 $j_i <  k_i$。

| $x_{j_i}\text{的符号}$ | $x_{k_i}\text{的符号}$ | $\text{是否合法}$ |
| :----------: | :----------: | :----------: |
| $\forall$ | $\forall$ | $\text{不合法}$ |
| $\forall$ | $\exists$ | $\text{合法}$ |
| $\exists$ | $\forall$ | $\text{不合法}$ |
| $\exists$ | $\exists$ | $\text{合法}$ |

大于也同理。

通过观察得到：这个点如果尽量可以选 $\forall$ 就选 $\forall$，选 $\exists$ 并不能是最优解。

那么对于一个点，如果它的最小前驱和最小后继都大于 $i$，那么这个点可以取 $\forall$，否则选 $\exists$。

求最小前驱可以正向建图，求最小后继就需要反向建图。

设 $dp_i$ 表示 $i$ 的最小前驱（后继），则有 $dp_{v} = \min\left(dp_v ,dp_u\right)$（$v$ 是 $u$ 的一个孩子）。一开始 $dp_i = i$。

看到这个过程我们明显可以拓扑。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long	
#define db double
#define inf 0x3f3f3f3f
#define infi 0x3f3f3f3f3f3f3f3fll
#define _Dark_Star exit(0)
#define up(i,x,y) for(register int i=x;i<=y;++i)
#define dn(i,x,y) for(register int i=x;i>=y;--i)

using namespace std;

inline int read(){int x=0;bool f=0;char ch=getchar();while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48),ch=getchar();return (f?-x:x);}
inline void write(int x){if(x<0)putchar('-'),x=-x;if(x>9)write(x/10);putchar(x%10|48);}
inline void writeln(int x){write(x),putchar('\n');}
inline void writesp(int x){write(x),putchar(' ');}
#define min(a ,b) a < b ? a : b
const int N = 2e5 + 10;
int n , m, in[N] ,in1[N] ,dp[N] ,dp1[N];
vector <int> edge[N] ,edge1[N];
bool vis[N];

inline bool topo1(){//拓扑，这个跑正向图。
  queue <int> q;
  up(i,1,n){if(!in[i])q.push(i);dp[i] = i;}
  while(!q.empty()){
    int u = q.front();
    q.pop();
    for(int i : edge[u]){
      dp[i] = min(dp[i] ,dp[u]);
      if((--in[i]) == 0) q.push(i);
    }
  }
  up(i,1,n) if(in[i]) return 1;//还有节点有入度，就是有环，那么约束条件不存在合法的解。
  return 0;
} inline void topo2(){//这个拓扑跑反图。
  queue <int> q;
  up(i,1,n){if(!in1[i]) q.push(i);dp1[i] = i;}
  while(!q.empty()){
    int u = q.front();
    q.pop();
    for(int i : edge1[u]){
      dp1[i] = min(dp1[i] ,dp1[u]);
      if((--in1[i]) == 0) q.push(i);
    }
  }
} signed main(){
  n = read() , m = read();
  up(i,1,m){int u = read() ,v = read();edge[u].push_back(v);edge1[v].push_back(u) ,in1[u] ++ , in[v] ++;}
  if(topo1()) return puts("-1") & 0;
  topo2();
  int tot = 0;
  up(i,1,n) if(!(dp[i] < i || dp1[i] < i)) ++ tot;//能选 A 就 A。
  writeln(tot);
  up(i,1,n) if(dp[i] < i || dp1[i] < i) putchar('E'); else putchar('A'); 
  return 0;
}
```

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2600}$
---
### 解题思路：

愚蠢的阅读理解题。

---
将一个约束条件描述为一条边，不妨设为若有约束条件 $x_i<x_j$ 时，$i$ 向 $j$ 链接一条有向边。

假设图中存在环，可以发现无论如何设置边的约束条件强弱，都无法使得答案满足条件，因为即使是将所有的约束条件设置为“存在”，都也一定能够推出形如 $x<x$ 的这样不可能存在的约束。

否则图就是一个 $\text{DAG}$，由于不等式存在传递性，所以其实只要一个点 $i$ 的某一级后继是 $j$，就一定有 $x_i<x_j$，对于前驱也是同理。

处理完图之后具体考虑不等式关系之间的相互影响，此处特别注意条件和条件之间的顺序是很重要的。如果有 $x_i<x_j$，其中 $i<j$，则无论 $x_i$ 为任意还是存在，$x_j$ 都只能是“存在”，对于 $x_i>x_j$ 也是同理。

由此得出，只要是有边相连的两个点，编号较大的一个只能取“粗在”，而如果一个点满足的所有不等式关系中都没有比当前点编号小的，则当前点一定能够取“任意”。

结合之前不等式的传递性，发现只需要计算出一个点的所有前驱和后继中的最小编号，与当前点比较即可。

总复杂度 $O(n+m)$。

---
### 代码：

```cpp
#include<cstdio>
#include<ALGORITHM>
using namespace std;
const int MAXN=200005;
int n,m,head[MAXN],nxt[MAXN*2],num[MAXN*2],tot,x,y,d[MAXN],q[MAXN],l,r,f1[MAXN],f2[MAXN];
int head_[MAXN],nxt_[MAXN*2],num_[MAXN*2],tot_,cnt;
void add(int x,int y){nxt[++tot]=head[x];head[x]=tot;num[tot]=y;}
void add_(int x,int y){nxt_[++tot_]=head_[x];head_[x]=tot_;num_[tot_]=y;}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		add(x,y);add_(y,x);d[y]++;
	}
	for(int i=1;i<=n;i++)
	if(d[i]==0)q[++r]=i;
	while(l<=r){
		int now=q[l];
		for(int i=head[now];i;i=nxt[i]){
			d[num[i]]--;
			if(d[num[i]]==0)
			q[++r]=num[i];
		}
		l++;
	}
	if(r!=n){
		printf("-1\n");
		return 0;
	}
	for(int i=1;i<=n;i++)
	f1[i]=f2[i]=i;
	for(int l=1;l<=n;l++){
		int now=q[l];
		for(int i=head_[now];i;i=nxt_[i])
		f1[now]=min(f1[now],f1[num_[i]]);
	}
	for(int l=n;l>=1;l--){
		int now=q[l];
		for(int i=head[now];i;i=nxt[i])
		f2[now]=min(f2[now],f2[num[i]]);
	}
	for(int i=1;i<=n;i++)if(f1[i]==i&&f2[i]==i)cnt++;
	printf("%d\n",cnt);
	for(int i=1;i<=n;i++){
		if(f1[i]==i&&f2[i]==i)printf("A");
		else printf("E");
	}
	printf("\n");
	return 0;
}
```


---

