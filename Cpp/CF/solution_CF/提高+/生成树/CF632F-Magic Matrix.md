# Magic Matrix

## 题目描述

You're given a matrix $ A $ of size $ n×n $ .

Let's call the matrix with nonnegative elements magic if it is symmetric (so $ a_{ij}=a_{ji} $ ), $ a_{ii}=0 $ and $ a_{ij}<=max(a_{ik},a_{jk}) $ for all triples $ i,j,k $ . Note that $ i,j,k $ do not need to be distinct.

Determine if the matrix is magic.

As the input/output can reach very huge size it is recommended to use fast input/output methods: for example, prefer to use scanf/printf instead of cin/cout in C++, prefer to use BufferedReader/PrintWriter instead of Scanner/System.out in Java.

## 样例 #1

### 输入

```
3
0 1 2
1 0 2
2 2 0
```

### 输出

```
MAGIC
```

## 样例 #2

### 输入

```
2
0 1
2 3
```

### 输出

```
NOT MAGIC
```

## 样例 #3

### 输入

```
4
0 1 2 3
1 0 3 4
2 3 0 5
3 4 5 0
```

### 输出

```
NOT MAGIC
```

# 题解

## 作者：是个汉子 (赞：11)

[洛谷传送门](https://www.luogu.com.cn/problem/CF632F)	[CF传送门](http://codeforces.com/problemset/problem/632/F)

### Solution

前面两个 $O(n^2)$ 暴力大家都会，就不多说了。

现在思考第三个条件怎么办？

第三个条件是 $a_{i,j}\leq \max(a_{i,k},a_{j,k})$ ，进一步变形可得：
$$
a_{i,j}\leq \max(a_{i,k},a_{k,j})\leq\max(a_{i,k},\max(a_{k,l},a_{l,j}))=\max\{a_{i,k},a_{k,l},a_{l,j}\}
$$
我们设此时已满足 $a_{i,j}=a_{j,i}$ ，那么我们将可以将魔法矩阵看作一个邻接矩阵，进而将这个矩阵看作一个无向图。

如果从 $i$ 到 $j$ 存在一条路径，上面的每一条边都满足 $<a_{i,j}$ ，那这条路径的 $\max<a_{i,j}$ ，就和上面变形之后的第三个条件冲突了。

~~本人画图水平为 $0$ ，所以请大家自己在大脑画图(oﾟvﾟ)ノ~~

那么我们就把判断第三个条件的方式转化为了判断路径。

将判断条件再精简一些——**所有权值小于 $a_{i,j}$ 的边构成的图上 $i,j$ 不联通**

不连通？权值？kruskal最小生成树？

我们在进行这张无向图的最小生成树过程中，来判断条件即可。

时间复杂度： $O(n^2\log n^2)$ 

小细节：我在代码中，并没有进行 $a_{i,j}=a_{j,i}$ 的判断。请读者自行思考为什么，这里就不说了。

### Code

```c++
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
const int N=2510;
int n;
struct node{
    int x,y,val;
    bool operator < (const node &x) const {
        return val<x.val;
    }
}a[N*N];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

int fa[N];
inline int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

inline void kruskal(){
    sort(a+1,a+n*n+1);
    a[n*n+1].val=-1;
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int l=1,r=0;l<=n*n;l=r+1){
        while(a[r+1].val==a[l].val) ++r;
        if(a[l].val!=0)
            for(int i=l;i<=r;i++)
                if(find(a[i].x)==find(a[i].y)){
                    puts("NOT MAGIC");
                    return ;
                }
        for(int i=l;i<=r;i++)
            fa[find(a[i].x)]=find(a[i].y);
    }
    puts("MAGIC");
}

inline int idx(int x,int y){
    return (x-1)*n+y;
}

int main(){
    n=read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            a[idx(i,j)].val=read();
            a[idx(i,j)].x=i; a[idx(i,j)].y=j;
            if(i==j&&a[idx(i,j)].val){
                puts("NOT MAGIC");
                return 0;
            }
        }
    kruskal();
    return 0;
}
```

Hi~ o(*￣▽￣*)ブ

上文给读者留下的问题还是说说的。

现在回到那个问题：

设此时不满足条件二的是 $a_{i,j}\not =a_{j,i}$ 且 $a_{i,j}<a_{j,i}$ 

如果 $a_{i,j}$ 满足第三个条件，在判断完 $a_{i,j}$ 时， $i,j$ 就已经被连接了。当判断 $a_{j,i}$ 时， $a_{i,j}$ 必定小于 $a_{j,i}$ 。

最后再讲一个有意思的小性质：

因为 $a_{i,j},a_{i,k},a_{k,j}$ 构成一个三元环。设 $a_{i,j}$ 为这里面的最大值，那么可得 $a_{i,j}\geq \max(a_{i,k},a_{k,j})$ ，题目给了 $a_{i,j}\leq \max(a_{i,k},a_{k,j})$ ，所以 $a_{i,j}=\max(a_{k,j},a_{i,k})$ 。

也就是说每一个三元环中都会有两个相等的边，且这两个边不小于剩的那个边ヾ(^▽^*)))



---

## 作者：nekko (赞：9)

考虑暴力模拟

将权值从小到大排序，然后依次填入（填入表示 $1$，未填入表示 $0$）

如果 $(i,j)$ 合法，当且仅当第 $i$ 行和第 $j$ 行对应位置都至少有一个 $0$ 才合法，判断完合法后就把所有相等权值插入即可

时间复杂度 $O(\frac{n^3}{w})$

``` cpp
#include "bits/stdc++.h"
using namespace std;

const int N = 2510;

int n, a[N][N];

void YES() {
    puts("MAGIC");
    exit(0);
}

void NO() {
    puts("NOT MAGIC");
    exit(0);
}

#define yes YES()
#define no NO()

bitset<N> f[N];

struct T { int x, y; } p[N * N];

bool operator < (T i, T j) {
    return a[i.x][i.y] < a[j.x][j.y];
}
int top;

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            scanf("%d", &a[i][j]);
            p[++ top] = (T) { i, j };
        }
    }
    sort(p + 1, p + 1 + top);
    // (1)
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            if(a[i][j] != a[j][i]) {
                no;
            }
        }
    }
    // (2)
    for(int i = 1 ; i <= n ; ++ i) {
        if(a[i][i]) {
            no;
        }
    }
    // (3)
    for(int i = 1 ; i <= top ; ) {
        int j = i;
        while(j + 1 <= top && a[p[j].x][p[j].y] == a[p[j + 1].x][p[j + 1].y]) ++ j;
        for(int k = i ; k <= j ; ++ k) {
            if((f[p[k].x] & f[p[k].y]).any()) {
                no;
            }
        }
        for(int k = i ; k <= j ; ++ k) {
            f[p[k].x][p[k].y] = 1;
        }
        i = j + 1;
    }

    yes;
}
```

