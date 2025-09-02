# Almost Acyclic Graph

## 题目描述

You are given a [directed graph](https://en.wikipedia.org/wiki/Directed_graph) consisting of $ n $ vertices and $ m $ edges (each edge is directed, so it can be traversed in only one direction). You are allowed to remove at most one edge from it.

Can you make this graph [acyclic](https://en.wikipedia.org/wiki/Directed_acyclic_graph) by removing at most one edge from it? A directed graph is called acyclic iff it doesn't contain any cycle (a non-empty path that starts and ends in the same vertex).

## 说明/提示

In the first example you can remove edge ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF915D/f1138b32236a89525fad2b8c02b9cbfbd546dfad.png), and the graph becomes acyclic.

In the second example you have to remove at least two edges (for example, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF915D/7480c546ca7ee72615c3ded7d769355b1c864f93.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF915D/f1138b32236a89525fad2b8c02b9cbfbd546dfad.png)) in order to make the graph acyclic.

## 样例 #1

### 输入

```
3 4
1 2
2 3
3 2
3 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
5 6
1 2
2 3
3 2
3 1
2 1
4 5
```

### 输出

```
NO
```

# 题解

## 作者：青烟绕指柔 (赞：14)

------

我们可以想一下，对于拓扑排序，我们删边的实质是什么？

就是让一个点的入度减一，使得这个点由原来不能放到队列当中，而现在可以到队列当中。

所以我们完全没有必要枚举删边，因为删的很多边实质都是使同一个点的入度减一。

所以我们枚举每个点的入度减一，然后拓扑排序判断环即可。

-----

```cpp
#pragma GCC optimize("-Ofast","-funroll-all-loops")
#include<bits/stdc++.h>
//#define int long long
using namespace std;
const int N=510;
int n,m,dag[N],t[N];
vector<int> g[N];
inline int top_sort(){
	int cnt=0;	queue<int> q;
	for(int i=1;i<=n;i++)	if(!dag[i])	q.push(i);
	while(q.size()){
		int u=q.front();	q.pop();	cnt++;
		for(auto to:g[u])	if(--dag[to]==0)	q.push(to);
	}
	return cnt==n;
}
signed main(){
	cin>>n>>m;
	for(int i=1,a,b;i<=m;i++)	scanf("%d %d",&a,&b),g[a].push_back(b),dag[b]++;
	for(int i=1;i<=n;i++)	t[i]=dag[i];
	for(int i=1;i<=n;i++)	if(dag[i]){
		dag[i]--;	if(top_sort())	return puts("YES"),0;
		for(int i=1;i<=n;i++)	dag[i]=t[i];
	}
	puts("NO");
	return 0;
}
```


---

## 作者：大菜鸡fks (赞：7)

