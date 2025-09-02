# New Year Santa Network

## 题目描述

一个 $n$ 个节点的树上进行 $q$ 次操作，每次操作将第 $r$ 条边的长度修改成 $w$。

用 $d(x,y)$ 表示从点 $x$ 到 $y$ 的距离。

在树上等概率选取三个点 $c_1,c_2,c_3$ ，求在每次操作后 $d(c_1,c_2)+d(c_1,c_3)+d(c_2,c_3)$ 的期望值。

## 样例 #1

### 输入

```
3
2 3 5
1 3 3
5
1 4
2 2
1 2
2 1
1 1
```

### 输出

```
14.0000000000
12.0000000000
8.0000000000
6.0000000000
4.0000000000
```

## 样例 #2

### 输入

```
6
1 5 3
5 3 2
6 1 7
1 4 4
5 2 3
5
1 2
2 1
3 5
4 1
5 2
```

### 输出

```
19.6000000000
18.6000000000
16.6000000000
13.6000000000
12.6000000000
```

# 题解

## 作者：hs_black (赞：10)

考虑每条边的贡献，一条边的贡献就是它成为一条路径上的边的次数乘上它的权值

对于边(x, y)， 不经过此边的情况下， 设x所在的连通块大小为sx， y所在的连通块大小为sy

那么在一个连通块中选两个点， 另一个连通块选一个点的方案数就是路径条数

所以一条边的贡献 = $(C_{sx}^2 * sy + sy * C_{sy}^2) * val$

由于可能算重， 总条数除以6以后贡献也要乘二， 具体见代码

*talk is cheap, show me the code*

```cpp
#include<bits/stdc++.h>
#define ll long double
using namespace std;
template<typename T> inline void read(T &x)
{
	x=0;char c=getchar();bool flag=false;
	while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	if(flag)x=-x;
}

int n, m;
const int N = 200500;
int h[N], ne[N<<1], to[N<<1];
int w[N<<1], siz[N], tot;
inline void add(int x,int y,int z) {
	ne[++tot] = h[x], h[x] = tot;
	to[tot] = y, w[tot] = z;
}

int x[N], y[N], f[N], val[N];

void dfs(int x,int fa) {
	f[x] = fa, siz[x] = 1;
	for (int i = h[x]; i; i = ne[i]) {
		int y = to[i]; if (y == fa) continue;
		dfs(y, x); siz[x] += siz[y];
	}
}

ll work(int x,int y,int val) {
	if (f[y] == x) swap(x, y);
	ll sx = siz[x], sy = n - sx;
	ll ans = 0;
	ans = (sx * (sx-1) / 2 * sy) + (sx * sy * (sy - 1) / 2);
	return ans * val;
}

int main()
{
	read(n);
	ll tmp = (ll) n * (n-1) * (n-2) / 6;
	for (int i = 1;i < n; i++) {
		read(x[i]), read(y[i]), read(val[i]);
		add(x[i], y[i], val[i]);
		add(y[i], x[i], val[i]);
	}
	dfs(1, 0);
	ll ans = 0;
	for (int i = 1;i < n; i++) ans += 2 * work(x[i], y[i], val[i]);
	read(m);
	for (int i = 1;i <= m; i++) {
		int a, b; read(a), read(b);
		ans -= 2 *work(x[a], y[a], val[a]);
		val[a] = b;
		ans += 2 * work(x[a], y[a], val[a]);
		cout << fixed << setprecision(8) << ans / tmp << endl;
	}		
	return 0;
}

```



---

## 作者：Rt__ (赞：1)