---

## 作者：chenxia25 (赞：8)

先讲一个暴力做法。

前两个条件直接跑。最后一个条件，就是说在 $i,j$ 这两列中，画 $n$ 条水平线经过的两个位置，不能全部 $<a_{i,j}$。这个事情可以用 `bitset` 来优化。我们将 $a_{i,j}$ 从小到大排序，实时在 `bitset` 里更新 $<a_{i,j}$ 的，然后 `bitset` `&` 一下即可。

复杂度三方除以 $w$。

---

然后是正解。

注意到前两条限制满足了，这个矩阵可以看作一个邻接矩阵，值是边权。于是试图往图论去转化（一般转化到图论都是很需要思维的，例如某 flip）。

我们将第三条稍微转化一下，将 $a_{j,k}\leq\max(a_{j,o},a_{k,o})$ 代入可得 $a_{i,j}\leq\max(a_{i,j},a_{j,o},a_{k,o})$。代入更多次可以得到一个等价条件：$a_{i,j}$ 不是任意一个包含 $(i,j)$ 的环上的严格最大值。

这跟 MST 的某些性质很像：树边不是任意一个包含它自身的加上一条非树边形成的环上的严格最大值。于是我们考虑求出 MST，之后怎么做呢。那么显然树边都不需要被检查了，检查非树边的时候，直觉告诉我们应该检查以它为两端的树上路径的 $\max$。这很好证明：必要性显然的吧；充分性呢，可以归纳证，$x\to y$ 的路径中，一定是树上路径的边 $\max$ 非严格最小。

求最小生成树呢，有 $m=n^2$，那么 Kruskal 是 $\mathrm O(m\log m)$，Prim 是 $\mathrm O\!\left(n^2\right)$。可见在这个完全图中，反而是 Prim 更优了。

~~（蒟蒻第一次写 Prim 呢，请多多指教）~~u1s1 Prim 还真是巨好写。

**_code: _**[Kruskal](https://www.luogu.com.cn/paste/4zsmfwxh) [Prim](https://www.luogu.com.cn/paste/1zu5c1ve)

---

## 作者：hxhhxh (赞：6)

## 大意

给你一个 $ n \times n $ 的矩阵 $ A $ ，求它是否满足以下条件：

+ 对于 $ 1 \leq i \leq n $ ， $ A_{i,i} = 0 $ ；
+ 对于 $ 1 \leq i,j \leq n $ ， $ A_{i,j} = A_{j,i} $ ；
+ 对于 $ 1 \leq i,j,k \leq n $ ， $ A_{i,j} \leq \max(A_{i,k},A_{j,k}) $ 。

## 思路

前两个条件，可以分别 $ O(n) $ 和 $ O(n^2) $ 判完。

仔细看，会发现， $ A $ 可以代表一个完全图的邻接矩阵，第三个条件的验证就可以往这边想。

将第三个条件变形，可以得到：

$$ A_{i,j} \leq \max(A_{i,k},A_{k,j}) \leq \max(A_{i,k},\max(A_{k,l},A_{l,j})) = \max(A_{i,k},A_{k,l},A_{l,j}) $$

以此类推，可以得到

$$ A_{i,j} \leq \max(A_{i,t_1},A_{t_1,t_2},\dots,A_{t_k,j}) $$

即边 $ i,j $ 所在的每一个环除 $ A_{i,j} $ 之外的最大权值不小于 $ A_{i,j} $ 。

可以从小到大依次加入所有的边并维护连通性（暂不考虑两边权值相同）。如果加入时这条边两端点已经联通，说明加上这条边后会形成一个环，并且这个环去掉该边后最大权值小于该边的权值，不符合条件。

现在考虑多边权值相同的情况。每一条这样的边互不影响，所以可以先统一各自判联通性，然后再统一加入。

如果一直加到最后一条边都没有不符合条件，那么它就是符合条件的。

时间复杂度 $ O(n^2 \log n^2) $ ，要带上并查集的常数。

## 代码

代码不长。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[2505][2505],f[2505],cnt;
struct edge{
	int u,v,w;
}e[6250006];
int find(int x){
	return f[x]==x?x:f[x]=find(f[x]);
}
bool cmp(edge a,edge b){
	return a.w<b.w;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++) if(a[i][i]!=0) goto NO;
	for(int i=1;i<=n;i++) for(int j=1;j<i;j++) if(a[i][j]!=a[j][i]) goto NO;
	for(int i=1;i<=n;i++) for(int j=1;j<i;j++) e[++cnt]=(edge){i,j,a[i][j]};
	sort(e+1,e+cnt+1,cmp);
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1;i<=cnt;){
		int t=i;
		while(e[i].w==e[t].w&&t<=cnt) t++;
		t--;
		for(int j=i;j<=t;j++) if(find(e[j].u)==find(e[j].v)) goto NO;
		for(int j=i;j<=t;j++) f[find(e[j].u)]=find(e[j].v);
		i=t+1;
	}
	printf("MAGIC");
	return 0;
	NO:;
	printf("NOT MAGIC");
	return 0;
}
```

---

## 作者：crpboy (赞：6)

这里介绍一种$O(n^2)$做法，目前是最优解rk2

对于给定的矩阵，首先跑一遍$O(n)$和$O(n^2)$暴力解决前两问，此时的矩阵满足了一个无自环的无向图。

不难证明，在最小生成树上的点一定满足题目条件3给定的要求，即条件3与最小生成树有关。因此我们只需要记录每个点在最小生成树上的父亲，然后枚举任意两个点，将深度较大的点的父亲作为k，判断这种情况下的k是否合法就可以了。$O(n^2)$

![qwq](https://cdn.luogu.com.cn/upload/pic/53179.png)

自己感性理解一下啦~

~~AC~~有毒の代码
```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;

