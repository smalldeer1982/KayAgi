# Strictly Positive Matrix

## 题目描述

You have matrix $ a $ of size $ n×n $ . Let's number the rows of the matrix from $ 1 $ to $ n $ from top to bottom, let's number the columns from $ 1 $ to $ n $ from left to right. Let's use $ a_{ij} $ to represent the element on the intersection of the $ i $ -th row and the $ j $ -th column.

Matrix $ a $ meets the following two conditions:

- for any numbers $ i,j $ ( $ 1<=i,j<=n $ ) the following inequality holds: $ a_{ij}>=0 $ ;
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF402E/5a3402d889c26bb1dab24aca748b24c9c6e8398d.png).

Matrix $ b $ is strictly positive, if for any numbers $ i,j $ ( $ 1<=i,j<=n $ ) the inequality $ b_{ij}&gt;0 $ holds. You task is to determine if there is such integer $ k>=1 $ , that matrix $ a^{k} $ is strictly positive.

## 样例 #1

### 输入

```
2
1 0
0 1
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
5
4 5 6 1 2
1 2 3 4 5
6 4 1 2 4
1 1 1 1 1
4 4 4 4 4
```

### 输出

```
YES
```

# 题解

## 作者：fzj2007 (赞：7)

~~都用 tarjan ，我偏要 floyd~~。

### 题目描述

> 给定一个矩阵 $A$，问是否存在一个正整数 $k$ 使得 $A^k$ 的每个元素都大于 $0$。

### 算法思路

原题中保证了 $A_{i,j}\ge 0$，即每个数不是正整数就是 $0$。

回顾一下矩阵乘法的：

$$
C_{i,j}=\sum_{t=1}^n A_{i,t}\times B_{t,j}
$$

则可以知道 $A^k_{i,j}$ 不为 $0$ 的充要条件是存在一个 $t(1\le t\le n)$ 满足 $A^k_{i,t}$ 与 $A^k_{t,j}$ 不同时为 $0$。

由于如果 $A_{i,j}>0$，那么一定有 $A^k_{i,j}>0$，则可以将原矩阵化为一个 $01$ 矩阵。

于是想到了经过 $k$ 条边的最短路模型，如果 $A^k_{i,j}$ 为 $1$，则说明有一条从 $i$ 到 $j$ 的经过 $k$ 条边的路径。又由于题目保证 $A_{i,i}>0$，所以从 $i$ 到 $j$ 一定有一条经过小于等于 $k$ 条边的路径。

当 $k$ 足够大的时候，事实上 $A_{i,j}$ 反映出 $i$ 到 $j$ 是否有一条路径。

原题被化为原图任意两点是否能够互相到达。

使用 $\text{floyd+bitset}$ 传递闭包即可。

### 代码实现

```
#include<bits/stdc++.h>
using namespace std;
namespace IO{
    template<typename T>inline void read(T &x){
        x=0;
        char ch=getchar();
        bool flag=0;
        while(ch<'0'||ch>'9') flag=flag||(ch=='-'),ch=getchar();
        while(ch>='0'&&ch<='9') x=x*10+(ch^'0'),ch=getchar();
        if(ch!='.'){
            x=flag?-x:x;
            return;
        }
        double Base=0.1;
        while(ch<'0'||ch>'9') ch=getchar();
        while(ch>='0'&&ch<='9') x=x+Base*(ch^'0'),Base/=10.0,ch=getchar();
        x=flag?-x:x;
    }
    template<typename T>void prt(T x){
        if(x>9) prt(x/10);
        putchar(x%10+'0');
    }
    template<typename T>inline void put(char ch,T x){
        if(x<0) putchar('-'),x=-x;
        prt(x);
        putchar(ch);
    }
    const int DM[10]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
    inline void putd(char ch,double x,int w){
        if(x<0) putchar('-'),x=-x;
        if(!w){
            put(ch,(int)(x+0.5));
            return;
        }
        int prex=(int)x;
        x-=(int)x;
        x*=DM[w];
        x+=0.5;
        int nowx=(int)x,now=0;
        if(nowx>=DM[w]) nowx=0,prex++;
        put('.',prex);
        int xx=nowx;
        if(!xx) now=1;
        else while(xx) xx/=10,now++;
        now=w-now;
        while(now--) putchar('0');
        put(ch,nowx);
    }
    inline void putstr(string s){
        for(int i=0;i<s.length();i++) putchar(s[i]);
    }
}
using namespace IO;
#define N 2005
int n;
bitset<N>f[N];
int main(){
	read(n);
	for(int i=1;i<=n;i++)
		for(int j=1,x;j<=n;j++)
			read(x),f[i][j]=(x>0);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(f[j][i]) f[j]|=f[i];
	for(int i=1;i<=n;i++)
		if(f[i].count()!=n) return putstr("NO\n"),0;
	putstr("YES\n");
	return 0;
}
```

