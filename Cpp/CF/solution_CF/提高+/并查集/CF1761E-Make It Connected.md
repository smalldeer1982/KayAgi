# Make It Connected

## 题目描述

You are given a simple undirected graph consisting of $ n $ vertices. The graph doesn't contain self-loops, there is at most one edge between each pair of vertices. Your task is simple: make the graph connected.

You can do the following operation any number of times (possibly zero):

- Choose a vertex $ u $ arbitrarily.
- For each vertex $ v $ satisfying $ v\ne u $ in the graph individually, if $ v $ is adjacent to $ u $ , remove the edge between $ u $ and $ v $ , otherwise add an edge between $ u $ and $ v $ .

Find the minimum number of operations required to make the graph connected. Also, find any sequence of operations with the minimum length that makes the graph connected.

## 说明/提示

In the first test case, the graph is connected at the beginning, so the answer is $ 0 $ .

In the second test case, if we do the operation with vertex $ 1 $ , we will get the following graph represented by an adjacency matrix:

$$ \begin{bmatrix} 0&1&1\\ 1&0&1\\ 1&1&0 \end{bmatrix}  $$

It's obvious that the graph above is connected.

In the third test case, if we do the operation with vertex  $ 3 $  and  $ 4 $ , we will get the following graph represented by an adjacency matrix:

$$  \begin{bmatrix} 0&1&1&1\\ 1&0&1&1\\ 1&1&0&1\\ 1&1&1&0 \end{bmatrix}  $$

It's obvious that the graph above is connected, and it can be proven that we can't perform less than  $2$ operations to make the graph connected.

## 样例 #1

### 输入

```
4
3
011
100
100
3
000
001
010
4
0100
1000
0001
0010
6
001100
000011
100100
101000
010001
010010```

### 输出

```
0
1
1
2
3 4 
3
2 5 6```

# 题解

## 作者：MSqwq (赞：13)

如果你 **TLE10** 了，**请使用较快的输入输出方式**。  
这题卡读入是我没想到的，可能很多人打出正解了然后被读入搞了一手。  


------------
题意：  
给你很多个图，然后你每次可以选点，将与这个点相连的边删掉，把它没有连边的点连起来，问你最少步数，并输出方案。   


------------
题解：  
其实是个结论题啊。。。  
首先考虑如果是一个图，就是全部点联通了，那么就是 $0$。至于连通块怎么数你拿个并查集维护一下即可，或者 dfs 一遍全部点，就能判处所以连通块。  

其次考虑如果存在一个大小为 $1$ 的连通块，就是一个点为一个图，那么很显然就是只需要 $1$ 的步数，就能把所有点联通了。  

再想，如果有一个图不为完全图（即图中任意两点都有边），那么其实也只需要 $1$ 步，就是找出度数最小的点，对它进行操作即可。  
证明很简单，将与这个度数最小的点有关的边删去后，它现在就为单独的一点，然后把它和刚刚没有连过的所有点相连，那么其他连通块肯定可以连起来，而且因为不为完全图，且它度数最小，所以重连边的时候一定有边会连向它在原来的那个图的点。判断完全图的方法就是点数等于边数减一，那么这里只要不满足这一点即可，对于找度数最短的点，你依然可以通过 dfs ，那么最后 dfs 到的点，就是度数最小的点。  

继续，如果有大于两个的连通块。其实也只需要两步就可以完成，随便找一个点进行操作，然后这个点会和其他连通块相连，但是和自己的连通块断开了，所以只需要再找一个另外的一个连通块上的点，进行操作，那么就可以将那个连通块联通回去了。    
证明其实很好证明，第一次操作后，一定只有两个连通块，且与第一次选点组成的连通块一定不为完全图，其实就变为了上一个讨论的东西，且更特殊，不需要找度数最小的点，因为所有点都不可能和每个点相连，所以只需要随便找一个不为原来连通块的点即可。   

最后一种情况，也是比较复杂的情况，需要贪心。剩下的这种情况其实就是两个完全图了。结论就是找较小的连通块，最小步数就是较小连通块的点数。  
证明，不难发现，每次操作完之后只是相当于把一个点从一个连通块分割出去，到另一个连通块那里去了，剩下的还是两个完全图，改变的只是两个连通块点的数量，那么其实就只需要一直操作一个连通块，使其剩下一个点，再操作那个点即可。  

