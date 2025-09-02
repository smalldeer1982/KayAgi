# Machine Schedule

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=246&page=show_problem&problem=3635

[PDF](https://uva.onlinejudge.org/external/11/p1194.pdf)

## 样例 #1

### 输入

```

5 5 10
0 1 1
1 1 2
2 1 3
3 1 4
4 2 1
5 2 2
6 2 3
7 2 4
8 3 3
9 4 3
0```

### 输出

```
3```

# 题解

## 作者：Binwens (赞：13)

**二分图最小点覆盖 基本裸题**

每个任务被两个点控制
只需一个点被覆盖
即为最小点覆盖
定理：
 _ _ _

------------
二分图最小点覆盖包含点数等于二分图最大匹配包含边数。_ _ _ 
此处略证明过程（Konig定理）


坑点：默认0模式 碰到0就不用处理。

上代码
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
const int N=550;
inline int read(){
    int ans=0;char c;bool flag=true;
    for(;c<'0'||c>'9';c=getchar())if(c=='-')flag=false;
    for(;c>='0'&&c<='9';c=getchar())ans=ans*10+c-'0';
    return flag ? ans : -ans;
}
struct Edge{
    int to,nxt;
}edge[N*N*4];
bool vis[N];
int match[N],head[N];
bool dfs(int u){
    for(int i=head[u];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(!vis[v]){
            vis[v]=1;
            if(!match[v]||dfs(match[v])){
                match[v]=u;
                return true;
            }
        }
    }
    return false;
}
int n,m,k,tot=1;
void add(int x,int y){
    edge[++tot].to=y;
    edge[tot].nxt=head[x];
    head[x]=tot;
}
int main()
{
//	freopen("5.in","r",stdin);
    int t,a,b;
    while(true){
        n=read();
        if(n==0)break;
        m=read();k=read();
        memset(edge,0,sizeof(edge));
        tot=1;
        memset(head,0,sizeof(head));
        memset(match,0,sizeof(match));
        for(int i=1;i<=k;i++){
         	t=read();a=read();b=read();
         	if(a==0||b==0)continue;//0模式默认 不用管 统计的都是重启了的 覆盖 
            add(a,b+n);
            add(b+n,a);
     	}
        int ans=0;
        for(int i=0;i<n;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i))ans++;
     	}
        printf("%d\n",ans);
    }
    return 0;
}
/*
5 5 10
0 1 1
1 1 2
2 1 3
3 1 4
4 2 1
5 2 2
6 2 3
7 2 4
8 3 3
9 4 3
0
*/
```


---

## 作者：xht (赞：11)

题目地址：[UVA1194 Machine Schedule](https://www.luogu.org/problemnew/show/UVA1194)

#### 二分图最小覆盖模型的要素

每条边有两个端点，二者至少选择一个。简称 $2$ 要素。

#### $2$ 要素在本题中的体现

每个任务要么在 $A$ 上以 $a_i$ 模式执行，要么在机器 $B$ 上以 $b_i$ 模式执行。

把 $A,B$ 的 $m$ 种模式分别作为 $m$ 个左部点和右部点，每个任务作为边连接左部 $a_i$ 节点和右部 $b_i$ 节点。

求这张二分图的最小覆盖，时间复杂度为 $O(nm)$ 。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 106;
int n, m, k, f[N], ans;
bool v[N];
vector<int> e[N];

bool dfs(int x) {
	for (unsigned int i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		if (v[y]) continue;
		v[y] = 1;
		if (!f[y] || dfs(f[y])) {
			f[y] = x;
			return 1;
		}
	}
	return 0;
}

inline void Machine_Schedule() {
	cin >> m >> k;
	for (int i = 1; i <= n; i++) e[i].clear();
	for (int i = 0; i < k; i++) {
		int x, y;
		scanf("%d %d %d", &i, &x, &y);
		e[x].push_back(y);
	}
	memset(f, 0, sizeof(f));
	ans = 0;
	for (int i = 1; i <= n; i++) {
		memset(v, 0, sizeof(v));
		ans += dfs(i);
	}
	cout << ans << endl;
}

int main() {
	while (cin >> n && n) Machine_Schedule();
	return 0;
}
```