#define dd ch=getchar()
inline int read()
{
	int x=0;bool f=false;char dd;
	while(!isdigit(ch)){f|=ch=='一';dd;}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);dd;}
	return f?-x:x;
}
#undef dd
void write(int x)
{
	if(x<0)putchar('一'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+48);
}

const int N=2505,INF=0x7fffffff;
int n;
int a[N][N];

int fa[N],d[N];//fa[i]表示i节点在最小生成树上的父亲 
bool vis[N];
inline void prim()//稠密图用prim跑最小生成树 
{
	for(int i=2;i<=n;i++)fa[i]=1,d[i]=a[1][i];
	memset(vis,false,sizeof(vis));vis[1]=true;
	int k,minn;
	for(int tot=2;tot<=n;tot++)
	{
		minn=INF;
		for(int i=1;i<=n;i++)
			if(minn>d[i]&&!vis[i])
				minn=d[i],k=i;
		vis[k]=true;
		for(int i=1;i<=n;i++)
			if(a[k][i]<d[i]&&!vis[i])
				d[i]=a[k][i],fa[i]=k;//更新d的同时记录父节点 
	}
}

int dep[N];
void getdep(int x)
{
	if(!dep[fa[x]])getdep(fa[x]);
	dep[x]=dep[fa[x]]+1;
}

int main()
{
	n=read();
	for(re int i=1;i<=n;i++)
		for(re int j=1;j<=n;j++)
			a[i][j]=read();
	for(re int i=1;i<=n;i++)
		if(a[i][i])
			return puts("NOT MAGIC"),0;
	for(re int i=1;i<=n;i++)
		for(re int j=i+1;j<=n;j++)
			if(a[i][j]!=a[j][i])
				return puts("NOT MAGIC"),0;
	prim();
	dep[1]=1; 
	for(re int i=2;i<=n;i++)
		if(!dep[i])
			getdep(i);//求以1节点为根的最小生成树上的每个节点的深度 
	for(re int i=1;i<=n;i++)
		for(re int j=i+1;j<=n;j++)//枚举最小生成树上的两个点 
		{
			int x=i,y=j;
			if(dep[x]<dep[y])swap(x,y);//保证x的深度大于y
			if(a[x][y]>max(a[fa[x]][y],a[fa[x]][x]))//与最小生成树不符
			  	return puts("NOT MAGIC"),0;
		}
	return puts("MAGIC"),0;
}
```
---
题外话：这道题是我们模拟赛的时候出的，不过削弱了数据导致$O(n^3)$可以水过去，结果全场$AC$。$2333$

---

## 作者：应吟吟 (赞：5)

# 暴力

当看到$n≤2500$和5000ms/512MB的时空限制时，

我就想到 ~~开花~~ 暴力(看到iki9奆佬的暴力之后，我深深地感受到了我是多么地菜)

这道题的暴力其实比较好打，按着题意打就可以了，

我的是 $ O(n^3) $ 暴力，所以我的暴力这道题并过不去~~,那我打出来干什么呢？~~仅供欣赏，不做讲解(同样打 $ O(n^3) $ 暴力的同学可以去[这里](https://www.luogu.org/problemnew/show/U64332)交一下，题目有一点小魔改，需要改一下程序的)

```cpp
#pragma GCC optimize(3)
#include<bits/stdc++.h>

using namespace std;

const int FFF=2500+5;

int n;
int a[FFF][FFF];

int main()
{
    ios::sync_with_stdio(false);
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            scanf("%d",&a[i][j]);
        }
    }
    for(int i=0;i<n;++i)
    {
        if(a[i][i]!=0)
        {
            puts("NOT MAGIC");
            return 0;
        }
    }
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<i+1;++j)
        {
            if(i!=j)
            {
                if(a[i][j]!=a[j][i])
                {
                    puts("NOT MAGIC");
                    return 0;
                }
            }
        }
    }
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            if(i!=j)
            {
                for(int k=0;k<n;++k)
                {
                    if(a[i][j]>max(a[i][k],a[k][j]))
                    {
                        puts("NOT MAGIC");
                        return 0;
                    }
                }
            }
        }
    }
    puts("MAGIC");
    return 0;
}

```

***

# ~~应该是~~正解~~吧~~

我们看一下本题的三个条件

1. 对于每一个$i,j,a_{i,j}=a_{j,i}$(在矩阵中就是左下角的数和右上角的数对称相等)
2. 对于每一个$i,a_{i,i}=0$(在矩阵中就是对角线都为 0)
3. 对于每一个$i,j,k,a_{i,j}≥max(a_{i,k},a_{k,j})$(在矩阵中就是对于任意一个格子$(i,j)$要满足对于任意的 $k$,$a_{i,j}≥max(a_{i,k},a_{k,j})$,k 为$1$~$n$中的任意数，可以与$i,j$相等)

是不是看起来有一点眼熟？

1. $a_{i,j}=a_{j,i}$,表示无向图
2. $a_{i,i}=0$,表示无自环
3. $a_{i,j}≥max(a_{i,k},a_{k,j})$,表示最小生成树

所以，这道题可以用最小生成树去写。

复杂度$O(n^2)$,可以$*$过此题

***

## 具体写法

第一个和第二个条件直接$O(n^2)$判断过去就好了，不表

我们重点讲然如何判断第三个条件(敲黑板)

怎么判断这个矩阵是不是最小生成树呢？

我们先把它看做一个邻接矩阵，

建立一个完全图，

如果这个图是的任一个生成树都是最小生成树的话，

则满足题意，输出“MAGIC”。

那么重点在于如何去证明这个完全图的任一个生成树都是最小生成树。

我们可以看一下下面的图

![](https://i.loli.net/2019/03/04/5c7cbdb58955f.png)

如果$max(a,b)≤c$,那么如果按照最小生成树的方法，应该选择连接$B-A-C$才是正确的连法，

否则这个完全图就不满足题意了。

下面是判断第三个条件的代码

```cpp
for(int i=0;i<n;++i)
{
    fa[i]=1;
    dis[i]=a[1][i];
}
us[1]=1;
while(true)
{
    j=-1;
    for(int i=0;i<n;++i)
    {
        if(!us[i]&&(j==-1||dis[i]<dis[j]))
        {
            j=i;
        }
    }
    if(j==-1)
    {
        break;
    }
    us[j]=1;
    for(int i=0;i<n;++i)
    {
        if(!us[i]&&a[j][i]<dis[i])
        {
            dis[i]=a[j][i];
            fa[i]=j;
        }
    }
}
d[1]=1;
for(int i=0;i<n;++i)
{
    if(!d[i])
    {
        getf(i);
    }    
}
for(int i=0;i<n;++i)
{
    for(int j=i+1; j<=n; j++)
    {
        x=i;
        y=j;
        if(d[y]>d[x])
        {
            swap(x,y);
        }
        if(a[x][y]>a[fa[x]][x]&&a[x][y]>a[fa[x]][y])
        {
            printf("NOT MAGIC");
            return 0;
        }
    }
}
```

***

## ~~献上我丑陋的AC~~代码

```cpp
#pragma GCC optimize(3)
#include<bits/stdc++.h>

