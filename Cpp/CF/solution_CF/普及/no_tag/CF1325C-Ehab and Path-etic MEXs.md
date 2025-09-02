# Ehab and Path-etic MEXs

## 题目描述

You are given a tree consisting of $ n $ nodes. You want to write some labels on the tree's edges such that the following conditions hold:

- Every label is an integer between $ 0 $ and $ n-2 $ inclusive.
- All the written labels are distinct.
- The largest value among $ MEX(u,v) $ over all pairs of nodes $ (u,v) $ is as small as possible.

Here, $ MEX(u,v) $ denotes the smallest non-negative integer that isn't written on any edge on the unique simple path from node $ u $ to node $ v $ .

## 说明/提示

The tree from the second sample:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1325C/3987a692dde98854639547ed68f742fb6eeb5979.png)

## 样例 #1

### 输入

```
3
1 2
1 3```

### 输出

```
0
1```

## 样例 #2

### 输入

```
6
1 2
1 3
2 4
2 5
5 6```

### 输出

```
0
3
2
4
1```

# 题解

## 作者：Provicy (赞：13)

~~昨晚没空打 CF，于是就口胡了下 C（雾~~

题意：给一棵有 $n$ 个结点的树，每条边的边权是 $0$ ~ $n-2$ 中的一个整数且两两不同。对于树上任意两个结点 $u,v(u\not=v)$，求出 $Ans=max\{MEX(u,v)\}$。我们需要给每条边添加边权使得 $Ans$ 最小。

首先发现当这棵树是一条链的时候无论如何添加边权，$Ans_{min}$ 也是 $n-1$。此时随便构造即可。

当这棵树不为一条链时，我们想让一条包含 $0$ 的路径上避免出现连续 $1,2,3$ 边权的边，但是无论如何构造，边权为 $0,1$ 的两条边总能出现在某条路径上，所以我们考虑如何使得边权为 $0,1,2$ 的这三条边无法同时出现在某一路径上。这是很容易的，因为当这棵树不为一条链时，必然有一个度数大于等于 $3$ 的结点，则我们把 $0,1,2$ 作为与这个结点相邻的任意 $3$ 个结点与其连边的边权，其他边随意赋值即可，这样 $Ans_{min}=2$，且不可能有比这个更优的方案，因为无论如何构造，$Ans_{min}\geq2$。

代码如下：
```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <vector>
#include <stack>
#include <map>
#define ri register
#define inf 0x7fffffff
#define E (1)
#define mk make_pair
#define int long long
using namespace std; const int N=500010;
inline int read()
{
	int s=0, w=1; ri char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') w=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48), ch=getchar(); return s*w;
}
void print(int x) {if(x<0) x=-x, putchar('-'); if(x>9) print(x/10); putchar(x%10+'0'); }
int n,deg[N],maxd,book[N]; vector<int> e[N];
signed main()
{
	n=read();
	for(ri int i=1;i<n;i++)
	{
		int u=read(), v=read();
		e[u].push_back(i);
		e[v].push_back(i);
		deg[u]++, deg[v]++;
	}
	int maxd=0,cnt=0;
	for(ri int i=1;i<=n;i++) maxd=max(maxd,deg[i]);
	if(maxd<3)
	{
		for(ri int i=0;i<n-1;i++) printf("%lld\n",i);
		return 0;
	}
	for(ri int i=1;i<=n;i++)
	{
		if(deg[i]>=3)
		{
			for(ri int j=0;j<3;j++) book[e[i][j]]=++cnt;
			break;
		}
	}
	for(ri int i=1;i<n;i++) if(!book[i]) book[i]=++cnt;
	for(ri int i=1;i<n;i++) printf("%lld\n",book[i]-1);
	return 0;
}
```


---

## 作者：Limit (赞：7)

CF神奇构造题

# 题目大意

给出一颗 $N$ 个节点树,每条边有边权,边权为 $0$ 到 $N-2$ 的整数,且不重复,使得任意两点的简单路径的MEX的最大值最小.(MEX指第一个没有出现过的非负整数)

# 分析

对于MEX最重要自然是 $0$,而且因为是树,所以必然可以做到将 $0$ 和 $1$ 放入同一条树链中,那么就要考虑 $2$ 的位置了,不可以让他出现在这条树链中,理解一下就是必须有一个点的度至少为 $3$,即这个图不是一条链,那么就有一种非常容易的方法,将 $0,1,2$ 放在三个度为 $1$ 的点的边上,这样就不可能出现 $0,1,2$ 同时出现在一条链上,其他也就可以乱放了,如果是一条链无论怎么放MEX都可以达到 $N-1$,所以可以直接乱放.

# 代码

