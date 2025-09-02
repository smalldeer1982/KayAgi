# Bandit in a City

## 题目描述

Bandits appeared in the city! One of them is trying to catch as many citizens as he can.

The city consists of $ n $ squares connected by $ n-1 $ roads in such a way that it is possible to reach any square from any other square. The square number $ 1 $ is the main square.

After Sunday walk all the roads were changed to one-way roads in such a way that it is possible to reach any square from the main square.

At the moment when the bandit appeared on the main square there were $ a_i $ citizens on the $ i $ -th square. Now the following process will begin. First, each citizen that is currently on a square with some outgoing one-way roads chooses one of such roads and moves along it to another square. Then the bandit chooses one of the one-way roads outgoing from the square he is located and moves along it. The process is repeated until the bandit is located on a square with no outgoing roads. The bandit catches all the citizens on that square.

The bandit wants to catch as many citizens as possible; the citizens want to minimize the number of caught people. The bandit and the citizens know positions of all citizens at any time, the citizens can cooperate. If both sides act optimally, how many citizens will be caught?

## 说明/提示

In the first example the citizens on the square $ 1 $ can split into two groups $ 2 + 1 $ , so that the second and on the third squares will have $ 3 $ citizens each.

In the second example no matter how citizens act the bandit can catch at least $ 4 $ citizens.

## 样例 #1

### 输入

```
3
1 1
3 1 2```

### 输出

```
3```

## 样例 #2

### 输入

```
3
1 1
3 1 3```

### 输出

```
4```

# 题解

## 作者：tommymio (赞：10)

暴力二分+贪心把这题叉了，不是很懂为啥要用 $\text{DP}$（大雾

令最大值最小，肯定是二分一个上界，然后 $\mathrm{check}$。现在我们需要考虑 $\mathrm{check(mid)}$ 怎么写。

我们称一棵子树 $x$ 内的所有叶子节点 $y$ 的 $\sum mid-a_y$ 为这棵子树的容量，记作 $incf_x$。一棵子树 $x$ 内的所有非叶子节点 $y$ 的 $\sum a_y$ 为这颗子树的流向其叶子节点的流量，记作 $flow_x$。显然当 $\forall x$，都有 $flow_x\leq incf_x$ 时，必然存在一种解使得最大值不超过上界。

交上去，发现 $\text{Wrong Answer on Test 5}$，什么情况呢？仔细观察我们发现，$mid$ 最大可以达到 $2\times 10^{14}$，那么 $\max\{incf_x\}$ 可能达到 $4\times 10^{19}$，直接爆 $\text{long long}$。

优化一下：将上界 $r$ 调为 $\sum\limits_{x=1}^n a_x$；将可能溢出的数据全部换成 $\text{unsigned long long}$ 来存储；合并一些运算，令中间运算值尽可能的小；对于 $\text{ull}$ 运算过程中可能出现负数的情况进行特判。这样就可以了。

吐槽一句：其实我感觉毒瘤出题人把数据出成这个鬼样子，就是想卡二分做法的。

但是二分的做法只是在溢出上被卡了，正确性并没有问题，所以可以考虑特判一些情况，调大数据类型的极限范围来保证 $\text{AC}$，考场上确实没有时间来想一些看上去更为华丽的正解，因此我觉得这些技巧是极为实用的。

```cpp
#include<cstdio>
typedef unsigned long long ull;
typedef long long ll;
int n,flag=0,cnt=0;
ull sum[200005],a[200005];
int h[200005],to[200005],ver[200005];
inline int read() {
    register int x=0,f=1;register char s=getchar();
    while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
    while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
    return x*f;
}
inline ll max(const ll &x,const ll &y) {return x>y? x:y;}
inline void add(int x,int y) {to[++cnt]=y;ver[cnt]=h[x];h[x]=cnt;}
inline void dfs2(int x,ll mid) {
    sum[x]=0; 
    int tot=0;
    for(register int i=h[x];i;i=ver[i]) {
        dfs2(to[i],mid); ++tot;
        sum[x]+=sum[to[i]];
    }
    if(!tot) {if(mid<a[x]) {flag=1;} else {sum[x]=mid-a[x];}}
    else {if(sum[x]<a[x]) {flag=1;} else {sum[x]-=a[x];}}
}
inline bool check(ll mid) {
    flag=0; 
    dfs2(1,mid);
    return 1-flag; 
}
int main() {
    ll l=0,r=0,res=0; n=read();
    for(register int i=2;i<=n;++i) {int fa=read();add(fa,i);}
    for(register int i=1;i<=n;++i) {a[i]=read(); r+=a[i];}
    while(l<=r) {
        ll mid=l+r>>1;
        if(check(mid)) r=mid-1,res=mid;
        else l=mid+1;
    }
    printf("%lld\n",res);
    return 0;
}
```

---

## 作者：Sqrtyz (赞：10)

可以当成一道树形 DP。

### 简化题意

+ 给定一棵树（$1$ 为根），点上有权。对于所有非叶子节点，把它的权值分给其儿子们（不一定要均分）。一直这样分下去，直到所有点权分到了叶子节点。