using namespace std;

const int L=1000000;
char LZH[L];
char *SSS,*TTT;
inline char gc()
{
    if (SSS==TTT) TTT=(SSS=LZH)+fread(LZH,1,L,stdin);
    return *SSS++;
}
inline int read()
{
    int x=0;
    char c=gc();
    for (;c<'0'||c>'9';c=gc());
    for (;c>='0'&&c<='9';c=gc())
        x=(x<<1)+(x<<3)+c-48;
    return x;
}

template < class T > inline void write(T x)
{
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + 48);
}

const int FFF=2500+5;

int n,j,x,y,a[FFF][FFF],fa[FFF],us[FFF],dis[FFF],d[FFF];

void getf(int x)
{
    if(!d[fa[x]])getf(fa[x]);
    d[x]=d[fa[x]]+1;
}

int main()
{
    n=read();
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            a[i][j]=read();
            if(i==j&&a[i][j]！=0)
            {
                puts("NOT MAGIC");
                return 0;
            }//判断第一个条件
            if(i>j&&a[i][j]！=a[j][i])
            {
                puts("NOT MAGIC");
                return 0;
            }//判断第二个条件
        }
    }
    for(int i=0;i<n;++i)
    {
        fa[i]=1;
        dis[i]=a[1][i];
    }
    us[1]=1;
    while(true)
    {
        j=-1;
        for(int i=0;i<n;++i)
        {
            if(!us[i]&&(j==-1||dis[i]<dis[j]))
            {
                j=i;
            }
        }
        if(j==-1)
        {
            break;
        }
        us[j]=1;
        for(int i=0;i<n;++i)
        {
            if(!us[i]&&a[j][i]<dis[i])
            {
                dis[i]=a[j][i];
                fa[i]=j;
            }
        }
    }
    d[1]=1;
    for(int i=0;i<n;++i)
    {
        if(!d[i])
        {
            getf(i);
        }
    }
    for(int i=0;i<n;++i)
    {
        for(int j=i+1; j<=n; j++)
        {
            x=i;
            y=j;
            if(d[y]>d[x])
            {
                swap(x,y);
            }
            if(a[x][y]>a[fa[x]][x]&&a[x][y]>a[fa[x]][y])
            {
                printf("NOT MAGIC");
                return 0;
            }
        }
    }
    puts("MAGIC");
    return 0;
}

```



---

## 作者：STDquantum (赞：2)

链接：[CF632F Magic Matrix](https://www.luogu.com.cn/problem/CF632F)。

本篇题解旨在总结一下现有题解做法，并讲解一些代码实现上的细节。

题目中前两个条件可以暴力枚举判断，不说。

第三个条件目前有两大种解法，其一是 bitset 优化暴力，另一个是两种最小生成树。

---

先来说朴素的暴力怎么做：发现 $a_{i,j}\le\max(a_{i,k},a_{k,j})$ 这个条件由于 $a_{i,j}=a_{j,i}$ 的存在等价于 $a_{i,j}\le\max(a_{i,k},a_{j,k})$，若将 $a_{i,j}$ 按权值排序后，则只需检查第 $i$ 与第 $j$ 行是否有同时小于 $a_{i,j}$ 的位置。这个过程是 $\mathcal{O}(n^3)$ 的。

发现只需验证其是否存在，可以用 bitset 加速比较，这样复杂度就除了一个 $w=64$ 或 $w=32$，最坏情况大约是 $5\times 10^8$，但是常数不大，足以通过此题。

---

最小生成树是什么解法呢？

首先若前两个题目条件满足，则给出的矩阵可以看做邻接矩阵，$a_{i,j}$ 代表 $i$ 到 $j$ 的边权，这个矩阵也就代表了一张完全图。

可以发现 $a_{i,j}\le\max(a_{i,k},a_{k,j})\le\max(a_{i,k},\max(a_{k,l},a_{l,j}))=\max(a_{i,k},a_{k,l},a_{l,j})$，从这里类推，可以任意选择一个 $m$ 与 $k_1,k_2,k_3,\dots,k_m$，都要满足 $a_{i,j}\le\max(a_{i,k_1},a_{k_1,k_2},\dots,a_{k_m,j})$。

不难发现这个式子的含义：$a_{i,j}$ 不大于 $i$ 到 $j$ 之间任意一条路径的最大边权。

反向转化一下，若无法满足这个条件，说明 $i$ 到 $j$ 之间每条边的边权都小于 $a_{i,j}$。

而我们不能让这个情况存在，因此权值小于 $a_{i,j}$ 的路径不能使 $i$ 和 $j$ 连通。

也就是 $a_{i,j}$ 使得 $i,j$ 连通，$a_{i,j}$ 还是 $i$ 到 $j$ 上所有路径最大边权的最小边权，那 $a_{i,j}$ 就是最小生成树上的边。

可能会有人质疑：若要满足每条边都是最小生成树上的边，那不就不是最小生成“树”了吗？

事实上，如样例一的 $\texttt{MAGIC}$ 矩阵，其等价完全图是这个样的：

![](https://gitee.com/stdquantum/STDquantumImages/raw/master/images/202010271.png)

其中 $\{(1,3),(1,2)\}$ 是最小生成树，$\{(2,3),(1,2)\}$ 也是最小生成树，这与每条边都在最小生成树上不冲突。

但是由于我们可能需要建出不同最小生成树，因此不能不考虑相同权值之间的影响（Kruskal 需要考虑，Prim 这种就没必要了）。

**Kruskal：**

注意要同时处理相同权值的边（初始化边的时候不要加入自环）。

维护两个位置 $l$ 和 $r$，表示相同权值的边编号的起点和终点。

然后先判断每条边的两个端点是否连通，若已经连通了，就说明存在 $k$ 使得 $a_{x,y}\gt \max(a_{x,k},a_{k,y})$ ，是不满足条件的，可以直接退出了。

若都满足，再将每条边两个端点所在的集合合并。

理论复杂度 $\mathcal{O}(n^2\log n^2)$，完全图所以效率有点低。

核心代码：

```cpp
struct UF {
    int fa[N];
    UF() {
        for (int i = 1; i < N; ++i) fa[i] = i;
    }
    int Find(int x) { return x == fa[x] ? x : fa[x] = Find(fa[x]); }
    void Union(int x, int y) { fa[Find(x)] = Find(y); }
} UF;

