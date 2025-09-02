# Cyclic Components

## 题目描述

给定一张 $n$ 个点，$m$ 条边的无向图。保证无重边、无自环。在该图的所有连通块中，你需要找出环的个数。

无向图的环的定义如下：

原无向图中的一个子图被定义为环，当且仅当它的点集重新排序后可以满足如下条件：

- 第一个点与第二个点通过一条边相连接；
- 第二个点与第三个点通过一条边相连接；
- ……
- 最后一个点与第一个点通过一条边相连接。
- 所有的边都应当是不同的。
- 其边集不应当包含除了以上所述的边以外的任何边。

这样，我们就称这个子图（点 + 边）为环。

根据定义，一个环至少需要包含三个点，且边数与点数应当是相同的。

![](https://cdn.luogu.org/upload/vjudge_pic/CF977E/4eb49ec2d535d241bf8aedac2221e1f54d715822.png)

例如对于上图，共有 $6$ 个联通块，但只有 $[7,10,16]$ 和 $[5,11,9,15]$ 这两个联通块是环。

## 说明/提示

在第一个样例中，只有 $[3, 4, 5]$ 这个联通块是一个环。

第二个样例就对应着题目解释中的图片。

## 样例 #1

### 输入

```
5 4
1 2
3 4
5 4
3 5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
17 15
1 8
1 12
5 11
11 9
9 15
15 5
4 13
3 13
4 3
10 16
7 10
16 7
14 3
14 4
17 6
```

### 输出

```
2
```

# 题解

## 作者：Otue (赞：12)

全场最简洁代码来咯。

# 思路
**问题 $1$：如何判断一个连通块是否是简单环？**

只需要看这个连通块的所有点的度数是不是 $2$ 即可。

**问题 $2$：如何找到每一个连通块？**

用并查集维护即可，合并每一条边。

所以这道题代码就呼之欲出了！
# 代码
```c++
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int n, m, p[N], st[N], d[N];
// d统计每个点的度数，st代表每个连通块是否为简单环
int res;

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) p[i] = i;
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        p[find(a)] = find(b);
        d[a]++, d[b]++;
    }
    for (int i = 1; i <= n; i++) {
        if (d[i] != 2) st[find(i)] = 1;  //度数不为2，标记一下
    }
    for (int i = 1; i <= n; i++) {
        if (find(i) == i && st[find(i)] == 0) res++;
        //枚举每个连通块
    }
    cout << res << endl;
}
```

---

## 作者：小明小红 (赞：3)

# CF977E 题解
**题目意思**：这道题的意思就是给你一个不保证联通的图，问其中环的数量。

**处理非环**：我们知道，环中的所有点的度数都为 $2$，所以我们只需要寻找那个的度数和不为 $2$，然后再把这个点所在的连通块的打上标记，剩下没被标记的就是类环的图。

**处理类环**：为什么是类环？因为题目中说了环都是 $3$ 个点及以上，所以我们来一遍连通块大小，然后特判掉 $1$ 和 $2$ 的情况即可。
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll head[200009],n,m,ans,d[200009],cnt=0,vis[200009],sum,a,b;
struct edge {
	ll to,last;
}e[400009];
void add(ll x,ll y) {//前向星连边 
	e[++cnt].to=y;
	e[cnt].last=head[x];
	head[x]=cnt;
}
void dfs(ll x) {
	ans++;//跑连通块 
	vis[x]=1;
	for(ll i=head[x]; i; i=e[i].last) {
		ll v=e[i].to;
		if(vis[v]==0) {
			dfs(v);
		}
	}
}
int main() {
	cin>>n>>m;
	for(ll i=1; i<=m; i++) {
		cin>>a>>b;
		d[a]++,d[b]++;//计算度数
		add(a,b);
		add(b,a);
	}
	for(ll i=1; i<=n; i++) {
		if(d[i]!=2) {
			dfs(i);//寻找非环 
		}
	}
	for(ll i=1; i<=n; i++) {
		if(vis[i]==0) {
			ans=0;
			dfs(i);
			if(ans>2) {//寻找类环 
				sum++;
			}
		}
	}
	cout<<sum;
	return 0;
}
```


---

## 作者：StudyingFather (赞：3)

容易看出，一个圈内所有点的度数均为 $ 2 $ 。

先DFS求出所有连通分量，判断各个连通分量内所有点是否满足上面的条件即可。

```cpp
#include <cstdio>
#include <vector>
using namespace std;
struct edge
{
 int v,next;
}e[400005];
int t[200005],head[200005],cnt,vis[200005];
vector<int> path;
void addedge(int u,int v)
{
 e[++cnt].v=v;
 e[cnt].next=head[u];
 head[u]=cnt;
}
void dfs(int u)
{
 vis[u]=1;
 path.push_back(u);
 for(int i=head[u];i;i=e[i].next)
  if(!vis[e[i].v])dfs(e[i].v);
 return;
}
int main()
{
 int n,m,ans=0;
 scanf("%d%d",&n,&m);
 for(int i=1;i<=m;i++)
 {
  int u,v;
  scanf("%d%d",&u,&v);
  t[u]++,t[v]++;
  addedge(u,v);
  addedge(v,u);
 }
 for(int i=1;i<=n;i++)
  if(!vis[i])
  {
   path.clear();
   dfs(i);
   int maxn=path.size(),flag=1;
   for(int i=0;i<maxn;i++)
    if(t[path[i]]!=2)
    {
     flag=0;
     break;
    }
   ans+=flag;
  }
 printf("%d\n",ans);
 return 0;
}
```


---

## 作者：first_fan (赞：3)

看见这道题，第一反应是并查集，做完后发现题解区没有并查集做法，故来分享一下。

本题中定义的环，是指一个所有点的度均为2的子图。

所以我们可以在读入时统计每个点的度数。

读入后我们利用并查集检查是否在同一个子图当中。

* 如果发现当前边连接的点所属集相同，那么则说明并查集找到了环，答案自增。

* 如果不在一个集中，那么就合并就好了。

感觉应该会比搜索好理解一些。

```cpp
#include <bits/stdc++.h>
#define ri register int
#define ll long long
using namespace std;

int read()
{
	int num=0;
	int flg=1;
	char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
		{
			flg=-1;
		}
		c=getchar();
	}
	while(isdigit(c))
	{
		num=(num<<1)+(num<<3)+(c^48);
		c=getchar();
	}
	return num*flg;
}