大概就是分这五类，每种情况都有每种情况非常独特的性质，希望读者自己画一画图理解一下。  
代码如下：  
```
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<functional>
#define ll long long
using namespace std;
const int mod=1e9+7;
const int INF=0x3f3f3f3f;

inline ll read()
{
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0',c=getchar();}
	return x*f;
}
const int N=4010;
char a[N];
vector<int>v[N],ve;
int cnt,qt;
int dfn[N];
void dfs(int x)
{
	ve.push_back(x);
	dfn[x]=cnt;
	for(int i=0;i<v[x].size();i++)
	{
		int to=v[x][i];
		if(!dfn[to])dfs(to);
	}
}
void solve()
{
	int n=read();
	for(int i=1;i<=n;i++)v[i].clear(),dfn[i]=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",a+1);
		//string a;cin>>a;
		for(int j=1;j<=n;j++)
			if(a[j]=='1')v[i].push_back(j);
	}
	
	cnt=0,qt=-1;
	
	for(int i=1;i<=n;i++)
	{
		if(!dfn[i])
		{
			cnt++;
			ve.clear();
			dfs(i);
			ll en=0;
			int si=ve.size();
			for(int j=0;j<si;j++)
				if(v[ve[j]].size()!=si-1)en=ve[j];
			if(en)qt=en;
			if(ve.size()==1)qt=i;
		}
	}
	if(cnt==1)
	{
		printf("0\n");
		return;
	}
	if(qt!=-1)
	{
		printf("1\n%d\n",qt);
		return;
	}
	if(cnt!=2)
	{
		printf("2\n1 ");
		for(int i=1;i<=n;i++)
		{
			if(dfn[i]!=dfn[1])
			{
				printf("%d\n",i);
				return;
			}
		}
	}
	int sum1=0,sum2=0;
	for(int i=1;i<=n;i++)
	{
		if(dfn[i]==dfn[1])sum1++;
		else sum2++;
	}
	printf("%d\n",min(sum1,sum2));
	
	if(sum1<sum2)
	{
		for(int i=1;i<=n;i++)
			if(dfn[i]==dfn[1])printf("%d ",i);
		printf("\n");
		return;
	}
	
	for(int i=1;i<=n;i++)
		if(dfn[i]!=dfn[1])printf("%d ",i);
	printf("\n");
}
int main()
{
	int T=read();
	while(T--)solve();
	return 0;
}

```


---

## 作者：EnofTaiPeople (赞：8)

题意给定 $n\le4000$ 的无向稠密图，求翻转尽量少的点的所有边，使得原图连通。

首先判掉本来就连通，如果有节点没有连边，对该点操作一次即可。

考虑对于一个连通块，找到一个**非**割点，如果它**没有**对该连通块的所有点均有连边，那么对它操作一次之后，该连通块依旧连通，并且全图连通。

否则，该图一定形如若干个团。

这时显然不能操作一次得到答案。

如果有超过两个团，我们可以操作任意一个点，这样就不再是形如若干个团了，事实上，这时再操作另一个团的任意点即可。

否则，只有两个团，我们应当对较小团的所有点依次操作，加入到大团里去：
```cpp
int T,n,K,a[N],b[N],bt,f[N],sz[N];
int gf(int x){return x==f[x]?x:f[x]=gf(f[x]);}
bitset<4005>g[4005],cut;
int dfn[4005],low[4005],dlt;
void tarjan(int x,int t){求割点
    dfn[x]=low[x]=++dlt;
    int y;
    for(y=1;y<=n;++y)
        if(g[x][y])
            if(dfn[y])ckmn(low[x],dfn[y]);
            else{
                tarjan(y,0),ckmn(low[x],low[y]);
                if(low[y]>=low[x])--t;
            }
    if(t<0)cut[x]=1;
}
string s1;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int i,j,k,l,r,x,y,z,d1,d2;
    for(cin>>T;T--;){
        cin>>n;
        for(x=1;x<=n;++x){
            cin>>s1;
            for(y=1;y<=n;++y)
                g[x][y]=s1[y-1]-'0';
        }
        for(x=1;x<=n;++x){
            if(g[x].none()){没有连边
            	printf("1\n%d\n",x);goto lc1;
            }
            f[x]=x;
        }
        for(x=1;x<=n;++x)
            for(y=x+1;y<=n;++y)
                if(g[x][y])f[gf(y)]=gf(x);
        for(x=1,bt=0;x<=n;++x)
            if(x==f[x])b[++bt]=x;
        if(bt<2){开始就连通
        	puts("0");goto lc1;
        }
        for(x=1;x<=n;++x)++sz[gf(x)];
        for(x=1;x<=n;++x)
            if(x==f[x])tarjan(x,1);
        for(x=1;x<=n;++x)
            if(!cut[x]&&g[x].count()!=sz[gf(x)]-1){
            	非割点并且并不全有连边
                printf("1\n%d\n",x);goto lc1;
            }
        if(bt>2){
        	各选一个点
            printf("2\n%d %d\n",b[1],b[2]);
            goto lc1;
        }
        x=b[sz[b[1]]>sz[b[2]]?2:1];
        printf("%d\n",sz[x]);
        for(k=1;k<=n;++k)
            if(gf(k)==x)printf("%d ",k);
        putchar('\n');
        lc1:
        for(x=1,dlt=0;x<=n;++x){
            g[x].reset();
            dfn[x]=low[x]=cut[x]=sz[x]=0;
        }
    }
    return 0;
}
```