---

## 作者：Mihari (赞：6)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF402E)

# 题解

~~想了半天没想出来~~

**首先需要注意题目中一个十分重要的条件，就是 $a_{i,j}\ge 0$，这个条件是我们做出这道题的关键**，而我们需要做的，是判断是否存在 $k$ 使得 $A^k$ 是一个严格正矩阵，即使其每一项都大于 $0$.

首先，利用 $a_{i,j}\ge 0$，我们将矩阵中所有大于 $0$ 的元素都看成 $1$，这样做为什么是对的？考虑矩阵乘法，假如有这样一个算式
$$
A\times B=C
$$
其中，$A$ 是 $n\times m$ 的矩阵，$B$ 是 $m\times k$ 的矩阵，那么这个算式写成一般形式就是
$$
c_{i,j}=\sum_{k=1}^ma_{i,t}\times b_{t,j}
$$
也就是说，我们只需知道 $A$ 的第 $i$ 行和 $B$ 的第 $j$ 列对位乘起来之后求和是否大于 $0$ 即可，对于这道题，所有的 $a_{i,j}\ge 0$，也就是说我们并不在意其值是多少，只要有$A$ 的第 $i$ 行和 $B$ 的第 $j$ 列对位的某一位恰好同时大于 $0$，那么结果的这一位就一定大于 $0$.

转换之后，$A^k$ 这个严格正矩阵其实就是一个全 $1$ 矩阵，而我们输入的矩阵无疑是一个 $01$ 矩阵。

由 $01$ 矩阵，我们可以想到邻接矩阵，对于某一个邻接矩阵 $D$，如果 $d_{i,j}=1$ 则表示 $i,j$ 间有一条边，将其拓展，**对于 $D^p$，如果 $d'_{u,v}>0$，则说明 $u,v$ 之间存在 $d'_{u,v}$ 条长度为 $p$ 的路径。**

将其放到我们的 $A$ 上面来，如果 $A^k$ 是严格正矩阵，则说明其所有点之间都存在长度为 $k$ 的路径，**既然存在路径，则说明其一定是联通的**，那么我们只需要看一看原图——也就是 $A$ 这个邻接矩阵反映的图是否是一个连通图即可。

最后方法很简单，在 $A$ 上跑一边 $tarjan$ 缩点，看是否只有一个 $scc$ 即可。

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13540163.html
```



---

## 作者：来日方长 (赞：3)

根据邻接矩阵的性质，$A^k$的矩阵中$A(i,j)$若为1，则$ij$间存在一条长度为$k$的路径。

$A^k$若全部为大于0的整数，那么所有的点之间都有长度为$k$ 的路径且可以互相到达。

但关键并不是存在长度为$k$的路径，而是所有点之间可以相互到达，那就说明这张图是张强连通图。

所以，只需要用$tarjan$算一下图中强连通分量的个数是否为1就好了。

AC代码：

```cpp
#include<bits/stdc++.h>
#define reint register int
using namespace std;
const int N=2005;
struct E{
  int to,nxt;
}ed[N*N*2];int H[N*N*2],cnt;
stack<int>sta;
bool vis[N][N],flg=true,ins[N];int n,tmp;
int dfn[N],low[N],tot,num;
inline void add(int x,int y){
  cnt++;ed[cnt].to=y;ed[cnt].nxt=H[x];H[x]=cnt;
  return;
}
void tarjan(int x){
  dfn[x]=low[x]=++tot;
  ins[x]=true;sta.push(x);
  int u,k;
  for(reint i=H[x];i;i=ed[i].nxt){
    u=ed[i].to;
    if(!dfn[u]){tarjan(u);low[x]=min(low[x],low[u]);}
    else if(ins[u])low[x]=min(low[x],dfn[u]);
  }
  if(low[x]==dfn[x]){
    num++;
    do{
      k=sta.top();sta.pop();
      ins[k]=false;
    }while(x!=k);
  }
}
int main(){
  scanf("%d",&n);
  for(reint i=1;i<=n;i++)
  for(reint j=1;j<=n;j++){
    scanf("%d",&tmp);
    if(tmp)vis[i][j]=true;
    else flg=false;
  }if(flg){puts("YES");return 0;}
  for(reint i=1;i<=n;i++)
  for(reint j=1;j<=n;j++)
    if(vis[i][j])add(i,j);
  for(reint i=1;i<=n;i++)if(!dfn[i])tarjan(i);
  if(num==1)puts("YES");
  else puts("NO");
  return 0;
}

