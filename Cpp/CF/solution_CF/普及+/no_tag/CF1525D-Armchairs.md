# Armchairs

## 题目描述

There are $ n $ armchairs, numbered from $ 1 $ to $ n $ from left to right. Some armchairs are occupied by people (at most one person per armchair), others are not. The number of occupied armchairs is not greater than $ \frac{n}{2} $ .

For some reason, you would like to tell people to move from their armchairs to some other ones. If the $ i $ -th armchair is occupied by someone and the $ j $ -th armchair is not, you can tell the person sitting in the $ i $ -th armchair to move to the $ j $ -th armchair. The time it takes a person to move from the $ i $ -th armchair to the $ j $ -th one is $ |i - j| $ minutes. You may perform this operation any number of times, but these operations must be done sequentially, i. e. you cannot tell a person to move until the person you asked to move in the last operation has finished moving to their destination armchair.

You want to achieve the following situation: every seat that was initially occupied must be free. What is the minimum time you need to do it?

## 说明/提示

In the first test, you can perform the following sequence:

1. ask a person to move from armchair $ 1 $ to armchair $ 2 $ , it takes $ 1 $ minute;
2. ask a person to move from armchair $ 7 $ to armchair $ 6 $ , it takes $ 1 $ minute;
3. ask a person to move from armchair $ 4 $ to armchair $ 5 $ , it takes $ 1 $ minute.

In the second test, you can perform the following sequence:

1. ask a person to move from armchair $ 1 $ to armchair $ 4 $ , it takes $ 3 $ minutes;
2. ask a person to move from armchair $ 2 $ to armchair $ 6 $ , it takes $ 4 $ minutes;
3. ask a person to move from armchair $ 4 $ to armchair $ 5 $ , it takes $ 1 $ minute;
4. ask a person to move from armchair $ 3 $ to armchair $ 4 $ , it takes $ 1 $ minute.

In the third test, no seat is occupied so your goal is achieved instantly.

## 样例 #1

### 输入

```
7
1 0 0 1 0 0 1```

### 输出

```
3```

## 样例 #2

### 输入

```
6
1 1 1 0 0 0```

### 输出

```
9```

## 样例 #3

### 输入

```
5
0 0 0 0 0```

### 输出

```
0```

# 题解

## 作者：LRL65 (赞：14)

这题赛场上我用的贪心，WA在了第8个点。赛后用**dp**过了。


------------

思路：

最开始的时候先预处理**人的位置**。

那么 $f_{i,j}$ 就表示**在前 $j$ 个椅子中，前 $i$ 个人已经坐在了原先没人的位置**。所以 $f_{0,k}=0(0\leq k\leq n)$。状态转移如下：

- 如果这个位置没有人，那么可以让这个人坐在这里，也可以不做，就是：$f_{i,j}=\min(f_{i,j-1},f_{i-1,j-1}+|b_i-j|)($其中  $b_i$ 为第 $i$ 个人的位置$)$
- 如果这个位置有人，那么就只能:$f_{i,j}=f_{i,j-1}$