先随便搜出一个环，再暴力断边，dfs检验

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const int N=505,M=100005;
struct edge{
    int link,next;
}e[M];
int tot,n,m,head[N];
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
inline void add_edge(int u,int v){
    e[++tot]=(edge){v,head[u]}; head[u]=tot;
}
inline void init(){
    n=read(); m=read();
    for (int i=1;i<=m;i++) {
        int u=read(),v=read();
        add_edge(u,v);
    }
}
bool flag;
int top,tmp,vis[N],stack[N],vis_edge[M];
void dfs(int u){
    vis[u]=1;
    for (int i=head[u];i;i=e[i].next){
        int v=e[i].link;
        if (flag) return;
        if (vis[v]==1){
            stack[++top]=i; flag=1;
            return;
        }
        if (!vis_edge[i]&&!vis[v]){
            stack[++top]=i;
            dfs(v);
            if (!flag) top--;
        }
    }
    vis[u]=2;
}
void Dfs(int u){
    vis[u]=1;
    for (int i=head[u];i;i=e[i].next){
        int v=e[i].link;
        if (i==tmp) continue;
        if (flag){
            return;
        }
        if (vis[v]==1){
            flag=1;
            return;	
        }
        if (!vis[v])Dfs(v);
    }
    vis[u]=2;
}
inline void solve(){
    for (int i=1;i<=n;i++) {
        top=0; if (!vis[i]) dfs(i);
        if (flag) break;
    }
    if (flag){
        for (int i=1;i<=top;i++){
            memset(vis,0,sizeof vis);
            tmp=stack[i]; flag=0;
            for (int j=1;j<=n;j++) {
                if (!vis[j]) Dfs(j);
                if (flag) break; 
            }
            if (!flag) {
                puts("YES");
                return;
            }
        }
        puts("NO");
    }else{
        puts("YES");
    }
}
int main(){
    init(); solve();
    return 0;
}
```

---

## 作者：蒟蒻且菜鸡 (赞：6)

题意简单明了，我们只需要注意一个点：删边的时候可以删一条边也可以一条都不删。

有一个很简单很暴力的办法就是枚举删除每一条边的情况，进行拓扑排序但是时间复杂度是  $O(m^2)$  的，会炸掉。

考虑删除每条边后拓扑排序的实质：让每个点的入度减一。这就启示我们可以枚举每个点在入度减一的情况下拓扑排序，是否还存在环就行了。

拓扑排序判环的方法是：整张图的深度大小是否等于节点个数。
```
#include<bits/stdc++.h>
using namespace std;
int t[550],in[550];//in,t都代表入度，t储存着整张图最原始的入度 ，因为在每次拓扑排序后，in中所存储的深度都会改变 
vector<int> g[550];
bool vis[550];
int n,m;
bool topo()
{
	memset(vis,false,sizeof(vis));//记录这个点是否拥有深度 
	int cnt=0;//记录深度 
	queue<int> q;
	for(int i=1;i<=n;i++)
	{
		if(in[i]==0)
		{
			vis[i]=true;
			q.push(i);
		} 
	}
	while(!q.empty())
	{
		int now=q.front();
		q.pop();
		cnt++;
		for(int i=0;i<g[now].size();i++)
		{
			in[g[now][i]]--;
		}
		for(int i=1;i<=n;i++)
		{
			if(in[i]==0&&!vis[i])
			{
				q.push(i);
				vis[i]=true;
			} 
		}
	}
	if(cnt==n) return true;
	else return false;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		in[v]++;
	}
	for(int i=1;i<=n;i++) t[i]=in[i];
	if(topo())
	{
		cout<<"YES";
		return 0;
	} 
	for(int i=1;i<=n;i++) in[i]=t[i];
	for(int i=1;i<=n;i++)
	{
		if(in[i])
		{
			in[i]--;
		    if(topo())
		    {
			   cout<<"YES";
			   return 0;
		    } 
		    for(int i=1;i<=n;i++) in[i]=t[i];
		}
	}
	cout<<"NO";
	return 0;
}
```


---

## 作者：hmya (赞：6)

这个题就是说给你 $n$ 个点 $m$ 条有向边，让你随便删一边（可以不删），问能不能搞出一个有向无环图。

众所周知，拓扑排序可以判断图里面有没有环，所以有一种朴素的做法：首先枚举边，然后然后把这条边弄掉，再然后跑拓扑，最后判断有没有环，有环继续做，没环直接输出。

这个算法时间复杂度是多少呢？首先 $O(m)$ 枚举边，然后 $O(n+m)$ 跑拓扑排序，总时间复杂度为 $O(m(n+m))$。

时间复杂度直接爆炸。

我们想想，删掉一条有向边对拓扑排序产生的影响是什么？

显然，是被指向的点的入度减一。

那么，这样一想，**如果这些边指向的点是相同的，那么删掉这些边，对拓扑排序的影响也是相同的**。

于是我们的策略转变为枚举点。

枚举到这个点，只要这个点入度不为 $0$，入度就减一，再跑一遍拓扑排序，最后判断有没有环，有环继续做，没环直接输出。

这个算法的时间复杂度是 $O(n(n+m))$，非常的牛逼。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,yikao[101010],m,rd[101010];
vector<int> aa[101010];
queue<int>q;
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		aa[x].push_back(y);
		rd[y]++;
	}
	for(int j=1;j<=n;j++){
		for(int i=1;i<=n;i++){//多用不重置，保龄两行泪
			yikao[i]=rd[i];
		}
		if(rd[j]==0){
			continue;
		}
		yikao[j]--;
		for(int i=1;i<=n;i++){
			if(!yikao[i]){
				q.push(i);
			}
		}
		int sum=0;
		while(!q.empty()){//拓扑排序
			sum++;
			for(int i=0;i<aa[q.front()].size();i++){
				yikao[aa[q.front()][i]]--;
				if(!yikao[aa[q.front()][i]]){
					q.push(aa[q.front()][i]);
				}
			}
			q.pop();
		}
		if(sum==n){//判断有没有环
			printf("YES");
			return 0;
		}
	}
	printf("NO");//没有环就输出NO
	return 0;
}	
```