```

---

## 作者：我是逍逍 (赞：2)

首先，我们需要了解矩阵乘法的规则。两个矩阵，设为 $A, B$ ，其中 $A$ 的大小为 $n \times m$ ，$B$ 的大小为 $m \times p$ ，设 $C = A \times B$ ，则 $C$ 的每个元素的计算方式如下式： 
$$C_{i,j} = \sum_{k=1}^{m} A_{i,k} \times B_{k,j}$$
如上式，我们可以发现 $C$ 的大小为 $n \times p$ ， $C_{i,j}$ 是 $A$ 的第 $i$ 行和 $B$ 的第 $j$ 列对应相乘的结果。以上的运算便是矩阵乘法，记为 $C = A \times B$ 。  

题目中的矩阵大小都为 $n \times n$ ，也就意味着矩阵大小不随着运算而改变，始终都为 $n \times n$ 。记原矩阵为 $A$ ，则运算一次后的矩阵 $A^2 = A \times A$ 如下：
$$\begin{matrix}
{\Sigma_{k=1}^n A_{1,k} \times A_{k,1}} & {\Sigma_{k=1}^n A_{1,k} \times A_{k,2}} & {\cdots} & {\Sigma_{k=1}^n A_{1,k} \times A_{k,n}} \\
{\Sigma_{k=1}^n A_{2,k} \times A_{k,1}} & {\Sigma_{k=1}^n A_{2,k} \times A_{k,2}} & {\cdots} & {\Sigma_{k=1}^n A_{2,k} \times A_{k,n}} \\
{\vdots} & {\vdots} & {\ddots} & {\vdots} \\
{\Sigma_{k=1}^n A_{n,k} \times A_{k,1}} & {\Sigma_{k=1}^n A_{n,k} \times A_{k,2}} & {\cdots} & {\Sigma_{k=1}^n A_{n,k} \times A_{k,n}} \\
\end{matrix}$$
由于题目只要求最终 $A^k$ 为严格正矩阵，而且保证 $\forall A_{i,j} \geq 0$ ，因此我们可以将原矩阵处理一下，若 $A_{i,j} > 0$ 则记其为 $1$ ， 否则记为 $0$ ，以免运算时溢出。   
观察上矩阵，我们可以发现矩阵值互相传递，由此想到题目可用图论作答：若 ${A^k}_{i,j} > 0$ 则等价于 $(i,j)$ 存在单向边，最终判断 $n$ 个点是否同属于一个强连通分量即可。   
强连通分量的求解使用 Tarjan 算法，时间复杂度 $O(n + m)$ ，在本题中为 $O(n^2)$ 。  
代码如下，$cnt$ 为强连通分量的数量。题目数据量大，最好使用快速读入（代码中未使用）。  
```cpp
#include <iostream>
#include <vector>
#include <stack>

using namespace std;
const int Max = 2005;

int n, dfn[Max], low[Max], t, cnt, g[Max][Max];
bool is[Max];
stack<int> st;

void tarjan(int x) {
	dfn[x] = low[x] = ++t;
	st.push(x);
	is[x] = true;
	
	for (int y = 1; y <= n; y++)
		if (g[x][y]) {
			if (!dfn[y]) {
				tarjan(y);
				low[x] = min(low[x], low[y]);
			} else if (is[y])
				low[x] = min(low[x], dfn[y]);
		}
		
	if (dfn[x] == low[x]) {
		cnt++;
		int y;
		do {
			y = st.top();
			st.pop();
			is[y] = false;
		} while (x != y);
	}
}