最后输出 $f_{cnt,n}(cnt$ $为总人数)$ 即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[5005],f[5005][5005],b[5005];
int main() {
	cin>>n;
	memset(f,0x3f3f3f,sizeof(f));
	int cnt=0;
	for(int i=1;i<=n;i++) {
		cin>>a[i];
		if(a[i]==1)b[++cnt]=i;
	}
	for(int i=0;i<=n;i++)f[0][i]=0;
	for(int i=1;i<=cnt;i++) {
		for(int j=1;j<=n;j++) {
			if(a[j]==0)  
				f[i][j]=min(f[i][j-1],f[i-1][j-1]+abs(b[i]-j));
			else 
				f[i][j]=f[i][j-1];
		}
	}
	cout<<f[cnt][n]<<endl;
}
```



------------
最后感谢 @云浅知处 的指导！



---

## 作者：oimaster (赞：7)

裸的 dp 题。![fad](https://cdn.luogu.com.cn/upload/pic/62250.png)![fad](https://cdn.luogu.com.cn/upload/pic/62250.png)![fad](https://cdn.luogu.com.cn/upload/pic/62250.png)

首先，预处理出每个人的下标和空椅子的下标。

我们设 $f_{i,j}$ 是第 $i$ 个人坐在 $j$ 号空椅子上，由此可以得到下面递推式子：

$$
f_{i,j}=\min(f_{i,j-1},f_{i-1,j-1}+|p_i-c_j|)
$$

其中， $p_i$ 指第 $i$ 个人的位置，$c_i$ 指第 $j$ 个椅子的位置。

$f$ 数组初值应该是无限大，边界（$f_{0,j}$）应该对于所有 $1\le j\le$ 椅子个数，全是 $0$。

```cpp
#include<iostream>
#include<vector>
using namespace std;
int getc(int a,int b){
	if(a>=b)
		return a-b;
	return b-a;
}
int main(){
	int n;
	cin>>n;
	vector<int>si(1,-1);
	vector<int>pe(1,-1);
	for(int i=1;i<=n;++i){
		int x;
		cin>>x;
		if(x==1)
			pe.push_back(i);
		else
			si.push_back(i);
	}
	n=pe.size()-1;
	int m=si.size()-1;
	int dp[n+1][m+1];
	for(int i=1;i<=n;++i)
		for(int j=0;j<=m;++j)
			dp[i][j]=100000000;
	for(int j=0;j<=m;++j)
		dp[0][j]=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			dp[i][j]=min(dp[i][j-1],dp[i-1][j-1]+getc(si[j],pe[i]));
	int minv=100000000;
	for(int i=1;i<=m;++i)
		minv=min(minv,dp[n][i]);
	cout<<minv<<endl;
}
```

---

## 作者：andyli (赞：5)

除了 dp，本题还有另外一种显而易见的做法——最小费用最大流。  

设源点为 $S$ ，汇点为 $T$。  
相邻两点互相连一条流量为 $n$ ，费用为 $1$ 的边。  
从 $S$ 向所有初始为 $1$ 的点连一条流量为 $1$，费用为 $0$ 的边。  
从所有初始为 $0$ 的点向 $T$ 连一条流量为 $1$，费用为 $0$ 的边。  

然后跑费用流即可。代码如下（[缺省源](https://www.luogu.com.cn/blog/andyli/read-template)）：
```cpp
#include <cstring>
#include <queue>

struct MCMF {
    static constexpr int maxn = 5005, maxm = 30005;
    static constexpr LL INF = 0x3f3f3f3f3f3f3f3fLL;
    struct Edge {
        int next, to, cap, flow, cost;
        Edge() {}
        Edge(int next, int to, int cap, int flow, int cost) : next(next), to(to), cap(cap), flow(flow), cost(cost) {}
    } edges[maxm << 1];

    int head[maxn], cur[maxn], cnt = 1;
    LL dis[maxn];
    bool vis[maxn];
    void AddEdge(int u, int v, int c, int w) {
        edges[++cnt] = Edge(head[u], v, c, 0, w);
        head[u] = cnt;
        edges[++cnt] = Edge(head[v], u, 0, 0, -w);
        head[v] = cnt;
    }
    bool SPFA(int s, int t) {
        memset(dis, 0x3f, sizeof(dis));
        memcpy(cur, head, sizeof(head));
        std::queue<int> q;
        q.push(s);
        dis[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = false;
            for (int i = head[u]; i; i = edges[i].next) {
                int v = edges[i].to;
                if (edges[i].cap > edges[i].flow && dis[v] > dis[u] + edges[i].cost) {
                    dis[v] = dis[u] + edges[i].cost;
                    if (!vis[v])
                        q.push(v), vis[v] = true;
                }
            }
        }
        return !!(dis[t] ^ INF);
    }
    int dfs(int u, int a, int t, LL& cost) {
        if (u == t || !a)
            return a;
        vis[u] = true;
        int flow = 0, f;
        for (int& i = cur[u]; i; i = edges[i].next) {
            int v = edges[i].to;
            if (!vis[v] && edges[i].cap > edges[i].flow && dis[v] == dis[u] + edges[i].cost && (f = dfs(v, std::min(a, edges[i].cap - edges[i].flow), t, cost))) {
                edges[i].flow += f;
                edges[i ^ 1].flow -= f;
                flow += f;
                a -= f;
                cost += 1LL * f * edges[i].cost;
                if (!a)
                    break;
            }
        }
        vis[u] = false;
        return flow;
    }
    auto mcmf(int s, int t) {
        int flow = 0, f;
        LL cost = 0;
        while (SPFA(s, t))
            while ((f = dfs(s, 0x3f3f3f3f, t, cost)))
                flow += f;
        return std::pair(flow, cost);
    }
} s;
int A[MCMF::maxn];

int main() {
    dR(int, n).readArray(A + 1, A + n + 1);

    const int S = n + 1, T = n + 2;
    for (int i = 1; i < n; i++)
        s.AddEdge(i, i + 1, n, 1), s.AddEdge(i + 1, i, n, 1);
    for (int i = 1; i <= n; i++)
        if (A[i])
            s.AddEdge(S, i, 1, 0);
        else
            s.AddEdge(i, T, 1, 0);
    writeln(s.mcmf(S, T).second);
    return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：3)

