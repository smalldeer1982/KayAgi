# Alyona and the Tree

## 题目描述

给你一棵树，边与节点都有权值，根节点为1，现不停删除叶子节点形成新树，问最少删掉几个点，能使得最后剩下的树内，$\forall v$与其子树内$\forall u$间边权的和小于等于点$u$权值

## 样例 #1

### 输入

```
9
88 22 83 14 95 91 98 53 11
3 24
7 -8
1 67
1 64
9 65
5 12
6 -80
3 8
```

### 输出

```
5
```

# 题解

## 作者：Edmundino (赞：2)

# 分析
这题正面去想比较难理解，

但是我们从反面去想：

我们找到符合此条件的点

最后拿n减去即可

所以就是用一个dfs去搜索

同时不断更新边权和的最大值

不符合的点就return

最后就可以求出符合点的个数

# 代码

如何储存

```cpp
cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=2;i<=n;i++)
	{
		cin>>x>>y;
		vec[x].push_back(i);
		vec[i].push_back(x);
		pou[i].push_back(y);
		pou[x].push_back(y);
	}
```
代码中的vec，pou都是vector

vec是存一个点相连的点

pou是存一个点所相连的边的边权



------------
如何dfs

```cpp
void dfs(long long u,long long sum)
{
	long long lon=vec[u].size();
	bo[u]=1;
	if(sum>a[u]) return;
	cs++;
	for(int i=0;i<lon;i++)
	{
		long long v=vec[u][i];
		if(bo[v]==0)
		{
			dfs(v,max(pou[u][i],sum+pou[u][i]));
		}
	}
	return;
}
```
bo数组用来记录此点是否访问过

cs便是符合的点的个数

dfs的sum是存边权和的最大值

由于边权可能为负数

所以我们求边权和的最大值时，

要探讨是从这个点出发比较大

还是之前的和加上此比较大



------------

最后送上AC完整代码


```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<iomanip>
#include<cmath>
#include<vector>

using namespace std;

const int N=100000+50;

vector<long long>vec[N],pou[N];

long long n,x,y,a[N],siz[N],cs;

bool bo[N];

void dfs(long long u,long long sum)
{
	long long lon=vec[u].size();
	bo[u]=1;
	if(sum>a[u]) return;
	cs++;
	for(int i=0;i<lon;i++)
	{
		long long v=vec[u][i];
		if(bo[v]==0)
		{
			dfs(v,max(pou[u][i],sum+pou[u][i]));
		}
	}
	return;
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=2;i<=n;i++)
	{
		cin>>x>>y;
		vec[x].push_back(i);
		vec[i].push_back(x);
		pou[i].push_back(y);
		pou[x].push_back(y);
	}
	dfs(1,0);
	cout<<n-cs;
	return 0;
} 
```


---

## 作者：极寒神冰 (赞：1)

题意可以转化为从一个点到根路径的最大前缀必须<=这个点点权，之后直接dfs不断加边权，到负数之后直接变0（要注意的是，任何一个祖先都可以，所以当上面传下来的和为负数的时候要舍掉），如果遇到一个子树要删掉，直接删除这个子树。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=200020;
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
struct edge
{
	int to,nxt,val;
}e[N];
int n;
int head[N],cnt,ans;
int a[N],sz[N];
inline void init()
{
	cnt=0;
	memset(head,-1,sizeof(head));
}
inline void add_edge(int u,int v,int d)
{
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	e[cnt].val=d;
	head[u]=cnt;
}
inline void dfs1(int u,int f)
{
	sz[u]=1;//先dfs一遍求出每个子树的大小
	for(int i=head[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==f) continue;
		dfs1(v,u);
		sz[u]+=sz[v];
	}

}
inline void dfs2(int u,int f,int sum)
{
	if(sum>a[u]) {ans+=sz[u];return;}//删除一个子树就加上这个子树大小
	for(int i=head[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==f) continue;
		dfs2(v,u,max(0ll,sum+e[i].val));
	}
}