int main() {
	ios::sync_with_stdio(false);
	
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) 
			cin >> g[i][j];
	
	for (int i = 1; i <= n; i++)
		if (!dfn[i])
			tarjan(i);
	
	cout << (cnt == 1 ? "YES" : "NO") << endl;
	return 0;
}
```


---

## 作者：封禁用户 (赞：2)

小蒟蒻的一大爱好：水题解 QωQ

# 题目
给出一张图，如果存在 $k(k\ge 0)$ 使得每对点之间都有长度为 $k$ 的路径，输出 $\tt YES$ ，否则输出 $\tt NO$ 。

重要性质：保证图中 __存在一个自环__。

# 思路
首先证明必要条件：整张图上的两个点原本就互相可达。

这是显然的，如果两个点之间没有路径，怎么可能存在长度为 $k$ 的路径呢？

然后证明充分条件：整张图上的两个点原本就互相可达。

这个不容易想到，因为此处必须利用那个神奇的性质。为什么一定要告诉你，有自环存在呢？

答案是，既然整张图上的两个点原本就互相可达，设自环存在于 $x$ ，那么 $a$ 到 $b$ 的路径可以是 $a\rightarrow\cdots\rightarrow x\rightarrow x\rightarrow\cdots\rightarrow x\rightarrow\cdots\rightarrow b$ ，也就是说先经过 $x$ 绕几圈再到达目的地。这条路径的存在性由上面的条件保证。

既然如此，路径长度充分大时（大于 $a\rightarrow\cdots\rightarrow x\rightarrow\cdots\rightarrow b$ 时），$a\rightarrow b$ 之间存在路径。

最终我们总结出了充要条件：__整张图上的两个点原本就互相可达__。

怎么判断？用 $\tt bfs$ 呗。如果 $s$ 能到达每个点，每个点也能到达 $s$ ，就满足该条件，否则不满足。取 $s=1$ 就行。

# 代码
```cpp
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
typedef long long int_;
inline int readint(){
	int a = 0; char c = getchar(), f = 1;
	for(; c<'0'||c>'9'; c=getchar())
		if(c == '-') f = -f;
	for(; '0'<=c&&c<='9'; c=getchar())
		a = (a<<3)+(a<<1)+(c^48);
	return a*f;
}

const int MaxN = 2005;

int n, a[MaxN][MaxN];
vector< int > q; bool vis[MaxN];
bool bfs(){
	/* 1 能到每个点吗？ */ ;
	q.push_back(1), vis[1] = 1;
	while(!q.empty()){
		int t = q.back();
		q.pop_back();
		for(int i=1; i<=n; ++i)
			if(!vis[i] && a[t][i]){
				vis[i] = true;
				q.push_back(i);
			}
	}
	for(int i=1; i<=n; ++i){
		if(!vis[i])
			return false;
		vis[i] = 0;
	}
	/* 每个点能到 1 吗？ */
	q.push_back(1), vis[1] = 1;
	while(!q.empty()){
		int t = q.back();
		q.pop_back();
		for(int i=1; i<=n; ++i)
			if(!vis[i] && a[i][t]){
				vis[i] = true;
				q.push_back(i);
			}
	}
	for(int i=1; i<=n; ++i){
		if(!vis[i])
			return false;
		vis[i] = 0;
	}
}

