# Eternal Victory

## 题目描述

经历了一场激烈的战斗之后，Valerian被Shapur抓住了。这个胜利是如此的伟大，以至于Shapur决定把Valerian的失败（也就是他的胜利）的场景雕刻在山上。所以他必须找到最好的地方使他的胜利永远被保存。

他决定到波斯的n个城市去寻找可以使用的最好的山，但是战斗后他太累了，所以不想走太多的路。因此，他希望以最短的路径走遍所有的n个城市。某些城市以双向道路相连。你可以通过这些道路从一个城市到另一个城市。在两个城市间最多只有一条双向道路。所有城市被从1到n编号。

Shapur目前在城市1，他想以最短的路径访问所有其他城市。他可以在任何城市结束他的旅行。

帮助Shapur算出他最少要走多远的路。

## 样例 #1

### 输入

```
3
1 2 3
2 3 4
```

### 输出

```
7
```

## 样例 #2

### 输入

```
3
1 2 3
1 3 3
```

### 输出

```
9
```

# 题解

## 作者：Kobe303 (赞：7)

# 思路分析：

“他可以在任何城市结束他的旅行。”

也就是说，他可以停在任意一点。

所以有一条链只需走一遍。

为使总路程最小，则那条最长的链只需走一遍。

例如下图：

![CF61D](https://cdn.luogu.com.cn/upload/image_hosting/dt33vzhc.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

$1$->$2$->$5$的路径长度总和为$15+4=19$。

$1$->$3$->$6$->$7$的路径长度总和为$2+5+6=13$。

$1$->$4$的路径长度总和为$4$。

故选择$1$->$2$->$5$这条路只走一遍，使得走的总路程最小。

最终输出的答案为边权和的两倍减去最长链的长度。

# 代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define reg register 
#define il inline
const int N = 100010;
int n;
int head[N], cnt;
struct node
{
	int to, next, w;
}e[2 * N];
//用链式前向星存图
ll ans;//记录边权和
ll longest;//记录最长链的长度
il void add(int u, int v, int w)
{
	++cnt;
	e[cnt].to = v;
	e[cnt].next = head[u];
	e[cnt].w = w;
	head[u] = cnt;
}
il void dfs(int u, int fa, ll sum)
{
	longest = std::max(longest, sum);
	for(reg int i = head[u]; i; i = e[i].next)
	{
		int v = e[i].to;
		if(v == fa) continue;
		dfs(v, u, sum + e[i].w);
	}
	return;
}
il int qrint()
{
	int s = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch))
	{
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (isdigit(ch))
	{
		s = (s << 1) + (s << 3) + (ch ^ 48);
		ch = getchar();
	}
	return s * f;
}
//快读不解释
int main()
{
	n = qrint();
	for(reg int i = 1; i < n; ++i)
	{
		int u = qrint(), v = qrint(), w = qrint();
		add(u, v, w);
		add(v, u, w);//因为是无向边，所以连两次
		ans += w;
	}
	dfs(1, 0, 0);
	printf("%lld", ans * 2 - longest);
	return 0;
}
```



---

## 作者：_lxy_ (赞：2)

#### 题意

求从 $1$ 号节点开始，遍历一个 $n$ 个点， $n-1$ 条边的无向图所需要的最短距离。

#### 分析

![](https://cdn.luogu.com.cn/upload/image_hosting/glei7j3e.png)

因为这个无向图由 $n$ 个点， $n-1$ 条边组成，所以这个图一定是一棵树。如图，我们可以发现，遍历一棵树，肯定会将一条链经过一次，其余的每条边都会被经过两次，为了使总距离最小，就让只经过一次的那条链最长即可。由于在树上两点之间不走回头路的路径唯一，因此可以以 $1$ 号节点为起始点，在整张图上跑最短路，对每一条最短路的长度取最大值，就能得到最长链。最终答案就是所有边权和的 $2$ 倍减最长链的长度。

#### 代码

```cpp
#include <bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a));
#define int long long
using namespace std;
const int MAXN=1e5+7;
int n;
int head[MAXN];
struct Edge
{
    int to,dis,nxt;
    Edge(){;}
    Edge(int _to,int _dis,int _nxt):to(_to),dis(_dis),nxt(_nxt){}
};
vector<Edge>edge;
void add_edge(int u,int v,int w)
{
    edge.push_back(Edge{v,w,head[u]});
    head[u]=edge.size()-1;
}
priority_queue<pair<int,int> >q;
int dis[MAXN];
bool vis[MAXN];
void dijkstra(int s)
{
    mem(dis,0x7f);mem(vis,0);
    dis[s]=0;
    q.push(make_pair(0,s));
    while(!q.empty())
    {
        int u=q.top().second;
        q.pop();
        if(vis[u]) continue;
        vis[u]=true;
        for(int i=head[u];i!=-1;i=edge[i].nxt)
        {
            if(dis[edge[i].to]>dis[u]+edge[i].dis)
            {
                dis[edge[i].to]=dis[u]+edge[i].dis;
                q.push(make_pair(-dis[edge[i].to],edge[i].to));
            }
        }
    }
}
signed main()
{
    scanf("%lld",&n);
    mem(head,-1);
    int i,j,sum=0;
    for(i=0;i<n-1;i++) 
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);sum+=w*2;
        add_edge(u,v,w);
        add_edge(v,u,w);
    }
    dijkstra(1);int mx=0;
    for(i=1;i<=n;i++) mx=max(mx,dis[i]); 
    printf("%lld\n",sum-mx);
    // system("pause");
    return 0;
}
```



---

## 作者：LKY928261 (赞：1)

## 题目分析

简化题意：求从一号节点开始遍历完整棵树的所有点的最短路径长度。

首先考虑从一号节点（根节点）遍历完后再回到根节点所需的总长度。不难发现，在遍历时所有的边都被经过了两次，所以此路径长度等于所有边权总和的两倍。

而题目中提到“可以在任何城市结束他的旅行”，说明结束点不一定要是根节点。所以，从最后一个遍历到的叶节点返回根节点的路程是多余的，最终的路程需要减去这段路。

其中，“最后一个遍历到的叶节点”可以是任意的。也就是说，需要找到合适的一个“最后一个遍历到的叶节点”，使得总路程最小。而减去值越大，最终值越小。所以，只需找到最大的根到叶节点的长度即可。

## 参考代码

代码仅供参考。

~~请不要在意我独特的码风。。。~~

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,x,y,z,s,t,T,h[100005],i;
struct o{ll x,y,z;}a[200005];
void p0(ll x,ll y,ll z){a[++T].x=h[x];h[x]=T;a[T].y=y;a[T].z=z;}
void p(ll x,ll y,ll fa){//dfs
	bool f=1;//用于判断是否为叶节点
	for(ll i=h[x];i;i=a[i].x)if(a[i].y!=fa)
		f=0,p(a[i].y,y+a[i].z,x);
	if(f)t=max(t,y);//记录最长的根到叶节点的路径
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(i=1;i<n;i++){cin>>x>>y>>z;p0(x,y,z);p0(y,x,z);s+=z;}
	p(1,0,1);
	cout<<(s<<1)-t<<"\n";
}
```

