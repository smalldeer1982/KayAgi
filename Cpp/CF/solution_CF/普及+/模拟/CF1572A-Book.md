# Book

## 题目描述

给你一本有 $n$ 章的书。

每一章都有一个为理解本章而需要理解的其他章节的特定列表。要理解一个章节，你必须在理解了所需列表中的每一章后再阅读。

目前你还不了解任何章节。你要从头到尾反复阅读这本书，直到你理解整本书。请注意，如果您在阅读某一章节时不理解某些必要章节，则表示您暂时不能理解本章。

输出你要读多少次书才能理解每一章。如果你永远不会理解整本书，那么输出 $-1$。

## 样例 #1

### 输入

```
5
4
1 2
0
2 1 4
1 2
5
1 5
1 1
1 2
1 3
1 4
5
0
0
2 1 2
1 2
2 2 1
4
2 2 3
0
0
2 3 2
5
1 2
1 3
1 4
1 5
0```

### 输出

```
2
-1
1
2
5```

# 题解

## 作者：0xFF (赞：9)

#### 题目简述

------------


有一本书共有 $n$ 章，其中某些章节有前置章节，若第 $u$ 章是第 $v$ 章的前置章节，而你当前又没有看懂第 $u$ 章，那么，你当前一定看不懂第 $v$ 章，显然，没有前置章节的章节一遍就能看懂。
你可以一遍一遍从前往后的看这本书，问：你最少要读几遍这本书，才能将它的所有章节全部看懂。若永远不能看懂所有的章节，那么输出 $-1$。


数据范围：

$1 \leq T \leq 2 \cdot 10^{4}$，$1 \leq n \leq 2 \cdot 10^{5}$，$\sum k_{i} \leq 2 \cdot 10^{5}$。


#### 题目分析


------------

根据题目描述可以很容易的知道每一个章节都与其前置章节有关，故可以很容易地想到拓扑排序。具体实现步骤如下：

- 如果想要理解第 $x$ 章就必须要理解第 $y$ 章，那么我们可以连一条 $y → x$ 的边

- 使用优先队列对图进行拓扑排序，将阅读次数小的放在前面，若阅读次数相同则按照阅读章节编号排序。假设第 $x$ 章在第 $y$ 章理解之后就能理解，若 $x$ 大于 $y$ 则本次阅读就可以理解 $x$ 章，否则需要下一次才能理解第 $x$ 章。

- 若图中存在环则不满足拓扑排序的条件（有向无环图），故直接输出 $-1$。

- 直接输出阅读次数最多的章节读了多少遍

#### 代码实现


------------

```cpp
#include<iostream>
#include<cmath>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
const int N = 2e5 + 10;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
    return x*f;
}
int n,ind[N],tot,ans;
vector<int> nodes[N];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >q;
void tuopu(){
	for(int i=1;i<=n;i++){
		if(ind[i] == 0){
			q.push(make_pair(1,i));
		}
	}
	while(!q.empty()){
		int u = q.top().second;
		int s = q.top().first;
		q.pop();
		tot++;
		ans = max(ans,s);
		for(int i=0,len=nodes[u].size();i<len;i++){
			int v = nodes[u][i];
			if(--ind[v] == 0){
				if(v > u){
					q.push(make_pair(s,v));
				}
				else q.push(make_pair(s+1,v)); 
			}
		}
	} 
	return;
}
int main(){
	int T = read();
	while(T--){
		n = read();
		for(int i=1;i<=n;i++){
			nodes[i].clear();
		}
		tot = ans = 0;
		for(int i=1;i<=n;i++){
			ind[i] = read();
			for(int j=1;j<=ind[i];j++){
				int x = read();
				nodes[x].push_back(i);
			}
		}
		tuopu();
		if(tot < n)
			printf("-1\n");
		else printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：Eibon (赞：4)

阅读一本书的某个章节需要先阅读一些其它的章节，很容易联想到，这是一道图论题。

将每个章节视为一个点，让它的前置章节连接它，记录入度，然后拓扑排序。

发现读一本书需要从前往后读，不妨设置边权。

当前置章节的编号小于它时，令边权为零，因为可以在一次阅读中解决这两个点。

当前置章节的编号大于它时，令边权为一，因为需要在两次阅读中解决这两个点。

发现如果要解决掉某个点，需要取经过它时读书次数的最大值，只有这样才能确保这本书已经被读完。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+5;
const int mod=1e9+7;
int T,n,k,u,v,ans,tot,VIP;
int head[maxn],ru[maxn],output[maxn],vis[maxn];
struct edge
{
	int to,nxt,w;
};
edge e[maxn<<1];
void add(int u,int v,int w)
{
	e[++tot]={v,head[u],w};
	head[u]=tot;
}
queue<int>q;
void topo_sort()
{
	for(int i=1;i<=n;i++){
		if(!ru[i]){
			q.push(i);
			vis[i]=1;
			output[i]=1;
		}
	}
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			ru[v]--;
			output[v]=max(output[v],output[u]+e[i].w);
			if(!ru[v]){
				q.push(v);
				vis[v]=1;
			}
		}
	}
}
signed main()
{
	scanf("%lld",&T);
	while(T--){
		VIP=1;
		ans=0;
		scanf("%lld",&n);
		for(int i=1;i<=n;i++){
			tot=0;ru[i]=0;head[i]=0;
			vis[i]=0;output[i]=0;
		}
		for(int i=1;i<=n;i++){
			scanf("%lld",&k);
			for(int j=1;j<=k;j++){
				scanf("%lld",&u);
				if(u<i){
					add(u,i,0);
				}
				else{
					add(u,i,1);
				}
				ru[i]++;
			}
		}
		topo_sort();
		for(int i=1;i<=n;i++){
			if(vis[i]){
				ans=max(ans,output[i]);
			}
			else{
				printf("-1\n");
				VIP=0;
				break;
			}
		}
		if(VIP){
			printf("%lld\n",ans);
		}
	}
	return 0;
}
//dyyyyds
```

