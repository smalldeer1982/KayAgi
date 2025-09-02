# [ABC401F] Add One Edge 3

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc401/tasks/abc401_f

给定两棵树：
- 树 1 包含 $N_1$ 个顶点，编号为 $1$ 到 $N_1$
- 树 2 包含 $N_2$ 个顶点，编号为 $1$ 到 $N_2$

树 1 的第 $i$ 条边双向连接顶点 $u_{1,i}$ 和 $v_{1,i}$，树 2 的第 $i$ 条边双向连接顶点 $u_{2,i}$ 和 $v_{2,i}$。

如果在树 1 的顶点 $i$ 和树 2 的顶点 $j$ 之间添加一条双向边，将得到一棵新的树。定义这棵新树的直径为 $f(i,j)$。

请计算 $\displaystyle\sum_{i=1}^{N_1}\sum_{j=1}^{N_2} f(i,j)$ 的值。

其中：
- 两顶点之间的距离定义为它们之间最短路径的边数
- 树的直径定义为所有顶点对之间距离的最大值

## 说明/提示

### 约束条件

- $1 \leq N_1, N_2 \leq 2 \times 10^5$
- $1 \leq u_{1,i}, v_{1,i} \leq N_1$
- $1 \leq u_{2,i}, v_{2,i} \leq N_2$
- 输入的两张图都是树
- 输入的所有数值均为整数

### 样例解释 1

例如，当连接树 1 的顶点 2 和树 2 的顶点 3 时，得到的新树直径为 5，因此 $f(2,3)=5$。所有 $f(i,j)$ 的总和为 39。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
1 3
1 2
3
1 2
3 1```

### 输出

```
39```

## 样例 #2

### 输入

```
7
5 6
1 3
5 7
4 5
1 6
1 2
5
5 3
2 4
2 3
5 1```

### 输出

```
267```

# 题解

## 作者：Awsdkl (赞：9)

首先找到第一棵树的直径 $d_1$ 和第二棵树的直径 $d_2$。  
不难发现，连接第一棵树的 $i$ 结点和第二棵树的 $j$ 结点后，$f(i, j)$ 就等于 $d_1$ 和 $d_2$ 和一条经过了边 $(i,j)$ 的路径的长度。这条路径一定可以被分成三部分：  
1. $i$ 到第一棵树中离 $i$ 最远一点的路径。
2. $j$ 到第二棵树中离 $j$ 最远一点的路径。
3. 边 $(i, j)$。  

则将这三部分的长度加起来就得到了 $f(i, j)$。  

我们记 $i$ 到第一棵树中离 $i$ 最远一点的路径长度为 $a_i$，记 $j$ 到第二棵树中离 $j$ 最远一点的路径长度为 $b_j$，则可写出 $f(i, j) = \max(\max(d_1, d_2), a_i + b_j + 1)$。  

计算直径的长度非常简单，先随便以一个点为起点，做一遍 bfs，找到离这个起点最远的点，这个点一定是直径的一个端点。然后再以这个端点为起点，做一遍 bfs，离这个端点最远的点一定是直径的另一个端点。  

然后我们考虑如何计算出 $a$ 和 $b$。在计算直径时，我们可以发现，端点中的一个一定是离这个点的最远的一个点，我们可以在 dfs 过程中记录这个值。注意两个端点都要当一次起点。  

然后我们考虑计算所有的 $f(i, j)$ 的值。发现如果 $a_i + b_j + 1 < \max(d_1, d_2)$，则 $f(i, j) = \max(d_1, d_2)$。  

可以将 $a$ 按从小到大排序，将 $b$ 从大到小排序。从 $1$ 到 $n_2$ 枚举 $j$，然后用一个变量记录第一个 $i$ 使得 $a_i + b_j + 1 \ge \max(d_1, d_2)$ 的值，则此时对于所有 $k$，$(1 \le k < i)$，有 $a_k + b_j + 1 < \max(d_1, d_2)$，则 $f(i, j) = \max(d_1, d_2)$。而所有 $k$，$(i \le k \le n_1)$，有 $a_k + b_j + 1 \ge \max(d_1, d_2)$，则 $f(i, j) = a_k + b_j + 1$。那么 $b_j$ 对于所有 $a$ 的贡献就是 $(i-1) \times \max(d_1, d_2) + (n_1 - i + 1) \times (b_i) + i + \displaystyle\sum_{k=i}^{n_1} a_k$。  

显然式子的最后一项可以用后缀和优化掉。并且 $i$ 对于 $b_j$ 的减小是递增的，则可以用一个类似于滑动窗口的东西求出来。计算的时间复杂度是 $O(n)$ 的。  
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 2e5+5;

int n1, n2;
int d1, d2, dmax;
int dis1[MAXN], dis2[MAXN];
int d11, d12, d21, d22;
int a[MAXN], b[MAXN];
vector<int> e1[MAXN], e2[MAXN];
ll ans;
ll sa[MAXN];
//e:当前 dfs 的树。
//d:起点到 u 的距离。
//maxd:上文中的 a 或者 b。
//c:求出的端点。
void dfs(int u, int fa, vector<int> *e, int *d, int *maxd, int *c)
{
	d[u] = d[fa]+1;
	maxd[u] = max(maxd[u], d[u]);
	if(d[u] > d[*c]) *c = u;
	for(auto v : e[u])
	{
		if(v == fa) continue;
		dfs(v, u, e, d, maxd, c);
	}
}

int main()
{
	scanf("%d", &n1);
	for(int i = 1;i < n1;i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e1[u].push_back(v);
		e1[v].push_back(u);
	}
	dis1[0] = -1;
	dfs(1, 0, e1, dis1, a, &d11);
	dfs(d11, 0, e1, dis1, a, &d12);
	d1 = dis1[d12];
	dfs(d12, 0, e1, dis1, a, &d11);//记住第二个端点也要 dfs 一便。
	
	scanf("%d", &n2);
	for(int i = 1;i < n2;i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e2[u].push_back(v);
		e2[v].push_back(u);
	}
	dis2[0] = -1;
	dfs(1, 0, e2, dis2, b, &d21);
	dfs(d21, 0, e2, dis2, b, &d22);
	d2 = dis2[d22];
	dfs(d22, 0, e2, dis2, b, &d21);

	dmax = max(d1, d2);

	sort(a + 1, a + n1 + 1); a[n1+1] = 0x3f3f3f3f; a[0] = INT_MIN;//a[n1+1] 赋值是为了防止下面 cur 不断的加。
	sort(b + 1, b + n2 + 1, greater<int>() );

	for(int i = n1;i >= 1;i--) sa[i] = sa[i+1] + a[i];
    //求出 a 的后缀和 sa.
	for(int i = 1, cur = 0;i <= n2;i++)
	{
		while(a[cur] + b[i] + 1 <= dmax) cur++;
        //类似于滑动窗口的东西
		ans += (ll)(cur - 1LL) * (ll)dmax + (ll)(n1 - cur + 1LL) * (ll)(b[i] + 1LL) + sa[cur];
	}
	printf("%lld\n", ans);

	return 0;
}
```

---

## 作者：chenxi2009 (赞：3)

## 思路
贪心地，考虑 $f(i,j)$ 有几种可能的取法：
- 全部在树 $T_1$ 的部分中，$f(i,j)=T_1$ 的直径；
- 全部在树 $T_2$ 的部分中，$f(i,j)=T_2$ 的直径；
- 横跨两棵树，路径为：$T_1$ 中离 $i$ 最远的点 $\rightarrow i\rightarrow j\rightarrow T_2$ 中离 $j$ 最远的点。

$f(i,j)$ 取这三种情况的最大值。\
假设我们已经知道了对于两棵树中的每个点，离它最远的点有多远（用 $\text{md}_{1/2,i}$ 表示），两棵树直径的较大值为 $\text{d}$，则题意即为求：
$$
\sum_{i=1}^{n_1}\sum_{j=1}^{n_2}\max(\text{d},\text{md}_{1,i}+\text{md}_{2,j}+1)
$$
这好办，我们给 $\text{md}_2$ 排个序，对于每个 $i$，二分最小的 $x$ 使得 $\text{md}_{1,i}+\text{md}_{2,x}+1\ge \text{d}$，$x$ 左边的每个 $j$ 对答案的贡献是 $\text{d}$，右边的贡献是 $\text{md}_{1,i}+\text{md}_{2,j}+1$，排完序求个后缀和就可以 $O(1)$ 计算出这些贡献。
### 伪代码
```py
sort(md[2])
s[n[2]] <- md[2][n[2]]
for i from (n[2] - 1) to 1:
    s[i] <- s[i + 1] + md[2][i]
forall i in [1,n[1]]:
    x <- lowerbound(md[2],md[1][i] + md[2][x] + 1 >= d)
    answer += (x - 1) * d + (n[2] - x + 1) * (md[1][i] + 1) + s[x]
```
求直径用板子就可以，唯一剩下来的问题就是如何求 $\text{md}$。

思维方法：离一个点最远的点是任意直径的一个端点。证明方法类同证明“所有直径交于中点”，略。

