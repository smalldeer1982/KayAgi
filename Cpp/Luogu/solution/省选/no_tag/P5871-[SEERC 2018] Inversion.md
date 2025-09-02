# [SEERC 2018] Inversion

## 题目描述

定义一个长为 $n$ 的*排列*为一个序列 $p_1, p_2, \dots, p_n$，其中 $[1, n]$ 范围内的整数都恰好在这个序列中出现一次。定义排列中的一个*逆序对*为一对整数 $(i, j)$，其中 $i, j \in [1,n]$，且满足 $i<j, p_i>p_j$。

定义一个*逆序对图*为一个有 $n$ 个点的图，图中存在一条 $(i, j)$ 的边当且仅当 $(i,j)$ 是一个逆序对。

定义一个图中的*独立集*为一个图中点的集合，满足集合中的点两两之间没有边相连。定义一个图中的*支配集*为一个图中点的集合，满足不在这个集合中的点都与集合中的某个点有边相连。定义一个图中的*独立支配集*为一个图中点的集合，这个集合既是独立集又是支配集。

给定某一个长为 $n$ 的排列的逆序对图，请计算出这个图中独立支配集的数量。

数据保证答案不会超过 $10^{18}$。

## 说明/提示

第一个样例中，图对应排列 $[1,4,2,3]$，独立支配集有 $(1,3,4)$ 和 $(1,2)$。

第二个样例中，图对应排列 $[3,5,4,1,2]$，独立支配集有 $(1,2),(1,3),(4,5)$。

第三个样例中，图对应排列 $[2,4,1,5,7,6,3]$。

第四个样例中，图对应排列 $[5,2,1,4,3]$。

## 样例 #1

### 输入

```
4 2
2 3
2 4```

### 输出

```
2```

## 样例 #2

### 输入

```
5 7
2 5
1 5
3 5
2 3
4 1
4 3
4 2```

### 输出

```
3```

## 样例 #3

### 输入

```
7 7
5 6
2 3
6 7
2 7
3 1
7 5
7 4```

### 输出

```
6```

## 样例 #4

### 输入

```
5 6
1 3
4 5
1 4
2 3
1 2
1 5```

### 输出

```
5```

# 题解

## 作者：xiaolilsq (赞：4)