signed main()
{
    init();
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
	}
	for(int i=2;i<=n;i++)
	{
		int x=read(),y=read();
		add_edge(i,x,y);add_edge(x,i,y);
	}
	dfs1(1,0);
	dfs2(1,0,0);
	cout<<ans;
}
```


---

## 作者：ZSYZSYZSYZSY (赞：0)

# CF682C Alyona and the Tree
[提交记录(CF)：277026613](https://codeforces.com/contest/682/submission/277026613)

## Main Idea

给你一棵树，边与节点都有权值，根节点为 $1$，现不停删除叶子节点形成新树，问最少删掉几个点，能使得最后剩下的树内，所有的 $u$ 和 $v$ 之间的距离小于等于 $a_u$。（$v$ 是 $u$ 的子树中的一个点）

## Solution
类似于求树上两点之间的距离的方法，用 $dis_u$ 表示根节点到 $u$ 的距离，所以 $u$ 和 $v$ 之间的距离即可表示为 $dis_v - dis_u$，用深搜即可预处理。

因为边的权值是有负数的，所以我们应该使用类似最大子段和的思想，从该节点往上的最大子段和。

例如以下的 $dis$ 数组的维护。
```cpp
dis[v] = max(0LL, dis[u] + w);
```

搜的过程中也可以同时预处理每个子树的大小，用 $sz_u$ 表示以 $u$ 为根节点的子树的大小。

每找到一组不满足题目给出条件的点和边就将其整个子树删除，然后最终答案加上该子树的大小即可。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define INF 1e17
inline ll read()
{
	ll x = 0, f = 1;
	char c = getchar();
	while(c < '0' || c > '9')
	{
		if(c == '-')
		{
			f = -1;
		}
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		x = (x << 1) + (x << 3) + c - '0';
		c = getchar();
	}
	return x * f;
}

ll p, head[500005], nxt[500005], to[500005], val[500005];
inline void add(ll u, ll v, ll w)
{
	nxt[++p] = head[u];
	head[u] = p;
	to[p] = v;
	val[p] = w;
}

ll ans;          //最终答案
ll a[500005];    //每个点的点权
ll dis[500005];  //表示根节点到u的距离
ll sz[500005];   //表示以u为根节点的子树的大小

void dfs(ll u, ll fa)//预处理dis[]和sz[]
{
	sz[u] = 1;
	for(ll i = head[u]; i; i = nxt[i])
	{
		ll v = to[i], w = val[i];
		if(v == fa)
		{
			continue;
		}
		dis[v] = max(0LL, dis[u] + w);
		dfs(v, u);
		sz[u] += sz[v];
	}
}

void dfs1(ll u, ll fa)//求答案
{
	if(dis[u] > a[u])
	{
		ans += sz[u];
		return ;
	}
	for(ll i = head[u]; i; i = nxt[i])
	{
		ll v = to[i];
		if(v == fa)
		{
			continue;
		}
		dfs1(v, u);
	}
}

int main()
{
	ll n = read();
	for (ll i = 1; i <= n; i++)
	{
		a[i] = read();
	}
	for (ll i = 1; i < n; i++)
	{
		ll u = i + 1, v = read(), w = read();
		add(u, v, w);//链式前向星建图
		add(v, u, w);
	}
	dfs(1, -1);
	dfs1(1, -1);
	cout << ans << endl;
	return 0;
}


```

---

## 作者：helium347 (赞：0)

# 题意：

- 树有 $n$ 个节点，根为 1，有点权、边权（有负数）

- 你能删除某个叶子



保证 “从一个点到**任意**祖先的**路径长**应小于其**点权**” ，求最少的节点删除数量。

---

# 思路：
深搜、树形 dp 均可，但已经有大佬写完了深搜的做法，我在这里写一下 **树形 dp** 的做法。

设：
- $pre[i]$ 为 节点 $i$ 到其任意祖先**路径长**的最大值

- $f[i]$ 为 节点 $i$ 的父节点编号

- $a[i]$ 为 节点 $i$ 的点权

- $w[i]$ 为 节点 $i$ 到其父节点的边权


最优子结构：$i$ 的最大路径一定来源于其祖先的最大路径

无后效性：$i$ 的子节点不影响 $i$ 的最大路径


### 递推式：
$$ pre[i] = \max(0, pre[f[i]] + w[i]);$$

因为研究 $i$ 的子节点时，取以下两种情况的最大值：

- 从 $i$ 出发

- 从之前的祖先出发


所以沿**拓扑正序**递推，最后沿拓扑正序计数即可

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
using ll = long long;
const int inf = 0x3f3f3f3f;
#define rf(i, n) for (int i = 1; i <= (n); ++i)
int rad(); // read int
const int max_size = 5 + 100;
const int maxn = 5 + 100000;

int n;
int f[maxn], a[maxn], w[maxn]; // 父节点，点权，到父节点的边权
int out_deg[maxn]; // 出度计数
ll pre[maxn]; // pre[i] = pre[f[i]] + w, 0
bool out[maxn]; // 是否需要删除