+ 最小化所有叶子节点中的最大权值。$n \leq 2 \times 10^5$。

### 解题

令 $f_u$ 表示以 $u$ 为根的子树中最大叶子节点的的最小值。

假如我们先不瓜分这个 $u$ 节点的权值，一定有 $f_u = \max \limits_{v \in son(u)} f_v$。

设 $u$ 的子树的权值和为 $siz_u$，$u$ 的子树中叶子节点共有 $leaf_u$ 个。理想状态下（均分），以 $u$ 为根的子树中最大叶子节点的的最小值为 $\lceil\frac{siz_u}{leaf_u}\rceil$。

然而理想状态不一定能达到。如果 $\max \limits_{v \in son(u)} f_v>\lceil\frac{siz_u}{leaf_u}\rceil$ 的话，$f_u$ 还是只能取 $\max \limits_{v \in son(u)} f_v$。

反之我们就理想地分配 $u$ 的权值（均分），即 $f_u=\lceil\frac{siz_u}{leaf_u}\rceil$。

（其实就是两者取 $\max$）

### 代码

```cpp
int n;
LL val[Maxn], siz[Maxn], f[Maxn], leaf[Maxn];

struct Edge {
    int next, to;
}
edge[Maxn];
int head[Maxn], edge_num;

void add_edge(int from, int to) {
    edge[++edge_num].next = head[from];
    edge[edge_num].to = to;
    head[from] = edge_num;
}

void dfs(int u) {
    bool flag = 1;
    for(int i = head[u]; i; i = edge[i].next) dfs(edge[i].to), flag = 0;
    if(flag) leaf[u] = 1; siz[u] = val[u];
    for(int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        f[u] = max(f[v], f[u]);
        siz[u] += siz[v]; leaf[u] += leaf[v];
    }
    f[u] = max(f[u], (siz[u] + leaf[u] - 1) / leaf[u]); // 注意向上取整
}

int main() {
    n = read();
    for(int i = 2; i <= n; ++i) {
        int fa = read();
        add_edge(fa, i);
    }
    for(int i = 1; i <= n; ++i) val[i] = read();
    dfs(1);
    cout << f[1] << endl;
    return 0;
}
```

---

## 作者：灵乌路空 (赞：3)

场上乱搞了个假 DP 吃了两发= =   

## 简述

