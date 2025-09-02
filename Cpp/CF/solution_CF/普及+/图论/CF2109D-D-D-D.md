# D/D/D

## 题目描述

当然，这道以字母 D 开头的题目是由 Declan Akaba 赞助的。

给定一个简单、连通的无向图，包含 $n$ 个顶点和 $m$ 条边。图中没有自环或重边。同时给定一个包含 $\ell$ 个元素的多重集 $A$：
$$ A = \{A_1, A_2, \ldots, A_\ell\} $$

从顶点 $1$ 出发，你可以执行以下操作任意次数（只要多重集 $A$ 不为空）：
- 从多重集 $A$ 中选择一个元素 $k$ 并移除它（必须移除 $k$ 的一个实例）。
- 遍历恰好包含 $k$ 条边的任意路径$^{\text{∗}}$，到达某个顶点（可以是起始顶点本身）。

对于每个 $i$（$1 \le i \le n$），判断是否存在一个操作序列，使得从顶点 $1$ 出发，使用原始多重集 $A$，最终能到达顶点 $i$。

注意：对每个顶点 $i$ 的检查是独立的——每次都需要从顶点 $1$ 重新开始，并使用原始多重集 $A$。

$^{\text{∗}}$ 长度为 $k$ 的路径是指一个顶点序列 $v_0, v_1, \ldots, v_{k-1}, v_k$，其中每对相邻顶点 $(v_i, v_{i+1})$ 都由图中的一条边连接。序列中允许包含重复的顶点。

## 说明/提示

**第一个测试用例解释：**
- 顶点 $1$ 无需任何操作即可到达。
- 顶点 $2$ 可通过选择 $A$ 中的元素 $3$ 到达，例如路径 $[1 \rightarrow 2 \rightarrow 1 \rightarrow 2]$。
- 顶点 $3$ 可通过选择 $A$ 中的元素 $2$ 并走路径 $[1 \rightarrow 2 \rightarrow 3]$ 到达。
- 顶点 $4$ 可通过选择 $A$ 中的元素 $3$ 并走路径 $[1 \rightarrow 2 \rightarrow 3 \rightarrow 4]$ 到达。
- 顶点 $5$ 无法通过任何有效操作序列到达。
- 顶点 $6$ 可通过以下方式到达：
  1. 选择 $A$ 中的元素 $2$ 并走路径 $[1 \rightarrow 2 \rightarrow 3]$；
  2. 选择 $A$ 中的元素 $3$ 并走路径 $[3 \rightarrow 4 \rightarrow 5 \rightarrow 6]$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
6 5 2
2 3
1 2
2 3
3 4
4 5
5 6
5 5 1
5
1 2
2 3
3 4
4 5
3 5
5 4 3
100 200 300
1 2
1 3
1 4
2 5```

### 输出

```
111101
11111
10001```

# 题解

## 作者：rich_xty (赞：1)

首先，观察题目，我们不难想到如果到达目标后所走的步数的奇偶性与可以走的步数的奇偶性相同，且现在的步数小于等于可以走的步数，那么一定可以找到一条路径满足要求，因为我们可以在同一条边上来回走去，只要走两步就可以走回原点。

接下来，我们又想到我们可以用集合中的数来拼出一些数，并且求出这些数中最大的奇数和最大的偶数，然后再求出从起点到各个节点的长度为奇数的最短路以及长度为偶数的最短路。

那么，最后，我们只需要比较每个奇数长度的最短路径和奇数的最大限制还有每个偶数长度的最短路径和偶数的最大限制即可得出结果。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+5;
int t,n,m,l,ans,ma,mb;
int a[N],ji[N],ou[N];
vector<int> g[N];
queue<pair<int,int> >q;
void bfs(){
	for(int i=1;i<=n;i++) ji[i]=ou[i]=1e15;
	while(!q.empty()) q.pop();
	ou[1]=0;
	for(int i=0;i<g[1].size();i++){
		ji[g[1][i]]=1;
		q.push(make_pair(g[1][i],1));
	}
	while(q.size()){
		int x=q.front().first,y=q.front().second;
		for(int i=0;i<g[x].size();i++){
			if(y%2==1){
				if(y+1<ou[g[x][i]]){
					ou[g[x][i]]=y+1;
					q.push(make_pair(g[x][i],y+1));
				}
			}else{
				if(y+1<ji[g[x][i]]){
					ji[g[x][i]]=y+1;
					q.push(make_pair(g[x][i],y+1));
				}
			}
		}
		q.pop();
	}
}
void work(){
	cin>>n>>m>>l;
	for(int i=1;i<=n;i++) g[i].clear();
	ans=1e15,ma=mb=0;
	for(int i=1;i<=l;i++){
		cin>>a[i];
		ma+=a[i];
		if(a[i]%2) ans=min(ans,a[i]);
	} 
	if(ma%2==0){
		mb=ma;
		if(ans!=1e15) ma=mb-ans;
		else ma=0;
	} 
	else if(ans!=1e15) mb=ma-ans;
	for(int i=1;i<=m;i++){
		int u,v; cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	bfs();
	for(int i=1;i<=n;i++){
		if(ji[i]<=ma || ou[i]<=mb) cout<<1;
		else cout<<0;
	}
	cout<<'\n';
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>t;
	while(t--) work();
	return 0;
}

```

