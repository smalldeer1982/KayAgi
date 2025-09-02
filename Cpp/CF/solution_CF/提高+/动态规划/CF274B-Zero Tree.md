# Zero Tree

## 题目描述

A tree is a graph with $ n $ vertices and exactly $ n-1 $ edges; this graph should meet the following condition: there exists exactly one shortest (by number of edges) path between any pair of its vertices.

A subtree of a tree $ T $ is a tree with both vertices and edges as subsets of vertices and edges of $ T $ .

You're given a tree with $ n $ vertices. Consider its vertices numbered with integers from 1 to $ n $ . Additionally an integer is written on every vertex of this tree. Initially the integer written on the $ i $ -th vertex is equal to $ v_{i} $ . In one move you can apply the following operation:

1. Select the subtree of the given tree that includes the vertex with number 1.
2. Increase (or decrease) by one all the integers which are written on the vertices of that subtree.

Calculate the minimum number of moves that is required to make all the integers written on the vertices of the given tree equal to zero.

## 样例 #1

### 输入

```
3
1 2
1 3
1 -1 1
```

### 输出

```
3
```

# 题解

## 作者：LukeLuke (赞：10)

# CF274B

这道题我们采用**树形 DP**。

~~众所周知~~，树形 DP 一般以**子树**为单位，所以，这道题的状态可以这样设计：

$f[i]$ 表示以 $i$ 为根的子树需要加上几才能全部变成 $0$。

$g[i]$ 表示以 $i$ 为根的子树需要减去几才能全部变成 $0$。

为什么要把加和减分开呢？因为这样才能统计出操作的次数。

如何转移呢？
$$
f[i] = \max_{j\in son_i} f[j]\\
g[i] = \max_{j\in son_i} g[j]\\
$$
之后， 如果 $v[i]$ 在加 $f[i]$ 减 $g[i]$ 了之后不是 $0$，就调整 $f[i],g[i]$，使得 $v[i]$ 等于 $0$。

为什么这样转移？

如下图： 

![](https://cdn.luogu.com.cn/upload/image_hosting/i9izmtyk.png)

对于这张图，要使 $1$ 号点的两颗子树都为 $0$，首先整体都用 $2$ 次操作加上 $2$，这样就满足了两颗子树都需要加 $2$。

然后再整体用 $3$ 次操作减 $3$ 满足了第二棵子树的需求。然后再将 $1$ 号点和以 $3$ 号点为根的子树都减去 $1$，就可以将 $1$ 的所有子树都变成 $0$ 了。总结一下，就是每次把没操作完的子树和 $1$ 本身都操作一次。最后，要把需要操作数最多的那几颗子树操作完。所以要取最大值。

最后，再将 $1$ 号点单独调整一下就行了。

最终的答案为 $f[1]+g[1]$。
```c++
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define int long long 

const int N = 100010;

int n, v[N], f[N], g[N];

vector<int> ve[N];

void dfs(int u, int fa) {
	for (int i : ve[u]) if (i != fa) {
		 dfs(i, u);
		 f[u] = max(f[u], f[i]);
		 g[u] = max(g[u], g[i]);
	}
	int k = v[u] + f[u] - g[u];
	if (k > 0) g[u] += k;
	else f[u] += -k;
}

signed main() {
	scanf("%lld", &n);
	for (int i = 1; i < n; i++) {
		int x, y;
		scanf("%lld%lld", &x, &y);
		ve[x].pb(y);
		ve[y].pb(x);
	}
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &v[i]);
	}
	dfs(1, 0);
	printf("%lld\n", f[1] + g[1]);
	return 0;
}
```

---

## 作者：首相大大 (赞：4)

### 思路
由于每一次子树都必须包含节点1,我们令1位根节点，则每一次修改一个点的权值必定修改其父亲的权值(根节点除外)

对于每一颗子树而言，其根节点最少被加上其子节点中权值最小的值的绝对值，最少被减去其子节点中的最大值(~~想一想，为什么~~)

我们令$up[u]$表示$u$最少被加的次数，$down[u]$表示$u$最少被减去的次数，$v$表示$u$的子节点

则有:
$$up[u] = max(up[v])$$
$$down[u] = max(down[v])$$
答案即为$up[1] + down[1]$

### 需要注意的地方
- 数组开`long long`
- 对$up[u]$和$down[u]$的初始化
- 如对于每一颗子树操作完了后子树的根节点权值不为0，还要特殊处理

### `CODE`
```
/*Do not go gentle into that good night*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
int k,head[100005];
ll w[100005],up[100005],down[100005];//up:变为0加的次数 down:变为0减的次数 
struct edge{int v,nxt;};
edge e[200005];
inline ll Max(ll x,ll y){return x > y ? x : y;}
inline void add_edge(int u,int v)
{
    e[++k].v = v;
    e[k].nxt = head[u],head[u] = k;
}
void dfs(int u,int fa)
{
    int v;
    for(int i(head[u]);i;i = e[i].nxt)
    {
        if((v = e[i].v) == fa) continue;
        dfs(v,u);
        up[u] = Max(up[u],up[v]),down[u] = Max(down[u],down[v]);
    }
    w[u] += up[u] - down[u];//处理子树的根节点
    if(w[u] > 0) down[u] += w[u];
    else up[u] -= w[u]; 
}
int main()
{
    int n,u,v;
    cin>>n;
    for(int i(1);i < n;i++) scanf("%d%d",&u,&v),add_edge(u,v),add_edge(v,u);
    for(int i(1);i <= n;i++) 
    {
        scanf("%lld",w + i);
        if(w[i] > 0) down[i] = w[i];
        else up[i] = -w[i];//操作次数为正
    }
    dfs(1,0);
    printf("%lld",up[1] + down[1]);
    return 0;
}
```
`PrimeMinister of GE All Rights Reserved`

`Feb 8th`

---

## 作者：Link_Cut_Y (赞：3)

给定一棵树，每个点有点权。每次操作可以选择一个与 $1$ 号点相连的连通块，将连通块里的点都 $ + 1$ 或 $ - 1$。求将每个点权变为 $0$ 的最小操作次数。

设 $f_u$ 表示以 $u$ 为根的子树都变成 $0$ 的最小操作次数中 $ + 1$ 的次数，$g_u$ 表示以 $u$ 为根的子树都变成 $0$ 的最小操作次数中 $ - 1$ 的次数。易得 $f_1 + g_1$ 即为答案。

考虑在 dp 过程中如何合并子树信息。如果出现下面的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/avhug4lb.png)