原题面：[Codeforces](https://codeforces.com/contest/1436/problem/D)。

>给定一棵 $n$ 个节点的有根树，根为 $1$，第 $i$ 个节点上有 $a_i$ 个人。  
>每个人可以往任意子节点走，直到走到叶节点，求最后人最多的叶节点的最少人数。  
>$2\le n\le 2\times 10^5$，$0\le a_i\le 10^9$。  
>1S，256MB

## 分析

知识点：树形 DP

设 $\operatorname{sum}_{u}$ 表示 $u$ 子树中所有节点的人数之和，$\operatorname{leaf}_u$ 表示 $u$ 子树中叶节点的个数。  
首先考虑最理想状态，对于节点 $u$，若它子树中的所有人都能均匀地散布在所有叶节点中，则显然该子树中 人最多的叶节点的人数为 $\left\lceil \frac{\operatorname{sum}_u}{\operatorname{leaf}_u} \right\rceil$。  

但一般无法达到理想状态，设 $f_{u}$ 表示以 $u$ 为根的子树中人最多的叶节点的人数。对于节点 $u$ 的某儿子 $v$，显然，存在 $f_{v} > \left\lceil \frac{\operatorname{sum}_u}{\operatorname{leaf}_u} \right\rceil$ 时无法均分。  
反之，当 $\forall v\in son(u),\ f_v\le \left\lceil \frac{\operatorname{sum}_u}{\operatorname{leaf}_u} \right\rceil$ 时，可以将 $a_u$ 按一定方案分配到各叶节点，形成均匀散布的形式。  

对于所有叶节点 $u$，初始化 $\operatorname{leaf}_u = 1$，则有显然的状态转移方程：  

$$\begin{aligned}
  \operatorname{sum}_u &= a_u + \sum_{v\in son(u)} \operatorname{sum}_v\\
  \operatorname{leaf}_u &= \sum_{v\in son(u)} \operatorname{leaf}_v\\
  f_{u} &= \max\left\{ \max_{v\in son(u)}\{f_v\},\  \left\lceil \frac{\operatorname{sum}_u}{\operatorname{leaf}_u} \right\rceil\right\}
\end{aligned}$$

答案即为 $f_1$。  

算法总时间复杂度 $O(n)$。  

还有种被卡 `ull` 的暴力二分答案，可以参考其他题解。

## 实现


```cpp
//知识点：树形DP 
/*
By:Luckyblock
*/
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#define LL long long
const int kN = 2e5 + 10;
//=============================================================
int n, e_num, a[kN], head[kN], v[kN], ne[kN];
LL leaf[kN], sum[kN], f[kN];
bool fa[kN];
//=============================================================
inline int read() {
  int f = 1, w = 0;
  char ch = getchar();
  for (; !isdigit(ch); ch = getchar())
    if (ch == '-') f = -1;
  for (; isdigit(ch); ch = getchar()) {
    w = (w << 3) + (w << 1) + (ch ^ '0');
  }
  return f * w;
}
void Chkmax(LL &fir_, LL sec_) {
  if (sec_ > fir_) fir_ = sec_;
}
void Chkmin(LL &fir_, LL sec_) {
  if (sec_ < fir_) fir_ = sec_;
}
void AddEdge(int u_, int v_) {
  v[++ e_num] = v_;
  ne[e_num] = head[u_];
  head[u_] = e_num;
}
void Dfs(int u_) {
  if (! fa[u_]) leaf[u_] = 1;
  sum[u_] = a[u_];
  
  for (int i = head[u_]; i; i = ne[i]) {
    int v_ = v[i];
    Dfs(v_);
    Chkmax(f[u_], f[v_]);
    sum[u_] += sum[v_];
    leaf[u_] += leaf[v_];
  }
  Chkmax(f[u_], ceil(1.0 * sum[u_] / leaf[u_]));
}
//=============================================================
int main() {
  n = read();
  for (int v_ = 2; v_ <= n; ++ v_) {
    int u_ = read();
    AddEdge(u_, v_);
    fa[u_] = true;
  }
  for (int i = 1; i <= n; ++ i) a[i] = read();
  Dfs(1);
  printf("%lld\n", f[1]);
  return 0;
}
```

---

## 作者：haooo (赞：2)

强盗想抓到**最多的市民**，而市民希望被强盗抓到的**最少**。

显然需要让市民**尽量的平均**。但有时某个叶子节点可能**值太大**，无法被平均。

因此需要在$maxn[son[x]]$与$sum[x]$在叶子节点的**平均值**中取**最大值**。

可以维护以下数组：

- $ maxn[x]$ ：为以$ x $为根的子树的叶子节点**最大值**
- $ sum[x] $ ：为以$ x $为根的子树的**权值和**
- $ cnt[x] $ ：为以$ x $为根的子树的**叶子节点数量**

可以很容易得到这三个转移方程：

 $ sum[x]=\sum_{y=son[x]} sum[y]+ dat[x] $
 
 $ cnt[x] = \sum_{y=son[x]} cnt[y] $
 
 $ maxn[x] = \max(maxn[son[x]],\lceil sum[x]/cnt[x] \rceil )$

最后显然$maxn[1]$就是答案。

这样就可以愉快的解决本题了~~




 **记得开long long ！（~~考试那天晚上上因为没开longlong送了100分）~~**

AC代码 ( ~~不要抄代码，有坑~~：

```cpp
#include<bits/stdc++.h>
#define ll int
using namespace std;
const int MAXN=1e5+5;
int head[MAXN],nex[MAXN];
int ver[MAXN];
int tot;
int vis[MAXN];
ll maxn[MAXN],sum[MAXN],cnt[MAXN];
inline void add(int x,int y){
    nex[++tot]=head[x];
    head[x]=tot;
    ver[tot]=y;
}
inline void dfs(int x){
    for(int i=head[x];i;i=nex[i]){
        int y=ver[i];
        dfs(y);
        cnt[x]+=cnt[y];
        maxn[x]=max(maxn[x],maxn[y]);
        sum[x]+=sum[y];
    }
    maxn[x]=max(maxn[x],(sum[x]+cnt[x]-1)/cnt[x]);
}
int n;
int main(){
    scanf("%d",&n);
    for(int y=2;y<=n;y++){
        int x;scanf("%d",&x);
        add(x,y);
        vis[x]=1;
    }
    for(int i=1;i<=n;i++)   if(!vis[i]) cnt[i]=1ll;
    for(int i=1;i<=n;i++)   scanf("%lld",&sum[i]);
    dfs(1);
    printf("%lld",maxn[1]);
    return 0;
}

```


---

## 作者：wzy2021 (赞：1)

我们来看一下此题：

看到最大值最小，很容易想到二分答案，设二分的值为 $x$

再设 $sum_i$ 是 $i$ 的子树中 $a_j$ 的和，$l_i$ 表示 $i$ 的子树中叶子结点的个数，

那么我们假设在点 $u$ 上，且 $u$ 的子树除了 $u$ 以外全部分配完成，那么 $u$ 上的人肯定会优先去人比较少的叶子节点，

那么如果目前合法，$u$ 不合法当且仅当 $x < \left\lceil\dfrac{sum_{u}}{l_u}\right\rceil$，

时间复杂度：$O(n log n)$

其实可以不用二分，直接取 $\left\lceil\dfrac{sum_{u}}{l_u}\right\rceil$ 的最大值即可

时间复杂度：$O(n)$



------------


```cpp
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
#define int long long // 别忘开 long long

const int maxn = 2e5 + 10;
struct node {
    int to, nxt;
} edge[maxn << 1];
int cnt, head[maxn];
int ans = 0, a[maxn], l[maxn], sum[maxn];

void add (int u, int v) { // 建边
    cnt ++;
    edge[cnt].to = v;
    edge[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs (int u, int f) {
    sum[u] = a[u];
    int son = 0;
    for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        if (v == f) continue;
        dfs (v, u);
        son ++;
        l[u] += l[v]; sum[u] += sum[v];
    }
    if (son == 0) l[u] = 1;
    int res = sum[u] / l[u];
    if (res * l[u] < sum[u]) res ++; 
    ans = max (ans, res); // 取最大值
}

signed main() {
    int n; scanf ("%lld", &n);
    for (int i = 2; i <= n; ++i) {
        int x; scanf ("%lld", &x);
        add (x, i); add (i, x);
    }
    for (int i = 1; i <= n; ++i) scanf ("%lld", &a[i]);
    dfs (1, 0);
    printf ("%lld", ans);
    return 0;
}
```


---

## 作者：_edge_ (赞：0)

提供一种贪心的想法。

首先，对于这道题目，最大值最小，二分答案没跑了。

考虑如何进行 check，我们发现这个树上的好像有点不太好搞？

然后考虑利用 dfs 序把它拍到序列上，我们只把叶子给拿出来，对于每一个点它所产生的贡献是他所掌管的一段区间的叶子。

然后问题就转化成了，给定一个序列，每个序列有一个上限，若干个区间，区间要填总和为 $x$ 填到这个序列里面。

这个问题很简单的一个想法就是把区间按右端点进行排序，然后从左往右填。

对于正确性可以感性理解一下，右端点升序，那么就是说交换相邻两个从左往右有可能把前面那个给占用掉。

当然，这样直接做是 $O(n^2 \log n)$ 的，因此我们需要一种东西去维护从某个点开始第一个没有到达上限的，同时支持删除，这个东西可以利用并查集向右连边很好实现。

总时间复杂度 $O(n \log^2 n)$，有个 $\log$ 是并查集的，当然也可以利用优化做到 $\alpha(n)$。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define int long long 
using namespace std;
const int INF=2e5+5;
struct _node_edge{
	int to_,next_;
}edge[INF<<1];
int n,head[INF],tot,dfn[INF],fl[INF],pre[INF],a[INF],sz[INF];
void add_edge(int x,int y) {
	edge[++tot]=(_node_edge){y,head[x]};
	head[x]=tot;return ;
}
void DFS(int x,int fa) {
	dfn[0]++;dfn[dfn[0]]=x;pre[x]=dfn[0];sz[x]=1;
	for (int i=head[x];i;i=edge[i].next_) {
		int v=edge[i].to_;
		if (v==fa) continue;
		DFS(v,x);fl[x]=1;sz[x]+=sz[v];
	}
}
struct _node_data{
	int l,r,x;
}b[INF];
int p[INF],p1[INF],l[INF],r[INF],vis[INF],c[INF],fa_set[INF];
bool cmp(_node_data xx,_node_data yy) {
	return xx.r<yy.r;
}
int find_set(int x) {return fa_set[x]==x?x:fa_set[x]=find_set(fa_set[x]);}
bool check(int xx) {
	for (int i=1;i<=n;i++) 
		fa_set[i]=i,vis[i]=xx;
	for (int i=1;i<=n;i++) c[i]=b[i].x;
	int fl=1;
	for (int i=1;i<=n;i++) {
		for (int j=b[i].l;j<=b[i].r;j=find_set(j)) {
			if (vis[j]>=b[i].x) {vis[j]-=b[i].x;b[i].x=0;break;}
			else b[i].x-=vis[j],vis[j]=0,fa_set[j]=j+1; 
		}
//		cout<<b[i].x<<" "<<b[i].l<<" "<<b[i].r<<" ??\n";
		if (!b[i].x) ;
		else fl=0;
	}
	for (int i=1;i<=n;i++) b[i].x=c[i];
	return fl;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=2;i<=n;i++) {
		int fa=0;cin>>fa;
		add_edge(fa,i);add_edge(i,fa);
	}
	DFS(1,0);
	for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=1;i<=dfn[0];i++)
		if (!fl[dfn[i]]) p[++p[0]]=dfn[i],p1[p[0]]=i;
	for (int i=1;i<=n;i++) {
		int ll=pre[i],rr=pre[i]+sz[i]-1;
		b[i].l=lower_bound(p1+1,p1+1+p[0],ll)-p1;
		b[i].r=upper_bound(p1+1,p1+1+p[0],rr)-p1-1;
		b[i].x=a[i];
	}
	sort(b+1,b+1+n,cmp);
//	cout<<check(100)<<" ?\n";
	int l=0,r=1e18,ans=-1;
	while (l<=r) {
		int Mid=(l+r)>>1;
		if (check(Mid)) r=(ans=Mid)-1;
		else l=Mid+1;
	}
	cout<<ans<<"\n";
	return 0; 
}
```


---

## 作者：RyexAwl (赞：0)

考虑所有人都在根节点的情况，那么等价于把$Sum$件物品分成$laefcnt$件，$\max_{u\in L}(cnt[u])$的最小值为$\lceil\frac{Sum}{laefcnt}\rceil$。

那么我们的目标就很明显了——令所有叶子节点最终的人数尽量相等。

类似于树形$\text{DP}$，我们去考虑每个以点$u\in T$为根的子树内的情况。

我们用$f[u]$表示以$u$为根的子树内，所有节点内的人均走到叶子节点，人最多的叶子节点最少的人数。

如果$a[u]=0$，那么其等价于在以$v\in son(u)$的子树内，所有节点内的人均走到叶子节点，人最多的叶子节点最少的人数,那么$f[u]=\max\limits_{v\in son(u)} (f[v])$。

接下来我们来考虑$a[u]\not = 0$的情况。

一种理想的情况是$f[u]=\lceil \frac{sum_u}{leafcnt_u}\rceil$。

但可惜的是这种情况并不总能出现。

接下来我们重点来讨论一下这种情况出现的条件。

我们发现$f[u]\ge \max\limits_{v\in son(u)}(f[v])$。

那么可以推出$f[u]=\lceil \frac{sum_u}{leafcnt_u}\rceil$的必要条件为$\lceil \frac{sum_u}{leafcnt_u}\rceil \ge \max\limits_{v\in son(u)}(f[v])$。

并且我们可以发现，$f[u]=\lceil \frac{sum_u}{leafcnt_u}\rceil$的充分条件为$\lceil \frac{sum_u}{leafcnt_u}\rceil \ge \max\limits_{v\in son(u)}(f[v])$ 。

那么我们只要证明充分性即可。

并且我们可以发现，当$\lceil \frac{sum_u}{leafcnt_u}\rceil < \max\limits_{v\in son(u)}(f[v])$ 时，$f[u]=\max\limits_{v\in son(u)}(f[v])$。

因此我们可以得出$ans=\max\limits_{u\in T}(\lceil \frac{sum_u}{leafcnt_u}\rceil)$。

掌握一种新的做法总是好的。

接下来我们来考虑二分。

其单调性比较显然，我们来重点讨论一下$\text{check}$。

类似于上一种做法，我们依然从$\text{DP}$的角度来分析。

令$f[u]$为以$u$为根的子树内是否存在一种方案使得最终每个叶子节点的人数均不超过$x$。

若$a[u]=0$,$f[u]=[\sum\limits_{v\in son(u)}f[v]=cntson_u]$。

接下来考虑$a[u]\not=0$的情况。

我们发现$f[u]=1$的必要条件为$cntleaf_u\times x \ge sum_u$

充分性的证明也比较简单，接下来来讨论一下有意思的东西 :)

$\frac{sum_u}{cntleaf_u}\le x\Rightarrow x\ge\lceil \frac{sum_u}{leafcnt_u}\rceil$

那么$\min(x)=\lceil \frac{sum_u}{leafcnt_u}\rceil$

和我们上一种做法所推出的结论一致！ ~~算法大一统~~。 

总结一下，即$f[u]=1$的充分必要条件即

$cntleaf_u\times x \ge sum_u$且$\sum\limits_{v\in son(u)}f[v]=cntson_u$

那么$f[1]=1$当且仅当$\forall u\in T$满足$cntleaf_u\times x \ge sum_u$ 。

```cpp
#include <iostream>

