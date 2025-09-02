# Bear and Fair Set

## 题目描述

Limak is a grizzly bear. He is big and dreadful. You were chilling in the forest when you suddenly met him. It's very unfortunate for you. He will eat all your cookies unless you can demonstrate your mathematical skills. To test you, Limak is going to give you a puzzle to solve.

It's a well-known fact that Limak, as every bear, owns a set of numbers. You know some information about the set:

- The elements of the set are distinct positive integers.
- The number of elements in the set is $ n $ . The number $ n $ is divisible by $ 5 $ .
- All elements are between $ 1 $ and $ b $ , inclusive: bears don't know numbers greater than $ b $ .
- For each $ r $ in $ {0,1,2,3,4} $ , the set contains exactly ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF628F/3fde03ba1459bf896eaa2d517e8e4b61f6946c2a.png) elements that give remainder $ r $ when divided by $ 5 $ . (That is, there are ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF628F/3fde03ba1459bf896eaa2d517e8e4b61f6946c2a.png) elements divisible by $ 5 $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF628F/3fde03ba1459bf896eaa2d517e8e4b61f6946c2a.png) elements of the form $ 5k+1 $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF628F/3fde03ba1459bf896eaa2d517e8e4b61f6946c2a.png) elements of the form $ 5k+2 $ , and so on.)

Limak smiles mysteriously and gives you $ q $ hints about his set. The $ i $ -th hint is the following sentence: "If you only look at elements that are between $ 1 $ and $ upTo_{i} $ , inclusive, you will find exactly $ quantity_{i} $ such elements in my set."

In a moment Limak will tell you the actual puzzle, but something doesn't seem right... That smile was very strange. You start to think about a possible reason. Maybe Limak cheated you? Or is he a fair grizzly bear?

Given $ n $ , $ b $ , $ q $ and hints, check whether Limak can be fair, i.e. there exists at least one set satisfying the given conditions. If it's possible then print ''fair". Otherwise, print ''unfair".

## 说明/提示

In the first example there is only one set satisfying all conditions: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}.

In the second example also there is only one set satisfying all conditions: {6, 7, 8, 9, 10, 11, 12, 13, 14, 15}.