---

## 作者：123zbk (赞：3)

很容易想到拓扑排序。如果第 $u$ 章是第 $v$ 章的前置章节，那么就连一条从 $u$ 到 $v$ 的有向边。

读书时是按顺序从头读到尾，所以如果 $u>v$ 时边权为 $1$，代表需要多读一次书，否则边权为 $0$。

然后对图进行拓扑排序，从入度为 $0$ 的点开始，计算距离的最大值即为答案。

如果该图是一个有向无环图，则永远无法读完此书，输出 $-1$。

最后记得答案为 $dis+1$，因为入度为 $0$ 的点需要读书一次。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int in[maxn],head[maxn],vis[maxn],dis[maxn],tot,T,n,k,x,ans;
struct edge
{
	int to,nxt,w;
}e[maxn<<1];
void add(int u,int v,int w)
{
	++tot;
	e[tot].to=v;
	e[tot].nxt=head[u];
	e[tot].w=w;
	head[u]=tot;
	in[v]++;
}
queue <int> q;
void topo()
{
	for(int i=1;i<=n;i++)
	{
		if(in[i]==0)
		{
			q.push(i);
		}
	}
	for(int i=1;i<=n;i++)
	{
		dis[i]=0;
	}
	ans=0;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt)
		{
			int v=e[i].to;
			int w=e[i].w;
			dis[v]=max(dis[v],dis[u]+w);
			ans=max(ans,dis[v]); 
			in[v]--;
			if(in[v]==0)
			{
				q.push(v);
			}
		}
	}
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		int ok=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&k);
			for(int j=1;j<=k;j++)
			{
				scanf("%d",&x);
				add(x,i,x>i);
			}		
		}	
		topo();
		for(int i=1;i<=n;i++)
		{
			if(vis[i]==0)
			{
				ok=1;
			}
		}
		printf("%d\n",ok==1?-1:ans+1);
		tot=0;
		for(int i=1;i<=n;i++)
		{
			in[i]=head[i]=dis[i]=vis[i]=0;
		}
	}	
	return 0;
} 
```

---

## 作者：Tenshi (赞：3)

## 分析

这里提供一个比较自然的想法。

首先看到题面，从这些约束关系很容易想到**拓扑排序**。

接下来我们考虑学会编号为 $u$ 的章节需要的时间 $f_u$，那么答案就是 $\max f_u$。

记学会 $u$ 的前驱章节为 $pre$，那么我们有 $f_u = \max (f_{pre} + [pre>u])$。

> $[pre>u]$ 代表如果 $pre>u$ 取 $1$，反之取 $0$。



```cpp
// Problem: A. Book
// Contest: Codeforces - Codeforces Round #743 (Div. 1)
// URL: https://codeforces.com/problemset/problem/1572/A
// Memory Limit: 256 MB
// Time Limit: 1500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;