[题目链接](https://www.luogu.com.cn/problem/P5871)

## 题目分析

考虑什么时候选出来的点才是**独立支配集**。

首先，所有选出来的点的值肯定单调递增，如果存在一个地方值减小了，那么选出的这两个点就肯定有连边，不满足**独立集**的要求。

也就是说，我们选出来的肯定是一个单调递增子序列。

如何才能满足**支配集**这个要求？考虑何时一个点不会被支配：

![](https://cdn.luogu.com.cn/upload/image_hosting/1dcgpu7l.png)

（其中 $A,B,C$ 为下标，矩形高度表示值，绿色的线为连边）

如果 $A,C$ 都被选入了点集，那么当且仅当 $B$ 的值在红色区域时 $B$ 才不能不选，此时 $B$ 是可以加入到这个单调递增子序列的。

也就是说，我们要选出来的是一个**极大的单调递增子序列**！（认为一个单调递增子序列是极大的当且仅当无法再往里面加入数）

此时就可以 $dp$ 做了，设 $dp_i$ 表示仅考虑 $1$ 到 $i$ 时将 $i$ 作为序列终点的极大单调递增子序列的数量，那么转移（ $a_i$ 表示排列中下标为 $i$ 的数）：

$$
dp_i=\begin{cases}1 &\ \max_{j=1}^{i-1}(a_j)>a_i \\ \sum_{1\le j\le i-1 \&\& \text{不存在一个位置}k(j<k<i)\text{使得}a_j<a_k<a_i}dp_j &\ {\rm otherwise} \end{cases}
$$

直接 $\mathcal O(n^2)$ 扫就可以了。

然后 $dp_i$ 可以被累加进答案当且仅当 $a_i>\max_{j=i+1}^n(a_j)$ 。

如何根据逆序对图还原排列？根据逆序对图得出每个数 $i$ 在 $i\dots n$ 中的排名，然后从后往前扫一遍一个个插入即可，模拟 $\mathcal O(n^2)$ （~~不妨写个 $\rm Splay$ 优化复杂度？~~）。

## 参考代码

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define ch() getchar()
#define pc(x) putchar(x)
template<typename T>inline void read(T&x){
	int f;char c;
	for(f=1,c=ch();c<'0'||c>'9';c=ch())if(c=='-')f=-f;
	for(x=0;c<='9'&&c>='0';c=ch())x=x*10+(c&15);x*=f;
}
template<typename T>inline void write(T x){
	static char q[64];int cnt=0;
	if(!x)pc('0');if(x<0)pc('-'),x=-x;
	while(x)q[cnt++]=x%10+'0',x/=10;
	while(cnt--)pc(q[cnt]);
}
const int maxn=105;
int d[maxn],pos[maxn],id[maxn];
long long dp[maxn];
int main(){
	int n,m;
	read(n),read(m);
	for(int i=1;i<=m;++i){
		int u,v;
		read(u),read(v);
		if(u>v)u^=v^=u^=v;
		++d[u];
	}
	for(int i=n;i>=1;--i){
		++d[i];
		for(int j=n-i+1;j>d[i];--j)
			pos[j]=pos[j-1];
		pos[d[i]]=i;
	}
	for(int i=1;i<=n;++i)
		id[pos[i]]=i;
	for(int i=1;i<=n;++i){
		int mx=0;
		for(int j=i-1;j>=1;--j){
			if(id[j]<id[i]&&id[j]>=mx){
				mx=id[j];dp[i]+=dp[j];
			}
		}
		if(!dp[i])dp[i]=1;
	}
	int mx=0;long long ans=0;
	for(int i=n;i>=1;--i)
		if(id[i]>=mx)
			mx=id[i],ans+=dp[i];
	write(ans),pc('\n');
	return 0;
}

```

---

## 作者：Whiking (赞：2)

# [SEERC2018] Inversion 题解

因为只有逆序对才会连边，那么就可以通过连边情况把 $P$ 求出来。

怎么求呢？拓扑就行了，$u$ 连向 $v$ 代表 $p_u < p_v$。

如果图中给了 $u,v$ 这条边，那么就连 $v,u$，否则就连 $u,v$。

所以入度为 $0$ 的点就是最小的。

显然是可以跑出 $P$。

现在得到了 $P$，就可以开始分析**独立支配集**。

**独立集**很显然，单调递增的子序列就不会有边相连。

那么**支配集**呢？怎么样才能让集合外的点连进来呢？

应该是这样的：

![](https://cdn.fzoi.top/upload/user/c20150023/23081204398540.png)

红色就是单调递增的子序列，黄色就是集合外部的点，不难发现，只要外部的点比红色的最小值大，比红色的最大值小，就可以连进来（因为满足了逆序对）。

所以我们要选出与红色一样的子序列。这个简单啊，DP 在 $O(n^2)$ 的复杂度可以完成。

### Code

```cpp
signed main(){
	read(n,m);
	for(int i=1,u,v;i<=m;i++){
		read(u,v);
		key[{min(u,v),max(u,v)}]=1;
	}
	for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++){
		if(key.count({i,j}))G1[j].push_back(i),in[i]++;
		else G1[i].push_back(j),in[j]++;
	}
	int s=1;while(in[s])s++;
	queue<int>q;
	q.push(s);
	p[s]=1;
	while(!q.empty()){//拓扑
		int u=q.front();
		q.pop();
		for(auto v:G1[u]){
			p[v]=max(p[v],p[u]+1);//要取最大的
			if(--in[v]==0)q.push(v);
		}
	}
	for(int i=1;i<=n;i++){
		int M=0;
		for(int j=i-1;j>=1;j--){
			if(p[i]>p[j]&&p[j]>M){
				M=p[j];
				dp[i]+=dp[j];
				vis[j]=1;
			}
		}
		if(!dp[i])dp[i]=1;//要算上自己
	}
	int ans=0;
	for(int i=1;i<=n;i++)if(!vis[i])ans+=dp[i];
	wt(ans);
}
```

---

## 作者：Filberte (赞：0)

结论：独立支配集 $\iff$ 极大独立集。反证，若一个集合是非极大独立集，则存在一个点 $u$ 与 $S$ 中所有点都没有边相连，此时 $S$ 不满足支配集的性质。

回到此题，原序列是排列，因为对于一个递增子序列，任意两个元素不构成逆序对，所以图中的独立集对应原序列的一个递增子序列。问题转化为求原排列的极长不降子序列。

考虑动态规划。令 $f_i$ 表示以 $i$ 结尾的极长不降子序列，首先如果存在 $j > i$ 且 $a_j > a_i$，则 $f_i$ 不能贡献至答案里。枚举上一个元素 $j$，当且仅当 $\forall k\in(j,i)$ ，不满足 $a_j<a_k < a_i$，此时 $f_j \rightarrow f_i$。从 $i$ 开始自大往小枚举 $j$，记录目前能转移节点的最大值，复杂度可以做到 $O(n^2)$。

最后还需要根据题目给定的逆序对图还原出原序列，按逆序对关系建出有向图，设 $u < v$，若有边 $(u,v)$，则连接 $u \rightarrow v$，否则连 $v\rightarrow u$，有向边 $u \rightarrow v$ 的含义是 $u$ 比 $v$ 大，接着在新图上拓扑排序即可。

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, m, a[N];
int deg[N], pos[N];
vector<int> g[N];
int in[N];
bool ed[N][N];
long long f[N];
int main(){
    memset(deg, 1, sizeof(deg));
    cin >> n >> m;
    for(int i = 1;i <= m;i++){
        int u, v;
        cin >> u >> v;
        if(u > v) swap(u, v);
        ed[u][v] = 1;
    }
    for(int i = 1;i <= n;i++)
        for(int j = i + 1;j <= n;j++){
            if(ed[i][j]) g[i].push_back(j), in[j]++;
            else g[j].push_back(i), in[i]++;
        }
    queue<int> q;int clk = n;
    for(int i = 1;i <= n;i++) if(!in[i]) q.push(i);
    while(!q.empty()){
        int u = q.front();q.pop();
        a[u] = clk--; 
        for(int v : g[u]) if(--in[v] == 0) q.push(v);
    }
    for(int i = 1;i <= n;i++){
        int Mx = 0;
        for(int j = i - 1;j;j--){
            if(a[j] < a[i] && a[j] > Mx){
                f[i] += f[j];
                Mx = a[j];
            }
        }
        if(f[i] == 0) f[i] = 1; 
    }
    int Mx = 0;
    long long Sum = 0;
    for(int i = n;i >= 1;i--){
        if(a[i] > Mx) Sum += f[i];
        Mx = max(a[i], Mx);
    }
    cout << Sum << endl;
    return 0;
}
```

---

## 作者：win114514 (赞：0)

一眼发现这个图是一个弦图。

但是放在弦图上依然不会做。

再看一看，发现这个图的性质比弦图还要强。

### 思路

首先将原排列求出来。

**性质一**：

假如 $\{v_1,v_2,\cdots,v_k\}$  是一个独立集，那么在原排列中一定是一个递增序列。

> 证明：假如不是递增序列，那么其中一定会有逆序对，那么就会有连边。

**性质二：**

独立集 $\{v_1,v_2,\cdots,v_k\}$ 是一个支配集，当且仅当独立集是极大独立集。

> 证明：
>
> 1. 若集合不是极大独立集，那么一定可以加点，则这个点没有被覆盖，所以不是支配集。
> 2. 若集合是极大独立集，那么没有可以加的点，也就是所有点都没覆盖率，则是一个支配集。

所以在原排列上我们只需要求出所有极大递增序列。

dp 求解即可。

时间复杂度：$O(n^2)$。

### Code

```cpp
/*
  ! 以渺小启程，以伟大结束。
  ! Created: 2024/06/29 21:40:04
*/
#include <bits/stdc++.h>
using namespace std;

#define fro(i, x, y) for (int i = (x); i <= (y); i++)
#define pre(i, x, y) for (int i = (x); i >= (y); i--)

const int N = 110;

int n, m, p[N], v[N], vs[N];
long long ans, dp[N];
vector<int> to[N];

signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  fro(i, 1, m) {
    int x, y;
    cin >> x >> y;
    to[x].push_back(y);
    to[y].push_back(x);
  }
  fro(i, 1, n) {
    p[i] = 1;
    for (auto j : to[i]) {
      while (v[p[i]]) p[i]++;
      if (j > i) p[i]++;
    }
    while (v[p[i]]) p[i]++;
    v[p[i]] = 1;
  }
  dp[1] = 1;
  fro(i, 2, n) {
    int mi = 1e9;
    fro(j, 1, i - 1) mi = min(mi, p[j]);
    if (mi > p[i]) {
      dp[i] = 1;
    } else {
      int las = -1;
      pre(j, i - 1, 1) {
        if (p[j] < p[i]) {
          if (las == -1) {
            las = j;
            dp[i] = dp[i] + dp[j], vs[j] = 1;
          } else if (p[j] > p[las]) {
            las = j;
            dp[i] = dp[i] + dp[j], vs[j] = 1;
          }
        }
      }
    }
  }
  fro(i, 1, n) if (vs[i] == 0) ans += dp[i];
  cout << ans << "\n";
  return 0;
}
```

---

## 作者：SamHJD (赞：0)

# [SEERC2018] Inversion

### Description

若存在一个 $1\dots n$ 的排列 $p$ 满足对于图 $G$ 上的任意一条边 $u\to v\ (u<v)$ 都有 $p_u>p_v$，则称 $G$ 为一个逆序对图。

给出一个逆序对图，求该图中独立支配集的数量。

### Solution

若图中 $u<v$ 且存在边 $u\to v$，那么排列 $p$ 中 $p_u>p_v$，反之 $p_u<p_v$。根据此关系建图拓扑排序，可以还原出 $p$。

观察独立集和支配集在逆序对图下的特点。

若集合 $U=\{p_{x_{1\dots k}}\}$ 满足 $p_{x_1}<p_{x_2}<\dots<p_{x_k}$，则 $U$ 为该图的一个独立集，因为 $p_{x_{1\dots k}}$ 中无逆序对，在逆序对图上互相无边相连。

进一步的，若对于 $i\not\in U$，$p_i$ 不能够插入 $U$ 构成新的不降子序列，那么 $U$ 为一个独立支配集。

于是问题转化为求 $p$ 中极大上升子序列的数量，可用动态规划计算。设 $f_i$ 为考虑 $1\dots i$，以 $i$ 结尾的极大上升子序列，倒序枚举 $1\le j<i$ 做为 $i$ 的上一个位置，若 $p_j$ 为 $[j,i)$ 中的最大值即可转移。

最终若 $p_i$ 为 $[i,n]$ 中的最大值便可将 $f_i$ 计入答案。

### Code

```cpp
#include "bits/stdc++.h"
#define int long long
#define rep(i,s,t) for(int i=s;i<=t;++i)
#define per(i,t,s) for(int i=t;i>=s;--i)
using namespace std;
template<typename T>
inline void read(T &x) {
	x=0;int f=1;char c=getchar();
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=x*10+c-'0';
	x*=f;
}
const int N=114;
int n,m,p[N],ecnt,head[N],in[N],k,f[N],vis[N],ans;
struct node{
	int v,next;
}e[N*N*2];
void add(int u,int v){
	e[++ecnt]={v,head[u]};
	head[u]=ecnt;
}
map<pair<int,int>,int> mp;
void topu(){
	queue<int> q;
	rep(i,1,n) if(in[i]==0) q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();
		p[u]=++k;
		for(int i=head[u];i;i=e[i].next){
			in[e[i].v]--;
			if(in[e[i].v]==0) q.push(e[i].v);
		}
	}
}
signed main(){
	read(n);read(m);
	rep(i,1,m){
		int u,v;read(u);read(v);
		if(u>v) swap(u,v);
		mp[{u,v}]=1;
	}
	rep(i,1,n) rep(j,i+1,n){
		if(!mp[{i,j}]) add(i,j),in[j]++;
		else add(j,i),in[i]++;
	}
	topu();
	rep(i,1,n){
		int mx=0;
		per(j,i-1,1){
			if(p[i]>p[j]&&p[j]>mx){
				mx=p[j];
				f[i]+=f[j];
				vis[j]=1;
			}
		}
		if(!f[i]) f[i]=1;
	}
	rep(i,1,n) if(!vis[i]) ans+=f[i];
	printf("%lld",ans);
	return 0;
}
```

---