---

## 作者：CharlesZiy (赞：3)

## 写在前面

这题想出了正解思路就很简单了，但要注意一些细节。

## 正文

如何判断一个图有没有坏？

用拓扑排序（复杂度 $O(n+m)$）。如果一张图的拓扑序列长度恰是其点数，那么显然地，这张图没有环。第一个问题我们解决了。

说到删边，我们第一想到的就是暴力枚举去删每条边然后进行拓扑排序。但是，正如其他大佬论述过的，这样的复杂度要乘上 $m$，最终是 $O(m(n+m))$。看一眼数据范围，肯定会炸。

之后，我们来想一下拓扑排序的模板：

```cpp
bool topsort()
{
	queue<int> q;
	int cnt = 0;
	
	for (int i = 1; i <= n; i++) in[i] = IN[i];
	
	for (int i = 1; i <= n; i++)
	{
		if (in[i] == 0) q.push(i);
	}
	
	while (!q.empty())
	{
		int u = q.front(); q.pop();
		cnt++;
		for (int i = 0; i < e[u].size(); i++)
		{
			int cur = e[u][i];
			in[cur]--;
			if (in[cur] == 0)
			{
				q.push(cur);
			}
		}
	}
	
	return (cnt == n);
}
```

容易发现，如果你用 `vector` 邻接表存图（其实别的存图方法肯定也行，只是 `vector` 更明显），跟删的是哪一条边**一点关系都没有啊！**

在拓扑排序中，我们关心的是**一个点的入度**而非**边**本身。

此时问题就很明朗了：我们枚举点而非枚举边。把枚举到的点的入度减 $1$ 就相当于删了一条边，同时这种情况囊括了删去所有指向这个点的边的情况。在本题中，$n$ 的值域远远小于 $m$ 的值域。于是，我们就可以快乐地拿下这道紫题啦！

## 代码实现

记得我说过这题细节很多吗？

1. 统计拓扑序长度的时候**不能放到最里层循环**（其实这是拓扑排序基本知识吧……）；

2. 每一次拓扑排序都要把原来的入度数组复制一份过来，因为在拓扑排序中会对入度数组进行操作。因为我们要多次使用这个数组，因此保留一份副本是必须的。

考虑到这些细节，就可以开始动手啦：

### Code

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define MAXM 100005
#define MAXN 505
using namespace std;

int n, m;
vector<int> e[MAXN];
int in[MAXN];
int IN[MAXN];

bool topsort()
{
	queue<int> q;
	int cnt = 0;
	
	for (int i = 1; i <= n; i++) in[i] = IN[i];
	
	for (int i = 1; i <= n; i++)
	{
		if (in[i] == 0) q.push(i);
	}
	
	while (!q.empty())
	{
		int u = q.front(); q.pop();
		cnt++;
		for (int i = 0; i < e[u].size(); i++)
		{
			int cur = e[u][i];
			in[cur]--;
			if (in[cur] == 0)
			{
				q.push(cur);
			}
		}
	}
	
	return (cnt == n);
}