#define debug(x) cerr << #x << ": " << (x) << endl
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define dwn(i,a,b) for(int i=(a);i>=(b);i--)

using pii = pair<int, int>;
using ll = long long;

inline void read(int &x){
    int s=0; x=1;
    char ch=getchar();
    while(ch<'0' || ch>'9') {if(ch=='-')x=-1;ch=getchar();}
    while(ch>='0' && ch<='9') s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
    x*=s;
}

const int N=2e5+5, M=N<<1;

struct Edge{
	int to, w, next;
}e[M];

int h[N], tot;

void add(int u, int v, int w){
	e[tot].to=v, e[tot].w=w, e[tot].next=h[u], h[u]=tot++;
}

int n;
int deg[N], f[N];

int bfs(){
	queue<int> q;
	rep(i,1,n) if(!deg[i]) q.push(i);
	rep(i,1,n) f[i]=0;
	
	int cnt=0;
	while(q.size()){
		int u=q.front(); q.pop();
		cnt++;
		
		for(int i=h[u]; ~i; i=e[i].next){
			int go=e[i].to;
			f[go]=max(f[go], f[u]+e[i].w);
			if(--deg[go]==0){
				q.push(go);
			}
		}
	}
	
	if(cnt!=n) return -1;
	return *max_element(f+1, f+1+n)+1;
}

int main(){
	int T; cin>>T;
	while(T--){
		cin>>n;
		rep(i,1,n) h[i]=-1, deg[i]=0;
		tot=0;
		
		rep(i,1,n){
			int k; read(k);
			while(k--){
				int u; read(u);
				add(u, i, u>i);
				deg[i]++;
			}
		}
		
		cout<<bfs()<<endl;
	}	
	return 0;
}
```



---

## 作者：The_Godfather (赞：2)

# Problem
### [题目传送门](https://www.luogu.com.cn/problem/CF1572A)

# Solution
前置芝士：拓扑排序。

题目大意：我现在有一本 $n$ 个章节的书，我要读的书是有先后顺序的，要读第 $i$ 个章节就必须**先**读完 $k_i$ 个章节。

那么为什么是拓扑排序呢？因为此题可以看做一个有向图，唯一不同与模版的是题目中要统计读的轮数。那么刚好拓扑排序就可以完美的做到轮数最小这个特点。

那我们先谈谈什么是拓扑排序。
***
### 拓扑排序

拓扑排序就是有向无环图，所以它常用来判断一个有向图中是否有环。

**核心：** 
- 把所有入度为 0 的点都入队，将这些点记在答案顺序中，并删除与其所关联的边。
- 在把剩下入度为 0 的点都入队，这样重复一直到队列为空返回。

在这里提供一个模版供大家参考：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fastio ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
const int N = 1e3 + 10;
vector<int> edge[N];
vector<int> ans;
queue<int> q;
int n, m;
int in[N];
void topsort()
{
    while(!q.empty())
    {
        int t = q.front();//每次取出列头点，计入答案
        ans.push_back(t);
        q.pop();
        for (int i = 0; i < edge[t].size();++i)
        {
            in[edge[t][i]]--;
            if(in[edge[t][i]] == 0)//删去边后入度为0也入队
                q.push(edge[t][i]);
        }
    }
}
int main()
{
    fastio;
    cin >> n >> m;
    for (int i = 1,x,y; i <= m;++i)
    {
        cin >> x >> y;
        edge[i].push_back(y);
        in[y]++;//入度+1
    }
    for (int i = 1; i <= n;++i)
    {
        if(in[i] == 0)//统计入度为0的点
        {
            q.push(i);
        }
    }
    return 0;
}
```

好了那么讲完模版后，我们再来看看这道题。

首先如果理解模版后，题目中输出 $-1$ 的这个操作就已经很明了了：
```cpp
	//这里只需要统计个数是否全输出就可以
  	if(ans.size() != n) cout << -1 << endl;
 	else cout << maxx << endl; 
```
这里就会有人问那层数怎么解决，这里的 $maxx$ 变量就是我们所统计的层数。

**重点：** 层数统计。

