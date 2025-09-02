# 広告

## 题目描述

有$r$行$c$列的矩阵，矩阵中的点有`.`，还有`*`。

要求选尽量多的`.`，使其两两不相邻。

## 说明/提示

$1\leq r,c\leq 40$

矩阵中只有`.字符`和`*字符`

## 样例 #1

### 输入

```
3 3
...
...
...```

### 输出

```
5```

## 样例 #2

### 输入

```
2 2
**
**```

### 输出

```
0```

## 样例 #3

### 输入

```
1 1
.```

### 输出

```
1```

## 样例 #4

### 输入

```
3 4
*..*
..**
*...```

### 输出

```
4```

# 题解

## 作者：sunkuangzheng (赞：5)

我们知道网格图黑白染色后是二分图，那么这道题就是让求二分图最大独立集。

我们有经典结论：二分图最大独立集等于 二分图顶点数 减去 二分图最大匹配，那么跑一遍二分图匹配即可。

因为这是 atcoder 题，你可以使用 `#include <atcoder/maxflow>`。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 05.01.2024 07:51:35
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
debug_helper deg;
#endif
#include <atcoder/maxflow>
using ll = long long;
const int N = 5e5+5;
using namespace std;
using namespace atcoder;
int n,ct,dx[5] = {0,0,1,0,-1},dy[5] = {0,1,0,-1,0},m,S,T;string s[45];
void los(){
    cin >> n >> m;
    mf_graph<int> g(n * m + 2);
    S = 0,T = n * m + 1;
    for(int i = 1;i <= n;i ++)
        cin >> s[i],s[i] = " " + s[i];
    auto id = [&](int x,int y){return (x - 1) * m + y;};
    for(int i = 1;i <= n;i ++) for(int j = 1;j <= m;j ++){
        if(s[i][j] != '.') continue; ct ++;
        if((i + j) % 2) g.add_edge(S,id(i,j),1); else {g.add_edge(id(i,j),T,1);continue;}
        for(int k = 1;k <= 4;k ++){
            int ax = i + dx[k],ay = j + dy[k];
            if(ax >= 1 && ay >= 1 && ax <= n && ay <= m && s[ax][ay] == '.')
                g.add_edge(id(i,j),id(ax,ay),1); 
        }
    }cout << ct - g.flow(S,T);
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    los();
}
```

---

## 作者：henry_qwh (赞：1)

**[题目传送门](https://www.luogu.com.cn/problem/AT_soundhound2018_c)**

### 题目大意

有一个由 `.` 和 `*` 组成的矩阵，选出最多的 `.` 使其两两互不相邻。

### 解题思路

要求出互不相邻的 `.` 很难实现，那么我们考虑统计所有 `.` 的个数，再求出不选的 `.` 的个数，最后相减即为答案。

我们令 `.` 的贡献为 $1$，令 `*` 的贡献为 $0$，然后对所有的 `.` 像国际象棋一样进行黑白染色，则所有的相邻的 `.` 颜色必然不同。这样，我们得到了一个二分图，原问题即为求该二分图的最大独立集。我们有定理 **二分图最大独立集 = 总点数 - 二分图最大匹配**，这也契合了我们上面的思想。

具体实现上，我们可以用最小割的思想。我们建立一个超级源点和一个超级汇点，由超级源点向每一个 `.` 连容量为 $1$ 的边，并由每个黑点向白点连容量为 $+\infty$ 的边，防止被割掉，而没有被割掉的边对应点的贡献之和即为答案，也即该二分图的最大独立集。最后使用最大流即可解决问题，时间复杂度为 $O(\sqrt nm)$。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
const int inf = 0x3f3f3f3f;
const int dx[] = {0,0,1,-1};
const int dy[] = {1,-1,0,0};

int s,t,cnt = 1,ans;
int g[N][N],head[N*N],dep[N*N],num[N][N];

struct edge
{
	int to,nxt,w;
} e[N*N*8];

void add(int u,int v,int w)
{
	cnt++;
	e[cnt].to = v;
	e[cnt].w = w;
	e[cnt].nxt = head[u];
	head[u] = cnt;
}

bool bfs()
{
	memset(dep,-1,sizeof(dep));
	queue<int> q;
	dep[s] = 1;
	q.push(s);
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int i = head[u];i;i = e[i].nxt)
		{
			int v = e[i].to,w = e[i].w;
			if (dep[v] == -1 && w)
			{
				dep[v] = dep[u]+1;
				q.push(v);
			}
		}
	}
	return dep[t] != -1;
}

int dfs(int u,int f)
{
	if (u == t) return f;
	int used = 0;
	for (int i = head[u];i;i = e[i].nxt)
	{
		int v = e[i].to,w = e[i].w;
		if (dep[v] == dep[u]+1 && w)
		{
			int tmp = dfs(v,min(f-used,w));
			used += tmp;
			e[i].w -= tmp;
			e[i^1].w += tmp;
		}
	}
	if (!used) dep[u] = -1;
	return used;
}

void dinic()
{
	while (bfs())
		ans -= dfs(s,inf);
}

int main()
{
	int n,m,cc = 0;
	cin >> m >> n;
	s = 0,t = 1e6;
	for (int i = 1;i <= m;i++)
		for (int j = 1;j <= n;j++)
		{
			char c;
			cin >> c;
			g[i][j] = (c == '.') ? 1 : 0;
			ans += g[i][j];
			num[i][j] = ++cc;
		}
	for (int i = 1;i <= m;i++)
		for (int j = 1;j <= n;j++)
		{
			if (((i+j)%2)==0)
			{
				add(s,num[i][j],g[i][j]);
				add(num[i][j],s,0);
			}
			else
			{
				add(num[i][j],t,g[i][j]);
				add(t,num[i][j],0);
			}
		} 
	for (int i = 1;i <= m;i++)
		for (int j = 1;j <= n;j++)
			if (((i+j)%2)==0)
			 	for (int k = 0;k < 4;k++)
			 	{
			 		int x = i+dx[k],y = j+dy[k];
			 		if (x >= 1 && y >= 1 || x <= m || y <= n)
			 		{
			 			add(num[i][j],num[x][y],inf);
			 			add(num[x][y],num[i][j],0);
			 		}
				}
	dinic();
	cout << ans << endl;
	
	return 0;
}
```