---

## 作者：Ginger_he (赞：1)

# 题目描述
给定一个含有 $n$ 个点的树，求从 $1$ 号点出发并经过所有点的路径的最小权值和。
# 题解
这棵树可以视作很多条由 $1$ 号点出发的链，所以每次走完一条链要回到 $1$ 号点，即每条链都要走 $2$ 遍。但是有一个例外，因为题目允许在任何一个点结束，所以可以有一条链只走一遍，又因为题目要求最小权值和，所以只走一遍最长链即可。

综上，若边权和为 $s$，最长链边权和为 $t$，那么答案为 $2s-t$。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 100005
struct node
{
	int v,w;
};
int n,u,v,w;
ll s;
vector<node> g[N];
ll dfs(int x,int fa)
{
	ll res=0;
	for(auto i:g[x])
	{
		if(i.v!=fa)
			res=max(res,dfs(i.v,x)+i.w);
	}
	return res;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		g[u].push_back(node{v,w});
		g[v].push_back(node{u,w});
		s+=w;
	}
	printf("%lld\n",s*2-dfs(1,0));
	return 0;
}
```

---

## 作者：Tune_ (赞：1)

这题还是比较有难度的，~~毕竟蒟蒻我整了半天才做出来~~

如果要回到原点，那就所有路都要走2遍，而本题是可以停在任意一点，所以有一条通向某个点的路只要走一遍，要让路程最短，那最长的那条只走一遍。

比如有一个像这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/snmmwfw7.png)

那么我们就应选择1->2->4->7这条（假设所有边长度都为1），走的路最少。

要记录这个图，可以用邻接表：

![](https://cdn.luogu.com.cn/upload/image_hosting/e7pw8oqr.png)

head是个数组，用链表的方式记录从每个点出发的路。

最后，用递归算出最长路径的长度，输出所有路径的2倍-最长路，就OK啦~

好了，接下来附上我的AC代码：

```
#include<bits/stdc++.h>
using namespace std;
struct data//一个结构体
{
	int t,d,next;
}a[200005];
int n,head[100005],s=0;
long long l,ans;
void add(int x,int y,int dis)//接上这个点
{
	s++;//为了省事，从链头插入
	a[s].t=y;
	a[s].d=dis;
	a[s].next=head[x];
	head[x]=s;
}
void dfs(int x,int f,long long now)//找最长
{
	l=max(l,now);
	for(int i=head[x];i;i=a[i].next)//链表要这样循环
	{
		if(a[i].t==f)
			continue;
		dfs(a[i].t,x,now+a[i].d);//下一点
	}
	return;
}
int main()
{
	cin>>n;
	for(int i=1;i<n;i++)//输入
	{
		int x,y,dis;
		cin>>x>>y>>dis;
		add(x,y,dis);
		add(y,x,dis);
		ans+=dis;
	}
	dfs(1,0,0);//开找！
	cout<<ans*2-l;//输出答案
	return 0;//拜了个拜
}
```
走过路过，给本蒟蒻点个赞鸭~

---

## 作者：Mint_Flipped (赞：1)

大佬都只给了一个结论，我来解释一下过程。

初看题，以为是个TSP，咱是个菜鸡，也不会啊！！！

再看题，就是一颗无向树，问从1节点，游历所有节点所用的最短路径为几何？

简单讲一下这一个过程，你在树上某一点，你有好几条路，要走。你只能选择，先走一条，再回来，走其他路，即游历两次。

如何得到最短路径，即树上最长的路只走一次，即求树上最长的链。遇到其他的路，去走完，再返回，走那条最长链即可。

那么最短路径即为：所有路径的长度乘二-最长链即可。

代码如下：
```c
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define fo1(a,b) for(int a=0;a<b;++a)
#define fo2(a,b) for(int a=1;a<=b;++a)
#define lowbit(a) (a&(-a))
#define fir(a) a->first 
#define sec(a) a->second 
const int inf=0x3f3f3f3f;
const int maxn=1e5+5;
const int mod=1e9+7;
const double eps=1e-6;
int n;
ll sum,ans;
struct Edge{
    int v;
    ll w;
    Edge(int _v,ll _w):
    v(_v),w(_w){}
};
vector <Edge> p[maxn];
void dfs(int x,int y,ll cnr){
    if(ans<cnr)
    ans=cnr;
    int s=p[x].size();
    fo1(i,s){
        int v=p[x][i].v;
        ll w=p[x][i].w;
        if(v!=y)
        dfs(v,x,cnr+w);
    }
}
int main()
{
    int u,v;
    ll w;
    scanf("%d",&n);
    fo2(i,n-1){
        scanf("%d%d%lld",&u,&v,&w);
        p[u].push_back(Edge(v,w));
        p[v].push_back(Edge(u,w));
        sum+=w;
    }
    dfs(1,0,0);
    cout<<2*sum-ans<<endl;
    return 0;
}
```


---

## 作者：tZEROちゃん (赞：0)

>给定一个 $n$ 个点的树，求从 $1$ 号点出发并经过所有点的路径的最小权值和。

注意到因为他可以在任意点结束，所以每条链都要经过 $1$ 次或 $2$ 次，且只有一条链经过 $1$ 次。

那么答案就是总边权 $\times 2\ - $ 只经过 $1$ 次的那条链上所有边的边权。  

那我们肯定希望经过 $1$ 次的那条链的长度尽可能大，显然可以 dfs 求解出最长链的长度。

[参考代码](https://www.luogu.com.cn/paste/qh66izv5)。

---

## 作者：FrozenDream (赞：0)

### 引言：
最近刚学了边表，写一篇题解来巩固一下。

------------

### 思路：
既然要求最短路径把所有节点全部遍历一遍，那么所有路径肯定全部都要走两遍的，但最后不用回到开始的节点，所以可以有一条路径只用走一遍，要使答案最优，这条只走一遍的路径肯定要选最长的。

还不懂？没关系，我们结合一组样例来理解一下:
![](https://cdn.luogu.com.cn/upload/image_hosting/9fsn9n2r.png)
从 $1$ 号节点开始，遍历全部节点，显而易见，三条路中，有两条肯定是要走两遍的，剩下的一条路只用走一遍了，这一条路肯定要选最长的。

最后输出时就输出总路径长度 $\times$ $2$ $-$ 最长路径长度就可以了。

------------
### Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,u,v,w,tot,nxt[200005],head[200005],to[200005],val[200005],ans,sum2;
void add(int u,int v,int w){
	tot++;
	nxt[tot]=head[u];
	head[u]=tot;
	to[tot]=v;
	val[tot]=w;
}
void dfs(long long sum,long long city,long long value,long long f){
	ans=max(ans,value);
	if(f>=n){
		return;
	}
	for(int i=head[city];i;i=nxt[i]){
		if(to[i]!=sum){
			dfs(city,to[i],value+val[i],f+1);
		}
	}
	return;
}
int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
		sum2+=w;
	}
	dfs(1,1,0,0);
	cout<<sum2*2-ans;
}

```


