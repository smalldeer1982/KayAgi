# Brain Network (medium)

## 题目描述

给出一个 $n$ 个点 $m$ 条边的有效的神经网络，定义：

- 大脑的之间的距离：即大脑之间的最短距离；
- 神经网络的权值：该图中大脑之间的距离的最大值。

请求出给出的神经网络的权值。

其中有效神经网络的定义：

- 任意两个大脑都是连通的；
- 删去任意一条边都会使得上述条件不成立。

## 说明/提示

$1 \le n,m \le 10^5$。

感谢 @[_Wolverine](https://www.luogu.com.cn/user/120362) 提供的翻译

## 样例 #1

### 输入

```
4 3
1 2
1 3
1 4
```

### 输出

```
2```

## 样例 #2

### 输入

```
5 4
1 2
2 3
3 4
3 5
```

### 输出

```
3```

# 题解

## 作者：Priori_Incantatem (赞：4)

看到这题，感觉很像树的直径，只不过是在图上的（燃鹅并没有图的直径这一说法）。

题目要求的是点对之间的最短距离最长，可以比较轻松地想到最小生成树：不会改变两点之间距离，而且路径还唯一。  
那么，这道题就被转化成求树的直径了

直接 bfs 或树形DP即可

```cpp
#include<cstdio> 
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int Maxn=100000+20,inf=0x3f3f3f3f;
int f[Maxn],g[Maxn];
int n,m,ans;
vector <int> e[Maxn];
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch ^ 48),ch=getchar();
	return s*w;
}
int find(int x)
{
	if(f[x]==x)return x;
	return f[x]=find(f[x]);
}
void dfs(int x,int fa) // 这里求直径用的是树形DP
{
	int m1=-1,m2=-1;
	for(int i=0;i<e[x].size();++i)
	{
		int y=e[x][i];
		if(y==fa)continue;
		dfs(y,x);
		int tmp=f[y]+1;
		f[x]=max(f[x],tmp);
		if(tmp>m1)m2=m1,m1=tmp;
		else if(tmp>m2)m2=tmp;
	}
	ans=max(max(ans,m1+m2),max(m1,m2));
}
int main()
{
//	freopen("in.txt","r",stdin);
	n=read(),m=read();
	
	for(int i=1;i<=n;++i)
	f[i]=i;
	for(int i=1;i<=m;++i)
	{
		int x=read(),y=read();
		if(find(x)==find(y))continue;
		e[x].push_back(y);
		e[y].push_back(x);
		f[find(x)]=find(y);
	}
	fill(f+1,f+1+n,0);
	
	dfs(1,0);
	printf("%d\n",ans);
	
	return 0;
}
```

---

## 作者：朦胧_XY (赞：1)

### 理解：

有效神经网络有两个性质：

1. 是个连通图；
2. 每两个点间**只有一条**通路（也就是没有环）。

由**性质二**可得每两个点之间的距离是**确定**的，直接 dfs 搜一下就好。

------------

### 思路：

要求最大距离，而这个最大距离的两端点是不确定的，直接枚举端点会超时。

先从点 $1$ 搜到每个点的距离，设到点 $1$ **距离最大**的点为点 $i$；

设点 $i$ 到点 $1$ 的距离为 $len_{1,i}$；

若图中另有点 $j$ 和点 $1$ 的距离 $len_{1,j}$ 小于 $len_{1,i}$，那么这三个点间的**最大距离**为：
$$\max_{x\in\left\{1,j\right\}}{len_{x,i}}$$

（注：这里没把 $len_{1,j}$ 放进去是因为它**已经小于** $len_{1,i}$ 了）

可以看出，这三点间的最大距离的**一端必为** $i$；

以此类推，易得**整个图的最大距离**的一端也**必为** $i$；

所以从点 $i$ 搜一遍到每个点的距离的**最大值**便为答案。

复杂度为 $O(n)$。

------------

### 代码：

```cpp
#include<iostream>
#include<cstring>
#define N 200005
using namespace std;
int n, m, u, v, sum[N], l[N], tot, ans, vis[N], st = 1;
int head[N], to[N], nxt[N];
void add(int x, int y){
	to[++tot] = y;
	nxt[tot] = head[x];
	head[x] = tot;
}
void find(int x){
	if(sum[x] == 1 && x != st) return; // 搜到头返回
	for(int i = head[x]; i; i = nxt[i]){
		if(!vis[to[i]]){ // 搜没搜过的点，防止死循环
			l[to[i]] = l[x] + 1, vis[to[i]] = 1;
			find(to[i]);
		}
	}
}
int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++){
		scanf("%d%d", &u, &v);
		sum[u]++, sum[v]++;
		add(u, v), add(v, u);
	}
	find(1); // 从 点1 搜
	for(int i = 2; i <= n; i++){
		if(l[i] > ans) ans = l[i], st = i; // 更新到 点1 最远的点为 点i
	}
	memset(vis, 0, sizeof(vis)), memset(l, 0, sizeof(l)), vis[st] = 1;
	find(st); // 再从 点i 搜
	for(int i = 1; i <= n; i++){
		ans = max(ans, l[i]); // 更新最大距离
	}
	printf("%d", ans);
	return 0;
} 
```


---

## 作者：Larry76 (赞：0)

## 题目大意：

给你一棵树，求一下直径。

## 题目分析：

emm，怎么说吧，就是树的直径的板子。

可能有人不大理解，明明是图，你为什么要说是给定一棵树。

大家可以一起验证一下，满足如下两个性质的是否是一棵树：

- 任意两个点之间是相互联通的
- 删掉任意一条边则不满足上一条性质

简要证明：

因为给定的图为无向图，所以当图是联通的时候，必定满足性质一。

对于性质二，因为没有自环和重边，所以若有一张无向图使得断**任意**一条边就会让改图不连通，则该图的边数必定有且只有 $n-1$ 条。

那么显然，一张 $n$ 个点，$n-1$ 条边且保证是联通的无向图就是一颗无根树。

然后树上的最长路显然是树的直径。

## 代码实现：

```cpp
#include <bits/stdc++.h>
#define debug(x) cerr<<#x<<": "<<x<<endl;
#define int long long
using namespace std;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

namespace Larry76{
    const int MAX_SIZE = 2.1e5;
    int head[MAX_SIZE];
    int Next[MAX_SIZE];
    int ver[MAX_SIZE];
    int tot;
    int d = -1;
    int n,m;
    void add(int u,int v){
        ver[++tot] = v;
        Next[tot] = head[u];
        head[u] = tot;
    }
    int f[MAX_SIZE];
    int vis[MAX_SIZE];
    void dp(int u){
        vis[u] = true;
        for(int i=head[u];i;i=Next[i]){
            int v = ver[i];
            if(vis[v])
                continue;
            dp(v);
            d = max(d,f[u]+f[v]+1);
            f[u] = max(f[u],f[v]+1);
        }
    }
    void main(){
        //Code Here;
        cin>>n>>m;
        for(int i=1;i<=m;i++){
            int u,v;
            cin>>u>>v;
            add(u,v);
            add(v,u);
        }
        dp(1);
        cout<<d<<endl;
    }
}

signed main(){
#ifdef LOCAL
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
    double c1 = clock();
#else
    ios::sync_with_stdio(false);
#endif
//============================================
    Larry76::main();
//============================================
#ifdef LOCAL
    double c2 = clock();
    cerr<<"Used Time: "<<c2-c1<<"ms"<<endl;
    if(c2-c1>1000)
        cerr<<"Warning!! Time Limit Exceeded!!"<<endl;
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}
```

---

## 作者：JWRuixi (赞：0)

~~为什么 Easy，Medium，hard 完全不一样啊！！~~

- 题意

求树的直径。

- 分析

通常的做法有两种：

1. 两遍 dfs，每次通过深搜求出离一个固定根最远的点，显然对任意点做一遍，在对求出来的点做一遍，两个结果一定是直径的端点。
2. 通过 dp 实现，设 $f_u$ 表示当前 $u$ 离叶子的最远距离，直接 $ans\leftarrow f_u+f_v+1,f_u\leftarrow f_v+1$ 即可。

- code

提供 dp 实现的代码。

```cpp
#include <bits/stdc++.h>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
using namespace std;

namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn(2e5 + 500);
int n, m, head[maxn], tot, f[maxn], ans;
bool vis[maxn];

struct edge {
	int v, nxt;
} e[maxn << 1];

inline void add (int u, int v) {
	e[++tot] = {v, head[u]};
	head[u] = tot;
}

void dfs (int u, int fa) {
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].v;
		if (v == fa) continue;
		dfs(v, u);
		ans = max(f[u] + f[v] + 1, ans);
		f[u] = max(f[u], f[v] + 1);
	}
}

int main () {
	n = read(), m = read();
	for (int i = 1, u, v; i < n; i++) {
		u = read(), v = read();
		add(u, v);
		add(v, u);
	}
	dfs(1, 0);
	write(ans);
}
```

---