struct E {
    int x, y, w;
    E() {}
    E(int X, int Y, int W) : x(X), y(Y), w(W) {}
    bool operator<(const E &rhs) const { return w < rhs.w; }
} e[N * N];

bool check() {
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i != j) e[++cnt] = E(i, j, a[i][j]);
        }
    }
    sort(e + 1, e + cnt + 1);
    for (int l = 1, r = 0; l <= cnt; l = r + 1) {
        while (r < cnt && e[r + 1].w == e[l].w) ++r;
        for (int i = l; i <= r; ++i) {
            if (UF.Find(e[i].x) == UF.Find(e[i].y)) { return false; }
        }
        for (int i = l; i <= r; ++i) UF.Union(e[i].x, e[i].y);
    }
    return true;
}
```

**Prim：**

在 Prim 中，我们是一次扩展一个节点。

令 $minE_x$ 表示 $x$ 到已经求出的最小生成树上节点距离的最小值，这是 Prim 的核心。

令 $dis_{i,j}$ 表示 $i$ 到 $j$ 所有路径上最大权值的最小值，那么我们需要要求 $a_{i,j}\le dis_{i,j}$。

要求出 $dis_{i,j}$，还需要记录每个节点在最小生成树上的父亲 $fa_i$。

在每次用新确定的节点更新其他节点的 $dis$ 与 $minE$ 时，需要做一下判断：

- 如果节点 $y$ 还不在最小生成树里，新确定的节点 $x$ 还可以更新 $minE_y$，那么就令 $fa_y=x$。

- 如果节点 $y$ 已经在最小生成树里，那么就可以判断 $a_{x,y}$ 是否合法了。

  先来更新 $dis_{x,y}=dis_{y,x}=\min(dis_{x,y},\max(minE_x,dis_{y,fa_x}) )$。

  因为 $y$ 和 $fa_x$ 都在最小生成树里，$dis_{y,fa_x}$ 已经被更新完了，所以刚好可以用 $dis_{y,fa_x}$ 来更新 $dis_{x,y}$。

  $dis_{x,y}$ 更新完后，也不会再被更新，于是就可以用来检查答案是否合法。

时间复杂度 $\mathcal{O}(n^2)$。

核心代码：

```cpp
int fa[N], minE[N], dis[N][N];
bool vis[N];
bool check() {
    memset(dis, 0x3f, sizeof(dis));
    vis[1] = true;
    for (int i = 1; i <= n; ++i)
        minE[i] = a[1][i], fa[i] = 1, dis[i][i] = 0;
    for (int i = 1, x; i < n; ++i) {
        x = 0;
        for (int j = 1; j <= n; ++j) {
            if (!vis[j] && (!x || minE[j] < minE[x])) x = j;
        }
        vis[x] = true;
        for (int y = 1; y <= n; ++y) {
            if (!vis[y]) {
                if (minE[y] > a[x][y]) { minE[y] = a[x][y], fa[y] = x; }
            } else {
                dis[y][x] = dis[x][y] =
                        min(dis[x][y], max(minE[x], dis[y][fa[x]]));
                if (dis[x][y] < a[x][y]) { return false; }
            }
        }
    }
    return true;
}
```

完整代码：[云剪贴板](https://www.luogu.com.cn/paste/8mezegr7)。

---

## 作者：happybob (赞：1)

有趣的题。

首先第一个和第二个条件可以暴力枚举，复杂度 $O(n^2)$。

可以发现如果满足了第一个和第二个条件，这个矩阵其实就是一个无向完全图的邻接矩阵，$a_{i,j}$ 表示 $i \leftrightarrow j$ 的边权。

接着思考第三个。

我们发现第三个限制相当于，对于任意 $i,j$，不存在一个点 $k$ 使得 $i \rightarrow k \rightarrow j$ 的路径的边权最大值小于 $a_{i,j}$。

看着是一条长度为 $3$ 的路径，但是我们可以把 $k$ 带入 $j$ 中，变成长度为 $4$ 的路径。依次循环带入，就变成任意长的路径。

所以我们要判断，对于所有 $i,j$，是否存在一条路径的边权最大值小于 $a_{i,j}$。换句话说，对于 $i,j$，我们要找到从 $i$ 到 $j$ 的一条边权最大值最小的路径。这是什么？经典的最小瓶颈路。

于是求出最小生成树之后维护树上两点之间边权最大值即可。使用树剖加 ST 表可以做到 $O(n^2 \log n)$。

此外，建议加上快读。我不用快读用 `scanf` 一直 TLE。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstring>
#include <utility>
#include <string>
using namespace std;

const int N = 6e6 + 5, M = 5e3 + 5;

int n, a[M][M], m = 0, aa[M];
vector<pair<int, int> > G[M];
bool vs[N];

struct Edge
{
	int u, v, w;
	bool operator<(const Edge& g) const
	{
		return w < g.w;
	}
}p[N];

class Union_Find
{
public:
	int fa[M];
	void Init()
	{
		for (int i = 0; i < M; i++) fa[i] = i;
	}
	int find(int u)
	{
		return (fa[u] == u ? u : fa[u] = find(fa[u]));
	}
	void merge(int u, int v)
	{
		fa[find(u)] = find(v);
	}
}s;

void kruskal()
{
	s.Init();
	sort(p + 1, p + m + 1);
	for (int i = 1; i <= m; i++)
	{
		int u = p[i].u, v = p[i].v;
		if (s.find(u) == s.find(v))
		{
			continue;
		}
		G[u].emplace_back(make_pair(v, p[i].w));
		G[v].emplace_back(make_pair(u, p[i].w));
		s.merge(u, v);
		vs[i] = 1;
	}
}

class ST
{
public:
	int f[M][30], LG2[M];
	void Init(int* a)
	{
		for (int i = 1; i <= n; i++)
		{
			f[i][0] = a[i];
		}
		for (int i = 2; i < M; i++)
		{
			LG2[i] = LG2[i / 2] + 1;
		}
		for (int i = 1; i <= LG2[n]; i++)
		{
			for (int j = 1; j + (1 << i) - 1 <= n; j++)
			{
				f[j][i] = max(f[j][i - 1], f[j + (1 << (i - 1))][i - 1]);
			}
		}
	}
	int query(int l, int r)
	{
		if (l > r) return 0;
		int p = LG2[r - l + 1];
		return max(f[l][p], f[r - (1 << p) + 1][p]);
	}
};

class TreeCut
{
public:
	ST st;
	int id[M], top[M], sz[M], fa[M], dep[M], son[M], na[M], idx;
	void dfs1(int u, int f)
	{
		sz[u] = 1;
		dep[u] = dep[f] + 1;
		fa[u] = f;
		for (auto& j : G[u])
		{
			if (j.first == f) continue;
			dfs1(j.first, u);
			sz[u] += sz[j.first];
			if (sz[son[u]] < sz[j.first]) son[u] = j.first;
		}
	}
	void dfs2(int u, int f)
	{
		top[u] = f;
		id[u] = ++idx;
		na[idx] = aa[u];
		if (!son[u]) return;
		dfs2(son[u], f);
		for (auto& j : G[u])
		{
			if (j.first != son[u] && j.first != fa[u])
			{
				dfs2(j.first, j.first);
			}
		}
	}
	void build()
	{
		dfs1(1, 1);
		for (int i = 1; i <= m; i++)
		{
			if (!vs[i]) continue;
			if (dep[p[i].u] > dep[p[i].v]) swap(p[i].u, p[i].v);
			aa[p[i].v] = p[i].w;
		}
		dfs2(1, 1);
		st.Init(na);
	}
	int query(int u, int v)
	{
		int res = 0;
		while (top[u] ^ top[v])
		{
			if (dep[top[u]] < dep[top[v]]) swap(u, v);
			res = max(res, st.query(id[top[u]], id[u]));
			u = fa[top[u]];
		}
		if (dep[u] > dep[v]) swap(u, v);
		res = max(res, st.query(id[u] + 1, id[v]));
		return res;
	}
}tc;

struct FastIO {
	static const int S = 1e7;
	int wpos;
	char wbuf[S];
	FastIO() : wpos(0) {}
	inline int xchar() {
		static char buf[S];
		static int len = 0, pos = 0;
		if (pos == len)
			pos = 0, len = fread(buf, 1, S, stdin);
		if (pos == len) exit(0);
		return buf[pos++];
	}
	inline int xuint() {
		int c = xchar(), x = 0;
		while (c <= 32) c = xchar();
		for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
		return x;
	}
	inline int xint()
	{
		int s = 1, c = xchar(), x = 0;
		while (c <= 32) c = xchar();
		if (c == '-') s = -1, c = xchar();
		for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
		return x * s;
	}
	inline void xstring(char* s)
	{
		int c = xchar();
		while (c <= 32) c = xchar();
		for (; c > 32; c = xchar()) *s++ = c;
		*s = 0;
	}
	inline void wchar(int x)
	{
		if (wpos == S) fwrite(wbuf, 1, S, stdout), wpos = 0;
		wbuf[wpos++] = x;
	}
	inline void wstring(const char* s)
	{
		while (*s) wchar(*s++);
	}
	~FastIO()
	{
		if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
	}
} io;

int main()
{
	n = io.xint();
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			a[i][j] = io.xint();
		}
		if (a[i][i] != 0)
		{
			printf("NOT MAGIC\n");
			return 0;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (a[i][j] != a[j][i])
			{
				printf("NOT MAGIC\n");
				return 0;
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			p[++m] = { i, j, a[i][j] };
		}
	}
	kruskal();
	tc.build();
	for (int i = 1; i <= n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			int p = tc.query(i, j);
			if (p < a[i][j])
			{
				printf("NOT MAGIC\n");
				return 0;
			}
		}
	}
	printf("MAGIC\n");
	return 0;
}
```