这里的 $ + 2$ 指的是这颗子树被加了两次。

那么显然，合并的时候，直接将整颗子树全部 $ + 2$ 就可以了。

所以 $f_u = \max \limits_{v \in son_u}^{} f_v$，$g_u = \max \limits_{v \in son_u}^{} g_v$。

最后不要忘了一点：如果 $c_u + f_u - g_u > 0$，则需要在 $u$ 点上再减去 $c_u + f_u - g_u$。同理如果 $ < 0$，则加上 $c_u + f_u - g_u$。

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#define pb push_back
#define int long long
		
using namespace std;
		
const int N = 100010;
int f[N], g[N], c[N], n;
vector<int> e[N];

void dfs(int u, int father) {
	for (int v : e[u]) {
		if (v == father) continue;
		dfs(v, u);	
		f[u] = max(f[u], f[v]);
		g[u] = max(g[u], g[v]);
	}
	if (c[u] + f[u] - g[u] < 0) f[u] -= c[u] + f[u] - g[u];
	else g[u] += c[u] + f[u] - g[u];
}
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i < n; i ++ ) {
		int a, b; scanf("%lld%lld", &a, &b);
		e[a].pb(b), e[b].pb(a);
	}
	for (int i = 1; i <= n; i ++ )
		scanf("%lld", &c[i]);
	dfs(1, 0);
	printf("%lld\n", f[1] + g[1]);
	return 0;
}
```

---

## 作者：Crab_Dave (赞：3)

## CF274B Zero Tree 题解

+ ### 题意

  给出一棵 $n$ 个点带点权的树，每次操作可以对一个联通子图中的点全部加 $1$，或者全部减 $1$，且每次操作必须包含点 $1$，问最少通过多少次操作可以让整棵树每个点的权值变为 $0$。

+ ### 思路

  首先考虑以 $1$ 为根。

  然后显然对于每个点，只需关注它的加或减的次数最大的那个儿子即可。

  于是我们令 $up[u]$ 表示 $u$ 最少被加的次数，$down[u]$ 表示 $u$ 最少被减去的次数，$v$ 表示 $u$ 的子节点。

  则 $up[u]=max(up[v]),down[u]=max(down[v])$

  答案即为 $up[1]+down[1]$

  注意初始化，注意操作完后根节点不为 $0$ 时的特判。

+ ### 部分代码

  初始化：

  ```cpp
  for(register int i=1;i<=n;i++){
          scanf("%lld",&val[i]);
          if(val[i]>0)down[i]=val[i];
          else up[i]=-val[i];
  }
  ```

  dp部分：

  ```cpp
  void dfs(int u,int fa){
      for(register int i=head[u];i;i=e[i].next){
      	int v=e[i].to; if(v==fa)continue; dfs(v,u);
  		down[u]=max(down[v],down[u]);
  		up[u]=max(up[v],up[u]);
      }val[u]+=up[u]-down[u];
      if(val[u]<=0)up[u]-=val[u];
      else down[u]+=val[u];
  }
  ```

  

---

## 作者：ZettaByte (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF274B)

### 题意

给你一棵根为 $1$，节点数为 $n$ 的树，每个点有点权 $a_i$。每次可以把一棵子树上的所有点权加 $1$ 或减 $1$，问最少要多少次操作才能使得所有点权变成零。

### 解法

这题使用树形 dp，共两个 dp 数组：

- $dp1_i$ 表示这棵子树需要加几次才能将它的点权全部变成 $0$；

- $dp2_i$ 表示这棵子树需要减几次才能将它的点权全部变成 $0$；

转移方程：$dp1_u=\max\{dp1_v\}$，$dp2_u=\max\{dp2_v\}$。

最后，若发现 $a_u+dp1_u-dp2_u>0$，则 $dp2_u$ 应加上 $a_u+dp1_u-dp2_u$；否则 $dp1_u$ 减去 $a_u+dp1_u-dp2_u$。

#### AC CODE：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n, a[N]; ll dp1[N], dp2[N]; vector<int> g[N];
void dfs(int u, int fa)
{
	for (int v : g[u])
		if (v != fa) dfs(v, u), dp1[u] = max(dp1[u], dp1[v]), dp2[u] = max(dp2[u], dp2[v]);
	if (a[u] + dp1[u] - dp2[u] > 0) dp2[u] += a[u] + dp1[u] - dp2[u];
	else dp1[u] -= a[u] + dp1[u] - dp2[u];
}

int main()
{
	scanf("%d", &n);
	for (int i = 1, x, y; i < n; i++) scanf("%d%d", &x, &y), g[x].push_back(y), g[y].push_back(x);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	dfs(1, -1), printf("%lld\n", dp1[1] + dp2[1]);
	return 0;
}
```