---

## 作者：sixrc (赞：0)

### 题目大意

一棵树，你从 $1$ 号结点出发，最后可以停在任意一个点，求恰好经过全部点走过的最短路。

### 分析

结论题。一个很重要的性质是，**它是一棵树**。

那么对于一棵树，由于要经过每个点，那每条边肯定都会被经过。对于最优情况，我们把每一条链走到底，然后再返回。容易发现这样做每条边都要经过 $2$ 次。但是最后可以停留在任意一个点，那么我们就留最长的那条链只走一次，剩下的都走两次。答案就是边权和 $\times 2$ 减去最长链的长度。

### Code：
```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, s, p, x, y, z, h[100010], ret;
struct node{
	int x, y, z, next;
}d[200010];
void add(int x, int y, int z){
	d[++p].y = y, d[p].z = z, d[p].next = h[x], h[x] = p;
}
void dfs(int x, int fa, int cnt){
	ret = max(ret, cnt);
	for (int i=h[x]; i; i=d[i].next){
		int y = d[i].y;
		if (y == fa) continue;
		dfs(y, x, cnt+d[i].z);
	}
}
signed main(){
	scanf ("%lld", &n);
	for (int i=1; i<n; i++){
		scanf ("%lld%lld%lld", &x, &y, &z);
		add(x, y, z);
		add(y, x, z);
		s += z;
	}
	dfs(1, 0, 0);
	printf ("%lld\n", s * 2 - ret);
	return 0;
}

```