回到题目中，我们可以发现其实只要在一个序列中有一个章节小于前一个章节，那就代表我们这本书得重读一遍，所以当我们在入度为 0 时还要多判断一个条件：是否递增。

```cpp
if(in[edge[t.second][i]] == 0)
{
    if(edge[t.second][i] > t.second)
        q.push(make_pair(t.first, edge[t.second][i]));
    else
        q.push(make_pair(t.first + 1, edge[t.second][i]));
}
```
好了那么这道题我们就可以开开心心的打代码了！

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define fastio ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
const int N = 2e4 + 10;
pair<int,int> t;
priority_queue<pair<int, int>,vector<pair<int,int> >,greater<pair<int, int> > > q;
vector<int> edge[N];
vector<int> ans;
int in[N];
int maxx = 0;
void topsort()
{
    while(!q.empty())
    {
        maxx = max(maxx, q.top().first);
        t = q.top();
        ans.push_back(t.second);
        q.pop();
        for (int i = 0; i < edge[t.second].size();++i)
        {
            in[edge[t.second][i]]--;
            if(in[edge[t.second][i]] == 0)
            {
                if(edge[t.second][i] > t.second)
                    q.push(make_pair(t.first, edge[t.second][i]));
                else
                    q.push(make_pair(t.first + 1, edge[t.second][i]));
            }
        }
    }
}
int main()
{
    fastio;
    int T, x, y, n;
    cin >> T;
    while(T--)
    {
        ans.clear();
        for (int i = 1; i <= 20000;++i)
        {
            edge[i].clear();
        }
        memset(in, 0, sizeof(in));
        maxx = 0;
        cin >> n;
        for (int i = 1; i <= n;++i)
        {
            cin >> x;
            for (int j = 1; j <= x;++j)
            {
                cin >> y;
                edge[y].push_back(i);
                in[i]++;
            }
        }
        for (int i = 1; i <= n;++i)
        {
            if(in[i] == 0)
                q.push(make_pair(1,i));
        }
        topsort();
        if(ans.size() != n)
            cout << "-1" << endl;
        else
            cout << maxx << endl;
    }
}
```

---

## 作者：fls233666 (赞：2)

首先考虑题目中章节与章节之间的关系。

假设要看懂第 $i$ 章，要先看懂 $a_1,a_2,a_3,...,a_k$ 章的内容。那么可以考虑把每个章节看作一个点，将 $a_1,a_2,a_3,...,a_k$ 章所代表的点向第 $i$ 章所代表的点连有向边。**于是整本书的章节关系就变成了一张有向图。**

再考虑看书的过程。

显然，看书时要先从没有前置章节的章节开始理解，然后再理解有前置章节的章节。转换到图上，就是从入度为零的点开始，逐一删掉这些点的连边，然后产生新的入度为零的点，再删边......于是，看书的过程被转换为了 **在一个有向图上拓扑排序的过程。**

接下来进一步考虑如何拓扑排序。

可以发现，题目要我们输出的是**至少看几遍书才能理解整本书的内容**。而看书的时候，**不能跳着看章节，而是要一章一章的往下看**。因此，不能直接使用朴素的拓补排序，应当加以修改。

首先可以想到一种很暴力的算法，就是模拟每次看书的过程并拓补排序。具体来说，就是循环遍历书的 $n$ 章，遇到一个新的可以理解的章节时就删边。很不幸的是，这个暴力算法在第四个测试点超时了。

考虑优化这一暴力算法。

注意到这个算法消耗时间最多的部分在于模拟看书的过程。如果最终答案与 $n$ 的乘积太大，超时是不可避免的。而实际上，**已经理解的章节不需要再被遍历到**。因此我们要考虑如何让每个章节只被遍历一次。

如果要求每个章节仅被遍历一次，我们需要回归到朴素的拓扑排序。但是朴素的拓扑排序存在一个显然的问题：**如何在排序中确定看书的先后顺序。**

我们再重新考虑看书的整个过程。可以发现，**看书时总是从编号小的章节看到编号大的章节**。因此，我们可以用小根堆，每次取出编号最小的章节观看。这样就保证了看书的章节顺序。

但这里又存在一个新的问题：假设看书看到第 $4$ 章时，第 $3$ 章和第 $5$ 章的前置章节都看完了。这时程序把 $3$ 和 $5$ 一起放进小根堆。那么看下一章时，程序从堆中取出的章节是 $3$，但是我们看书已经看到第 $4$ 章了，不能跳回去看第 $3$ 章，于是我们的答案就出错了。

从另一方面想，既然看到第 $4$ 章时，我们发现可以理解第 $3$ 章了，**为什么不把第 $3$ 章放进下一轮看书的安排中呢**？于是我们开两个小根堆，一个存储当前在看的章节，一个存储下一次能看的章节。当删完边出现新的能理解的章节时，可以把比当前章节序号大的章节加到正在用于排序的堆中，把比当前章节序号小的章节加到另一个堆中。然后在排序过程中轮流使用这两个堆，就得到答案了。

最后考虑如何判定无解。可以在排序过程中统计看的章节数量。如果统计结果最后没有 $n$ 章，即可判定为无解。

至此，此题得解，下面是代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define ll long long
#define rgt register int
using namespace std;

const int mxn = 2e5+5;
int tot,n,cnt,ans;
int nxt[mxn],lst[mxn],to[mxn],kn[mxn];
priority_queue < int , vector<int> , greater<int> > que[2];

inline void add(int a,int b){
	tot++;
	to[tot]=b;
	nxt[tot]=lst[a];
	lst[a]=tot;
}   //连边

int main(){
	int test,chp,q=0;
	scanf("%d",&test);
	while(test--){
		
		scanf("%d",&n);
		memset(kn,0,sizeof(kn));
		memset(lst,0,sizeof(lst));
		for(rgt di,i=1;i<=n;i++){
			scanf("%d",&di);
			for(rgt d,j=1;j<=di;j++){
				scanf("%d",&d);
				kn[i]++;
				add(d,i);
			}
		}  //数据读入与连边建图
		
		for(rgt i=1;i<=n;i++){
			if(!kn[i]){
				que[q].push(i);
			}
		}  //把不需要前置章节的章节先放进堆里面
		
		ans=cnt=0;　　//cnt统计理解的章节数量，ans统计看书次数
		while(!que[0].empty()||!que[1].empty()){
			ans++;
			while(!que[q].empty()){
				chp=que[q].top();
				que[q].pop();
				cnt++;
				for(rgt i=lst[chp];i;i=nxt[i]){
					kn[to[i]]--;
					if(!kn[to[i]]){
						if(to[i]>chp)  
							que[q].push(to[i]);  //把编号大的章节加入当前堆中
						else
							que[q^1].push(to[i]);  //把编号小的章节加入另一个堆中
					}
				}
			}
			q^=1;  //转换，使用另一个堆
		}
		
		if(cnt!=n)  //判定是否无解并输出答案
			printf("-1\n");
		else
			printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：xieyikai2333 (赞：1)

# 拓扑排序题

- [题目传送门](https://www.luogu.com.cn/problem/CF1572A)

---

- 看到题面，马上想到拓扑排序。

做法：

1. 若要理解第 $x$ 章，就必须要理解第 $y$ 章，就连一条从 $y$ 到 $x$ 的边；

2. 用优先队列对图进行拓扑排序，阅读次数小的排在前。若阅读次数相同，则按章节编号排序。设第 $x$ 章在第 $y$ 章理解后就可以理解：若 $x$ 大于 $y$，则本次阅读就可理解 $x$，反之则下次阅读才能理解 $x$；

3. 若发现存在环，则输出 $-1$；

4. 否则输出阅读次数最多的章节看了几遍。

---

**AC 代码**：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> PII;
int n,ind[200005],tot,ans;
vector<int> nodes[200005];
priority_queue<PII,vector<PII>,greater<PII> > pq;
void topo()
{
	for(int i=1;i<=n;i++)if(ind[i]==0)pq.push(make_pair(1,i));
	while(!pq.empty())
	{
		int u=pq.top().second,s=pq.top().first;
		pq.pop();
		tot++;
		ans=max(ans,s);
		for(int i=0,len=nodes[u].size();i<len;i++)
		{
			int v=nodes[u][i];
			if(--ind[v]==0)
			{
				if(v>u)pq.push(make_pair(s,v));
				else pq.push(make_pair(s+1,v));
			}
		}
	}
	return;
}
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)nodes[i].clear();
		tot=ans=0;
		for(int i=1;i<=n;i++)
		{
			cin>>ind[i];
			for(int j=1;j<=ind[i];j++)
			{
				int x;
				cin>>x;
				nodes[x].push_back(i);
			}
		}
		topo();
		if(tot<n)cout<<"-1\n";
		else cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

模拟。

考虑拓扑排序，维护所有入度为 $0$ 的点的集合 $S$ 与一个指针 $t$ 表示扫描到第几个数，每次从 $S$ 中取出最小的大于等于 $t$ 的位置更新并令 $t$ 等于这个位置，假若某个时刻存在点没有被更新但是 $S$ 为空则无解，假若 $S$ 中不存在大于等于 $t$ 的数则让 $t$ 回到开头并让次数加一即可。

[代码](https://codeforces.com/contest/1572/submission/280211562)

---

## 作者：卷王 (赞：0)

一道较简单的题。做法：拓扑排序+dp。

假设理解了第 $u$ 章才能理解第 $v$ 章，就连一条 $u\rightarrow v$ 的单向边，接着直接拓扑求出符合要求的阅读顺序。

然后 dp 求答案。设 $dp_u$ 表示按照拓扑序阅读到第 $u$ 章的最小阅读次数。则：

```cpp
if(v>u) dp[v]=max(dp[v],dp[u]);
else dp[v]=max(dp[v],dp[u]+1);
```

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long
typedef long long ll;
typedef pair<int, int> pr;
#define up(i, l, r) for(int i = (l); i <= (r); i++)
#define down(i, r, l) for(int i = (r); i >= (l); i--)
const int mod = 1000000007;
const int base = 2333;
const double eps = 1e-6;

namespace fast_io {
	char buf[1 << 12], *p1 = buf, *p2 = buf, sr[1 << 23], z[23], nc;
	int C = -1, Z = 0, Bi = 0;
	inline char gc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 12, stdin), p1 == p2) ? EOF : *p1++;
	}
	inline int read() {
		int x = 0, y = 1;
		while (nc = gc(), (nc < 48 || nc > 57) && nc != -1)if (nc == 45)y = -1;
		Bi = 1;
		x = nc - 48;
		while (nc = gc(), 47 < nc && nc < 58)x = (x << 3) + (x << 1) + (nc ^ 48), Bi++;
		return x * y;
	}
	inline void ot() {
		fwrite(sr, 1, C + 1, stdout);
		C = -1;
	}
	inline void flush() {
		if (C > 1 << 22) ot();
	}
};
using namespace fast_io;

int n, m, k, Q, T, _, ans = 0;
int in[200007];
vector<int>G[200007],E[200007];
int ord[200007],cnt=0;
int dp[200007];

inline bool topo(){
	queue<int>q;
	for(int i=1;i<=n;i++) {
		if(in[i]==0) q.push(i);
	}
	while(!q.empty()){
		int u=q.front(); q.pop();
		ord[++cnt]=u;
		for(auto v:G[u]){
			in[v]--;
			if(in[v]==0) q.push(v);
		}
	}
	if(cnt<n) return 0;
	return 1;
}

signed main() {
	T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;i++) {
			G[i].clear(),E[i].clear();
			in[i]=0;
			dp[i]=0;
		}
		for(int i=1;i<=n;i++){
			int l=read();
			while(l--){
				int x=read();
				G[x].push_back(i);
				E[i].push_back(x);
				in[i]++;
			}
		}
		cnt=0;
		bool flag=topo();
		if(!flag) {
			printf("-1\n");
			continue;
		}
		ans=0;
		for(int i=1;i<=cnt;i++){
			int u=ord[i];
			if(dp[u]==0) dp[u]=1;
			for(auto v:G[u]){
				if(v>u) dp[v]=max(dp[v],dp[u]);
				else dp[v]=max(dp[v],dp[u]+1);
			}
			ans=max(ans,dp[u]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Graph_Theory (赞：0)

### 思路

看到阅读一章节时有前置章节，大概率说明这是一道拓扑排序。

可以连接有必要关系的两个章节，进行排序，记录每一张需要看多少次。因为不能返回去看前面的章节，所以直接输出最多次观看的章节的观看次数。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int n,s=0;
int in[200209],maxread=0;
bool vis[200209];
vector <int> e[200209];
vector <int> ans;

void doit()
{
	cin>>n;
	maxread=0;
	for(int i=1;i<=n+100;i++) 
	{
		vis[i]=0;
		e[i].clear();
		in[i]=0;
	}
	ans.clear();
	for(int i=1;i<=n;i++)
	{
		cin>>s;
		in[i]=s;
	//	e[i].push_back(s);
		for(int j=1;j<=s;j++)
		{
			int pussh;
			cin>>pussh;
			e[pussh].push_back(i);
		}
	}
	
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;

	for(int i=1;i<=n;i++)
	{
		if(in[i]==0) 
		{
			q.push(make_pair(1,i));
	//		cout<<endl<<"     pushsss "<<i;
		}
	//	cout<<endl<<"  "<<in[i];
	}
	while(!q.empty())
	{
		pair<int,int> u=q.top();
		ans.push_back(u.second);
	//	cout<<" sec   "<<u.second<<endl;
		maxread=max(maxread,u.first);
		q.pop();
		for(int i=0;i<e[u.second].size();i++) 
		{
			int v=e[u.second][i];
			in[v]--;
			if(in[v]==0)
			{
				if(v>u.second)
					q.push(make_pair(u.first,v));
				else
					q.push(make_pair(u.first+1,v));
			}	
		}
	}
	
	//cout<<maxread<<" "<<ans.size()<<"     ";
	cout<<((ans.size()<n)?-1:maxread)<<endl;
}

int main()
{
	int TT;
	cin>>TT;
	while(TT--)
		doit();
	return 0;
}
```