int main()
{
	std::ios::sync_with_stdio(false);
	
	cin >> n >> m;
	
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		IN[v]++;
	}
	
	for (int i = 1; i <= n; i++)
	{
		bool flag = 0;
		if (IN[i] != 0)
		{
			IN[i]--;
			flag = true;
		}
		
		if (topsort())
		{
			cout << "YES" << endl;
			return 0;
		}
		
		if (flag == true) IN[i]++;
	}
	
	cout << "NO" << endl;
}
```

~~如果觉得蒟蒻讲得好不妨点个赞吧……球球了……~~

---

## 作者：Nukumizu_Kaju (赞：2)

有一个显然的暴力：

暴力删边，删完之后拓扑判断有没有环，时间复杂度 $O(m(n+m))$，显然炸。

我们考虑，删掉一条边对于拓扑的贡献是什么。

一个点入度减一。

**那么对于多条指向同一个点 $u$ 的边，删掉其中任意一条边所作出的贡献是一样的。**

既然这样，我们就枚举一个点，让他入度减一后再跑拓扑排序，这相当于删掉其中一条指向他的边，这么做之后判断有没有环就行了。

时间复杂度 $O(n(n+m))$，飕飕快。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
vector<int> ljb[505];
int rd[505];
int Rd[505];
bool topo(){//跑拓扑
    queue<int> q;
    int cnt=0;
    for(int i=1;i<=n;i++){
        Rd[i]=rd[i];
    }
    for(int i=1;i<=n;i++){
        if(Rd[i]==0)q.push(i);
    }
    while(!q.empty()){
        cnt++;
        int tmp=q.front();
        q.pop();
        for(int i=0;i<ljb[tmp].size();i++){
            int v=ljb[tmp][i];
            Rd[v]--;
            if(Rd[v]==0){
                q.push(v);
            }
        }
    }
    return (cnt==n);//判断又没有环
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        ljb[u].push_back(v);
        rd[v]++;
    }
    for(int i=1;i<=n;i++){
        bool flag=false;
        if(rd[i]!=0)rd[i]--,flag=true;//删去一条指向点i的边（有可能没有指向i的边，特判一下即可）
        if(topo()){
            puts("YES");
            return 0;
        }
        if(flag)rd[i]++;//如果有指向i的边，入度记得加回来
    }
    puts("NO");
    return 0;
}
```

---

## 作者：happybob (赞：2)

# 题意

给定一张 $n$ 个点 $m$ 条边的图，问是否可以删除一条边使得整个图没有环。

# 解法

先考虑暴力，删除每一条边用拓扑排序判断环，复杂度 $O(m \times (m + n)) = O(m^2 + m \cdot n)$，明显 $O(m^2)$ 已经承受不下，因为这是一个稠密图。

考虑删边的本质，其实就是将那条有向边的终点的入度 $-1$，考虑对于每一个入度 $\ge 1$ 的点的入度 $-1$，复杂度 $O(n \times (m+n))$，可以通过。

另外注意，每次拓扑后入度数组会改变，要两个数组储存，我一开始就是因为这个错了好多次。

用时：$810ms$。

代码：

```cpp
#ifdef ONLINE_JUDGE
#pragma GCC optimize(2)
#endif
#include <bits/stdc++.h>
using namespace std;

const int N = 505;

int n, m, u, v, in[N], cop[N];
vector<int> G[N], ans;

bool tsort()
{
	ans.clear();
	queue<int> q;
	for (int i = 1; i <= n; i++)
	{
		cop[i] = in[i];
		if (cop[i] == 0) q.push(i);
	}
	while (!q.empty())
	{
		int l = q.front();
		q.pop();
		ans.push_back(l);
		for (int i = 0; i < G[l].size(); i++)
		{
			int nx = G[l][i];
			cop[nx]--;
			if (cop[nx] == 0) q.push(nx);
		}
	}
	return ans.size() == n;
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		scanf("%d %d", &u, &v);
		G[u].push_back(v);
		in[v]++;
	}
	for (int i = 1; i <= n; i++)
	{
		if (in[i] > 0)
		{
			in[i]--;
			if (tsort()) 
			{
				printf("YES\n");
				return 0;
			}
			in[i]++;
		}
	}
	printf("NO\n");
	return 0;
}
```


---

## 作者：郑朝曦zzx (赞：1)

# 一 解题思路

## 前置知识：拓扑排序与判环

拓扑排序是可以用来判环的，我们想象一下，假如某个图里有环，那么一定有至少两个点相互制约。这是因为它们的父亲节点并没有被访问，而它们也不能被访问，但是它们互为父亲节点。

打一个形象的比方，你的老师催你写作业，你说，我同桌写作业我就写作也，而你的同桌说，如果你写作业他也写作业，容易想象，最终的结果是，你和同桌都没有写作业。

## 本题的解法