---

## 作者：E_M_T (赞：0)

好像 C 难一些啊。


因为边可以重复走，所以如果能通过 $x$ 条边走到 $u$ 则一定可以反复一次，通过 $x+2$ 条边走到 $u$。

（唯一不行的情况是 $1$ 走到自己且没有边，但图联通且 $n\ge 2$ 所以不会有这种情况。）

同理通过 $x+2d$（$d\in N$） 条边也可以。

即转化为奇偶问题，如果我们能找到一条 $1\to i$ 经过 $x$ 条边的路径使得它和 $a$ 中某些数的和 $sum$ 的奇偶性一样，且 $sum\ge x$ 就可以到达。

处理出每个点的奇偶最短路和 $a$ 能够凑出的最大奇数/偶数即可。

```cpp
#include<bits/stdc++.h>
#define sd std::
#define int long long
#define inf 1e12
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define ff(i,a,b) for(int i=(a);i>=(b);i--)
#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
#define me(x,y) memset(x,y,sizeof x)
#define pii sd pair<int,int>
#define X first
#define Y second
#define Fr(a) for(auto it:a)
#define dbg(x) sd cout<<#x<<":"<<x<<" "
#define dg(x) sd cout<<#x<<":"<<x<<"\n"
int read(){int w=1,c=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;for(;ch>='0'&&ch<='9';ch=getchar()) c=(c<<3)+(c<<1)+ch-48;return w*c;}
void printt(int x){if(x>9) printt(x/10);putchar(x%10+48);}
void print(int x){if(x<0) putchar('-'),printt(-x);else printt(x);}
void put(int x){print(x);putchar('\n');}
void printk(int x){print(x);putchar(' ');}
const int N=4e5+10;
int n,m,k,A[N],dis[N][2];//奇偶最短路
struct node
{
	int nex;
	int to;
}a[N<<1];
int tot,head[N];
void add(int u,int v)
{
	a[++tot].nex=head[u];
	head[u]=tot;
	a[tot].to=v;
}
struct xhx
{
	int u;
	int tp;
	xhx(int x,int y)
	{
		u=x;
		tp=y;
	}
};
sd queue<xhx> q;
int vis[N][2];
void dij(int s)
{
	F(i,0,n) dis[i][0]=dis[i][1]=inf,vis[i][0]=vis[i][1]=0;
	dis[s][0]=0;
	q.push(xhx(s,0));
	while(!q.empty())
	{
		auto [u,tp]=q.front();q.pop();
		if(vis[u][tp]) continue;
		vis[u][tp]=1;
		for(int i=head[u];i;i=a[i].nex)
		{
			int v=a[i].to;
			if(dis[v][!tp]>dis[u][tp]+1)
			{
				dis[v][!tp]=dis[u][tp]+1;
				q.push(xhx(v,!tp));
			}
		}
	}
}
int max[2],mi,sum;//A中最小的奇数
void solve()
{
	tot=0;
	n=read(),m=read(),k=read();
	F(i,1,n) head[i]=0;
	mi=inf;
	sum=0;
	F(i,1,k)
	{
		A[i]=read(),sum+=A[i];
		if(A[i]&1) mi=MIN(mi,A[i]);
	}
	if(sum&1) max[1]=sum,max[0]=sum-mi;
	else max[0]=sum,max[1]=sum-mi;
	
	
	F(i,1,m)
	{
		int x=read(),y=read();
		add(x,y);
		add(y,x);
	}
	dij(1);
	
	
	F(i,1,n)
	{
		if(max[0]>=dis[i][0]&&dis[i][0]!=inf) print(1);
		else if(max[1]>=dis[i][1]&&dis[i][1]!=inf) print(1);
		else print(0);
	}
	puts("");
}
signed main()
{
	int T=1;
	T=read();
	while(T--) solve();
    return 0;
}
```

---