int main(){
	n = readint();
	for(int i=1; i<=n; ++i)
	for(int j=1; j<=n; ++j)
		a[i][j] = readint();
	puts(bfs() ? "YES" : "NO");
	return 0;
}
```

---

## 作者：__Hacheylight__ (赞：2)

跑一遍tarjan 

啥是tarjan

说到以Tarjan命名的算法，我们经常提到的有3个，其中就包括本文所介绍的求强连通分量的Tarjan算法。而提出此算法的普林斯顿大学的Robert E Tarjan教授也是1986年的图灵奖获得者（具体原因请看本博“历届图灵奖得主”一文）。

      首先明确几个概念。

强连通图。在一个强连通图中，任意两个点都通过一定路径互相连通。比如图一是一个强连通图，而图二不是。因为没有一条路使得点4到达点1、2或3。
强连通分量。在一个非强连通图中极大的强连通子图就是该图的强连通分量。比如图三中子图{1,2,3,5}是一个强连通分量，子图{4}是一个强连通分量。


   关于Tarjan算法的伪代码和流程演示请到我的115网盘下载网上某大牛写的Doc（地址：http://u.115.com/file/f96af404d2<Tarjan算法.doc>）本文着重从另外一个角度，也就是针对tarjan的操作规则来讲解这个算法。

   其实，tarjan算法的基础是DFS。我们准备两个数组Low和Dfn。Low数组是一个标记数组，记录该点所在的强连通子图所在搜索子树的根节点的Dfn值（很绕嘴，往下看你就会明白），Dfn数组记录搜索到该点的时间，也就是第几个搜索这个点的。根据以下几条规则，经过搜索遍历该图（无需回溯）和对栈的操作，我们就可以得到该有向图的强连通分量。

 

数组的初始化：当首次搜索到点p时，Dfn与Low数组的值都为到该点的时间。

堆栈：每搜索到一个点，将它压入栈顶。

当点p有与点p’相连时，如果此时（时间为dfn[p]时）p’不在栈中，p的low值为两点的low值中较小的一个。

当点p有与点p’相连时，如果此时（时间为dfn[p]时）p’在栈中，p的low值为p的low值和p’的dfn值中较小的一个。

每当搜索到一个点经过以上操作后（也就是子树已经全部遍历）的low值等于dfn值，则将它以及在它之上的元素弹出栈。这些出栈的元素组成一个强连通分量。

继续搜索（或许会更换搜索的起点，因为整个有向图可能分为两个不连通的部分），直到所有点被遍历。

   由于每个顶点只访问过一次，每条边也只访问过一次，我们就可以在O（n+m）的时间内求出有向图的强连通分量。但是，这么做的原因是什么呢？

 

   Tarjan算法的操作原理如下：

1.Tarjan算法基于定理：在任何深度优先搜索中，同一强连通分量内的所有顶点均在同一棵深度优先搜索树中。也就是说，强连通分量一定是有向图的某个深搜树子树。

2.可以证明，当一个点既是强连通子图Ⅰ中的点，又是强连通子图Ⅱ中的点，则它是强连通子图Ⅰ∪Ⅱ中的点。

这样，我们用low值记录该点所在强连通子图对应的搜索子树的根节点的Dfn值。注意，该子树中的元素在栈中一定是相邻的，且根节点在栈中一定位于所有子树元素的最下方。

3.强连通分量是由若干个环组成的。所以，当有环形成时（也就是搜索的下一个点已在栈中），我们将这一条路径的low值统一，即这条路径上的点属于同一个强连通分量。

4.如果遍历完整个搜索树后某个点的dfn值等于low值，则它是该搜索子树的根。这时，它以上（包括它自己）一直到栈顶的所有元素组成一个强连通分量。

5.by the way题里给的范围虽然大 但是内存限度也大啊 按那个大小开准是没错的==

```cpp
#include <bits/stdc++.h>
#define N 2000 + 10
using namespace std ;
int a[N][N];
int mark[2][N] ;
int n,num ; 
void dfs(int k,int pre)
{
	mark[k][pre]=true,num++ ;
	for (int i=1;i<=n;i++)
	if (!mark[k][i])
	if ((k && a[pre][i]) || (!k && a[i][pre])) dfs(k,i) ;
}
int main() 
{
	scanf("%d",&n) ;
	for (int i=1;i<=n;i++)
	for (int j=1;j<=n;j++)
	scanf("%d",&a[i][j]) ;
	dfs(0,1);dfs(1,1) ;
	printf("%s\n",num==2*n?"YES":"NO") ;
	return  0;
}
```

---

## 作者：do_while_true (赞：1)

orz 峰

由于不是正数就是 $0$，可以把正数看成 $1$，变成了 $01$ 矩阵。

邻接矩阵的 $k$ 次幂中，${A^k}_{i,j}$ 代表 $i$ 到 $j$ 是否有长度为 $k$ 的路径。

这个题变成了是否存在一个 $k$，使得任意两点之间都有长度为 $k$ 的路径，初始给的 $A$ 即为告诉你哪些点直接直接有边相连。

数据保证了 $\sum_{i=1}^n a_{i,i}>0$，也就是至少存在一个子环。

那么问题可以转化为给你一张点数为 $n$ 的有向图，询问是否两两强连通。因为一定存在一个自环，则可以把 $k$ 看作一个很大的数，如果让一个点走到另一个点的时候先走到那个自环的位置把多余的路程消耗完了，再走到目的地的点，即可看为任意两点都有长度为 $k$ 的路径。

点数 $\leq 2000$，边数 $\leq 2000^2$，直接 dfs 是 $\mathcal{O}(n^3)$ 的。考虑实际上是问整张图是否是一个 SCC，直接 Tarjan 缩点即可。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<stack>
#include<cstring>
typedef long long ll;
ll mod;
template <typename T> T Add(T x, T y) { return (x + y >= mod) ? (x + y - mod) : (x + y); }
template <typename T> T cAdd(T x, T y) { return x = (x + y >= mod) ? (x + y - mod) : (x + y); }
template <typename T> T Mul(T x, T y) { return x * y % mod; }
template <typename T> T Mod(T x) { return x < 0 ? (x + mod) : x; }
template <typename T> T Max(T x, T y) { return x > y ? x : y; }
template <typename T> T Min(T x, T y) { return x < y ? x : y; }
template <typename T> T Abs(T x) { return x < 0 ? -x : x; }
template <typename T> T chkmax(T &x, T y) { return x = x > y ? x : y; }
template <typename T>
T &read(T &r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = (r << 3) + (r <<1) + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
inline int lowbit(int x) { return x & (-x); }
int popcount(int x) { int sumq = 0;	while(x) x -= lowbit(x), ++sumq; return sumq; }
ll qpow(ll x, ll y) {
	ll sumq = 1;
	while(y) {
		if(y & 1) sumq = sumq * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return sumq;
}
const int N = 2010;
std::queue<int>q;
std::stack<int>st;
int n, m, a[N][N];
int dfn[N], low[N], icnt;
int va[N], val[N], blo[N], bnt, f[N];
bool vis[N];
//Edge----------------------------
int head[N], ent;
struct Edge {
	int next, to;
}e[N*N];
inline void add(int x, int y) {
	e[++ent].to = y; e[ent].next = head[x]; head[x] = ent;
}
//dfs-----------------------------
void dfs(int x) {
	dfn[x] = low[x] = ++icnt; st.push(x);
	for(int i = head[x]; i; i = e[i].next) {
		int v = e[i].to;
		if(blo[v]) continue;
		if(!dfn[v]) {
			dfs(v);
			low[x] = Min(low[x], low[v]);
		}
		else low[x] = Min(low[x], dfn[v]);
	}
	if(low[x] == dfn[x]) {
		++bnt;
		do {
			int top = st.top(); st.pop();
			val[bnt] += va[top];
			blo[top] = bnt;
			if(top == x) break;
		} while(true);
	}
}
void dfs2(int x) {
	if(vis[x]) return ;
	vis[x] = 1;
	for(int i = head[x]; i; i = e[i].next)
		dfs2(e[i].to);
}
signed main() { //freopen("in.txt", "r", stdin);
	read(n);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j) {
			read(a[i][j]);
			if(a[i][j] && i != j) add(i, j);
		}
	for(int i = 1; i <= n; ++i)
		if(!dfn[i])
			dfs(i);
	if(bnt == 1) puts("YES");
	else puts("NO");
	return 0;
}
```