const int maxn=1e6+7;
int f[maxn];

int find(int x)
{
	return x==f[x]?x:(f[x]=find(f[x]));
}

int u[maxn];
int v[maxn];
int ind[maxn];

int main()
{
	int n;
	int m;
	while(scanf("%d%d",&n,&m))
	{
		int ans=0;
		for(ri i=1;i<=n;i++)
		{
			f[i]=i;
			ind[i]=0;
		}
		for(ri i=1; i<=m; i++)
		{
			u[i]=read();
			v[i]=read();
			ind[u[i]]++;
			ind[v[i]]++;
		}
		for(ri i=1;i<=m;i++)
		{
			if(ind[u[i]]==2&&ind[v[i]]==2)
			{
				int fu=find(u[i]);
				int fv=find(v[i]);
				if(fu!=fv)
				{
					f[fu]=fv;
				}
				else
				{
					ans++;
				}
			}
		}
		printf("%d\n",ans);
	}
}
```

---

## 作者：Priori_Incantatem (赞：2)

### 题目大意

给出一个有若干个连通块无向图，求有多少个连通块满足 该连通块构成一个环

一个环，就是一个形如下图的连通块，满足点数与边数相等，且不应有多余的边
![image.png](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9pLmxvbGkubmV0LzIwMTkvMTIvMTkvNmdPWWxuNXJoUmNHd0JxLnBuZw?x-oss-process=image/format,png)
第一个想到的就是 dfs 判环：如果要访问的节点 $y$ 被访问过了，并且 $y$ 为当前连通块遍历的第一个节点 $top$ （也就是连通块遍历完了），`return true`；如果$y \ne top$ `return 0`

dfs 代码
```cpp
bool dfs(int x,int fa,int top)
{
	vis[x]=1;
	for(int i=0;i<e[x].size();++i)
	{
		int y=e[x][i];
		if(y==fa)continue;
		if(vis[y] && y!=top)return 0;
		if(y==top)return 1;
		bool flag=dfs(y,x,top);
		if(flag)return 1;
	}
	return 0;
}
```

写完发现过不了样例，又加了个 bfs 计算点数和边数，并判等

```cpp
bool bfs(int s)
{
	queue <int> q;
	int cnt=0,tot=0;
	vist[s]=1,q.push(s);
	while(q.size())
	{
		int x=q.front();
		q.pop();
		++cnt;
		if(d[x]!=2)return 0;  // 判断度数，后面会讲
		for(int i=0;i<e[x].size();++i)
		{
			int y=e[x][i];
			++tot;
			if(vist[y])continue;
			vist[y]=1,q.push(y);
		}
	}
	tot>>=1;
	return cnt==tot;
}
```

提交上去又双叒叕在第三个点挂了，仔细想了想后，发现环中的每个节点度数都为 $2$ ，加了判断度数后才AC

**完整代码：**

```cpp
#include<cstdio> 
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
const int Maxn=200000+20,inf=0x3f3f3f3f;
int n,m,ans;
bool vis[Maxn],vist[Maxn];
int d[Maxn];
vector <int> e[Maxn];
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
bool dfs(int x,int fa,int top)
{
	vis[x]=1;
	for(int i=0;i<e[x].size();++i)
	{
		int y=e[x][i];
		if(y==fa)continue;
		if(vis[y] && y!=top)return 0;
		if(y==top)return 1;
		bool flag=dfs(y,x,top);
		if(flag)return 1;
	}
	return 0;
}
bool bfs(int s)
{
	queue <int> q;
	int cnt=0,tot=0;
	vist[s]=1,q.push(s);
	while(q.size())
	{
		int x=q.front();
		q.pop();
		++cnt;
		if(d[x]!=2)return 0;
		for(int i=0;i<e[x].size();++i)
		{
			int y=e[x][i];
			++tot;
			if(vist[y])continue;
			vist[y]=1,q.push(y);
		}
	}
	tot>>=1;
	return cnt==tot;
}
int main()
{
//	freopen("in.txt","r",stdin);
	n=read(),m=read();
	for(int i=1;i<=m;++i)
	{
		int x=read(),y=read();
		e[x].push_back(y);
		e[y].push_back(x);
		d[x]++,d[y]++;
	}
	for(int i=1;i<=n;++i)
	{
		if(vis[i])continue;
		bool flag=dfs(i,0,i) && bfs(i);
		if(flag)++ans;
		//printf("i = %d  %d\n",i,flag);
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：FanYongchen (赞：2)

首先，不难看出，如果一个连通图为环，则它的每一个节点的[度](https://baike.baidu.com/item/%E8%8A%82%E7%82%B9%E5%BA%A6/8353467?fr=aladdin)一定为 $2$ 。

那么，我们就可以用深搜找连通块，然后判断每个点的度是不是 $2$ 就行了。

记录每个店的度可以用 ```vector``` 来存。

还有注意这是无向边。

```cpp
#include <iostream>
#include <vector>
using namespace std;
#define ms(x,y) memset(x,y,sizeof(x))
vector<int> v[200005];
bool vis[200005];
int n,m;
bool f;
void dfs(int u)//找连通块
{
    if(v[u].size()!=2) f=false;//判断每个点的度是否为2
    for(int i=0;i<v[u].size();i++)
        if(!vis[v[u][i]])
            vis[v[u][i]]=1,dfs(v[u][i]);//继续找下去
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        v[x].push_back(y);
        v[y].push_back(x);//注意这是无向边
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        if(!vis[i]) //找过的不用找了
            vis[i]=f=true,dfs(i),ans+=f;//如果为环，ans++
    cout<<ans;
    return 0;
}
```

---

## 作者：fjy666 (赞：1)

# 0x01 思路
- 环的特点是什么？  
- 环的个数和点的个数相等？
- 每个点的度为 $2$！  

什么是度？  
左转百度 [Link](https://baike.baidu.com/item/%E5%9B%BE/13018767?fr=aladdin)  
> 度（Degree）：一个顶点的度是指与该顶点相关联的边的条数，顶点v的度记作d(v)。

我们可以在读入边的时候预处理就OK了！

怎么找到一个环？  
$\texttt{DFS}$ 求联通块？  
珂以。  
我们先遍历所有点，对于每个度数不是 $2$ 的点，把它以及与之相连的点都标记掉。  

再对于剩下所有点，每找到一个也标记一下，顺便将环的总量增加 $1$。  
时间复杂度：$\Theta(n+m)$

# 0x02 代码
```cpp
#include <algorithm>
#include <cstdio>
#include <vector>
#include <bitset>
#define _for(i_,a_,b_) for(int i_ = a_;i_ < b_;++i_)
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
const int kN = 205000;
int degree[kN];
std::vector<int> edge[kN];
std::bitset<kN> isVisit;
void addEdge(int u,int v){
	edge[u].push_back(v);
	edge[v].push_back(u);
	++degree[u];++degree[v];
}
void dfs(int p){
	if(isVisit[p])return;
	isVisit[p] = 1;
	if(edge[p].size())
		_rep(i,0,edge[p].size() - 1)
			dfs(edge[p].at(i));
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m); 
	_rep(i,1,m){
		int u,v;
		scanf("%d%d",&u,&v);
		addEdge(u,v);
	}
	_rep(i,1,n){if(degree[i] != 2)dfs(i);} 
	int cntCycle = 0;
	_rep(i,1,n)
		if(!isVisit[i]){
			++cntCycle;
			dfs(i);
		}
	printf("%d",cntCycle);
    return 0;
}
```

---

## 作者：FiraCode (赞：0)

## 题解思路：
我们先用并查集来维护连通块，然后再判断每个联通块是否是环即可。

那么判断是否是环，我们就看看他每个点的度数是否都为 $2$ 就可以了。

那么再读入边的时候我们就维护一下并查集还有每个点的度数，那么当一个点的度数不为 $2$ 的时候，就把他所在的集合标记一下。

然后最后遍历一下所有的集合，看看是否标记就可以了。

## AC CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
int p[200010];
int du[200010];
bool st[200010];
int find(int x) {return x == p[x] ? x : p[x] = find(p[x]);}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)//初始化并查集
		p[i] = i;
	while (m--) {
		int a, b;
		scanf("%d%d", &a, &b);
		if (find(a) != find(b))
			p[find(a)] = find(b);//预处理并查集
		du[a] ++; du[b] ++;//度数+1
	}
	for (int i = 1; i <= n; ++i) {
		if (du[i] != 2) {//不满足条件
			st[find(i)] = true;//标记一下
		}
	}
	int res = 0;
	for (int i = 1; i <= n; ++i)
		if (p[i] == i && !st[i])//是环
			res ++;//答案++
	printf("%d\n", res);
	return 0;
}
```

---

## 作者：ZZQF5677 (赞：0)

### 解题思路
题面就说到了**根据定义，一个环至少需要包含三个点，且边数与点数应当是相同的**。但由于输入的图可能包含多了个图，那么我们就得细化到从每个点出发是否能够成一个环。首先，如果要构成环，那么还要每个点满足别的点连接这个点，这个点还要去连接另外一个点的条件，也就是一个点能连接其他 $2$ 个点，并且是只能连接 $2$ 个。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, ans;
vector<int> e[200005];
bool vis[200005];
bool f;
void bfs(int x) {
  queue<int> q;
  q.push(x);
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    if (vis[v]) {
      continue;
    }
    vis[v] = 1;
    if (e[v].size() != 2) {  //度必须等于2.
      f = 0;
    }
    for (int i = 0; i < e[v].size(); i++) {
      if (vis[e[v][i]]) {
        continue;
      }
      q.push(e[v][i]);
    }
  }
}
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    e[v].push_back(u);
    e[u].push_back(v);
  }
  for (int i = 1; i <= n; i++) {
    if (vis[i]) {
      continue;
    }
    f = 1;
    bfs(i);
    ans = ans + f;
  }
  printf("%d\n", ans);
  return 0;
}
```

---

## 作者：ModestCoder_ (赞：0)

求环的个数

直接dfs处理出每个连通块

然后如果一个连通块的所有点的度数都为2，那么是一个环

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 200010
using namespace std;
struct Edge{
	int to, next;
}edge[maxn << 1];
int num, head[maxn], n, m, d[maxn], vis[maxn], ans, cnt;
vector <int> loop[maxn];

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

void addedge(int x, int y){ edge[++num] = (Edge){y, head[x]}; head[x] = num; }

void dfs(int u){
	loop[cnt].push_back(u); vis[u] = 1;
	for (int i = head[u]; i; i = edge[i].next){
		int v = edge[i].to;
		if (!vis[v]) dfs(v);
	}
}

int main(){
	n = read(), m = read();
	for (int i = 1; i <= m; ++i){
		int x = read(), y = read();
		addedge(x, y), addedge(y, x);
		++d[x], ++d[y];
	}
	for (int i = 1; i <= n; ++i)
		if (!vis[i]) ++cnt, dfs(i);
	for (int i = 1; i <= cnt; ++i){
		int flag = 1;
		for (int j = 0; j < loop[i].size(); ++j)
			if (d[loop[i][j]] != 2){ flag = 0; break; }
		ans += flag;
	}
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：RainbOwO (赞：0)

# 一个环中，可以保证每个节点的度数为2
我们可以以样例为例，不难看出如果若干个节点可以构成一个环，那么这几个节点的度数必定为2

所以我们可以先进行vector邻接表存图（常规操作）

再通过dfs遍历该图，遍历的时候注意统计节点的度数（即ve[node].size()）

若度数不为2，说明与该节点所连的所有节点都不能构成环，则需要建立一个标记，
使其在最后结算的时候不用加上这个节点所能连通到的所有节点

vis[]数组用来记录哪些点被访问过了，被访问过的节点之后就可以不用重复访问了


```
#include<stdio.h>
#include<vector>
using namespace std;

vector<int>ve[200005];
bool vis[200005];
bool flag=1;

void build(int a,int b)///存无向图
{
    ve[a].push_back(b);
    ve[b].push_back(a);
}

void dfs(int node)
{
    int big=ve[node].size();
    if(big!=2)
    {
        flag=0;
    }
    for(int i=0; i<big; i++)
    {
        if(!vis[ve[node][i]])
        {
            vis[ve[node][i]]=1;
            dfs(ve[node][i]);
        }
    }
}

int main()
{
    int n,m,ans=0;
    scanf("%d%d",&n,&m);
    while(m--)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        build(a,b);
    }
    for(int i=1; i<=n; i++)
    {
        if(vis[i]==0)
        {
            dfs(i);
            if(flag==1) ans++;///结算
            else flag=1;///如果flag==0，则跳过ans++，再更新ans的值
        }
    }
    printf("%d\n",ans);
    return 0;
}
```


---