电信诈骗！！！                
                
                
可以证明对于需要挪的两个位子 $a , b$ 且 $a \leq b$ 以及两个空位 $c , d$ 且 $c \leq d$,$a$ 挪到 $c$ 并且 $b$ 挪到 $d$ 会不劣。                        

所以我们只要利用这个性质进行 DP ,定义 $dp_{i,j}$ 表示的是前 i 个需要挪动的位置挪到前 j 个空位置的最小代价。                

接着我们直接暴力转移就好了，比赛的时候因为在 DP 内部取 min 输出被制裁了 4 发……                           

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int Len = 5005;
int n,m,a[Len],b[Len],c[Len],tot1,tot2,dp[Len][Len],pre[Len][Len];
inline int Iabs(int x){return x < 0 ? -x : x;}
int main()
{
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++) scanf("%d",&a[i]);
	for(int i = 1 ; i <= n ; i ++) 
	{
		if(a[i] == 1) b[++ tot1] = i; 
		else c[++ tot2] = i;
	}
	if(!tot1)
	{
		puts("0");
		return 0;
	}
	for(int i = 0 ; i <= n ; i ++)
		for(int j = 0 ; j <= n ; j ++) dp[i][j] = 1e9;
	int minn = 1e9 , ans = 1e9;
	for(int i = 1 ; i <= tot2 ; i ++)
	{
		minn = min(minn , Iabs(b[1] - c[i]));
		dp[1][i] = minn;
	}
	for(int i = 2 ; i <= tot1 ; i ++)
		for(int j = i ; j <= tot2 ; j ++)
			dp[i][j] = min(dp[i][j - 1] , dp[i - 1][j - 1] + Iabs(b[i] - c[j]));
	printf("%d\n", dp[tot1][tot2]);
	return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

第一眼没想出来 dp，唉。

费用流。

每个位置往其左右两边连流量为 $+\infty$，费用为 $1$ 的边，因为人可以随意经过每个位置，每个人移动一个距离会有 $1$ 的花费。

如果 $a_i=1$，让源点向其连流量为 $1$，费用为 $0$ 的边，表示有一个人在这里。否则向汇点连流量为 $1$，费用为 $0$ 的边，表示有一个人找到了合适的位置。

跑最小费用最大流。

# Code

```cpp
int main(){
	scanf("%d",&n);
	s=n+1;t=s+1;
	for(int i=1,x;i<=n;++i)
		scanf("%d",&x),x?adds(s,i,1,0):adds(i,t,1,0);
	for(int i=1;i<n;++i)
		adds(i,i+1,inf,1),adds(i+1,i,inf,1);
	printf("%d",Dinic().second);
	return 0;
}
```

---

## 作者：lwwwb_555 (赞：1)

## 思路
首先，这是一道十分明显的 $dp$ 题，但我的 $dp$ 设计似乎和大多数人的不太一样

先分别预处理出人和椅子的位置，然后我们设 $f_{i,j}$ 表示第 $i$ 个人要挪到第 $j$ 个位置所需花费的最小代价，那么我们就能得到下列式子
$$f_{i,j}=\min^{j-1}_{k=1}f_{i-1,k}+|b_i-c_j|$$

这里的 $b$ 数组表示人所在的位置 $c$ 数组表示椅子所在的位置

推出这个式子之后，我们发现只需要对每个 $f_i$ 取一个前缀 $min$ 就可以达到 $O(n^2)$ 的时间复杂度了

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[5005],b[5005],c[5005],ctot,btot;
long long f[5005][5005],g[5005][5005];
long long ans=1e9+10;
bool flag=1;
int read(){
	int res=0,f=1;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(isdigit(c)){
		res=(res<<3)+(res<<1)+c-'0';
		c=getchar();
	}
	return res*f;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(a[i]==1) flag=0,b[++btot]=i;
		else c[++ctot]=i;
	}
	for(int i=1;i<=btot;i++){
		for(int j=0;j<=ctot;j++) g[i][j]=1e9+10;
	}
	for(int i=1;i<=btot;i++){
		for(int j=i;j<=ctot;j++){
			f[i][j]=g[i-1][j-1]+abs(b[i]-c[j]);//dp
		}
		for(int j=i;j<=ctot;j++) g[i][j]=min(g[i][j-1],f[i][j]);//取前缀min
	}
	long long ans=1e18+10;
	for(int i=btot;i<=ctot;i++) ans=min(ans,f[btot][i]);//统计答案
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：1)

## 思路