---

## 作者：JK_LOVER (赞：1)

## 题意
判断一个矩阵是否满足下面的三个条件。（题面翻译错误，见讨论）[$QAQ$](https://www.luogu.com.cn/blog/xzc/solution-cf632f)

- $a_{i,j} =a_{j,i}$

- $a_{i,i} = 0$

- $a_{i,j} \le \max(a_{i,k},a_{k,j})$
## 分析
对于第一和第二个条件，我们可以直接判断，时间复杂度分别为 $O(n),O(n^2)$ 。算法的瓶颈出现在对于第三个的判断。我们只需要知道 $a_{i,j}$ 和 $a_{i,k},a_{k,j}$ 的大小关系，这个就不需要对每一个元素储存大小了。再根据第一条 $a_{i,j} = a_{j,i}$ ，那么第三个条件就变为 $a_{i,j} \le \max(a_{i,k},a_{j,k})$ 。考虑把 $a_{i,j}$ 由小到大排序。那么我们的问题就转化为检查是否第 $i$ 列和第 $j$ 列有同时小于 $a_{i,j}$ 的元素了。这个可以 $\text{bitset}$ 优化。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int read() {
	int x = 0,f = 0;char ch = getchar();
	while(!isdigit(ch)) {if(ch == '-') f = 1;ch = getchar();}
	while(isdigit(ch)) {x = x * 10 + ch - '0';ch = getchar();}
	return f ? -x : x;
}
const int N = 2510;
struct Node{int x,y,val;}s[N*N];
bitset<N> f[N];
bool cmp(Node a,Node b) {return a.val < b.val;}
int n,id = 0,val[N][N];
int main() {
	n = read();
	for(int i = 1;i <= n;i++) {
		for(int j = 1;j <= n;j++) val[i][j] = read();
		if(val[i][i]) {printf("NOT MAGIC\n");return 0;}
	}
	for(int i = 1;i <= n;i++) {
		for(int j = 1;j <= n;j++) {
			s[++id].x = i;s[id].y = j;s[id].val = val[i][j];
			if(val[i][j] != val[j][i]) {printf("NOT MAGIC\n");return 0;}
		}		
	}
	sort(s+1,s+1+id,cmp);
	for(int l = 1,r = 0;l <= id;) {
		r = l;
		while(r < id && s[r].val == s[r+1].val) r++;
		for(int j = l;j <= r;j++) {
			if((f[s[j].x] & f[s[j].y]).any()) {printf("NOT MAGIC\n");return 0;}
		}
		for(int j = l;j <= r;j++) f[s[j].x][s[j].y] = 1;
		l = r + 1;
	}
	printf("MAGIC\n");
	return 0;
}

```


---

## 作者：tzc_wk (赞：0)

安利个人 blog：https://www.cnblogs.com/ET2006/

[题面传送门](https://codeforces.ml/contest/632/problem/F)

开始挖老祖宗（ycx）留下来的东西.jpg

本来想水一道紫题作为 AC 的第 500 道紫题的，结果发现点开了道神题。

首先先讲一个我想出来的暴力做法。条件一和条件二直接扫一遍判断掉。先将所有点按照 $a_{i,j}$ 按权值大小从小到大排序并依次插入这些点，我们实时维护一个 $n\times n$ 的 bool 数组 $vis$，$vis_{i,j}$ 表示第 $i$ 行第 $j$ 列的数是否被访问了。当我们插入某个 $a_{i,j}$ 时，如果 $\exist k\in[1,n]$ 使得 $vis_{i,k}=vis_{j,k}=1$，那么意味着 $a_{i,k},a_{j,k}$ 均小于 $a_{i,j}$，也就不符合条件三了。这个将 bool 数组换成 ```bitset``` 可以实现 $\mathcal O(\dfrac{n}{\omega})$ 判断。还有一个小问题，那就是如果有权值重复的，比如说 $a_{i,j}=a_{i',j'}$，假设 $a_{i',j'}$ 比 $a_{i,j}$ 后访问，那么在访问 $a_{i',j'}$ 的时候 $vis_{i,j}$ 已经等于 $1$ 了。如果在这种情况下 $i'=i$，并且 $vis_{j',j}$ 刚好等于 $1$，那么程序就会认为这种情况不满足条件三，而实际上 $\max(a_{i,j},a_{j',j})=a_{i',j'}$。这个问题也异常容易解决，直接 two pointers 扫描一遍权值相同的数，对于这些数，先一起判断掉再一起插入就行了。

时间复杂度 $\dfrac{n^3}{\omega}$，~~荣膺最劣解~~。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
template<typename T> void read(T &x){
	x=0;char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=2500;
int n,a[MAXN+5][MAXN+5];pair<int,pii> p[MAXN*MAXN+5];
bitset<MAXN+5> bt[MAXN+5];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++){
		scanf("%d",&a[i][j]);p[(i-1)*n+j]=mp(a[i][j],mp(i,j));
	} sort(p+1,p+n*n+1);
	for(int i=1;i<=n;i++) if(a[i][i]) return printf("NOT MAGIC\n"),0;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(a[i][j]!=a[j][i])
		return printf("NOT MAGIC\n"),0;
	for(int l=1,r=1;l<=n*n;l=r){
		while(p[r].fi==p[l].fi&&r<=n*n){
			int x=p[r].se.fi,y=p[r].se.se;
			if((bt[x]&bt[y]).count()) return printf("NOT MAGIC\n"),0;
			r++;
		} for(int i=l;i<r;i++){int x=p[i].se.fi,y=p[i].se.se;bt[x][y]=1;}
	} printf("MAGIC\n");
	return 0;
}
```

事实上我们发现这个东西和图论关系非常密切。如果我们把这个矩阵看作邻接矩阵，那么条件一意味着图中不存在自环，条件二意味着 $w_{u,v}=w_{v,u}$，也就是说满足条件一和条件二的矩阵是一张无向带权完全图的邻接矩阵。我们再来分析条件三。比方说有四个点 $i,j,k,l$，根据条件三 $w_{i,k}\leq\max(w_{i,j},w_{j,k}),w_{i,l}\leq\max(w_{i,k},w_{k,l})\leq\max\{w_{i,j},w_{j,k},w_{k,l}\}$，这意味着 $\forall i,j\in[1,n]$，任意一条 $i,j$ 路径上的边权的最大值 $\geq w_{i,j}$。故 $\forall i,j\in[1,n]$，$i,j$ 之间路径上最大权值的最小值 $\geq w_{i,j}$。看到这个条件很容易想到最小瓶颈路——构建出最小生成树，那么 $i,j$ 之间路径上最大权值的最小值就是最小生成树上 $i,j$ 路径上权值的最大值。于是求一遍最小生成树，然后对于每个点进行一遍 DFS 求出它到每个点的路径上权值的最大值就行了。注意到这张图是一张稠密图，$m=n^2$，故 Kruskal、加堆优化的 Prim 都是 $m\log n=n^2\log n$ 的，而不加堆优化的 Prim 反而是 $n^2$ 的，故此题用 Prim 效率反而更高。

然而这才是我第二次写 Prim（第一次是两年以前） 啊……习惯了 Kruskal 的我都忘了 Prim 咋写了……

code（Kruskal）：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
template<typename T> void read(T &x){
	x=0;char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=2500;
int n,a[MAXN+5][MAXN+5],f[MAXN+5];
pair<int,pii> p[MAXN*MAXN+5];
int find(int x){return (!f[x])?x:f[x]=find(f[x]);}
bool merge(int x,int y){
	x=find(x);y=find(y);
	if(x!=y) return f[x]=y,1;
	return 0;
}
int hd[MAXN+5],to[MAXN*2+5],nxt[MAXN*2+5],ec=0;
void adde(int u,int v){to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;}
void dfs(int x,int rt,int f,int mx){
	if(f&&a[x][rt]>mx){printf("NOT MAGIC\n");exit(0);}
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f) continue;
		dfs(y,rt,x,max(mx,a[x][y]));
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++){
		scanf("%d",&a[i][j]);p[(i-1)*n+j]=mp(a[i][j],mp(i,j));
	}
	for(int i=1;i<=n;i++) if(a[i][i]) return printf("NOT MAGIC\n"),0;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(a[i][j]!=a[j][i])
		return printf("NOT MAGIC\n"),0;
	sort(p+1,p+n*n+1);
	for(int i=1;i<=n*n;i++) if(merge(p[i].se.fi,p[i].se.se))
		adde(p[i].se.fi,p[i].se.se),adde(p[i].se.se,p[i].se.fi);
	for(int i=1;i<=n;i++) dfs(i,i,0,-1);
	printf("MAGIC\n");
	return 0;
}
```

code（Prim）：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
template<typename T> void read(T &x){
	x=0;char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=2500;
const int INF=0x3f3f3f3f;
int n,a[MAXN+5][MAXN+5],hd[MAXN+5],to[MAXN*2+5],nxt[MAXN*2+5],ec=0;
void adde(int u,int v){to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;}
int mn[MAXN+5],fa[MAXN+5];bool vis[MAXN+5];
void prim(){
	vis[1]=1;for(int i=2;i<=n;i++) mn[i]=a[1][i],fa[i]=1;
	for(int i=1;i<=n-1;i++){
		int mnv=INF,k=0;
		for(int j=1;j<=n;j++) if(!vis[j]&&mn[j]<mnv) mnv=mn[j],k=j;
		vis[k]=1;
		for(int j=1;j<=n;j++) if(!vis[j]&&mn[j]>a[k][j]) mn[j]=a[k][j],fa[j]=k;
	}
}
void dfs(int x,int rt,int f,int mx){
	if(f&&a[x][rt]>mx){printf("NOT MAGIC\n");exit(0);}
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f) continue;
		dfs(y,rt,x,max(mx,a[x][y]));
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++) if(a[i][i]) return printf("NOT MAGIC\n"),0;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(a[i][j]!=a[j][i])
		return printf("NOT MAGIC\n"),0;
	prim();for(int i=2;i<=n;i++) adde(i,fa[i]),adde(fa[i],i);
	for(int i=1;i<=n;i++) dfs(i,i,0,-1);printf("MAGIC\n");
	return 0;
}
```