---

## 作者：Plus_Ultra (赞：5)

### 题解：

很容易看出这是一个求二分图最小点覆盖问题.

n个点为左半部分点集，m个点为右半部分点集.

二分图最小点覆盖：

- 给定一张二分图，求出一个最小的点集 S，使得图中任意一条边都已至少一个端点属于 S.这个问题被称为二分图的最小点覆盖.

问题转化：

- 我们知道一个任务可以看做一条边，对应的a[i]和b[i]分别为两端点.因为一个任务必须由这两个模式中的一个来完成，即为在一条边中至少有一个点属于最小点覆盖.

- 由定理可知：二分图最小点覆盖包含的点数 = 二分图最大匹配包含的边数.

- 证明： [此博客写的不错](https://blog.csdn.net/qq_41730082/article/details/81456611).

- 那么我们求二分图的最大匹配即可

解决二分图最大匹配大概有两种做法，
 
  -  网络流算法. 就是在原图的基础上建一个源点，再建一个汇点，跑最大流即可.不过本题 EK 会炸，所以要用Dinic，介于本文主要介绍匈牙利算法，这里不再赘叙.
  
  -  匈牙利算法. 前方内容较多，大佬们可跳过.


一. 二分图最大匹配

    • 匹配：选出图的边集 E 的一个子集 F，使 V1 和 V2 中的每个点
最多关联了 F 中的一条边。

    • 最大匹配：选出的子集包含边的个数最大。


二. 增广路定理

设 F 是一个匹配。

    • V1, V2 中被 F 覆盖到的点称为饱和点，未覆盖到的叫非饱和点。

    • F 中的边称为匹配边，其它的叫非匹配边。

    • 交错路：从非饱和点出发，依次经过非匹配边、匹配边、非匹配边、匹配边、非匹配边……

    • 增广路：从非饱和点出发最后走到一个非饱和点的交错路。

    • 增广路中非匹配边比匹配边多一条。

    • 如果图中存在增广路，则把经过的非匹配边和匹配边互换，能得到更大的匹配 F′。 

    • 如果 F 不是最大匹配，则存在增广路。


四. 增广路算法

  1. 一开始，F 为空。

  2. 每次找 F 的增广路，能找到就增广。

  3. 找不到增广路时，算法结束。


五. 匈牙利算法

  1. 一开始，F 为空。

  2. 枚举 V1 中的点 x，找以 x 为起点的增广路，找到了就增广。

  3. V1 中的点都尝试增广一次后，算法结束。

定理：如果在某一时刻，找不到以 x 为起点的增广路，则增广几轮之后仍不会找到。

时间复杂度：O(nm)

下面分析一下板子：


```
#include<iostream>

using namespace std;

const int V=1000010;
int N,M,E,ans;
int edge[V],head[1010],nxt[V],tot;
int dfn[2020],match[1010],x,y,ti;

void add(int x,int y)//加边
{
	edge[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}

int dfs(int x,int ti)//ti是时间戳
{
	for(int i=head[x];i;i=nxt[i])
	{
		int j=edge[i];
		if(dfn[j]!=ti)//这一轮还没有遍历到
		{
			dfn[j]=ti;
			if(!match[j]||dfs(match[j],ti))//没有和j点匹配的点或者是找到了一条可增广的路径
			{
				match[j]=i;//i,j匹配
				return 1;
			}
		}
			  
	}
	return 0;
}

int main()
{
	cin>>N>>M>>E;
	for(int i=1;i<=E;i++)
	{
		cin>>x>>y;
		if(x>N||y>M)  continue;
		add(x,y);
	}
	
	for(int i=1;i<=N;i++)
		if(dfs(i,++ti))  ans++;//找到了一条增广路
		
	cout<<ans<<endl;
	
	return 0;
}
```

OK，有了板子之后就可以直接套上去了.

不过有一个要注意的地方：一条边 k ，其两端点为x,y，假如x=0或者y=0，那么直接跳过即可（不用再重新启动）.

下面上代码（我知道各位大佬也不需要代码）：

```
#include<iostream>
#include<cstring>

#define N 210
#define M 20010

using namespace std;

int n,m,k,vis[N],mat[N],a,x,y,ans;
int edge[M],nxt[M],head[N],tot;//记得，边数和点数要开够 

void add(int x,int y)//邻接表 
{
	edge[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}

int match(int x)//找匹配 
{
	for(int i=head[x];i;i=nxt[i])
	{
		int y=edge[i];
		if(!vis[y])//没被x点遍历过 
		{
			vis[y]=1;
			if(!mat[y]||match(mat[y]))//还没有匹配点或能找到替换路 
			{
				mat[y]=x;//匹配 
				return 1;
			}
		}
	}
	return 0;
}

int main()
{
	while(cin>>n&&n)
	{
		memset(mat,0,sizeof(mat));tot=0;
		memset(head,0,sizeof(head));
		cin>>m>>k; ans=0;//初始化 
		for(int i=1;i<=k;i++)
		{
			cin>>a>>x>>y;
			if(!x||!y)  continue;//直接跳过 
			add(x,y+n),add(y+n,x);//为了没有重复，右半部分点+n来存储 
		}
		for(int i=1;i<=n;i++)
		memset(vis,0,sizeof(vis)),ans+=match(i);//记得初始化 
		cout<<ans<<endl;
	}
	
	return 0;
} 
```

### [Plus Ultra!!!](https://www.luogu.org/blog/OnePunchManGO/)

---

## 作者：niiick (赞：2)

#### **二分图最小点覆盖集**

**定义：**

在二分图中求出一个**最小点集**
使得图中**任意一条边至少有一个端点**在点集内

换句话说，
若一个点能覆盖**所有与他的连边**
要求一个最小点集覆盖所有边

**解法：**

对二分图进行**最大匹配**，
**最大匹配数**就是二分图的最小点覆盖集包含的点数
******************
把A机器的n个点作为二分图的左部，B机器的m个点作为右部

对于每个任务的两种模式$A_x,B_y$，
将**左部的第x个点 与 右部的第y个点**连边

这样每条边代表一个任务，每个点代表一种模式

题目要求用最少的模式完成所有任务，
也就相当于用最少的点覆盖所有边，
即这个二分图的**最小点覆盖集**
************

```cpp
//niiick
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;

int read()
{
    int f=1,x=0;
    char ss=getchar();
    while(ss<'0'||ss>'9'){if(ss=='-')f=-1;ss=getchar();}
    while(ss>='0'&&ss<='9'){x=x*10+ss-'0';ss=getchar();}
    return f*x;
}

const int inf=1e9;
const int maxn=510;
int n,m,k,s,t;
struct node{int v,f,nxt;}E[maxn*100];
int head[maxn],tot=1;
int lev[maxn],maxf;

void add(int u,int v,int f)
{
	E[++tot].nxt=head[u];
	E[tot].v=v; E[tot].f=f;
	head[u]=tot;
}

int bfs()
{
	queue<int> q; q.push(s);
	memset(lev,-1,sizeof(lev)); lev[s]=0;
	while(!q.empty())
	{
		int u=q.front(); q.pop();
		for(int i=head[u];i;i=E[i].nxt)
		{
			int v=E[i].v;
			if(E[i].f&&lev[v]==-1)
			{
				lev[v]=lev[u]+1;
				if(v==t) return 1;
				q.push(v);
			}
		}
	}
	return 0;
}

int dfs(int u,int cap)
{
	if(u==t) return cap;
	int flow=cap;
	for(int i=head[u];i;i=E[i].nxt)
	{
		int v=E[i].v;
		if(E[i].f&&lev[v]==lev[u]+1&&flow)
		{
			int f=dfs(v,min(E[i].f,flow));
			flow-=f;
			E[i].f-=f; E[i^1].f+=f;
		}
	}
	return cap-flow;
}

void init()
{
	maxf=0; tot=1;
	memset(head,0,sizeof(head)); 
}

int main()
{
	while(scanf("%d",&n)!=EOF)
	{
		if(n==0) break; init();
		m=read();k=read();t=n+m+1;
		
		for(int i=1;i<=n;++i)
		add(s,i,1),add(i,s,0);
		for(int i=1;i<=m;++i)
		add(i+n,t,1),add(t,i+n,0);
		
		for(int i=1;i<=k;++i)
		{
			int num=read(),x=read(),y=read();
			if(x*y==0) continue;
			add(x,y+n,inf); add(y+n,x,0);
		}
		
		while(bfs()) 
		maxf+=dfs(s,inf);
		
		printf("%d\n",maxf);
	}
	return 0;
}

```


---

## 作者：Swanwan_OWO (赞：2)

本蒟蒻人生第一次发题解竟然是这个......
我很菜，菜到爆炸的我想了一晚上才发现原来不就是水题么
（逃
有些像模板，我垃圾就没做那么多优化和删减了，既然是模板，应该不用有过多的解释吧
粘代码了
```c
#include<cstdio>

const int MAX=2099999999;

int array[250][250];
bool book[250];
int gath[250];

int n,m,k;

void fset(void);
bool ga(int);

int main()
{
	int trash,x,y;
	int sum;
	while((scanf("%d",&n)==1)&&(n))//多组数据不解释
	{
		scanf("%d%d",&m,&k);
		fset();
		sum=0;
		for(int i=0;i<k;i++)
		{
			scanf("%d%d%d",&trash,&x,&y);//编号是垃圾
			if((x!=0)&&(y!=0))//坑点
			{
				array[x][n+y]=1;
			}
		}
		for(int i=0;i<n;i++)
		{
			for(int g=0;g<n+m;g++)
			{
				book[g]=true;
			}
			if(ga(i))
			{
				sum++;
			}
		}
		printf("%d\n",sum);
	}
	return 0;
} 

void fset(void)
{
	for(int i=0;i<n+m;i++)
	{
		for(int j=0;j<n+m;j++)
		{
			array[i][j]=MAX;//坑点
		}
	}
	for(int i=0;i<n+m;i++)
	{
		gath[i]=-1;//坑点
	}
	return;
}
bool ga(int w)
{
	book[w]=false;
	for(int i=n;i<n+m;i++)
	{
		if((array[w][i]==1)&&(book[i]))
		{
			book[i]=false;
			if((gath[i]==-1)||(ga(gath[i])))
			{
				gath[i]=w;
				return true;
			}
		}
	}
	return false;
}
```

好了，做了2遍感觉坑的地方就这么多了，如果你觉得我一个绿名都是大佬了，呃，我真的一直在刷入门题谢谢！

---

## 作者：逃离地球 (赞：1)

[题目链接](https://www.luogu.org/problem/UVA1194)

把机器A的n个模式作为n个左部节点，机器B的m个模式作为m个右部节点，每个任务是一条边，连接a[i]和b[i]。由于每个任务需要在A和B之间选一个，所以求这个二分图的最小点覆盖就相当于用最少的模式完成任务。

由König定理，二分图最小点覆盖包含的点数等于二分图最大匹配包含的边数。所以只需求那张图的最大匹配即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int INF=10e8;
#define FOR(i,m,n) for (register int i = m; i <= n; i++)
#define _FOR(i,m,n) for (register int i = m ; i >= n; i--)
#define QAQ printf("QAQ\n");

int n,m,e,Map[1001][1001],match[1001]={0},vis[1001];

bool dfs(int x){
	for(int i=1;i<=m;i++){
		if(Map[x][i]&&!vis[i]){
			vis[i]=1;
			if(!match[i]||dfs(match[i])){
				match[i]=x;
				return true;
			}
		}
	}
	return false;
}//匈牙利

int main() {
	while(1){
		cin>>n;
		if(n==0)
			break;
		cin>>m>>e;
		
		int x,y,jntm;
		memset(Map,0,sizeof(Map));
		memset(match,0,sizeof(match));
		
		for(int i=0;i<e;i++){
			cin>>jntm>>x>>y;//输入的第一个数毫无作用
			if(x==0||y==0){
				continue;
			}
			Map[x][y]=1;
		}
		
		int cnt=0;
		for(int i=1;i<=n;i++){
			memset(vis,0,sizeof(vis));
			cnt+=dfs(i);//求最大匹配
		}
		cout<<cnt<<endl;
	}
		
    return 0;
}
```



---

## 作者：fanfansann (赞：0)

本题中每一个任务要么在A机器上以$a[i]$执行，要么在B机器上以$b[i]$执行，二者比选其一。
因此我们可以将A机器的N种模式作为N个左部点，机器B的M种模式作为M个右部点，每一个任务以一个无向边连接$a[i]$和$b[i]$，意味着左右两部选一即可。
那么这张图很显然就是一张二分图，我们直接求出它的最小点覆盖，也就是用尽可能少的点覆盖每一条边，既是用尽可能少的点完成所有的任务，也就是用尽量少的模式（等价于最少的重启次数）来完成所有的任务。
因为数据较小，我们可以直接跑一个匈牙利算法求最大匹配数，最大匹配数 = 最小点覆盖

要注意的是由于刚开始两个机器的模式都是0，因此所有可以用模式0完成的任务就可以直接不重启完成，也就是不用加这种的边计算了。
时间复杂度：$O(NM)$
```cpp
/*最小点覆盖问题*/

#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

const int N = 207, M = 5007;

int n, m, k;
int match[N];
int g[N][N];
bool vis[N];

bool find(int x){
    for(int i= 1;i <= m;++ i){
        if(!vis[i] && g[x][i]){
            vis[i] = true;
            int t = match[i];
            if(t == -1 || find(t)){
                match[i] = x;
                return true;
            }
        }
    }
    return false;
}

int main(){
    while(~scanf("%d%d%d",&n, &m, &k) && n){
        memset(g,0,sizeof g);
        for(int i = 1;i <= k;++ i){
            int t,a,b;
            scanf("%d%d%d",&t, &a,&b);
            if(a == 0 || b == 0)continue;
            g[a][b] = true;
        }
    
        int res = 0;
        memset(match, -1, sizeof match);
        for(int i = 0;i < n;++ i){
            memset(vis,0,sizeof vis);
            if(find(i))
            res ++ ;
        }
        printf("%d\n",res);
    }
    return 0;
}

```


---

## 作者：youngk (赞：0)

这道题求的是二分图的最小点覆盖，看到其余的题解都是用匈牙利算法实现的，所以可以将二分图的最小点覆盖，转化成网络流的最小割，也就是求最大流，上一波网络流算法。

DINIC:

```
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<set>
#define _USE_MATH_DEFINES
#include<math.h>
#include<queue>
#include<vector>
#include<limits.h>
#include<functional>
#include<stack>
typedef long long ll;
#pragma GCC optimize(2)
using namespace std;
inline void write(int x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) {
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (isdigit(ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}
#define maxm 211000
#define maxn 10200
int n, m, cnt = 1, s, t, maxflow, cost;
int head[maxn], to[maxm], Next[maxm], val[maxm], depth[maxn], cur[maxn], w[maxm], dis[maxn], h[maxn], e[maxn], gap[maxn];
bool vis[maxn];
void add(int u, int v, int w)
{
	to[++cnt] = v;
	val[cnt] = w;
	Next[cnt] = head[u];
	head[u] = cnt;
}
void addedge(int u, int v, int w)
{
	add(u, v, w);
	add(v, u, 0);
}
bool bfs()
{
	queue<int> q;
	memset(depth, 0x3f, sizeof(depth));
	memset(vis, 0, sizeof(vis));
	memcpy(cur, head, sizeof(head));
	depth[s] = 0;
	q.push(s);
	while (q.size())
	{
		int u = q.front();
		q.pop();
		for (int i = head[u]; i; i = Next[i])
		{
			int v = to[i];
			if (depth[v] > depth[u] + 1 && val[i])
			{
				depth[v] = depth[u] + 1;
				if (v == t)
					break;
				if (!vis[v])
				{
					q.push(v);
					vis[v] = true;
				}
			}
		}
	}
	return depth[t] != 0x3f3f3f3f;
}
int dfs(int u, int flow)
{
	int rlow = 0;
	if (u == t)
	{
		maxflow += flow;
		return flow;
	}
	int used = 0;
	for (int i = cur[u]; i; i = Next[i])
	{
		cur[u] = i;
		int v = to[i];
		if (val[i] && depth[v] == depth[u] + 1 && (rlow = dfs(v, min(val[i], flow - used))))
		{
			used += rlow;
			val[i] -= rlow;
			val[i ^ 1] += rlow;
			if (used == flow)
				break;
		}
	}
	return used;
}
void dinic()
{
	while (bfs())
		dfs(s, INT_MAX);
}
int a, b;
signed main()
{
	while (true)
	{
		a = read();
		if (!a)
			break;
		b = read(), m = read();
		memset(head, 0, sizeof(head));
		memset(to, 0, sizeof(to));
		memset(val, 0, sizeof(val));
		memset(Next, 0, sizeof(Next));
		cnt = 1;
		maxflow = 0;
		s = maxn - 10, t = maxn - 9;
		for (int i = 1; i <= a; i++)
			addedge(s, i, 1);
		for (int i = 1; i <= b; i++)
			addedge(1000 + i, t, 1);
		while (m--)
		{
			int num = read(), x = read(), y = read();
			addedge(x, 1000 + y, 1);
		}
		dinic();
		write(maxflow);
		puts("");
	}
	return 0;
}
```

ISAP:

```
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<set>
#define _USE_MATH_DEFINES
#include<math.h>
#include<queue>
#include<vector>
#include<limits.h>
#include<functional>
#include<stack>
typedef long long ll;
#pragma GCC optimize(2)
using namespace std;
inline void write(int x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) {
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (isdigit(ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}
#define maxm 211000
#define maxn 10200
int n, m, cnt = 1, s, t, maxflow, cost;
int head[maxn], to[maxm], Next[maxm], val[maxm], depth[maxn], cur[maxn], w[maxm], dis[maxn], h[maxn], e[maxn], gap[maxn];
bool vis[maxn];
void add(int u, int v, int w)
{
	to[++cnt] = v;
	val[cnt] = w;
	Next[cnt] = head[u];
	head[u] = cnt;
}
void addedge(int u, int v, int w)
{
	add(u, v, w);
	add(v, u, 0);
}
void isap_bfs()
{
	memset(depth, 0x3f, sizeof(depth));
	memset(gap, 0, sizeof(gap));
	depth[t] = 0;
	gap[0] = 1;
	queue<int> q;
	q.push(t);
	while (q.size())
	{
		int u = q.front();
		q.pop();
		for (int i = head[u]; i; i = Next[i])
		{
			int v = to[i];
			if (depth[v] != 0x3f3f3f3f || val[i])
				continue;
			q.push(v);
			depth[v] = depth[u] + 1;
			gap[depth[v]]++;
		}
	}
	return;
}
int isap_dfs(int u, int flow)
{
	if (u == t)
	{
		maxflow += flow;
		return flow;
	}
	int used = 0;
	for (int i = cur[u]; i; i = Next[i])
	{
		cur[u] = i;
		int v = to[i];
		if (val[i] && depth[v] + 1 == depth[u])
		{
			int minflow = isap_dfs(v, min(val[i], flow - used));
			if (minflow)
			{
				val[i] -= minflow;
				val[i ^ 1] += minflow;
				used += minflow;
			}
			if (used == flow)
				return used;
		}
	}
	--gap[depth[u]];
	if (!gap[depth[u]])
		depth[s] = maxn - 10;
	depth[u]++;
	gap[depth[u]]++;
	return used;
}
void isap()
{
	isap_bfs();
	while (depth[s] < maxn - 10)
	{
		memcpy(cur, head, sizeof(head));
		isap_dfs(s, INT_MAX);
	}
}
int a, b;
signed main()
{
	while (true)
	{
		a = read();
		if (!a)
			break;
		b = read(), m = read();
		memset(head, 0, sizeof(head));
		memset(to, 0, sizeof(to));
		memset(val, 0, sizeof(val));
		memset(Next, 0, sizeof(Next));
		cnt = 1;
		maxflow = 0;
		s = maxn - 10, t = maxn - 9;
		for (int i = 1; i <= a; i++)
			addedge(s, i, 1);
		for (int i = 1; i <= b; i++)
			addedge(1000 + i, t, 1);
		while (m--)
		{
			int num = read(), x = read(), y = read();
			addedge(x, 1000 + y, 1);
		}
		isap();
		write(maxflow);
		puts("");
	}
	
	return 0;
}
```


---

## 作者：COUPDETAT (赞：0)

# 二分图点最小覆盖

**点覆盖**的概念定义：
对于图G=(V,E)中的一个点覆盖是一个集合S⊆V使得每一条边至少有一个端点在S中。
最小点覆盖：点个数最少的S集合。

可以通过二分图匹配，匈牙利算法来解决最小点覆盖问题

①最小点集覆盖<=最大匹配，
假设最小点集覆盖为n, 那么一定能构造出一个为n的匹配， 显然这个匹配<= 最大匹配

②最小点集覆盖 >= 最大匹配。

综上：

**最小点集覆盖 == 最大匹配**

【匈牙利算法】

把二分图分为A,B两个集合，依次枚举A中的每个点，试图在B集合中找到一个匹配。

【Hopcroft-Karp算法】

利用匈牙利算法找到增广路径

## 拓展
**最大独立集**

定义：选出一些顶点使得这些顶点两两不相邻，则这些点构成的集合称为独立集。找出一个包含顶点数最多的独立集称为最大独立集。

**定理：最大独立集 = 所有顶点数 - 最小顶点覆盖 = 所有顶点数 -   最大匹配**

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#define maxn 200200
using namespace std;
vector<int>edges[maxn];
bool state[maxn];
 int result[maxn];
 int n,m,a,b,tot = 0;
bool find(int x)
{
	for(int i = 0;i < edges[x].size();++i)
	{
		int o = edges[x][i];
		if(!state[o])
		{
			state[o] = true;
			if(result[o] == 0 || find(result[o]))
			{
				result[o] = x;
				return true;
			}
		}
	}
	return false;
}
int main()
{
//	freopen("erfen.in","r",stdin);
	while(1)
	{
		tot=0;
		memset(result,0,sizeof(result));
		int n1,n2; 
		cin >> n1;
		if(n1==0) break;
		cin>>n2 >> m;
		n=max(n1,n2);
		for(int i = 1;i <= m;++i)
		{
			int j;
			cin >> j >> a >> b;
			if(a<=n1&&b<=n2)
			edges[a].push_back(b);
		}
		for(int i = 1;i <= n;++i)
		{
			memset(state,0,sizeof(state));
			if(find(i))tot++;
		}
		cout << tot << endl;
		for(int i=1;i<=m;i++)
		edges[i].clear();
	} 
	return 0;
 }
```


---