---

## 作者：2021sunzishan (赞：1)

简单的树形 dp。

## 题目大意：
给定一棵树，每次可以选择一个子树，该子树上的每个点的权值 $+1$ 或 $-1$。问最少多少次该树变为全 $0$。

## 思路：
~~话说我刚看题看到子树想到了树链剖分……~~

定义两个状态数组，$f1[u]$ 代表以 $u$ 为根的子树要加几次，$f2[u]$ 代表以 $u$ 为根的子树要减几次。

然后我们在 dfs 遍历的过程中，$f1[u]$ 取它所有子节点 $f1[v]$ 的最大值，$f2[u]$ 也是一样的。

最后算一下操作后 $u$ 点的值，如果需要就再次单独修改这个点。

最后的答案为 $f1[1]+f2[1]$。

以上就是本题的思路了，非常简单对不对？

如果还是不懂，就看看代码吧！

**切勿抄袭！！！**

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long//这题要开long long，偷个懒
struct node{//链式前向星
	int next,to;
}edge[1000005];
int head[1000005],cnt=0;
void addedge(int u,int v){
	edge[++cnt].next=head[u];
	head[u]=cnt;
	edge[cnt].to=v;
}
int f1[1000005],f2[1000005];
int n,a[1000005];
inline int read(){//快读
	int a=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if  (c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		a=a*10+(c-'0');
		c=getchar();
	}
	return f*a;
}
void dfs(int u,int fa){
	for(int i=head[u];i;i=edge[i].next){
		int v=edge[i].to;
		if(v==fa)continue;/
		dfs(v,u);
		f1[u]=max(f1[u],f1[v]);//取最大值
		f2[u]=max(f2[u],f2[v]);
	}
	int k=a[u]+f1[u]-f2[u];
	if(k>0)//做修改
		f2[u]+=k;
	else
		f1[u]-=k;
}
main(){
//	freopen("zerotree.in","r",stdin);
//	freopen("zerotree.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		addedge(u,v);//树，双向加边
		addedge(v,u);
	}
	for(int i=1;i<=n;i++)a[i]=read();
	dfs(1,0);
	printf("%lld\n",f1[1]+f2[1]);//最后输出答案
	return 0;
}