---

## 作者：fjy666 (赞：0)

## 0x01 思路
容易发现最多只有一条链只经过 $1$ 次。  
所以 $\verb!dfs!$ 一遍，求出以 $1$ 开头的最长链（链的长度定义为链上的边权和），令它为 $s$，答案就是 $(2\sum w_i) - s$。  
复杂度 $\mathcal{O}(n)$。  

## 0x02 代码
```cpp
//writer:fjy
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cassert>
#include <vector>
#include <cstdio>
#include <ctime>
#include <cmath>

char *tmp = "qwq";
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
#define _for(i_,a_,b_) for(int i_ = a_;i_ < b_;++i_)
#define _bug(a) cerr << "[DEBUG] " << #a << "=" << (a) << " @ line "<<__LINE__<<endl
typedef long long ll;
using namespace std;
const int inf = 0x3f3f3f3f;
int M;
vector<pair<int,int> > e[100005];

void dfs(int x,int sum,int fat) {
	M = max(M,sum);
	for(auto to : e[x]) 
		if(to.first != fat) 
			dfs(to.first,sum + to.second,x);
}

int main() {
#ifdef LOCAL
    clock_t c1 = clock();
#endif
	int n;
	scanf("%d",&n);
	int s = 0;
	_rep(i,1,n-1) {
		int a,b,w;
		scanf("%d%d%d",&a,&b,&w);
		e[a].push_back(make_pair(b,w));
		e[b].push_back(make_pair(a,w));
		s += w;
	}
	dfs(1,0,-1);
	printf("%lld\n",s * 2ll - M);
#ifdef LOCAL
    fprintf(stderr,"\nTime used = %ldms\n", clock() - c1);
#endif
    return 0;
}
```

---

