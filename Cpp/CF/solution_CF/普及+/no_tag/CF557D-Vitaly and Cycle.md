# Vitaly and Cycle

## 题目描述

After Vitaly was expelled from the university, he became interested in the graph theory.

Vitaly especially liked the cycles of an odd length in which each vertex occurs at most once.

Vitaly was wondering how to solve the following problem. You are given an undirected graph consisting of $ n $ vertices and $ m $ edges, not necessarily connected, without parallel edges and loops. You need to find $ t $ — the minimum number of edges that must be added to the given graph in order to form a simple cycle of an odd length, consisting of more than one vertex. Moreover, he must find $ w $ — the number of ways to add $ t $ edges in order to form a cycle of an odd length (consisting of more than one vertex). It is prohibited to add loops or parallel edges.

Two ways to add edges to the graph are considered equal if they have the same sets of added edges.

Since Vitaly does not study at the university, he asked you to help him with this task.

## 说明/提示

The simple cycle is a cycle that doesn't contain any vertex twice.

## 样例 #1

### 输入

```
4 4
1 2
1 3
4 2
4 3
```

### 输出

```
1 2
```

## 样例 #2

### 输入

```
3 3
1 2
2 3
3 1
```

### 输出

```
0 1
```

## 样例 #3

### 输入

```
3 0
```

### 输出

```
3 1
```

# 题解

## 作者：spider_oyster (赞：2)

题外话：要隐退一段时间了，再写篇题解吧。做了 30 个深蹲后思维格外清醒。

一个显然的结论：最多加 3 条边。考虑分类讨论。

>- 加 $3$ 条边：$m=0$，显然就是随便选 $3$ 个点加三条边，方案数 $C_{n}^{3}$。
>- 加 $2$ 条边：最大连通块大小 $<3$。显然有 $m$ 个大小为 $2$ 的连通块，每个连通块可以被任意一个非当前连通块的节点连两条边，方案数 $(n-2)\times m$。
>- 加 $1$ 条边：对于每个连通块，非相邻节点之间可以任意连一条，设非相邻节点分别有 $s_1,s_2$ 个，则当前连通块的贡献为 $C_{s1}^{2}+C_{s2}^{2}$。
>- 加 $0$ 条边：已存在一个奇环。

判断奇环，计数相邻节点都可以用染色 dfs 解决。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5;
int n,m,co[N];
long long ans,c1,c2;
vector<int> G[N];

bool dfs(int u,int col)
{
    if(~co[u]) return co[u]!=col;
    co[u]=col;
    col?c1++:c2++;
    bool f=0;
    for(int v:G[u]) f|=dfs(v,col^1);
    return f;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    if(m==0) return cout<<3<<' '<<1ll*n*(n-1)*(n-2)/6<<'\n',0;
    for(int i=1,u,v;i<=m;i++) cin>>u>>v,G[u].push_back(v),G[v].push_back(u);
    memset(co,-1,sizeof(co));
    bool f=0;
    for(int i=1;i<=n;i++)
        if(co[i]==-1)
        {
            c1=c2=0;
            if(dfs(i,0)) return cout<<"0 1"<<'\n',0;
            if(c1+c2>2) {f=1;ans+=c1*(c1-1)/2+c2*(c2-1)/2;}
        }
    f?cout<<1<<' '<<ans<<'\n':cout<<2<<' '<<1ll*(n-2)*m<<'\n';
}
```

---

## 作者：Stream月 (赞：1)

图论的小思维题，注意分类讨论即可  

题目有两问，先回答需要加多少边，再回答方案数  

仔细想想加边数不会超过三，随便把三个点连起来肯定会形成一个基环  **此时一定有 边数 $m = 0$**

那么继续考虑加边数($a$)为 0,1,2的情况  

1.$a = 0$

判断奇环不难想到最常用的黑白染色，如果已经**存在**奇环，那么$a= 0$,方案数唯一

2. $a = 1$

当**存在**一个连通块内点数$\geq3$时，由抽屉原理可得，必定存在同色点，这时我们连接两个同色点就会得到一个奇环，设一个连通块内白点个数为$w$,黑点个数为$b$,该连通块对答案的贡献为$C(w,2)+C(b,2)$

3. $a = 2$

当**存在**一个连通块点数$=2$,该连通块内两个点，向其他任意一个点连两条边即可形成有三条边的奇环，对答案的贡献为$n - 2$

以上结论都非常直观自己画画图可以独立解决，注意几个条件之间的关系。

喜闻乐见的代码实现（写的有点丑）：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long ll;

using namespace std;
#define $(i,a,n) for(int i = a; i <= n; ++i)

inline ll read() {
	   ll ans = 0;
	   char last = ' ',ch = getchar();
	   while(ch < '0' || ch > '9') last = ch, ch = getchar();
	   while(ch >= '0' && ch <= '9') ans = (ans << 3) + (ans << 1) + ch - '0', ch = getchar();
	   if(last == '-') ans = -ans;
	   return ans;
}

const int INF = 0x3f3f3f3f;

const int N = 1e5 + 5;
int b, w;
int head[N];
int n, m;
struct Edge{
	int next, to;
}e[N << 1];
int tot;
int col[N];
void insert(int x, int y) {
	e[++tot].next = head[x];
	head[x] = tot;
	e[tot].to = y;
}
int num = 0;
bool dfs(int u, int c) {
	if(col[u]) {
		if(col[u] != c) return false;
		return true;
	}
	col[u] = c;
	if(c == 1) ++b;
	else ++w;
	++num;
	bool flag = true;
	int v;
	for(int i = head[u]; i; i = e[i].next) {
		v = e[i].to;
		flag &= dfs(v, -c);
	}
	return flag;
}
ll ans2, ans3;
int main(){
	//freopen("testdata.in", "r", stdin);
	//freopen("ans.out", "w", stdout);
	n = read(), m = read();
	int x, y;
	if(m == 0) {
		printf("%d %I64d\n", 3, 1ll * n * (n - 1) * (n - 2)/6);
		return 0;
	}
	for(int i = 1; i <= m; ++i) {
		x = read(), y = read();
		insert(x, y), insert(y, x);
	}
	bool flag0 = true, flag1 = false;
	for(int i = 1; i <= n; ++i) {
		if(col[i] == 0) {
			num = 0;
			b = 0, w = 0;
			flag0 &= dfs(i, 1);
			if(!flag0) {
				printf("0 1\n");
				return 0;
			}
			if(num >= 3) {
				ans3 += 1ll * b * (b - 1)/2 + 1ll * w * (w - 1)/2;
				flag1 = true;
			} else if(num == 2 && !flag1) {
				ans2 += 1ll * (n - 2);
			}
		}
	}
	if(flag1) printf("1 %I64d\n", ans3);
	else printf("2 %I64d\n", ans2);
	return 0;
}

```
最后祝大家CSP 2019 rp++