代码方法：注意到这是一个经典的换根 DP，先钦定一个根 $1$，求出 $f_i$ 表示 $i$ 的子树中离 $i$ 最远的点有多远，然后再跑一遍搜索，每个点除了自己子树中最远的点外还要考虑**不在自己子树中的离父亲最远的点**离自己的距离。
### 伪代码
```py
void dfs(int u,int fa,int df):
    md[u] <- max(f[u],df) /*子树中的点和子树外的点*/
    int mx = 0,cmx = 0,mxw = 0 /*由于要保证遍历儿子时传下去的“离父亲最远的点”不在儿子子树内，需要记录最大值和次大值*/
    forall v in son_of[u]:
        if(f[v] > mx): /*更新最大值与次大值*/
            mx <- f[v],mxw <- v
        elif(f[v] > cmx) cmx <- f[v]
    forall v in son_of[u]:
        if(v == mxw):
            dfs(v,u,max(df,cmx) + 1) /*最大值所在子树，传入次大值*/
        else:
            dfs(v,u,max(df,mx) + 1)


dfs(1,1,0)
```

精细实现时间复杂度 $O(\min N\log\max N)$，瓶颈在排序和二分。
## 代码
```cpp
#include<bits/stdc++.h> 
using namespace std;
int md[2][300000],f[300000],u,v,mxd,n[2];
long long ans,s[300000];
vector<int>e[2][300000];
void sch(int w,int u,int fa){
	f[u] = 0;//f_u 为 u 子树中离它最远的点的距离 
	for(auto v : e[w][u]){
		if(v == fa) continue;
		sch(w,v,u),f[u] = max(f[u],f[v] + 1);
	}
}
void dfs(int w,int u,int fa,int df){
	int mx = 0,mxw = 0,cmx = 0;
	md[w][u] = max(f[u],df);//df 为 u 子树外离父亲最远的点与 u 之间的距离 
	for(auto v : e[w][u]){
		if(v == fa) continue;
		if(f[v] + 1 > mx){
			cmx = mx;mx = f[v] + 1,mxw = v;
		}
		else if(f[v] + 1 > cmx) cmx = f[v] + 1;
	}
	for(auto v : e[w][u]){
		if(v == fa) continue;
		if(v == mxw) dfs(w,v,u,max(df,cmx) + 1);
		else dfs(w,v,u,max(df,mx) + 1);
	}
}
int main(){
	for(int i = 0;i < 2;i ++){
		read(n[i]);
		for(int j = 1;j < n[i];j ++){
			read(u,v);
			e[i][u].push_back(v),e[i][v].push_back(u);
		}
		sch(i,1,0),dfs(i,1,0,0);
		for(int j = 1;j <= n[i];j ++) mxd = max(mxd,md[i][j]);//记录两棵树直径较大值 
	}
	sort(md[1] + 1,md[1] + n[1] + 1);//排序 
	for(int i = n[1];i;i --) s[i] = s[i + 1] + md[1][i];//预处理后缀方便计算 
	for(int i = 1;i <= n[0];i ++){
		int x = lower_bound(md[1] + 1,md[1] + n[1] + 1,mxd - 1 - md[0][i]) - md[1];//二分 
		ans += 1ll * (x - 1) * mxd + s[x] + 1ll * (n[1] - x + 1) * (md[0][i] + 1);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：cheng2010 (赞：2)

## 思路

首先，我们找出两棵树的直径和端点，记为 $T1_l,T1_r,T2_l,T2_r$，与它们长度 $l1,l2$。

定义 $dist(i,j)$ 为 $i,j$ 间的距离，那么，对于一个点 $x$，从它延申出的最长链长度一定是：

$$
\max\{dist(x,T1_l),dist(x,T1_r),dist(x,T2_l),dist(x,T2_r)\}$$

现在，我们把第一棵树每个 $i$ 对应的上面那个式子的值记为 $a_i$，第二棵为 $b_i$。

好了，求完了这些，有什么用？

此时，我们可以惊讶地发现，原式变成了：

$$
\sum_{i=1}^{N1} \sum_{j=1}^{N2} \max\{a_i+b_j+1,l1,l2\}
$$

那么，只用把 $a,b$ 排序，就可以用双指针、树状数组、二分之类随便做了。

## code

[link](https://atcoder.jp/contests/abc401/submissions/64775348)

---

## 作者：wendywan (赞：1)

# 题解：AT_abc401_f [ABC401F] Add One Edge 3
[luogu link->](https://www.luogu.com.cn/problem/AT_abc401_f)

[at link->](https://atcoder.jp/contests/abc401/tasks/abc401_f)

~~感觉不水,强烈建议升蓝。~~

主要思路：树的直径，前缀和，二分（也可以用双指针，桶等）。

---

## 题目大意

有两棵树，枚举树 1 上 $i$ 和树 2 上 $j$ 两点，添加双向边连接 $i$ 与 $j$，得到新的树。

求：$\displaystyle\sum_{i=1}^{N_1}\sum_{j=1}^{N_2} f(i,j)$ 的值。

---

## 思路

考虑先将两棵树的直径分别预处理出来，存在数组 $dis1$ 和 $dis2$ 中。

求直径的同时，我们也可以求出直径的端点。

考虑枚举树 1 上的 $i$ 和树 2 上的 $j$。

此时最大的直径就会有三种情况：

1.  为树 1 的直径；

2.  为树 2 的直径；

3.  为一条跨过两棵树的距离并且经过点 $i$，点 $j$。

第一和第二种情况很好解决，只用求树 $1$ 和 $2$ 直径的最大值即可。

我们来处理第三种情况。

我们要使这条新的距离最长，就要取 $i$ 到树 1 中的最远点，$j$ 到树 2 中的最远点。

这时我们借助树的直径的定理来枚举。

> 定理：在一棵树上，从任意节点 $y$ 开始进行一次 DFS，到达的距离其最远的节点 $z$ 必为直径的一端。

（源自 [树的直径 - OI Wiki](https://oi.wiki/graph/tree-diameter/#%E8%BF%87%E7%A8%8B)）

此时我们使用 $4$ 次 dfs 处理出四个直径端点到 $i$ 或 $j$ 的距离，并取每棵树两个 $dis$ 的最大值存到 $dis7$ 和 $dis8$ 中。

以上，我们求出了所有需要的直径。

现在，我们来枚举 $i$ 与 $j$。

考虑到暴力枚举是 $O ( N ^ 2 )$ 的，我们需要加以优化。

先将 $dis7$ 和 $dis8$ 从小到大排序处理出单调性，在枚举 $i$ 的同时，我们二分一个 $j$。

此时的下标 $j$ 前面的所有数在上述的三种情况中都是第 $1$ 和 $2$ 种情况是最大的，我们可以直接乘法得出。

下表 $ j \to N2 $ 之间都是第三种情况的。

~~因为复杂度不允许~~我们需要对 $dis8$ 进行后缀和预处理便于最后的计算。

最后得出式子：

$ ans = \sum_{i = 1}^{N1} (j - 1) \times d + sum[j] + ( N2 - j + 1 ) \times ( a[i] + 1 )$

---

## Code

代码有~~非常清晰明了的结构与~~注释，可以放心使用。

```加一条边
#include<bits/stdc++.h>

using namespace std;
const int MAXN = 2e5 + 5;
int N1, N2;
long long sum[MAXN];//树2直径最大距离的后缀和
//================
int cnt1 = 0, head1[MAXN], cnt2 = 0, head2[MAXN];
struct star{
    int nxt, to, w;
}e1[MAXN * 2], e2[MAXN * 2];

void add1( int u, int v, int w ){
    e1[++ cnt1].nxt = head1[u];
    e1[cnt1].to = v;
    e1[cnt1].w = w;
    head1[u] = cnt1;
}

void add2( int u, int v, int w ){
    e2[++ cnt2].nxt = head2[u];
    e2[cnt2].to = v;
    e2[cnt2].w = w;
    head2[u] = cnt2;
}
//================star_edge↑

