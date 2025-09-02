# [POI 2011] IMP-Party

## 题目描述

**译自 POI 2011 Round 3. Day 1. A「[Party](https://szkopul.edu.pl/problemset/problem/PCtteC6gKwc2ZikW8nUZzfyh/site/?key=statement)」**

Byteasar 打算举行一次聚会。他自然想要这次聚会成功进行。此外，Byteasar 确信只要邀请的嘉宾都互相认识就可以了。他目前在试着写一份邀请名单。

Byteasar 有 $n$ 个朋友，这里 $n$ 可以被 $3$ 整除。幸运的是，Byteasar 的朋友大部分都互相认识。并且 Byteasar 想起了一次他参加的聚会，那次聚会有 $ \frac{2}{3}n $ 个他的朋友参加，并且他们都互相认识。不幸的是，关于那次聚会的具体细节他不记得了……总的来说，他忘了是他的哪些朋友参加了。

Byteasar 认为他没有义务举办一个大型聚会，但他想邀请至少 $ \frac{n}{3} $ 个他的朋友。他不知道邀请谁，所以请你帮他。

## 说明/提示

对于全部数据，$ 3 \le n \le 3000 , \frac{\frac{2}{3}n(\frac{2}{3}n-1)}{2} \le m \le \frac{n(n-1)}{2}, 1 \le a_i \lt b_i \le n $。

翻译来自于 [LibreOJ](https://loj.ac/p/2166)。

## 样例 #1

### 输入

```
6 10
2 5
1 4
1 5
2 4
1 3
4 5
4 6
3 5
3 4
3 6```

### 输出

```
2 4```

# 题解

## 作者：wsy_jim (赞：12)

## 0x01 题意

给定一张 $3N$ 个点的图，保证其中有一个大小为 $2N$ 的团，找到一个大小为 $N$ 的团

## 0x02 解

每次选两个不连通的点，

根据题意这两个点最多有一个在团里，

那么我们每次删掉这两个不连通的点，

删去了 $N$ 对之后，

最多有 $N$ 个在团中的点被删掉，

最少有 $N$ 个不在团里的点被删掉，

剩下点的必定都在团里

## 0x03 码

```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int INF=0x3f3f3f3f,N=3010;

int n,m,mapp[N][N],vis[N],cnt=0;

inline int read(){
    int x=0,y=1;char c=getchar();
    while (c<'0'||c>'9') {if (c=='-') y=-1;c=getchar();}
    while (c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
    return x*y;
}

int main(){
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int a,b;
        a=read(),b=read();
        mapp[a][b]=mapp[b][a]=1;
    }
    for(int i=1;i<=n;i++){
        if(vis[i]) continue;
        for(int j=i+1;j<=n;j++){
            if(mapp[i][j]||vis[j]) continue;
            vis[i]=vis[j]=1;
            break;
        }
    }
    for(int i=1;i<=n;i++) if(!vis[i]){
        printf("%d ",i);
        cnt++;
        if(cnt*3==n) return 0;
    }
    cout<<endl;
    return 0;
}
```



---

## 作者：zzlzk (赞：6)

~~这么简单的题为什么没人做呢？~~


- 先普及一下什么是团

> 选择一个图中的若干点，若任意两个点之间均有一条边联通，则这些点组成的集合是一个团。

- 知道了这个这道题就很简单了

- 在一个团里的点肯定是两个点之间均有一条边联通

- 所以不在团里的点肯定没有一条边让他们联通

- 所以枚举每个点和哪个点之间没有边，然后打一个标记

- 最后输出还有被标记的点就好了..


```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;

template<typename T>
void input(T &x) {
    x=0; T a=1;
    register char c=getchar();
    for(;c<'0'||c>'9';c=getchar())
        if(c=='-') a=-1;
    for(;c>='0'&&c<='9';c=getchar())
        x=x*10+c-'0';
    x*=a;
    return;
}

#define MAXN 3010

bool G[MAXN][MAXN],vis[MAXN];

int main() {
    int n,m;
    input(n),input(m);
    for(int i=1;i<=m;i++) {
        int u,v;
        input(u),input(v);
        G[u][v]=G[v][u]=true;
    }
    for(int i=1;i<=n;i++)
        if(!vis[i]) {
            for(int j=i+1;j<=n;j++)
                if(!vis[j]&&!G[i][j]&&!G[j][i]) {
                    vis[i]=vis[j]=true;
                    break;
                }
        }
    int cnt=0;
    for(int i=1;i<=n;i++)
        if(!vis[i]) {
            printf("%d ",i);
            cnt++;
            if(cnt*3==n) return 0;
        }
    return 0;
}
```

---

## 作者：Larryyu (赞：4)

# P3524 [POI2011]IMP-Party 题解
 [题目传送门](https://www.luogu.com.cn/problem/P3524)
 
[更好的阅读体验](https://www.luogu.com.cn/blog/larryyu-blog/solution-p3524)
##  _前置芝士_ 
#### _团_
设 $V$ 为 $G$ 子图，当 $V$ 中任意两点都有边相连，则 $V$ 为 $G$ 的一个团。
![](https://cdn.luogu.com.cn/upload/image_hosting/hahssekf.png)
此图为本题样例

最大团： $\{1,3,4,5\}$

大小为 $\dfrac {1}{3}n$ 的团： $\{1,3\}\space \{3,6\} \space \{ 1,5\} \space \{1,4\}\space \{3,5\} \space \{4,5\}\space\{3,4\}\space\{4,6\}\space \{4,2\}\space\{5,2\}$
#### _一点点的图论_

##   _Description_  
给定一个大小为 $n$ 的图，保证 $n$ 为 $3$ 的倍数，且存在一个大小为 $\dfrac {2}{3}n$ 的团，要求输出一个大小为 $\dfrac {1}{3}n$ 的团（输出点编号即可）。
##  _Solution_
由题意得: 至少有 $\dfrac {2}{3}n$ 个点两两相连，所以剩下的 $\dfrac {1}{3}n$ 个点与这个大小为 $\dfrac {2}{3}n$ 两两不一定相连。那就只要见一对点不相连，就删一对，见两对删两对。明显，最多只会删 $\dfrac {1}{3}n$ 对点，也就是 $\dfrac {2}{3}n$ 个点，剩下的点即为题目所求。

#### _结合样例_
$\{1,2\}$ 无连边，删去。

$\{5,6\}$ 无连边，删去。

$\{3,4\}$ 即为题目所求 。
## _Code_
```cpp
int n,m,cnt;
bool is_con[10010][10010],vis[10010]; //是否连边或删除
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		_________________________; //连边
	}
	for(int i=1;i<=n;i++){
		if(vis[i]) continue;
		for(int j=1;j<=n;j++){
			if(j==i||vis[j]||______) continue; //已经删了或不
			vis[i]=1;			               //满足删的条件
			vis[j]=1;
			break;
		}
	}
	for(int i=1;i<=n;i++){
		if(vis[i]) continue;
		cout<<i<<" ";
		cnt++;
		if(________) return 0; //大小已满足
	}
	cout<<endl;
	return 0;
}

```

#### _完结撒花！！_

如有错误，麻烦各位大佬指出。

---

## 作者：长安何处在 (赞：3)

写在前面：此题思维题想法比较巧妙，但实现不难

关于团的定义：一个图中的若干点，若**任意两个点**之间**均有**一条边联通，则这些点组成的集合是一个团。

一句话题意：已知有一张点数为$n$，边数为$m$的图，保证图中存在一个大小为$\frac{2}{3}n$的团，需要找出$\frac{1}{3}n$个在团上点。

解决方案：

首先对于可以知道若两点都在团上则两点一定联通，所以对于两个互不相连的点，不难推知两点至少有一个不在团上，否则根据团的定义，两点一定是联通的。

由于本题团的大小为$\frac{2}{3}n$可行的答案较多，我们只需要找出$\frac{1}{3}n$个点的合法答案即可，所以我们可以有宁可错杀一千也不放过一个的资本，考虑对于两个点无边相连$x,y$显然据上述可知，$x,y$中至少有一个不在团上，那么我们可以直接错杀一千，将$x,y$都排除出正确答案，那么排除$\frac{1}{3}n$个不在团上的点最坏情况每一个点的排除可能会“冤枉”一个在团上的点。但是还剩下$\frac{2}{3}n$-$\frac{1}{3}n$就一定在团上。

完结撒花

Code:

```cpp
//coded by 长安何处在2019于CJ
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#include<queue>
#include<map>
#include<set>

using namespace std;

typedef long long ll;
typedef long double ld;
#define re register
#define il inline

const int N=3010;
int n,m,mp[N][N],vi[N],tot=1;

inline int read()
{
  	int a=0,b=1;char c;c=getchar();
  	while(c<'0'||c>'9'){if(c=='-')b=-1;c=getchar();}
  	while(c>='0'&&c<='9'){a=(a<<3)+(a<<1)+(c^48);c=getchar();}
  	return a*b;
}//读入优化

int main()
{
    n=read(),m=read();
    for(re int i=1;i<=m;i++)
    {
		int o=read(),p=read();
		mp[o][p]=1,mp[p][o]=1;
    }//矩阵建图
    for(re int i=1;i<=n;i++)
    {
		if(vi[i])continue;//如果一个点已经被认定不在团上，那就不要再管它
		for(re int j=i+1;j<=n;j++)
		{
	    	if(vi[j]||mp[i][j])continue;
	    	vi[i]=1,vi[j]=1;
	    	break;//一个点已经被认定不在团上，就不要再让它祸害其他可能在团上的点
		}
    }
    for(re int i=1;i<=n;i++)
    {
		if(tot*3>n)break;
		if(vi[i])continue;
		printf("%d ",i);
		tot++;
    }//输出答案
    printf("\n");
    return 0;
}
```


---

## 作者：Tiphereth_A (赞：2)

前往 [我的 Blog](https://blog.tifa-233.com/archives/luogu-p3524/#%E8%A7%A3%E9%A2%98%E6%80%9D%E8%B7%AF) 以获取更好的阅读体验。

---

讲一个效率和正确率都很高的非完美算法。

我们发现如果团内每个点的度往往都大于不在团内每个点的度，所以我们自然想到把所有点按度降序排个序然后取前 $n\over3$ 个输出。

但是这样是有 [反例](https://www.luogu.com.cn/discuss/show/272368) 的。

> 我们可以构造这样的图：
> 
>     9 24
>     1 3
>     1 5
>     1 6
>     2 5
>     2 6
>     3 4
>     3 5
>     5 6
>     2 1
>     2 3
>     6 3
>     4 1
>     2 4
>     4 5
>     4 6
>     7 9
>     8 9
>     9 3
>     9 2
>     9 5
>     9 4
>     9 6
>     1 7
>     1 8
>
> 画出来是这样的：
> 
> ![](https://cdn.luogu.com.cn/upload/image_hosting/xx9v2tvg.png)
> 
> 我们发现 $1$ 和 $9$ 的度是 $7$，$7$ 和 $8$ 的度是 $2$，其余点的度是 $6$。
> 
> 按这样的做法就会输出：
> 
>     1 x 9
> 
> 其中 $x\in\{2,3,4,5,6\}$。
> 
> 而 $1$ 和 $9$ 没有边，所以这是错误答案。

我们观察这个反例可以发现如果我们把取点策略换成：在前 $2n\over 3$ 个点里随机取 $n\over3$ 的点，就有很大概率正确。

所以我们搞个 Las Vegas 随机就好了（本篇题解只是单纯的单次 `shuffle`，没搞 Las Vegas 随机）。

不考虑输入部分的话，时间复杂度主要在排序上，也就是 $O(n\log n)$，这是比正解快的（输入部分的时间复杂度是 $O(n^2)$）。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e3 + 5;

struct node {
    int in, id;
    bool operator<(const node& rhs) const { return in > rhs.in; }
} deg[N];

int ans[N];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) deg[i].id = i;
    for (int i = 1, x, y; i <= m; ++i) {
        scanf("%d%d", &x, &y);
        ++deg[x].in;
        ++deg[y].in;
    }
    sort(deg + 1, deg + n + 1);

    mt19937 g(time(0));
    shuffle(deg + 1, deg + n / 3 * 2 + 1, g);

    sort(deg + 1, deg + n / 3 + 1, [](const node& a, const node& b) { return a.id < b.id; });
    for (int i = 1; i <= n / 3; ++i) printf("%d%c", deg[i].id, " \n"[i == n / 3]);
    return 0;
}
```

---

## 作者：shiroi (赞：2)

### Description

给定一张 n 个点 m 条边的图，其中 $n\equiv 0 \pmod 3$，保证存在一个大小为 $\dfrac{2}{3}n$ 的团，要求输出 $\dfrac{n}{3}$ 个团上的点。

### Solution

一道思路题。首先给出团的定义：

> 对于图中的点集 $V$ ，若 $V$ 中任意两个不同的顶点间均有边相连，则 $V$ 是图的一个团。

由于团上的点两两连通，因此可以直接用邻接矩阵存边。

考虑 $O(n^2)$ 遍历所有点对。一对点之间没有连边说明其中至少有一个点不在团上，则同时给两个点都打上一个标记。由于已知在团外的点只有 $\dfrac{n}{3}$ 个，因此过程中只会有 $\dfrac{n}{3}$ 个团上的点被标记，最终未被标记的即是所求的点。

代码实现难度相对较低。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read()
{
	int x=0,f=1,c=getchar();
	while(c<48) c=='-'&&(f=-1),c=getchar();
	while(c>47) x=x*10+c-'0',c=getchar();
	return x*f;
}

typedef long long ll;
const int MAXN = 3005;
int out[MAXN],e[MAXN][MAXN];
int n,m;

int main(int argc, char const *argv[])
{
	n=read(); m=read();
	for(int i=1,x,y; i<=m; ++i)
		x=read(),y=read(),e[x][y]=e[y][x]=1;
	for(int i=1; i<=n; ++i)
		if(!out[i]) for(int j=i+1; j<=n; ++j)
				if(!out[j]&&!e[i][j]&&!e[j][i])
				{out[i]=out[j]=1; break;}
	for(int i=1,cnt=0; cnt!=(n/3)&&i<=n; ++i)
		if(!out[i]) printf("%d ", i),++cnt;
	return 0;
}
```

---

## 作者：wf1594937223 (赞：2)

一道很好的题，充分体现了 $OI$ 的本质~~考思路不考码量，与2020CSP-ST1形成了鲜明的对比~~。

团的定义先前有几位大佬都讲过了，此处不再赘述。

但此处稍微补充一点，就是求最大团的做法是 $O(3^n)$ 的，所以本题要用到更好的办法。

许多题解都讲了一种正规的方法，此处提供一种能通过所有洛谷数据的方法。

考虑一个点，它的度数如果 $≥ \dfrac{2\times n}{3}-1$ ，那么在它和它直接连接的点（及其之间的边）中一定存在一个大小为 $\dfrac{n}{3}$ 的团且包含它自己。下面给出他的证明，不想看的奆佬可以直接略过。

---

#### 证明：

由于题目中说了至少有一个大小 $≥ \dfrac{2\times n}{3}$ 的团，所以至多有 $\dfrac{n}{3}$ 个点不在这个环中，所以它所连的点至少有 $\dfrac{n}{3}-1$ 个点在这个团中；而它与这至少 $\dfrac{n}{3}-1$ 个点都有连边，所以必定存在一个大小为 $\dfrac{n}{3}$ 的团。

---

然后就开始乱搞了：

考虑这个条件，它能保证所有在那个大小 $≥ \dfrac{2\times n}{3}$ 的团中的点都通过这个条件。所以我们维护一个数组 $a$，并对所有能通过这个点的点及其所连的点的 $a_i$ 加一。

最后将 $a_i$ 最大的 $\dfrac{n}{3}$ 个点输出就行了。

附上代码：

```cpp
# include <stdio.h>
# include <string.h>
# include <algorithm>
# include <queue>
# include <utility>
using namespace std;
int du[3010],li[3010][3010],dd[3010];
priority_queue< pair< int,int > >q,anss;
int read()
{
	int now=0;
	char c=getchar();
	while(c<'0' || c>'9')
		c=getchar();
	while(c>='0' && c<='9')
	{
		now=(now<<1)+(now<<3)+c-'0';
		c=getchar();
	}
	return now;
}
int main()
{
	int i,j,n,m,x,y;
	n=read();
	m=read();
	for(i=1;i<=m;i++)
	{
		x=read();
		y=read();
		li[x][y]=1;
		li[y][x]=1;
		du[x]++;
		du[y]++;
	}
	pair< int,int >o;
	for(i=1;i<=n;i++)
	{
		o.first=du[i];
		o.second=i;
		q.push(o);
	}
	while(q.top().first>=2*n/3-1)
	{
		o=q.top();
		for(i=1;i<=n;i++)
			if(li[o.second][i])
				dd[i]++;
		dd[o.second]++;
		q.pop();
	}
	for(i=1;i<=n;i++)
	{
		o.first=dd[i];
		o.second=i;
		anss.push(o);
	}
	i=0;
	while(i<n/3)
	{
		i++;
		o=anss.top();
		printf("%d ",o.second);
		anss.pop();
	}
	return 0;
}

```

---

附注：

致亲爱的管理员：

本片提解释我突发奇想想出来的做法，不能保证正确性，写在这里的原因是为了让所有看到这篇题解的人开拓一些思维，~~顺便拓宽其骗分的方法~~。如果不通过的话，能否回复一下如何让这种思想与大家分享（如：发讨论区），不胜感激！

---

## 作者：1saunoya (赞：2)

考虑团的性质，两点之间必有边。

然后把点分成两类，团内点和团外点。

然后 $\frac{2}{3}-\frac{1}{3}=\frac{1}{3}$。

也就是如果说 $i,j$ 不连通两个都排除答案。

所以就做完了？。。


---

## 作者：Hope888 (赞：1)

# 思路

团就是完全图，即任意两个点之间均有一条边。

那么只需枚举点 $i$ 和点 $j$，如果它们之间没有边，将 $j$ 打上标记，最后输出哪些点没有被标记即可，注意只输出 $\frac{n}{3}$ 个点。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
bool edge[3005][3005],vis[3005];
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v;
		cin>>u>>v;
		edge[u][v]=edge[v][u]=1;
	}
	for(int i=1;i<=n;i++)
	{
		if(vis[i]!=0)continue;
		for(int j=i+1;j<=n;j++)
		{
			if(edge[i][j]==1||vis[j]==1)continue;//如果有边就不需要打标记
			vis[i]=vis[j]=1;
			break;
		}
	}
	int sum=0;
	for(int i=1;i<=n;i++)
	{
		if(vis[i]==1)continue;
		++sum;
		cout<<i<<" ";
		if(sum*3>=n)return 0;
	}
}
```

---

## 作者：StudyingFather (赞：1)

早上杨主力讲课的时候讲到了这题，所以过来补题。

为了方便起见，我们令 $n=3k$，即我们需要找到一个大小为 $k$ 的团。

我们首先按题意将点分为两类，团内点和团外点。显然从 $2k$ 个团内点中任意挑出 $k$ 个点作为答案肯定是一种合法方案。问题变成了我们怎么找到团内点。

注意到团内点有个性质，任意两个团内点之间一定有边相连。考虑利用这个性质排除团外点。

我们枚举点对 $(i,j)$，若 $i,j$ 间没有边，则表示这两个点之间至少有一个点不是团内点。我们将这两个点都从图上移除。

这样势必会导致一些团内点被错误的删除。不过因为一次删除至多删掉一个团内点，而团外点也至多只有 $k$ 个，因此我们至多删除 $k$ 个团内点，从而留下的团内点不少于 $k$ 个，刚好符合要求。

代码就不贴了。

---

## 作者：LinkZelda (赞：0)

一个纯随机的做法。

通过直觉发现一个点在 $\frac{2}{3}n$ 的团内的概率非常大，于是可以直接随机一个点然后 check。

check 过程就是维护当前在团内的点集，可以使用 `bitset` 维护一下新加入的点出边是否可以和当前点集成为团，这样单次 check 是 $O(\frac{n^2}{w})$ 的。

注意我们最好也把点的编号 `random_shuffle` 一下，从而避免构造数据导致选出来的点集收敛成一个较小的团。

[代码](https://www.luogu.com.cn/paste/w20o6085)。

---

## 作者：Code_AC (赞：0)

题意翻译已在题中很清晰的给出，这里不再多赘述...

## 题目分析：

首先解释一下团的概念：

**团指的是一个图中的完全子图。**

这里提供两种思路：

**1.**  建补图：

补图是什么？

**简单理解，就是将原图中未连边的点全部连上，然后把连了的边全部删掉。**

打个比方：

看下面这张图：

![](https://pic.imgdb.cn/item/62da5f27f54cd3f937c96651.jpg)

这就是它的补图：

![](https://pic.imgdb.cn/item/62da5f51f54cd3f937ca6a70.jpg)

那么，我们可以想到，先建原图的补图，那么度数大于 $\dfrac{1}{3}n$ 点在原图中一定无法构成团，那么就把它们都删掉，然后在剩下的点中选即可。

这个做法可行，就不给代码了，可以自己尝试写一下。

**2.** 观察题目给出的条件：

我们来思考一下 $n, \dfrac{2}{3}n, \dfrac{1}{3}n$ 这三个两之间的关系：

很明显：

$$n=\dfrac{2}{3}n + \dfrac{1}{3}n$$

故我们可以想到这样的处理方式：

**step1** 建图过程中，将有连边的两个点打上标记；

**step2** 然后找到任意一对没有连边的点，将它们删掉；

**step3** 由于数据保证有由 $\dfrac{2}{3}n$ 个点组成的团，所以当我们删掉了 $\dfrac{1}{3}n$ 对点时，其中的 $\dfrac{1}{3}n$ 为保证的团中的点，另外 $\dfrac{1}{3}n$ 则是不包含在团中的点，那么整个图中剩下的 $\dfrac{1}{3}n$ 个点就必然构成一个 $\dfrac{1}{3}n$ 个点的团。

这种做法正确性显然。

这种方法给出核心代码：

**Code**

```cpp
int n,m,cnt;
bool edge[MAXN][MAXN],vis[MAXN];//edge用来记录是否连边，vis用来删边

int main()
{
	n=read(),m=read();
	for(register int i=1;i<=m;i++)
	{
		int x=read(),y=read();
		edge[x][y]=edge[y][x]=true;//连边
	}
	for(register int i=1;i<=n;i++)
		for(register int j=1;j<=n;j++)
			if(!vis[i]&&!vis[j]&&i!=j&&!edge[i][j])
                vis[i]=vis[j]=true;//删边
	for(register int i=1;i<=n;i++)
	{
		if(vis[i])
            continue;
		if(++cnt==n/3)
		{
			printf("%d",i);
			break;
		}
		else 
            printf("%d ",i);
	}
    return 0;
}
```

---