---

## 作者：FL_sleake (赞：0)

### 前置

第一次独立做出来 `*2000` 的题，肯定是 cf 评分评高了。

### 题意简述

给定一个 $n$ 个点 $m$ 条边的无向图，问最少添加几条边使图中有奇环，且添加边的方案有多少种。

### 解题思路

不难发现最多加 $3$ 条边。因为保证 $n\geq 3$，所以你可以随机选 $3$ 个点然后在它们之间加边，就有奇环了。

具体地说，我们分以下几种情况：

1. $m=0$

这时候必须加 $3$ 条边，加边的方案数为 $\frac{n\times (n-1)\times (n-2)}{6}$。实质就是从 $n$ 个点中选三个点的方案数。

2. 存在奇环

此时答案为 `0 1`。主要讲一下如何判断奇环。我们给 dfs 一个参数 $len$，走到一个点时把这个点的 $num$ 值设成 $len$，下次再走到时我们判断是否走了奇数步即可（不理解的可以看看代码）。

3. 存在一个连通块包含至少三个点

这个时候我们只需要连 $1$ 条边。具体的，从连通块中找出距离为偶数且不相邻的点连边即可。注意这个时候我们连的边一定是在块内连，不可能将两个连通块连起来，因为将两个本不相连的连通块连起来不会产生环。

如何统计连边方案数？我们从连通块中任意一个点出发，对整个块黑白染色，连的这一条边要么是黑点和黑点，要么是白点和白点，直接 dfs 统计黑点白点数量然后计算即可。

4. 其余情况

这个时候我们需要连 $2$ 条边，方案数为 $m \times (n-2)$。事实上有了前面几种情况铺垫，到这里时，已经保证连通块内点数不超过 $2$ 了。也就是说每一条边都是孤立的！我们假设某条边的两个端点是 $x,y$，此时我们找到一个 $z$，从 $x,y$ 分别向 $z$ 连一条边即可。共 $m$ 条边，对于每条边我们可以找到 $n-2$ 个上述的 $z$ 点，所以方案数就出来了。

### 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,vis[200010],cnt_0=0,cnt_1=0,ans=0,num[200010],flg=0;
vector<int> G[200010];
void dfs(int x,int len){
	if(vis[x]){
		if(len-num[x]>=3&&(len-num[x])%2){
			cout<<"0 1"<<endl;
			exit(0);
		}
		return;
	}
	vis[x]=1,num[x]=len;
	if(num[x]%2) cnt_1++;
	else cnt_0++;
	for(int v:G[x]) dfs(v,len+1);
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	if(m==0) return cout<<"3 "<<n*(n-1)*(n-2)/6<<endl,0;
	for(int i=1;i<=n;i++) if(!vis[i]) dfs(i,0);
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			cnt_0=cnt_1=0;
			dfs(i,0);
			if(cnt_0>1||cnt_1>1) flg=1;
			ans=ans+cnt_0*(cnt_0-1)/2;
			ans=ans+cnt_1*(cnt_1-1)/2;
		}
	}
	if(flg) cout<<"1 "<<ans<<endl;
	else cout<<"2 "<<m*(n-2)<<endl;
	return 0;
}
```

---