删掉一条边，本质上是使一个点的**入度减一**，如果我们枚举删去每一条边，就会有大量重复的情况被计算。故**不妨枚举每个点**被删去一条如边，再跑拓扑排序判环，这样就能在 $n$ 次拓扑排序内得到答案。

# 二 代码
```cpp
#include <cstdio>
#include <vector>
#include <queue> 
using namespace std;
const int maxn = 505;
int n, m;
vector <int> g[maxn];
int in[maxn], rem[maxn];
queue <int> q;
bool check()
{
	while (!q.empty()) q.pop();
	int cnt = 0;
	for (int i = 1; i <= n; ++i)
		if (in[i] == 0)
			q.push(i);
	while (!q.empty())
	{
		int node = q.front();
		q.pop(); ++cnt;
		for (int i = 0; i < g[node].size(); ++i)
			if (--in[g[node][i]] == 0)
			{
				in[g[node][i]] = 0;
				q.push(g[node][i]);
			}
	}
	return (cnt == n);
}
int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; ++i)
	{
		int f, t; scanf("%d %d", &f, &t);
		g[f].push_back(t);
		++in[t];
	}
	for (int i = 1; i <= n; ++i)
		rem[i] = in[i];
	for (int i = 1; i <= n; ++i)
	{
		if (in[i] == 0) continue;
		--in[i];
		if (check() == 1)
		{
			printf("YES\n");
			return 0;
		}
		for (int j = 1; j <= n; ++j)
			in[j] = rem[j];
	}
	printf("NO\n");
	return 0;
}
```


---

## 作者：Nero_Claudius (赞：1)

这道题我第一次的想法是直接判环的数量，然而事实证明实在是太naive了。

随便画个图都可以卡掉我的解法。（不知道在想什么）

------------

这道题的正解是拓扑排序。

朴素的想法是对所有边都跑一次拓扑，但这样$O(m(n+m))$会炸，于是可以有下面的优化。

我们找到所有入度不为零的点，然后把他们每一个都删掉一条边跑一遍拓扑排序。

那么这样就可以优化到$O(n(n+m))$了，稳得一批。

------------

AC代码如下：

`1935ms 1356kb`

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace StandardIO {

	template<typename T>inline void read (T &x) {
		x=0;T f=1;char c=getchar();
		for (; c<'0'||c>'9'; c=getchar()) if (c=='-') f=-1;
		for (; c>='0'&&c<='9'; c=getchar()) x=x*10+c-'0';
		x*=f;
	}

	template<typename T>inline void write (T x) {
		if (x<0) putchar('-'),x*=-1;
		if (x>=10) write(x/10);
		putchar(x%10+'0');
	}

}

using namespace StandardIO;

namespace Solve {
	
	const int N=505;
	
	int n,m;
	vector<int>graph[N];
	int indeg[N];
	queue<int>q;
	
	inline bool toposort (int n) {
		int temp[N],size=0;
		memcpy(temp,indeg,sizeof(indeg));
		while (!q.empty()) q.pop();
		for (register int i=1; i<=n; ++i) {
			if (temp[i]==0) q.push(i),size++;
		}
		while (!q.empty()) {
			int v=q.front();q.pop();
			for (register int i=0; i<graph[v].size(); ++i) {
				int to=graph[v][i];
				temp[to]--;
				if (temp[to]==0) q.push(to),size++;
			}
		}
		return size>=n;
	}
	
	inline void solve () {
		read(n),read(m);
		for (register int i=1; i<=m; ++i) {
			int x,y;
			read(x),read(y);
			indeg[y]++;
			graph[x].push_back(y);
		}
		for (register int i=1; i<=n; ++i) {
			if (indeg[i]!=0) {
				indeg[i]--;
				if (toposort(n)) {
					puts("YES");
					return;
				}
				indeg[i]++;
			}
		}
		puts("NO");
	}
}

using namespace Solve;

int main () {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	solve();
}