namespace wxy{
const int N = 2e5 + 5;
#define int long long
int size[N],sum[N],a[N],n;
int head[N],edge[N << 1],cnt[N],fail[N << 1],tot;
bool vis[N];
inline void add(int x,int y){
    edge[++tot] = y;
    fail[tot] = head[x];
    head[x] = tot;
}
inline int ceil(int n,int k){
    if (n % k == 0) return n / k;
    else return n / k + 1;
}
inline void dfs(int x){
    vis[x] = true; sum[x] = a[x];
    for (int i = head[x];i;i = fail[i]){
        int v = edge[i];
        if (vis[v]) continue;
        cnt[x]++;
    }
    if (cnt[x] == 0){size[x] = 1; return;}
    for (int i = head[x];i;i = fail[i]){
        int v = edge[i];
        if (vis[v]) continue;
        dfs(v); size[x] += size[v]; sum[x] += sum[v];
    }
}
inline void main(){
    tot = 0; std::cin >> n;
    for (int i = 2; i <= n; i++){
        int in; std::cin >> in;
        add(i,in); add(in,i);
    }
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    dfs(1); int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = std::max(ans,ceil(sum[i],size[i]));
    std::cout << ans;
}
}signed main(){wxy::main(); return 0;}
```


---

## 作者：cirnovsky (赞：0)

## 题意简述

给定以 $1$ 为根的 $n$ 个节点的一棵树，每个节点上有 $a_{i}$ 个人，每个人可以选择往任意子节点走，直到走到叶子节点为止，问最后人最多的叶子节点最少有多少人。

## 题解

哇你们都这么能 DP 的吗。

一篇二分的题解。

先考虑二分答案，设当前二分的答案为 $x$。

考虑如何判断。

我们枚举每一个叶节点（这里设 $\text{subtree}(u)$ 中的叶节点集合为 $V_{l}(u)$，非叶节点集合为 $V_{f}(u)$），设当前枚举到了 $u$，那么 $x$ 这个值可行的条件为：

1. $a_{u}$ 本身 $\le x$。
2. 对于 $\forall i,i'\in V_{l}(i),i''\in V_{f}(i)$，满足 $\sum a_{i'}+a_{i''}\le x\times|V_{l}(i)|$。

那么我们就可以二分了。

注意一下变量类型（小坑）。

$\text{check}$ 函数有一个乘法（会爆 `long long`），可以转化为除法，用 `double`。

最后预处理一下需要的东西即可。

```cpp
#include<cstdio>
int n,cntot,val[200005],begin[200005],to[200005],nxt[200005],onesiz[200005],anosiz[200005];
unsigned long long subcost[200005];
void read(int &hhh)
{
	int x=0;
	char c=getchar();
	while((c<'0'||c>'9')&&c^'-')	c=getchar();
	if(c^'-')	x=c^'0';
	char d=getchar();
	while(d>='0'&&d<='9')
	{
		x=(x<<3)+(x<<1)+(d^'0');
		d=getchar();
	}
	if(c^'-')	hhh=x;
	else	hhh=-x;
}
void writing(unsigned long long x)
{
	if(!x)	return;
	if(x>9)	writing(x/10);
	putchar((x%10)^'0');
}
void write(unsigned long long x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	else if(!x)
	{
		putchar('0');
		putchar('\n');
		return;
	}
	writing(x);
	putchar('\n');
}
void dfs(int u)
{
	onesiz[u]=1;
	if(!begin[u])	anosiz[u]=1;
	subcost[u]=val[u];
	for(int i=begin[u];i;i=nxt[i])
	{
		int v=to[i];
		dfs(v);
		onesiz[u]+=onesiz[v];
		anosiz[u]+=anosiz[v];
		subcost[u]+=subcost[v];
	}
}
bool check(unsigned long long cur)
{
	for(int i=1;i<=n;++i)
	{
		double one=subcost[i],ano=anosiz[i];
		if(one/ano>(double)cur)	return 0;
	}
	return 1;
}
long long search(long long l,long long r)
{
	long long res=0;
	while(l<=r)
	{
		long long mid=(l+r)>>1;
		if(check(mid))
		{
			r=mid-1;
			res=mid;
		}
		else	l=mid+1;
	}
	return res;
}
int main()
{
	read(n);
	for(int i=2;i<=n;++i)
	{
		int f;
		read(f);
		to[++cntot]=i;
		nxt[cntot]=begin[f];
		begin[f]=cntot;
	}
	for(int i=1;i<=n;++i)	read(val[i]);
	dfs(1);
	write(search(0,2e5*1e9));
	return 0;
}
```

---

## 作者：木木！ (赞：0)

DP 思路和楼下各位大佬一样（存下目前最大值和与均匀状态的差值），我只是想说这题不需要 DFS。

因为给的顺序就是拓扑序的倒序，直接从后往前扫一遍就行了。

附 AC 代码：

```cpp
#include <cstdio>
using namespace std;