vector<int> order; // 逆拓扑序
void top_sort(int root = 1) {
    rf(i, n) if (out_deg[i] == 0)
        order.push_back(i);
    for (int i = 0; i < n; ++i) {
        if (--out_deg[f[order[i]]] == 0)
            order.push_back(f[order[i]]);
    }
}

int main() {
    n = rad();
    rf(i, n) a[i] = rad();
    for (int i = 2; i <= n; ++i)
        f[i] = rad(), w[i] = rad(), out_deg[f[i]]++;

    top_sort();
    for (int i = n - 1; i >= 0; --i) {
        int &now = order[i];
        pre[now] = max(0LL, pre[f[now]] + w[now]);
    }

    int ans = 0;
    for (int i = n - 1; i >= 0; --i) {
        int &now = order[i];
        if (out[f[now]] || pre[now] > a[now]) out[now] = true, ans++; // 父节点删除了，子节点也要删除
    }
    printf("%d", ans);
}

int rad() {
    int back = 0, ch = 0, neg = 0;
    for (; ch < '0' || ch > '9'; ch = getchar())
        neg = ch == '-';
    for (; ch >= '0' && ch <= '9'; ch = getchar())
        back = (back << 1) + (back << 3) + (ch & 0xf);
    return (back ^ -neg) + neg;
}
```


---

## 作者：影踪派武僧 (赞：0)

简单搜索题，我们每找到一组不满足题目给出条件的点和边就将其整个子树删除，然后最终答案加上该子树的大小即可。注意，搜索的时候如果当前的边权和sum已经为负了，应该将其改为0（可以想想为什么）

**注：题目翻译有误**

**原文中的小于应该改为小于等于**
```cpp
#include<bits/stdc++.h>
#define maxn 100005
using namespace std;
inline char get(){
	static char buf[30000],*p1=buf,*p2=buf;
	return p1==p2 && (p2=(p1=buf)+fread(buf,1,30000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	register char c=get();register int f=1,_=0;
	while(c>'9' || c<'0')f=(c=='-')?-1:1,c=get();
	while(c<='9' && c>='0')_=(_<<3)+(_<<1)+(c^48),c=get();
	return _*f;
}
struct edge{
	int u,v,w,next;
}E[maxn<<1];
int p[maxn],eid;
inline void init(){
	for(register int i=0;i<maxn;i++)p[i]=-1;
	eid=0;
}
inline void insert(int u,int v,int w){
	E[eid].u=u;
	E[eid].v=v;
	E[eid].w=w;
	E[eid].next=p[u];
	p[u]=eid++;
}
inline void insert2(int u,int v,int w){
	insert(u,v,w);
	insert(v,u,w);
}
int n;
int a[maxn];
int fa[maxn],size[maxn];
int ans=0;
inline void get_size(int u,int fa){
	size[u]=1;
	for(register int i=p[u];~i;i=E[i].next){
		int v=E[i].v;
		if(v==fa)continue;
		get_size(v,u);
		size[u]+=size[v];
	}
}
inline void dfs(int u,int fa,int sum){
	if(sum>a[u]){
		ans+=size[u];
		//cout<<sum<<" "<<a[u]<<endl;
		return;
	}
	for(register int i=p[u];~i;i=E[i].next){
		int v=E[i].v;
		int w=E[i].w;
		if(v==fa)continue;
		dfs(v,u,max(sum+w,0));
	}
}
int main(){
	//freopen("1.txt","r",stdin);
	init();
	n=read();
	for(register int i=1;i<=n;i++)a[i]=read();
	fa[1]=-1;
	for(register int i=2;i<=n;i++){
		int p=read(),c=read();
		fa[i]=p;
		insert2(i,p,c);
	}
	get_size(1,-1);
	dfs(1,-1,0);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Adove (赞：0)

简单的DFS

可以将问题转化为求剩下的点的个数，用总个数去减

```cpp
#include"cstdio"
#include"cstring"
#include"iostream"
#include"algorithm"
using namespace std;

const int MAXN=1e5+5;

int n,cnt,np;
int v[MAXN],h[MAXN];
struct rpg{
	int li,nx,ln;
}a[MAXN];

void add(int ls,int nx,int ln){a[++np]=(rpg){h[ls],nx,ln};h[ls]=np;}
void dfs(int x,long long sum)
{
	if(sum>v[x]) return;
	++cnt;
	for(int i=h[x];i;i=a[i].li) dfs(a[i].nx,max(0ll,sum+a[i].ln));
	return;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&v[i]);
	for(int i=2;i<=n;++i){
		int x,y;scanf("%d%d",&x,&y);
		add(x,i,y);
	}dfs(1,0ll);
	printf("%d\n",n-cnt);
	return 0;
}
```

---