首先假设只有两个人和两把椅子。那么我们一定让靠左的那个人坐靠左的那把椅子，无论椅子和人的位置关系如何。这个可以类比一下氧化还原反应中电子的转移规律。即不交叉原则。这一点很容易证明。

推广一下，我们可以发现，假设从左往右第 $i$ 个人坐的椅子的位置为 $q_i$，那么 $q_i$ 一定是递增的（我们规定右是正方向），这样我们设计 dp 就很容易了。

dp 状态我们设计为：$dp_{i,j}$ 表示已经安排了前 $i$ 个人的座位，当前考虑到第 $j$ 把椅子时的最小代价。那么对于一个位置，我们要么坐，要么不坐，所以转移就是 $dp_{i,j}=\min(dp_{i,j-1},dp_{i-1,j-1}+|p_i-q_j|)$（$p_i$ 表示第 $i$ 个人的位置）。为了方便写代码，我们也可以把状态中的 $j$ 定义为考虑到第 $j$ 个位置，那么如果位置 $j$ 是人而不是椅子，那么我们就从 $j-1$ 直接转移即可。

## 代码

```C++
/*
CB Ntsc
*/

#include<bits/stdc++.h>
using namespace std;
#define int long long


#define rd read()
inline int read()
{
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}


const int N=5e3+5;
const int M=5e5+5;
const int INF=1e9+5;
const int MOD=1e9+7;
bool f1;
int m,k,n,qzh;

int q;
int t,ans,p[M],mn=INF,mx;
int cnt,r;
int f[N][N];
int a[M];

bool f2;


signed main(){
	// freopen("xor.in","r",stdin);
	// freopen("xor.out","w",stdout);
	n=rd;
	for(int i=1;i<=n;i++){
		a[i]=rd;
		if(a[i])p[++cnt]=i;
	}
	memset(f,0x3f,sizeof(f));
	for(int i=0;i<=n;i++)f[0][i]=0;

	for(int i=1;i<=cnt;i++){
		for(int j=1;j<=n;j++){
			if(a[j])f[i][j]=f[i][j-1];
			else f[i][j]=min(f[i][j-1],f[i-1][j-1]+abs(p[i]-j));
		}
	}
	cout<<f[cnt][n];

	return 0;
}

/*
2
3 2 3 6
*/

```




---

## 作者：7KByte (赞：1)

费用流模板。

对于为 $1$ 的点，从源点连一条容量为 $1$ ，费用为 $0$ 的边。

对于为 $0$ 的点，向汇点连一条容量为 $1$ ，费用为 $0$ 的边。

对于每个 $i$ ，点 $i$ 向点 $i-1$ 和点 $i+1$ 分别连容量为 $n$ ，费用为 $1$ 的边。

最后跑最小费用最大流即可，时间复杂度能过。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 5005
#define M 50005
using namespace std;
int n,m,s,t,h[N],tot=1;
struct edge{int to,nxt,cap,val;}e[M<<1];
void add(int x,int y,int z,int w){
	e[++tot].nxt=h[x];h[x]=tot;e[tot].to=y;e[tot].val=w;e[tot].cap=z;
	e[++tot].nxt=h[y];h[y]=tot;e[tot].to=x;e[tot].val=-w;e[tot].cap=0;
}
queue<int>q;int v[N],d[N],pre[N],cur[N],flow,ans;
bool bfs(){
	memset(d,0x3f,sizeof(d));
	memset(v,0,sizeof(v));
	d[s]=0;q.push(s);cur[s]=0x7fffffff;cur[t]=0;
	while(!q.empty()){
		int x=q.front();q.pop();
		v[x]=0;
		for(int i=h[x];i;i=e[i].nxt)if(e[i].cap&&d[x]+e[i].val<d[e[i].to]){
			d[e[i].to]=d[x]+e[i].val;pre[e[i].to]=i;cur[e[i].to]=min(cur[x],e[i].cap);
			if(!v[e[i].to])v[e[i].to]=1,q.push(e[i].to);
		}
	}
	return cur[t]?1:0;
}
void updata(){
	flow+=cur[t];
	ans+=cur[t]*d[t];
	int x=t;
	while(x!=s){
		e[pre[x]].cap-=cur[t];
		e[pre[x]^1].cap+=cur[t];
		x=e[pre[x]^1].to;
	}
}
int main(){
	scanf("%d",&n);s=n+1;t=s+1;
	rep(i,1,n){
		int x;scanf("%d",&x);
		if(x==1)add(s,i,1,0);
		else add(i,t,1,0);
	}
	rep(i,1,n-1)add(i,i+1,n,1);
	rep(i,2,n)add(i,i-1,n,1);
	while(bfs())updata();
	printf("%d\n",ans);
	return 0;
}
```

---