---

## 作者：lqsy002 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF1572A)。

## 解题思路

拓扑排序。

因为要读懂 $v$ 就要读懂 $u$，所以考虑建一条 $u\to v$ 的边。

如果 $u>v$ 则次数加一，同时记录点的遍历次数，若 $cnt\not  =n$ 则说明有环，输出 $-1$，否则输出 $u>v$ 的次数。

## 参考代码
```cpp
#include<bits/stdc++.h>
#define maxn 200005
#define maxm 20000005
using namespace std;
int t,n;
int idx,head[maxn];
int cnt,ans,deg[maxn],dis[maxn];
struct edge{
	int to;
	int nxt;
}e[maxm];
struct node{
	int u;
	int w;
};
queue<node>q;
void add(int u,int v){
	e[++idx]={v,head[u]};
	head[u]=idx;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		idx=cnt=ans=0;
		for(int i=1;i<=n;++i)
			head[i]=deg[i]=dis[i]=0;
		cin>>n;
		for(int i=1,k,u;i<=n;++i){
			cin>>k;
			deg[i]=k;
			if(!k){
				q.push({i,1});
				continue;
			}
			while(k--){
				cin>>u;
				add(u,i);
			}
		}
		while(!q.empty()){
			int u=q.front().u,w=q.front().w; 
			q.pop();
			++cnt;
			ans=max(ans,w);
			for(int i=head[u],v;i;i=e[i].nxt){
				v=e[i].to;
				dis[v]=max(dis[v],w+(u>v));
				if(!--deg[v])
					q.push({v,dis[v]});
			}
		}
		if(cnt!=n)
			cout<<-1;
		else
			cout<<ans;
		cout<<'\n';
	}	
	return 0;
}
```