```cpp
#include<bits/stdc++.h>
#define REP(i,first,last) for(int i=first;i<=last;++i)
#define DOW(i,first,last) for(int i=first;i>=last;--i)
using namespace std;
const int MAXN=114514;
int N,M;
int T;
int out[MAXN];//记录度
int p[MAXN];//比较懒,不想存图,所以就只记录一下每个点最后一条出边,反正最后有影响的之后度为1的点,所以没关系
int answer[MAXN];//记录答案
void work()
{
	scanf("%d",&N);
	int f,t;
	REP(i,1,N-1)
	{
		scanf("%d%d",&f,&t);
		out[f]++;
		out[t]++;
		p[f]=p[t]=i;
	}
	if(N==2)//注意特判2
	{
		printf("%d",0);
		return;
	}
	int cnt=0;
	REP(i,1,N)
	{
		if(out[i]==1)//在前三个度为1的点的出边赋值上0,1,2,为了方便处理这里就用了1,2,3
		{
			answer[p[i]]=++cnt;
			if(cnt==3)
			{
				break;
			}
		}
	}
	REP(i,1,N-1)//输出
	{
		if(answer[i])//如果有答案就输出答案
		{
			printf("%d\n",answer[i]-1);
		}
		else//没有反正可以乱输出
		{
			++cnt;
			printf("%d\n",cnt-1);
		}
	}
}
int main()
{
	work();
	return 0;
}
```

---

## 作者：huayucaiji (赞：5)

~~首先这道题我读了20min才读懂~~

闲话不多说，我们先来看题。通过思考，我们发现，其实我们只需要考虑边权为 $0,1,2$ 的边。为什么呢？首先，我们来讲一个~~废话~~真命题：对于任意两条边，他们肯定同时出现在一条也是唯一一条链上。

因此我们发现，题目中所提到的 $\max_{(u,v)\in E} MEX(u,v)$，无论如何，最小值至少为2，因为 $0,1$ 肯定出现在一条链上。而对于答案是否大于 $2$，我们就要分析边权为 $2$ 的这条边了。所以，为了使 $0,1,2$，不再一条链上，我们需要找到如下图的“T型” ，如果能找到，那么答案就为2，找到一个“T型”，然后把 $0,1,2$ 分别放上去即可。