int d;//两棵树单独时最大的直径
int dis1[MAXN], dis2[MAXN];//求树1、2的直径所需的数组
int dfs1( int u, int fa, int w ){
    dis1[u] = dis1[fa] + w;
    int ans = u;
    for( int i = head1[u]; i; i = e1[i].nxt ){
        int to = e1[i].to;
        if( to == fa ) continue;
        int a = dfs1( to, u, e1[i].w );
        if( dis1[a] > dis1[ans] ) ans = a;
    }
    return ans;
}
int dfs2( int u, int fa, int w ){
    dis2[u] = dis2[fa] + w;
    int ans = u;
    for( int i = head2[u]; i; i = e2[i].nxt ){
        int to = e2[i].to;
        if( to == fa ) continue;
        int a = dfs2( to, u, e2[i].w );
        if( dis2[a] > dis2[ans] ) ans = a;
    }
    return ans;
}
//================原始的直径↑
int dis3[MAXN], dis4[MAXN], dis5[MAXN], dis6[MAXN];//树1、2直径两端点到每一节点的距离
int _1dis[MAXN], _2dis[MAXN];//最终最大的直径某一端点到每个节点的距离
void dfs3( int u, int fa ){//树1端点1
    for( int i = head1[u]; i; i = e1[i].nxt ){
        int to = e1[i].to;
        if( to == fa ) continue ;
        dis3[to] = dis3[u] + e1[i].w;
        dfs3( to, u );
    }
}
void dfs4( int u, int fa ){//树2端点1
    for( int i = head2[u]; i; i = e2[i].nxt ){
        int to = e2[i].to;
        if( to == fa ) continue ;
        dis4[to] = dis4[u] + e2[i].w;
        dfs4( to, u );
    }
}
void dfs5( int u, int fa ){//树1端点2
    _1dis[u] = max( dis3[u], dis5[u] );
    for( int i = head1[u]; i; i = e1[i].nxt ){
        int to = e1[i].to;
        if( to == fa ) continue ;
        dis5[to] = dis5[u] + e1[i].w;//顺便统计最大值
        dfs5( to, u );
    }
}
void dfs6( int u, int fa ){//树2端点2
    _2dis[u] = max( dis4[u], dis6[u] );
    for( int i = head2[u]; i; i = e2[i].nxt ){
        int to = e2[i].to;
        if( to == fa ) continue ;
        dis6[to] = dis6[u] + e2[i].w;
        dfs6( to, u );
    }
}
//================最终处理出d数组↑
int main(){
    cin >> N1;
    for( int i = 1; i < N1; i ++ ){
        int u, v;
        cin >> u >> v;
        add1( u, v, 1 );
        add1( v, u, 1 );
    }
    cin >> N2;
    for( int i = 1; i < N2; i ++ ){
        int u, v;
        cin >> u >> v;
        add2( u, v, 1 );
        add2( v, u, 1 );
    }
//================读入↑
    int d1_1 = dfs1( 1, 0, 0 );
    int d1_2 = dfs1( d1_1, 0, 0 );

    int d2_1 = dfs2( 1, 0, 0 );
    int d2_2 = dfs2( d2_1, 0, 0 );
    //求出直径以及2*2个端点

    dfs3( d1_1, 0 );
    dfs4( d2_1, 0 );
    dfs5( d1_2, 0 );
    dfs6( d2_2, 0 );
    //求出直径端点到每个节点的距离

    int d_1 = dis1[d1_2], d_2 = dis2[d2_2];//两棵树直径的值
    d = max( d_1, d_2 );//不添加边时的最大直径
    sort( _1dis + 1, _1dis + N1 + 1 );
    sort( _2dis + 1, _2dis + N2 + 1 );//排序（升序）

    for( int i = N2; i >= 1; i -- ){
        sum[i] = sum[i + 1] + _2dis[i];//处理后缀和
    }

    long long ans = 0;
    for( int i = 1; i <= N1; i ++ ){
        int j = lower_bound( _2dis + 1, _2dis + N2 + 1, d - _1dis[i] - 1 ) - _2dis;
        //二分 条件为当前j的坐标可以满足连接ij使得比原来的d要大
        //其实可以手写但是我懒(mei)得(tiao)写(chu)了(lai)
        ans += ( j - 1 ) * d + sum[j] + ( N2 - j + 1 ) * ( _1dis[i] + 1 );
        //统计答案 其实可以分为两部分
        //一部分是( j - 1 ) * d，即我们二分出来的j前面都是原来直径比较大，直接相乘得出答案
        //另一部分sum[j] + ( N2 - j + 1 ) * ( _1dis[i] + 1 )，即为j后面加上这条边得出的直径更大，公式使用后缀和并且稍加推到可以得出
    }
    cout << ans;
    return 0;
}
```

---

## 放在最后

代码中最后二分后的 $j$ 要 $-1$ 是因为我求出来的是需要改变的第一个的下标，自己推一推很容易得出。

个人认为如果慢慢看的话讲述的是非常清楚的。

如果您有什么看不懂/~~我太弱了所以~~讲错了的地方，请您在评论区指出，我会解答并且修改本题解。

如果您觉得写的还不错，那可以留个赞吗?

QWQ。

感谢阅读。

---

## 作者：returnzheng (赞：1)

~~本题虽然思路难想，但是代码难度也很高呢~~
很容易想到，如果加一条边会改变直径，那么直径肯定经过那一条边。所以最后的直径只有两种可能：

1. 经过加的边
2. 原本的两条直径中长的一条

先不管第二点，它就只是两个直径而已，我们知道，一棵树中从某个点开始走的最长的简单路径另一端肯定是直径的某个端点，所以可以对两棵树分别进行三次 dfs 求出直径和每个点走的最远的距离。

这又什么用呢？分解一下第一点，发现 $f(i, j) = d_{1, i} + d_{2, j} + 1$ 也就是经过 $i, j$ 这条边的直径一定是两棵树中从 $i$ 和 $j$ 开始的最长路在加上这条边的长度。

现在，求第一点和第二点都是很简单的，可是什么时候用哪种可能还不知道。于是可以枚举第一棵树中的 $i$ 然后直接求出用直径的范围。在拿两个桶存第二棵树最长长度的个数和权值和，就可以方便的求出来了。


```cpp
#include <bits/stdc++.h>
using namespace std;
int d[210000];
int dd[210000];
int ddd[210000];
int dddd[210000];
vector<int> e[210000];
vector<int> ee[210000];
int ll = 0;
void dfs(int p, int fa = 0, int w = 0){
    d[p] = max(d[p], w);
    dd[p] = w;
    for (int i = 0; i < e[p].size(); i++){
        int x = e[p][i];
        if (x == fa){
            continue;
        }
        dfs(x, p, w + 1);
    }
    return;
}
void ddfs(int p, int fa = 0, int w = 0){
    ddd[p] = max(ddd[p], w);
    dddd[p] = w;
    for (int i = 0; i < ee[p].size(); i++){
        int x = ee[p][i];
        if (x == fa){
            continue;
        }
        ddfs(x, p, w + 1);
    }
    return;
}
int lll = 0;
int tt[300000];
int ttt[300000];
int main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 1; i <= n - 1; i++){
        int x, y;
        cin >> x >> y;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    int m;
    cin >> m;
    for (int i = 1; i <= m - 1; i++){
        int x, y;
        cin >> x >> y;
        ee[x].push_back(y);
        ee[y].push_back(x);
    }
    dfs(1);
    int p = 1;
    for (int i = 1; i <= n; i++){
        if (dd[p] < dd[i]){
            p = i;
        }
    }
    dfs(p);
    for (int i = 1; i <= n; i++){
        if (dd[p] < dd[i]){
            p = i;
        }
    }
    dfs(p);
    for (int i = 1; i <= n; i++){
        if (d[i] > ll){
            ll = d[i];
        }
    }
    ddfs(1);
    p = 1;
    for (int i = 1; i <= m; i++){
        if (dddd[p] < dddd[i]){
            p = i;
        }
    }
    ddfs(p);
    for (int i = 1; i <= m; i++){
        if (dddd[p] < dddd[i]){
            p = i;
        }
    }
    ddfs(p);
    for (int i = 1; i <= m; i++){
        if (ddd[i] > lll){
            lll = ddd[i];
        }
        tt[ddd[i]]++;
    }
    for (int i = 1; i <= m; i++){
        ttt[i] = ttt[i - 1] + tt[i] * i;
        tt[i] += tt[i - 1];
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++){
        int l = max(lll, ll) - d[i] - 1;
        ans += tt[l] * max(lll, ll) + (ttt[m] - ttt[l]) + (tt[m] - tt[l]) * (d[i] + 1);
    }
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：Shellchen (赞：1)

这题的核心是拆贡献。

首先我们需要求出每个点到其他点的最长路径长度。需要两次 dfs：第一次求出一个结点往下走的最长路径和次长路径（类似树的直径），第二次求出向上走的最长路径（如果这个结点在它父亲向下走的最长路径上，就是它父亲向上走和次长向下的最大值加一，否则就是父亲向上走和最长向下的最大值加一）。最长路径就是向下最长和向上最长的最大值。

之后，我们暂且忽略不经过新加的边的情况，那么总贡献就是 $\sum l_1 \cdot n_2 + \sum l_2 \cdot n_1 + n_1 \cdot n_2$（$\sum l_1$ 就是第一棵树中的最长长度之和，$\sum l_2$ 就是第二棵树的）。但是有时直径不经过新加的边，那它一定等于原来两棵树的直径最大值。于是我们可以二分查找换成直径更优的位置，用前缀和更新贡献。

**值得一提的是，代码非常难调！** 所以我们一定要 **细心检查每一个变量名，确保没有问题。**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e5+10,mod=1e9+7;
vector<int>adj1[N],adj2[N];
int d11[N],d12[N],hs1[N],u1[N],d21[N],d22[N],hs2[N],u2[N];
int n1,n2;
void dfs11(int u,int fa)
{
	for(auto v:adj1[u])
	{
		if(v==fa) continue;
		dfs11(v,u);
		int s=d11[v]+1;
		if(s>d11[u]) d12[u]=d11[u],d11[u]=s,hs1[u]=v;
		else if(s>d12[u]) d12[u]=s;
	}
}
void dfs21(int u,int fa)
{
	for(auto v:adj2[u])
	{
		if(v==fa) continue;
		dfs21(v,u);
		int s=d21[v]+1;
		if(s>d21[u]) d22[u]=d21[u],d21[u]=s,hs2[u]=v;
		else if(s>d22[u]) d22[u]=s;
	}
}
void dfs12(int u,int fa)
{
	for(auto v:adj1[u])
	{
		if(v==fa) continue;
		if(v==hs1[u]) u1[v]=max(u1[u],d12[u])+1;
		else u1[v]=max(u1[u],d11[u])+1;
		dfs12(v,u);
	}
}
void dfs22(int u,int fa)
{
	for(auto v:adj2[u])
	{
		if(v==fa) continue;
		if(v==hs2[u]) u2[v]=max(u2[u],d22[u])+1;
		else u2[v]=max(u2[u],d21[u])+1;
		dfs22(v,u);
	}
}
int l1[N],l2[N];
int s1[N],s2[N];
signed main()
{
	cin>>n1;
	for(int i=1;i<n1;i++)
	{
		int u,v;
		cin>>u>>v;
		adj1[u].push_back(v);
		adj1[v].push_back(u);
	}
	cin>>n2;
	for(int i=1;i<n2;i++)
	{
		int u,v;
		cin>>u>>v;
		adj2[u].push_back(v);
		adj2[v].push_back(u);
	}
	dfs11(1,0);
	dfs12(1,0);
	dfs21(1,0);
	dfs22(1,0);
	for(int i=1;i<=n1;i++) l1[i]=max(d11[i],u1[i]);
	for(int i=1;i<=n2;i++) l2[i]=max(d21[i],u2[i]);
	int d1=0,d2=0;
	for(int i=1;i<=n1;i++) d1=max(d1,d11[i]+d12[i]);
	for(int i=1;i<=n2;i++) d2=max(d2,d21[i]+d22[i]);
	int d=max(d1,d2);
	sort(l1+1,l1+n1+1);
	sort(l2+1,l2+n2+1);
	for(int i=1;i<=n1;i++) s1[i]=s1[i-1]+l1[i];
	for(int i=1;i<=n2;i++) s2[i]=s2[i-1]+l2[i];
	int ans1=s1[n1]*n2+s2[n2]*n1+n1*n2;
	for(int i=1;i<=n1;i++)
	{
		int p=lower_bound(l2+1,l2+n2+1,d-l1[i]-1)-l2-1;
		if(p==0) break;
		ans1=(ans1-p*l1[i]-s2[p]-p+p*d);
	}
	cout<<ans1;
	return 0;
}
```

---

## 作者：biyi_mouse (赞：1)

大力换根！

先考虑 $f(i, j)$ 怎么求，显然应该是第一棵树和第二棵树的直径与从 $i$ 最远能走的距离加从 $j$ 能走的最远距离 $+ 1$。

形式化的，我们设 $D1$ 为第一棵树的直径，$D2$ 为第二棵树的直径，$H1(i)$ 为第一棵树上的点 $i$ 能走到的最远距离，$H2(i)$ 为第二棵树上的点 $i$ 能走到的最远距离。则 $f(i, j) = \max(D1, D2, H1(i) + H2(j) + 1)$。

$D1$ 和 $D2$ 是人都会求，所以考虑怎么求 $H$。我们以第一棵树举例，第二棵树与第一棵树的求法一模一样。 

以 $1$ 为根，$G(u)$ 表示 $u$ 往子树走能到达的最远距离，$F(u)$ 表示 $u$ 往上走能到的最远距离，那么 $H(u) = \max(G(u), F(u))$。

对于 $G(u)$ 显然从子树转移过来即可，而对于 $F(u)$，我们可以从 $F(fa) + 1$ 转移过来，也可以从 $G2(fa) + 1$ 转移过来，其中 $G2(fa)$ 表示 $fa$ 往子树走的次长路。

这样你就会求 $H1$ 和 $H2$，然后考虑 $\sum f(i, j)$ 怎么求。

你会发现 $D1, D2$ 都是定值，所以设 $D = \max(D1, D2)$，然后将 $H2$ 排序。则对于一个 $H1(i)$，我们一定能将在 $H2$ 中找到一个划分点使得前半部分 $H1(i) + H2(j) + 1 < D$，后半部分大于 $D$。换言之，只需要在 $H2$ 中二分 $D - H1(i) - 1$ 即可。

然后由于你要计算一段的 $H2$ 值，所以前缀和优化一下就好了，还是蛮简单的（？）。

代码看起来很长其实一大部分都是重复的内容（我写的太狗屎了），而且这个方法好像也不是最优方法？看哥哥的代码是只有一个 BFS 这就有点抽象了。

```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i ++)
#define fro(i, a, b) for (int i = (a); i >= b; i --)
#define INF 0x3f3f3f3f
#define eps 1e-6
#define lowbit(x) (x & (-x))
#define initrand srand((unsigned)time(0))
#define random(x) ((LL)rand() * rand() % (x))
#define eb emplace_back
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
typedef pair<double, int> PDI;
#define int long long
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
    return x * f;
}

