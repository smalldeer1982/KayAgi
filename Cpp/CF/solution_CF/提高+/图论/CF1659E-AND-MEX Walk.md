# AND-MEX Walk

## 题目描述

There is an undirected, connected graph with $ n $ vertices and $ m $ weighted edges. A walk from vertex $ u $ to vertex $ v $ is defined as a sequence of vertices $ p_1,p_2,\ldots,p_k $ (which are not necessarily distinct) starting with $ u $ and ending with $ v $ , such that $ p_i $ and $ p_{i+1} $ are connected by an edge for $ 1 \leq i < k $ .

We define the length of a walk as follows: take the ordered sequence of edges and write down the weights on each of them in an array. Now, write down the bitwise AND of every nonempty prefix of this array. The length of the walk is the MEX of all these values.

More formally, let us have $ [w_1,w_2,\ldots,w_{k-1}] $ where $ w_i $ is the weight of the edge between $ p_i $ and $ p_{i+1} $ . Then the length of the walk is given by $ \mathrm{MEX}(\{w_1,\,w_1\& w_2,\,\ldots,\,w_1\& w_2\& \ldots\& w_{k-1}\}) $ , where $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND).

Now you must process $ q $ queries of the form u v. For each query, find the minimum possible length of a walk from $ u $ to $ v $ .

The MEX (minimum excluded) of a set is the smallest non-negative integer that does not belong to the set. For instance:

- The MEX of $ \{2,1\} $ is $ 0 $ , because $ 0 $ does not belong to the set.
- The MEX of $ \{3,1,0\} $ is $ 2 $ , because $ 0 $ and $ 1 $ belong to the set, but $ 2 $ does not.
- The MEX of $ \{0,3,1,2\} $ is $ 4 $ because $ 0 $ , $ 1 $ , $ 2 $ and $ 3 $ belong to the set, but $ 4 $ does not.

## 说明/提示

The following is an explanation of the first example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1659E/e80c1510937e2e4c165cad1b2b45b357811161d4.png)The graph in the first example.Here is one possible walk for the first query:

 $ $$$1 \overset{5}{\rightarrow} 3 \overset{3}{\rightarrow} 2 \overset{1}{\rightarrow} 1 \overset{5}{\rightarrow} 3 \overset{1}{\rightarrow} 4 \overset{2}{\rightarrow} 5. $ $ </p><p>The array of weights is  $ w=\[5,3,1,5,1,2\] $ . Now if we take the bitwise AND of every prefix of this array, we get the set  $ \\{5,1,0\\} $ . The MEX of this set is  $ 2$$$. We cannot get a walk with a smaller length (as defined in the statement).

## 样例 #1

### 输入

```
6 7
1 2 1
2 3 3
3 1 5
4 5 2
5 6 4
6 4 6
3 4 1
3
1 5
1 2
5 3```

### 输出

```
2
0
1```

## 样例 #2

### 输入

```
9 8
1 2 5
2 3 11
3 4 10
3 5 10
5 6 2
5 7 1
7 8 5
7 9 5
10
5 7
2 5
7 1
6 4
5 2
7 6
4 1
6 2
4 7
2 8```

### 输出

```
0
0
2
0
0
2
1
0
1
1```

# 题解

## 作者：Binary_Lee (赞：14)

## [题目传送门](https://www.luogu.com.cn/problem/CF1659E)

## 位运算

设题目中序列 $w_1,w_1 \& w_2,w_1 \& w_2 \& w_3,\dots,w_1 \& w_2 \& \dots \& w_n$ 为序列 $A$。

因为是数字一个一个 $\&$ 到之前的结果上，所以可以知道 $A$ 序列单调不增。

~~从给出的样例中发现，似乎没有答案超过 $2$ 的情况~~

**证明：**

假设答案 $>2$，则说明 $A$ 序列至少中出现过了 $0,1,2$，因为 $A$ 序列单调不增，所以假设当前的 $A_i$ 为 $2$，必须后面的数出现 $1$ 和 $0$ 才可以。但 $2$ 的二进制末位为 $0$，无论怎么 $\&$ ，后面的数也不可能出现 $1$，假设不成立，所以答案不可能 $>2$。

**结论：**

答案为 $0$，$1$ 或 $2$。

## 判断答案

- **首先考虑答案为 $0$ 的情况，即 $A$ 序列中没有出现过 $0$：**

$A$ 序列中没有出现过 $0$，即说明对于所有 $w$，在二进制下至少有一位都是 $1$，不然 $\&$ 后就会变 $0$。

那么如何判断是否有一条路径上所有边权在二进制下至少有一位都是 $1$？

考虑用并查集维护。因为 $w<=2^{30}$，所以可以开 $30$ 个并查集，分别维护每一位上是 $1$ 的边权所连接的点的集合，然后要判断求的两点是否在其中一张图中连通即可。

- **再看答案为 $1$ 的情况，即 $A$ 序列中出现过 $0$ 但没有出现过 $1$：**

$A$ 序列中没有出现过 $1$，即说明对于 $A$ 序列前某一部分 $(i<k)$，$a_i>1$，而 $a_k$ 及之后都是 $0$。

先考虑如何保证 $A$ 序列前某一部分 $(i<k)$，$a_i>1$。这个和答案为 $0$ 的情况很像，只要所有  $w_i(i<k)$ 中至少有一位都是 $1$  即可。但特别地，这一位不能是末位，否则 $a_{k-1}$ 就变 $1$ 了。

然后就只要判断之后是否有一条边可以使 $\&$ 之后结果为 $0$ 即可。

如何维护？

先上结论：只要保证末位有一个 $0$ 即可。先把之前判断答案是否为 $0$ 的并查集借过来，然后事先找好哪些边权末位为 $0$，将与这些边相邻的点和一个虚点 $0$ 连起来。如果后询问中出发点 $u$ 可以和虚点 $0$ 连通，那么答案就为 $1$ 了。

证明：如果后询问中出发点 $u$ 可以和虚点 $0$ 连通，就意味着 $u$ 在某一位上 （不为末位）可经过连续的几个 $1$，保证了 $a_i>1$。然后可以走到一位末位为 $0$ 的，$a_i$ 的末位就会变成 $0$。之后，因为不存在某一位全部为 $1$ 的（已经被判掉了），所以可以保证 $a_i$ 的其他位最终也会变成 $0$。

这一部分有点绕，建议花点时间自己举几个例子好好理解一下。

- **最后，都不是这两种情况的答案就为 $2$。**

------------

那么，如何方便地实现并查集？

## 便利の并查集

可以写到一个结构体里。（涨芝士了

比如：

```cpp
struct DSU{
	int fa[100005];
	DSU(){for(int i=0;i<=100000;i++)fa[i]=i;}  //初始化 
	int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}  //find 
	void merge(int x,int y){fa[find(x)]=find(y);}  //合并 
	bool query(int x,int y){return find(x)==find(y);}  //判断 
}x[35];
```

合并： 
```cpp
x[i].merge(u,v);
```

判断联通：
```cpp
if(x[i].query(u,v))
```

要开多个并查集时很方便，比写二维数组要清楚。