---

## 作者：Alex_Wei (赞：6)

考虑到如果一个连通块不是完全图，那么找到不同时与该连通块内所有点有边的某点 $x$，对 $x$ 执行操作，就可以让整张图连通。

因此，若整张图连通，答案为 $0$。

否则，考虑到对孤立点操作可以使它同时与所有点连通，所以若存在孤立点，则答案为 $1$。

否则，若存在至少一个不为完全图的连通分量，则答案为 $1$。

否则，考虑到对任意一个点 $x$ 执行操作会断开它和它所在连通块内所有点的边，并和其它所有点连边，所以

- 当连通块数为 $2$ 时，这会让被操作点所在完全图大小减去 $1$，另一个完全图大小增加 $1$，此时答案即较小连通块大小。
- 当连通块数大于 $2$ 时，执行操作后满足至少存在一个不为完全图的连通分量，只需再执行一次操作，所以答案为 $2$。

很好，简单题，写一发交上去，结果 [WA on test 4](https://codeforces.com/contest/1761/submission/181831137)? 怎么回事呢？肯定是算法假了而不是写挂了（确信。

想想看，对 $x$ 执行操作为什么能使整张图连通？它断开了和它相连的所有边，把其它连通块连起来，并且和原连通块有至少一条边相连。这些都建立在一个前提下，就是执行操作后 $x$ 所在连通块仍连通。不连通那不就寄了嘛！

所以，我们对 $x$ 还有一个要求，就是它不是割点。而这样的点必然存在，直接暴力判断即可。

证明：根据之前的条件，可知连通块大小 $m \geq 3$。建出连通块的圆方树。若整个连通块点双连通，显然。否则选择一个叶子圆点即可。我们知道圆方树的叶子圆点均不是割点，且它不可能和所有点均直接相连，否则它就和其它所有点同时点双连通，结合 $m\geq 3$，与叶子圆点矛盾。正比。

时间复杂度 $\mathcal{O}(n ^ 2)$。[代码](https://codeforces.com/contest/1761/submission/183457022)。

---

## 作者：EBeason (赞：3)

### 构造
首先观察性质  
1.如果联通直接输出 `0`。  
2.如果不连通那么一定是被分成了联通的几部分。  
3.如果其中一块不是完全图，那么答案一定是 `1`。  
 ##### 为什么呢？
设 $x$ 存在与这一块中其他点不连边，那么我对 $x$ 反转， $x$ 将会和所有其他块联通，（同时也会与自己一块联通，与刚才不连边的那个点联通）。  
如果他是完全图的话，那么只能对这个块中每一个点都反转才能使整个图联通。  
#### ~~结束~~  
其实还有一种情况， 当完全图个数大于三个时， 我任意选择两个不同块中的两个点，　那么我可以使整个图联通。（自己画一下就知道了，比较好证明）。  
  ### 代码
```cpp
    #include<bits/stdc++.h>
    using namespace std;
    #define ll long long 
    #define int ll
    const int MaxN=4e3+100;
    const int INF=1e9;
    int N,M,T,vis[MaxN],top,st[MaxN];
    char s1[MaxN][MaxN];
    int a[MaxN],jg[MaxN];
    vector<int>G1[MaxN];
    template<class T>
    inline void qread(T &sum)
    {
        sum=0;int boo=1;
        char x=getchar();
        while(x<'0'||x>'9'){if(x=='-')boo=-1;x=getchar();}
        while(x>='0'&&x<='9'){sum=(sum<<1)+(sum<<3)+x-'0';x=getchar();}
        sum*=boo;
    }
    template<class T>
    void qput(T x)
    {
        if(x<0) {x=-x;putchar('-');}
        if(x>9){qput(x/10);}
        putchar(x%10+48);
    }
    void dfs1(int x)
    {
        vis[x]=1;
        st[++top]=x;
        for(int i=0;i<(int)G1[x].size();i++)
        {
            int y=G1[x][i];
            if(!vis[y])
            dfs1(y);
        }
    }
    inline void Solve()
    {
        qread(N);
        for(int i=1;i<=N;i++)
        {
            scanf("%s",s1[i]+1);
            G1[i].clear();
            vis[i]=0;
        }
        int ans=INF;
        for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
        {
            if(i==j) continue;
            if(s1[i][j]=='1')
            {
                G1[i].push_back(j);
            }
        }
        int sum=0;
        for(int i=1;i<=N;i++)
        {
            if(!vis[i])
            {
                sum++;
                jg[sum]=i;
                top=0;
                dfs1(i);
                if(top==N) ans=min(ans,0ll);
                if(top==1)
                {
                    if(1<ans)
                    {
                        ans=1;
                        a[1]=i;
                    }
                }
                if(top>1)
                {
                    int pd=1,id=0;
                    for(int k=1;k<=top;k++)
                    {
                        int x=st[k];
                        for(int j=1;j<=top;j++)
                        {
                            if(k==j) continue;
                            if(s1[x][st[j]]=='0') pd=0,id=x;
                        }
                    }
                    if(pd==1)
                    {
                        if(top<ans)
                        {
                            ans=top;
                            for(int j=1;j<=top;j++)
                            a[j]=st[j];
                        }
                    }
                    else 
                    {
                        if(1<ans)
                        {
                            ans=1;
                            a[1]=id;
                        }
                    }
                }
            }
        }
        if(sum>=3&&2<ans)
        {
            ans=2;
            a[1]=jg[1];
            a[2]=jg[2];
        }
        qput(ans);putchar('\n');
        for(int i=1;i<=ans;i++)
        qput(a[i]),putchar(' ');
        if(ans!=0)
        putchar('\n');
    }
    signed main()
    {
        qread(T);
        while(T--) Solve();
    }
```



---

## 作者：Iam1789 (赞：3)

考虑若每个连通块不都是大小 $>1$ 的团，则选择不属于团的度数最小的点操作一次。设这个点为 $u$。因为 $u$ 所在的连通块不是团，因此此连通块中一定存在 $v$ 使得 $u,v$ 之间不存在边。如果 $u$ 为割点，因为 $u$ 度数最小，所以 $u$ 与割下的每个连通块中也存在 $v$ 与之不连通。操作一次，原本的连通块连通性不变，而不与 $u$ 连通的点都会连通，因此只需要操作一次。

考虑只有两个团。不难发现，任意一个点操作一次变成的图依然为两个团，所以答案为较小团的大小。

考虑大于两个团。任意一个点操作一次就会变为第一种情况，因此需要操作两次。

---

## 作者：封禁用户 (赞：2)

考虑从特殊情况出发：

* 如果原图已经联通则答案为 $0$，否则原图会被分成若干个联通块。此时注意到一个重要性质：如果翻转点 $x$，则 $x$ 会与除原联通块外的所有联通块联通。
* 如果有一个点是孤立点（所在联通块大小为 $1$），发现只需要将这个点翻转即可连接到其他所有点，此时所有点都和这个点联通，答案为 $1$。

图示如下（红色是新增的边）：

![](https://cdn.luogu.com.cn/upload/image_hosting/94c7l827.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

* 如果有一个联通块不为完全子图，发现可以将其中一个没有连接到其他所有点的点 $x$ 翻转，此时 $x$ 仍与原联通块联通，答案为 $1$。

图示如下（此处图有误，$x$ 与上面的点的边应该断开，不过不影响理解）：

![](https://cdn.luogu.com.cn/upload/image_hosting/kv1agkvf.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

---

这里有一个细节：可能会出现以下情况使得原连通块不再连通：

![](https://cdn.luogu.com.cn/upload/image_hosting/3phwehfc.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

此时翻转 $x$ 显然不合法。所以在 $x$ 的选择上不能选择割点，否则会使原子图不再联通。


* 原图刚好被分为 $2$ 个完全子图。

注意到如果其中有一个联通块大小为 $2$ 的话，就可以翻转其中一个点，这个联通块的另外一个点就变为了孤立点，此时答案为 $2$。

图示如下（翻转 $x$ 后 $y$ 就变为了孤立点）：

![](https://cdn.luogu.com.cn/upload/image_hosting/15xz586k.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如果没有，此时一次操作会使一个联通块大小 $-1$，另一个 $+1$。考虑操作其中一个联通块直到其大小为 $2$，答案最小为 $\min(a-2,b-2)+2=\min(a,b)$。其中 $a$ 与 $b$ 为两个联通块的大小。

* 原图被分为 $>2$ 个完全子图。

注意到此时如果将 $x$ 翻转，则 $x$ 必定与原联通块不连通，且与其余联通块联通。

图示如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/lltvgmup.png?x-oss-process=image/resize,m_lfit,h_170,w_225)


显然，任意两个联通块不连通，所以此时由 $x$ 所造成的大联通块**必定不是完全图**，特殊情况是原图只有 $2$ 个联通块，但已经讨论过了。

于是这种情况我们只需要再翻转一次，答案为 $1+1=2$。

[代码](https://www.luogu.com.cn/paste/7jnf0hbq)，我的实现很丑很暴力。

---

## 作者：KidA (赞：1)

构造题，先从特殊情况开始。

- 图联通。操作次数显然为 $0$。

- 有孤点。直接操作一次这个孤点即可。

- 有一个联通块不是完全图。那么操作其中任意一点之后这个点一定还会在这个联通块里，并且还会和其他联通块联通，从而使得整个图联通。

第二种情形手玩样例可以看出，第三种情形则随便构造一个不联通的普通图即可发现。

其中，第三种情况启发我们依据完全图的数量去对一般情形进行分类。

继续手玩样例，可以得出：

- 有恰好两个完全图。选择较小的那个，不停地选点操作即可。

更一般的情形（画图可知）：

- 有多于两个完全图。随便选一个点进行操作，容易发现此时图一定只有两个联通块，且至少有一个不是完全图。这时就转化为第三种情况了。因此仅需操作两次。

然后我们就解决了此题。

[本人实现](https://codeforces.com/contest/1761/submission/290660225)是并查集解法，时间复杂度 $O(n^2\alpha(n))$。

---

## 作者：Engulf (赞：1)

分讨题。

- 原图联通，答案是 $0$。
- 否则，若存在一个度为 $0$ 的点 $x$，操作它即可，答案是 $1$。
- 否则，若存在一个非完全子图，则对这个非完全子图中的**非割点**操作一次即可，答案是 $1$。[证明](https://www.luogu.com.cn/paste/iycyifea)。
- 否则，这个图由多个团组成。若这个图由 $>2$ 个团组成，此时只需选一个团中的任意一个点，再选另一个团中的任意一个点即可。[证明](https://www.luogu.com.cn/paste/vd7n50om)。
- 否则，这个图由 $2$ 个团组成。即这两个团是 $S$ 和 $T$，不管操作哪个点，剩下的仍然是两个团，相当于把一个点扔到另一个团中。所以最小操作次数就是 $\min(|S|, |T|)$。

判断 $G$ 是否是完全图的方法：$\forall x \in G, \deg_x = |G| - 1$。这些都可以通过 dfs 找出来。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 5005;

int n;

vector<int> g[N];

bool isClique[N];
int bel[N];
int deg[N];

void dfs(int u, int root, vector<int> &cli) {
    bel[u] = root;
    cli.emplace_back(u);
    for (auto v: g[u])
        if (!bel[v])
            dfs(v, root, cli);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        for (int i = 1; i <= n; i++) {
            g[i].clear();
            bel[i] = isClique[i] = deg[i] = 0;
        }
        cin >> n;

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                char c; cin >> c;
                if (c == '1')
                    g[i].emplace_back(j), deg[j]++;
            }

        int tot = 0;
        int alone = 0;
        vector<int> clique;

        for (int i = 1; i <= n; i++)
            if (!bel[i]) {
                vector<int> cli;
                dfs(i, ++tot, cli);
                int valid = 1;
                for (auto j: cli)
                    valid &= g[j].size() == cli.size() - 1;
                if (valid) clique.emplace_back(i), isClique[tot] = 1;
                if (valid && !g[i].size())
                    alone = i;
            }

        if (tot == 1) {
            cout << "0\n";
            continue;
        }

        if (alone) {
            cout << "1\n" << alone << "\n";
            continue;
        }

        if (tot != clique.size()) {
            int x = 0, d = n;
            for (int i = 1; i <= n; i++) {
                if (isClique[bel[i]]) continue;
                if (deg[i] < d) {
                    x = i;
                    d = deg[i];
                }
            }
            cout << "1\n" << x << "\n";
            continue;
        }

        if (clique.size() > 2) {
            cout << "2\n" << clique[0] << " " << clique[1] << "\n";
            continue;
        }

        if (g[clique[0]].size() + 1 > g[clique[1]].size() + 1) swap(clique[0], clique[1]);

        cout << g[clique[0]].size() + 1 << "\n";
        cout << clique[0] << " ";
        for (auto j: g[clique[0]])
            cout << j << " ";

        cout << "\n";

    }
    return 0;
}
```

---

## 作者：GJX_Algorithm (赞：0)

# CF1761E 题解
## 题目描述
- 给定一张无向图。

- 你可以进行一种操作，具体内容如下：

  1. 选择任意点 $x$。
 
  2. 如果点 $x$ 与 点 $y$ 之间有一条边，则删去这条边；反之则添加这条边。
 
- 现在需要你求出最少操作次数使得这个图联通以及其方案。

## 解题思路
- 如果这张图本身就是联通的，则答案为 0。

- 如果这张图本身不连通，那么其一定会被分成几个连通块，此时我们需要分情况讨论：

  1. 如图，**如果某个连通块只有一个点**，说明没有任何点与它连边，那么只需要操作这个点，即可联通：
  ![](https://cdn.luogu.com.cn/upload/image_hosting/tsi21iso.png)

  2. 如下图，**如果图中有某个连通块不是完全图**，则操作那个连通块中任意一个破坏了完全图的那些点（及没有与连通块中其他点都连边的点），不过要注意，**该点如果是割点，可能会出错**：
  ![](https://cdn.luogu.com.cn/upload/image_hosting/v5z49ibf.png)
  ![](https://cdn.luogu.com.cn/upload/image_hosting/ft2tuz3i.png)
  ![](https://cdn.luogu.com.cn/upload/image_hosting/qs8webpv.png)
 
  3. **如果图中只有两个连通块，且它们都是完全图**，我们发现，无论在连通块里删去那个点，剩下的点依然可以组成一个完全图，而那个删去的点又会与另外一个连通块组成一个新的完全图。故而要把某个连通块的点全部操作完才能使该图联通。
 
  4. **如果图中有三个及三个以上的连通块**，先随便对一个点进行操作，发现现在图被分成一个不是完全图的连通块（由添加边造成的）和一个是完全图的连通块（由删去边造成的），此时再进行情况 2 的步骤即可。


## 代码
```cpp
//本代码不知何原因，一直Time limit exceeded on test 10
#include<bits/stdc++.h>
using namespace std;
const int N = 4005;
int t, n;
int cnt, tot, cnt1, root;
int to[N], nxt[N], head[N];
int dfn[N], low[N];
int edge[N][N];
vector<int> Connected_blocks[N];
bool vis[N], cut[N];
char s[N];
void add(int u, int v)
{
    nxt[++tot] = head[u];
    head[u] = tot, to[tot] = v;
    return ;
}
void dfs(int id, int cur)
{
    Connected_blocks[id].push_back(cur); //存连通块
    for (int i = head[cur]; ~i; i = nxt[i])
    {
        int nex = to[i];
        if (vis[nex] == 0)
        {
            vis[nex] = 1;
            dfs(id, nex);
        }
    }
    return ;
}
void tarjan(int cur)
{
    dfn[cur] = low[cur] = ++cnt1;
    int sum = 0;
    for (int i = head[cur]; ~i; i = nxt[i])
    {
        int nex = to[i];
        if (dfn[nex] == 0)
        {
            tarjan(nex);
            low[cur] = min(low[cur], low[nex]);
            sum++;
            if (low[nex] >= dfn[cur] && (cur != root || sum >= 2))
                cut[cur] = 1;
        }
        else low[cur] = min(low[cur], dfn[nex]);
    }
    return ;
}
void init()
{
    fill(head + 1, head + 1 + n, -1);
    fill(nxt + 1, nxt + 1 + tot, 0);
    fill(to + 1, to + 1 + tot, 0);
    fill(low + 1, low + 1 + n, 0);
    fill(dfn + 1, dfn + 1 + n, 0);
    fill(cut + 1, cut + 1 + n, 0);
    fill(vis + 1, vis + 1 + n, 0);
    tot = cnt1 = 0;
    for (int i = 1; i <= cnt; i++) Connected_blocks[i].clear();
    cnt = 0;
    return ;
}
void solve()
{
    //输入与建边
    scanf("%d", &n);
    init();
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", s + 1);
        for (int j = 1; j <= n; j++)
        {
            edge[i][j] = (int)(s[j] - '0');
            if (edge[i][j] == 1)
                add(i, j); //建边
        }
    }
    //找连通块
    for (int i = 1; i <= n; i++)
        if (vis[i] == 0)
        {
            vis[i] = 1;
            dfs(++cnt, i);        
        }
    //tarjan求割点
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
        {
            root = i;
            tarjan(i);
        }
    //判断联通情况
    if (cnt == 1) //已经联通
    {
        printf("%d\n", 0);
        return ;
    }
    //判断情况1
    for (int i = 1; i <= cnt; i++)
        if (Connected_blocks[i].size() == 1)
        {
            printf("%d\n%d\n", 1, Connected_blocks[i][0]);
            return ;
        }
    //判断情况2
    for (int id = 1; id <= cnt; id++)
    {
        bool flag = 0;
        int ans = 0;
        for (int cur : Connected_blocks[id])
            for (int nxt : Connected_blocks[id])
            {
                if (cur == nxt) continue;
                if (edge[cur][nxt] == 0 && cut[cur] == 0)
                {
                    flag = 1, ans = cur;
                    goto end;
                }
                else if (edge[cur][nxt] == 0 && cut[nxt] == 0)
                {
                    flag = 1, ans = nxt;
                    goto end;
                }
            }
        end:
        if (flag == 1)
        {
            printf("%d\n%d\n", 1, ans);
            return ;
        }
    }
    //判断情况3
    if (cnt == 2)
    {
        if (Connected_blocks[1].size() > Connected_blocks[2].size())
        {
            printf("%d\n", Connected_blocks[2].size());
            for (int i : Connected_blocks[2]) 
                printf("%d ", i);
        }
        else
        {
            printf("%d\n", Connected_blocks[1].size());
            for (int i : Connected_blocks[1]) 
                printf("%d ", i);
        }
        printf("\n");
    }
    //判断情况4
    if (cnt >= 3)
    {
        printf("%d\n%d ", 2, 1);
        //先随便找个点，模拟增边删边
        init();
        for (int i = 2; i <= n; i++) edge[1][i] = edge[i][1] = edge[1][i] ^ 1; //0变1，1变0
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (edge[i][j] == 1)
                    add(i, j);
        for (int i = 1; i <= n; i++)
            if (vis[i] == 0)
            {
                vis[i] = 1;
                dfs(++cnt, i);        
            }
        for (int i = 1; i <= n; i++)
            if (dfn[i] == 0)
            {
                root = i;
                tarjan(i);
            }
        //进行情况2
        for (int id = 1; id <= cnt; id++)
        {
            bool flag = 0;
            int ans = 0;
            for (int cur : Connected_blocks[id])
                for (int nxt : Connected_blocks[id])
                {
                    if (cur == nxt) continue;
                    if (edge[cur][nxt] == 0 && cut[cur] == 0)
                    {
                        flag = 1, ans = cur;
                        goto end1;
                    }
                    else if (edge[cur][nxt] == 0 && cut[nxt] == 0)
                    {
                        flag = 1, ans = nxt;
                        goto end1;
                    }
                }
            end1:
            if (flag == 1) printf("%d\n", ans);
        }
    }
    return ;
}
int main()
{
    scanf("%d", &t);
    while (t--) solve();
    return 0;
}
```

---

## 作者：Yuzimy (赞：0)

这一题的难度主要在于分讨吧……我感觉除了分讨，性质其实是很好找到的。

分成以下五种情况讨论：

### I.图连通

没什么好说的，直接输出 ```0``` 即可。

### II.子图中存在至少一个非完全图

既然不能图连通，说明至少有一次的操作~~废话~~。由于贪心的思想，我们最好需要找到某个点使得建反边原来的图还是连通的。其实有一个很好的结论。结论如下：

**在任意非完全连通图（非孤立点）中，都存在至少一个点 $u$，使得建了 $u$ 的反边之后，图仍然连通。**

考虑反证法。若结论不成立，则说明对于每个点，建反边之后都会使得图不连通。

所以可推得这个图中度数最小的点 $u$，使得建了 $u$ 的反边之后，图不连通。

我们很容易发现，一个点在非孤立点的非完全连通图中，具有建了它的反边之后图不连通的性质当且仅当它是割点且连接至少有一个大小为 $sum$ 的连通子图的边的数量恰好等于 $sum$。

假设 $u$ 连接的最小的连通子图的大小为 $sum$。易得 $u$ 的大小至少为 $sum$ 。而大小为 $sum$ 的连通子图中的点的度数最多为 $sum-1$，与假设条件不符。故结论成立。

同事我们还可以得到另外一个性质：

**对于任意非完全连通子图，度数最小的点 $u_0$ 使得建了 $u_0$ 的反边之后，图仍然连通。** 

对于这种情况，只需要取非完全图中的度数最小点即可。

### III.存在至少 1 个孤立点

只需要执行孤立点即可。

### IV.原图可分成 2 个完全图

无论执行图上的任意点，原图的最大连通子图个数只能为 $1$ 或 $2$。此处感性理解即可。然后只需要执行较小的那个连通子图即可。

### V.原图可分成 3 个及以上完全图

我们随便找一个点执行，然后它操作后所连成的图又是一个非完全图。执行 I 操作即可。

最后放下代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e3+5;
int n,deg[N],sz[N],fa[N],vis[N];
char s[N][N];
vector<int>E[N],sub;
void init(){
	sub.clear();
	for(int i=1;i<=n;i++){
		sz[i]=0;
		vis[i]=0;
		fa[i]=i;
		deg[i]=0;
		E[i].clear();
	}
}
int Find(int x){
	if(fa[x]==x){
		return x;
	}
	return fa[x]=Find(fa[x]);
}
void merge(int u,int v){
	u=Find(u),v=Find(v);
	fa[u]=v;
}
int tmp[N];
bool cmp(int A,int B){
	return deg[A]<deg[B];
}
void solve(){
	scanf("%d",&n);
	init();
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(s[i][j]=='1'){
				deg[i]++;
				merge(i,j);
			}
		}
	}
	bool check0=1,check1=0,check2=0,check3;
	for(int i=1;i<=n;i++){
		sz[Find(i)]++;
		E[Find(i)].push_back(i);
		if(!vis[Find(i)]){
			vis[Find(i)]=1;
			sub.push_back(Find(i));
		}
	}
	for(int i=1;i<=n;i++){
		check0&=sz[Find(i)]==n;
		check1|=sz[Find(i)]!=deg[i]+1;
		check2|=sz[Find(i)]==1;
	}
	check3=sub.size()==2;
	if(check0){
		printf("%d\n",0);
	}else if(check1){
		printf("%d\n",1);
		for(int i=1;i<=n;i++){
			if(sz[Find(i)]!=deg[i]+1){
				int u=Find(i),sum=0;
				for(int j=0;j<E[u].size();j++){
					int v=E[u][j];
					tmp[++sum]=v;
				}
				sort(tmp+1,tmp+sum+1,cmp);
				printf("%d\n",tmp[1]);
				break;
			}
		}
	}else if(check2){
		printf("%d\n",1);
		for(int i=1;i<=n;i++){
			if(sz[Find(i)]==1){
				printf("%d\n",i);
				break;
			}
		}
	}else if(check3){
		int U=sub[0],V=sub[1];
		if(sz[sub[0]]>sz[sub[1]]){
			swap(sub[0],sub[1]);
		}
		printf("%d\n",sz[sub[0]]);
		for(int i=0;i<E[sub[0]].size();i++){
			printf("%d ",E[sub[0]][i]);
		}
		printf("\n");
	}else{
		printf("%d\n",2);
		printf("%d ",sub[0]);
		int sum=0;
		for(int i=1;i<sub.size();i++){
			for(int j=0;j<E[sub[i]].size();j++){
				tmp[++sum]=E[sub[i]][j];
			}
		}
		sort(tmp+1,tmp+sum+1,cmp);
		printf("%d\n",tmp[1]);
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n+1;j++){
			s[i][j]=0;
		}
	}
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		solve();
	}
	return 0;
}
```


---