---

## 作者：Special_Tony (赞：0)

# 思路
这题其实就是每次贪心从头读到尾，暂时不能读的就要等下一轮读，直到读完。如果有环就永远读不完。

然后就是拓扑排序板子。但是这题因为每次阅读必须递增，因此我们可以用 set 加上 lower_bound 代替 queue。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int t, n, du[200005], x, sum, now;
vector <int> v[200005];
set <int> q;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n;
		for (int i = 1; i <= n; ++ i)
			du[i] = 0, v[i].clear ();
		for (int i = 1; i <= n; ++ i) {
			cin >> du[i];
			if (! du[i]) //没有入度，加入队列
				q.insert (i);
			else
				for (int j = 0; j < du[i]; ++ j)
					cin >> x, v[x].push_back (i);
		}
		sum = 0;
		while (! q.empty ()) {
			++ sum, now = 0;
			while (1) {
				auto it = q.upper_bound (now);
				if (it == q.end ())
					break ;
				int x = now = *it;
				q.erase (it);
				for (int i : v[x])
					if (! -- du[i])
						q.insert (i);
			}
		}
		for (int i = 1; i <= n; ++ i)
			if (du[i]) { //拓扑完毕还有没理解的，肯定无解
				sum = -1;
				break ;
			}
		cout << sum << '\n';
	}
	return 0;
}
```

---

## 作者：hewo (赞：0)

看到先决条件，第一反应就是拓扑排序。

用拓扑排序获得可以阅读的章数。

对于第 $i$ 章 ， $f[i]=max(f[j]+i<j)$ ( $j$ 是 $i$ 的先决条件。) 

也就是说，每章的次数就是所有先决条件达成后的情况，如果 $i>j$ 的话，顺着就看过去了，不会产生贡献。如果 $i<j$ 就要再看1次，加1。

看到这里，不妨回去看一下数据范围，这么做肯定要超时的。

我们想到了 $\max(f[j]+i<j)$ ，就可以用一个优先队列来维护，每次优先处理 $f[i]$ 小的。这样做就好比对每一次翻书进行处理，看这次翻书最多处理到哪里。

要注意的是，我们的优先队列在全职相等的情况下，要满足 $id$ 从小到大，这样最后的稻草就是最大的 $id$ 了，如果它都没有超过 $i$ ，才能说明不用 $+1$ 。

其他细节看代码，这道题似乎卡时间，推荐使用快速读写，有时候在1300ms徘徊，有时候又只有600ms。

codes

```cpp
#include<bits/stdc++.h>