const int N = 200010;
int n1, n2;
vector<int> G1[N], G2[N];
int f1[N], f2[N], g1[N], g2[N], F1[N], F2[N], s[N];

void dfs1(int u, int fa) {
    g1[u] = 0;
    for (auto v : G1[u]) {
        if (v == fa) continue;
        dfs1(v, u);
        g1[u] = max(g1[u], g1[v] + 1);
    }
}

void dfs2(int u, int fa) {
    g2[u] = 0;
    for (auto v : G2[u]) {
        if (v == fa) continue;
        dfs2(v, u);
        g2[u] = max(g2[u], g2[v] + 1);
    }
}

void dfs3(int u, int fa) {
    int maxd = 0, smaxd = 0;
    for (auto v : G1[u]) {
        if (v == fa) continue;
        int d = g1[v] + 1;
        if (d > maxd) smaxd = maxd, maxd = d;
        else if (d > smaxd) smaxd = d;
    }
    for (auto v : G1[u]) {
        if (v == fa) continue;
        int use = maxd;
        if (use == g1[v] + 1) use = smaxd;
        f1[v] = max(f1[u] + 1, use + 1); 
        dfs3(v, u);
    }
}

void dfs4(int u, int fa) {
    int maxd = 0, smaxd = 0;
    for (auto v : G2[u]) {
        if (v == fa) continue;
        int d = g2[v] + 1;
        if (d > maxd) smaxd = maxd, maxd = d;
        else if (d > smaxd) smaxd = d;
    }
    for (auto v : G2[u]) {
        if (v == fa) continue;
        int use = maxd;
        if (use == g2[v] + 1) use = smaxd;
        f2[v] = max(f2[u] + 1, use + 1); 
        dfs4(v, u);
    }
}