~~（午安，Kruskal 人）~~

---

## 作者：Mihari (赞：0)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF632F)

# 题解

首先，这道题的洛谷题目翻译有点问题，题目意思是这样的：

>满足下列条件的矩阵称为魔法矩阵：
>
>1. $a[i][j]=a[j][i]$；
>2. $a[i][i]=0$；
>3. $a[i][j]\le \min\{\max(a[i][k],a[k][j])\}$
>
>现给你一个 $n\times n$ 的矩阵，试判断它是不是魔法矩阵，若是，输出 `MAGIC`，否则输出 `NOT MAGIC`

对于要求 $1,2$，我们可以先用 $n^2$ 直接判断，唯一的难点在于条件三的判断，如果直接做，我们需要 $\mathcal O(n^3)$ 的复杂度，但是只比时限超了一点点，我们能否考虑用一些卡常技巧卡过去？

考虑将一个值 $k$ 作为分界点，小于其的看做 $1$，大于的看做 $0$，对于某一个 $(x,y)$ 如果其位置上的值为 $k$，那么，将其所在排、列的二进制串并起来，如果最后得到 $0$，那么合法，否则不合法

为什么这样做是合法的？首先，条件三最里面的 $\max(a[i][k],a[k][j])$ 是一对一对来的，而按位并也是按位来的，而如果这一位为 $0$ 则说明对应的俩数中大的一个比 $k$ 大，而我们要求所有位置中都要比 $k$ 大，所以最后的结果也必须为 $0$