---

## 作者：SamHJD (赞：0)

## [Strictly Positive Matrix](https://www.luogu.com.cn/problem/CF402E)

### 题意

给出矩阵 $A$ 求是否存在 $k$ 使 $A^k$ 的每个元素大于 $0$。

------------

### 解法

因为初始矩阵内所有数为非负，我们可以把所有大于 $1$ 的数视为 $1$，计算新矩阵时直接取 $\max$ 即可。

设 $A\times A$ 为 $C$，新计算方式如下：

$$C_{i,j}=\max\limits_{k=1}^{n}A_{i,k}\times A_{k,j}$$

不妨改变对 $C_{i,j}$ 的理解，$C_{i,j}$ 代表此时 $i,j$ 是否连通，而计算 $C_{i,j}$ 的过程便是找一个点 $k$ 使得 $(i,k),(k,j)$ 连通，便可确认 $i,j$ 连通。

$C=A^2$ 时 $C_{i,j}$ 表示 $i,j$ 是否经过最多一个点连通。同理，$C=A^3$ 时表示 $i,j$ 是否经过最多两个点连通。

我们只需判断在最终图中 $C_{i,j}$ 是否均为 $1$，即所有点强连通。于是可以在初始给出的邻接矩阵中建边，看是否所有点是一个强连通分量即可。