Easy to see that there is no set satisfying all conditions from the third example. So Limak lied to you :-(

## 样例 #1

### 输入

```
10 20 1
10 10
```

### 输出

```
fair
```

## 样例 #2

### 输入

```
10 20 3
15 10
5 0
10 5
```

### 输出

```
fair
```

## 样例 #3

### 输入

```
10 20 2
15 3
20 10
```

### 输出

```
unfair
```

# 题解

## 作者：45dino (赞：5)

这一题最大流是能做，但提供一个更简单的做法，可以将题目难度降低很多。

可以发现，如果判断是否能取出 $n$ 个**只符合大小限制**的数并不能证明一定满足，同理，只是分别判断对于模5余0~4的符合大小限制的数能否取出也无法说明什么。

于是想到，如果尝试着对于每一种组合进行判断是否可行。

可以举个例子：
```
10 20 3
15 10
5 0
10 5
```
将区间排序，整理，得到：

区间1：$[1,5]$，可以取 $0$ 个数；

区间2：$[6,10]$，可以取 $5$ 个数；

区间3：$[11,15]$，可以取 $5$ 个数；

区间4：$[16,20]$，可以取 $0$ 个数。

对于一种组合 ```11000``` ,代表区间只包含模5余0，1的数。

则对于区间1，有 $2$ 个数符合条件，只能取 $0$ 个数；

对于区间2，有 $2$ 个数符合条件，可以取 $2$ 个数；

……

最后最多可以取 $0+2+2+0=4$ 个数，大于等于 $2\times \frac n 5=4$。

将 $2^5=32$ 种情况逐一尝试，如果全部满足，则可以证明存在这样的区间，大概可以用反证法证明。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,b,q;
vector<pair<int,int>>v;
int main()
{
	scanf("%d%d%d",&n,&b,&q);
	for(int i=1;i<=q;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		v.push_back({x,y});
	}
	v.push_back({b,n});
	sort(v.begin(),v.end());
	for(int i=0;i<v.size()-1;i++)
		if(v[i].second>v[i+1].second)
			return puts("unfair");
	for(int k=0;k<32;k++)
	{
		int can=0;
		for(int i=0;i<=q;i++)
		{
			int pre=i?v[i-1].first+1:1;
			int quan=i?v[i].second-v[i-1].second:v[i].second;
			int s=0;
			for(int j=pre;j<=v[i].first;j++)
				if((k>>(j%5))&1)
					s++;
			can+=min(quan,s);
		}
		if(can<n/5*__builtin_popcount(k))
			return puts("unfair");
	}
	puts("fair");
	return 0;
}

```


---

## 作者：xtx1092515503 (赞：5)

~~乍一看，什么破题目，根本不可做！~~

实际上，是**网络流**，建图比较毒瘤，建议紫题或以上，标签最大流。

（数组含义以英文题面为准）

为了方便，我们添加两组新的限制：
$upTo_0=0,quantity_0=0$以及$upTo_{q+1}=b,quantity_{q+1}=n$

之后，将$q$改变为$q+1$（因为添加了原来的第$q+1$组限制）。

这个时候，我们就可以将集合分成$q$段。对$\forall i \in [1,q]$，第$i$段中有$(quantity_i-quantity_{i-1})$个值域在$(upTo_{i-1},upTo_i]$的数。

这时候就可以建图了。

**前置知识：在区间$(i,j]$中，模$5$余$k$的数有$(j-k)/5-(i-k)/5$个，其中$/$是整除符号。**

设$id_i$为表示模5余$i$的节点的**虚拟节点**。

则从源点$S$，我们向每个$i$连$quantity_i$单位流量；

再从每个$i$，向每个$id_j$，连 **$(upTo_{i-1},upTo_i]$中模$5$余$j$的数的数量** 的流量

最后从每个$id_i$向汇点$T$连$n/5$的流量

之后跑最大流即可。如果最大流不是$n$，则不合法。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
pair<int,int>p[10100];
int n,lim,m,head[20100],cur[20100],dep[20100],cnt,id[5],S,T,res;
struct node{
	int to,next,val;
}edge[200100];
void ae(int u,int v,int w){
	edge[cnt].next=head[u],edge[cnt].to=v,edge[cnt].val=w,head[u]=cnt++;
	edge[cnt].next=head[v],edge[cnt].to=u,edge[cnt].val=0,head[v]=cnt++;
}
int calc(int L,int R,int mod){//Calculate the number of (%5=mod)'s nums in range (i,j] 
	R=R-mod+5,L=L-mod+5;
	return R/5-L/5;
}
bool reach;
queue<int>q;
bool bfs(){
	memset(dep,0,sizeof(dep)),dep[S]=1,q.push(S);
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=cur[x]=head[x];i!=-1;i=edge[i].next)if(edge[i].val&&!dep[edge[i].to])dep[edge[i].to]=dep[x]+1,q.push(edge[i].to);
	}
	return dep[T]>0;
}
int dfs(int x,int flow){
	if(x==T){reach=true;res+=flow;return flow;}
	int used=0;
	for(int &i=cur[x];i!=-1;i=edge[i].next){
		if(!edge[i].val||dep[edge[i].to]!=dep[x]+1)continue;
		int ff=dfs(edge[i].to,min(flow-used,edge[i].val));
		if(ff){
			edge[i].val-=ff;
			edge[i^1].val+=ff;
			used+=ff;
			if(used==flow)break;
		}
	}
	return used;
}
int main(){
	scanf("%d%d%d",&n,&lim,&m),memset(head,-1,sizeof(head));
	S=n+6,T=n+7;
	for(int i=0;i<5;i++)id[i]=n+i+1,ae(id[i],T,n/5);
	for(int i=1;i<=m;i++)scanf("%d%d",&p[i].first,&p[i].second);
	sort(p+1,p+m+1),m++,p[m]=make_pair(lim,n);
	for(int i=1;i<=m;i++)if(p[i].first-p[i-1].first<p[i].second-p[i-1].second||p[i].second<p[i-1].second){puts("unfair");return 0;}//if there are more numbers than the range, or in a larger range there's a smaller total,it is definitelt invalid. 
	for(int i=1;i<=m;i++)ae(S,i,p[i].second-p[i-1].second);
	for(int i=1;i<=m;i++)for(int j=0;j<5;j++)ae(i,id[j],calc(p[i-1].first,p[i].first,j));
	while(bfs()){
		reach=true;
		while(reach)reach=false,dfs(S,0x3f3f3f3f);
	}
//	printf("%d\n",res);
	puts(res==n?"fair":"unfair");
	return 0;
}
```



---

## 作者：SlyCharlotte (赞：1)

前面有神仙讲述了非网络流的神仙做法，这里讲述一下思考过程与正确性？
## 题意描述

是否存在一个有 $n,5 \mid n$ 个正整数构成的的集合 $S$，满足有 $\frac n 5$ 个数除以 $5$ 分别余 $0,1,2,3,4$，元素大小在 $[1,b]$ 之间，每个数只出现一次，且 $x,x\in S\cup [1,u_i]$ 的个数为 $t_i$。

## 简要分析

首先，元素大小在 $[1,b]$ 之间可以转换成 $x,x\in S\cup [1,b]$ 的个数为 $n$。

此时，若存在 $i,j$ 满足 $u_i < b_j,u_i > t_j$ 显然无解。

不考虑关于每个区间能选多少数的限制，可以直接枚举 $[1,b]$ 的数统计模 $5$ 等于 $0,1,2,3,4$ 的数量。

现在加上限制，然后对所有区间做差分。

这样就能得出在 $[l,r]$ 中能有多少数。

发现所有区间都是相邻的即区间与区间中间不会存在正整数。

如果加上限制再去统计模 $5$ 等于 $0,1,2,3,4$ 的数量是错误的。

可能会存在一个区间，在这个区间中只能选出 $x$ 个数，然而在这个区间中模 $5$ 等于 $0,1,2,3,4$ 的数都有 $x - 1$ 个。

此时统计模 $5$ 等于 $1$ 的时候，取出了这个区间内的 $x - 1$ 个数，然后加上其他区间的模 $5$ 为 $1$ 的数合法了，再统计模 $5$ 为 $2$ 的时候仍取出了这个区间内的 $x-1$ 个数，然后加上其他区间满足条件的数，再次合法。

问题出在没有考虑重复的情况，此时我们统计模 $5$ 为 $0 \cup1,1\cup2,\dots ,3 \cup4,0\cup1\cup2,\dots$，等等一共 $32$ 种情况就可以避免重复情况（类比容斥）。

若 $32$ 种情况中有一次不合法那么即为 `unfair`，全部合法即为 `fair`。

时间复杂度 $O(q \log q + b)$。

关于代码这里不再赘述。

---

## 作者：happybob (赞：1)

题意：有一个 $n$ 个数的整数集合，保证 $5\mid n$，每个数都在区间 $[1,b]$ 区间中，且 $n$ 个数中模 $5$ 余 $0,1,2,3,4$ 的数的个数都相同。现在有 $q$ 个限制，每个形如 $[1,u_i]$ 中在集合内的数的个数为 $t_i$，判断是否存在合法的一个集合。

解法：

考虑把所有限制离线排序，然后转化成前缀和差，就变成了若干个互不相交的区间，每个区间的和是某个数。注意这里需要添加一个 $[1,b]$ 有 $n$ 个数。

建立网络，建 $5$ 个虚点，从源点连向他们，每条边容量都是 $\dfrac{n}{5}$，然后每个虚点向相对应的余数为 $0,1,2,3,4$ 连边，容量为 $1$。限制变成新建一个虚点，将 $[l,r]$ 中每个点向这个虚点连边，容量为 $1$。虚点向汇点连边，容量为 $c$，$c$ 为这个区间中的数的个数。显然问题等价于最大流是否为 $n$。使用 Dinic 即可通过。

[Submmison Link.](https://codeforces.com/problemset/submission/628/257719474)

---

## 作者：cike_bilibili (赞：0)

可以跑上下界流。

首先建立 $5$ 个虚点，从源点往这 $5$ 个源点都建立上下界都为 $\frac{n}{5}$ 的边，表示模 $5$ 为 $0,1,2,3,4$ 的都要取 $\frac{n}{5}$ 个，然后建立 $b$ 个点表示不同取值，将对应的模 $5$ 的虚点与它们连 $[0,1]$ 的边，表示是否取这个数，然后将 $Q$ 个条件差分化后对应不相交的几段区间，将区间内的数与询问对应的点连 $[0,1]$ 的边，并将所有询问对应的边向汇点连上下界都为 $\Delta t$ 的边，跑可行流就行了。

---

## 作者：eee_hoho (赞：0)

感觉这题用不着高深的网络流建模技巧，直接二分图匹配不好吗。

考虑 $b$ 中每个数对每个余数匹配， $i\to i\%5$ ，流量为 $1$ 。

然后考虑对集合的限制，差分完之后可以得到每个区间恰好有几个数，设当前区间为 $[l,r]$ 建一个虚点 $x$ ， $S\to x$ ，流量为区间恰好的数的个数， $x\to i(l\le i\le r)$ ,流量为 $1$ 。

最后模数向 $T$ 连流量为 $\frac{n}{5}$ 的边。

我们还需要满足集合限制中的恰好，可以看作是一条边流量的上下界，直接跑有源有汇上下界可行流就行了。

跑的很快QAQ

**Code**
``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
const int N = 1e4;
const int inf = 1e9;
using namespace std;
struct qry
{
    int u,t;
}a[N + 5];
int n,b,q,idc,id1[N + 5],S,T,id2[10],t[N + 5],fl[N * 10 + 5];
namespace F
{
    const int N = 1e6;
    const long long inf = 2e18;
    struct edges
    {
        int to;
        long long cost;
    }edge[N * 2 + 5];
    int nxt[N * 2 + 5],head[N + 5],edge_cnt = 1,dis[N + 5],q[N + 5],cur[N + 5],S,T;
    void add_edge(int u,int v,long long w)
    {
        edge[++edge_cnt] = (edges){v,w};
        nxt[edge_cnt] = head[u];
        head[u] = edge_cnt;
    }
    void add(int u,int v,long long w)
    {
        add_edge(u,v,w);
        add_edge(v,u,0);
    }
    int bfs()
    {
        for (int i = 1;i <= idc;i++)
            cur[i] = head[i],dis[i] = 0;
        int l = 1,r = 0;
        dis[S] = 1;
        q[++r] = S;
        while (l <= r)
        {
            int u = q[l++];
            for (int i = head[u];i;i = nxt[i])
            {
                int v = edge[i].to,w = edge[i].cost;
                if (w && !dis[v])
                {
                    dis[v] = dis[u] + 1;
                    q[++r] = v;
                }
            }
        }
        return dis[T];
    }
    long long dfs(int u,long long flow)
    {
        if (u == T)
            return flow;
        long long sm = 0;
        for (int &i = cur[u];i;i = nxt[i])
        {
            int v = edge[i].to;
            long long w = edge[i].cost;
            if (dis[v] == dis[u] + 1 && w)
            {
                long long res = dfs(v,min(w,flow));
                edge[i].cost -= res;
                edge[i ^ 1].cost += res;
                sm += res;
                flow -= res;
                if (!flow)
                    break;
            }
        }
        return sm;
    }
    long long dinic(int s,int t)
    {
        S = s;T = t;
        long long ans = 0;
        while (bfs())
            ans += dfs(S,inf);
        return ans;
    }
    void clear()
    {
        edge_cnt = 1;
        for (int i = 1;i <= idc;i++)
            head[i] = 0;
        idc = 0;
    }
    bool check(int S,int T)
    {
        for (int i = head[S];i;i = nxt[i])
            if (edge[i].cost)
                return 0;
        for (int i = head[T];i;i = nxt[i])
            if (edge[i ^ 1].cost)
                return 0;
        return 1;
    }
}
bool cmp(qry a,qry b)
{
    return a.u < b.u;
}
int main()
{
    scanf("%d%d%d",&n,&b,&q);
    for (int i = 1;i <= q;i++)
        scanf("%d%d",&a[i].u,&a[i].t);
    S = ++idc;T = ++idc;
    for (int i = 1;i <= b;i++)
        id1[i] = ++idc;
    for (int i = 0;i <= 4;i++)
        id2[i] = ++idc;
    for (int i = 1;i <= b;i++)
        F::add(id1[i],id2[i % 5],1);
    sort(a + 1,a + q + 1,cmp);
    for (int i = 1;i <= q;i++)
    {
        if (!t[a[i].u])
            t[a[i].u] = a[i].t;
        else
        {
            if (t[a[i].u] != a[i].t)
            {
                cout<<"unfair"<<endl;
                return 0;
            }
        }
        if (a[i].u != a[i - 1].u)
        {
            int x = a[i].t - a[i - 1].t;
            if (x < 0)
            {
                cout<<"unfair"<<endl;
                return 0;
            }
            int nw = ++idc;
            F::add(S,nw,0);
            fl[S] -= x;
            fl[nw] += x;
            for (int j = a[i - 1].u + 1;j <= a[i].u;j++)
                F::add(nw,id1[j],1);
        }
    }
    for (int i = a[q].u + 1;i <= b;i++)
        F::add(S,id1[i],1);
    for (int i = 0;i <= 4;i++)
    {
        F::add(id2[i],T,0);
        fl[id2[i]] -= n / 5;
    }
    F::add(T,S,inf);
    fl[T] = n;
    int ss = ++idc,tt = ++idc;
    for (int i = 1;i <= idc;i++)
        if (fl[i] < 0)
            F::add(i,tt,-fl[i]);
        else
            if (fl[i] > 0)
                F::add(ss,i,fl[i]);
    int x = F::dinic(ss,tt);
    if (F::check(ss,tt))
        cout<<"fair"<<endl;
    else
        cout<<"unfair"<<endl;
    return 0;
}
```

---