二进制则可以使用 `bitset` 进行优化，加一个 $\frac{1}{32}$ 的常数，然后就可以水过去了

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13343215.html
```



---

## 作者：yellow_bored (赞：0)

# [MAGIC](https://www.luogu.com.cn/problem/CF632F)
## 图论，最小生成树
### 前言
我太菜了，这题卡了我好久好久，主要是不知道最小生成树从何而来，有什么用（实际上不会最小生成树也是可以做的）。
### 读题
这题的题面比较简单，但仔细思考，题面中蕴含了许多有用的信息。  
不要看到矩阵就想到线性代数，不要忘了还有邻接矩阵存图这种东西。请我们将这个矩阵当作一个图。  
一个$MAGIC$矩阵满足一下条件：  
#### $1.$
$\forall i \in[1,n],a_i,_i=0$  
说明这个图是无自环的。
#### $2.$
$\forall i,j \in[1,n],a_i,_j=a_j,_i$  
说明这个图是无向图（$i$->$j$与$j$->$i$边权是相同的）。  
所以推式子时，无论如何交换$a$的下标都是无影响的。  
由$1,2$可知，此矩阵实际上是一张无自环的无向图，于是我们就把它转化为了更形象的图论。
#### $3.$ 
$\forall i,j,k \in [1,n], a_i,_j \leq max(a_i,_k,a_k,_j)$    
这是最重要的一个条件，我们拿出来单独分析。
### 条件$3$
#### 首先  
根据条件$3$：   
$a_i,_j\leq max(a_i,_k,a_k,_j)$.  
$a_i,_k\leq max(a_i,_l,a_l,_k)$.   
于是$a_i,_j\leq max(max(a_i,_l,a_l,_k),a_k,_j)$.  
就是$a_i,_j\leq max(a_i,_l,a_l,_k,a_k,_j)$.  
这个式子在图上是什么意思呢   
![](https://cdn.luogu.com.cn/upload/image_hosting/0n442crh.png)
就是说$g,h,m$三条边中，至少存在一条边大于$f$。  
换句话说，就是如果$g,h,m$三条边都比$f$边要小，那么它就是不合法的。
#### 如何判断
排序就好了，先加入小的边。当要加入$f$边时如果发现$i,j$已经相连，那么显然$i,j$是被小于$f$的边连起来的，于是就是不合法的。可以发现这一过程与最小生成树十分相似，但实际上就算不会，也是可以做这题的，并查集直接维护两点间联通关系就好。
### 最后
此题最重要的是对于题中条件的充分利用，不要看到最小生成树就往算法上死想。此题并不用直接运用最小生成树，更多的是它的思想（排序加边）。此题其实还有很多美妙的解法，~~但是我不会QAQ~~。



---