## 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q,u,v,w;
bool mark[100005];
struct DSU{   //还是喜欢不压行
	int fa[100005];
	DSU(){
		for(int i=0;i<=100000;i++) fa[i]=i;
	}
	int find(int x){
		if(fa[x]==x) return x;
		return fa[x]=find(fa[x]);
	}
	void merge(int u,int v){
		fa[find(u)]=find(v);
		return ;
	}
	bool query(int u,int v){
		return find(u)==find(v);
	}
}x[35],y[35];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&u,&v,&w);
		for(int j=0;j<30;j++){  
			if((w>>j)&1) x[j].merge(u,v);  //j位是1的连起来
		}
		if(!(w&1)) mark[u]=mark[v]=1;  //末位不是1做标记
	}
	for(int i=1;i<=30;i++){   //从1开始
		y[i]=x[i];
		for(int j=1;j<=n;j++){
			if(mark[j]) y[i].merge(j,0);  //有标记和0连
		}
	}
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		scanf("%d%d",&u,&v);
		bool fl=0; 
		for(int j=0;j<30;j++){   //从0开始
			if(x[j].query(u,v)){
				printf("0\n"),fl=1;
				break;
			}
		}
		if(fl) continue;
		for(int j=1;j<30;j++){    //从1开始
			if(y[j].query(u,0)){
				printf("1\n"),fl=1;
				break;
			}
		}
		if(fl) continue;
		printf("2\n");
	}
	return 0;
}
```


---

## 作者：jiangtaizhe001 (赞：3)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/16175665.html)  
[题目传送门](https://codeforces.com/problemset/problem/1659/E)

### 题目大意
给定一个无向带权图，总共有 $n$ 个点 $m$ 条边，选定一个起点 $u$ 和终点 $v$，现在你需要确定一条路径，设路径上的 $k$ 条边的边权为 $w_1,w_2,\dots,w_k$，求出 $\operatorname{MEX}\left(\{w_1,w_1 \& w_2,w_1\&w_2\&w_3,\dots,w_1\&w_2\&\dots\&w_k\}\right)$ 的最小值。其中  MEX 指集合中最小的不存在的自然数。  
数据范围：$n,m\le 10^5$，边权 $\le 2^{30}$。  
### 题目解析
设路径上的 $k$ 条边的边权为 $w_1,w_2,\dots,w_k$，为了方便设序列 $w_1,w_1 \& w_2,w_1\&w_2\&w_3,\dots,w_1\&w_2\&\dots\&w_k$ 的第 $i$ 项为 $a_i$。

首先我们~~通过样例~~发现一个结论：答案只可能是 $0,1,2$。    
其实就是证明答案不是 $0,1$ 的时候答案为 $2$,证明如下：  
我们发现序列 $\{a_n\}$ 不增。  
如果答案不是 $0,1$，那么序列中就一定存在 $0,1$，如果答案不是 $2$，那么肯定存在一个数字 $i$ 使得 $a_i=2$ 并且 $a_{i+1}=1$，也就是说 $2\&w_{i+1}=1$，显然不成立。

这样我们只需要判断答案是否为 $0$，然后判断答案是否为 $1$，如果都不是那么答案就是 $2$。  

答案为 $0$ 的时候很简单，我们只需要判断是否从 $u$ 到 $v$ 存在一条路径，使得这条路径上的所有边权在二进制下某一位都为 $1$。只需要每一位建立一个并查集就可以了。  

然后就是答案为 $1$ 的情况了。  
不难发现答案为 $1$ 的时候，一定存在一个 $r$ 使得 $\forall i\le r,a_i>1$ 并且 $a_{r+1}=0$。  
换句话说，只要在走这一条边之前的与和大于 $1$，走之后与和为 $0$ 就可以了，然后接下来怎么走都可以，所以这样答案与终点无关。  
那么怎么得到这样一条路径呢？  
显然我们需要选定一位 $i$（不能是二进制下最低的一位！），然后从出发点走遍所有边权二进制这一位为 $1$ 的边，然后我们只需要找是否存在一条边能够让与和变成 $0$。  
具体用代码实现的话需要利用前面建立的并查集，并且记录每一个点所有的出边的边权的与和 $f_i$，然后算出在同一个联通块里面的点 $f_i$ 的与和，如果是 $0$ 代表这一个联通块内的点作为出发点可以做到答案为 $1$。

如果答案不是 $0$ 也不是 $1$，那么答案就是 $2$ 了。

代码：
```cpp
#include<cstdio>
#define gc getchar
#define maxn 100039
using namespace std;
int read(){
	char c=gc(); int s=0; int flag=0;
	while((c<'0'||c>'9')&&c!='-') c=gc(); if(c=='-') c=gc(),flag=1;
	while('0'<=c&&c<='9'){ s=(s<<1)+(s<<3)+(c^48); c=gc(); }
	if(flag) return -s; return s;
}
int n,m,u,v,w,T,fa[30][maxn],f[maxn],s[maxn],flag[maxn];
int getfa(int x,int y){ if(fa[x][y]==y) return y; else return fa[x][y]=getfa(x,fa[x][y]); }
int check0(){ int i; for(i=0;i<30;i++) if(getfa(i,u)==getfa(i,v)) return 1; return 0; }
int main(){
	n=read(); m=read(); int i,j,k; for(i=0;i<30;i++) for(j=1;j<=n;j++) fa[i][j]=j;
	for(i=1;i<=n;i++) f[i]=(1<<30)-1;
	for(i=1;i<=m;i++){
		u=read(); v=read(); w=read(); f[u]&=w; f[v]&=w;
		for(j=0;j<30;j++) if(w&(1<<j)) fa[j][getfa(j,u)]=getfa(j,v);
	}
	for(k=1;k<30;k++){
		for(i=1;i<=n;i++) s[i]=(1<<30)-1;
		for(i=1;i<=n;i++) s[getfa(k,i)]&=f[i];
		for(i=1;i<=n;i++) if(s[getfa(k,i)]==0) flag[i]=1;
	} T=read(); while(T--){
		u=read(); v=read(); if(check0()) puts("0"); else if(flag[u]) puts("1"); else puts("2");
	} return 0;
}
```

---

## 作者：ran_qwq (赞：2)

很不错的一道题！

样例输出只有 $0,1,2$，猜测输出就只有这三种。

why？这个与有个典型性质：设 $w$ 数组长度为 $k$，$s_i=w_1\operatorname{and}w_2\operatorname{and}\dots\operatorname{and}w_i$，则 $s_i\le s_{i-1}$，且 $s_i\subseteq s_{i-1}$（表示对于 $s_i$ 所有的 $1$，$s_j$ 那一位也是 $1$）。所以 $2$ 后面不能跟着 $1$，$2$ 不能和 $1$ 同时出现，MEX 不会大于 $2$。

接下来就好办多了，开始分类讨论。

1. 答案为 $0$。

也就是说不存在 $i$ 使得 $s_i=0$，即 $s_k>0$，所有经过的边权与起来不为 $0$。所以存在一位，使得经过的所有边权这一位都是 $1$。

做法比较多，可以维护 $\log V$（$V$ 是值域）个并查集，第 $i$ 个表示在经过的所有边权第 $i$ 位都是 $1$。询问时判断连通性即可。

2. 答案为 $1$。

此时的 $s$ 值都是前面全部 $>1$，后面全部 $=0$。

现在我们就只需要判断能否在 $s_i\ne1$ 的情况下，找到一条边权为偶数的边。这样后面不管怎样走 $s_i$ 都为 $0$。

可以建一个虚点，如果 $(x,y)$ 的边权为偶数，就把 $x$ 和 $y$ 都和虚点连边。判断时对于所有非末位的位的并查集，判断是否与虚点连通就行了。

3. 答案为 $2$。

剩下的就是答案为 $2$ 的情况。

---

## 作者：Exp10re (赞：1)

好题。

## 解题思路

观察样例 2，猜测答案不大于 $2$。

证明：若存在一组询问满足答案大于 $2$，则显然集合内同时存在 $0,1,2$。由于 $x \And y\leq \min(x,y)$，又因为上述条件被满足需要存在一条边 $x$ 满足 $w_i \And 2 =1$，而这是不可能的，故答案小于等于 $2$。

考虑判断答案为 $0$ 的条件。不难注意到答案为 $0$ 当且仅当存在一条路径满足这条路径上的所有边权二进制某一位均为 $1$。

考虑如下做法：建立 $31$ 个并查集，对于边权二进制第 $i$ 位为 $1$ 的边，在并查集中合并该边连接的点。不难注意到答案为 $0$ 当且仅当询问的两点满足存在一个并查集使得该两点连接。

接下来判断 $1$：容易发现，若答案为 $1$，则至少需要经过一条边权为偶数的边，且在此之前经过的边边权与起来的值不为 $1$。

后者可以用先前建立的并查集判断两点是否存在一条路径满足其边权与值不为 $0$ 或 $1$，前者可以考虑在加入一条边权为偶数的边时将所有并查集中其连接的两点所在的并查集染色，如此，若答案不为 $0$，则答案为 $1$ 的充要条件是存在一个并查集满足起点所在的并查集被染色。

除此之外的询问答案都为 $2$。

时间复杂度 $O(\omega(n+m+q)\alpha(n))$，其中 $\omega=31$。

---

## 作者：Hisaishi_Kanade (赞：1)

天才般的题目！

首先原题这种 $\text{mex}(\{w_1,w_1\&w_2,w_1\&w_2\&w_3,\cdots\})$ 太抽象了吧，考虑到 $\&$ 的一个性质：

+ $a\& b \le \min(a, b)$。

即一个数按位与另外一个数，结果肯定不会比这个数大。证明是显然的。

那么这个结论有什么用呢？我们会发现很多非常有意思的事实。设 $P\gets \{w_1,w_1\&w_2,w_1\&w_2\&w_3,\cdots\}$。

那么 $P$ 会成为一个不升的序列，其 $\text{mex}$ 我们直接考虑其最后几项。

设最后一个值是 $P_k$，那么若 $P_k\not =0 $，结果会是 $0$。

考虑怎么做到这个东西。那么就是存在一条路径，使得路径上全部 $\&$ 起来不为 $0$。

这个时候拆位是很显然，每一位拆开，然后并查集维护每一位上为 $1$ 的路径。这个时候有 $\log V$ 个并查集，对于每个询问 $u,v$ 如果 $u,v$ 在至少一个并查集中属于一个集合，那么就说明可以有至少一条路径将 $u,v$ 连接且权值不为 $0$。

如果答案为 $1$，会怎么样呢？其实就是 $P$ 满足每个数的最低位形成一段 $1$（且这一段的 $P$ 都得 $>0$），一段 $0$。因为我们刚刚判过了 $u,v$ 可以直接联通的情况，所以其他位都不能直接联通。

那我们不如改写 $u\to v$ 到 $u\to v^\prime\to v$，其中 $v^\prime$ 表示这个点之后的最后一位都变成 $0$ 了。

那其实就是我们从 $u$ 在这一位的并查集所在的集合，存在一条连的偶数边。只有偶数能做到把最低位的 $1$ 给消了。

那么这就简单了，我们把所有能连到偶数边的点全部拉到一个虚点 $s$ 上，这就可以解决问题了！如果 $u,s$ 联通，那么就说明答案为 $1$。

答案为 $2$，则出现了 $0, 1$ 且不出现 $2$，有点难处理，答案为 $3$？但是你发现这样 $P$ 最后肯定出现了形如 $2,1,0$ 的部分，而 $2$ 不可能变成 $1$。

所以 $ans\in\{0,1,2\}$，故判了 $0,1$ 就可以输出 $2$。

```cpp
// LUOGU_RID: 127401697
#include <bits/stdc++.h>
#define per(i, l, r) for(i=l; i<r; ++i)
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
using namespace std;
using ll=long long;
static const int Buf_size=1<<25;
static char _c; static int _x;
static const signed int base_10=10, zero(48), nine(57), flag_signed(45);
static char buf[Buf_size], *p1=buf, *p2=buf;
#define digit() (zero<=_c&&_c<=nine)
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,Buf_size,stdin),p1==p2)?EOF:*p1++)
inline int read(){_x=0;_c=getchar();while(!digit()){_c=getchar();}while(digit()){_x=_x*10+(_c^zero);_c=getchar();}return _x;}
const int lgN=30, N=1e5+5, inf=2e9;
const ll illf=1e18;
int a[N];
int qt, n, i, j, k, u, v, w, m, s;
class DSU
{
private:
	int f[N]; int i;
public:
	inline void reset(int x) {int i; rep(i, 1, x) f[i]=i;}
	inline int find(int x)
	{
		while(x!=f[x]) x=f[x]=f[f[x]];
		return x;
	}
	inline void merge(int x, int y)
	{
		f[find(x)]=find(y);
	}
} dsu[3][lgN];
int main()
{
	n=read(); m=read(); int s=n+1, q;
	rep(i, 0, 29) dsu[1][i].reset(n);
	rep(i, 0, 29) dsu[2][i].reset(n+1);
//	puts("ok");
	rep(i, 1, m)
	{
		u=read(); v=read(); w=read();
		rep(j, 0, 29) if(w&(1<<j)) {dsu[1][j].merge(u, v); dsu[2][j].merge(u, v);}
		if(w%2==0) rep(j, 0, 29) {dsu[2][j].merge(u, s); dsu[2][j].merge(v, s);}
	}
	q=read();
	while(q--)
	{
		u=read(); v=read();
		rep(j, 0, 29) if(dsu[1][j].find(u)==dsu[1][j].find(v))
		{
			puts("0");
			break;
		}
		if(j<=29) continue;
		rep(j, 1, 29) if(dsu[2][j].find(u)==dsu[2][j].find(s))
		{
			puts("1");
			break;
		}
		if(j<=29) continue;
		puts("2");
	}
	return 0;
}
```

---

## 作者：chzhc (赞：1)

### 题意

给定一张 $n$ 个点 $m$ 条边（边有边权）的无向联通图，定义一条路径的长度为 $\operatorname{mex}\{w_1, w_1 \& w_2, \cdots, w_1 \& w_2 \&\cdots \&w_k\}$，其中 $k$ 为这条路径的长度，$w_1, w_2, \cdots, w_k$ 表示这条路径上依次经过的边的边权。现在有 $q$ 次询问，每次询问给出 $u, v$，要你求出 $u \to v$ 的最小路径长度。

数据范围：$2 \le n \leq 10^5$，$n - 1 \leq m \leq \min\left(\dfrac{n (n - 1)}{2}, 10^5\right)$，$0 \leq w \leq 2 ^ {30}$，$1 \leq q \leq 10^5$。

### 做法

定理 1. $1$ 和 $2$ 不会同时出现在一条路径的 $\operatorname{mex}$ 中。

证明如下：使用反证法证明，假设 $1$ 先出现在该路径的 $\operatorname{mex}$ 中，考虑到 $1$ 的二进制下的第二位是 $0$，且进行的是 $\&$ 运算，于是后面的值中第二位不可能 $1$，也就证明了 $2$ 不可能出现在该路径的 $\operatorname{mex}$ 中；对于 $2$ 先出现在该路径的 $\operatorname{mex}$ 中的情况同理。

由定理 1. 可知：任何一个路径其长度不可能大于 $2$。

那么只需要判断是否存在长度为 $0 / 1$ 的路径，若不存在则答案为 $2$。

1. 判断是否存在长度为 $0$ 的路径，即存在某一位 $k$，使得路径上每一条边的边权在第 $k$ 位上均为 $1$。考虑枚举 $k \in [0, 29]$，将边权在第 $k$ 位为 $1$ 的边保留下来，这样会形成 $30$ 个新图，对每个新图都使用并查集维护连通性即可。对于询问 $(u, v)$，我们只需判断是否有新图满足 $u, v$ 在同一个的连通块，若有则代表存在长度为 $0$ 的路径。
2. 判断是否存在长度为 $1$ 的路径，考虑这条路径如何实现，一定是先经过若干位奇数边权（当前长度 $>1$），然后经过一个偶数边权，最后随便经过某些路径，最后到达终点。考虑还是先枚举 $k \in [1, 29]$，使得每一条边都只经过边权在第 $0 / k$  位为 $1$ 的边，照样用并查集维护这些新图，然后对于边权为偶数的边 $(u, v)$，我们在所有新图上 $u, v$ 所在的连通块打上标记。对于询问 $(u, v)$，我们只需判断是否有新图满足 $u$ 的连通块上有标记，若有标记则代表存在长度为 $1$ 的路径。

时间复杂度 $\mathcal O(n \log w + (m + q) \cdot \alpha(n)\log w)$。

[评测链接](https://codeforces.com/contest/1659/submission/154053555)。

---

## 作者：耶梦加得 (赞：1)

~~此题难点在于：看出这题可做。~~

为了方便，称路径上的 $w$ 构成了 $W$ 数组，$W$ 的前缀 AND 和为 $S$ 数组。

首先我们容易想到如果存在一条路径，所有的 $S_i$ 均非 $0$，则答案为 $0$。这时所有的边权至少有一个二进制位均为 $1$。我们把边权按位拆开，建立 $30$ 张无向图，在第 $i$ 张图中， $u, v$ 之间有边，当且仅当原图中 $u, v$ 之间有边 $(u, v, w)$ 且 $w \& 2^i$ 非 $0$。我们可以用并查集维护，即可快速维护查询的两点 $u, v$ 之间是否存在一条答案为 $0$ 的路径。

~~可是 CF 没有部分分啊，你跟我讲这干啥。~~

大眼观察样例，发现答案只有 $0, 1, 2$ 三种。是不是答案不会超过 $2$ ？

小心求证，发现如果答案大于 $2$，说明 $S$ 中同时存在 $1, 2$ 两个数字，由 AND 运算的单调不升性质，这可以推出在某一时刻有 $2 \& W_i = 1$，这显然是不可能的。

~~换而言之，我们刚才做完了这题的三分之一。~~

继续大力讨论答案为 $1$ 的情况。由刚才的讨论我们知道 $S$ 中存在 $0$ 是可以保证的。则我们只需保证 $S$ 中不存在 $1$。

接下来是相对难想的部分：假设路径上第一个偶数边权为 $w_i$。显然 $S_j (j \ge i)$ 均为偶数，即不为 $1$。由单调不升性，则我们只需要保证 $S_{i-1} \ne 1$。由假设 $w_j (j < i)$ 均为奇数，则 $S_{i-1}$ 也为奇数，$S_{i-1} \ge 3$，则 $S_{i-1}$ 的二进制表达中，第 $0$ 位必然是 $1$，且有另一位也为 $1$。

和第一种情况处理类似，我们把图拆成 $29$ 张，在第 $i$ 张图中,，$u, v$ 之间有边，当且仅当原图中 $u, v$ 之间有边 $(u, v, w)$ 且 $w \& 2^i, w \& 1$ 均非 $0$。

除此之外我们还需要保证我们有一条偶数边权的边可以走，只要~~到达那个地方~~走到偶数边权的边之后我们怎么走都无所谓（换而言之，对于这种情况，$v$ 是谁根本不重要）。

我们标记原图中，偶数边权的边的两个端点。然后对于每一张图，遍历每一个点把标记 push 给并查集中的祖先。查询时对于每一张图看一看 $u$ 在这张图上的祖先到底行不行就行了。

~~还有剩下三分之一咋做。~~

~~答案就三种，你排除了其他两个不输出 $2$ 难道钝角吗。~~

令 $\omega = 32$，并查集复杂度为 $d(n)$，则总时间复杂度为 $O((q+n+m)d(n)\omega)$。

```cpp
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
#include<vector>
#define miu 100007
using namespace std;
int n, m;
bool flag[miu], f[miu][31];
struct UDS {
    int fa[miu];
    inline void init() {
        for(int i = 1; i <= n; ++i) fa[i] = i;
    }
    int getf(int x) {
        return fa[x] == x ? x : fa[x] = getf(fa[x]);
    }
    inline void merge(int x, int y) {
        int u = getf(x), v = getf(y);
        fa[u] = v;
    }
}s0[31], s1[31];
signed main() {
    scanf("%d %d", &n, &m);
    for(int i = 0; i <= 29; ++i) {
        s0[i].init(); s1[i].init();
    }
    for(int i = 1; i <= m; ++i) {
        int u, v, w; scanf("%d %d %d", &u, &v, &w);
        for(int j = 0; j <= 29; ++j) {
            if((1 << j) & w) s0[j].merge(u, v);
        }
        if(w & 1 ^ 1) flag[u] = flag[v] = true;
        else {
            for(int j = 1; j <= 29; ++j) {
                if((1 << j) & w) s1[j].merge(u, v);
            }
        }
    }
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= 29; ++j) {
            int x = s1[j].getf(i);
            f[x][j] |= flag[i];
        }
    }
    int q;
    scanf("%d", &q);
    while(q--) {
        int u, v;
        scanf("%d %d", &u, &v);
        int ans = -1;
        for(int j = 0; j <= 29; ++j) {
            if(s0[j].getf(u) == s0[j].getf(v)) {
                ans = 0; break;
            }
        }
        if(~ans) {printf("%d\n", ans); continue;}
        for(int j = 1; j <= 29; ++j) {
            if(f[s1[j].getf(u)][j]) {
                ans = 1; break;
            }
        }
        printf("%d\n", ~ans ? ans : 2);
    }
    return 0;
}