using namespace std;

const int MX=3*100000+1000;
#define LL long long
#define inf 0x3f3f3f3f

struct ios {
    inline char read(){
        static const int IN_LEN=1<<18|1;
        static char buf[IN_LEN],*s,*t;
        return (s==t)&&(t=(s=buf)+fread(buf,1,IN_LEN,stdin)),s==t?-1:*s++;
    }

    template <typename _Tp> inline ios & operator >> (_Tp&x){
        static char c11,boo;
        for(c11=read(),boo=0;!isdigit(c11);c11=read()){
            if(c11==-1)return *this;
            boo|=c11=='-';
        }
        for(x=0;isdigit(c11);c11=read())x=x*10+(c11^'0');
        boo&&(x=-x);
        return *this;
    }
}io;
template<class T>inline void _print(T x){
	if(x/10) _print(x/10);
	putchar(x%10+'0');
}
template<class T>inline void print(T x){
	if(x<0) putchar('-'),x=-x;
	_print(x);
}

int n;

struct tEdge
{
	int to;
	int next;
}edge[MX<<1];
int head[MX],cnt=0;

inline void add(int from,int to)
{
	edge[++cnt].to=to,edge[cnt].next=head[from];
	head[from]=cnt;
}

int in[MX];

struct tDL
{
	int val;
	int id;
	friend bool operator <(tDL a,tDL b)
	{
		if(a.val==b.val) return a.id>b.id;
		return a.val>b.val;
	}//if a.val<b.val     a<b
};

