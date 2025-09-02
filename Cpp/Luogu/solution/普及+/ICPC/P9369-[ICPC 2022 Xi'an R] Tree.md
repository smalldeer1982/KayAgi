# [ICPC 2022 Xi'an R] Tree

## 题目描述

给定大小为 $n$ 的有根树 $T$，根节点为 $1$。定义 $\mathrm{subtree}(u)$ 表示结点 $u$ 的子树。

称集合 $S$ 是好的，当且仅当 $S$ 至少满足下列条件之一：

- 对于 $u, v\in S$ 且 $u\neq v$，$u\in \mathrm{subtree}(v)$ 或 $v\in \mathrm{subtree}(u)$。
- 对于 $u, v\in S$ 且 $u\neq v$，$u\notin \mathrm{subtree}(v)$ 且 $v\notin \mathrm{subtree}(u)$。

将 $T$ 划分为若干好的集合，求集合数量的最小值。

共有 $Q$ 组数据。

$1\leq Q\leq 10 ^ 5$，$1\leq n, \sum n\leq 10 ^ 6$，每个点的父亲编号 $1\leq p_i < i$。

## 样例 #1

### 输入

```
2
7
1 1 2 2 2 3
5
1 2 3 4
```

### 输出

```
3
1
```

# 题解

## 作者：StarRain3 (赞：4)

我们可以发现每个点集要么是一个链，要么是不同子树中的许多点。

那么显然，如果我们想要取一个链作为集合，那么只有把这个链一直取到叶子才是最优的。

那么我们考虑把这棵树做长链剖分，假设我们得到了 $p$ 条长链，每条长链的长度为 $lp_i$。

假设我们一开始全都用第二类集合来划分，那么答案显然是整棵树最大的深度。这个答案也可以看做是将所有长链的底端对其以后水平放置，同一行的点划分进一个点集的结果，也就是这些长链的最大长度。显然同一行中的点不存在祖先关系。

考虑贪心选择一些长链作为第一个集合，显然因为第二类集合的数量应该是“剩余长链的最大长度”，所以选择最长的长链必然最优。

将 $lp_i$ 从大到小排序，枚举我们选择了前 $i$ 条长链作为第一类集合，那么剩余的长链作为第二类集合的集合数量是 $lp_{i+1}$，因此答案就是 $i+lp_{i+1}$。

时间复杂度 $O(n)$。

部分代码：
```cpp
void dfs1(int x) {
    for (int y : g[x]) {
        dfs1(y);
        if (len[y] > len[son[x]]) son[x] = y;
    }
    len[x] = len[son[x]] + 1;
}
void dfs2(int x, int l = 0) {
    if (!son[x]) lp.push_back(l);
    else {
        dfs2(son[x], l + 1);
        for (int y : g[x]) if (y != son[x]) dfs2(y, 1);
    }
}
```

[AC记录](https://www.luogu.com.cn/record/111365593)。

---

## 作者：Poole_tea (赞：3)

先来转化一下所给条件。

先看第一个条件，意味着这个集合的点处在同一条链上。

再看第二个条件，意味着这个集合处在不同的链上，处在同一深度。

那么我们将树进行长链剖分，那么假设将长度在前 $x$ 的链当作第一个集合，那么后面的点要么是也是第一个集合，要么是第二个集合，而第二个集合的数量应是剩下链中的长度最大值，假设我们不按照长度一个一个选链，而是跳着选，那么这种一定不会是最优的，你可以手玩几组数据就知道了。于是我们可以进行枚举所选的链，然后再统计答案即可。

有一个坑点，就是别拿邻接表存图，因为多测清空邻接表复杂度有点很高，会 TLE。其他就没了。

Code


```cpp
#include <bits/stdc++.h>
using namespace std ;
const int MAXN = 1e6 + 10 ;
struct edge {
    int to, nxt ;
}e[MAXN] ;
int head[MAXN] ;
int len[MAXN], son[MAXN], siz[MAXN], tot ;
inline int read() {
	register int x = 0, f = 0;
	register char ch = getchar();
	while (ch < '0' || ch > '9')
		f |= ch == '-', ch = getchar();
	while (ch >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
inline void add (int u, int v) {
    e[++tot].to = v ;
    e[tot].nxt = head[u] ;
    head[u] = tot ;
}
inline bool cmp (int x, int y) {
    return x > y ;
}
inline void dfs (int x) {
    for (int i = head[x] ; i ; i = e[i].nxt) {
       int v = e[i].to ;
       dfs(v) ;
       if (siz[son[x]] < siz[v]) son[x] = v ;
    }
    siz[x] = siz[son[x]] + 1 ;
}
inline void redfs (int x, int k) {
    if (!son[x]) len[++tot] = k ;
    else redfs(son[x], k + 1) ;
    for (int i = head[x] ; i ; i = e[i].nxt) {
        int v = e[i].to ;
        if (v != son[x]) redfs (v, 1) ;
    }
}
int main () {
    int t ;
    t = read() ;
    while (t--) {
        int n ;
        n = read() ;
        int x ;
        for (int i = 1 ; i <= n ; i++) head[i] = 0, son[i] = 0 ;
        tot = 0 ;
        for (int i = 2 ; i <= n ; i++) {
            x = read() ;
            add(x, i) ;
        }
        tot = 0 ;
        dfs(1) ;
        redfs(1, 1) ;
        sort(len + 1, len + tot + 1, cmp) ;
        int ans = len[1] ;
        len[tot + 1] = 0 ;
        for (int i = 1 ; i <= tot ; i++) ans = min(i + len[i + 1], ans) ;
        cout << ans << '\n' ;
    }
}
```

---

## 作者：蒟蒻君HJT (赞：3)

来点不一样的做法喵。

首先划分出来的集合有重复也没关系，只要所有点都覆盖到就行。这样的话所有 type1 肯定是选满一条链最优。只用 type1，答案是叶子个数。

然后考虑 type2。假设我们正好有一个 type2 的集合，不难发现这一集合包含所有叶子一定是最优的。

证明：首先这些叶子必然没有祖先后代关系；其次如果我们把一些叶子换成其祖先结点，那么这个叶子到根的链并没有被省下来，也就是这种操作是不优的。因此只有一个 type2 的集合的话必然选出所有叶子。答案就是剩下的叶子个数 $+1$。

归纳下去容易发现每多加一个 type2 的集合就是剥掉当前所有的叶子。而答案就是剥叶子的轮数 $+$ 剩余的叶子个数。

模拟剥叶子过程即可。复杂度线性。

```cpp
#include <bits/stdc++.h>

int n, d[1000005], fa[1000005];

std::vector <int> leaf, tmp;

void solve(){
  scanf("%d", &n);
  for(int i = 1; i <= n; ++i) d[i] = 0;
  for(int i = 2; i <= n; ++i){
    int x; scanf("%d", &x);
    ++d[x]; fa[i] = x;
  }
  leaf.clear(), tmp.clear();
  for(int i = 1; i <= n; ++i) if(!d[i]) leaf.push_back(i);
  int num = 0, ans = 1e9;
  while(leaf.size()){
    ans = std::min(ans, num + (int)leaf.size());
    num += 1;
    for(auto v : leaf) {
      --d[fa[v]];
      if(!d[fa[v]]) tmp.push_back(fa[v]);
    }
    leaf.clear();
    std::swap(leaf, tmp);
  }
  printf("%d\n", ans);
  return ;
}

int main(){
  int T = 1;
  scanf("%d", &T);
  for(int i = 1; i <= T; ++i) solve();
  return 0;
}
```


---

## 作者：Missa (赞：3)

whk 选手做思维题保持手感 /kel

还是好题，思路整体挺顺畅。

力求严密些。

----------------

题意：给定一棵树，定义一个集合是好的当且仅当其满足两点条件中任意一点：

- $\forall u, v \in S$，$u \in \text{subtree}(v)$ 或 $v \in \text{subtree}(u)$。
- $\forall u, v \in S$，$u \not\in \text{subtree}(v)$ 且 $v \not\in \text{subtree}(u)$。

求最小的 $k$，使得可以将树上所有节点不重不漏划分至 $k$ 个好集合中。

--------------

其实不重没什么用，显然好集合的子集也是好集合。

为方便叙述，将根到某点的路径上的点的集合称为一条链，将满足第一个条件的集合称为 A 型集合，将满足第二个条件的集合称为 B 型集合。

B 型集合的条件很奇怪。所以先研究 A 型集合，找到最优解的一个性质，再来处理 B 型集合。

1. 存在最优解的形式形如：有 $m$ 个点（后称为黑点），每个 A 集合是根到其中一个点的路径。

容易发现 A 型集合是一条链的子集。设链的另一端为 $u$。容易发现将根到 $u$ 上整条路径都放进同一集合不劣。

2. 若所有链上白点数目的最大值为 $t$，则再取 $t$ 个 B 集合可以覆盖所有白点。

同链上的点不能属于一个 B 型集合，这就说明了这是下限。

考虑在树上 dfs 的过程，这里增量构造。

只考虑 dfs 时访问的叶结点（一个点处的要求包含其父亲），则一条链上的白点是从其另一端点起的连续的一段路径。忽略掉 lca 处已经被处理过的点，从上到下将
未处理的点合并到 $u$ 链上的点。这样显然不会使用超过 $t$ 个集合。

本质是，点 $u$ 所在集合的编号是【它的祖先中离它最近的的白点】所在集合的编号加一。可以归纳证其合法性。


![img](https://img2023.cnblogs.com/blog/2840104/202305/2840104-20230525222726142-1283489249.png)

枚举几个 B 型集合就行了。那么关键是找到黑点数目的最小值。

3. 设一个点到其子树中叶结点的距离的最大值为 $mx_u$，则若 B 型集合有 $k$ 个，最小化黑点时，黑点恰为所有 $mx=k$ 的点。

若 $mx_u > k$，这个点不该被染黑，因为黑点的子树中不能有黑点。

若 $mx_u < k$，改而将其父亲染黑不劣。

一个点的父亲的 $mx$ 大于它本身的 $mx$，于是存在最优解只使用所有 $mx=k$ 的点，此时必须取全所有 $mx=k$ 的点，故结论得证。

做完了。

一个月没写代码的人一遍写对，很感动。

```cpp
#include <bits/stdc++.h>
const int M = 1e6 + 5;

void solve() {
  int n; scanf("%d", &n);
  std::vector<int> fa(n + 1), mx(n + 1), cnt(n + 1);
  for (int i = 2; i <= n; i++) 
    scanf("%d", &fa[i]);
  for (int i = n; i >= 1; i--) {
    mx[fa[i]] = std::max(mx[fa[i]], mx[i] + 1);
    ++cnt[mx[i]];
  }
  int ans = n;
  for (int i = 0; i <= n; i++)
    ans = std::min(ans, cnt[i] + i);
  printf("%d\n", ans);
}

int main() {
  int T; scanf("%d", &T); while (T--) {
    solve();
  }
  return 0;
}
```

---

## 作者：ZLRest (赞：2)

## 题目大意：
将一棵树上的点分为若干集合，每个集合满足父子关系或非父子关系，
求集合数量的最小值。
## 分析：
显然，满足条件一的点只能是一条链上的点；满足条件二的点是所有深度相同的点，所以集合二的个数即为数的深度。
## 解法：
考虑贪心，找尽量长的长链将链上的点归为一个集合，因为剪去长链后的树的深度即为剩下最长长链的深度，所以这样保证了尽量多的点在一个集合且剩余深度尽量小。寻找长链考虑长链剖分。

长链剖分可以用两遍 dfs 解决。第一遍 dfs 找当前节点子树中链最长的儿子记录下来，第二遍 dfs 遍历树中链的长度。
### 代码：
```cpp
void dfs1(int now){
	for(int i=0;i<v[now].size();i++){
		int y=v[now][i];
		dfs1(y);
		if(siz[son[now]]<siz[y]) son[now]=y;//寻找最长链作为长儿子
	}
	siz[now]=siz[son[now]]+1;// 当前节点的最长链就是他长儿子的长度+1
} 
void dfs2(int now,int len){
    if(!son[now])ans[cnt++]=len;//如果当前节点没有长儿子，就记录长度为链长
    else{
    	dfs2(son[now],len+1);//如果有，就遍历长儿子。
	for(int i=0;i<v[now].size();i++)
            if(v[now][i]!=son[now])dfs2(v[now][i],1); 
    }
   
}
```
### 完整代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x;
}
int T;
int siz[1000100],son[1000010];
int n;
int ans[10000010];
int cnt=0;
vector <int> v[2000010];
void dfs1(int now){
	for(int i=0;i<v[now].size();i++){
	int y=v[now][i];
		dfs1(y);
		if(siz[son[now]]<siz[y]) son[now]=y;
	}
	siz[now]=siz[son[now]]+1;
} 
void dfs2(int now,int len){
    if(!son[now]){
		 ans[cnt++]=len;
	}
    else{
    	dfs2(son[now],len+1);
		for(int i=0;i<v[now].size();i++) if(v[now][i]!=son[now]) dfs2(v[now][i],1); 
    }
   
}
bool cmp(int x,int y){return x>y;}
signed main(){
	T=read();
	while(T--){
	n=read();
	cnt=0;
	for(int i=0;i<=n;i++) son[i]=0,siz[i]=0;
	for(int i=1;i<=n;i++) v[i].clear();
	for(int i=2;i<=n;i++){
		int x=read();
		v[x].push_back(i);
	}
	dfs1(1);
	dfs2(1,1);
	sort(ans,ans+cnt,cmp);
	int anss=cnt;
	for(int i=0;i<cnt;i++) anss=min(anss,i+ans[i]);
	printf("%lld\n",anss);
	
	}
}
```

---

## 作者：KobeBeanBryantCox (赞：1)

# P9369 [ICPC 2022 Xi'an R] Tree 题解

---------------

[题目传送门](https://www.luogu.com.cn/problem/P9369)。

好题啊！

---------------

## 题意

略。

---------------

## 思路

考虑转换一下题目的好集合的条件：

1. 一条从任意一点走到其任意祖先的链。
2. 任意两点没有祖先关系的点集。

考虑只有第一个条件。我们要取最小，那么肯定是每一条链都取到叶子是最优的。答案是链的个数。

考虑只有第二个条件。取最小，所以能取就取，所以答案是最大深度。

考虑把这俩玩意联系起来。

考虑长链剖分（作用：分出来尽可能长的链，以便尽可能减少第一个数量，同时由于从大到小打擂台，所以还能减少第二个的答案）。

考虑怎么联系。我们发现第二个条件其实是每一条链同时从链顶走到链底，每一时刻每一条链当前走到的节点的集合。

考虑把所有链搞出来。然后贪心地选择一些长链，剩余的用第二个条件。

考虑从大到小排序打擂台求最小即可。

时间复杂度是 $O(n\log n)$ 的，瓶颈在排序。

但是链长不超过 $n$，我们能用计数排序优化到 $O(n)$。

-----------------

## AC 代码

```cpp
#include<bits/stdc++.h>
#define Code using
#define by namespace
#define wjb std
Code by wjb;
int in()
{
	int k=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k*f;
}
void out(int x)
{
	if(x<0)putchar('-'),x=-x;
	if(x<10)putchar(x+'0');
	else out(x/10),putchar(x%10+'0');
}
void clear(int);
void sort();
const int N=1e6+10;
vector<int>e[N];
int son[N],len[N];
void init(int u)
{
	for(int v:e[u])
	{
		init(v);
		if(len[u]<len[v]+1)son[u]=v,len[u]=len[v]+1;
	}
}
int chain[N],cnt=0;
void dfs(int u,int id)
{
	chain[id]++;
	if(son[u])dfs(son[u],id);
	for(int v:e[u])if(v!=son[u])dfs(v,++cnt);
}
void work()
{
	int n=in();clear(n);
	for(int i=2;i<=n;i++)e[in()].push_back(i);
	init(1),dfs(1,++cnt);
	sort();
	int ans=n;
	for(int i=0;i<=cnt;i++)ans=min(ans,i+chain[i+1]);
	out(ans),putchar('\n');
}
int t[N];
void sort()
{
	int maxx=0;
	for(int i=1;i<=cnt;i++)t[chain[i]]++,maxx=max(maxx,chain[i]);
	for(int i=maxx,j=1;i>=1;i--)while(t[i])chain[j++]=i,t[i]--;
}
void clear(int n)
{
	cnt=0;
	for(int i=1;i<=n;i++)e[i].clear();
	for(int i=1;i<=n;i++)son[i]=len[i]=0;
	for(int i=1;i<=n;i++)t[i]=chain[i]=0;
}
int main()
{
	for(int t=in();t--;work());
	return 0;
}
```

----------------

~~其实我感觉有下位蓝或上位绿了。。。~~

若有误或不清，欢迎评论或私信。

---

## 作者：SDLTF_凌亭风 (赞：1)

### 大致题意
给定一棵以 $ 1 $ 为根的有根树，将这棵树划分为若干点集。对于每个点集，要么他们是父子关系，要么不是父子关系。 

求最小的集合数。

---
### 思路
只考虑父子关系，那这棵树没什么用了，直接将其看做一条链，也不难想到使用长链剖分解决。

接下来考虑到底怎么剖。假设只使用“不是父子关系”这一条件。

由于树的同一高度上不存在父子关系，那么不难发现集合数量就是这棵树的高度。

接下来我们加入“满足父子关系”这一条件。假设这棵树有 $ k $ 个长链，你选了 $ a(a\leq k) $ 放进 $ a $ 个集合里，这棵树就变成了这样（以选走一条链为例）：

![从高度为4变到高度为3](https://cdn.luogu.com.cn/upload/image_hosting/bgh62o4x.png)

树的高度变成了剩余长链的最大长度。

接下来，对这个剩余的树就有两种做法：要么塞到“满足父子关系”的集合，要门塞到“不满足父子关系”的集合。我们只需要不断地去枚举某一条链“是否满足父子关系”并求出最小值即可。

需要注意的是，可以先对链的长度进行排序。显然，链越长越优。

---
### 部分代码
```cpp
// 长链剖分板子
void dfs(int nowid, int d) {
    for(auto e : Tree[nowid]) {
        dfs(e, d + 1);
        Child[nowid] = (deep[e] > deep[Child[nowid]]) ? e : Child[nowid];
    }
    deep[nowid] = deep[Child[nowid]] + 1;
}

void dfs2(int nowid, int d) {
    if (!Child[nowid]) lis.push_back(d);
    else {
        dfs2(Child[nowid], d + 1);
        for(auto e : Tree[nowid]) {
            if(e == Child[nowid]) continue;
            dfs2(e, 1);
        }
    }
}

...

unsigned long long ans = lis.size();
sort(v.begin(), v.end(), greater<int>());
for(auto e : lis) ans = min(ans, e + i);
```

---