```


---

## 作者：_Spectator_ (赞：1)

[可能更好的食用体验](/article/o7jd9wns) $|$ 
[题目传送门](/problem/CF1659E) $|$ 
[我的其他题解](/user/523641#article.2)

有趣的题。

------------

### ${\color{#00CD00}\text{思路}}$

为了便于叙述，定义 $a_i = w_1 \land w_2 \land \dots \land w_i$。

首先可以发现，对于任意一个询问，答案只有可能是 $0,1,2$ 中的一个。

- 这是因为：根据按位与运算的性质，如果一个数 $x$ 在二进制下的某一位是 $0$，那么当 $x$ 进行了若干次按位与运算后，这一位将永远是 $0$。而 $1$ 在二进制下是 $01$，$2$ 在二进制下是 $10$。显然，$1$ 和 $2$ 不可能同时出现在 $a$ 序列中。原命题得证。

这样一来，原问题就被简化为了只需要判断答案是 $0$ 还是 $1$ 还是 $2$ 即可。 

- 若答案为 $0$，说明 $a$ 序列中没有出现 $0$。

$a$ 中没有出现 $0$，相当于所有的 $w$ 在二进制下至少有一位全都是 $1$。如何判断？考虑用**并查集**维护。我们可以开 $30$ 个并查集，对于一条边 $(u,v,w)$，如果 $w$ 某个二进制位上是 $1$，就在这一位对应的并查集里将 $u$ 和 $v$ 合并。

然后对于每一个查询 $(u, v)$，只需要判断是否存在一个二进制位，使得 $u$ 和 $v$ 在对应的并查集中连通即可。

- 若答案为 $1$，说明 $a$ 中出现了 $0$，但没有出现 $1$。

发现可以把路径分为前后两段，满足前半段的边权按位与后不为 $1$，后半段第一条的边权在二进制下末位为 $0$（即边权为偶数）。

对于前半段，可以用类似判 $0$ 的方法，只需要查询除了第 $0$ 位之外的并查集即可。

对于后半段，由于可以重复经过一些边，因此只需要判断 $u$ 能否到达一条边权为偶数的边即可。我们在原来的并查集上新增一个虚点 $0$，对于一条边 $(u,v,w)$，若 $w$ 为偶数，就将 $u$ 和 $v$ 与 $0$ 合并。这样对于每一个查询 $(u,v)$，只需要判断是否存在一个二进制位，使得 $u$ 在对应的并查集中与 $0$ 连通即可。

- 最后，若答案既不是 $0$ 也不是 $1$，就只能是 $2$ 了。

恕我表述不清，部分实现细节和正确性证明还请读者自行思考或参见代码。

------------

### ${\color{#00CD00}\text{代码}}$

```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i=a; i<=b; i++)
using namespace std;
const int N = 1e5 + 5;
struct DSU{ //并查集 
	int f[N]; DSU(){rep(i, 0, 1e5) f[i] = i;}
	void merge(int x, int y){f[find(x)] = find(y);}
	bool check(int x, int y){return find(x) == find(y);}
	int find(int x){return f[x] ^ x ? f[x] = find(f[x]) : x;}
}s[30], s1[30];
int n, m, Q;
signed main(){
	ios::sync_with_stdio(false), cin.tie(nullptr);
	for(cin >> n >> m; m --> 0;){
		int u, v, w; cin >> u >> v >> w;
		rep(j, 0, 29) if(w >> j & 1) s[j].merge(u, v), s1[j].merge(u, v);
		if((w & 1) == 0) rep(j, 1, 29) s1[j].merge(u, 0), s1[j].merge(v, 0);
	}
	for(cin >> Q; Q --> 0;){
		int u, v; cin >> u >> v;
		rep(i, 0, 29) if(s[i].check(u, v)){cout << 0; goto brk;}
		rep(i, 1, 29) if(s1[i].check(u, 0)){cout << 1; goto brk;}
		cout << 2; brk: cout << "\n";
	}
	return 0;
}
```

[AC Record](https://codeforces.com/contest/1659/submission/285831851)

---

## 作者：Vocaloid世末歌者 (赞：1)

学校模拟赛出了这题，感觉上位蓝。

-------------------------------

观察样例，发现只有 $0,1,2$？

猜一下，答案只能是 $0,1,2$。

> Proof：
> 
> 如果有 $>2$ 的，设这个数为 $t$。
> 
>那么一定要有 $0,1,2$。
> 
>但是！
> 
>这个序列是单调不升的！因为你一定是越 `&` 越小或者不变。
> 
>所以，如果你有了 $2$，那你 $1$ 一定是后面出的。
>但是！
> 
>你 $2$ 的末尾是 $0$，给它 `&` 到天上去末尾都不能是 $1$！
> 
>出矛盾，证毕。

~~然后某些人就可以快乐打随机数了。~~

既然只有三个，那就一个个来。

1. $0$ 的情况

也就是，$A$ 里面一个 $0$ 也没有。

那就需要边权 `&` 之后至少有一个 $1$，也就是这些边权**至少有一位都是 $1$**。

于是考虑并查集。

发现我们的 $w<2^{30}$，于是开 $30$ 个并查集，每个并查集维护第 $x$ 位上为 $1$ 的边形成的连通块。然后判断 $s,t$ 是否在同一个连通块内。

2. $1$ 的情况

也就是某一位之前全是 $1$，后面（包括自己）全是 $0$。

这是最恶心的地方，我搞出想法之后都觉得可能是假的。

我们需要选定一位 $i$（注意！不能是最右边那位！），然后从出发点走遍所有边权二进制这一位为 $i$ 的边，然后我们只需要找是否存在一条边能够让 
`&` 后的值变成 $0$。

接下来就是这题的精妙之处了，我们发现前面的并查集又能用？记录每一个点所有的出边的边权的与和 $and_i$（注意 `and` 是关键字，不要用），然后统计一整个连通块内 $and_i$ 的与和。若这个与和为零，这个连通块内的任意一个点作为 $s$ 的答案就可以是 $1$ 啦！

3. $2$ 的情况

运用小学知识，发现除了 $0,1$ 以外只能是 $2$ 了。~~最简单的一个。~~

代码：

```cpp
#include<stdio.h>
#include<bits/stdc++.h>
#define N 100010
#define MOD 998244353
#define esp 1e-8
#define INF 999999999999999999
#define LL long long
#define rep(i,a,b,g) for(LL i=a;i<=b;i+=g)
#define rem(i,a,b,g) for(LL i=a;i>=b;i-=g)
#define repn(i,a,b,g) for(LL i=a;i<b;i+=g)
#define remn(i,a,b,g) for(LL i=a;i>b;i-=g)
#define pll pair<LL,LL>
#define mkp(x,y) make_pair(x,y)
#define i128 __int128
#define lowbit(x) ((x)&(-(x)))
#define ls(x) ((x)<<1)
#define rs(x) ((x)<<1|1)
using namespace std;
void read(i128 &x)
{
    x=0;
    i128 f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')f=-1;
        ch=getchar();
    }
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	x*=f;
}
void write(i128 x)
{
    if(x<0)
    {
    	putchar('-');
    	x=-x;
    }
    if(x>9)write(x/10);
    putchar((x%10)^48);
}
LL T,n,m,u,v,w,fa[35][N],small_d[N],zaw[N],_is_1[N];
LL fi(LL x,LL i)
{
	if(fa[x][i]==i)return i;
	else return fa[x][i]=fi(x,fa[x][i]);
}
LL _is_0(LL u,LL v)
{
	repn(i,0,30,1)
	{
		if(fi(i,u)==fi(i,v))
		{
			return 1;
		}
	}
	return 0;
}
int main()
{
	cin>>n>>m;
	repn(i,0,30,1)
	{
		rep(j,1,n,1)
		{
			fa[i][j]=j;
		}
	}
	rep(i,1,n,1)small_d[i]=(1LL<<30)-1;
	rep(i,1,m,1)
	{
		cin>>u>>v>>w;
		small_d[u]&=w;
		small_d[v]&=w;
		repn(j,0,30,1)
		{
			if(w&(1LL<<j))
			{
				fa[j][fi(j,u)]=fi(j,v);
			}
		}
	}
	repn(x,1,30,1)
	{
		rep(i,1,n,1)
		{
			zaw[i]=(1LL<<30)-1;
		}
		rep(i,1,n,1)
		{
			zaw[fi(x,i)]&=small_d[i];
		}
		rep(i,1,n,1)
		{
			if(zaw[fi(x,i)]==0)
			{
				_is_1[i]=1;
			}
		}
	}
	cin>>T;
	while(T--)
	{
		cin>>u>>v;
		if(_is_0(u,v))puts("0");
		else
		{
			if(_is_1[u])puts("1");
			else puts("2");
		}
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

# CF1659E 题解



## 思路分析

注意到如下的观察：

> 对于任意的节点对 $(u,v)$，其答案只有可能是 $0,1,2$ 中的一个
>
> 对于任意的路径 $u\to v$ 记 $s_i=w_1\&w_2\&\cdots\&w_i$ 注意到 $s_1\supseteq s_2\supseteq\cdots$，那么显然 $u\to v$ 中不可能同时出现 $1$ 和 $2$ 故对于任何一条路径其权值 $\le2$。

所以我们只需要解决两个问题：

- 是否存在一条路径 $u\to v$ 使得 $\{s_i\}$ 中不出现 $0$。
- 是否存在一条路径 $u\to v$ 使得 $\{s_i\}$ 中不出现 $1$。

先解决第一个问题：

显然，假如 $\{s_i\}$ 中没有 $0$，那么一定有至少一个二进制位 $k$ 一直保持为 $1$，即我们经过所有的边权 $w_i$ 的第 $k$ 位都是 $1$。

因此我们可以对于每个 $k\in[0,30)$ 维护一个图 $\mathbf G_k$，把所有满足 $w$ 的第 $k$ 为 $1$ 的边加入 $\mathbf G_k$ 中，如果在某个 $\mathbf G_k$ 中 $(u,v)$ 联通，那么说明存在路径 $u\to v$ 使得第 $k$ 位一直保持为 $1$，答案为 $0$，如果不存在这样的 $k$，那么答案至少为 $1$，我们再去解决第二个问题。

考虑第二个问题：

由于此时所有路径 $u\to v$ 都包含 $0$，因此只要解决这个问题就能确定答案是 $1$ 还是 $2$ 了。

考虑 $\{s_i\}$ 中的第 $0$ 位，有如下两种情况。

- $\{s_i\}$ 的第 $0$ 位一直是 $0$，此时对于所有 $2\mid w$ 的边加入一张新图中并维护 $(u,v)$ 连通性即可。
- 在 $s_{i}\to s_{i+1}$ 时 $s_i$ 的第 $0$ 位从 $1$ 变成 $0$，且 $s_{i}$ 中除第 $0$ 位外至少有一个位置值为 $1$，类似问题一对于所有 。$k\in(0,30)$ 的 $k$，将所有第 $k$ 位和第 $0$ 位都为 $1$ 的边加入一个图 $\mathbf G'_k$ 中，而对于 $\mathbf G'_k$ 中的一个连通块，如果原图中存在一条 $2\mid w$ 的边连接其中的一个点，那么这个连通块里的所有点都可以通过经过这条边得到一个合法的 $s_{i+1}$。

因此对于每个问题我们维护 $n\log w$ 个并查集即可。

时间复杂度 $\Theta((m+q)\alpha(n)\log w)$。

## 代码呈现

```cpp
#include<bits/stdc++.h> 
using namespace std;
const int MAXN=1e5+1;
inline bool bit(int x,int k) { return (x>>k)&1; }
struct DSU {
	int dsu[MAXN];
	inline void size(int n) {
		for(int i=1;i<=n;++i) dsu[i]=i;
	}
	inline int find(int x) {
		if(dsu[x]==x) return x;
		return dsu[x]=find(dsu[x]);
	}
	inline void merge(int u,int v) {
		dsu[find(u)]=find(v);
	}
	inline bool same(int u,int v) {
		return find(u)==find(v);
	}
}	G0[30],G1[30];
bool mark1[30][MAXN];
inline bool void0(int u,int v) {
	for(int k=0;k<30;++k) if(G0[k].same(u,v)) return true;
	return false;
}
inline bool void1(int u,int v) {
	if(G1[0].same(u,v)) return true;
	for(int k=1;k<30;++k) if(mark1[k][G1[k].find(u)]) return true;
	return false;
}
signed main() {
	int n,m;
	scanf("%d%d",&n,&m);
	for(int k=0;k<30;++k) G0[k].size(n),G1[k].size(n);
	for(int i=1;i<=m;++i) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		for(int k=0;k<30;++k) {
			if(bit(w,k)) G0[k].merge(u,v);
			if(k!=0) {
				if(bit(w,k)&&bit(w,0)) G1[k].merge(u,v);
				if(!bit(w,0)) mark1[k][u]=mark1[k][v]=true;
			} else if(!bit(w,0)) G1[k].merge(u,v);
		}
	}
	for(int i=1;i<=n;++i) for(int k=1;k<30;++k) mark1[k][G1[k].find(i)]|=mark1[k][i];
	int q;
	scanf("%d",&q);
	while(q--) {
		int u,v;
		scanf("%d%d",&u,&v);
		if(void0(u,v)) puts("0");
		else if(void1(u,v)) puts("1");
		else puts("2");
	}
	return 0;
}

```



---

## 作者：donaldqian (赞：0)

首先注意到答案只可能是 $0,1,2$。

答案为 $0$ 时，即为存在 $i$ 使得 $w_1 \to w_k$ 中都含有 $2^i$ 这一位。

考虑分层图（多维并查集）。定义数组 `fa[i][j]` 表示在只有边权包含 $2^i$ 这一位的边构成的图里，$j$ 的父亲。此时答案为 $0$ 等价于在某一个图中，$s$ 和 $t$ 在同一个连通块中。

答案为 $1$ 时，就是前一段的权值都大于 $1$，后一段等于 $1$。

还是用上面的并查集，定义 $f_i$ 表示点 $i$ 的所有连边的与值，$F_i$ 表示在某一个分层图中，$i$ 所在的连通块每个点的 $f_i$ 值的与值。此时答案为 $1$ 等价于在某一个（非 `fa[0]` 的）（理由：在 `fa[0]` 这层图里，权值与出来会等于 $1$）分层图中，$F_s = 0$。（理由：在连通块里可以随便乱转，权值都一定不等于 $1$ 和 $0$，所以只要 $F = 0$，最后一定能取到 $0$）

其他的情况答案为 $2$。

[代码](https://local.cwoi.com.cn:8443/contest/C0599/problem/C)。

---

## 作者：Grace2022 (赞：0)

步骤和其它题解差不多，但思路讲得比较详细（个人认为），也可能比较啰嗦。
## 题目大意
题目链接：  
[[洛谷CF1659E] AND-MEX Walk](https://www.luogu.com.cn/problem/CF1659E)  
[[Codeforces1659E] AND-MEX Walk](https://codeforces.com/problemset/problem/1659/E)  
题目叙述得比较简练，这里不再赘述。但是要注意的是，从 $u$ 到 $v$ 可能存在多条路径，所以需要求的是“最小”路径长度。  
## 思路分析
### 答案是一个怎样的数
当我们拿到一道题却无所适从的时候，或许我们可以从答案入手反推。通过样例，我们推测答案只有 $0$、$1$、$2$ 三种。如果你没看出来这个规律也没关系，我们还可以观察按位与的性质（and 表示按位与，代码中表示为```&```）。  
1. $0\operatorname{and}0=0$ 
2. $0\operatorname{and}1=0$
3. $1\operatorname{and}0=0$
4. $1\operatorname{and}1=1$

观察上面四个式子，我们可以发现，对于每一个二进制位，只能从 $1$ 变成 $0$，而不能从 $0$ 变成 $1$。而 $0=(0)_2$，$1=(1)_2$，$2=(10)_2$。对于 $2$，我们不管怎么按位与都不能把它变成 $1$，同理可得，在集合 $mex$ 中，$1$ 和 $2$ 不可能同时存在。而我们要求的恰好是不在集合 $mex$ 中的最小自然数，所以答案只能在 $0$、$1$、$2$ 中。  
### 对答案分类讨论，反推过程
在我们确定了答案只能在 $0$、$1$、$2$ 这三个数之间时，就可以分类讨论了。因为求的是**最小**，所以我们从 $0$ 开始。  

#### 第一步：答案等于 0
当答案为 $0$ 时，$w_1$，$w_1\operatorname{and}{w_2}$，$w_1\operatorname{and}w_2\operatorname{and}w_3$，$w_1\operatorname{and}w_2\operatorname{and}w_3\cdots{w_{k-1}}$，这些按位与的结果不能为 0（$w$、$k$ 的含义见原题题面）。这就意味着从 $w_1$ 到 $w_{k-1}$ 在二进制位下至少有一位同时为 $1$，这才能使最终的结果在二进制位下至少有一位为 $1$，从而不等于 $0$。否则，最终的结果在二进制位下每一位都会变成 $0$，最后就等于 $0$，不符合条件。  

我们看到数据范围：$w\lt2^{30}$，这提示我们可以枚举每一个边权的二进制位，最后统计或者计算答案的时候只需要循环 30 次。现在需要思考：给出起点 $u$ 和终点 $v$，怎样判断 $u$ 和 $v$ 之间一定存在一个路径，使得路径上的每一个边权在二进制下至少有一位都是 $1$。我们可以把第 $i$ 位为 $1$ 的边放在一个集合中，如果 $u$ 和 $v$ 能被集合里的边连通，那么就输出答案 $0$。看到集合就触发关键词：并查集，我们可以把符合条件的边的两端点放在一个并查集中，如果 $u$ 和 $v$ 在一个集合里，就输出答案，如果硬要说实现过程比较像最小生成树判断点是否已经连通。  
#### 第二步：答案等于 1
到这一步时，我们已经进行完“等于 $0$”的判断，结果是不管怎么样最后一定存在 $0$ 在集合 $mex$ 中。  

我们在文初已经说明，$(0)_2$ 无论如何按位与都无法得到 $(1)_2$。那么只要二进制下末位为 $0$ 的 $w$ 先出现，再怎么按位与都不会得到 $1$ 了。而 $1$ 先出现的条件是所有的 $w$ 在二进制下末位为 $1$，更直白地说就是出现 $1$，所以排除掉 $1$ 即可。  

我们可以统计每一个边权在二进制下的每一位是否为 $1$ 并存在并查集中，因为在这个并查集中的边权相互按位与一定得不到 $1$。这个过程与上一步相同，所以可以借用上一步的并查集。我们还要统计边权为偶数（即在二进制下末位为 $0$）的边有哪些，并且把这些边存在同一个集合里。因为每次只枚举一条边，这里用到一个虚点 0 来代替并查集添加函数 $\operatorname{merge}$ 的第二个参数。然后我们跳过末位（即从倒数第二位）开始枚举，如果起点 $u$ 与虚点 0 在同一个集合里，就输出答案 $1$。  

虽然我们跳过了二进制下末位为 $1$ 的边权，但是如果该边权不等于 $1$，在后面的枚举中就会出现。  

当某个点在虚点 0 的集合中，那么这个点一定能在 $1$ 出现前先遇见偶数边权。如果还是没有理解可以手模样例试试，我实现过程讲得比较乱，~~但是毕竟我都能理解了~~。  

虚点 0 可以理解成一个不存在的集合祖先，因为所有含偶数边权的两端点都应该在一个集合内。当然你也可以先计算出第一个满足条件的端点并存储、使用，效果和虚点 0 是一样的，只不过比较麻烦。  
#### 第三步：答案等于 2
因为答案只可能是 $0$、$1$ 或 $2$，当判断下来答案不可能等于 $0$、$1$ 时，答案就是 $2$ 了。也就是说，当前面两步都不符合条件没输出，直接输出 $2$ 就行。
### 整理思路步骤，开始写代码
首先预处理第一步、第二步所需要的并查集，然后在询问的时候各自判断，时间复杂度 $\mathcal{O}(\max(n,q))$。
## AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long //可以不用 long long
struct edge{//存边，当然也可以随输入随存不用结构体
	int u,v,w;
}e[100005];
struct bingchaji{//用结构体成员函数写并查集，比二维并查集写起来简单些
	int fa[100005];
	bingchaji(){//初始化
		for(int i=1;i<=100000;i++){
			fa[i]=i;
		}
	}
	int find(int x){//寻找祖先
		if(fa[x]==x){
			return x;
		}
		else{
			return fa[x]=find(fa[x]);
		}
	}
	bool query(int x,int y){//查询祖先是否相等
		return find(x)==find(y);
	}
	void merge(int x,int y){//把 x 和 y 放在一个集合里
		fa[find(x)]=find(y);
	}
}a[35],b[35];
//a：第一步所需并查集
//b: 第二步所需并查集
/*
当ans=0：所有的w中至少有一个二进制位都是1
当ans=1：在遇到“1”之前先遇到了偶数边相连 
*/
int get(int x,int y,int m){
	for(int i=1;i<=30;i++){
		if(a[i].query(x,y)){
			return 0;
		}
	}
	for(int i=2;i<=30;i++){
		if(b[i].query(x,0)){
			return 1;
		}
	}
	return 2;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
//	cout<<(sizeof(e)+sizeof(a)+sizeof(b))/1024.0/1024;
	int n,m,q;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>e[i].u>>e[i].v>>e[i].w;
	}
	for(int i=1;i<=m;i++){//第一步预处理
		int cnt=1,t=e[i].w;
		while(t){
			if(t&1){//如果当前位为1就把边加入集合
				a[cnt].merge(e[i].u,e[i].v);
			}
			t>>=1;
			cnt++;
		}
	} 
	for(int i=2;i<=30;i++){
		b[i]=a[i];
		for(int j=1;j<=m;j++){
			if(!(e[j].w&1)){//如果为偶数边权就把两端点加入一个集合中
				b[i].merge(e[j].u,0);
				b[i].merge(e[j].v,0);
			}
		}
	}
	cin>>q;
	while(q--){
		int x,y;
		cin>>x>>y;
		cout<<get(x,y,m)<<'\n';
	}
	return 0;
}
```

---

## 作者：cwxcplh (赞：0)

一道十分灵活的题（没点脑子真做不出来）。

题目简化：经过某一条路径，使得这条路径能到 $u$ 和 $v$ 且这条路的 $\operatorname{mex}$ 值最小。其中 $\operatorname{mex}$ 是沿途路径权值两两与运算后没出现的最小的自然数。

~~通过样例可以看出好像答案只有 $0,1,2$。~~

**证明：** 假设 $0,1,2$ 都出现过，而有一个大于 $2$ 的数没出现。那因为 $2$ 出现过，所以必然有一段数转化为二进制后最后一位与运算后为 $0$，因为 $0$ 和任何数与运算后都是 $0$，所以 $1$ 一定在 $2$ 的前面，而因为有 $1$，所以除了二进制的最后一位，其他的位数都是 $0$，但是 $2$ 在 $1$ 后面且 $2$ 的第二位是 $1$ 不是 $0$，所以 $1$ 根本没出现，正好矛盾。

那什么时候答案是 $0$，什么时候答案是 $1$，什么时候又是 $2$ 呢？

### 思路

- **答案是 $0$：**

  如果答案是 $0$，说明除 $0$ 之外其他的数都出现过，很容易想到，只要保证这条路径上所有的边权的二进制必然有一位都是 $1$ 就可以了。

- **答案是 $1$：**

  这就不太好想了。我们可以这么思考：如果没出现过 $1$，说明存在一条分界线，它的前半部分 $\gt1$，后半部分则全是 $0$。

  前半部分 $\gt1$ 的做法很像上面求答案是 $0$ 的做法。只需要保证前半部分中有一位全都是 $1$ 就可以了。但要注意，这一位不能是最后一位，不然前半部分就已经出现 $1$ 了。

  后半部分全是 $0$ 的情况也很简单。我们只需要先判断后半部分的权值是不是没有任何一位全都是 $1$（上面算答案 $0$ 的时候就判断过，只要答案不是 $0$，那就肯定不满足），接着在看看后半部分是不是有一个末位为 $0$ 的，如果有，那答案就是 $1$。

- **答案是 $2$：**

  只要上面的都不满足，那答案就是 $2$ 了，具体证明见上。

思路有了，可是上面的做法时间复杂度太高了，怎么优化一下？

这就要请出这道题的精髓了：**并查集！**

怎么想到并查集的呢？主要还是因为这从始至终其实是一个图，而且又要找 $1$ 的个数，和并查集中的合并很像，所以就想到并查集了。

### 并查集优化

首先是合并，怎么合并呢？

我们不难发现，上面的思路中我们都在找一个东西：当前二进制中这一位有 $1$ 的权值。那很容易想到，我们只需要把这一位有 $1$ 的权值全连起来，形成一个小的连通块（或者叫树），我在查找从起点到终点之间是否有 $1$ 时，只需要看看它们两个是否连通了，如果连通了，那就说明必然有一位全都是 $1$。

接着是查找。查答案是 $0$ 的我们说过了，那答案为 $1$ 的呢？

注意看答案为 $1$ 的重点：**如果最后一位为 $0$，那后半部分就必然为 $0$**。这里主要在说关于最后一位的，所以我们只需要判断每个边权的最后一位是否为 $0$，然后再找个超级原点 $0$ 把所有最后一位是 $0$ 的起点和终点都合并到这个超级原点上，在判断时只需要看看起点能否到这个超级原点，能到末位就必然为 $1$。

**证明：** 如果我能到超级原点，那在其中就一定有一个点到另一个点之间的边权二进制最后一位为 $0$，那么在这个点之后的所有边权与运算后值都为 $0$，而在这个点之前的边权与运算后的值都 $\gt1$（上面已经否定了前面有 $1$ 的情况），因此这条路上必然没有 $1$。

**代码实现：**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,q,u,v,w,b[100006];
struct mw {
	int db[100006];
	mw() {
		for(int i=1; i<=100006; i++) {
			db[i]=i;
		}
	}
	int find(int u) {
		return u==db[u]?u:db[u]=find(db[u]);
	}
	void hb(int u,int v) {
		db[find(u)]=find(v);
	}
	bool pd(int u,int v) {
		return find(u)==find(v);
	}
} x[36],y[36];
signed main() {
	cin>>n>>m;
	for(int i=1; i<=m; i++) {
		cin>>u>>v>>w;
		for(int j=0; j<30; j++) {
			if(w&(1<<j)) {
				x[j].hb(u,v);
			}
		}
		if(!(w&1)) {
			b[u]=b[v]=1;
		}
	}
	for(int i=1; i<30; i++) {
		y[i]=x[i];
		for(int j=1; j<=n; j++) {
			if(b[j]) {
				y[i].hb(j,0);
			}
		}
	}
	cin>>q;
	while(q--) {
		cin>>u>>v;
		bool flag=false;
		for(int i=0; i<30; i++) {
			if(x[i].pd(u,v)) {
				cout<<"0"<<endl;
				flag=true;
				break;
			}
		}
		if(flag) {
			continue;
		}
		for(int i=1; i<30; i++) {
			if(y[i].pd(u,0)) {
				cout<<"1"<<endl;
				flag=true;
				break;
			}
		}
		if(flag) {
			continue;
		}
		cout<<"2"<<endl;
	}
	return 0;
}
```

---

## 作者：ifffer_2137 (赞：0)

### 题意
给定一个 $n$ 个点 $m$ 条边的无向连通图，边有边权。若一条路径（可以走重点重边）经过的边权序列为 $w_1,w_2,w_3\ldots w_k$，定义这条路径的代价为:
$$\text{mex}(w_1,w_1\&w_2,w_1\&w_2\&w_3,\ldots,w_1\&w_2\&\ldots\&w_k)$$
有 $q$ 次询问，每次给定两个点 $u,v$，求 $u$ 到 $v$ 的路径中的最小代价。
### 分析
盯真样例，发现答案 $\le2$。证明的话，显然前缀 $\&$ 序列是不升的，并且你有了一个 $2$ 之后最低位已经为 $0$，不可能再变为 $1$，所以 $0,1,2$ 不能同时出现，答案 $\le2$。

一般图上面在线回答不太好弄，询问离线下来一起处理。

先考虑答案等于 $0$ 的情况，一定存在某个 bit 使得整条路径上所有边权这个 bit 都为 $1$。直接枚一下这个 bit，每次把这个 bit 为 $1$ 的边加到并查集里，看一下如果某个询问的两个点连通，它的答案就是 $0$。

然后我们只要判断答案是否能为 $1$ 即可。你枚举一个 bit 带着一个 $1$，把这两位为 $1$ 的边连起来，如果一个点能通过走这些边走到一个权值为偶数的边，那么以它为起点的询问答案都为 $1$。

剩下还没处理过的答案都是 $2$ 了，时间复杂度 $O(n\log n\log V)$。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=1e5+5;
int n,m,q;
struct Edge{
	int u,v,w;
}E[maxn];
pii Q[maxn];
vector<int> S[maxn];
int ok[maxn],ans[maxn];
struct DSU{
	int fa[maxn];
	void init(){for(int i=1;i<=n;i++) fa[i]=i;}
	int fd(int x){return fa[x]==x?x:fa[x]=fd(fa[x]);}
	void merge(int x,int y){
		x=fd(x),y=fd(y);
		if(x==y) return;
		fa[x]=y;
	}
}dsu;
signed main(){
	cin.tie(0),cout.tie(0);
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		E[i]=(Edge){u,v,w};
	}
	q=read();
	for(int i=1;i<=q;i++){
		Q[i].fir=read(),Q[i].sec=read();
		ans[i]=2;S[Q[i].fir].eb(i);
	}
	for(int b=0;b<30;b++){
		dsu.init();
		for(int i=1;i<=m;i++) if(E[i].w&(1<<b)) dsu.merge(E[i].u,E[i].v);
		for(int i=1;i<=q;i++) if(dsu.fd(Q[i].fir)==dsu.fd(Q[i].sec)) ans[i]=0;
	}
	dsu.init();
	for(int i=1;i<=m;i++) if(!(E[i].w&1)) dsu.merge(E[i].u,E[i].v);
	for(int i=1;i<=q;i++) if(ans[i]&&dsu.fd(Q[i].fir)==dsu.fd(Q[i].sec)) ans[i]=1;
	for(int b=1;b<=30;b++){
		dsu.init();
		for(int i=1;i<=n;i++) ok[i]=0;
		for(int i=1;i<=m;i++){
			if((E[i].w&1)&&(E[i].w&(1<<b))) dsu.merge(E[i].u,E[i].v);
			else if(!(E[i].w&1)) ok[E[i].u]=ok[E[i].v]=1;
		}
		for(int i=1;i<=n;i++) ok[dsu.fd(i)]|=ok[i];
		for(int i=1;i<=n;i++) if(ok[dsu.fd(i)]) for(int j:S[i]) if(ans[j]) ans[j]=1;
	}
	for(int i=1;i<=q;i++) cout<<ans[i]<<"\n";
	return 0;
}
```

---

## 作者：Mine_King (赞：0)

[在我的博客获得更好的阅读体验](https://www.cnblogs.com/mk-oi/p/16670544.html)

## Problem

[CF1659E AND-MEX Walk](https://www.luogu.com.cn/problem/CF1659E)

**题目大意：**

给你一张 $n$ 个点 $m$ 条边的无向联通图，边有边权。  

定义一条依次经过 $e_1,e_2,\cdots,e_k$ 这些边的路径的权值为 $\operatorname{mex} \{w_1,w_2\&w_3,\cdots,w_1\&w_2\&\cdots\&w_k\}$。其中 $w_i$ 为边 $e_i$ 的边权。（**tips：路径可以重复经过一些边和一些点。**）

现在给你 $q$ 个询问，问从 $u$ 到 $v$ 的路径的权值的最小值。

## Solution

首先有一个结论，$w_1,w_2\&w_3,\cdots,w_1\&w_2\&\cdots\&w_k$ 是一个递减的序列，且若第 $i$ 个数二进制下某一位上为 $0$，则第 $i \le j \le k$ 个数这一位也必然为 $0$。原因显然。

然后又有一个结论，任意路径的权值只能是 $0,1,2$ 中的某一个。

**证明：**

若 $w_1\&w_2\&\cdots\&w_k \not= 0$，则这条路径的权值为 $0$。

在除掉上一种情况后，若存在某个 $i$ 使得 $w_i$ 为偶数，且序列中 $i$ 之前不存在 $1$ 则整个序列必然不可能出现 $1$，故权值为 $1$。

假设存在一条路径，序列中某一位是 $2$，某一位是 $1$。由第一个结论得 $2$ 必然在 $1$ 前面出现。但 $2$ 在二进制下第 $0$ 位为 $0$，$1$ 在二进制下第 $0$ 位为 $1$，与第一条结论冲突。故序列中不可能同时存在 $2$ 和 $1$，故除了上面两种情况，其他情况的权值均为 $2$。

接下来考虑一个一个判断。

要判断是否存在权值为 $0$ 的路径，实际上就是要判断是否存在一条路径使得路径上所有边权按位与后不为 $0$，也就是找一条路径使得路径上的边权在二进制下某一位均为 $1$。  
这个问题很好解决，只需要按位建立并查集，第 $i$ 个并查集只使用边权二进制下第 $i$ 位为 $1$ 的边，最后判联通即可。

若一条路径边权为 $1$，则其前半段路径上边权按位与之后不为 $1$，后半段第一条边边权为偶数。  
对于第一个条件，可以用类似于判 $0$ 的方法，只查询除了第 $0$ 位以外的并查集即可。  
对于第二个条件，由于可以重复经过一些边，所以我们可以让路径一直连到某一条边权为偶数的边，走一下再退回来。所以我们可以标记有边权为偶数的边直接连接的点，只要于这些点中的某一个联通即可。由于整张图是联通的，而走完这条边之后可以随便走，所以之后必然存在答案。但是如果每个集合都枚举这些点判是否联通，复杂度是 $O(nq)$ 的，所以我们可以建立一个虚点 $0$，把所有于偶数边权边直接相连的点与 $0$ 合并，这样只需查询是否与 $0$ 联通。

若以上两个条件都不满足，则最小权值只能是 $2$。

## Code

```cpp
//Think twice,code once.
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,m,f[100005];
struct bin
{
	int fa[100005];
	bin(){for(int i=0;i<=100000;i++) fa[i]=i;}
	int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
	void merge(int x,int y){fa[find(x)]=find(y);return ;}
	int query(int x,int y){return find(x)==find(y);}
}x[35],y[35];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		for(int i=0;i<30;i++)
			if((w>>i)&1) x[i].merge(u,v);
		if(!(w&1)) f[u]=f[v]=1;
	}
	for(int i=1;i<30;i++)
	{
		y[i]=x[i];
		for(int j=1;j<=n;j++)
			if(f[j]) y[i].merge(j,0);
	}
	int q;
	scanf("%d",&q);
	while(q--)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		for(int i=0;i<30;i++)
			if(x[i].query(u,v)){puts("0");goto NXT;}
		for(int i=1;i<30;i++)
			if(y[i].query(u,0)){puts("1");goto NXT;}
		puts("2");
		NXT:;
	}
	return 0;
}
```



---