priority_queue<tDL> qaq;

inline int topsort()
{
	while(!qaq.empty()) qaq.pop();
	for(int i=1;i<=n;i++) 
	{
		if(in[i]==0) qaq.push(tDL{1,i});//没有先决条件的为1
	}
	int idx=0;//用来判断有没有看不到的书
	idx=qaq.size();
	int maxn=1;
	while(!qaq.empty())
	{
		tDL q=qaq.top();
		qaq.pop();
		int x=q.id;
		int s=q.val;
		maxn=s;
		for(int i=head[x];i;i=edge[i].next)
		{
			int yt=edge[i].to;
			in[yt]--;
			if(in[yt]==0)
			{
				qaq.push(tDL{s+(yt<x),yt});
				idx++;
			}
		}
	}
	if(idx!=n) return -1;
	else return maxn;
}

inline void csh()
{
	//memset(in,0,sizeof(in));
	memset(head,0,sizeof(head));
	//memset(edge,0,sizeof(edge));
	cnt=0;
}

/*
4
0
1 1
2 4 2
1 1
-1
*/

int main(int argc, char const *argv[])
{
	int T;
	io>>T;
	while(T--)
	{
		csh();
		io>>n;
		for(int i=1;i<=n;i++)
		{
			int num;
			io>>num;
			in[i]=num;
			for(int j=1;j<=num;j++)
			{
				int inx;
				io>>inx;
				add(inx,i);
			}
		}
		print(topsort());
		puts("");
	}
	return 0;
}
```

---