```

完结~


---

## 作者：BorisDimitri (赞：1)

### 【题意】
选择一个包含根的子树，一次操作中可以将其所有点同时 $+1$ 或 $-1$。
求将所有点值变为 $0$ 需要的最少次数。

### 【思路】
定义 $f[u,0/1]$ 将 $u$ 的子树减/加成 $0$ 需要的最少次数。
由于可以随便选哪几个子树，所以至少加上子树中的最小的负数值，减去子树中最小的正数值。

**初始化**：如果 $a_i < 0$，则 $f[i,1] = |a_i|$，否则 $f[u,0] = a_i$。

**转移方程**：
$$f[u,0] = \max_{v \in son(u)} f[v,0]$$
$$f[u,1] = \max_{v \in son(u)} f[v,1]$$


```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL N = 1e5 + 10;

LL n; 
struct Edge
{
	LL v,nxt;
} e[N*2];
LL head[N], idx;
void add(LL u,LL v)
{
	e[++idx].v = v,  e[idx].nxt = head[u], head[u] = idx;
}

LL a[N];
LL f[N], g[N];
void dfs(LL u,LL fa)
{
	for(LL i=head[u];i;i=e[i].nxt)
	{
		LL v = e[i].v;
		if(v == fa) continue;
		
		dfs(v,u);
		f[u] = max(f[u],f[v]);
		g[u] = max(g[u],g[v]);
	}
	a[u] += f[u] - g[u];
	if(a[u] > 0) g[u] += a[u];
	else f[u] -= a[u];
}