int getint()
{
	char ch;
	while((ch=getchar()) < '!') ;
	int x = ch^'0';
	while((ch=getchar()) > '!') x = (x*10)+(ch^'0');
	return x;
}

typedef long long lld;

int fa[200005];
int ai[200005];
lld ri[200005];
int siz[200005];
lld maxi[200005];

int main()
{
	const int n = getint();
	for(int i=2; i<=n; ++i)
	{
		fa[i] = getint();
	}
	for(int i=1; i<=n; ++i)
	{
		ai[i] = getint();
	}
	
	for(int i=n; i>=1; --i)
	{
		if(!siz[i])
		{
			ri[i] = 0;
			siz[i] = 1;
			maxi[i] = ai[i];
		}
		else
		{
			if(ri[i] >= ai[i])
			{
				ri[i] -= ai[i];
			}
			else
			{
				maxi[i] += (ai[i]-ri[i]-1)/siz[i] + 1;
				ri[i] = (siz[i]-1) - (ai[i]-ri[i]-1)%siz[i];
			}
		}
		if(maxi[fa[i]] == maxi[i])
		{
			ri[fa[i]] += ri[i];
		}
		else if(maxi[fa[i]] > maxi[i])
		{
			ri[fa[i]] += (maxi[fa[i]]-maxi[i])*siz[i] + ri[i];
		}
		else
		{
			ri[fa[i]] += (maxi[i]-maxi[fa[i]])*siz[fa[i]] + ri[i];
			maxi[fa[i]] = maxi[i];
		}
		siz[fa[i]] += siz[i];
	}
	
	printf("%lld\n",maxi[1]);
}
```

---

## 作者：hs_wfz_orz (赞：0)

这里给出一个比较暴力的做法

先简化一下题意，因为强盗要选最终最多市民的点，所以我们想要最终最多市民的点尽可能小，这样就成了一个二分答案的问题

对于当前的一个二分值$x$，每找到一个出度为0的点，就不断向上找父亲节点和它合并，直到合并到$x$，并且合并过程中要不断修改每个点的市民个数，再合并就不符合要求。假如最后还有节点的市民还存在，说明不合法

这样显然会超时，考虑如何优化

我们发现，假如向上合并的过程中的市民个数是$0$，那么这个点显然不会对当前点产生影响，只和有市民的点有影响，考虑并查集优化

对于$f_x$，代表$x$这个点向上合并时的第一个非0的节点编号，同时，对于每一个节点，假如能直接合并到这个点，那么继续合并，具体见代码

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <queue>
#include <map>
#include <stack>
#define N 200005
#define int long long
#define p 100000007

using namespace std;

struct Edge{
	int to;
	int next;
};

Edge edge[2*N];
int head[N], num;

void add(int u, int v) {
	num++;
	edge[num].to = v;
	edge[num].next = head[u];
	head[u] = num;
}

int n, a[N], cnt[N], outside[N], uu[N], vv[N], f[N], fath[N], l, r, ans = 0, lim = 0;

int find(int x) {
	if(f[x] == x) return x;
	return f[x] = find(f[x]);
}

void Merge(int u, int v) {
	int fu = find(u), fv = find(v);
	f[fu] = fv;
}

void dfs(int u, int fa) {
	fath[u] = fa;
	for(int i=head[u]; i; i=edge[i].next) {
		int v = edge[i].to;
		if(v == fa) continue;
		dfs(v, u);
	}
}

bool check(int x) {
	for(int i=1; i<=n; i++) cnt[i] = a[i], f[i] = i;
	for(int i=1; i<=n; i++) {
		if(outside[i] != 0) continue;
		int tmp = i, last = x;
		while(tmp != 0 && last != 0) {
			int sum = min(last, cnt[tmp]);
			cnt[tmp] -= sum;
			last -= sum;
			if(cnt[tmp] == 0) Merge(tmp, fath[tmp]);
			tmp = find(tmp);
		}
	}
	int flag = 0;
	for(int i=1; i<=n; i++) if(cnt[i] > 0) flag = 1;
	if(flag) return 0;
	else return 1; 
}

signed main(void) {
	scanf("%lld", &n);
	for(int i=1; i<n; i++) {
		int pi = 0;
		scanf("%lld", &pi);
		uu[i] = pi, vv[i] = i+1;
		add(uu[i], vv[i]);
		outside[uu[i]]++;
	}
	dfs(1, 0);
	for(int i=1; i<=n; i++) scanf("%lld", &a[i]), lim += a[i];
	l = 0, r = lim;
	while(l <= r) {
		int mid = (l + r) / 2;
		if(check(mid)) r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	cout << ans;
}
```