signed main() {
    n1 = read();
    for (int i = 1; i < n1; i ++) {
        int a = read(), b = read();
        G1[a].push_back(b); G1[b].push_back(a);
    }
    n2 = read();
    for (int i = 1; i < n2; i ++) {
        int a = read(), b = read();
        G2[a].push_back(b); G2[b].push_back(a);
    }
    dfs1(1, -1); dfs2(1, -1);
    dfs3(1, -1); dfs4(1, -1);
    int d1 = 0, d2 = 0;
    for (int i = 1; i <= n1; i ++) {
        F1[i] = max(g1[i], f1[i]);
        d1 = max(d1, F1[i]);
    }
    for (int i = 1; i <= n2; i ++) {
        F2[i] = max(g2[i], f2[i]);
        d2 = max(d2, F2[i]);
    }
    int D = max(d1, d2), ans = 0;
    sort(F2 + 1, F2 + 1 + n2);
    for (int i = 1; i <= n2; i ++) s[i] = s[i - 1] + F2[i];
    for (int i = 1; i <= n1; i ++) {
        int X = D - F1[i] - 1;
        int j = lower_bound(F2 + 1, F2 + 1 + n2, X) - F2;
        ans += (j - 1) * D + s[n2] - s[j - 1] + (F1[i] + 1) * (n2 - j + 1);
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：I_will_AKIOI (赞：1)

根据经典结论：把两棵树合并在一起，新树的直径端点肯定在原来两棵树直径端点上。因此我们可以先预处理出直径端点 $p_0\sim p_3$，第一棵树的直径端点用 $p_0,p_1$ 表示，第二棵用 $p_2,p_3$ 表示。同时预处理出距离 $dis_{0,i}\sim dis_{3,i}$，其中 $dis_{0,i}$ 表示 $p_0$ 到 $i$ 的距离，其余同理。

合并成的新树的直径分三种情况：在第一棵树，在第二棵树，和跨过两棵树。对于前两种情况，由于直径是最长的，因此只需要令 $d$ 为两棵树直径最大值就可以优化掉一种情况。

假设两个端点为 $i,j$，那么第一棵树到 $i$ 的长度就是 $\max(dis_{0,i},dis_{1,i})$，第二棵树到 $j$ 的长度就是 $\max(dis_{2,j},dis_{3,j})$。先预处理 $m_{0,i}$ 表示 $\max(dis_{0,i},dis_{1,i})$，$m_{1,j}$ 表示 $\max(dis_{2,j},dis_{3,j})$。把 $i,j$ 连起来的直径就是 $\max(m_{0,i}+m_{1,j}+1,d)$。

发现答案和 $i,j$ 无关，因此可以直接对 $m$ 进行排序，接着只枚举 $i$，二分出一个最大的 $j$ 使得 $m_{0,i}+m_{1,j}+1\le d$，这样就可以利用前缀和快速计算两部分了。时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200005
using namespace std;
int ans,sum[N],n[2],p[4],dis[4][N],maxx[2][N],len;
vector<int>v[2][N];
void dfs(int p1,int p2,int k,int fa)//当前的树为 p1，起点为 p2，走到了节点 k。
{
	for(int now:v[p1][k])
	{
		if(now==fa) continue;
		dis[p2][now]=dis[p2][k]+1;
		dfs(p1,p2,now,k);
	}
	return;
}
signed main()
{
	cin>>n[0];
	for(int i=1;i<n[0];i++)
	{
		int x,y;
		cin>>x>>y;
		v[0][x].push_back(y);
		v[0][y].push_back(x);
	}
	cin>>n[1];
	for(int i=1;i<n[1];i++)
	{
		int x,y;
		cin>>x>>y;
		v[1][x].push_back(y);
		v[1][y].push_back(x);
	}
	dfs(0,0,1,0);
	for(int i=1;i<=n[0];i++) if(dis[0][i]>dis[0][p[0]]) p[0]=i;
	dfs(0,1,p[0],0);
	for(int i=1;i<=n[0];i++) if(dis[1][i]>dis[1][p[1]]) p[1]=i;
	dfs(1,2,1,0);
	for(int i=1;i<=n[1];i++) if(dis[2][i]>dis[2][p[2]]) p[2]=i;
	dfs(1,3,p[2],0);
	for(int i=1;i<=n[1];i++) if(dis[3][i]>dis[3][p[3]]) p[3]=i;
	memset(dis,0,sizeof(dis));
	dfs(0,0,p[0],0);
	dfs(0,1,p[1],0);
	dfs(1,2,p[2],0);
	dfs(1,3,p[3],0);
	for(int i=1;i<=n[0];i++) maxx[0][i]=max(dis[0][i],dis[1][i]);
	for(int i=1;i<=n[1];i++) maxx[1][i]=max(dis[2][i],dis[3][i]);
	sort(maxx[1]+1,maxx[1]+n[1]+1);
	for(int i=1;i<=n[1];i++) sum[i]=sum[i-1]+maxx[1][i];
	len=max(dis[0][p[1]],dis[2][p[3]]);
	for(int i=1;i<=n[0];i++)
	{
		int l=0,r=n[1],mid;
		while(l<r)
		{
			mid=l+r+1>>1;
			if(maxx[0][i]+maxx[1][mid]>=len) r=mid-1;
			else l=mid;
		}
		ans+=len*l+(sum[n[1]]-sum[l])+((maxx[0][i]+1)*(n[1]-l));
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：WuMin4 (赞：1)

## [[ABC401F] Add One Edge 3](https://atcoder.jp/contests/abc401/tasks/abc401_f)

## 题意

给出两棵树，可以在两棵树的任意两点添加一条边，问所有连边方案形成的新树的直径之和为多少。

## 思路

考虑加入一条边后，树的直径的可能性有几种。

1. 树的直径经过新加入的边，此时树的直径大小即为 $D_{1,i}+D_{2,j}+1$，此处 $D_{1,i},D_{2,j}$ 表示该点到该树任意一点的最远路径长度。

2. 树的直径不经过新加入的边，此时树的直径即为 $\max{(mx_1,mx_2)}$，即为两棵树直径的最大值。

若边 $(i,j)$ 已经确定了点 $i$，我们可以发现当 $D_{1,i}+D_{2,j}+1\le \max{(mx_1,mx_2)}$ 时方案二不劣于方案一，也就是 $j$ 要满足 $D_{2,j}\le \max{(mx_1,mx_2)}-D_{1,i}-1$。

我们设 $P_j=1$ 表示满足该条件，$P'_j=1$ 表示不满足该条件，于是对于 $j=1,2,\cdots,n_2$，将 $(i,j)$ 连边能产生的代价之和即为：

$$
\max{(mx_1,mx_2)}\times \sum_{j=1}^{n_2} P_j+(D_{1,i}+1)\times \sum_{j=1}^{n_2} P'_j+\sum_{j=1}^{n_2} (P'_j \times D_{2,j})
$$

因为我们不关心点，只关心最远路径长度，所以 $\sum_{j=1}^{n_2} P_j$ 可以很容易通过对 $D_{2,j}$ 排序后二分算出来。对于 $\sum_{j=1}^{n_2} (P'_j \times D_{2,j})$ 也可以通过对 $D_{2,j}$ 求前缀和计算。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n1,n2,mx1,mx2,d11,d12,d21,d22,D1[200005],D2[200005],c[200005],ans;
vector<int> t1[200005],t2[200005];
void dfs11(int x,int fa,int d){
	if(d>mx1) mx1=d,d11=x;
	for(int v:t1[x])
		if(v!=fa) dfs11(v,x,d+1);
}
void dfs12(int x,int fa,int d){
	if(d>mx1) mx1=d,d12=x;
	D1[x]=max(D1[x],d);
	for(int v:t1[x])
		if(v!=fa) dfs12(v,x,d+1);
}
void dfs13(int x,int fa,int d){
	D1[x]=max(D1[x],d);
	for(int v:t1[x])
		if(v!=fa) dfs13(v,x,d+1);
}
void dfs21(int x,int fa,int d){
	if(d>mx2) mx2=d,d21=x;
	for(int v:t2[x])
		if(v!=fa) dfs21(v,x,d+1);
}
void dfs22(int x,int fa,int d){
	if(d>mx2) mx2=d,d22=x;
	D2[x]=max(D2[x],d);
	for(int v:t2[x])
		if(v!=fa) dfs22(v,x,d+1);
}
void dfs23(int x,int fa,int d){
	D2[x]=max(D2[x],d);
	for(int v:t2[x])
		if(v!=fa) dfs23(v,x,d+1);
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n1;
	for(int x,y,i=1;i<n1;i++){
		cin>>x>>y;
		t1[x].push_back(y);
		t1[y].push_back(x);
	}
	cin>>n2;
	for(int x,y,i=1;i<n2;i++){
		cin>>x>>y;
		t2[x].push_back(y);
		t2[y].push_back(x);
	}
	dfs11(1,0,0);mx1=0;
	dfs12(d11,0,0);
	dfs13(d12,0,0);
	dfs21(1,0,0);mx2=0;
	dfs22(d21,0,0);
	dfs23(d22,0,0);
	sort(D1+1,D1+1+n1);
	sort(D2+1,D2+1+n2);
	for(int i=1;i<=n2;i++)
		c[i]=c[i-1]+D2[i];
	for(int x,i=1;i<=n1;i++){
		x=upper_bound(D2+1,D2+1+n2,max(mx1,mx2)-D1[i]-1)-D2-1;
		ans+=max(mx1,mx2)*x+(D1[i]+1)*(n2-x)+(c[n2]-c[x]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：small_lemon_qwq (赞：1)

一个显然的性质，$f_{i,j}$ 的取值可能是：
+ 树 $1$ 的直径
+ 树 $2$ 的直径
+ 树 $1$ 中距离 $i$ 最远的点 $+$ 树 $2$ 中距离 $j$ 最远的点 $+1$。

那么问题就变成了求树中距离每个点最远的点的距离。

有手就行，设距离为 $d_i,D_{i}$，直径分别为 $x,X$。

答案就是 $\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}\max\{x,X,d_i+D_j+1\}$。

非常简单，先对 $D$ 排序，然后可以求满足 $\max\{x,X\}\le d_i+D_j+1$ 的 $j$ 的 $D_j$ 的个数和 $D_j$ 的和，$\max\{x,X\}>d_i+D_j+1$ 同理。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,N,f[200005][2],d[200005],D[200005],x,X,ans,sum[200005];
vector<int>g[200005],G[200005];
void dfs(int x,int fa,const vector<int>g[]){
	f[x][0]=f[x][1]=0;
	for(int y:g[x]){
		if(y==fa)continue;
		dfs(y,x,g);
		if(f[y][0]+1>f[x][0]){
			f[x][1]=f[x][0];
			f[x][0]=f[y][0]+1;
		}else{
			f[x][1]=max(f[x][1],f[y][0]+1);
		}
	}
}
void dfs2(int x,int fa,const vector<int>g[],int d[],int&ans){
	for(int y:g[x]){
		if(y==fa)continue;
		if(f[x][0]==f[y][0]+1){
			int t=f[x][1]+1;
			if(t>f[y][0])f[y][0]=t;
			else f[y][1]=max(f[y][1],t);
		}else{
			int t=f[x][0]+1;
			if(t>f[y][0])f[y][0]=t;
			else f[y][1]=max(f[y][1],t);
		}
		d[y]=f[y][0];
		ans=max(ans,d[y]);
		dfs2(y,x,g,d,ans);
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=2;i<=n;i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	cin>>N;
	for(int i=2;i<=N;i++){
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1,-1,g);
	x=d[1]=f[1][0];
	dfs2(1,-1,g,d,x);
	
	dfs(1,-1,G);
	X=D[1]=f[1][0];
	dfs2(1,-1,G,D,X);
//	for(int i=1;i<=n;i++){
//		cout<<d[i]<<" ";
//	}
//	cout<<"\n";
//	for(int i=1;i<=N;i++){
//		cout<<D[i]<<" ";
//	}
//	cout<<"\n";
	stable_sort(D+1,D+N+1);
	for(int i=N;i>=1;i--)sum[i]=sum[i+1]+D[i];
	for(int i=1;i<=n;i++){
		int pos=lower_bound(D+1,D+N+1,max(x,X)-d[i]-1)-D;
		ans+=sum[pos]+(N-pos+1)*(d[i]+1);
		ans+=(pos-1)*max(x,X);
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：Lucyna_Kushinada (赞：1)

# abc401_f  Add One Edge 3

## 简要题意

给定两棵树 $T_1,T_2$，点数分别为 $N_1,N_2$。

定义 $f(i,j)$ 表示将 $T_1$ 上的点 $i$ 与 $T_2$ 上的点 $j$ 连一条边后得到的新树的直径。

求 $\displaystyle \sum_{i=1}^{N_1}\sum_{j=1}^{N_2} f(i,j)$。

$1\le N_1,N_2\le 2\times 10^5$。

## 题解

知识点：树的直径，图论，~~树状数组~~。

定义 $d_{1,i}$ 表示 $T_1$ 以 $i$ 为根后树的最大深度，$d_{2,i}$ 同理，$len_1$ 表示 $T_1$ 的直径，$len_2$ 同理，$D=\max\{len_1,len_2\}$。

则 $f(i,j)=\max\{D,d_{1,i}+d_{2,j}+1\}$。

显然当 $d_{1,i}+d_{2,j}+1\le D$ 时，$f(i,j)=D$。

所以 $d_{1,i}+d_{2,j}+1$ 有贡献当且仅当 $d_{1,i}+d_{2,j}+1>D$，即 $d_{1,j}>D-1-d_{2,i}$。

$d_{1}$，$d_{2}$ 是好求的，直接 dp 即可，而 $len_1,len_2$ 更不必说了。

先把 $T_1$ 上的每一个点的 $d_{1,i}$ 丢到值域树状数组上。

枚举 $T_2$ 上的点 $j$，查询树状数组中满足上述不等式的 $d_{1,i}$ 之和，加到贡献中，还要查询**不满足**上述不等式的点的数量 $c$，将 $c\times D$ 加到贡献中，就做完了。

复杂度 $O(n\log_2 n)$。

启发：

- 两棵树合并后新的直径的求法。

- 善用结构体封装。

忘记给树状数组的 $n$ 赋初值了，导致了赛后过题的悲剧，下次一定要注意。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,l,r) for(int i=(l);i<=(r);++i)
#define per(i,l,r) for(int i=(r);i>=(l);--i)
#define pr pair<int,int>
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define sz(x) (x).size()

#define N 202504
#define int long long

struct TREE{
    vector<int>e[N];
    int n,len;
    int dw1[N],dw2[N],up[N],mx[N];
    int d1[N],d2[N];

    inline void input(){
        cin>>n;
        rep(i,1,n-1) {
            int u,v;
            cin>>u>>v;
            e[u].pb(v);
            e[v].pb(u);
        }
    }

    inline void bfs(int st,int *d){
        queue<int>q;
        fill(d+1,d+n+1,-1);

        d[st]=0;
        q.push(st);

        while(!q.empty()){
            int u=q.front();
            q.pop();

            for(int v:e[u]){
                if(d[v]==-1){
                    d[v]=d[u]+1;
                    q.push(v);
                }
            }
        }
    }

    inline void get_len(){
        bfs(1,d1);
        int u=max_element(d1+1,d1+n+1)-d1;
        bfs(u,d2);
        int v=max_element(d2+1,d2+n+1)-d2;
        len=d2[v];
    }

    inline void dfs_dw(int u,int fa){

        dw1[u]=dw2[u]=0;
        for (int v:e[u]){
            if (v!=fa){
                dfs_dw(v,u);
                int d=dw1[v]+1;
                if(d>dw1[u]){
                    dw2[u]=dw1[u];
                    dw1[u]=d;
                }
                else if(d>dw2[u]){
                    dw2[u]=d;
                }
            }
        }
    }

    inline void dfs_up(int u,int fa){
        for(int v:e[u]){
            if (v!=fa){
                up[v]=up[u]+1;
                if(dw1[v]+1==dw1[u]){
                    up[v]=max(up[v],dw2[u]+1);
                }
                else{
                    up[v]=max(up[v],dw1[u]+1);
                }
                dfs_up(v,u);
            }
        }
        mx[u]=max(dw1[u],up[u]);
    }

    inline void calc(){
        dfs_dw(1,0);
        up[1]=0;
        dfs_up(1,0);
    }
}t1,t2;

struct BIT{
    int tr[N],lim;
    #define lb(x) (x&-x)

    inline void upd(int k,int d){
        while(k<=lim){
            tr[k]+=d;
            k+=lb(k);
        }
    }

    inline int ask(int k){
        if(k<0){
            return 0;
        }
        int ans=0;

        while(k){
            ans+=tr[k];
            k-=lb(k);
        }

        return ans;
    }
}t,cnt;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    t1.input();
    t2.input();

    t1.get_len();
    t2.get_len();

    t1.calc();
    t2.calc();

    cnt.lim=t.lim=max(t1.n,t2.n);

    rep(i,1,t1.n){
        cnt.upd(t1.mx[i],1);
        t.upd(t1.mx[i],t1.mx[i]);
    }

    int ans=0,D=max(t1.len,t2.len);

    rep(i,1,t2.n){
        int c=cnt.ask(D-t2.mx[i]-1);

        ans=(ans+c*D);

        c=t1.n-c;
        int sum=t.ask(t.lim)-t.ask(D-t2.mx[i]-1);

        ans=(ans+c*(t2.mx[i]+1)+sum);
    }

    cout<<ans;

    return 0;
}
```

---

## 作者：dingxiongyue (赞：1)

# 题解：AT_abc401_f [ABC401F] Add One Edge 3 

## Description：
给定两棵无向树，定义 $f(i,j)$ 为添加一条树 $1$ 的结点 $i$ 与树 $2$ 的结点 $j$ 之间的无向边后新组成树的直径，求 $\sum _ {i = 1} ^ {N_1} \sum _ {j = 1} ^{N_2} f(i,j)$。

## Analysis：
设两棵树的直径分别是 $d_1$，$d_2$，数组 $a$，$b$ 分别表示两棵树中每个点能到达的最深深度。则 $
f (i,j) = \max  (d_1, d_2, a_i + b_j + 1)$。  

设树的直径的端点为 $u$，$v$，显然有 $a_i = \max (\operatorname{dist} (u, i) , \operatorname{dist} (v, i))$，可以快速求出数组 $a$，$b$。

至于统计答案，将数组 $a$，$b$ 排序后，对于每个 $a_i$，在 $b$ 中二分出第一个大于 $\max (d_1, d_2) - a_i - 1$ 的数，设其下标为 $t$，则答案为：

$$
\sum _ {i = 1} ^ {N_1} [(t - 1) \times \max (d_1, d_2) + \sum _ {j = t} ^ {N_2} (a_i + b_j + 1)]
$$

前缀和优化为：

$$
\sum _ {i = 1} ^ {N_1} [(t - 1) \times \max (d_1, d_2) + s_{N_2} - s_{t - 1} + (N_2 - t + 1) \times (a_i + 1)]
$$

时间复杂度 $O(N \log N)$。

## Code:
[AC记录](https://atcoder.jp/contests/abc401/submissions/64895018)
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#define int long long
const int N = 2e5 + 10;
int n1, n2;
int u, v;
int d1, d2, d;
int root;
int rt;
int maxn;
int ans;
int a[N], b[N];
int s[N];
int w[N][3];
int e[N << 1], ne[N << 1], h[N << 1], idx;
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}

inline void write(int x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

void init() {
	memset(h, -1, sizeof h);
	memset(w, 0, sizeof w);
	idx = maxn = 0;
}

void add(int a, int b) {
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u, int fa, int k) {
	if (u != root) w[u][k] = w[fa][k] + 1;
	for (int i = h[u]; ~i; i = ne[i]) {
		int v = e[i];
		if (v == fa) continue;
		dfs(v, u, k);
	}
}

signed main() {
	init();
	n1 = read();
	for (int i = 1; i < n1; i++) {
		u = read(), v = read();
		add(u, v), add(v, u);
	}
	root = 1;
	dfs(1, 0, 0);
	for (int i = 1; i <= n1; i++) 
		if (w[i][0] > maxn) 
			maxn = w[i][0], root = i;
	for (int i = 1; i <= n1; i++) 
		a[i] = w[i][0];
	dfs(root, 0, 1);
	rt = root;
	for (int i = 1; i <= n1; i++) {
		a[i] = std::max(a[i], w[i][1]);
		if (d1 < w[i][1]) 
			d1 = w[i][1], root = i;
	}
	a[rt] = std::max(a[rt], d1);
	dfs(root, 0, 2);
	for (int i = 1; i <= n1; i++) 
		a[i] = std::max(a[i], w[i][2]);
		

	init();
	n2 = read();
	for (int i = 1; i < n2; i++) {
		u = read(), v = read();
		add(u, v), add(v, u);
	}
	root = 1;
	dfs(1, 0, 0);
	for (int i = 1; i <= n2; i++) 
		if (w[i][0] > maxn) 
			maxn = w[i][0], root = i;
	for (int i = 1; i <= n2; i++) 
		b[i] = w[i][0];
	dfs(root, 0, 1);
	rt = root;
	for (int i = 1; i <= n2; i++) {
		b[i] = std::max(b[i], w[i][1]);
		if (d2 < w[i][1]) 
			d2 = w[i][1], root = i;
	}
	b[rt] = std::max(b[rt], d2);
	dfs(root, 0, 2);
	for (int i = 1; i <= n2; i++) 
		b[i] = std::max(b[i], w[i][2]);
		
 
	d = std::max(d1, d2);
	std::sort(a + 1, a + 1 + n1);
	std::sort(b + 1, b + 1 + n2);
	for (int i = 1; i <= n2; i++) 
		s[i] = s[i - 1] + b[i];
	for (int i = 1; i <= n1; i++) {
		int id = std::upper_bound(b + 1, b + 1 + n2, d - a[i] - 1) - b;
		ans += (id - 1) * d + s[n2] - s[std::max(id - 1, 0ll)] + (n2 - id + 1) * (a[i] + 1);
	}
	
	
	write(ans);
	putchar('\n');
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

## Solution

显然对于一对点 $u \in T_1 , v \in T_2$，$f(u,v)$ 要么是原本 $T_1,T_2$ 直径的最大值，要么是连了新边之后经过边 $(u,v)$ 的最长路径。前者是容易的，对于后者，我们发现可以拆成 $T_1$ 内 $u$ 能到达的最长路径长度加上 $T_2$ 内 $v$ 能到达的最长路径长度再加 $1$，两部分显然是很好求的。

将 $T_1$ 内 $u$ 能到达的最长路径长度设为 $f_u$，设 $T_1$ 的直径为 $x \leadsto y$，那么显然根据直径的定义，$f_u$ 就等于 $\max({\rm dist}(u,x) , {\rm dist}(u,y))$。$g_v$ 同理。

然后统计答案，因为 $f,g$ 的顺序没有影响，于是可以排个序使其满足单调性，于是二分或者双指针算即可。

时间复杂度 $O(n \log n)$ 或 $O(n)$。

## Code

```cpp
int n,m,f[N],g[N],s[N],dep[N];
vector <int> p[2][N];

il void dfs(int u,int ufa,bool op)
{
	for(auto v:p[op][u]) v!=ufa && (dep[v]=dep[u]+1,dfs(v,u,op),1);
}

signed main()
{
	read(n),_::r(p[0],n-1,false),read(m),_::r(p[1],m-1,false);
	
	int _mx,x,y,len=0;
	rep(op,0,1)
	{
		int *dp=op?g:f;
		int num=op?m:n;
		
		memset(dep,0,sizeof(dep)),dfs(1,0,op);
		_mx=-1; rep(i,1,num) dep[i]>_mx && (_mx=dep[i],x=i);
		
		memset(dep,0,sizeof(dep)),dfs(x,0,op);
		_mx=-1; rep(i,1,num) dep[i]>_mx && (_mx=dep[i],y=i);
		chmax(len,_mx);
		rep(i,1,num) chmax(dp[i],dep[i]);
		
		memset(dep,0,sizeof(dep)),dfs(y,0,op);
		rep(i,1,num) chmax(dp[i],dep[i]);
		
	}
	
	sort(g+1,g+m+1);
	rpe(i,m,1) s[i]=s[i+1]+g[i];
	
	int ans=0,ind;
	rep(i,1,n)
	{
		ind=lower_bound(g+1,g+m+1,len-f[i]-1)-g;
		ans+=s[ind]+(f[i]+1)*(m-ind+1)+len*(ind-1);
	}
	
	write(ans);
	
	return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：Ivan422 (赞：1)

### 赛时反思

太久没有写直径了导致没有发现：

- 两树连边后直接可能**过新边**也可能**不过新边**。

同时变相导致正好 Rating 掉了 $1$。

### 题目大意

给你两颗树点分别为 $n,m$，考虑两两连边，即 $1$ 树的 $i$ 点与 $2$ 树 $j$ 点连边。

然后设 $f(i,j)$ 为新树直径。

求 $\sum_{i=1}^n\sum_{j=1}^m f(i,j)$。

### 赛时做法

最基础的题解，最勾石的做法。

我们考虑过新边的做法如何统计。

容易得答案为 $dis_{0,i}+1+dis_{1,i}$，$dis_{0/1,i}$ 为一个树以 $i$ 为根的最远点距离。

然后我们发现这是一个经典的东西。

我们考虑换根。

我的状态定义比较构式，$f_{0/1,i,0/1,0/1}$ 不太美观，就是 $f_{tr,p,idx,is}$，$tr$ 表示树编号，$p$ 表示节点，$idx$ 表示记录的是最长还是次长，$is$ 表示记录的是长度还是前往节点。

然后直接维护。

前方勾石！

当 $f_{tr,v,0,0}+1>f_{tr,p,0,0}$，我们发现从 $p$ 往 $v$ 子树可以走更远。

这时我们要进行以下 $4$ 个操作：

1. $f_{tr,p,1,0}=f_{tr,p,0,0}$，更新次长**长度**。
2. $f_{tr,p,1,1}=f_{tr,p,0,1}$，更新次长**指向节点**。
3. $f_{tr,p,0,0}=f_{tr,v,0,0}+1$，更新最长**长度**。
4. $f_{tr,p,0,1}=v$，更新最长**指向节点**。

好的接下来同理否则当 $f_{tr,v,0,0}+1>f_{tr,p,1,0}$：

1. $f_{tr,p,1,0}=f_{tr,v,0,0}+1$，更新次长**长度**。
2. $f_{tr,p,1,1}=v$，更新次长**指向节点**。

好的接下来才是真的换上根了。

我们注意到答案还可能是**回到根走另一条路**。

具体的看图（手绘很丑）：

![](https://cdn.luogu.com.cn/upload/image_hosting/se3s15go.png)

我们刚刚说的东西就是 $g_{tr,p}$。

我们考虑在第二次深搜中求这个东西。

分讨。

1. 首先要是 $f_{tr,p,0,1}=v$，那么我们就不能简单的由 $g_{tr,p}$ 来继承最短路，因为最短路已经被占用了。转移就是 $g_{tr,v}=\max(g_{tr,p},f_{tr,p,1,0})+1$，显然用根的次长路更新。
2. 否则 $g_{tr,v}=\max(g_{tr,p},f_{tr,p,0,0})+1$。

好的接下来我们就可以维护**过一个点的最长路径长度**。

即 $f_{tr,p,0,0}$，$f_{tr,p,1,0}$，$g_{tr,p}$ 中选最长两个拼起来。

同理我们还可以维护**以一个点为根的最大深度节点的深度**，设这个值为 $nw_{tr,p}$。

然后我们就完成了第一部分。

### 赛后补充

但是，我菜，想不到直径可能出现在单个树里面。

其实我们可以很容易根据上面的东西维护出 $d_{tr}$，即一颗树的直径。

然后我们考虑 $f(i,j)=\max(d_0,d_1,d_{new})$ 的长度，$d_{new}$ 就是 $i$ 点为根，$j$ 点也为根，两最大深度节点深度加起来再 $+1$，可以表示为 $nw_{0,i}+1+nw_{1,i}$。

我们发现 $\max(d_0,d_1)$ 为定值。

可以用二分轻松维护答案。

具体的，要是 $\max(d_0,d_1)\ge nw_{0,i}+1+nw_{1,i}$ 就可以直接用 $\max(d_0,d_1)$。

我们考虑在 $nw_{1}$ 上二分。

不等式移项得 $nw_{1,i}\le \max(d_0,d_1)-nw_{0,i}-1$。

可以直接二分了。

然后我们得出来前 $ps$ 个都取 $\max(d_0,d_1)$。

接下来拆双 $\sum$。

我们发现式子变成：

$$
\sum_{i=1}^n (ps\times\max(d_0,d_1)+\sum_{j=ps+1}^m nw_{0,i}+1+nw_{1,j})
$$

拆 $\sum$ 得：

$$
\sum_{i=1}^n (ps\times\max(d_0,d_1)+(m-ps)(nw_{0,i}+1)+\sum_{j=ps+1}^m nw_{1,j})
$$ 

发现后面的 $\sum_{j=ps+1}^m nw_{1,j}$ 转化成前缀和得：

$$
\sum_{i=1}^n (ps\times\max(d_0,d_1)+(m-ps)(nw_{0,i}+1)+s_m-s_{ps})
$$ 

复杂度 $\mathcal O(n\log n)$。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,m,U,V,W;
__int128 f[2][N][2][2],g[2][N],nw[2][N],su,ans,d[2],s[N];
vector<int>e[2][N];
template<typename type>
inline void write(type x){
    x<0?x=-x,putchar('-'):0;static short Stack[50],top(0);
    do Stack[++top]=x%10,x/=10; while(x);
    while(top) putchar(Stack[top--]|48);
}
void dfs(int tr,int p,int fa){
	for(auto v:e[tr][p])if(v!=fa){
		dfs(tr,v,p);
		if(f[tr][v][0][0]+1>f[tr][p][0][0]){
			f[tr][p][1][0]=f[tr][p][0][0];
			f[tr][p][1][1]=f[tr][p][0][1];
			f[tr][p][0][0]=f[tr][v][0][0]+1;
			f[tr][p][0][1]=v;
		}else if(f[tr][v][0][0]+1>f[tr][p][1][0]){
			f[tr][p][1][0]=f[tr][v][0][0]+1;
			f[tr][p][1][1]=v;
		}
	}
}
void dfs2(int tr,int p,int fa){
	for(auto v:e[tr][p])if(v!=fa){
		if(f[tr][p][0][1]==v){
			if(g[tr][p]>=f[tr][p][1][0])g[tr][v]=g[tr][p]+1;
			else g[tr][v]=f[tr][p][1][0]+1;
		}else g[tr][v]=max(f[tr][p][0][0],g[tr][p])+1;
		dfs2(tr,v,p);
	}
}
signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>U>>V;
		e[0][U].push_back(V);
		e[0][V].push_back(U);
	}
	cin>>m;
	for(int i=1;i<m;i++){
		cin>>U>>V;
		e[1][U].push_back(V);
		e[1][V].push_back(U);
	}
	dfs(0,1,0);
	dfs2(0,1,0);
	dfs(1,1,0);
	dfs2(1,1,0);
	for(int i=1;i<=n;i++)
		nw[0][i]=max({
			f[0][i][1][0],
			f[0][i][0][0],
			g[0][i]}),
		d[0]=max(d[0],
			f[0][i][1][0]+
			f[0][i][0][0]+
			g[0][i]-nw[0][i]);
	for(int i=1;i<=m;i++)
		nw[1][i]=max({
			f[1][i][1][0],
			f[1][i][0][0],
			g[1][i]}),
		d[1]=max(d[1],
			f[1][i][1][0]+
			f[1][i][0][0]+
			g[1][i]-nw[1][i]);
	sort(nw[0]+1,nw[0]+n+1);
	sort(nw[1]+1,nw[1]+m+1);	
	for(int j=1;j<=m;j++)
		s[j]=s[j-1]+nw[1][j];
	for(int i=1;i<=n;i++){
		__int128 val=max(d[0],d[1])-nw[0][i]-1;
		int ps=lower_bound(nw[1]+1,nw[1]+m+1,val)-nw[1];
		ans+=ps*max(d[0],d[1])+(s[m]-s[ps])+(m-ps)*(nw[0][i]+1);
		nw[0][i]+1+x<=max(d[0],d[1]);
	}
	write(ans);
	return 0; 	
}
```

---

## 作者：VitrelosTia (赞：0)

首先我们很难不想到一个结论：拼起来树的直径端点在原本两个树的直径端点集合之中。设两树端点分别为 $(A_1,B_1)，(A_2,B_2)$。

我们画一下图，如果直径跨过连的边 $(i,j)$，长度就是 $\displaystyle \max(dis_{A_1,i},dis_{B_1,i}) + 1 + \max(dis_{A_2,j},dis_{B_2,j})$，根据前面那个结论应该比较显然，但是可能直径还在原树上，所以还有要和两个原树的直径的较大值 $d$ 取个 $\max$。

可以先对两个树把每个点的 $\max(dis_{A,i},dis_{B,i})$ 给预处理出来，我们要做的问题就形如 $\displaystyle\sum_{i,j}\max(p_i+q_j+1,d)$，这个问题比较经典，我们先把 $p_i$ 排个序，然后枚举 $j$，贡献区间显然是连续的。我们二分查找处 $\max$ 的变化点，前面的贡献都是 $d$，后面的贡献 $p$ 部分可以后缀和解决，$q$ 的贡献是固定的。

附上~~我觉得很好看的~~代码。~~代码渲染比较唐，可以复制到 ide 上看。~~

```cpp
const int N = 2e5 + 5;
int sum[N];
struct Tree {
    int n; vector <int> g[N]; int A, B, d[N], da[N], db[N], c[N];
    void Add(int u, int v) { g[u].push_back(v); g[v].push_back(u); }
    void dfs1(int u, int fa) { d[u] = d[fa] + 1; if (d[u] > d[A]) A = u; for (int v : g[u]) if (v != fa) dfs1(v, u); }
    void dfs2(int u, int fa) { da[u] = da[fa] + 1; if (da[u] > da[B]) B = u; for (int v : g[u]) if (v != fa) dfs2(v, u); }
    void dfs3(int u, int fa) { db[u] = db[fa] + 1; for (int v : g[u]) if (v != fa) dfs3(v, u); }
    void init() {
        cin >> n;
        for (int i = 1, u, v; i < n; i++) {
            cin >> u >> v;
            g[u].push_back(v); g[v].push_back(u);
        } da[0] = db[0] = -1; dfs1(1, 0); dfs2(A, 0); dfs3(B, 0);
        for (int i = 1; i <= n; i++) c[i] = max(da[i], db[i]);
    }
} t1, t2;

signed main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    t1.init(); t2.init(); int d = max(t1.da[t1.B], t2.da[t2.B]);
    sort(t1.c + 1, t1.c + t1.n + 1); int ans = 0;
    for (int i = t1.n; i >= 1; i--) sum[i] = sum[i + 1] + t1.c[i];
    for (int i = 1; i <= t2.n; i++) {
        int p = upper_bound(t1.c + 1, t1.c + t1.n + 1, d - t2.c[i] - 1) - t1.c - 1;
        ans += p * d + sum[p + 1] + (t2.c[i] + 1) * (t1.n - p);
    } cout << ans;
    return 0;
}

```

---

## 作者：DengStar (赞：0)

[题目链接](https://atcoder.jp/contests/abc401/tasks/abc401_f) | [在博客园中查看（推荐）](https://www.cnblogs.com/dengstar/p/18825708/solution-abc401f)

并不是很难的题，但赛时写的太麻烦了（4k，写了一个多小时），重新梳理一遍。

加上新的边 $(i, j)$ 之后，树的直径要么跨越 $(i, j)$，要么在原来的两棵树中。设 $d_1$，$d_2$ 分别表示两棵树的直径，$f_1(u)$ 和 $f_2(u)$ 分别表示两棵树中离 $u$ 最远的点到 $u$ 的距离，则加入新边后直径的长度为
$$
\max(d_1, d_2, f_1(i) + 1 + f_2(j))
$$
求出直径和 $f$ 数组后，考虑枚举第一棵树中的点 $i$ 统计答案。把 $f_2$ 排序，我们只需找到一个分界点 $x$，当 $j \ge x$ 时直径跨越两棵树，否则直径在原来的树中。二分以后求 $f_2$ 的一段区间和，用前缀和优化。

现在来看看怎么求出 $f$ 数组。我们有如下结论：在边权全为正的情况下，对树上的一点 $u$，离它最远的点必然是直径的一端。这个结论在用 bfs/dfs 求直径时会用到，这里我们反着来使用它：求出直径的两端 $(s, t)$ 后，比较 $\operatorname{dis}(s, u)$ 和 $\operatorname{dis}(t, u)$，较大者即为 $f(u)$。按理说这是一个很基础的结论，求直径的时候也会用到，但赛时我鬼使神差地忘了，所以最好还是重新证一下：

设树的直径为 $(s, t)$。离 $u$ 最远的点为 $v$，且 $v$ 到 $u$ 的距离**严格大于** $s$ 和 $t$ 到 $u$ 的距离。反证法，假设 $v$ 不是直径的一端，分三种情况讨论：

1. $u$ 在 $s \rightsquigarrow t$ 上：

   由于 $\operatorname{dis}(u, v) > \operatorname{dis}(u, t)$，所以把 $s \rightsquigarrow t$ 路径中的 $u \rightsquigarrow t$ 替换成 $u \rightsquigarrow v$，得到的 $s \rightsquigarrow v$ 的距离比直径长，矛盾。

2. $u$ 不在 $s \rightsquigarrow t$ 上，且 $s \rightsquigarrow t$ 与 $u \rightsquigarrow v$ 有重合的点：

   设 $x$ 是两条路径上第一个重合的点。根据假设，有 $\operatorname{dis}(x, v) > \operatorname{dis}(x, t)$，所以 $\operatorname{dis}(s, v) > \operatorname{dis}(s, t)$，矛盾。

3. $u$ 不在 $s \rightsquigarrow t$ 上，且 $s \rightsquigarrow t$ 与 $u \rightsquigarrow v$ 没有重合的点：

   考虑 $u \rightsquigarrow t$ 这条路径，设这条路径与 $u \rightsquigarrow v$ 最后一个重合的点为 $x$，与 $s \rightsquigarrow t$ 第一个重合的点为 $y$。那么 $\operatorname{dis}(x, v) > \operatorname{dis}(x, t)$，因此 $\operatorname{dis}(x, v) > \operatorname{dis}(y, t)$，进而 $\operatorname{dis}(y, v) > \operatorname{dis}(y, t)$（这都是建立在边权为正的基础上），最终可以推出 $\operatorname{dis}(s, v) > \operatorname{dis}(s, t)$，矛盾。

![](https://cdn.luogu.com.cn/upload/image_hosting/jh95dflw.png)


有了这个结论之后，就可以在求直径的时候同时求出 $f$。[代码](https://atcoder.jp/contests/abc401/submissions/64848355)（参考了 jiangly 的写法）

但即使不知道这个结论，也可以求出 $f$ 数组。这是我赛时的写法，比较难写，仅供参考：

换根 dp。设 $g(u)$ 表示 $u$ 子树的高度，dp 求出。设 $r$ 为根节点，则 $g(r) = f(r)$。然后换根。由于转移方程涉及到 $\max$，而 $\max$ 不可逆，所以换根时不能简单地”减去“贡献，而枚举所有子节点重新求一遍，时间复杂度会退化成 $O(n^2)$。解决方法也很简单：预处理子节点高度的最大值、次大值和最大值数量，分类讨论删去的子节点是不是最大值即可。我的代码用了 `multiset`，时间复杂度多了一个 $\log$，但其实没有必要。[代码](https://atcoder.jp/contests/abc401/submissions/64791673)

---