int main()
{
	scanf("%lld",&n);
	for(LL i=1;i<n;i++) 
	{
		LL u,v;
		scanf("%lld%lld",&u,&v);
		add(u,v),add(v,u);
	}
	for(LL i=1;i<=n;i++) scanf("%lld",&a[i]);
	
	dfs(1,0);
	
	cout<<f[1] + g[1];
	
	return 0;
}
```

---

## 作者：lilong (赞：0)

由于修改深度较大的节点会影响深度较小的节点，故应当先修改深度较大的节点才能避免后续操作被浪费。设 $f_u,g_u$ 分别表示以 $u$ 为根的子树需要 $-1,+1$ 的最少次数，由于每次操作每个子节点 $v$ 可选可不选，故有显然的转移 $f_u=\max f_v,g_u=\max g_v$。最后考察子节点的操作对当前节点 $u$ 的影响，并使用对应次数的操作即可。时间复杂度 $O(n)$。


```cpp
//
#include<iostream>
#include<cstdio>
#include<vector>
#define int long long
#define N 500010
using namespace std;
int n,f[N],g[N],a[N];
vector<int>G[N];
void dfs(int u,int ff){
    for(auto v:G[u]){
        if(v==ff)continue;
        dfs(v,u);
        f[u]=max(f[u],f[v]),g[u]=max(g[u],g[v]);
    }
    a[u]=a[u]-f[u]+g[u];
    if(a[u]<0)g[u]+=(-a[u]);
    else f[u]+=a[u];
    return;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n;
    int u,v;
    for(int i=1;i<n;i++){
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for(int i=1;i<=n;i++)
        cin>>a[i];
    dfs(1,0);
    cout<<f[1]+g[1];
    return 0;
}
```

---

## 作者：sSkYy (赞：0)

# [CF274B Zero Tree ](https://www.luogu.com.cn/problem/CF274B)

## 题意

给定一颗带点权的树，点权有正有负，每次操作你可以对任意包含节点 $1$ 的联通块上的点全部 $+1$ 或者 $-1$。

求将点权全部变为 $0$ 的最小操作次数。

## 题解

树形 DP。

以 $1$ 为根节点,设 $f_u$ 表示以 $u$ 为根的子树都变成 $0$ 的最小操作次数中 $ + 1$ 的次数，$g_u$ 表示以 $u$ 为根的子树都变成 $0$ 的最小操作次数中 $ - 1$ 的次数。

各个子树的操作可以合并一起来，所以取子树的最大操作数，然后由于根节点可以自己调整，不会有操作冗余，所以可以先保证子树最优，全部归零，再调整根节点。

转移方程：

$f_u = \max \limits_{v \in son_u}^{} f_v$，$g_u = \max \limits_{v \in son_u}^{} g_v$

令 $d=w_u+f_u-g_u$，如果 $d>0$，则需要在 $u$ 点上单独额外减去 $d$：$g_u\leftarrow g_u+|d|$。如果 $d<0$，则加上 $d$：$f_u\leftarrow f_u+|d|$，**注意这里 $d$ 的符号**。

最终答案为 $f_1+g_1$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,f[N],g[N],w[N];
vector<int> e[N];
void dfs(int u,int fa){
    for(int v:e[u]){
        if(v==fa) continue;
        dfs(v,u);
        f[u]=max(f[u],f[v]),g[u]=max(g[u],g[v]);
    }
    int d=w[u]+f[u]-g[u];
    (d>0)?g[u]+=d:f[u]+=(-d);
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v; cin>>u>>v;
        e[u].emplace_back(v),e[v].emplace_back(u);
    }
    for(int i=1;i<=n;i++) cin>>w[i];
    dfs(1,1);
    cout<<f[1]+g[1];
    return 0;
}
```

---

## 作者：liaiyang (赞：0)

我们设 $dp_{x,0/1}$ 表示以 $x$ 为根的子树加上/减去几才能全部变成 $0$。

可得转移方程为
$$dp_{x,0}=\max_{i\in son_x}dp_{i,0}$$
$$dp_{x,1}=\max_{i\in son_x}dp_{i,1}$$

注意计算上每个 $a_i$ 的贡献即可。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define min(a,b) (a<b?a:b) 
#define P pair<int,int>
#define x first
#define y second
#define modd(x) (((x)%mod+mod)%mod) 
#define rd read()
#define lowbit(x) ((x)&(-x))
mt19937 rnd(time(0));
inline int read(int u=0, char c=getchar(), bool f=false){
    for (;!isdigit(c);c=getchar()) f|=c=='-';
    for (;isdigit(c);c=getchar()) u=(u<<1)+(u<<3)+c-'0';
    return f?-u:u;
}
inline void wt(int x){
    if(x<0) x=-x,putchar('-');
    if(x>9) wt(x/10);
    putchar(x%10+48);
}
inline void wt(int x,char k){wt(x),putchar(k);}
const int inf=~0U>>1,linf=~0ULL>>1; 
const int mod=998244353;
const int N=1e5+10;
int n,a[N],f[N][2];
vector<int>e[N];
void dfs(int x,int fa){
    for(int i:e[x]){
        if(i==fa) continue; 
        dfs(i,x);
        f[x][0]=max(f[x][0],f[i][0]);
        f[x][1]=max(f[x][1],f[i][1]);
    }
    a[x]+=f[x][0]-f[x][1];
    if(a[x]<0) f[x][0]-=a[x];
    else f[x][1]+=a[x];
}
main(){
    n=rd;
    for(int i=1;i<n;i++){
        int x=rd,y=rd;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    for(int i=1;i<=n;i++){
        a[i]=rd;
        if(a[i]<0) f[i][0]=-a[i];
        else f[i][1]=a[i];
    }
    dfs(1,0);
    cout<<f[1][0]+f[1][1]<<endl;
    return 0;
}
```

---

## 作者：_xxxxx_ (赞：0)

### 题意

给出一颗树，每个点有点权，有两种操作：

1. 选择一条树上的简单路径，将它们的边权都加一。
2. 选择一条树上的简单路径，将它们的边权都减一。

问要将所有点点权置为 $0$ 的最少操作次数。

### 分析

树上找最小步数，考虑树形 dp。

我们把问题简化一下，假如只有 $1$ 操作（只有加），那我们该如何解决？

可以想到，定义 $dp[u]$ 为把以 $u$ 为根的子树全部置为 $0$ 的最小步数。

每次在儿子中找一个值最大的转移即可，即：

$$dp[u]=max(dp[son])$$

其中 $son$ 是 $u$ 的其中一个儿子。

因为每次只能增加 $1$，因此每次递归时，$dp[u]$ 需要加上点权与 $dp[u]$ 的差，一次一次补上去。

假如只有 $2$ 操作，也同理。这样我们就可以处理出只有一种操作的形式。

现在就出现了一个问题：如何把两种操作合并在一起。

我们每次对子树进行操作时，定义 $k$ 为当前点权减去操作 $2$ 的个数加上操作 $1$ 的个数。那么当前的 $k$ 就是把目前这个点归零所还需要的操作次数，如果 $k>0$，则需要减；如果 $k<0$，则需要加。

同时在递归过程中，也进行对子树取最大值。

现在我们就完成了转移。最后考虑答案存在哪里，现在到了根节点，子树需要加减的次数都求出来了。因此答案即为操作 $1$ 的个数加上操作 $2$ 的个数。

### 代码

```cpp
#include <iostream>
#define int long long
using namespace std;
const int N = 1e6 + 10;
const int INF = 0x3f3f3f3f;
int n;
int head[N], ne[N], to[N], id;
int a[N];
void add(int x, int y)
{
	to[++id] = y;
	ne[id] = head[x];
	head[x] = id;
}
int dp[N][2];
//dp[u][0]:以u为根的子树需要多少次操作1
//dp[u][1]:以u为根的子树需要多少次操作2
void dfs(int u, int fa)
{
	for(int i = head[u]; i; i = ne[i])
	{
		int v = to[i];
		if(v == fa) continue;
		dfs(v, u);
		//分开转移，同只有一种操作 
		dp[u][0] = max(dp[u][0], dp[v][0]);
		dp[u][1] = max(dp[u][1], dp[v][1]);
	}
	//点权-操作2+操作1 
	int k = a[u] - dp[u][1] + dp[u][0];
	if(k > 0) dp[u][1] += k; 
	else dp[u][0] -= k;
}
signed main()
{
	cin >> n;
	for(int i = 1; i < n; i++)
	{
		int x, y;
		cin >> x >> y;
		add(x, y);
		add(y, x);
	}
	for(int i = 1; i <= n; i++) cin >> a[i];
	dfs(1, 0);
	cout << dp[1][0] + dp[1][1] << endl;//操作1+操作2 
	return 0;
}
```

---

## 作者：ademik (赞：0)

#### 分析：

题意简化为：每次我们可以将任意一个包含节点 $1$ 的联通块中的所有节点的权值加 $1$ 或减 $1$，求最少的操作次数使得所有节点的权值为 $0$。

对于每个节点来讲，深度越大的节点能修改它的方案越少，故而贪心的从下向上依次修改节点权值为 $0$。

注意到对于一个子树来讲，要修改它的子节点就必须修改它的根节点，故而考虑树形 DP 求解。

由于我们可以任意选择联通块，那么我们只需在意子树中需要修改幅度最大的值，因为我们可以随意改动修改的形态使得满足在我们需要的地方加减。

需要将加减分开统计。

#### Code：

```cpp
# include <bits/stdc++.h>
# define TIME 1e3 * clock() / CLOCKS_PER_SEC
using namespace std;
typedef long long i64;
const int N = 1e5 + 50;
int n, head[N], edge_sum;
struct edge {
	int nst, to;
} e[N << 1];
i64 g[N], f[N], a[N]; // f 统计 + , g 统计 -
void dfs(int u, int fa)
{
	for(int i = head[u]; i; i = e[i].nst) {
		int v = e[i].to;
		if(v == fa) continue;
		dfs(v, u);
		f[u] = max(f[u], f[v]);
		g[u] = max(g[u], g[v]);
	}
    // 计算修改当前节点所需的步数。 
	int now = a[u] + f[u] - g[u];
	if(now > 0) g[u] += now;
	else f[u] += -now; 
	return;
}
int main()
{
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie();
	cin >>n;
	for(int i = 1, u, v; i < n; i ++) {
		cin >>u >>v;
		e[++ edge_sum] = (edge){head[u], v}; head[u] = edge_sum;
		e[++ edge_sum] = (edge){head[v], u}; head[v] = edge_sum; 
	}
	for(int i = 1; i <= n; i ++) cin >>a[i];
	dfs(1, 0);
	cout <<f[1] + g[1] <<endl;
	return 0;
}
```

---