---

## 作者：luuia (赞：1)

### 题目大意

给定一个 $01$ 矩阵，要求在其中选出最多的 $1$ 使得它们之间没有相邻的边。

### Solution

我们可以考虑建立一个二分图，将相邻的两块分到两个不同的子集中连边，再求出最大独立集即可。

因为在最小点覆盖中，任意一条边都被至少选了一个顶点，所以对于其点集的补集，任意一条边都被至多选了一个顶点，所以不存在边连接两个点集中的点，且该点集最大。

因此二分图中，最大独立集 $=n \,-$  最小点覆盖。而最小点覆盖就是二分图的最大匹配，因此用网络流求出二分图的最大匹配即可。

具体地，按 $x+y$ 的奇偶将每个点分为黑点和白点，并向周围的四个点连边，将所有的黑点连到源点，所有的白点连到汇点，跑 dinic 求最大匹配即可。

加强版：

[P2774 方格取数问题](https://www.luogu.com.cn/problem/P2774)

[P4474 王者之剑](https://www.luogu.com.cn/problem/P4474)


[P3365 骑士共存问题](https://www.luogu.com.cn/problem/P3355)

[P4304 [TJOI2013] 攻击装置](https://www.luogu.com.cn/problem/P4304)

[P5030 长脖子鹿放置](https://www.luogu.com.cn/problem/P5030)

### Code

[AC 记录](https://www.luogu.com.cn/record/164582529)

```cpp
#include<bits/stdc++.h>
using namespace std;

int read()
{
	int s = 0,w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		if(ch == '-') w = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	return s * w;
}

const int N = 1e6 + 10,inf = 0x3f3f3f3f;
const int dx[5] = {0,0,0,1,-1};
const int dy[5] = {0,1,-1,0,0};

long long n,m,S,T,u,flow,w,op,v,maxflow,a[110][110],num[110][110],color[110][110];
long long sum,cnt = 1,head[N],dep[N],x[N];
struct EDGE
{
	int to,nxt,flow;
}e[N];

void add(int u,int flow,int w)
{
	e[++cnt].to = flow,e[cnt].flow = w,e[cnt].nxt = head[u],head[u] = cnt;
	e[++cnt].to = u,e[cnt].flow = 0,e[cnt].nxt = head[flow],head[flow] = cnt;
}

bool bfs()
{
	int step = 0,t = 0;
	memset(dep,-1,sizeof(dep));
	x[t++] = S,dep[S] = 0;
	while(step < t)
	{
		int now = x[step++];
		for(int i = head[now];i;i = e[i].nxt)
		{
			int v = e[i].to;
			if(dep[v] == -1 && e[i].flow)
			{
				dep[v] = dep[now] + 1;
				x[t++] = v;
			}
		}
	}
	if(dep[T] != -1) return 1;
	return 0;
}

int dfs(int x,int step)
{
	if(x == T) return step;
	int w,used = 0;
	for(int i = head[x];i;i = e[i].nxt)
	{
		int v = e[i].to;
		if(dep[v] == dep[x] + 1 && e[i].flow)
		{
			w = dfs(v,min(step - used,e[i].flow));
			e[i].flow -= w;
			e[i ^ 1].flow += w;
			used += w;
			if(used == step) return step;
		}
	}
	if(!used) dep[x] = -1;
	return used;
}

void dinic(){while(bfs()) maxflow += dfs(S,inf);}

bool check(int x,int y){return (x >= 1 && x <= m && y >= 1 && y <= n);}

void init(){memset(head,0,sizeof(head)),cnt = 1;}

void build_edge()
{
	for(int i = 1;i <= m;i++)
	{
		for(int j = 1;j <= n;j++)
		{
			if(color[i][j] == 0)
			{
				add(S,num[i][j],a[i][j]);
				for(int k = 1;k <= 4;k++)
				{
					int xx = i + dx[k],yy = j + dy[k];
					if(check(xx,yy)) add(num[i][j],num[xx][yy],inf);
				}
			}
			else add(num[i][j],T,a[i][j]);
		}
	}
}

int main()
{
	// freopen("input.in","r",stdin);
	init();m = read(),n = read();S = 0,T = 1e5;
	for(int i = 1;i <= m;i++)
	{
		for(int j = 1;j <= n;j++)
		{
		    char ch = getchar();
		    if(ch == '\n') ch = getchar();
		    if(ch == '.') a[i][j] = 1;else a[i][j] = 0;
			sum += a[i][j],op++,num[i][j] = op;
			color[i][j] = (i + j) % 2;
		}
	}
	build_edge(),dinic();
	cout << sum - maxflow << endl;
	return 0;
}
```

---

## 作者：Ryan_Adam (赞：0)

## 题解：AT_soundhound2018_c 広告
### Tag
网络流
### Solution
个人感觉这题的思路很像 [AT_abc193_f Zebraness](https://www.luogu.com.cn/problem/AT_abc193_f)，也可能是这种思路很典，反正多一道题不是啥坏事。

我们发现直接求不相邻的点最多有多少很困难，转化一下，我们找到相邻的点最少有多少，用总点数减去就行了。接下来经典套路，把二维的点转换为一维，将原图黑白染色，即求颜色不同的点的个数最少有多少。把黑点连源点 $s$，白点连汇点 $t$，再把原图中相邻关系的点连上，直接跑 `Dinic` 即可。
### Code
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=1e6+5;
const int INF=0x3f3f3f3f;
int n,m,s,t,k;
struct edge
{
    int nxt,to,val;
}e[N];
int ans;
int now[N];
int dis[N],head[N],cnt=1;

void add(int u,int v,int w)
{
    e[++cnt].to=v;
    e[cnt].val=w;
    e[cnt].nxt=head[u];
    head[u]=cnt;

    e[++cnt].to=u;
    e[cnt].val=0;
    e[cnt].nxt=head[v];
    head[v]=cnt;
}

bool bfs()
{
    memset(dis,-1,sizeof(dis));
    queue<int> q;
    q.push(s);
    dis[s]=0;
    now[s]=head[s];
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=e[i].nxt)
        {
            int v=e[i].to;
            if(e[i].val>0&&dis[v]==-1)
            {
                q.push(v);
                dis[v]=dis[u]+1;
                now[v]=head[v];
                if(v==t)return 1;
            }
        }
    }
    return 0;
}

int dfs(int x,int sum)
{
    if(x==t)return sum;
    int k,res=0;
    for(int i=now[x];i&&sum;i=e[i].nxt)
    {
        now[x]=i;
        int v=e[i].to;
        if(e[i].val>0&&dis[v]==dis[x]+1)
        {
            k=dfs(v,min(sum,e[i].val));
            if(k==0)dis[v]=-1;
            e[i].val-=k;
            e[i^1].val+=k;
            sum-=k;
            res+=k;
        }
    }
    return res;
}

void Dinic()
{
    while(bfs())
        ans+=dfs(s,INF);
    return ;
}

char mp[50][50];

int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
int id(int x,int y)
{
    return (x-1)*m+y;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int anss=0;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>mp[i][j],anss+=(mp[i][j]=='.');
    s=0,t=n*m+1;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if((i+j)%2==0)
                add(s,id(i,j),(mp[i][j]=='.'));
            else
                add(id(i,j),t,(mp[i][j]=='.'));
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if((i+j)%2==0)
            {
                for(int k=0;k<4;k++)
                {
                    int x=i+dx[k],y=j+dy[k];
                    if(x<1||x>n||y<1||y>m)continue;
                    add(id(i,j),id(x,y),INF);
                }
            }
        }
    }
    Dinic();
    cout<<anss-ans<<endl;
    return 0;
}
```

---

