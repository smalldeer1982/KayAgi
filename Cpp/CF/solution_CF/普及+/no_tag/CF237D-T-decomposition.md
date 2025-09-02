# T-decomposition

## 题目描述

给定一棵 $n$ 个结点的无根树 $s$，它的点集为 $V$。你需要构造出一棵无根树 $t$，每个结点 $x_i$ 是 **$V$ 中的一个非空子集**。这棵树需要满足下列要求：

- 所有 $x_i$ 的并集为 $V$。
- 对于树 $s$ 中的任意一条边 $(a,b)$，在 $t$ 中都能够找到一个集合 $x$ 使得 $a,b\in x$。
- 对于树 $s$ 中的任意一个点 $a$，所有在 $t$ 中包含了 $a$ 的集合构成了一个连通块。

设你构造出来的树 $t$ 的价值为 $t$ 中最大集合的大小。你的构造需要满足在价值最小的前提下，集合个数最少。$1\le n\le 10^5$。

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
1
2 1 2
```

## 样例 #2

### 输入

```
3
1 2
2 3
```

### 输出

```
2
2 1 2
2 2 3
1 2
```

## 样例 #3

### 输入

```
4
2 1
3 1
4 1
```

### 输出

```
3
2 2 1
2 3 1
2 4 1
1 2
2 3
```

# 题解

## 作者：liyichun001 (赞：6)

## 题解:
首先 ,先看一下题目,

 会不会觉得$\huge\text{特别想......AFO???}$
# $\color{blue}\text{But:没关系}$
题意$\huge\color{red}\text{虽然十分复杂}$，但读明白了这个题就$\color{CornFlowerblue}\text{十分简(hao)单(xiao)}$，题目本质上就是**构造一棵新的树**，使得树上的新结点是之前树上的某条边，权值是新点中原点里编号最大的那个的编号，并且构建出的树权值最小

由于要求**权值最小**，那么我们尽量让新点中最大的那个编号数更小，考虑每两个点组成一个新结点，**这样一来，可以保证构建出的新树是权值最小的**

考虑新树的点，由于原来的树有 $n-1$ 条边，那么新树就有 $n-1$ 个点，每个点是原树的一条边，每输入一条边，就直接输出对应的点的编号

再考虑新树的边，在输入的时候，将原来的边的点与当前点的编号$i$分别$\color{red}\text{构建一条新边}$即可，最后只需要将相邻两边输出即可
### 上代码：
```cpp
#include<bits/stdc++.h>
const int N = 500000+5;
using namespace std;
vector<int> G[N];
int main(){
    int n;
    scanf("%d",&n);
    printf("%d\n",n-1);
    for(int i=1;i<=n-1;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        printf("2 %d %d\n",x,y);
        x--;
        y--;
        G[x].push_back(i);
        G[y].push_back(i);
    }
    for(int i=0;i<=n-1;i++)
        for(int j=0;j<G[i].size()-1;j++)
            printf("%d %d\n",G[i][j],G[i][j+1]);
    return 0;
}
```
所以说这道题~~特别的水~~

祝大家$\begin{matrix}\underbrace{1+2+\cdots+\infty}\\rp++\end{matrix}$ 

---

## 作者：迟暮天复明 (赞：2)

思考+写代码的时间比读题时间短。

显然需要 $n-1$ 个点，每个点代表原图上的一条边。

至于构造，不难证明所有新加进去的点只需要任意挂在图中包含相应数字的连通块下就可以。实现的话可以维护每个数字所在连通块的点的编号，然后对于扫一遍去加边即可。

[提交记录](https://codeforces.com/contest/237/submission/276367877)

---

## 作者：LHLeisus (赞：2)

[原题链接](https://codeforces.com/problemset/problem/237/D)

[更好的阅读体验](https://www.cnblogs.com/LHLeisus/p/17765213.html)

![](https://img.zshfoj.com/6f038c0962a4d7c38ad442a82340374aa6dd8072b4a32703aad36ab1451b2841.png)
# 链式前向星，他来了

- 通过观察发现，每个集合的大小最小为 $2$，显然我们需要构造一种方案使得每一个集合的大小都为 $2$，这样是最优的。
- 每个集合大小为 $2$，等价于把每条边转换成新树上的一个点，一共 $n-1$ 边，对应 $n-1$ 个集合，每个集合的点对在 dfs 的时候输出每一条边的两个端点即可。
- 对于第三问，一种合法的构造方案是：
  - 对于一个节点 $u$ 和它的儿子 $v$，让 $\{u,v\}$ 与 $\{fa_u,u\}$ 连边。注意根节点需要特殊处理，因为不存在 $fa_{root}$。
  - 具体操作是记录一个 $id$，表示 $\{fa_u,u\}$ 的编号，用 dfs 实现编号的向下传递，每次在 $id$ 和 ${\{u,v\}}$ 之间建边。
  - 对于根节点，我们让 $id$ 初值为 $0$，并且在 $id$ 为零的时候不进行加边操作，而是将 $\{root,v\}$ 的编号赋值给 $id$，也就是将根节点和其他儿子组成的集合都与根节点和第一个儿子的集合连边，仍能保证第三条性质。

# code
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
#include<utility>
#include<vector>
#include<queue>
#include<bitset>
#include<map>
#define FOR(i,a,b) for(register int i=a;i<=b;i++)
#define ROF(i,a,b) for(register int i=a;i>=b;i--)
#define mp(a,b) make_pair(a,b)
#define pll pair<long long,long long>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
inline int read();
typedef long long ll;
typedef double db;
const int N=1e5+5;
const int INF=0x3f3f3f3f;
int n,m,k;
struct E{
	int to,nex;
}edge[N<<1];
int head[N],cnt=0;
void add(int u,int v){
	edge[++cnt]=(E){v,head[u]};
	head[u]=cnt;
}
void dfs(int u,int fa){
	for(int i=head[u];i;i=edge[i].nex){
		int v=edge[i].to;
		if(v==fa) continue;
		printf("2 %d %d\n",u,v);
		dfs(v,u);
	}
}
map<pii,int>pos;
int Pos=0;
int toNum(int u,int v){
	if(pos.find(mp(u,v))==pos.end()){
		pos[mp(u,v)]=++Pos;
	}
	return pos[mp(u,v)];
}
void dfs1(int u,int fa,int id){
	for(int i=head[u];i;i=edge[i].nex){
		int v=edge[i].to;
		if(v==fa) continue;
		if(id!=0) printf("%d %d\n",id,toNum(u,v));
		else id=toNum(u,v);
		dfs1(v,u,toNum(u,v));
	}
}
int main()
{
	n=read();
	FOR(i,1,n-1){
		int u=read(),v=read();
		add(u,v);
		add(v,u);
	}
	printf("%d\n",n-1);//第一问 
	dfs(1,0);//第二问 
	dfs1(1,0,0);//第三问 
	return 0;
}


inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f*x;
}
```