[CF500D New Year Santa Network](https://www.luogu.com.cn/problem/CF500D)
## 题意简述
给定一颗大小为 $n$ 的树，在树上随机选择 $3$ 个点 $a$ $b$ $c$，并且记这种情况的花费为 $d_{a, b} + d_{b, c} + d_{a, c}$（$d_{i, j}$ 为 $i$ 到 $j$ 的距离），$q$ 次操作，每次将第 $r$ 条边的权值改为 $w$，求出每次操作后花费的期望值。
## 思路
$O(n^3)$ 枚举 $a$ $b$ $c$，$O(n)$ 算距离，$O(n^4)$ 显然是过不了的。我门考虑每条边对答案产生的影响。一条边要能对答案产生贡献，说明三个点一定在它的两边，也就是一边一个一边两个。设这条边一边有 $num_l$ 个点，另一边就有 $n - num_l$ 个点，因为三个点不一样，有顺序，所以这条边对答案产生贡献的种类数为：
$$
A_{num_{i,l}}^1 \times A_{n - num_{i,l}}^2 + A_{num_{i,l}}^2\times A_{n - num_{i,l}}^1\times 3
$$

每一种情况，这条边都会被经过两次，所以该边 $i$ 对总的费用和的贡献为：
$$
ans_i=(A_{num_{i,l}}^1 \times A_{n - num_{i,l}}^2 + A_{num_{i,l}}^2\times A_{n - num_{i,l}}^1)\times w_i \times 6
$$

那么总的答案就是：
$$
\frac {\sum_{i = 1}^{n}ans_i}{A^3_n}
$$
化简一下（为了不溢出）：
$$
\begin{aligned}
\frac {\sum_{i = 1}^{n}ans_i}{A^3_n} &= \sum_{i = 1}^{n} \frac {ans_i}{A^3_n}\\ 
&= \sum_{i = 1}^{n} \frac {(A_{num_{i,l}}^1 \times A_{n - num_{i,l}}^2 + A_{num_{i,l} }^2\times A_{n - num_{i,l}}^1)\times w_i \times 6}{A^3_n}\\
&= \sum_{i = 1}^{n} \frac {(C_{num_{i,l}}^1 \times C_{n - num_{i,l}}^2 \times 2 + C_{num_{i,l}}^2\times C_{n - num_{i,l}}^1 \times 2)\times w_i \times 6}{C^3_n \times 6}\\
&= \sum_{i = 1}^{n} \frac {(C_{num_{i,l}}^1 \times C_{n - num_{i,l}}^2  + C_{num_{i,l}}^2\times C_{n - num_{i,l}}^1 )\times w_i \times 2}{C^3_n}\\
&= 2\times \sum_{i = 1}^{n} \frac {(C_{num_{i,l}}^1 \times C_{n - num_{i,l}}^2  + C_{num_{i,l}}^2\times C_{n - num_{i,l}}^1 )\times w_i }{C^3_n}
\end{aligned}
$$
照着写代码就可以了。$O(n+q)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 100010;

int C[N][5];
void init(){
    C[0][0] = 1;
    for(int i = 1; i <= N - 10; i ++){
        C[i][0] = 1;
        if(i <= 3)C[i][i] = 3;
        int mid = 1;
        for(int j = 1; j <= 3; j ++){
            mid = mid * j;
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }
    return;
}
int h[N], e[N * 2], ne[N * 2], w[N * 2], idx;
void add(int a, int b, int c){
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;
    return;
}
int deep[N];
int siz[N];
void dfs(int u, int fa){
    deep[u] = deep[fa] + 1;
    siz[u] = 1;
    for(int i = h[u]; i != -1; i = ne[i]){
        int j = e[i];
        if(j == fa)continue;
        dfs(j, u);
        siz[u] += siz[j];
    }
    return;
}
double ans = 0;
int n;
void dfss(int u, int fa){
    for(int i = h[u]; i != -1; i = ne[i]){
        int j = e[i];
        if(j == fa)continue;
        dfss(j, u);
        int mid = deep[u] < deep[j] ? j : u;
        ans += (C[siz[mid]][1] * C[n - siz[mid]][2] + C[siz[mid]][2] * C[n - siz[mid]][1]) * w[i] * 1.0 / C[n][3];
    }
}
struct e{
    int u, v, w;
}edge[N];
signed main(){
    memset(h, -1, sizeof h);
    init();
    cin >> n;
    for(int i = 1; i < n; i ++){
        int u, v, w;
        cin >> u >> v >> w;
        edge[i] = {u, v, w};
        add(u, v, w);
        add(v, u, w);
    }
    dfs(1, 0);
    dfss(1, 0);
    int q;
    cin >> q;
    while(q --){
        int a, b;
        cin >> a >> b;
        int u = edge[a]. u, v = edge[a]. v;
        int mid = deep[u] < deep[v] ? v : u;
        ans -= (C[siz[mid]][1] * C[n - siz[mid]][2] + C[siz[mid]][2] * C[n - siz[mid]][1]) * (edge[a]. w - b) * 1.0 / C[n][3];
        edge[a]. w = b;
        printf("%.7lf \n", ans * 2.0);
    }
    return 0;
}
```

---

## 作者：dgdyrkst (赞：1)

## 思路
暴力枚举三个点显然不可做，我们考虑将期望拆成两个组合计数。

但还要维护修改边权的操作，于是可以将贡献拆到每一条边上统计。
## 实现
我们的思路显然很对，来考虑一下具体怎么实现。

拆成的两个组合计数分别是 __所有选点方案的边权之和__ 及 __选点的方案数__ 。

后者显然就是 $\dfrac{n(n-1)(n-2)}{6}$，考虑你选第一个点有 $n$ 种方案，选第二个不同点有 $(n-1)$ 种方案，选第三个不同点有 $(n-2)$ 种方案。

而任意排列会有 $6$ 种情况选到的三个点是一样的，所以再除以 $6$ 即可。

那么前者如何解决呢？

每条边的贡献就是它 __被算到的次数__ 乘上它的边权，所以我们只需要算出每条边会被所有情况算多少次就可以了。

对于任意一条边 $(x,y)$ ，我们约定 $x$ 的深度小于 $y$ 的深度，并且以 $y$ 为根的子树大小为 $siz$ 。

接下来分类讨论。

- 当三个点全部在 $y$ 的子树内或全部在 $y$ 的子树外时，这条边显然不会被经过。

- 当有且仅有两个点在 $y$ 的子树内时，有 $\dfrac{siz(siz-1)(n-siz)}{2}$ 种方案。

- 当有且仅有一个点在 $y$ 的子树内时，有 $\dfrac{siz(n-siz)(n-siz-1)}{2}$ 种方案。

于是总方案数就是 $\dfrac{siz(siz-1)(n-siz)}{2}+\dfrac{siz(n-siz)(n-siz-1)}{2}$。

但是对任意方案，会发现这条边会被经过两遍，记总方案数为 $cnt$，边权为 $w$，则这条边的贡献就是 $2 \cdot cnt \cdot w$。

所有边的贡献总和记为 $sum$，则答案就是 $\dfrac{6 \cdot sum}{n(n-1)(n-2)}$，即总贡献除以总方案数得到期望。

最后，对于修改边权，我们只要将原来这条边的贡献减去，并加上新的贡献就可以了，因为 $cnt$ 是不变的，只有 $w$ 会变，所以很好处理。
## 代码
以下为代码参考。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long double
typedef long long ll;
const ll N=1e5+5;
int d,w[N<<1],siz[N],ans,cnt[N<<1];
ll n,q,a,b,tot=1,head[N],ne[N<<1],to[N<<1];
inline void add()
{
	tot++;
	ne[tot]=head[a],head[a]=tot;
	to[tot]=b,w[tot]=d; 
}
void dfs(ll now,ll fa)
{
	siz[now]=1;
	for (ll i=head[now];i;i=ne[i])
	{
		if (i==fa)continue;
		dfs(to[i],i^1);
		siz[now]+=siz[to[i]];
	}
	cnt[fa]=cnt[fa^1]=siz[now]*(siz[now]-1)*(n-siz[now])+siz[now]*(n-siz[now])*(n-siz[now]-1);
	if (fa)ans+=cnt[fa]*w[fa];
}
signed main()
{
	cin >> n;
	for (ll i=1;i<n;i++)
	{
		cin >> a >> b >> d;
		add(),swap(a,b),add();
	}
	dfs(1,0);
	cin >> q;
	while (q--)
	{
		cin >> a >> d;
		a<<=1;
		ans-=cnt[a]*w[a];
		w[a]=d;
		ans+=cnt[a]*d;
		printf("%.10Lf\n",(long double)ans*6/n/(n-1)/(n-2));
	}
	return 0;
}
```


---

## 作者：Arcturus1350 (赞：0)

这道题首先是要看看该如何化简，先把三元组化成二元组。

之后统计经过某条边的 次数$*$权值  的和。

最后除以总基数 $tot$


其中，每条边被计算的次数为 子树的点数$*$非子树的点数 （自己想想）

然后就没了。

### ps:一定要注意$n$个节点的树有$n-1$条边，本宝宝调了一下午+一晚上。。。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct data{int v;int value;int nxt;}edge[200010];
int alist[100010];int cnt;
void add(int u,int v,int value)
{ 
    edge[++cnt].nxt=alist[u];
    edge[cnt].v=v;
    edge[cnt].value=value;
    alist[u]=cnt;
}

int len[100010];
int num[100010];
int n,m;
int in[100010];int out[100010];

double ans;double tot;
void dfs(int x,int f)
{
    num[x]=1;
    for(int i=alist[x];i!=-1;i=edge[i].nxt)
    {
        int v=edge[i].v;
        if(v==f) continue;
        dfs(v,x);
        num[x]+=num[v];
        ans+=(double)edge[i].value*num[v]*(n-num[v])/tot;
    }
}

int u,v,value;
int main()
{
    scanf("%d",&n);
    memset(alist,-1,sizeof(alist));
    for(int i=1;i<n;i++)
    {
        scanf("%d%d%d",&u,&v,&value);
        in[i]=u;
        out[i]=v;
        len[i]=value;
        add(u,v,value);
        add(v,u,value);
    }
    tot=(double)n*(n-1)/6.0;
    dfs(1,-1);
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        value=min(num[in[u]],num[out[u]]);
        ans-=(double)(len[u]-v)*value*(n-value)/tot;
        len[u]=v;
        printf("%.8lf\n",ans);
    }
    return 0;
}
```

---