```

---

## 作者：lgswdn_SA (赞：0)

很显然有一个 $O(m^2)$ 的暴力，就是暴力删边然后拓扑判环。

然后我们考虑一个问题：拓扑排序失败的问题是什么。我们拓扑完一遍后，图上存留未删除的点一定是入度 $>\ge 1$ 的点。我们删除一条边相当于让一个点的入度减少 1。那么我们枚举那些入度为 $1$ 的点，然后让他们的入度减去 1，然后对于每个点，在剩下的图上拓扑一下判断是否可行即可。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define per(i,a,b) for(register int i=(a);i>=(b);i--)
using namespace std;
const int N=509;

inline int read() {
    register int x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

int n,m,d[N],td[N];
vector<int>e[N];

void topo() {
	queue<int>q;
	rep(i,1,n) if(!d[i]) q.push(i);
	while(!q.empty()) {
		int u=q.front(); q.pop();
		for(auto v:e[u]) {
			d[v]--;
			if(d[v]==0) q.push(v);
		}
	}
}

int main() {
	n=read(), m=read();
	rep(i,1,m) {
		int u=read(), v=read();
		e[u].push_back(v), d[v]++;
	}
	topo();
	rep(i,1,n) td[i]=(d[i]==0?-1:d[i]);
	bool ans=1;
	rep(i,1,n) if(td[i]>0) ans=0;
	if(ans==1) {
		puts("YES");
		return 0;
	}
	rep(i,1,n) if(td[i]==1) {
		rep(j,1,n) d[j]=td[j];
		d[i]--;
		topo();
		bool flag=1;
		rep(i,1,n) if(d[i]>0) flag=0;
		if(flag==1) {
			ans=1;
			break;
		}
	}
	if(ans==1) puts("YES");
	else puts("NO");
	return 0;
}
```

---

## 作者：wangyibo201026 (赞：0)

## 前面的话

此题目洛谷评分错误，根本没有紫题难度。

## 思路

最开始的想法：枚举删除的每一条边，做一遍拓扑排序，最后直接暴力得出答案。

但是，仔细分析时间复杂度：$O(m(n + m))$，根本过不去，所以想优化。

我们可以发现，当有 $x$ 条边是指向 $u$ 时，我们在上面的算法流程中就会把每一条边都枚举一次，枚举 $x$ 次。但仔细想想，对于每次拓扑排序的结果只跟 $in$ 数组有关，如果每次拓扑排序中的 $in$ 数组没有改变，那么排序的结果就不会改变。而这 $x$ 次对应的 $in_u$ 全部都是一样的，也就是说，这 $x$ 次操作只用做 $1$ 次！！！

也就是说，我们不必循环 $m$ 条边，我们只需要循环每个入度不为 $0$ 的点就可以了（因为都没有边指向它，干什么去拓扑）。

那么时间复杂度就降成了 $O(n(n + m))$。主要还是思考 $in$ 数组的作用。

## 代码

代码来啦：

```cpp
#include<bits/stdc++.h>
#define int long long    //本作者手残打上去的，千万别打

using namespace std;

int n, m, u[100005], v[100005], in[505], IN[505];   //IN 数组用来替换 in 数组。因为你 in 数组全都变为 0 了还搞什么呀
bool e[505][505];

bool topo(){    //简单的拓扑模板，不会的可以上网搜
  for(int i = 1; i <= n; i++){
    IN[i] = in[i];   //替换
  }
  queue<int> q;
  for(int i = 1; i <= n; i++){
    if(!IN[i]){
      q.push(i);    //首次入队
    }
  }
  int cnt = 0;
  while(!q.empty()){
    int x = q.front();
    q.pop();
    cnt++;     //这个 cnt 是用来判环的
    for(int i = 1; i <= n; i++){
      if(!e[x][i]){
        continue;
      }
      IN[i]--;
      if(!IN[i]){
        q.push(i);
      }
    }
  }
  return cnt == n;    //如果没环，那么 n 个点一定都算过了
}

void Solve(){
  cin >> n >> m;
  for(int i = 1; i <= m; i++){
    cin >> u[i] >> v[i];
    in[v[i]]++;    //统计入度
    e[u[i]][v[i]] = true;
  }
  if(topo()){
    cout << "YES\n";
    return ;
  }
  for(int i = 1; i <= n; i++){
    if(in[i]){     //要入度为 0 才删除
      in[i]--;    //删掉一个点的入度
      if(topo()){
        cout << "YES\n";
        return ;
      }
      in[i]++;    //回溯
    }
  }
  cout << "NO\n";
}

signed main(){     //这个 signed 不用管它
  Solve();
  return 0;
}
```

---