---

## 作者：一只小咕咕 (赞：0)

[更好的阅读体验](https://www.cnblogs.com/yzxgg/p/solution-cf237d.html)

### 思路

构造 $k$ 个集合，使这些集合满足以下性质：

- 集合的并集为 $V$。

- 对于树 $s$ 中的任意一条边 $(a,b)$，都能在 $k$ 个集合中找到一个集合 $x$ 使得 $a,b\in x$。

- 对于树 $s$ 中的任意一个点 $a$，所有在 $k$ 个集合中包含了 $a$ 的集合构成了一个连通块。

构造出来的价值为最大集合的大小。需要求出满足在价值最小的前提下，集合个数最少。

我们再把以上性质和要求进一步结合起来看，就不难发现这几个性质：

1. 每个集合大小都应为 $2$。

2. 每个集合其实就是就是原树的一条边。

如果要把这 $k$ 个集合连接起来，所以那就应保证是相邻的两个边连接。

具体如何处理呢，很自然的我们会想到用邻接表进行处理，因为在邻接表重，相邻的两个边就是 $g_{i,j}$ 和 $g_{i,j+1}$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
inline int read();
int n;
vector<int> g[N];
int main()
{
	n=read();
	printf("%d\n",n-1);
	for(int i=1;i<n;i++)
	{
		int a,b;
		a=read();b=read();
		printf("2 %d %d\n",a,b);
		g[a].push_back(i);
		g[b].push_back(i);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<g[i].size()-1;j++)
		{
			printf("%d %d\n",g[i][j],g[i][j+1]);
		}
	}	
	return 0;
}

inline int read()
{
	int x=0,f=1;
	char ch;
	ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-') f=-f;ch=getchar();}
	while(ch<='9'&&ch>='0')
	{
		x=(x<<1)+(x<<3)+(ch&15);
		ch=getchar();
	}
    return x*f;
}
```

---