![C](http://image.qingtengbc.com/2020/03/16/e6237c89c9fb5.png)

但如果找不到呢？是不是要考虑 $3$？

其实不用，如果找不到“T型”，那么，这棵树就退化成了一条链，那么所有边在一条链上（也只有一条链），所以边权随意乱放，答案也都一样。这道题就分析完了。

```cpp
//#pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
//#pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int maxn=1e5+10;

int n,ans[maxn];
vector<int> bi[maxn];


signed main() {
	
	n=read();
	fill(ans,ans+n+1,-1);
	for(int i=1;i<n;i++) {
		int a=read(),b=read();
		bi[a].push_back(i);
		bi[b].push_back(i);
	}
	int now=0;
	for(int i=1;i<=n;i++) {
		if(bi[i].size()>=3) {
			for(int j=0;j<3;j++) {
				ans[bi[i][j]]=j;
			}
			now=3;
			break;
		}
	}
	for(int i=1;i<n;i++) {
		if(ans[i]==-1) {
			ans[i]=now++;
		}
	}
	for(int i=1;i<n;i++) {
		cout<<ans[i]<<endl;
	}
	return 0;
}

```

---

## 作者：dead_X (赞：1)

## 1 题意简述
给你一棵树，让你给这棵树的边标号 $0,1,\cdots,n-1$，使得任意两点的最短路径中没有出现的最小非负整数的最大值最小。
## 2 思路简述
如果是一条链，随便标，因为可以取两边。

如果不是一条链，找一个度大于 $2$ 的点，并且选三条连着的边标上 $0,1,2$ ，其余随便标。因为这样可以使答案最大为 $2$ ，显然答案不能为 $1$，所以是最优策略。
## 3 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> a[100003];
int u[100003],v[100003];
int main()
{
	int n,k=-1;
	scanf("%d",&n);
	for(int i=1; i<n; i++) scanf("%d%d",&u[i],&v[i]),a[u[i]].push_back(v[i]),a[v[i]].push_back(u[i]);
	for(int i=1; i<=n; i++) if(a[i].size()>2) 
	{
		k=i;
		break;
	}
	if(k==-1) 
	{
		for(int i=1; i<n; i++) printf("%d\n",i-1);
		return 0;
	}
	int now=3;
	for(int i=1; i<n; i++) if(u[i]==k)
	{
		if(v[i]==a[k][0]) printf("0\n");
		else if(v[i]==a[k][1]) printf("1\n");
		else if(v[i]==a[k][2]) printf("2\n");
		else printf("%d\n",now++);
	 } 
	 else if(v[i]==k)
	 {
	 	if(u[i]==a[k][0]) printf("0\n");
		else if(u[i]==a[k][1]) printf("1\n");
		else if(u[i]==a[k][2]) printf("2\n");
		else printf("%d\n",now++);
	 }
	 else printf("%d\n",now++);
	return 0;
}
 
```
## 4 评价
始终没想出来/kel

还是zk提醒我的/qq

zk不愧是我的npy啊

建议难度 黄

---

## 作者：TLE_Automat (赞：0)

看了看其他dalao的思路，发现和我的都不一样，于是来水一篇题解。

PS：~~我是不会告诉你我比赛的时候因为代码写挂了然后开心掉分的。~~

进入正题：咳咳，其实本题的思路很简洁：显然的结论，树上任何两点间的简单路径都不可能同时经过所有叶子节点（除非树的形态是一条链，我们先不考虑），所以 $MEX(u,v)$ 中取最小值的边集一定包含叶子节点所连的边，而题目又要求把 $\max(MEX(u,v))$ 最小化，这就意味着我们只要把叶子节点所连的边的权值最小化，剩下的随便赋值就行了，对于链，接随便瞎赋值就行了！(逃

怎么样？思路听起来是不是很简洁。然而蒟蒻因为码力太弱当场写挂，调了 $1h$ 没调出来，然后成功开心下分。

加一句:别忘了特判 $n=2$ 的情况！

$Code:$


```cpp
#include <bits/stdc++.h>

using namespace std;

struct Edge
{
    int to;
    int nxt;
};

int n;
int cnt;
int tot;
int head[100010];
int in[100010];
int uu[100010];
int vv[100010];
int ans[100010];
Edge e[100010<<1];

inline void addedge(int u,int v)
{
    e[cnt].to=v;
    e[cnt].nxt=head[u];
    head[u]=cnt;
    cnt++;
}

inline void dfs1(int u,int last)
{
    if(in[u]==1)
    {
        ans[u]=tot++;
    }
    for(int i=head[u];i!=-1;i=e[i].nxt)
    {
        int v=e[i].to;
        if(v==last) continue;
        dfs1(v,u);
    }
}

int main()
{
    memset(head,-1,sizeof(head));
    memset(ans,-1,sizeof(ans));
    scanf("%d",&n);
    for(int i=1;i<=n-1;i++)
    {
        scanf("%d%d",&uu[i],&vv[i]);
        addedge(uu[i],vv[i]);
        addedge(vv[i],uu[i]);
        in[uu[i]]++;
        in[vv[i]]++;
    }
    if(n==2)
    {
        puts("0");
        return 0;
    }
    dfs1(1,0);
    for(int i=1;i<=n-1;i++)
    {
        if(in[uu[i]]>1 && in[vv[i]]>1)
        {
            printf("%d\n",tot++);
        }
        else
        {
            if(in[uu[i]]==1)
                printf("%d\n",ans[uu[i]]);
            else
                printf("%d\n",ans[vv[i]]);
        }
    }
    return 0;
}
```

求管理员大大通过qwq。


---

## 作者：Clever_Jimmy (赞：0)

#### C. Ehab and Path-etic MEXs [题目链接](https://codeforces.ml/contest/1325/problem/C)

1.  如果是一条链，那么随便填都是可以的。

2.  如果不是一条链：

    我们可以找到一个度数大于等于 $3$ 的点，将它的任意三条连边填上 $0, 1, 2$，剩下的随便填。

    显然此时的答案为 $2$，且不可能有答案为 $1$ 的方案。

    因此这个方案最优。

[code](https://codeforces.ml/contest/1325/submission/73256891)

---

## 作者：gyh20 (赞：0)

分情况考虑。

如果原图是一条链，则随意安排。

否则一定存在一个度 $>2$ 的点，只要把 $0,1,2$ 分别放在这个点连出的 $3$ 条边中，就能保证不存在 $mex(u,v) >2$ 的点，（无法保证 $mex(u,v)>1$，因为 $0,1$ 这两条边无论怎样都可以在同一条链上）。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;
	re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0'){
		t=(t<<3)+(t<<1)+v-48;
		v=getchar();
	}
	return t;
}
int n,m,cnt,head[400002];
struct edge{
	int to,next;
}e[400002];
inline void add(re int x,re int y){
	e[++cnt].to=y;
	e[cnt].next=head[x];
	head[x]=cnt;
}
int rd[400002],p[400002],v[400002],tot,vis[400002];
inline bool cmp(re int x,re int y){
	return rd[x]>rd[y];
}
int main(){
	n=read();
	for(re int i=1;i<n;++i){
		re int x=read(),y=read();
		add(x,y);
		add(y,x);
		++rd[x];
		++rd[y];
	}
	for(re int i=1;i<=n;++i)p[i]=i;
	sort(p+1,p+n+1,cmp);
	for(re int i=1;i<=n;++i){
		vis[p[i]]=1;
		for(re int j=head[p[i]];j;j=e[j].next){
			if(!vis[e[j].to])v[j]=tot++;
		}
	}
	for(re int i=1;i<=cnt;i+=2)printf("%d\n",v[i]+v[i+1]);
}
```


---