------------

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e3+10;
int n,a[N][N],id[N],head[N*N],ecnt;
struct E{
	int v,next;
}e[N*N*2];
void add(int u,int v){
	e[++ecnt]={v,head[u]};
	head[u]=ecnt;
}
int low[N],dfn[N],tim,inst[N],st[N],top,scc;
void tarjan(int u){
	dfn[u]=low[u]=++tim;
	inst[u]=1;st[++top]=u;
	for(int i=head[u];i;i=e[i].next){
		if(!dfn[e[i].v]){
			tarjan(e[i].v);
			low[u]=min(low[u],low[e[i].v]);
		}
		else if(inst[e[i].v]) low[u]=min(low[u],dfn[e[i].v]);
	}
	if(low[u]==dfn[u]){
		scc++;int x;
		do{
			x=st[top--];
			inst[x]=0;
		}while(x!=u);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			scanf("%d",&a[i][j]);
			if(a[i][j]) add(i,j);
		}
	}
	for(int i=1;i<=n;++i) if(!dfn[i]) tarjan(i);
	if(scc>1) printf("NO\n");
	else printf("YES\n");
	return 0;
}

```

---

## 作者：CRTL_xzh2009 (赞：0)

考虑矩阵 $A \times A$ 的意义。

定义 $B[i][j] =  {\textstyle \sum_{k=1}^{n}} A[i][k] \times A[k][j]$，$A[i][k] \times A[k][j]$ 非负当且仅当 $A[i][k]$ 和 $A[k][j]$ 非负。

如果以图论来理解 $A[i][j] > 0$，表示 $i$ 到 $j$ 有有向边；若 $A[i][j] = 0$，表示 $i$ 到 $j$ 无边。

$B[i][j]$ 表示是否存在长度为 $2$ 的路径从 $i$ 到 $j$。

$A^{k}$ 中 $A[i][j]$ 就代表从 $i$ 到 $j$ 有没有一条长度等于 $k$ 的路径。

此题本质上就是问根据所给矩阵建图，是否全图为一个强联通分量。

套 Tarjan 模板即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int dfn[500005],low[500005],cnt=0,h[500005]={-1},e[500005],ne[500005],vis[500005];
int in=0,oo=0;
stack<int> qq;
void add(int x,int y)
{
    e[++cnt]=y;
    ne[cnt]=h[x];
    h[x]=cnt;
}
void tarjan(int u)
{
    dfn[u]=low[u]=++in;
    vis[u]=1;
    qq.push(u);
    for(int i=h[u]; i!=-1; i=ne[i])
    {
        int y=e[i];
        if(dfn[y]==0)
        {
            tarjan(y);
            low[u]=min(low[u],low[y]);
        }
        else if(vis[y]==1)
            low[u]=min(low[u],dfn[y]);
    }
    if(dfn[u]==low[u])
    {
        oo++;
        int v;
        do
        {
            v=qq.top();
            qq.pop();
            vis[v]=0;
        }
        while(u!=v);
    }
}
int main()
{
    cnt=in=oo=0;
    int n;
    cin>>n;
    for(int i=1; i<=n; ++i)
        for(int j=1; j<=n; ++j)
        {
            int x;
            scanf("%d",&x);
            if(x!=0)
                add(i,j);
        }
    for(int i=1; i<=n; i++)
        if(dfn[i]==0)
            tarjan(i);
    if(oo==1)
        cout<<"YES\n";
    else
        cout<<"NO\n";
    return 0;
}
```


---