---

## 作者：Imitators (赞：0)

考试时候想了半天，发现是个水题，写了一发就过pretest了

然后就被学长叉没了.....

![](https://cdn.luogu.com.cn/upload/image_hosting/h98o4hao.png)

这个题不是博弈，而本质其实就是找到一种走的方式，让叶子节点中最大的尽量小。

从下向上合并。

考虑维护：
* 一个`lef[x]`表示`x`的子树中有多少个叶子节点。

* 一个`mx[x]`表示`x`子树中使其叶子节点最大的尽量小，此时最大的大小。

* 一个`dp[x]`表示`x`子树中所有叶子节点与`mx[x]`的差取一个`sigma`

`lef[x]`很好转移，现在我们想要把现在`x`节点的`val`尽量平均的放到`x`所有叶子节点上，也就是想尽量先把`dp[x]`取成0

两种情况:
* `dp[x]>=val` 直接`dp[x]-=val`
* `dp[x]<val` 那就把`dp[x]`取净，然后剩下的平均分在每个叶子节点上。
	* 设平均分出的权值为$z=\lceil \dfrac{val}{lef} \rceil$
	* `val-=dp[x],mx[x]+=z,dp[x]=z*lef[x]`
    
转移完毕，输出`mx[1]`。

`tips:上取证不能用什么 val=(a-1)/b+1`.......

``` cpp
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e5+10;
vector<int>v[N];
int n,m,val[N];
int lef[N];
int mx[N];
int dp[N],x;
inline void dfs(int x)
{
	if(v[x].size()==0)
	{
		lef[x]=1;
		mx[x]=val[x];
		return ;
	}
	for(int i=0;i<v[x].size();i++)
	{
		int y=v[x][i];
		dfs(y);
		
		mx[x]=max(mx[x],mx[y]);	 
	}
	for(int i=0;i<v[x].size();i++)
	{
		int y=v[x][i];
 		lef[x]+=lef[y];
		if(mx[x]>mx[y]) 
		{
			dp[x]+=dp[y]+(mx[x]-mx[y])*lef[y];
		}
		else dp[x]+=dp[y];
	}
	if(dp[x]>val[x])
	{
		dp[x]-=val[x];
		return ;
	}
	else
	{
		val[x]-=dp[x];
        int up=0;
        if(val[x]%lef[x]==0) up=val[x]/lef[x];
        else up=val[x]/lef[x]+1;
		mx[x]+=up;
		dp[x]=up*(lef[x])-val[x];
	}
}
signed main()
{
    //freopen("res","w",stdout);
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=2;i<=n;i++)
	{
		cin>>x;
		v[x].push_back(i);
	}
	for(int i=1;i<=n;i++)
		cin>>val[i];
	dfs(1);
	cout<<mx[1];
    
}
```


---

## 作者：kradcigam (赞：0)

可能是做这题的人中唯一一个用二分的吧。

看着这个题就像二分，我们二分答案 $x$，然后从叶子节点开始递归，往上传值，这个值为最大可以过来的人数。

如果这个值出现负数，那么就说明不行了。

这时候，你会写出类似于这样的代码。

```cpp
int s[500010];
vector<int>v[500010];
int dfs(int x,int y){
	if(!v[x].size())return y-s[x];
	int s=0;
	for(int i:v[x]){
		int z=dfs(i,y);
		if(z<0)return z;
		s+=z;
	}
	return s-::s[x];
}
bool check(int x){
	return dfs(1,x)>=0;
}
int main(){
	int n,s=0;read(n);
	for(int i=2;i<=n;i++){
		int x;read(x);
		v[x].push_back(i);
	}
	for(int i=1;i<=n;i++)read(::s[i]),s+=::s[i];
	int l=-1,r=s;
	while(l+1<r){
		int mid=(l+r)>>1;
		if(check(mid))r=mid;
		else l=mid;
	}cout<<r;
	return 0;
}
```

然后你会发现过不了！开`long long`？没用！开`__int128`？在 $CF$ 上 $AC$ 了，可是想在洛谷上 $AC$ 本题，还得另辟蹊径。

于是，我就开始乱搞。

![QQ图片20201030173352.png](https://i.loli.net/2020/10/30/gpAletiSK5xrYbX.png)

不能 $AC$ 的原因，是因为二分上界设太大就会爆掉。

于是，我试图开始手动设上界，但是第 $88$ 个点的输出太大，我设它的输出为最大值后，第 $5$ 个点就 $WA$ 了。

后来，我开始设置 `unsigned long long`，我本来并不指望这可以 $AC$，但是经过一番改进，它过了！

代码：
```cpp
unsigned long long s[500010];
vector<long long>v[500010];
bool f;
long long dfs(unsigned long long x,unsigned long long y){
	if(f)return 0;//优化
	if(!v[x].size()){
		if(y<s[x]){
			f=1;
			return 0;//优化
		}
		return y-s[x];
	}
	unsigned long long s=0;
	for(int i:v[x]){
		unsigned long long z=dfs(i,y);
		if(z<0){
			f=1;
			return 0;//优化
		}
		s+=z;
	}
	if(s<::s[x]){
		f=1;
		return 0;//优化
	}return s-::s[x];
}
bool check(unsigned long long x){
	f=0;dfs(1,x);
	return !f;
}
int main(){
	int n;read(n);
	for(int i=2;i<=n;i++){
		int x;read(x);
		v[x].push_back(i);
	}
	for(int i=1;i<=n;i++)read(s[i]);
	unsigned long long l=0,r=100188730122209;//第88个点的输出+1
	while(l+1<r){
		unsigned long long mid=(l+r)>>1;
		if(check(mid))r=mid;
		else l=mid;
	}
	if(check(0))puts("0");
	else cout<<r;
	return 0;
}
```

---

## 作者：Fairicle (赞：0)

题目可以抽象为我们将每个节点的人向下发放，使得人数最大的叶子节点人数最少。

那么就有一个思路：对于每个节点 $x$，尝试子树叶子节点的值，也就是子树和除以子树叶子节点数。但因为本题并非人集中在一个点，所以**可能做不到平均**，于是还需要维护一个数组 $mx[x]$ 表示以 $x$ 为根的子树中，叶子节点最大值的最小值为多少。

所以我们要维护的就是子树和 $sum[x]$，子树叶子数 $lf[x]$，子树最大值 $mx[x]$。转移时有 

$sum[x]=\sum_{y\in son(x)}sum[y]+a[x]$

$lf[x]=\sum_{y\in son(x)}lf[y]$

$mx[x]=max(mx[y](y\in son(x)),\left\lceil\dfrac{sum[x]}{lf[x]}\right\rceil)$

code：
```cpp
#define ll long long
#define ri register int
#define N 200010
ll wl,n,a[N],x,y,head[N],lf[N],sum_lf[N],mx_lf[N];
struct node{
	int nxt,to;
}star[N];
inline void add(int from,int to){
	wl++;
	star[wl].to=to;
	star[wl].nxt=head[from];
	head[from]=wl;
}
inline void dfs(int x,int fa){
	if(!head[x]){
		lf[x]++,sum_lf[x]=a[x],mx_lf[x]=max(mx_lf[x],a[x]);
		return;
	}
	sum_lf[x]=a[x];
	for(ri i=head[x];i;i=star[i].nxt){
		int u=star[i].to;
		dfs(u,x);
		lf[x]+=lf[u];
		sum_lf[x]+=sum_lf[u];
		mx_lf[x]=max(mx_lf[x],mx_lf[u]);
	}
	ll ave=(sum_lf[x]+lf[x]-1)/lf[x];
	if(ave>mx_lf[x]) mx_lf[x]=ave;
}
int main()
{
	std::ios::sync_with_stdio(false);
	cin>>n;
	for(ri i=1;i<n;++i){
		int s;
		cin>>s;
		add(s,i+1);
	}
	for(ri i=1;i<=n;++i) cin>>a[i];
	dfs(1,0);
	cout<<mx_lf[1];
    return 0;
}
```


---

